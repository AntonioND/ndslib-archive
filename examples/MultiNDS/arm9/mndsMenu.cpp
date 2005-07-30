/*****************************  DARKSTAR  ******************************\
*  Copyright (c) 2005 Vincent E. Milum Jr., All rights reserved.        *
*                                                                       *
*  See License.txt for more information                                 *
*                                                                       *
*  Latest source versions can be found at:  HTTP://WWW.DARKAIN.COM/     *
\***********************************************************************/


//library includes
#include <NDS/NDS.h>
#include <NDS/ndsload.h>

//darkstar includes
#include <NDS/DarkStar/dsSound.h>

//local includes
#include "common.h"
#include "main.h"
#include "letters.h"
#include "mndsMenu.h"
#include "mndsLoadGame.h"
#include "mndsGame.h"
#include "mndsMove.h"
#include "mndsFade.h"

//resources
#include "cur_raw.h"
#include "cur_pal.h"
#include "button_raw.h"
#include "button_pal.h"
#include "darkain_raw.h"
#include "darkain_pal.h"
#include "game_raw.h"
#include "game_pal.h"
#include "dong_raw.h"
#include "select_raw.h"



//i need to do something about this, as the size glitch doesnt exist anymore
static const char uselessdata[2*1024] = {0};


mndsMenu::mndsMenu() {
  sel = 0;
  top = 0;

  zeros = (u32*)uselessdata;//(u32*)malloc(32*16);
  buffer = (u8*)malloc(256*192);
/*  for (int i=0; i<32*16/4; i++) zeros[i] = 0x11111111;

  PALETTE[768+(14*16)+1] = RGB(16,16,16);
  dsSpriteSingle *iconbg = new dsSpriteSingle(DS_CORE_SUB, zeros, SIZE_32_X_32, false, 14);
  iconbg->move(33, 49);
  iconbg->setPriority(1);
  iconbg->show();*/

  for (int i=0; i<32*16/4; i++) zeros[i] = 0x00000000;
  icon = new dsSpriteSingle(DS_CORE_SUB, zeros, SIZE_32_X_32, false, 5);
  icon->move(32, 48);
  icon->setPriority(0);
  icon->show();


  for (int i=0; i<4; i++) {
    sprites[i] = new dsSpriteSingle(DS_CORE_MAIN, zeros, SIZE_32_X_32, false, i+1);
    sprites[i]->move(16, (i*8*5)+20);
    sprites[i]->show();
  }

  dmaCopyHalfWords(3, cur_pal, &PALETTE[256+(15*16)], 32);
  for (int i=0; i<4; i++) {
    cursors[i] = new dsSpriteSingle(DS_CORE_MAIN, cur_raw, SIZE_16_X_16, false, 15);
    cursors[i]->show();
  }
  cursors[0]->setFlip(FLIP_NONE);
  cursors[1]->setFlip(FLIP_HORZ);
  cursors[2]->setFlip(FLIP_VERT);
  cursors[3]->setFlip(FLIP_BOTH);

  dmaCopyHalfWords(3, button_pal, &PALETTE[256+(12*16)], 32);
  new mndsLoadGame(this);
  up = new mndsMoveUp(this);
  down = new mndsMoveDown(this);

  dmaCopyHalfWords(3, darkain_pal, &PALETTE[768+(15*16)], 32);
  logo[0] = new dsSpriteSingle(DS_CORE_SUB, darkain_raw+  0, SIZE_32_X_16, false, 15);
  logo[1] = new dsSpriteSingle(DS_CORE_SUB, darkain_raw+256, SIZE_32_X_16, false, 15);
  logo[2] = new dsSpriteSingle(DS_CORE_SUB, darkain_raw+512, SIZE_32_X_16, false, 15);
  logo[0]->move(166, 0);
  logo[1]->move(198, 0);
  logo[2]->move(230, 0);

  const GBFS_FILE  *gbfs  = ((const GBFS_FILE *)GBFS);
  const GBFS_ENTRY *files = ((const GBFS_ENTRY*)(((u8*)gbfs) + gbfs->dir_off));

  for (int i=0; i<gbfs->dir_nmemb; i++) {
    games.appendItem(new mndsGame(&files[i]));
  }

  u8 palindex = 1;
  for (int y=3; y<22; y+=5) {
    dmaCopyHalfWords(3, game_pal,    &PALETTE[palindex*16], 32);

    for (int x=0; x<22; x++) {
      BG_GFX[0x400+x+7+((y+0)*32)] = 0x0002 | (palindex<<12);
      BG_GFX[0x400+x+7+((y+1)*32)] = 0x0005 | (palindex<<12);
      BG_GFX[0x400+x+7+((y+2)*32)] = 0x0008 | (palindex<<12);
      BG_GFX[0x400+x+7+((y+3)*32)] = 0x000B | (palindex<<12);
    }

    BG_GFX[0x400+6+((y+0)*32)] = 0x0001 | (palindex<<12);
    BG_GFX[0x400+6+((y+1)*32)] = 0x0004 | (palindex<<12);
    BG_GFX[0x400+6+((y+2)*32)] = 0x0007 | (palindex<<12);
    BG_GFX[0x400+6+((y+3)*32)] = 0x000A | (palindex<<12);

    BG_GFX[0x400+29+((y+0)*32)] = 0x0003 | (palindex<<12);
    BG_GFX[0x400+29+((y+1)*32)] = 0x0006 | (palindex<<12);
    BG_GFX[0x400+29+((y+2)*32)] = 0x0009 | (palindex<<12);
    BG_GFX[0x400+29+((y+3)*32)] = 0x000C | (palindex<<12);

    palindex++;
    if (palindex > games.getItemCount()) break;
  }


  dmaCopyHalfWords(3, game_pal, &PALETTE[512+(1*16)], 32);
  for (int x=4; x<28; x++) {
    BG_GFX_SUB[0x400 + x + ( 5*32)] = 0x1002;
    BG_GFX_SUB[0x400 + x + (16*32)] = 0x1005;
    BG_GFX_SUB[0x400 + x + (17*32)] = 0x1008;
    BG_GFX_SUB[0x400 + x + (18*32)] = 0x100B;
  }

  for (int y=6; y<16; y++) {
    BG_GFX_SUB[0x400 +  3 + (y*32)] = 0x1011;
    BG_GFX_SUB[0x400 + 28 + (y*32)] = 0x1014;

    for (int x=4; x<28; x++) {
      BG_GFX_SUB[0x400 + x + (y*32)] = 0x100E;
    }
  }

  BG_GFX_SUB[0x400 +  3 + ( 5*32)] = 0x100D;
  BG_GFX_SUB[0x400 + 28 + ( 5*32)] = 0x1003;
  BG_GFX_SUB[0x400 +  3 + (16*32)] = 0x1010;
  BG_GFX_SUB[0x400 + 28 + (16*32)] = 0x1006;
  BG_GFX_SUB[0x400 +  3 + (17*32)] = 0x1013;
  BG_GFX_SUB[0x400 + 28 + (17*32)] = 0x1009;
  BG_GFX_SUB[0x400 +  3 + (18*32)] = 0x1016;
  BG_GFX_SUB[0x400 + 28 + (18*32)] = 0x100C;


  u8 *sounddata = (u8*)GETRAW(dong_raw);
  for (int i=0; i<GETRAWSIZE(dong_raw); i++) {
    *sounddata += 128;
    sounddata++;
  }
  
  sounddata = (u8*)GETRAW(select_raw);
  for (int i=0; i<GETRAWSIZE(select_raw); i++) {
    *sounddata += 128;
    sounddata++;
  }

  for (int i=0; i<4; i++) {
    clicks[i] = new mndsClick((i*8*5)+20, this);
  }
  
  fade = new mndsFade();

  updateDisplay();
}



