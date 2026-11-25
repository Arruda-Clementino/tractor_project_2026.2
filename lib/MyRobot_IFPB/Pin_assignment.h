/*
///////////////////////////////////////////////////////////////////
Atribuição dos pinos do arduino
///////////////////////////////////////////////////////////////////
*/

          //Descrição     //número do pino 
#define   led_status      13    //nomeia o pino 13 como "led_status"
#define   buzzer          48    //nomeia o pino 48 como "buzzer"
#define   PWM1            11    //nomeia o pino 11 como PWM1
#define   PWM2            12    //nomeia o pino 12 como PWM2
#define   INA1            52    //nomeia o pino 52 como INA1
#define   INB1            53    //nomeia o pino 53 como INB1
#define   INA2            50    //nomeia o pino 50 como INA2
#define   INB2            51    //nomeia o pino 51 como INB2
#define   LIGHT_SENSOR    49    //nomeia o pino 49 como LIGHT_SENSOR (sensores de luz)


//Configuração da direção dos pinos de entrada/saída.
void pins_configuration(void)
{  
  //Pinos de saída:
  pinMode(led_status, OUTPUT);  //saída para um led de status no pino 13
  digitalWrite(led_status, LOW); //inicializa o led de status
  
  pinMode(buzzer, OUTPUT);      //saída para um buzzer no pino 23
  digitalWrite(buzzer, LOW);    //inicia o beep desligado
  
  pinMode(PWM1, OUTPUT);        //saída do sinal PWM do motor 1 no pino 11
  pinMode(PWM2, OUTPUT);        //saída do sinal PWM do motor 2 no pino 12
  pinMode(INA1, OUTPUT);        //saída do sinal INA1 (faz o motor M1 girar para frente)
  pinMode(INB1, OUTPUT);        //saída do sinal INB1 (faz o motor M1 girar para trás)
  pinMode(INA2, OUTPUT);        //saída do sinal INA2 (faz o motor M2 girar para frente)
  pinMode(INB2, OUTPUT);        //saída do sinal INB2 (faz o motor M2 girar para trás)

  digitalWrite(LIGHT_SENSOR, HIGH);  //inicia o sensor desligado (o sensor é ativo em LOW)
  pinMode(LIGHT_SENSOR, OUTPUT);     //saída para ativação dos sensores de luz     
}

