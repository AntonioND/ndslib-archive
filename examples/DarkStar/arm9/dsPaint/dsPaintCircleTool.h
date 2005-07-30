/*****************************  DARKSTAR  ******************************\
*  Copyright (c) 2005 Vincent E. Milum Jr., All rights reserved.        *
*                                                                       *
*  See License.txt for more information                                 *
*                                                                       *
*  Latest source versions can be found at:  HTTP://WWW.DARKAIN.COM/     *
\***********************************************************************/


#ifndef _DS_PAINT_CIRCLE_TOOL_H_
#define _DS_PAINT_CIRCLE_TOOL_H_


#include "dsPaintTool.h"


class dsPaintCircleTool : public dsPaintTool {
  public:
    dsPaintCircleTool(dsPaint *dspaint, u8 ibtnx, u8 ibtny);
    virtual ~dsPaintCircleTool();

    virtual void onSelectTool();
    virtual void onDeselectTool();
    virtual void onSelectSubTool(u8 id);

//    virtual void paintStart(s16 x, s16 y);
    virtual void paintDrag(s16 x, s16 y, s16 ox, s16 oy);

  private:
    s32 ra;
    dsPaintSubTool *fill[3];
    u8 fillEnable;
};


#endif //_DS_PAINT_CIRCLE_TOOL_H_
