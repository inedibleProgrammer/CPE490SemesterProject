/***********************************************************
	Project:	Semester Project
	Company:	CPE 490 Embedded Systems
	Author:		Andrew Davies
	File:		gui.c
	Purpose:	functions to create the GUI
***********************************************************/
//**Includes**//
#include "gui.h"
#include "vga.h"

//**Defines**//
#define Navy			0x0010
#define MutedNavy		0x528E
#define MarsalaWine		0x8124
#define Aubergine		0x61EA
#define MetallicGold	0xD567
#define Eggplant		0x310A
#define Burgandy		0x7804

//**Function Code**//
void GUI_Setup(void)
{
	VGA_box(0, 0, 319, 239, MutedNavy);				//background
	VGA_box(59, 149, 261, 166, MetallicGold);		//bar's border
	VGA_box(60, 150, 260, 165, Burgandy);			//bar's background

	char input[40] = "RPM Input:";
	VGA_text(10, 10, input);
	char set[40] = "Set RPM:";
	VGA_text(12, 13, set);
	char actual[40] = "Actual RPM:";
	VGA_text(9, 16, actual);
	char current[40] = "Current:";
	VGA_text(12, 19, current);
}

void Print_Bars(int value)
{
	float percent = ((value / (float) 233));
	int size = (200 * percent);								//turn percent into number of pixels
	int inverseSize = 200 - size;							//get the negative size
	VGA_box(260 - inverseSize, 150, 260, 165, Aubergine);	//print negative bar
	VGA_box(60, 150, 60 + size, 165, Burgandy);				//print progress bar
	if(percent == 0)											//if the total is zero
		VGA_box(60, 150, 60, 165, Aubergine);					//clear lowest end of progress bar
}

void InputRPM_Write(char* value)
{
	VGA_text(21, 10, value);
	char rpm[40] = "RPM";
	VGA_text(25, 10, rpm);
}

void InputRPM_Clear()
{
	char clear[40] = "       ";
	VGA_text(21, 10, clear);
}

void SetRPM_Write(char* value)
{
	VGA_text(21, 13, value);
	char rpm[40] = "RPM";
	VGA_text(25, 13, rpm);
}

void ActualRPM_Write(char* value)
{
	VGA_text(21, 16, value);
	char rpm[40] = " RPM";
	VGA_text(24, 16, rpm);
}

void Current_Write(char* value)
{
	VGA_text(21, 19, value);
	char miliAmps[40] = "mA";
	VGA_text(25, 19, miliAmps);
}

//**End of File**//
