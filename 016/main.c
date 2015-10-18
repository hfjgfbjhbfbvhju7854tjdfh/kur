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

#define BUFSIZE 8094
char ansv [BUFSIZE];

int protocol_http (int sock) {
    

     bytes_read = recv (sock, buf, 1024, 0);
     if (bytes_read <=0 ) {
        printf ("Wrong recv\n");
 	return -1;
	}   
 
     strcpy (ansv, "HTTP/1.1 200 OK\r\n");
	strcpy (ansv, "Server: myLocalHost\r\n");
	strcpy (ansv, "Content-Type: text/html\r\n");     
	strcpy (ansv, "Connection: keep-alive\r\n");
        strcpy (ansv, "\r\n");
	strcpy (ansv, "\r\n");
	fread (ansv, );
          
    
   //  printf ("%s\n", buf);
      send (sock, ansv, bytes_read, 0);
   }

}

int main () {

int sock;
int listener;
char buf [1024];
int bytes_read;
struct sockaddr_in addr;

listener = socket (AF_INET, SOCK_STREAM, 0);
if (listener < 0) {
   printf("Wrong socket\n");
   exit (1);
}

addr.sin_family = AF_INET;
addr.sin_port = htons(10000);
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

   
  protocol_http (sock);
   
   close(sock);

}


return 0;
}
 include <sys/stat.h>

int main (int arg, char* argv[]) {


return 0;
}
