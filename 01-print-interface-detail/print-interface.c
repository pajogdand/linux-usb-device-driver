// TASK: a dummy device driver to detect the pendrive with given PID and VID and print interface details

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/usb.h>

#define USB_VENDOR_ID    0x1234  // Replace with your desired Vendor ID
#define USB_PRODUCT_ID   0x5678  // Replace with your desired Product ID

static struct usb_device_id my_usb_table[] = {
    { USB_DEVICE(USB_VENDOR_ID, USB_PRODUCT_ID) },
    { }  // Terminating entry
};
MODULE_DEVICE_TABLE(usb, my_usb_table);

static int my_usb_probe(struct usb_interface *interface, const struct usb_device_id *id)
{
    struct usb_device *udev = interface_to_usbdev(interface);

    // Print interface details
    printk(KERN_INFO "USB Interface Details:\n");
    printk(KERN_INFO "  VID: %04X\n", udev->descriptor.idVendor);
    printk(KERN_INFO "  PID: %04X\n", udev->descriptor.idProduct);
    printk(KERN_INFO "  Class: %02X\n", interface->cur_altsetting->desc.bInterfaceClass);
    printk(KERN_INFO "  Subclass: %02X\n", interface->cur_altsetting->desc.bInterfaceSubClass);
    printk(KERN_INFO "  Protocol: %02X\n", interface->cur_altsetting->desc.bInterfaceProtocol);

    return 0;
}

static struct usb_driver my_usb_driver = {
    .name = "my_usb_driver",
    .id_table = my_usb_table,
    .probe = my_usb_probe,
};

static int __init my_usb_init(void)
{
    int result = usb_register(&my_usb_driver);
    if (result < 0)
        printk(KERN_ERR "Failed to register USB driver: %d\n", result);
    return result;
}

static void __exit my_usb_exit(void)
{
    usb_deregister(&my_usb_driver);
}

module_init(my_usb_init);
module_exit(my_usb_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Dummy USB Device Driver");
