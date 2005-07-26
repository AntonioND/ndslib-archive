#include <NDS/nds.h>
#include <NDS/ARM9/image.h>
#include <malloc.h>

int loadPCX(unsigned char* pcx, sImage* image)
{
	//struct rgb {unsigned char b,g,r;};
	RGB_24* pal;
	
	PCXHeader* hdr = (PCXHeader*) pcx;

	pcx += sizeof(PCXHeader);
	
	unsigned char c;
	int size;
	int count;
	int run;
	int i;

	image->width  = hdr->xmax - hdr->xmin + 1 ;
	image->height = hdr->ymax - hdr->ymin + 1;

	size = image->width *image->height;
	
	image->data8 = (unsigned char*)malloc(size);
	image->palette = (unsigned short*)malloc(256 * 2);

	if(hdr->bitsPerPixel != 8)
		return 0;
	
	count = 0;

	while(count < size)
	{
		c = *pcx++;
		
		if(c < 192)
			image->data8[count++] = c;

		else
		{
			run = c - 192;
		
			c = *pcx++;
			
			for(i = 0; i < run; i++)
				image->data8[count++] = c;
		}
	}
	
	pal = (RGB_24*)(pcx + 1);

	for(i = 0; i < 256; i++)
		image->palette[i] = RGB15(pal[i].r >> 3 ,pal[i].g >> 3 , pal[i].b >> 3) ;
	
	return 1;
}
