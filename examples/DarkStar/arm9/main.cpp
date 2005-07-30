/*****************************  DARKSTAR  ******************************\
*  Copyright (c) 2005 Vincent E. Milum Jr., All rights reserved.        *
*                                                                       *
*  See License.txt for more information                                 *
*                                                                       *
*  Latest source versions can be found at:  HTTP://WWW.DARKAIN.COM/     *
\***********************************************************************/


//library includes
#include <NDS/NDS.h>

//common includes
#include "common.h"

//darkstar includes
#include "DarkStar/dsMainMenu.h"
#include <NDS/DarkStar/dsSound.h>
#include <NDS/DarkStar/dsGfx.h>
#include "DarkStar/dsApp.h"

//filesystem includes
//#include "fs/gbfs.h"

//local includes
#include "main.h"
//#include "nds_loader/ndsload.h"
#include <NDS/ndsload.h>

//resources
#include "font_raw.h"
#include "font_pal.h"
#include "menu_raw.h"
#include "menu_pal.h"
#include "icons_raw.h"
#include "icons_pal.h"



class dsMenuReturn : public dsApp {
  public:
    dsMenuReturn() {}
    virtual ~dsMenuReturn() {}

    virtual const char *getAppName()  { return "Return To Menu"; }
    virtual const char *getMenuName() { return "Return To Menu"; }
    virtual void onLaunch() { LOADNDS->ARM9FUNC(BOOT_NDS); }
    virtual void onClose()  {}
};



//////////////////////////////////////////////////////////////////////


//some external stuff
extern void InterruptHandler(void);


