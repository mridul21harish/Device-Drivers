#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");

int init(void)
{
	printk("Hello, this kernel is in Mridul's Laptop\n");
	return(0);
}

void cleanup(void)
{
	printk("Goodbye! Come again to visit the kernel in Mridul's Laptop\n");
	return;
}

module_init(init);
module_exit(cleanup);
