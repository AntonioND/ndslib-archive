/*****************************  DARKSTAR  ******************************\
*  Copyright (c) 2005 Vincent E. Milum Jr., All rights reserved.        *
*                                                                       *
*  See License.txt for more information                                 *
*                                                                       *
*  Latest source versions can be found at:  HTTP://WWW.DARKAIN.COM/     *
\***********************************************************************/


#include <stdlib.h>
#include <string.h>

//library includes
#include <NDS/NDS.h>

//local includes
#include "common.h"
#include "mndsGame.h"

//resources
#include "default_raw.h"
#include "default_pal.h"


mndsGame::mndsGame(const GBFS_ENTRY *entry) {
  file = entry;
  offset = file->data_offset;
  data = (char*)(GBFS + offset);
  filesize = file->len;

  memcpy(name, file->name, 24);
  name[24] = 0x00;

  memcpy(gamecode, data+0xC, 4);
  gamecode[4] = '-';
  memcpy(&gamecode[5], data+0x0, 12);
  gamecode[17] = 0;

  u32 iconres = ( *(u32*)(data + 0x068) );

  if ( (iconres != 0) && (iconres < file->len - 1088) ) {
    memcpy(palette,  data + iconres + 544,  32);
    memcpy(icondata, data + iconres +  32, 512);
    memcpy(text,     data + iconres + 576 + (personal->language * 256),  256);
  } else {
    memcpy(palette,  default_pal,  32);
    memcpy(icondata, default_raw, 512);
    text[0] = 0;
  }

  textdata[0] = text;
  textdata[1] = 0;
  textdata[2] = 0;

  s16 *txt = textdata[0];
  u8 count = 0;
  while (*txt) {
    if (*txt == '\n') {
      *txt = 0x0000;
      count++;
      if (count >= 3) break;
      textdata[count] = txt+1;
    }
    txt++;
  }
}



mndsGame::~mndsGame() {
}
