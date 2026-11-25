#include <Arduino.h>

#include "../lib/SensorsDriver.h"
#include "../lib/GpsDriver.h"
#include "../lib/Dht22Driver.h"
#include "../lib/BmpDriver.h"
#include "../lib/RfidDriver.h"

static const uint32_t RFID_INTERVAL_MS = 100;

static uint32_t lastRfidMs = 0;

void SensorsDriver_Init() {
  GpsDriver_Init();
  Dht22Driver_Init();
  BmpDriver_Init();
  RfidDriver_Init();

  lastRfidMs = millis();
}

bool SensorsDriver_Update() {
  bool newTag = false;

  // GPS: todo ciclo, para não perder bytes da serial
  GpsDriver_Update();

  // DHT22 e BMP280: o intervalo é controlado dentro de cada driver
  Dht22Driver_Update();
  BmpDriver_Update();

  // RFID: a cada 100 ms
  uint32_t now = millis();
  if (now - lastRfidMs >= RFID_INTERVAL_MS) {
    lastRfidMs = now;
    newTag = RfidDriver_Update();
  }

  return newTag;
}

SensorsData SensorsDriver_Get() {
  SensorsData d;
  d.gps  = GpsDriver_Get();
  d.dht  = Dht22Driver_Get();
  d.bmp  = BmpDriver_Get();
  d.rfid = RfidDriver_Get();
  return d;
}
