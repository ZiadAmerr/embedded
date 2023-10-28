#include <stdint.h>

#include "DIO.h"
#include "regs.h"
#include "bitwise_operations.h"

void DIO_Init() {
    // Enable the clock for PortF
    SYSCTL_RCGCGPIO_R |= 0x00000020;

    // Wait until PortF is enabled
    while ((SYSCTL_PRGPIO_R & 0x00000020) == 0);

    // Unlock GPIO Port F (if required for certain configurations)
    GPIO_PORTF_LOCK_R = 0x4C4F434B;

    // Allow changes for selected pins (if required for certain configurations)
    GPIO_PORTF_CR_R = 0x1F;

    // Set pins as output (LEDs on pins 1, 2, and 3)
    GPIO_PORTF_DIR_R = 0x0E;

    // Set pins as input (buttons on pins 0 and 4)
    GPIO_PORTF_PUR_R = 0x11;

    // Enable digital functionality (LEDs and buttons)
    GPIO_PORTF_DEN_R = 0x1F;
}

void GPIO_writePin(uint8_t pin_num, uint8_t value) {
    if (value == 1) {
        Set_Bit(GPIO_PORTF_DATA_R, pin_num);
    } else {
        Clear_Bit(GPIO_PORTF_DATA_R, pin_num);
    }
}


void DIO_WritePort(uint32_t data, uint32_t mask) {
    GPIO_PORTF_DATA_R = (GPIO_PORTF_DATA_R & ~mask) | (data & mask);
}


int main() {
    DIO_Init();

    // Enable first LED in PORTF
    GPIO_writePin(1, 1);

    // Enable second LED in PORTF
    GPIO_writePin(2, 1);

    // Enable third LED in PORTF
    GPIO_writePin(3, 1);
}