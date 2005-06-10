//////////////////////////////////////////////////////////////////////
// Simple consol print demo
// -- dovoto
//////////////////////////////////////////////////////////////////////

#include <NDS/NDS.h>

#include <NDS/ARM9/console.h> //basic print funcionality

void irqRecieve(void)
{
	consolePrintf("Command Recieved: %d\n", IPC_SYNC_GET_COMMAND);
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
	
	irqInitHandler(irqDefaultHandler);
	irqSet(IRQ_SYNC, irqRecieve);
	IPC_SYNC = IPC_SYNC_IRQ_ENABLE;

	
	while(1)
	{
		
	}
	return 0;
}
