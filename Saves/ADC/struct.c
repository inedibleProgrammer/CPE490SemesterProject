/***********************************************************
	Project:	Semester Project
	Company:	CPE 490 Embedded Systems
	Author:		Andrew Davies
	File:		struct.c
	Purpose:	holds struct definitions and globals
***********************************************************/

//**Includes**//
#include "struct.h"

//**Global Structs**//
struct Monitor inprpm;
struct Monitor setrpm;
struct Monitor actrpm;
struct Monitor current;


char GetCharacter(int key)
{
	const int array[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
	char ckey = array[key];
	return ckey;
}

void Clear_inprpm(void)
{
	inprpm.iHundred = 0;
	inprpm.iTen = 0;
	inprpm.iOne = 0;
	inprpm.iTotal = 0;

	inprpm.cHundred = ' ';
	inprpm.cTen = ' ';
	inprpm.cOne = ' ';
	inprpm.cTotal[0] = ' ';
	inprpm.cTotal[1] = ' ';
	inprpm.cTotal[2] = ' ';
}

void Total_inprpm(void)
{
	int hundred = inprpm.iHundred;
	int ten = inprpm.iTen;

	hundred = inprpm.iHundred * 100;
	ten = inprpm.iTen * 10;
	inprpm.iTotal = hundred + ten + inprpm.iOne;
}

//**Function Code**//
void InitializeStructs(void)
{
	inprpm.iHundred = 0;
	inprpm.iTen = 0;
	inprpm.iOne = 0;
	inprpm.iTotal = 0;

	inprpm.cHundred = ' ';
	inprpm.cTen = ' ';
	inprpm.cOne = ' ';
	inprpm.cTotal[0] = ' ';
	inprpm.cTotal[1] = ' ';
	inprpm.cTotal[2] = ' ';

	setrpm = inprpm;
	actrpm = inprpm;
}

//**End of File**//