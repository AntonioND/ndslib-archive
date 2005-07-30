/*****************************  DARKSTAR  ******************************\
*  Copyright (c) 2005 Vincent E. Milum Jr., All rights reserved.        *
*                                                                       *
*  See License.txt for more information                                 *
*                                                                       *
*  Latest source versions can be found at:  HTTP://WWW.DARKAIN.COM/     *
\***********************************************************************/


#ifndef _DS_SWAP_SCREENS_BUTTON_H_
#define _DS_SWAP_SCREENS_BUTTON_H_


//local includes
#include <NDS/DarkStar/dsClickable.h>
#include <NDS/DarkStar/dsSwapScreens.h>
#include <NDS/DarkStar/dsSprite.h>
#include "dsBox.h"

//resource includes
#include "icons_raw.h"
#include "icons_pal.h"


class dsSwapScrBtn : public dsToggleBox, public dsSwapScreens {
  public:
    dsSwapScrBtn() : dsToggleBox(30, 0, 2, 2) {
      icons[0] = new dsSpriteSingle(DS_CORE_MAIN, &icons_raw[128], SIZE_16_X_16, false, 0);
      icons[1] = new dsSpriteSingle(DS_CORE_SUB,  &icons_raw[128], SIZE_16_X_16, false, 0);
      icons[0]->setPriority(0);
      icons[1]->setPriority(0);
      icons[0]->setX(SCREEN_WIDTH - 16);
      icons[1]->setX(SCREEN_WIDTH - 16);
      icons[1]->hide();
      renderBox();
    }

    virtual ~dsSwapScrBtn() {}

    virtual void onClick(s16 x, s16 y) { swapScreens(); }

    virtual void onSwapScreen(bool activeScreen) {
      setBoxBuffer(mainmenu->getActiveBuffer());
      selSelStyle(activeScreen, true);
      if (activeScreen) {
        icons[0]->hide();
        icons[1]->show();
      } else {
        icons[0]->show();
        icons[1]->hide();
      }
    }

  private:
    dsSprite *icons[2];
};


#endif //_DS_SWAP_SCREENS_BUTTON_H_
