//---------------------------------------------------------
// #### PROYECTO STRETCHER MAGNETO F103 - Custom Board ####
// ##
// ## @Author: Med
// ## @Editor: Emacs - ggtags
// ## @TAGS:   Global
// ## @CPU:    STM32F103
// ##
// #### TREATMENT.C ###############################
//---------------------------------------------------------

/* Includes ------------------------------------------------------------------*/
#include "treatment.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
// #include "hard.h"


//--- VARIABLES EXTERNAS ---//

//--- VARIABLES GLOBALES ---//
treatment_conf_t treatment_conf;
unsigned char global_error = 0;

// Private Defines ----------------------------------------
#define ENABLE_CHX_MASK    0x40
#define DISABLE_CHX_MASK    0x80
#define CHX_MASK        0x0F


//--- FUNCIONES DEL MODULO ---//

resp_t TreatmentSetSignalType (signal_type_t a)
{
    if ((a == SQUARE_SIGNAL) ||
        (a == TRIANGULAR_SIGNAL) ||
        (a == SINUSOIDAL_SIGNAL))

        treatment_conf.treatment_signal.signal = a;
    else
        return resp_error;

    return resp_ok;
}

signal_type_t TreatmentGetSignalType (void)
{
    return treatment_conf.treatment_signal.signal;
}

resp_t TreatmentSetFrequency (unsigned char freq_int, unsigned char freq_dec)
{
    resp_t resp = resp_error;
    unsigned int calc = 1000000;
    unsigned short freq = 0;

    //el synchro es un timer con tick cada 100us
    //la cuenta para 2 decimales da 1M/(freq*100)
    freq = freq_int * 100;
    freq += freq_dec;
    freq = freq * K_SYNCHRO_ADJUST;
    freq = freq / 100;

    calc = calc / freq;
    if ((calc < TIMER_SYNCHRO_MAX) && (calc > TIMER_SYNCHRO_MIN))
    {
        treatment_conf.treatment_signal.freq_int = freq_int;
        treatment_conf.treatment_signal.freq_dec = freq_dec;
        treatment_conf.timer_synchro = (unsigned short) calc;
        resp = resp_ok;
    }
    
    return resp;
}

unsigned short TreatmentGetSynchroTimer (void)
{
    return treatment_conf.timer_synchro;
}

void TreatmentSetChannelsFlag (unsigned char  a)
{
    if (a & ENABLE_CHX_MASK)
        treatment_conf.channels_in_treatment |= (a & CHX_MASK);

    if (a & DISABLE_CHX_MASK)
        treatment_conf.channels_in_treatment &= (~(a & CHX_MASK));
}

unsigned char TreatmentGetChannelsFlag (void)
{
    return (treatment_conf.channels_in_treatment & CHX_MASK);
}

// resp_t TreatmentChannelFlags (ch_in_treatment_t a)
// {
//     if (a == CH1_ENABLE)
//         treatment_conf.ch1_enable = 1;

//     if (a == CH2_ENABLE)
//         treatment_conf.ch2_enable = 1;

//     if (a == CH3_ENABLE)
//         treatment_conf.ch3_enable = 1;

//     if (a == CH1_DISABLE)
//         treatment_conf.ch1_enable = 0;

//     if (a == CH2_DISABLE)
//         treatment_conf.ch2_enable = 0;

//     if (a == CH3_DISABLE)
//         treatment_conf.ch3_enable = 0;
    
//     return resp_ok;
// }

void TreatmentGetFrequency (unsigned char * f_int, unsigned char * f_dec)
{
    *f_int = treatment_conf.treatment_signal.freq_int;
    *f_dec = treatment_conf.treatment_signal.freq_dec;    
}

resp_t TreatmentSetPower (unsigned char a)
{
    if (a > 100)
        treatment_conf.treatment_signal.power = 100;
    else if (a < 10)
        treatment_conf.treatment_signal.power = 10;
    else
        treatment_conf.treatment_signal.power = a;

    return resp_ok;
}

unsigned char TreatmentGetPower (void)
{
    return treatment_conf.treatment_signal.power;
}

resp_t TreatmentSetTime (unsigned char h, unsigned char m, unsigned char s)
{
    if ((h > 1) || (m > 60) || (s > 60))
        return resp_error;

    treatment_conf.treatment_time = h * 3600;
    treatment_conf.treatment_time += m * 60;
    treatment_conf.treatment_time += s;
    
    return resp_ok;
}

unsigned short TreatmentGetTime (void)
{
    return treatment_conf.treatment_time;
}

void TreatmentGetAllConf (char * tosend)
{
    char buf[30];
    
    sprintf(buf, "signal: %d\n", treatment_conf.treatment_signal.signal);
    strcpy(tosend, buf);
    sprintf(buf, "freq: %d.%02dHz\n",
            treatment_conf.treatment_signal.freq_int,
            treatment_conf.treatment_signal.freq_dec);
    strcat(tosend, buf);
    sprintf(buf, "power: %d\n", treatment_conf.treatment_signal.power);
    strcat(tosend, buf);
    sprintf(buf, "synchro: %d\n", treatment_conf.treatment_signal.synchro_needed);
    strcat(tosend, buf);
    sprintf(buf, "time in s: %d\n", treatment_conf.treatment_time);
    strcat(tosend, buf);
}

//verifica que se cumplan con todos los parametros para poder enviar una senial coherente
resp_t TreatmentAssertParams (void)
{
    resp_t resp = resp_error;

    if ((treatment_conf.treatment_signal.power > 100) || (treatment_conf.treatment_signal.power < 10))
        return resp;

    if ((treatment_conf.treatment_signal.freq_dec > 99) ||
        (treatment_conf.treatment_signal.freq_int < FREQ_MIN_ALLOWED) ||
        (treatment_conf.treatment_signal.freq_int > FREQ_MAX_ALLOWED))
        return resp;

    if ((treatment_conf.treatment_signal.signal != SQUARE_SIGNAL) &&
        (treatment_conf.treatment_signal.signal != TRIANGULAR_SIGNAL) &&
        (treatment_conf.treatment_signal.signal != SINUSOIDAL_SIGNAL))
        return resp;

    if (!(treatment_conf.channels_in_treatment & CHX_MASK))
        return resp;

    return resp_ok;
}


//--- end of file ---//
