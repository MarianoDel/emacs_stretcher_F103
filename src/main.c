//---------------------------------------------------------
// #### PROYECTO STRETCHER MAGNETO F103 - Custom Board ####
// ##
// ## @Author: Med
// ## @Editor: Emacs - ggtags
// ## @TAGS:   Global
// ## @CPU:    STM32F103
// ##
// #### MAIN.C ############################################
//---------------------------------------------------------

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "hard.h"

// #include "GTK_Hard.h"
#include "timer.h"
#include "gpio.h"
#include "comms_from_rasp.h"
#include "usart.h"
// #include "pwm.h"
// #include "adc.h"
// #include "GTK_Estructura.h"
// #include "GTK_Signal.h"
// #include "flash_program.h"
// #include "GTK_Errors.h"


/* Externals ------------------------------------------------------------------*/
//--- Externals para avisar data ready en usart
volatile unsigned char usart1_have_data;
volatile unsigned char usart2_have_data;
volatile unsigned char usart3_have_data;
volatile unsigned char usart4_have_data;
volatile unsigned char usart5_have_data;

char buffSendErr[64];

//--- Externals para enviar keepalive por UART
#define TIME_RUN_DEF 250
volatile unsigned short timeRun = TIME_RUN_DEF;

//--- Externals para muestreos de corriente con el ADC
volatile unsigned char flagMuestreo = 0;
volatile unsigned char take_current_samples = 0;

//--- Externals para armar seniales y comprobar el TIM5 en el inicio del programa
volatile unsigned int session_warming_up_channel_1_stage_time = 0;

//--- Externals para el BUZZER
unsigned short buzzer_timeout = 0;

//--- Externals de los timers
volatile unsigned short wait_ms_var;

// //Estructuras.
// session_typedef session_slot_aux;

// session_typedef session_ch_1;
// session_typedef session_ch_2;
// session_typedef session_ch_3;
// session_typedef session_ch_4;

unsigned char temp_actual_channel_1_int = 0;
unsigned char temp_actual_channel_1_dec = 0;
unsigned char temp_actual_channel_2_int = 0;
unsigned char temp_actual_channel_2_dec = 0;
unsigned char temp_actual_channel_3_int = 0;
unsigned char temp_actual_channel_3_dec = 0;
unsigned char temp_actual_channel_4_int = 0;
unsigned char temp_actual_channel_4_dec = 0;

//session_typedef session_slot_1;
//session_typedef session_slot_2;
//session_typedef session_slot_3;
//session_typedef session_slot_4;
//session_typedef session_slot_5;

unsigned char channel_1_pause = 0;
unsigned char channel_2_pause = 0;
unsigned char channel_3_pause = 0;
unsigned char channel_4_pause = 0;

/* Globals ------------------------------------------------------------------*/


//--- FUNCIONES DEL MODULO ---//
void TimingDelay_Decrement(void);


