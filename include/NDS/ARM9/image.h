#ifndef IMAGE_H
#define IMAGE_H


//holds a rgb triplet
 typedef struct
 {
    unsigned char r,g,b;
 }__attribute__ ((packed)) RGB_24;
 
 //holds a basic image type for loading image files
 typedef struct 
 {
    short height,width;
    int bpp;
    unsigned short* palette;
 
    union
    {
       unsigned char* data8;
       unsigned short* data16;
       unsigned int* data32;
    };
 
 } sImage, *psImage;

#ifdef __cplusplus
extern "C" {
#endif

void image8to16(sImage* img);
void image8to16trans(sImage* img, u8 transperentColor);
void imageDestroy(sImage* img);


#ifdef __cplusplus
}
#endif


#include <NDS/ARM9/pcx.h>

#endif
