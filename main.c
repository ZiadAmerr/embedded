#include "tm4c123gh6pm.h"
#include "BT.h"
#include <stdint.h>
#include <stdlib.h>

int main(void)
{
	  
	HC05_init(); // call HC05_init() to initialze UART5 of TM4C123GH6PM
	
	/* Set PF1, PF2 and PF3 as digital output pins */

	SYSCTL_RCGCGPIO_R |= 0x20;	/* enable clock to GPIOF */
	GPIO_PORTF_DIR_R |= 0x0E;	// set PF1, PF2 and PF3 as digital output pin
	GPIO_PORTF_DEN_R |= 0x0E;	// CON PF1, PF2 and PF3 as digital GPIO pins

	Delay(1000);
	
	while(1) {
		char c = Bluetooth_Read();

		char* LED_ctrl_ret = LED_Control(c);

		Bluetooth_Write_String(LED_ctrl_ret);
	}
}

const char *Set_LED(char color, uint8_t state)
{
	uint8_t bit_idx;
	const char *ret;

	switch (color)
	{
	case 'R':
		bit_idx = 1;
		ret = (state) ? "RED LED ON\n" : "RED LED OFF\n";
		break;

	case 'B':
		bit_idx = 2;
		ret = (state) ? "BLUE LED ON\n" : "BLUE LED OFF\n";
		break;

	case 'G':
		bit_idx = 3;
		ret = (state) ? "GREEN LED ON\n" : "GREEN LED OFF\n";
		break;

	default:
		return "Invalid color\n";
	}

	if (state)
		GPIO_PORTF_DATA_R |= (1 << bit_idx);
	else
		GPIO_PORTF_DATA_R &= ~(1 << bit_idx);

	return ret;
}

const char *LED_Control(char c)
{
	switch (c)
	{
	case 'R':
	case 'B':
	case 'G':
		return Set_LED(c, 1);

	case 'r':
	case 'b':
	case 'g':
		return Set_LED(c, 0);

	default:
		return "Invalid input\n";
	}
}