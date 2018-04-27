/***********************************************************
	Project:	Lab06
	Company:	CPE 490 Embedded Systems
	Author:		Andrew Davies
	File:		vga.c
	Purpose:	functions to interface with a monitor
***********************************************************/
//**Includes**//
#include "vga.h"
#include "address_map.h"
//**Function Code**//
void VGA_box(int x1, int y1, int x2, int y2, short pixel_color)
{
	int pixel_ptr, row, col;

	for (row = y1; row <= y2; row++)		
	{
		for (col = x1; col <= x2; ++col)
		{
			pixel_ptr = FPGA_ONCHIP_BASE + (row << 10) + (col << 1);
			*(short *)pixel_ptr = pixel_color;		// set pixel color
		}
	}
} 

void VGA_text(int x, int y, char* text_ptr)
{
	int offset;
  	volatile char* character_buffer = (char *) FPGA_CHAR_BASE;	// VGA character buffer

	offset = (y << 7) + x;
	while ( *(text_ptr) )
	{
		*(character_buffer + offset) = *(text_ptr);	// write to the character buffer
		++text_ptr;
		++offset;
	}
}