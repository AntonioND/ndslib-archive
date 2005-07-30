/*****************************  DARKSTAR  ******************************\
*  Copyright (c) 2005 Vincent E. Milum Jr., All rights reserved.        *
*                                                                       *
*  See License.txt for more information                                 *
*                                                                       *
*  Latest source versions can be found at:  HTTP://WWW.DARKAIN.COM/     *
\***********************************************************************/


//library
#include <NDS/NDS.h>

//common includes
#include "../common.h"

//local includes
#include "ttt.h"


//resource data
#include "ttt_raw.h"
#include "ttt_pal.h"


static dsAppTemplate<dsTTT> dsTTTApp;



u8 tttWin[8][3] = {
  {0, 1, 2},
  {3, 4, 5},
  {6, 7, 8},

  {0, 3, 6},
  {1, 4, 7},
  {2, 5, 8},

  {0, 4, 8},
  {6, 4, 2},
};


u8 tttAI1[4] = { 0, 2, 6, 8, };
u8 tttAI2[5] = { 1, 3, 5, 7, 4, };


dsTTT::dsTTT() {
  count = 0;
  lock  = false;
  start = false;

  for (int y=0; y<3; y++) {
    for (int x=0; x<3; x++) {
      btn[(y*3)+x] = new dsTTTButton(x, y, this);
    }
  }

  
  for (int x=6; x<26; x++) {
    BG_GFX[0x800 + ( 9*32)+x] = 0x0014;
    BG_GFX[0x800 + (16*32)+x] = 0x0014;
  }

  for (int y=3; y<23; y++) {
    BG_GFX[0x800 + (y*32)+12] = 0x0010;
    BG_GFX[0x800 + (y*32)+19] = 0x0010;
  }

  BG_GFX[0x800 + ( 9*32)+12]  = 0x0011;
  BG_GFX[0x800 + ( 9*32)+19]  = 0x0011;
  BG_GFX[0x800 + (16*32)+12]  = 0x0011;
  BG_GFX[0x800 + (16*32)+19]  = 0x0011;

  dmaCopyWords(3, ttt_raw,  &BG_GFX[0x2A00], 2304);
  dmaCopyWords(3, ttt_pal,  &PALETTE[0x30], 32);
}


dsTTT::~dsTTT() {
  for (int i=0; i<9; i++) {
    delete btn[i];
  }

  for (int y=2; y<24; y++) {
    for (int x=0; x<32; x++) {
      BG_GFX[0x800 + (y*32)+x] = 0;
    }
  }
}


void dsTTT::resetGame() {
  count = 0;
  lock = false;

  for (int i=0; i<9; i++) {
    btn[i]->setTile(0);
  }
}


void dsTTT::onButtonPress(u8 id) {
  resetGame();
  start = !start;
  if (start) AI();
}


