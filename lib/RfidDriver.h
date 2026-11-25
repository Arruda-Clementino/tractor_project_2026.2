#pragma once

#include <Arduino.h>
#include "Types.h"

// Configura os pinos, reseta o MFRC522 e liga a antena.
void RfidDriver_Init();

// Procura uma tag nova no leitor. Chamar a cada ~100 ms.
// Retorna true só quando uma tag NOVA foi lida neste ciclo
// (use para enviar o evento imediato). Sem tag, retorna false e o
// último implemento identificado continua valendo.
bool RfidDriver_Update();

// Retorna uma cópia do implemento atual (não lê hardware).
RfidData RfidDriver_Get();
