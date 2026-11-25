#include <Arduino.h>
#include <DHT.h>

#include "../lib/Dht22Driver.h"
#include "../lib/Pinout.h"

// DHT22 exige ~2 s entre leituras físicas
static const uint32_t DHT_READ_INTERVAL_MS = 2000;

static DHT       dht(DHT22_PIN, DHT22);
static Dht22Data data;
static uint32_t  lastReadMs = 0;

void Dht22Driver_Init() {
  dht.begin();

  data.valid        = false;
  data.temp_c       = 0.0f;
  data.humidity_pct = 0.0f;

  // Força a primeira leitura no primeiro Update()
  lastReadMs = millis() - DHT_READ_INTERVAL_MS;
}

void Dht22Driver_Update() {
  uint32_t now = millis();
  if (now - lastReadMs < DHT_READ_INTERVAL_MS) return;
  lastReadMs = now;

  float h = dht.readHumidity();
  float t = dht.readTemperature();   // Celsius

  if (isnan(h) || isnan(t)) {
    // Leitura falhou: mantém os últimos valores, apenas sinaliza como inválido
    data.valid = false;
    return;
  }

  data.temp_c       = t;
  data.humidity_pct = h;
  data.valid        = true;
}

Dht22Data Dht22Driver_Get() {
  return data;
}
