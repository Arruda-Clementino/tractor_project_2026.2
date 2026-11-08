/*
  Código do Arduino Pro Mini, escravo do arduíno Mega do robô seguidor de linha.

  Esse código conta os pulsos dos encoders dos motores 1 e 2 e o armazena em duas variáveis do tipo inteira.
  Os pulsos são incrementados para rotações do eixo no sentido frontal, e decrementados para rotações no sentido contrário.
  Para transmitir a contagem via comunicação I2C, as variáveis inteiras são transmitidas byte a byte (4 bytes no total)
*/

//inclusões de arquivos auxiliares

#include <Wire.h>                   //inclui a biblioteca para operação com I2C
#include "Global_variables.h"       //declaração das variáveis globais
#include "Pin_assignment.h"         //atribuição de pinos
#include "Functions_prototypes.h"   //declaração dos protótipos das funções
#include "I2C_functions.h"          //funções de manipulação do barramento I2C
#include "Setup.h"                  //função setup para inicialização do hardware interno

//Função principal
void loop()
{
  //faz uma nova leitura para determinação do estado atual dos terminais dos encoders
  Estado_Atual_A1 = digitalRead(pin_A1);
  Estado_Atual_B1 = digitalRead(pin_B1);
  Estado_Atual_A2 = digitalRead(pin_A2);
  Estado_Atual_B2 = digitalRead(pin_B2);

  //verifica se houve mudança de estado nos pinos do encoder do motor 1
  if (Estado_Atual_A1 != Estado_Anterior_A1) //verifica se houve mudança no pino A
  {
    if (Estado_Atual_A1 != Estado_Atual_B1)
      ++contador_M1;
    else
      --contador_M1;          
    Estado_Anterior_A1 = Estado_Atual_A1;            
  }
  if (Estado_Atual_B1 != Estado_Anterior_B1) //verifica se houve mudança no pino B
  {
    if (Estado_Atual_B1 == Estado_Atual_A1)
      ++contador_M1;
          
    else
      --contador_M1;          
    Estado_Anterior_B1 = Estado_Atual_B1;        
  }

  //verifica se houve mudança de estado nos pinos do encoder do motor 2
  if (Estado_Atual_A2 != Estado_Anterior_A2) //verifica se houve mudança no pino A
  {
    if (Estado_Atual_A2 != Estado_Atual_B2)
      ++contador_M2;
    else
      --contador_M2;          
    Estado_Anterior_A2 = Estado_Atual_A2;           
  }
  if (Estado_Atual_B2 != Estado_Anterior_B2) //verifica se houve mudança no pino B
  {
    if (Estado_Atual_B2 == Estado_Atual_A2)
      ++contador_M2;
          
    else
      --contador_M2;          
    Estado_Anterior_B2 = Estado_Atual_B2;        
  }

  //zera as variáveis contador_M1 e contador_M2 após retornarem das funções de interrupção I2C,
  //pois essas variáveis não podem ser alteradas nas funções de interrupção caso elas estejam sendo atualizadas no momento em que ocorre a chamada
  if(back_loop)         
  {
      contador_M1=0;
      contador_M2=0;
      back_loop=false;
  }
}


