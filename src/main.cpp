#include <Arduino.h>
#include "../lib/RfidDriver.h"

void setup() {
  Serial.begin(115200);
  RfidDriver_init();

  Serial.println(F("=== Sistema RFID - Identificacao de Implementos ==="));
  Serial.println(F("Aproxime um cartao (Rocadeira, Adubadora ou Reboque)...\n"));
}

void loop() {
  // Só entra no if quando um cartão novo for aproximado
  if (RfidDriver_update()) {
    RfidData implemento = RfidDriver_getData();

    Serial.print(F("UID Lido: "));
    Serial.print(implemento.uid);
    Serial.print(F(" | Implemento: "));
    Serial.print(implemento.nome);
    Serial.print(F(" (Codigo "));
    Serial.print(implemento.tipo);
    Serial.print(F(") | Valido: "));
    Serial.println(implemento.identificado ? F("SIM") : F("NAO"));

    if (implemento.identificado) {
      Serial.print(F(">> Implemento engatado: "));
      Serial.println(implemento.nome);
    } else {
      Serial.println(F(">> Cartao nao cadastrado!"));
    }

    Serial.println();
  }
}