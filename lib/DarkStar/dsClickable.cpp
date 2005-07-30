/*****************************  DARKSTAR  ******************************\
*  Copyright (c) 2005 Vincent E. Milum Jr., All rights reserved.        *
*                                                                       *
*  See License.txt for more information                                 *
*                                                                       *
*  Latest source versions can be found at:  HTTP://WWW.DARKAIN.COM/     *
\***********************************************************************/


#include <NDS/NDS.h>
#include <NDS/DarkStar/dsClickable.h>


vList<dsClickable*> dsClickable::items;


dsClickable *dsClickable::getItem(s16 x, s16 y, DS_SCREEN iscreen) {
  dsClickable *c = items.getLastItem();
  while (c) {
    if (c->hitTest(x, y, iscreen)) return c;
    c = items.getPrevItem(c);
  }
  return NULL;
}


//////////////////////////////////////////////////////////////////////////////////


dsClickRect::dsClickRect(s16 ix1, s16 iy1, s16 ix2, s16 iy2, DS_SCREEN iscreen) {
  x1 = ix1;
  y1 = iy1;
  x2 = ix2;
  y2 = iy2;
  screen = iscreen;
}


dsClickRect::~dsClickRect() {
}


bool dsClickRect::hitTest(s16 x, s16 y, DS_SCREEN iscreen) {
  if (screen & 0x80) return false;
  if (x < x1) return false;
  if (x > x2) return false;
  if (y < y1) return false;
  if (y > y2) return false;
  return (screen & iscreen & 0x03) > 0;
}


void dsClickRect::setBox(s16 ix1, s16 iy1, s16 ix2, s16 iy2) {
  x1 = ix1;
  y1 = iy1;
  x2 = ix2;
  y2 = iy2;
}

void dsClickRect::setRect(s16 ix, s16 iy, s16 iw, s16 ih) {
  x1 = ix;
  y1 = iy;
  x2 = ix + iw;
  y2 = iy + ih;
}
