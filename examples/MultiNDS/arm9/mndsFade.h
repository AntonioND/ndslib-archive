/*****************************  DARKSTAR  ******************************\
*  Copyright (c) 2005 Vincent E. Milum Jr., All rights reserved.        *
*                                                                       *
*  See License.txt for more information                                 *
*                                                                       *
*  Latest source versions can be found at:  HTTP://WWW.DARKAIN.COM/     *
\***********************************************************************/


#ifndef _MNDS_FADE_H_
#define _MNDS_FADE_H_


//DarkStar includes
#include <NDS/DarkStar/dsBlank.h>
#include <NDS/DarkStar/dsGfx.h>


//resources
#include "game_raw.h"
#include "game_pal.h"
#include "palette_themes.h"



class mndsFade : public dsBlank {
  public:
    mndsFade() { counter=0; palette=1; dir=1; wait=0; }
    virtual ~mndsFade() {}

    void setPalette(u32 pal) { palette = pal; }

    virtual void onVBlank() {
      wait++;
      if (wait == 3) {
        wait = 0;
        counter += dir;
        if (counter == 0) { dir = 1; }
        if (counter == 10) { dir = -1; }
        PALETTE[palette] = dsGfx::alphaBlend(RGB(0,0,0), RGB(31,31,31), 10-counter);
        
        for (int i=0; i<16; i++) {
          PALETTE[(palette*16)+i] = dsGfx::alphaBlend(((u16*)game_pal)[i], PALETTE_THEME[COLOR_THEME][i], counter);
        }
      }
    }

  private:
    u32 counter;
    u32 palette;
    s8 dir;
    u8 wait;
};


#endif //_MNDS_FADE_H_
