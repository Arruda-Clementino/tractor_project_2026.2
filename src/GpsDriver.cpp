#include <Arduino.h>
#include <TinyGPSPlus.h>

#include "../lib/GpsDriver.h"
#include "../lib/Pinout.h"

// Posição considerada inválida se o último fix tiver mais de 2 s
static const uint32_t GPS_MAX_AGE_MS = 2000;

static TinyGPSPlus gps;
static GpsData     data;

void GpsDriver_Init() {
  GPS_SERIAL.begin(GPS_BAUD);

  data.fix        = false;
  data.lat        = 0.0;
  data.lon        = 0.0;
  data.alt_m      = 0.0f;
  data.speed_kmh  = 0.0f;
  data.satellites = 0;
}

void GpsDriver_Update() {
  // Consome tudo que chegou na serial (buffer do Mega é de só 64 bytes)
  while (GPS_SERIAL.available() > 0) {
    gps.encode(GPS_SERIAL.read());
  }

  data.satellites = gps.satellites.isValid() ? (uint8_t)gps.satellites.value() : 0;

  data.fix = gps.location.isValid() && gps.location.age() < GPS_MAX_AGE_MS;

  if (data.fix) {
    data.lat       = gps.location.lat();
    data.lon       = gps.location.lng();
    data.alt_m     = gps.altitude.isValid() ? (float)gps.altitude.meters() : data.alt_m;
    data.speed_kmh = gps.speed.isValid()    ? (float)gps.speed.kmph()      : 0.0f;
  } else {
    // Sem fix: mantém a última posição conhecida, mas zera a velocidade
    data.speed_kmh = 0.0f;
  }
}

GpsData GpsDriver_Get() {
  return data;
}
