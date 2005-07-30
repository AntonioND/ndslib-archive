/*****************************  DARKSTAR  ******************************\
*  Copyright (c) 2005 Vincent E. Milum Jr., All rights reserved.        *
*                                                                       *
*  See License.txt for more information                                 *
*                                                                       *
*  Latest source versions can be found at:  HTTP://WWW.DARKAIN.COM/     *
\***********************************************************************/


//libs
#include <NDS/NDS.h>
#include <stdio.h>

//common includes
#include "../common.h"

//DarkStar includes
#include "../DarkStar/dsApp.h"
#include <NDS/DarkStar/dsSound.h>
#include "../DarkStar/dsMainMenu.h"

//local includes
#include "mines.h"

//resource data
#include "menu_raw.h"
#include "mines_raw.h"
#include "mines2_raw.h"
#include "mines_pal.h"
#include "mines2_pal.h"
#include "explode_raw.h"
#include "flip_raw.h"


static dsAppTemplate<dsMines> dsMinesApp;
static const char dsMineFlagName[] = "FLAG";


dsMines::dsMines() : dsClickRect(4, 20, 243, 179, DS_SCREEN_MAIN) {
  generated = false;
  bombed = false;
  flagcount = 0;

  movescreen = new dsMinesMoveScreen(this);

  scroll = new dsMinesScroll(this);
  scroll->setHorzPos(14);
  scroll->setVertPos(9);
  xoff = 0;
  yoff = 0;

  BG2_X0 = 0x04;
  BG2_Y0 = 0x04;

  for (u32 y=0; y<22; y++) {
    for (u32 x=0; x<32; x++) {
      mine[y][x] = 0;
      BG_GFX_SUB[0x800 + ((y+2)*32)+x] = 0x0011;
    }
  }

  dmaCopyWords(3, mines_raw,  &BG_GFX[0x2A00],     1792);
  dmaCopyWords(3, mines_pal,  &PALETTE[0x30],      32);
  dmaCopyWords(3, mines2_raw, &BG_GFX_SUB[0x2A00], 448);
  dmaCopyWords(3, mines2_pal, &PALETTE_SUB[0x30],  32);

  corner[0] = new dsSpriteSingle(DS_CORE_SUB, &menu_raw[352], SIZE_8_X_8, false, 1);
  corner[1] = new dsSpriteSingle(DS_CORE_SUB, &menu_raw[352], SIZE_8_X_8, false, 1);
  corner[2] = new dsSpriteSingle(DS_CORE_SUB, &menu_raw[352], SIZE_8_X_8, false, 1);
  corner[3] = new dsSpriteSingle(DS_CORE_SUB, &menu_raw[352], SIZE_8_X_8, false, 1);
  corner[0]->setFlip(FLIP_NONE);
  corner[1]->setFlip(FLIP_HORZ);
  corner[2]->setFlip(FLIP_VERT);
  corner[3]->setFlip(FLIP_BOTH);

  flagbox = new dsToggleBox(dsMineFlagName);
  flagbox->resizeBox(5, 2);
  mainmenu->appendBox(flagbox);

  renderField();
  updateText();
}


dsMines::~dsMines() {
  mainmenu->removeBox(flagbox);
  delete flagbox;

  for (u32 y=0; y<22; y++) {
    for (u32 x=0; x<32; x++) {
      BG_GFX[    0x800 + ((y+2)*32)+x] = 0x0000;
      BG_GFX_SUB[0x800 + ((y+2)*32)+x] = 0x0000;
    }
  }

  for (int i=0; i<4; i++) delete corner[i];

  delete movescreen;
  delete scroll;

  BG2_X0 = 0x00;
  BG2_Y0 = 0x00;
}


void dsMines::flagMine(u8 x, u8 y) {
  if (bombed) return;

  x += xoff;
  y += yoff;
  u8 val = mine[y][x];
  if (val & 0x80) return;

  if (val & 0x40) {  //is it already flagged?
    flagcount--;
    val &= 0x3F;
  } else {
    flagcount++;
    val |= 0x40;
  }


  mine[y][x] = val;
  uncover(x, y);
  renderField();
  updateText();
}


