/***************************************************************************************************
Notes: 
***************************************************************************************************/
#ifndef RTCLOCK_H_
#define RTCLOCK_H_

/***************************************************************************************************
Structures:
***************************************************************************************************/
typedef struct 
{
    unsigned char thousands;
    unsigned char hundreds;
    unsigned char tens;
    unsigned char ones;
} Digits;

typedef struct 
{
    unsigned char       hours;
    unsigned char     minutes;
    unsigned char     seconds;
    short        milliSeconds;
} Time;


/***************************************************************************************************
Global Variables:
***************************************************************************************************/
extern unsigned char buttonPressed;
extern Time clock;

/***************************************************************************************************
Function Prototpes:
***************************************************************************************************/

/*
    pushbutton_ISR:
        * This routine checks which KEY has been pressed. It writes to HEX0
        * (Example - Given)
*/
void pushbutton_ISR (void);

/*
    TimerISR:
        * TimerISR
*/
void TimerISR(void);

/*
    ClockInit:
        * Initializes clock time to 12:58:00
*/
void ClockInit(void);

/*
    ClockTime:
        * Updates the currentTime
        * Returns 1 every second
*/
unsigned char ClockTime(Time* currentTime);

/*
    DigitSeparator
        * Separates a number into 4 separate digits
*/
Digits DigitSeparator(int number);

/*
    DisplayLEDs:
        * Controls 7-Segment clock display
*/
void DisplayLEDs(Digits hours, Digits minutes, Digits seconds);

/*
    Segments:
        * Causes HEX LEDs to reflect input value
*/
unsigned char Segments(unsigned char number);


#endif /* RTCLOCK_H_ */