/*
 * main.h
 *
 *  Created on: Dec 29, 2021
 *      Author: Mohamed Galloul
 */

#ifndef INC_MAIN_H_
#define INC_MAIN_H_

void delay_ms(int ms);
void KeypadCallouts_KeyPressNotificaton(void);
void EXTI0_IRQHandler(void);
void EXTI1_IRQHandler(void);
void Display_number(unsigned int key);
#endif /* INC_MAIN_H_ */
