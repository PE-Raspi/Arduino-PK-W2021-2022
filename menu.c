#include "Exercices.h"


enum enum_state_display STATE_DISPLAY;

void main_display(int16_t adc){
	if (STATE_DISPLAY==PASSWORD){
		display_password();
	}
	else if (STATE_DISPLAY==MENU){
		display_menu(adc);
		ADCSRA |= (1<<ADSC); // start conversion
	}
	else if (STATE_DISPLAY==OUTPUT){
		display_output(adc_to_number(adc));
	}
	else if (STATE_DISPLAY==UART){
		if (STATE_UART==OFF){
			LCD_Clear();
			init_UART();
		}
		LCD_GoTo(0,0);
		LCD_WriteText("   UART Mode    ");
	}
}




int8_t split_adc (int16_t adc, int8_t nb_tranche){
	if (adc>(TRANCHE*nb_tranche) && adc<=(TRANCHE*(nb_tranche+1))){
		return true;
	}
	else return false;
}

int8_t adc_to_number(int16_t adc){
	for (int i=0; i<20; i++){
		if (split_adc(adc, i)){
			return i;
		}
	}

	if (adc==0)
		return 0;
	else return -1;
}


void display_menu(int16_t adc){

	int8_t state_menu=adc_to_number(adc);

	char aff1[15]="UART MODE     ";
	char aff2[15]="              ";

	state_menu-=1;
	
	if (state_menu!=-1){
		for (int8_t i=0; i<14; i++){
			if (password[state_menu][0][i]==0){
				aff1[i]=' ';
			}
			else{
				aff1[i]=password[state_menu][0][i];
			}
		}
	}
	for (int8_t i=0; i<14; i++){
		if (password[state_menu+1][0][i]==0){
			aff2[i]=' ';
		}
		else{
			aff2[i]=password[state_menu+1][0][i];
		}
	}
	

	LCD_GoTo(0,0);
	LCD_WriteData(0b01111110);	// arrow
	LCD_WriteText(aff1);
	LCD_GoTo(1,1);
	LCD_WriteText(aff2);
}

void display_password(){

	LCD_GoTo(1,1);
	for (int8_t i=0; i<16; i+=2){
		if (button[i]!=(-1)){
			LCD_WriteText("*");
		}
		else LCD_WriteText(" ");
	}

}

int8_t check_password(){
	int8_t password[8]={0,0,0,0,0,0,0,0};
	for (int8_t i=0; i<16; i+=2){
		if (button[i]!=password[i/2])
			return false;
	}
	return true;
}

void display_output(int8_t nb_adc){

	LCD_GoTo(0,0);
	char disp1[15]="               ";
	char disp2[15]="               ";

	nb_adc-=1;

	if (nb_adc==-1){
		STATE_DISPLAY=UART;
	}
	else {
		for (int8_t i=0; i<14; i++){
			disp1[i]=password[nb_adc][1][i];
		}
		for (int8_t i=14; i<28; i++){
			disp2[i-14]=password[nb_adc][1][i];
		}

		LCD_WriteText(disp1);
		LCD_WriteText(disp2);
	}
}


void print_title(){
	char str[6]={0};
	for (int8_t i=0; i<20;i++){
		if (password[i][0][0]!=NULL){
			sprintf(str, " %d - ",i);
			print(str);
			print (password[i][0]);
			print("\r\n");
		}
	}
	print("\r\n");
}

