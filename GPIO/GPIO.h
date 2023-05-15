#ifndef GPIO_H
#define GPIO_H
#include "bit_utilies.h" //Bit-functions
#include "TM4C123.h"
#define RED 0x02
#define GREEN 0x08
#define YELLOW 0x0A

void initPortF();
void initPortD();
void initPortE();
void turn_led(int color); //Color = RED or YELLOW or GREEN
#endif
