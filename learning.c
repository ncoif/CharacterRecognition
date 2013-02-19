#include <stdio.h>
#include <stdlib.h>

#include "bmplib.h"
#include "preprocessing.h"
#include "learning.h"

void Write(FILE *fic,int val)
{
    fprintf(fic,"%d ",val);
}

void Write_etiquette(FILE *fic,unsigned int val)
{
    fprintf(fic,"%d      | ",val);
}

void Entete_ppv(FILE *fic)
{
    fprintf(fic,"%s","Classe |  Parametres du traitement\n----------------------------------\n");
}

void load(char *name,unsigned int classe,FILE *fic,int option)
{
    int i,j;
    BMP *pImage = bmp_load(name);
    BMP *pCaractere = NULL;
    VECT *pTraitement = NULL;//for using *pTraitement2; //MODIF VECT
    for(i=0; i<n_appr[classe]; i++)
    {
        pCaractere = bmp_select_car(pImage,i);
        if(option==1)
            pTraitement = pretraitement_jeter(pCaractere,GAUCHE);
        if(option==2)
            pTraitement = pretraitement_jeter(pCaractere,DROITE);
        if(option==3)
            pTraitement = pretraitement_jeter(pCaractere,HAUT);
		if(option==4)
            pTraitement = pretraitement_jeter(pCaractere,BAS);

		Write_etiquette(fic,classe);
        for(j=0; j<DIMENSION_PPV; j++)
        {
            Write(fic,pTraitement->data[j]);
        }
        fprintf(fic,"\n");
    }

    bmp_destroy(pImage);
    bmp_destroy(pCaractere);
    vect_destroy(pTraitement);
}

void load_All(int option,FILE *fic)
{
    load("appr/appr_0.bmp",0,fic,option);
    load("appr/appr_1.bmp",1,fic,option);
    load("appr/appr_2.bmp",2,fic,option);
    load("appr/appr_3.bmp",3,fic,option);
    load("appr/appr_4.bmp",4,fic,option);
    load("appr/appr_5.bmp",5,fic,option);
    load("appr/appr_6.bmp",6,fic,option);
    load("appr/appr_7.bmp",7,fic,option);
    load("appr/appr_8.bmp",8,fic,option);
    load("appr/appr_9.bmp",9,fic,option);
}

/* Apprentissage utilisant le pretraitement 1 */
void learning_knn_1()
{
    FILE *fic;
    fic=fopen("data/learning_knn_1.txt","w");
    Entete_ppv(fic);
    load_All(1,fic);
    printf("Learning done. (Using preprocessing LEFT)\n");
    fclose(fic);

}

/* Apprentissage utilisant le pretraitement 2 */
void learning_knn_2()
{
    FILE *fic;
    fic=fopen("data/learning_knn_2.txt","w");
    Entete_ppv(fic);
    load_All(2,fic);
    printf("Learning done. (Using preprocessing RIGHT)\n");
    fclose(fic);

}

/* Apprentissage utilisant le pretraitement 3 */
void learning_knn_3()
{
    FILE *fic;
    fic=fopen("data/learning_knn_3.txt","w");
    Entete_ppv(fic);
    load_All(3,fic);
    printf("Learning done. (Using preprocessing TOP)\n");
    fclose(fic);

}

/* Apprentissage utilisant le pretraitement 4 */
void learning_knn_4()
{
    FILE *fic;
    fic=fopen("data/learning_knn_4.txt","w");
    Entete_ppv(fic);
    load_All(4,fic);
    printf("Learning done. (Using preprocessing BOTTOM)\n");
    fclose(fic);

}
