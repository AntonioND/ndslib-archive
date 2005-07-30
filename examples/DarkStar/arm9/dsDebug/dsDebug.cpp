/*****************************  DARKSTAR  ******************************\
*  Copyright (c) 2005 Vincent E. Milum Jr., All rights reserved.        *
*                                                                       *
*  See License.txt for more information                                 *
*                                                                       *
*  Latest source versions can be found at:  HTTP://WWW.DARKAIN.COM/     *
\***********************************************************************/


#include <NDS/NDS.h>
#include <stdio.h>
#include <malloc.h>

#include "dsDebug.h"
#include "../common.h"
#include "../DarkStar/palette_themes.h"
#include <NDS/DarkStar/dsSpriteManager.h>
#include <NDS/DarkStar/dsEnums.h>


static dsAppTemplate<dsDebug> dsDebugApp;


dsDebug::dsDebug() : dsClickRect(0, 16, 255, 191, DS_SCREEN_BOTH) {
  tx = 0;
  ty = 0;

  print("TOUCH X/Y:", 0, 2, 2);
  print("TOUCH Z:", 0, 3, 2);
  print("CALIB TOUCH:", 0, 4, 2);
  print("CALIB PIXEL:", 0, 5, 2);
  print("TEMP:", 0, 6, 2);
  print("INPUT:", 0, 7, 2);
  print("SPRITE:", 0, 8, 2);
  print("BDAY/ALARM:", 0, 9, 2);
  print("TIME:", 0, 10, 2);
  print("TIME:", 0, 11, 2);
  print("BATT/AUX:", 0, 12, 2);

  print(personal->message, 0, 2, 1);
  print("NAME:", 0, 3, 1);
  print(personal->name, 6, 3, 1);
  print("THEME:", 0, 4, 1);
  print("LANGUAGE:", 0, 5, 1);

/*
  {
    char str[10];
    print("MEMORY:", 0, 21, 1);
//    print( itoa(memsize0, str),  15, 21, 1 );
    print( itoa(_msize(), str),  24, 21, 1 );
  }
*/

  //debug
  print("IPC DEBUG 0/1:", 0, 20, 1);
  print("IPC DEBUG 2/3:", 0, 21, 1);
  print("DEBUG 0/1:", 0, 22, 1);
  print("DEBUG 2/3:", 0, 23, 1);
}


dsDebug::~dsDebug() {
  for (int i=0; i<32*32; i++) {
    BG_GFX[0x800 + i] = 0x0000;
    BG_GFX_SUB[0x800 + i] = 0x0000;
  }
}


void dsDebug::print(const char *text, u8 x, u8 y, u8 screen) {
  u16 *buffer = (screen==1) ? BG_GFX : BG_GFX_SUB;
  buffer += (y*32)+x + 0x800;

  while (*text) {
    if ( (*text >= 'a') && (*text <= 'z') ) {
      *buffer = 0x1040 + (*text - '!' - 32);
    } else {
      *buffer = 0x1040 + (*text - '!');
    }
    text++;
    buffer++;
  }
}


void dsDebug::print(const short *text, u8 x, u8 y, u8 screen) {
  u16 *buffer = (screen==1) ? BG_GFX : BG_GFX_SUB;
  buffer += (y*32)+x + 0x800;

  while (*text) {
    if ( (*text >= 'a') && (*text <= 'z') ) {
      *buffer = 0x1040 + (*text - '!' - 32);
    } else {
      *buffer = 0x1040 + (*text - '!');
    }
    text++;
    buffer++;
  }
}


