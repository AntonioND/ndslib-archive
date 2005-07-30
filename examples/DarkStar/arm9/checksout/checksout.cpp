/*****************************  DARKSTAR  ******************************\
*  Copyright (c) 2005 Vincent E. Milum Jr., All rights reserved.        *
*                                                                       *
*  See License.txt for more information                                 *
*                                                                       *
*  Latest source versions can be found at:  HTTP://WWW.DARKAIN.COM/     *
\***********************************************************************/


//library includes
#include <NDS/NDS.h>
#include <stdio.h>

//DarkStar includes
#include "../DarkStar/dsApp.h"
#include "../DarkStar/dsMainMenu.h"
#include <NDS/DarkStar/dsSound.h>

//local includes
#include "checksout.h"
#include "checksoutBox.h"
#include "checksoutLevel.h"

//resource data
#include "hover_raw.h"
#include "mines_pal.h"


static dsAppTemplate<dsChecksOut> dsChecksOutApp;
#define CHECKS_RANDOM 10


/*
PUZZLE LEVEL FORMAT:
u16 value per row.  bit 0 to bit 9 used for each square
10 u16's total, 1 for each row.

so, first tile would be u16 0, bit 0, next tile would be bit 1...
because of the way data is arranged in hex notation, left tiles
appear on the right hex values, and right tiles appear on the
left hex values.

rows are stored as 2 and a half nibbles (10 bits)

 0    1    2
1248 1248 12

0000 0000 00  row 0
0000 0000 00  row 1
0000 0000 00  row 2
0000 0000 00  row 3
0000 0000 00  row 4

0000 0000 00  row 5
0000 0000 00  row 6
0000 0000 00  row 7
0000 0000 00  row 8
0000 0000 00  row 9
*/

const u16 dsChecksOut::puzzle[][10] = {
  { //level 0, 8 clicks total
    0x0303, 0x0201, 0x0000, 0x0030, 0x0078,
    0x0078, 0x0030, 0x0000, 0x0201, 0x0303,
  },

  { //level 1, 20 clicks total
    0x0201, 0x0102, 0x0084, 0x0048, 0x0030,
    0x0030, 0x0048, 0x0084, 0x0102, 0x0201,
  },

  { //level 2, 20 clicks total
    0x0000, 0x00CC, 0x014A, 0x01B6, 0x0078,
    0x0078, 0x01B6, 0x014A, 0x00CC, 0x0000,
  },

  { //level 3, 8 clicks total
    0x0000, 0x0030, 0x0048, 0x00B4, 0x014A,
    0x014A, 0x00B4, 0x0048, 0x0030, 0x0000,
  },

  { //level 4, 28 clicks total
    0x0285, 0x00B4, 0x0333, 0x0000, 0x0186,
    0x0186, 0x0000, 0x0333, 0x00B4, 0x0285,
  },

  { //level 5, 12 clicks total
    0x0044, 0x01EE, 0x03D6, 0x017F, 0x00FA,
    0x017C, 0x03FA, 0x01AF, 0x01DE, 0x0088,
  },

  { //level 6, 16 clicks total
    0x0084, 0x0048, 0x0285, 0x017A, 0x0048,
    0x0048, 0x017A, 0x0285, 0x0048, 0x0084,
  },

  { //level 7, 20 clicks total
    0x011A, 0x03F7, 0x013A, 0x0125, 0x01C7,
    0x038E, 0x0292, 0x0172, 0x03BF, 0x0162,
  },

  { //level 8, 16 clicks total
    0x034B, 0x02FD, 0x014A, 0x03B7, 0x017A,
    0x017A, 0x03B7, 0x014A, 0x02FD, 0x034B,
  },

  { //level 9, 44 clicks total
    0x03FF, 0x03FF, 0x03FF, 0x03FF, 0x03FF,
    0x03FF, 0x03FF, 0x03FF, 0x03FF, 0x03FF,
  },
};


/////////////////////////////////////////////////////////////////////////////////


