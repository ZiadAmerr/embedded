#include "tm4c123gh6pm.h"
#include <stdint.h>

#ifndef BT_H
#define BT_H

void HC05_init(void);
char BT_Read(void);
void BT_Write(unsigned char data);
void BT_WriteStr(char *str);
void delayMs(int n);

#endif