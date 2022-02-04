obj-m += my_module.o

all:
	        make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	        make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

load: my_module.ko
	        sudo insmod my_module.ko

unload:
	        sudo rmmod my_module.ko
