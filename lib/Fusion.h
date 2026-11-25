#pragma once

#include <Arduino.h>
#include "Types.h"

// Tamanho de buffer suficiente para o JSON gerado (~200 bytes no pior caso)
#define FUSION_JSON_MAX 256

// Monta o JSON de telemetria no formato do mega_sender (ArduinoJson v7):
// {"dht":{"temp":...,"umid":...},"bmp":{"pressao":...,"temp":...},"gps":{"lat":...,"lng":...},"rfid":{"uid":"..."}}
// Retorna false se o buffer for pequeno demais.
bool Fusion_BuildTelemetry(const SensorsData& s, char* out, size_t outSize);