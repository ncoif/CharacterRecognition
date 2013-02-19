#include <stdio.h>
#include <stdlib.h>

#include "bmplib.h"
#include "preprocessing.h"
#include "decision.h"

void debut_lecture(FILE *fic,int indice)
{
    char str[80];
    int i;

    for(i=0; i<indice; i++)
        fscanf (fic, "%s",str);
}

long int distance_2(VECT *a,VECT *b)
{
    int i;
    long int distance=0;
    for(i=0; i<a->size; i++)
        distance+=(a->data[i]-b->data[i])*(a->data[i]-b->data[i]);

    return distance;
}

Point lecture_ppv(FILE *fic)
{
    char temp[50];
    int i,val;
    VECT *vect=vect_create(DIMENSION_PPV);
    Point point;

    fscanf(fic,"%d",&val);
    point.Classe=val;
    fscanf(fic,"%s",temp);

    for(i=0; i<DIMENSION_PPV; i++)
    {
        fscanf(fic,"%d",&val);
        vect->data[i]=val;
    }
    point.vect=vect;

    return point;
}

void initialise(int *vect,int size,long int valeur)
{
    int i;
    for(i=0; i<size; i++)
    {
        vect[i]=valeur;
    }
}

int vote_majoritaire(VECT *vect)
{
    int i,max;
    VECT *T=vect_create(10);

    for(i=0; i<vect->size; i++)
        T->data[vect->data[i]]++;

    max=0;
    for(i=0; i<T->size; i++)
        if(T->data[max]<T->data[i])
        {
            max=i;
        }

	vect_destroy(T);
    return max;
}


int decision_knn(BMP *pCaractere,int NbreVoisin)
{
    FILE *fic1,*fic2;
    int i,j,distance,ind_max;//,distance_sup;
    long int d_max;

    VECT *C=vect_create(NbreVoisin);
    int *D=malloc(NbreVoisin*sizeof(long int));
    initialise(D,NbreVoisin,200000);

    VECT *pTraitement1,*pTraitement2;
    Point point,point2;

	fic1=fopen("data/learning_knn_1.txt","r");
    pTraitement1 = pretraitement_jeter(pCaractere,GAUCHE);
    
    fic2=fopen("data/learning_knn_2.txt","r");
    pTraitement2 = pretraitement_jeter(pCaractere,DROITE);

    debut_lecture(fic1,6);
    debut_lecture(fic2,6);

    for(i=0; i<4527; i++)
    {
        d_max=D[0];
        ind_max=0;
        for(j=0; j<NbreVoisin; j++)
            if(d_max<D[j])
            {
                d_max=D[j];
                ind_max=j;
            }

        point=lecture_ppv(fic1);
        point2=lecture_ppv(fic2);

        distance=distance_2(point.vect,pTraitement1);
		//vect_destroy(point.vect);

        distance+=distance_2(point2.vect,pTraitement2);
		//vect_destroy(point2.vect);

		//free the vect of the point
		//vect_destroy(point.vect);
		//vect_destroy(point2.vect);


        if(distance<d_max)
        {
            C->data[ind_max]=point.Classe;
            D[ind_max]=distance;
        }
    }
    fclose(fic1);
    fclose(fic2);


	int result = vote_majoritaire(C);

	vect_destroy(C);
	free(D);
	vect_destroy(pTraitement1);
	vect_destroy(pTraitement2);

	return result;
}
