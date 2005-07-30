######################################################################

ROMNAME := loader
#UPLOAD := some path to copy the completed ROM to on completion

######################################################################

all:

	make -C boot -I $(CURDIR)
	mv boot/boot.gba $(ROMNAME).bin
	padbin 16384 $(ROMNAME).bin
	mv $(ROMNAME).bin ../build/


######################################################################

clean:
	make clean -C boot -I $(CURDIR)
	rm -f ../build/$(ROMNAME).bin

######################################################################
