//////////////////////////////////////////////////////////////////////
//
// videoGL.h -- Video API vaguely similar to OpenGL
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

#ifndef VIDEOGL_ARM9_INCLUDE
#define VIDEOGL_ARM9_INCLUDE

//////////////////////////////////////////////////////////////////////

#ifndef ARM9
#error 3D hardware is only available from the ARM9
#endif

//////////////////////////////////////////////////////////////////////

#include <NDS/jtypes.h>
#include <NDS/ARM9/video.h>

//////////////////////////////////////////////////////////////////////

typedef int f32;             // 20.12 fixed point for matricies
#define intof32(n)           ((n) << 12)
#define f32toint(n)          ((n) >> 12)
#define floatof32(n)         ((f32)((n) * (1 << 12)))

typedef short int t16;       // text coordinate 12.4 fixed point
#define intot16(n)           ((n) << 4)
#define t16toint(n)          ((n) >> 4)
#define floatot16(n)         ((t16)((n) * (1 << 4)))
#define TEXTURE_PACK(u,v)    ((intot16(u)<<16) | intot16(v))

typedef short int v16;       // vertex 4.12 fixed format
#define intov16(n)           ((n) << 12)
#define v16toint(n)          ((n) >> 12)
#define floatov16(n)         ((v16)((n) * (1 << 12)))

typedef short int v10;       // vertex 4.6 fixed point
#define intov10(n)           ((n) << 9)
#define v10toint(n)          ((n) >> 9)
#define floatov10(n)         ((v10)((n) * (1 << 9)))
#define NORMAL_PACK(x,y,z)   (intov10(x) | (intov10(y) << 10) | (intov10(z) << 20))

typedef unsigned short rgb;

typedef struct {
  f32 m[9];
} m3x3;

typedef struct {
  f32 m[16];
} m4x4;

typedef struct {
  f32 m[12];
} m4x3;

typedef struct {
  f32 x,y,z;
} vector;

//////////////////////////////////////////////////////////////////////

#define GL_TRIANGLE        0
#define GL_QUAD            1
#define GL_TRIANGLE_STRIP  2
#define GL_QUAD_STRIP      3

#define GL_MODELVIEW       2
#define GL_PROJECTION      0
#define GL_TEXTURE         3

#define GL_AMBIENT              1
#define GL_DIFFUSE              2
#define GL_AMBIENT_AND_DIFFUSE  3
#define GL_SPECULAR             4
#define GL_SHININESS            8
#define GL_EMISSION             10

//////////////////////////////////////////////////////////////////////

#define POLY_ALPHA(n)  ((n) << 16)
#define POLY_CULL_BACK        0x80
#define POLY_CULL_FRONT       0x40
#define POLY_CULL_NONE        0xC0

//////////////////////////////////////////////////////////////////////

#define POLY_FORMAT_LIGHT0      0x1
#define POLY_FORMAT_LIGHT1      0x2
#define POLY_FORMAT_LIGHT2      0x4
#define POLY_FORMAT_LIGHT3      0x8

//////////////////////////////////////////////////////////////////////

#define TEXTURE_SIZE_8     0
#define TEXTURE_SIZE_16    1
#define TEXTURE_SIZE_32    2
#define TEXTURE_SIZE_64    3
#define TEXTURE_SIZE_128   4
#define TEXTURE_SIZE_256   5
#define TEXTURE_SIZE_512   6
#define TEXTURE_SIZE_1024  7 

