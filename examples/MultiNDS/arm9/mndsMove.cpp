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
#include "mndsMove.h"
#include "mndsMenu.h"

//resources
#include "button_raw.h"
#include "button_pal.h"



mndsMoveUp::mndsMoveUp(mndsMenu *gmenu) : dsClickRect(208, 2, 240, 18, DS_SCREEN_MAIN),
  dsSpriteSingle(DS_CORE_MAIN, button_raw+0, SIZE_32_X_16, false, 12) {
  menu=gmenu;
  move(dsClickRect::getX1(), dsClickRect::getY1());
  show();
}


mndsMoveUp::~mndsMoveUp() {
}


void mndsMoveUp::onClick(s16 x, s16 y) {
  dmaCopyHalfWords(3, button_raw+768, getMem(), getTileSize()<<5);
}


void mndsMoveUp::onDrag(s16 x, s16 y) {
  if (hitTest(x, y)) {
    dmaCopyHalfWords(3, button_raw+768, getMem(), getTileSize()<<5);
  } else {
    dmaCopyHalfWords(3, button_raw+0, getMem(), getTileSize()<<5);
  }
}


void mndsMoveUp::onDrop(s16 x, s16 y) {
  dmaCopyHalfWords(3, button_raw+0, getMem(), getTileSize()<<5);
  if (hitTest(x, y)) menu->pageUp();
}



////////////////////////////////////////////////////////////////////////////////////////


mndsMoveDown::mndsMoveDown(mndsMenu *gmenu) : dsClickRect(208, 174, 240, 190, DS_SCREEN_MAIN),
  dsSpriteSingle(DS_CORE_MAIN, button_raw+256, SIZE_32_X_16, false, 12) {
  menu=gmenu;
  move(dsClickRect::getX1(), dsClickRect::getY1());
  show();
}


mndsMoveDown::~mndsMoveDown() {
}


void mndsMoveDown::onClick(s16 x, s16 y) {
  dmaCopyHalfWords(3, button_raw+1024, getMem(), getTileSize()<<5);
}


void mndsMoveDown::onDrag(s16 x, s16 y) {
  if (hitTest(x, y)) {
    dmaCopyHalfWords(3, button_raw+1024, getMem(), getTileSize()<<5);
  } else {
    dmaCopyHalfWords(3, button_raw+256, getMem(), getTileSize()<<5);
  }
}


void mndsMoveDown::onDrop(s16 x, s16 y) {
  dmaCopyHalfWords(3, button_raw+256, getMem(), getTileSize()<<5);
  if (hitTest(x, y)) menu->pageDown();
}
