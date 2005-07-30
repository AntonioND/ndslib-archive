/*****************************  DARKSTAR  ******************************\
*  Copyright (c) 2005 Vincent E. Milum Jr., All rights reserved.        *
*                                                                       *
*  See License.txt for more information                                 *
*                                                                       *
*  Latest source versions can be found at:  HTTP://WWW.DARKAIN.COM/     *
\***********************************************************************/


#ifndef _DS_PAINT_COLOR_H_
#define _DS_PAINT_COLOR_H_


#include <NDS/DarkStar/dsClickable.h>


class dsPaint;


class dsPaintColor : public dsClickRect {
  public:
    dsPaintColor(dsPaint *dspaint, u8 ix, u8 iy, u16 color, u16 palette, u32 tileloc);
    ~dsPaintColor();

    virtual void onClick(s16 x, s16 y);
    
    inline u16 getColor() const { return clr; }
  
  private:
    dsPaint *paint;
    u32 tile; 
    u16 clr;
};


#endif //_DS_PAINT_COLOR_H_
