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
#include <signal.h>
#include <sys/select.h>


char buf [16];
int fd;

int main (int arg, char * argv[]) {

 if (arg != 3) {
  printf ("Enter 2 argument\n");
  exit (1);
}  

strcpy (buf, argv[1]);

fd = open ("/dev/myeth", O_RDWR);
if(-1 == fd) {
  printf("Error open devise\n");
  exit (1);
}


/// write to driver
if (0 == strcmp (buf , "wr") ){
 int cnt = strlen (argv[2]);
 write ( fd, argv[2], cnt ); 
 printf ("write buffer\n"); 
}

///   read from driver
if (0 == strcmp(buf, "rd")) {
char tmp[10];
int siz;
  int cnt = atoi (argv[2]);
  printf ("read %d\n", cnt);
  siz = read ( fd, tmp, cnt );
  
  if (siz == 0) {
  printf ("Error read\n");
  return 0;
  }

printf ("%s\n", &tmp[0]);
}

return 0;
}
