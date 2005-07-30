/*****************************  DARKSTAR  ******************************\
*  Copyright (c) 2005 Vincent E. Milum Jr., All rights reserved.        *
*                                                                       *
*  See License.txt for more information                                 *
*                                                                       *
*  Latest source versions can be found at:  HTTP://WWW.DARKAIN.COM/     *
\***********************************************************************/


#ifndef _DS_MESSAGE_BOX_H_
#define _DS_MESSAGE_BOX_H_


//local includes
#include "dsBox.h"
#include <NDS/DarkStar/dsInput.h>
#include <NDS/DarkStar/dsEnums.h>


class dsMessageBox;
class dsMessageBoxButton;
class dsMsgBoxCallback;


class dsMessageBox : public dsBox, public dsInput {
  public:
    dsMessageBox(const char *text, DS_SCREEN dsscreen=DS_SCREEN_NONE);
    virtual ~dsMessageBox();

    virtual void onKeyChange(u32 inputState, u32 lastState);

    void onButtonPress(u8 id);

    inline void setCallback(dsMsgBoxCallback *callback) { cb = callback; }

  private:
    dsMessageBoxButton *btnOk;
    dsMsgBoxCallback *cb;
};


class dsMessageBoxButton : public dsButton {
  public:
    dsMessageBoxButton(u8 btnid, dsMessageBox *dsbox, s16 bx, s16 by, s16 bw, s16 bh, const char *btext)
      : dsButton(bx, by, bw, bh, btext) {
      id = btnid;
      msgbox = dsbox;
    }

    virtual ~dsMessageBoxButton() {}

    virtual void onButton() { msgbox->onButtonPress(id); }

  private:
    dsMessageBox *msgbox;
    u8 id;
};



class dsMsgBoxCallback {
  public:
    dsMsgBoxCallback() {}
    virtual ~dsMsgBoxCallback() {}

    virtual void onButtonPress(u8 id)=0;

    dsMessageBox *msgbox(const char *text) {
      dsMessageBox *msg = new dsMessageBox(text);
      msg->setCallback(this);
      return msg;
    }
};

#endif //_DS_MESSAGE_BOX_H_
