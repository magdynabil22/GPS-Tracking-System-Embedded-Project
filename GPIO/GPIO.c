#include "TM4C123.h"
#include "GPIO.h"
#include "TM4C123GH6PM.h"
	//For Testing
//void SystemInit(){};
/*	 int main(){
	int SW1 = 0; 
  int SW2 = 0;
	
	initPortF();
	
    while (1) {
        // Check switchs ON or OFF
        SW1 = (GPIO_PORTF_DATA_R & 0x10) == 0;
        SW2 = (GPIO_PORTF_DATA_R & 0x01) == 0;
			
        if (SW1 && SW2) {  // Both switches ON, Red LED ON
            turn_led(RED);
					
        } else if (SW1 && !SW2) { // Switch 1 pressed, turn on Blue 
          turn_led(YELLOW);
					
        } else if (SW2 && !SW1) { // Switch 2 pressed, turn on Green 
					turn_led(GREEN);
					
        } else { 													// No switches pressed, turn off all LEDs
            GPIO_PORTF_DATA_R &= ~0x0E;
        }
    }
    return 0;
}*/
// initialization of port F
void initPortF(){
	SET_BIT(SYSCTL_RCGCGPIO_R,5); 								// 	Activate clock for Porf F
	while((SYSCTL_PRGPIO_R& (0x01 << 5)) == 0){} 	// Delay
  GPIO_PORTF_LOCK_R = 0x4C4F434B;   						// 	Unlock Port F
  GPIO_PORTF_CR_R = 0x1F;           						// 	Allow changes to Port F
  GPIO_PORTF_AMSEL_R = 0x00;        						// 	Disable analog function
  GPIO_PORTF_PCTL_R = 0x00000000;   						// 	GPIO clear bit PCTL
  GPIO_PORTF_DIR_R = 0x0E;          						//  PF4,PF0 in, PF3-1 out
  GPIO_PORTF_AFSEL_R = 0x00;        						// 	No alternate function
  GPIO_PORTF_PUR_R = 0x11;          						//  enable pull-up on PF0 and PF4
  GPIO_PORTF_DEN_R = 0x1F;         						 	//  enable digital I/O on PF4-0
}			
void initPortD(){ 
	SET_BIT(SYSCTL_RCGCGPIO_R,3);         				// activate clock for Port D
  while ((SYSCTL_PRGPIO_R & (0x01 << 3)) == 0);	//  Delay
  GPIO_PORTD_CR_R = 0xF;                 				// allow changes to PD3-0
  GPIO_PORTD_AMSEL_R = 0x00;              			//  disable analog on PD
  GPIO_PORTD_PCTL_R = 0x00000000;         			//  PCTL GPIO on PD7-0 disabled i won't use Aleternate function
  GPIO_PORTD_DIR_R = 0x0F;                			//  PD3-0 as output
  GPIO_PORTD_AFSEL_R = 0x00;             				 //  disable alt funct on PD7-0
  GPIO_PORTD_DEN_R = 0x0F;												//  enable digital I/O on PD3-0
}	



void turn_led(int color){ 			//color = RED or YELLOW or GREEN, thier values are in the header file
	GPIO_PORTF_DATA_R &= ~0x0E; // Clear all Leds
	GPIO_PORTF_DATA_R |= color; // Set color
}
