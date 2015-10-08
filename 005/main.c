#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>


void sigfunc (int sig) {
  if (sig != SIGINT) {
  return ;  
  } else {
    printf ("\nGoodbye\n");
    exit (0);
  }

}


int main (void) {

 int i;
 char buf [256];
 char path [256];
 
 signal (SIGINT, sigfunc);

path[0]=0;
sprintf(path,"%s:%s",getenv("PATH"),getcwd(buf,256));
setenv("PATH",path,1);


 printf ("### Shell ###\n");

while (1) {
 printf (">>");
 fgets (buf, 20, stdin);
 if (buf == "") printf ("\n>>"); 
 system (buf);
 for (i=0; i<256; i++){ buf[i]=0;}
}

  return 0;
}



//
// scanf ("%s %s", buf, par);
// printf ("%s\n", buf);