int main (void)
{
    unsigned char i = 0;
    unsigned long ii = 0;
    char local_buff [64];
    treatment_t main_state = TREATMENT_STANDBY;
// 	unsigned char counter_keep_alive = 0;
// 	//Configuracion de clock.
    // RCC_Config ();

    //Configuracion systick    
    if (SysTick_Config(72000))
    {
        while (1)	/* Capture error */
        {
            if (L_ZONA)
                L_ZONA_OFF;
            else
                L_ZONA_ON;

            for (i = 0; i < 255; i++)
            {
                asm (	"nop \n\t"
                        "nop \n\t"
                        "nop \n\t" );
            }
        }
    }
        

// 	//Configuracion led. & Enabled Channels
    Led_Config();

    //enciendo TIM7
    TIM7_Init();

    // L_ZONA_ON;
    // L_ALARMA_ON;
    // L_SERV_ON;
    // L_NETLIGHT_ON;
    // L_WIFI_ON;

    //enciendo usart3
    Usart3Config();

    //---- Prueba Leds ----------
    // while (1)
    // {
    //     if (L_ZONA)
    //     {
    //         // RX_PIN_ON;
    //         L_ZONA_OFF;
    //         L_ALARMA_OFF;
    //         L_SERV_OFF;
    //         L_NETLIGHT_OFF;
    //         // L_WIFI_OFF;
    //     }
    //     else
    //     {
    //         // RX_PIN_OFF;
    //         L_ZONA_ON;
    //         L_ALARMA_ON;
    //         L_SERV_ON;
    //         L_NETLIGHT_ON;
    //         // L_WIFI_ON;
    //     }



    //     Wait_ms(2000);
    // }
    //---- Fin Prueba Leds ----------

    //---- Prueba Usart3 ----------
    // while (1)
    // {
    //     // Wait_ms(2000);
    //     L_ALARMA_OFF;
    //     Usart3Send("HOLA!!!\n");
    //     Wait_ms(100);

    //     if (usart3_have_data)
    //     {
    //         usart3_have_data = 0;
    //         L_ALARMA_ON;
    //         ReadUsart3Buffer(local_buff, 64);
    //         if (strcmp((const char *) "HOLA!!!", local_buff) == 0)
    //             L_ZONA_ON;
    //         else
    //             L_ZONA_OFF;

    //         Wait_ms(100);
    //         L_ALARMA_OFF;
    //         L_ZONA_OFF;
    //         Wait_ms(1900);
    //     }
    // }
    //---- Fin Prueba Usart3 ----------

    //---- Prueba Usart3 Contra PC ----------
    while (1)
    {
        UpdateRaspberryMessages();
    }
    //---- Fin Prueba Usart3 loop en terminal ----------

    //---- Prueba Usart3 loop en terminal ----------
    // while (1)
    // {
    //     if (usart3_have_data)
    //     {
    //         usart3_have_data = 0;
    //         L_ALARMA_ON;
    //         ReadUsart3Buffer(local_buff, 64);
    //         Wait_ms(1000);
    //         i = strlen(local_buff);
    //         if (i < 62)
    //         {
    //             local_buff[i] = '\n';
    //             local_buff[i+1] = '\0';
    //             Usart3Send(local_buff);
    //         }
    //         L_ALARMA_OFF;
    //     }
    // }
    //---- Fin Prueba Usart3 loop en terminal ----------

    //---- Prueba Usart3 envia caracter solo 'd' ----------
    // while (1)
    // {
    //     unsigned char snd = 'd';
    //     Usart3SendUnsigned(&snd, 1);
    //     // USART3->DR = 'd';
    //     Wait_ms(100);
    // }
    //---- Fin Prueba Usart3 envia caracter solo 'd' ----------

    //---- Programa Principal ----------
    while (1)
    {
        switch (main_state)
        {
            case TREATMENT_STANDBY:

                if (comms_messages & COMM_CONF_CHANGE)
                {
                    PowerSendConf();
                    comms_messages &= ~COMM_CONF_CHANGE;
                }

                if (comms_messages & COMM_START_TREAT)
                {
                    //me piden por el puerto que arranque el tratamiento
                    if (TreatmentAssertParams() == resp_error)
                    {
                        RPI_Send("ERROR\r\n");
                        comms_messages &= ~COMM_START_TREAT;
                    }
                    else
                    {
                        PowerSendStart();
                        main_state = TREATMENT_STARTING;                        
                    }
                }
                break;

            case TREATMENT_STARTING:
                secs_end_treatment = TreatmentGetTime();
                secs_in_treatment = 0;
                secs_elapsed_up_to_now = 0;
                main_state = TREATMENT_RUNNING;
                break;

            case TREATMENT_RUNNING:

                if (comms_messages & COMM_PAUSE_TREAT)
                {
                    comms_messages &= ~COMM_PAUSE_TREAT;
                    PowerSendStop();
                    main_state = TREATMENT_PAUSED;
                    secs_elapsed_up_to_now = secs_in_treatment;
                }

                if ((comms_messages & COMM_STOP_TREAT) ||
                    (secs_in_treatment >= secs_end_treatment))
                {
                    //termine el tratamiento
                    comms_messages &= ~COMM_STOP_TREAT;                 
                    PowerSendStop();
                    main_state = TREATMENT_STOPPING;
                }
                break;

            case TREATMENT_PAUSED:

                if (comms_messages & COMM_START_TREAT)
                {
                    comms_messages &= ~COMM_START_TREAT;
                    secs_in_treatment = secs_elapsed_up_to_now;
                    PowerSendStart();
                    main_state = TREATMENT_RUNNING;
                }

                if (comms_messages & COMM_STOP_TREAT)
                {
                    //estaba en pausa y me mandaron stop
                    comms_messages &= ~COMM_STOP_TREAT;                 
                    PowerSendStop();
                    main_state = TREATMENT_STOPPING;
                }                
                break;
                
            case TREATMENT_STOPPING:
                main_state = TREATMENT_STANDBY;
                break;

            default:
                main_state = TREATMENT_STANDBY;
                break;
        }            

        
        //reviso comunicacion con raspberry
        UpdateRaspberryMessages();
    }
    //---- Fin Programa Pricipal ----------

        

// 	//Timer 1ms -- Wait_ms()
// 	TIM7_Init();

// 	//Timer 100ms.
// 	TIM6_Init();

// 	//Signal timer -- 100us
// 	TIM5_Init();

// 	//ADC1.
// 	ADC1_Init();

// 	//UART_Debug Config.
// 	UART_PC_Init();
// 	UART_CH1_Init();
// 	UART_CH2_Init();
// 	UART_CH3_Init();
// 	UART_CH4_Init();

// 	//Configuracion PWM.
// 	PWM1_Init();
// 	PWM2_Init();
// 	PWM3_Init();
// 	PWM4_Init();

// 	//Initialize channels.
// 	Channel_1_Init();
// 	Channel_2_Init();
// 	Channel_3_Init();
// 	Channel_4_Init();

// 	//Ajusto frecuencia del clock, debe prender el led Ton = 100ms T = 200ms
// 	//de otra forma revisar el cristal elegido
// 	//pruebo TIM5 100us step
// 	for (i = 0; i < 20; i++)
// 	{
// 		if (LED1)
// 		{
// 			LED1_OFF;
// 			// ENA_CH4_OFF;
// 		}
// 		else
// 		{
// 			LED1_ON;
// 			// ENA_CH4_ON;
// 		}

// 		while (session_warming_up_channel_1_stage_time != 0);
// 		session_warming_up_channel_1_stage_time = 1000;	//100ms
// //		Wait_ms(100);
// 	}
// 	LED1_OFF;

// //---- Defines from GTK_Hard.h -----//
// 	UART_PC_Send("\r\nGausstek Limited Inc. -- Magnet Equipment\r\n");
// 	UART_PC_Send("powered by: Kirno Technology\r\n");

// #ifdef HARD
// 	UART_PC_Send(HARD);
// #else
// #error	"No Hardware defined in GTK_Hard.h file"
// #endif

// #ifdef SOFT
// 	UART_PC_Send(SOFT);
// #else
// #error	"No Soft Version defined in GTK_Hard.h file"
// #endif

// 	UART_PC_Send("Ready!\r\n");
// 	// BuzzerCommands(BUZZER_MULTIPLE_SHORT, 1);
// //---- End of Defines from GTK_Hard.h -----//

// 	//mando ENABLE los canales
// 	ENA_CH1_ON;
// 	ENA_CH2_ON;
// 	ENA_CH3_ON;
// 	ENA_CH4_ON;
// 	Wait_ms(10);
// 	ENA_CH1_OFF;
// 	ENA_CH2_OFF;
// 	ENA_CH3_OFF;
// 	ENA_CH4_OFF;

// 	while (TRUE)
// 	{
// 		if (timeRun == 0)	//decrece cada 1ms
// 		{

// 			if (counter_keep_alive > 10)
// 			{
// 				counter_keep_alive = 0;

// 				//sprintf(&buffSendErr[0], (const char *) "keepalive,%d,%d,%d,%d\r\n", session_ch_1.status, session_ch_2.status, session_ch_3.status, session_ch_4.status);
// 				//UART_PC_Send(&buffSendErr[0]);

// 				//UART_PC_Send("ant0,010.60,078.20,002.00,065.00,4\r\n");

// 				if (session_ch_1.status == 0)
// 					UART_CH1_Send("keepalive\r\n");
// 				if (session_ch_2.status == 0)
// 					UART_CH2_Send("keepalive\r\n");
// 				if (session_ch_3.status == 0)
// 					UART_CH3_Send("keepalive\r\n");
// 				if (session_ch_4.status == 0)
// 					UART_CH4_Send("keepalive\r\n");
// 			}
// 			else
// 				counter_keep_alive++;

// 			//Led3Toggle();

// 			timeRun = TIME_RUN_DEF;
// 		}

// 		//ADC control.
// 		Session_Current_Limit_control();

// 		//Channel 1.
// 		Session_Channel_1 ();
// 		UART_CH1_Receive();

// 		//Channel 2.
// 		Session_Channel_2 ();
// 		UART_CH2_Receive();

// 		//Channel 3.
// 		Session_Channel_3 ();
// 		UART_CH3_Receive();

// 		//Channel 4.
// 		Session_Channel_4 ();	//si comento esto se cuelga saltando siempre TIM1_1MS pero parece solo con el debugger puesto PROBR QUITNDO TODOS LOS BREAKS
// 		UART_CH4_Receive();

// 		//Recepcion de la configuracion por PC.
// 		UART_PC_Receive();

// 		//Chequeo de errores globales
// 		CheckforGlobalErrors();

// #ifdef SOFTWARE_VERSION_1_2
// 		//Funciones del Buzzer
// 		UpdateBuzzer();
// #endif

// 	}
}

//--- End of Main ---//


void TimingDelay_Decrement(void)
{
    if (wait_ms_var)
        wait_ms_var--;

    // if (timer_standby)
    //     timer_standby--;

    // if (timer_filters)
    //     timer_filters--;
    
    // if (timer_led)
    //     timer_led--;

    // if (timer_led_pwm < 0xFFFF)
    //     timer_led_pwm ++;
    
}

//--- end of file ---//

