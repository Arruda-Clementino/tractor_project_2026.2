
---
# Sensor BMP280

É o **componente físico** (o chip). Ele mede temperatura e pressão atmosférica. Para conversar com a placa (Raspberry Pi), ele usa um protocolo de comunicação serial por fios chamado **I2C**.

| ![[Pasted image 20260908154712.png\|130]] | ![[Pasted image 20260908154726.png\|126]] |
| ----------------------------------------- | ----------------------------------------- |

## (Barramento I2C)

| **Pino no Módulo** | **Função**              | **Onde conectar (Arduino Mega)** | **Explicação da Conexão**                                                                              |
| ------------------ | ----------------------- | -------------------------------- | ------------------------------------------------------------------------------------------------------ |
| **VCC**            | Alimentação Positiva    | **3.3V**                         | Alimenta o chip BMP280 com tensão lógica segura de 3,3V.                                               |
| **GND**            | Terra (0V)              | **GND**                          | Referência negativa da alimentação elétrica.                                                           |
| **SDA / SDI**      | Dados Seriais (I2C)     | **Pino 20 (SDA)**                | Transporta os dados de temperatura e pressão atmosférica pelo pino I2C dedicado do Arduino Mega.       |
| **SCL / SCK**      | Clock Serial (I2C)      | **Pino 21 (SCL)**                | Sincroniza a comunicação I2C usando o pino de clock dedicado do Arduino Mega.                          |
| **CSB**            | Chip Select             | **3.3V**                         | Precisa ser mantido em nível lógico ALTO para ativar o protocolo I2C e desativar o modo SPI.           |
| **SDO**            | Seletor de Endereço I2C | **GND**                          | Define o endereço de comunicação do sensor no barramento I2C; ligado ao GND fixa o endereço em `0x76`. |
_**atenção:** Como este módulo possui 6 pinos para suportar tanto I2C quanto SPI, os pinos `CSB` e `SDO` precisam ser polarizados para travar o sensor no modo **I2C** nos pinos dedicados do Mega.

---
# RFID - RC522

Esse componente é um **Módulo Leitor e Gravador RFID**, modelo **[RFID-RC522](https://www.google.com/search?ibp=oshop&prds=pvt:hg,pvo:29,mid:576462783695185363,imageDocid:14421490267531210180,gpcid:13768523787844020742,headlineOfferDocid:12984525687558684029,catalogid:9753837786186068883,productDocid:14679060500273737649&q=product&sa=X&ved=2ahUKEwjxtdOK7f-XAxXUuJUCHZthH9kQxa4PegYIAAgNEAE)** (baseado no chip **MFRC522** da NXP).Ele possui **8 pinos** na lateral esquerda e utiliza o protocolo de comunicação **SPI** para conversar com o microcontrolador.

![[Pasted image 20261111085514.png|221]]

## (Barramento SPI)

| **Pino no Módulo** | **Função**           | **Onde conectar (Arduino Mega)** | **Explicação da Conexão**                                                                                        |
| ------------------ | -------------------- | -------------------------------- | ---------------------------------------------------------------------------------------------------------------- |
| **3.3V**           | Alimentação Positiva | **3.3V**                         | Fornece energia para o circuito funcionar (não deve ser ligado em 5V).                                           |
| **GND**            | Terra (0V)           | **GND**                          | Referência negativa da alimentação elétrica.                                                                     |
| **SDA**            | Slave Select (SS)    | **Pino Digital 53**              | Ativa ou desativa a comunicação com o leitor no barramento SPI; o pino 53 é o SS nativo do Mega.                 |
| **SCK**            | Serial Clock         | **Pino Digital 52**              | Sincroniza a transmissão de dados enviando pulsos de clock pelo barramento SPI de hardware.                      |
| **MOSI**           | Master Out Slave In  | **Pino Digital 51**              | Envia comandos e dados do Arduino Mega (Mestre) para o leitor RFID (Escravo).                                    |
| **MISO**           | Master In Slave Out  | **Pino Digital 50**              | Envia os dados lidos da tag/cartão RFID de volta para o Arduino Mega.                                            |
| **RST**            | Reset                | **Pino Digital 49**              | Reinicia o módulo ou o coloca em modo de economia de energia, posicionado fisicamente ao lado do barramento SPI. |
| **IRQ**            | Interrupt Request    | **Não conectar**                 | Avisa quando um cartão entra no campo de leitura, mas é mantido desconectado na operação padrão.                 |
_**atenção:** O leitor RFID utiliza o protocolo  SPI. No Arduino Mega, os pinos físicos desse barramento ficam na fileira dupla traseira (pinos 50 a 53), liberando os pinos digitais frontais.

---
# Módulo DHT22

**Módulo Sensor de Temperatura e Umidade**, modelo **DHT22** (também conhecido comercialmente como **AM2302**). Ele mede a **temperatura** e a **umidade relativa do ar** do ambiente ao mesmo tempo e envia esses valores em formato digital para o microcontrolador.

![[Pasted image 20261111090925.png|252]]

## (Pino Digital)

|**Pino no Módulo**|**Função**|**Onde conectar (Arduino Mega)**|**Explicação da Conexão**|
|---|---|---|---|
|**VCC**|Alimentação Positiva|**5V**|Fornece energia para o circuito interno do sensor funcionar, aceitando de 3,3V a 5V.|
|**GND**|Terra (0V)|**GND**|Referência negativa da alimentação elétrica.|
|**DAT**|Dados Digitais|**Pino Digital 2**|Transmite os sinais digitais com os valores de temperatura e umidade relativa do ar lidos pelo sensor.|
_**atenção:** O DHT22 transmite seus dados em formato digital por um único fio, sendo alocado no início da régua de comunicação digital do Mega.

---
# GY-NEO6MV2

**Módulo Receptor GPS**, modelo **GY-NEO6MV2** (equipado com o chip **u-blox NEO-6M**). Ele capta sinais de satélites GPS em órbita e envia as informações de posicionamento para o microcontrolador por meio de comunicação serial.

![[Pasted image 20261111091352.png|208]]

## (Barramento UART / Serial1)

|**Pino no Módulo**|**Função**|**Onde conectar (Arduino Mega)**|**Explicação da Conexão**|
|---|---|---|---|
|**VCC**|Alimentação Positiva|**5V**|Fornece energia ao módulo, que aceita de 3,3V a 5V graças ao regulador de tensão interno.|
|**GND**|Terra (0V)|**GND**|Referência negativa da alimentação elétrica.|
|**TX**|Transmissão Serial|**Pino 19 (RX1)**|Envia os dados de localização (protocolo NMEA) do GPS para o microcontrolador, exigindo ligação cruzada com o pino de recepção (RX) da placa.|
|**RX**|Recepção Serial|**Pino 18 (TX1)**|Recebe comandos e configurações enviados pelo microcontrolador, exigindo ligação cruzada com o pino de transmissão (TX) da placa.|
_**atenção:** O GPS utiliza comunicação serial e deve ser ligado à porta **Serial1** dedicada do Arduino Mega para não disputar processamento com os outros sensores

---
