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


int main (int arg, char * argv[]) {
 fd_set rd;
struct term to = {5,0};
char buf [BUFSIZ];

  if (arg < 3 || arg > 3){
printf ("Enter: chanName1 chanName2\n");
} 

int p1 = open (argv[1], O_RDWR);
int p2 = open (argv[2], O_RDWR);

while (true) {
    FD_ZERO (&rd);
    FD_SET (p1, &rd);
    FD_SET (p2, &rd);

to.tv_sec= 5;

ready =select (10, &rd, NULL, NULL, &to);

if (!ready) {
  printf ("Nothing\n");
  continue;
}

if (FD_ISSET (p1, &rd)) {
	read (p1, buf, BUFSIZ);
	printf ("p1: have got %s\n", buf);
}

if (FD_ISSET (p2, &rd)) {
  read (p2, buf, BUFSIZ);
  printf ("p2: have got %s\n", buf);
}



}//while

return 0;
}




