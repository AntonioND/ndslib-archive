Version 0.1 - No promises.

Unzip (preserving directories) into $(DEVKIT_ROOT)\arm-elf\lib

For instance, if you previously installed DevkitARM into C:/devkitARM, then you would unzip into C:/devkitARM/arm-elf/lib

To use, replace -spec=xxx in your LD line with:
  -spec=ds_arm7.specs      (ARM7 in RAM)
  -spec=ds_arm9.specs      (ARM9 in RAM)
  -spec=ds_arm7cart.specs  (ARM7 running on GBA cartridge)

WARNING: Do *not* make these files in the devkit directory.  I have renamed the makefile to make you think about this before you do something silly.  The clean rule in the provided Makefile deletes all .o files in the 4 directories it builds into.  By default, Wntrmute's crt0's aren't rebuildable, you have to do it by hand.  As long as your devkit is in the path, you can rebuild this source from anywhere else, it doesn't need anything external to build.  Once done, copy the .o files in the root, and in the thumb/interwork subdirectories back to the same place where you initially unpacked it.

Todo:
The RAM-based crt0's haven't been checked for extra busy-work, they may be pointlessly copying initialized data from RAM to RAM.  The ARM9 doesn't do all the cleanup it probably should (disable cache, remap DTCM, etc...), since the bootloader handles this when it hijacks the ARM9.  Need to add support for auto-copying segments to the ARM7/ARM9 fast memory regions (DTCM, WRAM) in the linkscript and crt0.  This isn't necessary if we switch to .elf files on the GBA cart, and make the bootloader a bit more intelligent.