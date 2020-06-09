#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

static int __init hello_init(void){
	printk("This is Kingtous' Kernel, Welcome!\n");
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

