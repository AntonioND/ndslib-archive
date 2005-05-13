#---------------------------------------------------------------------------------
# Clear the implicit built in rules
#---------------------------------------------------------------------------------
.SUFFIXES:
#---------------------------------------------------------------------------------

#---------------------------------------------------------------------------------
# path to tools - this can be deleted if you set the path in windows
#---------------------------------------------------------------------------------
#export PATH		:=	/c/prog/devkitARM_r8/bin:/bin

#---------------------------------------------------------------------------------
# the prefix on the compiler executables
#---------------------------------------------------------------------------------
PREFIX			:=	arm-elf-

#---------------------------------------------------------------------------------
# source directories
#---------------------------------------------------------------------------------
SOURCES		:= . ../common

#---------------------------------------------------------------------------------
# include directories
#---------------------------------------------------------------------------------
INCLUDES	:= .

#---------------------------------------------------------------------------------
# list of directories containing libraries, this must be the top level containing
# include and lib
#---------------------------------------------------------------------------------
#LIBDIRS	:=	$(LIBGBA)

#---------------------------------------------------------------------------------
# any extra libraries we wish to link with the project
#---------------------------------------------------------------------------------
#LIBS	:=	-lndslib 

#---------------------------------------------------------------------------------
# canned command sequence for binary data
#---------------------------------------------------------------------------------
define bin2o
	cp $(<) $(*).tmp
	$(OBJCOPY) -I binary -O elf32-littlearm -B arm \
	--rename-section .data=.rodata,readonly,data,contents,alloc \
	--redefine-sym _binary_$*_tmp_start=$*\
	--redefine-sym _binary_$*_tmp_end=$*_end\
	--redefine-sym _binary_$*_tmp_size=$*_size\
	$(*).tmp $(@)
#	echo "extern const uint32" $(*)"_end[];" >> $(*).h
#	echo "extern const uint8" $(*)"[];" >> $(*).h
#	echo "extern const uint32" $(*)_size[]";" >> $(*).h
	rm $(*).tmp
endef

#---------------------------------------------------------------------------------
# TARGET is the name of the output
# BUILD is the directory where object files & intermediate files will be placed
# SOURCES is a list of directories containing source code
# INCLUDES is a list of directories containing extra header files
# RESOURCEDIR is a directory from which resources will be grabbed and bin2o'ed
#---------------------------------------------------------------------------------

TARGET		:=	arm9
RESOURCEDIR	:=	resources
BUILD		:=	build
#SOURCES	+=	?
INCLUDES	+=	../../include
#LIBS		+=	?

#---------------------------------------------------------------------------------
# options for code generation
#---------------------------------------------------------------------------------

ARCH	:=	-mthumb-interwork

# note: arm9tdmi isn't the correct CPU arch, but anything newer and LD
# *insists* it has a FPU or VFP, and it won't take no for an answer!
CFLAGS	:=	-g -Wall -O0\
 			-mcpu=arm9 -mtune=arm9 -fomit-frame-pointer\
			-ffast-math \
			$(ARCH)

CFLAGS	+=	$(INCLUDE) -DARM9

ASFLAGS	:=	-x assembler-with-cpp -g $(ARCH)

LDFLAGS	:=	-g $(ARCH) -Wl,-Map,$(notdir $@).map -mno-fpu


#---------------------------------------------------------------------------------
# no real need to edit anything past this point unless you need to add additional
# rules for different file extensions
#---------------------------------------------------------------------------------
ifneq ($(BUILD),$(notdir $(CURDIR)))
#---------------------------------------------------------------------------------

export OUTPUT	:=	$(CURDIR)/$(TARGET)

export VPATH	:=	$(foreach dir,$(SOURCES),$(CURDIR)/$(dir))

export CC	:=	$(PREFIX)gcc
export CXX	:=	$(PREFIX)g++
export AR	:=	$(PREFIX)ar
export OBJCOPY	:=	$(PREFIX)objcopy

#---------------------------------------------------------------------------------
# automatically build a list of object files for our project
#---------------------------------------------------------------------------------

CFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))
CPPFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.cpp)))
SFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.s)))
SSFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.S)))
BINFILES	:=  $(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.bin)))

export OFILES	:=	$(CPPFILES:.cpp=.o) $(CFILES:.c=.o) $(SFILES:.s=.o) $(SSFILES:.S=.o) $(BINFILES:.bin=.o)

#---------------------------------------------------------------------------------
# build a list of include paths
#---------------------------------------------------------------------------------

export INCLUDE	:=	$(foreach dir,$(INCLUDES),-I$(CURDIR)/$(dir)) \
			$(foreach dir,$(LIBDIRS),-I$(dir)/include) \
			-I$(CURDIR)/$(BUILD)

#---------------------------------------------------------------------------------
# build a list of library paths
#---------------------------------------------------------------------------------

export LIBPATHS	:=	$(foreach dir,$(LIBDIRS),-L$(dir)/lib)

.PHONY: $(BUILD) clean

#---------------------------------------------------------------------------------

$(BUILD):
	@[ -d $@ ] || mkdir -p $@
	@make --no-print-directory -C $(BUILD) -f $(CURDIR)/Makefile

#---------------------------------------------------------------------------------

clean:
	@echo clean ...
	@rm -fr $(BUILD) ../libnds9.a

#---------------------------------------------------------------------------------

else

DEPENDS	:=	$(OFILES:.o=.d) Makefile

libnds9.a	:	$(OFILES)

%.a:
	@$(PREFIX)ar rcs ../../libnds9.a $(OFILES)

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

%.o : %.arm.cpp
	@echo $(notdir $<)
	@$(CXX) -MMD -marm $(CFLAGS) -o $@ -c $<

#---------------------------------------------------------------------------------

%.o : %.arm.c
	@echo $(notdir $<)
	@$(CC) -MMD -marm $(CFLAGS) -o $@ -c $<

#---------------------------------------------------------------------------------

%.o : %.s
	@echo $(notdir $<)
	@$(CC)  $(ASFLAGS) -o $@ -c $<

#---------------------------------------------------------------------------------

%.o : %.S
	@echo $(notdir $<)
	@$(CC)  $(ASFLAGS) -o $@ -c $<

#---------------------------------------------------------------------------------

%.o : %.bin
	@echo $(notdir $<)
	@$(bin2o)

#---------------------------------------------------------------------------------

-include $(DEPENDS)

#---------------------------------------------------------------------------------
endif
#---------------------------------------------------------------------------------
