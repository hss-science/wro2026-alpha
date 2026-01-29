#include "app_main.h"

#include "hrtim.h"
#include "pcf8574.h"
#include "dev_ev3_motor.h"
#include "stm32h7xx_hal.h"

void App_Init(void)
{
    HAL_HRTIM_WaveformOutputStart(&hhrtim, HRTIM_OUTPUT_TC2);
    HAL_HRTIM_WaveformCounterStart(&hhrtim, HRTIM_TIMERID_MASTER | HRTIM_TIMERID_TIMER_C);
}

void App_Loop(void)
{
    static int count = 0;

    PCF8574_Write(0x1);
    count++;
    if(count%2){
    	dev_motor_set_power(DEV_MOTOR_1, 100);
    }else{
    	dev_motor_set_power(DEV_MOTOR_1, 60.0);
    }
    HAL_Delay(1000);
}
