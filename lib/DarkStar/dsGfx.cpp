/*****************************  DARKSTAR  ******************************\
*  Copyright (c) 2005 Vincent E. Milum Jr., All rights reserved.        *
*                                                                       *
*  See License.txt for more information                                 *
*                                                                       *
*  Latest source versions can be found at:  HTTP://WWW.DARKAIN.COM/     *
\***********************************************************************/

/*
this is a basic graphics library...
it is a horrible fawking mess.  it is a quick throw-together
job os several other basic graphics libraries all into one
*/


#include <malloc.h>
#include <NDS/NDS.h>
#include <NDS/DarkStar/dsGfx.h>
//#include "../common/common.h"





dsGfx::dsGfx(u16 *frontBuffer, u16* backBuffer, u16 bfWidth, u16 bfHeight) {
  screen = frontBuffer;
  back   = backBuffer;
  width  = bfWidth;
  height = bfHeight;
}



void dsGfx::fillBufferA(u16 color) {
  colourdata = color;
  dma3(screen, width*height);
}



void dsGfx::fillBufferB(u16 color) {
  colourdata = color;
  dma3(back, width*height);
}



void dsGfx::flip() {
  /*
  if (screen == VRAM_A) {
    screen = VRAM_B;
    back   = VRAM_A;
	  videoSetMode(MODE_FB1);
  } else {
    screen = VRAM_A;
    back   = VRAM_B;
	  videoSetMode(MODE_FB0);
  }
  */
}



void dsGfx::box(u8 x1, u8 y1, u8 x2, u8 y2, u16 color, u8 size) {
  //horz
  line(x1, y1, x2, y1, color, size);
  line(x1, y2, x2, y2, color, size);

  //vert
  line(x1, y1, x1, y2, color, size);
  line(x2, y1, x2, y2, color, size);
}



void dsGfx::box(u8 x1, u8 y1, u8 x2, u8 y2, u16 color, u8 blend, u8 size) {
  //horz
  lineblend(x1, y1, x2, y1, color, blend, size);
  lineblend(x1, y2, x2, y2, color, blend, size);

  //vert
  lineblend(x1, y1, x1, y2, color, blend, size);
  lineblend(x2, y1, x2, y2, color, blend, size);
}



void dsGfx::boxfill(u8 x1, u8 y1, u8 x2, u8 y2, u16 color) {
  if (y2 < y1) {
    u8 t = y1;
    y1 = y2;
    y2 = t;
  }

  for (int i=y1; i<=y2; i++) {
    line(x1, i, x2, i, color);
  }
}



void dsGfx::boxfill(u8 x1, u8 y1, u8 x2, u8 y2, u16 color, u8 blend) {
  if (y2 < y1) {
    u8 t = y1;
    y1 = y2;
    y2 = t;
  }

  for (int i=y1; i<=y2; i++) {
    lineblend(x1, i, x2, i, color, blend);
  }
}



inline void dsGfx::dma3(void *dest, u16 words) {
  if (words == 0) return;

  DC_FlushAll();  //flush cache

  DMA3_SRC   = (u32) &colourdata;
  DMA3_DEST  = (u32) dest;
  DMA3_CR    = (DMA_COPY_HALFWORDS | DMA_SRC_FIX) | (words);
  while(DMA3_CR & DMA_BUSY);
}



void dsGfx::floodfill(u16 x, u16 y, u16 color) {
  register u16 srccolor = screen[(y*width)+x];
  if (srccolor == color) return;

  u32 *stack = (u32*)malloc(width*height);
  u32 stackSize = 0;
  stack[stackSize++] = x | (y<<16);

  while(true) {
    if (stackSize == 0) {
      free(stack);
      return;
    }

    u32 coordinates = stack[--stackSize]; 

    x = coordinates & 0xffff;
    y = coordinates >> 16;

    u16 *bgn = &screen[y*width];
    u16 *mid = bgn + x;
    u16 *end = bgn + width;
    u16 *top = bgn - width;
    u16 *bf = mid;

    if ( (*bf == srccolor) & (x < width) & (y < height) ) {

      while ((bf >= bgn) && (*bf == srccolor)) { *bf=color; bf--; }
      u16 x1 = (bf - bgn) + 1;

      bf = mid;
      *bf = srccolor;
      while ((bf < end) && (*bf == srccolor)) { *bf=color; bf++; }
      u16 x2 = (bf - bgn) - 1;

      if (y > 0) {
        bool inScanLine = false;
        for (int i=x1; i<=x2; i++) {
          register u16 clr = top[i];
          if (!inScanLine && clr==srccolor) {
            stack[stackSize++] = i | ((y-1)<<16);
            inScanLine = true;
          }
          else if (inScanLine && clr!=srccolor) {
            inScanLine = false;
          }
        }
      }

      if (y < height-1) {
        bool inScanLine = false;
        for (int i=x1; i<=x2; i++) {
          register u16 clr = end[i];
          if (!inScanLine && clr==srccolor) {
            stack[stackSize++] = i | ((y+1)<<16);
            inScanLine = true;
          }
          else if (inScanLine && clr!=srccolor) {
            inScanLine = false;
          }
        }
      }

    }
  }        
}


