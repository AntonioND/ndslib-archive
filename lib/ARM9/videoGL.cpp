//////////////////////////////////////////////////////////////////////
//
// videoGL.cpp -- Video API vaguely similar to OpenGL
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
//   0.2: Added gluFrustrum, gluPerspective, and gluLookAt
//			Converted all floating point math to fixed point
//
//////////////////////////////////////////////////////////////////////

#include <NDS/ARM9/videoGL.h>
#include <NDS/ARM9/trig_lut.h>
#include <NDS/ARM9/math.h>

//lut resolution must be power of two
#define LUT_SIZE (512)
#define LUT_MASK (0x1FF)

//////////////////////////////////////////////////////////////////////

void glLoadMatrix4x4(m4x4 * m)
{
  MATRIX_LOAD4x4 = m->m[0];
  MATRIX_LOAD4x4 = m->m[1];
  MATRIX_LOAD4x4 = m->m[2];
  MATRIX_LOAD4x4 = m->m[3];

  MATRIX_LOAD4x4 = m->m[4];
  MATRIX_LOAD4x4 = m->m[5];
  MATRIX_LOAD4x4 = m->m[6];
  MATRIX_LOAD4x4 = m->m[7];

  MATRIX_LOAD4x4 = m->m[8];
  MATRIX_LOAD4x4 = m->m[9];
  MATRIX_LOAD4x4 = m->m[10];
  MATRIX_LOAD4x4 = m->m[11];

  MATRIX_LOAD4x4 = m->m[12];
  MATRIX_LOAD4x4 = m->m[13];
  MATRIX_LOAD4x4 = m->m[14];
  MATRIX_LOAD4x4 = m->m[15];
}

//////////////////////////////////////////////////////////////////////

void glLoadMatrix4x3(m4x3* m)
{
  MATRIX_LOAD4x3 = m->m[0];
  MATRIX_LOAD4x3 = m->m[1];
  MATRIX_LOAD4x3 = m->m[2];
  MATRIX_LOAD4x3 = m->m[3];

  MATRIX_LOAD4x3 = m->m[4];
  MATRIX_LOAD4x3 = m->m[5];
  MATRIX_LOAD4x3 = m->m[6];
  MATRIX_LOAD4x3 = m->m[7];

  MATRIX_LOAD4x3 = m->m[8];
  MATRIX_LOAD4x3 = m->m[9];
  MATRIX_LOAD4x3 = m->m[10];
  MATRIX_LOAD4x3 = m->m[11];
}

//////////////////////////////////////////////////////////////////////

void glMultMatrix4x4(m4x4* m)
{
  MATRIX_LOAD4x4 = m->m[0];
  MATRIX_LOAD4x4 = m->m[1];
  MATRIX_LOAD4x4 = m->m[2];
  MATRIX_LOAD4x4 = m->m[3];

  MATRIX_LOAD4x4 = m->m[4];
  MATRIX_LOAD4x4 = m->m[5];
  MATRIX_LOAD4x4 = m->m[6];
  MATRIX_LOAD4x4 = m->m[7];

  MATRIX_LOAD4x4 = m->m[8];
  MATRIX_LOAD4x4 = m->m[9];
  MATRIX_LOAD4x4 = m->m[10];
  MATRIX_LOAD4x4 = m->m[11];

  MATRIX_LOAD4x4 = m->m[12];
  MATRIX_LOAD4x4 = m->m[13];
  MATRIX_LOAD4x4 = m->m[14];
  MATRIX_LOAD4x4 = m->m[15];
}

//////////////////////////////////////////////////////////////////////

