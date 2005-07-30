/*****************************  DARKSTAR  ******************************\
*  Copyright (c) 2005 Vincent E. Milum Jr., All rights reserved.        *
*                                                                       *
*  See License.txt for more information                                 *
*                                                                       *
*  Latest source versions can be found at:  HTTP://WWW.DARKAIN.COM/     *
\***********************************************************************/

 
#include <NDS/NDS.h>
#include <NDS/ndsload.h>


#define TOUCH_CAL_X1 (*(vs16*)0x027FFCD8)
#define TOUCH_CAL_Y1 (*(vs16*)0x027FFCDA)
#define TOUCH_CAL_X2 (*(vs16*)0x027FFCDE)
#define TOUCH_CAL_Y2 (*(vs16*)0x027FFCE0)


//////////////////////////////////////////////////////////////////////

#define SCREEN_WIDTH    256
#define SCREEN_HEIGHT   192

s32 TOUCH_WIDTH; 
s32 TOUCH_HEIGHT; 
s32 TOUCH_OFFSET_X;
s32 TOUCH_OFFSET_Y; 

s16 OLD_X_PX;
s16 OLD_Y_PX;


#define abs(a)  ((a) < (0) ? 0-(a) : (a))


inline void WaitForVblank() {
	while(DISP_Y!=191);
	while(DISP_Y==191);
}


void startSound(int sampleRate, const void* data, uint32 bytes, u8 channel, u8 vol,  u8 pan, u8 format) {
  SCHANNEL_TIMER(channel)  = SOUND_FREQ(sampleRate);
  SCHANNEL_SOURCE(channel) = (uint32)data;
  SCHANNEL_LENGTH(channel) = bytes;
  SCHANNEL_CR(channel)     = SCHANNEL_ENABLE | SOUND_ONE_SHOT | SOUND_VOL(vol) | SOUND_PAN(pan) | (format==1?SOUND_8BIT:SOUND_16BIT);
}


s8 getFreeSoundChannel() {
  int i;
  for (i=0; i<16; i++) {
    if ( (SCHANNEL_CR(i) & SCHANNEL_ENABLE) == 0 ) return i;
  }
  return -1;
}


//////////////////////////////////////////////////////////////////////


void InterruptHandler(void) {
  static int heartbeat = 0;
 
  if (IF & IRQ_VBLANK) {
    u32 i;
    if (LOADNDS->PATH != 0) {
      LOADNDS->ARM7FUNC(LOADNDS->PATH);
    }


    s16 but=0, x=0, y=0, xpx=0, ypx=0, z1=0, z2=0, batt=0, aux=0;
    int t1=0, t2=0;
    uint32 temp=0;
    uint8 ct[sizeof(IPC->curtime)];
    
    // Update the heartbeat
    heartbeat++;
 
    // Read the X/Y buttons and the /PENIRQ line
    but = XKEYS;
    if (!(but & 0x40)) {
      // Read the touch screen
      x = touchRead(TSC_MEASURE_X);
      y = touchRead(TSC_MEASURE_Y);
      xpx = ( ((SCREEN_WIDTH -60) * x) / TOUCH_WIDTH  ) - TOUCH_OFFSET_X;
      ypx = ( ((SCREEN_HEIGHT-60) * y) / TOUCH_HEIGHT ) - TOUCH_OFFSET_Y;
      z1 = touchRead(TSC_MEASURE_Z1);
      z2 = touchRead(TSC_MEASURE_Z2);

      if ( (XKEYS & 0x40) || (y == 0x7FF) || abs(xpx-OLD_X_PX)>40 || abs(ypx-OLD_Y_PX)>40 ) {
        but |= IPC_PEN_DOWN;
      }

      OLD_X_PX = xpx;
      OLD_Y_PX = ypx;
    }

    
    batt = touchRead(TSC_MEASURE_BATTERY);
    aux  = touchRead(TSC_MEASURE_AUX);

    // Read the time
    rtcGetTime((uint8 *)ct);
    BCDToInteger((uint8 *)&(ct[1]), 7);
 
    // Read the temperature
    temp = touchReadTemperature(&t1, &t2);
 
    // Update the IPC struct
    IPC->heartbeat = heartbeat;
    IPC->buttons   = but;
    IPC->touchX    = x;
    IPC->touchY    = y;
    IPC->touchXpx  = xpx;
    IPC->touchYpx  = ypx;
    IPC->touchZ1   = z1;
    IPC->touchZ2   = z2;
    IPC->battery   = batt;
    IPC->aux       = aux;

    for(i=0; i<sizeof(ct); i++) {
      IPC->curtime[i] = ct[i];
    }

    IPC->temperature = temp;
    IPC->tdiode1 = t1;
    IPC->tdiode2 = t2;


    //sound code  :)
    TransferSound *snd = IPC->soundData;
    IPC->soundData = 0;
    if (snd) {
      for (i=0; i<snd->count; i++) {
        s8 chan = getFreeSoundChannel();
        if (chan >= 0) {
          startSound(snd->data[i].rate, snd->data[i].data, snd->data[i].len, chan, snd->data[i].vol, snd->data[i].pan, snd->data[i].format);
        }
      }
    }

  }
 
  // Acknowledge interrupts
  IF = IF;
}
 

//////////////////////////////////////////////////////////////////////
 

int main(int argc, char ** argv) {
  TOUCH_WIDTH  = TOUCH_CAL_X2 - TOUCH_CAL_X1;
  TOUCH_HEIGHT = TOUCH_CAL_Y2 - TOUCH_CAL_Y1;
  TOUCH_OFFSET_X = ( ((SCREEN_WIDTH -60) * TOUCH_CAL_X1) / TOUCH_WIDTH  ) - 28;
  TOUCH_OFFSET_Y = ( ((SCREEN_HEIGHT-60) * TOUCH_CAL_Y1) / TOUCH_HEIGHT ) - 28;
//  TOUCH_WIDTH  = PersonalData->calX2 - PersonalData->calX1; //TOUCH_CAL_X2 - TOUCH_CAL_X1;
//  TOUCH_HEIGHT = PersonalData->calY2 - PersonalData->calY1; //TOUCH_CAL_Y2 - TOUCH_CAL_Y1;
//  TOUCH_OFFSET_X = ( ((SCREEN_WIDTH -60) * PersonalData->calX1) / TOUCH_WIDTH  ) - 28;
//  TOUCH_OFFSET_Y = ( ((SCREEN_HEIGHT-60) * PersonalData->calY1) / TOUCH_HEIGHT ) - 28;

  OLD_X_PX = 0;
  OLD_Y_PX = 0;

  // Reset the clock if needed
  rtcReset();


  //enable sound
  SOUND_CR = SOUND_ENABLE | SOUND_VOL(0x7F);
  IPC->soundData = 0;

  LOADNDS->PATH = 0;

  // Set up the interrupt handler
  IME = 0;
  IRQ_HANDLER = &InterruptHandler;
  IE = IRQ_VBLANK;
  IF = ~0;
  DISP_SR = DISP_VBLANK_IRQ;
  IME = 1;

  // Keep the ARM7 out of main RAM
  while (1) {
//    swiWaitForVBlank();
    WaitForVblank();
  }
  return 0;
}

 
//////////////////////////////////////////////////////////////////////

