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
//
//////////////////////////////////////////////////////////////////////

#include <NDS/ARM9/videoGL.h>
#include <math.h>

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

void glRotateZ(float angle)
{
  f32 sine = floatof32(sin(angle * M_PI / 360.0));
  f32 cosine = floatof32(cos(angle * M_PI / 360.0));

  MATRIX_MULT3x3 = cosine;
  MATRIX_MULT3x3 = sine;
  MATRIX_MULT3x3 = 0;

  MATRIX_MULT3x3 = - sine;
  MATRIX_MULT3x3 = cosine;
  MATRIX_MULT3x3 = 0;
  
  MATRIX_MULT3x3 = 0;
  MATRIX_MULT3x3 = 0;
  MATRIX_MULT3x3 = floatof32(1.0);
}

//////////////////////////////////////////////////////////////////////

void glRotateY(float angle)
{
  f32 sine = floatof32(sin(angle * M_PI / 360.0));
  f32 cosine = floatof32(cos(angle * M_PI / 360.0));

  MATRIX_MULT3x3 = cosine;
  MATRIX_MULT3x3 = 0;
  MATRIX_MULT3x3 = -sine;
  
  MATRIX_MULT3x3 = 0;
  MATRIX_MULT3x3 = floatof32(1.0);
  MATRIX_MULT3x3 = 0;
  
  MATRIX_MULT3x3 = sine;
  MATRIX_MULT3x3 = 0;
  MATRIX_MULT3x3 = cosine;
}

//////////////////////////////////////////////////////////////////////

void glRotateX(float angle)
{
  f32 sine = floatof32(sin(angle * M_PI / 360.0));
  f32 cosine = floatof32(cos(angle * M_PI / 360.0));

  MATRIX_MULT3x3 = floatof32(1.0);
  MATRIX_MULT3x3 = 0;
  MATRIX_MULT3x3 = 0;

  MATRIX_MULT3x3 = 0;
  MATRIX_MULT3x3 = cosine;
  MATRIX_MULT3x3 = sine;
  
  MATRIX_MULT3x3 = 0;
  MATRIX_MULT3x3 = -sine;
  MATRIX_MULT3x3 = cosine;
}

//////////////////////////////////////////////////////////////////////
