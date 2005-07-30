/*****************************  DARKSTAR  ******************************\
*  Copyright (c) 2005 Vincent E. Milum Jr., All rights reserved.        *
*                                                                       *
*  See License.txt for more information                                 *
*                                                                       *
*  Latest source versions can be found at:  HTTP://WWW.DARKAIN.COM/     *
\***********************************************************************/


#ifndef _DS_PAINT_TOOL_H_
#define _DS_PAINT_TOOL_H_


//common includes
#include <NDS/DarkStar/vList.h>

//DarkStar includes
#include "../DarkStar/dsBox.h"
#include <NDS/DarkStar/dsSprite.h>
#include <NDS/DarkStar/dsClickable.h>

//local includes
#include "dsPaintSubTool.h"

//resource includes
#include "buttons_raw.h"


class dsPaint;
class dsToggleBox;


class dsPaintTool : public dsClickRect, public dsSpriteSingle {
  friend class dsPaint;

  public:
    dsPaintTool(dsPaint *dspaint, u8 ibtnx, u8 ibtny, const void *sprData);
    virtual ~dsPaintTool();

  public:
    static dsPaintTool *getSelected() { return sel; }
    void selectTool();

    virtual void onSelectTool() {}
    virtual void onDeselectTool() {}
    virtual void onSelectSubTool(u8 id) {}

    void drawButton();
    void eraseButton();

    virtual void onClick(s16 x, s16 y) { selectTool(); }

    virtual void paintStart(s16 x, s16 y) {}
    virtual void paintDrag(s16 x, s16 y, s16 ox, s16 oy) {}
    virtual void paintStop(s16 x, s16 y, s16 ox, s16 oy) {}

  private:
    static void clearTools();
  
  protected:
    dsPaint *paint;
    u8 btnx, btny;

    static dsPaintTool *sel;
    static vList<dsPaintTool*> tools;
};


#endif //_DS_PAINT_TOOL_H_
