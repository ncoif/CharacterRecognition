#makefile
#define the variables
CC = gcc
#CFLAGS = -lm -O2
CFLAGS = -lm -O2 `sdl-config --cflags --libs` -lSDL

#all
all: main.o bmplib.o preprocessing.o decision.o learning.o gui.o
	$(CC) $^ -o CharacterRecognition $(CFLAGS)

bmplib.o: bmplib.c bmplib.h

preprocessing.o: preprocessing.c preprocessing.h bmplib.h

learning.o: learning.c learning.h bmplib.h preprocessing.h

decision.o: decision.c decision.h bmplib.h preprocessing.h learning.h

gui.o: gui.c gui.h bmplib.h

main.o: main.c bmplib.h preprocessing.h learning.h decision.h

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)
 	   	 
# clean
clean:
	rm -rf *.bak rm -rf *.o rm -rf *~
 	   	 	 
# mrproper
mrproper: clean CharacterRecognition
