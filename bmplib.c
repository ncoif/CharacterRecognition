#include <stdio.h>
#include <stdlib.h>

#include "bmplib.h"

// ------------------------------------------------------------
// Cet ensemble de fonction ne permet de lire que
// les fichiers .bmp en indexé 2 couleurs (pas de RGB)
// ------------------------------------------------------------

void bmp_setcolor(BMP *bmp, int x, int y, char octet)
{
    int position = 0;
    for(position =0;position < 8;position++)
        bmp->data[bmp->height-y-1][x+(7-position)] =  !( ((1 << position) & octet) >> position  ); //le ième bit de l'octet
}

BMP *bmp_create(int x, int y)
{
    int i;
    BMP *b = (BMP*) malloc(sizeof(BMP));
    b->width  = x;
    b->height = y;
    b->data   = malloc(y*sizeof(int*));
    for(i=0;i<y;i++)
        (b->data)[i] = malloc(x*sizeof(int));

    return b;
}

BMP *bmp_load(char *filename)
{
    BMP *bmp;
    int x, y, a;
    bmpFHEAD h1;
    bmpIHEAD h2;
    char swp;
    char octet;
    int nb_octet;

    FILE *fp = fopen(filename, "r");
    if(fp==NULL)
        printf("Le fichier ' %s ' n'a pu etre ouvert, verifiez qu'il existe bien dans le chemin spécifié !!!\n",filename);

    //FILEHEADER
    fread(&h1.bfType, sizeof(h1.bfType), 1, fp);
    fread(&h1.bfSize, sizeof(h1.bfSize), 1, fp);
    fread(&h1.bfReserved1, sizeof(h1.bfReserved1), 1, fp);
    fread(&h1.bfReserved2, sizeof(h1.bfReserved2), 1, fp);
    fread(&h1.bfOffBits, sizeof(h1.bfOffBits), 1, fp);

    //INFOHEADER
    fread(&h2, sizeof(h2), 1, fp);
    bmp = bmp_create(h2.biWidth, h2.biHeight);

    //decalage de 8 octect correspondant à la palette d'indexage des couleurs
    for(a=0;a<8;a++)
        fread (&swp, sizeof(char), 1, fp);

    for(y=0; y < bmp->height; y++)
    {
        for(x=0; x < bmp->width; x=x+8)
        {
            fread (&octet, sizeof(octet), 1, fp);
            bmp_setcolor(bmp, x, y, octet);
        }

        //La ligne doit avoir un multiple de 4 octets et est complétée par des 0
        nb_octet = (4 - ( (bmp->width+bmp->width%8) /8 )%4 ) %4;
        for (a=0; a<nb_octet; a++)
            fread (&swp, sizeof(char), 1, fp);
    }

    fclose(fp);
    return bmp;
}

void bmp_destroy(BMP *bmp)
{
    int i;
    for(i=0;i<bmp->height;i++)
        free(bmp->data[i]);
    free(bmp->data);
    free(bmp);
}

void bmp_initialize()
{
    //nombre de caractère dans chaque image d'apprentissage
    n_appr[0] = 465;
    n_appr[1] = 445;
    n_appr[2] = 462;
    n_appr[3] = 464;
    n_appr[4] = 429;
    n_appr[5] = 431;
    n_appr[6] = 463;
    n_appr[7] = 464;
    n_appr[8] = 456;
    n_appr[9] = 446;

    //nombre de caractère dans chaque image de reconnaissance
    n_rec[0] = 489;
    n_rec[1] = 452;
    n_rec[2] = 452;
    n_rec[3] = 453;
    n_rec[4] = 431;
    n_rec[5] = 409;
    n_rec[6] = 452;
    n_rec[7] = 449;
    n_rec[8] = 447;
    n_rec[9] = 422;

}

//#define NORMAL 0
//#define DEFAULT 1
void bmp_display(BMP *bmp,int option)
{
    int i,j;

    if(option == NORMAL)
    {
        printf("Taille image: %d × %d\n",bmp->width,bmp->height);
        for(i=0;i<bmp->height;i++)
        {
            for(j=0;j<bmp->width;j++){
                printf("%d ",bmp->data[i][j]);
            }
            printf("\n");
        }
    }
    else //option == DEFAULT
    {
        printf("Taille image: %d × %d\n",bmp->width,bmp->height);
        for(i=0;i<bmp->height;i++)
        {
            for(j=0;j<bmp->width;j++){
                if(bmp->data[i][j]==0)
                printf("  ");
                else
                printf("%d ",bmp->data[i][j]);
            }
            printf("\n");
        }
    }
}

BMP *bmp_select_car(BMP *bmp, int nb_car)
{
    // Attention aux valeurs numériques
    // Le premier caractère est le caractère numéro 0
    // Il y a 465 caractère par fichier (de 0 à 464)

    BMP *caractere;
    int n,p;
    int i,j;

    caractere = bmp_create(64, 64);

    n = nb_car /20;
    p = nb_car % 20;

    for(i=0;i<64;i++)
        for(j=0;j<64;j++)
            caractere->data[i][j] = bmp->data[64*n+i][64*p+j];

    return caractere;
}

BMP *bmp_copy(BMP *image)
{
    int i,j;
    BMP *copy;

    copy = bmp_create(image->width, image->height);
    for(i=0; i < image->height;i++)
        for(j=0;j< image->width;j++)
            copy->data[i][j] = image->data[i][j];

    return copy;
}
