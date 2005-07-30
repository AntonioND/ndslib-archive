/*****************************  DARKSTAR  ******************************\
*  Copyright (c) 2005 Vincent E. Milum Jr., All rights reserved.        *
*                                                                       *
*  See License.txt for more information                                 *
*                                                                       *
*  Latest source versions can be found at:  HTTP://WWW.DARKAIN.COM/     *
\***********************************************************************/


#ifndef _DS_SPRITE_MANAGER_H_
#define _DS_SPRITE_MANAGER_H_


class dsSpriteManager;
extern dsSpriteManager *sprmgr;


typedef enum
{
  DS_CORE_MAIN = 0,
  DS_CORE_SUB  = 1,
} DS_CORE;


class dsSpriteManager {
	public:
		dsSpriteManager(bool clear=true);
    ~dsSpriteManager();

    u8 allocSprite(DS_CORE core);
    void freeSprite(DS_CORE core, u8 sprite);

    u16 allocSpriteMem(DS_CORE core, u16 size);
    void freeSpriteMem(DS_CORE core, u16 tile, u16 size);

    void updateSystemOAM();
    void updateLocalOAM();

    inline u16 *getOAM()      { return  oam; }
    inline u16 *getOAM(u8 id) { return &oam[id<<2]; }

		inline void *spriteDebug1() { return spriteAlloc; }
		inline void *spriteDebug2() { return data; }
		inline void *spriteDebug3() { return oam; }

	private:
		u8 spriteAlloc[2][128];		//128 sprites total
		u8 data[2][1024];
//		u8 rotationAlloc;			//8 rotation entreries

    u16 oam[256*4];  //OAM copy in RAM
};


#endif //_DS_SPRITE_MANAGER_H_
