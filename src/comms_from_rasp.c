//---------------------------------------------------------
// ##
// ## @Author: Med
// ## @Editor: Emacs - ggtags
// ## @TAGS:   Global
// ## @CPU:    STM32F103
// ##
// #### COMMS_FROM_RASP.C ############################################
//---------------------------------------------------------

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "hard.h"

#include "comms_from_rasp.h"
#include "usart.h"
#include "treatment_signals.h"

#include <string.h>


#define RPI_Send(X)    Usart3Send(X)

/* Externals ------------------------------------------------------------------*/
extern volatile unsigned char usart3_have_data;



/* Globals ------------------------------------------------------------------*/
char local_rasp_buff [SIZEOF_RXDATA];

const char s_getall [] = {"get all conf"};

/* Module Private Functions -----------------------------------------------------------*/
static void RaspBerry_Messages (char *);
static void SendAllConf (void);

/* Module Exported Functions -----------------------------------------------------------*/
void UpdateRaspberryMessages (void)
{
    if (usart3_have_data)
    {
        usart3_have_data = 0;
        L_ALARMA_ON;
        ReadUsart3Buffer((unsigned char *) local_rasp_buff, SIZEOF_RXDATA);
        RaspBerry_Messages(local_rasp_buff);
        L_ALARMA_OFF;
    }
}



