/*
 * stepper.c
 *
 *  Created on: Dec 8, 2022
 *      Author: artem
 */


#include "stepper.h"




void stepper_moveForward(Stepper *stepper)
{
	stepper->currentCommand = MoveForward;
	stepper->state = Run_Forward;
}

void stepper_moveBack(Stepper *stepper)
{
	stepper->currentCommand = MoveBack;
	stepper->state = Run_Backward;
}


void stepper_stop(Stepper *stepper)
{
	stepper->currentCommand = Stop;
	stepper->state = Wait;
	stepper->targetPosition = 0;
}


void stepper_init(Stepper *stepper,
		GPIO_TypeDef* enable_port, uint16_t enable_pin,
		GPIO_TypeDef* direction_port, uint16_t direction_pin,
		GPIO_TypeDef* step_port, uint16_t step_pin,
		GPIO_TypeDef* reset_port, uint16_t reset_pin )
{
	stepper->enable_port = enable_port;
	stepper->enable_pin = enable_pin;
	stepper->direction_port = direction_port;
	stepper->direction_pin = direction_pin;
	stepper->step_port = step_port;
	stepper->step_pin = step_pin;


	stepper->state = Wait;
	stepper->curPosition = 0;
	//stepper->stepDelay = 40;

	stepper->forward.block = 0;
	stepper->backward.block = 0;

}

void buttons_init(Stepper *stepper,
		GPIO_TypeDef* btn_fw_port, uint16_t btn_fw_pin,
		GPIO_TypeDef* btn_bw_port, uint16_t btn_bw_pin   )
{
	stepper->forward.btn_port = btn_fw_port;
	stepper->forward.btn_pin = btn_fw_pin;
	stepper->backward.btn_port = btn_bw_port;
	stepper->backward.btn_pin = btn_bw_pin;
	stepper->timerPeriod = 29999;
}

void enders_init(Stepper *stepper,
		GPIO_TypeDef* end_fw_port, uint16_t end_fw_pin,
		GPIO_TypeDef* end_bw_port, uint16_t end_bw_pin  )
{
	stepper->forward.end_port = end_fw_port;
	stepper->forward.end_pin = end_fw_pin;
	stepper->backward.end_port = end_bw_port;
	stepper->backward.end_pin = end_bw_pin;


	stepper->forward.end_oldstate = 1;
	stepper->forward.block = 0;

	stepper->backward.end_oldstate = 1;
	stepper->backward.block = 0;

	stepper->curPosition = 0;

}

uint8_t check_button(Direction *dir)
{
	uint8_t result = 0;
	if (HAL_GPIO_ReadPin(dir->btn_port, dir->btn_pin) != dir->btn_oldstate)
	{
		if((HAL_GPIO_ReadPin(dir->btn_port, dir->btn_pin)) == GPIO_PIN_SET)
		{
			// нажатие кнопки
 		   result = 1;
		}
		else
		{
			// отпускание кнопки
			result = 2;
		}

		dir->btn_oldstate = HAL_GPIO_ReadPin(dir->btn_port, dir->btn_pin);
	}
	return result;

}

uint8_t check_ender(Direction *dir)
{
	uint8_t result = 0;
	if (HAL_GPIO_ReadPin(dir->end_port, dir->end_pin) != dir->end_oldstate)
	{
		if ((HAL_GPIO_ReadPin(dir->end_port, dir->end_pin) == GPIO_PIN_RESET))
		{
			// пришло нажатие на концевик
			dir->block = 1;
			result = 1;
		}
		else
		{
			// отпускание концевика
			dir->block = 0;
			result = 2;
		}
		dir->end_oldstate = HAL_GPIO_ReadPin(dir->end_port, dir->end_pin);
	}
	return result;
}

void new_command(Stepper *stepper, Command cmd)
{
	switch (cmd)
	{
		case Stop:
			stepper_stop(stepper);
			break;
		case MoveForward:
			stepper_moveForward(stepper);
			break;
		case MoveBack:
			stepper_moveBack(stepper);
			break;
	}

}


void mstep_init(Stepper *stepper,
		GPIO_TypeDef* ms1_port, uint16_t ms1_pin,
		GPIO_TypeDef* ms2_port, uint16_t ms2_pin,
		GPIO_TypeDef* ms3_port, uint16_t ms3_pin)
{
	stepper->ms1_port = ms1_port;
	stepper->ms1_pin = ms1_pin;
	stepper->ms2_port = ms2_port;
	stepper->ms2_pin = ms2_pin;
	stepper->ms3_port = ms2_port;
	stepper->ms3_pin = ms2_pin;
}



void stepper_boost(Stepper *stepper, TIM_HandleTypeDef *timer) //ускорение двигателя
{
	stepper->countTimer++;
	if (stepper->countTimer>30)
	{
		if (stepper->timerPeriod > 9999) // 3999) //7999
		{
			stepper->timerPeriod -= 500; // 700
			__HAL_TIM_SET_AUTORELOAD(timer, stepper->timerPeriod); // меняем период таймера для регулировки скорости вращения двигателя
		}

		stepper->countTimer = 0;

	}
}


void stepper_step(Stepper *stepper, TIM_HandleTypeDef *htim)
{
	if (stepper->state != Wait)
	{
		HAL_GPIO_TogglePin(stepper->step_port, stepper->step_pin);
		stepper_boost(stepper, htim);
	}
	else
	{
		stepper_stop_boosting(stepper, htim);
	}
}

void stepper_stop_boosting(Stepper *stepper, TIM_HandleTypeDef *timer)
{
	stepper->timerPeriod = 19999; //19999; //29999
	__HAL_TIM_SET_AUTORELOAD(timer, stepper->timerPeriod);

}


void stepper_tick(Stepper *stepper)
{
	switch(stepper->currentCommand)
	{
		case(Wait):
			HAL_GPIO_WritePin(stepper->enable_port, stepper->enable_pin, GPIO_PIN_SET);
			break;
		case(MoveForward):
			HAL_GPIO_WritePin(stepper->direction_port, stepper->direction_pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(stepper->enable_port, stepper->enable_pin, GPIO_PIN_RESET);
			break;
		case(MoveBack):
			HAL_GPIO_WritePin(stepper->direction_port, stepper->direction_pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(stepper->enable_port, stepper->enable_pin, GPIO_PIN_RESET);
			break;
	}
}
