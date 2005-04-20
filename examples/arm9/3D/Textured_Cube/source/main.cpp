#include <NDS/NDS.h>
#include <NDS/ARM9/rand.h>

//texture_bin.h is created automagicaly from the texture.bin placed in arm9/resources
//texture.bin is a raw 128x128 16 bit image.  I will release a tool for texture conversion 
//later
#include "texture.h"


//verticies for the cube
v16 CubeVectors[] = {
 		floatov16(-0.5),	floatov16(-0.5),	floatov16(0.5), 
		floatov16(0.5),		floatov16(-0.5),	floatov16(0.5),
		floatov16(0.5),		floatov16(-0.5),	floatov16(-0.5),
		floatov16(-0.5),	floatov16(-0.5),	floatov16(-0.5),
		floatov16(-0.5),	floatov16(0.5),		floatov16(0.5), 
		floatov16(0.5),		floatov16(0.5),		floatov16(0.5),
		floatov16(0.5),		floatov16(0.5),		floatov16(-0.5),
		floatov16(-0.5),	floatov16(0.5),		floatov16(-0.5)
};

//polys
u8 CubeFaces[] = {
	3,2,1,0,
	0,1,5,4,
	1,2,6,5,
	2,3,7,6,
	3,0,4,7,
	5,6,7,4
};

//texture coordinates
u32 uv[] =
{
	
	TEXTURE_PACK(intot16(128), 0),
	TEXTURE_PACK(intot16(128),intot16(128)),
	TEXTURE_PACK(0, intot16(128)),
	TEXTURE_PACK(0,0)
};

u32 normals[] =
{
	NORMAL_PACK(0,intov10(-1),0),
	NORMAL_PACK(0,intov10(1),0),
	NORMAL_PACK(intov10(1),0,0),
	NORMAL_PACK(0,0,intov10(-1)),
	NORMAL_PACK(intov10(-1),0,0),
	NORMAL_PACK(0,intov10(1),0)

};

//draw a cube face at the specified color
 void drawQuad(int poly)
{	
	
	u32 f1 = CubeFaces[poly * 4] ;
	u32 f2 = CubeFaces[poly * 4 + 1] ;
	u32 f3 = CubeFaces[poly * 4 + 2] ;
	u32 f4 = CubeFaces[poly * 4 + 3] ;


	glNormal(normals[poly]);

	glTexCoord1i(uv[0]);
	glVertex3v16(CubeVectors[f1*3], CubeVectors[f1*3 + 1], CubeVectors[f1*3 +  2] );
	
	glTexCoord1i(uv[1]);
	glVertex3v16(CubeVectors[f2*3], CubeVectors[f2*3 + 1], CubeVectors[f2*3 + 2] );
	
	glTexCoord1i(uv[2]);
	glVertex3v16(CubeVectors[f3*3], CubeVectors[f3*3 + 1], CubeVectors[f3*3 + 2] );

	glTexCoord1i(uv[3]);
	glVertex3v16(CubeVectors[f4*3], CubeVectors[f4*3 + 1], CubeVectors[f4*3 + 2] );
}


int main()
{	
	
	int textureID;
	int i;
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
		
		

		
		glLight(0, RGB15(31,31,31) , 0,				  floatov10(-1.0),		 0);
		glLight(1, RGB15(31,0,31),   0,				  floatov10(1) - 1,			 0);
		glLight(2, RGB15(0,31,0) ,   floatov10(-1.0), 0,					 0);
		glLight(3, RGB15(0,0,31) ,   floatov10(1.0) - 1,  0,					 0);

		glPushMatrix();

		//move it away from the camera
		glTranslate3f32(0, 0, floatof32(-1));
				
		glRotateX(rotateX);
		glRotateY(rotateY);
		
		glMatrixMode(GL_TEXTURE);
		glIdentity();
		
		glMatrixMode(GL_MODELVIEW);

		glMaterialf(GL_AMBIENT, RGB15(8,8,8));
		glMaterialf(GL_DIFFUSE, RGB15(16,16,16));
		glMaterialf(GL_SPECULAR, BIT(15) | RGB15(8,8,8));
		glMaterialf(GL_EMISSION, RGB15(5,5,5));

		//ds uses a table for shinyness..this generates a half-ass one
		glMaterialShinnyness();

		//not a real gl function and will likely change
		glPolyFmt(POLY_ALPHA(31) | POLY_CULL_BACK | POLY_FORMAT_LIGHT0 | POLY_FORMAT_LIGHT1 | 
													POLY_FORMAT_LIGHT2 | POLY_FORMAT_LIGHT3 ) ;
		
		if(!(KEYS & KEY_UP)) rotateX += 3;
		if(!(KEYS & KEY_DOWN)) rotateX -= 3;
		if(!(KEYS & KEY_LEFT)) rotateY += 3;
		if(!(KEYS & KEY_RIGHT)) rotateY -= 3;
		
		glBindTexture(0, textureID);

		//draw the obj
		glBegin(GL_QUAD);
			for(i = 0; i < 6; i++)
				drawQuad(i);
		
		glEnd();
		
		glPopMatrix(1);
			
		glFlush();

		//swi seems to be broken, will let you know when i get this POS figured out	
		//swiWaitForVBlank();
	}

	return 0;
}//end main 