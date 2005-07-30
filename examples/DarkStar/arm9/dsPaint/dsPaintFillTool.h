/*****************************  DARKSTAR  ******************************\
*  Copyright (c) 2005 Vincent E. Milum Jr., All rights reserved.        *
*                                                                       *
*  See License.txt for more information                                 *
*                                                                       *
*  Latest source versions can be found at:  HTTP://WWW.DARKAIN.COM/     *
\***********************************************************************/


#ifndef _DS_PAINT_FILL_TOOL_H_
#define _DS_PAINT_FILL_TOOL_H_


#include "dsPaintTool.h"


class dsPaintFloodTool : public dsPaintTool {
  public:
    dsPaintFloodTool(dsPaint *dspaint, u8 ibtnx, u8 ibtny);
    virtual ~dsPaintFloodTool();

    virtual void paintStart(s16 x, s16 y);
};


#endif //_DS_PAINT_FILL_TOOL_H_
