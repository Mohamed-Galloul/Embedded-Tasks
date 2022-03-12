/*
 * Author : Mohamed Galloul
 * Date   : 29/12/2021
 * Version: 1.0.0
 */
#include "GPIO.h"
#include "interrupt.h"
#include "Keypad.h"

void delay_ms(int ms);
void KeypadCallouts_KeyPressNotificaton(void);

void EXTI0_IRQHandler(void);
void EXTI1_IRQHandler(void);
void Display_number(unsigned int key);


static unsigned char sevenSegHex[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66,
										  0x6D, 0x7D, 0x07, 0x7F, 0x6F};


unsigned int counter = 0;


int main(void) {

		// Enable clock for Port A & B
		GPIO_EnableClock(0);
		GPIO_EnableClock(1);

		// Configure each pin in the seven segment connected to port B as OUTPUT in PUSH_PULL state
		for (int i = 0; i < 7; ++ i)
		{
			GPIO_Init(1, i, OUTPUT, PUSH_PULL);
		}


		// Enable clock for SYSCFG --> In order to enabling external interrupts.
		SYSCFG_EnableClock();

		// Iterate over each push button.
		for (int i = 0; i < 2; ++i) {

			// Configure each button as INPUT in PULL_UP state
			GPIO_Init(0, i, INPUT, PULL_UP);

			// Enable EXTI for each button's pin, unmask the EXTI, set the trigger to be at falling edges,
			// and enable the corresponding NVIC line for each EXTI.
			EXTI_Enable(i);
			EXTI_Unmask(i);
			EXTI_Trigger_Selection(FALLING, i);
			NVIC_Enable(6+i);
		}



  while (1) {

	  unsigned char hex_number = sevenSegHex[counter];

	  // Iterate over each pin in PortB connected to seven segment
	  	for (int i = 0; i < 7; i++)
	  	{
	  		if(hex_number & (0x01<<i))
	  		{
	  			GPIO_WritePin(1, i , 1);
	  		}
	  		else
	  		{
	  			GPIO_WritePin(1, i , 0);
	  		}
	  	}

  }

  return 0;
}

void EXTI0_IRQHandler(void)
	{
	// Disable EXTI1 on NVIC line 7
	NVIC_Disable(7);

	// Increment the counter, and make sure it value is under 10
	counter += 1;
	counter %= 10;

	// Clear the corresponding bit in the pending register, to prevent infinite execution for the ISR
	EXTI_Clear(0);
	}

void EXTI1_IRQHandler(void)
	{
	// Disable EXTI0 on NVIC line 6
	NVIC_Disable(6);

	// Increment the counter, and make sure its value is above 0.
	counter -= 1;
	if (counter == -1) counter = 9;

	// Clear the corresponding bit in the pending register, to prevent infinite execution for the ISR
	EXTI_Clear(1);
	}





/*
 * the following function is only for testing
 */


void Display_number(unsigned int key)
{
//Get the corresponding hex representation of the key
unsigned char hex_number = sevenSegHex[key];

//Iterate over each pin in PortB connected to seven segment
	for (int i = 0; i < 7; i++)
	{
		if(hex_number & (0x01<<i))
		{
			GPIO_WritePin(1, i , 1);
		}
		else
		{
			GPIO_WritePin(1, i , 0);
		}
	}

}


void KeypadCallouts_KeyPressNotificaton(void){
	int key = Keypad_GetKey();
	if(key != -1){
		//Get the corresponding hex representation of the key
		unsigned char hex_number = sevenSegHex[key];

		//Iterate over each pin in PortB connected to seven segment
		for (int i = 0; i < 7; i++) {
					if(hex_number & (0x01<<i))
						{
							GPIO_WritePin(1, i , 1);
					}
					else{
							GPIO_WritePin(1, i , 0);
					}
			  }
	}

}


void delay_ms(int ms) {
  unsigned int i;
  for (i = 0; i < ms *1000; i++) {
  }
}


