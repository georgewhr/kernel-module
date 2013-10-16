/*-
 * Copyright 2013 George Wang
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	
 */

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
MODULE_DESCRIPTION("Character driver");

struct devStruc //inode,shared by all processes
{
    struct cdev *iCdev;
    struct semaphore *sem;
    dev_t devno;   //device number
    spinlock_t sp;
};




int init_module(void);
void cleanup_module(void);
static int dev_open (struct inode *inode, struct file *fil);
static ssize_t dev_read (struct file *file, char *buf, size_t count, loff_t *fpp);
static ssize_t dev_write (struct file *file, const char *buf, size_t count, loff_t *fpp);
static int dev_rls (struct inode *inode, struct file *file);
static ssize_t dev_ioctl(struct inode *inode,struct file *file,unsigned int cmd,unsigned long arg);


/*The data structure below is 
 *file operation methods
 *for this device
 */

struct file_operations fops=
{
   .read = dev_read,
   .write = dev_write,
   .open = dev_open,
   .ioctl = dev_ioctl,
   .release = dev_rls,

};

//dev_t devno = 0;
int times = 0, i;
char buffer[100] = {0};
struct devStruc *thisDevice;



static ssize_t dev_ioctl(struct inode *inode,struct file *file,unsigned int cmd,unsigned long arg)
{

     char *temp;
     int i;

    switch(cmd)
    {
        case IOCTL_READ:

             if(dev_read(file, (char *)arg, 100, 0))
                     return -1;
      
        break;


        case IOCTL_WRITE:

           
             if(dev_read(file, (char *)arg, 100, 0))
                     return -1;

        break;
     }

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
        printk(KERN_ALERT "Hi George, the device driver is not found\n");
        return i;
    }
    else
        printk(KERN_ALERT "Good work George, deivice is being registerd\n");
  
    cdev_init(&(thisDevice->cdev), &fops);
    thisDevice->cdev.ops = &fops;
    thisDevice->devno = i;
    thisDevice->sem = (struct semaphore *)kmalloc(sizeof(struct semaphore), GFP_KERNEL);
    //kernel has its own headerfile
  

    if (thisDevice->sem == NULL) 
       printk(KERN_ALERT "Fail Allocate Semaphore\n");

    else 
    {
      sema_init(thisDevice->sem, 10); //semaphore value initialzed
      printk(KERN_ALERT "Allocate and Initialize Semaphore\n");
    }
  
    spin_lock_init(thisDevice->sp);
    printk(KERN_ALERT "Initialize Spinlock \n");
    spin_lock(thisDevice->sp);

    return i;

}


static int dev_open(struct inode *inod, struct file *fil)
{ 
    printk(KERN_INFO "Open Device\n");
    times++;
    printk(KERN_ALERT "It is opened %d times\n", times);
    return 0; 
}



static ssize_t dev_read(struct file *file, char *buff, size_t len, loff_t *off)
{
    //int size = len;
    int count1 = 0;
    int count2=0;
    int c = 0;
    if (down_interruptible(thisDevice->sem)) //case a: aqucire the semaphore
        return -ERESTARTSYS;                 //case b: get to sleep until interrupt
  
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


//buff is the user buffer
static ssize_t dev_write(struct file *file,const char *buff, size_t len, loff_t *off)
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


static int dev_rls(struct inode *inod, struct file *fil)
{
    printk(KERN_ALERT"DIY Device closed\n");
    spin_unlock(&thisDevice->sp);
    return 0;
}

void cleanup_module(void)
{
    unregister_chrdev(i, "DIY");
}






