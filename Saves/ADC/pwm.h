/***************************************************************************************************
Notes: 
***************************************************************************************************/
#ifndef PWM_H_
#define PWM_H_

/***************************************************************************************************
Global Variables:
***************************************************************************************************/
extern double PWMLength;
extern double percentage;

/***************************************************************************************************
Function Prototypes:
***************************************************************************************************/

/*
    SetPWM:
        * Period:  Length of period in microseconds
        * Percent: Percent of time the PWM signal is on out of the period time
            * Controlled by Switch value
*/
void SetPWM(unsigned int period, double percent);
void PWM_Setup(void);

#endif /* PWM_H_ */