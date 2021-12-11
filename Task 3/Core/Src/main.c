#include "GPIO.h"
#include "stm32f401xc.h"
#include "stm32f401cc_interface.h"
#include "stdio.h"
void delay_ms(int ms);


int main(void) {


    //Set pin 3 in port B to be in input mode with PULL_UP state
    GPIO_Init('B', 3 , INPUT, PULL_UP);
    //Set pins 5,6,7 in port B to be in output mode with PUSH_PULL state
    GPIO_Init('B', 5 , OUTPUT, PUSH_PULL);
    GPIO_Init('B', 6 , OUTPUT, PUSH_PULL);
    GPIO_Init('B', 7 , OUTPUT, PUSH_PULL);


	int counter=1;
	unsigned int previous_state, current_state;
	while (1) {

		previous_state = GPIO_ReadPin('B', 3);
		delay_ms(80); //delay to capture change in button's state
		current_state = GPIO_ReadPin('B', 3);
		delay_ms(10); //delay for button debouncing

		// if previous_state was 1 then current_state is 0 then falling edge detected
		if(previous_state == 1 && current_state == 0){

			counter= counter%8; //make sure we are in the color range [0, 7]

			//set the led to the next color
			GPIO_WritePin('B', 5 , counter & 0x01);
			GPIO_WritePin('B', 6 , counter & 0x02);
			GPIO_WritePin('B', 7 , counter & 0x04);

			//increment counter to show the next color
			counter++ ;
		}

  }
  return 0;
}


void delay_ms(int ms)
{
	  for (int i = 0; i < (ms*1000); i++)
	  {
	  }
}

