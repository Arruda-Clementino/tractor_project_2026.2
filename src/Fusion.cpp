#include <Arduino.h>
#include <ArduinoJson.h>

#include "../lib/Fusion.h"

bool Fusion_BuildTelemetry(const SensorsData& s, char* out, size_t outSize) {
  if (!out || outSize == 0) return false;

  JsonDocument doc;

  // ----- DHT22 -----
  JsonObject dht = doc["dht"].to<JsonObject>();
  if (s.dht.valid) {
    dht["temp"] = s.dht.temp_c;
    dht["umid"] = s.dht.humidity_pct;
  } else {
    dht["temp"] = nullptr;
    dht["umid"] = nullptr;
  }

  // ----- BMP280 -----
  JsonObject bmp = doc["bmp"].to<JsonObject>();
  if (s.bmp.valid) {
    bmp["pressao"] = s.bmp.pressure_hpa;
    bmp["temp"]    = s.bmp.temp_c;
  } else {
    bmp["pressao"] = nullptr;
    bmp["temp"]    = nullptr;
  }

  // ----- GPS -----
  JsonObject gps = doc["gps"].to<JsonObject>();
  if (s.gps.fix) {
    gps["lat"] = s.gps.lat;
    gps["lng"] = s.gps.lon;
  } else {
    gps["lat"] = nullptr;
    gps["lng"] = nullptr;
  }

  // ----- RFID -----
  JsonObject rfid = doc["rfid"].to<JsonObject>();
  if (s.rfid.tipo != IMPLEMENTO_NENHUM) {
    rfid["uid"] = s.rfid.uid;
  } else {
    rfid["uid"] = "";
  }

  size_t written = serializeJson(doc, out, outSize);
  return (written > 0 && written < outSize);
}