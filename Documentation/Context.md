
---

O projeto consiste no desenvolvimento de um 'Trator' de sensores, onde será monitorado a temperatura, pressão, umidade e localização do mesmo. Neste projeto, também será desenvolvido 3 tipos de implementos (engates) para o trator, sendo identificados e diferenciados via tags RFID (RC522).

Os sensores selecionados para a captura dos dados e monitoramento do status do trator serão um BMP280 para a análise da temperatura e pressão, um  módulo sensor de temperatura e umidade (DHT22) e um módulo Receptor GPS (GY-NEO6MV2) 

---
# Estrutura do projeto

```
project/
├── inc/
│   ├── Types.h    <-- Structs e tipos de dados compartilhados
│   ├── GpsDriver.h
│   ├── BmpDriver.h
│   ├── Dht22Driver.h
│   ├── RfidDriver.h
│   ├── Fusion.h         <-- Agregador de dados dos sensores
│   ├── MqttService.h    <-- Gerencia conexão e envio MQTT
│   └── Pinout.h  <-- Define a pinagem do sistema
└── src/
    ├── GpsDriver.cpp
    ├── BmpDriver.cpp
    ├── Dht22Driver.cpp
    ├── RfidDriver.cpp
    ├── Fusion.cpp
    ├── MqttService.cpp
    └── Main.cpp       <-- Orquestrador do sistema
```

O sistema vai ser integrado da seguinte forma, teremos um arquivo para definir a pinagem do sistema, um arquivo usado para definir as variáveis usadas no sistema. Também será implementado para cada sensor um arquivo próprio com contato apenas com sua biblioteca específica, um arquivo chamado Fusion será o responsável pela integração dos valores captados em cada polo de sensor, unindo-os e preparando um json com os dados coletados. Na parte de exibição das informações, o arquivo MqttService cuida da parte da conexão e envio MQTT dos dados para um servidor web, enquanto a main é a intermediária entre o Fusion e o MqttService, definindo a frequência com que os sensores são lidos e de quanto em quanto tempo os dados são publicados, monitorar a conexão e ordenar reconexões caso o MQTT caia, sem travar a leitura contínua dos sensores.

---
# Schema json

```json
GpsDriver{
  "gps": {
    "valido": true,
    "lat": -23.550520,
    "lng": -46.633308,
    "alt": 760.5,
    "vel": 42.3,
    "sats": 8
  }
}
```

---
# Sensores, protocolos e conexões

| **Módulo / Sensor** | **Protocolo**    | **Pinos no Arduino Mega**                                                                    | **Observação de Ligação**                                                                                                                              |
| ------------------- | ---------------- | -------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------ |
| **GPS (NEO-6M)**    | UART (Serial)    | **19 (RX1)** e **18 (TX1)**                                                                  | Cruzado: TX do GPS no pino 19; RX do GPS no pino 18.                                                                                                   |
| **BMP180 / BMP280** | I2C              | **20 (SDA)** e **21 (SCL)**                                                                  | Pinos fixos de I2C do Mega.                                                                                                                            |
| **RFID (MFRC522)**  | SPI              | **50 (MISO)**, **51 (MOSI)**, **52 (SCK)**<br><br>  <br><br>+ **53 (SDA/CS)** e **49 (RST)** | Os pinos 50-52 são fixos do barramento SPI. O CS e o RST você escolhe (53 e 49 são o padrão).                                                          |
| **DHT22**           | Digital (1-Wire) | **Pino 2** (ou qualquer digital livre)                                                       | Usa apenas 1 pino de dados comum.                                                                                                                      |
| **Rede (MQTT)**     | SPI ou UART      | _Depende do módulo_                                                                          | Se usar **Ethernet Shield**, ele encaixa direto em cima do Mega (usa SPI + pino 10). Se usar **ESP8266 / ESP-01**, vai na **Serial2 (pinos 16 e 17)**. |

---
