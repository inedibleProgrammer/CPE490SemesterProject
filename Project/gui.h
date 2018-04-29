/***********************************************************
	Project:	Semester Project
	Company:	CPE 490 Embedded Systems
	Author:		Andrew Davies
	File:		gui.h
	Purpose:	prototypes for gui.c
***********************************************************/

//**Prototypes**//
void GUI_Setup(void);

void InputRPM_Write(char*);

void InputRPM_Clear();

void SetRPM_Write(char* value);

void ActualRPM_Write(char* value);

void Current_Write(char* value);

//**End of File**//