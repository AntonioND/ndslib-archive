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
#include "mndsLoadGame.h"
#include "mndsMenu.h"

//resources
#include "button_raw.h"
#include "button_pal.h"


mndsLoadGame::mndsLoadGame(mndsMenu *gmenu) : dsClickRect(160, 174, 192, 190, DS_SCREEN_MAIN),
  dsSpriteSingle(DS_CORE_MAIN, button_raw+512, SIZE_32_X_16, false, 12) {
  menu=gmenu;
  move(dsClickRect::getX1(), dsClickRect::getY1());
  show();
}


mndsLoadGame::~mndsLoadGame() {
}


void mndsLoadGame::onClick(s16 x, s16 y) {
  dmaCopyHalfWords(3, button_raw+1280, getMem(), getTileSize()<<5);
}


void mndsLoadGame::onDrag(s16 x, s16 y) {
  if (hitTest(x, y)) {
    dmaCopyHalfWords(3, button_raw+1280, getMem(), getTileSize()<<5);
  } else {
    dmaCopyHalfWords(3, button_raw+512, getMem(), getTileSize()<<5);
  }
}


void mndsLoadGame::onDrop(s16 x, s16 y) {
  dmaCopyHalfWords(3, button_raw+512, getMem(), getTileSize()<<5);
  if (hitTest(x, y)) menu->loadGame();
}

