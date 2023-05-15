#include "TM4C123GH6pm.h"
#include "UART.h"

//intialization of UART5
void UART5_GPS_init() //should be called only once
{
	SYSCTL_RCGCUART_R |= 0x20;// ACTIVATE UART5
	SYSCTL_RCGCGPIO_R |= 0x10;
	while((SYSCTL_RCGCGPIO_R & 0x10)==0);
	while((SYSCTL_RCGCUART_R & 0x20)==0);
	GPIO_PORTE_CR_R = 0x1F; // allow changes
	///////Baudrate = 9600 
	// to calculate 
	UART5_IBRD_R= 104;
	UART5_FBRD_R= 11;
	UART5_LCRH_R=0x00000070;//8-bit word length, enable FIFO 
	UART5_CTL_R |= 0x301;//enable RXE ,TXE,and UART
	GPIO_PORTE_AFSEL_R |= 0x30;
	GPIO_PORTE_PCTL_R |=(GPIO_PORTE_PCTL_R & 0xFF00FFFF) + 0x00110000;
	GPIO_PORTE_DEN_R |=0x30;
	GPIO_PORTE_AMSEL_R=0x0;
}
char UART5_GPS_read()
{
	while((UART5_FR_R&0x10)!=0);
	return (char) (UART5_DR_R &0xFF);
}
void UART5_GPS_write(char x)
{
	while((UART5_FR_R&0x10)!=0);
	UART5_DR_R = x;
}
void UART5_ReadString(char *str)
{
	int i;
	char c;
	for(i = 0;str && str[i]!= '*';i++)
	{
		str[i]=UART5_GPS_read();	
	}
}
void UART5_WriteString(char *str)
{
	int i=0;
	while(str[i])
	{
		UART5_GPS_write(str[i]);
		i++;
	}
}
void UART1_7seg_init()
{
	SYSCTL_RCGCUART_R |= 0x02;
	SYSCTL_RCGCGPIO_R |= 0x02;
	while((SYSCTL_RCGCGPIO_R & 0x02)==0);
	while((SYSCTL_RCGCUART_R & 0x02)==0);
	UART1_CTL_R &= ~0x00000001;
	//baudrate = 9600 
	UART1_IBRD_R= 104;
	UART1_FBRD_R= ((0.1666667*64)+0.5);
	UART1_LCRH_R=0x00000070;
	UART1_CTL_R |= 0x301;
	GPIO_PORTB_AFSEL_R |= 0x1;
	GPIO_PORTB_PCTL_R |=(GPIO_PORTA_PCTL_R & 0xFFFFFF00) + 0x11;
	GPIO_PORTB_DEN_R |=0x03;
	GPIO_PORTB_AMSEL_R=0x0;
}
char UART1_7seg_read()
{
	while((UART1_FR_R&0x10)!=0);
	return (char) (UART1_DR_R &0xFF);
}
void UART1_7seg_write(char x)
{
	while((UART1_FR_R&0x20)!=0);
	UART1_DR_R = x;
}
void UART1_ReadString(char *str)
{
	int i;
	char c;
	for(i = 0;str && str[i]!= '*';i++)
	{
		str[i]=UART1_7seg_read();
	}
}
void UART1_WriteString(char *str)
{
	int i=0;
	while(str[i])
	{
		UART1_7seg_write(str[i]);
		i++;
	}
}
void initializeTIMER(void)
{

 NVIC_ST_CTRL_R = 0;
 NVIC_ST_RELOAD_R = 0x00FFFFFF;
 NVIC_ST_CURRENT_R = 0;
 NVIC_ST_CTRL_R = 0x00000005;
}
void waitseconds(unsigned int x)
{
int i;
NVIC_ST_RELOAD_R = 16000000-1;
 NVIC_ST_CURRENT_R=0;
for(i=0; i<x;i++)
{
while ((NVIC_ST_CTRL_R & 0x00010000) == 0);
}
}

void UART0_GPS_init()
{
SYSCTL_RCGCUART_R |= 0x01;
SYSCTL_RCGCGPIO_R |= 0x01;
while((SYSCTL_RCGCGPIO_R & 0x01)==0);
while((SYSCTL_RCGCUART_R & 0x01)==0);
initializeTIMER();
waitseconds(1);
UART0_CTL_R &= ~0x00000001;
//baudrate = 9600
UART0_IBRD_R= 104;
UART0_FBRD_R= ((0.1666667*64)+0.5);
UART0_LCRH_R=0x00000070;
UART0_CTL_R |= 0x301;
GPIO_PORTA_AFSEL_R |= 0x03;
GPIO_PORTA_PCTL_R |=(GPIO_PORTA_PCTL_R & 0xFFFFFF00) + 0x11;
GPIO_PORTA_DEN_R |=0x03;
GPIO_PORTA_AMSEL_R=0x0;
}
char UART0_GPS_read()
{
while((UART0_FR_R&0x10)!=0);
return (char) (UART0_DR_R &0xFF);
}
void UART0_GPS_write(char x)
{
while((UART0_FR_R&0x20)!=0);
UART0_DR_R = x;
}
