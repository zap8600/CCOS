# Cotton Candy OS (CCOS)
A barely developed OS.

### Notice
CCOS is being rewritten. The latest Binutils (2.39) has problems with the code.

## Why did I create it?
When I started making this, I was coding it as a 16-bit Real Mode assembly. I wasn't that great at assembly because I mainly use C. Eventually, I wanted to make it in C. At the time, I didn't think that 64-bit processors could run 16-bit code, so I wanted to make it 32-bit. I searched for a while, but couldn't find any information. But when I was about to give up, I found someone on Github called [cfenollosa](https://github.com/cfenollosa) with [this tutorial](https://github.com/cfenollosa/os-tutorial) that was exactly what I needed. At the time, I wasn't able to start building, so I studied it. Eventually, I was able to start.

## Features
* 32-bit Protected Mode
* Command Line
* Keyboard Input
* VGA Graphics
* *kmalloc()* Requesting
* Floppy Drive Driver (barely)

## Features yet to be added
* Floppy Drive Support
* Sound Blaster 16
* ATA/ATAPI Drive R/W
* File System
* Userspace
* Text Editor
* Running Apps
* Playing Media
* Etc.

## Currently working on
* Floppy Drive Support

## Current Architectures
* *i686-elf* (aka *i386-elf*)

## Current Architectures Becoming Supported
* *arm-none-eabi* (for Raspberry Pis 0, 1, 2, 3, & 4)
* *aarch64-elf* (for Raspberry Pis 3 & 4)

## How to compile and run
If you want to compile this, you can look at the [OSDev Wiki's page on making a GCC Cross-Compiler](https://wiki.osdev.org/GCC_Cross-Compiler) for making the cross compiler. Using GCC version 8.3.0 and Binutils version 2.37 worked best for me. Use the same flags the Wiki's page uses. Make sure the target is *i686-elf*. To compile the OS, head to the directory where the files are extracted and run these commands:
```
make kernel.bin
make os-image.bin
make run
```

If you want to clean up the the compile, you can run this command:
```
make clean
```

If you don't use the *make run* command, you can do the following:
```
sudo apt install qemu qemu-system
qemu-system-i386 -fda os-image.bin
```
Only install QEMU if you need to!

I'm using a Ubuntu/Debian based Linux distro. Make sure to install the right apps and run the right commands for whatever system or Linux distro your using. 
