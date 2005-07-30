/*****************************  DARKSTAR  ******************************\
*  Copyright (c) 2005 Vincent E. Milum Jr., All rights reserved.        *
*                                                                       *
*  See License.txt for more information                                 *
*                                                                       *
*  Latest source versions can be found at:  HTTP://WWW.DARKAIN.COM/     *
\***********************************************************************/


#ifndef _DS_PAINT_DRAW_TOOL_H_
#define _DS_PAINT_DRAW_TOOL_H_


#include "dsPaintTool.h"


class dsPaintDrawTool : public dsPaintTool {
  public:
    dsPaintDrawTool(dsPaint *dspaint, u8 ibtnx, u8 ibtny);
    virtual ~dsPaintDrawTool();

    virtual void onSelectTool();
    virtual void onDeselectTool();

    virtual void paintStart(s16 x, s16 y) { px=x; py=y; }
    virtual void paintDrag(s16 x, s16 y, s16 ox, s16 oy);

  private:
    s16 px, py;
    dsToggleBox *aa;
};


#endif //_DS_PAINT_DRAW_TOOL_H_
