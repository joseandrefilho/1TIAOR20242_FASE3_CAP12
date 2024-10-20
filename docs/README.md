# FIAP - Faculdade de Informática e Administração Paulista

<p align="center">
<a href= "https://www.fiap.com.br/"><img src="../assets/logo-fiap.png" alt="FIAP - Faculdade de Informática e Admnistração Paulista" border="0" width=40% height=40%></a>
</p>

<br>

# Documentação do Sistema de Monitoramento Agrícola

## Integrantes

- <a href="https://www.linkedin.com/in/joseandrefilho">Jose Andre Filho</a>

## Professores

### Tutor(a)

- <a href="https://www.linkedin.com/in/lucas-gomes-moreira-15a8452a/">Lucas Gomes Moreira</a>

### Coordenador(a)

- <a href="https://www.linkedin.com/in/profandregodoi/">André Godoi Chiovato</a>

## Descrição Geral do Sistema

O sistema utiliza quatro sensores conectados ao ESP32 para monitorar variáveis ambientais em uma fazenda, permitindo a automação de irrigação e a vigilância de segurança. O sistema coleta dados de temperatura, umidade, nível de água, luminosidade e presença de movimento, ajustando automaticamente a irrigação conforme a necessidade.

### Sensores Utilizados

1. **DHT22 (Sensor de Temperatura e Umidade):**
   - Mede a temperatura e umidade do ambiente. Esses dados são fundamentais para o controle da irrigação, evitando desperdícios e otimizando a quantidade de água usada nas plantas.

2. **HC-SR04 (Sensor de Ultrassom):**
   - Mede a distância até a superfície da água em um reservatório. O sistema utiliza essa medida para garantir que a irrigação só ocorra se houver água suficiente disponível no tanque.

3. **PIR (Sensor de Movimento):**
   - Detecta a presença de animais ou pessoas em áreas monitoradas, sendo útil para a segurança e a vigilância da fazenda.

4. **LDR (Sensor de Luz):**
   - Monitora a intensidade da luz solar, permitindo ajustar a quantidade de água usada na irrigação. Em dias ensolarados, a irrigação é reduzida, e em dias nublados ou com baixa luminosidade, a irrigação é aumentada.

### Desenho do Circuito

O diagrama abaixo ilustra a conexão dos sensores ao microcontrolador ESP32:

![Diagrama do Circuito](circuito_diagrama.png)

### Funcionalidades Implementadas

1. **Monitoramento Climático:**
   - O sensor DHT22 coleta dados de temperatura e umidade, ajustando a irrigação de acordo com as condições climáticas.

2. **Controle Automatizado de Irrigação:**
   - O sensor HC-SR04 monitora o nível de água no reservatório e aciona a irrigação apenas quando há água disponível.

3. **Vigilância e Segurança:**
   - O sensor PIR detecta movimento em áreas monitoradas e pode ativar alarmes ou registrar presença no sistema.

4. **Ajuste de Irrigação por Luminosidade:**
   - O sensor LDR mede a intensidade da luz solar e ajusta automaticamente a irrigação, utilizando mais água em dias nublados e menos em dias ensolarados.