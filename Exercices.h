
#ifndef EXERCICES_H
#define EXERCICES_H

#define True 	1
#define true	1
#define False 	0
#define false 	0

#define F_CPU 16000000UL 	// 16 MHz, with util/delay.h
//#define NB_MENU 10

#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>

#include "uart.h"
#include "lib.h"
#include "HD44780.h"
#include "menu.h"
#include "interrupt.h"
#include "eeprom.h"

extern enum enum_state_display STATE_DISPLAY;
extern enum enum_state_uart STATE_UART;

#endif // EXERCICES_H
