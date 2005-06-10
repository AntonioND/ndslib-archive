//////////////////////////////////////////////////////////////////////
// Simple IPC demo.  It sends a command to the arm7 wich resieves it,
//  interprets it then sends it back and the result is printed.
// -- dovoto
//////////////////////////////////////////////////////////////////////

#include <NDS/NDS.h>

#include <NDS/ARM9/console.h> //basic print funcionality

void irqVblank(void)
{
    static int heartbeat = 0;
    heartbeat++;
    
    IPC_SYNC_SEND_COMMAND(heartbeat >> 6);
    
    IF = IRQ_VBLANK;
}
void irqRecieve(void)
{
	consolePrintf("Command Recieved: %X\n", IPC_SYNC_GET_COMMAND);
	
	IF = IRQ_SYNC;
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
	irqSet(IRQ_VBLANK, irqVblank);
    irqSet(IRQ_SYNC, irqRecieve);
	IPC_SYNC = IPC_SYNC_IRQ_ENABLE;

	
	while(1)
	{
		
	}
	return 0;
}
