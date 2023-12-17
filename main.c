#include "tm4c123gh6pm.h"
#include "BT.h"
#include <stdint.h>
#include <stdlib.h>

char *Set_LED(char color, uint8_t state);
char *LED_Control(char c);

int main(void)
{
	uint8_t read_flag = 0;
	// Init UART5 module for HC-05
	HC05_init();
	
	// Config PINs

	// CLK
	SYSCTL_RCGCGPIO_R |= 0x20;

	// Set Port F PINs 1, 2 and 3 as digital GPIO pins
	GPIO_PORTF_DIR_R |= 0x0E;

	// Enable digital function for PF1, PF2 and PF3
	GPIO_PORTF_DEN_R |= 0x0E;

	// Delay to make sure clock is stable
	delayMs(1);
        
    Bluetooth_Write_String("Hi, welcome to the bluetooth terminal application!\n");
	
	while(1) {
		char c = Bluetooth_Read();
		if (read_flag == 0) {
			char *LED_ctrl_ret = LED_Control(c);

			Bluetooth_Write_String(LED_ctrl_ret);

			read_flag = 1;

		} else if (read_flag == 1) {
			read_flag = 0;
		};
	}
}

char *Set_LED(char color, uint8_t state)
{
	uint8_t bit_idx;
	char *ret;

	switch (color)
	{
	case 'R':
    case 'r':
		bit_idx = 1;
		ret = (state) ? "RED LED ON\n" : "RED LED OFF\n";
		break;

	case 'B':
    case 'b':
		bit_idx = 2;
		ret = (state) ? "BLUE LED ON\n" : "BLUE LED OFF\n";
		break;

	case 'G':
    case 'g':
		bit_idx = 3;
		ret = (state) ? "GREEN LED ON\n" : "GREEN LED OFF\n";
		break;
	}

	if (state)
		GPIO_PORTF_DATA_R |= (1 << bit_idx);
	else
		GPIO_PORTF_DATA_R &= ~(1 << bit_idx);

	return ret;
}

char *LED_Control(char c)
{
	switch (c)
	{
	case 'R':
	case 'B':
	case 'G':
		return Set_LED(c, 1);
                break;

	case 'r':
	case 'b':
	case 'g':
		return Set_LED(c, 0);
                break;
	
	default:
		return "Invalid command\n";
	}
}