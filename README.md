# snakOs

<p align="center"><img src="resources/snakOs.png" width="40%"/></p>

The goal of this little project is to manage to create an operating system (or at least a kernel) that only runs a Snake game.

**DISCLAIMER**: This is just a funny way for me to learn more about operating systems programming.

## Credits
Great thanks to ***https://www.youtube.com/@DaedalusCommunity*** channel for the 'Making an OS (x86)' serie of videos that helped me a lot for this project.

Below, a list of useful websites which talk about OS programming:
- https://wiki.osdev.org/

## Prerequisites

I am driving this project from a **linux machine (Ubunut 24 LTS)**. So all the tools I use have only been tested on this OS.

To have the project running, I am using `qEMU` to emulate the system boot of the snakOs.

To compile the assembly code, I use `nasm`.
And to be able to compile C code which is used by the snakOs, I use an **i386-elf** cross compiler.

## Installation

To make the installations easy (in particular for the cross compiler), I use the shell script given by **DaedalusCommunity** through his github : https://github.com/mell-o-tron/MellOs/blob/main/A_Setup/setup-gcc-debian.sh


## Compilation and execution

Once the installation done, you only need to build the binary:

    make

And then, run it with the `qemu` virtual machine:

    qemu-system-x86_64 -drive format=raw,file="snakOS.bin",index=0,if=floppy

