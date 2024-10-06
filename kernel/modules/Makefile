# Makefile for the kernel module
obj-m += priority_test.o priority_queue.o
EXTRA_CFLAGS += -I/home/vboxuser/linux-6.5.2/include/linux


all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
