#include "TM4C123.h"
#include <stdint.h>

#ifndef BT_H
#define BT_H

void HC05_init(void);                     // Initialize UART5 module for HC-05
char Bluetooth_Read(void);                // Read data from Rx5 pin of TM4C123
void Bluetooth_Write(unsigned char data); // Transmit a character to HC-05 over Tx5 pin
void Bluetooth_Write_String(char *str);   // Transmit a string to HC-05 over Tx5 pin

#endif