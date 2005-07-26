/****************************************
 * 		NDS NeHe Lesson 10    			*
 * 		Author: Dovoto					*
 ****************************************/

// include your ndslib
#include <NDS/NDS.h>
#include <malloc.h>
#include <stdio.h>

//needed to load pcx files
#include <NDS/ARM9/image.h>


#include "Mud.h"
#include "World.h"


int DrawGLScene();

const float piover180 = 0.0174532925f;
float heading;
float xpos;
float zpos;

GLfloat	yrot;				// Y Rotation
GLfloat walkbias = 0;
GLfloat walkbiasangle = 0;
GLfloat lookupdown = 0.0f;

int	texture[3];			// Storage For 3 Textures (only going to use 1 on the DS for this demo)

typedef struct tagVERTEX
{
	float x, y, z;
	float u, v;
} VERTEX;

typedef struct tagTRIANGLE
{
	VERTEX vertex[3];
} TRIANGLE;

typedef struct tagSECTOR
{
	int numtriangles;
	TRIANGLE* triangle;
} SECTOR;

VAR_IN_EXRAM SECTOR sector1;				// Our Model Goes Here:


float sin(float angle)
{
	f32 s = SIN[(int)((angle * LUT_SIZE) / 360.0) & LUT_MASK];

	return f32tofloat(s);
}

float cos(float angle)
{
	f32 c = COS[(int)((angle * LUT_SIZE) / 360.0) & LUT_MASK];

	return f32tofloat(c);
}
 u8* file = (u8*)World;

 void myGetStr(char* buff, int size)
{
	*buff = *file++;

	while( (*buff != '\n') && (*buff != 0xD))
	{
		buff++;
		*buff = *file++;
	}
	
	buff[0] = '\n';	
	buff[1] = 0;
	
}


void readstr(char *string)
{
	do
	{
		myGetStr(string, 255);
	} while ((string[0] == '/') || (string[0] == '\n' ));
	return;
}

void SetupWorld()
{
	float x, y, z, u, v;
	int numtriangles;
	char oneline[255];

	readstr(oneline);
	sscanf(oneline, "NUMPOLLIES %d\n", &numtriangles);

	sector1.triangle = (TRIANGLE*)malloc(numtriangles*sizeof(TRIANGLE));
	sector1.numtriangles = numtriangles;
	
	for (int loop = 0; loop < numtriangles; loop++)
	{
		for (int vert = 0; vert < 3; vert++)
		{
			readstr(oneline);
			sscanf(oneline, "%f %f %f %f %f", &x, &y, &z, &u, &v);
			sector1.triangle[loop].vertex[vert].x = x;
			sector1.triangle[loop].vertex[vert].y = y;
			sector1.triangle[loop].vertex[vert].z = z;
			sector1.triangle[loop].vertex[vert].u = u;
			sector1.triangle[loop].vertex[vert].v = v;
		}
	}
	
	return;
}
int LoadGLTextures()									// Load PCX files And Convert To Textures
{
	sImage pcx;                //////////////(NEW) and different from nehe.

	//load our texture
	loadPCX((u8*)Mud, &pcx);
	
	image8to16(&pcx);

	glGenTextures(1, &texture[0]);
	glBindTexture(0, texture[0]);
	glTexImage2D(0, 0, GL_RGB, TEXTURE_SIZE_128 , TEXTURE_SIZE_128, 0, TEXGEN_TEXCOORD | GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T, pcx.data8);

	return TRUE;
}

