//////////////////////////////////////////////////////////////////////
// Simple consol print demo
// -- dovoto
//////////////////////////////////////////////////////////////////////

#include <NDS/NDS.h>

#include <NDS/ARM9/console.h> //basic print funcionality


//make file automaticaly makes a header file for access
//to the binary data in any file ending in .bin that is in 
//the data folder.  It also links in that data to your project

#include "drunkenlogo.h"
#include "palette.h"

void WaitForVblank()
{
	while(DISP_Y!=192);
	while(DISP_Y==192);
}

int main(void)
{
    //set the mode for 2 text layers and two extended background layers
	videoSetMode(MODE_5_2D | DISPLAY_BG3_ACTIVE); 
	
	//set the sub background up for text display (we could just print to one
	//of the main display text backgrounds just as easily
	videoSetModeSub(MODE_0_2D | DISPLAY_BG0_ACTIVE); //sub bg 0 will be used to print text
	
    //set the first bank as background memory and the third as sub background memory
    //B and D are not used
    vramSetMainBanks(VRAM_A_MAIN_BG_0x6000000, VRAM_B_LCD, 
                     VRAM_C_SUB_BG , VRAM_D_LCD); 

	////////////////set up text background for text/////////////////////
    SUB_BG0_CR = BG_MAP_BASE(31);
	
	BG_PALETTE_SUB[255] = RGB15(31,31,31);//by default font will be rendered with color 255
	
	//consoleInit() is a lot more flexible but this gets you up and running quick
	consoleInitDefault((u16*)SCREEN_BASE_BLOCK_SUB(31), (u16*)CHAR_BASE_BLOCK_SUB(0), 16);

	consolePrintf("\n\n\tHello DS devers\n");
	consolePrintf("\twww.drunkencoders.com\n");
	consolePrintf("\t256 color bitmap demo");
	
	///////////////set up our bitmap background///////////////////////
	
	BG3_CR = BG_BMP8_256x256;
	
	//these are rotation backgrounds so you must set the rotation attributes:
    //these are fixed point numbers with the low 8 bits the fractional part
    //this basicaly gives it a 1:1 translation in x and y so you get a nice flat bitmap
        BG3_XDX = 1 << 8;
        BG3_XDY = 0;
        BG3_YDX = 0;
        BG3_YDY = 1 << 8;
    //our bitmap looks a bit better if we center it so scroll down (256 - 192) / 2 
        BG3_CX = 0;
        BG3_CY = 32 << 8;
           
	dmaCopy(drunkenlogo, BG_GFX, 256*256);
	dmaCopy(palette, BG_PALETTE, 256*2);
	
	
    while(1)WaitForVblank();

	return 0;
}
