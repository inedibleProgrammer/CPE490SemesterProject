/***************************************************************************************************
Notes: 
***************************************************************************************************/

#include "Keyboard.h"


/***************************************************************************************************
Global Variables:
***************************************************************************************************/
struct Code code;

/***************************************************************************************************
Function Definitions:
***************************************************************************************************/

void PS2ISR(void)
{
    

    volatile int * PS2_ptr = (int *) 0xFF200100;        // PS/2 port address
    int PS2_data, RAVAIL;

    PS2_data = *(PS2_ptr);                              // read the Data register in the PS/2 port
    RAVAIL = (PS2_data & 0xFFFF0000) >> 16;             // extract the RAVAIL field
    if (RAVAIL > 0)
    {
        /* always save the last three bytes received */
        code.byte1 = code.byte2;
        code.byte2 = code.byte3;
        code.byte3 = PS2_data & 0xFF;
    }

    code.word = ( (code.byte1 << 16) | (code.byte2 << 8) | (code.byte3) );
}

unsigned char CodeLookup(void)
{
    static const int codes[] = 
    {
        0x0070F070, // KP 0
        0x0069F069, // KP 1
        0x0072F072, // KP 2
        0x007AF07A, // KP 3
        0x006BF06B, // KP 4
        0x0073F073, // KP 5
        0x0074F074, // KP 6
        0x006CF06C, // KP 7
        0x0075F075, // KP 8
        0x007DF07D, // KP 9
        0x005AF05A, // ENTER i 10
        0x00E0F05A, // KP EN i 11
    };

    int i = 0;
    for(i; i < 12; i++)
    {
        if(code.word == codes[i])
        {
            code.word = 0x00;
            return i;
        }
    }
    return 100;
}

/*
JUNK
{
            put_jtag( GetDigit( ((code.byte1) & 0xF0) >> 4) );
            put_jtag( GetDigit( (code.byte1) & 0x0F ) );
            put_jtag( GetDigit( ((code.byte2) & 0xF0) >> 4) );
            put_jtag( GetDigit( (code.byte2) & 0x0F ) );
            put_jtag( GetDigit( ((code.byte3) & 0xF0) >> 4) );
            put_jtag( GetDigit( (code.byte3) & 0x0F ) );
            put_jtag('\n');

}
ENDJUNK
*/