int main()
{	
	
	
	// Turn on everything
	powerON(POWER_ALL);
	
	// Setup the Main screen for 3D 
	videoSetMode(MODE_0_3D);
	vramSetBankA(VRAM_A_TEXTURE);                        //NEW  must set up some memory for textures

	// IRQ basic setup
	irqInitHandler(irqDefaultHandler);
	irqSet(IRQ_VBLANK, 0);

	// Set our viewport to be the same size as the screen
	glViewPort(0,0,255,191);
	
	// Specify the Clear Color and Depth 
	glClearColor(0,0,0);
	glClearDepth(0x7FFF);
	LoadGLTextures();
	SetupWorld();
	

	while (1) 
	{
		//these little button functions are pretty handy
		scanKeys();
				
	
		if (keysHeld() & KEY_A)
		{
			lookupdown -= 1.0f;
		}
		if (keysHeld() & KEY_B)
		{
			lookupdown += 1.0f;
		}
		if (keysHeld() & KEY_LEFT)
		{
			heading -= 1.0f;	
			yrot = heading;
		}
		if (keysHeld() & KEY_RIGHT)
		{
			heading += 1.0f;
			yrot = heading;
		}
		if (keysHeld() & KEY_DOWN)
		{
			
			xpos -= (float)sin(heading) * 0.05f;
			zpos += (float)cos(heading) * 0.05f;
			if (walkbiasangle >= 359.0f)
			{
				walkbiasangle = 0.0f;
			}
			else
			{
				walkbiasangle+= 10;
			}
			walkbias = (float)sin(walkbiasangle)/20.0f;
		}
		if (keysHeld() & KEY_UP)
		{
			xpos += (float)sin(heading) * 0.05f;
			zpos -= (float)cos(heading) * 0.05f;
			if (walkbiasangle <= 1.0f)
			{
				walkbiasangle = 359.0f;
			}
			else
			{
				walkbiasangle-= 10;
			}
			walkbias = (float)sin(walkbiasangle)/20.0f;
		}

		// Reset the screen and setup the view
		glReset();
		gluPerspective(35, 256.0 / 192.0, 0.1, 100);
		glColor3f(1,1,1);
		
		glLight(0, RGB15(31,31,31) , 0,				  floatov10(-1.0),		 0);

		glPushMatrix();
		
		glMatrixMode(GL_TEXTURE);
		glIdentity();
		
		glMatrixMode(GL_MODELVIEW);

		//need to set up some material properties since DS does not have them set by default
		glMaterialf(GL_AMBIENT, RGB15(16,16,16));
		glMaterialf(GL_DIFFUSE, RGB15(16,16,16));
		glMaterialf(GL_SPECULAR, BIT(15) | RGB15(8,8,8));
		glMaterialf(GL_EMISSION, RGB15(16,16,16));

		//ds uses a table for shinyness..this generates a half-ass one
		glMaterialShinnyness();
		
		
		//ds specific, several attributes can be set here	
		glPolyFmt(POLY_ALPHA(31) | POLY_CULL_NONE | POLY_FORMAT_LIGHT0);
		
		// Set the current matrix to be the model matrix
		glMatrixMode(GL_MODELVIEW);
		
		//Push our original Matrix onto the stack (save state)
		glPushMatrix();	

		DrawGLScene();
		
		// Pop our Matrix from the stack (restore state)
		glPopMatrix(1);

		// flush to screen	
		glFlush();
	
	}
	
	return 0;
}

int DrawGLScene()											// Here's Where We Do All The Drawing
{
											// Reset The View

	GLfloat x_m, y_m, z_m, u_m, v_m;
	GLfloat xtrans = -xpos;
	GLfloat ztrans = -zpos;
	GLfloat ytrans = -walkbias-0.25f;
	GLfloat sceneroty = 360.0f - yrot;
	
	glLoadIdentity();
	
	int numtriangles;

	glRotatef(lookupdown,1.0f,0,0);
	glRotatef(sceneroty,0,1.0f,0);
	
	glTranslatef(xtrans, ytrans, ztrans);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	
	numtriangles = sector1.numtriangles;
	
	
	// Process Each Triangle
	for (int loop_m = 0; loop_m < numtriangles; loop_m++)
	{
		glBegin(GL_TRIANGLES);
			glNormal3f( 0.0f, 0.0f, 1.0f);
			x_m = sector1.triangle[loop_m].vertex[0].x;
			y_m = sector1.triangle[loop_m].vertex[0].y;
			z_m = sector1.triangle[loop_m].vertex[0].z;
			u_m = sector1.triangle[loop_m].vertex[0].u;
			v_m = sector1.triangle[loop_m].vertex[0].v;
			glTexCoord2f(u_m,v_m); glVertex3f(x_m,y_m,z_m);
			
			x_m = sector1.triangle[loop_m].vertex[1].x;
			y_m = sector1.triangle[loop_m].vertex[1].y;
			z_m = sector1.triangle[loop_m].vertex[1].z;
			u_m = sector1.triangle[loop_m].vertex[1].u;
			v_m = sector1.triangle[loop_m].vertex[1].v;
			glTexCoord2f(u_m,v_m); glVertex3f(x_m,y_m,z_m);
			
			x_m = sector1.triangle[loop_m].vertex[2].x;
			y_m = sector1.triangle[loop_m].vertex[2].y;
			z_m = sector1.triangle[loop_m].vertex[2].z;
			u_m = sector1.triangle[loop_m].vertex[2].u;
			v_m = sector1.triangle[loop_m].vertex[2].v;
			glTexCoord2f(u_m,v_m); glVertex3f(x_m,y_m,z_m);
		glEnd();
	}
	return TRUE;										// Everything Went OK

}
