/*****************************  DARKSTAR  ******************************\
*  Copyright (c) 2005 Vincent E. Milum Jr., All rights reserved.        *
*                                                                       *
*  See License.txt for more information                                 *
*                                                                       *
*  Latest source versions can be found at:  HTTP://WWW.DARKAIN.COM/     *
\***********************************************************************/


#ifndef _MINES_H_
#define _MINES_H_


//DarkStar includes
#include "../DarkStar/dsBox.h"
#include <NDS/DarkStar/dsInput.h>
#include <NDS/DarkStar/dsClickable.h>
#include "../DarkStar/dsScrollBar.h"
#include <NDS/DarkStar/dsSprite.h>


class dsMinesBox;
class dsMinesScroll;
class dsMinesMoveScreen;


class dsMines : public dsClickRect, public dsInput {
  public:
    dsMines();
    virtual ~dsMines();

    void move(s16 x, s16 y);
    void renderField();
    void flagMine(u8 x, u8 y);
    void checkMine(u8 x, u8 y);
    void generateMap(u8 x, u8 y);

    void uncover(u8 x, u8 y);
    void uncoverSet(u8 x, u8 y);

    void updateText();

    virtual void onClick(s16 x, s16 y);
    virtual void onKeyChange(u32 inputState, u32 lastState);

   
    inline static const char *getAppName()  { return "DS-MINES - v0.4"; }
    inline static const char *getMenuName() { return "DS-MINES"; }
  
  private:
    dsMinesScroll *scroll;
    dsMinesMoveScreen *movescreen;
    u8 mine[22][32];
    int xoff, yoff;
    bool generated;
    bool bombed;
    s16 flagcount;

    dsToggleBox *flagbox;
    dsSprite *corner[4];
};


class dsMinesScroll : public dsScrollBarBoth {
  public:
    dsMinesScroll(dsMines *dsmines) { mines = dsmines; }
    virtual ~dsMinesScroll() {}

    virtual void onScrollHorz() { mines->renderField(); }
    virtual void onScrollVert() { mines->renderField(); }

  private:
    dsMines *mines;
};


class dsMinesMoveScreen : public dsClickRect {
  public:
    dsMinesMoveScreen(dsMines *dsmines) : dsClickRect(0, 16, 255, 191, DS_SCREEN_SUB) { mines = dsmines; }
    virtual ~dsMinesMoveScreen() {}

    virtual void onClick(s16 x, s16 y) { mines->move(x, y); }
    virtual void onDrag(s16 x, s16 y)  { mines->move(x, y); }
    virtual void onDrop(s16 x, s16 y)  { mines->move(x, y); }

  private:
    dsMines *mines;
};


#endif //_MINES_H_
