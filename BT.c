#include "BT.h"
#include "tm4c123gh6pm.h"

// void HC05_init(void);                     // Initialize UART5 module for HC-05
// char Bluetooth_Read(void);                // Read data from Rx5 pin of TM4C123
// void Bluetooth_Write(unsigned char data); // Transmit a character to HC-05 over Tx5 pin
// void Bluetooth_Write_String(char *str);   // Transmit a string to HC-05 over Tx5 pin

void HC05_init(void) {
    SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R5; /* enable clock to UART5 */
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R4; /* enable clock to PORTE for PE4/Rx and RE5/Tx */

    Delay(1000);

    /* UART0 initialization */
    UART5_CTL_R = 0;        /* UART5 module disbable */
    UART5_IBRD_R = 104;     /* for 9600 baud rate, integer = 104 */
    UART5_FBRD_R = 11;       /* for 9600 baud rate, fractional = 11*/
    UART5_CC_R = 0;          /* select system clock */
    UART5_LCRH_R = UART_LCRH_WLEN_8; /* data lenght 8-bit, not parity bit, no FIFO */
    UART5_CTL_R = 0x301;     /* Enable UART5 module, Rx and Tx */

    /* UART5 TX5 and RX5 use PE4 and PE5. Configure them digital and enable alternate function */
    GPIO_PORTE_DEN_R = 0x30; /* set PE4 and PE5 as digital */
    GPIO_PORTE_DEN_R = 0x30; /* Use PE4,PE5 alternate function */
    GPIO_PORTE_AMSEL_R = 0;  /* Turn off analg function*/
    GPIO_PORTE_PCTL_R = 0x00110000; /* configure PE4 and PE5 for UART */
}

char Bluetooth_Read(void)
{
    char data;
    while ((UART5_FR_R & (1 << 4)) != 0)
        ;             /* wait until Rx buffer is not full */
    data = UART5_DR_R; /* before giving it another byte */
    return (unsigned char)data;
}

void Bluetooth_Write(unsigned char data)
{
    while ((UART5_FR_R & (1 << 5)) != 0)
        ;             /* wait until Tx buffer not full */
    UART5_DR_R = data; /* before giving it another byte */
}

void Bluetooth_Write_String(char *str)
{
    while (*str)
    {
        Bluetooth_Write(*(str++));
    }
}

void Delay(unsigned long counter)
{
    unsigned long i = 0;

    for (i = 0; i < counter; i++);
}