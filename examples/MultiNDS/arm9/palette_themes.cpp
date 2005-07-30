/*****************************  DARKSTAR  ******************************\
*  Copyright (c) 2005 Vincent E. Milum Jr., All rights reserved.        *
*                                                                       *
*  See License.txt for more information                                 *
*                                                                       *
*  Latest source versions can be found at:  HTTP://WWW.DARKAIN.COM/     *
\***********************************************************************/


#include <NDS/NDS.h>
#include "common.h"
#include "palette_themes.h"


const u16 PALETTE_THEME[16][16] = {
  {  //0: Gray
    RGB( 0, 0, 0),  //transparent

    RGB( 7,11,12),
    RGB( 8,12,13),
    RGB( 9,13,14),
    RGB(10,14,15),
    RGB(11,15,16),
    RGB(12,16,17),
    RGB(13,17,18),  //mid colour
    RGB(14,18,19),
    RGB(15,19,20),
    RGB(16,20,21),
    RGB(17,21,22),
    RGB(18,22,23),
    RGB(19,23,24),
    RGB(20,24,25),

//    RGB( 0, 0, 0),  //dark border
    RGB(31,31,31),  //light border
  },

  {  //1: Maroon
    RGB( 0, 0, 0),  //transparent

    RGB(12, 4, 2),
    RGB(13, 4, 2),
    RGB(14, 5, 3),
    RGB(15, 5, 3),
    RGB(16, 6, 4),
    RGB(17, 6, 4),
    RGB(18, 7, 5),  //mid colour
    RGB(19, 7, 5),
    RGB(20, 8, 6),
    RGB(21, 8, 6),
    RGB(22, 9, 7),
    RGB(23, 9, 7),
    RGB(24,10, 8),
    RGB(25,10, 8),

//    RGB( 0, 0, 0),  //dark border
    RGB(31,31,31),  //light border
  },

  {  //2: Red
    RGB( 0, 0, 0),  //transparent

    RGB(18, 5, 5),
    RGB(19, 5, 5),
    RGB(20, 6, 6),
    RGB(21, 6, 6),
    RGB(22, 7, 7),
    RGB(23, 7, 7),
    RGB(24, 8, 8),  //mid colour
    RGB(25, 8, 8),
    RGB(26, 9, 9),
    RGB(27, 9, 9),
    RGB(28,10,10),
    RGB(29,10,10),
    RGB(30,11,11),
    RGB(31,11,11),

//    RGB( 0, 0, 0),  //dark border
    RGB(31,31,31),  //light border
  },

  {  //3: Pink
    RGB( 0, 0, 0),  //transparent

    RGB(25,14,25),
    RGB(25,15,25),
    RGB(26,16,26),
    RGB(26,17,26),
    RGB(27,18,27),
    RGB(27,19,27),
    RGB(28,20,28),  //mid colour
    RGB(28,21,28),
    RGB(29,22,29),
    RGB(29,23,29),
    RGB(30,24,30),
    RGB(30,25,30),
    RGB(31,26,31),
    RGB(31,27,31),

//    RGB( 0, 0, 0),  //dark border
    RGB(31,31,31),  //light border
  },

  {  //4: Orange
    RGB( 0, 0, 0),  //transparent

    RGB(25,12, 3),
    RGB(25,13, 3),
    RGB(26,14, 4),
    RGB(26,15, 4),
    RGB(27,16, 5),
    RGB(27,17, 5),
    RGB(28,18, 6),  //mid colour
    RGB(28,19, 7),
    RGB(29,20, 7),
    RGB(29,21, 8),
    RGB(30,22, 8),
    RGB(30,23, 9),
    RGB(31,24, 9),
    RGB(31,25, 9),

//    RGB( 0, 0, 0),  //dark border
    RGB(31,31,31),  //light border
  },

  {  //5: Yellow
    RGB( 0, 0, 0),  //transparent

    RGB(26,18, 0),
    RGB(25,19, 1),
    RGB(26,20, 2),
    RGB(26,21, 3),
    RGB(27,22, 4),
    RGB(27,23, 5),
    RGB(28,24, 6),  //mid colour
    RGB(28,25, 7),
    RGB(29,26, 8),
    RGB(29,27, 9),
    RGB(30,28,10),
    RGB(30,29,11),
    RGB(31,30,12),
    RGB(31,31,13),

//    RGB( 0, 0, 0),  //dark border
    RGB(31,31,31),  //light border
  },

  {  //6: Lime
    RGB( 0, 0, 0),  //transparent

    RGB(14,25, 2),
    RGB(15,25, 3),
    RGB(16,26, 4),
    RGB(17,26, 5),
    RGB(18,27, 6),
    RGB(19,27, 7),
    RGB(20,28, 8),  //mid colour
    RGB(21,28, 9),
    RGB(22,29,10),
    RGB(23,29,11),
    RGB(24,30,12),
    RGB(25,30,13),
    RGB(26,31,14),
    RGB(27,31,15),

//    RGB( 0, 0, 0),  //dark border
    RGB(31,31,31),  //light border
  },

  {  //7: Green
    RGB( 0, 0, 0),  //transparent

    RGB( 0,25, 0),
    RGB( 1,25, 1),
    RGB( 2,26, 2),
    RGB( 3,26, 3),
    RGB( 4,27, 4),
    RGB( 5,27, 5),
    RGB( 6,28, 6),  //mid colour
    RGB( 7,28, 7),
    RGB( 8,29, 8),
    RGB( 9,29, 9),
    RGB(10,30,10),
    RGB(11,30,11),
    RGB(12,31,12),
    RGB(13,31,13),

//    RGB( 0, 0, 0),  //dark border
    RGB(31,31,31),  //light border
  },

  {  //8: Dark Green
    RGB( 0, 0, 0),  //transparent

    RGB( 0,14, 0),
    RGB( 0,15, 0),
    RGB( 1,16, 1),
    RGB( 1,17, 1),
    RGB( 2,18, 2),
    RGB( 2,19, 2),
    RGB( 3,20, 3),  //mid colour
    RGB( 3,21, 3),
    RGB( 4,22, 4),
    RGB( 4,23, 4),
    RGB( 5,24, 5),
    RGB( 5,25, 5),
    RGB( 6,26, 6),
    RGB( 6,27, 6),

//    RGB( 0, 0, 0),  //dark border
    RGB(31,31,31),  //light border
  },

  {  //9: Teal 
    RGB( 0, 0, 0),  //transparent

    RGB( 4,21,10),
    RGB( 5,21,11),
    RGB( 6,22,12),
    RGB( 7,22,13),
    RGB( 8,23,14),
    RGB( 9,23,15),
    RGB(10,24,16),  //mid colour
    RGB(11,24,17),
    RGB(12,25,18),
    RGB(13,25,19),
    RGB(14,26,20),
    RGB(15,26,21),
    RGB(16,27,22),
    RGB(17,27,23),

//    RGB( 0, 0, 0),  //dark border
    RGB(31,31,31),  //light border
  },

  {  //A: Light Blue 
    RGB( 0, 0, 0),  //transparent

    RGB( 4,25,25),
    RGB( 5,25,25),
    RGB( 6,26,26),
    RGB( 7,26,26),
    RGB( 8,27,27),
    RGB( 9,27,27),
    RGB(10,28,28),  //mid colour
    RGB(11,28,28),
    RGB(12,29,29),
    RGB(13,29,29),
    RGB(14,30,30),
    RGB(15,30,30),
    RGB(16,31,31),
    RGB(17,31,31),

//    RGB( 0, 0, 0),  //dark border
    RGB(31,31,31),  //light border
  },

  {  //B: Blue 
    RGB( 0, 0, 0),  //transparent

    RGB( 4, 4,25),
    RGB( 5, 5,25),
    RGB( 6, 6,26),
    RGB( 7, 7,26),
    RGB( 8, 8,27),
    RGB( 9, 9,27),
    RGB(10,10,28),  //mid colour
    RGB(11,11,28),
    RGB(12,12,29),
    RGB(13,13,29),
    RGB(14,14,30),
    RGB(15,15,30),
    RGB(16,16,31),
    RGB(17,17,31),

//    RGB( 0, 0, 0),  //dark border
    RGB(31,31,31),  //light border
  },

  {  //C: Dark Blue 
    RGB( 0, 0, 0),  //transparent

    RGB( 0, 0,14),
    RGB( 0, 0,15),
    RGB( 0, 0,16),
    RGB( 0, 0,17),
    RGB( 0, 0,18),
    RGB( 0, 0,19),
    RGB( 0, 0,20),  //mid colour
    RGB( 1, 1,21),
    RGB( 2, 2,22),
    RGB( 3, 3,23),
    RGB( 4, 4,24),
    RGB( 5, 5,25),
    RGB( 6, 6,26),
    RGB( 6, 6,27),

//    RGB( 0, 0, 0),  //dark border
    RGB(31,31,31),  //light border
  },

  {  //D: Dark Purple 
    RGB( 0, 0, 0),  //transparent

    RGB( 8, 0,16),
    RGB( 9, 0,17),
    RGB(10, 0,18),
    RGB(11, 0,19),
    RGB(12, 0,20),
    RGB(13, 0,21),
    RGB(14, 0,22),  //mid colour
    RGB(15, 1,23),
    RGB(16, 2,24),
    RGB(17, 3,25),
    RGB(18, 4,26),
    RGB(19, 5,27),
    RGB(20, 6,28),
    RGB(21, 6,29),

//    RGB( 0, 0, 0),  //dark border
    RGB(31,31,31),  //light border
  },

  {  //E: Light Purple 
    RGB( 0, 0, 0),  //transparent

    RGB(18, 4,18),
    RGB(18, 5,18),
    RGB(19, 6,19),
    RGB(19, 7,19),
    RGB(20, 8,20),
    RGB(20, 9,20),
    RGB(21,10,21),  //mid colour
    RGB(21,11,21),
    RGB(22,12,22),
    RGB(22,13,22),
    RGB(23,14,23),
    RGB(23,15,23),
    RGB(24,16,24),
    RGB(24,17,24),

//    RGB( 0, 0, 0),  //dark border
    RGB(31,31,31),  //light border
  },

  {  //F: Dark Pink 
    RGB( 0, 0, 0),  //transparent

    RGB(25, 4,15),
    RGB(25, 5,15),
    RGB(26, 6,16),
    RGB(26, 7,16),
    RGB(27, 8,17),
    RGB(27, 9,17),
    RGB(28,10,18),  //mid colour
    RGB(28,11,18),
    RGB(29,12,19),
    RGB(29,13,19),
    RGB(30,14,20),
    RGB(30,15,20),
    RGB(31,16,21),
    RGB(31,17,21),

//    RGB( 0, 0, 0),  //dark border
    RGB(31,31,31),  //light border
  },

};



