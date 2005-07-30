/*****************************  DARKSTAR  ******************************\
*  Copyright (c) 2005 Vincent E. Milum Jr., All rights reserved.        *
*                                                                       *
*  See License.txt for more information                                 *
*                                                                       *
*  Latest source versions can be found at:  HTTP://WWW.DARKAIN.COM/     *
\***********************************************************************/


//libs
#include <NDS/NDS.h>

//local includes
#include "dsBox.h"
#include "dsMainMenu.h"


//  tl      tr      bl      br      t       b       l       r
u16 dsBox::boxStyle[4][9] = {
  { 0x0009, 0x0006, 0x0008, 0x0007, 0x0002, 0x0004, 0x0005, 0x0003, 0x0001 },  // 0 box
  { 0x0C07, 0x0C08, 0x0C06, 0x0C09, 0x0C04, 0x0C02, 0x0C03, 0x0C05, 0x0001 },  // 1 box inverted
  { 0x0015, 0x0016, 0x0017, 0x0018, 0x0002, 0x0004, 0x0005, 0x0003, 0x0001 },  // 2 rounded
  { 0x0C18, 0x0C17, 0x0C16, 0x0C15, 0x0C04, 0x0C02, 0x0C03, 0x0C05, 0x0001 },  // 3 rounded inverted
};


dsBox::dsBox(const char *btext, DS_STYLE bstyle) {
  if (mainmenu) buffers = mainmenu->getActiveBuffer(); else buffers = NULL;
  boxx=0;  boxy=0;
  boxw=0;  boxh=0;
  txtx=0;  txty=0;
  text  = btext;
  style = bstyle;
}


dsBox::dsBox(s16 bx, s16 by, s16 bw, s16 bh, const char *btext, DS_STYLE bstyle) {
  if (mainmenu) buffers = mainmenu->getActiveBuffer(); else buffers = NULL;
  boxx=bx;  boxy=by;
  boxw=bw;  boxh=bh;
  txtx=0;   txty=0;
  text  = btext;
  style = bstyle;
}


dsBox::~dsBox() {
  if (style != DS_STYLE_NONE) eraseButton();
}



void dsBox::renderText(u16 *buffer, DS_TEXT_COLOR color) {
  drawText( text, &buffer[((boxy+txty)*32) + boxx + txtx + 0x400], (color==DS_TEXT_COLOR_NORMAL)?1:2 );
}


void dsBox::renderBox(u16 *buffer) {
  u16 *bgbuff = &buffer[((boxy)*32) + boxx];
  u16 btw = boxw - 1;
  u16 bth = boxh - 2;

  bgbuff[0]   = boxStyle[style][0];
  bgbuff[btw] = boxStyle[style][1];
  for (int x=1; x<btw; x++) {
    bgbuff[x] = boxStyle[style][4];
  }
  bgbuff += 32;

  for (int y=0; y<bth; y++) {
    bgbuff[0]   = boxStyle[style][6];
    bgbuff[btw] = boxStyle[style][7];
    for (int x=1; x<btw; x++) {
      bgbuff[x] = boxStyle[style][8];
    }
    bgbuff += 32;
  }

  bgbuff[0]   = boxStyle[style][2];
  bgbuff[btw] = boxStyle[style][3];
  for (int x=1; x<btw; x++) {
    bgbuff[x] = boxStyle[style][5];
  }
}


void dsBox::eraseBox() {
  u16 *bgbuff = &buffers[((boxy)*32) + boxx];

  for (int y=0; y<boxh; y++) {
    for (int x=0; x<boxw; x++) {
      bgbuff[x]  = 0x0000;
    }
    bgbuff  += 32;
  }
}


void dsBox::eraseText() {
  u16 *textbuf = &buffers[((boxy+txty)*32) + boxx + txtx + 0x400];

  for (int y=0; y<boxh-1; y++) {
    for (int x=0; x<boxw-1; x++) {
      textbuf[x] = 0x0000;
    }
    textbuf += 32;
  }
}


void dsBox::resizeBox(s16 bw, s16 bh) {
  boxw = bw;
  boxh = bh;
}


void dsBox::moveBox(s16 bx, s16 by) {
  boxx = bx;
  boxy = by;
}

void dsBox::moveResizeBox(s16 bx, s16 by, s16 bw, s16 bh) {
  boxx=bx;  boxy=by;
  boxw=bw;  boxh=bh;
}

void dsBox::moveText(s16 tx, s16 ty) {
  txtx = tx;
  txty = ty;
}



///////////////////////////////////////////////////////////////////////////////////////////


dsToggleBox::dsToggleBox(const char *btext, DS_STYLE bstyle0, DS_STYLE bstyle1)
 : dsBox(btext, bstyle0) {
  screen = DS_SCREEN_BOTH;
  styles[0] = bstyle0;
  styles[1] = bstyle1;
  sel = 0;
}


dsToggleBox::dsToggleBox(s16 bx, s16 by, s16 bw, s16 bh, const char *btext, DS_STYLE bstyle0, DS_STYLE bstyle1)
 : dsBox(bx, by, bw, bh, btext, bstyle0) {
  screen = DS_SCREEN_BOTH;
  styles[0] = bstyle0;
  styles[1] = bstyle1;
  sel = 0;
}


void dsToggleBox::toggleBox(bool repaint) {
  sel = (sel==0) ? 1 : 0;
  setStyle(styles[sel]);
  if (repaint) renderBox();
}


void dsToggleBox::selSelStyle(u8 which, bool repaint) {
  sel = !!which;
  setStyle(styles[sel]);
  if (repaint) renderBox();
}


bool dsToggleBox::hitTest(s16 x, s16 y, DS_SCREEN iscreen) {
  if (screen & 0x80) return false;
  if (x < (getBoxX()<<3)) return false;
  if (y < (getBoxY()<<3)) return false;
  if (x > ((getBoxX()+getBoxWidth())<<3)) return false;
  if (y > ((getBoxY()+getBoxHeight())<<3)) return false;
  return (screen & iscreen & 0x03) > 0;
}


///////////////////////////////////////////////////////////////////////////////////////////


dsButton::dsButton(const char *btext, DS_STYLE bstyle0, DS_STYLE bstyle1)
 : dsToggleBox(btext, bstyle0, bstyle1){
}

dsButton::dsButton(s16 bx, s16 by, s16 bw, s16 bh, const char *btext, DS_STYLE bstyle0, DS_STYLE bstyle1)
 : dsToggleBox(bx, by, bw, bh, btext, bstyle0, bstyle1) {
}

void dsButton::onClick(s16 x, s16 y) {
  selSelStyle(1, true);
}

void dsButton::onDrag(s16 x, s16 y) {
  if (hitTest(x, y, DS_SCREEN_BOTH)) {
    selSelStyle(1, true);
  } else {
    selSelStyle(0, true);
  }
}

void dsButton::onDrop(s16 x, s16 y) {
  selSelStyle(0, true);
  if (hitTest(x, y, DS_SCREEN_BOTH)) {
    onButton();
  }
}