mndsMenu::~mndsMenu() {
  mndsGame *game = games.getFirstItem();
  while (game) {
    delete game;
    games.removeItem(game);
    game = games.getFirstItem();
  }
}




void mndsMenu::loadGame() {
  mndsGame *game = games.getItem(top+sel);
  if (!game) return;

  new dsSound(GETRAW(select_raw), GETRAWSIZE(select_raw)>>2, 11025);
  dsSound::updateIpcSound();

  for (int i=3; i<16; i++) {
    BLEND_AB      = (i<<8) | (16-i);
    SUB_BLEND_AB  = (i<<8) | (16-i);
    for (int x=0; x<2; x++) WaitForVblank();
  }

  videoSetMode(   MODE_3_2D | DISPLAY_BG2_ACTIVE | (2<<5));
  videoSetModeSub(MODE_3_2D | DISPLAY_BG2_ACTIVE | (2<<5));
  BLEND_CR     = BLEND_FADE_WHITE | BLEND_SRC_BG2 | BLEND_SRC_BACKDROP;
  SUB_BLEND_CR = BLEND_FADE_WHITE | BLEND_SRC_BG2 | BLEND_SRC_BACKDROP;

  for (int i=0; i<=16; i++) {
    BLEND_Y  = i;
    SUB_BLEND_Y  = i;
    for (int x=0; x<2; x++) WaitForVblank();
  }
  LOADNDS->ARM9FUNC(game->getFile()->name);
}




