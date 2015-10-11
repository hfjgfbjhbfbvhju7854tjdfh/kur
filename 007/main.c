#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

struct box_tr {
	double right;
	double left;
	double result;
	pthread_t  tid ;
};

int N;
int n;
typedef struct box_tr box_tmp;

void *test (void *n) {
  double delta; 
  double sq;
  int X = 10;
  box_tmp *tmp = (box_tmp*) n;
  delta = tmp->right - tmp->left;
  sq = delta * X;
  tmp->result = sq;
 // sleep (90);
 
}



int main (int arg, char *argv[])
{

int it;
int status;
int status_addr;
int i = 0;
double res=0;

if (arg !=3) {
  printf ("Enter 2 arguments. N and n \n");
 return 0;
}
if (arg > 3) {
 printf ("Enter 2 arguments. N and n\n");
 return 0;
}

N = atoi(argv[1]);  // правая граница 
n = atoi(argv[2]);  // колличесво патоков

if ((n == 0) || (n > 63)) {
 printf ("Enter n < 64 and n != 0\n "); 
 return 0;
}

n = n - 1;

struct box_tr box_tread [64];

  for (i=0; i<n; i++) {
      box_tread[i].left =((double)N/n)*i;
      box_tread[i].right =((double)N/n)*(i+1);  
      status = pthread_create( &box_tread[i].tid, NULL, test, (void*) &box_tread[i] );
      if( status != 0 ) perror( "pthread_create" ), exit( EXIT_FAILURE ); 
 }

  for (i=0; i<n; i++) {
      status = pthread_join (box_tread[i].tid, NULL ); //(void**)&status_addr);
     if (status != 0) {
              printf("Can't join thread, status = %d\n",i);
              exit(1);
     }
  }
   
  for (i=0; i<n; i++){
     res += box_tread[i].result;  
  }

printf ("resultat = %f\n", res);

return 0;
}
