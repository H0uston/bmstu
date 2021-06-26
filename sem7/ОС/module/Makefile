EXTRA_CFLAGS += -std=gnu99

obj-m += mymodule.o
mymodule-objs := func.o mod_proc.o


all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
