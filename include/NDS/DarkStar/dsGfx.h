/*****************************  DARKSTAR  ******************************\
*  Copyright (c) 2005 Vincent E. Milum Jr., All rights reserved.        *
*                                                                       *
*  See License.txt for more information                                 *
*                                                                       *
*  Latest source versions can be found at:  HTTP://WWW.DARKAIN.COM/     *
\***********************************************************************/


#ifndef _DS_GFX_H_
#define _DS_GFX_H_


/*
supported templates are dsGfx<u16> and dsGfx<u8>

NOTE: most functions do NOT support 8bit read/writes yet
*/


/*
this is a basic graphics library...
it is a horrible fawking mess.  it is a quick throw-together
job os several other basic graphics libraries all into one
*/


#define RGB(r,g,b)  ((r)+((g)<<5)+((b)<<10))
#define BGR(b,g,r)  ((r)+((g)<<5)+((b)<<10))
#define RGB16(r,g,b)  ((r)+((g)<<5)+((b)<<10)+0x8000)
#define BGR16(b,g,r)  ((r)+((g)<<5)+((b)<<10)+0x8000)

#define REDMASK   (0x7C00)
#define GREENMASK (0x03E0)
#define BLUEMASK  (0x001F)
#define ALPHAMASK (0x8000)
#define EXTENDEDMASK (0xF8000)

#define RGBRED(c)   (((c)>> 0) & 0x001F)
#define RGBGREEN(c) (((c)>> 5) & 0x001F)
#define RGBBLUE(c)  (((c)>>10) & 0x001F)

#define WHITE RGB(31,31,31)
#define BLACK RGB(0,0,0)


#include "vTypes.h"
//#include "../common/common.h"


class dsGfx {
  public:
    dsGfx(u16 *frontBuffer=VRAM_A, u16* backBuffer=VRAM_B, u16 bfWidth=256, u16 bfHeight=192);

  public:
    inline u16 getGfxWidth()  const { return width;  }
    inline u16 getGfxHeight() const { return height; }
    inline u32 getGfxSize()   const { return width*height; }
    inline u32 getGfxByteSize()   const { return getGfxSize()*sizeof(u16); }

    void flip();

    void fillBufferA(u16 color);
    void fillBufferB(u16 color);
    inline void eraseA() { fillBufferA(RGB(0,0,0) | 0x8000); }
    inline void eraseB() { fillBufferB(RGB(0,0,0) | 0x8000); }
    inline void erase()  { eraseA(); }

    void line(s16 x1, s16 y1, s16 x2, s16 y2, u16 color, u8 size=1);
    void lineaa(s16 x1, s16 y1, s16 x2, s16 y2, u16 color, u8 size=1);
    void lineblend(s16 x1, s16 y1, s16 x2, s16 y2, u16 color, u8 blend, u8 size=1);

    void box(u8 x1, u8 y1, u8 x2, u8 y2, u16 color, u8 size=1);
    void box(u8 x1, u8 y1, u8 x2, u8 y2, u16 color, u8 blend, u8 size=1);
    void boxfill(u8 x1, u8 y1, u8 x2, u8 y2, u16 color);
    void boxfill(u8 x1, u8 y1, u8 x2, u8 y2, u16 color, u8 blend);
    
    void floodfill(u16 x, u16 y, u16 color);

    void circle(s16 cx, s16 cy, s16 radius, u16 color);
    void circleaa(s16 cx, s16 cy, s16 radius, u16 color);
    void circlefill(s16 cx, s16 cy, s16 radius, u16 color);
    void circlefill(s16 cx, s16 cy, s16 radius, u16 color, u8 blend);
    void circlefillaa(s16 cx, s16 cy, s16 radius, u16 color);
    void circle(s16 cx, s16 cy, s16 radius, u16 color, u8 blend);
    void disc(s16 cx, s16 cy, s16 radius, u16 color);

    inline void setPixelA(s16 x, s16 y, u16 color) { if (x>=0 && x<width && y>=0 && y<height) screen[(y*width)+x] = color; }
    inline void setPixelB(s16 x, s16 y, u16 color) { if (x>=0 && x<width && y>=0 && y<height) back[(y*width)+x] = color; }
    inline void drawPixelA(u8 x, u8 y, u16 color) { screen[(y*width)+x] = color; }
    inline void drawPixelB(u8 x, u8 y, u16 color) { back[(y*width)+x] = color; }
    inline void pixel(u8 x, u8 y, u16 color=RGB16(31,31,31)) { drawPixelA(x, y, color); }
    inline void setPixel(u8 x, u8 y, u16 color=RGB16(31,31,31)) { drawPixelA(x, y, color); }
    inline u16 getPixel(u8 x, u8 y) { return screen[(y*width)+x]; }
    inline u16 *getPixelPtr(u8 x, u8 y) { return &screen[(y*width)+x]; }

    void copyAtoB();
    void copyBtoA();
    void copyAtoB(u8 x1, u8 y1, u8 x2, u8 y2);
    void copyBtoA(u8 x1, u8 y1, u8 x2, u8 y2);

    void copyHLineAtoB(u8 x, u8 y, u8 len, u8 size=1);
    void copyHLineBtoA(u8 x, u8 y, u8 len, u8 size=1);
    void copyVLineAtoB(u8 x, u8 y, u8 len, u8 size=1);
    void copyVLineBtoA(u8 x, u8 y, u8 len, u8 size=1);

    void copyBoxAtoB(u8 x1, u8 y1, u8 x2, u8 y2, u8 size=1);
    void copyBoxBtoA(u8 x1, u8 y1, u8 x2, u8 y2, u8 size=1);
    //use copyAtoB and copyBtoA for copyBoxFillAtoB and copyBoxFillBtoA

    inline u16 *getBufferA() { return screen; }
    inline u16 *getBufferB() { return back; }


    void Mandelbrot(double lx=-2, double ux=0.6, double ly=-1.2, double uy=1.2, double d=0.02);



  private:
    inline void dma3(void *dest, u16 words);


  public:
    static inline u16 mixColors(u16 c1, u16 c2) { return ((c1>>1)&0x3DEF) + ((c2>>1)&0x3DEF) | 0x8000; }

    static inline u16 alphaBlend(u16 c1, u16 c2, u8 trans) {
      if (c1 == c2) return c1;
      trans &= 0x1F;
      switch(trans) {
        case  0: return c1;
        case  7: return mixColors(c1, mixColors(c1, c2));
        case 15: return mixColors(c1, c2);
        case 23: return mixColors(c2, mixColors(c2, c1));
        case 31: return c2;
      }
      register u8 trans2 = 31-trans;
      return (u16)0x8000 |
        (u32)(((((c2&BLUEMASK) *trans)+((c1&BLUEMASK) *trans2))&GREENMASK)
            | ((((c2&GREENMASK)*trans)+((c1&GREENMASK)*trans2))&REDMASK)
            | ((((c2&REDMASK)  *trans)+((c1&REDMASK)  *trans2))&EXTENDEDMASK)) >> 5;
    }

    inline void blendPixel(u8 x, u8 y, u16 color, u8 trans=31) { setPixel(x,y, alphaBlend(getPixel(x,y), color, trans)); }

    static inline u16 grey(int intensity) { return RGB(intensity, intensity, intensity); }


  protected:
    u16 *screen;
    u16 *back;

    u16 width;
    u16 height;

    //used with DMA colour filling
    u16 colourdata;
};


#endif //_DS_GFX_H_