// http://www.gamedev.net/reference/articles/article1275.asp

void dsGfx::line(s16 x1, s16 y1, s16 x2, s16 y2, u16 color, u8 size) { 
  if (size == 0) return;

  s32 deltax = abs(x2 - x1);    // The difference between the x's
  s32 deltay = abs(y2 - y1);    // The difference between the y's
  s32 x = x1;                   // Start x off at the first pixel
  s32 y = y1;                   // Start y off at the first pixel

  s32 xinc1, xinc2, yinc1, yinc2;
  s32 den, num, numadd, numpixels;

  if (x2 >= x1) {               // The x-values are increasing
    xinc1 = 1;
    xinc2 = 1;
  } else {                      // The x-values are decreasing
    xinc1 = -1;
    xinc2 = -1;
  }

  if (y2 >= y1) {               // The y-values are increasing
    yinc1 = 1;
    yinc2 = 1;
  } else {                      // The y-values are decreasing
    yinc1 = -1;
    yinc2 = -1;
  }

  if (deltax >= deltay) {       // There is at least one x-value for every y-value
//    xinc1 = 0;                  // Don't change the x when numerator >= denominator
//    yinc2 = 0;                  // Don't change the y for every iteration
    den = deltax;
    num = deltax >> 1;
    numadd = deltay;
    numpixels = deltax;         // There are more x-values than y-values

    for (s32 curpixel = 0; curpixel <= numpixels; curpixel++) {
      setPixelA(x, y, color);     // Draw the current pixel
      if (size>1) setPixelA(x, y+1, color);
      if (size>2) setPixelA(x, y-1, color);

      num += numadd;              // Increase the numerator by the top of the fraction
      if (num >= den) {           // Check if numerator >= denominator
        num -= den;               // Calculate the new numerator value
//        x += xinc1;               // Change the x as appropriate
        y += yinc1;               // Change the y as appropriate
      }
      x += xinc2;                 // Change the x as appropriate
//      y += yinc2;                 // Change the y as appropriate
    }


  } else {                      // There is at least one y-value for every x-value
//    xinc2 = 0;                  // Don't change the x for every iteration
//    yinc1 = 0;                  // Don't change the y when numerator >= denominator
    den = deltay;
    num = deltay >> 1;
    numadd = deltax;
    numpixels = deltay;         // There are more y-values than x-values

    for (s32 curpixel = 0; curpixel <= numpixels; curpixel++) {
      setPixelA(x, y, color);     // Draw the current pixel
      if (size>1) setPixelA(x+1, y, color);
      if (size>2) setPixelA(x-1, y, color);

      num += numadd;              // Increase the numerator by the top of the fraction
      if (num >= den) {           // Check if numerator >= denominator
        num -= den;               // Calculate the new numerator value
        x += xinc1;               // Change the x as appropriate
//        y += yinc1;               // Change the y as appropriate
      }
//      x += xinc2;                 // Change the x as appropriate
      y += yinc2;                 // Change the y as appropriate
    }

  }
/*
  for (s32 curpixel = 0; curpixel <= numpixels; curpixel++) {
    setPixelA(x, y, color);     // Draw the current pixel
    num += numadd;              // Increase the numerator by the top of the fraction
    if (num >= den) {           // Check if numerator >= denominator
      num -= den;               // Calculate the new numerator value
      x += xinc1;               // Change the x as appropriate
      y += yinc1;               // Change the y as appropriate
    }
    x += xinc2;                 // Change the x as appropriate
    y += yinc2;                 // Change the y as appropriate
  }
*/
}





