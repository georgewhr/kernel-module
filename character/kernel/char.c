//*Driver to read s stream from user to kernel 
//and output the same stream from kernel to user
//Author: George Wang

#include <linux/version.h>
#include <generated/utsrelease.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/fs.h>
#include <linux/mm.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>
#include <linux/proc_fs.h>              
#include <linux/sched.h>       
#include <linux/semaphore.h>
#include <linux/slab.h>
#include <linux/spinlock.h>
#include <sys/ioctl.h>


#include "ioctldef.h"

MODULE_AUTHOR("George Wang");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Char driver");

struct devStruc 
{
    struct cdev cdev;
    struct semaphore *sem;
    dev_t devno;
    spinlock_t sp;
};

int init_module(void);
void cleanup_module(void);
static int dev_open (struct inode *inode, struct file *file);
static ssize_t dev_read (struct file *file, char *buf, size_t count, loff_t *fpp);
static ssize_t dev_write (struct file *file, const char *buf, size_t count, loff_t *fpp);
static int dev_rls (struct inode *inode, struct file *file);
static int device_ioctl(struct inode *inode,struct file *file,unsigned int cmd,unsigned long arg);

struct file_operations fops=
{
   .read = dev_read,
   .write = dev_write,
   .open = dev_open,
   .ioctl = dev_ioctl,
   .release = dev_rls,

};

dev_t devno = 0;
int times = 0, i;
char buffer[100] = {0};
struct devStruc *thisDevice;



static int device_ioctl(struct inode *inode,struct file *file,unsigned int cmd,unsigned long arg)
{

     char *temp;
     int i;

    switch(cmd)

        case IOCTL_READ:

             if(device_read(file, (char *)arg, 100, 0))
                     return -1;
      
        break;


        case IOCTL_WRITE:

           
             if(device_read(file, (char *)arg, 100, 0))
                     return -1;

        break;


/************************************************
//For ioctl function call, we can put any type of 
//methods we want not only the read and write
//
//
/************************************************/
     return 0;

}






int init_module(void)
{
    i = register_chrdev(0,"DIY",&fops);	
    
    if(i < 0)
    {
        printk(KERN_ALERT "Hi George, the device is not found\n");
        return i;
    }
    else
        printk(KERN_ALERT "Good work George, deivice is being registerd\n");
  

    thisDevice->cdev.ops = &fops;
    thisDevice->devno = devno;
    thisDevice->sem = (struct semaphore *)kmalloc(sizeof(struct semaphore), GFP_KERNEL);
  

    if (thisDevice->sem == NULL) 
       printk(KERN_ALERT "Fail Allocate Semaphore\n");

    else 
    {
      sema_init(thisDevice->sem, 10); //semaphore value initialzed
      printk(KERN_ALERT "Allocate and Initialize Semaphore\n");
    }
  
    spin_lock_init(&thisDevice->sp);
    printk(KERN_ALERT "Initialize Spinlock \n");
    spin_lock(&thisDevice->sp);

    return i;

}


int dev_open(struct inode *inod, struct file *fil)
{ 
    printk(KERN_INFO "Open Device\n");
    times++;
    printk(KERN_ALERT "It is opened %d times\n", times);
    return 0; 
}



int dev_read(struct file *filp, char *buff, size_t len, loff_t *off)
{
    //int size = len;
    int count1 = 0;
    int count2=0;
    int c = 0;
    if (down_interruptible(thisDevice->sem)) 
        return -ERESTARTSYS;
  
    while(len>0)
    {
        put_user(buffer[c], buff++);//put kernel buffer to user buffer
        count1++;
        count2++;
        len--;
        c++;
    }
    
    up(thisDevice->sem);
    return len;

}



int dev_write(struct file *filp,const char *buff, size_t len, loff_t *off)
{
    int count1 = 0;
    int count2 = 0;
    memset(buffer, 0, 100);
    if (down_interruptible(thisDevice->sem)) 
        return -ERESTARTSYS;
    
    while(len > 0)
    {
        buffer[count1++] = buff[count2++];//user buffer to kernel buffer
        len--;
    }
    
    up(thisDevice->sem);

    return len;
}


int dev_rls(struct inode *inod, struct file *fil)
{
    printk(KERN_ALERT"DIY Device closed\n");
    spin_unlock(&thisDevice->sp);
    return 0;
}

void cleanup_module(void)
{
    unregister_chrdev(i, "DIY");
}






