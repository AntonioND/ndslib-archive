#include <NDS/NDS.h>


#include "teapot.h"
#include "cafe.h"


#ifndef PEN_DOWN
#define PEN_DOWN	(((~IPC->buttons) << 6) & (1<<12))
#endif


static void get_pen_delta( int *dx, int *dy )
{
	static int prev_pen[2] = { 0x7FFFFFFF, 0x7FFFFFFF };

	if( PEN_DOWN )
	{
		if( prev_pen[0] != 0x7FFFFFFF )
		{
			*dx = (prev_pen[0] - IPC->touchX);
			*dy = (prev_pen[1] - IPC->touchY);
		}

		prev_pen[0] = IPC->touchX;
		prev_pen[1] = IPC->touchY;
	}
	else
	{
		prev_pen[0] = prev_pen[1] = 0x7FFFFFFF;
		*dx = *dy = 0;
	}
}


int main()
{	

	int rotateX = 0;
	int rotateY = 0;

	powerON(POWER_ALL);

	//set mode 0, enable BG0 and set it to 3D
	videoSetMode(MODE_0_3D);

	//irqs are nice
	irqInitHandler(irqDefaultHandler);
	irqSet(IRQ_VBLANK, 0);

	//this should work the same as the normal gl call
	glViewPort(0,0,255,191);
	
	glClearColor(0,0,0);
	glClearDepth(0x7FFF);

	vramSetBankA(VRAM_A_TEXTURE);

	int cafe_texid;
	glGenTextures( 1, &cafe_texid );
	glBindTexture( 0, cafe_texid );
	glTexImage2D( 0, 0, GL_RGB, TEXTURE_SIZE_128 , TEXTURE_SIZE_128, 0, GL_TEXTURE_WRAP_S|GL_TEXTURE_WRAP_T|TEXGEN_NORMAL, (u8*)cafe );


	while(1)		
	{
		glReset();

		//any floating point gl call is being converted to fixed prior to being implemented
		gluPerspective(35, 256.0 / 192.0, 0.1, 40);


		//TEXGEN_NORMAL helpfully pops our normals into this matrix and uses the result as texcoords
		glMatrixMode(GL_TEXTURE);
		glIdentity();
		vector tex_scale = { 64<<16, -64<<16, 1<<16 };
		glScalev( &tex_scale );		//scale normals up from (-1,1) range into texcoords
		glRotateXi(rotateX>>3);			//rotate texture-matrix to match the camera
		glRotateYi(rotateY>>3);


		glMatrixMode(GL_MODELVIEW);
		glIdentity();
		glTranslate3f32(0, 0, floatof32(-3));
		glRotateXi(rotateX>>3);
		glRotateYi(rotateY>>3);


		glMaterialf(GL_EMISSION, RGB15(31,31,31));

		glPolyFmt(POLY_ALPHA(31) | POLY_CULL_BACK );

		if(!(KEYS & KEY_UP)) rotateX += 3<<3;
		if(!(KEYS & KEY_DOWN)) rotateX -= 3<<3;
		if(!(KEYS & KEY_LEFT)) rotateY += 3<<3;
		if(!(KEYS & KEY_RIGHT)) rotateY -= 3<<3;

		int pen_delta[2];
		get_pen_delta( &pen_delta[0], &pen_delta[1] );
		rotateY -= pen_delta[0];
		rotateX -= pen_delta[1];


		glBindTexture( 0, cafe_texid );
		glCallList((u32*)teapot);	

		glFlush();

		//swi seems to be broken, will let you know when i get this POS figured out	
		//swiWaitForVBlank();
	}

	return 0;
}//end main 
