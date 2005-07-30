/*****************************  DARKSTAR  ******************************\
*  Copyright (c) 2005 Vincent E. Milum Jr., All rights reserved.        *
*                                                                       *
*  See License.txt for more information                                 *
*                                                                       *
*  Latest source versions can be found at:  HTTP://WWW.DARKAIN.COM/     *
\***********************************************************************/


#ifndef _DS_SPRITE_ENUM_H_
#define _DS_SPRITE_ENUM_H_


/*
shape/size is 4-bits spread across attrib0 and attrib1
first two bits are shape, second two are size
0000:  8 x  8        1000:  8 x 16
0001: 16 x 16        1001:  8 x 32
0010: 32 x 32        1010: 16 x 32
0011: 64 x 64        1011: 32 x 64
0100: 16 x  8        1100: Not used
0101: 32 x  8        1101: Not used
0110: 32 x 16        1110: Not used
0111: 64 x 32        1111: Not used

SOURCE: http://www.cs.rit.edu/~tjh8300/CowBite/CowBiteSpec.htm#OAM%20(sprites)
*/

typedef enum {
  SIZE_8_X_8    = 0x0,
  SIZE_16_X_16  = 0x1,
  SIZE_32_X_32  = 0x2,
  SIZE_64_X_64  = 0x3,

  SIZE_16_X_8   = 0x4,
  SIZE_32_X_8   = 0x5,
  SIZE_32_X_16  = 0x6,
  SIZE_64_X_32  = 0x7,

  SIZE_8_X_16   = 0x8,
  SIZE_8_X_32   = 0x9,
  SIZE_16_X_32  = 0xA,
  SIZE_32_X_64  = 0xB,

  SIZE_UNK1     = 0xC,
  SIZE_UNK2     = 0xD,
  SIZE_UNK3     = 0xE,
  SIZE_UNK4     = 0xF,
} SPRITE_SIZE;


typedef enum {
  ROTOSCALE_NORMAL     = 0x0, 
  ROTOSCALE_ROTATION   = 0x1, 
  ROTOSCALE_HIDDEN     = 0x2,
  ROTOSCALE_DOUBLESIZE = 0x3,
} SPRITE_ROTOSCALE;


typedef enum {
  DISPLAY_NORMAL      = 0x0,
  DISPLAY_TRANSPARENT = 0x1,
  DISPLAY_WINDOW      = 0x2,
  DISPLAY_TRUECOLOR   = 0x3,  // not available on GBA
} SPRITE_DISPLAY;


typedef enum {
  FLIP_NONE = 0x0,
  FLIP_HORZ = 0x1,
  FLIP_VERT = 0x2,
  FLIP_BOTH = 0x3,
} SPRITE_FLIP;


#endif //_DS_SPRITE_ENUM_H_
