SinaKasraA1: SinaKasraA1.o SinaKasraA1Main.o
	gcc SinaKasraA1.o SinaKasraA1Main.c -o SinaKasraA1 -lm
SinaKasraA1A1.o: SinaKasraA1.c givenA1.h
	gcc -Wall -std=c99 -c SinaKasraA1.c
SinaKasraA1Main.o: SinaKasraA1Main.c givenA1.h
	gcc -Wall -std=c99 -c SinaKasraA1Main.c
clean:
	rm *.o SinaKasraA1