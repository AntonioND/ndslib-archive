/*****************************  DARKSTAR  ******************************\
*  Copyright (c) 2005 Vincent E. Milum Jr., All rights reserved.        *
*                                                                       *
*  See License.txt for more information                                 *
*                                                                       *
*  Latest source versions can be found at:  HTTP://WWW.DARKAIN.COM/     *
\***********************************************************************/


#ifndef _MNDS_LOADGAME_H_
#define _MNDS_LOADGAME_H_


//DarkStar includes
#include <NDS/DarkStar/dsClickable.h>
#include <NDS/DarkStar/dsSprite.h>


class mndsMenu;


class mndsLoadGame : public dsClickRect, public dsSpriteSingle {
  public:
    mndsLoadGame(mndsMenu *gmenu);
    virtual ~mndsLoadGame();
    
    virtual void onClick(s16 x, s16 y);
    virtual void onDrag(s16 x, s16 y);
    virtual void onDrop(s16 x, s16 y);

  private:
    mndsMenu *menu;
};


#endif //_MNDS_LOADGAME_H_
