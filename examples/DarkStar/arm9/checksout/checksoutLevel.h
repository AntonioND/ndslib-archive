/*****************************  DARKSTAR  ******************************\
*  Copyright (c) 2005 Vincent E. Milum Jr., All rights reserved.        *
*                                                                       *
*  See License.txt for more information                                 *
*                                                                       *
*  Latest source versions can be found at:  HTTP://WWW.DARKAIN.COM/     *
\***********************************************************************/


#ifndef _CHECKSOUT_LEVEL_H_
#define _CHECKSOUT_LEVEL_H_


//DarkStar includes
#include "../DarkStar/dsBox.h"
#include <NDS/DarkStar/dsSprite.h>


class dsChecksOut;


class dsChecksOutLevel : public dsToggleBox, public dsSpriteSingle {
  public:
    dsChecksOutLevel(u8 x, u8 y, s32 lvl, dsChecksOut *checksout);
    virtual ~dsChecksOutLevel() {}

    virtual void onClick(s16 x, s16 y);
    virtual bool hitTest(s16 x, s16 y, DS_SCREEN iscreen=DS_SCREEN_MAIN);

  private:
    s32 level;
    dsChecksOut  *checks;
};


#endif //_CHECKSOUT_LEVEL_H_
