######################################################################
# Warning: clean deletes *all* .o files
######################################################################

# Clear the implicit built in rules
.SUFFIXES:

# the prefix on the compiler executables
PREFIX			:=	arm-elf-

######################################################################

SOURCES		:=	.
export CC	:=	$(PREFIX)gcc -x assembler-with-cpp
export CXX	:=	$(PREFIX)g++
export AR	:=	$(PREFIX)ar
export OBJCOPY	:=	$(PREFIX)objcopy

SSFILES		:=	ds_arm7_crt0.S ds_arm9_crt0.S dscart_crt0.S
OFILES		:=	ds_arm7_crt0.o ds_arm9_crt0.o dscart_crt0.o
DEPENDS		:=	$(OFILES:.o=.d) Makefile

######################################################################

%.o : %.S
	@echo $(notdir $<)
	$(CC) -marm -c $< -o $@
	$(CC) -marm -mthumb-interwork -c $< -o interwork/$@
	$(CC) -mthumb -c $< -o thumb/$@
	$(CC) -mthumb -mthumb-interwork -c $< -o thumb/interwork/$@

######################################################################

all:	$(OFILES)


DELDIRS		:=	. interwork thumb thumb/interwork

clean:
	rm -rf $(foreach dir,$(DELDIRS),$(wildcard $(dir)/*.o))


######################################################################
