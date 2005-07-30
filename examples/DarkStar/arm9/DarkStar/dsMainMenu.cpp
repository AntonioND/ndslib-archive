/*****************************  DARKSTAR  ******************************\
*  Copyright (c) 2005 Vincent E. Milum Jr., All rights reserved.        *
*                                                                       *
*  See License.txt for more information                                 *
*                                                                       *
*  Latest source versions can be found at:  HTTP://WWW.DARKAIN.COM/     *
\***********************************************************************/


//libs
#include <NDS/NDS.h>

//local headers
#include "dsMainMenu.h"
#include "dsMessageBox.h"
#include "dsApp.h"
#include "dsAppMenu.h"
#include <NDS/DarkStar/dsSprite.h>
#include <NDS/DarkStar/dsSound.h>
#include "dsSwapScreensBtn.h"

//common includes
#include "../common.h"

//resource includes
#include "palette_themes.h"
#include "icons_raw.h"
#include "icons_pal.h"
#include "ping_raw.h"
#include "lain_raw.h"


extern const u16 DarkStar2_Map[49152];
dsMainMenu *mainmenu = NULL;


dsMainMenu::dsMainMenu() : dsToggleBox(0, 0, 2, 2) {
  mainmenu = this;
  appmenu = 0;
  lock = 0;

  setBoxBuffer(getActiveBuffer());

  {  //cheap hack to make sound, well, sound right
    u8 *src = (u8*)lain_raw;
    for (int i=0; i<GETRAWSIZE(lain_raw); i++) src[i] = src[i] + 128;
    new dsSound(GETRAW(lain_raw), GETRAWSIZE(lain_raw)>>2, 16000, 0x7F, 0x3F, 1);
  }

  swapButtons = new dsSwapScrBtn();

  icons[0] = new dsSpriteSingle(DS_CORE_MAIN, icons_raw, SIZE_16_X_16, false, 0);
  icons[0]->setPriority(0);

  icons[1] = new dsSpriteSingle(DS_CORE_SUB,  icons_raw, SIZE_16_X_16, false, 0);
  icons[1]->setPriority(0);
  icons[1]->hide();

  bars[0] = new dsBox(2, 0, 28, 2, 0, DS_STYLE_BOX_INV);  //bottom screen
  bars[0]->renderBox();

  bars[1] = new dsBox(0, 0, 32, 2, getShellName(), DS_STYLE_BOX);      //top screen
  bars[1]->setBoxBuffer(getInactiveBuffer());
  bars[1]->moveText(2, 0);
  bars[1]->renderButton();

  //this is a very VERY cheap hack, and should be done on the resource data itself
  u16 *darkstar = (u16*)DarkStar2_Map;
  for (u32 i=0; i<sizeof(DarkStar2_Map)>>1; i++) {
    darkstar[i] = darkstar[i] | 0x8000;
  }


  DC_FlushAll();

  loadTheme();
  updateTextPalette();

  renderBox();
  restoreBackground();
  selItem(0);
}


dsMainMenu::~dsMainMenu() {
  delete appmenu;
  delete swapButtons;
  delete icons[0];
  delete icons[1];
  delete bars[0];
  delete bars[1];
  mainmenu = 0;
}



void dsMainMenu::openMenu() {
  if (!appmenu) {
    new dsAppMenu(this);
    selSelStyle(1, true);
  }
}



void dsMainMenu::cancelMenu() {
  if (appmenu) {
    //delete appmenu;
    appmenu->killMenu();
    //selSelStyle(0, true);
  }
}



void dsMainMenu::selItem(dsApp *app) {
  cancelMenu();
  setName(0);

  dsMain::selItem(app);
  
  //we need to erase old text here, then print new text
  bars[1]->eraseText();
  bars[1]->setBoxText( (app!=0) ? app->getAppName() : getShellName() );
  bars[1]->renderText();
}


void dsMainMenu::preSwapScreen() {
  new dsSound(GETRAW(ping_raw), GETRAWSIZE(ping_raw)>>2, 22050);
  cancelMenu();
}


void dsMainMenu::onSwapScreen() {
  if (getActiveScreen()) {
    icons[0]->hide();
    icons[1]->show();
  } else {
    icons[0]->show();
    icons[1]->hide();
  }

  setBoxBuffer(getActiveBuffer());
  renderBox();

  //erase old text before setting new buffer
  bars[0]->eraseText();
  bars[1]->eraseText();

  dsBox *bx = appButtons.getFirstItem();
  while (bx) {
    bx->eraseText();
    bx->setBoxBuffer(getActiveBuffer());
    bx->renderButton();
    bx = appButtons.getNextItem(bx);
  }

  bars[0]->setBoxBuffer(getActiveBuffer());
  bars[0]->renderButton();

  bars[1]->setBoxBuffer(getInactiveBuffer());
  bars[1]->renderButton();
}


