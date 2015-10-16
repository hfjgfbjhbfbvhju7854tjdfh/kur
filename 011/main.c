#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

 ///// GLOBAL VAL  ////////
int pipe_get;  //get from pipe
int pipe_write;  //write to the pipe 

int Goodbye;

//////    pthread   //////
void *tr_get (void* n) {  //get from pipe
 
char bf[110];

  while (1) {
    read (pipe_get,bf, 100);
    bf[100]='\0';
    printf ("%s\n", bf);
  
   if (Goodbye == 1) return ;
  }

}

void *tr_write (void *n) {  //send from stdin to the pipe_write
  
int cn=0;
char buff [100];
   while (1) {
   gets (buff);
   cn = strlen (buff);
   if (-1 == write(pipe_write, buff, cn)) {
       printf("Error in tread tr_write\n");
       pthread_exit(NULL);      
 	}
   
    if (Goodbye == 1) return ;
   }

}


void goodbye (int sig )
 {
if (sig != SIGINT) return ;
 if (sig == SIGINT) Goodbye = 1;
 }


int main (int arg, char* argv[] ) {

pthread_t tr_get_tid;
pthread_t tr_write_tid;

if ((arg<3) || (arg>3)) {
  printf ("Enter 2 pipe chanel\n");
  return -1;
}

if ( access(&argv[1][0], F_OK)<0 ) {
    if (mkfifo(&argv[1][0], 0777) < 0) {
     printf ("Don`t creat fifo\n");
     exit (1);
    }
}

if ( access(&argv[2][0], F_OK) <0) {
    if (mkfifo(&argv[2][0], 0777) < 0) {
     printf ("Don`t creat fifo\n");
     exit (1);
    }
}

pipe_write = open (&argv[1][0], O_RDWR);
if ( pipe_write < 0 ) {
   printf ("Don`t open pipe\n");
   exit(1);
}

pipe_get = open (&argv[2][0], O_RDWR);
if ( pipe_get < 0 ) {
 printf ("Don`t open pipe\n");
 exit(1);
}

//Goodbye = 0;
//signal (SIGINT, goodbye);

pthread_create (&tr_get_tid, NULL, tr_get, NULL );
pthread_create (&tr_write_tid, NULL, tr_write, NULL );


pthread_join (tr_get_tid, NULL);
pthread_join (tr_write_tid, NULL);




return 0;

}
