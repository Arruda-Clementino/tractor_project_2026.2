
---
# Microcontroladores usados no sistema:

![[Pasted image 20261113075645.png|479]]



---
# Sensor BMP280

É o **componente físico** (o chip). Ele mede temperatura e pressão atmosférica. 

| ![[Pasted image 20260908154712.png\|130]] | ![[Pasted image 20260908154726.png\|126]] |
| ----------------------------------------- | ----------------------------------------- |

## (Barramento SPI)

|**Pino no Módulo BMP280**|**Pino no Arduino Mega (Número)**|**Onde achar na placa (fora dos círculos)**|
|---|---|---|
|**CSB** (ou `CS`)|**Pino Digital 24**|Barra lateral direita: **2º furo da coluna esquerda**|
|**SCL** (ou `SCK`)|**Pino Digital 26**|Barra lateral direita: **3º furo da coluna esquerda**|
|**SDA** (ou `SDI` / `MOSI`)|**Pino Digital 28**|Barra lateral direita: **4º furo da coluna esquerda**|
|**SDO** (ou `MISO`)|**Pino Digital 30**|Barra lateral direita: **5º furo da coluna esquerda**|
|**VCC**|**3.3V** _(dividido com o RFID)_|Barra `POWER` embaixo: **3º furo** (após `IOREF` e `RESET`)|
|**GND**|**GND** _(ao lado do pino 13)_|Régua superior: **1º furo à esquerda do pino 13**|

_**atenção:** Como este módulo possui 6 pinos para suportar tanto I2C quanto SPI, os pinos `CSB` e `SDO` precisam ser polarizados para travar o sensor no modo **I2C** nos pinos dedicados do Mega.

---
# RFID - RC522

Esse componente é um **Módulo Leitor e Gravador RFID**, modelo **[RFID-RC522](https://www.google.com/search?ibp=oshop&prds=pvt:hg,pvo:29,mid:576462783695185363,imageDocid:14421490267531210180,gpcid:13768523787844020742,headlineOfferDocid:12984525687558684029,catalogid:9753837786186068883,productDocid:14679060500273737649&q=product&sa=X&ved=2ahUKEwjxtdOK7f-XAxXUuJUCHZthH9kQxa4PegYIAAgNEAE)** (baseado no chip **MFRC522** da NXP).Ele possui **8 pinos** na lateral esquerda e utiliza o protocolo de comunicação **SPI** para conversar com o microcontrolador.

![[Pasted image 20261111085514.png|221]]

## (Barramento SPI)

| **Pino no Módulo RFID** | **Onde ligar no Arduino Mega** |
| ----------------------- | ------------------------------ |
| **SDA (SS)**            | **Pino Digital 9**             |
| **SCK**                 | **Pino Digital 5**             |
| **MOSI**                | **Pino Digital 6**             |
| **MISO**                | **Pino Digital 7**             |
| **RST**                 | **Pino Digital 8**             |
| **IRQ**                 | **Não conectar**               |
| **3.3V**                | **3.3V (Compartilhado)**       |
| **GND**                 | **GND livre**                  |

---
# Módulo DHT22

**Módulo Sensor de Temperatura e Umidade**, modelo **DHT22** (também conhecido comercialmente como **AM2302**). Ele mede a **temperatura** e a **umidade relativa do ar** do ambiente ao mesmo tempo e envia esses valores em formato digital para o microcontrolador.

![[Pasted image 20261111090925.png|252]]

## (Pino Digital)

| **Pino no Módulo** | **Função**           | **Onde conectar (Arduino Mega)** | **Explicação da Conexão**                                                                              |
| ------------------ | -------------------- | -------------------------------- | ------------------------------------------------------------------------------------------------------ |
| **VCC**            | Alimentação Positiva | **5V**                           | Fornece energia para o circuito interno do sensor funcionar, aceitando de 3,3V a 5V.                   |
| **GND**            | Terra (0V)           | **GND**                          | Referência negativa da alimentação elétrica.                                                           |
| **DAT**            | Dados Digitais       | **Pino Digital 2**               | Transmite os sinais digitais com os valores de temperatura e umidade relativa do ar lidos pelo sensor. |
_**atenção:** O DHT22 transmite seus dados em formato digital por um único fio, sendo alocado no início da régua de comunicação digital do Mega.

---
# GY-NEO6MV2

**Módulo Receptor GPS**, modelo **GY-NEO6MV2** (equipado com o chip **u-blox NEO-6M**). Ele capta sinais de satélites GPS em órbita e envia as informações de posicionamento para o microcontrolador por meio de comunicação serial.

![[Pasted image 20261111091352.png|208]]

## (Barramento UART / Serial1)

| **Pino no Módulo** | **Função**           | **Onde conectar (Arduino Mega)** | **Explicação da Conexão**                                                                                                                     |
| ------------------ | -------------------- | -------------------------------- | --------------------------------------------------------------------------------------------------------------------------------------------- |
| **VCC**            | Alimentação Positiva | **5V**                           | Fornece energia ao módulo, que aceita de 3,3V a 5V graças ao regulador de tensão interno.                                                     |
| **GND**            | Terra (0V)           | **GND**                          | Referência negativa da alimentação elétrica.                                                                                                  |
| **TX**             | Transmissão Serial   | **Pino 19 (RX1)**                | Envia os dados de localização (protocolo NMEA) do GPS para o microcontrolador, exigindo ligação cruzada com o pino de recepção (RX) da placa. |
| **RX**             | Recepção Serial      | **Pino 18 (TX1)**                | Recebe comandos e configurações enviados pelo microcontrolador, exigindo ligação cruzada com o pino de transmissão (TX) da placa.             |
_**atenção:** O GPS utiliza comunicação serial e deve ser ligado à porta **Serial1** dedicada do Arduino Mega para não disputar processamento com os outros sensores

---
|Sensor|Pinos no Mega|
|
|GPS|Serial1 (19 e 18), 9600 baud|
|DHT22|2|
|BMP280|CS 24, SCK 26, MOSI 28, MISO 30|
|RFID|SS 9, SCK 5, MOSI 6, MISO 7, RST 8|