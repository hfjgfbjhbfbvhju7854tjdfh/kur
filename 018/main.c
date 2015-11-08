#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

void sig_fn (int sig) {
FILE *f;
char buf[] = "Hello";
f = fopen ("log", "w+");
fwrite (buf,5,1,f);
fclose (f);
exit(0);
}



int main (int arg, char * argc[]) {

int status;
int pid;

if (arg != 2) {
	printf ("Enter: file.log\n");
	return -1;
}



pid = fork ();

if (pid == -1) {
printf ("Faled fork\n");
}

if (!pid) {

setsid ();
signal (SIGTERM, sig_fn);  //cntr+c

close (STDIN_FILENO);
close (STDOUT_FILENO);
close (STDERR_FILENO);

while (1) {
   
}

return 1;

} else  {
  return 0;  //perenc dead
}

return 0;
}
