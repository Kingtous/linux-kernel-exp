#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

static int debug = 1;
module_param(debug,int,0644);
MODULE_PARM_DESC(debug,"debugging infomation");

#define dprintk(args...) if(debug){printk(KERN_DEBUG args);}

static int myparm = 10;
module_param(myparm,int,0644);
MODULE_PARM_DESC(debug,"myparm");

static int __init hello_init(void){
	dprintk("This is Kingtous' Kernel, Welcome!\n");
	dprintk("myparm : %d\n",myparm);
	return 0;
}

static void __exit hello_exit(void){
	printk("Kingtous: Good Bye...\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("LGPL");
MODULE_AUTHOR("Kingtous");
MODULE_DESCRIPTION("Hello Kingtous' Module");
MODULE_ALIAS("kingtous");
