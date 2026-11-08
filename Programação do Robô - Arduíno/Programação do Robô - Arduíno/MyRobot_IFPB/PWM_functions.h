/*
///////////////////////////////////////////////////////////////////////////////////////
Funções de manipulação dos sinais PWM

Relação entre os Timers e sinal PWM nos pinos:
  Timer 0 —>  pinos 4, 13
  Timer 1 —>  pinos 11, 12
  Timer 2 —–  pin 9, 10
  Timer 3 —–  pin 2, 3, 5
  Timer 4 —–  pin 6, 7, 8
  Timer 5 —– pin 44, 45, 46  
O timer 0 é usado nativamente nas funções de controle de tempo do Arduino ex.: delay();
///////////////////////////////////////////////////////////////////////////////////////
*/

//Função de configuração do TIMER1 para geração de sinais PWM1 e PWM2 nos pinos 11 e 12
void PWM12_config()
{
  //Ajuste dos sinais PWM1 e PWM2 para 2 kHz de frequência e 10 bits de resolução     
  TCCR1A = TCCR1A | 0b10100011; //seta os bits COM1A1, COM1B1, WGM11 e WGM10
  TCCR1A = TCCR1A & 0b10101111; //reseta o bit COM1A0, COM1B0
  TCCR1B = TCCR1B | 0b00001010; //seta os bits WGM12 e CS11
  TCCR1B = TCCR1B & 0b11101010; //reseta os bits WGM13, CS12 e CS10     
}

//Atualização do duty cicle do sinal PWM1
void PWM1_duty(unsigned int duty)
{
  if(!duty)
  {
    TCCR1A = TCCR1A & 0b01111111; //desabilita o pino 11    
  }
  else
  {
    TCCR1A = TCCR1A | 0b10000000; //reabilita o pino 11
    OCR1A = duty;    
  }    
}

//Atualização do duty cicle do sinal PWM2
void PWM2_duty(unsigned int duty)
{
  if(!duty)
  {
    TCCR1A = TCCR1A & 0b11011111; //desabilita o pino 12    
  }
  else
  {
    TCCR1A = TCCR1A | 0b00100000; //reabilita o pino 12
    OCR1B = duty;    
  }    
}
