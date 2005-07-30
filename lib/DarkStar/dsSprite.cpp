/*****************************  DARKSTAR  ******************************\
*  Copyright (c) 2005 Vincent E. Milum Jr., All rights reserved.        *
*                                                                       *
*  See License.txt for more information                                 *
*                                                                       *
*  Latest source versions can be found at:  HTTP://WWW.DARKAIN.COM/     *
\***********************************************************************/


#include <NDS/NDS.h>

#include <NDS/DarkStar/dsSprite.h>


dsSprite::dsSprite(DS_CORE dscore) {
  sprite = sprmgr->allocSprite(dscore) | (dscore << 7);
  oam = (sprite_struct*)sprmgr->getOAM(sprite);

  oam->ATTRIB0 = 0x0000;
  oam->ATTRIB1 = 0x0000;
  oam->ATTRIB2 = 0x0000;
}


dsSprite::~dsSprite() {
  oam->ATTRIB0 = 0x0200;  //hide the sprite
  oam->ATTRIB1 = 0x0000;
  oam->ATTRIB2 = 0x0000;

  sprmgr->freeSprite(getCore(), getSpriteIndex());
}


u8 dsSprite::getTileSize(SPRITE_SIZE spriteSize) {
  switch (spriteSize) {
    case  SIZE_8_X_8:
      return 1;

    case SIZE_16_X_8:
    case SIZE_8_X_16:
      return 2;

    case SIZE_16_X_16:
    case SIZE_32_X_8:
    case SIZE_8_X_32:
      return 4;

    case SIZE_32_X_16:
    case SIZE_16_X_32:
      return 8;

    case SIZE_32_X_32:
      return 16;

    case SIZE_64_X_32:
    case SIZE_32_X_64:
      return 32;

    case SIZE_64_X_64:
      return 64;

    //GCC wined when i didnt implement these
    case SIZE_UNK1:
    case SIZE_UNK2:
    case SIZE_UNK3:
    case SIZE_UNK4:
      return 0;
  }
  return 0;
}



/////////////////////////////////////////////////////////////////////////////////////////


dsSpriteSingle::dsSpriteSingle(DS_CORE dscore, const void *sprData, SPRITE_SIZE sprSize, bool highClr, u8 sprPalette)
 : dsSprite(dscore) {

  //get the size (in tiles) of our sprite, and allocate ram
  u8 tilesize = getTileSize(sprSize);
  if (highClr) tilesize <<= 1;
  u16 tile = sprmgr->allocSpriteMem(dscore, tilesize);

  //store our params, ATTRIB0
  oam->highColor = highClr;
  oam->shape = (sprSize >> 2);

  //store our params, ATTRIB1
  oam->size = (sprSize & 0x3);

  //store our params, ATTRIB2
  oam->tileIndex = tile;
  oam->priority = 2;  // default to priority 2, for the sake or DarkStar
  oam->palette = sprPalette;


  //copy sprite data to sprite ram
  dmaCopyHalfWords(3, sprData, getMem(), tilesize<<5);
}


dsSpriteSingle::~dsSpriteSingle() {
  //deallocate our sprite ram
  sprmgr->freeSpriteMem(getCore(), oam->tileIndex, getTileSize(getSpriteSize()));
}
