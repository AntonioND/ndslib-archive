/*****************************  DARKSTAR  ******************************\
*  Copyright (c) 2005 Vincent E. Milum Jr., All rights reserved.        *
*                                                                       *
*  See License.txt for more information                                 *
*                                                                       *
*  Latest source versions can be found at:  HTTP://WWW.DARKAIN.COM/     *
\***********************************************************************/


#ifndef _DS_DEBUG_H_
#define _DS_DEBUG_H_


#include "../DarkStar/dsApp.h"
#include <NDS/DarkStar/dsBlank.h>
#include <NDS/DarkStar/dsClickable.h>


class dsDebug : public dsBlank, dsClickRect {
  public:
    dsDebug();
    virtual ~dsDebug();

    void print(const char *text, u8 x, u8 y, u8 screen=1);
    void print(const short *text, u8 x, u8 y, u8 screen=1);

    virtual void onVBlank();

    const char *getMonthName(int month) const;


    virtual void onClick(s16 x, s16 y) { tx=x;  ty=y; }
    virtual void onDrag(s16 x, s16 y)  { tx=x;  ty=y; }
    virtual void onDrop(s16 x, s16 y)  { tx=x;  ty=y; }

    inline static const char *getAppName()  { return "[D]ARK-[S]TAR - DEBUG"; }
    inline static const char *getMenuName() { return "DEBUG"; }

  private:
    s16 tx, ty;
};


#endif //_DS_DEBUG_H_
