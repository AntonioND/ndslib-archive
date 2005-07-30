/*****************************  DARKSTAR  ******************************\
*  Copyright (c) 2005 Vincent E. Milum Jr., All rights reserved.        *
*                                                                       *
*  See License.txt for more information                                 *
*                                                                       *
*  Latest source versions can be found at:  HTTP://WWW.DARKAIN.COM/     *
\***********************************************************************/


#ifndef _DS_PAINT_LINE_TOOL_H_
#define _DS_PAINT_LINE_TOOL_H_


#include "dsPaintTool.h"


class dsPaintLineTool : public dsPaintTool {
  public:
    dsPaintLineTool(dsPaint *dspaint, u8 ibtnx, u8 ibtny);
    virtual ~dsPaintLineTool();

    virtual void onSelectTool();
    virtual void onDeselectTool();

    virtual void paintDrag(s16 x, s16 y, s16 ox, s16 oy);

  private:
    dsToggleBox *aa;
};


#endif //_DS_PAINT_LINE_TOOL_H_
