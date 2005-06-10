//////////////////////////////////////////////////////////////////////
//
// keys.h -- provides slightly higher level input forming
//
//  Contributed by DesktopMA
//
// version 0.1, February 14, 2005
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
//
//////////////////////////////////////////////////////////////////////

//---------------------------------------------------------------------------------
#ifndef	_keys_h_
#define	_keys_h_
//---------------------------------------------------------------------------------

#include <NDS/NDS.h>

#define KEY_TOUCH (1<<12)
#define KEY_X (1<<10)
#define KEY_Y (1<<11)

void scanKeys();
void keysInit();
u32 keysHeld();
u32 keysDown();
u32 keysUp();

#define KEYS_CUR ( ((~KEYS)&0x3ff) | (((~IPC->buttons)&3)<<10) | (((~IPC->buttons)<<6) & KEY_TOUCH ))

//---------------------------------------------------------------------------------
#endif // _keys_h_
//---------------------------------------------------------------------------------