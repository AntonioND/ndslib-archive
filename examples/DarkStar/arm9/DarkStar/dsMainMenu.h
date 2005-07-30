/*****************************  DARKSTAR  ******************************\
*  Copyright (c) 2005 Vincent E. Milum Jr., All rights reserved.        *
*                                                                       *
*  See License.txt for more information                                 *
*                                                                       *
*  Latest source versions can be found at:  HTTP://WWW.DARKAIN.COM/     *
\***********************************************************************/


#ifndef _DS_MAINMENU_H_
#define _DS_MAINMENU_H_


//common includes
#include "../common.h"
#include <NDS/DarkStar/vArray.h>
#include <NDS/DarkStar/vName.h>

//local includes
#include "dsMain.h"
#include <NDS/DarkStar/dsClickable.h>
#include <NDS/DarkStar/dsInput.h>
#include <NDS/DarkStar/dsBlank.h>
#include "dsBox.h"


class dsMainMenu;
class dsAppMenu;
class dsSprite;
class dsSwapScrBtn;


extern dsMainMenu *mainmenu;


class dsMainMenu : public dsMain, public dsToggleBox, public dsInput, public dsBlank, public vName {
  friend class dsAppMenu;
  friend class dsMessageBox;

  public:
    dsMainMenu();
    virtual ~dsMainMenu();

    virtual void onClick(s16 x, s16 y) { openMenu(); }

    virtual void openMenu();
    virtual void cancelMenu();

    virtual void preSwapScreen();
    virtual void onSwapScreen();

    virtual void onVBlank();

    virtual void selItem(dsApp *app);

    virtual void onKeyChange(u32 inputState, u32 lastState);

    dsClickable *getLockedClickable(s16 x, s16 y, DS_SCREEN iscreen=DS_SCREEN_MAIN);

    void printTitle(const char *title);
    void messageBox(const char *text);


    inline const char *getShellName() const { return "[D]ARK-[S]TAR - BY DARKAIN"; }
    virtual void onNameChange(const char *newname);

    void restoreBackground(DS_SCREEN bg=DS_SCREEN_BOTH);

    inline bool getKeyLock() const { return keylock; }
    inline bool getTouchLock() { return touchlock; }

    void updateTextPalette();

    void appendBox(dsBox *box);
    void removeBox(dsBox *box);
    void updateBox();


  private:
    packed_union {
      packed_struct {
        unsigned keylock        : 1;
        unsigned touchlock      : 1;
        unsigned exclusivelock  : 1;
      };
      u32 lock;
    };

  private:
    dsAppMenu *appmenu;
    dsSprite *icons[2];
    dsSwapScrBtn *swapButtons;

    dsBox *bars[2];
    vList<dsBox*> appButtons;

    vList<dsInput*> lockedInputs;
    vList<dsClickable*> lockedClickables;
};


#endif // _DS_MAINMENU_H_
