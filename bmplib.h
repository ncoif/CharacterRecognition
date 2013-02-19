#ifndef BMPLIB_H
#define BMPLIB_H

//tableau contenant le nombre d'images de chaque fichier
int n_appr[9];
int n_rec[9];

typedef struct
{
  unsigned short bfType;
  unsigned int   bfSize;
  unsigned short bfReserved1;
  unsigned short bfReserved2;
  unsigned int   bfOffBits;
} bmpFHEAD;

typedef struct bmpIHEAD
{
  unsigned int   biSize;
  int            biWidth;
  int            biHeight;
  unsigned short biPlanes;
  unsigned short biBitCount;
  unsigned int   biCompression;
  unsigned int   biSizeImage;
  int            biXPelsPerMeter;
  int            biYPelsPerMeter;
  unsigned int   biClrUsed;
  unsigned int   biClrImportant;
} bmpIHEAD;

typedef struct
{
  int width;
  int height;
  int** data;
} BMP;

BMP *bmp_create(int x, int y);
void bmp_destroy(BMP *bmp);
BMP *bmp_copy(BMP *image);
void bmp_initialize();

void bmp_setcolor(BMP *bmp, int x, int y, char octet);
BMP *bmp_load(char *filename);

BMP *bmp_select_car(BMP *bmp, int nb_car);

#define NORMAL 0
#define DEFAULT 1
void bmp_display(BMP *bmp,int option);

#endif
