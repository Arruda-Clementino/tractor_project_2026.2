#include <Arduino.h>
#include <Wire.h>                   //inclui a biblioteca para operação com I2C

#include "../lib/Motion.h"

// Arquivos originais do MyRobot_IFPB (sem nenhuma alteração), na mesma ordem do .ino
#include "Global_variables.h"       //declaração das variáveis globais
#include "Pin_assignment.h"         //atribuição de pinos
#include "Functions_prototypes.h"   //declaração dos protótipos das funções
#include "Timer3_functions.h"       //funções do Timer3
#include "PWM_functions.h"          //funções de manipulação dos sinais PWM
#include "Robot_movements.h"        //funções para movimentação do robô
#include "I2C_functions.h"          //funções de manipulação do barramento I2C
#include "PID_functions.h"          //funções de controle PID (velocidade e posição)
#include "ADC_functions.h"          //funções de manipulação do conversor AD
// Setup.h não é mais usado: o conteúdo dele virou Motion_Init() abaixo.


// ===============================================================
// Antigo setup() (Setup.h)
// ===============================================================
void Motion_Init()
{
  Wire.begin();           //inicializa o hardware de comunicação serial I2C
  Serial.begin(2000000);   //inicializa a porta serial
  
  pins_configuration();     //configura os pinos de entrada e saída
  PWM12_config();           //configura o timer1 para geração de sinais PWM
  reset_encoders();         //reseta as variáveis dos contadores no arduino Pro mini
  contador_M1=0;            //inicia os contadores locais M1 e M2 com 0
  contador_M2=0;

  //beep de sinalização do início da execução do programa  
  digitalWrite(buzzer, HIGH);
  delay(10);
  digitalWrite(buzzer, LOW);
  delay(150);
  digitalWrite(buzzer, HIGH);
  delay(10);
  digitalWrite(buzzer, LOW);
  delay(2000);  

  Move(0, 0);       //inicia o programa com os motores desligados

  ADC_Config();     //configura o conversor AD
  Sensor_OFF();      //inicia com o sensor de luz desligado  

  timer3_config();  //configura o Timer3 para geração de interrupção a cada 50ms  
}


// ===============================================================
// Antigo loop() (MyRobot_IFPB.ino)
// ===============================================================
void Motion_Loop()
{  
  if(Perform_reads)
  {
    digitalWrite(led_status,!digitalRead(led_status));  //alterna o estado do led de status para sinalizar a entrada nas leituras dos sensores
    I2C_reads();                                        //faz a varredura dos sensores conectados ao barramento I2C
    Read_Lightsensor();                                 //faz a leitura dos sensores de luz

    Move(PID_M1(setpoint_M1,contador_M1),PID_M2(setpoint_M2,contador_M2));  //movimentação dos motores
          
    Perform_reads=false;      //desliga o flag de varredura da leitura dos sensores
    
    //Serial.println(ADC_sensors, BIN);
    //Serial.println(Light_sensor[6]);
    Serial.println(contador_M1);           
  }  
}
