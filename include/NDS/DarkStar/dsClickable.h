/*****************************  DARKSTAR  ******************************\
*  Copyright (c) 2005 Vincent E. Milum Jr., All rights reserved.        *
*                                                                       *
*  See License.txt for more information                                 *
*                                                                       *
*  Latest source versions can be found at:  HTTP://WWW.DARKAIN.COM/     *
\***********************************************************************/


#ifndef _DS_CLICKABLE_H_
#define _DS_CLICKABLE_H_


//common includes
#include "vList.h"

//local includes
#include "dsEnums.h"


class dsClickable {
  public:
    dsClickable() { items.appendItem(this); }
    virtual ~dsClickable() { items.removeItem(this); }

//  protected:
    virtual void onClick(s16 x, s16 y) {}
    virtual void onDrag(s16 x, s16 y) {}
    virtual void onDrop(s16 x, s16 y) {}

    virtual bool hitTest(s16 x, s16 y, DS_SCREEN iscreen=DS_SCREEN_MAIN)=0;

  public:  //some statics, to aquire a clickable item
    static dsClickable *getItem(s16 x, s16 y, DS_SCREEN iscreen=DS_SCREEN_MAIN);
    inline static dsClickable *getFirst() { return items.getFirstItem(); }
    inline static dsClickable *getNext(dsClickable *itm) { return items.getNextItem(itm); }
    inline static bool hasItem(dsClickable *item) { return items.itemExists(item); }

  private:
    static vList<dsClickable*> items;
};


class dsClickRect : public dsClickable {
  public:
    dsClickRect(s16 ix1, s16 iy1, s16 ix2, s16 iy2, DS_SCREEN iscreen=DS_SCREEN_MAIN);
    virtual ~dsClickRect();

    virtual bool hitTest(s16 x, s16 y, DS_SCREEN iscreen=DS_SCREEN_MAIN);

    void setDisabled(u8 disabled);
    bool getDisabled() { return screen && 0x80; }

    void setBox(s16 ix1, s16 iy1, s16 ix2, s16 iy2);
    void setRect(s16 ix, s16 iy, s16 iw, s16 ih);

    inline s16 getX1() const { return x1; }
    inline s16 getY1() const { return y1; }
    inline s16 getX2() const { return x2; }
    inline s16 getY2() const { return y2; }
    inline s16 getWidth()  const { return x2-x1; }
    inline s16 getHeight() const { return y2-y1; }
    
    inline DS_SCREEN getClickScreen() const { return screen; }
    inline void setClickScreen(DS_SCREEN dsscreen) { screen = dsscreen; }

  protected:
    s16 x1, y1, x2, y2;
    DS_SCREEN screen;
};


#endif //_DS_CLICKABLE_H_
