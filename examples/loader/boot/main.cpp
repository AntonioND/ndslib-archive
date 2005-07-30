#define LOADER_VERSION 0x20050730


#define ARM9
#include <NDS/memory.h>
#undef ARM9

#include <NDS/NDS.h>
#include <NDS/ndsload.h>

#define ARM9
#include <NDS/ARM9/video.h>

#include <malloc.h>
#include "gbfs.h"


extern "C" {

#define LOAD_VIA_DMA
#define READWORD(file, addr) (*((u32*)(&file[addr])))

void __attribute__ ((long_call)) arm7stage1(const char *path);
void __attribute__ ((long_call)) arm7stage2();
//void __attribute__ ((long_call)) arm7stage3();

void __attribute__ ((long_call)) arm9stage1(const char *path);
void __attribute__ ((long_call)) arm9stage2();
void __attribute__ ((long_call)) arm9stage3();



//////////////////////////////////////////////////////////////////////



static inline void dmaFillWords(const void* src, void* dest, uint32 size) {
	DMA_SRC(3)  = (uint32)src;
	DMA_DEST(3) = (uint32)dest;
	DMA_CR(3)   = DMA_COPY_WORDS | DMA_SRC_FIX | (size>>2);
	while(DMA_CR(3) & DMA_BUSY);
}


inline void __attribute__ ((long_call)) copyBin(const u32 *src, u32 *dst, u32 size) {
#ifdef LOAD_VIA_DMA

  for (u32 i=0; i<(size>>18); i++) {
    dmaCopyWords(3, src, dst, 0);  //copy 256kb at a time
    src += (64*1024);
    dst += (64*1024);
  }

  //amount left over
  if ((size & 0x3FFFF) > 0) dmaCopyWords(3, src, dst, (size & 0x3FFFF));


#else
  for (; size > 0; size -= 4) { *dst++ = *src++; }
#endif
}


u32 __attribute__ ((long_call)) query(u32 id) {
  return 0;
}


void __attribute__ ((long_call)) arm7stage1(const char *path) {
  IME = 0;
  LOADNDS->PATH = path;

  for (int i=0; i<16; i++) {
    SCHANNEL_CR(i) = 0;
    SCHANNEL_TIMER(i) = 0;
    SCHANNEL_SOURCE(i) = 0;
    SCHANNEL_LENGTH(i) = 0;
  }
  SOUND_CR = 0;

  //clear out ARM7 DMA channels and timers
  for (int i=0; i<4; i++) {
    DMA_CR(i) = 0;
    DMA_SRC(i) = 0;
    DMA_DEST(i) = 0;
    TIMER_CR(i) = 0;
    TIMER_DATA(i) = 0;
  }

  //switch to user mode
  __asm volatile(
    "mov r6, #0x1F                \n"
    "msr cpsr, r6                 \n"
  );
/*
  __asm volatile(
  //switch to IRQ mode
    "mov r6, #0x12                \n"
    "msr cpsr, r6                 \n"
    "ldr sp, =0x03808000-0x100    \n"  //Set irq stack

  //switch to svc mode
    "mov r6, #0x13                \n"
	  "msr cpsr, r6                 \n"
    "ldr sp, =0x03808000-0x200    \n"  //Set svc stack

  //switch to user mode
    "mov r6, #0x1F                \n"
    "msr cpsr, r6                 \n"
    "ldr sp, =0x03808000-0x300    \n"  //Set user stack
  );
*/
  //clear IWRAM
  LOADNDS->RESERVED = 0;
	DMA_SRC(3)  = (uint32)&LOADNDS->RESERVED;
	DMA_DEST(3) = (uint32)0x03800000;
	DMA_CR(3)   = DMA_COPY_WORDS | DMA_SRC_FIX | ((64*1024)>>2);

  //clear shared RAM
  LOADNDS->RESERVED = 0;
	DMA_SRC(3)  = (uint32)&LOADNDS->RESERVED;
	DMA_DEST(3) = (uint32)0x037F8000;
	DMA_CR(3)   = DMA_COPY_WORDS | DMA_SRC_FIX | ((32*1024)>>2);

  //clear first 256k part of EWRAM
  LOADNDS->RESERVED = 0;
	DMA_SRC(3)  = (uint32)&LOADNDS->RESERVED;
	DMA_DEST(3) = (uint32)(0x02000000);
	DMA_CR(3)   = DMA_COPY_WORDS | DMA_SRC_FIX | 0;
  
  arm7stage2();
}


void __attribute__ ((long_call)) arm7stage2() {
  IE = 0;
  IF = ~0;
  (*(vu32*)(0x04000000-4)) = 0;  //IRQ_HANDLER ARM7 version
  (*(vu32*)(0x04000000-8)) = ~0; //VBLANK_INTR_WAIT_FLAGS, ARM7 version
  POWER_CR = 1;  //turn off power to stuffs

  //open the file... what happened to the verification check ???
  const GBFS_FILE *gbfs = find_first_gbfs_file((void*)0x08004000);
  register const char *file;

  if (gbfs->dir_nmemb == 1) {
    u32 filesize = 0;
    char filename[24];
    file = (const char*)gbfs_get_nth_obj(gbfs, 0, filename, &filesize);
  } else {
    u32 filesize = 0;
    file = (const char*)gbfs_get_obj(gbfs, (LOADNDS->PATH==BOOT_NDS?"boot.nds":LOADNDS->PATH), &filesize);
    if (!file) file = (const char*)gbfs_get_obj(gbfs, "boot.nds", &filesize);
  }


  //make sure LOADNDS remains set
  LOADNDS->VERSION  = LOADER_VERSION;
  LOADNDS->QUERY    = query;
  LOADNDS->ARM7FUNC = arm7stage1;
  LOADNDS->ARM9FUNC = arm9stage1;
  LOADNDS->PATH     = 0;
  LOADNDS->RESERVED = READWORD(file, 0x034);

  //read ARM9 info from NDS file
  u32 *ARM9_SRC = (u32*)(READWORD(file, 0x020) + ((u32)file));
  u32 *ARM9_DST = (u32*)(READWORD(file, 0x028));
  u32 ARM9_LEN = READWORD(file, 0x02C);

  //read ARM7 info from NDS file
  u32 *ARM7_SRC = (u32*)(READWORD(file, 0x030) + ((u32)file));
  u32 *ARM7_DST = (u32*)(READWORD(file, 0x038));
  u32 ARM7_LEN = READWORD(file, 0x03C);

  //copy ARM7 and ARM9 binaries to RAM
  copyBin(ARM9_SRC, ARM9_DST, ARM9_LEN);
  copyBin(ARM7_SRC, ARM7_DST, ARM7_LEN);

  //mirrored header CRC
  (*(vu16*)0x027FF808) = READWORD(file, 0x15E);
  (*(vu16*)0x027FFC08) = READWORD(file, 0x15E);

  //mirrored secure area CRC
  (*(vu16*)0x027FF80A) = READWORD(file, 0x06C);
  (*(vu16*)0x027FFC0A) = READWORD(file, 0x06C);

	while(DISP_Y!=191);
	while(DISP_Y==191);

  //copy NDS header into RAM
  copyBin((u32*)file, (u32*)0x027FFE00, 0x170);
//  copyBin((u32*)(file),      (u32*)(0x027FFE00), 0x024);  //skip 4 bytes for PASSME addy
//  copyBin((u32*)(file+0x28), (u32*)(0x027FFE28), 0x148);
//  copyBin((u32*)(file),      (u32*)(0x027FFE00), 0x020);  //skip 4 bytes for PASSME addy
//  copyBin((u32*)(file+0x28), (u32*)(0x027FFE28), 0x148);

  //launch ARM9
//  (*(vu32*)0x027FFE24) = READWORD(file, 0x024);

  while(DISP_Y!=191);
	while(DISP_Y==191);


  //launch ARM7
  __asm volatile(
    "ldr r0,=0x02800000-20        \n"
    "ldr r0,[r0]                  \n"
    "bx r0                        \n"
  );
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////


void __attribute__ ((long_call)) arm9stage1(const char *path) {
  IME = 0;
  IE = 0;
  IF = ~0;

  LOADNDS->VERSION = (u32)path;

  __asm volatile(
    
    //clean and flush cache
    "mov r1, #0                   \n"
    "outer_loop:                  \n"
    " mov r0, #0                  \n"
    " inner_loop:                 \n"
    "  orr r2, r1, r0             \n"
    "  mcr p15, 0, r2, c7, c14, 2 \n"
    "  add r0, r0, #0x20          \n"
    "  cmp r0, #0x400             \n"
    " bne inner_loop              \n"
    " add r1, r1, #0x40000000     \n"
    " cmp r1, #0x0                \n"
    "bne outer_loop               \n"
    
    "mov r10, #0                  \n"
    "mcr p15, 0, r10, c7, c5, 0   \n"  //disable ICache
    "mcr p15, 0, r10, c7, c6, 0   \n"  //disable DCache
    "mcr p15, 0, r10, c7, c10, 4  \n"  //empty write buffer

	  "mcr p15, 0, r10, c3, c0, 0   \n"  //disable write buffer       (def = 0)

    "mcr p15, 0, r10, c1, c0      \n"  //disable DTCM and protection unit

    "mcr p15, 0, r10, c6, c0, 0   \n"  //disable protection unit 0  (def = 0)
    "mcr p15, 0, r10, c6, c1, 0   \n"  //disable protection unit 1  (def = 0)
    "mcr p15, 0, r10, c6, c2, 0   \n"  //disable protection unit 2  (def = 0)
    "mcr p15, 0, r10, c6, c3, 0   \n"  //disable protection unit 3  (def = 0)
    "mcr p15, 0, r10, c6, c4, 0   \n"  //disable protection unit 4  (def = ?)
    "mcr p15, 0, r10, c6, c5, 0   \n"  //disable protection unit 5  (def = ?)
    "mcr p15, 0, r10, c6, c6, 0   \n"  //disable protection unit 6  (def = ?)
    "mcr p15, 0, r10, c6, c7, 0   \n"  //disable protection unit 7  (def = ?)

    "mcr p15, 0, r10, c5, c0, 3   \n"  //IAccess
    "mcr p15, 0, r10, c5, c0, 2   \n"  //DAccess

	  "ldr r10,=0x0080000A          \n"
	  "mcr p15, 0, r10, c9, c1, 0   \n"  //DTCM base  (def = 0x0080000A) ???
	
    "ldr r10,=0x0000000C          \n"
	  "mcr p15, 0, r10, c9, c1, 1   \n"  //ITCM base  (def = 0x0000000C) ???
//  );
/*
//  __asm volatile(
  //switch to irq mode
    "mov r10, #0x12               \n"
	  "msr cpsr, r10                \n"
    "ldr sp, =0x00800000          \n"  //Set irq stack

  //switch to svc mode
    "mov r10, #0x13               \n"
	  "msr cpsr, r10                \n"
    "ldr sp, =0x00800100          \n"  //Set svc stack

  //switch to user mode
    "mov r10, #0x1F               \n"
	  "msr cpsr, r10                \n"
    "ldr sp, =0x00800200          \n"  //Set user stack*/

    "mov r10, #0x1F               \n"
	  "msr cpsr, r10                \n"
  );

  for (int i=0; i<16*1024; i+=4) {  //first 16KB
    (*(vu32*)(i+0x00000000)) = 0x00000000;      //clear ITCM
    (*(vu32*)(i+0x00800000)) = 0x00000000;      //clear DTCM
  }

  for (int i=16*1024; i<32*1024; i+=4) {  //second 16KB
    (*(vu32*)(i+0x00000000)) = 0x00000000;      //clear ITCM
  }

  (*(vu32*)0x00803FFC) = 0;   //IRQ_HANDLER ARM9 version
  (*(vu32*)0x00803FF8) = ~0;  //VBLANK_INTR_WAIT_FLAGS ARM9 version
  (*(vu32*)0x027FFE24) = 0;   //set ARM9 load address to 0

  
//  __asm volatile("bx %0" : : "r" (arm9stage2) ); 
  arm9stage2();
}


void __attribute__ ((long_call)) arm9stage2() {
/*  dont do this on the ARM9, cause itll fuck everything up
  //clear EWRAM
  LOADNDS->RESERVED = 0;
	DMA_SRC(3)  = (uint32)&LOADNDS->RESERVED;
	DMA_DEST(3) = (uint32)0x02000000;
//	DMA_CR(3)   = DMA_COPY_WORDS | DMA_SRC_FIX | ((0x400000-0x1000)>>2);
	DMA_CR(3)   = DMA_COPY_WORDS | DMA_SRC_FIX | ((0x200000)>>2);
	while(DMA_CR(3) & DMA_BUSY);
*/

  //clear out ARM9 DMA channels
  for (int i=0; i<4; i++) {
    DMA_CR(i) = 0;
    DMA_SRC(i) = 0;
    DMA_DEST(i) = 0;
    TIMER_CR(i) = 0;
    TIMER_DATA(i) = 0;
  }

  VRAM_CR = 0x80808080;
  LOADNDS->RESERVED = 0;
  PALETTE[0] = 0xFFFF;
  dmaFillWords((void*)&LOADNDS->RESERVED, PALETTE+1, (2*1024)-2);
  dmaFillWords((void*)&LOADNDS->RESERVED, OAM,     2*1024);
  dmaFillWords((void*)&LOADNDS->RESERVED, (void*)0x04000000, 0x56);  //clear main display registers
  dmaFillWords((void*)&LOADNDS->RESERVED, (void*)0x04001000, 0x56);  //clear sub  display registers
  dmaFillWords((void*)&LOADNDS->RESERVED, VRAM,  656*1024);


  DISP_SR = 0;
  videoSetMode(0);
  videoSetModeSub(0);
  VRAM_A_CR = 0;
  VRAM_B_CR = 0;
  VRAM_C_CR = 0;
  VRAM_D_CR = 0;
  VRAM_E_CR = 0;
  VRAM_F_CR = 0;
  VRAM_G_CR = 0;
  VRAM_H_CR = 0;
  VRAM_I_CR = 0;
  VRAM_CR   = 0x03000000;
  POWER_CR  = 0x820F;

  //set shared ram to ARM7
  WRAM_CR = 0x03;

  //copy ARM9 function to RAM
  dmaCopyWords(3, (void*)arm9stage3, (void*)0x027FF000, 256);

  //have the ARM9 wait on the ARM7 to load
  __asm volatile("bx %0" : : "r" (0x027FF000) ); 
}


void __attribute__ ((long_call)) arm9stage3() {
  WAIT_CR = 0xE880;
  LOADNDS->PATH = (const char*)LOADNDS->VERSION;
	while(DISP_Y!=191);
	while(DISP_Y==191);
  while ( (*(vu32*)0x027FFE24) == 0 ) {}
	while(DISP_Y!=191);
	while(DISP_Y==191);
  __asm volatile("bx %0" : : "r" (*(vu32*)0x027FFE24));
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////


int main(int argc, char **argv) {

  (*(vu32*)0x02000000) = 0x11111111;
  if ( (*(vu32*)0x02080000) == 0x11111111) {
    (*(vu32*)0x02080000) = 0x22222222;
    if ( (*(vu32*)0x02000000) == 0x22222222) {
      while (1) {}  //we are running on teh GBA
    }
  }

  (*(vu32*)0x02000000) = 0x00000000;
  (*(vu32*)0x02080000) = 0x00000000;


  //copy ARM9 function to RAM, and make the ARM9 jump to it
  dmaCopyWords(3, (void*)arm9stage3, (void*)0x027FF000, 256);
  (*(vu32*)0x027FFE24) = (u32)0x027FF000;
  

  LOADNDS->PATH = BOOT_NDS;
  arm7stage2();
  return 0;
}


}  //extern "C"

