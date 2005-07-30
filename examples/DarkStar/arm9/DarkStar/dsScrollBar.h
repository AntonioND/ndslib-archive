/*****************************  DARKSTAR  ******************************\
*  Copyright (c) 2005 Vincent E. Milum Jr., All rights reserved.        *
*                                                                       *
*  See License.txt for more information                                 *
*                                                                       *
*  Latest source versions can be found at:  HTTP://WWW.DARKAIN.COM/     *
\***********************************************************************/


#ifndef _DS_SCROLL_BAR_H_
#define _DS_SCROLL_BAR_H_


#include <NDS/DarkStar/dsClickable.h>


class dsScrollBarHorz : public dsClickRect {
  public:
    dsScrollBarHorz();
    virtual ~dsScrollBarHorz();

  public:
    virtual void onScrollHorz() {}

    //function inherited from dsClickable
    virtual void onClick(s16 x, s16 y);
    virtual void onDrag(s16 x, s16 y);
    virtual void onDrop(s16 x, s16 y);

    inline int getHorzPos() const { return horzpos; }
    void setHorzPos(int pos);

  private:
    int horzpos;
    u8 drag;
};


class dsScrollBarVert : public dsClickRect {
  public:
    dsScrollBarVert();
    virtual ~dsScrollBarVert();

  public:
    virtual void onScrollVert() {}

    //function inherited from dsClickable
    virtual void onClick(s16 x, s16 y);
    virtual void onDrag(s16 x, s16 y);
    virtual void onDrop(s16 x, s16 y);

    inline int getVertPos() const { return vertpos; }
    void setVertPos(int pos);

  private:
    int vertpos;
    u8 drag;
};


class dsScrollBarBoth : public dsClickRect {
  public:
    dsScrollBarBoth();
    virtual ~dsScrollBarBoth();

  public:
    virtual void onScrollHorz() {}
    virtual void onScrollVert() {}

    //function inherited from dsClickable
    virtual void onClick(s16 x, s16 y);
    virtual void onDrag(s16 x, s16 y);
    virtual void onDrop(s16 x, s16 y);

    //use custom hit detection, since it isnt a single rectagle
    virtual bool hitTest(s16 x, s16 y, DS_SCREEN iscreen=DS_SCREEN_MAIN);

    inline int getHorzPos() const { return horzpos; }
    inline int getVertPos() const { return vertpos; }
    void setHorzPos(int pos);
    void setVertPos(int pos);

  private:
    int horzpos, vertpos;
    u8 drag;
};


#endif //_DS_SCROLL_BAR_H_
