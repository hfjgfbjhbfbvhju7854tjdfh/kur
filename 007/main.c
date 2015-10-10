#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void *test (void *n) {
 while (1) { 
  printf ("Hello thread\n");  
  printf ("pid=%lu, tid=%lu\n",getpid(), pthread_self() );
  sleep (1);
 }
}



int main (int arg, int *argv[])
{

pthread_t  tid = 0;
int  it;
int status;
int status_addr;
int i = 0;

if (arg !=3) {
  printf ("Enter 2 arguments. N and n \n");
}



  for (i=0; i<10; i++) {
      status = pthread_create( &tid, NULL, test, (void*) &it );
      if( status != 0 ) perror( "pthread_create" ), exit( EXIT_FAILURE ); 
 }

  for (i=0; i<10; i++) {
      status = pthread_join (tid, (void**)&status_addr);
     if (status != 0) {
              printf("main error: can't join thread, status = %d\n", status);
              exit(1);
     }
  }


   

return 0;
}
