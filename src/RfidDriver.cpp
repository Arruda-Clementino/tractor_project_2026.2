#include <Arduino.h>
#include <string.h>

#include "../lib/RfidDriver.h"
#include "../lib/Pinout.h"

// =====================================================================
// CADASTRO DOS 3 IMPLEMENTOS (substitua pelos UIDs reais das tags)
// =====================================================================
static const char* UID_ROCADEIRA = "E6 FF EF 73";  // Tag 1 = Roçadeira
static const char* UID_ADUBADORA = "F3 6E 79 2D";  // Tag 2 = Adubadora
static const char* UID_REBOQUE   = "XX XX XX XX";  // Tag 3 = Reboque

// Registradores do MFRC522 usados
#define REG_COMMAND   0x01
#define REG_COMIRQ    0x04
#define REG_DIVIRQ    0x05
#define REG_ERROR     0x06
#define REG_FIFODATA  0x09
#define REG_FIFOLEVEL 0x0A
#define REG_BITFRAME  0x0D
#define REG_COLL      0x0E
#define REG_MODE      0x11
#define REG_TXCONTROL 0x14
#define REG_TXASK     0x15
#define REG_CRC_H     0x21
#define REG_CRC_L     0x22
#define REG_TMODE     0x2A
#define REG_TPRESC    0x2B
#define REG_TRELOAD_H 0x2C
#define REG_TRELOAD_L 0x2D

static RfidData data;

// ---------------------------------------------------------------------
// SPI por software (bit-bang) nos pinos do Pinout.h
// ---------------------------------------------------------------------
static byte spiTransfer(byte out) {
  byte in = 0;
  for (uint8_t i = 0; i < 8; i++) {
    digitalWrite(PIN_RFID_MOSI, (out & 0x80) ? HIGH : LOW);
    out <<= 1;
    digitalWrite(PIN_RFID_SCK, HIGH);
    in <<= 1;
    if (digitalRead(PIN_RFID_MISO)) in |= 0x01;
    digitalWrite(PIN_RFID_SCK, LOW);
  }
  return in;
}

static void writeReg(byte reg, byte value) {
  digitalWrite(PIN_RFID_SS, LOW);
  spiTransfer((reg << 1) & 0x7E);
  spiTransfer(value);
  digitalWrite(PIN_RFID_SS, HIGH);
}

static byte readReg(byte reg) {
  digitalWrite(PIN_RFID_SS, LOW);
  spiTransfer(((reg << 1) & 0x7E) | 0x80);
  byte val = spiTransfer(0x00);
  digitalWrite(PIN_RFID_SS, HIGH);
  return val;
}

// ---------------------------------------------------------------------
// Comunicação com a tag
// ---------------------------------------------------------------------
static bool calcCRC(byte* buf, byte len, byte* result) {
  writeReg(REG_COMMAND, 0x00);    // Idle
  writeReg(REG_DIVIRQ, 0x04);     // Limpa CRCIRq
  writeReg(REG_FIFOLEVEL, 0x80);  // Limpa FIFO
  for (byte i = 0; i < len; i++) writeReg(REG_FIFODATA, buf[i]);
  writeReg(REG_COMMAND, 0x03);    // CalcCRC

  unsigned long t0 = millis();
  while (millis() - t0 < 15) {
    if (readReg(REG_DIVIRQ) & 0x04) {
      writeReg(REG_COMMAND, 0x00);
      result[0] = readReg(REG_CRC_L);
      result[1] = readReg(REG_CRC_H);
      return true;
    }
  }
  return false;
}

static bool transceive(byte* send, byte sendLen, byte* back, byte* backLen, byte validBits) {
  writeReg(REG_COMMAND, 0x00);    // Idle
  writeReg(REG_COMIRQ, 0x7F);     // Limpa interrupções
  writeReg(REG_FIFOLEVEL, 0x80);  // Limpa FIFO
  for (byte i = 0; i < sendLen; i++) writeReg(REG_FIFODATA, send[i]);

  writeReg(REG_BITFRAME, validBits);
  writeReg(REG_COMMAND, 0x0C);                 // Transceive
  writeReg(REG_BITFRAME, validBits | 0x80);    // StartSend

  unsigned long t0 = millis();
  while (millis() - t0 < 25) {
    byte irq = readReg(REG_COMIRQ);
    if (irq & 0x30) break;       // RxIRq ou IdleIRq
    if (irq & 0x01) return false; // Timeout
  }

  if (readReg(REG_ERROR) & 0x1B) return false;

  if (back && backLen) {
    byte n = readReg(REG_FIFOLEVEL);
    if (n > *backLen) n = *backLen;
    *backLen = n;
    for (byte i = 0; i < n; i++) back[i] = readReg(REG_FIFODATA);
  }
  return true;
}

