/*****************************  DARKSTAR  ******************************\
*  Copyright (c) 2005 Vincent E. Milum Jr., All rights reserved.        *
*                                                                       *
*  See License.txt for more information                                 *
*                                                                       *
*  Latest source versions can be found at:  HTTP://WWW.DARKAIN.COM/     *
\***********************************************************************/


#ifndef _MNDS_GAME_H_
#define _MNDS_GAME_H_


#include "gbfs/gbfs.h"


#define GBFS (0x08004000)


class mndsGame {
  public:
    mndsGame(const GBFS_ENTRY *entry);
    virtual ~mndsGame();

    const GBFS_ENTRY *getFile() const { return file; }

    u32 getOffset() const { return offset; }
    u32 getFilesize() const { return filesize; }
    const char *getFilename() const { return name; }
    const char *getGamecode() const { return gamecode; }
    const s16  *getTextData(u8 id) const { return textdata[id]; }
    const u8   *getIcon() const { return icondata; }
    const u16  *getPalette() const { return palette; }


  private:
    const GBFS_ENTRY *file;
    const char *data;
    u32 offset;
    u32 filesize;

    s16  text[128];
    s16 *textdata[3];

    u16  palette[16];
    u8   icondata[512];

    char gamecode[18];

    char name[25];
};


#endif //_MNDS_GAME_H_
