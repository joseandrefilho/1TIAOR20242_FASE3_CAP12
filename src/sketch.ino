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

void setup()
{
    Serial.begin(115200);   // Inicializando a comunicação serial com uma taxa de 115200 bps (para exibir informações no monitor serial)
    pinMode(PIRPIN, INPUT); // Configurando o pino do sensor PIR como entrada
    pinMode(LDRPIN, INPUT); // Configurando o pino do sensor LDR como entrada (analógico)
    dht.begin();            // Inicializando o sensor DHT22
}

void loop()
{
    // Chama as funções de leitura dos sensores e armazena os valores em variáveis
    float temperatura = lerTemperatura(); // Lê a temperatura ambiente do DHT22
    float umidade = lerUmidade();         // Lê a umidade do DHT22
    float distanciaAgua = lerNivelAgua(); // Lê o nível de água no reservatório usando o HC-SR04
    int movimento = detectarMovimento();  // Verifica se há movimento detectado pelo PIR
    int luzAmbiente = lerLuminosidade();  // Lê o nível de luminosidade ambiente usando o LDR

    // Controle da irrigação com base nos valores lidos dos sensores
    controlarIrrigacao(temperatura, umidade, distanciaAgua, luzAmbiente, movimento);

    delay(2000); // Pausa de 2 segundos entre as leituras para dar tempo ao sistema de atualizar os sensores
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

// Função para controlar a irrigação com base nas leituras dos sensores
// Função para controlar a irrigação
void controlarIrrigacao(float temp, float umidade, float nivelAgua, int luzAmbiente, int movimento)
{
    // Se houver movimento, a irrigação não será ativada
    if (movimento == HIGH)
    {
        Serial.println("Movimento detectado! Irrigação não será ativada.");
        return; // Sai da função para não prosseguir com a irrigação
    }

    // Condições normais para ativar a irrigação se não houver movimento detectado
    if (umidade < 40 && nivelAgua > 10 && luzAmbiente < 500)
    {
        Serial.println("Irrigação ativada!");
        // Aqui você pode adicionar o código para ligar a bomba d'água
    }
    else
    {
        Serial.println("Irrigação desativada.");
    }
}
