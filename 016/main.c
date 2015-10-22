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
/*
char *sumstr (char * t, char* str, int * cnt) {
	int i= 0;
	len = strlen (str);
	for (i = 0; i<=len, i++) {
		
	}
*/

int protocol_http (int sock_m, char bhtml[], char bjpg[]) {
    
	#define text 1
	#define img  2
	#define  err_404  3
        char *tm;
	char *p = NULL;
	int *png = NULL;
        int i = 0;
	int cmd = 0;
        
     png = (int*)  &bjpg[0];
     bytes_read = recv (sock_m, buf, 1024, 0);
     if (bytes_read <=0 ) {
        printf ("Wrong recv\n");
 	return -1;
	}   
 	
 	for (i=0; i<256+ftxt_size; i++) ansv[i]=0;	
	tm=ansv;
 	
	p = strstr(buf, "text" );
	    if (p!=NULL){		
		char *ee = strstr (buf , "index.html");
		if (ee == NULL) cmd = err_404; 		
		else if (ee != NULL) cmd = text;
		}	
	p = strstr(buf, "image"); 
	    if (p!=NULL) cmd = img;
	
     switch (cmd) {
	
	case text :
	{
    	sprintf (tm, "HTTP/1.1 200 OK\r\n"
	"Server: myServer\r\n"
	"Content-Length: %ld \r\n"
	"Connection: keep-alive\r\n"
	"Content-Type:text/html; charset=UTF-8\r\n"
	"Keep-Alive: timeout=5, max=97\r\n"
	"\r\n"
	"\r\n"
	"%s"
	,ftxt_size+256
        ,bhtml);
        printf ("%s\n", buf);
        printf ("%s\n", tm);
        send (sock, tm,256+ftxt_size , 0);
	}
	break;
	
	case img:
	{
	char tmm [340000];	
	char head[512]; //= &tmm[0];
	char* tmj = &head[0]; 
	int len = 0;
    	tmj = stpcpy (tmj, "HTTP/1.1 200 OK\r\n");
	tmj = stpcpy (tmj, "Server: myServer\r\n");
 	tmj = stpcpy (tmj,  "Connection: keep-alive\r\n");
        tmj = stpcpy (tmj, "Content-Type: image/png \r\n");
        tmj = stpcpy (tmj, "Keep-Alive: timeout=5, max=97\r\n\r\n");

	len += strlen ("HTTP/1.1 200 OK\r\n");
	len += strlen ("Server: myServer\r\n");
	len += strlen ("Connection: keep-alive\r\n");
	len += strlen ("Content-Type: image/png \r\n");
	len += strlen ("Keep-Alive: timeout=5, max=97\r\n\r\n");
	
	fread (tmm ,fjpg_size, 1,fjpg);
	send (sock, head, len, 0);	
	send (sock, tmm, fjpg_size, 0);	
       
	printf ("%s\n", buf);
	printf ("%s\n", head);
	printf ("len=%d\n", len);	
	printf ("png = %lu\n", fjpg_size);
	}
	break;
	
	case err_404 :{
	char head[512]; 
	char txt [512];
	char* tmj = &head[0]; 
	int len = 0;
	FILE *e404;
	e404 = fopen ("404.html", "r");
    	tmj = stpcpy (tmj, "HTTP/1.1 200 OK\r\n");
	tmj = stpcpy (tmj, "Server: myServer\r\n");
 	tmj = stpcpy (tmj,  "Connection: keep-alive\r\n");
        tmj = stpcpy (tmj, "Content-Type: text/html \r\n");
        tmj = stpcpy (tmj, "Keep-Alive: timeout=5, max=97\r\n\r\n");

	len += strlen ("HTTP/1.1 200 OK\r\n");
	len += strlen ("Server: myServer\r\n");
	len += strlen ("Connection: keep-alive\r\n");
	len += strlen ("Content-Type: text/html \r\n");
	len += strlen ("Keep-Alive: timeout=5, max=97\r\n\r\n");

	send (sock, head, len, 0);	
	fread (txt, 190, 1, e404);
	send (sock, txt, 190, 0);
	
	printf ("%s", buf);
	printf ("%s\n", head);
	printf ("%s\n", txt);
	}
	break;



	default :
	break;
    }
	  

       	
      //send (sock, bjpg, fjpg_size, 0);
   
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
fjpg = fopen ("linux.png", "rb");
if (fjpg == NULL){ printf ("no read foto,jpg\n"); exit(1); }


fpos_t l;
fpos_t ll;
fpos_t* pos_start = &l;
fpos_t* pos_jp = &ll; 
long tt;

fgetpos (ftxt, pos_start);
fseek (ftxt, 0, SEEK_END);
ftxt_size = ftell (ftxt);
fsetpos (ftxt, pos_start);


fgetpos (fjpg, pos_jp);
fseek (fjpg, 0, SEEK_END);
fjpg_size = ftell (fjpg); 
fsetpos (fjpg, pos_jp);

//printf ("%ld  %ld\n", ftxt_size, fjpg_size);
/*
tt=fjpg_size;
if (fread (bjpg, tt, 1, fjpg) == 0 ) {
	printf ("Wrong read files: foto.jpg\n");
	exit (1);
}
*/

tt = ftxt_size;
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


/*
*/


