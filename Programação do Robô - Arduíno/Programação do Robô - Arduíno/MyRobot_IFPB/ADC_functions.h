/*
///////////////////////////////////////////////////////////////////
Funções de manipulação do conversor AD

Data de criação: 04/07/2017
///////////////////////////////////////////////////////////////////
*/

//configuração do conversor AD para resolução de 8 bits e velocidade de conversão de xx amostras por segundo
void ADC_Config()
{
  analogReference(DEFAULT);   //+5V é usado como valor máximo permitido para conversão  
}

//liga o sensor de luz seguidor de linha
void Sensor_ON()
{
  digitalWrite(LIGHT_SENSOR, LOW);  //liga o sensor de luz (o sensor é ativo em LOW)  
}

//desliga o sensor de luz seguidos de linha
void Sensor_OFF()
{
  digitalWrite(LIGHT_SENSOR, HIGH);  //desliga o sensor de luz (o sensor é ativo em LOW)  
}

//faz a leitura dos 7 sensores de luz seguidores de linha
void Read_Lightsensor(void)
{
  //executa a varredura dos sensores de luz e converte a leitura para 8 bits
  for(int contador=0; contador<=6; ++contador)
  {
    Light_sensor[contador] = analogRead(contador) >> 2;    
  }
  
  for(int contador=0; contador<=6; ++contador)
  {
    if(Light_sensor[contador] > 170)
      bitSet(ADC_sensors, contador);
    else
      bitClear(ADC_sensors, contador);    
  }  
}

