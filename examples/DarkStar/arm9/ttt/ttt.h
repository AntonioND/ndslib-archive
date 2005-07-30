/*****************************  DARKSTAR  ******************************\
*  Copyright (c) 2005 Vincent E. Milum Jr., All rights reserved.        *
*                                                                       *
*  See License.txt for more information                                 *
*                                                                       *
*  Latest source versions can be found at:  HTTP://WWW.DARKAIN.COM/     *
\***********************************************************************/


#ifndef _TTT_H_
#define _TTT_H_


//DarkStar includes
#include "../DarkStar/dsApp.h"
#include <NDS/DarkStar/dsClickable.h>
#include "../DarkStar/dsMessageBox.h"


class dsTTTButton;


class dsTTT : public dsMsgBoxCallback {
  public:
    dsTTT();
    virtual ~dsTTT();

    inline bool getLock() const { return lock; }

    void resetGame();
    void AI();

    virtual void onButtonPress(u8 id);

    inline static const char *getAppName()  { return "TIC-TAC-TOE - v0.4"; }
    inline static const char *getMenuName() { return "TIC-TAC-TOE"; }

  private:
    dsTTTButton *btn[9];
    int count;
    bool lock;
    bool start;
};


class dsTTTButton : public dsClickRect {
  public:
    dsTTTButton(u8 ix, u8 iy, dsTTT *dsttt);
    ~dsTTTButton();

    void setTile(u8 value);
    inline u8 getVal() const { return val; }

    virtual void onClick(s16 x, s16 y);

  private:
    u8 x, y;
    u8 val;
    dsTTT *ttt;
};


#endif //_TTT_H_
