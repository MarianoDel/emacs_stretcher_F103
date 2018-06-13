//---------------------------------------------
// ##
// ## @Author: Med
// ## @Editor: Emacs - ggtags
// ## @TAGS:   Global
// ## @CPU:    STM32F103
// ##
// #### HARD.H #################################
//---------------------------------------------

#ifndef HARD_H_
#define HARD_H_


//----------- Defines For Configuration -------------

//----- Board Configuration -------------------//
//--- Hardware ------------------//
#define HARDWARE_VERSION_2_0
// #define HARDWARE_VERSION_1_0        //esto seria una placa P1 en realidad
// #define HARDWARE_VERSION_2_1        //esto seria una placa magneto chico
//--- Software ------------------//
// #define SOFTWARE_VERSION_1_2		
// #define SOFTWARE_VERSION_1_1	     //habla contra pc o rpi con nuevo protocolo camilla
#define SOFTWARE_VERSION_1_0        //habla contra rpi con programa magneto y traduce a micros potencia

//-------- Type of Program (depending on software version) ----------------
// #define MAGNETO_NORMAL
#define GATEWAY_TO_POWER_BOARDS



//-------- Type of Program and Features ----------------
//Si utiliza la proteccion con la int para cortar la corriente
// #define USE_PROTECTION_WITH_INT

//Si utiliza la proteccion de soft overcurrent o no
// #define USE_SOFT_OVERCURRENT

//Modo de uso de la USART (placa individual single - placa enganchada bus)
// #define USART_IN_BUS
// #define USART_SINGLE

//-------- Kind of Reports Sended ----------------

//-------- Others Configurations depending on the formers ------------

//-------- Hysteresis Conf ------------------------

//-------- PWM Conf ------------------------

//-------- Oscillator and Crystal selection (Freq in startup_clocksh) ---
#define HSI_INTERNAL_RC
// #define HSE_CRYSTAL_OSC


//-------- End Of Defines For Configuration ------




//--- Hardware & Software Messages ------------------//
#ifdef HARDWARE_VERSION_2_0
#define HARD "Hardware Version: 2.0\r\n"
#endif
#ifdef HARDWARE_VERSION_2_1
#define HARD "Hardware Version: 2.1\r\n"
#endif
#ifdef SOFTWARE_VERSION_2_2
#define SOFT "Software Version: 2.2\r\n"
#endif
#ifdef SOFTWARE_VERSION_1_0
#define SOFT "Software Version: 1.0\r\n"
#endif
#ifdef SOFTWARE_VERSION_1_1
#define SOFT "Software Version: 1.1\r\n"
#endif
//--- End of Hardware & Software Messages ------------------//



//--- Exported constants ---//
typedef enum {
	resp_ok = 0,
	resp_not_own,
	resp_error

} resp_t;

enum resultados
{
	NO_INIT = 0,
	TRABAJANDO,
	FIN_OK,
	FIN_ERROR,
	FIN_TIMEOUT
};

enum bool
{
	FALSE = 0,
	TRUE = !FALSE
};


//--- Configuracion de leds ---//
#ifdef HARDWARE_VERSION_2_0
//--- PC0 ---//
#define LED1 ((GPIOC->ODR & 0x0001) == 0)
#define LED1_OFF GPIOC->BSRR = 0x00000001
#define LED1_ON GPIOC->BSRR = 0x00010000

//--- PC1 ---//
#define LED2 ((GPIOC->ODR & 0x0002) == 0)
#define LED2_OFF GPIOC->BSRR = 0x00000002
#define LED2_ON GPIOC->BSRR = 0x00020000

//PA0, PA1 NC

//PA2
//PA3    Usart2

//PA4, PA5, PA6, PA7  NC

//PC4    Analog
//PC5    Analog

//PB0, PB1, PB2 NC

//PB10
//PB11    Usart3

//PB12    NC

//--- PB13 ---//
#define OUT5 ((GPIOB->ODR & 0x2000) == 0)
#define OUT5_OFF GPIOB->BSRR = 0x00002000
#define OUT5_ON GPIOB->BSRR = 0x20000000

