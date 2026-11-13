#ifndef PINOUT_H
#define PINOUT_H

#include <Arduino.h>

// ==========================================
// 1. GPS GY-NEO6MV2 (Hardware Serial1)
// ==========================================
#define GPS_SERIAL Serial1
const uint32_t GPS_BAUD = 9600;

// ==========================================
// 2. Sensor BMP280 (Barramento I2C)
// ==========================================
const uint8_t BMP280_I2C_ADDR = 0x76;

// ==========================================
// 3. Leitor RFID-RC522 (Pinos Digitais 4 a 8)
// ==========================================
const uint8_t PIN_RFID_SS   = 4; // SDA
const uint8_t PIN_RFID_SCK  = 5; // SCK
const uint8_t PIN_RFID_MOSI = 6; // MOSI
const uint8_t PIN_RFID_MISO = 7; // MISO
const uint8_t PIN_RFID_RST  = 8; // RST

// ==========================================
// 4. Sensor DHT22 (Digital)
// ==========================================
const uint8_t PIN_DHT22 = 2;

#endif