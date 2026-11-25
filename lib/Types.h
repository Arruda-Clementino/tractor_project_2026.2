#pragma once

#include <stdint.h>

// ---------------------------------------------------------------
// Types.h - Structs e tipos de dados compartilhados
// ---------------------------------------------------------------

// ---------- GPS (NEO-6M) ----------
struct GpsData {
  bool     fix;         // true se a posição é válida e recente
  double   lat;
  double   lon;
  float    alt_m;
  float    speed_kmh;
  uint8_t  satellites;
};

// ---------- DHT22 ----------
struct Dht22Data {
  bool   valid;         // false se a última leitura falhou
  float  temp_c;
  float  humidity_pct;
};

// ---------- BMP280 ----------
struct Bmp280Data {
  bool   valid;         // false se o sensor não foi achado ou a leitura falhou
  float  temp_c;
  float  pressure_hpa;
};

// ---------- RFID (implementos) ----------
enum ImplementoTipo {
  IMPLEMENTO_NENHUM = 0,
  IMPLEMENTO_1,           // Roçadeira
  IMPLEMENTO_2,           // Adubadora
  IMPLEMENTO_3,           // Reboque
  IMPLEMENTO_DESCONHECIDO
};

struct RfidData {
  ImplementoTipo tipo;
  char           uid[16];   // "AA BB CC DD"
  char           nome[16];  // "Rocadeira", "Adubadora", "Reboque", ...
  bool           identificado;
};

// ---------- Agregado de todos os sensores (SensorsDriver) ----------
struct SensorsData {
  GpsData    gps;
  Dht22Data  dht;
  Bmp280Data bmp;
  RfidData   rfid;
};
