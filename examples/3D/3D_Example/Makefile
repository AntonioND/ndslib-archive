######################################################################

ROMNAME := template.nds
#UPLOAD := some path to copy the completed ROM to on completion

######################################################################

all:
	rm -rf arm9/arm9.bin
	rm -rf arm7/arm7.bin
	make -C arm7 -I $(CURDIR)
	make -C arm9 -I $(CURDIR)
	cp arm9/arm9.bin boot/resources/arm9.bin
	cp arm7/arm7.bin boot/resources/arm7.bin
	make -C boot -I $(CURDIR)
	mv boot/boot.gba $(ROMNAME)
ifdef UPLOAD
	cp $(ROMNAME) $(UPLOAD)
endif

######################################################################

clean:
	make clean -C arm7 -I $(CURDIR)
	make clean -C arm9 -I $(CURDIR)
	make clean -C boot -I $(CURDIR)
	rm -f $(ROMNAME)

######################################################################
