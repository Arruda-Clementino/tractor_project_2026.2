/*
///////////////////////////////////////////////////////////////////
Função Setup para inicialização de hardwares internos
A função setup() roda uma vez quando alimentamos a placa ou pressionamos o botão de reset
///////////////////////////////////////////////////////////////////
*/

//a função setup() roda uma vez no início da execução do programa
void setup()
{  
  Serial.begin(250000);             //inicializa a porta serial   
  pinMode(led_status, OUTPUT);      //configura o pino conectado ao LED como saída
  pinMode(pin_A1, INPUT);           //configura o pino conectado ao terminal A do encoder do motor 1 como entrada
  pinMode(pin_A2, INPUT);           //configura o pino conectado ao terminal A do encoder do motor 2 como entrada
  pinMode(pin_B1, INPUT);           //configura o pino conectado ao terminal B do encoder do motor 1 como entrada
  pinMode(pin_B2, INPUT);           //configura o pino conectado ao terminal B do encoder do motor 2 como entrada

  digitalWrite(led_status, LOW);    //inicializa o LED com nível lógico baixo
  Wire.begin(Slave_Address);        //inicializa o barramento I2C fornecendo o endereço do dispositivo escravo
  Wire.onRequest(requestEvent);     //indica o nome da função para atendimento da interrupção de leitura do I2C
  Wire.onReceive(receiveEvent);     //indica o nome da função para atendimento da interrupção de escrita do I2C

  contador_M1=0;  //inicializa os contadores M1 e M2 com zero
  contador_M2=0;
  
  //faz as leituras das condições iniciais dos terminais dos encoders
  Estado_Anterior_A1 = digitalRead(pin_A1);
  Estado_Anterior_B1 = digitalRead(pin_B1);
  Estado_Anterior_A2 = digitalRead(pin_A2);
  Estado_Anterior_B2 = digitalRead(pin_B2);  
}

