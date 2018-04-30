#include "encoder.h"
#include "gui.h"
#include "struct.h"
#include "Numbers.h"
#include "JTAG_UART.h"


// int encoderValue;	//used in isr.c

void GetActualRpm(void)
{

}

void PrintActualRpm(void)
{
    actrpm = RPM_Splitter(actrpm.iTotal);
    actrpm = RPM_Characters(actrpm);
/*
        struct Digits actual;
        actual = DigitSeparator(actrpm.iTotal);
        
        put_jtag('A');
        put_jtag('c');
        put_jtag('t');
        put_jtag('u');
        put_jtag('a');
        put_jtag('l');
        put_jtag(':');
        put_jtag(' ');

        put_jtag(GetDigit(actual.thousands));
        put_jtag(GetDigit(actual.hundreds));
        put_jtag(GetDigit(actual.tens));
        put_jtag(GetDigit(actual.ones));
        put_jtag('\n');
        put_jtag('\n');
*/
    // if(actrpm.cTotal[0] == '0');
       // actrpm.cTotal[0] = ' ';
    ActualRPM_Write(actrpm.cTotal);
}

/*
    /*
    static char time;
    static unsigned int longTime;
    static int test;
    unsigned int count = 0;
    static int countPerSec[5];
    //countPerSec[4] = countPerSec[3];
    //countPerSec[3] = countPerSec[2];
    //countPerSec[2] = countPerSec[1];
    countPerSec[1] = countPerSec[0];
    countPerSec[0] = encoderValue;

    longTime = longTime + encoderValue;
    encoderValue = 0;
    test++;
    if(test == 10)
    {
        test = 0;
        struct Digits test;
        test = DigitSeparator(longTime);
        
        put_jtag('t');
        put_jtag('e');
        put_jtag('s');
        put_jtag('t');
        put_jtag(':');
        put_jtag(' ');

        put_jtag(GetDigit(test.thousands));
        put_jtag(GetDigit(test.hundreds));
        put_jtag(GetDigit(test.tens));
        put_jtag(GetDigit(test.ones));
        put_jtag('\n');
        longTime = 0;
    }
/*
        struct Digits counts0;
        struct Digits counts1;

        counts0 = DigitSeparator(countPerSec[0]);
        counts1 = DigitSeparator(countPerSec[1]);
        
        put_jtag('c');
        put_jtag('o');
        put_jtag('u');
        put_jtag('n');
        put_jtag('t');
        put_jtag('0');
        put_jtag(':');
        put_jtag(' ');

        put_jtag(GetDigit(counts0.thousands));
        put_jtag(GetDigit(counts0.hundreds));
        put_jtag(GetDigit(counts0.tens));
        put_jtag(GetDigit(counts0.ones));
        put_jtag('\n');

        //Current:
        put_jtag('c');
        put_jtag('o');
        put_jtag('u');
        put_jtag('n');
        put_jtag('t');
        put_jtag('1');
        put_jtag(':');
        put_jtag(' ');
        put_jtag(GetDigit(counts1.thousands));
        put_jtag(GetDigit(counts1.hundreds));
        put_jtag(GetDigit(counts1.tens));
        put_jtag(GetDigit(counts1.ones));
        put_jtag('\n');
        put_jtag('\n');
*/

    /*
    int i;
    for(i = 0; i <= time; i++)
    {
        count = count + countPerSec[i];
    }
    actrpm.iTotal = ( (count * (2.0/3.0) ) / (time + 1.0));
    count = 0;
    time++;
    if(time > 1)
    {
        time = 1;
    }
    */

//**End of File**//