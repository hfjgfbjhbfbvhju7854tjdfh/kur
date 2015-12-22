#include <linux/fs.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/etherdevice.h>

#define NIITM_NAME "MYeth"
#define NDEV_NAME "MyEthernet"

char* buffer;
//char mas [] = "Hello\n";
struct cdev *my_cdev;
dev_t first_node;
int rez;

ssize_t c_read (struct file *name_f, char __user *user, size_t lbuf, loff_t *lof) {
	
  int nbytes; 
  printk (KERN_INFO "Func c_read: %s\n", NIITM_NAME); 
  nbytes = lbuf - copy_to_user (user, buffer, lbuf);  //buffer
  *lof += nbytes;
  return nbytes; 

}


ssize_t c_write (struct file *name_f, const char __user *user, size_t siz, loff_t *lof){
  int nbytes;
  printk (KERN_INFO "Func c_write: %s\n", NIITM_NAME);
  nbytes = siz -copy_from_user(buffer, user, siz);
  *lof += nbytes;
  return nbytes;   
}

int c_open (struct inode *inode_m, struct file *file_m) {
 //printk(KERN_INFO "Open devis c_open()\n");
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

//  eth ****************************************************

struct myeth_dev {
    struct net_device *dev;
    /*
     * Private block
     */
    unsigned long open;
    unsigned long stop;
    unsigned long cnt;
};

struct net_device* myeth_dev = NULL;

int mynet_netdev_open(struct net_device *dev)
{
    //struct mynet_device* priv = netdev_priv(dev);
	
    //priv->open++;
    return 0;
}

int  mynet_netdev_stop(struct net_device *dev)
{
   // struct mynet_device* priv = netdev_priv(dev);
   // priv->stop++;
    return 0;
}

int mynet_netdev_start_xmit(struct sk_buff *skb, struct net_device *dev)
{
    // struct vnet_priv* priv = netdev_priv(dev);
    //priv->xmit++;
    /* free skb */
    dev_consume_skb_any(skb);
	
    printk (KERN_INFO "Enter mynet_netdev_start_xmit () \n");
    return NETDEV_TX_OK;
}

static const struct net_device_ops mynetdev_ops = {
	.ndo_open = mynet_netdev_open,
	.ndo_stop = mynet_netdev_stop,
	.ndo_start_xmit = mynet_netdev_start_xmit,
	//.nod_tx_timeout = mynet_netdev_tx_timeout,
	//.ndo_get_stats =mynet_netdev_get_stats
};

static void mynet_init(struct net_device *dev)
{
    struct myeth_dev* priv = netdev_priv(dev);

    priv->cnt = 0;
    ether_setup(dev);
    dev->watchdog_timeo = 100; //NDEV_TOUT;
    dev->netdev_ops  = &mynetdev_ops;
    dev->flags |= IFF_NOARP;
}

//  **********************************************************

int init__ (void)
{
  
  buffer = kmalloc(PAGE_SIZE, GFP_KERNEL);
  if (buffer==NULL)
  { 
   printk (KERN_INFO "Create buffer error\n");     
   return -ENOMEM;
  }
   register_chrdev (866, "myeth", &chardev_fops);

   first_node = MKDEV(866, 50);	
   register_chrdev_region (first_node, 1, "myeth");
   my_cdev = cdev_alloc();
   cdev_init(my_cdev, &chardev_fops);
   cdev_add (my_cdev,first_node, 1);
   printk (KERN_INFO "loaded: %s\n", NIITM_NAME);
   
   //eth  *****
     myeth_dev = alloc_netdev(sizeof(struct myeth_dev), NDEV_NAME,
		NET_NAME_UNKNOWN, &mynet_init);
  

    if(register_netdev(myeth_dev)) {
	printk(KERN_ERR "netdev register failed\n");
	return -ENODEV;
    }
	
   printk(KERN_INFO "netdev registered success\n");


   return 0;
}

void exit__ (void) 
{
   kfree (buffer);
   cdev_del (my_cdev);
   unregister_chrdev_region (first_node,1);
  printk (KERN_INFO "Unloaded %s\n", NIITM_NAME);

	if (myeth_dev) {
	unregister_netdev (myeth_dev); 
	free_netdev (myeth_dev); 
	printk (KERN_INFO "Unloaded ethernet device %s\n", NIITM_NAME);
	}

	 


}


module_init (init__);
module_exit (exit__);
MODULE_LICENSE("GPL");