void dsGfx::lineaa(s16 x1, s16 y1, s16 x2, s16 y2, u16 color, u8 size) {
  if (size == 0) return;

  int dx, dy, xDir;
  if(y1>y2) {
    int tmp;
    tmp=y1; y1=y2; y2=tmp;
    tmp=x1; x1=x2; x2=tmp;
  }

  pixel(x1,y1, color); //First and last Pixels always get Set:
  pixel(x2,y2, color);

  dx = x2 - x1;
  dy = y2 - y1;

  if(dx>=0) {
    xDir = 1;
  } else {
    xDir = -1;
    dx = -dx;
  }
  
  if(dx==0) { // vertical line
    for (int i=y1; i<=y2; i++) screen[(i*width)+x1] = color;
    return;
  }
  if(dy==0) { // horizontal line
    colourdata = color;
    u16 *dest = &screen[(y1*width)+min(x1,x2)];
    dma3(dest, dx+1);
    return;
  }
  if(dx==dy) { // diagonal line.
    while (dx--) {
      screen[(y1*width)+x1] = color;
      x1 += xDir;
      y1++;
    }
    return;
  }

// line is not horizontal, diagonal, or vertical: use Wu Antialiasing:
  u32 ErrorAcc=0;
  u8 trans;

  if(dy>dx) { // y-major line
    u32 ErrorAdj = ((u32)dx<<16) / (u32)dy;
    
    if(xDir < 0) {
        while(--dy) {
        ErrorAcc += ErrorAdj;
        ++y1;
        x2 = x1 - (u16)(ErrorAcc>>16);
        trans = (u8)(ErrorAcc>>11);
        blendPixel(x2  , y1, color, 31-trans);
        blendPixel(x2-1, y1, color,    trans);
      }
    } else {
      while(--dy) {
        ErrorAcc+=ErrorAdj;
        ++y1;
        x2=x1+(u16)(ErrorAcc>>16);
        trans=(u8)(ErrorAcc>>11);
        blendPixel(x2     , y1, color, 31-trans);
        blendPixel(x2+xDir, y1, color,    trans);
      }
    }

  } else { // x-major line
    u32 ErrorAdj=((u32)dy<<16) / (u32)dx;
    while(--dx) {
      ErrorAcc += ErrorAdj;
      x1 += xDir;
      y2 = y1 + (u16)(ErrorAcc>>16);
      trans=(u8)(ErrorAcc>>11);
      blendPixel(x1, y2  , color, 31-trans);
      blendPixel(x1, y2+1, color,    trans);
    }
  }
}


