#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //pour initialiser le générateur aléatoire

#include "bmplib.h"
#include "preprocessing.h"
#include "learning.h"
#include "decision.h"
#include "gui.h"

int main()
{
    srand(getpid());//initialisation de la fonction aléatoire
    bmp_initialize();
    printf("Character Recognition\n");

	learning_knn_1();
	learning_knn_2();
	learning_knn_3();
	learning_knn_4();


/*
    char adresse_image1[30];
    VECT *T=vect_create(10);
    int i,j,test;
    for(i=1; i<10; i++)
    {
        sprintf(adresse_image1, "rec/rec_%d.bmp",i);

        BMP *pImage = bmp_load(adresse_image1);
        for(j=0; j<n_rec[i]; j++)
        {	
			BMP *pCaractere=bmp_select_car(pImage,j);
            test=decision_knn(pImage,5);
            if(test==i)
                T->data[i]++;
			bmp_destroy(pCaractere);
        }
		bmp_destroy(pImage);
        printf("Number of %d recognized: %f\%\n",i,(float)(T->data[i]*100)/(float)(n_rec[i]));

    }
*/

	gui();

    return 0;
}
