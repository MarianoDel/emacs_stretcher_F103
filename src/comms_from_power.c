//---------------------------------------------------------
// ##
// ## @Author: Med
// ## @Editor: Emacs - ggtags
// ## @TAGS:   Global
// ## @CPU:    STM32F103
// ##
// #### COMMS_FROM_POWER.C ############################################
//---------------------------------------------------------

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "hard.h"

#include "comms_from_power.h"
#include "usart.h"
#include "treatment_signals.h"

#include <string.h>


#define Power_Send(X)    Usart2Send(X)

/* Externals ------------------------------------------------------------------*/
extern volatile unsigned char usart2_have_data;



/* Globals ------------------------------------------------------------------*/
char local_power_buff [SIZEOF_RXDATA];

//estos son los mismos que en stretcher_F030
const char s_ch1 [] = {"ch1"};
const char s_ch2 [] = {"ch2"};
const char s_ch3 [] = {"ch3"};
const char s_chf [] = {"chf"};
const char s_set_signal [] = {"signal"};
const char s_frequency [] = {"frequency"};
const char s_power [] = {"power"};
const char s_square [] = {"square"};
const char s_triangular [] = {"triangular"};
const char s_sinusoidal [] = {"sinusoidal"};
const char s_ten_hz [] = {"10Hz"};
const char s_thirty_hz [] = {"30Hz"};
const char s_sixty_hz [] = {"60Hz"};
const char s_start_treatment [] = {"start treatment"};
const char s_stop_treatment [] = {"stop treatment"};
const char s_status [] = {"status"};
const char s_flush_errors [] = {"flush errors"};
const char s_getall [] = {"get all conf"};


/* Module Private Functions -----------------------------------------------------------*/
static void Power_Messages (char *);


/* Module Exported Functions -----------------------------------------------------------*/
void UpdatePowerMessages (void)
{
    if (usart2_have_data)
    {
        usart2_have_data = 0;
        L_ALARMA_ON;
        ReadUsart3Buffer((unsigned char *) local_power_buff, SIZEOF_RXDATA);
        Power_Messages(local_power_buff);
        L_ALARMA_OFF;
    }
}


void PowerSendConf (void)
{
    char buff [128];
    signal_type_t sig;
    frequency_t freq;

    sig = TreatmentGetSignalType ();
    if (sig == SQUARE_SIGNAL)
        sprintf (buff, "%s %s %s\n",s_chf, s_set_signal, s_square);
    else if (sig == TRIANGULAR_SIGNAL)
        sprintf (buff, "%s %s %s\n",s_chf, s_set_signal, s_triangular);
    else (sig == SINUSOIDAL_SIGNAL)
        sprintf (buff, "%s %s %s\n",s_chf, s_set_signal, s_sinusoidal);
    
    Power_Send(buff);

    freq = TreatmentGetFrequency ();
    if (freq == TEN_HZ)
        sprintf (buff, "%s %s %s\n",s_chf, s_frequency, s_ten_hz);
    else if (sig == THIRTY_HZ)
        sprintf (buff, "%s %s %s\n",s_chf, s_frequency, s_thirty_hz);
    else (sig == SIXTY_HZ)
        sprintf (buff, "%s %s %s\n",s_chf, s_frequency, s_sixty_hz);
    
    Power_Send(buff);

    sprintf (buff, "%s %s %d\n",s_chf, s_power, TreatmentGetPower());
    Power_Send(buff);

}

void PowerSendStart( void )
{
    char buff [64];
    sprintf (buff, "%s %s\n", s_chf, s_start_treatment);
    Power_Send(buff);
}

void PowerSendStop( void )
{
    char buff [64];
    sprintf (buff, "%s %s\n", s_chf, s_stop_treatment);
    Power_Send(buff);
}