void mndsMenu::updateDisplay(u8 dir) {
  if (dir == 1) {
    new dsSound(GETRAW(dong_raw), GETRAWSIZE(dong_raw)>>2, 18000);
  } else if (dir == 2) {
    new dsSound(GETRAW(dong_raw), GETRAWSIZE(dong_raw)>>2, 22000);
  } else if (dir == 3) {
    new dsSound(GETRAW(dong_raw), GETRAWSIZE(dong_raw)>>2, 20000);
  }

  //restore palettes
  for (int i=1; i<5; i++) {
    PALETTE[i] = RGB(0,0,0);
    dmaCopyHalfWords(3, game_pal, &PALETTE[i*16], 32);
  }

  //setup palette fading
  fade->setPalette(sel+1);

  
  //clear buffer
  for (int i=0; i<256*192; i++) buffer[i] = 0;

  u8 count = 4;
  if (games.getItemCount() < 4) {
    count = games.getItemCount();
    up->hide();
    down->hide();
  } else {
    if (top == 0) up->hide(); else up->show();
    if (top == games.getItemCount()-4) down->hide(); else down->show();
  }

  for (int i=0; i<count; i++) {
    mndsGame *game = games.getItem(top+i);
    if (game) {
      dmaCopyHalfWords(3, game->getIcon(), sprites[i]->getMem(),    32*16);
      dmaCopyHalfWords(3, game->getPalette(), &PALETTE[256+16+(i*16)], 32);

      renderText(game->getTextData(0), buffer, 50, 20+(i*8*5), i+1);
      renderText(game->getFilename(),  buffer, 52, 34+(i*8*5), i+1);
    }
  }

  for (int i=count; i<4; i++) {
    dmaCopyHalfWords(3, zeros, sprites[i]->getMem(), 32*16);
    dmaCopyHalfWords(3, zeros, &PALETTE[256+16+(i*16)], 32);
  }

  cursors[0]->move( 11, (sel*8*5)+15);
  cursors[1]->move(229, (sel*8*5)+15);
  cursors[2]->move( 11, (sel*8*5)+41);
  cursors[3]->move(229, (sel*8*5)+41);

  WaitForVblank();
  sprmgr->updateSystemOAM();  //this will automatically flush cache
  dmaCopyHalfWords(3, buffer, &BG_GFX[0x4000], 64*1024);


  for (int i=0; i<256*192; i++) buffer[i] = 0;

  mndsGame *game = games.getItem(top+sel);
  if (game) {
    dmaCopyHalfWords(3, game->getIcon(), icon->getMem(), 32*16);
    dmaCopyHalfWords(3, game->getPalette(), &PALETTE[768+(5*16)], 32);

    renderText(game->getFilename(), buffer, 29, 134);

    renderText(game->getTextData(0), buffer, 27,  86);
    renderText(game->getTextData(1), buffer, 27, 101);
    renderText(game->getTextData(2), buffer, 27, 116);

    renderText(game->getGamecode(), buffer, 70, 44);

    char str[20] = "0x00000000 Offset";
    itoa(game->getOffset(), str+2);
    str[10] = ' ';
    renderText(str, buffer, 70, 56);

    memcpy(str, "0x00000000 Bytes", 17);
    itoa(game->getFilesize(), str+2);
    str[10] = ' ';
    renderText(str, buffer, 70, 68);
  }

  //version info
  {
    char str[9];
    renderText(itoa(LOADNDS->VERSION, str), buffer, 40, 177);
    renderText("Loader:", buffer, 2, 177);
    
    itoa(GUIVERSION, str);
    u32 w = getTextWidth(str);
    renderText(str, buffer, 253-w, 177);
    renderText("GUI:", buffer, 253-w-18, 177);
  }


  DC_FlushAll();
  dmaCopyHalfWords(3, buffer, &BG_GFX_SUB[0x4000], 64*1024);
}








void mndsClick::onClick(s16 x, s16 y) {
  menu->onClick(this);
}

