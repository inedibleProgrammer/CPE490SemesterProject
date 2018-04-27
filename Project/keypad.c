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

//**Global Variables**//
int keyData;	//used int isr.c
extern char enterPress;

//**Function Code**//

void Key(void)
{
	char key = GetKey(keyData);
	if(key == 0xB)
		return;

	if(key != 0xA)
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
	}

	if(key == 0xA)
	{
		if(inprpm.cTotal[2] != ' ')
		{
			enterPress = 1;
			setrpm = inprpm;
			InputRPM_Clear();
			Clear_inprpm();
			Total_setrpm();
			if(setrpm.iTotal > 230)
			{
				setrpm.iTotal = 230;
				setrpm.cTotal[0] = '2';
				setrpm.cTotal[1] = '3';
				setrpm.cTotal[2] = '0';
			}
			SetRPM_Write(setrpm.cTotal);
		}

	}
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
		default:		//invalid
			key = 0xB;
			break;
	}
	return key;
}