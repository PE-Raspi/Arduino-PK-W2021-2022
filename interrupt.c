#include "Exercices.h"


volatile int16_t adc_value;
volatile int8_t button[16];
volatile int16_t old_time;

void init_interrupt(){
	
	sei();			// Enable interrupt
	
	//	Timer0 8bits (traitement UART)
	TCCR0A=0x00;
	TCCR0B=0x02;			// Timer runing prescaler 8
	//TCCR0B=0x00;			// Timer stoped
	TIMSK0=0x01;			// Enable interrupt

	// 	Timer1 16bits	
	TCCR1A = 0b00000000;
	//TCCR1B = 0b00000100;		// Timer runing prescaler 256
	TCCR1B = 0b00000010;		// Timer runing prescaler 8
	//TCCR1B = 0x00;			// Timer stoped
	TIMSK1 = 0x01;			// Interrupt
	
	
	//	Timer2 8bits (PWM)
	TCCR2A = 0b11000011;
	TCCR2B = 0b00000001;	// No prescaling
	//TCCR2B = 0x00;	// Timer stoped
	OCR2A = 2;

	// 	Config interrupt buttons
	PCICR=0b00000100;
	PCMSK2=0b00001111;


	for (int8_t i; i<16; i++){
		button[i]=(-1);
	}
}

// Interrupt on Timer0 (UART)
ISR(TIMER0_OVF_vect){
	if (info_to_treat){
		switch (STATE_UART){
			case MAIN:
				if(buffer[0][0]=='\0'){
					print("1 - Add password\n\r");
					print("2 - Delete\n\r");
					print("3 - Exit\n\r");
				}
				else if (buffer[0][0]=='1'){
					print("Tap your title and password ( <title> <password> ): ");
					STATE_UART=ADD_TITLE;
				}
				else if (buffer[0][0]=='2'){
					print_title();
					print("Select the password to delete : ");
					STATE_UART=DEL;
				}
				else if (buffer[0][0]=='3'){
					print("-------\r\n");
					print("| End |\r\n");
					print("-------\r\n");
					disable_UART();
				}
				break;
			case ADD_TITLE:
				if(buffer[0][0]=='\0' || param_index<1){
					print("1 - Add password\n\r");
					print("2 - Delete\n\r");
					print("3 - Exit\n\r");
					STATE_UART=MAIN;
				}
				else if (param_index==1){
					add_title_pw(buffer[0], buffer[1]);
					print ("New password added !\n\r");
					get_password();
					STATE_UART=MAIN;
				}
				else{
					print("1 - Add password\n\r");
					print("2 - Delete\n\r");
					print("3 - Exit\n\r");
					STATE_UART=MAIN;
				}
				break;
			case DEL:
				if(buffer[0][0]=='\0'){
					print("1 - Add password\n\r");
					print("2 - Delete\n\r");
					print("3 - Exit\n\r");
					STATE_UART=MAIN;
				}
				else if (param_index==0){
					int8_t rep;
					if (buffer_index >1){
						rep = buffer[0][1]-'0'+10;
					}
					else {
						rep = buffer[0][0]-'0';
					}
					delete(rep);
					print("Password delete !\r\n");
					STATE_UART=MAIN;
				}
				else {
					print("1 - Add password\n\r");
					print("2 - Delete\n\r");
					print("3 - Exit\n\r");
					STATE_UART=MAIN;
				}
				break;
			default:
				print("Erreur");
				break;
		}

		//print_buffer();
		for (int8_t param_reset=0; param_reset<8; param_reset++){
			for(int8_t compteur_reset=0;compteur_reset<64; compteur_reset++){buffer[param_reset][compteur_reset]='\0';}
		}
		buffer_index=0;
		param_index=0;
		sendchar('\r');
		sendchar('\n');
		info_to_treat=0;
	}
}

// Interrupt on Timer1
ISR(TIMER1_OVF_vect){
	main_display(adc_value);
}

// End conversion of ACD
ISR(ADC_vect){
	adc_value=ADC;
}

// Interrupt on button
ISR(PCINT2_vect){
	PCICR&=~(1<<PCIF2);	// Disable interrupt
	volatile int16_t time=(TCNT1H<<8)|TCNT1L;
	if (time!=old_time){
		if (button[15]!=-1){
			for (int8_t i; i<16; i++){button[i]=(-1);}
		}
		else {
			for (int8_t i=16; i>0; i--){
				button[i]=button[i-1];
			}
			//alternance();
			if (!(PIND & (1u<<0))){
				button[0]=0;
			}
			else if (!(PIND & (1u<<1))){
				button[0]=1;
			}
			else if (!(PIND & (1u<<2))){
				button[0]=2;
			}
			else if (!(PIND & (1u<<3))){
				button[0]=3;
			}
		}
	}
	old_time=time;
	PCICR|=(1<<PCIF2);
}
