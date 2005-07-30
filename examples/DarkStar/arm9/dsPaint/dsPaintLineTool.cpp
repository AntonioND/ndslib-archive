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
#include "dsPaintLineTool.h"


dsPaintLineTool::dsPaintLineTool(dsPaint *dspaint, u8 ibtnx, u8 ibtny)
 : dsPaintTool(dspaint, ibtnx, ibtny, &buttons_raw[0x080]) {
  aa=0;
}


dsPaintLineTool::~dsPaintLineTool() {
  delete aa;
}


void dsPaintLineTool::paintDrag(s16 x, s16 y, s16 ox, s16 oy) {
  paint->copyBtoA();
  if (aa && aa->getBoxPushed()) {
    paint->lineaa(x, y, ox, oy, paint->getColor(), paint->getSize());
  } else {
    paint->lineblend(x, y, ox, oy, paint->getColor(), paint->getAlpha(), paint->getSize());
  }
}


void dsPaintLineTool::onSelectTool() {
  aa = new dsPaintSubTool(this, 26, 3, &buttons_raw[0x480]);
}

void dsPaintLineTool::onDeselectTool() {
  delete aa;
  aa = 0;
}
