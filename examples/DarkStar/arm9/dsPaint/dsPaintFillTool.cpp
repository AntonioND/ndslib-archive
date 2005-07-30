/*****************************  DARKSTAR  ******************************\
*  Copyright (c) 2005 Vincent E. Milum Jr., All rights reserved.        *
*                                                                       *
*  See License.txt for more information                                 *
*                                                                       *
*  Latest source versions can be found at:  HTTP://WWW.DARKAIN.COM/     *
\***********************************************************************/


//libs
#include <NDS/NDS.h>

//local includes
#include "dsPaint.h"
#include "dsPaintFillTool.h"


dsPaintFloodTool::dsPaintFloodTool(dsPaint *dspaint, u8 ibtnx, u8 ibtny)
 : dsPaintTool(dspaint, ibtnx, ibtny, &buttons_raw[0x380]) {
}


dsPaintFloodTool::~dsPaintFloodTool() {
}


void dsPaintFloodTool::paintStart(s16 x, s16 y) {
  paint->floodfill(x, y, paint->getColor());
}
