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
#include "dsPaintBoxTool.h"


dsPaintBoxTool::dsPaintBoxTool(dsPaint *dspaint, u8 ibtnx, u8 ibtny)
 : dsPaintTool(dspaint, ibtnx, ibtny, &buttons_raw[0x100]) {
  fill[0] = 0;
  fill[1] = 0;
  fillEnable = 0;
}


dsPaintBoxTool::~dsPaintBoxTool() {
  delete fill[0];
  delete fill[1];
}


void dsPaintBoxTool::paintStart(s16 x, s16 y) {
  px = x;
  py = y;
}


/*
yes, this is longer then it could be...
did some optimization here.  instead of repainting the entire
screen each and every frame, we only paint the additions and
subtractions since last frame.  because of the way
dsClickable works, this is only called when touch X/Y is changed,
making it that much easier for us to speed things up here
*/
void dsPaintBoxTool::paintDrag(s16 x, s16 y, s16 ox, s16 oy) {
  if (fillEnable) {
    if (paint->getAlpha() == 31) {
      u8 draw = 0;

      if ( ((x < px) && (px > ox)) || ((x > px) && (px < ox)) ) {
        //move closer to center point on X axis
        paint->copyBtoA(x, oy, px, py);
      } else {
        //move away from center point on X axis
        paint->boxfill(x, oy, px, py, paint->getColor(), paint->getAlpha());
        draw++;
      }

      if ( ((y < py) && (py > oy)) || ((y > py) && (py < oy)) ) {
        //move closer to center point on Y axis
        paint->copyBtoA(ox, y, px, py);
      } else {
        //move away from center point on Y axis
        paint->boxfill(ox, y, px, py, paint->getColor(), paint->getAlpha());
        draw++;
      }

      if (draw == 1) {
        //move closer to center on X and/or Y axis
        paint->copyBtoA(x, y, px, py);
      } else if (draw == 2) {
        //move away from center on X and Y axis
        paint->boxfill(x, y, px, py, paint->getColor(), paint->getAlpha());
      }

      //if we crossed center, paint box from center to current possition
      if ( ((x>ox)&&(ox>px)) || ((y>oy)&&(oy>py))
        || ((x<ox)&&(ox<px)) || ((y<oy)&&(oy<py)) ) {
        paint->boxfill(ox, oy, x, y, paint->getColor());
      }
    }

    else {
      paint->copyBtoA();
      paint->boxfill(ox, oy, x, y, paint->getColor(), paint->getAlpha());
    }

  } else {
    paint->copyBoxBtoA(px, py, ox, oy, paint->getSize());
    paint->box(x, y, ox, oy, paint->getColor(), paint->getAlpha(), paint->getSize());
  }

  px = x;
  py = y;
}


void dsPaintBoxTool::onSelectTool() {
  fill[0] = new dsPaintSubTool(this, 26, 3, &buttons_raw[0x100], 0);
  fill[1] = new dsPaintSubTool(this, 26, 6, &buttons_raw[0x180], 1);
  fill[fillEnable]->selSelStyle(1, true);
}

void dsPaintBoxTool::onDeselectTool() {
  delete fill[0];
  delete fill[1];
  fill[0] = 0;
  fill[1] = 0;
}


void dsPaintBoxTool::onSelectSubTool(u8 id) {
  fill[fillEnable]->selSelStyle(0, true);
  fillEnable = id;
  fill[fillEnable]->selSelStyle(1, true);

  //i want to update the local sprite...
  //this turned out to be a nice hach to do that!!
  dmaCopyHalfWords(3, fill[fillEnable]->getMem(), getMem(), getTileSize()<<5);
}

