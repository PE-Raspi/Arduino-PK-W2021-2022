#ifndef EEPROM_H
#define EEPROM_H
#include "Exercices.h"


#ifndef _STRING_H_
#include <string.h>
#endif

extern char password[20][2][16];
extern uint8_t NB_MENU;
extern uint16_t TRANCHE;

void get_password();
void write_word (char* chaine);
void add_title_pw(char* title, char* pw);
void clear_eeprom();
uint8_t* research_separator_pack(uint8_t* i);
uint8_t* research_separator_password(uint8_t* i);
uint8_t* research_blank_pack();
void eeprom_user_title(int8_t numbre, char* title);
void eeprom_password(int8_t numbre, char* pw);
void delete(int8_t number);
#endif 	// EEPROM_H