void dsMainMenu::messageBox(const char *text) {
  new dsMessageBox(text);
}


void dsMainMenu::restoreBackground(DS_SCREEN bg) {
  if (bg == DS_SCREEN_MAIN) {
    dmaCopyWords(3, DarkStar2_Map,  &BG_GFX[0x4000], sizeof(DarkStar2_Map));
  }

  else if (bg == DS_SCREEN_SUB) {
    dmaCopyWords(3, DarkStar2_Map,  &BG_GFX_SUB[0x4000], sizeof(DarkStar2_Map));
  }

  else if (bg == DS_SCREEN_BOTH) {
    dmaCopyWordsAsynch(2, DarkStar2_Map,  &BG_GFX[0x4000],     sizeof(DarkStar2_Map));
    dmaCopyWordsAsynch(3, DarkStar2_Map,  &BG_GFX_SUB[0x4000], sizeof(DarkStar2_Map));
    while ( dmaBusy(2) || dmaBusy(3) ) { *DEBUG1 = *DEBUG1 + 1; }
   }
}


void dsMainMenu::onVBlank() {
  if (getTheme() != COLOR_THEME) {
    loadTheme();
    updateTextPalette();
  }
}


void dsMainMenu::updateTextPalette() {
  for (int i=2; i<15; i++) {
    PALETTE[48-i] = PALETTE[i];
    PALETTE[32-i] = RGB( 31-RGBRED(PALETTE[i]), 31-RGBGREEN(PALETTE[i]), 31-RGBBLUE(PALETTE[i]) );
    PALETTE[48-i+512] = PALETTE[i];
    PALETTE[32-i+512] = RGB( 31-RGBRED(PALETTE[i]), 31-RGBGREEN(PALETTE[i]), 31-RGBBLUE(PALETTE[i]) );
  }
/*
  PALETTE[17] = TEXT_BORDER[getTheme()][0];
  PALETTE[33] = TEXT_BORDER[getTheme()][1];
  PALETTE[17+512] = TEXT_BORDER[getTheme()][0];
  PALETTE[33+512] = TEXT_BORDER[getTheme()][1];
*/
}


dsClickable *dsMainMenu::getLockedClickable(s16 x, s16 y, DS_SCREEN iscreen) {
  for (int i=0; i<lockedClickables.getItemCount(); i++) {
    dsClickable *click = lockedClickables.getItem(i);
    if (click->hitTest(x, y, iscreen)) return click;
  }
  return 0;
}


void dsMainMenu::onKeyChange(u32 inputState, u32 lastState) {
  if (keylock) {
    for (int i=0; i<lockedInputs.getItemCount(); i++) {
      lockedInputs.getItem(i)->onKeyChange(inputState, lastState);
    }
    return;
  }

  if ( (lastState & KEY_SELECT) && (!(inputState & KEY_SELECT)) ) {
    swapScreens();
  }

  if ( (lastState & KEY_START) && (!(inputState & KEY_START)) ) {
    if (appmenu) {
      cancelMenu();
    } else {
      openMenu();
    }
  }
}


void dsMainMenu::onNameChange(const char *newname) {
  bars[0]->eraseText();
  bars[0]->setBoxText(newname);
  bars[0]->renderText();
}


void dsMainMenu::appendBox(dsBox *box) {
  appButtons.appendItem(box);
  updateBox();
}

void dsMainMenu::removeBox(dsBox *box) {
  appButtons.removeItem(box);
  box->setStyle(DS_STYLE_NONE);
  box->eraseButton();
  updateBox();
}


void dsMainMenu::updateBox() {
  bars[0]->eraseText();

  int total = 0;
  dsBox *bx = appButtons.getFirstItem();
  while (bx) {
    int w = bx->getBoxWidth();
    total += w;
    bx->moveBox(30-total, 0);
    bx->renderButton();
    bx = appButtons.getNextItem(bx);
  }

  bars[0]->resizeBox(28-total, 2);
  bars[0]->renderButton();
}


///////////////////////////////////////////////////////////////////


void dsSwapScreens::swapScreens() {
  if (mainmenu) mainmenu->swapScreens();
}
