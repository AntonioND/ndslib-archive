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
#include "dsPaintCircleTool.h"


dsPaintCircleTool::dsPaintCircleTool(dsPaint *dspaint, u8 ibtnx, u8 ibtny)
 : dsPaintTool(dspaint, ibtnx, ibtny, &buttons_raw[0x200]) {
  fill[0] = 0;
  fill[1] = 0;
  fill[2] = 0;
  fillEnable = 0;
}


dsPaintCircleTool::~dsPaintCircleTool() {
  delete fill[0];
  delete fill[1];
  delete fill[2];
}


void dsPaintCircleTool::paintDrag(s16 x, s16 y, s16 ox, s16 oy) {
  int dx = x - ox;
  int dy = y - oy;
  int r = sqrt32(dx*dx+dy*dy);

  if (fillEnable == 1) {
    if (paint->getAlpha() == 31) {
      if (r < ra) paint->copyBtoA();
      paint->circlefill(ox, oy, r, paint->getColor());
    } else {
      paint->copyBtoA();
      paint->circlefill(ox, oy, r, paint->getColor(), paint->getAlpha());
    }
  }

  else if (fillEnable == 2) {
    paint->copyBtoA();
    paint->disc(ox, oy, r, paint->getColor());
  }

  else {
    paint->copyBtoA();
    paint->circle(ox, oy, r, paint->getColor(), paint->getAlpha());
  }

//  paint->circleaa(ox, oy, sqrt32(dx*dx+dy*dy), paint->getColor());
//  paint->disc(ox, oy, sqrt32(dx*dx+dy*dy), paint->getColor());
  ra = r;
}


void dsPaintCircleTool::onSelectTool() {
  fill[0] = new dsPaintSubTool(this, 26, 3, &buttons_raw[0x200], 0);
  fill[1] = new dsPaintSubTool(this, 26, 6, &buttons_raw[0x280], 1);
  fill[2] = new dsPaintSubTool(this, 26, 9, &buttons_raw[0x300], 2);
  fill[fillEnable]->selSelStyle(1, true);
}

void dsPaintCircleTool::onDeselectTool() {
  delete fill[0];
  delete fill[1];
  delete fill[2];
  fill[0] = 0;
  fill[1] = 0;
  fill[2] = 0;
}


void dsPaintCircleTool::onSelectSubTool(u8 id) {
  fill[fillEnable]->selSelStyle(0, true);
  fillEnable = id;
  fill[fillEnable]->selSelStyle(1, true);

  //i want to update the local sprite...
  //this turned out to be a nice hach to do that!!
  dmaCopyHalfWords(3, fill[fillEnable]->getMem(), getMem(), getTileSize()<<5);
}

