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

///////  thread and function   /////////////////////////////
void *tr_read (void *n) {
   static int i = 0;
   pthread_mutex_t * mtx = &res.mutex; 
   while (!goodbye) { 
     pthread_mutex_lock (mtx);
     if (res.resurs[i] == 1) {
      res.resurs[i] = 0;  
      }
      i++;
     if (res.max == i) i = 0;
     pthread_mutex_unlock (mtx);  
     sleep (1);
  }

}


void *tr_write (void *n) {
   static int t = 0;  
   while (!goodbye) {
    pthread_mutex_lock (&res.mutex);
    if (res.resurs[t] == 0) {
     res.resurs[t] = 1;
     }
    t++;
    if ( res.max == t) t = 0;
    pthread_mutex_unlock (&res.mutex);
    sleep (1);
   }
}

/*
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
*/
void sigfunc (int sig) {
 if (sig != SIGINT ) return ;
 else goodbye = 1;

}



///////////  main   ///////////////////////////////
int main (int arg, char *argv[]) {


if ( (arg > 3) || (arg <3)) {
 printf ("Enter 2 arguments. read writes \n");
 return 0;
}

int shmid;
char *shm;
int SHMSZ = 0;
key_t key = 5678;
int i =0;
int status;
int max;
int reads;
int writs;
pthread_t *read_tid;
pthread_t *write_tid;
//pthread_t *consol_tid;  

reads =  atoi (argv [1]);
writs =  atoi (argv [2]);
goodbye = 0;
res.max= 10;


if ( ( shmid = shmget (key, res.max, IPC_CREAT | 0666) )  <0) {
printf ("Error shared memory\n");
exit(1);
}

if (( shm = shmat(shmid, NULL, 0) ) == (char*)-1) {
printf ("Error get shared memory\n");
exit (0);
}

/*
res.resurs = (int*)  calloc(max,sizeof(int));
if (res.resurs == NULL){ printf ("res.resurs is wrong\n"); return 0; }
*/

res.resurs = shm;

read_tid = (pthread_t*) calloc (reads, sizeof(pthread_t));
if (read_tid == NULL){ printf ("read_tid is wrong\n"); return 0; }

write_tid = (pthread_t*) calloc (writs , sizeof (pthread_t));
if (write_tid == NULL){ printf ("res.mutex is wrong\n"); return 0; }

/*
consol_tid = (pthread_t*) calloc (1 , sizeof (pthread_t));
if (consol_tid == NULL){ printf ("res.mutex is wrong\n"); return 0; }
*/
signal (SIGINT, sigfunc);

///    read  thread  ///////////////////
  for (i=0; i<reads; i++) {
      status = pthread_create( &read_tid[i], NULL, tr_read, (void*) res.resurs); // int *resurs;
      if( status != 0 ) perror( "pthread_create" ), exit( EXIT_FAILURE );
 }



///   write   thread   //////////////////
    for (i=0; i<writs; i++) {
       status = pthread_create( &write_tid[i], NULL, tr_write, (void*) res.resurs); // 
       if( status != 0 ) perror( "pthread_create" ), exit( EXIT_FAILURE );
  }



////    consol thread    ///////////////
//       status = pthread_create( consol_tid, NULL, tr_consol, (void*) res.resurs); //
//       if( status != 0 ) perror( "pthread_create" ), exit( EXIT_FAILURE );


 for (i=0; i<reads; i++) { // read
     status = pthread_join (read_tid[i], NULL ); 
     if (status != 0) {
              printf("Can't join thread, status = %d\n",i);
              exit(1);
     }
  }


 for (i=0; i<reads; i++) {  // write
       status = pthread_join (write_tid[i], NULL ); 
      if (status != 0) {
               printf("Can't join thread, status = %d\n",i);
               exit(1);
      }
   }
 
  
/* status = pthread_join (*consol_tid, NULL );   // consol
 if (status != 0) {
     printf("Can't join thread, status = %d\n",i);
     exit(1); }
*/

printf ("\nProgram tread is END\n");
//free (res.resurs);
shmdt (res.resurs);
free (write_tid);
free (read_tid);
//free (consol_tid);
return 0;
}