void dsGfx::lineblend(s16 x1, s16 y1, s16 x2, s16 y2, u16 color, u8 blend, u8 size) {
  if (blend == 0) return;
  if (size == 0) return;
  if (blend == 31) {
    line(x1, y1, x2, y2, color, size);
    return;
  }

  s32 deltax = abs(x2 - x1);    // The difference between the x's
  s32 deltay = abs(y2 - y1);    // The difference between the y's
  s32 x = x1;                   // Start x off at the first pixel
  s32 y = y1;                   // Start y off at the first pixel

  s32 xinc1, xinc2, yinc1, yinc2;
  s32 den, num, numadd, numpixels;

  if (x2 >= x1) {               // The x-values are increasing
    xinc1 = 1;
    xinc2 = 1;
  } else {                      // The x-values are decreasing
    xinc1 = -1;
    xinc2 = -1;
  }

  if (y2 >= y1) {               // The y-values are increasing
    yinc1 = 1;
    yinc2 = 1;
  } else {                      // The y-values are decreasing
    yinc1 = -1;
    yinc2 = -1;
  }

  if (deltax >= deltay) {       // There is at least one x-value for every y-value
//    xinc1 = 0;                  // Don't change the x when numerator >= denominator
//    yinc2 = 0;                  // Don't change the y for every iteration
    den = deltax;
    num = deltax >> 1;
    numadd = deltay;
    numpixels = deltax;         // There are more x-values than y-values

    for (s32 curpixel = 0; curpixel <= numpixels; curpixel++) {
      blendPixel(x, y, color, blend); // Draw the current pixel
      if (size>1) blendPixel(x, y+1, color, blend);
      if (size>2) blendPixel(x, y-1, color, blend);

      num += numadd;              // Increase the numerator by the top of the fraction
      if (num >= den) {           // Check if numerator >= denominator
        num -= den;               // Calculate the new numerator value
//        x += xinc1;               // Change the x as appropriate
        y += yinc1;               // Change the y as appropriate
      }
      x += xinc2;                 // Change the x as appropriate
//      y += yinc2;                 // Change the y as appropriate
    }


  } else {                      // There is at least one y-value for every x-value
//    xinc2 = 0;                  // Don't change the x for every iteration
//    yinc1 = 0;                  // Don't change the y when numerator >= denominator
    den = deltay;
    num = deltay >> 1;
    numadd = deltax;
    numpixels = deltay;         // There are more y-values than x-values

    for (s32 curpixel = 0; curpixel <= numpixels; curpixel++) {
      blendPixel(x, y, color, blend); // Draw the current pixel
      if (size>1) blendPixel(x+1, y, color, blend);
      if (size>2) blendPixel(x-1, y, color, blend);

      num += numadd;              // Increase the numerator by the top of the fraction
      if (num >= den) {           // Check if numerator >= denominator
        num -= den;               // Calculate the new numerator value
        x += xinc1;               // Change the x as appropriate
//        y += yinc1;               // Change the y as appropriate
      }
//      x += xinc2;                 // Change the x as appropriate
      y += yinc2;                 // Change the y as appropriate
    }
  }
/*
  for (s32 curpixel = 0; curpixel <= numpixels; curpixel++) {
    blendPixel(x, y, color, blend); // Draw the current pixel
    num += numadd;              // Increase the numerator by the top of the fraction
    if (num >= den) {           // Check if numerator >= denominator
      num -= den;               // Calculate the new numerator value
      x += xinc1;               // Change the x as appropriate
      y += yinc1;               // Change the y as appropriate
    }
    x += xinc2;                 // Change the x as appropriate
    y += yinc2;                 // Change the y as appropriate
  }*/
}



void dsGfx::copyAtoB() {
  dmaCopyHalfWords(3, screen, back, (width*height*2));
}



void dsGfx::copyBtoA() {
  dmaCopyHalfWords(3, back, screen, (width*height*2));
}



void dsGfx::copyAtoB(u8 x1, u8 y1, u8 x2, u8 y2) {
  if (x2 < x1) {
    u8 t = x1;
    x1 = x2;
    x2 = t;
  }

  if (y2 < y1) {
    u8 t = y1;
    y1 = y2;
    y2 = t;
  }

  u16 len = ((x2 - x1) + 1) << 1;
  u16 *src = &screen[x1 + (y1 * width)];
  u16 *dst = &back[x1 + (y1 * width)];

  for (int i=y1; i<=y2; i++) {
    dmaCopyHalfWords(3, src, dst, len);
    src += width;
    dst += width;
  }
}



void dsGfx::copyBtoA(u8 x1, u8 y1, u8 x2, u8 y2) {
  if (x2 < x1) {
    u8 t = x1;
    x1 = x2;
    x2 = t;
  }

  if (y2 < y1) {
    u8 t = y1;
    y1 = y2;
    y2 = t;
  }

  u16 len = ((x2 - x1) + 1) << 1;
  u16 *src = &back[x1 + (y1 * width)];
  u16 *dst = &screen[x1 + (y1 * width)];

  for (int i=y1; i<=y2; i++) {
    dmaCopyHalfWords(3, src, dst, len);
    src += width;
    dst += width;
  }
}



void dsGfx::copyHLineAtoB(u8 x, u8 y, u8 len, u8 size) {
  u16 *src = &screen[x + (y * width)];
  u16 *dst = &back[x + (y * width)];
  for (int i=0; i<=len; i++) *dst++ = *src++;

  if ( (size > 1) && (y+1 < height) ) {
    src = &screen[x + ((y+1) * width)];
    dst = &back[x + ((y+1) * width)];
    for (int i=0; i<=len; i++) *dst++ = *src++;
  }

  if ( (size > 2) && (y-1 > 0) ) {
    src = &screen[x + ((y-1) * width)];
    dst = &back[x + ((y-1) * width)];
    for (int i=0; i<=len; i++) *dst++ = *src++;
  }

/*
  dmaCopyHalfWords(3, src, dst, ((u32)len)<<1);
  if ((size > 1) && (y+1 < height)) dmaCopyHalfWords(3, src+width, dst+width, ((u32)len)<<1);
  if ((size > 2) && (y-1 < 0))      dmaCopyHalfWords(3, src-width, dst-width, ((u32)len)<<1);
*/
}



