#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>


////////  global variable   ///////////////////
typedef struct  _resurs_t {
   int *resurs;
   pthread_mutex_t *mutex;
   int max;
}resurs_t;

resurs_t res;
int goodbye;

///////  thread and function   /////////////////////////////
void *tr_read (void *n) {
   static i = 0;
   pthread_mutex_lock (res.mutex);
   if (res.resurs[i]) {
    res.resurs[i] = 0;  
    }
   i++;
   pthread_mutex_unlock (res.mutex); 
    
   if (res.max == i) i = 0;

   if (goodbye == 1) exit(1);

}


void sigfunc (int sig) {
 if (sig != SIGINT ) return ;
 else goodbye = 1;

}

///////////  main   ///////////////////////////////
int main (int arg, char *argv[]) {


if ( (arg > 4) || (arg <4)) {
 printf ("Enter 3 arguments. read writes max\n");
 return 0;
}


int i =0;
int status;
int max;
int reads;
int writs;
pthread_t *read_tid;
pthread_t *write_tid;

reads =  atoi (argv [1]);
writs =  atoi (argv [2]);
max = atoi (argv[3]);
goodbye = 0;

res.resurs = (int*)  calloc(max,sizeof(int));
res.mutex = (pthread_mutex_t*)  calloc(1, sizeof(pthread_mutex_t));
read_tid = (pthread_t*) calloc (reads, sizeof(pthread_t));
write_tid = (pthread_t*) calloc (writs , sizeof (pthread_t));

  for (i=0; i<reads; i++) {
      status = pthread_create( &read_tid[i], NULL, tr_read, (void*) res.resurs); // int *resurs;
      if( status != 0 ) perror( "pthread_create" ), exit( EXIT_FAILURE );
 }


 for (i=0; i<reads; i++) {
      status = pthread_join (read_tid[i], NULL ); //(void**)&status_add);
     if (status != 0) {
              printf("Can't join thread, status = %d\n",i);
              exit(1);
     }
  }


signal (SIGINT, sigfunc);

while (goodbye==0); //delay

free (res.resurs);
free (res.mutex);
free (write_tid);
free (read_tid);
return 0;
}
