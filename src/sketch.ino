#include <DHT.h>        // Biblioteca para o sensor de umidade e temperatura DHT22
#include <Ultrasonic.h> // Biblioteca para o sensor de ultrassom HC-SR04

// Definindo os pinos onde os sensores estão conectados
#define DHTPIN 4      // Pino de dados do DHT22 (conectado ao GPIO 4 do ESP32)
#define DHTTYPE DHT22 // Definindo o tipo de sensor DHT (DHT22)
#define TRIGPIN 5     // Pino Trigger do HC-SR04 (conectado ao GPIO 5 do ESP32)
#define ECHOPIN 18    // Pino Echo do HC-SR04 (conectado ao GPIO 18 do ESP32)
#define PIRPIN 14     // Pino do sensor PIR (conectado ao GPIO 14 do ESP32)
#define LDRPIN 32     // Pino do sensor LDR (conectado ao GPIO 32 do ESP32, que lê valores analógicos)

DHT dht(DHTPIN, DHTTYPE);                // Criando o objeto dht com o pino e o tipo do sensor
Ultrasonic ultrasonic(TRIGPIN, ECHOPIN); // Criando o objeto ultrasonic com os pinos Trigger e Echo

// Definição de constantes para facilitar a manutenção e ajuste do sistema
const float UMIDADE_MINIMA = 40.0;
const float TEMPERATURA_IDEAL_MIN = 24.0;
const float TEMPERATURA_IDEAL_MAX = 30.0;
const float TEMPERATURA_ALTA = 30.0;
const int LUMINOSIDADE_ALTA = 500;

void setup()
{
    Serial.begin(115200);   // Inicializando a comunicação serial com uma taxa de 115200 bps (para exibir informações no monitor serial)
    pinMode(PIRPIN, INPUT); // Configurando o pino do sensor PIR como entrada
    pinMode(LDRPIN, INPUT); // Configurando o pino do sensor LDR como entrada (analógico)
    dht.begin();            // Inicializando o sensor DHT22
}

// Função principal
void loop()
{
    // Monitoramento climático
    float temperatura = lerTemperatura(); // Função para ler temperatura do DHT22
    float umidade = lerUmidade();         // Função para ler umidade do DHT22

    // Controle de irrigação automatizada
    float distanciaAgua = lerNivelAgua(); // Função para ler nível de água com o HC-SR04

    // Detecção de presença
    int movimento = detectarMovimento(); // Função para ler estado do PIR

    // Ajuste de irrigação com base na luminosidade
    int luzAmbiente = lerLuminosidade(); // Função para ler luminosidade com o LDR

    // Controlar a irrigação com base na temperatura, umidade, nível de água e luminosidade
    controlarIrrigacao(temperatura, umidade, distanciaAgua, luzAmbiente, movimento);

    delay(2000); // Pausa para evitar leitura contínua
}

// Função para ler a temperatura do DHT22
float lerTemperatura()
{
    float temp = dht.readTemperature(); // Chama a função para ler a temperatura do sensor DHT22
    if (isnan(temp))
    {                                              // Verifica se a leitura é válida (não é NaN - Not a Number)
        Serial.println("Erro ao ler temperatura"); // Imprime uma mensagem de erro se a leitura falhar
        return 0;                                  // Retorna 0 como valor padrão em caso de erro
    }
    Serial.print("Temperatura: "); // Imprime a mensagem "Temperatura: " no monitor serial
    Serial.println(temp);          // Imprime o valor da temperatura no monitor serial
    return temp;                   // Retorna o valor lido da temperatura
}

// Função para ler a umidade do DHT22
float lerUmidade()
{
    float humidity = dht.readHumidity(); // Chama a função para ler a umidade do sensor DHT22
    if (isnan(humidity))
    {                                          // Verifica se a leitura é válida (não é NaN)
        Serial.println("Erro ao ler umidade"); // Imprime uma mensagem de erro se a leitura falhar
        return 0;                              // Retorna 0 como valor padrão em caso de erro
    }
    Serial.print("Umidade: "); // Imprime a mensagem "Umidade: " no monitor serial
    Serial.println(humidity);  // Imprime o valor da umidade no monitor serial
    return humidity;           // Retorna o valor lido da umidade
}

// Função para ler o nível de água no reservatório usando o HC-SR04
float lerNivelAgua()
{
    float distancia = ultrasonic.read(); // Chama a função para ler a distância medida pelo ultrassom
    Serial.print("Nivel de Agua: ");     // Imprime a mensagem "Nível de Água: " no monitor serial
    Serial.println(distancia);           // Imprime o valor da distância (nível de água) no monitor serial
    return distancia;                    // Retorna o valor da distância
}

// Função para detectar movimento com o PIR
int detectarMovimento()
{
    int movimento = digitalRead(PIRPIN); // Lê o estado do pino do sensor PIR (se há movimento ou não)
    if (movimento == HIGH)
    {                                           // Se o valor lido for HIGH, significa que há movimento
        Serial.println("Movimento Detectado!"); // Imprime a mensagem de detecção de movimento
    }
    return movimento; // Retorna o valor (HIGH ou LOW) indicando se houve movimento
}

// Função para ler a luminosidade com o LDR (sensor de luz)
int lerLuminosidade()
{
    int valorLuz = analogRead(LDRPIN); // Lê o valor analógico do pino do LDR (intensidade de luz)
    Serial.print("Luminosidade: ");    // Imprime a mensagem "Luminosidade: " no monitor serial
    Serial.println(valorLuz);          // Imprime o valor da luminosidade no monitor serial
    return valorLuz;                   // Retorna o valor lido da luminosidade
}

// Função auxiliar para ativar irrigação e exibir mensagens
void ativarIrrigacao(float aguaNecessaria, float nivelAgua)
{
    if (nivelAgua >= aguaNecessaria)
    {
        Serial.print("Nível de água suficiente: ");
        Serial.print(nivelAgua);
        Serial.println(" cm, ativando irrigação.");
        // Lógica para ativar a irrigação (por exemplo, ligar a bomba)
    }
    else
    {
        Serial.print("Nível de água insuficiente: ");
        Serial.print(nivelAgua);
        Serial.print(" cm, necessário: ");
        Serial.print(aguaNecessaria);
        Serial.println(" cm. Irrigação não será ativada.");
        // Sai da função se não houver água suficiente
    }
}

// Função principal para controlar a irrigação
void controlarIrrigacao(float temperatura, float umidade, float nivelAgua, int luzAmbiente, int movimento)
{
    // Se houver movimento detectado, a irrigação não será ativada
    if (movimento == HIGH)
    {
        Serial.println("Movimento detectado! Irrigação não será ativada.");
        return; // Sai da função, impedindo a irrigação
    }

    // Verificar se a umidade está abaixo do ideal
    if (umidade < UMIDADE_MINIMA)
    {
        Serial.println("Umidade baixa, avaliando necessidade de irrigação...");

        // Definir volume de água necessário com base na temperatura e luminosidade
        float aguaNecessaria;

        // Verificar se a temperatura está no intervalo ideal
        if (temperatura >= TEMPERATURA_IDEAL_MIN && temperatura <= TEMPERATURA_IDEAL_MAX)
        {
            Serial.println("Temperatura ideal, avaliando luminosidade...");

            // Avaliar luminosidade para definir intensidade da irrigação
            if (luzAmbiente > LUMINOSIDADE_ALTA)
            {
                Serial.println("Dia ensolarado, ativando irrigação intensa.");
                aguaNecessaria = 20.0; // Exemplo: 20 cm de água necessária
            }
            else
            {
                Serial.println("Dia nublado, ativando irrigação leve.");
                aguaNecessaria = 10.0; // Exemplo: 10 cm de água necessária
            }

            // Verificar se a temperatura é alta
        }
        else if (temperatura > TEMPERATURA_ALTA)
        {
            Serial.println("Temperatura alta, avaliando luminosidade...");

            // Avaliar luminosidade para ajustar a irrigação em alta temperatura
            if (luzAmbiente > LUMINOSIDADE_ALTA)
            {
                Serial.println("Dia ensolarado com alta temperatura, ativando irrigação muito intensa.");
                aguaNecessaria = 25.0; // Exemplo: 25 cm de água necessária
            }
            else
            {
                Serial.println("Dia nublado com alta temperatura, ativando irrigação moderada.");
                aguaNecessaria = 15.0; // Exemplo: 15 cm de água necessária
            }

            // Temperatura abaixo do ideal
        }
        else
        {
            Serial.println("Temperatura baixa, ativando irrigação leve.");
            aguaNecessaria = 10.0; // Exemplo: 10 cm de água necessária
        }

        // Ativar irrigação com base no nível de água e necessidade calculada
        ativarIrrigacao(aguaNecessaria, nivelAgua);
    }
    else
    {
        Serial.println("Umidade adequada, irrigação não necessária.");
    }
}
