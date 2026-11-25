#pragma once

#include <Arduino.h>
#include "Types.h"

// ---------------------------------------------------------------
// JsonSerial - Monta o JSON (Fusion / ArduinoJson v7) e envia pela
// Serial3 para o ESP32 no formato do mega_sender.
//
// Protocolo (uma linha JSON por ciclo, terminada em '\n'):
//   Mega -> ESP32 :  "<json>\n"
//   ESP32 -> Mega :  "S 1\n" / "S 0\n"   conectado / sem broker
//
// Nada aqui bloqueia: os JSONs vão para uma fila e saem aos poucos
// a cada chamada de JsonSerial_Loop().
// ---------------------------------------------------------------

// Serial e velocidade usadas com o ESP32 (Serial3: 14 = TX3, 15 = RX3).
#ifndef JSON_SERIAl
    #define JSON_SERIAL  Serial3
#endif
#ifndef JSON_BAUD
    #define JSON_BAUD    115200     // mesmo baud do SERIAL_BAUD no config.h do ESP32
#endif

// Monitor no PC: 1 = mostra na Serial (USB) cada linha enviada ao ESP32; 0 = desliga.
// (NÃO use Serial1: ela é do GPS.)
#ifndef JSON_DEBUG
  #define JSON_DEBUG   1
#endif
#define JSON_DEBUG_SERIAL  Serial

// Abre a serial do ESP32. Chamar uma vez no setup().
void JsonSerial_Init();

// Chamar em TODO ciclo do loop():
//  - empurra para a serial os bytes que estão na fila de envio
//  - lê o status que o ESP32 devolve ("S 1" / "S 0")
void JsonSerial_Loop();

// Monta o JSON unificado (dht, bmp, gps, rfid) e coloca na fila ("<json>\n").
// Retorna false se a fila estiver cheia ou o JSON não couber (nada trava).
bool JsonSerial_SendTelemetry(const SensorsData& s);

// true se o ESP32 avisou recentemente que está conectado ao broker.
bool JsonSerial_IsConnected();