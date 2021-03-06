/***********************************************************
	Project:	Semester Project
	Company:	CPE 490 Embedded Systems
	Author:		Andrew Davies & John Bugay
	File:		PS2.h
	Purpose:	
***********************************************************/
#include "address_map.h"

extern int keyData;     //declared in keypad.c

void PS2_Read(void)
{
    volatile int* PS2_ptr = (int*) PS2_BASE;
    static char flag = 0;   //holds if release accured
    char waiting = 1;
    int trash = 0;          //holds current PS2 read
    int ravail;             //holds if unread data
  	int rvalid;

    while(waiting == 1)                              //if unread data
    {
        ravail = (*(PS2_ptr) & 0xFFFF0000) >> 16;
        rvalid = (*(PS2_ptr) & 0x8000) >> 15;

        if(ravail == 0)
            return;

    	if(rvalid == 1)
        {
        	trash = *(PS2_ptr) & 0xFF;                //read data
        	if(flag == 1)                               //if flag set
        	{
           		keyData = trash;                          //keep data
            	flag = 0;                                 //clear local flag
                waiting = 0;
        	}
        	if(trash == 0xF0)                           //if date is break code
        	{
            	flag = 1;                                 //set local flag
            	keyData = 0;
        	}
        }
    }
}
