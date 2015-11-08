#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <linux/sched.h>


#define STACK_SIZE (1024*1024)


static int my_thread (void* arg) {

	while (1) {
	printf ("Hello clone\n");
	sleep (1);
	}

}



int main (int arg, char* argv[]) {

pid_t pid;
char *stack;
int clon_pid;


stack = malloc (STACK_SIZE);
if (stack)


pid = clone ( my_thread, stack, CLONE_VM | CLONE_FILES  , (void*)&clon_pid );

if (pid = -1) {
	printf("Can`t creat clone\n");
	exit (-1);
}


if ( waitpid (pid, NULL, 0) == -1){
	printf ("Wrong close\n");
}


exit (EXIT_SUCCESS);


return 0;
}

