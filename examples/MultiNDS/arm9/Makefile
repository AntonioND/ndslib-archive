include	CommonMakefile.in

#---------------------------------------------------------------------------------
# TARGET is the name of the output
# BUILDDIR is the directory where object files & intermediate files will be placed
# DSAPPTOOLS is a list of directories containing tools for DarkStar.  tools will
#   appears in the menu in reverse order in which they are listed
# SOURCES is a list of directories containing source code
# INCLUDES is a list of directories containing extra header files
# RESOURCEDIR is a directory from which resources will be grabbed and bin2o'ed
#---------------------------------------------------------------------------------

TARGET			:=	arm9
export RESOURCEDIR	:=	resources
export BUILDDIR		:=	build
#DSAPPTOOLS		+=	dsDebug
SOURCES			+=	DarkStar common fs
#INCLUDES		+=	D:\Programming\C++\ARM\ndslib\include
LIBS			+=	nds9

#---------------------------------------------------------------------------------
# options for code generation
#---------------------------------------------------------------------------------

ARCH	:=	-mthumb-interwork

# note: arm9tdmi isn't the correct CPU arch, but anything newer and LD
# *insists* it has a FPU or VFP, and it won't take no for an answer!
CFLAGS	:=	-g -Wall -O2\
 		-mcpu=arm9tdmi -mtune=arm9tdmi -fomit-frame-pointer\
		-ffast-math \
		$(ARCH) \
		-D BYTE_ORDER=LITTLE_ENDIAN -D _ARM_ASSEM_

CFLAGS	+=	$(INCLUDE) -DARM9

ASFLAGS	:=	-g $(ARCH)
LDFLAGS	:=	-g $(ARCH) -mno-fpu --emit-relocs


#---------------------------------------------------------------------------------
# no real need to edit anything past this point unless you need to add additional
# rules for different file extensions
#---------------------------------------------------------------------------------
ifneq ($(BUILDDIR),$(notdir $(CURDIR)))
#---------------------------------------------------------------------------------

export OUTPUT	:=	$(CURDIR)/$(TARGET)

export VPATH	:=	$(foreach dir,$(SOURCES),$(CURDIR)/$(dir))

export CC	:=	$(PREFIX)gcc
export CXX	:=	$(PREFIX)g++
export AR	:=	$(PREFIX)ar
export OBJCOPY	:=	$(PREFIX)objcopy

#---------------------------------------------------------------------------------
# use CXX for linking C++ projects, CC for standard C
#---------------------------------------------------------------------------------

export LD	:=	$(CXX)
#export LD	:=	$(CC)

#---------------------------------------------------------------------------------
# automatically build a list of object files for our project
#---------------------------------------------------------------------------------

CFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))
CPPFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.cpp)))
SFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.s)))
SSFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.S)))
export BINFILES	:=	$(wildcard $(RESOURCEDIR)/*.*)
export BINOBJECTS:=	$(addsuffix .o, $(notdir $(BINFILES)))

export OFILES	:=	$(BINOBJECTS) $(CPPFILES:.cpp=.o) $(CFILES:.c=.o) $(SFILES:.s=.o) $(SSFILES:.S=.o)

#---------------------------------------------------------------------------------
# build a list of include paths
#---------------------------------------------------------------------------------

export INCLUDE	:=	$(foreach dir,$(INCLUDES),-I$(CURDIR)/$(dir)) \
			$(foreach dir,$(LIBDIRS),-I$(dir)/include) \
			-I$(CURDIR)/$(BUILDDIR)

#---------------------------------------------------------------------------------
# build a list of library paths
#---------------------------------------------------------------------------------

export LIBPATHS	:=	$(foreach dir,$(LIBDIRS),-L$(dir)/lib)

.PHONY: $(BUILDDIR) clean

#---------------------------------------------------------------------------------

$(BUILDDIR):
	@[ -d $@ ] || mkdir -p $@
	@make --no-print-directory -C $(CURDIR)   -f $(CURDIR)/../MakeResources.in
	@make --no-print-directory -C $(BUILDDIR) -f $(CURDIR)/Makefile

#---------------------------------------------------------------------------------

clean:
	@echo clean ...
	@rm -fr $(BUILDDIR) *.elf *.bin

#---------------------------------------------------------------------------------

else

DEPENDS	:=	$(OFILES:.o=.d) Makefile

#---------------------------------------------------------------------------------
# main targets
#---------------------------------------------------------------------------------
$(OUTPUT).bin	:	$(OUTPUT).elf

$(OUTPUT).elf	:	$(OFILES)

#---------------------------------------------------------------------------------

%.bin: %.elf
	@echo built ... $(notdir $@)
	@$(OBJCOPY) -O binary $< $@

#---------------------------------------------------------------------------------

%.elf:
	@$(LD) $(LDFLAGS) -Wl,-Map,$(notdir $@).map -specs=ds_arm9.specs $(OFILES) $(LIBPATHS) -l$(LIBS) -o $@

#---------------------------------------------------------------------------------
# Compile Targets for C/C++
#---------------------------------------------------------------------------------

%.o : %.cpp
	@echo $(notdir $<)
	@$(CXX) -MMD -mthumb $(CFLAGS) -o $@ -c $<

#---------------------------------------------------------------------------------

%.o : %.c
	@echo $(notdir $<)
	@$(CC) -MMD -mthumb $(CFLAGS) -o $@ -c $<

#---------------------------------------------------------------------------------

%.o : %.thumb.cpp
	@echo $(notdir $<)
	@$(CXX) -MMD -mthumb $(CFLAGS) -o $@ -c $<

#---------------------------------------------------------------------------------

%.o : %.thumb.c
	@echo $(notdir $<)
	@$(CC) -MMD -mthumb $(CFLAGS) -o $@ -c $<

#---------------------------------------------------------------------------------

%.o : %.s
	@echo $(notdir $<)
	@$(CC) -MMD $(ASFLAGS) -o $@ -c $<

#---------------------------------------------------------------------------------

%.o : %.S
	@echo $(notdir $<)
	@$(CC) -MMD $(ASFLAGS) -o $@ -c $<

#---------------------------------------------------------------------------------

-include $(DEPENDS)

#---------------------------------------------------------------------------------
endif
#---------------------------------------------------------------------------------
