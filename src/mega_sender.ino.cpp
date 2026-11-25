// Arduino Mega -> ESP32 (via Serial3: TX3 = pino 14, RX3 = pino 15)
// Envia uma linha JSON por ciclo, terminada em '\n'.
#include <ArduinoJson.h>   // v7

const unsigned long INTERVALO_MS = 2000;
unsigned long ultimoEnvio = 0;

void enviarTelemetria() {
  JsonDocument doc;

  // TODO: troque os valores abaixo pelas leituras reais dos sensores
  JsonObject dht = doc["dht"].to<JsonObject>();
  dht["temp"] = 25.3;
  dht["umid"] = 60.1;

  JsonObject bmp = doc["bmp"].to<JsonObject>();
  bmp["pressao"] = 1013.2;
  bmp["temp"]    = 24.8;

  JsonObject gps = doc["gps"].to<JsonObject>();
  gps["lat"] = -23.550520;
  gps["lng"] = -46.633308;

  JsonObject rfid = doc["rfid"].to<JsonObject>();
  rfid["uid"] = "";   // preencha quando ler um cartão

  serializeJson(doc, Serial3);   // para o ESP32
  Serial3.print('\n');

  serializeJson(doc, Serial);    // debug no monitor serial
  Serial.println();
}

void setup() {
  Serial.begin(115200);
  Serial3.begin(115200);         // mesmo baud do SERIAL_BAUD no config.h
}

void loop() {
  if (millis() - ultimoEnvio >= INTERVALO_MS) {
    ultimoEnvio = millis();
    enviarTelemetria();
  }
}
