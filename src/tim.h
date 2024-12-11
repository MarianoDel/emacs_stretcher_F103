//---------------------------------------------
// ##
// ## @Author: Med
// ## @Editor: Emacs - ggtags
// ## @TAGS:   Global
// ## @CPU:    STM32F103
// ##
// #### TIM.H #################################
//---------------------------------------------

#ifndef _TIMER_H_
#define _TIMER_H_

// Module Exported Types Constants and Macros ----------------------------------

#define EnableTimer1    (TIM1->CR1 |= TIM_CR1_CEN)
#define DisableTimer1    (TIM1->CR1 &= ~TIM_CR1_CEN)

#define EnableTimer3 (TIM3->CR1 |= TIM_CR1_CEN)
#define DisableTimer3    (TIM3->CR1 &= ~TIM_CR1_CEN)

#ifdef STM32F10X_HD
#define EnableTimer6    (TIM6->CR1 |= TIM_CR1_CEN)
#define DisableTimer6    (TIM6->CR1 &= ~TIM_CR1_CEN)

#define EnableTimer7    (TIM7->CR1 |= TIM_CR1_CEN)
#define DisableTimer7    (TIM7->CR1 &= ~TIM_CR1_CEN)
#endif


//--- Exported Functions ------------------------------
void Wait_ms (unsigned short);

void TIM1_Init (void);
unsigned char TIM1_SyncGet (void);
void TIM1_SyncReset (void);
unsigned char TIM1_SyncVerify (unsigned char * freq_int, unsigned char * freq_dec);

void TIM3_Init (void);

void TIM4_Init (void);
void TIM4_Update_CH2 (unsigned short a);
void TIM4_Update_CH3 (unsigned short a);

void TIM5_Init (void);
void TIM5_Update_CH1 (unsigned short a);
void TIM5_Update_CH2 (unsigned short a);

void TIM6_Init(void);
void TIM6_IRQHandler (void);
void TIM6_Change (unsigned short new_psc, unsigned short new_arr);
unsigned char TIM6_UIF_Get_Flag (void);
void TIM6_UIF_Reset (void);
void TIM6_UIF_Set (void);
void TIM6_Stop (void);

void TIM7_Init(void);
void TIM7_IRQHandler (void);
void TIM7_Change (unsigned short new_psc, unsigned short new_arr);
unsigned char TIM7_UIF_Get_Flag (void);
void TIM7_UIF_Reset (void);
void TIM7_UIF_Set (void);
void TIM7_Stop (void);

void TIM8_Init (void);
void TIM8_Stop (void);
void TIM8_Update_CH1 (unsigned short a);
void TIM8_Update_CH2 (unsigned short a);
void TIM8_Update_CH3 (unsigned short a);
void TIM8_Update_CH4 (unsigned short a);

#endif /* _TIMER_H_ */
