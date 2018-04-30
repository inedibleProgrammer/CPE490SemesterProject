/***********************************************************
	Project:	Semester Project
	Company:	CPE 490 Embedded Systems
	Author:		Andrew Davies & John Bugay
	File:		main.c
	Purpose:	main program code
***********************************************************/

#define PGAIN 0.1
#define IGAIN 0.5

//**Inlcudes**//
#include "gui.h"
#include "keypad.h"
#include "interrupt.h"
#include "JTAG_UART.h"
#include "ps2.h"
#include "isr.h"
#include "pwm.h"
#include "adc.h"
#include "encoder.h"
#include "struct.h"
#include "pid.h"

//**Prototype**//

typedef struct
{
    double iState; // Integrator state
    double iMax;
    double iMin; 
    double iGain;
    double pGain;
} SPid;

double UpdatePID(SPid * pid, double error);

//**Global Variables**//
int ps2Interrupt;		//used in isr.c
int encoderInterrupt;	//used in isr.c
int monitorInterrupt;	//used in isr.c
int adcInterrupt;       //used in isr.c
int pidInterrupt;       //used in isr.c
int encoderValue;       //used in isr.c

int goodKey;			//used in ps2.c
char enterPress;		//used in keypad.c

//**Program Code**//


int main(void)
{
	//**Initialize Interrupts**//
	disable_A9_interrupts();
	set_A9_IRQ_stack();
	config_GIC();
	configInterupt();
	enable_A9_interrupts();

	//**Initialize GUI**//
	GUI_Setup();

	//**Initialize Structs**//
	InitializeStructs();

    //GPIO
    volatile int* GPIOPtr = (int*)0xFF200060;
    *(GPIOPtr + 1) |= (1 << 0); // Set D0 as output

    // PID
    SPid pidObj = {0.0, (100.0 / IGAIN), (-100.0 / IGAIN), IGAIN, PGAIN};

    /*
    pidObj.iState = 0.0;
    pidObj.pGain = 0.1;
    pidObj.iGain = 0.5;
    pidObj.iMin = (-100.0 / iGain);
    pidObj.iMax = (100.0 / iGain);
    */
    double error = 0.0;
	
	while(1)
	{
        /*******************************************************************************************
        PID:
        *******************************************************************************************/
        if(pidInterrupt == 1)
        {
            actrpm.iTotal = ( (encoderValue / 0.1) * 2/3 );
            encoderValue = 0;

            error = ( (inprpm.iTotal - actrpm.iTotal) / (233) ) * 100;

            actrpm.iTotal = UpdatePID(&pidObj, error);

            PrintActualRpm();

            pidInterrupt = 0;
        }

        /*******************************************************************************************
        KEYBOARD:
        *******************************************************************************************/
		if(ps2Interrupt == 1)
		{
			ps2Interrupt = 0;
          	PS2_Read();

          	if(goodKey == 1)
            {
              	Key();
                goodKey = 0;
            }
		}

        /*******************************************************************************************
        MONITOR:
        *******************************************************************************************/
		if(monitorInterrupt == 1)
		{
			monitorInterrupt = 0;
			//Print_Bars(actrpm.iTotal);
		}

        /*******************************************************************************************
        ENCODER:
        *******************************************************************************************/
		if(encoderInterrupt == 1)
		{
			encoderInterrupt = 0;
			GetActualRpm();
			

		}

        /*******************************************************************************************
        ADC:
        *******************************************************************************************/
        if(adcInterrupt == 1)
        {
            adcInterrupt = 0; // disable flag
            ADC_Get();
        }
	}

	int _end_ = 0;
  	return _end_;
}

double UpdatePID(SPid * pid, double error)
{
    double pTerm, iTerm;
    pTerm = pid->pGain * error; // calculate the proportional term
    // calculate the integral state with appropriate limiting
    pid->iState += error;
    if (pid->iState > pid->iMax) pid->iState = pid->iMax;
    else if (pid->iState < pid->iMin) pid->iState = pid->iMin;
    iTerm = pid->iGain * pid->iState; // calculate the integral term
    return pTerm + iTerm;
}

//**End of File**//