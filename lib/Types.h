#ifndef TYPES_H
#define TYPES_H

#include <Arduino.h>

// ==========================================
// Dados do GPS
// ==========================================
struct GpsData {
  double latitude;
  double longitude;
  double altitude;
  double speedKmph;
  uint32_t satellites;
  bool isValid;
};

// ==========================================
// Dados do RFID (Identificação de Implementos)
// ==========================================
enum TipoImplemento {
  IMPLEMENTO_NENHUM = 0,
  IMPLEMENTO_1 = 1,           // Ex: Arado
  IMPLEMENTO_2 = 2,           // Ex: Semeadeira
  IMPLEMENTO_3 = 3,           // Ex: Pulverizador
  IMPLEMENTO_DESCONHECIDO = 99
};

struct RfidData {
  TipoImplemento tipo;
  char uid[16];       // Guarda o código hexadecimal da tag (ex: "A1 B2 C3 D4")
  char nome[24];      // Nome legível do implemento para enviar no JSON
  bool identificado;  // true se um dos 3 implementos conhecidos foi lido
};

#endif