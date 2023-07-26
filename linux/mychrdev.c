#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/cdev.h>

static char *kbuf;
static dev_t first;
static unsigned int count = 1;
static int my_major = 511, my_minor = 0;
static struct cdev *my_cdev;

#define MYDEV_NAME "mychrdev"
#define KBUF_SIZE (size_t) ((10) * PAGE_SIZE)

static int mychrdev_open(struct inode *inode, struct file *file)
{

	printk(KERN_INFO "Opening device: %s \n\n", MYDEV_NAME);
	return 0;
}

static int mychrdev_release(struct inode *inode, struct file *file)
{

	printk(KERN_INFO "Release device: %s \n\n", MYDEV_NAME);
	return 0;
}

static ssize_t mychrdev_read(struct file *file, char __user *buf, size_t lbuf, loff_t *ppos)
{
	ssize_t readed = 0;
	printk(KERN_INFO "Read device: %s \n at pos %lld\n", MYDEV_NAME, *ppos);
	if (file->f_pos < 12){
		strcpy(buf,"hello world");
		readed = 12;
		(*ppos) += 12;
	}
	return readed;
}

static ssize_t mychrdev_write(struct file *file, const char __user *buf, size_t lbuf, loff_t *ppos)
{

	printk(KERN_INFO "Write device: %s \n\n", MYDEV_NAME);
	return 55;
}
static void cleanup_chrdev(void)
{
	if(kbuf) kfree(kbuf);
	printk(KERN_INFO "Bye , unloading");
}

const struct file_operations mycdev_fops = {
	.owner = THIS_MODULE,
	.read = mychrdev_read,
	.write = mychrdev_write,
	.open = mychrdev_open,
	.release = mychrdev_release};


static int init_chrdev(void)
{

	printk(KERN_INFO "Hello, loading");
	kbuf = kmalloc(KBUF_SIZE, GFP_KERNEL);

	first = MKDEV(my_major, my_minor);
	register_chrdev_region(first, count, MYDEV_NAME);

	my_cdev = cdev_alloc();

	cdev_init(my_cdev, &mycdev_fops);
	cdev_add(my_cdev, first, count);

	return 0;
}

module_init(init_chrdev);
module_exit(cleanup_chrdev);

MODULE_LICENSE("GPL");
