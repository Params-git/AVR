/*
 * Interfacing_with_GLCD.c
 *
 * Created: 4/26/2021 1:00:03 PM
 * Author : Paramjeet singh
 */ 

#define F_CPU 8000000UL

#include <inttypes.h>
#include <avr/io.h>
#include <string.h>
#include <util/delay.h>

#include "ks0108.h"
#include "arial_bold_14.h"
#include "glcd.h"
#include "graph.h"
#include "SC.h"
#include "font12x16.h"
#include "corsiva_12.h"


int main(void)
{
	ks0108Init(0);
	glcd_clear();
	/*ks0108DrawRect(0,0,127,63,BLACK); //Rec*/
	
	ks0108SelectFont(&font12x16,ks0108ReadFontData,BLACK);
	ks0108GotoXY(2,2); //X,Y
	ks0108Puts("font 1");
	ks0108DrawLine(0,8,127,8,BLACK); //Horizontal
	
	ks0108SelectFont(&SmallHollows,ks0108ReadFontData,BLACK);
	ks0108GotoXY(2,10);
	ks0108Puts("font 2");
	ks0108DrawLine(0,18,127,18,BLACK); //Horizontal
	
	ks0108SelectFont(&Corsiva_12,ks0108ReadFontData,BLACK);
	ks0108GotoXY(2,20);
	ks0108Puts("font 3");
	ks0108DrawLine(0,32,127,32,BLACK); //Horizontal
	
}


