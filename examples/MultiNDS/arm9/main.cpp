/*****************************  DARKSTAR  ******************************\
*  Copyright (c) 2005 Vincent E. Milum Jr., All rights reserved.        *
*                                                                       *
*  See License.txt for more information                                 *
*                                                                       *
*  Latest source versions can be found at:  HTTP://WWW.DARKAIN.COM/     *
\***********************************************************************/


//library includes
#include <NDS/NDS.h>


//local includes
#include "main.h"
#include "mndsMenu.h"

//resources
#include "square_raw.h"
#include "square_pal.h"
#include "game_raw.h"
#include "game_pal.h"



//////////////////////////////////////////////////////////////////////


//some external stuff
extern void InterruptHandler(void);


int main(int argc, char ** argv) {
  WaitForVblank();

  // Turn on the screens and 2D cores and switch to mode 0
  POWER_CR = POWER_ALL_2D;

  //set our vram banks
  vramSetMainBanks(VRAM_A_MAIN_BG_0x6000000, VRAM_B_MAIN_BG_0x6020000, VRAM_C_SUB_BG_0x6200000, VRAM_D_SUB_SPRITE);
  
  vramSetBankE(VRAM_E_MAIN_SPRITE);
//  vramSetBankI(VRAM_I_SUB_SPRITE);
  vramSetBankG(VRAM_G_BG_EXT_PALETTE);

  u16 *disp = ((u16*)0x06894000);
  for (int i=0; i<8*1024; i++) disp[i] = 0xFFFF;

  if (!sprmgr) new dsSpriteManager();

  //main screen (defaults to bottom)
  videoSetMode(   MODE_3_2D | DISPLAY_SPR_ACTIVE | DISPLAY_BG0_ACTIVE | DISPLAY_BG1_ACTIVE
    | DISPLAY_BG2_ACTIVE | DISPLAY_BG3_ACTIVE | DISPLAY_SPR_1D_LAYOUT | (2<<5));

  //sub screen (defaults to top)
  videoSetModeSub(MODE_3_2D | DISPLAY_SPR_ACTIVE | DISPLAY_BG0_ACTIVE | DISPLAY_BG1_ACTIVE
    | DISPLAY_BG2_ACTIVE | DISPLAY_BG3_ACTIVE | DISPLAY_SPR_1D_LAYOUT | (2<<5));


  //main bg0 - menu background
  BG0_CR = BG_16_COLOR | BG_MAP_BASE(0) | BG_TILE_BASE(1) | BG_PRIORITY_2;
  BG0_X0 = 0x00;
  BG0_Y0 = 0x04;

  //main bg1 - menu text
  BG1_CR = BG_16_COLOR | BG_MAP_BASE(1) | BG_TILE_BASE(1) | BG_PRIORITY_1;
  BG1_X0 = 0x00;
  BG1_Y0 = 0x04;

  //sub bg2 - application background
  BG2_CR = BG_16_COLOR | BG_MAP_BASE(2) | BG_TILE_BASE(1) | BG_PRIORITY_3;

  //main bg3 - application background
  BG3_CR = BG_BMP8_256x256 | BG_BMP_BASE(2) | BG_PRIORITY_0;
  BG3_XDX = 0x100;
  BG3_YDY = 0x100;
/*
  //main bg3 - bitmap background
  BG3_CR = BG_BMP16_256x256 | BG_BMP_BASE(8) | BG_PRIORITY_3;
  BG3_XDX = 0x100;
  BG3_YDY = 0x100;
*/

  //sub bg0 - menu background
  SUB_BG0_CR = BG_16_COLOR | BG_MAP_BASE(0) | BG_TILE_BASE(1) | BG_PRIORITY_2;

  //sub bg1 - menu text
  SUB_BG1_CR = BG_16_COLOR | BG_MAP_BASE(1) | BG_TILE_BASE(1) | BG_PRIORITY_1;

  //sub bg2 - application background
  SUB_BG2_CR = BG_16_COLOR | BG_MAP_BASE(2) | BG_TILE_BASE(1) | BG_PRIORITY_3;

  //sub bg3 - bitmap background
  SUB_BG3_CR = BG_BMP8_256x256 | BG_BMP_BASE(2) | BG_PRIORITY_0;
  SUB_BG3_XDX = 0x100;
  SUB_BG3_YDY = 0x100;



  BLEND_CR     = BLEND_FADE_WHITE | BLEND_SRC_BG0 | BLEND_SRC_BG1 | BLEND_SRC_BG2
    | BLEND_SRC_BG3 | BLEND_SRC_SPRITE | BLEND_SRC_BACKDROP;

  //set blending on sub-screen
  SUB_BLEND_CR = BLEND_FADE_WHITE | BLEND_SRC_BG0 | BLEND_SRC_BG1 | BLEND_SRC_BG2
    | BLEND_SRC_BG3 | BLEND_SRC_SPRITE | BLEND_SRC_BACKDROP;

  BLEND_Y  = 16;
  SUB_BLEND_Y  = 16;


  for (int i=0; i<0x4000; i++) {
    BG_GFX[i] = 0;
  }
  
  dmaCopyWords(3, square_pal, &PALETTE[(16*10)], 32);
  dmaCopyWords(3, square_raw, &BG_GFX[0x2190],  128);
  dmaCopyWords(3, square_pal, &PALETTE[512+(16*10)], 32);
  dmaCopyWords(3, square_raw, &BG_GFX_SUB[0x2190],  128);

  for (int y=0; y<24; y+=2) {
    for (int x=0; x<32; x+=2) {
      BG_GFX[0x800 + x + 0 + ((y + 0) * 32)] = 0xA019;
      BG_GFX[0x800 + x + 1 + ((y + 0) * 32)] = 0xA01A;
      BG_GFX[0x800 + x + 0 + ((y + 1) * 32)] = 0xA01B;
      BG_GFX[0x800 + x + 1 + ((y + 1) * 32)] = 0xA01C;
      BG_GFX_SUB[0x800 + x + 0 + ((y + 0) * 32)] = 0xA019;
      BG_GFX_SUB[0x800 + x + 1 + ((y + 0) * 32)] = 0xA01A;
      BG_GFX_SUB[0x800 + x + 0 + ((y + 1) * 32)] = 0xA01B;
      BG_GFX_SUB[0x800 + x + 1 + ((y + 1) * 32)] = 0xA01C;
    }
  }


  for (int i=0; i<=16; i++) {
    BLEND_Y  = 16-i;
    SUB_BLEND_Y  = 16-i;
    for (int x=0; x<2; x++) WaitForVblank();
  }
  
  //switch SLOT2 (GBA) over to using the ARM9
  WAIT_CR &= ~0x8080;


  //set blending on main screen
  BLEND_CR     = BLEND_ALPHA | BLEND_SRC_BG0 | BLEND_SRC_BG1 | BLEND_DST_BG2
    | BLEND_DST_BG3 | BLEND_SRC_SPRITE | BLEND_DST_BACKDROP;

  //set blending on sub-screen
  SUB_BLEND_CR = BLEND_ALPHA | BLEND_SRC_BG0 | BLEND_SRC_BG1 | BLEND_DST_BG2
    | BLEND_DST_BG3 | BLEND_SRC_SPRITE | BLEND_DST_BACKDROP;

  BLEND_AB     = 0x1000;
  SUB_BLEND_AB = 0x1000;

  dmaCopyWords(3, game_pal, &PALETTE[512],           32);
  dmaCopyWords(3, game_raw, &BG_GFX[0x2010],        768);
  dmaCopyWords(3, game_raw, &BG_GFX_SUB[0x2010],    768);

  new mndsMenu();


  for (int i=0; i<=12; i++) {
    BLEND_AB      = i | ((16-i)<<8);
    SUB_BLEND_AB  = i | ((16-i)<<8);
    for (int x=0; x<2; x++) WaitForVblank();
  }


  // Enable the V-blank interrupt
  IME = 0;
  IRQ_HANDLER = &InterruptHandler;
  IE = IRQ_VBLANK;
  IF = ~0;
  DISP_SR = DISP_VBLANK_IRQ;
  IME = 1;

 
  while (1) {
    //swiWaitForVBlank();  // Sleep to save power
    WaitForVblank();
  }

  return 0;
}
