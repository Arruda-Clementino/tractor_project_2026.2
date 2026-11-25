#pragma once

#include <Arduino.h>

// ---------------------------------------------------------------
// Pinout.h - Pinagem e constantes de hardware (Arduino Mega 2560)
// ---------------------------------------------------------------

// ---------- GPS NEO-6M (Serial1, UART) ----------
// TX do módulo -> pino 19 (RX1) | RX do módulo -> pino 18 (TX1)
#define GPS_SERIAL    Serial1
#define GPS_BAUD      9600

// ---------- DHT22 (1 fio) ----------
#define DHT22_PIN     2

// ---------- BMP280 (SPI por software) ----------
#define PIN_BMP_CS    24   // CSB
#define PIN_BMP_SCK   26   // SCL / SCK
#define PIN_BMP_MOSI  28   // SDA / SDI
#define PIN_BMP_MISO  30   // SDO

// ---------- RFID RC522 (SPI por software) ----------
#define PIN_RFID_SS   9    // SDA (SS)
#define PIN_RFID_SCK  5
#define PIN_RFID_MOSI 6
#define PIN_RFID_MISO 7
#define PIN_RFID_RST  8
