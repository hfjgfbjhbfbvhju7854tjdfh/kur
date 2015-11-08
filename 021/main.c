#include <stdio.h> //printf
#include <string.h> //memset
#include <stdlib.h> //exit(0);
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <error.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>


static int cpfun (const void *a, const void *b, void * cnt ) {
 
return memcmp (a, b, *(size_t*) cnt );
  //return strcmp ( *(char* const*)a, * (char* const*)b );
}




int main (int arg, char *argv[] ) {

struct stat sb;
int size_f;
int fd;
char * p;

if (arg != 3) {
 printf ("Enter 2 arguments\n");
 exit (1);
}

fd = open (argv[1], O_RDWR); // O_RDWR
if (fd == -1){
 printf  ("Dont open file\n");
 exit (1);
}

size_f = atoi (argv[2]);
if (size_f >= 257) {
printf ("You mast  enter size < 257 ");
exit (1);
}

if (fstat (fd, &sb) == -1){
  printf ("Wrong status file \n");
  exit (1);
}

p = mmap (0, sb.st_size, PROT_READ | PROT_WRITE, MAP_SHARED,  fd, 0);
if (p == MAP_FAILED) {
  printf ("Wrong in map\n");
  exit (1);
}

if (close (fd) == -1) {
   printf ("Wrong is closed \n");
   exit (1);
}

if (sb.st_size <= size_f) {
 printf ("Size enter is low file\n");
}


/*
int i = 0;
for (i=0; i<sb.st_size; i++) {
 putchar (p[i]);
}
*/

 qsort_r  (p,  sb.st_size/size_f , size_f, cpfun, &size_f); //  sb.st_size/size_f 
printf ("OK\n");

munmap (p, sb.st_size);

return 0;
}
