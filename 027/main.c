
#define _GNU_SOURCE
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
#include <sched.h>
#include <sys/utsname.h>

int main (int arg, char * argv[]) {

pid_t pid;
struct utsname uts;


  switch(pid=fork()) {
  case -1:
          printf ("fork is error\n"); /* произошла ошибка */
          exit(1); /*выход из родительского процесса*/
  case 0:
	  unshare (CLONE_NEWUTS);
	const char *str = "my namespas";
	  if (sethostname (str,strlen(str))== -1){
	printf ("sethostname is error");
	}
 	uname(&uts);
	printf ("Процесс потомок uts.nodename =  %s\n", uts.nodename);
          exit(1);
  default:
	uname (&uts);
	printf ("Это процесс-родитель ust.nodename = %s\n", uts.nodename);
     

 }


return 0;
}




