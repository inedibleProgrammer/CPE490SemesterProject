/***********************************************************
	Project:	Semester Project
	Company:	CPE 490 Embedded Systems
	Author:		Andrew Davies
	File:		struct.h
	Purpose:	holds global struct externs
***********************************************************/

//**Global Structs**//
extern struct RPM inprpm;
extern struct RPM setrpm;
extern struct RPM actrpm;
extern struct RPM currpm;

//**Struct Definition**//
struct RPM
{
	int iHundred;
	int iTen;
	int iOne;
	int iTotal;

	char cHundred;
	char cTen;
	char cOne;
	char cTotal[3];
};

//**Prototypes**//
char GetCharacter(int);
void Clear_inprpm();
void Total_setrpm(void);
void InitializeStructs(void);