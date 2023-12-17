#include "BT.h"
#include "tm4c123gh6pm.h"

const unsigned int CLKSPEED = 16000000; // 16 MHz

void delayMs(int n) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < 3180; j++) {
        }
    }
}


void HC05_init(void) {
    // Desired baud rate is 9600
    uint32_t baud_rate = 9600;

    // Calculate baud rate
    float full_baud_rate = (float)CLKSPEED / (16 * baud_rate);

    // Split baud rate into integer and fractional parts
    uint32_t int_baud_rate = (uint16_t)full_baud_rate;
    uint32_t frac_baud_rate_int = (uint8_t)((full_baud_rate - int_baud_rate) * 64 + 0.5);

    // Enable clock to UART5
    SYSCTL_RCGCUART_R |= 0x20;

    // Enable clock to PORTE for PE4/Rx and RE5/Tx
    SYSCTL_RCGCGPIO_R |= 0x10;

    // Delay to ensure clocks are stable
    delayMs(1);

    // UART5 initialization
    UART5_CTL_R &= ~0x00000001; // UART5 module disable

    // config baud rate
    UART5_IBRD_R = int_baud_rate;
    UART5_FBRD_R = frac_baud_rate_int;

    // select sys clock
    UART5_CC_R = 0x0;

    // config data transmission, FIFO, no parity, 1-byte packet
    UART5_LCRH_R = 0x60;

    // enable UART5 module, Rx and Tx
    UART5_CTL_R = 0x301;

    // GPIO configuration
    // PE4 and PE5 digital enable
    GPIO_PORTE_DEN_R = 0x30;

    // Use alternate function
    GPIO_PORTE_AFSEL_R = 0x30;

    // Turn off analog function
    GPIO_PORTE_AMSEL_R = 0;

    // Configure PE4 and PE5 for UART
    GPIO_PORTE_PCTL_R = (GPIO_PORTE_PCTL_R & 0xFF00FFFF) | 0x00110000; // configure PE4 and PE5 for UART
}


char BT_Read(void)
{
    char data;

    // wait until Rx buffer not full
    while ((UART5_FR_R & (1 << 4)) != 0);

    // assign Rx buffer to data
    data = UART5_DR_R;

    // return data
    return (unsigned char)data;
}

void BT_Write(unsigned char data)
{
    // wait until Tx buffer not full
    while ((UART5_FR_R & (1 << 5)) != 0);

    // full, append a byte
    UART5_DR_R = data;
}

void BT_WriteStr(char *str)
{
    // send bytes until end of string
    while (*str) {
        Bluetooth_Write(*(str++));
    }
}