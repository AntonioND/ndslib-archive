//////////////////////////////////////////////////////////////////////
// Simple consol print demo
// -- dovoto
//////////////////////////////////////////////////////////////////////

#include <NDS/NDS.h>

#include <NDS/ARM9/console.h> //basic print funcionality

#include <NDS/ndsload.h>

int main(void)
{
	videoSetMode(0); //not using the main screen
	videoSetModeSub(MODE_0_2D | DISPLAY_BG0_ACTIVE); //sub bg 0 will be used to print text
	vramSetBankC(VRAM_C_SUB_BG); 

	SUB_BG0_CR = BG_MAP_BASE(31);
	
	BG_PALETTE_SUB[255] = RGB15(31,31,31);//by default font will be rendered with color 255
	
	//consoleInit() is a lot more flexible but this gets you up and running quick
	consoleInitDefault((u16*)SCREEN_BASE_BLOCK_SUB(31), (u16*)CHAR_BASE_BLOCK_SUB(0), 16);

	consolePrintf("\n\n\tHello DS devers\n");
	consolePrintf("\twww.drunkencoders.com");
	
	while(1)
	{
		//move the cursor
		consolePrintSet(0,10);
		consolePrintf("Touch x = %04X\n", IPC->touchX);
		consolePrintf("Touch y = %04X\n", IPC->touchY);		
    if ( !(KEYS & KEY_SELECT) && !(KEYS & KEY_START) )
    {
      WAIT_CR &= ~0x8080;
      LOADNDS->ARM9FUNC(BOOT_NDS);
    }	
	}
	return 0;
}
