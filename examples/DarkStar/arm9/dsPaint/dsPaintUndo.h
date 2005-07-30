/*****************************  DARKSTAR  ******************************\
*  Copyright (c) 2005 Vincent E. Milum Jr., All rights reserved.        *
*                                                                       *
*  See License.txt for more information                                 *
*                                                                       *
*  Latest source versions can be found at:  HTTP://WWW.DARKAIN.COM/     *
\***********************************************************************/


#ifndef _DS_PAINT_UNDO_H_
#define _DS_PAINT_UNDO_H_


#include "../DarkStar/dsBox.h"


class dsPaint;


class dsPaintUndo : public dsButton {
  public:
    dsPaintUndo(dsPaint *dspaint);
    virtual ~dsPaintUndo();

    virtual void onButton();

  private:
    dsPaint *paint;
};


#endif //_DS_PAINT_UNDO_H_
