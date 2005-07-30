/*****************************  DARKSTAR  ******************************\
*  Copyright (c) 2005 Vincent E. Milum Jr., All rights reserved.        *
*                                                                       *
*  See License.txt for more information                                 *
*                                                                       *
*  Latest source versions can be found at:  HTTP://WWW.DARKAIN.COM/     *
\***********************************************************************/


#ifndef _DS_SPRITE_H_
#define _DS_SPRITE_H_


#include "dsSpriteEnum.h"
#include "dsSpriteManager.h"
//#include "../common/common.h"
#include "vTypes.h"



class dsSprite {
  public:
    dsSprite(DS_CORE dscore);
    ~dsSprite();

  public:
    //enable/disable hidden mode
    inline void hide() { oam->rotoscale = ROTOSCALE_HIDDEN; }
    inline void show() { oam->rotoscale = ROTOSCALE_NORMAL; }

    //position the sprite on the screen
    inline u16  getX() const { return oam->x; }
    inline u16  getY() const { return oam->y; }
    inline void setX(u16 x) { oam->x = x; }
    inline void setY(u16 y) { oam->y = y; }
    inline void move(u16 x, u16 y) { oam->x=x; oam->y=y; }

    
    inline DS_CORE getCore() const { return (DS_CORE)(sprite>>7); }
    inline SPRITE_SIZE getSpriteSize() const { return (SPRITE_SIZE)(oam->shape<<2 | oam->size); }
    inline u8 getSpriteIndex() const { return (sprite & 0x7F); }

    inline void setDisplay(SPRITE_DISPLAY display) { oam->display = display; }

    inline void setPriority(u8 priority) { oam->priority = priority; }

    inline void setFlip(SPRITE_FLIP flip) { oam->flip = flip; }

    inline void setPalette(u8 palette) { oam->palette = palette; }

    //how many tiles does a specific sprite size take?
    static u8 getTileSize(SPRITE_SIZE spriteSize);
    inline u8 getTileSize() const { return getTileSize(getSpriteSize()); }

  protected:
    typedef packed_union {
      packed_struct {
        // u16 ATTRIB0
        unsigned y            : 8;
        unsigned rotoscale    : 2;
        unsigned display      : 2;
        unsigned mosaic       : 1;
        unsigned highColor    : 1;
        unsigned shape        : 2;  //see size notes below

        // u16 ATTRIB1
        unsigned x            : 9;
        unsigned RESERVED1    : 3;  //RESERVED
//        unsigned flipHorz     : 1;  //shared with rotIndex
//        unsigned flipVert     : 1;  //shared with rotIndex
        unsigned flip         : 2;  //shared with rotIndex
        unsigned size         : 2;  //see size notes below

        // u16 ATTRIB2
        unsigned tileIndex    :10;
        unsigned priority     : 2;
        unsigned palette      : 4;
      };

      packed_struct {
        // u16 ATTRIB0
        unsigned RESERVED2    :16;  //RESERVED

        // u16 ATTRIB1
        unsigned RESERVED3    : 9;  //RESERVED
        unsigned rotIndex     : 5;  //shared with flip(Horz/Vert)
        unsigned RESERVED4    : 2;  //RESERVED

        // u16 ATTRIB2
        unsigned RESERVED5    :16;  //RESERVED
      };

      packed_struct {
        u16 ATTRIB0;
        u16 ATTRIB1;
        u16 ATTRIB2;
      };
    } sprite_struct;
    
    sprite_struct *oam;
    u8 sprite;
};



class dsSpriteSingle : public dsSprite {
  public:
    dsSpriteSingle(DS_CORE dscore, const void *sprData, SPRITE_SIZE sprSize, bool highClr=false, u8 sprPalette=0);
    ~dsSpriteSingle();

  public:
    //get the pointer to sprite RAM
    inline u16 *getMem() const { return (sprite & 0x80) ? &SPRITE_GFX_SUB[oam->tileIndex<<4] : &SPRITE_GFX[oam->tileIndex<<4]; }
};



#endif //_DS_SPRITE_H_
