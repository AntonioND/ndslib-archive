/*****************************  DARKSTAR  ******************************\
*  Copyright (c) 2005 Vincent E. Milum Jr., All rights reserved.        *
*                                                                       *
*  See License.txt for more information                                 *
*                                                                       *
*  Latest source versions can be found at:  HTTP://WWW.DARKAIN.COM/     *
\***********************************************************************/



#define GUIVERSION 0x20050730



extern void enumTools();

extern s32 TOUCH_WIDTH;
extern s32 TOUCH_HEIGHT;
extern s32 TOUCH_OFFSET_X;
extern s32 TOUCH_OFFSET_Y;



inline void CODE_IN_IWRAM WaitForVblank() {
	while(DISP_Y!=191);
	while(DISP_Y==191);
}
