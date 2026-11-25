/*
///////////////////////////////////////////////////////////////////
Funções para movimentação do robô
///////////////////////////////////////////////////////////////////
*/

//Função principal de movimentação do robô
//Devem ser fornecidas as velocidades dos dois motores no intervalo [-1023,1023]
void Move(int vel_1, int vel_2)
{
  //definição das direções de rotação dos motores
  if (vel_1>0)
    frente_M1();    //gira pra frente
  else
  {
    if (vel_1<0)
      re_M1();      //gira pra trás
    else
      break_M1();   //para
  }

  if (vel_2>0)
    frente_M2();    //gira pra frente
  else
  {
    if (vel_2<0)
      re_M2();      //gira pra trás
    else
      break_M2();   //para
  } 

  //atualização do duty cicle
  PWM1_duty(abs(vel_1));
  PWM2_duty(abs(vel_2));
}

//Funções auxiliares de movimentação
void frente_M1()
{
  digitalWrite(INA1, HIGH);
  digitalWrite(INB1, LOW);
}
void re_M1()
{
  digitalWrite(INA1, LOW);
  digitalWrite(INB1, HIGH);
}
void break_M1()
{
  digitalWrite(INA1, LOW);
  digitalWrite(INB1, LOW);
}
void frente_M2()
{
  digitalWrite(INA2, HIGH);
  digitalWrite(INB2, LOW);
}
void re_M2()
{
  digitalWrite(INA2, LOW);
  digitalWrite(INB2, HIGH);
}
void break_M2()
{
  digitalWrite(INA2, LOW);
  digitalWrite(INB2, LOW);
}

#ifdef ACCEL
  //função para aceleração/desaceleração suaves do motor
  void Drive()
  {
    if(setpoint_M1_tracker != setpoint_M1)
    {
      if(setpoint_M1_tracker < setpoint_M1)
        setpoint_M1_tracker = setpoint_M1_tracker + aceleracao;
      else
        setpoint_M1_tracker = setpoint_M1_tracker - aceleracao;          
    }
  
    if(setpoint_M2_tracker != setpoint_M2)
    {
      if(setpoint_M2_tracker < setpoint_M2)
        setpoint_M2_tracker = setpoint_M2_tracker + aceleracao;
      else
        setpoint_M2_tracker = setpoint_M2_tracker - aceleracao;          
    }  
  }
#endif

