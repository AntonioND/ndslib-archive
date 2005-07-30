/*****************************  DARKSTAR  ******************************\
*  Copyright (c) 2005 Vincent E. Milum Jr., All rights reserved.        *
*                                                                       *
*  See License.txt for more information                                 *
*                                                                       *
*  Latest source versions can be found at:  HTTP://WWW.DARKAIN.COM/     *
\***********************************************************************/


//lib includes
#include <NDS/NDS.h>

//common includes
#include "../common.h"

//DarkStar includes
#include "../DarkStar/dsMainMenu.h"

//local includes
#include "dsPaint.h"
#include "dsPaintClear.h"


dsPaintClear::dsPaintClear(dsPaint *dspaint) : dsButton("CLEAR") {
  paint = dspaint;
  resizeBox(6, 2);
  mainmenu->appendBox(this);
}


dsPaintClear::~dsPaintClear() {
  mainmenu->removeBox(this);
}


void dsPaintClear::onButton() {
  DC_FlushAll();

  dmaCopyHalfWords(3, paint->getScreenBuffer(), paint->getBufferB(),      paint->getGfxByteSize());
//  paint->dma3(paint->getScreenBuffer(), paint->getGfxByteSize() >> 4);
  paint->fillBufferA(paint->getColor());
  dmaCopyHalfWords(3, paint->getBufferA(),      paint->getScreenBuffer(), paint->getGfxByteSize());

/*
  dmaCopyHalfWords(3, paint->getScreenBuffer(), paint->getBufferA(),      paint->getGfxByteSize());
  dmaCopyHalfWords(3, paint->getBufferB(),      paint->getScreenBuffer(), paint->getGfxByteSize());
  dmaCopyHalfWords(3, paint->getBufferA(),      paint->getBufferB(),      paint->getGfxByteSize());
  dmaCopyHalfWords(3, paint->getScreenBuffer(), paint->getBufferA(),      paint->getGfxByteSize());
*/
}
