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
#include "dsText.h"
#include "dsMainMenu.h"


//ANSI
void dsText::drawText(const char *text, s16 x, s16 y, DS_SCREEN screen, u16 palette) {
  drawText( text, &mainmenu->getBuffer(screen)[(y*32) + x + 0x400], palette );
}

void dsText::drawText(const char *text, u16 *buffer, s16 x, s16 y, u16 palette) {
  drawText( text, &buffer[(y*32) + x], palette );
}

void dsText::drawText(const char *text, u16 *buffer, u16 palette) {
  if (!text) return;
  palette <<= 12;

  while (*text) {
    if (*text >= 'a' && *text <= 'z') {
      *buffer = (0x0020 + *text - '!') | palette;
    } else if (*text >= '!' && *text <= '¡') {
      *buffer = (0x0040 + *text - '!') | palette;
    }
    text++;
    buffer++;
  }
}



//UNICODE
void dsText::drawText(u16 *text, s16 x, s16 y, DS_SCREEN screen, u16 palette) {
  drawText( text, &mainmenu->getBuffer(screen)[(y*32) + x + 0x400], palette );
}

void dsText::drawText(u16 *text, u16 *buffer, s16 x, s16 y, u16 palette) {
  drawText( text, &buffer[(y*32) + x], palette );
}

void dsText::drawText(u16 *text, u16 *buffer, u16 palette) {
  if (!text) return;
  palette <<= 12;

  while (*text) {
    if (*text >= 'a' && *text <= 'z') {
      *buffer = (0x0020 + *text - '!') | palette;
    } else if (*text >= '!' && *text <= '¡') {
      *buffer = (0x0040 + *text - '!') | palette;
    }
    text++;
    buffer++;
  }
}
