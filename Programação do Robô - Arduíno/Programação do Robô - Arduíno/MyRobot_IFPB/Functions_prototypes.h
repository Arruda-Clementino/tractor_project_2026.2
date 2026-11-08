/*
///////////////////////////////////////////////////////////////////
Declaração dos protótipos das funções
///////////////////////////////////////////////////////////////////
*/

//Timer3
void timer3_config(void);       //função de configuração do Timer3 para geração de interrupções

//PWM
void PWM12_config(void);        //configura o timer 1 para geração dos sinais PWM1 e PWM2 usado nos motores
void PWM1_duty(unsigned int);   //ajusta o duty cicle do sinal PWM1
void PWM2_duty(unsigned int);   //ajusta o duty cicle do sinal PWM2

//Movimentação
void Move(int, int);    //função genérica de movimentação do robô
void frente_M1(void);   //faz o motor M1 girar para frente
void frente_M2(void);   //faz o motor M2 girar para frente
void re_M1(void);       //faz o motor M1 girar para trás
void re_M2(void);       //faz o motor M2 girar para trás
void break_M1(void);    //faz o motor M1 travar
void break_M2(void);    //faz o motor M2 travar
#ifdef ACCEL
  void Drive();           //função para aceleração/desaceleração suaves do motor 
#endif

//I2C
void I2C_reads(void);       //executa a varredura das leituras dos componetes I2C
void reset_encoders(void);  //reseta as variáveis contadoras de pulso do Arduino Pro mini


//PID
int PID_M1(int, int);   //Executa o controle PID para o PWM do motor 1
int PID_M2(int, int);   //Executa o controle PID para o PWM do motor 2

//ADC
void ADC_Config(void);        //configura o conversor AD
void Sensor_ON(void);         //liga o sensor de luz seguidor de linha
void Sensor_OFF(void);        //desliga o sensor de luz seguidor de linha
void Read_Lightsensor(void);  //faz a leitura dos 7 sensores de luz
