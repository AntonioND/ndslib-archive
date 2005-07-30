/*****************************  DARKSTAR  ******************************\
*  Copyright (c) 2005 Vincent E. Milum Jr., All rights reserved.        *
*                                                                       *
*  See License.txt for more information                                 *
*                                                                       *
*  Latest source versions can be found at:  HTTP://WWW.DARKAIN.COM/     *
\***********************************************************************/


#ifndef _DS_PAINT_CLEAR_H_
#define _DS_PAINT_CLEAR_H_


#include "../DarkStar/dsBox.h"


class dsPaint;


class dsPaintClear : public dsButton {
  public:
    dsPaintClear(dsPaint *dspaint);
    virtual ~dsPaintClear();

    virtual void onButton();

  private:
    dsPaint *paint;
};


#endif //_DS_PAINT_CLEAR_H_