void dsGfx::copyHLineBtoA(u8 x, u8 y, u8 len, u8 size) {
  u16 *src = &back[x + (y * width)];
  u16 *dst = &screen[x + (y * width)];

  for (int i=0; i<=len; i++) *dst++ = *src++;

  if ( (size > 1) && (y+1 < height) ) {
    src = &back[x + ((y+1) * width)];
    dst = &screen[x + ((y+1) * width)];
    for (int i=0; i<=len; i++) *dst++ = *src++;
  }

  if ( (size > 2) && (y-1 > 0) ) {
    src = &back[x + ((y-1) * width)];
    dst = &screen[x + ((y-1) * width)];
    for (int i=0; i<=len; i++) *dst++ = *src++;
  }
/*
  dmaCopyHalfWords(3, src, dst, ((u32)len)<<1);
  if ((size > 1) && (y+1 < height)) dmaCopyHalfWords(3, src+width, dst+width, ((u32)len)<<1);
  if ((size > 2) && (y-1 < 0))      dmaCopyHalfWords(3, src-width, dst-width, ((u32)len)<<1);
*/
}



void dsGfx::copyVLineAtoB(u8 x, u8 y, u8 len, u8 size) {
  u16 *src = &screen[x + (y * width)];
  u16 *dst = &back[x + (y * width)];
  for (int i=0; i<=len; i++) {
    *dst = *src;
    src += width;
    dst += width;
  }
  
  if ( (size > 1) && (x+1 < width) ) {
    src = &screen[x + 1 + (y * width)];
    dst = &back[x + 1 + (y * width)];
    for (int i=0; i<=len; i++) {
      *dst = *src;
      src += width;
      dst += width;
    }
  }

  if ( (size > 2) && (x-1 > 0) ) {
    src = &screen[x - 1 + (y * width)];
    dst = &back[x - 1 + (y * width)];
    for (int i=0; i<=len; i++) {
      *dst = *src;
      src += width;
      dst += width;
    }
  }
}



void dsGfx::copyVLineBtoA(u8 x, u8 y, u8 len, u8 size) {
  u16 *src = &back[x + (y * width)];
  u16 *dst = &screen[x + (y * width)];
  for (int i=0; i<=len; i++) {
    *dst = *src;
    src += width;
    dst += width;
  }
  
  if ( (size > 1) && (x+1 < width) ) {
    src = &back[x + 1 + (y * width)];
    dst = &screen[x + 1 + (y * width)];
    for (int i=0; i<=len; i++) {
      *dst = *src;
      src += width;
      dst += width;
    }
  }

  if ( (size > 2) && (x-1 > 0) ) {
    src = &back[x - 1 + (y * width)];
    dst = &screen[x - 1 + (y * width)];
    for (int i=0; i<=len; i++) {
      *dst = *src;
      src += width;
      dst += width;
    }
  }
}



void dsGfx::copyBoxAtoB(u8 x1, u8 y1, u8 x2, u8 y2, u8 size) {
  if (x2 < x1) {
    u8 t = x1;
    x1 = x2;
    x2 = t;
  }

  if (y2 < y1) {
    u8 t = y1;
    y1 = y2;
    y2 = t;
  }

  //horz
  copyHLineAtoB(x1, y1, x2-x1, size);
  copyHLineAtoB(x1, y2, x2-x1, size);

  //vert
  copyVLineAtoB(x1, y1, y2-y1, size);
  copyVLineAtoB(x2, y1, y2-y1, size);
}



void dsGfx::copyBoxBtoA(u8 x1, u8 y1, u8 x2, u8 y2, u8 size) {
  if (x2 < x1) {
    u8 t = x1;
    x1 = x2;
    x2 = t;
  }

  if (y2 < y1) {
    u8 t = y1;
    y1 = y2;
    y2 = t;
  }

  //horz
  copyHLineBtoA(x1, y1, x2-x1, size);
  copyHLineBtoA(x1, y2, x2-x1, size);

  //vert
  copyVLineBtoA(x1, y1, y2-y1, size);
  copyVLineBtoA(x2, y1, y2-y1, size);
}



