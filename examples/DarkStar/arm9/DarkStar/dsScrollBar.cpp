/*****************************  DARKSTAR  ******************************\
*  Copyright (c) 2005 Vincent E. Milum Jr., All rights reserved.        *
*                                                                       *
*  See License.txt for more information                                 *
*                                                                       *
*  Latest source versions can be found at:  HTTP://WWW.DARKAIN.COM/     *
\***********************************************************************/


#include <NDS/NDS.h>

#include "../common.h"

#include "dsScrollBar.h"


dsScrollBarHorz::dsScrollBarHorz() : dsClickRect(0, 184, 255, 191, DS_SCREEN_MAIN) {
  horzpos = 0;
  drag = 0;

  BG_GFX[(23*32)+ 0] = 0x0012;
  BG_GFX[(23*32)+31] = 0x0013;

  for (int i=1; i<31; i++) {
    BG_GFX[(23*32)+i] = 0x0C14;
  }

  BG_GFX[(23*32)+horzpos+1] = 0x0011;
}


dsScrollBarHorz::~dsScrollBarHorz() {
  for (int i=0; i<32; i++) {
    BG_GFX[(23*32)+i] = 0x0000;
  }
}


void dsScrollBarHorz::onClick(s16 x, s16 y) {
  if (x < 8) {
    BG_GFX[(23*32)+ 0] = 0x0C13;
    BG_GFX[(23*32)+horzpos+1] = 0x0C14;
    if (horzpos > 0) horzpos--;
    BG_GFX[(23*32)+horzpos+1] = 0x0011;
  } else if (x > 256-8) {
    BG_GFX[(23*32)+31] = 0x0C12;
    BG_GFX[(23*32)+horzpos+1] = 0x0C14;
    if (horzpos < 29) horzpos++;
    BG_GFX[(23*32)+horzpos+1] = 0x0011;
  } else {
    BG_GFX[(23*32)+horzpos+1] = 0x0C14;
    horzpos = (x>>3) - 1;
    horzpos = min(max(horzpos, 0), 29);
    BG_GFX[(23*32)+horzpos+1] = 0x0C11;
    drag = 1;
  }
  onScrollHorz();
}


void dsScrollBarHorz::onDrag(s16 x, s16 y) {
  if (drag == 1) {
    BG_GFX[(23*32)+horzpos+1] = 0x0C14;
    horzpos = (x>>3) - 1;
    horzpos = min(max(horzpos, 0), 29);
    BG_GFX[(23*32)+horzpos+1] = 0x0C11;
  }
  onScrollHorz();
}


void dsScrollBarHorz::onDrop(s16 x, s16 y) {
  BG_GFX[(23*32)+ 0] = 0x0012;
  BG_GFX[(23*32)+31] = 0x0013;
  if (drag == 1) {
    BG_GFX[(23*32)+horzpos+1] = 0x0C14;
    horzpos = (x>>3) - 1;
    horzpos = min(max(horzpos, 0), 29);
    BG_GFX[(23*32)+horzpos+1] = 0x0011;
    drag = 0;
  }
  onScrollHorz();
}


void dsScrollBarHorz::setHorzPos(int pos) {
  BG_GFX[(23*32)+horzpos+1] = 0x0C14;
  horzpos = min(max(pos, 0), 29);
  BG_GFX[(23*32)+horzpos+1] = 0x0011;
}


////////////////////////////////////////////////////////////////////////


dsScrollBarVert::dsScrollBarVert() : dsClickRect(248, 16, 255, 191, DS_SCREEN_MAIN) {
  vertpos = 0;
  drag = 0;

  BG_GFX[( 2*32)+31] = 0x000E;
  BG_GFX[(23*32)+31] = 0x000F;

  for (int i=3; i<23; i++) {
    BG_GFX[(i*32)+31] = 0x0C10;
  }

  BG_GFX[((vertpos+3)*32)+31] = 0x0011;
}


dsScrollBarVert::~dsScrollBarVert() {
  for (int i=3; i<24; i++) {
    BG_GFX[(i*32)+31] = 0x0000;
  }
}


