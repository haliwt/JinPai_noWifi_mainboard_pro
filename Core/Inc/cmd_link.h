#ifndef __CMD_LINK_H_
#define __CMD_LINK_H_
#include "main.h"


extern uint8_t rx_wifi_data[7];

extern uint8_t inputBuf[4];

extern uint8_t  inputCmd[2];
extern uint8_t wifiInputBuf[1];

void Decode_Function(void);

void SendData_To_TouchKey(uint8_t hum,uint8_t temp);

void SendCmd_To_Fan(uint8_t odata);


#endif 
