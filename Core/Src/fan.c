#include "fan.h"
#include "main.h"
#include "tim.h"
#include "run.h"
#include "delay.h"



void AI_On(void)
{
    FAN_CCW_RUN();
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);//ultrasnoic ON 
	PLASMA_SetHigh();
	PTC_SetHigh();

}


void FAN_CCW_RUN(void)
{
   FAN_CW_SetLow();
   FAN_CCW_SetHigh();
  
}

void FAN_Stop(void)
{
    FAN_CCW_SetLow(); //brake
    FAN_CW_SetLow(); //brake
}



void Buzzer_On(void)
{
  unsigned int m=200;//80
	while(m--){
		BUZZER_TOGGLE() ; 
        delay_us(400);
       }
  
 }

void ShutDown_AllFunction(void)
{
	
	PLASMA_SetLow(); //
	HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);//ultrasnoic ON 
	PTC_SetLow();
	FAN_Stop();



}

void Rat_Control_Function(uint8_t sel)
{
    if(sel==0){//open 
		 FAN_CCW_RUN();
		// PLASMA_SetHigh();
		 HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);//ultrasnoic ON 

	}
	else{ //close

		HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);//ultrasnoic off
		
	}

}

void UV_Function(uint8_t sel)
{

	if(sel==0){//open 
			 FAN_CCW_RUN();
			 PLASMA_SetHigh();
			
	
		}
		else{ //close
	
				
			PLASMA_SetLow();
			
	
		}



}

void Dry_Function(uint8_t sel)
{
   if(sel ==1){  //turn on 
        FAN_CCW_RUN();
		PTC_SetHigh();

   }
   else{ //turn off

       PTC_SetLow();

   }

}

