/*****************************  DARKSTAR  ******************************\
*  Copyright (c) 2005 Vincent E. Milum Jr., All rights reserved.        *
*                                                                       *
*  See License.txt for more information                                 *
*                                                                       *
*  Latest source versions can be found at:  HTTP://WWW.DARKAIN.COM/     *
\***********************************************************************/


//libs
#include <NDS/NDS.h>
#include <stdio.h>

//common includes
#include "../common.h"
#include <NDS/DarkStar/huffman.h>

//DarkStar includes
#include "../DarkStar/dsMainMenu.h"

//local headers
#include "dsPaint.h"
#include "dsPaintColor.h"
#include "dsPaintSlider.h"
#include "dsPaintUndo.h"
#include "dsPaintClear.h"

//paint tools
#include "dsPaintBoxTool.h"
#include "dsPaintCircleTool.h"
#include "dsPaintDrawTool.h"
#include "dsPaintDropperTool.h"
#include "dsPaintFillTool.h"
#include "dsPaintLineTool.h"

//resources
#include "menu_raw.h"
#include "menu_pal.h"
#include "buttons_pal.h"


static dsAppTemplate<dsPaint> dsPaintApp;


#define LOCALBUFFER


void sramRead(void *data, u32 offset, u32 len) {
  u8 *idata = (u8*)data;
  u8 *sram = SRAM+offset;
  while (len > 0) {
    *idata = *sram;
    idata++;
    sram++;
    len--;
  }
}

void sramWrite(const void *data, u32 offset, u32 len) {
  const u8 *idata = (u8*)data;
  u8 *sram = SRAM+offset;
  while (len > 0) {
    *sram = *idata ;
    idata++;
    sram++;
    len--;
  }
}


