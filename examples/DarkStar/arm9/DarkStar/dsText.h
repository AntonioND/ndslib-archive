/*****************************  DARKSTAR  ******************************\
*  Copyright (c) 2005 Vincent E. Milum Jr., All rights reserved.        *
*                                                                       *
*  See License.txt for more information                                 *
*                                                                       *
*  Latest source versions can be found at:  HTTP://WWW.DARKAIN.COM/     *
\***********************************************************************/


#ifndef _DS_TEXT_H_
#define _DS_TEXT_H_


#include <NDS/DarkStar/dsEnums.h>


class dsText {
  public:
    dsText() {}
    ~dsText() {}

    //ANSI
    static void drawText(const char *text, u16 *buffer, u16 palette=1);
    static void drawText(const char *text, u16 *buffer, s16 x, s16 y, u16 palette=1);

    static void drawText(const char *text, s16 x, s16 y, DS_SCREEN screen, u16 palette=1);


    //UNICODE
    static void drawText(u16 *text, u16 *buffer, u16 palette=1);
    static void drawText(u16 *text, u16 *buffer, s16 x, s16 y, u16 palette=1);

    static void drawText(u16 *text, s16 x, s16 y, DS_SCREEN screen, u16 palette=1);
};


#endif //_DS_TEXT_H_