void glMultMatrix4x3(m4x3* m)
{
  MATRIX_MULT4x3 = m->m[0];
  MATRIX_MULT4x3 = m->m[1];
  MATRIX_MULT4x3 = m->m[2];
  MATRIX_MULT4x3 = m->m[3];

  MATRIX_MULT4x3 = m->m[4];
  MATRIX_MULT4x3 = m->m[5];
  MATRIX_MULT4x3 = m->m[6];
  MATRIX_MULT4x3 = m->m[7];

  MATRIX_MULT4x3 = m->m[8];
  MATRIX_MULT4x3 = m->m[9];
  MATRIX_MULT4x3 = m->m[10];
  MATRIX_MULT4x3 = m->m[11];

  MATRIX_MULT3x3 = m->m[0];
  MATRIX_MULT3x3 = m->m[1];
  MATRIX_MULT3x3 = m->m[2];
  
  MATRIX_MULT3x3 = m->m[3];
  MATRIX_MULT3x3 = m->m[4];
  MATRIX_MULT3x3 = m->m[5];
  
  MATRIX_MULT3x3 = m->m[6];
  MATRIX_MULT3x3 = m->m[7];
  MATRIX_MULT3x3 = m->m[8];
}

//////////////////////////////////////////////////////////////////////
// Integer rotation (not gl standard)
//	based on 512 degree circle
void glRotateZi(int angle)
{

  f32 sine = SIN[angle &  LUT_MASK];
  f32 cosine = COS[angle & LUT_MASK];

  MATRIX_MULT3x3 = cosine;
  MATRIX_MULT3x3 = sine;
  MATRIX_MULT3x3 = 0;

  MATRIX_MULT3x3 = - sine;
  MATRIX_MULT3x3 = cosine;
  MATRIX_MULT3x3 = 0;
  
  MATRIX_MULT3x3 = 0;
  MATRIX_MULT3x3 = 0;
  MATRIX_MULT3x3 = intof32(1);
}

//////////////////////////////////////////////////////////////////////

void glRotateYi(int angle)
{
  f32 sine = SIN[angle &  LUT_MASK];
  f32 cosine = COS[angle & LUT_MASK];

  MATRIX_MULT3x3 = cosine;
  MATRIX_MULT3x3 = 0;
  MATRIX_MULT3x3 = -sine;
  
  MATRIX_MULT3x3 = 0;
  MATRIX_MULT3x3 = intof32(1);
  MATRIX_MULT3x3 = 0;
  
  MATRIX_MULT3x3 = sine;
  MATRIX_MULT3x3 = 0;
  MATRIX_MULT3x3 = cosine;
}

//////////////////////////////////////////////////////////////////////

void glRotateXi(int angle)
{
  f32 sine = SIN[angle &  LUT_MASK];
  f32 cosine = COS[angle & LUT_MASK];

  MATRIX_MULT3x3 = cosine;
  MATRIX_MULT3x3 = sine;
  MATRIX_MULT3x3 = 0;

  MATRIX_MULT3x3 = - sine;
  MATRIX_MULT3x3 = cosine;
  MATRIX_MULT3x3 = 0;
  
  MATRIX_MULT3x3 = 0;
  MATRIX_MULT3x3 = 0;
  MATRIX_MULT3x3 = intof32(1);
}
//////////////////////////////////////////////////////////////////////
//	rotations wrapped in float...mainly for testing
void glRotateX(float angle)
{
	glRotateXi((int)(angle * LUT_SIZE / 360.0));
}
//////////////////////////////////////////////////////////////////////

void glRotateY(float angle)
{
	glRotateYi((int)(angle * LUT_SIZE / 360.0));
}
///////////////////////////////////////////////////////////////////////
void glRotateZ(float angle)
{
	glRotateZi((int)(angle * LUT_SIZE / 360.0));
}

