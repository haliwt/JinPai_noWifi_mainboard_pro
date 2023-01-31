#include "run.h"


#include "dht11.h"
#include "fan.h"
#include "tim.h"
#include "cmd_link.h"
#include "special_power.h"




 


//static CProcess1 cprocess;
RUN_T run_t; 
uint8_t times;
 
uint8_t timeArray[7];




/**********************************************************************
*
*Functin Name: void Initial_Ref(void)
*Function : be check key of value 
*Input Ref:  key of value
*Return Ref: NO
*
**********************************************************************/
void Initial_Ref(void)
{
  
  run_t.gPlasma=0;
  run_t.gDry =0;
  run_t.gAi = 0; //WT.EDIT.2023.01.29

  run_t.gFan_counter=0;
 

}


/**********************************************************************
*
*Function Name:void Decode_RunCmd(void)
*Function: receive usart touchkey of command 
*Input Ref:NO
*Return Ref:NO
*
**********************************************************************/
void Decode_RunCmd(void)
{

 uint8_t cmdType_1=inputCmd[0],cmdType_2 = inputCmd[1];
    
  switch(cmdType_1){
  
      case 'P': //power 
        if(cmdType_2 == 0x00){ //power off
          SetPowerOff_ForDoing();
		  run_t.gPower_On=0;
		  run_t.SingleMode = 0;
		} 
       else if(cmdType_2 ==1){ //power on
          SetPowerOn_ForDoing();
          run_t.gPower_On=1;
          run_t.SingleMode = 1;
	    }       
      
          
      break;
      
      case 'C': //wifi  control function ->wifi ->indicate Fun
        
        if(run_t.gPower_On==1){
			Single_ReceiveCmd(cmdType_2);
        }

      break;

    case 'Z' :
	    if(run_t.gPower_On==1){

		    if(cmdType_2== 'Z'){//turn off AI
			    Buzzer_On();
			}
		}

	    break;
 	}
    
}
/**********************************************************************
	*
	*Functin Name: void Single_ReceiveCmd(uint8_t cmd)
	*Function : resolver is by usart port receive data  from display panle  
	*Input Ref:  usart receive data
	*Return Ref: NO
	*
**********************************************************************/
void Single_ReceiveCmd(uint8_t cmd)
{
  
    if(run_t.gPower_On==1){
	switch(cmd){

    //   case 0x11: //AI turn off 
       
    //         run_t.gAi =1;
    //         Buzzer_On();
	        
    //         cmd = 0xff;

    //   break;

    //  case 0x01://AI turn on
    //  	   run_t.gAi = 0;
	// 	   run_t.gPlasma =0;
	//        run_t.gDry =0;
	// 	   run_t.gFan = 0;
	// 	   Buzzer_On();
	// 	   AI_On();

		   
		   
    //  	    cmd=0xff;
    //  break;

     //Function
    //  case 0x08: //Fan turn on
       
	// 	Buzzer_On();
	// 	run_t.gFan=0;
	//     run_t.gFan_continueRun =0;
    //     cmd =0xff;
    //  break;

    //  case 0x18: //fan turn off
       
    //     Buzzer_On();
	// 	run_t.gFan=1; 
	//     run_t.gDry =1;
		 	
	//     Dry_Function(1) ;//PTC turn off
	// 	cmd=0xff;
      
    //   break;

     //dry key
     case 0x12: //PTC turn on
        
             Buzzer_On();
			 run_t.gDry = 1;
             run_t.gFan_continueRun =0;
		
			 Dry_Function(1);

	break;

     case 0x02: //PTC turn off
		Buzzer_On();
		run_t.gDry =0;
		Dry_Function(0) ;//Display_Function_OnOff();
        if(run_t.gPlasma ==1){ //plasma turn off flag
			run_t.gFan_counter =0;
			run_t.gFan_continueRun =1;

		}

cmd=0xff; 
       
     break;

     //kill key

    //  case 0x04:
       
    //    Buzzer_On();
	//    run_t.gPlasma =0;
	//    run_t.gFan_continueRun =0;
	//    UV_Function(0); //turn on
	//    Rat_Control_Function(0); //drive rat turn on
	//     cmd = 0xff; 
		   
    //    break;

    //  case 0x14:
        
    //  	    Buzzer_On();
       
    //         run_t.gPlasma =1; //turn off plasma 
		
    //        UV_Function(1); //turn off kill function
    //        Rat_Control_Function(1); //drive rat turn off
	// 		 if( run_t.gDry ==1){
			 
	// 			  run_t.gFan_counter =0;
	// 			 run_t.gFan_continueRun =1;
	// 		 }
    
    //       cmd = 0xff;
        
      
    //  break;

    //  case 0x88:
	            

	// 		    Buzzer_On(); 

	 
    //       cmd =0xff;


	//  break;

	//  case 0x87:
			  

    //            Buzzer_On(); 
    //      cmd = 0xff;
			      
	//  break;
     
    //  case 0x91:  //turn off PTC "heat"
    //      run_t.gDry =1;
	// 	 Dry_Function(1) ;//Display_Function_OnOff();
		    
    //         if(run_t.gPlasma ==1){ //plasma turn off flag
    //              run_t.gFan_counter =0;
	// 			 run_t.gFan_continueRun =1;

    //          }
		   
    //     cmd=0xff; 
         
    //  break;
     
    //  case 0x90: //turn on PTC heat
    //       run_t.gDry = 0;
    //       run_t.gFan_continueRun =0;
		
	// 	   Dry_Function(0);
    //        cmd=0xff; 
     break;

     default:
         
     break;


    }

	}
}

