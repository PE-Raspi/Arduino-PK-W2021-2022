#include "Exercices.h"



volatile char buffer[8][64];
volatile int8_t buffer_index;
volatile int8_t param_index;
volatile int8_t info_to_treat;

enum enum_state_uart STATE_UART;

void init_UART(){
	
	UCSR0A = 0x00;
	UCSR0B = 0b11011000;
	UCSR0C = 0b00000110;

	UBRR0H = 0x00;	UBRR0L = 103; 	// BAUD Rate = 9600;

	char buffer[8][64]={0};
	int8_t buffer_index=0;
	int8_t param_index=0;
	int8_t info_to_treat=0;
	
	STATE_UART=MAIN;
}
void disable_UART(){
	UCSR0A = 0x00;
	UCSR0B = 0x00;
	UCSR0C = 0x00;

	UBRR0H = 0x00;	UBRR0L = 0x00;
	
	STATE_DISPLAY=MENU;
	STATE_UART=OFF;
}

ISR(USART_TX_vect){
	UCSR0A|=0x40;
}

ISR(USART_RX_vect){
	char lettre;
	lettre=UDR0;
	//alternance();
	traitement(lettre);
	UDR0=lettre;
	UCSR0A|=0x80;
}

ISR(USART_UDRE_vect){
	//alternance();
	UCSR0A|=0x20;
}

void sendchar(char lettre){
	while(!(UCSR0A & (1<<UDRE0)));
	UDR0=(lettre);
}

void print(char* chaine){
	//int8_t size_chaine= (&chaine)[1]-chaine;
	int8_t size_chaine= strlen(chaine);
	for (int8_t i=0; i<=size_chaine; i++){
		//buffer[i]=chaine[i];
		sendchar(chaine[i]);
	}
}
void print_int(char * chaine, uint8_t nb){
	char str[20];
	sprintf(str, "%s : %d\r\n",chaine, nb);
	print(str);

}

void print_buffer(){
	//int* p_buffer=&buffer;
	//print( buffer[0]);
	//print( buffer[1]);
	
	for (int8_t i; i<8; i++){
		print( buffer[i]);
		sendchar(' ');
	}
}

void traitement(char lettre){
	if (lettre=='\r'){
		info_to_treat=1;
		sendchar('\r');
		sendchar('\n');
	}
	else if (lettre == ' '){
		buffer_index=0;
		param_index++;
	}
	else {
		buffer[param_index][buffer_index]=lettre;
		buffer_index++;
	}
}
