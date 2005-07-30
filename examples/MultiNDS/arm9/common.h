/*****************************  DARKSTAR  ******************************\
*  Copyright (c) 2005 Vincent E. Milum Jr., All rights reserved.        *
*                                                                       *
*  See License.txt for more information                                 *
*                                                                       *
*  Latest source versions can be found at:  HTTP://WWW.DARKAIN.COM/     *
\***********************************************************************/


#ifndef _COMMON_H_
#define _COMMON_H_


char *itoa(int val, char *buffer);
void print(const char *text);
void print16(u16 *text);
void printmem(u32 addr, u8 size);
void initDebug();

extern vu32 *DEBUG0;
extern vu32 *DEBUG1;
extern vu32 *DEBUG2;
extern vu32 *DEBUG3;


#define RGB(r,g,b)  ((r)+((g)<<5)+((b)<<10))
#define BGR(b,g,r)  ((r)+((g)<<5)+((b)<<10))
#define RGB16(r,g,b)  ((r)+((g)<<5)+((b)<<10)+0x8000)
#define BGR16(b,g,r)  ((r)+((g)<<5)+((b)<<10)+0x8000)

#define REDMASK   (0x7C00)
#define GREENMASK (0x03E0)
#define BLUEMASK  (0x001F)
#define ALPHAMASK (0x8000)
#define EXTENDEDMASK (0xF8000)

#define RGBRED(c)   (((c)>> 0) & 0x001F)
#define RGBGREEN(c) (((c)>> 5) & 0x001F)
#define RGBBLUE(c)  (((c)>>10) & 0x001F)

#define WHITE RGB(31,31,31)
#define BLACK RGB(0,0,0)


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


template<class T> inline void swap(T a, T b) {
  T tmp = a;
  a = b;
  b = tmp;
}


extern u32 seed; 

inline signed long dice(signed long min, signed long max)  { 
	seed *= 69069; 
	return min + (((max - min + 1) * (seed >> 16)) >> 16); 
} 


packed_struct PERSONAL_DATA {
  u8  RESERVED0[2];           //0x023FFC80  05 00 ?

  u8  theme;                  //0x027FFC82  favorite color (0-15)
  u8  birthMonth;             //0x027FFC83  birthday month (1-12)
  u8  birthDay;               //0x027FFC84  birthday day (1-31)

  u8  RESERVED1[1];           //0x027FFC85  ???

  s16 name[10];               //0x027FFC86  name, UTF-16?
  u16 nameLen;                //0x027FFC9A  length of name in characters

  s16 message[26];            //0x027FFC9C  message, UTF-16?
  u16 messageLen;             //0x027FFCD0  length of message in characters

  u8  alarmHour;              //0x027FFCD2  alarm hour
  u8  alarmMinute;            //0x027FFCD3  alarm minute

  u8  RESERVED2[4];           //0x027FFCD4  ??


  //calibration information
  u16 calX1;                  //0x027FFCD8
  u16 calY1;                  //0x027FFCDA
  u8  calX1px;                //0x027FFCDC
  u8  calY1px;                //0x027FFCDD

  u16 calX2;                  //0x027FFCDE
  u16 calY2;                  //0x027FFCE0
  u8  calX2px;                //0x027FFCE2
  u8  calY2px;                //0x027FFCE3

  packed_struct {             //0x027FFCE4
    unsigned language    : 3; //            language
    unsigned gbaScreen   : 1; //            GBA mode screen selection. 0=upper, 1=lower
    unsigned RESERVED3   : 2; //            ??
    unsigned autoMode    : 1; //            auto/manual mode. 0=manual, 1=auto
    unsigned RESERVED4   : 1; //            ??
  };
};

extern PERSONAL_DATA *personal;



#endif //_COMMON_H_
