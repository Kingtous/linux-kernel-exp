#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/mm.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <asm/io.h>
#include <asm/switch_to.h>
#include <asm/uaccess.h>
#include <linux/errno.h>
#include <linux/sched.h>

#define MYCDEV_MAJOR 300
#define MYCDEV_SIZE 1024

static int mycdev_open(struct inode *inode,struct file *fp){
	return 0;
}

static int mycdev_release(struct inode *inode,struct file *fp){
	return 0;
}

static ssize_t mycdev_read(struct file *fp,char __user *buf,size_t size,loff_t *pos){
	unsigned long p = *pos;
	unsigned int cnt = size;
	char kernel_buf[MYCDEV_SIZE] = "This is mycdev driver!";
	int i;
	if(p >= MYCDEV_SIZE){
		//overflow
		return -1;
	}
	if(cnt > MYCDEV_SIZE){
		cnt = MYCDEV_SIZE - p;
	}
	if(copy_to_user(buf,kernel_buf,cnt)!=0){
		printk("read error!\n");
		return -1;
	}
	printk("reader: %d bytes was read.\n",cnt);
	return size;
}

static ssize_t mycdev_write(struct file *fp,const char __user *buf,size_t size,loff_t *pos){
	return size;
}

static const struct file_operations mycdev_fops = {
	.owner = THIS_MODULE,
	.open = mycdev_open,
	.release = mycdev_release,
	.read = mycdev_read,
	.write = mycdev_write,
};

static int __init mycdev_init(void){
	printk("mycdev driver is now starting!\n");

	int ret = register_chrdev(MYCDEV_MAJOR,"my_cdev_driver",&mycdev_fops);

	if (ret < 0){
		printk("failed.\n");
	} else {
		printk("register success.\n");
	}
	return 0;
}

static void __exit mycdev_exit(void){
	printk("mycdev driver exiting.\n");
	unregister_chrdev(MYCDEV_MAJOR,"my_cdev_driver");
}


module_init(mycdev_init);
module_exit(mycdev_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Kingtous");
MODULE_DESCRIPTION("mycdev driver test");