//////////////////////////////////////////////////////////////////////
//
// jtypes.h -- Common types (and a few useful macros)
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

#ifndef NDS_JTYPES_INCLUDE
#define NDS_JTYPES_INCLUDE

//////////////////////////////////////////////////////////////////////

#define CODE_IN_IWRAM __attribute__ ((section (".iwram"), long_call))
#define VAR_IN_IWRAM __attribute__ ((section (".iwram")))
#define CODE_IN_EXRAM __attribute__ ((section (".ewram"), long_call))
#define VAR_IN_EXRAM __attribute__ ((section (".ewram")))
#define PACKED __attribute__ ((packed))
  
// These are linked to the bin2o macro in the Makefile
#define GETRAW(name)      (name)
#define GETRAWSIZE(name)  ((int)name##_end - (int)name)

#define ASSERT(arg) 

//////////////////////////////////////////////////////////////////////

typedef unsigned char           uint8;
typedef unsigned short int      uint16;
typedef unsigned int            uint32;
typedef unsigned long long int  uint64;

typedef signed char             int8;
typedef signed short int        int16;
typedef signed int              int32;
typedef signed long long int    int64;

typedef float                   float32;
typedef double                  float64;

typedef volatile uint8          vuint8;
typedef volatile uint16         vuint16;
typedef volatile uint32         vuint32;
typedef volatile uint64         vuint64;

typedef volatile int8           vint8;
typedef volatile int16          vint16;
typedef volatile int32          vint32;
typedef volatile int64          vint64;

typedef volatile float32        vfloat32;
typedef volatile float64        vfloat64;

typedef uint8                   byte;

typedef int32                   fixed;
typedef int64                   dfixed;

typedef volatile int32          vfixed;

//////////////////////////////////////////////////////////////////////

typedef void (* VoidFunctionPointer)(void);

//////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////
