#include <NDS/NDS.h>
#include <NDS/ARM9/rand.h>

//texture_bin.h is created automagicaly from the texture.bin placed in arm9/resources
//texture.bin is a raw 128x128 16 bit image.  I will release a tool for texture conversion 
//later
#include "texture.h"





int main()
{	
	
	int textureID;

	float rotateX = 0.0;
	float rotateY = 0.0;

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

	glGenTextures(1, &textureID);
	glBindTexture(0, textureID);
	glTexImage2D(0, 0, GL_RGB, TEXTURE_SIZE_128 , TEXTURE_SIZE_128, 0, TEXGEN_TEXCOORD, (u8*)texture);
	
	
	while(1)		
	{
		glReset();
	
		//any floating point gl call is being converted to fixed prior to being implemented
		gluPerspective(35, 256.0 / 192.0, 0.1, 40);

		gluLookAt(	0.0, 0.0, 1.0,		//camera possition 
					0.0, 0.0, 0.0,		//look at
					0.0, 1.0, 0.0);		//up
		
		


		glPushMatrix();

		//move it away from the camera
		glTranslate3f32(0, 0, floatof32(-1));
				
		glRotateX(rotateX);
		glRotateY(rotateY);
		
		glMatrixMode(GL_TEXTURE);
		glIdentity();
		
		glMatrixMode(GL_MODELVIEW);

		glMaterialf(GL_AMBIENT, RGB15(16,16,16));
		glMaterialf(GL_DIFFUSE, RGB15(16,16,16));
		glMaterialf(GL_SPECULAR, BIT(15) | RGB15(8,8,8));
		glMaterialf(GL_EMISSION, RGB15(16,16,16));

		//ds uses a table for shinyness..this generates a half-ass one
		glMaterialShinnyness();

		//not a real gl function and will likely change
		glPolyFmt(POLY_ALPHA(31) | POLY_CULL_BACK);

		if(!(KEYS & KEY_UP)) rotateX += 3;
		if(!(KEYS & KEY_DOWN)) rotateX -= 3;
		if(!(KEYS & KEY_LEFT)) rotateY += 3;
		if(!(KEYS & KEY_RIGHT)) rotateY -= 3;
		
		glBindTexture(0, textureID);

		//draw the obj
		glBegin(GL_QUAD);
			glNormal(NORMAL_PACK(0,intov10(-1),0));

			glTexCoord1i(TEXTURE_PACK(intot16(128), 0));
			glVertex3v16(floatov16(-0.5),	floatov16(-0.5), 0 );
	
			glTexCoord1i(TEXTURE_PACK(intot16(128),intot16(128)));
			glVertex3v16(floatov16(0.5),	floatov16(-0.5), 0 );
	
			glTexCoord1i(TEXTURE_PACK(0, intot16(128)));
			glVertex3v16(floatov16(0.5),	floatov16(0.5), 0 );

			glTexCoord1i(TEXTURE_PACK(0,0));
			glVertex3v16(floatov16(-0.5),	floatov16(0.5), 0 );
		
		glEnd();
		
		glPopMatrix(1);
			
		glFlush();

		//swi seems to be broken, will let you know when i get this POS figured out	
		//swiWaitForVBlank();
	}

	return 0;
}//end main 
