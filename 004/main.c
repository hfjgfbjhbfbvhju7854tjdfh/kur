#include <stdio.h>
#include <string.h>


int main (int i, char *v[] ) {

int pid = 0;
FILE *fl =0;
char *ch=0;
char buf_fl[1024];
char *str;
char name[BUFSIZ];

if (i==1){
  printf ("enter argument\n");
  return -1;
 }
if (i>=3) {
 printf ("not correct argument \n"); 
 return -1;
}

pid = atoi (v[1]);
printf ("%d", pid);
nx:  //read ppid 
sprintf (name, "/proc/%d/status", pid );
fl = fopen (name,"r");
if (fl == NULL) {printf ("\nnot open process\n"); return -1;}

if (fread(buf_fl, sizeof(char), 100, fl ) != 100 ) {
  if (feof(fl)) printf ("\nSmol  file\n");
  else printf ("\nFile fatal read\n");
}

 str = strstr( buf_fl, "PPid");
 str =  str + 6;
 pid = atoi(str);

if (pid == 1) {
 printf ("->%d\n", pid );
 fclose (fl);
} else { 
 printf ("->%d", pid);
 goto nx;
}

return 0;
}



//
//printf ("%s\n", str);
//fread ( str, sizeof(char), 5, fl);
