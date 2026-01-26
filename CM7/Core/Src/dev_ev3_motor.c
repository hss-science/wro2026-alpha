/*
 * dev_ev3_motor.c
 *
 *  Created on: Jan 22, 2026
 *      Author: hayat
 */

#include <math.h>

#include "dev_ev3_motor.h"

typedef struct{
	GPIO_TypeDef *GPIOx;
	uint16_t GPIO_Pin;
} gpio_pair_t;

const gpio_pair_t IN1[] = {
		{GPIOA,GPIO_PIN_13},
		{GPIOB,GPIO_PIN_5},
		{GPIOC,GPIO_PIN_10},
		{GPIOC,GPIO_PIN_14},
		{GPIOD,GPIO_PIN_2},
		{GPIOD,GPIO_PIN_9},
};
const gpio_pair_t IN2[] = {
		{GPIOA,GPIO_PIN_14},
		{GPIOB,GPIO_PIN_7},
		{GPIOC,GPIO_PIN_11},
		{GPIOC,GPIO_PIN_15},
		{GPIOD,GPIO_PIN_3},
		{GPIOD,GPIO_PIN_10},
};
const gpio_pair_t EN[] = {
		{GPIOB,GPIO_PIN_0},
		{GPIOB,GPIO_PIN_12},
		{GPIOC,GPIO_PIN_12},
		{GPIOC,GPIO_PIN_12},
		{GPIOD,GPIO_PIN_4},
		{GPIOD,GPIO_PIN_11},
};
const gpio_pair_t SLEW = {GPIOB,GPIO_PIN_13};
const gpio_pair_t SF[] = {
		{GPIOB,GPIO_PIN_2},
		{GPIOC,GPIO_PIN_5},
		{GPIOC,GPIO_PIN_13},
		{GPIOD,GPIO_PIN_1},
		{GPIOD,GPIO_PIN_5},
		{GPIOD,GPIO_PIN_6},
};

typedef enum{
	MOTOR_FORWARD,
	MOTOR_BACKWARD,
	MOTOR_BRAKE,
	MOTOR_OFF,
} IN_T;

static void gpio_pair_write(gpio_pair_t pair, GPIO_PinState state){
	HAL_GPIO_WritePin(pair.GPIOx, pair.GPIO_Pin, state);
}
static IN_T motor_IN_state[] = {MOTOR_OFF,MOTOR_OFF,MOTOR_OFF,MOTOR_OFF,MOTOR_OFF,MOTOR_OFF};
static HAL_StatusTypeDef set_sign(dev_motor_t port, IN_T in){
	motor_IN_state[port] = in;
	switch(in){
	case MOTOR_FORWARD:
		gpio_pair_write(IN1[port], GPIO_PIN_SET);
		gpio_pair_write(IN2[port], GPIO_PIN_RESET);
		break;
	case MOTOR_BACKWARD:
		gpio_pair_write(IN1[port], GPIO_PIN_RESET);
		gpio_pair_write(IN2[port], GPIO_PIN_SET);
		break;
	case MOTOR_BRAKE:
		gpio_pair_write(IN1[port], GPIO_PIN_SET);
		gpio_pair_write(IN2[port], GPIO_PIN_SET);
		break;
	case MOTOR_OFF:
		gpio_pair_write(IN1[port], GPIO_PIN_RESET);
		gpio_pair_write(IN2[port], GPIO_PIN_RESET);
		break;
	default:
		return HAL_ERROR;
	}
	return HAL_OK;
}
static int motor_sleep[] = {1,1,1,1,1,1};
static HAL_StatusTypeDef set_abs_power(dev_motor_t port, double power){
	if(motor_sleep[port]){
		motor_sleep[port] = 0;
		gpio_pair_write(EN[port], GPIO_PIN_SET);
	}
	if(power > 100.0) power = 100.0;
	if(power < 0.0){
		return HAL_ERROR;
	}
	power /= 100.0;
	switch(port){
	case DEV_MOTOR_1:
	{
		uint32_t period = hhrtim.Instance->sTimerxRegs[HRTIM_TIMERINDEX_TIMER_C].PERxR;
		hhrtim.Instance->sTimerxRegs[HRTIM_TIMERINDEX_TIMER_C].CMP1xR = (uint32_t)(power*period+0.5);
		hhrtim.Instance->sCommonRegs.CR2 |= HRTIM_CR2_TCSWU;
		break;
	}
	case DEV_MOTOR_2:
		break;
	case DEV_MOTOR_3:
		break;
	case DEV_MOTOR_4:
		break;
	case DEV_MOTOR_5:
		break;
	case DEV_MOTOR_6:
		break;
	default:
		return HAL_ERROR;
	}
	return HAL_OK;
}

void dev_motor_set_power(dev_motor_t port, double power){
	if(power == 0.0){
		set_abs_power(port, 0);
		set_sign(port, MOTOR_OFF);
	}else if(power > 0.0){
		if(motor_IN_state[port] == MOTOR_FORWARD){
			set_abs_power(port, power);
		}else{
			if(motor_IN_state[port] != MOTOR_OFF){
				set_sign(port, MOTOR_OFF);
			}
			set_abs_power(port, power);
			set_sign(port, MOTOR_FORWARD);
		}
	}else{
		if(motor_IN_state[port] == MOTOR_BACKWARD){
			set_abs_power(port, -power);
		}else{
			if(motor_IN_state[port] != MOTOR_OFF){
				set_sign(port, MOTOR_OFF);
			}
			set_abs_power(port, -power);
			set_sign(port, MOTOR_BACKWARD);
		}
	}
}
void dev_motor_stop(dev_motor_t port, double power){
	set_sign(port, MOTOR_BRAKE);
	set_abs_power(port, 0);
}
int32_t dev_motor_get_counts(dev_motor_t port, double power){
	return 0;
}