int main(int argc, char ** argv) {
  /*
  if (!(KEYS & KEY_L)) {
    WAIT_CR &= ~0x8080;
    WaitForVblank();

    const GBFS_FILE *data = find_first_gbfs_file((void*)0x08004000);
    const GBFS_ENTRY *files = (const GBFS_ENTRY*)data;

    for (int i=0; i<data->dir_nmemb; i++) {
      if (memcmp(files[i+1].name, "meteos_demo_jap.nds", 20) == 0) {
        LOADNDS->ARM9FUNC(files[i+1].name);
      }
    }
  }


  if (!(KEYS & KEY_R)) {
    WAIT_CR &= ~0x8080;
    WaitForVblank();

    const GBFS_FILE *data = find_first_gbfs_file((void*)0x08004000);
    const GBFS_ENTRY *files = (const GBFS_ENTRY*)data;

    for (int i=0; i<data->dir_nmemb; i++) {
      if (memcmp(files[i+1].name, "polarium_demo_usa.nds", 22) == 0) {
        LOADNDS->ARM9FUNC(files[i+1].name);
      }
    }
  }
  */
/*
  __asm volatile("ldr r9,=0x02003FFC");
  __asm volatile("str r10,[r9]");

  *DEBUG1 = POWER_CR;

  initDebug();
*/



  //switch SLOT2 (GBA) over to using the ARM9
  WAIT_CR &= ~0x8080;

  // Turn on the screens and 2D cores and switch to mode 0
  POWER_CR = POWER_ALL_2D;

  //set our vram banks
  vramSetMainBanks(VRAM_A_MAIN_BG, VRAM_B_MAIN_SPRITE, VRAM_C_SUB_BG, VRAM_D_SUB_SPRITE);
/*
  //main screen (defaults to bottom)
  videoSetMode(   MODE_3_2D | DISPLAY_SPR_ACTIVE | DISPLAY_BG0_ACTIVE | DISPLAY_BG1_ACTIVE
    | DISPLAY_BG2_ACTIVE | DISPLAY_BG3_ACTIVE | DISPLAY_SPR_1D_LAYOUT | (2<<5));

  //sub screen (defaults to top)
  videoSetModeSub(MODE_3_2D | DISPLAY_SPR_ACTIVE | DISPLAY_BG0_ACTIVE | DISPLAY_BG1_ACTIVE
    | DISPLAY_BG2_ACTIVE | DISPLAY_BG3_ACTIVE | DISPLAY_SPR_1D_LAYOUT | (2<<5));
*/

  //main bg0 - menu background
  BG0_CR = BG_16_COLOR | BG_MAP_BASE(0) | BG_TILE_BASE(1) | BG_PRIORITY_1;

  //main bg1 - menu text
  BG1_CR = BG_16_COLOR | BG_MAP_BASE(1) | BG_TILE_BASE(1) | BG_PRIORITY_0;
  BG1_X0 = 0xFC;
  BG1_Y0 = 0xFC;

  //main bg2 - application background
  BG2_CR = BG_16_COLOR | BG_MAP_BASE(2) | BG_TILE_BASE(1) | BG_PRIORITY_2;

  //main bg3 - bitmap background
  BG3_CR = BG_BMP16_256x256 | BG_BMP_BASE(2) | BG_PRIORITY(3);
  BG3_XDX = 0x100;
  BG3_YDY = 0x100;

  
  //sub bg0 - menu background
  SUB_BG0_CR = BG_16_COLOR | BG_MAP_BASE(0) | BG_TILE_BASE(1) | BG_PRIORITY_1;

  //sub bg1 - menu text
  SUB_BG1_CR = BG_16_COLOR | BG_MAP_BASE(1) | BG_TILE_BASE(1) | BG_PRIORITY_0;
  SUB_BG1_X0 = 0xFC;
  SUB_BG1_Y0 = 0xFC;

  //sub bg2 - application background
  SUB_BG2_CR = BG_16_COLOR | BG_MAP_BASE(2) | BG_TILE_BASE(1) | BG_PRIORITY_2;

  //sub bg3 - bitmap background
  SUB_BG3_CR = BG_BMP16_256x256 | BG_BMP_BASE(2) | BG_PRIORITY(3);
  SUB_BG3_XDX = 0x100;
  SUB_BG3_YDY = 0x100;


  //load colour palettes for the font, and gui icons
//  dmaCopyWords(3, font_pal,  &PALETTE[16],        32);
//  dmaCopyWords(3, font_pal,  &PALETTE[528],       32);
  dmaCopyWords(3, icons_pal, &PALETTE[256],       32);
  dmaCopyWords(3, icons_pal, &PALETTE[768],       32);

  //load graphics for gui menu and font
  dmaCopyWords(3, menu_raw,  &BG_GFX[0x2010],     800);
  dmaCopyWords(3, font_raw,  &BG_GFX[0x2400],     1536<<1);
  dmaCopyWords(3, menu_raw,  &BG_GFX_SUB[0x2010], 800);
  dmaCopyWords(3, font_raw,  &BG_GFX_SUB[0x2400], 1536<<1);
/*
  //hilighted text palette
  for (int i=2; i<14; i++) {
    PALETTE[i+32] = RGB( RGBGREEN(PALETTE[i+16]), RGBRED(PALETTE[i+16]), RGBRED(PALETTE[i+16]) );
    PALETTE[i+32+512] = PALETTE[i+32];
  }
*/
  //start the main GUI
  mainmenu = NULL;
  new dsMainMenu();


  if ( ((u32)LOADNDS->ARM9FUNC) > 0x08000000 && ((u32)LOADNDS->ARM9FUNC) < 0x08004000
    && ((u32)LOADNDS->ARM7FUNC) > 0x08000000 && ((u32)LOADNDS->ARM7FUNC) < 0x08004000) {
    new dsMenuReturn();
  }


  dsSound::updateIpcSound();


  //fade from white
  {
    videoSetMode(   MODE_3_2D | DISPLAY_BG3_ACTIVE | (2<<5));
    videoSetModeSub(MODE_3_2D | DISPLAY_BG3_ACTIVE | (2<<5));

    BLEND_CR     = BLEND_FADE_WHITE | BLEND_SRC_BG3 | BLEND_SRC_BACKDROP;
    SUB_BLEND_CR = BLEND_FADE_WHITE | BLEND_SRC_BG3 | BLEND_SRC_BACKDROP;

    BLEND_Y     = 16;
    SUB_BLEND_Y = 16;

    for (int i=0; i<=16; i++) {
      BLEND_Y  = 16-i;
      SUB_BLEND_Y  = 16-i;
      for (int x=0; x<2; x++) WaitForVblank();
    }
  }


  //fade in GUI objects
  {
    //set blending on main screen
    BLEND_CR = BLEND_ALPHA | BLEND_SRC_BG0 | BLEND_SRC_BG1 | BLEND_SRC_BG2
      | BLEND_DST_BG3 | BLEND_SRC_SPRITE | BLEND_DST_BACKDROP;

    //set blending on sub-screen
    SUB_BLEND_CR = BLEND_ALPHA | BLEND_SRC_BG0 | BLEND_SRC_BG1 | BLEND_SRC_BG2
      | BLEND_DST_BG3 | BLEND_SRC_SPRITE | BLEND_DST_BACKDROP;

    BLEND_AB     = 0x1000;
    SUB_BLEND_AB = 0x1000;

    videoSetMode(   MODE_3_2D | DISPLAY_SPR_ACTIVE | DISPLAY_BG0_ACTIVE | DISPLAY_BG1_ACTIVE
      | DISPLAY_BG2_ACTIVE | DISPLAY_BG3_ACTIVE | DISPLAY_SPR_1D_LAYOUT | (2<<5));

    videoSetModeSub(MODE_3_2D | DISPLAY_SPR_ACTIVE | DISPLAY_BG0_ACTIVE | DISPLAY_BG1_ACTIVE
      | DISPLAY_BG2_ACTIVE | DISPLAY_BG3_ACTIVE | DISPLAY_SPR_1D_LAYOUT | (2<<5));

    for (int i=0; i<=12; i++) {
      BLEND_AB      = i | ((16-i)<<8);
      SUB_BLEND_AB  = i | ((16-i)<<8);
      for (int x=0; x<2; x++) WaitForVblank();
    }

    BLEND_AB = 0x0612;
    BLEND_Y  = 0x0000;
    SUB_BLEND_AB = 0x0612;
    SUB_BLEND_Y  = 0x0000;
  }


/*
  //set blending on main screen
  BLEND_CR = BLEND_ALPHA | BLEND_SRC_BG0 | BLEND_SRC_BG1 | BLEND_DST_BG2
    | BLEND_DST_BG3 | BLEND_DST_SPRITE | BLEND_DST_BACKDROP;
  BLEND_AB = 0x0612;
  BLEND_Y  = 0x0000;

  //set blending on sub-screen
  SUB_BLEND_CR = BLEND_ALPHA | BLEND_SRC_BG0 | BLEND_SRC_BG1 | BLEND_DST_BG2
    | BLEND_DST_BG3 | BLEND_DST_SPRITE | BLEND_DST_BACKDROP;
  SUB_BLEND_AB = 0x0612;
  SUB_BLEND_Y  = 0x0000;
*/

  // Enable the V-blank interrupt
  IME = 0;
  IRQ_HANDLER = &InterruptHandler;
  IE = IRQ_VBLANK;
  IF = ~0;
  DISP_SR = DISP_VBLANK_IRQ;
//  VBLANK_INTR_WAIT_FLAGS = IF | IE;
  IME = 1;


 
  while (1) {
    //swiWaitForVBlank();  // Sleep to save power
    WaitForVblank();
    *DEBUG2 = *DEBUG2 + 1;
  }
  return 0;
}
