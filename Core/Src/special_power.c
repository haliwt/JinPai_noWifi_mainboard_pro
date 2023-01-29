#include "special_power.h"
#include "dht11.h"
#include "fan.h"
#include "tim.h"
#include "cmd_link.h"
#include "run.h"




void SetPowerOn_ForDoing(void)
{
    Buzzer_On();
    run_t.gFan_counter=0;
    run_t.gPower_flag = 1; //turn on power
    run_t.gFan_continueRun =0;
    run_t.gPower_On=1;
    run_t.SingleMode = 1;
	run_t.gAi=0;
	run_t.gFan=0;
	run_t.gPlasma=0;
	run_t.gDry=0;
	
	run_t.gmt_time_flag=0;

	
    FAN_CCW_RUN();
    PLASMA_SetHigh(); //
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);//ultrasnoic ON 
    PTC_SetHigh();
	Initial_Ref();
    
    

}

void SetPowerOff_ForDoing(void)
{
    Buzzer_On();
	run_t.gPower_flag = 0;
	run_t.gFan_counter=0;
	run_t.gFan_continueRun =1; //the fan still run 60s
	run_t.gPower_On=0;
   
  
    run_t.SingleMode = 0;

	run_t.gAi=1;
	run_t.gFan=1;
	run_t.gPlasma=1;
	run_t.gDry=1;

   
    
	PLASMA_SetLow(); //
	HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);//ultrasnoic ON 
	PTC_SetLow();
	FAN_Stop();

}



