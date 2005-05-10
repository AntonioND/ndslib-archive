//////////////////////////////////////////////////////////////////////
//
// ipcSound.h -- Inter-processor communication
//
// version 0.1, May 10, 2005
//
//  Copyright (C) 2005 Michael Noland (joat) and Jason Rogers (dovoto)
//
//  This software is provided 'as-is', without any express or implied
//  warranty.  In no event will the authors be held liable for any
//  damages arising from the use of this software.
//
//  Permission is granted to anyone to use this software for any
//  purpose, including commercial applications, and to alter it and
//  redistribute it freely, subject to the following restrictions:
//
//  1. The origin of this software must not be misrepresented; you
//     must not claim that you wrote the original software. If you use
//     this software in a product, an acknowledgment in the product
//     documentation would be appreciated but is not required.
//  2. Altered source versions must be plainly marked as such, and
//     must not be misrepresented as being the original software.
//  3. This notice may not be removed or altered from any source
//     distribution.
//
// Changelog:
//   0.1: First version
//
//////////////////////////////////////////////////////////////////////

#ifndef NDS_IPC_SOUND_INCLUDE
#define NDS_IPC_SOUND_INCLUDE

//////////////////////////////////////////////////////////////////////

#include <NDS/jtypes.h>

//////////////////////////////////////////////////////////////////////

 
typedef struct sTransferSoundData {
  const void *data;
  u32 len;
  u32 rate;
  u8 vol;
  u8 pan;
  u8 format;
  u8 PADDING[1];
} TransferSoundData, * pTransferSoundData;


typedef struct sTransferSound {
  u8 count;
  u8 PADDING[3];
  TransferSoundData data[16];
} TransferSound, * pTransferSound;


#endif //NDS_IPC_SOUND_INCLUDE
