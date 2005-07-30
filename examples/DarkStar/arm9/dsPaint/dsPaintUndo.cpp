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
#include "dsPaintUndo.h"


dsPaintUndo::dsPaintUndo(dsPaint *dspaint) : dsButton("UNDO") {
  paint = dspaint;
  resizeBox(5, 2);
  mainmenu->appendBox(this);
}


dsPaintUndo::~dsPaintUndo() {
  mainmenu->removeBox(this);
}


void dsPaintUndo::onButton() {
  DC_FlushAll();
  dmaCopyHalfWords(3, paint->getScreenBuffer(), paint->getBufferA(),      paint->getGfxByteSize());
  dmaCopyHalfWords(3, paint->getBufferB(),      paint->getScreenBuffer(), paint->getGfxByteSize());
  dmaCopyHalfWords(3, paint->getBufferA(),      paint->getBufferB(),      paint->getGfxByteSize());
  dmaCopyHalfWords(3, paint->getScreenBuffer(), paint->getBufferA(),      paint->getGfxByteSize());
}
