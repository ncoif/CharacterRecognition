#ifndef PRETRAITEMENT_H_INCLUDED
#define PRETRAITEMENT_H_INCLUDED

#include "bmplib.h"

typedef struct
{
  int size;
  int* data;
} VECT;

VECT *vect_create(int n);
void vect_destroy(VECT *v);
void vect_display(VECT *vecteur);

#define PRETRAITEMENT_JETER 1
#define PRETRAITEMENT_INTERSECTION 2
void pretraitement_display(int option);

#define DROITE 1
#define BAS 2
#define GAUCHE 3
#define HAUT 4
#define HORIZONTAL 1
#define VERTICAL 2
VECT *pretraitement_jeter(BMP *caractere,int option);
VECT *pretraitement_intersection(BMP *caractere,int option);

BMP* pretraitement_normalize(BMP *caractere);

#endif // PRETRAITEMENT_H_INCLUDED
