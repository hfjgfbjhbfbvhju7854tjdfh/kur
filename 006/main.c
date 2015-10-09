#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
//#include <sys/types.h>  
#include <errno.h>


int main (int arg, char *argv[]){

pid_t pid = 0;
int sig = 0;
int res = 0;
char ch = 0;
if (arg != 3) {
 printf ("Enter 2 arguments. Pid and Sig\n");
 return -1;
}

pid = atoi (argv[1]);
sig = atoi (argv[2]);
if (pid == 1) { printf ("It is impossible to send a signal to process number 1" );
return 0;
}

printf ("You want to send a signal %d to the procrss %d. y/n :",sig, pid);
ch = fgetc (stdin);

if (ch=='y') {

  res =  kill (pid, sig);
  if (res == 0) { 
    printf ("The command is executed\n");
    return 0; 
  }
  if (res == -1) {
    printf("Erro kill\n");
  }  
 

  switch (errno) {
  case EINVAL :
      printf("The wrong signal type is set.\n");
   break;
  case ESRCH :
     printf ("Process or group don't exist.\n");
  break;
  case EPERM :
     printf ("Process has no sufficient rights in order that \
              to send signals to one of processes receivers.\n");
   break;
  default :
  break; 
  };
  

} else{
 printf ("Goodbye\n");
}


return 0;
   
}






