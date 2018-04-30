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

struct Monitor RPM_Splitter(long value)
{
    struct Monitor structure;
	structure.iHundred = 0;
	structure.iTen = 0;
	structure.iOne = 0;
	structure.iTotal = 0;

	structure.cHundred = ' ';
	structure.cTen = ' ';
	structure.cOne = ' ';
	structure.cTotal[0] = ' ';
	structure.cTotal[1] = ' ';
	structure.cTotal[2] = ' ';

    structure.iHundred  = (value / 100);
    structure.iTen      = ((value % 100) / 10);
    structure.iOne      = ((value % 100)% 10);
    structure.iTotal	= value;

    return structure;
}

struct Monitor RPM_Characters (struct Monitor structure)
{
	structure.cTotal[0] = GetCharacter(structure.iHundred);
	structure.cTotal[1] = GetCharacter(structure.iTen);
	structure.cTotal[2] = GetCharacter(structure.iOne);
	return structure;
}

//**End of File**//