obj-m := mychardev.o # Name of the kernel object file
KERNELDIR ?= /lib/modules/$(shell uname -r)/build # Kernel directory
PWD := $(shell pwd) # Current directory
default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean