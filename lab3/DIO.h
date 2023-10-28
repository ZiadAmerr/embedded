#include <stdint.h>

#ifndef DIO_H
#define DIO_H

void DIO_Init(void);
void DIO_WritePin(uint8_t pin, uint8_t value);
void DIO_WritePort(uint32_t data, uint32_t mask);

#endif // DIO_H