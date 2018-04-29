#include "encoder.h"
#include "gui.h"
#include "struct.h"


int encoderValue;	//used in isr.c

void GetActualRpm(void)
{
	static char time;
    unsigned int count = 0;
    static int countPerSec[5];
    countPerSec[4] = countPerSec[3];
    countPerSec[3] = countPerSec[2];
    countPerSec[2] = countPerSec[1];
    countPerSec[1] = countPerSec[0];
    countPerSec[0] = encoderValue;

    int i;
    for(i = 0; i <= time; i++)
    {
    	count = count + countPerSec[i];
    }
    actrpm.iTotal = ( (count * (2/3) ) / (time + 1));
    time++;
}

void PrintActualRpm(void)
{
    actrpm = RPM_Splitter(actrpm.iTotal);
    actrpm = RPM_Characters(actrpm);
    if(actrpm.cTotal[0] == '0');
        actrpm.cTotal[0] = ' ';
    ActualRPM_Write(actrpm.cTotal);
}