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
struct RPM inprpm;
struct RPM setrpm;
struct RPM actrpm;

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
char GetCharacter(int key)
{
	const int array[9] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
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
	inprpm.iHundred = inprpm.iHundred * 100;
	inprpm.iTen = inprpm.iTen * 10;
	inprpm.iTotal = inprpm.iHundred + inprpm.iTen + inprpm.iOne;
}

void Total_setrpm(void)
{
	setrpm.iHundred = setrpm.iHundred * 100;
	setrpm.iTen = setrpm.iTen * 10;
	setrpm.iTotal = setrpm.iHundred + setrpm.iTen + setrpm.iOne;
}