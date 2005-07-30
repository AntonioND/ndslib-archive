/*****************************  DARKSTAR  ******************************\
*  Copyright (c) 2005 Vincent E. Milum Jr., All rights reserved.        *
*                                                                       *
*  See License.txt for more information                                 *
*                                                                       *
*  Latest source versions can be found at:  HTTP://WWW.DARKAIN.COM/     *
\***********************************************************************/


#include <NDS/NDS.h>

#include "common.h"


u32 seed = 1;

vu32 *DEBUG0 = (vu32*)0x02003FF0;
vu32 *DEBUG1 = (vu32*)0x02003FF4;
vu32 *DEBUG2 = (vu32*)0x02003FF8;
vu32 *DEBUG3 = (vu32*)0x02003FFC;

PERSONAL_DATA *personal = (PERSONAL_DATA*)0x27FFC80;

unsigned int volatile vlistcount = 0;



char *itoa(int val, char *buffer) {
  ASSERT(buffer != NULL);

	char *nbuffer = buffer;
	*buffer = ((val>>28)&0x0F)+'0';
	if (*buffer > '9') *buffer += 7;
	buffer++;
	*buffer = ((val>>24)&0x0F)+'0';
	if (*buffer > '9') *buffer += 7;
	buffer++;
	*buffer = ((val>>20)&0x0F)+'0';
	if (*buffer > '9') *buffer += 7;
	buffer++;
	*buffer = ((val>>16)&0x0F)+'0';
	if (*buffer > '9') *buffer += 7;
	buffer++;
	*buffer = ((val>>12)&0x0F)+'0';
	if (*buffer > '9') *buffer += 7;
	buffer++;
	*buffer = ((val>>8)&0x0F)+'0';
	if (*buffer > '9') *buffer += 7;
	buffer++;
	*buffer = ((val>>4)&0x0F)+'0';
	if (*buffer > '9') *buffer += 7;
	buffer++;
	*buffer = ((val)&0x0F)+'0';
	if (*buffer > '9') *buffer += 7;
	buffer++;
	*buffer = 0;
	return nbuffer;
}

/*
void print(const char *text) {
  if (!text) return;
  if (!*text) return;

  static u8 x=0;
  static u8 y=0;

  u16 *map = (u16*)BG_MAP_RAM_SUB(0);

  while (*text) {
    if (*text == '\r') {
      x = 0;
    } else if (*text == '\n') {
      x = 0;
      y++; //todo: check to see if we are at the bottom, and scroll
    }
  
    else if ( (*text >= '!') && (*text <= '~') ) {
      if (x == 32) {
        x = 0;
        y++;
      }

      if ( (*text >= 'a') && (*text <= 'z') ) {
        map[(y*32)+x] = *text - ('!'+31);
      } else {
        map[(y*32)+x] = *text - ('!'-1);
      }
      
      x++;
    }

    else {
      if (x == 32) {
        x = 0;
        y++; //todo: check to see if we are at the bottom, and scroll
      }

      map[(y*32)+x] = 0;

      x++;
    }

    text++;
  }
}


void print16(u16 *text) {
  if (!text) return;
  if (!*text) return;
  if (*text == 0xffff) return;
  if (*text == 0x00ff) return;
  if (*text == 0xff00) return;
  char str[2] = {0, 0};

  while (*text) {
    str[0] = (char)(*text & 0x00FF);
    print(str);
    text++;
  }
}


void printmem(u32 addr, u8 size) {
  u8 *data = (u8*)addr;
  char str[3] = {0, 0, 0};

  for (int i=0; i<size; i++) {
    u8 hi = *data >> 4;
    u8 lo = *data & 0x0F;

    if (hi > 9) {
      str[0] = hi - 10 + 'A';
    } else {
      str[0] = hi + '0';
    }

    if (lo > 9) {
      str[1] = lo - 10 + 'A';
    } else {
      str[1] = lo + '0';
    }

    print(str);
    data++;
  }
  print("\n");
}


void initDebug() {
/ *  DEBUG0 = new vu32;
  DEBUG1 = new vu32;
  DEBUG2 = new vu32;
  DEBUG3 = new vu32;
  *DEBUG0 = 0;
  *DEBUG1 = 0;
  *DEBUG2 = 0;
  *DEBUG3 = 0;* /
}
*/

