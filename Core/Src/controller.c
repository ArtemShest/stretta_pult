/*
 * controller.c
 *
 *  Created on: Mar 10, 2023
 *      Author: artem
 */
#include "controller.h"

#include "stepper.h"

Stepper stepperX;
Stepper stepperY;

void controller()
{
	check_buttons(&stepperX); 		// проверка на кнопки и концевики первой оси
	check_buttons(&stepperY);		// проверка на кнопки и концевики второй оси
	stepper_tick(&stepperX);		// обработка команд первой оси
	stepper_tick(&stepperY);		// обработка команд второй оси
}


void steppers_init()
{
	// ------------- init stepper X --------------
	stepper_init(&stepperX,
			ENABLE_X_GPIO_Port, ENABLE_X_Pin,
			DIR_X_GPIO_Port, DIR_X_Pin,
			STEP_X_GPIO_Port, STEP_X_Pin,
			RESET_X_GPIO_Port, RESET_X_Pin);
	buttons_init(&stepperX,
			BTN_RIGHT_GPIO_Port, BTN_RIGHT_Pin,
			BTN_LEFT_GPIO_Port, BTN_LEFT_Pin);
	enders_init(&stepperX,
			LS_X1_GPIO_Port, LS_X1_Pin,
			LS_X2_GPIO_Port, LS_X2_Pin);
	mstep_init(&stepperX,
			MS1_X_GPIO_Port, MS1_X_Pin,
			MS2_X_GPIO_Port, MS2_X_Pin,
			MS3_X_GPIO_Port, MS3_X_Pin);

	// ------------- init stepper Y ----------------
	stepper_init(&stepperY,
			ENABLE_Y_GPIO_Port, ENABLE_Y_Pin,
			DIR_Y_GPIO_Port, DIR_Y_Pin,
			STEP_Y_GPIO_Port, STEP_Y_Pin,
			RESET_Y_GPIO_Port, RESET_Y_Pin);
	buttons_init(&stepperY,
			BTN_DOWN_GPIO_Port, BTN_DOWN_Pin,
			BTN_UP_GPIO_Port, BTN_UP_Pin);
	enders_init(&stepperY,
			LS_Y1_GPIO_Port, LS_Y1_Pin,
			LS_Y2_GPIO_Port, LS_Y2_Pin);
	mstep_init(&stepperY,
			MS1_Y_GPIO_Port, MS1_Y_Pin,
			MS2_Y_GPIO_Port, MS2_Y_Pin,
			MS3_Y_GPIO_Port, MS3_Y_Pin);

	HAL_GPIO_WritePin(SLEEP_X_GPIO_Port, SLEEP_X_Pin, GPIO_PIN_SET); //sleep X
	HAL_GPIO_WritePin(SLEEP_Y_GPIO_Port, SLEEP_Y_Pin, GPIO_PIN_SET); //sleep Y


	HAL_GPIO_WritePin(stepperX.reset_port, stepperX.reset_pin, GPIO_PIN_SET); //reset X
	HAL_GPIO_WritePin(stepperY.reset_port, stepperY.reset_pin, GPIO_PIN_SET); //reset Y

	HAL_Delay(1);

	HAL_GPIO_WritePin(stepperX.enable_port, stepperX.enable_pin, GPIO_PIN_SET); //enable X
	HAL_GPIO_WritePin(stepperY.enable_port, stepperY.enable_pin, GPIO_PIN_SET); //enable Y
	HAL_Delay(1);
}



void check_buttons(Stepper *stepper)
{
	switch (check_button(&(stepper->forward))) //проверка нажатия на кнопку движения вперед
	{
		case 1:
			if (stepper->forward.block == 0)
				new_command(stepper, MoveForward);
			break;
		case 2:
			new_command(stepper, Stop);
			break;
	}
	switch (check_button(&(stepper->backward))) //проверка нажатия на кнопку движения назад
	{
		case 1:
			if (stepper->backward.block == 0)
				new_command(stepper, MoveBack);
			break;
		case 2:
			new_command(stepper, Stop);
			break;
	}
	switch (check_ender(&(stepper->forward))) //проверка нажатия на концевик движения вперед
	{
		case 1:
			if(stepper->state == Run_Forward)
			{
				new_command(stepper, Stop);
			}
			break;
		case 2:
			break;
	}
	switch (check_ender(&(stepper->backward))) //проверка нажатия на концевик движения назад
	{
		case 1:
			if(stepper->state == Run_Backward)
			{
				new_command(stepper, Stop);
			}
			break;
		case 2:
			break;
	}
}
