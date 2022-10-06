#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/module.h> /* Needed by all modules */
#include <linux/init.h> /* Needed for the macros */

MODULE_LICENSE("GPL");
MODULE_AUTHOR("CED18I065 Animesh Kumar");
MODULE_DESCRIPTION("Simple Character Device Driver Module");

// max Minor devices
#define MAX_DEV 2

static int my_open(struct inode *inode, struct file *file)
{
	printk("MYCHARDEV: Device open\n");
	return 0;
}

static int my_release(struct inode *inode, struct file *file)
{
	printk("MYCHARDEV: Device close\n");
	return 0;
}

static ssize_t my_read(struct file *file, char __user *buf, size_t count, loff_t *offset)
{
	printk("MYCHARDEV: Device read\n");
	return 0;
}

static ssize_t my_write(struct file *file, const char __user *buf, size_t count, loff_t *offset)
{
	printk("MYCHARDEV: Device write\n");
	return count;
}

// initialize file_operations

static const struct file_operations mychardev_fops = {
.owner = THIS_MODULE,
.open = my_open,
.release = my_release,
.read = my_read,
.write = my_write
};

// device data holder, this structure may be extended to hold additional data
struct mychar_device_data 
{
	struct cdev cdev;
};

// global storage for device Major number
static int dev_major = 0;

// sysfs class structure
static struct class *mychardev_class = NULL;

// array of mychar_device_data for
static struct mychar_device_data mychardev_data[MAX_DEV];

static int __init char_dev_init(void) 
{
	int err, i;
	dev_t dev;

	// allocate chardev region and assign Major number
	err = alloc_chrdev_region(&dev, 0, MAX_DEV, "mychardev");
	dev_major = MAJOR(dev); // kernel does the major number assignment

	// create sysfs class
	mychardev_class = class_create(THIS_MODULE, "mychardev");

	// Create necessary number of the devices
	for (i = 0; i < MAX_DEV; i++) 
	{
		// init new device
		cdev_init(&mychardev_data[i].cdev, &mychardev_fops);
		mychardev_data[i].cdev.owner = THIS_MODULE;
		printk(KERN_ALERT "Major %d: Minor : %d\n", dev_major, i);
		
		// add device to the system where "i" is a Minor number of the new device
		cdev_add(&mychardev_data[i].cdev, MKDEV(dev_major, i), 1);
		device_create(mychardev_class, NULL, MKDEV(dev_major, i), NULL, "mychardev-%d", i);
	}
	printk(KERN_ALERT "Devices Created Successfully");
	return 0;
}

static void __exit char_dev_exit(void) 
{
	int i;
	for (i = 0; i < MAX_DEV; i++) 
	{
		device_destroy(mychardev_class, MKDEV(dev_major, i));
	}

	class_unregister(mychardev_class);
	class_destroy(mychardev_class);

	unregister_chrdev_region(MKDEV(dev_major, 0), MINORMASK);

	printk(KERN_ALERT "Devices Destroyed Successfully");
}

module_init(char_dev_init);
module_exit(char_dev_exit);
