# make file for my  project

all: main.c libmprint.so
	gcc  main.c -o usedso -ldl

m_print.o : m_print.c
	gcc -c -fPIC m_print.c

glob_print.o: glob_print.c
	gcc -c -fPIC glob_print.c

libmprint.so : m_print.o glob_print.o
	gcc -shared -o libmprint.so m_print.o glob_print.o 

#all : main.o libmprint.so
#	gcc -o solibm main.o -L. -lmprint  -Wl,-rpath,.


clean:
	rm -f *.o *.so usedso

.PHONY: clean
