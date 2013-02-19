#ifndef DECISION_H_INCLUDED
#define DECISION_H_INCLUDED

#include "bmplib.h"
#include "learning.h"

typedef struct
{
  unsigned int Classe;
  VECT *vect;
} Point;

long int distance_2(VECT *a,VECT *b);
void debut_lecture(FILE *fic,int indice);

int decision_knn(BMP *pImage,int NbreVoisin);

#endif // DECISION_H_INCLUDED
