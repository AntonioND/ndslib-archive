/*****************************  DARKSTAR  ******************************\
*  Copyright (c) 2005 Vincent E. Milum Jr., All rights reserved.        *
*                                                                       *
*  See License.txt for more information                                 *
*                                                                       *
*  Latest source versions can be found at:  HTTP://WWW.DARKAIN.COM/     *
\***********************************************************************/


#ifndef _DS_SWAP_SCREENS_H_
#define _DS_SWAP_SCREENS_H_


class dsSwapScreens {
  friend class dsMain;

  public:
    dsSwapScreens() { items.appendItem(this); }
    virtual ~dsSwapScreens() { items.removeItem(this); }

    virtual void onSwapScreen(bool activeScreen) {}

    void swapScreens();

  private:
    static vList<dsSwapScreens*> items;
};


#endif //_DS_SWAP_SCREENS_H_