static void RaspBerry_Messages (char * msg)
{
    unsigned short hours = 0;
    unsigned short minutes = 0;
    unsigned short seconds = 0;
    
    if (!strncmp(msg, (const char *)"get_temp,", (sizeof("get_temp,") - 1)))
    {
        switch (*(msg+9))
        {
        case '1':
            // UART_CH1_Send("get_temp\r\n");
            RPI_Send("OK\r\n");
            break;

        case '2':
            // UART_CH2_Send("get_temp\r\n");
            RPI_Send("OK\r\n");
            break;

        case '3':
            // UART_CH3_Send("get_temp\r\n");
            RPI_Send("OK\r\n");
            break;

        default:
            RPI_Send("ERROR\r\n");
            break;
        }
    }

//     else if (!strncmp(msg, (const char *)"get_antenna_con,", (sizeof("get_antenna_con,") - 1)))
//     {
//         //0 si no tengo, 1 si esta 1, 2 si est 2 "ant_con,0,2,0,0\r\n"
//         /*
//           sprintf((const char *)&buffUART1rx2[0], "ant_con,0,2,0,0\r\n",
//           antenna.resistance_int,
//           antenna.resistance_dec,
//           antenna.inductance_int,
//           antenna.inductance_dec,
//           antenna.current_limit_int,
//           antenna.current_limit_dec,
//           antenna.temp_max_int,
//           antenna.temp_max_dec);
//           UART_PC_Send(buffUART1rx2);
//           buffUART1rx2[0] = '\0';
//         */
//         UART_PC_Send((char *) "ant_con,0,2,0,0\r\n");
//         buffUART1rx2[0] = '\0';
//     }

//     else if (!strncmp(msg, (const char *)"get_antenna,", (sizeof("get_antenna,") - 1)))
//     {
//         //--- Get antenna parameters ---//
//         Session_Get_Antenna (&session_ch_1, 1, &antenna);
//         //strcpy((const char *)&buffUART1rx2[0], (const char *)"ant0,");
//         //sprintf((const char *)&buffUART1rx2[0], "ant0,%03d.%02d,%03d.%02d,%03d.%02d,%03d.%02d,1\r\n",
//         sprintf((char *)&buffUART1rx2[0], "ant0,%03d.%02d,%03d.%02d,%03d.%02d,%03d.%02d,1\r\n",
//                 antenna.resistance_int,
//                 antenna.resistance_dec,
//                 antenna.inductance_int,
//                 antenna.inductance_dec,
//                 antenna.current_limit_int,
//                 antenna.current_limit_dec,
//                 antenna.temp_max_int,
//                 antenna.temp_max_dec);

//         //UART_PC_Send((const char *) buffUART1rx2);
//         UART_PC_Send((char *) buffUART1rx2);
//         buffUART1rx2[0] = '\0';

//         Session_Get_Antenna (&session_ch_2, 1, &antenna);
//         //strcpy((const char *)&buffUART1rx2[0], (const char *)"ant0,");
//         sprintf((char *)&buffUART1rx2[0], "ant0,%03d.%02d,%03d.%02d,%03d.%02d,%03d.%02d,2\r\n",
//                 antenna.resistance_int,
//                 antenna.resistance_dec,
//                 antenna.inductance_int,
//                 antenna.inductance_dec,
//                 antenna.current_limit_int,
//                 antenna.current_limit_dec,
//                 antenna.temp_max_int,
//                 antenna.temp_max_dec);

//         //UART_PC_Send((const char *) buffUART1rx2);
//         UART_PC_Send((char *) buffUART1rx2);
//         buffUART1rx2[0] = '\0';

//         Session_Get_Antenna (&session_ch_3, 1, &antenna);
//         //strcpy((const char *)&buffUART1rx2[0], (const char *)"ant0,");
//         sprintf((char *)&buffUART1rx2[0], "ant0,%03d.%02d,%03d.%02d,%03d.%02d,%03d.%02d,3\r\n",
//                 antenna.resistance_int,
//                 antenna.resistance_dec,
//                 antenna.inductance_int,
//                 antenna.inductance_dec,
//                 antenna.current_limit_int,
//                 antenna.current_limit_dec,
//                 antenna.temp_max_int,
//                 antenna.temp_max_dec);

//         UART_PC_Send((char *) buffUART1rx2);
//         buffUART1rx2[0] = '\0';

//         Session_Get_Antenna (&session_ch_4, 1, &antenna);
//         //strcpy((const char *)&buffUART1rx2[0], (const char *)"ant0,");
//         sprintf((char *)&buffUART1rx2[0], "ant0,%03d.%02d,%03d.%02d,%03d.%02d,%03d.%02d,4\r\n",
//                 antenna.resistance_int,
//                 antenna.resistance_dec,
//                 antenna.inductance_int,
//                 antenna.inductance_dec,
//                 antenna.current_limit_int,
//                 antenna.current_limit_dec,
//                 antenna.temp_max_int,
//                 antenna.temp_max_dec);

//         UART_PC_Send((char *) buffUART1rx2);
//         buffUART1rx2[0] = '\0';

//         if (Get_Antenna_Name(CH1, (char *) &buffUART1rx2[0]) != 0)
//         {
//             UART_PC_Send((char *) (const char *) "ant_name,1,");
//             UART_PC_Send((char *) buffUART1rx2);
//             UART_PC_Send((char *) (const char *) "\r\n");
//         }

//         if (Get_Antenna_Name(CH2, (char *) &buffUART1rx2[0]) != 0)
//         {
//             UART_PC_Send((char *) (const char *) "ant_name,2,");
//             UART_PC_Send((char *) buffUART1rx2);
//             UART_PC_Send((char *) (const char *) "\r\n");
//         }

//         if (Get_Antenna_Name(CH3, (char *) &buffUART1rx2[0]) != 0)
//         {
//             UART_PC_Send((char *) (const char *) "ant_name,3,");
//             UART_PC_Send((char *) buffUART1rx2);
//             UART_PC_Send((char *) (const char *) "\r\n");
//         }

//         if (Get_Antenna_Name(CH4, (char *) &buffUART1rx2[0]) != 0)
//         {
//             UART_PC_Send((char *) (const char *) "ant_name,4,");
//             UART_PC_Send((char *) buffUART1rx2);
//             UART_PC_Send((char *) (const char *) "\r\n");
//         }

//         buffUART1rx2[0] = '\0';
//     }

//     else if (!strncmp(msg, (const char *)"antenna,", (sizeof("antenna,") - 1)))
//     {

//         if (((buffUART1rx2[28] - 48) > 0) && ((buffUART1rx2[28] - 48) < 4) && (buffUART1rx2[27] == ','))
//         {
//             antenna.resistance_int = 	(buffUART1rx2[8] - 48) * 100 + (buffUART1rx2[9] - 48) * 10 + (buffUART1rx2[10] - 48);
//             antenna.resistance_dec = 	(buffUART1rx2[12] - 48) * 10 + (buffUART1rx2[13] - 48);
//             antenna.inductance_int = 	(buffUART1rx2[15] - 48) * 100 + (buffUART1rx2[16] - 48) * 10 + (buffUART1rx2[17] - 48);
//             antenna.inductance_dec = 	(buffUART1rx2[19] - 48) * 10 + (buffUART1rx2[20] - 48);
//             antenna.current_limit_int = (buffUART1rx2[22] - 48) * 10 + (buffUART1rx2[23] - 48);
//             antenna.current_limit_dec = (buffUART1rx2[25] - 48) * 10 + (buffUART1rx2[26] - 48);

//             //--- Save antenna parameters ---//
//             Session_Set_Antenna (&session_slot_aux, (buffUART1rx2[28] - 48), &antenna);

//             UART_PC_Send((char *)"OK\r\n");
//         }
//         else
//             UART_PC_Send((char *)"ERROR\r\n");
//     }
    //example. signal,100,100,0000,0003,0003,0003,0006,0000,0000,1
    else if (!strncmp(msg, (const char *)"signal,", (sizeof("signal,") - 1)))
    {
        //signal,%03d,%03d,0%x%x%d,%04d,%04d,%04d,%04d,%04d,%04d,1\r\n",
        if (((*(msg + 50) -'0') > 0) && ((*(msg + 50) - '0') < 4) && (*(msg + 49) == ','))
        {
            if (TreatmentTranslateOldMsg( msg ) == resp_ok)
                RPI_Send((char *)"OK\r\n");
            else
                RPI_Send((char *)"ERROR\r\n");            
        }
        else
            RPI_Send((char *)"ERROR\r\n");

    }
//     //example.	duration,00,10,00,1
    else if (!strncmp(msg, (const char *)"duration,", (sizeof("duration,") - 1)))
    {
        if ((*(msg + 18) > '0') && ((*(msg + 18)) < '4') && (*(msg + 17) == ','))
        {
            hours = (*(msg + 9) - '0') * 10 + *(msg + 10) - '0';
            minutes = (*(msg + 12) - '0') * 10 + *(msg + 13) - '0';
            seconds = (*(msg + 15) - '0') * 10 + *(msg + 16) - '0';

            if (TreatmentSetTime(hours, minutes, seconds) == resp_ok)
                RPI_Send((char *)"OK\r\n");
            else
                RPI_Send((char *)"ERROR\r\n");
        }
        else
            RPI_Send((char *)"ERROR\r\n");
    }

    else if (!strncmp(msg, (const char *)"save,01", (sizeof("save,01") - 1)))
    {
        // i = FLASH_Program(&session_slot_aux, ((buffUART1rx2[5] - 48) * 10 + (buffUART1rx2[6] - 48)));

        // if (i == FIN_OK)
        // {
        //     RPI_Send("Guardado OK\r\n");
        //     Wait_ms(1000);
        //     //Reset.
        //     NVIC_SystemReset();
        // }

        // if (i == FIN_ERROR)
        // {
        //     RPI_Send("Guardado ERROR\r\n");
        //     Wait_ms(1000);
        //     //Reset.
        //     NVIC_SystemReset();
        // }
        RPI_Send((char *)"OK\r\n");
    }


//     else if (!strncmp(msg, (const char *)"pause,", (sizeof("pause,") - 1)))
//     {
//         if (buffUART1rx2[6] - 48)
//         {
//             channel_1_pause = 1;
//             channel_2_pause = 1;
//             channel_3_pause = 1;
//             channel_4_pause = 1;
//         }
//         else
//         {
//             channel_1_pause = 0;
//             channel_2_pause = 0;
//             channel_3_pause = 0;
//             channel_4_pause = 0;
//         }
// /*			switch(buffUART3rx2[6] - 48)
// 			{
//                         case 1:
//                         if (buffUART3rx2[8] - 48)
//                         channel_1_pause = 1;
//                         else
//                         channel_1_pause = 0;

//                         break;

//                         case 2:
//                         if (buffUART3rx2[8] - 48)
//                         channel_2_pause = 1;
//                         else
//                         channel_2_pause = 0;
//                         break;

//                         case 3:
//                         if (buffUART3rx2[8] - 48)
//                         channel_3_pause = 1;
//                         else
//                         channel_3_pause = 0;
//                         break;

//                         case 4:
//                         if (buffUART3rx2[8] - 48)
//                         channel_4_pause = 1;
//                         else
//                         channel_4_pause = 0;
//                         break;

//                         default:
//                         UART3Send((char *)"ERROR\r\n");
//                         break;
// 			}
// */
//     }

    else if (!strncmp(msg, (const char *)"load,01", (sizeof("load,01") - 1)))
    {
        RPI_Send((char *)"OK\r\n");
    }

    else if (!strncmp(msg, (const char *)"stop,", (sizeof("stop,") - 1)))
    {
        // Session_Channel_1_Stop();
        // Session_Channel_2_Stop();
        // Session_Channel_3_Stop();
        // Session_Channel_4_Stop();

        RPI_Send((const char *)"OK\r\n");
    }

    else if (!strncmp(msg, (const char *)"pause,", (sizeof("pause,") - 1)))
    {
        RPI_Send((const char *)"OK\r\n");
    }
    
    else if (!strncmp(msg, (const char *)"reset", (sizeof("reset") - 1)))
    {
        RPI_Send((const char *) "Restarting...\r\n");
        // Wait_ms(1000);
        // NVIC_SystemReset();
    }

    else if (!strncmp(msg,(const char *)"start,", (sizeof("start,") - 1)))
    {
        // Session_Channel_1_Start();
        // Session_Channel_2_Start();
        // Session_Channel_3_Start();
        // Session_Channel_4_Start();

        // ResetCheckGlobalErrors ();
        // Current_Limit_Counter_Reset ();

        RPI_Send((char *)"OK\r\n");
    }



//     //example. state_of_stage,0,1
//     else if (!strncmp(msg, (const char *)"state_of_stage,", (sizeof("state_of_stage,") - 1)))
//     {

//         if (((buffUART1rx2[15] - 48) == 0) || ((buffUART1rx2[15] - 48) == 1))
//         {

//             Session_Set_Status (&session_slot_aux, (buffUART1rx2[17] - 48),(buffUART1rx2[15] - 48));

//             RPI_Send((char *)"OK\r\n");
//         }
//         else
//             RPI_Send((char *)"ERROR\r\n");

//     }

//     else if (!strncmp(msg, (const char *)"special_function,", (sizeof("special_function,") - 1)))
//     {

//         RPI_Send((char *)"OK\r\n");
//     }


//     else if (!strncmp(msg, (const char *)"stop,", (sizeof("stop,") - 1)))
//     {
// /*			if((buffUART3rx2[5] - 48) == 1)
//                         Session_Channel_1_Stop();
// 			if((buffUART3rx2[5] - 48) == 2)
//                         Session_Channel_2_Stop();
// 			if((buffUART3rx2[5] - 48) == 3)
//                         Session_Channel_3_Stop();
// 			if((buffUART3rx2[5] - 48) == 4)
//                         Session_Channel_4_Stop();
// */
//         Session_Channel_1_Stop();
//         Session_Channel_2_Stop();
//         Session_Channel_3_Stop();
//         Session_Channel_4_Stop();

//         RPI_Send((char *)"OK\r\n");
//     }

// #ifdef HARDWARE_VERSION_2_1
//     else if (!strncmp(msg, (const char *)"finish_ok,", (sizeof("finish_ok,") - 1)))
//     {
//         Session_Channel_1_Stop();
//         Session_Channel_2_Stop();
//         Session_Channel_3_Stop();
//         Session_Channel_4_Stop();

//         BuzzerCommands(BUZZER_MULTIPLE_SHORT, 3);
//         RPI_Send((char *)"OK\r\n");
//     }
// #endif

//     else if (!strncmp(msg, (const char *)"read_channel,", (sizeof("read_channel,") - 1)))
//     {
//         if (((buffUART1rx2[13] - 48) < 5) && ((buffUART1rx2[13] - 48) > 0))
//         {
//             Channel_Load (&session_slot_aux, (buffUART1rx2[13] - 48));

//             //--- Send slot content ---//
//             SessionSend(&session_slot_aux);

//             RPI_Send((char *)"OK\r\n");
//         }
//         else
//             RPI_Send((char *)"ERROR\r\n");
//     }

//     else if (!strncmp(msg, (const char *)"read_slot,", (sizeof("read_slot,") - 1)))
//     {
//         //load,slot[2],destino[1]
//         if ((((buffUART1rx2[11] - 48) + (buffUART1rx2[10] - 48) * 10) < 11))
//         {
//             Session_Load (&session_slot_aux, (((buffUART1rx2[10] - 48) * 10) + buffUART1rx2[11] - 48), 0);

//             //--- Send slot content ---//
//             SessionSend(&session_slot_aux);

//             RPI_Send((char *)"OK\r\n");
//         }
//         else
//             RPI_Send((char *)"ERROR\r\n");
//     }

//     else
//         RPI_Send((char *)"ERROR\r\n");
    else if (strncmp(msg, s_getall, sizeof(s_getall) - 1) == 0)
        SendAllConf();


//     //--- end ---//

}


static void SendAllConf (void)
{
    char b [128];
    TreatmentGetAllConf(b);
    RPI_Send(b);
}























//---- End of File ----//