//--- PB14 ---//
#define OUT4 ((GPIOB->ODR & 0x4000) == 0)
#define OUT4_OFF GPIOB->BSRR = 0x00004000
#define OUT4_ON GPIOB->BSRR = 0x40000000

//--- PB15 ---//
#define OUT1 ((GPIOB->ODR & 0x8000) == 0)
#define OUT1_OFF GPIOB->BSRR = 0x00008000
#define OUT1_ON GPIOB->BSRR = 0x80000000

//--- PC6 ---//
#define OUT2 ((GPIOC->ODR & 0x0040) != 0)
#define OUT2_ON GPIOC->BSRR = 0x00000040
#define OUT2_OFF GPIOC->BSRR = 0x00400000

//--- PC7 ---//
#define OUT3 ((GPIOC->ODR & 0x0080) != 0)
#define OUT3_ON GPIOC->BSRR = 0x00000080
#define OUT3_OFF GPIOC->BSRR = 0x00800000

//--- PC8 ---//
#define IN2 ((GPIOC->IDR & 0x0100) != 0)

//--- PC9 ---//
#define IN1 ((GPIOC->IDR & 0x0200) != 0)

//--- PA8 ---//
#define IN0 ((GPIOA->IDR & 0x0100) != 0)

//PA9
//PA10    Usart1

//PA11, PA12, PA13, PA14, PA15    NC

//PC10
//PC11    Uart4

//PC12
//PD2    Uart5

//PB3, PB4    NC

//--- PB5 ---//
#define SW_RX_TX ((GPIOB->ODR & 0x0020) != 0)
#define SW_RX_TX_ON GPIOB->BSRR = 0x00000020
#define SW_RX_TX_OFF GPIOB->BSRR = 0x00200000

//PB6, PB7, PB8, PB9    NC

#endif //HARDWARE_VERSION_2_0


#ifdef HARDWARE_VERSION_2_1
//--- PC13 ---//
#define BUZZER ((GPIOC->ODR & 0x2000) != 0)
#define BUZZER_ON GPIOC->BSRR = 0x00002000
#define BUZZER_OFF GPIOC->BSRR = 0x20000000

//--- PB11 prueba salida por USART3_RX ---//
#define RX_PIN ((GPIOB->ODR & 0x0800) != 0)
#define RX_PIN_ON GPIOB->BSRR = 0x00000800
#define RX_PIN_OFF GPIOB->BSRR = 0x08000000

//--- PB9 ---//
#define L_ZONA ((GPIOB->ODR & 0x0200) != 0)
#define L_ZONA_ON GPIOB->BSRR = 0x00000200
#define L_ZONA_OFF GPIOB->BSRR = 0x02000000

//--- PB8 ---//
#define L_ALARMA ((GPIOB->ODR & 0x0100) != 0)
#define L_ALARMA_ON GPIOB->BSRR = 0x00000100
#define L_ALARMA_OFF GPIOB->BSRR = 0x01000000

//--- PB7 ---//
#define L_SERV ((GPIOB->ODR & 0x0080) != 0)
#define L_SERV_ON GPIOB->BSRR = 0x00000080
#define L_SERV_OFF GPIOB->BSRR = 0x00800000

//--- PB6 ---//
#define L_NETLIGHT ((GPIOB->ODR & 0x0040) != 0)
#define L_NETLIGHT_ON GPIOB->BSRR = 0x00000040
#define L_NETLIGHT_OFF GPIOB->BSRR = 0x00400000

//--- PB5 ---//
#define L_WIFI ((GPIOB->ODR & 0x0020) != 0)
#define L_WIFI_ON GPIOB->BSRR = 0x00000020
#define L_WIFI_OFF GPIOB->BSRR = 0x00200000

//--- PB0 ---//
#define ENA_CH1 ((GPIOB->ODR & 0x0001) != 0)
#define ENA_CH1_ON GPIOB->BSRR = 0x00000001
#define ENA_CH1_OFF GPIOB->BSRR = 0x00010000

//--- PB1 ---//
#define ENA_CH2 ((GPIOB->ODR & 0x0002) != 0)
#define ENA_CH2_ON GPIOB->BSRR = 0x00000002
#define ENA_CH2_OFF GPIOB->BSRR = 0x00020000