/**********************************************************************
	*
	*Functin Name: void RunCommand_Order(void)
	*Function : be check key of value 
	*Input Ref:  key of value
	*Return Ref: NO
	*
**********************************************************************/
void RunCommand_Order(void)
{
    
    static uint8_t retimes=0;


   if(run_t.gPower_On==0)times=0;
	
   if(run_t.gPower_On==1){

    if(run_t.sendtimes> 5 || retimes < 50) { // display humidity and temperature value
		run_t.sendtimes=0;

        retimes++;
      
       
		if(run_t.gPower_flag ==1){
			
            if(run_t.SingleMode ==1 )
                Display_DHT11_Value(&DHT11);
            
             }
		
      }
    
	
	 if(run_t.gFan_continueRun ==1 && run_t.gPower_On ==1 ){
          
                if(run_t.gFan_counter < 61){
          
                       FAN_CCW_RUN();
                  }       

	           if(run_t.gFan_counter > 59){
		           
				   run_t.gFan_counter=0;
				
				   run_t.gFan_continueRun++;
				   FAN_Stop();
				   SendCmd_To_Fan(0x01);
				   
	           }
	  }
	  if(run_t.gPower_On !=0 && run_t.gFan_continueRun ==0){

	      FAN_CCW_RUN();
      }
      
      
 }

   //Fan at power of function 
  if(run_t.gPower_On ==0 && run_t.gFan_continueRun ==1){ //Fan be stop flag :0 -Fan works 
        
         if(run_t.gFan_counter < 61){
         
             FAN_CCW_RUN();
         }        
       
        if(run_t.gFan_counter >= 60){ //60s
        
	     run_t.gFan_counter=0;
	  
         run_t.gFan_continueRun++;
		  FAN_Stop();
		  SendCmd_To_Fan(0x01);
	   }
   }

}


/**
  * Function Name: void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
  * Function: Tim3 interrupt call back function
  * Tim3 timer :timing time 10ms
  * 
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{

    static uint8_t tm0 ,tm1,tm3;
    if(htim->Instance==TIM3){
	   tm0 ++ ;
   
    
	   if(tm0 == 100){//100ms *10 = 1000ms =1s
       tm0 =0;
        tm3++;
   
       run_t.sendtimes++;
      if(run_t.gFan_continueRun ==1){
	   	   tm1++;
           run_t.gFan_counter++;
		   if(tm1 > 60){
		   	  tm1=0;
	          run_t.gTimer_60s =1;
              
		   }
	   }
     

	 }
  }

} 
    
