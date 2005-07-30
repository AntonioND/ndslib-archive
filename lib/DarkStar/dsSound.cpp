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
#include <NDS/DarkStar/dsSound.h>


vList<dsSound*> dsSound::sounds;
TransferSound *dsSound::ipcdata = 0;


dsSound::dsSound(const void *data, u32 len, u32 rate, u8 vol, u8 pan, u8 format) {
  if (ipcdata == 0) ipcdata = (TransferSound*)malloc(sizeof(TransferSound));
  soundData.data    = data;
  soundData.len     = len;
  soundData.rate    = rate;
  soundData.vol     = vol;
  soundData.pan     = pan;
  soundData.format  = format;
  sounds.appendItem(this);
}


dsSound::~dsSound() {
  sounds.removeItem(this);
}


void dsSound::updateIpcSound() {
  if (sounds.getItemCount() == 0) return;
  ipcdata->count = min(sounds.getItemCount(), 16);

  for (int i=0; i<ipcdata->count; i++) {
    dsSound *snd = sounds.getItem(i);
    ipcdata->data[i] = snd->soundData;
  }

  IPC->soundData = ipcdata;
  DC_FlushAll();

  dsSound *snd = sounds.getFirstItem();
  while (snd) {
    delete snd;
    snd = sounds.getFirstItem();
  }
/*
  for (int i=sounds.getItemCount()-1; i>=0; i++) {
    dsSound *snd = sounds.getItem(i);
    delete snd;
  }
*/
}
