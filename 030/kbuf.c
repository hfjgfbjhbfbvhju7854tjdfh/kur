#include <linux/fs.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/cdev.h>
#include <linux/slab.h>

#define NIITM_NAME "niitm hello"  
#define P_SIZE 64

//struct module *c_owner;  
static char *data;


ssize_t c_read (struct file *name_f, char __user *user, size_t lbuf, loff_t *lof){
  
  //int nbytes = lbuf - copy_to_user ();
   printk (KERN_INFO "Func c_read: %s\n", NIITM_NAME); 
   return 0;
}

ssize_t c_write (struct file *name_f, const char __user *user, size_t siz, loff_t *lof){
   printk (KERN_INFO "Func c_write: %s\n", NIITM_NAME);
   return 0;
}

int c_open (struct inode *inode_m, struct file *file_m) {
 return 0;
} 

int c_release (struct inode * inode_m, struct file * file_m){
 return 0;
}

static const struct file_operations chardev_fops = {
	.owner   = THIS_MODULE,
	.read    = c_read,
	.write   = c_write,
	.open    = c_open,
	.release = c_release
} ;

int init__ (void)
{
   struct cdev *my_cdev;
   dev_t first_node; // = MKDEV (866, 66);
   first_node = MKDEV (866, 66);   
   register_chrdev (866, "kbuf", &chardev_fops);	
   register_chrdev_region (first_node, 1, "mydev");
   my_cdev = cdev_alloc ();
   cdev_init(my_cdev, &chardev_fops);
   cdev_add (my_cdev, first_node, 1);
   data =  kmalloc (P_SIZE, GFP_KERNEL);
   if (data == NULL) printk (KERN_INFO "Error in init__: %s\n", NIITM_NAME); 
   printk (KERN_INFO "loaded: %s\n", NIITM_NAME);
   return 0;
}

void exit__ (void) 
{
  kfree (data);
  printk (KERN_INFO "Unloaded %s\n", NIITM_NAME);
}


module_init (init__);
module_exit (exit__);
