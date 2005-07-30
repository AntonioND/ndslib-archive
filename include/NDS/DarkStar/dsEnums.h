/*****************************  DARKSTAR  ******************************\
*  Copyright (c) 2005 Vincent E. Milum Jr., All rights reserved.        *
*                                                                       *
*  See License.txt for more information                                 *
*                                                                       *
*  Latest source versions can be found at:  HTTP://WWW.DARKAIN.COM/     *
\***********************************************************************/


#ifndef _DS_ENUMS_H_
#define _DS_ENUMS_H_


typedef enum {
  DS_SCREEN_NONE = 0x00,
  DS_SCREEN_MAIN = 0x01,
  DS_SCREEN_SUB  = 0x02,
  DS_SCREEN_BOTH = 0x03,

  DS_SCREEN_NONE_DISABLED = 0x80,
  DS_SCREEN_MAIN_DISABLED = 0x81,
  DS_SCREEN_SUB_DISABLED  = 0x82,
  DS_SCREEN_BOTH_DISABLED = 0x83,
} DS_SCREEN;


typedef enum {
  DS_THEME_GRAY        = 0x0,
  DS_THEME_BROWN       = 0x1,
  DS_THEME_RED         = 0x2,
  DS_THEME_PINK        = 0x3,

  DS_THEME_ORANGE      = 0x4,
  DS_THEME_YELLOW      = 0x5,
  DS_THEME_LIME_GREEN  = 0x6,
  DS_THEME_GREEN       = 0x7,

  DS_THEME_DARK_GREEN  = 0x8,
  DS_THEME_SEA_GREAN   = 0x9,
  DS_THEME_TURQUOISE   = 0xA,
  DS_THEME_BLUE        = 0xB,

  DS_THEME_DARK_BLUE   = 0xC,
  DS_THEME_DARK_PURPLE = 0xD,
  DS_THEME_VIOLET      = 0xE,
  DS_THEME_MAGENTA     = 0xF,
} DS_THEME;


typedef enum {
  DS_LANGUAGE_JAPANESE = 0x0,
  DS_LANGUAGE_ENGLISH  = 0x1,
  DS_LANGUAGE_FRENCH   = 0x2,
  DS_LANGUAGE_GERMAN   = 0x3,
  DS_LANGUAGE_ITALIAN  = 0x4,
  DS_LANGUAGE_SPANISH  = 0x5,
} DS_LANGUAGE;


typedef enum {
  DS_STYLE_BOX       = 0x00,
  DS_STYLE_BOX_INV   = 0x01,
  DS_STYLE_ROUND     = 0x02,
  DS_STYLE_ROUND_INV = 0x03,
  DS_STYLE_NONE      = 0xFF,
} DS_STYLE;


typedef enum {
  DS_TEXT_COLOR_NORMAL = 0x0,
  DS_TEXT_COLOR_INVERT = 0x1,
} DS_TEXT_COLOR;


#endif //_DS_ENUMS_H_
