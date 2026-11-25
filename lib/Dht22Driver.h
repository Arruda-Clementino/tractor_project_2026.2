#pragma once

#include <Arduino.h>
#include "Types.h"

// Inicia o sensor DHT22.
void Dht22Driver_Init();

// Tenta uma leitura física. Pode ser chamado em todo ciclo do loop():
// internamente só lê o sensor a cada 2000 ms (limite físico do DHT22).
void Dht22Driver_Update();

// Retorna uma cópia da última leitura (não bloqueia, não lê hardware).
Dht22Data Dht22Driver_Get();
