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
#include <signal.h>

#define BUFSIZE 8094
char ansv [BUFSIZE];
char bhtml [1024];
int sock;
int bytes_read;
char buf [1024];
char Goodbye;
FILE* ftxt;
FILE* fjpg;
long ftxt_size;
long fjpg_size;
char bjpg  [12000];

int protocol_http (int sock_m, char bhtml[], char bjpg[]) {
    
	char *tm;
        int i = 0;
     bytes_read = recv (sock_m, buf, 1024, 0);
     if (bytes_read <=0 ) {
        printf ("Wrong recv\n");
 	return -1;
	}   
 	
 	for (i=0; i<256+ftxt_size; i++) ansv[i]=0;	
	tm=ansv;
    	sprintf (tm, "HTTP/1.1 200 OK\r\n"
	"Server: myServer\r\n"
	"Content-Length: 160 \r\n"
	"Connection: keep-alive\r\n"
	"Content-Type:text/html; charset=UTF-8\r\n"
	"Keep-Alive: timeout=5, max=97\r\n"
	"\r\n"
	"\r\n"
	"%s"
         , bhtml);
	
	  
      printf ("Server get:\n  %s\n", buf);
      printf ("Server send\n %s\n", ansv);
      send (sock, tm, 256+ftxt_size , 0);	
      send (sock, bjpg, fjpg_size, 0);
   
}

void sigclose(int sig) {
  if (sig == SIGINT) {
     Goodbye = 1;
     exit (1);   
  }
}

int main (int arg, char * argv[]) {

int listener;
struct sockaddr_in addr;
int port;


if ( (arg <2) ||(arg>2)) {
 printf ("Enter one argument: <PORT>\n");
 exit (1);
}

port = atoi (argv[1]);

//signal (SIGINT, sigclose);
//-------------------------------
ftxt = fopen ("index.html", "r");
if (ftxt == NULL){ printf ("read index.html\n");  exit (1);}
fjpg = fopen ("foto.jpeg", "rb");
if (fjpg == NULL){ printf ("no read foto,jpg"); exit(1); }


fpos_t l;
fpos_t ll;
fpos_t* pos_start = &l;
fpos_t* pos_jp = &ll; 

fgetpos (ftxt, pos_start);
fseek (ftxt, 0, SEEK_END);
ftxt_size = ftell (ftxt);
fsetpos (ftxt, pos_start);


fgetpos (fjpg, pos_jp);
fseek (fjpg, 0, SEEK_END);
fjpg_size = ftell (fjpg); 
fsetpos (fjpg, pos_jp);

long tt = ftxt_size;
//printf ("%ld  %ld\n", ftxt_size, fjpg_size);

tt=fjpg_size;
if (fread (bjpg, sizeof(char), tt, fjpg) == 0 ) {
	printf ("Wrong read files: foto.jpg\n");
	exit (1);
}

//printf ("%ld  %ld\n", ftxt_size, fjpg_size);

if (fread (bhtml, sizeof(char), tt, ftxt) == 0) {
	printf ("Wrong read file: index.html 0 \n");
	exit(1);
}

//printf ("%ld  %ld\n", ftxt_size, fjpg_size);

//--------------------------------
listener = socket (AF_INET, SOCK_STREAM, 0);
if (listener < 0) {
   printf("Wrong socket\n");
   exit (1);
}

addr.sin_family = AF_INET;
addr.sin_port = htons(port);
addr.sin_addr.s_addr = htonl(INADDR_ANY);
if (bind (listener, (struct sockaddr*) &addr, sizeof(addr)) ) {
  printf ("Wrong is bind\n");
  exit (1);
}

listen (listener, 1);

while (1) {

  sock  = accept (listener, NULL, NULL);
  if (sock<0) { 
    printf ("Wrong is sock\n");
    exit (1);
   }
  
  
  protocol_http (sock, bhtml, bjpg);
  
  close(sock);
 
 if (Goodbye == 1) break;

}

bye:
close (sock);
fclose (ftxt);
fclose (fjpg);

return 0;
}



