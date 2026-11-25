#pragma once

#include <Arduino.h>
#include "Types.h"

// Inicia o BMP280 (SPI por software). Se não achar o sensor, valid fica false.
void BmpDriver_Init();

// Lê temperatura e pressão. Pode ser chamado em todo ciclo:
// internamente só lê a cada 1000 ms.
void BmpDriver_Update();

// Retorna uma cópia da última leitura (não lê hardware).
Bmp280Data BmpDriver_Get();