void dsDebug::onVBlank() {
  char str[32];

  //touch coords
  print( itoa((IPC->touchX <<16)|IPC->touchY, str),  15, 2, 2 );
  print( itoa((tx<<16)|ty, str),  24, 2, 2 );

  //pressure
  print( itoa((IPC->touchZ1<<16)|IPC->touchZ2, str), 15, 3, 2 );
//  u32 pressure = (IPC->touchX * IPC->touchZ2) / (64 * IPC->touchZ1) - IPC->touchX / 64;
  u32 pressure = (((IPC->touchZ2 <<16) / IPC->touchZ1) >>16) * IPC->touchX;
  print( itoa(pressure, str),  24, 3, 2 );

  //calibration, touch coords
  print( itoa((personal->calX1<<16)|personal->calY1, str), 15, 4, 2 );
  print( itoa((personal->calX2<<16)|personal->calY2, str), 24, 4, 2 );

  //calibration, pixel coords
  print( itoa((personal->calX1px<<16)|personal->calY1px, str), 15, 5, 2 );
  print( itoa((personal->calX2px<<16)|personal->calY2px, str), 24, 5, 2 );

  //temp
  u32 tempC = (IPC->temperature >> 12);
  u32 tempF = (mulf32(IPC->temperature, floatof32((float)1.8))>>12) + 32;
  print( itoa((IPC->tdiode1<<16)|IPC->tdiode2, str),  15, 6, 2 );
  print( itoa(tempC | (tempF<<16), str),  24, 6, 2 );

  //keys
  print( itoa((IPC->buttons<<16)|KEYS, str),  24, 7, 2 );

  print( itoa((u32)sprmgr->spriteDebug2(), str),  15, 8, 2 );
  print( itoa((u32)sprmgr->spriteDebug3(), str),  24, 8, 2 );

  print( itoa((personal->birthMonth   << 16) | personal->birthDay,       str), 15, 9, 2);
  print( itoa((personal->alarmHour << 16) | personal->alarmMinute, str), 24, 9, 2);

  print( itoa((*(u32*)&IPC->curtime[0]), str),  15, 10, 2 );
  print( itoa((*(u32*)&IPC->curtime[4]), str),  24, 10, 2 );

  int hours = IPC->rtc_hours;
  if (hours > 50) hours -= 40;
  sprintf(str, "%02d:%02d:%02d - %d %s %d", hours, IPC->rtc_minutes, IPC->rtc_seconds, IPC->rtc_day, getMonthName(IPC->rtc_month), IPC->rtc_year+2000);
  print(str, 32-strlen(str), 11, 2);

  print( itoa(IPC->battery, str),  15, 12, 2 );
  print( itoa(IPC->aux, str),  24, 12, 2 );
/*
  print( itoa(IPC->DEBUG0, str), 15, 20);
  print( itoa(IPC->DEBUG1, str), 24, 20);
  print( itoa(IPC->DEBUG2, str), 15, 21);
  print( itoa(IPC->DEBUG3, str), 24, 21);
*/
  print( itoa(*DEBUG0, str), 15, 22);
  print( itoa(*DEBUG1, str), 24, 22);
  print( itoa(*DEBUG2, str), 15, 23);
  print( itoa(*DEBUG3, str), 24, 23);


  switch (personal->theme) {
    case DS_THEME_GRAY:        print("00 GREY",         15, 4, 1); break;
    case DS_THEME_BROWN:       print("01 MAROON",       15, 4, 1); break;
    case DS_THEME_RED:         print("02 RED",          15, 4, 1); break;
    case DS_THEME_PINK:        print("03 PINK",         15, 4, 1); break;

    case DS_THEME_ORANGE:      print("04 ORANGE",       15, 4, 1); break;
    case DS_THEME_YELLOW:      print("05 YELLOW",       15, 4, 1); break;
    case DS_THEME_LIME_GREEN:  print("06 LIME",         15, 4, 1); break;
    case DS_THEME_GREEN:       print("07 GREEN",        15, 4, 1); break;

    case DS_THEME_DARK_GREEN:  print("08 DARK GREEN",   15, 4, 1); break;
    case DS_THEME_SEA_GREAN:   print("09 TEAL",         15, 4, 1); break;
    case DS_THEME_TURQUOISE:   print("0A LIGHT BLUE",   15, 4, 1); break;
    case DS_THEME_BLUE:        print("0B BLUE",         15, 4, 1); break;

    case DS_THEME_DARK_BLUE:   print("0C DARK BLUE",    15, 4, 1); break;
    case DS_THEME_DARK_PURPLE: print("0D DARK PURPLE",  15, 4, 1); break;
    case DS_THEME_VIOLET:      print("0E LIGHT PURPLE", 15, 4, 1); break;
    case DS_THEME_MAGENTA:     print("0F DARK PINK",    15, 4, 1); break;
    default:                   print("UNKNOWN THEME",   15, 4, 1); break;
  }

  switch (personal->language) {
    case DS_LANGUAGE_JAPANESE: print("00 JAPANESE",      15, 5, 1); break;
    case DS_LANGUAGE_ENGLISH:  print("01 ENGLISH",       15, 5, 1); break;
    case DS_LANGUAGE_FRENCH:   print("02 FRENCH",        15, 5, 1); break;
    case DS_LANGUAGE_GERMAN:   print("03 GERMAN",        15, 5, 1); break;
    case DS_LANGUAGE_ITALIAN:  print("04 ITALIAN",       15, 5, 1); break;
    case DS_LANGUAGE_SPANISH:  print("05 SPANISH",       15, 5, 1); break;
    default:                   print("UNKNOWN LANGUAGE", 15, 5, 1); break;
  }
}


const char *dsDebug::getMonthName(int month) const {
  switch (month) {
    case 1:  return "JANUARY";
    case 2:  return "FEBRUARY";
    case 3:  return "MARCH";
    case 4:  return "APRIL";
    case 5:  return "MAY";
    case 6:  return "JUNE";

    case 7:  return "JULY";
    case 8:  return "AUGUST";
    case 9:  return "SEPTEMBER";
    case 10: return "OCTOBER";
    case 11: return "NOVEMBER";
    case 12: return "DECEMBER";
  }
  return "???";
}
