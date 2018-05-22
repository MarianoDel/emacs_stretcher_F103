//---------------------------------------------
// ##
// ## @Author: Med
// ## @Editor: Emacs - ggtags
// ## @TAGS:   Global
// ## @CPU:    STM32F103
// ##
// #### COMMS_FROM_POWER.H ################################
//---------------------------------------------

#ifndef _COMMS_FROM_POWER_H_
#define _COMMS_FROM_POWER_H_

//---- Includes to help the Defines ----------



//---- Configurations Defines --------------------
typedef enum {
    ASK_CH1 = 0,
    WAIT_ANSWER_CH1,
    ASK_CH2,
    WAIT_ANSWER_CH2,
    ASK_CH3,
    WAIT_ANSWER_CH3,
    CHECK_COUNTERS
    
} comm_state_t;


//---- Common Defines --------------------
#define MAX_NO_COMM_ERRORS        15



//--- Exported functions ---//
void UpdatePowerMessages (void);
void PowerSendConf (void);
void PowerSendStart( void );
void PowerSendStop( void );

#endif
