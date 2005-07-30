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
//#include "common/common.h"

//darkstar includes
#include <NDS/DarkStar/dsClickable.h>
#include <NDS/DarkStar/dsInput.h>
#include <NDS/DarkStar/dsBlank.h>
#include <NDS/DarkStar/dsSound.h>
#include <NDS/DarkStar/dsSpriteManager.h>


//local includes
#include "main.h"


void InterruptHandler(void) {
  if (IF & IRQ_VBLANK) {

//    seed *= 69069; //help randomize things a bit

    static bool lastState = false;
    static dsClickable *click = NULL;
    static s16 lastx=0;
    static s16 lasty=0;

    //update OAM
    sprmgr->updateSystemOAM();
    dsSound::updateIpcSound();

    //check for key press or release
    static u32 lastInputState = KEYS | (IPC->buttons << 16);
		u32 inputState = KEYS | (IPC->buttons << 16);

    if (lastInputState != inputState) {
//      if (mainmenu->getKeyLock()) {
//        mainmenu->onKeyChange(inputState, lastInputState);
//      } else {
        dsInput *input = dsInput::items.getFirstItem();
        while (input) {
          input->onKeyChange(inputState, lastInputState);
          input = dsInput::items.getNextItem(input);
        }
//      }
      lastInputState = inputState;
    }


    s32 x = IPC->touchXpx;
    s32 y = IPC->touchYpx;

    //touch
    if ( !(IPC->buttons & 0x40) ) {
      x = min(max(x, 0), SCREEN_WIDTH-1);
      y = min(max(y, 0), SCREEN_HEIGHT-1);

      if ( (x != lastx) || (y != lasty) ) {

        //new touch
        if (!lastState) {
//          if (mainmenu->getTouchLock()) {
//            click = mainmenu->getLockedClickable( x, y, (dsMainMenu::getActiveScreen() ? DS_SCREEN_SUB : DS_SCREEN_MAIN) );
//          } else {
            click = dsClickable::getItem( x, y, DS_SCREEN_MAIN );
//          }
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
  }

  // Acknowledge interrupts
  IF = IF;
  //VBLANK_INTR_WAIT_FLAGS = IF | IE;
}
