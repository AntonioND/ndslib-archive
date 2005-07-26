/****************************************
 * 		NDS NeHe Lesson 04    			*
 * 		Author: Ethos					*
 ****************************************/

// include your ndslib
#include <NDS/NDS.h>
#include <malloc.h>
//needed to load pcx files
#include <NDS/ARM9/image.h>


#include "drunkenlogo.h"

int DrawGLScene();

float	xrot;				// X Rotation ( NEW )
float	yrot;				// Y Rotation ( NEW )
float	zrot;				// Z Rotation ( NEW )

int	texture[1];			// Storage For One Texture ( NEW )

void image8to16(sImage* img)
 {
	 int i;

	 u16* temp = (u16*)malloc(img->height*img->width*2);
	 
	 for(i = 0; i < img->height * img->width; i++)
		 temp[i] = img->palette[img->data8[i]] | (1<<15);

	 img->data16 = temp;
 }

int LoadGLTextures()									// Load PCX files And Convert To Textures
{
	sImage pcx;                //////////////(NEW) and different from nehe.

	//load our texture
	loadPCX((u8*)drunkenlogo, &pcx);
	
	image8to16(&pcx);

	glGenTextures(1, &texture[0]);
	glBindTexture(0, texture[0]);
	glTexImage2D(0, 0, GL_RGB, TEXTURE_SIZE_128 , TEXTURE_SIZE_128, 0, TEXGEN_TEXCOORD, pcx.data8);

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
		
		glLight(0, RGB15(31,31,31) , 0,				  floatov10(-1.0),		 0);
		glLight(1, RGB15(31,31,31) , 0,				  0,	floatov10(-1.0));
		glLight(2, RGB15(31,31,31) , 0,				  0,	floatov10(1.0));

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
		glPolyFmt(POLY_ALPHA(31) | POLY_CULL_NONE  | POLY_FORMAT_LIGHT0| POLY_FORMAT_LIGHT1| POLY_FORMAT_LIGHT2);
		
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
	glLoadIdentity();									// Reset The View
	glTranslatef(0.0f,0.0f,-5.0f);

	glRotatef(xrot,1.0f,0.0f,0.0f);
	glRotatef(yrot,0.0f,1.0f,0.0f);
	glRotatef(zrot,0.0f,0.0f,1.0f);

	glBindTexture(GL_TEXTURE_2D, texture[0]);

	glBegin(GL_QUADS);
		// Front Face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
		// Back Face
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
		// Top Face
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
		// Bottom Face
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
		// Right face
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
		// Left Face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
	glEnd();

	xrot+=0.3f;
	yrot+=0.2f;
	zrot+=0.4f;
	return TRUE;			
}
