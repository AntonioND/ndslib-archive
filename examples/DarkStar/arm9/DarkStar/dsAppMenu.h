/*****************************  DARKSTAR  ******************************\
*  Copyright (c) 2005 Vincent E. Milum Jr., All rights reserved.        *
*                                                                       *
*  See License.txt for more information                                 *
*                                                                       *
*  Latest source versions can be found at:  HTTP://WWW.DARKAIN.COM/     *
\***********************************************************************/


#ifndef _DS_APPMENU_H_
#define _DS_APPMENU_H_


//local includes
#include <NDS/DarkStar/dsClickable.h>
#include <NDS/DarkStar/dsInput.h>
#include <NDS/DarkStar/dsBlank.h>
#include "dsText.h"
#include "dsBox.h"
#include "dsApp.h"


class dsMenuItem;
class dsMainMenu;


class dsAppMenu : public dsBox, public dsClickRect, public dsInput, public dsBlank {
  friend class dsMenuItem;

  public:
    dsAppMenu(dsMainMenu *mainmenu);
    virtual ~dsAppMenu();

    void killMenu();

    virtual void onClick(s16 x, s16 y);
    void selItem(dsApp *app);

    virtual void onKeyChange(u32 inputState, u32 lastState);

    virtual void onVBlank();

    inline DS_SCREEN getActiveScreen() const { return (activeScreen) ? DS_SCREEN_SUB : DS_SCREEN_MAIN; }

  private:
    dsMainMenu *main;
    s16 w, h;
    bool activeScreen;
    vList<dsMenuItem*> items;
    dsMenuItem *selected;

    u8 anim;
    s16 animpos;
    u16 backbuff[32*24];
    u16 textbuff[32*24];
};



class dsMenuItem : public dsClickRect, public dsText {
  public:
    dsMenuItem(dsAppMenu *appmenu, dsApp *dsapp, u8 ix, u8 iy) : dsClickRect(0, 0, 0, 0, DS_SCREEN_BOTH) {
      app = dsapp;
      menu = appmenu;
      mx=ix; my=iy;
    }

    virtual ~dsMenuItem() {}

    virtual void onClick(s16 x, s16 y) { menu->selItem(app); }
    dsApp *getApp() { return app; }

//    void printText(u8 palette, u16 *buffer) { drawText(app->getAppMenuName(),  }

    void printText(u8 palette, u16 *buffer) {
      drawText(app->getMenuName(), buffer, mx, my, palette);
    }

  private:
    dsAppMenu *menu;
    dsApp *app;
    u8 mx, my;
};


#endif //_DS_APPMENU_H_
