#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h> 
#include <string.h>

#define MAX 1024

int main (int arg, char *argv[] )
{

FILE *pip_w;
FILE *fl;
char buff [MAX];
char buff_all [MAX];
int i = 0;
int n = 0;

pip_w= popen (argv[1], "r");
if (pip_w == NULL) { printf ("exit fl == NULL\n"); return 0;}

while ( fgets (buff, MAX, pip_w ) ) { 
n= strlen (buff);

for (i=0; i<n; i++) {
  char p;
  p = buff [i];
  buff_all [n-i-1] = p;
}

buff_all [n] = 0;
printf ("%s\n", buff_all);

}

//printf("\n");

pclose(pip_w);

return 0;
}
