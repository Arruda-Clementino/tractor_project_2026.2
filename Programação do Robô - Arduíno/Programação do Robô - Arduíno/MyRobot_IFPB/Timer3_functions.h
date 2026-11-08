/*
///////////////////////////////////////////////////////////////////
Funções relativas à operação do Timer3
///////////////////////////////////////////////////////////////////
*/

//Função de configuração do Timer3 para geração de interrupções periódicas a cada 50 ms
void timer3_config()
{
  noInterrupts();                 //desabilita todas as interrupções
  TCCR3A = TCCR3A & 0b11111100;   //ajusta o modo do Timer para comparação com o registrador OCR
  TCCR3B = TCCR3B | 0b00001011;   //configura o prescaler para fosc/64 e ajusta o modo do Timer para comparação com o registrador OCR
  TCCR3B = TCCR3B & 0b11101011;   
  OCR3A = 12500;                  //ajusta o valor para comparação (gerando interrupção a cada 50 ms)
  TIMSK3 = TIMSK3 | 0b00000010;   //habilita a interrupção por comparação
  interrupts();                   //reabilita todas as interrupções
}

//Função de atendimento da interrupção do Timer3
ISR(TIMER3_COMPA_vect)
{ 
  Perform_reads = true;           //habilita o flag de varredura para leitura de todos os sensores  
}

