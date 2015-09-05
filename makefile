CFLAGS = -g -Wall

all: aux main
	gcc $(CFLAGS) hospital_list.o bandeijao.o -o program

aux:
	gcc -g -c hospital_list.c

main:
	gcc -g -c bandeijao.c

clean:
	rm *.o

run:
	./program
