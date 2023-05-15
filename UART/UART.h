#ifndef UART_H
#define UART_H
void UART5_GPS_init();
char UART5_GPS_read();
void UART5_GPS_write(char x);
void UART5_ReadString(char *str);
void UART5_WriteString(char *str);
void UART1_7seg_init();
char UART1_7seg_read();
void UART1_7seg_write(char x);
void UART1_ReadString(char *str);
void UART1_WriteString(char *str);
void UART0_GPS_write(char x);
char UART0_GPS_read();
void UART0_GPS_init();
void initializeTIMER(void);
void waitseconds(unsigned int x);
#endif
