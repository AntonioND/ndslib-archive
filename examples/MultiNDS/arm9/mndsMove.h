/*****************************  DARKSTAR  ******************************\
*  Copyright (c) 2005 Vincent E. Milum Jr., All rights reserved.        *
*                                                                       *
*  See License.txt for more information                                 *
*                                                                       *
*  Latest source versions can be found at:  HTTP://WWW.DARKAIN.COM/     *
\***********************************************************************/


#ifndef _MNDS_MOVE_H_
#define _MNDS_MOVE_H_


//DarkStar includes
#include <NDS/DarkStar/dsClickable.h>
#include <NDS/DarkStar/dsSprite.h>


class mndsMenu;


class mndsMoveUp : public dsClickRect, public dsSpriteSingle {
  public:
    mndsMoveUp(mndsMenu *gmenu);
    virtual ~mndsMoveUp();
    
    virtual void onClick(s16 x, s16 y);
    virtual void onDrag(s16 x, s16 y);
    virtual void onDrop(s16 x, s16 y);

  private:
    mndsMenu *menu;
};


////////////////////////////////////////////////////////////////////////////////////////


class mndsMoveDown : public dsClickRect, public dsSpriteSingle {
  public:
    mndsMoveDown(mndsMenu *gmenu);
    virtual ~mndsMoveDown();
    
    virtual void onClick(s16 x, s16 y);
    virtual void onDrag(s16 x, s16 y);
    virtual void onDrop(s16 x, s16 y);

  private:
    mndsMenu *menu;
};


#endif //_MNDS_MOVE_H_
