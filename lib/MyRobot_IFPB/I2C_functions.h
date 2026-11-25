/*
///////////////////////////////////////////////////////////////////
Funções de manipulação do barramento I2C
///////////////////////////////////////////////////////////////////
*/

//varredura na leitura dos dispositivos I2C
void I2C_reads()
{
  byte encoder_read[4];                               //variável de armazenamento da leitura do encoder
  byte contador=0;  

  //leitura do dispositivo Encoders
  Wire.requestFrom(Encoders, Nbytes_encoders);        //solicita Nbytes_encoders do dispositivo Encoders
  while (Wire.available())
  {
    encoder_read[contador] = Wire.read(); //recebe um byte
    ++contador;       
  }
  
  contador_M1 = encoder_read[1]<<8 | encoder_read[0];
  contador_M2 = encoder_read[3]<<8 | encoder_read[2];  
}

//reseta as variáveis contadoras de pulso do Arduino Pro mini
void reset_encoders()
{
  Wire.beginTransmission(Encoders); //inicia a transmissão para o dispositvo Encoders                             
  Wire.write(0xAA);                 //envia o valor 0xAA para o dispositivo Encoders  
  Wire.endTransmission();           //finaliza a transmissão  
}


