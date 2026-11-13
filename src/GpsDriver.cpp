#include "../lib/GpsDriver.h"
#include <TinyGPSPlus.h>

// O modificador 'static' garante que o objeto 'gps' seja privado deste arquivo.
// Nenhum outro arquivo do projeto consegue acessá-lo diretamente.
static TinyGPSPlus gps;

// Configurações de hardware do Arduino Mega (Serial1 = pinos 18 TX e 19 RX)
static const uint32_t GPS_BAUD_RATE = 9600;
static const uint32_t MAX_DATA_AGE_MS = 2000;

void teste(){
    Serial.println(gps.location.isValid());
}

void GpsDriver_init() {
  Serial1.begin(GPS_BAUD_RATE);
}

void GpsDriver_update() {
  while (Serial1.available() > 0) {
    gps.encode(Serial1.read());
  }
}

GpsData GpsDriver_getData() {
  GpsData data;

  // Verifica se o fix é válido E se o dado não é antigo (ex: perdeu sinal dentro de um túnel)
  bool hasRecentFix = gps.location.isValid() && (gps.location.age() < MAX_DATA_AGE_MS);

  data.isValid = hasRecentFix;

  if (hasRecentFix) {
    data.latitude   = gps.location.lat();
    data.longitude  = gps.location.lng();
    data.altitude   = gps.altitude.meters();
    data.speedKmph  = gps.speed.kmph();
    data.satellites = gps.satellites.value();
  } else {
    // Zera os valores para evitar envio de lixo de memória caso não haja sinal
    data.latitude   = 0.0;
    data.longitude  = 0.0;
    data.altitude   = 0.0;
    data.speedKmph  = 0.0;
    data.satellites = 0;
  }

  return data;
}