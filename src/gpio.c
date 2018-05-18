//---------------------------------------------
// ##
// ## @Author: Med
// ## @Editor: Emacs - ggtags
// ## @TAGS:   Global
// ## @CPU:    STM32F103
// ##
// #### GPIO.C ################################
//---------------------------------------------

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "gpio.h"
#include "hard.h"


/* Externals ------------------------------------------------------------------*/


/* Globals ------------------------------------------------------------------*/


/* Module Functions -----------------------------------------------------------*/

//************************************************************************************//
// void RCC_Config (void){

// 	//Configuracion clock.
// 	RCC_DeInit();

// 	//---- HSEON ----//
// 	RCC_HSEConfig(RCC_HSE_ON);
// 	while (!RCC_WaitForHSEStartUp());

// 	// First set the flash latency to work with our clock
// 	//	000 Zero wait state, if 0  MHz < SYSCLK <= 24 MHz
// 	//	001 One wait state, if  24 MHz < SYSCLK <= 48 MHz
// 	//	010 Two wait states, if 48 MHz < SYSCLK <= 72 MHz

// #ifdef sysFREC48
// 	  FLASH_SetLatency(FLASH_Latency_1);
// 	  RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_6);
// #endif
// #ifdef sysFREC72_XTAL_8
//    FLASH_SetLatency(FLASH_Latency_2);
//    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);
//    //RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_6);
// #endif
// #ifdef sysFREC72_XTAL_12
//    FLASH_SetLatency(FLASH_Latency_2);
//    //RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);
//    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_6);
// #endif

//    	RCC_PLLCmd(ENABLE);

// 	while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);

// 	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
// 	while (RCC_GetSYSCLKSource() != 0x08);

// 	//CLK AHB. Max 72MHz.
// 	RCC_HCLKConfig(RCC_SYSCLK_Div1);

// 	//CLK APB1. Max 36MHZ.
// 	RCC_PCLK1Config(RCC_HCLK_Div2);

// 	//CLK APB2 Max 72MHz.
// 	//RCC_PCLK2Config(RCC_HCLK_Div2);
// 	RCC_PCLK2Config(RCC_HCLK_Div1);

// 	//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
// 	//NVIC_SetPriority(SysTick_IRQn, 0);
// }

//--- Tamper config ---//
void Tamper_Config(void)
{
	unsigned long temp;

	//--- GPIOB ---//
	//--- Clock ---//
	if (!(RCC->APB2ENR & 0x00000008))
		RCC->APB2ENR |= 0x00000008;

	//--- Config pines ---//
	temp = GPIOB->CRH;
	temp &= 0xFF0FFFFF;
	temp |= 0x00800000;
	GPIOB->CRH = temp;
	GPIOB->BSRR = 0x00002000;
}





//------- GPIO REGISTERS ----------//
//
//	GPIOx->CRL	pin 7 - 0
//	3  2  1  0
//	CNF0  MODE0
//	GPIOx->CRH	pin 15 - 8
//
//      En hexa me queda cada nibble es igual a la configuracion de ese pin
//      nibble0 configura completo pin0
//
//	MODEx 00 Input (reset)
//	MODEx 01 Output 10MHz
//	MODEx 10 Output 2MHz
//	MODEx 11 Output 50MHz
//
//	Input Mode
//      las funciones alternativas de los pines estan directamente conectadad al
//      periferico en el modo input
//      CNFx 00 Analog
//      CNFx 01 Floating (reset)
//      CNFx 10 Input (pull up / dwn)
//      CNFx 11 Reserved
//
//	Output Mode
//      CNFx 00 Push Pull
//      CNFx 01 Open Drain
//      CNFx 10 Alternate func Push Pull
//      CNFx 11 Alternate func Open Drain


//--- Leds ---//
void Led_Config(void)
{

    unsigned long temp;

    //--- GPIOB & GPIOC ---//
    //--- Clock ---//
    if (!RCC_GPIOB_CLK)
        RCC_GPIOB_CLKEN;

    if (!RCC_GPIOC_CLK)
        RCC_GPIOC_CLKEN;

    //--- Config pines ---//
    //--- GPIOC pin 0 ---//
    //--- GPIOC pin 1 ---//
    temp = GPIOC->CRL;
    temp &= 0xFFFFFF00;
    temp |= 0x00000022;
    GPIOC->CRL = temp;

    //--- GPIOC pin 13 ---//
    temp = GPIOC->CRH;
    temp &= 0xFF0FFFFF;
    temp |= 0x00200000;
    GPIOC->CRH = temp;

    //--- Configuro los leds en PB5 - PB7 ---//
    temp = GPIOB->CRL;
    temp &= 0x000FFFFF;
    temp |= 0x22200000;
    GPIOB->CRL = temp;

    //--- Configuro los leds en PB8 - PB9 ---//
    //PB10 y PB11 alternative
    temp = GPIOB->CRH;
    temp &= 0xFFFF0000;
    // temp |= 0x0000AA22;    //con PB10 USART3_TX y PB11 USART3_RX
    temp |= 0x00008A22;    //con PB10 USART3_TX y PB11 input pdwn para USART3_RX    
    // temp |= 0x00002022;    // PB11 prueba salida USART3_RX
    GPIOB->CRH = temp;

}

void Led1Toggle(void){

	if(LED1){

		LED1_OFF;
	}
	else {

		LED1_ON;
	}
}

void Led2Toggle(void){

	if(LED2){

		LED2_OFF;
	}
	else {

		LED2_ON;
	}
}

/*
void Led3Toggle(void)
{
	if(LED3)
		LED3_OFF;
	else
		LED3_ON;
}
*/