void dsTTT::AI() {
  if (lock) return;
  count++;

  //did you win?
  for (int i=0; i<8; i++) {
    if (btn[tttWin[i][0]]->getVal()==1 && btn[tttWin[i][1]]->getVal()==1 && btn[tttWin[i][2]]->getVal()==1) { msgbox("YOU WIN"); lock=true; return; }
  }

  if (count == 5) {
    msgbox("TIE GAME");
    lock = true;
    return;
  }

  //can i win?
  for (int i=0; i<8; i++) {
    if (btn[tttWin[i][0]]->getVal()==2 && btn[tttWin[i][1]]->getVal()==2 && btn[tttWin[i][2]]->getVal()==0) { msgbox("DS WINS"); lock=true; btn[tttWin[i][2]]->setTile(2); return; }
    if (btn[tttWin[i][0]]->getVal()==2 && btn[tttWin[i][1]]->getVal()==0 && btn[tttWin[i][2]]->getVal()==2) { msgbox("DS WINS"); lock=true; btn[tttWin[i][1]]->setTile(2); return; }
    if (btn[tttWin[i][0]]->getVal()==0 && btn[tttWin[i][1]]->getVal()==2 && btn[tttWin[i][2]]->getVal()==2) { msgbox("DS WINS"); lock=true; btn[tttWin[i][0]]->setTile(2); return; }
  }

  //can i stop you from winning?
  for (int i=0; i<8; i++) {
    if (btn[tttWin[i][0]]->getVal()==1 && btn[tttWin[i][1]]->getVal()==1 && btn[tttWin[i][2]]->getVal()==0) { btn[tttWin[i][2]]->setTile(2); return; }
    if (btn[tttWin[i][0]]->getVal()==1 && btn[tttWin[i][1]]->getVal()==0 && btn[tttWin[i][2]]->getVal()==1) { btn[tttWin[i][1]]->setTile(2); return; }
    if (btn[tttWin[i][0]]->getVal()==0 && btn[tttWin[i][1]]->getVal()==1 && btn[tttWin[i][2]]->getVal()==1) { btn[tttWin[i][0]]->setTile(2); return; }
  }

  //okies, its my turn... random guessing time?  ;)
  if (count == 1) {
    if ( btn[tttAI1[0]]->getVal()==1 || btn[tttAI1[1]]->getVal()==1
      || btn[tttAI1[2]]->getVal()==1 || btn[tttAI1[3]]->getVal()==1 ) {
      btn[4]->setTile(2);
      return;
    }
  }

  if (count == 2) {
    u32 total = 0;
    for (int i=0; i<4; i++) if (btn[tttAI1[i]]->getVal()==1) total++;

    if (total == 2) {
      while (1) {
        int check = dice(0, 4);
        if (btn[tttAI2[check]]->getVal()==0) {
          btn[tttAI2[check]]->setTile(2);
          return;
        }
      }
    }

    total = 0;
    for (int i=0; i<4; i++) if (btn[tttAI2[i]]->getVal()==1) total++;

    if (total == 2) {
      if (btn[tttAI2[4]]->getVal()==0) {
        btn[tttAI2[4]]->setTile(2);
        return;
      }
    }
  }


  if ( btn[tttAI1[0]]->getVal()==0 || btn[tttAI1[1]]->getVal()==0
    || btn[tttAI1[2]]->getVal()==0 || btn[tttAI1[3]]->getVal()==0 ) {
    while (1) {
      int check = dice(0, 3);
      if (btn[tttAI1[check]]->getVal()==0) {
        btn[tttAI1[check]]->setTile(2);
        return;
      }
    }
  }

  while (1) {
    int check = dice(0, 4);
    if (btn[tttAI2[check]]->getVal()==0) {
      btn[tttAI2[check]]->setTile(2);
      return;
    }
  }
}


///////////////////////////////////////////////////////////////////////////


dsTTTButton::dsTTTButton(u8 ix, u8 iy, dsTTT *dsttt) : dsClickRect((ix*7*8)+48, (iy*7*8)+24, (ix*7*8)+48+48, (iy*7*8)+24+48) {
  x = ix;
  y = iy;
  ttt = dsttt;
  val = 0;
}


dsTTTButton::~dsTTTButton() {
}


void dsTTTButton::setTile(u8 value) {
  val = value;

  if (val == 0) {
    for (int yy=0; yy<6; yy++) {
      for (int xx=0; xx<6; xx++) {
        BG_GFX[0x800 + ((yy+(y*7)+3)*32)+xx+(x*7)+6] = 0;
      }
    }
  }
  
  else {
    int base = 160 + ((val-1) * 36);

    for (int yy=0; yy<6; yy++) {
      for (int xx=0; xx<6; xx++) {
        BG_GFX[0x800 + ((yy+(y*7)+3)*32)+xx+(x*7)+6] = (base++) | 0x3000;
      }
    }
  }
}


void dsTTTButton::onClick(s16 x, s16 y) {
  if (val != 0) return;
  if (ttt->getLock()) return;
  setTile(1);
  ttt->AI();
}
