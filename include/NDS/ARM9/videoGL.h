////////////////////////////////////////////////////////////////////
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
//   0.2: Added gluFrustrum, gluPerspective, and gluLookAt
//			Converted all floating point math to fixed point
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

typedef int f32;             // 1.19.12 fixed point for matricies
#define intof32(n)           ((n) << 12)
#define f32toint(n)          ((n) >> 12)
#define floatof32(n)         ((f32)((n) * (1 << 12)))
#define f32tofloat(n)        (((float)(n)) / (float)(1<<12))

typedef short int t16;       // text coordinate 1.11.4 fixed point
#define intot16(n)           ((n) << 4)
#define t16toint(n)          ((n) >> 4)
#define floatot16(n)         ((t16)((n) * (1 << 4)))
#define TEXTURE_PACK(u,v)    ((intot16(u)<<16) | intot16(v))

typedef short int v16;       // vertex 1.3.12 fixed format
#define intov16(n)           ((n) << 12)
#define v16toint(n)          ((n) >> 12)
#define floatov16(n)         ((v16)((n) * (1 << 12)))

typedef short int v10;       // vertex 1.0.9 fixed point
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
#define MAX_TEXTURES 2048  //this should be enough ! but feel free to change

#define TEXTURE_SIZE_8     0
#define TEXTURE_SIZE_16    1 
#define TEXTURE_SIZE_32    2
#define TEXTURE_SIZE_64    3
#define TEXTURE_SIZE_128   4
#define TEXTURE_SIZE_256   5
#define TEXTURE_SIZE_512   6
#define TEXTURE_SIZE_1024  7 

//////////////////////////////////////////////////////////////////////

#define GL_TEXTURE_WRAP_S (1 << 16)
#define GL_TEXTURE_WRAP_T (1 << 17)
#define GL_TEXTURE_FLIP_S (1 << 18)
#define GL_TEXTURE_FLIP_T (1 << 19)

#define GL_TEXTURE_2D		1

//////////////////////////////////////////////////////////////////////

#define GL_RGB		8
#define GL_RGBA		7	//15 bit color + alpha bit
#define GL_RGB4		2	//4 color palette
#define GL_RGB256	3	//256 color palette
#define GL_RGB16	4	//16 color palette
#define GL_COMPRESSED	5 //compressed texture

//////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
extern "C" {
#endif


//////////////////////////////////////////////////////////////////////

void glLoadMatrix4x4(m4x4 * m);
void glLoadMatrix4x3(m4x3 * m);
void glMultMatrix4x4(m4x4 * m);
void glMultMatrix4x3(m4x3 * m);
void glMultMatrix3x3(m3x3 * m);
void glRotateXi(int angle);
void glRotateYi(int angle);
void glRotateZi(int angle);
void glRotateX(float angle);
void glRotateY(float angle);
void glRotateZ(float angle);
void gluLookAtf32(f32 eyex, f32 eyey, f32 eyez, f32 lookAtx, f32 lookAty, f32 lookAtz, f32 upx, f32 upy, f32 upz);
void gluLookAt(float eyex, float eyey, float eyez, float lookAtx, float lookAty, float lookAtz, float upx, float upy, float upz);
void gluFrustumf32(f32 left, f32 right, f32 bottom, f32 top, f32 near, f32 far);
void gluFrustum(float left, float right, float bottom, float top, float near, float far);
void gluPerspectivef32(int fovy, f32 aspect, f32 zNear, f32 zFar);
void gluPerspective(float fovy, float aspect, float zNear, float zFar);
int glTexImage2D(int target, int empty1, int type, int sizeX, int sizeY, int empty2, int param, uint8* texture);
void glBindTexture(int target, int name);
int glGenTextures(int n, int *names);
void glResetTextures(void);
void glMaterialf(int mode, rgb color);
void glResetMatrixStack(void);
void glReset(void);
//////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////

  void glBegin(int mode);


//////////////////////////////////////////////////////////////////////

  void glEnd( void);

//////////////////////////////////////////////////////////////////////

  void glClearColor(uint8 red, uint8 green, uint8 blue);

//////////////////////////////////////////////////////////////////////

  void glClearDepth(uint16 depth);


//////////////////////////////////////////////////////////////////////

  void glColor3b(uint8 red, uint8 green, uint8 blue);


//////////////////////////////////////////////////////////////////////

  void glColor(rgb color);

//////////////////////////////////////////////////////////////////////

  void glVertex3v16(v16 x, v16 y, v16 z);


//////////////////////////////////////////////////////////////////////

  void glVertex2v16(int yx, v16 z);

//////////////////////////////////////////////////////////////////////

  void glTexCoord2t16(t16 u, t16 v);


//////////////////////////////////////////////////////////////////////

  void glTexCoord1i(uint32 uv);

//////////////////////////////////////////////////////////////////////

  void glPushMatrix(void);


//////////////////////////////////////////////////////////////////////

  void glPopMatrix(int32 index);


//////////////////////////////////////////////////////////////////////

  void glRestoreMatrix(int32 index);

//////////////////////////////////////////////////////////////////////

  void glStoreMatrix(int32 index);


//////////////////////////////////////////////////////////////////////

  void glScalev(vector* v);


//////////////////////////////////////////////////////////////////////

  void glTranslatev(vector* v);


//////////////////////////////////////////////////////////////////////

  void glTranslate3f32(f32 x, f32 y, f32 z);

//////////////////////////////////////////////////////////////////////

  void glScalef32(f32 factor);


//////////////////////////////////////////////////////////////////////

  void glTranslatef32(f32 delta);

//////////////////////////////////////////////////////////////////////

  void glLight(int id, rgb color, v10 x, v10 y, v10 z);

//////////////////////////////////////////////////////////////////////

  void glNormal(uint32 normal);

//////////////////////////////////////////////////////////////////////

  void glIdentity(void);


//////////////////////////////////////////////////////////////////////

  void glMatrixMode(int mode);

//////////////////////////////////////////////////////////////////////

  void glViewPort(uint8 x1, uint8 y1, uint8 x2, uint8 y2);
/////////////////////////////////////////////////////////////////////

  void glFlush(void);

//////////////////////////////////////////////////////////////////////
void glMaterialShinnyness(void);

//////////////////////////////////////////////////////////////////////

  void glPolyFmt(int alpha); 

//////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif

#endif

//////////////////////////////////////////////////////////////////////