#ifdef LOCALBUFFER
dsPaint::dsPaint() : dsGfx(buffer[0], buffer[1], 256, 176), dsClickRect(0, 16, 255, 191, DS_SCREEN_MAIN) {
#else
dsPaint::dsPaint() : dsGfx(&BG_GFX[0x5000], buffer[0], 256, 176), dsClickRect(0, 16, 255, 191, DS_SCREEN_MAIN) {
#endif

  size = 2;

  colors.appendItem(new dsPaintColor(this, 13,  4, RGB(10, 0, 0), 0x81, 166));
  colors.appendItem(new dsPaintColor(this, 13,  6, RGB( 0,10, 0), 0x82, 167));
  colors.appendItem(new dsPaintColor(this, 13,  8, RGB( 0, 0,10), 0x83, 168));
  colors.appendItem(new dsPaintColor(this, 13, 10, RGB( 0,10,10), 0x84, 169));
  colors.appendItem(new dsPaintColor(this, 13, 12, RGB(10, 0,10), 0x85, 170));
  colors.appendItem(new dsPaintColor(this, 13, 14, RGB(10,10, 0), 0x86, 171));

  colors.appendItem(new dsPaintColor(this, 15,  4, RGB(21, 0, 0), 0x87, 172));
  colors.appendItem(new dsPaintColor(this, 15,  6, RGB( 0,21, 0), 0x88, 173));
  colors.appendItem(new dsPaintColor(this, 15,  8, RGB( 0, 0,21), 0x89, 174));
  colors.appendItem(new dsPaintColor(this, 15, 10, RGB( 0,21,21), 0x8A, 175));
  colors.appendItem(new dsPaintColor(this, 15, 12, RGB(21, 0,21), 0x8B, 176));
  colors.appendItem(new dsPaintColor(this, 15, 14, RGB(21,21, 0), 0x8C, 177));

  colors.appendItem(new dsPaintColor(this, 17,  4, RGB(31, 0, 0), 0x91, 178));
  colors.appendItem(new dsPaintColor(this, 17,  6, RGB( 0,31, 0), 0x92, 179));
  colors.appendItem(new dsPaintColor(this, 17,  8, RGB( 0, 0,31), 0x93, 180));
  colors.appendItem(new dsPaintColor(this, 17, 10, RGB( 0,31,31), 0x94, 181));
  colors.appendItem(new dsPaintColor(this, 17, 12, RGB(31, 0,31), 0x95, 182));
  colors.appendItem(new dsPaintColor(this, 17, 14, RGB(31,31, 0), 0x96, 183));

  colors.appendItem(new dsPaintColor(this, 19,  4, RGB(31,15,15), 0xA7, 196));
  colors.appendItem(new dsPaintColor(this, 19,  6, RGB(15,31,15), 0xA8, 197));
  colors.appendItem(new dsPaintColor(this, 19,  8, RGB(15,15,31), 0xA9, 198));
  colors.appendItem(new dsPaintColor(this, 19, 10, RGB(15,31,31), 0xAA, 199));
  colors.appendItem(new dsPaintColor(this, 19, 12, RGB(31,15,31), 0xAB, 200));
  colors.appendItem(new dsPaintColor(this, 19, 14, RGB(31,31,15), 0xAC, 201));

  colors.appendItem(new dsPaintColor(this, 21,  4, RGB(21,10,10), 0xA1, 190));
  colors.appendItem(new dsPaintColor(this, 21,  6, RGB(10,21,10), 0xA2, 191));
  colors.appendItem(new dsPaintColor(this, 21,  8, RGB(10,10,21), 0xA3, 192));
  colors.appendItem(new dsPaintColor(this, 21, 10, RGB(10,21,21), 0xA4, 193));
  colors.appendItem(new dsPaintColor(this, 21, 12, RGB(21,10,21), 0xA5, 194));
  colors.appendItem(new dsPaintColor(this, 21, 14, RGB(21,21,10), 0xA6, 195));

  colors.appendItem(new dsPaintColor(this, 23,  4, RGB(15, 6, 6), 0x97, 184));
  colors.appendItem(new dsPaintColor(this, 23,  6, RGB( 6,15, 6), 0x98, 185));
  colors.appendItem(new dsPaintColor(this, 23,  8, RGB( 6, 6,15), 0x99, 186));
  colors.appendItem(new dsPaintColor(this, 23, 10, RGB( 6,15,15), 0x9A, 187));
  colors.appendItem(new dsPaintColor(this, 23, 12, RGB(15, 6,15), 0x9B, 188));
  colors.appendItem(new dsPaintColor(this, 23, 14, RGB(15,15, 6), 0x9C, 189));

  colors.appendItem(new dsPaintColor(this, 13, 16, RGB( 0, 0, 0), 0xB1, 202));
  colors.appendItem(new dsPaintColor(this, 15, 16, RGB( 6, 6, 6), 0xB2, 203));
  colors.appendItem(new dsPaintColor(this, 17, 16, RGB(12,12,12), 0xB3, 204));
  colors.appendItem(new dsPaintColor(this, 19, 16, RGB(19,19,19), 0xB4, 205));
  colors.appendItem(new dsPaintColor(this, 21, 16, RGB(25,25,25), 0xB5, 206));
  colors.appendItem(new dsPaintColor(this, 23, 16, RGB(31,31,31), 0xB6, 207));

  dmaCopyWords(3, (uint32*)buttons_pal, (uint32*)&PALETTE[768+32], 64);

  drawText("R  G  B  A", mainmenu->getBuffer(DS_SCREEN_SUB)+0x800, 1, 3);
  red   = new dsPaintSlider(this,  8, 40);
  green = new dsPaintSlider(this, 32, 40);
  blue  = new dsPaintSlider(this, 56, 40);
  alph  = new dsPaintSlider(this, 80, 40);

  
  for (int i=0; i<18; i++) {
    BG_GFX_SUB[0x800 + ((4+i)*32)+1]  = 0x0003;
    BG_GFX_SUB[0x800 + ((4+i)*32)+2]  = 0x0005;

    BG_GFX_SUB[0x800 + ((4+i)*32)+4]  = 0x0003;
    BG_GFX_SUB[0x800 + ((4+i)*32)+5]  = 0x0005;

    BG_GFX_SUB[0x800 + ((4+i)*32)+7]  = 0x0003;
    BG_GFX_SUB[0x800 + ((4+i)*32)+8]  = 0x0005;

    BG_GFX_SUB[0x800 + ((4+i)*32)+10] = 0x0003;
    BG_GFX_SUB[0x800 + ((4+i)*32)+11] = 0x0005;

    BG_GFX_SUB[0x800 + ((3+i)*32)+25] = 0x0C0D;
    BG_GFX_SUB[0x800 + ((3+i)*32)+28] = 0x000D;
  }

  for (int i=0; i<8; i++) {
    BG_GFX_SUB[0x800 + (20*32)+13+i] = 0x3001;
    BG_GFX_SUB[0x800 + (21*32)+13+i] = 0x3001;
  }

  BG_GFX_SUB[0x800 + ( 2*32)+26] = 0x0C19;
  BG_GFX_SUB[0x800 + ( 2*32)+27] = 0x0C19;
  BG_GFX_SUB[0x800 + (21*32)+26] = 0x0019;
  BG_GFX_SUB[0x800 + (21*32)+27] = 0x0019;

  (new dsPaintDrawTool(     this, 29,  3))->selectTool();
  new dsPaintLineTool(      this, 29,  6);
  new dsPaintBoxTool(       this, 29,  9);
  new dsPaintCircleTool(    this, 29, 12);
  new dsPaintFloodTool(     this, 29, 15);
  new dsPaintDropperTool(   this, 29, 18);

  undo  = new dsPaintUndo(this);
  clear = new dsPaintClear(this);
  
  updateColor();

  eraseA();
  eraseB();


  //decode huffman data
  if (memcmp(SRAM, "DSPAINT", 8) == 0) { 
    u32 inlen = 0;
    sramRead(&inlen, 8, 4);
    u8 *input = (u8*)malloc(inlen);
    sramRead(input, 12, inlen);
    DC_FlushAll();

    u32 outlen=0;
    u8 *output=0;

    huffman_decode_memory(input, inlen, &output, &outlen);
    memcpy(buffer[0], output, outlen);

    free(input);
    free(output);
    DC_FlushAll();
  }

#ifdef LOCALBUFFER
  dmaCopyHalfWords(3, buffer[0], &BG_GFX[0x5000], 256*176*2);
#endif
}


dsPaint::~dsPaint() {

  //encode huffman data
  if (memcmp((void*)0x080000AC, "PASS", 4) == 0) {
    DC_FlushAll();
#ifdef LOCALBUFFER
    dmaCopyHalfWords(3, &BG_GFX[0x5000], buffer[0], 256*176*2);
#endif

    u32 outlen=0;
    u8 *output=0;

    huffman_encode_memory( (u8*)buffer[0], 256*176*2, &output, &outlen );

    sramWrite("DSPAINT", 0, 8);
    sramWrite(&outlen, 8, 4);
    sramWrite(output, 12, outlen);

    free(output);
  }

  for (int i=0; i<32*24; i++) {
    BG_GFX_SUB[0x800 + i]  = 0;
  }

  delete red;
  delete green;
  delete blue;
  delete alph;

  delete clear;
  delete undo;

  dsPaintColor *c = colors.getFirstItem();
  while (c) {
    delete c;
    colors.removeItem(c);
    c = colors.getFirstItem();
  }

  dsPaintTool::clearTools();

  mainmenu->restoreBackground(DS_SCREEN_MAIN);
}



void dsPaint::flipH() {  //mirror
  DC_FlushAll();
  dmaCopyHalfWords(3, getScreenBuffer(), getBufferB(), getGfxByteSize());

  u16 *src = getBufferB() + getGfxWidth() - 1;
  u16 *dst = getScreenBuffer();

  for (int i=0; i<getGfxHeight(); i++) {
	  DMA_SRC(3)  = (uint32)src;
	  DMA_DEST(3) = (uint32)dst;
	  DMA_CR(3)   = DMA_COPY_HALFWORDS | DMA_SRC_DEC | (getGfxWidth());
	  while(DMA_CR(3) & DMA_BUSY);

    src += getGfxWidth();
    dst += getGfxWidth();
  }

  dmaCopyHalfWords(3, getScreenBuffer(), getBufferA(), getGfxByteSize());
}


void dsPaint::flipV() {  //upside-down
  DC_FlushAll();
  dmaCopyHalfWords(3, getScreenBuffer(), getBufferB(), getGfxByteSize());

  u16 *src = getBufferB() + getGfxSize() - getGfxWidth();
  u16 *dst = getScreenBuffer();

  for (int i=0; i<getGfxHeight(); i++) {
    dmaCopyHalfWords(3, src, dst, getGfxWidth()*2);
    src -= getGfxWidth();
    dst += getGfxWidth();
  }

  dmaCopyHalfWords(3, getScreenBuffer(), getBufferA(), getGfxByteSize());
}



void dsPaint::setColor(u16 color) {
  clr = color | 0x8000;
  PALETTE[567] = clr;
  red->setValue(RGBRED(color));
  green->setValue(RGBGREEN(color));
  blue->setValue(RGBBLUE(color));

  char str[16];
  sprintf(str, "%02d %02d %02d %02d", red->getValue(), green->getValue(), blue->getValue(), alph->getValue());
  drawText(str, mainmenu->getBuffer(DS_SCREEN_SUB)+0x800, 1, 22);
}


void dsPaint::updateColor() {
  clr = RGB( red->getValue(), green->getValue(), blue->getValue() ) | 0x8000;
  PALETTE[567] = clr;

  char str[16];
  sprintf(str, "%02d %02d %02d %02d", red->getValue(), green->getValue(), blue->getValue(), alph->getValue());
  drawText(str, mainmenu->getBuffer(DS_SCREEN_SUB)+0x800, 1, 22);
}


u8 dsPaint::getAlpha() const {
  return alph->getValue();
}


u16 *dsPaint::getScreenBuffer() {
#ifdef LOCALBUFFER
  return &BG_GFX[0x5000];
#else
  return getBufferA();
#endif
}


void dsPaint::onClick(s16 x, s16 y) {
  ox = x;
  oy = y-16;

  dsPaintTool *tool = dsPaintTool::getSelected();
  if (tool) {
    DC_FlushAll();
    dmaCopyHalfWords(3, &buffer[0], buffer[1], 256*176*2);

    tool->paintStart(ox, oy);
#ifdef LOCALBUFFER
    DC_FlushAll();
    dmaCopyHalfWords(3, buffer[0], &BG_GFX[0x5000], 256*176*2);
#endif
  }
}

  
void dsPaint::onDrag(s16 x, s16 y) {
  x = max(min(x, 255), 0);
  y = max(min(y, 191), 16);
  y -= 16;

  dsPaintTool *tool = dsPaintTool::getSelected();
  if (tool) {
    tool->paintDrag(x, y, ox, oy);
#ifdef LOCALBUFFER
    DC_FlushAll();
    dmaCopyHalfWords(3, buffer[0], &BG_GFX[0x5000], 256*176*2);
#endif
  }
}


void dsPaint::onDrop(s16 x, s16 y) {
  x = max(min(x, 255), 0);
  y = max(min(y, 191), 16);
  y -= 16;

  dsPaintTool *tool = dsPaintTool::getSelected();
  if (tool) {
    tool->paintStop(x, y, ox, oy);
#ifdef LOCALBUFFER
    DC_FlushAll();
    dmaCopyHalfWords(3, buffer[0], &BG_GFX[0x5000], 256*176*2);
#endif
  }
}


void dsPaint::onKeyChange(u32 inputState, u32 lastState) {
  if ( (lastState & KEY_UP) && (!(inputState & KEY_UP)) ) {
    size++;
    size = min(size, 3);
  }
  if ( (lastState & KEY_DOWN) && (!(inputState & KEY_DOWN)) ) {
    size--;
    size = max(size, 1);
  }

  if ( (lastState & KEY_L) && (!(inputState & KEY_L)) ) {
    flipH();
  }
  if ( (lastState & KEY_R) && (!(inputState & KEY_R)) ) {
    flipV();
  }
}

