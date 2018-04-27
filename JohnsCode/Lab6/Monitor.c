#include "Monitor.h"
#include "Constants.h"

/***************************************************************************************************
Global Variables:
***************************************************************************************************/

/***************************************************************************************************
Function Definitions:
***************************************************************************************************/
void VGA_text (struct CoordinatesChar* coordinatesChar)
{
    int offset;
    volatile char * character_buffer = (char *) FPGA_CHAR_BASE; // VGA character buffer

    char* text_ptr = &( coordinatesChar->string[0] );

    /* assume that the text string fits on one line */
    offset = (coordinatesChar->y << 7) + coordinatesChar->x;
    while ( *(text_ptr) )
    {
        *(character_buffer + offset) = *(text_ptr); // write to the character buffer
        ++text_ptr;
        ++offset;
    }
}

void VGA_box(struct Coordinates* coordinates)
{
    int pixel_ptr, row, col;

    /* assume that the box coordinates are valid */
    for (row = coordinates->y1; row <= coordinates->y2; row++)
    {
        for (col = coordinates->x1; col <= coordinates->x2; ++col)
        {
            pixel_ptr = FPGA_ONCHIP_BASE + (row << 10) + (col << 1);
            *(short *)pixel_ptr = coordinates->color;      // compute halfword address, set pixel
        }
    }
}



/*void VGA_box(int x1, int y1, int x2, int y2, short pixel_color)
{
    int pixel_ptr, row, col;

    
    for (row = y1; row <= y2; row++)
    {
        for (col = x1; col <= x2; ++col)
        {
            pixel_ptr = FPGA_ONCHIP_BASE + (row << 10) + (col << 1);
            *(short *)pixel_ptr = pixel_color;    
        }
    }
}*/

/*
#include <stdio.h>

struct Coordinate
{
    int x;
    int y;
};

void function(struct Coordinate* value)
{
    (value->x)++;
}

int main()
{
    struct Coordinate coordinate, *coordinatePtr = &coordinate;
    
    coordinate.x = 0;
    coordinate.y = 0;
    
    function(coordinatePtr);
    
    printf("Value: %i", coordinate.x);
}


#include <stdio.h>

struct Fraction
{
    int quotient;
    int divisor;
    int remainder;
};

int main()
{
    struct Fraction percent;
    
    percent.quotient = (177 * 100) / 1023;
    percent.remainder = (177 * 100) % 1023;
    
    printf("Remainder: %i\n", percent.quotient);
    printf("Remainder: %i", percent.remainder);

    return 0;
}

void VGA_text(int x, int y, char * text_ptr)
{
    int offset;
    volatile char * character_buffer = (char *) FPGA_CHAR_BASE; // VGA character buffer

    // assume that the text string fits on one line 
    offset = (y << 7) + x;
    while ( *(text_ptr) )
    {
        *(character_buffer + offset) = *(text_ptr); // write to the character buffer
        ++text_ptr;
        ++offset;
    }
}

*/

/*
#include <stdio.h>

struct Digits
{
    unsigned char thousands;
    unsigned char hundreds;
    unsigned char tens;
    unsigned char ones;
};

struct FractionalNumber
{
    int quotient;
    int divisor;
    int remainder;
};

struct Digits DigitSeparator(int number)
{
    struct Digits numberSeparated;

    numberSeparated.thousands = number / 1000;
    numberSeparated.hundreds  = (number % 1000) / 100;
    numberSeparated.tens      = ((number % 1000) % 100) / 10;
    numberSeparated.ones      = (((number % 1000) % 100) % 10);

    return numberSeparated;
}

struct FractionalNumber SwitchPercent(void)
{
    // volatile int* switchPtr = (int*)(SW_BASE);

    struct FractionalNumber percent;

    percent.divisor = 1023;
    percent.quotient = ( (177) * 100 ) / percent.divisor;
    percent.remainder = ( (177) * 100 ) % percent.divisor;

    return percent;
}

int main()
{
    struct FractionalNumber percent;
    struct Digits percentSeparated;
    
    percent = SwitchPercent();
    percentSeparated = DigitSeparator(percent.quotient);
    
    printf("%i%i%i%i.%i", percentSeparated.thousands, percentSeparated.hundreds, percentSeparated.tens, percentSeparated.ones, (percent.remainder * 10) / percent.divisor );

    return 0;
}

*/

/*

#include <stdio.h>

struct Digits
{
    unsigned char thousands;
    unsigned char hundreds;
    unsigned char tens;
    unsigned char ones;
};

struct FractionalNumber
{
    int quotient;
    int divisor;
    int remainder;
    float fraction;
};

struct Digits DigitSeparator(int number)
{
    struct Digits numberSeparated;

    numberSeparated.thousands = number / 1000;
    numberSeparated.hundreds  = (number % 1000) / 100;
    numberSeparated.tens      = ((number % 1000) % 100) / 10;
    numberSeparated.ones      = (((number % 1000) % 100) % 10);

    return numberSeparated;
}

struct FractionalNumber SwitchPercent(void)
{
    // volatile int* switchPtr = (int*)(SW_BASE);
    int x = 183;

    struct FractionalNumber percent;

    percent.divisor = 1023;
    percent.quotient = ( (x) * 100 ) / percent.divisor;
    percent.remainder = ( (x) * 100 ) % percent.divisor;
    percent.fraction = ( (float)(percent.remainder) ) / ( (float)(percent.divisor) );

    return percent;
}

int main()
{
    struct Digits percentSeparated;
    
    double percentFraction = 0.0;
    int percentInt = 0;
    
    int x2 = 0;
    
    percentFraction = (183 / (float)1023) * 100 + 0.05;
    percentInt = percentFraction; // convert to an int
    percentFraction = percentFraction - percentInt;
    
    percentSeparated = DigitSeparator(percentInt);
    
    x2 = (percentFraction * 2) + 60;
    
    printf("Pixel: %i\n", x2);
    printf("percentFraction: %f\n", percentFraction);
    printf("percentInt: %i\n", percentInt);
    
    printf("--------\n");
    
    printf("%i%i%i.%i", percentSeparated.hundreds, percentSeparated.tens, percentSeparated.ones, (int)(percentFraction * 10));
    
    
   
    return 0;
}


*/