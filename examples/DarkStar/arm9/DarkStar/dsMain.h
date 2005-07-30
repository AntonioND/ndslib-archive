/*****************************  DARKSTAR  ******************************\
*  Copyright (c) 2005 Vincent E. Milum Jr., All rights reserved.        *
*                                                                       *
*  See License.txt for more information                                 *
*                                                                       *
*  Latest source versions can be found at:  HTTP://WWW.DARKAIN.COM/     *
\***********************************************************************/


#ifndef _DS_MAIN_H_
#define _DS_MAIN_H_


#include <NDS/DarkStar/dsEnums.h>


class dsApp;


class dsMain {
  public:
    dsMain();
    virtual ~dsMain();

    virtual void preSwapScreen() {}
    virtual void onSwapScreen() {}
    virtual bool canSwapScreens() { return true; }

    virtual void selItem(dsApp *app);

    void swapScreens();

    inline static bool getActiveScreen() { return activeScreen; }
    inline dsApp *getActiveApp() { return activeApp; }


    u16 *getBuffer(DS_SCREEN screen) const;
    inline u16 *getBuffer(bool active) const { return active ? BG_GFX_SUB : BG_GFX;  }
    inline u16 *getActiveBuffer()      const { return getBuffer( getActiveScreen()); }
    inline u16 *getInactiveBuffer()    const { return getBuffer(!getActiveScreen()); }

    /*
    loadTheme()
    theme = 0xFF to autodetect favourite colour
    palette = 0xFFFF to put theme data into BG_MAIN, BG_SUB,
      SPRITE_MAIN, and SPRITE_SUB pallete 0 each
    */
    void loadTheme(u8 theme=0xFF, u16 palette=0xFFFF);
    inline u8 getTheme() const { return themeid; }

  private:
    u8 themeid;
    dsApp *activeApp;
    static bool activeScreen;
};



#endif //_DS_MAIN_H_
