//---------------------------------------------
// ## @Author: Med
// ## @Editor: Emacs - ggtags
// ## @TAGS:   Global
// ## @CPU:    TEST PLATFORM FOR FIRMWARE
// ##
// #### TESTS.C ###############################
//---------------------------------------------

// Includes Modules for tests --------------------------------------------------
#include "comms_from_rasp.h"


#include <stdio.h>
// #include <math.h>

// Types Constants and Macros --------------------------------------------------


// Externals -------------------------------------------------------------------
volatile unsigned short adc_ch [2];
volatile unsigned char usart1_have_data = 0;
unsigned short comms_messages_rpi = 0;

// Globals ---------------------------------------------------------------------


// Module Functions to Test ----------------------------------------------------
void Test_Comm_From_Rasp_Module (void);
void Test_Functions (void);

// Module Auxiliary Functions --------------------------------------------------
void HARD_L1_ON (void);
void HARD_L1_OFF (void);
void Usart1Send (char * s);
unsigned char ReadUsart1Buffer (char * bout, unsigned short max_len);
void BuzzerCommands(unsigned char command, unsigned char multiple);


// Tests Module Auxiliary or General Functions ---------------------------------
void PrintOK (void);
void PrintERR (void);


// Module Functions ------------------------------------------------------------
int main (int argc, char *argv[])
{
    // Test_Functions ();
    Test_Comm_From_Rasp_Module();

    return 0;
}


void Test_Comm_From_Rasp_Module (void)
{
    Raspberry_Messages ("signal triangular");
    
}

void HARD_L1_ON (void)
{
    printf("Led1 -> ON\n");
}

void HARD_L1_OFF (void)
{
    printf("Led1 -> OFF\n");
}

void Usart1Send (char * s)
{
    printf("sended: %s\n", s);
}

void BuzzerCommands(unsigned char command, unsigned char multiple)
{
    printf("buzzer cmd: %d multiple: %d\n", command, multiple);
}

unsigned char ReadUsart1Buffer (char * bout, unsigned short max_len)
{
    return 1;
}


void Test_Functions (void)
{
    printf("tested ok!\n");
    PrintOK();
}


void PrintOK (void)
{
    printf("\033[0;32m");    //green
    printf("OK\n");
    printf("\033[0m");    //reset
}


void PrintERR (void)
{
    printf("\033[0;31m");    //red
    printf("ERR\n");
    printf("\033[0m");    //reset
}
//--- end of file ---//


