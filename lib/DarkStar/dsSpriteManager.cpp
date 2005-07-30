/*****************************  DARKSTAR  ******************************\
*  Copyright (c) 2005 Vincent E. Milum Jr., All rights reserved.        *
*                                                                       *
*  See License.txt for more information                                 *
*                                                                       *
*  Latest source versions can be found at:  HTTP://WWW.DARKAIN.COM/     *
\***********************************************************************/


#include <NDS/NDS.h>

#include <NDS/DarkStar/dsSpriteManager.h>


dsSpriteManager *sprmgr = 0;


dsSpriteManager::dsSpriteManager(bool clear) {
  sprmgr = this;

  //hide all sprites
  //there are 128 sprites per core, but
  //their memory address are right next
  //to each other, so we can loop from 0
  //to 255 and it will work
  if (clear) {
    for (int i=0; i<256; i++) {
      oam[i<<2] = 0x0200;
    }
  }

  for (int y=0; y<2; y++) {
    for (int x=0; x<128; x++) {
      spriteAlloc[y][x] = 0;
    }
    for (int x=0; x<1024; x++) {
      data[y][x] = 0;
    }
  }
  data[0][0] = 1;
  data[1][0] = 1;
}


dsSpriteManager::~dsSpriteManager() {
  sprmgr = 0;
}


u8 dsSpriteManager::allocSprite(DS_CORE core) {
  for (int i=0; i<128; i++) {
    if (spriteAlloc[core][i] == 0) {
      spriteAlloc[core][i] = 1;
      return i;
    }
  }
  return 0xFF;  //error, no free sprites
}


void dsSpriteManager::freeSprite(DS_CORE core, u8 sprite) {
  spriteAlloc[core][sprite] = 0;
}


u16 dsSpriteManager::allocSpriteMem(DS_CORE core, u16 size) {
  for (int i=0; i<1024-size; i++) {
    if (data[core][i] == 0) {
      bool ok=true;
      for (int x=0; x<size; x++) if (data[core][i+x] != 0) ok=false;

      if (ok) {
        for (int x=0; x<size; x++) data[core][i+x] = 1;
        return i;
      }
    }
  }
  return 0xFFFF;  //error, no available mem
}


void dsSpriteManager::freeSpriteMem(DS_CORE core, u16 tile, u16 size) {
  for (int i=0; i<size; i++) data[core][tile+i] = 0;
}


void dsSpriteManager::updateSystemOAM() {
  DC_FlushAll();
  dmaCopyHalfWords(3, oam, OAM, sizeof(oam));
}

void dsSpriteManager::updateLocalOAM()  {
  DC_FlushAll();
  dmaCopyHalfWords(3, OAM, oam, sizeof(oam));
}
