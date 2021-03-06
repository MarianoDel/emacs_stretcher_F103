//---------------------------------------------
// ##
// ## @Author: Med
// ## @Editor: Emacs - ggtags
// ## @TAGS:   Global
// ## @CPU:    STM32F103
// ##
// #### COMMS.H ################################
//---------------------------------------------

#ifndef _COMMS_H_
#define _COMMS_H_

//---- Includes to help the Defines ----------



//---- Configurations Defines --------------------



//---- Common Defines --------------------
//flags de mensajes raspberry
#define COMM_NONE_TREAT     0x0000
#define COMM_START_TREAT    0x0001
#define COMM_STOP_TREAT     0x0002
#define COMM_PAUSE_TREAT    0x0004
#define COMM_CONF_CHANGE    0x0008
#define COMM_STRETCHER_UP   0x0010
#define COMM_GOTO_BRIDGE    0x0020

#define COMM_RPI_ALL_MSG_MASK          0x00FF

//flags de mensajes placa potencia
#define COMM_POWER_ERROR_MASK          0x00FF

#define COMM_ERROR_OVERCURRENT         0x0001
#define COMM_ERROR_NO_CURRENT          0x0002
#define COMM_ERROR_SOFT_OVERCURRENT    0x0004
#define COMM_ERROR_OVERTEMP            0x0008
#define COMM_ERROR_NO_COMM             0x0010
#define COMM_ERROR_NO_TREATMENT        0x0020







//--- Exported functions ---//




#endif
