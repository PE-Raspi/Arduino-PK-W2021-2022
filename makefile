defaut: flash

sources = Exercices.c lib.c uart.c HD44780.c menu.c interrupt.c eeprom.c
objets  = $(sources:.c=.o)
#out 	= $(:=Release/ $(objets))
out 	= $(patsubst %,Release/%,$(objets))

build: $(objets)
	#@echo "coucou"
	#@echo $(objets)
	#@echo $(out)
	#avr-gcc -Os -mmcu=atmega328p $(out) -o Release/out.elf
	avr-gcc -Os -mmcu=atmega328p -o Release/out.elf $(out)
	avr-objcopy -O ihex -R .eeprom Release/out.elf Release/out.hex


%.o : %.c
	avr-gcc -Os -c -mmcu=atmega328p -o Release/$@ -c $< 


Release/out.hex: Release/out.elf
	@echo "Conversion en hex"
	avr-objcopy -O ihex -R .eeprom Release/out.elf Release/out.hex

flash: build
ifdef port
		avrdude -F -V -c arduino -p ATMEGA328P -P $(port) -b 115200 -U flash:w:Release/out.hex
else
		avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -U flash:w:Release/out.hex
endif

uart: flash
	minicom -D /dev/ttyACM0 -b 9600

#avr-gcc -Os -mmcu=atmega328p -o Release/Exercices.elf Exercices.c && avr-objcopy -O ihex -R .eeprom Release/Exercices.elf Release/Exercices.hex
