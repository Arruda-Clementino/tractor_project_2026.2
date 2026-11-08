/*
///////////////////////////////////////////////////////////
  MyRobot_IFPB
  Programa do Robô v2.0
  Controlador do robô seguidor de linha

  Criado em 26/03/2017
  por: Clube de Robótica - IFPB - Campus Princesa Isabel
//////////////////////////////////////////////////////////
*/

//inclusões de arquivos auxiliares
#include <Wire.h>                   //inclui a biblioteca para operação com I2C
#include "Global_variables.h"       //declaração das variáveis globais
#include "Pin_assignment.h"         //atribuição de pinos
#include "Functions_prototypes.h"   //declaração dos protótipos das funções
#include "Timer3_functions.h"       //funções do Timer3
#include "PWM_functions.h"          //funções de manipulação dos sinais PWM
#include "Robot_movements.h"        //funções para movimentação do robô
#include "I2C_functions.h"          //funções de manipulação do barramento I2C
#include "PID_functions.h"          //funções de controle PID (velocidade e posição)
#include "ADC_functions.h"          //funções de manipulação do conversor AD
#include "Setup.h"                  //função setup para inicialização do hardware interno


//A função loop é a função principal e executa continuamente
void loop()
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