void dsMines::checkMine(u8 x, u8 y) {
  if (bombed) return;
  x += xoff;
  y += yoff;

  if (!generated) generateMap(x, y);
  if (mine[y][x] & 0x80) return;  //i forget why we need this check?
  if (mine[y][x] & 0x40) return;  //return if its a flag
  uncoverSet(x, y);

  //we found a bomb... game over!!
  if (mine[y][x] == 0x8F) {
    mine[y][x] = 0x8E;
    uncover(x, y);  //repaint to show it was the blown up mine
    new dsSound(GETRAW(explode_raw), GETRAWSIZE(explode_raw)>>2, 11025);

    bombed = true;
    for (int iy=0; iy<22; iy++) {
      for (int ix=0; ix<32; ix++) {
        if (mine[iy][ix] == 0xF) {
          mine[iy][ix] = 0x8F;
          uncover(ix, iy);
        } else if ( (mine[iy][ix] & 0x40) && ((mine[iy][ix] & 0xF)!=0xF) ) {
          uncover(ix, iy);
        }
      }
    }
  }

  else {  //not a mine, so normal flip sound
    new dsSound(GETRAW(flip_raw), GETRAWSIZE(flip_raw)>>2, 22050);
  }

  renderField();
}


void dsMines::uncover(u8 x, u8 y) {
  u8 val = mine[y][x];

  u16 *tile = &BG_GFX_SUB[0x800 + ((y+2)*32)+x];

  if (val == 0x80) {        //blank tile
    *tile = 0x0000;

  } else if (val & 0x40) {  //flag
    if ( bombed && ((val & 0xf) != 0xF) ) {
      *tile = 173 | 0x3000;
    } else {
      *tile = 172 | 0x3000;
    }

  } else if (val == 0x8E) { //blown up bomb
    *tile = 171 | 0x3000;

  } else if (val == 0x8F) { //bomb
    *tile = 170 | 0x3000;

  } else if (val & 0x80) {  //number
    *tile = 160 + (val & 0xF) | 0x3000;

  } else {                  //covered tile
    *tile = 0x0011;
  }
}


void dsMines::uncoverSet(u8 x, u8 y) {
  mine[y][x] |= 0x80;
  uncover(x, y);
  if (mine[y][x] != 0x80)  return;

  if (x >  0) if (mine[y][x-1] < 0x9) uncoverSet(x-1, y);
  if (x < 31) if (mine[y][x+1] < 0x9) uncoverSet(x+1, y);
  if (y >  0) if (mine[y-1][x] < 0x9) uncoverSet(x, y-1);
  if (y < 21) if (mine[y+1][x] < 0x9) uncoverSet(x, y+1);

  if ((x >  0) && (y >  0)) if (mine[y-1][x-1] < 0x9) uncoverSet(x-1, y-1);
  if ((x < 31) && (y >  0)) if (mine[y-1][x+1] < 0x9) uncoverSet(x+1, y-1);
  if ((x >  0) && (y < 21)) if (mine[y+1][x-1] < 0x9) uncoverSet(x-1, y+1);
  if ((x < 31) && (y < 21)) if (mine[y+1][x+1] < 0x9) uncoverSet(x+1, y+1);
}


void dsMines::generateMap(u8 x, u8 y) {
  int count = 100;

  while (count > 0) {
    int mx = dice(0, 31);
    int my = dice(0, 21);
    u8 val = mine[my][mx];
    if ( (mx != x) || (my != y) && ((val & 0xF) == 0x0) ) {
      mine[my][mx] = 0x0F | val;
      count--;
    }
  }

  for (int iy=0; iy<22; iy++) {
    for (int ix=0; ix<32; ix++) {
      if ((mine[iy][ix] & 0xF) == 0x0) {
        int val = 0;
        
        if (ix >  0) if (mine[iy][ix-1] == 0xF) val++;
        if (ix < 31) if (mine[iy][ix+1] == 0xF) val++;
        if (iy >  0) if (mine[iy-1][ix] == 0xF) val++;
        if (iy < 21) if (mine[iy+1][ix] == 0xF) val++;

        if ((ix >  0) && (iy >  0)) if (mine[iy-1][ix-1] == 0xF) val++;
        if ((ix < 31) && (iy >  0)) if (mine[iy-1][ix+1] == 0xF) val++;
        if ((ix >  0) && (iy < 21)) if (mine[iy+1][ix-1] == 0xF) val++;
        if ((ix < 31) && (iy < 21)) if (mine[iy+1][ix+1] == 0xF) val++;

        mine[iy][ix] = val;
      }
    }
  }

  generated = true;
}


