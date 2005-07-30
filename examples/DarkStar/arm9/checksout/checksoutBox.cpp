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
#include "checksout.h"
#include "checksoutBox.h"


dsChecksOutBox::dsChecksOutBox(u8 ix, u8 iy, dsChecksOut *dscheckout)
 : dsClickRect(ix<<3, iy<<3, (ix+2)<<3, (iy+2)<<3, DS_SCREEN_MAIN) {
  checkout = dscheckout;
  xx = ix;
  yy = iy;
  val = 0;

  BG_GFX[0x800 + ((yy+0)*32)+xx+0]  = 0x0009;
  BG_GFX[0x800 + ((yy+1)*32)+xx+0]  = 0x0008;
  BG_GFX[0x800 + ((yy+0)*32)+xx+1]  = 0x0006;
  BG_GFX[0x800 + ((yy+1)*32)+xx+1]  = 0x0007;
}


dsChecksOutBox::~dsChecksOutBox() {
  BG_GFX[0x800 + ((yy+0)*32)+xx+0]  = 0;
  BG_GFX[0x800 + ((yy+1)*32)+xx+0]  = 0;
  BG_GFX[0x800 + ((yy+0)*32)+xx+1]  = 0;
  BG_GFX[0x800 + ((yy+1)*32)+xx+1]  = 0;
}


void dsChecksOutBox::onClick(s16 x, s16 y) {
  checkout->change(xx, yy);
}


void dsChecksOutBox::render() {
  if (val) {
    BG_GFX[0x800 + ((yy+0)*32)+xx+0]  = 0x000C;
    BG_GFX[0x800 + ((yy+1)*32)+xx+0]  = 0x080C;
    BG_GFX[0x800 + ((yy+0)*32)+xx+1]  = 0x040C;
    BG_GFX[0x800 + ((yy+1)*32)+xx+1]  = 0x0C0C;
  } else {
    BG_GFX[0x800 + ((yy+0)*32)+xx+0]  = 0x0009;
    BG_GFX[0x800 + ((yy+1)*32)+xx+0]  = 0x0008;
    BG_GFX[0x800 + ((yy+0)*32)+xx+1]  = 0x0006;
    BG_GFX[0x800 + ((yy+1)*32)+xx+1]  = 0x0007;
  }
}

void dsChecksOutBox::setValue(u8 value) {
  val = !!value;
  render();
}


void dsChecksOutBox::invert() {
  val = !val;
  render();
}
