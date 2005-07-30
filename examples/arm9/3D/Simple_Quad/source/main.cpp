#include <NDS/NDS.h>

#include <NDS/ndsload.h>


int main()
{	
	
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
		
		
		glMatrixMode(GL_MODELVIEW);



		//not a real gl function and will likely change
		glPolyFmt(POLY_ALPHA(31) | POLY_CULL_NONE);

		if(!(KEYS & KEY_UP)) rotateX += 3;
		if(!(KEYS & KEY_DOWN)) rotateX -= 3;
		if(!(KEYS & KEY_LEFT)) rotateY += 3;
		if(!(KEYS & KEY_RIGHT)) rotateY -= 3;
		

		//draw the obj
		glBegin(GL_QUAD);
			
			glColor3b(31,0,0);
			glVertex3v16(intov16(-1),intov16(-1),0);

			glColor3b(0,31,0);
			glVertex3v16(intov16(1), intov16(-1), 0);

			glColor3b(0,0,31);
			glVertex3v16(intov16(1), intov16(1), 0);

			glColor3b(31,0,31);
			glVertex3v16(intov16(-1), intov16(1), 0);
			
		glEnd();
		
		glPopMatrix(1);
			
		glFlush();

		//swi seems to be broken, will let you know when i get this POS figured out	
		//swiWaitForVBlank();
    if ( !(KEYS & KEY_SELECT) && !(KEYS & KEY_START) )
    {
      WAIT_CR &= ~0x8080;
      LOADNDS->ARM9FUNC(BOOT_NDS);
    }
  }

	return 0;
}//end main 