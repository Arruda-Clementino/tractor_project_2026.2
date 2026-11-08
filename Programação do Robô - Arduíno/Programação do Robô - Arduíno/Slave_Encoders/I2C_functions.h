/*
///////////////////////////////////////////////////////////////////
Funções de manipulação do barramento I2C
///////////////////////////////////////////////////////////////////
*/

//função executada para atender à requisição de leitura do barramento I2C
void requestEvent(void)
{
  digitalWrite(led_status, !digitalRead(led_status));   //inverte o status do led de status
  //Serial.println(contador_M1);    
    
  //responde com a mensagem com os 4 bytes referentes aos dois contadores  
  Wire.write(contador_M1);
  Wire.write(contador_M1>>8);
  Wire.write(contador_M2);
  Wire.write(contador_M2>>8);  

  back_loop=true;   //sinaliza o retorno ao loop principal  
}


//função executada para atender à requisição de escrita do barramento I2C
void receiveEvent(void)
{
  byte dado_recebido=0;
  dado_recebido = Wire.read();

  if(dado_recebido == 0xAA)
  {
    contador_M1=0;
    contador_M2=0;
    back_loop=true;   //sinaliza o retorno ao loop principal     
  }  
}
