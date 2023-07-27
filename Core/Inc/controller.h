/*
 * controller.h
 *
 *  Created on: Mar 10, 2023
 *      Author: artem
 */

#ifndef INC_CONTROLLER_H_
#define INC_CONTROLLER_H_


#include "main.h"
#include "stepper.h"

void steppers_init();
void check_buttons(Stepper *stepper);
void controller();

#endif /* INC_CONTROLLER_H_ */
