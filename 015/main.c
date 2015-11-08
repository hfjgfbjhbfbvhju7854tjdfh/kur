#include <stdio.h> //printf
#include <string.h> //memset
#include <stdlib.h> //exit(0);
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <error.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>


//---------global val ------------------
#define BUF_SIZE 256


typedef struct pap
{
int sock;
struct sockaddr_in* to_me;
struct sockaddr_in* to_other;
}P_t;

P_t pa;

//--------------threads-----------------
void *tr_get (void* n) {
 struct sockaddr_in faddr;
 socklen_t len;
 int nb;
 char bf[BUF_SIZE];
 len =  sizeof (faddr);

  while (1) {
      nb=recvfrom(pa.sock, bf, BUF_SIZE, 0 , (struct sockaddr*)&faddr, &len);
      if (nb <=0) break;
	bf[nb]=0;
        printf(">> %s\n",bf);
  }
return 0;
}


void *tr_send (void *n) {
 int ns;
 char bf[BUF_SIZE]; 

 while (fgets (bf , BUF_SIZE, stdin) != NULL) {
    	ns =sendto( pa.sock, bf, BUF_SIZE, 0, (struct sockaddr*)(pa.to_other), sizeof( struct sockaddr_in));
        if(ns<=0) break;
  }

return 0;
}



 

int main (int arg, char* argv[]) {

struct sockaddr_in to_me;
struct sockaddr_in to_other; 
int in_port;
int out_port;
pthread_t get_tid;
pthread_t send_tid;  
int s;

if (arg<2 || arg>2) {
 printf ("Enter 2 arguments: PORT_IN and PORT_OUT\n");
 exit (1);
}

in_port = atoi (argv[1]);


if (in_port<32675 || in_port>64000) {
   printf ("Enter 32675<out port<64000\n");
   exit(1);
}


 //create a UDP socket
if ((s=socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
    printf ("Soket is wrong\n");
    exit(1);    
}

// zero  the structure
memset((char *) &to_me, 0, sizeof(to_me));
    to_me.sin_family = AF_INET;
    to_me.sin_addr.s_addr = htonl((in_addr_t) INADDR_BROADCAST);
    to_me.sin_port = htons(in_port);

const int optval = 1;
setsockopt (s, SOL_SOCKET, SO_BROADCAST, );

//bind socket to port
//if( bind(s , (struct sockaddr*)&to_me, sizeof(to_me) ) == -1) {
//    printf ("Bind is wrong\n"); exit (1);
// }

pa.sock = s;
pa.to_me = &to_me;


pthread_create (&get_tid, NULL, tr_get, NULL );
pthread_create (&send_tid, NULL, tr_send, NULL );

pthread_join (get_tid, NULL);
pthread_join (send_tid, NULL);



return 0;
}
