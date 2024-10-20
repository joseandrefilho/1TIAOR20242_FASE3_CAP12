# FIAP - Faculdade de Informática e Administração Paulista

<p align="center">
<a href= "https://www.fiap.com.br/"><img src="assets/logo-fiap.png" alt="FIAP - Faculdade de Informática e Admnistração Paulista" border="0" width=40% height=40%></a>
</p>

<br>

# Sistema Inteligente de Monitoramento Agrícola com ESP32

## Integrantes: 
- <a href="https://www.linkedin.com/in/joseandrefilho">Jose Andre Filho</a>

## Professores:
### Tutor(a) 
- <a href="https://www.linkedin.com/in/lucas-gomes-moreira-15a8452a/">Lucas Gomes Moreira</a>
### Coordenador(a)
- <a href="https://www.linkedin.com/in/profandregodoi/">André Godoi Chiovato</a>

## Objetivo do Projeto

O objetivo deste projeto é desenvolver um sistema inteligente de monitoramento agrícola utilizando o microcontrolador ESP32 e sensores diversos para coletar dados ambientais e automatizar decisões, como o controle de irrigação e a vigilância em áreas monitoradas.

O sistema combina sensores para medir umidade, temperatura, nível de água, movimento e luminosidade, garantindo que a irrigação seja acionada automaticamente com base nas condições do ambiente, exceto quando houver detecção de movimento no local.

## Estrutura do Repositório

```plaintext
/
├── assets/
│   ├── logo-fiap.png           # Logo da FIAP
├── docs/
│   ├── README.md               # Documentação detalhada do projeto
│   ├── circuito_diagrama.png   # Diagrama do circuito utilizado
├── src/
│   ├── sketch.ino              # Código-fonte principal
├── tests/
│   └── README.md               # Documentação dos testes dos sensores e funções do projeto
│   └── *.png                   # Prints dos testes dos sensores e funções do projeto utilizados no README
├── README.md                   # Este arquivo
```

## Desenho do Circuito Completo

O projeto utiliza o ESP32 como microcontrolador e é conectado aos seguintes sensores:

1. **DHT22 (Temperatura e Umidade):** Conectado ao GPIO 4.
2. **HC-SR04 (Nível de Água):** Trigger no GPIO 5 e Echo no GPIO 18.
3. **PIR (Movimento):** Conectado ao GPIO 14.
4. **LDR (Luminosidade):** Conectado ao GPIO 32 (entrada analógica).

### Diagrama do Circuito

Inclua o diagrama abaixo para conectar corretamente os sensores ao ESP32.

![Diagrama do Circuito](docs/circuito_diagrama.png)

## Como Configurar e Rodar o Projeto no Wokwi e ESP32

### No Wokwi

1. Acesse o [Wokwi.com](https://wokwi.com/).
2. Monte o circuito conforme o diagrama e insira o código-fonte disponível na pasta `/src`.
3. Utilize o ESP32 como microcontrolador na simulação.
4. Verifique os dados dos sensores no Monitor Serial do Wokwi para garantir que o sistema está funcionando corretamente.

### Simulação no Wokwi

Você pode visualizar e interagir com a simulação do projeto no Wokwi clicando no link abaixo:

[![Simulação no Wokwi](docs/circuito_diagrama.png)](https://wokwi.com/projects/412291283723852801)

Clique na imagem acima ou [aqui](https://wokwi.com/projects/412291283723852801) para acessar a simulação.

### No ESP32

1. Abra a **IDE Arduino**.
2. Instale as bibliotecas necessárias:
   - `DHT.h` para o sensor DHT22.
   - `Ultrasonic.h` para o sensor HC-SR04.
3. Conecte o ESP32 ao computador via USB e faça o upload do código.
4. Abra o Monitor Serial na IDE para acompanhar as leituras dos sensores em tempo real.

## Instruções de Instalação e Dependências

- **Bibliotecas necessárias:** `DHT.h`, `Ultrasonic.h` (instaláveis via IDE Arduino).
- **Plataforma:** Wokwi.com ou IDE Arduino para simulações e deploy no ESP32.
- **Hardware:** ESP32, DHT22, HC-SR04, PIR, LDR.

## Contribuição e Versionamento

- **Branch principal:** `main`.
- **Branch de desenvolvimento:** `develop`.
- Os Pull Requests devem ser criados a partir da branch `develop` e revisados por antes de serem fundidos à `main`.
