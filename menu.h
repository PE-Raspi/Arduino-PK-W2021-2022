
#ifndef MENU_H
#define MENU_H
#include "Exercices.h"

//#define TRANCHE 1024/NB_MENU

enum enum_state_display {
	PASSWORD,
	MENU,
	OUTPUT,
	UART
};



int8_t split_adc(int16_t adc, int8_t nb_tranche);
void main_display(int16_t adc);
void display_menu(int16_t adc);
int8_t adc_to_number(int16_t adc);
void display_password();
int8_t check_password();
void display_output(int8_t nb_adc);
void print_title();

#endif // MENU_H
