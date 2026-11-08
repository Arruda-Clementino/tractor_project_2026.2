/*
///////////////////////////////////////////////////////////////////
Funções de manipulação do algoritmo PID
Biblioteca para controle PID

Data de criação: 10/09/2015
Data de modificação: 31/03/2017 VL - Clube de Robótica IFPB

O valor retornado pelas funções PID_M1() e PID_M2() são os valores de referência do PWM que devem ser enviados à função Move()
///////////////////////////////////////////////////////////////////
*/

//controle PID da velocidade do motor 1
int PID_M1(int setpoint, int vel_atual)
{   
   int erro;                                        //declara o erro
   int derivativo;                                //declara o termo derivativo
   float pid_output_M1;                             //saída do controlador PID com o valor do PWM a ser enviado aos motores
  
   erro = setpoint-vel_atual;                       //define o erro atual
   
   integral_M1 = integral_M1 + erro;                //soma o valor do erro ao valor da integral
   if(integral_M1 > acc_max)                        //limita o valor da integral ao valor máximo permitido(acc_max)
   {                        
    integral_M1 = acc_max;
   }
   else if(integral_M1 < acc_min)                   //limita o valor da integral ao valor mínimo permitido(acc_min)
   {                    
    integral_M1 = acc_min;
   }
   
   derivativo = erro-erro_anterior_M1;              //define a variação do erro como a diferença entre a erro atual e o erro anterior
   erro_anterior_M1 = erro;                         //atualiza o valor do erro anterior
   
   pid_output_M1 = (kp * (float)erro) + (ki * (float)integral_M1) + (kd * (float)derivativo);   //define a saída do controle PID como a soma dos termos proporcional, integral e derivativo
   
   if(pid_output_M1 > 1023)          //proíbe que o sinal PWM seja maior que 1023 (valor máximo permitido)
   {
    pid_output_M1 = 1023;                           
   }
   else if(pid_output_M1 < -1023)   //proíbe que o sinal PWM seja menor que -1023 (valor mínimo permitido)
   {
    pid_output_M1 = -1023;                          
   }

   return pid_output_M1;
}

//controle PID da velocidade do motor 2
int PID_M2(int setpoint, int vel_atual)
{   
   int erro;                                        //declara o erro
   int derivativo;                                //declara o termo derivativo
   float pid_output_M2;                             //saída do controlador PID com o valor do PWM a ser enviado aos motores    
   
   erro = setpoint-vel_atual;                       //define o erro atual
   
   integral_M2 = integral_M2 + erro;                //soma o valor do erro ao valor da integral
   if(integral_M2 > acc_max)                        //limita o valor da integral ao valor máximo permitido(acc_max)
   {                        
    integral_M2 = acc_max;
   }
   else if(integral_M2 < acc_min)                   //limita o valor da integral ao valor mínimo permitido(acc_min)
   {                    
    integral_M2 = acc_min;
   }
   
   derivativo = erro-erro_anterior_M2;              //define a variação do erro como a diferença entre a erro atual e o erro anterior
   erro_anterior_M2 = erro;                         //atualiza o valor do erro anterior
   
   pid_output_M2 = (kp * (float)erro) + (ki * (float)integral_M2) + (kd * (float)derivativo);   //define a saída do controle PID como a soma dos termos proporcional, integral e derivativo
   
   if(pid_output_M2 > 1023)          //proíbe que o sinal PWM seja maior que 1023 (valor máximo permitido)
   {
    pid_output_M2 = 1023;                           
   }
   else if(pid_output_M2 < -1023)   //proíbe que o sinal PWM seja menor que -1023 (valor mínimo permitido)
   {
    pid_output_M2 = -1023;                          
   }

   return pid_output_M2;
}

