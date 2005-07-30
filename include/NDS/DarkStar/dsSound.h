/*****************************  DARKSTAR  ******************************\
*  Copyright (c) 2005 Vincent E. Milum Jr., All rights reserved.        *
*                                                                       *
*  See License.txt for more information                                 *
*                                                                       *
*  Latest source versions can be found at:  HTTP://WWW.DARKAIN.COM/     *
\***********************************************************************/


#ifndef _DS_SOUND_H_
#define _DS_SOUND_H_


//common includes
#include "vArray.h"
#include "vList.h"

//special DarkStar IPC include
//#include "../../dsIpc.h"


class dsSound {
  public:
    dsSound(const void *data, u32 len, u32 rate, u8 vol=0x7F, u8 pan=0x3F, u8 format=0);
    ~dsSound();


    static void updateIpcSound();

  private:
    TransferSoundData soundData;

  private:
    static vList<dsSound*> sounds;
    static TransferSound *ipcdata;
};


#endif //_DS_SOUND_H_
