#include <linux/fs.h>
#include <linux/init.h>
#include <linux/miscdevice.h>
#include <linux/module.h>
#include <asm/uaccess.h>


static ssize_t buben_read(struct file * file, char * buf,
         size_t count, loff_t *ppos)
{

    char *buben_str = "Buben is works!\n";
    int len = strlen(buben_str);
    if (count < len)
         return -EINVAL;
    if (*ppos != 0)
         return 0;
    if (copy_to_user(buf, buben_str, len))
         return -EINVAL;
    *ppos = len;
    return len;
}

static const struct file_operations buben_fops = {
         .owner    = THIS_MODULE,
         .read    = buben_read,
};

static struct miscdevice buben_dev = {
         MISC_DYNAMIC_MINOR,
         "buben",
         &buben_fops
};



static int __init
buben_init(void)
{
    int ret;
    ret = misc_register(&buben_dev);
    if (ret)
    printk(KERN_ERR
     "Unable to register buben device\n");
    return ret;
    printk("Buben in work!\n");
    return 0;
}

module_init(buben_init);


static void __exit
buben_exit(void)
{
    misc_deregister(&buben_dev);
    printk("Buben is down!\n");
}

module_exit(buben_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mikhail Konyukhov <mk@example.com>");
MODULE_DESCRIPTION("buben device");
MODULE_VERSION("0.1");
