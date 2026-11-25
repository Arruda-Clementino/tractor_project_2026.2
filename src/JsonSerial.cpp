#include <Arduino.h>
#include <string.h>

#include "../lib/JsonSerial.h"
#include "../lib/Fusion.h"      // monta o JSON via ArduinoJson v7

#define TX_BUF_SIZE        512      // fila de envio
#define STATUS_TIMEOUT_MS  15000    // ESP32 manda status a cada 5 s; sem aviso por 15 s = offline

// ---------- fila circular de envio ----------
static char     txBuf[TX_BUF_SIZE];
static uint16_t txHead  = 0;    // onde entra o próximo byte
static uint16_t txTail  = 0;    // de onde sai o próximo byte
static uint16_t txCount = 0;    // bytes na fila

// ---------- recepção do status ----------
static char     rxLine[16];
static uint8_t  rxLen = 0;
static bool     brokerConnected = false;
static uint32_t lastStatusMs    = 0;

static void txPush(char c) {
  txBuf[txHead] = c;
  txHead = (txHead + 1) % TX_BUF_SIZE;
  txCount++;
}

// Põe "<json>\n" na fila (sem prefixo 'T '/'E ', compatível com mega_sender).
// Tudo ou nada: se não couber, descarta.
static bool enqueue(const char* json) {
  size_t n = strlen(json);
  if (n + 1 > (size_t)(TX_BUF_SIZE - txCount)) return false;

  for (size_t i = 0; i < n; i++) txPush(json[i]);
  txPush('\n');

#if JSON_DEBUG
  // Debug no monitor serial (USB), igual ao mega_sender
  JSON_DEBUG_SERIAL.println(json);
#endif
  return true;
}

void JsonSerial_Init() {
  JSON_SERIAL.begin(JSON_BAUD);
  txHead = txTail = txCount = 0;
  rxLen = 0;
  brokerConnected = false;
  lastStatusMs = millis();
}

void JsonSerial_Loop() {
  // 1. Envio sem bloquear: só escreve o que cabe no buffer da serial agora
  while (txCount > 0 && JSON_SERIAL.availableForWrite() > 0) {
    JSON_SERIAL.write((uint8_t)txBuf[txTail]);
    txTail = (txTail + 1) % TX_BUF_SIZE;
    txCount--;
  }

  // 2. Recebe o status do ESP32 ("S 1" / "S 0")
  while (JSON_SERIAL.available() > 0) {
    char c = (char)JSON_SERIAL.read();

    if (c == '\n') {
      rxLine[rxLen] = '\0';
      if (rxLen >= 3 && rxLine[0] == 'S' && rxLine[1] == ' ') {
        brokerConnected = (rxLine[2] == '1');
        lastStatusMs = millis();
      }
      rxLen = 0;
    } else if (c != '\r') {
      if (rxLen < sizeof(rxLine) - 1) rxLine[rxLen++] = c;
      else rxLen = 0;   // linha longa demais: lixo, recomeça
    }
  }
}

bool JsonSerial_SendTelemetry(const SensorsData& s) {
  char json[FUSION_JSON_MAX];
  if (!Fusion_BuildTelemetry(s, json, sizeof(json))) return false;
  return enqueue(json);
}

bool JsonSerial_IsConnected() {
  return brokerConnected && (millis() - lastStatusMs < STATUS_TIMEOUT_MS);
}