void dsScrollBarVert::onClick(s16 x, s16 y) {
  if (y < 24) {
    BG_GFX[( 2*32)+31] = 0x0C0F;
    BG_GFX[((vertpos+3)*32)+31] = 0x0C10;
    if (vertpos > 0) vertpos--;
    BG_GFX[((vertpos+3)*32)+31] = 0x0011;
  } else if (y > 183) {
    BG_GFX[(23*32)+31] = 0x0C0E;
    BG_GFX[((vertpos+3)*32)+31] = 0x0C10;
    if (vertpos < 19) vertpos++;
    BG_GFX[((vertpos+3)*32)+31] = 0x0011;
  } else {
    BG_GFX[((vertpos+3)*32)+31] = 0x0C10;
    vertpos = (y>>3) - 3;
    vertpos = min(max(vertpos, 0), 19);
    BG_GFX[((vertpos+3)*32)+31] = 0x0C11;
    drag = 1;
  }
  onScrollVert();
}


void dsScrollBarVert::onDrag(s16 x, s16 y) {
  if (drag == 1) {
    BG_GFX[((vertpos+3)*32)+31] = 0x0C10;
    vertpos = (y>>3) - 3;
    vertpos = min(max(vertpos, 0), 19);
    BG_GFX[((vertpos+3)*32)+31] = 0x0C11;
  }
  onScrollVert();
}


void dsScrollBarVert::onDrop(s16 x, s16 y) {
  BG_GFX[( 2*32)+31] = 0x000E;
  BG_GFX[(23*32)+31] = 0x000F;
  if (drag == 1) {
    BG_GFX[((vertpos+3)*32)+31] = 0x0C10;
    vertpos = (y>>3) - 3;
    vertpos = min(max(vertpos, 0), 19);
    BG_GFX[((vertpos+3)*32)+31] = 0x0011;
    drag = 0;
  }
  onScrollVert();
}


void dsScrollBarVert::setVertPos(int pos) {
  BG_GFX[((vertpos+3)*32)+31] = 0x0C10;
  vertpos = min(max(pos, 0), 19);
  BG_GFX[((vertpos+3)*32)+31] = 0x0011;
}


////////////////////////////////////////////////////////////////////////


dsScrollBarBoth::dsScrollBarBoth() : dsClickRect(0, 0, 0, 0, DS_SCREEN_NONE) {
  horzpos = 0;
  vertpos = 0;
  drag = 0;

  //bottom scroll bar
  BG_GFX[(23*32)+ 0] = 0x0012;
  BG_GFX[(23*32)+30] = 0x0013;

  for (int i=1; i<30; i++) {
    BG_GFX[(23*32)+i] = 0x0C14;
  }

  BG_GFX[(23*32)+horzpos+1] = 0x0011;

  
  //right scroll bar
  BG_GFX[( 2*32)+31] = 0x000E;
  BG_GFX[(22*32)+31] = 0x000F;

  for (int i=3; i<22; i++) {
    BG_GFX[(i*32)+31] = 0x0C10;
  }

  BG_GFX[((vertpos+3)*32)+31] = 0x0011;

  
  //unused corner tile
  BG_GFX[(23*32)+31] = 0x007;
}



dsScrollBarBoth::~dsScrollBarBoth() {
  //bottom scroll bar
  for (int i=0; i<32; i++) {
    BG_GFX[(23*32)+i] = 0x0000;
  }

  //right scroll bar
  //we go to 23, because the corner is erased in first loop
  for (int i=2; i<23; i++) {
    BG_GFX[(i*32)+31] = 0x0000;
  }
}



