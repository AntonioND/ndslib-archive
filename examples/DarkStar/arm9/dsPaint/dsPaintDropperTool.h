/*****************************  DARKSTAR  ******************************\
*  Copyright (c) 2005 Vincent E. Milum Jr., All rights reserved.        *
*                                                                       *
*  See License.txt for more information                                 *
*                                                                       *
*  Latest source versions can be found at:  HTTP://WWW.DARKAIN.COM/     *
\***********************************************************************/


#ifndef _DS_PAINT_DROPPER_TOOL_H_
#define _DS_PAINT_DROPPER_TOOL_H_


#include "dsPaintTool.h"


class dsPaintDropperTool : public dsPaintTool {
  public:
    dsPaintDropperTool(dsPaint *dspaint, u8 ibtnx, u8 ibtny);
    virtual ~dsPaintDropperTool();

    virtual void paintStart(s16 x, s16 y);
    virtual void paintDrag(s16 x, s16 y, s16 ox, s16 oy);
};


#endif //_DS_PAINT_DROPPER_TOOL_H_
