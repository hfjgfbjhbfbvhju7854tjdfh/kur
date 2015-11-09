
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>



////////  global variable   ///////////////////
typedef struct  _resurs_t {
   char *resurs;
   pthread_mutex_t mutex;
   int max;
}resurs_t;

resurs_t res;
int goodbye;
///////////////////////////////////////////////

void *tr_consol (void *n) {
   static int y = 0;
   int ii = 0;  
   int one = 0;
   int zero = 0;
   while (!goodbye) { 
     pthread_mutex_lock (&res.mutex);
     for (ii=0; ii<res.max; ii++) {
     if (res.resurs[ii] == 1) one++;  
     if (res.resurs[ii] == 0) zero++;      
    }
     printf ("Summ \"1\" = %d\n", one);
     printf ("Summ \"0\" = %d\n", zero);
     y++; zero = 0; one = 0;
     if (res.max == y) y = 0;
     pthread_mutex_unlock (&res.mutex);
     sleep (1);
    }
}


void sigfunc (int sig) {
 if (sig != SIGINT ) return ;
 else goodbye = 1;

}


int main () {


int shmid;
char *shm;
int SHMSZ = 0;
key_t key = 5678;
pthread_t *consol_tid;

res.max = 10;

if ( ( shmid = shmget (key, res.max, 0666) )  <0) {
printf ("Error shared memory\n");
exit(1);
}

if (( shm = shmat(shmid, NULL, 0) ) == (char*)-1) {
printf ("Error get shared memory\n");
exit (0);
}

res.resurs = shm;

consol_tid = (pthread_t*) calloc (1 , sizeof (pthread_t));
if (consol_tid == NULL){ printf ("res.mutex is wrong\n"); return 0; }


signal (SIGINT, sigfunc);

////    consol thread    ///////////////
   int status = pthread_create( consol_tid, NULL, tr_consol, (void*) res.resurs); //
       if( status != 0 ) perror( "pthread_create" ), exit( EXIT_FAILURE );

status = pthread_join (*consol_tid, NULL );   // consol

free (consol_tid);
printf ("\nEnd prog mon\n");
return 0;
}