//////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
extern "C" {
#endif
/*
void glBegin(int mode);
void glEnd(void);
void glClearColor(uint8 red, uint8 green, uint8 blue);
void glClearDepth(uint16 depth);
void glColor3b(uint8 red, uint8 green, uint8 blue);
void glColor(rgb color);
void glTextCoord2t16(t16 u, t16 v);
void glVertex3v16(v16 x, v16 y, v16 z);
void glVertex2v16(int yx,  v16 z);
void glFlush(void);
void glReset(void);
void glMaterialf(int mode, rgb color);
void glLight(int id, rgb color, v10 x, v10 y, v10 z);
void glNormal(uint32 normal);
void glViewPort(uint8 x1, uint8 y1, uint8 x2, uint8 y2);
void glResetMatrixStack(void);
void glPushMatrix(void);
void glPopMatrix(int32 index);
void glRestoreMatrix(int32 index);
void glStoreMatrix(int32 index);
void glScalev(vector* v);
void glTranslatev(vector* v);
void glTranslate3f32(f32 x, f32 y, f32 z);
void glScalef32(f32 s);
void glTranslatef32(f32 delta);
void glIdentity(void);
void glMatrixMode(int mode);
*/

//////////////////////////////////////////////////////////////////////

void glLoadMatrix4x4(m4x4 * m);
void glLoadMatrix4x3(m4x3 * m);
void glMultMatrix4x4(m4x4 * m);
void glMultMatrix4x3(m4x3 * m);
void glMultMatrix3x3(m3x3 * m);
void glRotateX(float angle);
void glRotateY(float angle);
void glRotateZ(float angle);

//////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
}
#endif

//////////////////////////////////////////////////////////////////////

inline extern void glBegin(int mode)
{
  GFX_BEGIN = mode;
}

//////////////////////////////////////////////////////////////////////

inline extern void glEnd( void)
{
  GFX_END = 0;
}

//////////////////////////////////////////////////////////////////////

inline extern void glClearColor(uint8 red, uint8 green, uint8 blue)
{
  GFX_CLEAR_COLOR = RGB15(red, green, blue);
}

//////////////////////////////////////////////////////////////////////

inline extern void glClearDepth(uint16 depth)
{
  GFX_CLEAR_DEPTH = depth;
}

//////////////////////////////////////////////////////////////////////

inline extern void glColor3ub(uint8 red, uint8 green, uint8 blue)
{
  GFX_COLOR = (vuint32)RGB15(red, green, blue);
}

//////////////////////////////////////////////////////////////////////

inline extern void glColor(rgb color)
{
  GFX_COLOR = (vuint32)color;
}

//////////////////////////////////////////////////////////////////////

inline extern void glVertex3v16(v16 x, v16 y, v16 z)
{
  GFX_VERTEX16 = (y << 16) | (x & 0xFFFF);
  GFX_VERTEX16 = ((uint32)(uint16)z);
}

//////////////////////////////////////////////////////////////////////

inline extern void glVertex2v16(int yx, v16 z)
{
  GFX_VERTEX16 = yx;
  GFX_VERTEX16 = (z);
}

//////////////////////////////////////////////////////////////////////

inline extern void glTexCoord2t16(t16 u, t16 v)
{
  GFX_TEX_COORD = (u << 16) + v;
}

//////////////////////////////////////////////////////////////////////

inline extern void glTexCoord1i(uint32 uv)
{
  GFX_TEX_COORD = uv;
}

//////////////////////////////////////////////////////////////////////

inline extern void glPushMatrix(void)
{
  MATRIX_PUSH = 0;
}

//////////////////////////////////////////////////////////////////////

inline extern void glPopMatrix(int32 index)
{
  MATRIX_POP = index;
}

//////////////////////////////////////////////////////////////////////

inline extern void glRestoreMatrix(int32 index)
{
  MATRIX_RESTORE = index;
}

//////////////////////////////////////////////////////////////////////

inline extern void glStoreMatrix(int32 index)
{
  MATRIX_STORE = index;
}

//////////////////////////////////////////////////////////////////////

inline extern void glScalev(vector* v)
{
  MATRIX_SCALE = v->x;
  MATRIX_SCALE = v->y;
  MATRIX_SCALE = v->z;
}

//////////////////////////////////////////////////////////////////////

inline extern void glTranslatev(vector* v)
{
  MATRIX_TRANSLATE = v->x;
  MATRIX_TRANSLATE = v->y;
  MATRIX_TRANSLATE = v->z;
}

//////////////////////////////////////////////////////////////////////

