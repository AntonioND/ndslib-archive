//////////////////////////////////////////////////////////////////////
// Simple bootloader, copies ARM7 and ARM9 binaries to RAM
// -- joat
//////////////////////////////////////////////////////////////////////

#include <NDS/NDS.h>

#include "arm7_bin.h"
#include "arm9_bin.h"

//////////////////////////////////////////////////////////////////////

extern "C" {
  extern void CapARM9(void);
  extern void CallARM7(void);
}

#define arm9flag  (*((vuint16*)0x02300000))

//////////////////////////////////////////////////////////////////////

void LoadBin(const void * src, uint32 dst, int size) {
  uint32 * ram = (uint32 *)dst;
  uint32 * rom = (uint32 *)src;
  for (; size > 0; size -= 4) { *ram++ = *rom++; }
}

//////////////////////////////////////////////////////////////////////

int main(int argc, char ** argv) 
{
 

  LoadBin(GETRAW(arm9_bin), 0x02004000, GETRAWSIZE(arm9_bin));
  LoadBin(GETRAW(arm7_bin), 0x02380000, GETRAWSIZE(arm7_bin));

  *((vuint32*)0x027FFE24)	= (vuint32)0x2004000;
 
  CallARM7();
  while (1) ;
  return 0;
}

//////////////////////////////////////////////////////////////////////