void dsMines::renderField() {
  xoff = (scroll->getHorzPos()*10) >> 4;
  yoff = (scroll->getVertPos()*11) >> 4;

  corner[0]->move((xoff+ 0)<<3, (yoff+ 2)<<3);
  corner[1]->move((xoff+14)<<3, (yoff+ 2)<<3);
  corner[2]->move((xoff+ 0)<<3, (yoff+11)<<3);
  corner[3]->move((xoff+14)<<3, (yoff+11)<<3);

  u16 *tile = &BG_GFX[0x800 + (3*32)+1];

  for (int y=0; y<10; y++) {
    for (int x=0; x<15; x++) {
      u8 val = mine[y+yoff][x+xoff];
      if (val & 0x40) {            //show flag
        int base;
        if ( bombed && ((val & 0xF) != 0xF) ) {
          base = 160 + (13 * 4);
        } else {
          base = 160 + (12 * 4);
        }
        tile[0x00] = base+0 | 0x3000;
        tile[0x01] = base+1 | 0x3000;
        tile[0x20] = base+2 | 0x3000;
        tile[0x21] = base+3 | 0x3000;
      }

      else if (val == 0x8E) {      //show blown up bonb
        int base = 160 + (11 * 4);
        tile[0x00] = base+0 | 0x3000;
        tile[0x01] = base+1 | 0x3000;
        tile[0x20] = base+2 | 0x3000;
        tile[0x21] = base+3 | 0x3000;
      }

      else if (val == 0x8F) {      //show bonb
        int base = 160 + (10 * 4);
        tile[0x00] = base+0 | 0x3000;
        tile[0x01] = base+1 | 0x3000;
        tile[0x20] = base+2 | 0x3000;
        tile[0x21] = base+3 | 0x3000;
      }

      else if (val == 0x80) {      //blank tile
        tile[0x00] = 0x0000;
        tile[0x01] = 0x0000;
        tile[0x20] = 0x0000;
        tile[0x21] = 0x0000;
      }

      else if (val & 0x80) {       //show tile number
        int base = 160 + ((val & 0xF) * 4);
        tile[0x00] = base+0 | 0x3000;
        tile[0x01] = base+1 | 0x3000;
        tile[0x20] = base+2 | 0x3000;
        tile[0x21] = base+3 | 0x3000;
      }
      
      else {                       //hidden tile
        tile[0x00] = 0x0009;
        tile[0x01] = 0x0006;
        tile[0x20] = 0x0008;
        tile[0x21] = 0x0007;
      }
      tile += 2;
    }
    tile += 34;
  }
}


void dsMines::updateText() {
  char str[32];
  sprintf(str, "MINES: %d", 100-flagcount);
  mainmenu->setName(str);
}


void dsMines::onClick(s16 x, s16 y) {
  x = (x -  4) >> 4;
  y = (y - 20) >> 4;

  if (flagbox->getBoxPushed()) {
    flagMine(x, y);
  } else {
    checkMine(x, y);
  }
}


void dsMines::onKeyChange(u32 inputState, u32 lastState) {
  if ( (lastState & KEY_UP) && (!(inputState & KEY_UP)) ) {
    scroll->setVertPos(scroll->getVertPos()-1);
    renderField();
  } else if ( (lastState & KEY_DOWN) && (!(inputState & KEY_DOWN)) ) {
    scroll->setVertPos(scroll->getVertPos()+1);
    renderField();
  }

  if ( (lastState & KEY_LEFT) && (!(inputState & KEY_LEFT)) ) {
    scroll->setHorzPos(scroll->getHorzPos()-1);
    renderField();
  } else if ( (lastState & KEY_RIGHT) && (!(inputState & KEY_RIGHT)) ) {
    scroll->setHorzPos(scroll->getHorzPos()+1);
    renderField();
  }

  if ( (lastState & KEY_B) && (!(inputState & KEY_B)) ) {
    flagbox->toggleBox(true);
  }
}


void dsMines::move(s16 x, s16 y) {
  x = (x- 8) >> 3;
  y = (y-24) >> 3;

  scroll->setHorzPos(x);
  scroll->setVertPos(y);

  renderField();
}
