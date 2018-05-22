//---------------------------------------------
// ##
// ## @Author: Med
// ## @Editor: Emacs - ggtags
// ## @TAGS:   Global
// ## @CPU:    STM32F103
// ##
// #### COMMS_FROM_RASP.H ################################
//---------------------------------------------

#ifndef _COMMS_FROM_RASP_H_
#define _COMMS_FROM_RASP_H_

//---- Includes to help the Defines ----------



//---- Configurations Defines --------------------
#define RPI_Send(X)    Usart3Send(X)


//---- Common Defines --------------------
#define COMM_NONE_TREAT     0x0000
#define COMM_START_TREAT    0x0001
#define COMM_STOP_TREAT     0x0002
#define COMM_PAUSE_TREAT    0x0004
#define COMM_CONF_CHANGE    0x0008





//--- Exported functions ---//
void UpdateRaspberryMessages (void);



#endif