void dsScrollBarBoth::onClick(s16 x, s16 y) {
  if (x <248) {  //bottom scroll bar
    if (x < 8) {
      BG_GFX[(23*32)+ 0] = 0x0C13;
      BG_GFX[(23*32)+horzpos+1] = 0x0C14;
      if (horzpos > 0) horzpos--;
      BG_GFX[(23*32)+horzpos+1] = 0x0011;
    } else if (x > 239) {
      BG_GFX[(23*32)+30] = 0x0C12;
      BG_GFX[(23*32)+horzpos+1] = 0x0C14;
      if (horzpos < 28) horzpos++;
      BG_GFX[(23*32)+horzpos+1] = 0x0011;
    } else {
      BG_GFX[(23*32)+horzpos+1] = 0x0C14;
      horzpos = (x>>3) - 1;
      horzpos = min(max(horzpos, 0), 28);
      BG_GFX[(23*32)+horzpos+1] = 0x0C11;
      drag = 1;
    }
    onScrollHorz();
  }

  else {  //right scroll bar
    if (y < 24) {
      BG_GFX[( 2*32)+31] = 0x0C0F;
      BG_GFX[((vertpos+3)*32)+31] = 0x0C10;
      if (vertpos > 0) vertpos--;
      BG_GFX[((vertpos+3)*32)+31] = 0x0011;
    } else if (y > 175) {
      BG_GFX[(22*32)+31] = 0x0C0E;
      BG_GFX[((vertpos+3)*32)+31] = 0x0C10;
      if (vertpos < 18) vertpos++;
      BG_GFX[((vertpos+3)*32)+31] = 0x0011;
    } else if (y < 176){
      BG_GFX[((vertpos+3)*32)+31] = 0x0C10;
      vertpos = (y>>3) - 3;
      vertpos = min(max(vertpos, 0), 19);
      BG_GFX[((vertpos+3)*32)+31] = 0x0C11;
      drag = 2;
    }
    onScrollVert();
  }
}


void dsScrollBarBoth::onDrag(s16 x, s16 y) {
  if (drag == 1) {  //bottom scroll bar
    BG_GFX[(23*32)+horzpos+1] = 0x0C14;
    horzpos = (x>>3) - 1;
    horzpos = min(max(horzpos, 0), 28);
    BG_GFX[(23*32)+horzpos+1] = 0x0C11;
    onScrollHorz();
  }
  else if (drag == 2) {  //right scroll bar
    BG_GFX[((vertpos+3)*32)+31] = 0x0C10;
    vertpos = (y>>3) - 3;
    vertpos = min(max(vertpos, 0), 18);
    BG_GFX[((vertpos+3)*32)+31] = 0x0C11;
    onScrollVert();
  }
}


void dsScrollBarBoth::onDrop(s16 x, s16 y) {
  //bottom scroll bar
  BG_GFX[(23*32)+ 0] = 0x0012;
  BG_GFX[(23*32)+30] = 0x0013;

  //right scroll bar
  BG_GFX[( 2*32)+31] = 0x000E;
  BG_GFX[(22*32)+31] = 0x000F;

  if (drag == 1) {  //bottom scroll bar
    BG_GFX[(23*32)+horzpos+1] = 0x0C14;
    horzpos = (x>>3) - 1;
    horzpos = min(max(horzpos, 0), 28);
    BG_GFX[(23*32)+horzpos+1] = 0x0011;
    drag = 0;
    onScrollHorz();
  }
  else if (drag == 2) {  //right scroll bar
    BG_GFX[((vertpos+3)*32)+31] = 0x0C10;
    vertpos = (y>>3) - 3;
    vertpos = min(max(vertpos, 0), 18);
    BG_GFX[((vertpos+3)*32)+31] = 0x0011;
    drag = 0;
    onScrollVert();
  }
}


void dsScrollBarBoth::setHorzPos(int pos) {
  BG_GFX[(23*32)+horzpos+1] = 0x0C14;
  horzpos = min(max(pos, 0), 28);
  BG_GFX[(23*32)+horzpos+1] = 0x0011;
}


void dsScrollBarBoth::setVertPos(int pos) {
  BG_GFX[((vertpos+3)*32)+31] = 0x0C10;
  vertpos = min(max(pos, 0), 18);
  BG_GFX[((vertpos+3)*32)+31] = 0x0011;
}


//use custom hit detection, since it isnt a single rectagle
bool dsScrollBarBoth::hitTest(s16 x, s16 y, DS_SCREEN iscreen) {
  if (iscreen != DS_SCREEN_MAIN) return false;
  if (y > 183) return (x < 284);  //far bottom part of the screen
  if (x > 247) return (y >  16);  //far right part of the screen
  return false;
}
