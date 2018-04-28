/***********************************************************
	Project:	Semester Project
	Company:	CPE 490 Embedded Systems
	Author:		Andrew Davies
	File:		keypad.c
	Purpose:	functions to deturmin the key pressed
***********************************************************/

//**Includes**//
#include "keypad.h"
#include "gui.h"
#include "struct.h"
#include "address_map.h"

//**Debugging**//
#include "JTAG_UART.h"

//**Global Variables**//
int keyData;	//used in isr.c
float percent;	//used in isr.c
extern char enterPress;

//**Function Code**//

void Key(void)
{
	char key = GetKey(keyData);

	if(key == 0xD)		//invalid key
		return;

	if( (key != 0xA) && (key != 0xB) && (key != 0xC) )	//is integer
	{
		inprpm.iHundred = inprpm.iTen;
		inprpm.iTen = inprpm.iOne;
		inprpm.iOne = key;
		Total_inprpm();

		inprpm.cHundred = inprpm.cTen;
		inprpm.cTen = inprpm.cOne;
		inprpm.cOne = GetCharacter(key);

		inprpm.cTotal[0] = inprpm.cHundred;
		inprpm.cTotal[1] = inprpm.cTen;
		inprpm.cTotal[2] = inprpm.cOne;

		InputRPM_Write(inprpm.cTotal);
		return;
	}

	if(key == 0xA)			//enter pressed
	{
		if(inprpm.cTotal[2] != ' ')
		{
			enterPress = 1;
			setrpm = inprpm;
			InputRPM_Clear();
			Clear_inprpm();

			if(setrpm.iTotal > 233)
			{
				setrpm.iTotal = 233;
				setrpm.cTotal[0] = '2';
				setrpm.cTotal[1] = '3';
				setrpm.cTotal[2] = '3';
			}
			SetRPM_Write(setrpm.cTotal);
			percent = setrpm.iTotal / (float) 233;
			return;
		}
	}
	/*
	volatile int* GPIOPtr = (int*)JP1_BASE;
	if(key == 0xB)		//forward
	{
		*GPIOPtr &= 0xFFFFFFFB;
		*GPIOPtr |= 0x8;
	}
	if(key == 0xC)		//reverse
	{
		*GPIOPtr &= 0xFFFFFFF7;
		*GPIOPtr |= 0x4;
	}
	*/
}

char GetKey(int keyData)
{
	char key;

	switch(keyData)
	{
		case 0x5A:		//enter
			key = 0xA;
			break;
		case 0xE0:		//enter
			key = 0xA;
			break;
		case 0x70:		//0
			key = 0;
			break;
		case 0x69:		//1
			key = 1;
			break;
		case 0x72:		//2
			key = 2;
			break;
		case 0x7A:		//3
			key = 3;
			break;
		case 0x6B:		//4
			key = 4;
			break;
		case 0x73:		//5
			key = 5;
			break;
		case 0x74:		//6
			key = 6;
			break;
		case 0x6C:		//7
			key = 7;
			break;
		case 0x75:		//8
			key = 8;
			break;
		case 0x7D:		//9
			key = 9;
			break;
		case 0x79:		//+
			key = 0xB;
			break;
		case 0x7B:		//-
			key = 0xC;
			break;
		default:		//invalid
			key = 0xD;
			break;
	}
	return key;
}

//**End of File**//