######################################################################

ROMNAME := DarkStar

######################################################################

all:
	rm -rf arm9/arm9.bin
	rm -rf arm7/arm7.bin
	make -C arm7 -I $(CURDIR)
	make -C arm9 -I $(CURDIR)
	ndstool -c $(ROMNAME).nds -7 arm7/arm7.bin -9 arm9/arm9.bin -r7 0x03800000 -e7 0x03800000 -r9 0x02000000 -e9 0x02000000 -b icon.bmp "DarkStar (v0.4);DarkStar NDS Shell by Darkain Dragoon;http://www.darkain.com"
	mv $(ROMNAME).nds ../build/
#	tools/gbfs boot.gbfs *.nds
#	cat -B loader.bin boot.gbfs > $(ROMNAME).ds.gba

######################################################################

clean:
	make clean -C arm7 -I $(CURDIR)
	make clean -C arm9 -I $(CURDIR)
	rm -f ../build/$(ROMNAME).nds 
#	rm -f $(ROMNAME).ds.gba 
#	rm -f $(ROMNAME).nds

######################################################################
