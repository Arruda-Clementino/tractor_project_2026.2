/*
///////////////////////////////////////////////////////////////////
Definições e declaração de variáveis globais
///////////////////////////////////////////////////////////////////
*/

//globais
volatile bool Perform_reads=false;   //flag de habilitação para varredura das leituras dos sensores


//comunicação I2C
#define   Encoders             0x01     //define o endereço I2C do dispositivo "Encoders" como 0x01
#define   Nbytes_encoders      4        //número de bytes a ser recebido via I2C do dispositivo Encoders
int contador_M1=0;                      //armazenamento do valor de contagem do encoder do motor 1
int contador_M2=0;                      //armazenamento do valor de contagem do encoder do motor 2


//PID
#define   max_vel   400      //define a velocidade máxima em pulsos do encoder (declarada apenas para informação)
#define   min_vel   10       //define a velocidade mínima em pulsos do encoder (declarada apenas para informação)

#define   kp        2.5      //constante de ganho proporcional
#define   ki        1.0      //constante de ganho integral (o valor mínimo de Ki deve ser tal que ki*acc_max >= 1023)
#define   kd        0.05     //constante de ganho derivativo

#define   acc_max   1023     //valor máximo para o acumulador de erro (valor original 2000)
#define   acc_min   -1023    //valor mínimo para o acumulador de erro (valor original 2000)

int setpoint_M1=75;           //valor desejado da velocidade do motor (em pulsos do encoder)
int setpoint_M2=75;

int erro_anterior_M1=0;      //erro anterior entre setpoint e valor medido (usado no cálculo do termo derivativo)
int erro_anterior_M2=0;

int integral_M1=0;         //acumulador do erro (usado no cálculo do termo integral)
int integral_M2=0;

//O bloco de código abaixo só é compilado na necessidade de aceleração e desaceleração suaves dos motores
#ifdef  ACCEL
  int setpoint_M1_copy=setpoint_M1;    //faz uma cópia do setpoint do motor M1
  int setpoint_M2_copy=setpoint_M2;    //faz uma cópia do setpoint do motor M2
  int setpoint_M1_tracker=0;           //rastreador do setpoint (permite aceleração e desaceleração suave dos motores)
  int setpoint_M2_tracker=0;
  int aceleracao=1;                    //define a taxa de aceleração (por interrupção)
#endif

//ADC
byte Light_sensor[7];
byte ADC_sensors;
