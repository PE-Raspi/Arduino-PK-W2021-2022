
#ifndef UART_H
#define UART_H
#include "Exercices.h"

#ifndef _STRING_H_
#include <string.h>
#endif

enum enum_state_uart{
	MAIN,
	ADD_TITLE,
	PASS,
	DEL,
	DEBUG,
	OFF
};

extern volatile char buffer[8][64];
extern volatile int8_t buffer_index;
extern volatile int8_t param_index;
extern volatile int8_t info_to_treat;


void init_UART();
void disable_UART();
ISR(USART_TX_vect);
ISR(USART_RX_vect);
ISR(USART_UDRE_vect);
void sendchar(char lettre);
void print (char* chaine);
void print_buffer();
void print_int(char * chaine, uint8_t nb);
void traitement(char lettre);

#endif 	// UART_H
