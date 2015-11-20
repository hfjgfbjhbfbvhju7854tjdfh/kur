#include <linux/module.h>
#include "export.h"
#define NIITM_NAME "niitm hello"


int init__ (void)
{
	niitm_init (); 
   //printk (KERN_INFO "loaded: %s\n", NIITM_NAME);
   return 0;
}

void exit__ (void) 
{
   niitm_exit ();
  //printk (KERN_INFO "Unloaded %s\n", NIITM_NAME);
}

module_init (init__);
module_exit (exit__);


