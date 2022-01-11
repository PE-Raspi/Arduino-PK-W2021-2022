#include "Exercices.h"


void led_OFF(){
	PORTB|=1<<4;
}

void led_ON(){
	PORTB&=~(1<<4);
}

void alternance(){
	PORTB^=1<<4;
}


