/*****************************  DARKSTAR  ******************************\
*  Copyright (c) 2005 Vincent E. Milum Jr., All rights reserved.        *
*                                                                       *
*  See License.txt for more information                                 *
*                                                                       *
*  Latest source versions can be found at:  HTTP://WWW.DARKAIN.COM/     *
\***********************************************************************/


//lib includes
#include <NDS/NDS.h>

//common inludes
#include "../common.h"

//DarkStar includes
#include "../DarkStar/dsMainMenu.h"

//local includes
#include "dsPaint.h"
#include "dsPaintTool.h"



dsPaintTool *dsPaintTool::sel = 0;
vList<dsPaintTool*> dsPaintTool::tools;



dsPaintTool::dsPaintTool(dsPaint *dspaint, u8 ibtnx, u8 ibtny, const void *sprData)
 : dsClickRect(ibtnx<<3, ibtny<<3, (ibtnx<<3)+16, (ibtny<<3)+16, DS_SCREEN_SUB),
   dsSpriteSingle(DS_CORE_SUB, sprData, SIZE_16_X_16, false, 2) {

  move(ibtnx<<3, ibtny<<3);
  btnx = ibtnx;
  btny = ibtny;
  paint = dspaint;
  drawButton();
  tools.appendItem(this);
}


dsPaintTool::~dsPaintTool() {
  eraseButton();
  tools.removeItem(this);
}


void dsPaintTool::clearTools() {
  dsPaintTool *tool = tools.getFirstItem();
  while (tool) {
    delete tool;
    tools.removeItem(tool);
    tool = tools.getFirstItem();
  }
  sel = 0;
}


void dsPaintTool::selectTool() {
  dsPaintTool *tmp = sel;
  sel = this;
  
  if (tmp) {
    tmp->drawButton();
    tmp->onDeselectTool();
  }

  drawButton();
  onSelectTool();
}


void dsPaintTool::drawButton() {
  if (this == sel) {
    BG_GFX_SUB[0x800 + ((btny+0)*32)+(btnx-1)] = 0x0019;
    BG_GFX_SUB[0x800 + ((btny+1)*32)+(btnx-1)] = 0x0C19;
    BG_GFX_SUB[0x800 + ((btny+0)*32)+(btnx+0)] = 0x0C07;
    BG_GFX_SUB[0x800 + ((btny+1)*32)+(btnx+0)] = 0x0C06;
    BG_GFX_SUB[0x800 + ((btny+0)*32)+(btnx+1)] = 0x0C08;
    BG_GFX_SUB[0x800 + ((btny+1)*32)+(btnx+1)] = 0x0C09;
  } else {
    BG_GFX_SUB[0x800 + ((btny+0)*32)+(btnx-1)] = 0x000D;
    BG_GFX_SUB[0x800 + ((btny+1)*32)+(btnx-1)] = 0x000D;
    BG_GFX_SUB[0x800 + ((btny+0)*32)+(btnx+0)] = 0x0009;
    BG_GFX_SUB[0x800 + ((btny+1)*32)+(btnx+0)] = 0x0008;
    BG_GFX_SUB[0x800 + ((btny+0)*32)+(btnx+1)] = 0x0006;
    BG_GFX_SUB[0x800 + ((btny+1)*32)+(btnx+1)] = 0x0007;
  }
}


void dsPaintTool::eraseButton() {
  BG_GFX_SUB[0x800 + ((btny+0)*32)+(btnx+0)] = 0;
  BG_GFX_SUB[0x800 + ((btny+0)*32)+(btnx+1)] = 0;
  BG_GFX_SUB[0x800 + ((btny+1)*32)+(btnx+0)] = 0;
  BG_GFX_SUB[0x800 + ((btny+1)*32)+(btnx+1)] = 0;
}