const u16 TEXT_BORDER[16][2] = {
  { RGB(31,31,31), RGB( 0, 0, 0) },  //0: Gray
  { RGB(31,31,31), RGB( 0, 0, 0) },  //1: Maroon
  { RGB( 0, 0, 0), RGB(31,31,31) },  //2: Red
  { RGB(31,31,31), RGB( 0, 0, 0) },  //3: Pink

  { RGB(31,31,31), RGB( 0, 0, 0) },  //4: Orange
  { RGB(31,31,31), RGB( 0, 0, 0) },  //5: Yellow
  { RGB(31,31,31), RGB( 0, 0, 0) },  //6: Lime
  { RGB(31,31,31), RGB( 0, 0, 0) },  //7: Green

  { RGB(31,31,31), RGB( 0, 0, 0) },  //8: Dark Green
  { RGB(31,31,31), RGB( 0, 0, 0) },  //9: Teal 
  { RGB(31,31,31), RGB( 0, 0, 0) },  //A: Light Blue 
  { RGB( 0, 0, 0), RGB(31,31,31) },  //B: Blue 

  { RGB( 0, 0, 0), RGB(31,31,31) },  //C: Dark Blue 
  { RGB( 0, 0, 0), RGB(31,31,31) },  //D: Dark Purple 
  { RGB(31,31,31), RGB( 0, 0, 0) },  //E: Light Purple 
  { RGB(31,31,31), RGB( 0, 0, 0) },  //F: Dark Pink 
};
