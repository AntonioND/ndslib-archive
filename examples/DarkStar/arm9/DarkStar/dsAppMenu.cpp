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
#include "dsAppMenu.h"
#include "dsApp.h"
#include "dsMainMenu.h"
#include <NDS/DarkStar/dsSound.h>

//resources
#include "click_raw.h"
#include "unclick_raw.h"


//list of all DarkStar Applications
vArray<dsApp*> *dsApp::apps = NULL;


dsAppMenu::dsAppMenu(dsMainMenu *mainmenu)
 : dsBox(0, DS_STYLE_ROUND_INV), dsClickRect(0, 0, SCREEN_WIDTH-1, SCREEN_HEIGHT-1, DS_SCREEN_BOTH) {
  main = mainmenu;
  activeScreen = main->getActiveScreen();
  main->appmenu = this;
  selected = 0;
  anim = 0;
  animpos = 0;

  for (int i=0; i<32*24; i++) {
    backbuff[i] = 0;
    textbuff[i] = 0;
  }

  w = 0;  //width,  calculated from text
  h = 0;  //height, calculated from text

  dsApp *app = dsApp::getFirstApp();
  while (app) {
    int len = strlen(app->getMenuName());
    if (len > 0) {
      h++;
      w = max(w, len);
      items.appendItem(new dsMenuItem(this, app, 0, h+1));
      app = dsApp::getNextApp(app);
    }
  }

  if ( (h == 0) || (w == 0) ) {
    delete this;
    return;
  }

  moveResizeBox(0, 2, w+1, h+1);
  renderBox(backbuff);


  int yy = 20;
  int ww = (w * 8) + 4;

  dsMenuItem *itm = items.getFirstItem();
  while (itm) {
    itm->setRect(0, yy, ww, 8);
    itm->printText(1, textbuff);
    itm = items.getNextItem(itm);
    yy += 8;
  }

  new dsSound(GETRAW(click_raw), GETRAWSIZE(click_raw)>>2, 22050);
  anim = 1;
}


dsAppMenu::~dsAppMenu() {
  main->appmenu = 0;

  if ( (h == 0) || (w == 0) ) return;

  dsMenuItem *itm = items.getFirstItem();
  while (itm) {
    delete itm;
    items.removeItem(itm);
    itm = items.getFirstItem();
  }
}


void dsAppMenu::killMenu() {
  if (anim == 2) {
    new dsSound(GETRAW(unclick_raw), GETRAWSIZE(unclick_raw)>>2, 22050);
    main->selSelStyle(0, true);
    anim = 3;
  }
}


void dsAppMenu::onClick(s16 x, s16 y) {
  mainmenu->cancelMenu();
}


void dsAppMenu::selItem(dsApp *app) {
  if (anim == 2) main->selItem(app);
}


void dsAppMenu::onKeyChange(u32 inputState, u32 lastState) {
  if (anim != 2) return;

  if ( (lastState & KEY_UP) && (!(inputState & KEY_UP)) ) {
    if (selected) selected->printText(1, getBoxBuffer()+0x400);
    selected = items.getPrevItem(selected);
    if (!selected) selected = items.getLastItem();
    selected->printText(2, getBoxBuffer()+0x400);
  }

  else if ( (lastState & KEY_DOWN) && (!(inputState & KEY_DOWN)) ) {
    if (selected) selected->printText(1, getBoxBuffer()+0x400);
    selected = items.getNextItem(selected);
    if (!selected) selected = items.getFirstItem();
    selected->printText(2, getBoxBuffer()+0x400);
  }

  else if ( (lastState & KEY_A) && (!(inputState & KEY_A)) ) {
    if (selected) {
      selItem(selected->getApp());
    }
  }

  else if ( (lastState & KEY_B) && (!(inputState & KEY_B)) ) {
    mainmenu->cancelMenu();
    return;
  }
}


void dsAppMenu::onVBlank() {
  if (anim == 1) {
    s16 animx = min(animpos, w);
    s16 animy = max(0, animpos-w)+2;
    s16 count = /*max(*/ min(animpos, min(w, h))+1/*, animpos - min(w, h) )*/;

  
    u16 *src1 = &backbuff[(animy*32)+animx];
    u16 *dst1 = &getBoxBuffer()[(animy*32)+animx];
    u16 *src2 = &textbuff[(animy*32)+animx];
    u16 *dst2 = &getBoxBuffer()[(animy*32)+animx + 0x400];

    for (int i=0; i<count; i++) {
      if (animpos+i > w+h) break;
      *dst1 = *src1;
      *dst2 = *src2;
      src1 += 31;
      dst1 += 31;
      src2 += 31;
      dst2 += 31;
    }

    animpos++;
    if (animpos > w+h) {
      anim = 2;
      animpos = 0;
    }
  }

  else if (anim == 3) {
    s16 animx = min(animpos, w);
    s16 animy = max(0, animpos-w)+2;
    s16 count = /*max(*/ min(animpos, min(w, h))+1/*, animpos - min(w, h) )*/;
  
    u16 *dst1 = &getBoxBuffer()[(animy*32)+animx];
    u16 *dst2 = &getBoxBuffer()[(animy*32)+animx + 0x400];

    for (int i=0; i<count; i++) {
      if (animpos+i > w+h) break;
      *dst1 = 0;
      *dst2 = 0;
      dst1 += 31;
      dst2 += 31;
    }

    animpos++;
    if (animpos > w+h) {
      delete this;
      return;
    }
  }
}
