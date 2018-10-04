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

#include "treatment.h"
#include "timer.h"
#include "gpio.h"
#include "comms_from_rasp.h"
#include "comms_from_power.h"
#include "comms.h"
#include "usart.h"
#include "GTK_Signal.h"    //por definiciones de canales

#include <stdio.h>



/* Externals ------------------------------------------------------------------*/
//--- Externals para avisar data ready en usart
volatile unsigned char usart1_have_data;
volatile unsigned char usart2_have_data;
volatile unsigned char usart3_have_data;
volatile unsigned char usart4_have_data;
volatile unsigned char usart5_have_data;

unsigned short comms_messages_1 = 0;
unsigned short comms_messages_2 = 0;
unsigned short comms_messages_3 = 0;
unsigned short comms_messages_rpi = 0;


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
volatile unsigned short wait_ms_var = 0;
volatile unsigned short comms_timeout = 0;

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
volatile unsigned short secs_in_treatment = 0;
volatile unsigned short millis = 0;
unsigned short secs_end_treatment;
unsigned short secs_elapsed_up_to_now;
volatile unsigned char timer_sync_xxx_ms = 0;

//--- FUNCIONES DEL MODULO ---//
void TimingDelay_Decrement(void);


int main (void)
{
    unsigned char i = 0;
    unsigned long ii = 0;

#ifdef MAGNETO_NORMAL
    char buff [64];
    treatment_t main_state = TREATMENT_STANDBY;
#endif

#ifdef GATEWAY_TO_POWER_BOARDS
    unsigned short bytes_readed = 0;
    char s_to_senda [100];
    char s_to_sendb [100];
#endif

// 	unsigned char counter_keep_alive = 0;
// 	//Configuracion de clock.
    // RCC_Config ();

    //Configuracion systick    
    if (SysTick_Config(72000))
    {
        while (1)	/* Capture error */
        {
            if (LED1)
                LED1_OFF;
            else
                LED1_ON;

            for (i = 0; i < 255; i++)
            {
                asm (	"nop \n\t"
                        "nop \n\t"
                        "nop \n\t" );
            }
        }
    }
        

// 	//Configuracion led. & Enabled Channels
    GpioInit();

    //enciendo TIM7
    TIM7_Init();

    //enciendo usart1 para raspberry
    Usart1Config();

    //enciendo usart2 para comunicacion con micros
    Usart2Config();
    

    //-- Welcome Messages --------------------
#ifdef GATEWAY_TO_POWER_BOARDS
    Usart1Send("\nGateway to power side TEST!!!\n");
    Wait_ms(100);
#endif    
#ifdef MAGNETO_NORMAL
    Usart1Send("\nGausstek Stretcher Board -- powered by: Kirno Technology\n");
    Wait_ms(100);
#endif
#ifdef HARD
    Usart1Send(HARD);
    Wait_ms(100);    
#else
#error	"No Hardware defined in hard.h file"
#endif

#ifdef SOFT
    Usart1Send(SOFT);
    Wait_ms(100);    
#else
#error	"No Soft Version defined in hard.h file"
#endif

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

    //---- Prueba contra PC o Raspberry ----------
    // while (1)
    // {
    //     UpdateRaspberryMessages();
    // }
    //---- Fin Prueba contra PC o Raspberry ----------    


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
#ifdef GATEWAY_TO_POWER_BOARDS
    while (1)
    {
        if (power_have_data)
        {
            power_have_data = 0;
            bytes_readed = ReadPowerBuffer(s_to_sendb, sizeof(s_to_sendb));

            if ((bytes_readed + 1) < sizeof(s_to_sendb))
            {
                *(s_to_sendb + bytes_readed - 1) = '\n';
                *(s_to_sendb + bytes_readed) = '\0';
                RPI_Send(s_to_sendb);
            }
        }

        if (rpi_have_data)
        {
            rpi_have_data = 0;
            bytes_readed = ReadRPIBuffer(s_to_senda, sizeof(s_to_senda));

            if ((bytes_readed + 1) < sizeof(s_to_senda))
            {
                *(s_to_senda + bytes_readed - 1) = '\n';
                *(s_to_senda + bytes_readed) = '\0';
                Power_Send(s_to_senda);
            }

            if (LED1)
                LED1_OFF;
            else
                LED1_ON;
        }

#ifdef USE_SYNC_ALL_PLACES        
        //envio sync cada 100ms continuo
        if (!timer_sync_xxx_ms)
        {
            Power_Send_Unsigned((unsigned char *) ".", 1);
            timer_sync_xxx_ms = 100;
        }
#endif
    }

#endif //GATEWAY_TO_POWER_BOARDS

    //---- Programa Principal ----------
#ifdef MAGNETO_NORMAL    
    while (1)
    {
        switch (main_state)
        {
            case TREATMENT_STANDBY:

                if (comms_messages_rpi & COMM_START_TREAT)
                {
                    //me piden por el puerto que arranque el tratamiento
                    comms_messages_rpi &= ~COMM_START_TREAT;
                    if (TreatmentAssertParams() == resp_error)
                    {
                        RPI_Send("ERROR\r\n");
                    }
                    else
                    {
                        RPI_Send("OK\r\n");
                        PowerSendConf();
                        PowerSendStart();
                        main_state = TREATMENT_STARTING;                        
                    }
                }
                break;

            case TREATMENT_STARTING:
                secs_end_treatment = TreatmentGetTime();
                secs_in_treatment = 1;    //con 1 arranca el timer
                secs_elapsed_up_to_now = 0;
                PowerCommunicationStackReset();
                main_state = TREATMENT_RUNNING;
                break;

            case TREATMENT_RUNNING:
                PowerCommunicationStack();    //me comunico con las potencias para conocer el estado

                if (comms_messages_rpi & COMM_PAUSE_TREAT)
                {
                    comms_messages_rpi &= ~COMM_PAUSE_TREAT;
                    RPI_Send("OK\r\n");
                    PowerSendStop();
                    main_state = TREATMENT_PAUSED;
                    secs_elapsed_up_to_now = secs_in_treatment;
                }

                if (comms_messages_rpi & COMM_STOP_TREAT)
                {
                    comms_messages_rpi &= ~COMM_STOP_TREAT;
                    //termine el tratamiento
                    RPI_Send("OK\r\n");
                    PowerSendStop();
                    main_state = TREATMENT_STOPPING;
                }

                //me mandaron start???
                if (comms_messages_rpi & COMM_START_TREAT)
                {
                    comms_messages_rpi &= ~COMM_START_TREAT;
                    RPI_Send("ERROR\r\n");
                }

                if (secs_in_treatment >= secs_end_treatment)
                {
                    //termine el tratamiento
                    PowerSendStop();
                    RPI_Send("ended ok\r\n");
                    main_state = TREATMENT_STOPPING;
                }

                //reviso si hay algun canal con error
                if ((comms_messages_1 & COMM_POWER_ERROR_MASK) ||
                    (comms_messages_2 & COMM_POWER_ERROR_MASK) ||
                    (comms_messages_3 & COMM_POWER_ERROR_MASK))
                {
                    PowerSendStop();
                    LED1_ON;
                    if (comms_messages_1 & COMM_POWER_ERROR_MASK)
                        RaspBerry_Report_Errors(CH1, &comms_messages_1);

                    if (comms_messages_2 & COMM_POWER_ERROR_MASK)
                        RaspBerry_Report_Errors(CH2, &comms_messages_2);

                    if (comms_messages_3 & COMM_POWER_ERROR_MASK)
                        RaspBerry_Report_Errors(CH3, &comms_messages_3);
                    
                    LED1_OFF;
                    main_state = TREATMENT_WITH_ERRORS;
                    sprintf (buff, "treat err, ch1: 0x%04x, ch2: 0x%04x, ch3: 0x%04x\r\n",
                             comms_messages_1,
                             comms_messages_2,
                             comms_messages_3);
                    
                    RPI_Send(buff);
                }
                break;

            case TREATMENT_PAUSED:
                if (comms_messages_rpi & COMM_START_TREAT)
                {
                    comms_messages_rpi &= ~COMM_START_TREAT;
                    secs_in_treatment = secs_elapsed_up_to_now;
                    RPI_Send("OK\r\n");
                    PowerSendStart();
                    main_state = TREATMENT_RUNNING;
                }

                if (comms_messages_rpi & COMM_STOP_TREAT)
                {
                    //estaba en pausa y me mandaron stop
                    comms_messages_rpi &= ~COMM_STOP_TREAT;
                    RPI_Send("OK\r\n");
                    PowerSendStop();
                    main_state = TREATMENT_STOPPING;
                }                
                break;
                
            case TREATMENT_STOPPING:
                sprintf (buff, "treat end, ch1: 0x%04x, ch2: 0x%04x, ch3: 0x%04x\r\n",
                         comms_messages_1,
                         comms_messages_2,
                         comms_messages_3);
                    
                RPI_Send(buff);
                main_state = TREATMENT_STANDBY;
                break;

            case TREATMENT_WITH_ERRORS:
                Wait_ms(1000);
                RPI_Send("STOP\r\n");
                Wait_ms(1000);
                RPI_Send("STOP\r\n");
                Wait_ms(1000);
                RPI_Send("Flushing errors\r\n");
                Power_Send("chf flush errors\r\n");
                Wait_ms(1000);
                main_state = TREATMENT_STANDBY;
                break;

            default:
                main_state = TREATMENT_STANDBY;
                break;
        }            

        
        //reviso comunicacion con raspberry
        UpdateRaspberryMessages();

        //reviso comunicacion con potencias
        UpdatePowerMessages();

#ifdef USE_SYNC_ALL_PLACES        
        //envio sync cada 100ms continuo
        if (!timer_sync_xxx_ms)
        {
            Power_Send_Unsigned((unsigned char *) ".", 1);
            timer_sync_xxx_ms = 100;
        }
#endif        
    }
#endif //MAGNETO_NORMAL
    //---- Fin Programa Pricipal ----------
}
//--- End of Main ---//


void TimingDelay_Decrement(void)
{
    if (wait_ms_var)
        wait_ms_var--;

    if (comms_timeout)
        comms_timeout--;
    
    if (secs_in_treatment)
    {
        if (millis < 1000)
            millis++;
        else
        {
            secs_in_treatment++;
            millis = 0;
        }
    }
    
    // if (timer_standby)
    //     timer_standby--;

    // if (timer_filters)
    //     timer_filters--;
    
    // if (timer_led)
    //     timer_led--;

    // if (timer_led_pwm < 0xFFFF)
    //     timer_led_pwm ++;

    if (timer_sync_xxx_ms)
        timer_sync_xxx_ms--;
}

//--- end of file ---//

