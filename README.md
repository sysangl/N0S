# ValeOS
Custom OS and bootloader. Initially intended for use with a custom PDA.

---

# Why am I making an operating system?
Why not? There was not really any reason, except someone told me I should make my own OS. And so I did.

# Overview
This repository contains (or will contain) an entire operating system complete with a bootloader. Written in Assembly and C, this is a project built from boredom and procrastination (I should've focused on my studies). No standard C libraries will be used, everything will be self written.
The roadmap is as follows :
- Bootloader
  - and whatever this thing does, as long as it boots without being unstable I'm happy.
- Kernel
  - Text interface
  - Numerical printing
  - Error logging
  - Serial IO
  - Memory management
    - Paging, might try to make my owwn paging algorithm
    - Memory map
    - Malloc/Free
  - File IO
  - GUI
  - Wireless
- "Operating System", the stuff 'normal' people will actually see
  - DE + WM, can be toggled or used as a hybrid
    - allow custom css/styling
    - keyboard shortcuts for the keyboard warriors
    - can be fully turned off for a text only session.
  - File system
    - Possibly might just use btrFS and write my own drivers, if not :
    - Basic interface (open, read, write, close, etc)
    - Permission system, more like UNIX (eg. 9-byte perms : rwxr-x--x, etc)
    - Try to make my own block algorithm
    - Add support for common FS, like FAT, ext4 and NTFS
  - Extensive user customisation
  - Video and Audio support
  - Package manager, both CLI and GUI
  - Custom highlevel language
    - Probably just a spin on Python
  - Some basic starter apps
    - terminal & shell
    - text editor (tui & gui)
    - music player
    - image and video viewer
    - basic web browser (really basic)
    - file explorer
    - any other things I may come up with
  - Doom (very important for any Operating System)

I might choose to seperate these into different repositories. Such as :
- Boot loader + Kernel + Libraries, the bare things needed : This Repo
- Filesystem (if I decide to make my own)
- Desktop Environment + Window Manager 
- Apps (although I may just leave them in this repo, if theyre not too big)
- Package manager
- Doom (again, very important, it needs its own repo)

# Building
1. Download this repo and unzip the file
2. Navigate into the repo, you should be in the same directory as the Makefile
3. Open terminal and enter
   ```make```
4. You should have a binary called 'os-image.bin' inside the 'bin' folder. You can run it using QEMU using
   ```qemu-system-i386 -drive format=raw,file=bin/os-image.bin,index=0,if=floppy```
    In the future, I will test flashing a USB with the image and launching it from a computer.