void dsGfx::circle(s16 cx, s16 cy, s16 radius, u16 color) {
  if (radius == 0) return;

  colourdata = color;
  if (radius < 0) radius =- radius;
  s16 x = 0;
  s16 y = radius;
  s16 p = 1 - radius;
  s16 d1 = 3;
  s16 d2 = -2*radius + 5;

  while (x < y) {
    if (p < 0) {
      p += d1;
      d1 += 2;
      d2 += 2;
    } else {
      p += d2;
      d1 += 2;
      d2 += 4;
      y--;
    }

    if (cy + y < height) {
      if (cx + x < width) pixel(cx + x, cy + y, colourdata);
      if (cx - x >= 0)    pixel(cx - x, cy + y, colourdata);
    }
    if (cy - y >= 0) {
      if (cx + x < width) pixel(cx + x, cy - y, colourdata);
      if (cx - x >= 0)    pixel(cx - x, cy - y, colourdata);
    }
    if (cy + x < height) {
      if (cx + y < width) pixel(cx + y, cy + x, colourdata);
      if (cx - y >= 0)    pixel(cx - y, cy + x, colourdata);
    }
    if (cy - x >= 0) {
      if (cx + y < width) pixel(cx + y, cy - x, colourdata);
      if (cx - y >= 0)    pixel(cx - y, cy - x, colourdata);
    }
    x++;
  }
}



void dsGfx::circleaa(s16 cx, s16 cy, s16 radius, u16 color) {
  if (radius == 0) return;

  colourdata = color;
  if (radius < 0) radius =- radius;
  s16 x = 0;
  s16 y = radius;
  s16 p = 1 - radius;
  s16 d1 = 3;
  s16 d2 = -2*radius + 5;
  u16 drop = radius >> 5;

  while (x < y) {
    u16 pp = p >> drop;

    if (p < 0) {
      p += d1;
      d1 += 2;
      d2 += 2;
    } else {
      p += d2;
      d1 += 2;
      d2 += 4;
      y--;
    }

    if (cy + y < height) {
      if (cx + x < width) blendPixel(cx + x, cy + y, colourdata, 31-pp);
      if (cx - x >= 0)    blendPixel(cx - x, cy + y, colourdata, 31-pp);
      if (cx + x < width) blendPixel(cx + x, cy + y - 1, colourdata, pp);
      if (cx - x >= 0)    blendPixel(cx - x, cy + y - 1, colourdata, pp);
    }
    if (cy - y >= 0) {
      if (cx + x < width) blendPixel(cx + x, cy - y, colourdata, 31-pp);
      if (cx - x >= 0)    blendPixel(cx - x, cy - y, colourdata, 31-pp);
      if (cx + x < width) blendPixel(cx + x, cy - y + 1, colourdata, pp);
      if (cx - x >= 0)    blendPixel(cx - x, cy - y + 1, colourdata, pp);
    }
    if (cy + x < height) {
      if (cx + y < width) blendPixel(cx + y, cy + x, colourdata, 31-pp);
      if (cx - y >= 0)    blendPixel(cx - y, cy + x, colourdata, 31-pp);
      if (cx + y < width) blendPixel(cx + y - 1, cy + x, colourdata, pp);
      if (cx - y >= 0)    blendPixel(cx - y + 1, cy + x, colourdata, pp);
    }
    if (cy - x >= 0) {
      if (cx + y < width) blendPixel(cx + y, cy - x, colourdata, 31-pp);
      if (cx - y >= 0)    blendPixel(cx - y, cy - x, colourdata, 31-pp);
      if (cx + y < width) blendPixel(cx + y - 1, cy - x, colourdata, pp);
      if (cx - y >= 0)    blendPixel(cx - y + 1, cy - x, colourdata, pp);
    }
    x++;
  }
}



