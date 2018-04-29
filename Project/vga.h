/***********************************************************
	Project:	Lab06
	Company:	CPE 490 Embedded Systems
	Author:		Andrew Davies
	File:		vga.h
	Purpose:	prototypes for vga.c
***********************************************************/

void VGA_box(int, int, int, int, short);
/*****************************************
Description: creates box
Parameters: int first x coordinate
			int first y coordinate
			int second x coordinate
			int second y coordinate
			short RGB color
Returns: None
Actions:
	writes to FPGA_ONCHIP_BASE
Example: VGA_box(59, 149, 261, 166, 0x7804);
*****************************************/
void VGA_text(int, int, char*);
/*****************************************
Description: prints text onto monitor
Parameters: int x coordinate
			int y coordinate
			pointer to array of ascii char
Returns: None
Actions:
	writes to FPGA_CHAR_BASE
Example: VGA_text(37, 35, array);
*****************************************/

//**End of File**//