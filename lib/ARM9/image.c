#include <NDS/nds.h>
#include <NDS/ARM9/image.h>
#include <malloc.h>

void image8to16(sImage* img)
 {
	 int i;

	 u16* temp = (u16*)malloc(img->height*img->width*2);
	 
	 for(i = 0; i < img->height * img->width; i++)
		 temp[i] = img->palette[img->data8[i]] | (1<<15);

	 free (img->data8);
	 free (img->palette);

	 img->bpp = 16;
	 img->data16 = temp;
 }

void image8to16trans(sImage* img, u8 transperentColor)
{
	 int i;
	 u8 c;
	 
	 u16* temp = (u16*)malloc(img->height*img->width*2);
	 
	 for(i = 0; i < img->height * img->width; i++)
	 {
		 c = img->data8[i];		
		 
		 if(c != transperentColor) 
			 temp[i] = img->palette[c] | (1<<15);
		 else
			temp[i] = img->palette[c]; 
	 }
	 free (img->data8);
	 free (img->palette);

	 img->bpp = 16;
	 img->data16 = temp;
}
void imageDestroy(sImage* img)
{
	if(img->data8) free (img->data8);
	if(img->palette && img->bpp == 8) free (img->palette);
}
