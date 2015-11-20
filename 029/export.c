#include <linux/module.h>
#define NIITM_NAME "niitm hello"


int load_print (void)
{
   printk (KERN_INFO "loaded: %s\n", NIITM_NAME);
   return 0;
}

void exit_print (void) 
{
  printk (KERN_INFO "Unloaded %s\n", NIITM_NAME);
}

void printer(void)
{
	printk(KERN_INFO, "hello");	
}


EXPORT_SYMBOL(printer)

module_init (load_print);
module_exit (exit_print);


