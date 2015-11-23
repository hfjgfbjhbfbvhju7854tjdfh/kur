#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <syslog.h>


const char *srt;
int cnt;


void sig_cnt (int sig) {
cnt++;

}

void sig_fn (int sig) {
openlog ("log", LOG_PID, LOG_USER);
syslog (LOG_INFO, "Sig = %d", cnt);
closelog ();
exit(0);
}



int main (int arg, char * argc[]) {

int status;
int pid;

//if (arg != 2) {
//	printf ("Enter: file.log\n");
//	return -1;
//}


pid = fork ();

if (pid == -1) {
printf ("Faled fork\n");
}

if (!pid) {

setsid ();
//signal (SIGTERM, sig_fn);  //cntr+c  15
signal (SIGUSR1, sig_fn);  //  10
signal (SIGUSR2, sig_cnt);  //  12

close (STDIN_FILENO);
close (STDOUT_FILENO);
close (STDERR_FILENO);

openlog ("test", LOG_PID, LOG_USER);
syslog (LOG_INFO, "Prog is load");
closelog ();


while (1) {
   
}

return 1;

} else  {
  return 0;  //perenc dead
}

return 0;
}
