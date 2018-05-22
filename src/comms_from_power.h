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



//---- Common Defines --------------------




//--- Exported functions ---//
void UpdatePowerMessages (void);
void PowerSendConf (void);
void PowerSendStart( void );
void PowerSendStop( void );

#endif
