######################################################################

ROMNAME := MultiNDS
#UPLOAD := some path to copy the completed ROM to on completion

######################################################################

all:
	rm -rf arm9/arm9.bin
	rm -rf arm7/arm7.bin
	make -C arm7 -I $(CURDIR)
	make -C arm9 -I $(CURDIR)
	ndstool -c boot.nds -7 arm7/arm7.bin -9 arm9/arm9.bin -r7 0x03800000 -e7 0x03800000 -r9 0x02000000 -e9 0x02000000 -b icon.bmp "Multi-NDS Loader;Programmed by Darkain Dragoon;http://ds.darkain.com/hack/"
	mv boot.nds ../build/
#	tools/gbfs boot.gbfs *.nds
#	cat -B loader.bin boot.gbfs > $(ROMNAME).ds.gba




######################################################################

clean:
	make clean -C arm7 -I $(CURDIR)
	make clean -C arm9 -I $(CURDIR)
	rm -f ../build/boot.nds 
#	rm -f ../build/$(ROMNAME).ds.gba 
#	rm -f ../build/$(ROMNAME).nds

######################################################################
