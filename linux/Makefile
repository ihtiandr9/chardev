obj-m += mychrdev.o

all:
	        make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules_prepare
	        make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	        make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

load: mychrdev.ko
	        sudo insmod mychrdev.ko

unload:
	        sudo rmmod mychrdev.ko
