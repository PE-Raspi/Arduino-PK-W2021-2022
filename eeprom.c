#include "Exercices.h"

/*
 *	EEPROM structur :
 *	user_title 0xAA 0xFE 0xB8 password 0xB6 0xA2 0xD0 user_title
 *
 *
 */

char password[20][2][16];
uint8_t NB_MENU;
uint16_t TRANCHE;

void get_password(){
	for (int8_t i=0;i<20;i++){
		for (int8_t j=0; j<2;j++){
			for (int8_t k=0;k<16;k++){password[i][j][k]='\0';}
		}
	}
	//char test[16]={0};
	//print("eeprom_user_title(0) : ");
	//eeprom_user_title(0, test);
	//print(test);

	for (uint8_t i=0; i<20; i++){
		while (!eeprom_is_ready());
		eeprom_user_title(i, password[i][0]);
		eeprom_password(i, password[i][1]);
		//print(password[i][0]);
	}
	uint8_t size=0;
	for (uint8_t i=0; i<20; i++){
		if (password[i][0][0]!=0){
			size+=1;
		}
	}
	NB_MENU=size+1;
	TRANCHE=1024/NB_MENU;
}

void write_word (char* chaine){
	int8_t size_chaine= strlen(chaine);
	uint8_t* addr=research_blank_pack();
	for (int8_t i=0; i<size_chaine; i++){
		while (!eeprom_is_ready());
		uint8_t* addr_write=addr+i;
		eeprom_write_byte(addr_write, chaine[i]);
		/*
		char str[20];
		sprintf(str, "%04x - %4x\r\n",chaine[i], addr_write);
		print(str);
		*/
	}
}

void add_title_pw(char* title, char* pw){
	int8_t size_title=strlen(title);
	int8_t size_pw=strlen(pw);
	int8_t size_chaine =size_title+size_pw+6;
	char str[45]={0};
	char code_pw[]={'\xaa', '\xfe', '\xb8', '\0'};
	char code_title[]={'\xB6', '\xA2', '\xD0', '\0'};
	strcpy(str, title);
	strcat(str, code_pw);
	strcat(str, pw);
	strcat(str, code_title);
	/*
	print("---\r\n");
	for (int8_t i=0; i<size_chaine; i++){
		sprintf(_str, "%04x\n\r",str[i]);
		print(_str);
	}*/
	write_word(str);
}

void clear_eeprom(){
	for (int8_t* i=0; i<(int8_t *)0xFF; i++){
		while (!eeprom_is_ready());
		eeprom_write_byte(i, 0x00);
	}
}

uint8_t* research_separator_pack(uint8_t* i){
	if (eeprom_read_byte(0)==0x00){
		return 0;
	}
	for (i; i<(uint8_t *)0xFF; i++){
		while (!eeprom_is_ready());
		if (eeprom_read_byte(i)==0xB6){
			if (eeprom_read_byte(i+1)==0xA2 && eeprom_read_byte(i+2)==0xD0){
				return (i+3);
			}
		}
	}
	return (uint8_t *)255;
}

uint8_t* research_separator_password(uint8_t* i){
	if (eeprom_read_byte(0)==0x00){
		return 0;
	}
	for (i; i<(uint8_t *)0xFF; i++){
		while (!eeprom_is_ready());
		if (eeprom_read_byte(i)==0xAA){
			if (eeprom_read_byte(i+1)==0xFE && eeprom_read_byte(i+2)==0xB8){
				return (i+3);
			}
		}
	}
	return (uint8_t *)255;

}

uint8_t* research_blank_pack(){
	uint8_t *pack=0;
	pack=research_separator_pack(pack);
	while (eeprom_read_byte(pack)!=0x00){
		while (!eeprom_is_ready());
		pack=research_separator_pack(pack);
	}
	return pack;
}

void eeprom_user_title(int8_t number, char* title){
	uint8_t *pack=0x00;
	int8_t i=0;
	for (i; i<number; i++){
		pack = research_separator_pack(pack);
	}
	uint8_t* end_pack = research_separator_password(pack)-4;

	if (end_pack!=(uint8_t *)251){
		for (int8_t i=0; i<=(end_pack-pack); i++){
			title[i]=eeprom_read_byte(pack+i);
		}
	}
}

void eeprom_password(int8_t number, char* pw){
	uint8_t* password=0x00;
	int8_t i=0;
	for (i; i<=number; i++){
		password = research_separator_password(password);
	}
	uint8_t* end_password = research_separator_pack(password)-4;
	
	if (end_password!=(uint8_t *)251){
		for (int8_t i=0; i<=(end_password-password); i++){
			pw[i]=eeprom_read_byte(password+i);
		}
	}
}

void delete(int8_t number){
	uint8_t *pack=0x00;
	int8_t i=0;
	for (i; i<number; i++){
		pack = research_separator_pack(pack);
	}
	uint8_t* end_pack = research_separator_pack(pack);
	//print_int("pack    ", (uint8_t)pack);
	//print_int("end_pack", (uint8_t)end_pack);
	for (uint8_t* addr=pack; addr<=end_pack; addr++){
		eeprom_write_byte(addr, 0x00);
	}
	get_password();
}
