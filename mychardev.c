#include <linux/module.h> // For module specific functions
#include <linux/kernel.h> // For KERN_INFO and other kernel functionality
#include <linux/fs.h> // For the file_operations structure

#include <linux/cdev.h> // For character device functions
#include <linux/uaccess.h> // For copy_to_user and copy_from_user
#include <linux/init.h> // For __init and __exit macros
#include <linux/slab.h> // For kmalloc/kfree
#define DEVICE_NAME "mychardev" // Name of the device
#define BUFFER_SIZE 1024 // Size of the buffer
static int major_number; // Major number of the device
static struct cdev *mcdev; // Character device structure
static char device_buffer[BUFFER_SIZE]; // Kernel buffer
// Function prototypes
static int device_open(struct inode *inode, struct file *file);
static int device_release(struct inode *inode, struct file *file);
static ssize_t device_read(struct file *file, char __user *user_buffer, size_t length, loff_t *offset);
// [cite: 65]
static ssize_t device_write(struct file *file, const char __user *user_buffer, size_t length, loff_t
*offset); 
// [cite: 65, 66]
// File operations structure [cite: 57, 58, 59, 60]
static struct file_operations fops = {
.open = device_open,
.release = device_release,
.read = device_read,
.write = device_write,
.llseek = no_llseek,
};
// Open function
static int device_open(struct inode *inode, struct file *file) {
printk(KERN_INFO "Device opened\n");
return 0;
}
// Release function
static int device_release(struct inode *inode, struct file *file) {
printk(KERN_INFO "Device closed\n");
return 0;
}
// Read function
static ssize_t device_read(struct file *file, char __user *user_buffer, size_t length, loff_t *offset) {
int bytes_read = 0;
if (*offset >= BUFFER_SIZE)
return 0;
bytes_read = min((int)(length), (int)(BUFFER_SIZE - *offset));
if (bytes_read == 0)
return 0;

if (copy_to_user(user_buffer, device_buffer + *offset, bytes_read))
return -EFAULT;
*offset += bytes_read;
printk(KERN_INFO "Device read %d bytes\n", bytes_read);
return bytes_read;
}
// Write function
static ssize_t device_write(struct file *file, const char __user *user_buffer, size_t length, loff_t
*offset) {
int bytes_written = 0;
bytes_written = min((int)(length), (int)(BUFFER_SIZE - *offset));
if (bytes_written == 0)
return 0;
if (copy_from_user(device_buffer + *offset, user_buffer, bytes_written))
return -EFAULT;
*offset += bytes_written;
printk(KERN_INFO "Device wrote %d bytes\n", bytes_written);
return bytes_written;
}
// Init function (called when the module is loaded)
static int __init chardev_init(void) {
// Allocate major number dynamically
major_number = register_chrdev(0, DEVICE_NAME, &fops);
if (major_number < 0) {
printk(KERN_ALERT "Failed to register a major number\n");
return major_number;
}
// Initialize the cdev structure
mcdev = cdev_alloc();
if (mcdev == NULL) {
printk(KERN_ALERT "cdev_alloc() failed\n");
unregister_chrdev_region(MKDEV(major_number, 0), 1);
return -ENOMEM;
}
cdev_init(mcdev, &fops);
mcdev->owner = THIS_MODULE;
// Add the cdev to the kernel
if (cdev_add(mcdev, MKDEV(major_number, 0), 1) < 0) {
printk(KERN_ALERT "cdev_add() failed\n");
cdev_del(mcdev);
unregister_chrdev_region(MKDEV(major_number, 0), 1);
return -EFAULT;
}

printk(KERN_INFO "Char device registered with major number %d\n", major_number);
return 0;
}
// Exit function (called when the module is unloaded)
static void __exit chardev_exit(void) {
cdev_del(mcdev);
unregister_chrdev_region(MKDEV(major_number, 0), 1);
printk(KERN_INFO "Char device unregistered\n");
}
module_init(chardev_init);
module_exit(chardev_exit);
MODULE_LICENSE("GPL"); // Important to declare license
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Simple character device driver");