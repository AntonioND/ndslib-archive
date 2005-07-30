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
#include "dsPaint.h"
#include "dsPaintDropperTool.h"


dsPaintDropperTool::dsPaintDropperTool(dsPaint *dspaint, u8 ibtnx, u8 ibtny)
 : dsPaintTool(dspaint, ibtnx, ibtny, &buttons_raw[0x400]) {
}


dsPaintDropperTool::~dsPaintDropperTool() {
}


void dsPaintDropperTool::paintStart(s16 x, s16 y) {
  paint->setColor(paint->getPixel(x, y));
}


void dsPaintDropperTool::paintDrag(s16 x, s16 y, s16 ox, s16 oy) {
  paint->setColor(paint->getPixel(x, y));
}

