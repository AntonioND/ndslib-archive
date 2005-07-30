/*****************************  DARKSTAR  ******************************\
*  Copyright (c) 2005 Vincent E. Milum Jr., All rights reserved.        *
*                                                                       *
*  See License.txt for more information                                 *
*                                                                       *
*  Latest source versions can be found at:  HTTP://WWW.DARKAIN.COM/     *
\***********************************************************************/


#ifndef _MNDS_MENU_H_
#define _MNDS_MENU_H_


//darkstar includes
#include <NDS/DarkStar/dsInput.h>
#include <NDS/DarkStar/dsSprite.h>
#include <NDS/DarkStar/dsClickable.h>


class mndsClick;
class mndsFade;
class mndsGame;


class mndsMenu : public dsInput {
  public:
    mndsMenu();
    virtual ~mndsMenu();


    void loadGame();
    void updateDisplay(u8 dir=0);


    void moveUp() {
      if (sel > 0) {
        sel--;
        updateDisplay(2);
      } else if (top > 0) {
        top--;
        updateDisplay(2);
      }
    }

    void moveDown() {
      if ( (sel < 3) && (sel < games.getItemCount()-1) ) {
        sel++;
        updateDisplay(1);
      } else if (top < games.getItemCount()-4) {
        top++;
        updateDisplay(1);
      }
    }

    void pageUp() {
      if (top-4 >= 0) {
        top -= 4;
        updateDisplay(2);
      } else if (top+sel != 0) {
        top = 0;
        sel = 0;
        updateDisplay(2);
      }
    }

    void pageDown() {
      if (games.getItemCount() < 5) return;
      if (top+4 <= games.getItemCount()-4) {
        top += 4;
        updateDisplay(1);
      } else if (top+sel < games.getItemCount()-1) {
        top = games.getItemCount() - 4;
        sel = 3;
        updateDisplay(1);
      }
    }

    void onKeyChange(u32 inputState, u32 lastState) {
      if ( (lastState & KEY_UP)   && (!(inputState & KEY_UP)) )   { moveUp();   }
      if ( (lastState & KEY_DOWN) && (!(inputState & KEY_DOWN)) ) { moveDown(); }
      if ( (lastState & KEY_L)    && (!(inputState & KEY_L)) )    { pageUp();   }
      if ( (lastState & KEY_R)    && (!(inputState & KEY_R)) )    { pageDown(); }
      if ( (lastState & KEY_A)    && (!(inputState & KEY_A)) )    { loadGame(); }
    }


    void onClick(mndsClick *click) {
      for (int i=0; i<4; i++) {
        if (click == clicks[i] && i < games.getItemCount()) {
          if (sel != i) {
            sel = i;
            updateDisplay(3);
          }
          return;
        }
      }
    }


  private:
    u32 *zeros;
    u8 *buffer;

    s32 sel;
    s32 top;

    dsSpriteSingle *cursors[4];
    dsSpriteSingle *sprites[4];
    dsSpriteSingle *logo[3];
    dsSpriteSingle *icon;

	  dsSpriteSingle *up;
	  dsSpriteSingle *down;

    mndsFade *fade;

    mndsClick *clicks[4];

    vList<mndsGame*> games;
};




class mndsClick : public dsClickRect {
  public:
    mndsClick(s16 iy, mndsMenu *gmenu) : dsClickRect(0, iy, 255, iy+32, DS_SCREEN_MAIN) { menu=gmenu; }
    virtual ~mndsClick() {}
    virtual void onClick(s16 x, s16 y);

  private:
    mndsMenu *menu;
};



#endif //_MNDS_MENU_H_
