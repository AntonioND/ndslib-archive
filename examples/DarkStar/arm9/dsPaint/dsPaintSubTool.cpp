/*****************************  DARKSTAR  ******************************\
*  Copyright (c) 2005 Vincent E. Milum Jr., All rights reserved.        *
*                                                                       *
*  See License.txt for more information                                 *
*                                                                       *
*  Latest source versions can be found at:  HTTP://WWW.DARKAIN.COM/     *
\***********************************************************************/


//lib includes
#include <NDS/NDS.h>

//DarkStar includes
#include "../DarkStar/dsMainMenu.h"

//local includes
#include "dsPaintTool.h"
#include "dsPaintSubTool.h"


dsPaintSubTool::dsPaintSubTool(dsPaintTool *painttool, u8 x, u8 y, const void *sprData, u8 subId)
 : dsToggleBox(x, y, 2, 2), dsSpriteSingle(DS_CORE_SUB, sprData, SIZE_16_X_16, false, 2) {
  tool = painttool;
  id = subId;
  setClickScreen(DS_SCREEN_SUB);
  setBoxBuffer(mainmenu->getBuffer(DS_SCREEN_SUB)+0x800);
  renderBox();
  move(x<<3, y<<3);
}


dsPaintSubTool::~dsPaintSubTool() {
}


void dsPaintSubTool::onClick(s16 x, s16 y) {
  dsToggleBox::onClick(x, y);
  tool->onSelectSubTool(id);
}
