#include "Exercices.h"



void config_ADC(){
	ADCSRA=0b10011111;
	ADMUX=0b01000000;
}


void main(){

	char all_row_up[8]={
		0b00111,
		0b00011,
		0b00101,
		0b01000,
		0b10000,
		0b00010,
		0b11111,
		0b00010
	};
	char all_row_down[8]={
		0b00010,
		0b11111,
		0b00010,
		0b10000,
		0b01000,
		0b00101,
		0b00011,
		0b00111
	};
	char row_up[8]={
		0b00111,
		0b00011,
		0b00101,
		0b01000,
		0b10000,
		0b00000,
		0b00000,
		0b00000
	};
	char none_row[8]={
		0b00000,
		0b00000,
		0b00000,
		0b00000,
		0b00000,
		0b00000,
		0b00000,
		0b00000
	};


	//DDRB|=(1<<PB2)|(1<<PB1)|(1<<PB0);
	DDRB=0b00111100;	
	DDRD=0b00000000;	// Set button input
	PORTB=0b00111100;	// Set leds on PORTB off

	//_delay_ms(1000);
	//PORTB=0x00;
	

	//int32_t i=0;
	//int8_t state1=0;
	//int8_t state2=0;
	
	
	//init_UART();
	//disable_UART();
	config_ADC();
	LCD_Initalize();
	init_interrupt();
	//clear_eeprom();
	get_password();

	LCD_Clear();
	LCD_RegisterCustomChar(all_row_up, 0);
	LCD_RegisterCustomChar(all_row_down, 1);
	LCD_RegisterCustomChar(row_up, 2);
	LCD_RegisterCustomChar(none_row, 3);
	LCD_GoTo(15,0);
	LCD_DisplayCustomChar(0);
	LCD_GoTo(15,1);
	LCD_DisplayCustomChar(1);
	LCD_GoTo(0,0);
	//LCD_WriteText("Pierre-Elric");



	STATE_DISPLAY=PASSWORD;
	STATE_UART=OFF;

	for (int8_t i; i<16; i++){button[i]=(-1);}	// Clean button

	LCD_GoTo(1,0);
	LCD_WriteText("Password:");
	while (!check_password());
	for (int8_t i; i<16; i++){button[i]=(-1);}
	for (;;){
		_delay_ms(200);
		LCD_Clear();
		LCD_GoTo(15,0);
		LCD_DisplayCustomChar(2);
		STATE_DISPLAY=MENU;
		
		while ((PIND & (1u<<0)));
		while (!(PIND& (1u<<0)));
		
		_delay_ms(200);
		LCD_Clear();
		LCD_GoTo(15,0);
		LCD_DisplayCustomChar(2);
		STATE_DISPLAY=OUTPUT;

		_delay_ms(100);
		
		while ((PIND & (1u<<0)));
		while (!(PIND& (1u<<0)));
		while (UBRR0L != 0x00);
	}
	
	while (1){
		/*
		PORTB &=~((1<<PB2)|(1<<PB1)|(1<<PB0));
		PORTB=0b00111100;
		_delay_ms(1000);
		PORTB |=((1<<PB2)|(1<<PB1)|(1<<PB0));
		PORTB=0x00;
		_delay_ms(1000);
		*/

		
		// Timer1
		/*
		if (TIFR1 & 1){
			state1=~state1;
			TIFR1|=0x01;
			if (state1){
				led_OFF();
			}
			else {led_ON();}
		}
		*/

		/*
		if ((PIND & 1) == 0){
			if (i<100000){
				i++;
			}
			else {
				state2=~state2;
				i=0;
				if (state2){
					PORTB|=0b00001000;
				}
				else {PORTB&=0b11110111;}
			}
		}
		else {PORTB|=0b00001000;}
		*/
		
	}
}
