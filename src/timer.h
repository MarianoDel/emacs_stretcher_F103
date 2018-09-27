//---------------------------------------------
// ##
// ## @Author: Med
// ## @Editor: Emacs - ggtags
// ## @TAGS:   Global
// ## @CPU:    STM32F103
// ##
// #### TIMER.H ################################
//---------------------------------------------

#ifndef _TIMER_H_
#define _TIMER_H_

#define EnableTimer6 TIM6->CR1 |= TIM_CR1_CEN
#define DisableTimer6 TIM6->CR1 &= ~TIM_CR1_CEN

#define EnableTimer7 TIM7->CR1 |= TIM_CR1_CEN
#define DisableTimer7 TIM7->CR1 &= ~TIM_CR1_CEN

//--- Exported Functions ------------------------------
void TIM7_IRQHandler (void);
void TIM7_Init(void);
void TIM6_IRQHandler (void);
void TIM6_Init(void);
void TIM2_Init(void);
void Wait_ms (unsigned short);

#endif /* _TIMER_H_ */
