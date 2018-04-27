/***************************************************************************************************
Notes:
    Name:       Tyler Beine
    Date:       3/25/2018
    Project:    CPE 490 Lab 5
***************************************************************************************************/
#include "address_map_arm.h"

/***************************************************************************************************
Program Start:
***************************************************************************************************/

//methods to use
int getKeyboardValue();
void DisplayKeyboard();
unsigned char Segments(unsigned char number);


//variables to use
int position;	
int pos1=0;
int pos2=0;
int pos3=0;
int pos4=0;
int pos5=0;
int pos6=0;

int main(void)
{
	volatile int * PS2_ptr = (int *) 0xFF200100;
	int PS2_data, RVALID;
	
	PS2_data=*(PS2_ptr);
	RVALID = PS2_data & 0x8000;
	
	position = 1;
	pos1=0;
	pos2=0;
	pos3=0;
	pos4=0;
	pos5=0;
	pos6=0;
	
while(1){	
//read the data register for the break code
PS2_data=*(PS2_ptr);
	RVALID = PS2_data & 0x8000;
	
	if(RVALID){
		//check if key was pressed
		if ((PS2_data & 0xFF) == 0xF0){
			//output the value if it was pressed
			DisplayKeyboard(getKeyboardValue());
		}
	}
}
}

int /* keypadValue */ getKeyboardValue(){
	
	//initialize the PS2 
	volatile int value = 0;
	
	volatile int * PS2_ptr = (int *) 0xFF200100;
	int PS2_data, RVALID;
	
	PS2_data=*(PS2_ptr);
	// RVALID = PS2_data & 0x8000;
	
	//read the data register for the break code
	value = PS2_data & 0xFF;

	while (value == 0xF0){
		PS2_data=*(PS2_ptr);
		value = PS2_data & 0xFF;
	}


	//check if enter was pressed
	if (value == 0x5A){
		position = 99;
		
	}
	
	//return the appropriate int value
	if (value == 0x70){
		return 0;
	}
	else if (value == 0x69){
		return 1;
	}
	else if (value == 0x72){
		return 2;
	}
	else if (value == 0x7A){
		return 3;
	}
	else if (value == 0x6B){
		return 4;
	}
	else if (value == 0x73){
		return 5;
	}
	else if (value == 0x74){
		return 6;
	}
	else if (value == 0x6C){
		return 7;
	}
	else if (value == 0x75){
		return 8;
	}
	else if (value == 0x7D){
		return 9;
	}
	return 567;
}

void DisplayKeyboard(int keypadValue)
{
    volatile int* upperSegment   = (int*) HEX5_HEX4_BASE;
    volatile int* lowerSegment = (int*) HEX3_HEX0_BASE;

    short upper = 0; //top 2 digits
    int lower = 0; // bottom 4 digits

	if (position == 99){
		position = 1;
		upper |= ( Segments (pos6) << 8);
		upper |= ( Segments (pos5) );
		lower|= ( Segments (pos4) << 24);
		lower |= ( Segments (pos3) << 16);
		lower |= ( Segments (pos2) << 8);
		lower |= ( Segments (pos1) );
		pos1=0; 
		pos2=0; 
		pos3=0; 
		pos4=0; 
		pos5=0; 
		pos6=0; 
	}
	else if (keypadValue==567){
		upper |= ( Segments (pos6) << 8);
		upper |= ( Segments (pos5) );
		lower|= ( Segments (pos4) << 24);
		lower |= ( Segments (pos3) << 16);
		lower |= ( Segments (pos2) << 8);
		lower |= ( Segments (pos1) );
	}
	
	
	//check which postion to write to then write the value to it
	else if(position==1){
		position = position + 1;
		pos1 = keypadValue;
		upper |= ( Segments (pos6) << 8);
		upper |= ( Segments (pos5) );
		lower|= ( Segments (pos4) << 24);
		lower |= ( Segments (pos3) << 16);
		lower |= ( Segments (pos2) << 8);
		lower |= ( Segments (pos1));
	}
	else if (position == 2){
		position = position + 1;
		pos2=pos1;
		pos1 = keypadValue;
		upper |= ( Segments (pos6) << 8);
		upper |= ( Segments (pos5) );
		lower|= ( Segments (pos4) << 24);
		lower |= ( Segments (pos3) << 16);
		lower |= ( Segments (pos2) << 8);
		lower |= ( Segments (pos1));
	}
	else if (position == 3){
		position = position + 1;
		pos3=pos2;
		pos2=pos1;
		pos1 = keypadValue;
		upper |= ( Segments (pos6) << 8);
		upper |= ( Segments (pos5) );
		lower|= ( Segments (pos4) << 24);
		lower |= ( Segments (pos3) << 16);
		lower |= ( Segments (pos2) << 8);
		lower |= ( Segments (pos1));
	}
	else if (position == 4){
		position = position + 1;
		pos4=pos3;
		pos3=pos2;
		pos2=pos1;
		pos1 = keypadValue;
		upper |= ( Segments (pos6) << 8);
		upper |= ( Segments (pos5) );
		lower|= ( Segments (pos4) << 24);
		lower |= ( Segments (pos3) << 16);
		lower |= ( Segments (pos2) << 8);
		lower |= ( Segments (pos1));
	}
	else if (position == 5){
		position = position + 1;
		pos5=pos4;
		pos4=pos3;
		pos3=pos2;
		pos2=pos1;
		pos1 = keypadValue;
		upper |= ( Segments (pos6) << 8);
		upper |= ( Segments (pos5) );
		lower|= ( Segments (pos4) << 24);
		lower |= ( Segments (pos3) << 16);
		lower |= ( Segments (pos2) << 8);
		lower |= ( Segments (pos1));
	}
	else if (position == 6){
		position = position + 1;
		pos6=pos5;
		pos5=pos4;
		pos4=pos3;
		pos3=pos2;
		pos2=pos1;
		pos1 = keypadValue;
		upper |= ( Segments (pos6) << 8);
		upper |= ( Segments (pos5) );
		lower|= ( Segments (pos4) << 24);
		lower |= ( Segments (pos3) << 16);
		lower |= ( Segments (pos2) << 8);
		lower |= ( Segments (pos1));
	}
	else{
		upper |= ( Segments (pos5) << 8);
		pos6=pos5;
		upper |= ( Segments (pos4) );
		pos5=pos4;
		lower|= ( Segments (pos3) << 24);
		pos4=pos3;
		lower |= ( Segments (pos2) << 16);
		pos3=pos2;
		lower |= ( Segments (pos1) << 8);
		pos2=pos1;
		lower |= ( Segments (keypadValue) );
		pos1 = keypadValue;
	}
	
    *(upperSegment) = upper;
    *(lowerSegment) = lower;
}


unsigned char Segments(unsigned char number)
{
    unsigned char segments;

    switch(number)
    {
        case 0:
            segments = 0b00111111;
            break;
        case 1:
            segments = 0b00000110;
            break;
        case 2:
            segments = 0b01011011;
            break;
        case 3:
            segments = 0b01001111;
            break;
        case 4:
            segments = 0b01100110;
            break;
        case 5:
            segments = 0b01101101;
            break;
        case 6:
            segments = 0b01111101;
            break;
        case 7:
            segments = 0b00000111;
            break;
        case 8:
            segments = 0b01111111;
            break;
        case 9:
            segments = 0b01101111;
            break;
		case 99:
			segments = 0b00000000;
    }
    return segments;
}