//--- PB2 ---//
#define ENA_CH3 ((GPIOB->ODR & 0x0004) != 0)
#define ENA_CH3_ON GPIOB->BSRR = 0x00000004
#define ENA_CH3_OFF GPIOB->BSRR = 0x00040000

//--- PB13 ---//
#define ENA_CH4 ((GPIOB->ODR & 0x2000) != 0)
#define ENA_CH4_ON GPIOB->BSRR = 0x00002000
#define ENA_CH4_OFF GPIOB->BSRR = 0x20000000

#endif    //HARDWARE_VERSION_2_1

//--- RCC clkEnable ---//

#define RCC_TIM1_CLK (RCC->APB2ENR & 0x00000800)
#define RCC_TIM1_CLKEN RCC->APB2ENR |= 0x00000800
#define RCC_TIM1_CLKDIS RCC->APB2ENR &= ~0x00000800

#define RCC_TIM2_CLK (RCC->APB1ENR & 0x00000001)
#define RCC_TIM2_CLKEN RCC->APB1ENR |= 0x00000001
#define RCC_TIM2_CLKDIS RCC->APB1ENR &= ~0x00000001

#define RCC_TIM3_CLK (RCC->APB1ENR & 0x00000002)
#define RCC_TIM3_CLKEN RCC->APB1ENR |= 0x00000002
#define RCC_TIM3_CLKDIS RCC->APB1ENR &= ~0x00000002

#define RCC_TIM4_CLK (RCC->APB1ENR & 0x00000004)
#define RCC_TIM4_CLKEN RCC->APB1ENR |= 0x00000004
#define RCC_TIM4_CLKDIS RCC->APB1ENR &= ~0x00000004

#define RCC_TIM5_CLK (RCC->APB1ENR & 0x00000008)
#define RCC_TIM5_CLKEN RCC->APB1ENR |= 0x00000008
#define RCC_TIM5_CLKDIS RCC->APB1ENR &= ~0x00000008


#define RCC_ADC1_CLK (RCC->APB2ENR & 0x00000200)
#define RCC_ADC1_CLKEN RCC->APB2ENR |= 0x00000200
#define RCC_ADC1_CLKDIS RCC->APB2ENR &= ~0x00000200

#define RCC_ADC2_CLK (RCC->APB2ENR & 0x00000400)
#define RCC_ADC2_CLKEN RCC->APB2ENR |= 0x00000400
#define RCC_ADC2_CLKDIS RCC->APB2ENR &= ~0x00000400

#define RCC_ADC3_CLK (RCC->APB2ENR & 0x00008000)
#define RCC_ADC3_CLKEN RCC->APB2ENR |= 0x00008000
#define RCC_ADC3_CLKDIS RCC->APB2ENR &= ~0x00008000

typedef enum
{
	BUZZER_INIT = 0,
	BUZZER_MULTIPLE_SHORT,
	BUZZER_MULTIPLE_SHORTA,
	BUZZER_MULTIPLE_SHORTB,
	BUZZER_MULTIPLE_HALF,
	BUZZER_MULTIPLE_HALFA,
	BUZZER_MULTIPLE_HALFB,
	BUZZER_MULTIPLE_LONG,
	BUZZER_MULTIPLE_LONGA,
	BUZZER_MULTIPLE_LONGB,
	BUZZER_TO_STOP

} tBuzzer;

//--- Tiempos (TIMEOUT) del buzzer
#define TIM_BIP_SHORT       300
#define TIM_BIP_SHORT_WAIT        500
#define TIM_BIP_HALF        600
#define TIM_BIP_HALF_WAIT        800
#define TIM_BIP_LONG        2000
#define TIM_BIP_LONG_WAIT        2000

//--- Exported Module Functions ----
//--- Clock ---//
void RCC_Config (void);
//--- Leds ---//
void Led_Config(void);
void Led1Toggle(void);
void Led2Toggle(void);
void Led3Toggle(void);
void UpdateBuzzer (void);
void BuzzerCommands(unsigned char , unsigned char );

#endif
