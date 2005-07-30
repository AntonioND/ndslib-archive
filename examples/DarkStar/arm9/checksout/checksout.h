/*****************************  DARKSTAR  ******************************\
*  Copyright (c) 2005 Vincent E. Milum Jr., All rights reserved.        *
*                                                                       *
*  See License.txt for more information                                 *
*                                                                       *
*  Latest source versions can be found at:  HTTP://WWW.DARKAIN.COM/     *
\***********************************************************************/


#ifndef _CHECKSOUT_H_
#define _CHECKSOUT_H_


//#include "../DarkStar/dsApp.h"
//#include "../DarkStar/dsBox.h"
#include <NDS/DarkStar/dsBlank.h>
//#include "../DarkStar/dsSprite.h"
//#include "../DarkStar/dsClickable.h"
#include "../DarkStar/dsMessageBox.h"


class dsChecksOut;
class dsChecksOutBox;
class dsChecksOutLevel;


class dsChecksOut : public dsBlank, public dsMsgBoxCallback {
  public:
    dsChecksOut();
    virtual ~dsChecksOut();

    void change(u8 x, u8 y);

    u8 getCount();

    void loadLevel(s32 lvl);

    void updateText();

    virtual void onVBlank();

    virtual void onButtonPress(u8 id);

    inline static const char *getAppName()  { return "CHECKS OUT - v0.4"; }
    inline static const char *getMenuName() { return "CHECKS OUT"; }

  private:
    s32 clicks;
    s32 level;
    u8 lastx, lasty;
    dsChecksOutBox *boxes[10][10];
    dsChecksOutLevel *levels[11];

    static const u16 puzzle[][10];
};


#endif //_CHECKSOUT_H_
