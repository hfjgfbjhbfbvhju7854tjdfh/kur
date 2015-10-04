#include <stdio.h>
#include <string.h>
int main (int cn, char* com[], char* ph[] )
{
printf ("Hello\n ");
if (ph[0] == 0 ) return -1;

while (*ph) {
char *p = strstr (*ph, "PWD=" );
if (p == *ph)
    printf ("path = %s\n", (p+4));
ph++;
}

/*
printf ( "%s\n ", ph[0]  );
printf ( "%s\n ", ph[1]  );
printf ( "%s\n ", ph[2]  );
*/
return 0;
}
