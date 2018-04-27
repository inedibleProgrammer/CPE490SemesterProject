/***************************************************************************************************
Notes: 
***************************************************************************************************/

#include "RTClock.h"
#include "JTAG_UART.h"

/***************************************************************************************************
Global Variables:
***************************************************************************************************/
unsigned char buttonPressed;
Time clock;

/***************************************************************************************************
Function Definitions:
***************************************************************************************************/
void pushbutton_ISR( void )
{
    volatile int * KEY_ptr = (int *) 0xFF200050;  // pushbutton KEY base address
    int press;

    // Global Variable buttonPressed
    buttonPressed = 1;

    press = *(KEY_ptr + 3); // read the pushbutton interrupt register
    *(KEY_ptr + 3) = press; // clear the interrupt
}

void TimerISR( void )
{
    unsigned char secondFlag = 0;

    secondFlag = ClockTime(&clock); // return 1 every second

    // Separate each value into digits
    Digits Hours        = DigitSeparator(clock.hours);
    Digits Minutes      = DigitSeparator(clock.minutes);
    Digits Seconds      = DigitSeparator(clock.seconds);
    Digits Milliseconds = DigitSeparator(clock.milliSeconds);

    if( secondFlag ) // update display every second
    {
        DisplayLEDs(Hours, Minutes, Seconds);
    }

    if(buttonPressed)
    {
        put_jtag(GetDigit(Hours.tens));
        put_jtag(GetDigit(Hours.ones));

        put_jtag(':');

        put_jtag(GetDigit(Minutes.tens));
        put_jtag(GetDigit(Minutes.ones));

        put_jtag(':');

        put_jtag(GetDigit(Seconds.tens));
        put_jtag(GetDigit(Seconds.ones));

        put_jtag(':');

        put_jtag(GetDigit(Milliseconds.hundreds));
        put_jtag(GetDigit(Milliseconds.tens));
        put_jtag(GetDigit(Milliseconds.ones));
        put_jtag('\n');
        buttonPressed = 0;
    }
}

void ClockInit(void)
{
    clock.hours   = 1;
    clock.minutes = 8;
}

unsigned char ClockTime(Time* currentTime)
{
    unsigned char secondFlag = 0;

    currentTime->milliSeconds++; // Increment every millisecond

    if(currentTime->milliSeconds == 1000) // Increment every second
    {
        currentTime->seconds++;
        currentTime->milliSeconds = 0;
        secondFlag = 1;
    }

    if(currentTime->seconds == 60) // Increment every minute
    {
        currentTime->minutes++;
        currentTime->seconds = 0;
    }

    if(currentTime->minutes == 60) // Increment every hour
    {
        currentTime->hours++;
        currentTime->minutes = 0;
    }

    if(currentTime->hours == 24) // Roll hours over
    {
        currentTime->hours = 0;
    }

    return secondFlag;
}

Digits DigitSeparator(int number)
{
    Digits numberSeparated;

    numberSeparated.thousands = number / 1000;
    numberSeparated.hundreds  = (number % 1000) / 100;
    numberSeparated.tens      = ((number % 1000) % 100) / 10;
    numberSeparated.ones      = (((number % 1000) % 100) % 10);

    return numberSeparated;
}

void DisplayLEDs(Digits hours, Digits minutes, Digits seconds)
{
    volatile int* HourSegment   = (int*) 0xFF200030;
    volatile int* MinuteSegment = (int*) 0xFF200020;

    short HourWord = 0;
    int MinuteWord = 0; // Includes seconds

    HourWord |= ( Segments(hours.tens) << 8);
    HourWord |= ( Segments(hours.ones) );

    *(HourSegment) = HourWord;

    MinuteWord |= ( Segments(minutes.tens) << 24 );
    MinuteWord |= ( Segments(minutes.ones) << 16 );

    MinuteWord |= ( Segments(seconds.tens) << 8 );
    MinuteWord |= ( Segments(seconds.ones) );

    *(MinuteSegment) = MinuteWord;
}

unsigned char Segments(unsigned char number)
{
    unsigned char segments;

    switch(number)
    {
        case 0:
            segments = 0b00111111;
            break;
        case 1:
            segments = 0b00000110;
            break;
        case 2:
            segments = 0b01011011;
            break;
        case 3:
            segments = 0b01001111;
            break;
        case 4:
            segments = 0b01100110;
            break;
        case 5:
            segments = 0b01101101;
            break;
        case 6:
            segments = 0b01111101;
            break;
        case 7:
            segments = 0b00000111;
            break;
        case 8:
            segments = 0b01111111;
            break;
        case 9:
            segments = 0b01101111;
            break;
    }
    return segments;
}
