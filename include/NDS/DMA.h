//////////////////////////////////////////////////////////////////////
//
// DMA.h -- Direct Memory Access channel control
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
//////////////////////////////////////////////////////////////////////

#ifndef NDS_DMA_INCLUDE
#define NDS_DMA_INCLUDE

//////////////////////////////////////////////////////////////////////
// DMA ///////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

#define DMA0_SRC       (*(vuint32*)0x040000B0)
#define DMA0_DEST      (*(vuint32*)0x040000B4)
#define DMA0_COUNT     (*(vuint16*)0x040000B8)
#define DMA0_CR        (*(vuint16*)0x040000BA)

#define DMA1_SRC       (*(vuint32*)0x040000BC)
#define DMA1_DEST      (*(vuint32*)0x040000C0)
#define DMA1_COUNT     (*(vuint16*)0x040000C4)
#define DMA1_CR        (*(vuint16*)0x040000C6)

#define DMA2_SRC       (*(vuint32*)0x040000C8)
#define DMA2_DEST      (*(vuint32*)0x040000CC)
#define DMA2_COUNT     (*(vuint16*)0x040000D0)
#define DMA2_CR        (*(vuint16*)0x040000D2)

#define DMA3_SRC       (*(vuint32*)0x040000D4)
#define DMA3_DEST      (*(vuint32*)0x040000D8)
#define DMA3_COUNT     (*(vuint16*)0x040000DC)
#define DMA3_CR        (*(vuint16*)0x040000DE)

#define DMA_SRC(n)     (*(vuint32*)(0x040000B0+(n*12)))
#define DMA_DEST(n)    (*(vuint32*)(0x040000B4+(n*12)))
#define DMA_COUNT(n)   (*(vuint16*)(0x040000B8+(n*12)))
#define DMA_CR(n)      (*(vuint16*)(0x040000BA+(n*12)))

//////////////////////////////////////////////////////////////////////

// DMA control register contents
// The defaults are 16-bit, increment source/dest addresses, no irq
#define DMA_ENABLE      (1<<15)
#define DMA_BUSY	    (1<<15)
#define DMA_IRQ_REQ     (1<<14)

#define DMA_START_NOW   (0<<12)

// fixme: is this arm7 only???
#define DMA_START_CARD  (2<<12)
#ifdef ARM7
#define DMA_START_VBL   (1<<12)
#endif

#ifdef ARM9
#define DMA_START_HBL   (2<<12)
#define DMA_START_VBL   (1<<12)
#endif

#define DMA_16_BIT      (0<<10)
#define DMA_32_BIT      (1<<10)


#define DMA_REPEAT      (1<<9)

#define DMA_SRC_INC     (0<<7)
#define DMA_SRC_DEC     (1<<7)
#define DMA_SRC_FIX     (2<<7)

#define DMA_DST_INC     (0<<5)
#define DMA_DST_DEC     (1<<5)
#define DMA_DST_FIX     (2<<5)
#define DMA_DST_RESET   (3<<5)

#define DMA_COPY_WORDS     (DMA_ENABLE | DMA_32_BIT | DMA_START_NOW)
#define DMA_COPY_HALFWORDS (DMA_ENABLE | DMA_16_BIT | DMA_START_NOW)

inline void dmaCopyWords(uint8 channel, uint32* src, uint32* dest, uint32 size)
{
	DMA_SRC(channel) = (uint32)src;
	DMA_DEST(channel) = (uint32)dest;
	DMA_COUNT(channel) = (uint16)(size>>2);
	DMA_CR(channel) = DMA_COPY_WORDS;
	while(DMA_CR(channel) & DMA_BUSY);
}
/*
inline int dmaBusy(uint8 channel)
{
	if (DMA_CR(channel) & DMA_BUSY) 
		return 1;
	else
		return 0;
}
*/
//////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////