inline extern void glTranslate3f32(f32 x, f32 y, f32 z)
{
  MATRIX_TRANSLATE = x;
  MATRIX_TRANSLATE = y;
  MATRIX_TRANSLATE = z;
}

//////////////////////////////////////////////////////////////////////

inline extern void glScalef32(f32 factor)
{
  MATRIX_SCALE = factor;
  MATRIX_SCALE = factor;
  MATRIX_SCALE = factor;
}

//////////////////////////////////////////////////////////////////////

inline extern void glTranslatef32(f32 delta)
{
  MATRIX_TRANSLATE = delta;
  MATRIX_TRANSLATE = delta;
  MATRIX_TRANSLATE = delta;
}

//////////////////////////////////////////////////////////////////////

inline extern void glLight(int id, rgb color, v10 x, v10 y, v10 z)
{
  id = (id & 3) << 30;
  GFX_LIGHT_VECTOR = id | ((z & 0x3FF) << 20) | ((y & 0x3FF) << 10) | (x & 0x3FF);
  GFX_LIGHT_COLOR = id | color;
}

//////////////////////////////////////////////////////////////////////

inline extern void glNormal(uint32 normal)
{
  GFX_NORMAL = normal;
}

//////////////////////////////////////////////////////////////////////

inline extern void glIdentity(void)
{
  MATRIX_IDENTITY = 0;
}

//////////////////////////////////////////////////////////////////////

inline extern void glMatrixMode(int mode)
{
  MATRIX_CONTROL = mode;
}

//////////////////////////////////////////////////////////////////////

inline extern void glViewPort(uint8 x1, uint8 y1, uint8 x2, uint8 y2)
{
  GFX_VIEWPORT = (x1) + (y1 << 8) + (x2 << 16) + (y2 << 24);
}

//////////////////////////////////////////////////////////////////////

inline extern void glFlush(void)
{
  GFX_FLUSH = 2;
}

//////////////////////////////////////////////////////////////////////

inline extern void glMaterialf(int mode, rgb color)
{
  static uint32 diffuse_ambient = 0;
  static uint32 specular_emission = 0;

  switch(mode) {
    case GL_AMBIENT:
      diffuse_ambient = (color << 16) | (diffuse_ambient & 0xFFFF);
      break;
    case GL_DIFFUSE:
      diffuse_ambient = color | (diffuse_ambient & 0xFFFF0000);
      break;
    case GL_AMBIENT_AND_DIFFUSE:
      diffuse_ambient= color + (color << 16);
      break;
    case GL_SPECULAR:
      specular_emission = color | (specular_emission & 0xFFFF0000);
      break;
    case GL_SHININESS:
      break;
    case GL_EMISSION:
      specular_emission = (color << 16) | (specular_emission & 0xFFFF);
      break;
  }
  
  GFX_DIFFUSE_AMBIENT = diffuse_ambient;
  GFX_SPECULAR_EMISSION = specular_emission;
}

//////////////////////////////////////////////////////////////////////

inline extern void glResetMatrixStack(void)
{
  // stack overflow ack ?
  GFX_STATUS |= 1 << 15;

  // pop the stacks to the top...seems projection stack is only 1 deep??
  glMatrixMode(GL_PROJECTION);
  glPopMatrix(GFX_STATUS & (1<<13));
  
  // 31 deep modelview matrix
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix(GFX_STATUS & (0x1F << 8));
}

//////////////////////////////////////////////////////////////////////

inline extern void glReset(void)
{
  while (GFX_STATUS & (1<<27)); // wait till gfx engine is not busy
  
  // Clear the FIFO
  GFX_STATUS |= (1<<29);

  // Clear overflows for list memory
  GFX_CONTROL |= ((1<<12) | (1<<13)) | 3;
  glResetMatrixStack();

  glMatrixMode(GL_PROJECTION);
  glIdentity();

  glMatrixMode(GL_MODELVIEW);
  glIdentity();
}

//////////////////////////////////////////////////////////////////////

inline extern void glPolyFmt(int alpha) // obviously more to this
{
  GFX_POLY_FORMAT = alpha;// << 16;
}

//////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////
