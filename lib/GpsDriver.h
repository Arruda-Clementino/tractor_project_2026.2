#ifndef GPS_DRIVER_H
#define GPS_DRIVER_H

#include "Types.h"

void teste();

// Inicializa a comunicação serial com o módulo NEO-6M
void GpsDriver_init();

// Lê os bytes da serial e alimenta o decodificador NMEA (deve rodar continuamente)
void GpsDriver_update();

// Retorna uma cópia limpa dos dados atuais do GPS
GpsData GpsDriver_getData();

#endif