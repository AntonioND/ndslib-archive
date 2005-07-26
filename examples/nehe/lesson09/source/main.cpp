/****************************************
 * 		NDS NeHe Lesson 09    			*
 * 		Author: dovoto
 *		DS does not appear to support 
		the features needed for this demo
 ****************************************/

// include your ndslib
#include <NDS/NDS.h>
#include <malloc.h>
//needed to load pcx files
#include <NDS/ARM9/image.h>
#include <NDS/ARM9/rand.h>

#include "Star.h"

int DrawGLScene();


bool	twinkle;			// Twinkling Stars
bool	tp;					// 'T' Key Pressed?

const	u32 num=50;				// Number Of Stars To Draw

typedef struct				// Create A Structure For Star
{
	int r, g, b;			// Stars Color
	GLfloat dist,			// Stars Distance From Center
			angle;			// Stars Current Angle
}stars;

stars star[num];			// Need To Keep Track Of 'num' Stars

GLfloat	zoom=-15.0f;		// Distance Away From Stars
GLfloat tilt=90.0f;			// Tilt The View
GLfloat	spin;				// Spin Stars

GLuint	loop;				// General Loop Variable
int	texture[1];			// Storage For One textures


int LoadGLTextures()									// Load PCX files And Convert To Textures
{
	sImage pcx;                //////////////(NEW) and different from nehe.

	//load our texture
	loadPCX((u8*)Star, &pcx);
	image8to16trans(&pcx, 0);

	//DS supports no filtering of anykind so no need for more than one texture
	glGenTextures(1, &texture[0]);
	glBindTexture(0, texture[0]);
	glTexImage2D(0, 0, GL_RGB, TEXTURE_SIZE_128 , TEXTURE_SIZE_128, 0, TEXGEN_TEXCOORD, pcx.data8);

	imageDestroy(&pcx);

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

	while (1) 
	{


		// Reset the screen and setup the view
		glReset();
		gluPerspective(35, 256.0 / 192.0, 0.1, 100);
		glColor3f(1,1,1);
		
		glEnable(GL_BLEND);


		//set up a directional ligth arguments are light number (0-3), light color, 
		//and an x,y,z vector that points in the direction of the light
		glLight(0, RGB15(31,31,31) , 0, 0,floatov10(-1.0));

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
		
		
		
		// Set the current matrix to be the model matrix
		glMatrixMode(GL_MODELVIEW);
		
    	//Push our original Matrix onto the stack (save state)
		glPushMatrix();	

		glPolyFmt(POLY_ALPHA(15) | POLY_CULL_BACK  | POLY_FORMAT_LIGHT0);

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
	glBindTexture(GL_TEXTURE_2D, texture[0]);			// Select Our Texture

	for (loop=0; loop<num; loop++)						// Loop Through All The Stars
	{
		glLoadIdentity();								// Reset The View Before We Draw Each Star
		glTranslatef(0.0f,0.0f,zoom);					// Zoom Into The Screen (Using The Value In 'zoom')
		glRotatef(tilt,1.0f,0.0f,0.0f);					// Tilt The View (Using The Value In 'tilt')
		glRotatef(star[loop].angle,0.0f,1.0f,0.0f);		// Rotate To The Current Stars Angle
		glTranslatef(star[loop].dist,0.0f,0.0f);		// Move Forward On The X Plane
		glRotatef(-star[loop].angle,0.0f,1.0f,0.0f);	// Cancel The Current Stars Angle
		glRotatef(-tilt,1.0f,0.0f,0.0f);				// Cancel The Screen Tilt
		
		if (twinkle)
		{
			glColor3b(star[(num-loop)-1].r,star[(num-loop)-1].g,star[(num-loop)-1].b);  ///different
			glBegin(GL_QUADS);
				glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,-1.0f, 0.0f);
				glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,-1.0f, 0.0f);
				glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f, 1.0f, 0.0f);
				glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 0.0f);
			glEnd();
		}

		glRotatef(spin,0.0f,0.0f,1.0f);
		glColor3b(star[loop].r,star[loop].g,star[loop].b);                            //different
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,-1.0f, 0.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,-1.0f, 0.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f, 1.0f, 0.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 0.0f);
		glEnd();

		spin+=0.01f;
		star[loop].angle+=float(loop)/num;
		star[loop].dist-=0.01f;
		if (star[loop].dist<0.0f)
		{
			star[loop].dist+=5.0f;
			star[loop].r=rand()%256;
			star[loop].g=rand()%256;
			star[loop].b=rand()%256;
		}
	}
	return TRUE;															// Keep Going

}
