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
#include "dsMessageBox.h"
#include "dsMainMenu.h"


dsMessageBox::dsMessageBox(const char *text, DS_SCREEN dsscreen) : dsBox(text, DS_STYLE_ROUND_INV) {
  cb = 0;
  int len = strlen(text);
  mainmenu->cancelMenu();

  //text height (1), button height (2), borders (3)
  s16 mbh = 1 + 2 + 3;
  s16 mby = 12-(mbh>>1);

  s16 mbw = len+3;
  s16 mbx = 16 - (mbw>>1);

  moveText(1, 1);
  moveResizeBox(mbx, mby, mbw, mbh);
  renderButton();

  btnOk = new dsMessageBoxButton(1, this, mbx+mbw-4, mby+mbh-3, 3, 2, "OK");
  btnOk->renderButton();

  mainmenu->keylock   = true;
  mainmenu->touchlock = true;
  mainmenu->lockedInputs.appendItem(this);
  mainmenu->lockedClickables.appendItem(btnOk);
}


dsMessageBox::~dsMessageBox() {
  mainmenu->lockedInputs.removeItem(this);
  mainmenu->lockedClickables.removeItem(btnOk);
  mainmenu->keylock   = false;
  mainmenu->touchlock = false;
  delete btnOk;
}


void dsMessageBox::onKeyChange(u32 inputState, u32 lastState) {
  if ( (lastState & KEY_B) && (!(inputState & KEY_B)) ) {
    onButtonPress(2);
    return;
  }
}


void dsMessageBox::onButtonPress(u8 id) {
  if (cb) cb->onButtonPress(id);
  delete this;
}
