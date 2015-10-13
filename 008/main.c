#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>


int main (int i, char *v[] ) {

int pid = 0;
FILE *fl =0;
char *ch=0;
char buf_fl[1024];
char *str;
char name_dir[BUFSIZ];
struct dirent *entry;
DIR *dir;

if ((i<2) || (i>2)){
  printf ("enter 1 argument: Pid\n");
  return -1;
 }

pid = atoi (v[1]);
printf ("user pid->%d\n", pid);

  sprintf (name_dir, "/proc/%d/task/", pid);
  dir = opendir (name_dir);
  if (dir == NULL) {printf("ERROR: open dir task\n"); exit(1); }
    
  while ( (entry = readdir(dir)) != NULL) {
    if ( atoi(entry->d_name) )
      printf ("--->task = %s\n",entry->d_name);
  }




return 0;
}

