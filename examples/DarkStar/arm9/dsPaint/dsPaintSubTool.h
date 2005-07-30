/*****************************  DARKSTAR  ******************************\
*  Copyright (c) 2005 Vincent E. Milum Jr., All rights reserved.        *
*                                                                       *
*  See License.txt for more information                                 *
*                                                                       *
*  Latest source versions can be found at:  HTTP://WWW.DARKAIN.COM/     *
\***********************************************************************/


#ifndef _DS_PAINT_SUBTOOL_H_
#define _DS_PAINT_SUBTOOL_H_


//DarkStar includes
#include "../DarkStar/dsBox.h"
#include <NDS/DarkStar/dsSprite.h>


class dsPaintTool;


class dsPaintSubTool : public dsToggleBox, public dsSpriteSingle {
  public:
    dsPaintSubTool(dsPaintTool *painttool, u8 x, u8 y, const void *sprData, u8 subId=0);
    virtual ~dsPaintSubTool();

    virtual void onClick(s16 x, s16 y);

  private:
    u8 id;
    dsPaintTool *tool;
};


#endif //_DS_PAINT_SUBTOOL_H_
