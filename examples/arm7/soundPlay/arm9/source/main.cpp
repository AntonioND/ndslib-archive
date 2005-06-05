//////////////////////////////////////////////////////////////////////
// Simple consol print demo
// -- dovoto
//////////////////////////////////////////////////////////////////////

#include <NDS/NDS.h>

#include <NDS/ARM9/console.h> //basic print funcionality

#include "blaster.h"
#include "saberoff.h"
#include "ion.h"

VAR_IN_EXRAM TransferSound snd;

//plays an 8 bit mono sample at 11025Hz
void playGenericSound(const void* data, u32 length)
{
	snd.count = 1;
	snd.data[0].data = data;
	snd.data[0].len = length;
	snd.data[0].rate = 11025;
	snd.data[0].pan = 64;
	snd.data[0].vol = 64;
	snd.data[0].format = 1;

	DC_FlushAll();
	IPC->soundData = &snd;
}
void waitForVBlank()
{
	while(!(DISP_SR & DISP_IN_VBLANK));
	while((DISP_SR & DISP_IN_VBLANK));
}
int main(void)
{
	videoSetMode(0); //not using the main screen
	videoSetModeSub(MODE_0_2D | DISPLAY_BG0_ACTIVE); //sub bg 0 will be used to print text
	vramSetBankC(VRAM_C_SUB_BG); 

	SUB_BG0_CR = BG_MAP_BASE(31);
	
	BG_PALETTE_SUB[255] = RGB15(31,31,31);//by default font will be rendered with color 255
	
	//consoleInit() is a lot more flexible but this gets you up and running quick
	consoleInitDefault((u16*)SCREEN_BASE_BLOCK_SUB(31), (u16*)CHAR_BASE_BLOCK_SUB(0), 16);

	consolePrintf("\n\n\tSOund Effect Demo\n");
	consolePrintf("\twww.drunkencoders.com");
	
	

	while(1)
	{
		
		scanKeys();

		//move the cursor
		consolePrintSet(0,10);
		consolePrintf("Touch x = %04X\n", IPC->touchX);
		consolePrintf("Touch y = %04X\n", IPC->touchY);	

		if(keysDown() & KEY_A) playGenericSound(saberoff, (u32)saberoff_size);
	
		if(keysDown() & KEY_B) playGenericSound(blaster, (u32)blaster_size);
	
		if(keysDown() & KEY_X) playGenericSound(ion, (u32)ion_size);
	
		waitForVBlank();

	}
	return 0;
}
