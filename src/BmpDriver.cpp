#include <Arduino.h>
#include <Adafruit_BMP280.h>

#include "../lib/BmpDriver.h"
#include "../lib/Pinout.h"

static const uint32_t BMP_READ_INTERVAL_MS = 1000;

// SPI por software: (CS, MOSI, MISO, SCK)
static Adafruit_BMP280 bmp(PIN_BMP_CS, PIN_BMP_MOSI, PIN_BMP_MISO, PIN_BMP_SCK);

static Bmp280Data data;
static bool       sensorOk   = false;
static uint32_t   lastReadMs = 0;

void BmpDriver_Init() {
  data.valid        = false;
  data.temp_c       = 0.0f;
  data.pressure_hpa = 0.0f;

  sensorOk   = bmp.begin();
  lastReadMs = millis() - BMP_READ_INTERVAL_MS;   // lê já no primeiro Update()
}

void BmpDriver_Update() {
  if (!sensorOk) return;

  uint32_t now = millis();
  if (now - lastReadMs < BMP_READ_INTERVAL_MS) return;
  lastReadMs = now;

  float t = bmp.readTemperature();        // °C
  float p = bmp.readPressure() / 100.0f;  // Pa -> hPa

  if (isnan(t) || isnan(p)) {
    data.valid = false;
    return;
  }

  data.temp_c       = t;
  data.pressure_hpa = p;
  data.valid        = true;
}

Bmp280Data BmpDriver_Get() {
  return data;
}
