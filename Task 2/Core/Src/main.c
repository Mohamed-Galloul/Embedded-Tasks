#include "stm32f401cc_interface.h"
#include <stdio.h>

/*
* General rule for masking is (mask << (size * position)) ;
* Clearing: |=
* Setting:  &= ~
* Toggling: ^=
*/

void delay_ms(int ms);

int main(void) {
    //Enable port B
    RCC_AHB1ENR |= (0x01 << (1 * 1));

    //Set pin 3 in port B to be in input mode
    GPIOB_MODER |= (0x00 << (2 * 3));
    //Set pins 5, 6, 7 in port B to be in general output mode
    GPIOB_MODER |= (0x01 << (2 * 5));
    GPIOB_MODER |= (0x01 << (2 * 6));
    GPIOB_MODER |= (0x01 << (2 * 7));

    //set input type for pin 3 in port B to be Pull-up
    GPIOB_PUPDR |= (0x01 << (2 * 3));
    //set output type for pins 5, 6, 7 in port B to be Push-pull
    GPIOB_OTYPER &= ~ (0x01 << (1 * 5));
    GPIOB_OTYPER &= ~ (0x01 << (1 * 6));
    GPIOB_OTYPER &= ~ (0x01 << (1 * 7));



/*
    //setting the falling edge interrupt
    //enable system configuration controller clock
    RCC_APB2ENR |= (0x01 << (1 * 14));
    //configure EXTI3 line for PB3
    SYSCFG_EXTICR1 |= (0x01 << (4 * 3));
    //Disable interrupt mask on EXTI3
    EXTI_IMR |= (0x01 << (1 * 3));
    //Enable falling edge trigger for PB3
    EXTI_FTSR |= (0x01 << (1 * 3));
    //clear the raising edge trigger for PB3
    EXTI_RTSR &= ~(0x01 << (1 * 3));
    //set priority and enable interrupt
    NVIC_SetPriority (EXTI3_IRQn, 1);
    NVIC_EnableIRQ (EXTI3_IRQn);

   */

	int counter=1;
	unsigned int previous_state, current_state;
	while (1) {

		previous_state = GPIOB_IDR & (0x01 << (1 * 3));
		delay_ms(80); //delay to capture change in button's state
		current_state = GPIOB_IDR & (0x01 << (1 * 3));
		delay_ms(10); //delay for button debouncing

		// if previous_state was 1 then current_state is 0 then falling edge detected
		if(previous_state > 1 && current_state == 0){

			GPIOB_ODR &= 0x00; //clearing the output register before setting the led's color

			counter= counter%8; //make sure we are in the color range [0, 7]
			GPIOB_ODR |= (counter << (1 * 5)); //set the led to the next color
			counter++ ;
		}

  }
  return 0;
}


void delay_ms(int ms){

	  for (int i = 0; i < (ms * 1000); i++)
	  {
		{}
	  }
}

