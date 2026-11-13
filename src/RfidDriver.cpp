#include "../lib/Pinout.h"
#include "../lib/RfidDriver.h"
#include <string.h>

static RfidData currentData;

// =====================================================================
// CADASTRO DOS 3 CARTÕES (Substitua pelos UIDs reais das suas tags)
// =====================================================================
static const char* UID_ROCADEIRA = "E6 FF EF 73"; // Cartão 1 = Roçadeira
static const char* UID_ADUBADORA = "F3 6E 79 2D"; // Cartão 2 = Adubadora
static const char* UID_REBOQUE   = "XX XX XX XX"; // Cartão 3 = Reboque

// =====================================================================
// Comunicação SPI e Registradores MFRC522 (Uso interno do driver)
// =====================================================================
static byte spiTransfer(byte data) {
  byte received = 0;
  for (uint8_t i = 0; i < 8; i++) {
    digitalWrite(PIN_RFID_MOSI, (data & 0x80) ? HIGH : LOW);
    data <<= 1;
    digitalWrite(PIN_RFID_SCK, HIGH);
    received <<= 1;
    if (digitalRead(PIN_RFID_MISO)) {
      received |= 0x01;
    }
    digitalWrite(PIN_RFID_SCK, LOW);
  }
  return received;
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

static bool calcCRC(byte *data, byte len, byte *result) {
  writeReg(0x01, 0x00); // Idle
  writeReg(0x05, 0x04); // Limpa CRCIRq
  writeReg(0x0A, 0x80); // Limpa FIFO
  for (byte i = 0; i < len; i++) {
    writeReg(0x09, data[i]);
  }
  writeReg(0x01, 0x03); // CalcCRC

  unsigned long t0 = millis();
  while (millis() - t0 < 15) {
    if (readReg(0x05) & 0x04) {
      writeReg(0x01, 0x00);
      result[0] = readReg(0x22); // CRCResultRegL
      result[1] = readReg(0x21); // CRCResultRegH
      return true;
    }
  }
  return false;
}

static bool transceive(byte *sendData, byte sendLen, byte *backData, byte *backLen, byte validBits = 0) {
  writeReg(0x01, 0x00); // Idle
  writeReg(0x04, 0x7F); // Limpa interrupcoes
  writeReg(0x0A, 0x80); // Limpa FIFO

  for (byte i = 0; i < sendLen; i++) {
    writeReg(0x09, sendData[i]);
  }

  writeReg(0x0D, validBits);
  writeReg(0x01, 0x0C); // Transceive
  writeReg(0x0D, validBits | 0x80); // StartSend

  unsigned long t0 = millis();
  while (millis() - t0 < 25) {
    byte irq = readReg(0x04);
    if (irq & 0x30) break;
    if (irq & 0x01) return false;
  }

  if (readReg(0x06) & 0x1B) return false; // ErrorReg

  if (backData && backLen) {
    byte n = readReg(0x0A);
    if (n > *backLen) n = *backLen;
    *backLen = n;
    for (byte i = 0; i < n; i++) {
      backData[i] = readReg(0x09);
    }
  }
  return true;
}

static void haltCard() {
  byte cmd[4] = {0x50, 0x00, 0x00, 0x00};
  if (calcCRC(cmd, 2, &cmd[2])) {
    transceive(cmd, 4, nullptr, nullptr, 0);
  }
}

static void formatarUid(byte *buffer, char *destino) {
  sprintf(destino, "%02X %02X %02X %02X", buffer[0], buffer[1], buffer[2], buffer[3]);
}

// =====================================================================
// Funções Públicas (Chamadas pela main)
// =====================================================================

void RfidDriver_clear() {
  currentData.tipo = IMPLEMENTO_NENHUM;
  strcpy(currentData.uid, "00 00 00 00");
  strcpy(currentData.nome, "Nenhum");
  currentData.identificado = false;
}


void RfidDriver_init() {
  pinMode(PIN_RFID_SS, OUTPUT);
  pinMode(PIN_RFID_SCK, OUTPUT);
  pinMode(PIN_RFID_MOSI, OUTPUT);
  pinMode(PIN_RFID_MISO, INPUT);
  pinMode(PIN_RFID_RST, OUTPUT);

  digitalWrite(PIN_RFID_SS, HIGH);
  digitalWrite(PIN_RFID_SCK, LOW);

  // Reset físico do módulo
  digitalWrite(PIN_RFID_RST, LOW);
  delay(10);
  digitalWrite(PIN_RFID_RST, HIGH);
  delay(50);

  // Configuração padrão do MFRC522
  writeReg(0x01, 0x0F); // SoftReset
  delay(50);
  writeReg(0x2A, 0x80); // TModeReg
  writeReg(0x2B, 0xA9); // TPrescalerReg
  writeReg(0x2C, 0x03); // TReloadRegH
  writeReg(0x2D, 0xE8); // TReloadRegL
  writeReg(0x15, 0x40); // TxASKReg
  writeReg(0x11, 0x3D); // ModeReg

  // Liga a antena RF
  byte txCtrl = readReg(0x14);
  if ((txCtrl & 0x03) != 0x03) {
    writeReg(0x14, txCtrl | 0x03);
  }

  RfidDriver_clear();
}


bool RfidDriver_update() {
  // 1. Detecta presença de novo cartão (REQA)
  byte reqa = 0x26;
  byte atqa[2];
  byte atqaLen = sizeof(atqa);
  writeReg(0x0E, 0x80);

  if (!transceive(&reqa, 1, atqa, &atqaLen, 0x07) || atqaLen != 2) {
    return false;
  }

  // 2. Lê o UID do cartão (Anticollision)
  byte antiCol[2] = {0x93, 0x20};
  byte uidResp[5];
  byte uidLen = sizeof(uidResp);

  if (!transceive(antiCol, 2, uidResp, &uidLen, 0x00) || uidLen != 5) {
    return false;
  }

  // Confere checksum (BCC)
  if ((uidResp[0] ^ uidResp[1] ^ uidResp[2] ^ uidResp[3]) != uidResp[4]) {
    return false;
  }

  // 3. Seleciona e coloca o cartão em Halt para não repetir leitura enquanto encostado
  byte selCmd[9] = {0x93, 0x70, uidResp[0], uidResp[1], uidResp[2], uidResp[3], uidResp[4], 0, 0};
  if (calcCRC(selCmd, 7, &selCmd[7])) {
    byte sak[3];
    byte sakLen = sizeof(sak);
    transceive(selCmd, 9, sak, &sakLen, 0);
    haltCard();
  }

  // 4. Identifica qual dos 3 implementos corresponde ao UID lido
  char uidLido[16];
  formatarUid(uidResp, uidLido);
  strcpy(currentData.uid, uidLido);

  if (strcmp(uidLido, UID_ROCADEIRA) == 0) {
    currentData.tipo = IMPLEMENTO_1;
    strcpy(currentData.nome, "Rocadeira");
    currentData.identificado = true;
  } else if (strcmp(uidLido, UID_ADUBADORA) == 0) {
    currentData.tipo = IMPLEMENTO_2;
    strcpy(currentData.nome, "Adubadora");
    currentData.identificado = true;
  } else if (strcmp(uidLido, UID_REBOQUE) == 0) {
    currentData.tipo = IMPLEMENTO_3;
    strcpy(currentData.nome, "Reboque");
    currentData.identificado = true;
  } else {
    currentData.tipo = IMPLEMENTO_DESCONHECIDO;
    strcpy(currentData.nome, "Desconhecido");
    currentData.identificado = false;
  }

  return true;
}

RfidData RfidDriver_getData() {
  return currentData;
}