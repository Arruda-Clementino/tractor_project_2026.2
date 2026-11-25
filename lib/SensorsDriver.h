#pragma once

#include <Arduino.h>
#include "Types.h"

// Liga todos os sensores (GPS, DHT22, BMP280, RFID). Chamar uma vez no setup().
void SensorsDriver_Init();

// Atualiza todos os sensores. Chamar em TODO ciclo do loop(), sem delay.
// Cada sensor respeita o próprio intervalo internamente:
//   GPS   -> todo ciclo (esvazia a serial)
//   RFID  -> a cada 100 ms
//   DHT22 -> a cada 2000 ms
//   BMP   -> a cada 1000 ms
// Retorna true quando uma tag RFID NOVA foi lida neste ciclo
// (use para publicar o evento de engate na hora).
bool SensorsDriver_Update();

// Retorna uma cópia de todos os dados mais recentes (não lê hardware).
SensorsData SensorsDriver_Get();
