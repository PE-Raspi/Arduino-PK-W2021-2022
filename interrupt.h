#ifndef INTERRUPT_H
#define INTERRUPT_H
#include "Exercices.h"

extern volatile int16_t adc_value;
extern volatile int8_t button[16];
extern volatile int16_t old_time;


void init_interrupt();

// Interrupt on timer1
// Send ACD conversion
ISR(TIMER1_OVF_vect);

// Interrupt on end of ACD conversion
// Send display menu
ISR(ADC_vect);

// Interrupt on button
ISR(PCINT2_vect);


#endif 	// INTERRUPT_H
