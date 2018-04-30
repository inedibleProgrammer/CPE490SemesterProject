/***********************************************************
	Project:	Semester Project
	Company:	CPE 490 Embedded Systems
	Author:		Andrew Davies
	File:		struct.h
	Purpose:	holds global struct externs
***********************************************************/

//**Global Structs**//
extern struct Monitor inprpm;
extern struct Monitor setrpm;
extern struct Monitor actrpm;
extern struct Monitor current;

//**Struct Definition**//
struct Monitor
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
void Total_inprpm(void);
void InitializeStructs(void);
struct Monitor RPM_Splitter(long value);
struct Monitor RPM_Characters (struct Monitor);

//**End of File**//