static void haltCard() {
  byte cmd[4] = {0x50, 0x00, 0x00, 0x00};
  if (calcCRC(cmd, 2, &cmd[2])) transceive(cmd, 4, nullptr, nullptr, 0);
}

// ---------------------------------------------------------------------
// Auxiliares
// ---------------------------------------------------------------------
static void setImplemento(ImplementoTipo tipo, const char* nome, bool ok) {
  data.tipo         = tipo;
  data.identificado = ok;
  strncpy(data.nome, nome, sizeof(data.nome) - 1);
  data.nome[sizeof(data.nome) - 1] = '\0';
}

// ---------------------------------------------------------------------
// Funções públicas
// ---------------------------------------------------------------------
void RfidDriver_Init() {
  pinMode(PIN_RFID_SS,   OUTPUT);
  pinMode(PIN_RFID_SCK,  OUTPUT);
  pinMode(PIN_RFID_MOSI, OUTPUT);
  pinMode(PIN_RFID_MISO, INPUT);
  pinMode(PIN_RFID_RST,  OUTPUT);

  digitalWrite(PIN_RFID_SS,  HIGH);
  digitalWrite(PIN_RFID_SCK, LOW);

  // Reset físico + soft reset
  digitalWrite(PIN_RFID_RST, LOW);
  delay(10);
  digitalWrite(PIN_RFID_RST, HIGH);
  delay(50);
  writeReg(REG_COMMAND, 0x0F);
  delay(50);

  // Configuração padrão
  writeReg(REG_TMODE,     0x80);
  writeReg(REG_TPRESC,    0xA9);
  writeReg(REG_TRELOAD_H, 0x03);
  writeReg(REG_TRELOAD_L, 0xE8);
  writeReg(REG_TXASK,     0x40);
  writeReg(REG_MODE,      0x3D);

  // Liga a antena
  byte tx = readReg(REG_TXCONTROL);
  if ((tx & 0x03) != 0x03) writeReg(REG_TXCONTROL, tx | 0x03);

  setImplemento(IMPLEMENTO_NENHUM, "Nenhum", false);
  strcpy(data.uid, "00 00 00 00");
}

bool RfidDriver_Update() {
  // 1. Há tag no campo? (REQA)
  byte reqa = 0x26;
  byte atqa[2];
  byte atqaLen = sizeof(atqa);
  writeReg(REG_COLL, 0x80);
  if (!transceive(&reqa, 1, atqa, &atqaLen, 0x07) || atqaLen != 2) return false;

  // 2. Lê o UID (anticollision)
  byte antiCol[2] = {0x93, 0x20};
  byte uid[5];
  byte uidLen = sizeof(uid);
  if (!transceive(antiCol, 2, uid, &uidLen, 0x00) || uidLen != 5) return false;
  if ((uid[0] ^ uid[1] ^ uid[2] ^ uid[3]) != uid[4]) return false;   // BCC

  // 3. Seleciona e coloca em Halt (evita reler enquanto estiver encostada)
  byte sel[9] = {0x93, 0x70, uid[0], uid[1], uid[2], uid[3], uid[4], 0, 0};
  if (calcCRC(sel, 7, &sel[7])) {
    byte sak[3];
    byte sakLen = sizeof(sak);
    transceive(sel, 9, sak, &sakLen, 0);
    haltCard();
  }

  // 4. Identifica o implemento
  snprintf(data.uid, sizeof(data.uid), "%02X %02X %02X %02X", uid[0], uid[1], uid[2], uid[3]);

  if      (strcmp(data.uid, UID_ROCADEIRA) == 0) setImplemento(IMPLEMENTO_1, "Rocadeira", true);
  else if (strcmp(data.uid, UID_ADUBADORA) == 0) setImplemento(IMPLEMENTO_2, "Adubadora", true);
  else if (strcmp(data.uid, UID_REBOQUE)   == 0) setImplemento(IMPLEMENTO_3, "Reboque",   true);
  else                                           setImplemento(IMPLEMENTO_DESCONHECIDO, "Desconhecido", false);

  return true;
}

RfidData RfidDriver_Get() {
  return data;
}
