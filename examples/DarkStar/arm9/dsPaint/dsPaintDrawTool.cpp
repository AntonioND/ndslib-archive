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
#include "dsPaintDrawTool.h"


dsPaintDrawTool::dsPaintDrawTool(dsPaint *dspaint, u8 ibtnx, u8 ibtny)
 : dsPaintTool(dspaint, ibtnx, ibtny, &buttons_raw[0x000]) {
  aa=0;
}


dsPaintDrawTool::~dsPaintDrawTool() {
  delete aa;
}


void dsPaintDrawTool::paintDrag(s16 x, s16 y, s16 ox, s16 oy) {
  if (aa && aa->getBoxPushed()) {
    paint->lineaa(px, py, x, y, paint->getColor(), paint->getSize());
  } else {
    paint->lineblend(px, py, x, y, paint->getColor(), paint->getAlpha(), paint->getSize());
  }
  px = x;
  py = y;
}


void dsPaintDrawTool::onSelectTool() {
  aa = new dsPaintSubTool(this, 26, 3, &buttons_raw[0x480]);
}

void dsPaintDrawTool::onDeselectTool() {
  delete aa;
  aa = 0;
}
