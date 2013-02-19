#include <stdio.h>
#include "gui.h"

void gui()
{
	//create a new gui
	SDL_Surface *ecran = NULL;
    SDL_Init(SDL_INIT_VIDEO);
 
    ecran = SDL_SetVideoMode(PIXEL_SIZE * IMAGE_WIDTH, PIXEL_SIZE * IMAGE_HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

	SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));	
	SDL_Flip(ecran);

	SDL_WM_SetCaption("Character Recognition", NULL);


	//main loop
    int continuer = 1;
    SDL_Event event;
 
	int x=0,y=0;
	SDL_Surface *pixel = SDL_CreateRGBSurface(SDL_HWSURFACE, PIXEL_SIZE, PIXEL_SIZE, 32, 0, 0, 0, 0); //pixel black
	SDL_Rect position;

	int i=0, j=0;
	BMP* draw = bmp_create(IMAGE_HEIGHT, IMAGE_WIDTH);
	for(i = 0; i < draw->height ; i++)
		for(j = 0; j < draw->width ; j++)
			draw->data[i][j] = 0;

	printf("Draw with the mouse.\nPress ENTER to recognize.\nPress ESC to clean.\n");

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
				printf("Exiting the application\n");
                continuer = 0;
				break;

			case SDL_MOUSEMOTION: //draw the character
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					x = event.motion.x / PIXEL_SIZE;
					y = event.motion.y / PIXEL_SIZE;
					//printf("pixel: (%d,%d)\n",x,y);
	
					//fill the pixel in black on the screen
					position.x = event.motion.x - (PIXEL_SIZE/2); 
					position.y = event.motion.y - (PIXEL_SIZE/2);
					SDL_FillRect(pixel, NULL, SDL_MapRGB(ecran->format, 0, 0, 0)); 
					SDL_BlitSurface(pixel, NULL, ecran, &position);
					SDL_Flip(ecran);

					//fill the pixel in black in the bmp
					draw->data[y][x] = 1;
				}
        		break;

			case SDL_KEYDOWN:
        		switch(event.key.keysym.sym)
        		{
            		case SDLK_RETURN: // Enter for recognition
						printf("KNN think that this character is a \"%d\".\n",decision_knn(draw,5));
                		break;

            		case SDLK_ESCAPE: // Echap for fill of white
						printf("Cleaning the screen\n");

						//reinitializing the screen
						SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));	
						SDL_Flip(ecran);

						//reinitializing the bmp
						for(i = 0; i < draw->height ; i++)
							for(j = 0; j < draw->width ; j++)
								draw->data[i][j] = 0;
                		break;
       			}
        		break;
        }
    }

	SDL_FreeSurface(pixel);
	SDL_Quit();
	bmp_destroy(draw);
}