void dsGfx::circlefill(s16 cx, s16 cy, s16 radius, u16 color) {
  if (radius == 0) return;

  colourdata = color;
  if (radius < 0) radius =- radius;
  s16 x = 0;
  s16 y = radius;
  s16 p = 1 - radius;
  s16 d1 = 3;
  s16 d2 = -2*radius + 5;
  
  while (x < y) {
    if (p < 0) {
      p += d1;
      d1 += 2;
      d2 += 2;
    } else {
      p += d2;
      d1 += 2;
      d2 += 4;
      y--;
    }

    register s32 w1 = min(x<<1, width-(cx-x));
    register s32 w2 = min(y<<1, width-(cx-y));
    register s32 l1 = cx-x;
    register s32 l2 = cx-y;
    if (l1 < 0) { w1 += l1; l1 = 0; }
    if (l2 < 0) { w2 += l2; l2 = 0; }
    if (cy+y<height) dma3(getPixelPtr(l1, cy+y), w1);
    if (cy-y>=0)     dma3(getPixelPtr(l1, cy-y), w1);
    if (cy+x<height) dma3(getPixelPtr(l2, cy+x), w2);
    if (cy-x>=0)     dma3(getPixelPtr(l2, cy-x), w2);

    x++;
  }
}



void dsGfx::circlefill(s16 cx, s16 cy, s16 radius, u16 color, u8 blend) {
  if (radius == 0) return;
  if (blend == 0) return;
  if (blend == 31) {
    circlefill(cx, cy, radius, color);
    return;
  }

  colourdata = color;
  if (radius < 0) radius =- radius;
  s16 x = 0;
  s16 y = radius;
  s16 p = 1 - radius;
  s16 d1 = 3;
  s16 d2 = -2*radius + 5;
  u8 set = 0;
  
  while (x < y) {
    if (p < 0) {
      p += d1;
      d1 += 2;
      d2 += 2;
      set |= 1;
    } else {
      p += d2;
      d1 += 2;
      d2 += 4;
      y--;
      set |= 2;
    }

    register s32 w1 = min(x<<1, width-(cx-x)-1);
    register s32 w2 = min(y<<1, width-(cx-y)-1);
    register s32 l1 = cx-x;
    register s32 l2 = cx-y;
    if (l1 < 0) { w1 += l1; l1 = 0; }
    if (l2 < 0) { w2 += l2; l2 = 0; }

    if (set & 2) {
      if (cy+y<height) lineblend(l1, cy+y, l1+w1, cy+y, color, blend);
      if (cy-y>=0)     lineblend(l1, cy-y, l1+w1, cy-y, color, blend);
    }

    if (cy+x<height) lineblend(l2, cy+x, l2+w2, cy+x, color, blend);
    if (cy-x>=0)     lineblend(l2, cy-x, l2+w2, cy-x, color, blend);

    x++;
    set = 0;
  }
}


//change from using X change to Y change to fix AA issue, maybe?

void dsGfx::circlefillaa(s16 cx, s16 cy, s16 radius, u16 color) {
  if (radius == 0) return;

  colourdata = color;
  if (radius < 0) radius =- radius;
  s16 x = 0;
  s16 y = radius;
  s16 p = 1 - radius;
  s16 d1 = 3;
  s16 d2 = -2*radius + 5;
  u16 drop = radius >> 5;

  while (x < y) {
    u16 pp = p >> drop;

    if (p < 0) {
      p += d1;
      d1 += 2;
      d2 += 2;
    } else {
      p += d2;
      d1 += 2;
      d2 += 4;
      y--;
    }

    if (cy + y < height) {
      if (cx + x < width) blendPixel(cx + x, cy + y, colourdata, 31-pp);
      if (cx - x >= 0)    blendPixel(cx - x, cy + y, colourdata, 31-pp);
    }
    if (cy - y >= 0) {
      if (cx + x < width) blendPixel(cx + x, cy - y, colourdata, 31-pp);
      if (cx - x >= 0)    blendPixel(cx - x, cy - y, colourdata, 31-pp);
    }
    if (cy + x < height) {
      if (cx + y < width) blendPixel(cx + y, cy + x, colourdata, 31-pp);
      if (cx - y >= 0)    blendPixel(cx - y, cy + x, colourdata, 31-pp);
    }
    if (cy - x >= 0) {
      if (cx + y < width) blendPixel(cx + y, cy - x, colourdata, 31-pp);
      if (cx - y >= 0)    blendPixel(cx - y, cy - x, colourdata, 31-pp);
    }

    register s32 w1 = min(x<<1, width-(cx-x))-1;
    register s32 w2 = min(y<<1, width-(cx-y))-1;
    register s32 l1 = cx-x+1;
    register s32 l2 = cx-y+1;
    if (l1 < 0) { w1 += l1; l1 = 0; }
    if (l2 < 0) { w2 += l2; l2 = 0; }
    if (cy+y<height && w1>0) dma3(getPixelPtr(l1, cy+y), w1);
    if (cy-y>0      && w1>0) dma3(getPixelPtr(l1, cy-y), w1);
    if (cy+x<height && w2>0) dma3(getPixelPtr(l2, cy+x), w2);
    if (cy-x>0      && w2>0) dma3(getPixelPtr(l2, cy-x), w2);

    x++;
  }
}



