/***********************************************************
    Project:    Semester Project
    Company:    CPE 490 Embedded Systems
    Author:     Andrew Davies
    File:       isr.c
    Purpose:    holds interrupt service routines
***********************************************************/
//**Includes**//
#include "isr.h"
#include "address_map.h"

//**Global Valiables**//
extern int ps2interrupt;    //declared in main.c
extern int keyData;         //declared in key.c

//**Funtion Code**//
void PS2ISR(void)
{
    volatile int* PS2_ptr = (int*) PS2_BASE;
    static char flag = 0;   //holds if release accured
    int trash = 0;          //holds current PS2 read
    int ravail;             //holds if unread data

    ravail = (*(PS2_ptr) & 0xFFFF0000) >> 16;   

    if(ravail > 0)                              //if unread data
    {
        trash = *(PS2_ptr) & 0xFF;                //read data
        if(flag == 1)                               //if flag set
        {
            keyData = trash;                           //keep data
            ps2interrupt = 1;                         //set global flag
            flag = 0;                                 //clear local flag
        }
        if(trash == 0xF0)                           //if date is break code
        {
            flag = 1;                                 //set local flag
            keyData = 0;
        }
    }
}