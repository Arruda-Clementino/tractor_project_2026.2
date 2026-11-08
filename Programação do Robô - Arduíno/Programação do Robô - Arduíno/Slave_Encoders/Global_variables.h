/*
///////////////////////////////////////////////////////////////////
Definições e declaração de variáveis globais
///////////////////////////////////////////////////////////////////
*/


#define Slave_Address 0x01     //define o endereço deste dispositivo slave
#define atraso        10       //define o delay (em microsegundos) entre leituras consecutivas nos terminais do encoder

//variáveis globais
int contador_M1;      //variável que guarda a quantidade de pulsos do encoder do motor 1
int contador_M2;      //variável que guarda a quantidade de pulsos do encoder do motor 2

bool Estado_Atual_A1;          //variável booleana que guarda a leitura atual do nivel lógico do sinal A do encoder do motor 1
bool Estado_Atual_B1;          //variável booleana que guarda a leitura atual do nivel lógico do sinal B do encoder do motor 1
bool Estado_Atual_A2;          //variável booleana que guarda a leitura atual do nivel lógico do sinal A do encoder do motor 2
bool Estado_Atual_B2;          //variável booleana que guarda a leitura atual do nivel lógico do sinal B do encoder do motor 2

bool Estado_Anterior_A1;       //variável booleana que guarda a leitura anterior do nivel lógico do sinal A do encoder do motor 1
bool Estado_Anterior_B1;       //variável booleana que guarda a leitura anterior do nivel lógico do sinal B do encoder do motor 1
bool Estado_Anterior_A2;       //variável booleana que guarda a leitura anterior do nivel lógico do sinal A do encoder do motor 2
bool Estado_Anterior_B2;       //variável booleana que guarda a leitura anterior do nivel lógico do sinal B do encoder do motor 2

bool back_loop=false;          //variável de controle para zerar as variáveis contador_M1 e contador_M2 ao retornar para o loop principal