//////////////////////////////////////////////////////////////////////
// Fixed point look at function, it appears to work as expected although 
//	testing is recomended
void gluLookAtf32(f32 eyex, f32 eyey, f32 eyez, f32 lookAtx, f32 lookAty, f32 lookAtz, f32 upx, f32 upy, f32 upz)
{
	f32 x[3], y[3], z[3], up[3];

	z[0] = eyex - lookAtx;
	z[1] = eyey - lookAty;
	z[2] = eyez - lookAtz;

	up[0] = upx;
	up[1] = upy;
	up[2] = upz;

	normalizef32(z);

	crossf32(up, z, x);
	crossf32(z, x, y);

	normalizef32(x);
	normalizef32(y);
	
	glMatrixMode(GL_MODELVIEW);

	MATRIX_LOAD4x3 = x[0];
	MATRIX_LOAD4x3 = x[1];
	MATRIX_LOAD4x3 = x[2];

	MATRIX_LOAD4x3 = y[0];
	MATRIX_LOAD4x3 = y[1];
	MATRIX_LOAD4x3 = y[2];

	MATRIX_LOAD4x3 = z[0];
	MATRIX_LOAD4x3 = z[1];
	MATRIX_LOAD4x3 = z[2];

	MATRIX_LOAD4x3 = 0;
	MATRIX_LOAD4x3 = 0;
	MATRIX_LOAD4x3 = floatof32(-1.0);

	glTranslate3f32(-eyex, -eyey, -eyez);
}
///////////////////////////////////////
//  glu wrapper for standard float call
void gluLookAt(float eyex, float eyey, float eyez, float lookAtx, float lookAty, float lookAtz, float upx, float upy, float upz)
{
	gluLookAtf32(floatof32(eyex), floatof32(eyey), floatof32(eyez), floatof32(lookAtx), floatof32(lookAty), floatof32(lookAtz),
					floatof32(upx), floatof32(upy), floatof32(upz));
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//	frustrum has only been tested as part of perspective
void gluFrustumf32(f32 left, f32 right, f32 bottom, f32 top, f32 near, f32 far)
{
  
   glMatrixMode(GL_PROJECTION);

   MATRIX_LOAD4x4 = divf32(2*near, right - left);     
   MATRIX_LOAD4x4 = 0;  
   MATRIX_LOAD4x4 = divf32(right + left, right - left);      
   MATRIX_LOAD4x4 = 0;

   MATRIX_LOAD4x4 = 0;  
   MATRIX_LOAD4x4 = divf32(2*near, top - bottom);     
   MATRIX_LOAD4x4 = divf32(top + bottom, top - bottom);      
   MATRIX_LOAD4x4 = 0;
   
   MATRIX_LOAD4x4 = 0;  
   MATRIX_LOAD4x4 = 0;  
   MATRIX_LOAD4x4 = -divf32(far + near, far - near);     
   MATRIX_LOAD4x4 = floatof32(-1.0F);
   
   MATRIX_LOAD4x4 = 0;  
   MATRIX_LOAD4x4 = 0;  
   MATRIX_LOAD4x4 = -divf32(2 * mulf32(far, near), far - near);  
   MATRIX_LOAD4x4 = 0;
	
   glStoreMatrix(0);
}
///////////////////////////////////////
//  Frustrum wrapper
void gluFrustum(float left, float right, float bottom, float top, float near, float far)
{
	gluFrustumf32(floatof32(left), floatof32(right), floatof32(bottom), floatof32(top), floatof32(near), floatof32(far));
}

//////////////////////////////////////////////////////////////////////////////////////////
//	Fixed point perspective setting
void gluPerspectivef32(int fovy, f32 aspect, f32 zNear, f32 zFar)
{
   f32 xmin, xmax, ymin, ymax;

   ymax = mulf32(zNear, TAN[fovy & LUT_MASK]);
   ymin = -ymax;
   xmin = mulf32(ymin, aspect);
   xmax = mulf32(ymax, aspect);

   gluFrustumf32(xmin, xmax, ymin, ymax, zNear, zFar);
}

///////////////////////////////////////
//  glu wrapper for floating point
void gluPerspective(float fovy, float aspect, float zNear, float zFar)
{
	
	 gluPerspectivef32((int)(fovy * LUT_SIZE / 360.0), floatof32(aspect), floatof32(zNear), floatof32(zFar));    
}
