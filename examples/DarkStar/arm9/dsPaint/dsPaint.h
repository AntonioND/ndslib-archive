/*****************************  DARKSTAR  ******************************\
*  Copyright (c) 2005 Vincent E. Milum Jr., All rights reserved.        *
*                                                                       *
*  See License.txt for more information                                 *
*                                                                       *
*  Latest source versions can be found at:  HTTP://WWW.DARKAIN.COM/     *
\***********************************************************************/


#ifndef _DS_PAINT_H_
#define _DS_PAINT_H_


#include "../DarkStar/dsApp.h"
#include <NDS/DarkStar/dsGfx.h>
#include "../DarkStar/dsText.h"
#include <NDS/DarkStar/dsInput.h>
#include <NDS/DarkStar/dsClickable.h>


class dsPaintSlider;
class dsPaintColor;
class dsPaintUndo;
class dsPaintClear;


class dsPaint : public dsGfx, public dsClickRect, public dsText, public dsInput {
  public:
    dsPaint();
    virtual ~dsPaint();

    virtual void onClick(s16 x, s16 y);
    virtual void onDrag(s16 x, s16 y);
    virtual void onDrop(s16 x, s16 y);

    void flipH();
    void flipV();

    inline u16 getColor() const { return clr; }
    void setColor(u16 color);
    void updateColor();

    u8 getAlpha() const;

    inline u8 getSize() const { return size; }

    u16 *getScreenBuffer();

    virtual void onKeyChange(u32 inputState, u32 lastState);

    // info for dsApp template
    inline static const char *getAppName()  { return "DS-PAINT - v0.4"; }
    inline static const char *getMenuName() { return "DS-PAINT"; }

  protected:
    dsPaintSlider *red;
    dsPaintSlider *green;
    dsPaintSlider *blue;
    dsPaintSlider *alph;

    dsPaintUndo *undo;
    dsPaintClear *clear;

    u8 size;

    s16 ox, oy;
    u16 clr;
    u16 buffer[2][256*176];

    vList<dsPaintColor*> colors;
};


#endif //_DS_PAINT_H_
