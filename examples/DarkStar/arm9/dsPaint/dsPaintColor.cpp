/*****************************  DARKSTAR  ******************************\
*  Copyright (c) 2005 Vincent E. Milum Jr., All rights reserved.        *
*                                                                       *
*  See License.txt for more information                                 *
*                                                                       *
*  Latest source versions can be found at:  HTTP://WWW.DARKAIN.COM/     *
\***********************************************************************/


#include <NDS/NDS.h>

#include "dsPaint.h"
#include "dsPaintColor.h"


dsPaintColor::dsPaintColor(dsPaint *dspaint, u8 ix, u8 iy, u16 color, u16 palette, u32 tileloc)
 : dsClickRect(ix<<3, iy<<3, (ix<<3)+16, (iy<<3)+16, DS_SCREEN_SUB) {
  paint = dspaint;
  tile = tileloc;
  clr = color;

  PALETTE_SUB[palette] = color;
  
  for (int i=0; i<16; i++) {
    BG_GFX_SUB[(tile<<4)+i + 0x2000] =
       (palette & 0xF)       | ((palette & 0xF) << 4) |
      ((palette & 0xF) << 8) | ((palette & 0xF) << 12);
  }

  BG_GFX_SUB[0x800 + ((iy+0)*32)+ix+0] = tile | ((palette>>4)<<12);
  BG_GFX_SUB[0x800 + ((iy+0)*32)+ix+1] = tile | ((palette>>4)<<12);
  BG_GFX_SUB[0x800 + ((iy+1)*32)+ix+0] = tile | ((palette>>4)<<12);
  BG_GFX_SUB[0x800 + ((iy+1)*32)+ix+1] = tile | ((palette>>4)<<12);
}


dsPaintColor::~dsPaintColor() {
  BG_GFX_SUB[0x800 + (((y1>>3)+0)*32)+(x1>>3)+0] = 0;
  BG_GFX_SUB[0x800 + (((y1>>3)+0)*32)+(x1>>3)+1] = 0;
  BG_GFX_SUB[0x800 + (((y1>>3)+1)*32)+(x1>>3)+0] = 0;
  BG_GFX_SUB[0x800 + (((y1>>3)+1)*32)+(x1>>3)+1] = 0;
}


void dsPaintColor::onClick(s16 x, s16 y) {
  paint->setColor(getColor());
}
