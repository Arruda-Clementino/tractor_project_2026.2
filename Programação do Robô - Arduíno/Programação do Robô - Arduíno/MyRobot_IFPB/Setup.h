/*
///////////////////////////////////////////////////////////////////
Função Setup para inicialização de hardwares internos
A função setup() roda uma vez quando alimentamos a placa ou pressionamos o botão de reset
///////////////////////////////////////////////////////////////////
*/

void setup()
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
