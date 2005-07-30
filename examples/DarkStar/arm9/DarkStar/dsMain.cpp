/*****************************  DARKSTAR  ******************************\
*  Copyright (c) 2005 Vincent E. Milum Jr., All rights reserved.        *
*                                                                       *
*  See License.txt for more information                                 *
*                                                                       *
*  Latest source versions can be found at:  HTTP://WWW.DARKAIN.COM/     *
\***********************************************************************/


//libraries
#include <NDS/NDS.h>

//common includes
#include "../common.h"

//local includes
#include "dsMain.h"
#include "dsApp.h"
#include <NDS/DarkStar/dsInput.h>
#include <NDS/DarkStar/dsBlank.h>
#include <NDS/DarkStar/dsSwapScreens.h>
#include <NDS/DarkStar/dsSpriteManager.h>

//resource includes
#include "palette_themes.h"


//some statics that DarkStar uses
vList<dsSwapScreens*> dsSwapScreens::items;
bool dsMain::activeScreen = false;



dsMain::dsMain() {
  //create the sprite manager if it doesnt already exist
  if (!sprmgr) new dsSpriteManager();

  activeApp = NULL;
  themeid = 0xFF;
}


dsMain::~dsMain() {
}


void dsMain::swapScreens() {
  if (!canSwapScreens()) return;

  preSwapScreen();
  activeScreen = !activeScreen;
  lcdSwap();
  onSwapScreen();

  dsSwapScreens *scr = dsSwapScreens::items.getFirstItem();
  while (scr) {
    scr->onSwapScreen(activeScreen);
    scr = dsSwapScreens::items.getNextItem(scr);
  }
  sprmgr->updateSystemOAM();
}


void dsMain::selItem(dsApp *app) {
  if (activeApp) activeApp->onClose();
  activeApp = app;
  if (activeApp) activeApp->onLaunch();
}


u16 *dsMain::getBuffer(DS_SCREEN screen) const {
  switch (screen) {
    case DS_SCREEN_MAIN:
    case DS_SCREEN_MAIN_DISABLED:
      return BG_GFX;

    case DS_SCREEN_SUB:
    case DS_SCREEN_SUB_DISABLED:
      return BG_GFX_SUB;

    default:
      return 0;
  }
}


void dsMain::loadTheme(u8 theme, u16 palette) {
  if (theme > 15) theme = COLOR_THEME;
  themeid = theme;

  if (palette == 0xFFFF) {
    for (int i=0; i<16; i++) {
      PALETTE[i]     = PALETTE_THEME[theme][i];  //CORE A BG  PAL 0
      PALETTE[i+512] = PALETTE_THEME[theme][i];  //CORE A SPR PAL 0
      PALETTE[i+272] = PALETTE_THEME[theme][i];  //CORE B BG  PAL 0
      PALETTE[i+784] = PALETTE_THEME[theme][i];  //CORE B SPR PAL 0
    }
  }

  else {
    for (int i=0; i<16; i++) {
      PALETTE[i + (palette<<4)] = PALETTE_THEME[theme][i];
    }
  }
}
