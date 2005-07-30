/***************************  VBASE SDK  *******************************\
*  Copyright (c) 2005 Vincent E. Milum Jr., All rights reserved.        *
*                                                                       *
*  See License.txt for more information                                 *
*                                                                       *
*  Latest SDK versions can be found at:  HTTP://www.Darkain.com         *
\***********************************************************************/


#ifndef _V_TYPES_H_
#define _V_TYPES_H_


#include <string.h>



#ifndef FALSE
#define FALSE   0
#endif

#ifndef TRUE
#define TRUE    1
#endif

#ifndef NULL
#define NULL    0
#endif


#ifndef BOOL
typedef int      BOOL;
#endif


#ifndef VOID
#define VOID void
typedef char            CHAR;
typedef unsigned char   BYTE;
typedef short           SHORT;
typedef unsigned short  WORD;
typedef int             INT;
typedef unsigned int    UINT;
typedef long            LONG;
typedef unsigned long   DWORD;
//typedef DWORD          *DWORD_PTR;

#define MAKEWORD(a, b)  ((WORD)(((BYTE)((DWORD_PTR)(a) & 0xff)) | ((WORD)((BYTE)((DWORD_PTR)(b) & 0xff))) << 8))
#define MAKELONG(a, b)  ((LONG)(((WORD)((DWORD_PTR)(a) & 0xffff)) | ((DWORD)((WORD)((DWORD_PTR)(b) & 0xffff))) << 16))
#define LOWORD(l)       ((WORD)((DWORD_PTR)(l) & 0xffff))
#define HIWORD(l)       ((WORD)((DWORD_PTR)(l) >> 16))
#define LOBYTE(w)       ((BYTE)((DWORD_PTR)(w) & 0xff))
#define HIBYTE(w)       ((BYTE)((DWORD_PTR)(w) >> 8))
#endif



#ifndef max
#define max(a, b)  (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a, b)  (((a) < (b)) ? (a) : (b))
#endif

#ifndef abs
#define abs(a)  ((a) < (0) ? -(a) : (a))
#endif


#define ALIGN4 __attribute__((aligned(4)))
#define ALIGN2 __attribute__((aligned(2)))
//#define ALIGN ALIGN4

#define PACK __attribute__((packed))
//#define packed_struct struct PACK
#define packed_union union PACK



/*
typedef unsigned char  byte;
typedef unsigned short hword;
typedef unsigned long  word;

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned long  u32;

typedef signed char  s8;
typedef signed short s16;
typedef signed long  s32;

typedef volatile unsigned char  vu8;
typedef volatile unsigned short vu16;
typedef volatile unsigned long  vu32;

typedef volatile signed char  vs8;
typedef volatile signed short vs16;
typedef volatile signed long  vs32;

typedef unsigned char  *pu8;
typedef unsigned short *pu16;
typedef unsigned long  *pu32;

typedef signed char  *ps8;
typedef signed short *ps16;
typedef signed long  *ps32;

typedef const unsigned char  const_u8;
typedef const unsigned short const_u16;
typedef const unsigned long  const_u32;
*/

//#define FIXED s32
#define PI 3.14159

//#define BIT(n) (1<<(n))

//static char NULLCHAR[1] = "";

#ifndef vZeroMemory
#define vZeroMemory(Destination,Length) memset((Destination),0,(Length))
#endif

#ifndef PlaylistHandle
typedef unsigned long PlaylistHandle;
#define INVALID_PLAYLIST_HANDLE ((PlaylistHandle)-1)
#endif

#ifndef PlaylistItem
typedef unsigned long PlaylistItem;
#define INVALID_PLAYLIST_ITEM ((PlaylistItem)-1)
#endif


#define vdelnull(x) delete x; x=NULL
#define vrelease(x) if(x) x->Release(); x=NULL
#define vrestore(x) if(x) x->Restore()


#ifdef __cplusplus

#ifndef HPLUGIN

class vHPLUGIN;
typedef vHPLUGIN * HPLUGIN;
#define INVALID_PLUGIN_HANDLE ((HPLUGIN)0)

class vHCONSOLE;
typedef vHCONSOLE * HCONSOLE;
#define CONSOLE_MAIN ((HCONSOLE)-2)
#define CONSOLE_BROADCAST ((HCONSOLE)-1)
#define CONSOLE_ACTIVE ((HCONSOLE)0)

class vHSCRIPT;
typedef vHSCRIPT * HSCRIPT;

class vHLIST {};
typedef vHLIST * HLIST;

class vHPARAM {};
typedef vHPARAM * HPARAM;

class vHRMX {};
typedef vHRMX * HRMX;
#define ANY_APPLICATION_HANDLE ((HRMX)-1)

#endif //HPLUGIN

#endif //__cplusplus


typedef struct _MAC {
  unsigned char  Data1;
  unsigned char  Data2;
  unsigned char  Data3;
  unsigned char  Data4;
  unsigned char  Data5;
  unsigned char  Data6;
} MAC;

//static MAC INVALID_MAC_ADDRESS = { 0, 0, 0, 0, 0, 0 };


#endif //_V_TYPES_H_
