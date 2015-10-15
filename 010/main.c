#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 8192

int main (int arg, char *argv[] )
{

FILE *fl;
int counter = 0;
char buff [MAX];

if (arg<3 || arg>3) {
 printf ("Enter 2 argumentd: string and filename");
 return 0;
}

fl = fopen (argv[2], "w");
if (fl == NULL) {
  printf ("File %s not open\n", argv[2]); return -1;
}


while (fgets (buff, MAX, stdin)) {
    fputs (buff, stdout);
    if ( strstr(buff, argv[1]) ) {
       counter++;
    }
}

if (counter) {
   fprintf (fl,"Sting %s, found %d\n", argv[1], counter);
} else {
 fprintf (fl, "String %s, not found\n", argv[1]);
}


fclose (fl);
return  0;
}