dsChecksOut::dsChecksOut() {
  clicks = 0;
  level  = -1;

  lastx  = 0xFF;
  lasty  = 0xFF;

  for (u32 y=0; y<10; y++) {
    for (u32 x=0; x<10; x++) {
      boxes[y][x] = new dsChecksOutBox((x+3)<<1, (y+2)<<1, this);
    }
  }


  levels[ 0] = new dsChecksOutLevel( 2, 4, 0, this);
  levels[ 1] = new dsChecksOutLevel( 6, 4, 1, this);
  levels[ 2] = new dsChecksOutLevel(10, 4, 2, this);
  levels[ 3] = new dsChecksOutLevel(14, 4, 3, this);
  levels[ 4] = new dsChecksOutLevel(18, 4, 4, this);

  levels[ 5] = new dsChecksOutLevel( 2, 8, 5, this);
  levels[ 6] = new dsChecksOutLevel( 6, 8, 6, this);
  levels[ 7] = new dsChecksOutLevel(10, 8, 7, this);
  levels[ 8] = new dsChecksOutLevel(14, 8, 8, this);
  levels[ 9] = new dsChecksOutLevel(18, 8, 9, this);

  levels[10] = new dsChecksOutLevel(2, 12, CHECKS_RANDOM, this);

  for (int i=0; i<11; i++) levels[i]->renderButton();

  dmaCopyWords(3, mines_pal, &PALETTE_SUB[0x130],  32);

  loadLevel(0);
}


dsChecksOut::~dsChecksOut() {
  for (int i=0; i<11; i++) delete levels[i];

  for (u32 y=0; y<10; y++) {
    for (u32 x=0; x<10; x++) {
      delete boxes[y][x];
    }
  }
}


void dsChecksOut::change(u8 x, u8 y) {
  new dsSound(GETRAW(hover_raw), GETRAWSIZE(hover_raw)>>2, 22050, 0x7F, x<<2);

  x = (x>>1)-3;
  y = (y>>1)-2;

  boxes[y][x]->invert();
  if (x > 0) boxes[y][x-1]->invert();
  if (x < 9) boxes[y][x+1]->invert();
  if (y > 0) boxes[y-1][x]->invert();
  if (y < 9) boxes[y+1][x]->invert();

  clicks++;
  updateText();

  u8 count = getCount();
  if (count == 0) {
    msgbox("ALL CLEARED");
  }
}


u8 dsChecksOut::getCount() {
  u8 val = 0;
  for (int y=0; y<10; y++) {
    for (int x=0; x<10; x++) {
      val += boxes[y][x]->getValue();
    }
  }
  return 100-val;
}


void dsChecksOut::loadLevel(s32 lvl) {
  level = lvl;

  for (int i=0; i<11; i++) levels[i]->selSelStyle(0, true);

  if (level == CHECKS_RANDOM) {
    levels[10]->selSelStyle(1, true);
    level = CHECKS_RANDOM;
    clicks = -100;
  }

  else {
    levels[level]->selSelStyle(1, true);
    clicks = 0;

    for (int y=0; y<10; y++) {
      for (int x=0; x<10; x++) {
        boxes[y][x]->setValue( !((puzzle[level][y] >> x) & 0x1) );
      }
    }
  }

  updateText();
}


void dsChecksOut::updateText() {
  char str[32];
  sprintf(str, "LEVEL %d - CLICKS %d", level, clicks);
  mainmenu->setName(str);
}


void dsChecksOut::onVBlank() {
  if (level == CHECKS_RANDOM) {
    if (clicks < 0) {
      u8 x = (dice(0, 9)+3)<<1;
      u8 y = (dice(0, 9)+2)<<1;

      while (x == lastx && y == lasty) {
        x = (dice(0, 9)+3)<<1;
        y = (dice(0, 9)+2)<<1;
      }

      lastx = x;
      lasty = y;
      change(x, y);
    }
  }
}


void dsChecksOut::onButtonPress(u8 id) {
  loadLevel(level+1);
}

