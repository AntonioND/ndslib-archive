/*****************************  DARKSTAR  ******************************\
*  Copyright (c) 2005 Vincent E. Milum Jr., All rights reserved.        *
*                                                                       *
*  See License.txt for more information                                 *
*                                                                       *
*  Latest source versions can be found at:  HTTP://WWW.DARKAIN.COM/     *
\***********************************************************************/


//library includes
#include <NDS/NDS.h>

//common includes
#include "common.h"

//darkstar includes
#include <NDS/DarkStar/dsClickable.h>
#include <NDS/DarkStar/dsInput.h>
#include <NDS/DarkStar/dsBlank.h>
#include <NDS/DarkStar/dsSound.h>
#include <NDS/DarkStar/dsSpriteManager.h>
#include "DarkStar/dsMainMenu.h"

//local includes
#include "main.h"

/*
#define TOUCH_CAL_X1 (*(vs16*)0x027FFCD8)
#define TOUCH_CAL_Y1 (*(vs16*)0x027FFCDA)
#define TOUCH_CAL_X2 (*(vs16*)0x027FFCDE)
#define TOUCH_CAL_Y2 (*(vs16*)0x027FFCE0)
s32 TOUCH_WIDTH  = TOUCH_CAL_X2 - TOUCH_CAL_X1;
s32 TOUCH_HEIGHT = TOUCH_CAL_Y2 - TOUCH_CAL_Y1;
s32 TOUCH_OFFSET_X = ( ((SCREEN_WIDTH -60) * TOUCH_CAL_X1) / TOUCH_WIDTH  ) - 28;
s32 TOUCH_OFFSET_Y = ( ((SCREEN_HEIGHT-60) * TOUCH_CAL_Y1) / TOUCH_HEIGHT ) - 28;
*/

void InterruptHandler(void) {
  if (IF & IRQ_VBLANK) {
//    CP15_FlushDCache();  //flush the cache, so things dont break
//    CP15_CleanAndFlushDCache();
//    CP15_DrainWriteBuffer();

    seed *= 69069; //help randomize things a bit

    static bool lastState = false;
    static dsClickable *click = NULL;
    static s16 lastx=0;
    static s16 lasty=0;

    //update OAM
//    CP15_DrainWriteBuffer();
    sprmgr->updateSystemOAM();
    dsSound::updateIpcSound();

    //check for key press or release
    static u32 lastInputState = KEYS | (IPC->buttons << 16);
		u32 inputState = KEYS | (IPC->buttons << 16);

    if (lastInputState != inputState) {
      if (mainmenu->getKeyLock()) {
        mainmenu->onKeyChange(inputState, lastInputState);
      } else {
        dsInput *input = dsInput::items.getFirstItem();
        while (input) {
          input->onKeyChange(inputState, lastInputState);
          input = dsInput::items.getNextItem(input);
        }
      }
      lastInputState = inputState;
    }


    s32 x = IPC->touchXpx;
    s32 y = IPC->touchYpx;

    //touch
    if ( !(IPC->buttons & 0x40) ) {
//      register s32 x = ( ((SCREEN_WIDTH -60) * tx) / TOUCH_WIDTH  ) - TOUCH_OFFSET_X;
//      register s32 y = ( ((SCREEN_HEIGHT-60) * ty) / TOUCH_HEIGHT ) - TOUCH_OFFSET_Y;
      x = min(max(x, 0), SCREEN_WIDTH-1);
      y = min(max(y, 0), SCREEN_HEIGHT-1);

      if ( (x != lastx) || (y != lasty) ) {

        //new touch
        if (!lastState) {
          if (mainmenu->getTouchLock()) {
            click = mainmenu->getLockedClickable( x, y, (dsMainMenu::getActiveScreen() ? DS_SCREEN_SUB : DS_SCREEN_MAIN) );
          } else {
            click = dsClickable::getItem( x, y, (dsMainMenu::getActiveScreen() ? DS_SCREEN_SUB : DS_SCREEN_MAIN) );
          }
          if (click) click->onClick(x, y);
        }

        //drag touch
        else {
          if (click && dsClickable::hasItem(click)) click->onDrag(x, y);
        }
      }

      lastx = x;
      lasty = y;
      lastState = true;
    }

    //no touch
    else {
      if (lastState) {
        if (click && dsClickable::hasItem(click)) {
          click->onDrop(lastx, lasty);
        }
        lastState = false;
        lastx = -1;
        lasty = -1;
      }
    }

    //vblank irq stuff
    dsBlank *bl = dsBlank::items.getFirstItem();
    while (bl) {
      bl->onVBlank();
      bl = dsBlank::items.getNextItem(bl);
    }

  // Acknowledge interrupts
    IME = 0;
    IF = IF;
    //VBLANK_INTR_WAIT_FLAGS = IF | IE;
    IME = 1;
  }

}
