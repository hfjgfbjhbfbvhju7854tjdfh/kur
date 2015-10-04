#include <stdio.h>
#include "m_print.h"
#include <dlfcn.h>

void (*my_p)(void);


int main () { 
void *handler;
char *err;

handler = dlopen ("./libmprint.so", RTLD_LAZY);
if (!handler){
 printf ("falid *.so\n");
 return -1;
}
my_p = dlsym (handler, "my_print");
if ((err = dlerror()) != NULL) {
 printf("falid function\n");
// fprintf (stderr,"%s\n", err);
 return -1;
}

(*my_p)();
dlclose(handler);

return 0;

}
