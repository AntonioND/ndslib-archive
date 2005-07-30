/*****************************  DARKSTAR  ******************************\
*  Copyright (c) 2005 Vincent E. Milum Jr., All rights reserved.        *
*                                                                       *
*  See License.txt for more information                                 *
*                                                                       *
*  Latest source versions can be found at:  HTTP://WWW.DARKAIN.COM/     *
\***********************************************************************/


//library includes
#include <NDS/NDS.h>

//DarkStar includes
#include "../DarkStar/dsMainMenu.h"

//local includes
#include "checksout.h"
#include "checksoutLevel.h"

//resource data
#include "mines_raw.h"


dsChecksOutLevel::dsChecksOutLevel(u8 x, u8 y, s32 lvl, dsChecksOut *checksout)
 : dsToggleBox(x, y, 2, 2), dsSpriteSingle(DS_CORE_SUB, &mines_raw[0x80*lvl], SIZE_16_X_16, false, 3) {
  move(x<<3, y<<3);
  setBoxBuffer(mainmenu->getBuffer(DS_SCREEN_SUB)+0x800);
  level = lvl;
  checks = checksout;
}


void dsChecksOutLevel::onClick(s16 x, s16 y) {
  checks->loadLevel(level);
}


bool dsChecksOutLevel::hitTest(s16 x, s16 y, DS_SCREEN iscreen) {
  if (iscreen & DS_SCREEN_SUB) return dsToggleBox::hitTest(x, y, iscreen);
  return false;
}