void dsGfx::circle(s16 cx, s16 cy, s16 radius, u16 color, u8 blend) {
  if (radius == 0) return;
  if (blend == 0) return;
  if (blend == 31) {
    circle(cx, cy, radius, color);
    return;
  }

  colourdata = color;
  if (radius < 0) radius =- radius;
  s16 x = 0;
  s16 y = radius;
  s16 p = 1 - radius;
  s16 d1 = 3;
  s16 d2 = -2*radius + 5;

  while (x < y) {
    if (p < 0) {
      p += d1;
      d1 += 2;
      d2 += 2;
    } else {
      p += d2;
      d1 += 2;
      d2 += 4;
      y--;
    }

    if (cy + y < height) {
      if (cx + x < width) blendPixel(cx + x, cy + y, colourdata, blend);
      if (cx - x >= 0)    blendPixel(cx - x, cy + y, colourdata, blend);
    }
    if (cy - y >= 0) {
      if (cx + x < width) blendPixel(cx + x, cy - y, colourdata, blend);
      if (cx - x >= 0)    blendPixel(cx - x, cy - y, colourdata, blend);
    }
    if (cy + x < height) {
      if (cx + y < width) blendPixel(cx + y, cy + x, colourdata, blend);
      if (cx - y >= 0)    blendPixel(cx - y, cy + x, colourdata, blend);
    }
    if (cy - x >= 0) {
      if (cx + y < width) blendPixel(cx + y, cy - x, colourdata, blend);
      if (cx - y >= 0)    blendPixel(cx - y, cy - x, colourdata, blend);
    }
    x++;
  }
}



void dsGfx::disc(s16 cx, s16 cy, s16 radius, u16 color) {
  if(radius==0) return;
  int radius2=radius*radius;
  pixel(cx, cy, color);

  for(int y=radius; y; --y) {
    for(int x=0; x<=y; ++x) {
      int r2=x*x+y*y;
      if(r2>=radius2) continue;
      
      u8 trans=u8(((radius2-r2)<<5)/radius2);
      if(trans==0) continue;

      if (cx+x < width) { 
        if (cy+y < height) blendPixel(cx+x, cy+y, color, trans);
        if (cy-y >= 0)     blendPixel(cx+x, cy-y, color, trans);
      }

      if(x) { // don't overdraw vertical line
        if (cx-x >= 0) { 
          if (cy+y < height) blendPixel(cx-x, cy+y, color, trans);
          if (cy-y >= 0)     blendPixel(cx-x, cy-y, color, trans);
        }
      }

      if(x==y) continue; // don't overdraw diagonal line
      if (cy+x < height) { 
        if (cx+y < width) blendPixel(cx+y, cy+x, color, trans);
        if (cx-y >= 0)    blendPixel(cx-y, cy+x, color, trans);
      }

      if(x==0) continue; // don't overdraw horizontal line
      if (cy-x >= 0) { 
        if (cx+y < width) blendPixel(cx+y, cy-x, color, trans);
        if (cx-y >= 0)    blendPixel(cx-y, cy-x, color, trans);
      }
    }
  }
}



void dsGfx::Mandelbrot(double lx, double ux, double ly, double uy, double d) {
  int px=0;
  for(double x=lx; x<ux; x+=d) {
    int py=0;
    for(double y=ly; y<uy; y+=d) {
      int i,iMax=50;
      double X=x;
      double Y=y;
      for(i=0; i<iMax; ++i) {
        double x1=X*X-Y*Y+x;
        double y1=2*X*Y+y;
        if(x1*x1+y1*y1>=4) break;
        X=x1;
        Y=y1;
      }
      int c=iMax-i;
      drawPixelB(px, py++, RGB(c*5, c*16, c*12)|0x8000);
    }
    ++px;
  }
}
