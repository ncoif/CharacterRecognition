#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "bmplib.h"
#include "preprocessing.h"

/*
La fonction s'agit d'aggrandir ou  compresser et mouver le chiffre original pour recevoir
un chiffre normalisé.
*/
BMP* pretraitement_normalize(BMP *caractere)
{
    BMP* newcaractere = bmp_create(caractere->height, caractere->width);
    int right=-1, left = caractere->width, low = -1, high = caractere->height;
    int i, j;

    float rate, temp;  // the rate of explanation or repression
    int centerX, centerY;
    int dX, dY; //le mouvement de la pointe centrale.
    int tempX, tempY;
    //left
    int *vecteur = malloc(caractere->height*sizeof(int));
    for(i=0; i<caractere->height; i++)
    {
        j=0;
        while( (j< caractere->width) && (caractere->data[i][j] != 1) )
            j++;
        vecteur[i] = j;
    }
    for(i=0; i<caractere->height; i++)
        if (vecteur[i] < left)
            left = vecteur[i];

    //right
    for(i=0; i<caractere->height; i++)
    {
        j=caractere->width-1;
        while((j>= 0) &&  (caractere->data[i][j] != 1) )
            j--;
        vecteur[i] = j;
    }

    for(i=0; i<caractere->height; i++)
        if (vecteur[i] >right)
            right = vecteur[i];

    //high
    for(i=0; i<caractere->width; i++)
    {
        j=0;
        while(  (j< caractere->height)&&(caractere->data[j][i] != 1) )
            j++;
        vecteur[i] = j;
    }
    for(i=0; i<caractere->width; i++)
        if (vecteur[i] < high)
            high = vecteur[i];

    //low
    for(i=0; i<caractere->width; i++)
    {
        j=caractere->height-1;
        while( (j>= 0) &&(caractere->data[j][i] != 1)  )
            j--;
        vecteur[i] = j;
    }

    for(i=0; i<caractere->width; i++)
        if (vecteur[i] >low)
            low = vecteur[i];

    //Center
    centerX = floor((left+right)/2);
    centerY = floor((high +low)/2);
    dX = 31-centerX;
    dY = 31-centerY;

    //rate
    if (low <62-dY && high >= 2-dY && left >= 2-dX && right <62-dX)
    {
        rate =  (31-2)/(float)(31-high-dY);

        temp = (31-2)/(float)(31-left-dX);
        if (rate > temp)  rate = temp;

        temp = (61-31)/(float)(low-31+dY);
        if (rate > temp)  rate = temp;

        temp = (61-31)/(float)(right-31+dX);
        if (rate > temp)  rate = temp;

    }
    free(vecteur);

    //construit la nouvelle matrice avec le ratio
    newcaractere->height = caractere->height;
    newcaractere->width = caractere->width;
    for (i = 0; i< newcaractere->height; i++)
        for (j = 0; j<newcaractere->width; j++)
        {

            tempX = centerX+(int)ceil((j-31)/rate);
            tempY = centerY+(int)ceil((i-31)/rate);
            if (tempX >= 0 && tempX <= 63 && tempY >= 0 && tempY<=63)

                newcaractere->data[i][j] =caractere->data[tempY][tempX];
            else
                newcaractere->data[i][j] =0;

        }
//    free(caractere);
    return newcaractere;
}


//crée un vecteur de taille n
VECT *vect_create(int n)
{
    int i;
    VECT *v = (VECT*) malloc(sizeof(VECT));
    v->size = n;
    v->data = malloc(n*sizeof(int));
    for(i=0; i<n; i++)
        (v->data)[i] = 0;

    return v;
}

void vect_destroy(VECT *v)
{
    free(v->data);
    free(v);
}

//affiche le vecteur (la taille est déjà donnée par la structure)
void vect_display(VECT *vecteur)
{
    int i;
    printf("Taille du vecteur: %d\n",vecteur->size);
    for(i=0; i<vecteur->size; i++)
        printf("%d ",vecteur->data[i]);
    printf("\n");
}

void pretraitement_display(int option)
{
    if(option == 1)
        printf("Prétraitement utilisé: \"Jeté par la gauche\"\n");
    if(option == 2)
        printf("Prétraitement utilisé: \"Intersections\" \n");
}

// ------------------------------------------------------------
// Jeté par la gauche
// compter au bout de combien de pixels on recontre le premier noir
// retourner un tableau de taille 64
// ------------------------------------------------------------
//#define PRETRAITEMENT_JETER 1
//#define DROITE 1
//#define BAS 2
//#define GAUCHE 3
//#define HAUT 4
VECT *pretraitement_jeter(BMP *car,int option)
{
    BMP *caractere = pretraitement_normalize(car);
	VECT *vecteur = NULL;
    int i,j;
    switch(option)
    {
    case DROITE:
		vecteur = vect_create(caractere->height);
        for(i=0; i<caractere->height; i++)
        {
            j=0;
            while( (j< caractere->width) && (caractere->data[i][caractere->width-j-1] != 1) )
                j++;
            vecteur->data[i] = j;
        }
        break;

    case GAUCHE:
		vecteur = vect_create(caractere->height);
        for(i=0; i<caractere->height; i++)
        {
            j=0;
            while( (j< caractere->width) && (caractere->data[i][j] != 1) )
                j++;
            vecteur->data[i] = j;
        }
        break;

    case HAUT:
		vecteur = vect_create(caractere->width);
        for(j=0; j<caractere->width; j++)
        {
            i=0;
            while( (i< caractere->height) && (caractere->data[i][caractere->height-i-1] != 1) )
                i++;
            vecteur->data[j] = i;
        }
        break;

    case BAS:
		vecteur = vect_create(caractere->width);
        for(j=0; j<caractere->width; j++)
        {
            i=0;
            while( (i< caractere->height) && (caractere->data[i][j] != 1) )
                i++;
            vecteur->data[j] = i;
        }
        break;
    }

    bmp_destroy(caractere);
    return vecteur;
}

// ------------------------------------------------------------
// Intersection
// nombre d'intersections entre une ligne et le caractere
// retourner un tableau de taille 64
// ------------------------------------------------------------
//#define PRETRAITEMENT_INTERSECTION 2
VECT *pretraitement_intersection(BMP *car,int option)
{
    BMP *caractere = pretraitement_normalize(car);
    VECT *vecteur = vect_create(caractere->height);
    int i,j;
    switch(option)
    {
    case HORIZONTAL:
        for(i=0; i<caractere->height; i++)
            for(j=1; j<caractere->width; j++)
            {
                if(caractere->data[i][j] == 1 && caractere->data[i][j-1]!=1)
                    vecteur->data[i]++;
            }
        break;

    case VERTICAL:
        for(i=0; i<caractere->width; i++)
            for(j=1; j<caractere->height; j++)
            {
                if(caractere->data[j][i] == 1 && caractere->data[j-1][i]!=1)
                    vecteur->data[i]++;
            }
        break;
    }

    return vecteur;
}
