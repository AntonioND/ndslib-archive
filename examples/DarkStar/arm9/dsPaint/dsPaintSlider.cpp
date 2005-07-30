/*****************************  DARKSTAR  ******************************\
*  Copyright (c) 2005 Vincent E. Milum Jr., All rights reserved.        *
*                                                                       *
*  See License.txt for more information                                 *
*                                                                       *
*  Latest source versions can be found at:  HTTP://WWW.DARKAIN.COM/     *
\***********************************************************************/


//libs
#include <NDS/NDS.h>

//local headers
#include "dsPaint.h"
#include "dsPaintSlider.h"
#include "../common.h"

//resources
#include "menu_raw.h"


dsPaintSlider::dsPaintSlider(dsPaint *dspaint, s16 x, s16 y)
 : dsClickRect(x, y, x+16, y+127, DS_SCREEN_SUB), dsSpriteSingle(DS_CORE_SUB, &menu_raw[288], SIZE_16_X_8, false, 1) {
  move(x, y-2);
  paint = dspaint;
  value = 31;
}


void dsPaintSlider::onClick(s16 x, s16 y) {
  y = min(y2, max(y1, y));
  setY(y-2);
  value = 31 - ((y - y1) >> 2);
  paint->updateColor();
}

void dsPaintSlider::onDrag(s16 x, s16 y) {
  y = min(y2, max(y1, y));
  setY(y-2);
  value = 31 - ((y - y1) >> 2);
  paint->updateColor();
}

void dsPaintSlider::setValue(u8 val) {
  value = val;
  setY( ((31 - value) << 2) + y1 );
}
