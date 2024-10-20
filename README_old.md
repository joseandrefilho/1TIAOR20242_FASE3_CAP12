# FIAP - Faculdade de Informática e Administração Paulista

<p align="center">
<a href= "https://www.fiap.com.br/"><img src="assets/logo-fiap.png" alt="FIAP - Faculdade de Informática e Admnistração Paulista" border="0" width=40% height=40%></a>
</p>

<br>

# Sistema Inteligente de Monitoramento Agrícola com ESP32

## Objetivo do Projeto

O objetivo deste projeto é desenvolver um sistema inteligente de monitoramento agrícola que coleta dados ambientais e automatiza o controle de irrigação e a segurança em áreas agrícolas. Para isso, são utilizados quatro sensores conectados ao microcontrolador ESP32, que ajudam a otimizar o uso de recursos como água e luz solar, além de monitorar a presença de intrusos.

## Desenho do Circuito Completo

O sistema utiliza o ESP32 para se comunicar com os seguintes sensores:

1. **DHT22:** Sensor de umidade e temperatura, crucial para o controle de irrigação.
2. **HC-SR04:** Sensor ultrassônico para medir a distância de líquidos em um reservatório, controlando o nível de água disponível.
3. **PIR:** Sensor de movimento que detecta a presença de animais ou pessoas, garantindo a segurança da área monitorada.
4. **LDR:** Sensor de luminosidade que mede a quantidade de luz solar, permitindo ajustes na irrigação com base nas condições de luz.

### Diagrama do Circuito:
Monte o circuito no Wokwi conforme o diagrama abaixo:

- **ESP32** conectado aos sensores:
  - **DHT22:** Conectado ao GPIO 4.
  - **HC-SR04:** Trigger no GPIO 5, Echo no GPIO 18.
  - **PIR:** Conectado ao GPIO 14.
  - **LDR:** Ligado ao GPIO 32 (entrada analógica).

![Diagrama do Circuito](docs/circuito_diagrama.png)

## Descrição do Papel de Cada Sensor no Sistema

1. **DHT22 (Temperatura e Umidade):**
   - Mede a temperatura e umidade do ambiente. Esses dados são usados para controlar a irrigação, aumentando ou diminuindo a quantidade de água fornecida às plantas conforme as condições climáticas.
  
2. **HC-SR04 (Distância de Líquidos):**
   - Mede o nível de água no reservatório de irrigação. Garante que a irrigação só será ativada se houver água suficiente disponível.

3. **PIR (Movimento):**
   - Detecta a presença de pessoas ou animais na área monitorada. Pode ser usado para ativar alarmes de segurança e monitorar áreas restritas.

4. **LDR (Luminosidade):**
   - Monitora a intensidade da luz solar. O sistema ajusta a irrigação com base na quantidade de luz recebida, diminuindo a irrigação em dias ensolarados e aumentando em dias nublados.

## Como Configurar e Rodar o Projeto no Wokwi e ESP32

### Configuração no Wokwi:

1. Acesse o [Wokwi](https://wokwi.com/).
2. Monte o circuito de acordo com o diagrama, conectando os sensores nos pinos corretos do ESP32.
3. Insira o código fonte do projeto na interface do Wokwi.

### Como Rodar no ESP32:

1. **Passo 1:** Abra a IDE Arduino (ou qualquer outra IDE compatível com o ESP32).
2. **Passo 2:** Instale as bibliotecas necessárias:
   - **DHT.h** para o sensor DHT22.
   - **Ultrasonic.h** para o sensor ultrassônico HC-SR04.
3. **Passo 3:** Faça upload do código para o ESP32 via cabo USB.
4. **Passo 4:** Abra o Monitor Serial para visualizar as leituras dos sensores e as ações automatizadas, como controle de irrigação ou detecção de movimento.

### Link para simulação no Wokwi:

- [Simulação no Wokwi](https://wokwi.com/projects/412291283723852801)

## Instruções de Instalação e Dependências

### Dependências

1. **Bibliotecas necessárias:**
   - `DHT.h`: Para o sensor DHT22.
   - `Ultrasonic.h`: Para o sensor HC-SR04.
2. **Instalação de Bibliotecas:**
   - Na IDE Arduino, vá para **Sketch > Incluir Biblioteca > Gerenciar Bibliotecas** e instale as bibliotecas mencionadas.

### Estrutura do Repositório

Dentre os arquivos e pastas presentes na raiz do projeto, definem-se:

- **assets**: Contém imagens e outros arquivos de mídia relacionados ao projeto, como logotipos e diagramas.
- **docs**: Diretório que contém a documentação completa do projeto, incluindo a descrição do sistema, explicações detalhadas sobre cada sensor e o diagrama do circuito utilizado.
- **src**: Contém o código-fonte principal do projeto, incluindo o arquivo principal da lógica e funções auxiliares para o funcionamento dos sensores.
- **tests**: Contém os testes automatizados ou manuais para verificar o funcionamento correto de cada sensor e funcionalidades do projeto.
- **README.md**: Arquivo de guia e explicação geral sobre o projeto (este que você está lendo agora).

### Estrutura de diretórios:

```plaintext
/
├── assets/
│   ├── logo-fiap.png           # Logo da FIAP
├── docs/
│   ├── README.md               # Documentação do projeto
│   ├── circuito_diagrama.png   # Diagrama do circuito
├── src/
│   ├── sketch.ino              # Código-fonte principal do projeto
│   ├── sensor_functions.h      # Funções auxiliares para os sensores
├── tests/
│   └── test_sensors.ino        # Testes automatizados para cada sensor
├── README.md                   # Página inicial do projeto com informações gerais

```

## Testes Realizados

### Testes de Funcionamento:
1. **DHT22:** O sensor foi testado para garantir a leitura correta da umidade e temperatura do ambiente.
2. **HC-SR04:** O sensor de ultrassom foi testado para medir corretamente a distância no reservatório de água.
3. **PIR:** O sensor de movimento detectou com precisão a presença de animais ou pessoas no ambiente monitorado.
4. **LDR:** O sensor LDR foi testado para garantir que ele ajusta a irrigação com base na intensidade da luz solar.

### Prints do Monitor Serial:

#### Exemplo de Leitura do Monitor Serial:

```plaintext
Temperatura: 25.3 ºC
Umidade: 45%
Nível de Água: 10 cm
Luminosidade: 300
Irrigação ativada!
Movimento Detectado!
```

Esses valores indicam que o sistema está funcionando corretamente, ativando a irrigação com base nas leituras e detectando movimento.
