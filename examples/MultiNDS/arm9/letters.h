/*****************************  DARKSTAR  ******************************\
*  Copyright (c) 2005 Vincent E. Milum Jr., All rights reserved.        *
*                                                                       *
*  See License.txt for more information                                 *
*                                                                       *
*  Latest source versions can be found at:  HTTP://WWW.DARKAIN.COM/     *
\***********************************************************************/



struct letterdata {
  u16 character;
  u16 width;
  u32 offset;
};


extern letterdata letters[];



extern const letterdata *getCharacter(u16 character);
extern u32 getTextWidth(const char *text);
extern u32 getTextWidth(const short *text);
extern u32 renderText(const char *text, u8 *buffer, u16 offx, u16 offy, u8 pal=1);
extern u32 renderText(const short *text, u8 *buffer, u16 offx, u16 offy, u8 pal=1);
