#pragma once

#include <Arduino.h>
#include "Types.h"

// Abre a Serial1 e zera os dados.
void GpsDriver_Init();

// Esvazia a Serial do GPS e atualiza os dados.
// Chamar em TODO ciclo do loop(), sem delay, para não perder bytes.
void GpsDriver_Update();

// Retorna uma cópia da última leitura (não bloqueia, não lê hardware).
GpsData GpsDriver_Get();
