#ifndef RFID_DRIVER_H
#define RFID_DRIVER_H

#include "Types.h"

// Inicializa o leitor RFID-RC522 nos pinos configurados no Pinout.h
void RfidDriver_init();

// Verifica se um novo cartao foi aproximado.
// Retorna true apenas no instante em que um cartao e lido.
bool RfidDriver_update();

// Retorna os dados do ultimo implemento lido (tipo, uid, nome, identificado)
RfidData RfidDriver_getData();

// Limpa os dados da leitura atual (volta para IMPLEMENTO_NENHUM)
void RfidDriver_clear();

#endif