obj-m += char.o

#KDIR = /usr/src/kernels/3.6.7-4.fc17.i686

all:
	make -C /lib/modules/`uname -r`/build M=$(PWD) modules
clean:
	make -C /lib/modules/`uname -r`/build M=$(PWD) clean
