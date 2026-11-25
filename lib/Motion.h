#pragma once

// ---------------------------------------------------------------
// Motion - Movimento do trator (projeto MyRobot_IFPB)
// Encapsula o antigo setup() e o antigo loop() do MyRobot_IFPB.ino
// ---------------------------------------------------------------

// Antigo setup(): I2C, Serial, pinos, PWM, encoders, beep, Timer3.
// Chamar uma vez no setup() da main.
void Motion_Init();

// Antigo loop(): quando o Timer3 sinaliza (a cada 50 ms) lê encoders e
// sensores de luz e executa o PID/Move. Chamar em TODO ciclo do loop().
void Motion_Loop();
