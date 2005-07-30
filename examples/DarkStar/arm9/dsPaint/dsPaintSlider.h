/*****************************  DARKSTAR  ******************************\
*  Copyright (c) 2005 Vincent E. Milum Jr., All rights reserved.        *
*                                                                       *
*  See License.txt for more information                                 *
*                                                                       *
*  Latest source versions can be found at:  HTTP://WWW.DARKAIN.COM/     *
\***********************************************************************/


#ifndef _DS_PAINT_SLIDER_H_
#define _DS_PAINT_SLIDER_H_


//includes
#include <NDS/DarkStar/dsSprite.h>
#include <NDS/DarkStar/dsClickable.h>


class dsPaint;


class dsPaintSlider : public dsClickRect, public dsSpriteSingle {
  public:
    dsPaintSlider(dsPaint *dspaint, s16 x, s16 y);
    virtual ~dsPaintSlider() {}

    virtual void onClick(s16 x, s16 y);
    virtual void onDrag(s16 x, s16 y);

    inline u16 getValue() const { return value; }
    void setValue(u8 val);

  private:
    dsPaint *paint;
    u8 value;
};


#endif //_DS_PAINT_SLIDER_H_
