#ifndef PCX_H
#define PCX_H
 
typedef struct
{
   char         manufacturer;   //should be 0
   char         version;        //should be 5 
   char         encoding;       //should be 1
   char         bitsPerPixel; //should be 8
   short int    xmin,ymin;      //coordinates for top left,bottom right
   short int    xmax,ymax;     
   short int    hres;           //resolution
   short int    vres;
   char         palette16[48];  //16 color palette if 16 color image
   char         reserved;       //ignore
   char         colorPlanes;   //ignore
   short int    bytesPerLine; 
   short int    paletteYype;   //should be 2
   char         filler[58];     //ignore
}__attribute__ ((packed)) PCXHeader, *pPCXHeader;

#ifdef __cplusplus
extern "C" {
#endif

	int loadPCX(unsigned char* pcx, sImage* image);

#ifdef __cplusplus
}
#endif

#endif

