### Build Options ###

BASEROM      := baserom.us.z64
TARGET       := marioparty3
COMPARE      ?= 1
NON_MATCHING ?= 0
CHECK        ?= 1
VERBOSE      ?= 0
QUIET        ?= 0
MOD 		 ?= 0

# Patches
# PATCHES_ASFLAGS := --defsym MP_SAVETYPE_PATCH=1

# Fail early if baserom does not exist
ifeq ($(wildcard $(BASEROM)),)
$(error Baserom `$(BASEROM)' not found.)
endif

# NON_MATCHING=1 implies COMPARE=0
ifeq ($(NON_MATCHING),1)
override COMPARE=0
endif

ifeq ($(VERBOSE),0)
V := @
endif

# Progress-message suppression. tools/build.sh passes QUIET=1
ifeq ($(QUIET),1)
ECHO := @true                  # swallow the progress message text
SPLAT_REDIRECT := > /dev/null  # splat logs progress to stdout, warn/error to stderr
STRIP_NOP_FLAGS := --quiet
else
ECHO := @
endif

ifeq ($(OS),Windows_NT)
  DETECTED_OS=windows
else
  UNAME_S := $(shell uname -s)
  ifeq ($(UNAME_S),Linux)
    DETECTED_OS=linux
  endif
  ifeq ($(UNAME_S),Darwin)
    DETECTED_OS=macos
    MAKE=gmake
    CPPFLAGS += -xc++
  endif
endif


### Output ###

BUILD_DIR := build
ROM       := $(BUILD_DIR)/$(TARGET).z64
ELF       := $(BUILD_DIR)/$(TARGET).elf
LD_SCRIPT := $(TARGET).ld
LD_MAP    := $(BUILD_DIR)/$(TARGET).map


### Tools ###

PYTHON		:= venv/bin/python3  # Ensure we're using the Python from the virtual environment
N64CKSUM	:= $(PYTHON) tools/n64cksum.py
SPLAT_YAML	:= marioparty3.yaml
MOD_YAML	:= marioparty3_mod.yaml
SPLAT	:= $(PYTHON) -m splat split $(SPLAT_YAML)  # Use splat from the virtual environment
MOD_SPLAT	:= $(PYTHON) -m splat split $(MOD_YAML)  # Use splat from the virtual environment
MOD_LINKER_INJECT := $(PYTHON) ./tools/append_mod_to_linker_script.py
MOD_OVL_TABLE_INJECT := $(PYTHON) ./tools/gen_new_overlay_table_file.py
EMULATOR   := mupen64plus
DIFF       := diff

CROSS    := mips-linux-gnu-
AS       := $(CROSS)as
LD       := $(CROSS)ld
OBJCOPY  := $(CROSS)objcopy
STRIP    := $(CROSS)strip

CC       := tools/gcc_2.7.2/$(DETECTED_OS)/gcc
IDO_CC   := tools/ido_recomp/$(DETECTED_OS)/5.3/cc
CC_HOST  := gcc
CPP      := cpp -P

PRINT := printf '
 ENDCOLOR := \033[0m
 WHITE     := \033[0m
 ENDWHITE  := $(ENDCOLOR)
 GREEN     := \033[0;32m
 ENDGREEN  := $(ENDCOLOR)
 BLUE      := \033[0;34m
 ENDBLUE   := $(ENDCOLOR)
 YELLOW    := \033[0;33m
 ENDYELLOW := $(ENDCOLOR)
 PURPLE    := \033[0;35m
 ENDPURPLE := $(ENDCOLOR)
ENDLINE := \n'

### Compiler Options ###

ASFLAGS        := -G 0 -I include -mips3 -mabi=32
CFLAGS         := -G0 -mips3 -mgp32 -mfp32 -D_LANGUAGE_C -DOLD_GCC -Wa,--force-n64align
CPPFLAGS     := -I include -I $(BUILD_DIR)/include -I src -DF3DEX_GBI_2 -D_LANGUAGE_C
LDFLAGS        := -T undefined_syms.txt -T undefined_funcs_auto.txt -T undefined_syms_auto.txt -T $(LD_SCRIPT) -Map $(LD_MAP) --no-check-sections
CHECK_WARNINGS := -Wall -Wextra -Wunused-but-set-variable -Wno-format-security -Wno-unused-parameter -Wno-sign-compare -Wno-unused-variable -Wno-pointer-to-int-cast -Wno-int-to-pointer-cast -Wuseless-cast -m32
CFLAGS_CHECK   := -fcommon -fsyntax-only -fsigned-char -nostdinc -fno-builtin -D CC_CHECK -D _LANGUAGE_C -std=gnu90 $(CHECK_WARNINGS)

ifneq ($(CHECK),1)
CFLAGS_CHECK += -w
endif

ifeq ($(MOD),1)
CFLAGS += -DMOD
CPPFLAGS += -DMOD
endif

OPTFLAGS := -O1

### Sources ###

# Object files
OBJECTS := $(shell grep -E 'build.+\.o' marioparty3.ld -o)
DEPENDS := $(OBJECTS:=.d) 

### Targets ###

build/src/libhmath/%.c.o build/src/libhmath/%.c.s: OPTFLAGS = -O2
build/src/libhmath/%.o build/src/libhmath/%.c.s build/src/libm/%.o: CFLAGS := -G0 -mips3 -mgp32 -mfp32 -ffast-math -Wa,--force-n64align

#build/src/libultra/os/%.o: CFLAGS := -O2 $(CFLAGSCOMMON)
#build/src/libultra/libc/%.o: CFLAGS := -O2 $(CFLAGSCOMMON)
# build/src/2.0L/%.o: CFLAGS := -O2 $(CFLAGSCOMMON)

all: $(ROM)

-include $(DEPENDS)

clean:
	$(V)rm -rf build

distclean: clean
	$(V)rm -rf asm
	$(V)rm -rf assets
	$(V)rm -f *auto.txt
	$(V)rm -f marioparty3.ld
	$(V)rm -f include/ld_addrs.h

setup: distclean split

modsetup: distclean modsplit

modsplit:
	$(V)rm -rf asm
	$(V)$(MOD_OVL_TABLE_INJECT)
	$(V)$(MOD_SPLAT)$(SPLAT_REDIRECT)
	$(V)$(MOD_LINKER_INJECT)

split:
	$(V)rm -rf asm
	$(V)$(SPLAT)$(SPLAT_REDIRECT)

test: $(ROM)
	$(V)$(EMULATOR) $<

# Flags for individual files. TODO: move these to a common directory and make this a directory thing instead
build/src/lib/hvq.c.o: OPTFLAGS = -O2
build/src/lib/hvq.c.o: CFLAGS += -Wa,--force-n64align
build/src/2.0L/audio/%.c.o: OPTFLAGS = -O2
build/src/2.0L/audio/%.c.o: CFLAGS = -G0 -mips3 -mgp32 -mfp32 -D_MIPS_SZLONG=32 -D_LANGUAGE_C -DF3DEX_GBI -D__MIPSEB__ -Wa,--force-n64align
build/src/2.0L/audio/%.c.o: CPPFLAGS = -I include -I include/PR -I include/gcc -I $(BUILD_DIR)/include -I src -DNDEBUG -D_MIPS_SZLONG=32 -DF3DEX_GBI_2
build/src/2.0L/n_audio/%.c.o: OPTFLAGS = -O2
build/src/2.0L/n_audio/%.c.o: CFLAGS = -G0 -mips3 -mgp32 -mfp32 -D_MIPS_SZLONG=32 -D_LANGUAGE_C -DF3DEX_GBI -D__MIPSEB__ -Wa,--force-n64align
build/src/2.0L/n_audio/%.c.o: CPPFLAGS = -I include -I include/PR -I include/gcc -I $(BUILD_DIR)/include -I src -DNDEBUG -D_MIPS_SZLONG=32 -DF3DEX_GBI_2
build/src/8A6B0.c.o: OPTFLAGS = -O2 #Could also be -O3?
build/src/2.0L/debug/threadprofile.c.o: OPTFLAGS = -O2
build/src/2.0L/gu/%.c.o: OPTFLAGS = -O2
build/src/2.0L/gu/%.c.o: NO_STRIP_NOP = 1
build/src/2.0L/gu/lookat.c.o: OPTFLAGS = -O3
build/src/2.0L/gu/perspective.c.o: OPTFLAGS = -O3
build/src/2.0L/gu/rotate.c.o: OPTFLAGS = -O3
build/src/2.0L/gu/rotaterpy.c.o: OPTFLAGS = -O3
build/src/2.0L/io/ai.c.o: OPTFLAGS = -O2
build/src/2.0L/io/aigetlen.c.o: OPTFLAGS = -O2
build/src/2.0L/io/aisetfreq.c.o: OPTFLAGS = -O2
build/src/2.0L/io/aisetnextbuf.c.o: OPTFLAGS = -O2
build/src/2.0L/io/cartrominit.c.o: OPTFLAGS = -O2
build/src/2.0L/io/conteeplongread.c.o: OPTFLAGS = -O2
build/src/2.0L/io/conteeplongwrite.c.o: OPTFLAGS = -O2
build/src/2.0L/io/conteepprobe.c.o: OPTFLAGS = -O2
build/src/2.0L/io/conteepread.c.o: OPTFLAGS = -O2
build/src/2.0L/io/conteepwrite.c.o: OPTFLAGS = -O2
build/src/2.0L/io/contpfs.c.o: OPTFLAGS = -O3
build/src/2.0L/io/contramread.c.o: OPTFLAGS = -O2
build/src/2.0L/io/contramwrite.c.o: OPTFLAGS = -O2
build/src/2.0L/io/contreaddata.c.o: OPTFLAGS = -O2
build/src/2.0L/io/controller.c.o: OPTFLAGS = -O2
build/src/2.0L/io/contsetch.c.o: OPTFLAGS = -O2
build/src/2.0L/io/devmgr.c.o: OPTFLAGS = -O2
build/src/2.0L/io/epidma.c.o: OPTFLAGS = -O2
build/src/2.0L/io/epirawdma.c.o: OPTFLAGS = -O2
build/src/2.0L/io/epirawread.c.o: OPTFLAGS = -O2
build/src/2.0L/io/epirawwrite.c.o: OPTFLAGS = -O2
build/src/2.0L/io/epiread.c.o: OPTFLAGS = -O2
build/src/2.0L/io/epiwrite.c.o: OPTFLAGS = -O2
build/src/2.0L/io/motor.c.o: OPTFLAGS = -O2
build/src/2.0L/io/pfsgetstatus.c.o: OPTFLAGS = -O2
build/src/2.0L/io/pfsisplug.c.o: OPTFLAGS = -O2
build/src/2.0L/io/pfsselectbank.c.o: OPTFLAGS = -O2
build/src/2.0L/io/piacs.c.o: OPTFLAGS = -O2 -fno-expensive-optimizations
build/src/2.0L/io/pigetcmdq.c.o: OPTFLAGS = -O2
build/src/2.0L/io/pimgr.c.o: OPTFLAGS = -O2
build/src/2.0L/io/pirawdma.c.o: OPTFLAGS = -O2
build/src/2.0L/io/pirawread.c.o: OPTFLAGS = -O2
build/src/2.0L/io/pirawwrite.c.o: OPTFLAGS = -O2
build/src/2.0L/io/piread.c.o: OPTFLAGS = -O2
build/src/2.0L/io/piwrite.c.o: OPTFLAGS = -O2
build/src/2.0L/io/si.c.o: OPTFLAGS = -O2
build/src/2.0L/io/siacs.c.o: OPTFLAGS = -O2 -fno-expensive-optimizations
build/src/2.0L/io/sirawdma.c.o: OPTFLAGS = -O2
build/src/2.0L/io/sirawread.c.o: OPTFLAGS = -O2
build/src/2.0L/io/sirawwrite.c.o: OPTFLAGS = -O2
build/src/2.0L/io/sp.c.o: OPTFLAGS = -O2
build/src/2.0L/io/spgetstat.c.o: OPTFLAGS = -O2
build/src/2.0L/io/sprawdma.c.o: OPTFLAGS = -O2
build/src/2.0L/io/sprawread.c.o: OPTFLAGS = -O2
build/src/2.0L/io/sprawwrite.c.o: OPTFLAGS = -O2
build/src/2.0L/io/spsetstat.c.o: OPTFLAGS = -O2
build/src/2.0L/io/sptask.c.o: OPTFLAGS = -O2
build/src/2.0L/io/sptaskyield.c.o: OPTFLAGS = -O2
build/src/2.0L/io/sptaskyielded.c.o: OPTFLAGS = -O2
build/src/2.0L/io/vi.c.o: OPTFLAGS = -O2
build/src/2.0L/io/viblack.c.o: OPTFLAGS = -O2
build/src/2.0L/io/vigetcurrcontext.c.o: OPTFLAGS = -O2
build/src/2.0L/io/vimgr.c.o: OPTFLAGS = -O2
build/src/2.0L/io/visetevent.c.o: OPTFLAGS = -O2
build/src/2.0L/io/visetmode.c.o: OPTFLAGS = -O2
build/src/2.0L/io/visetspecial.c.o: OPTFLAGS = -O2
build/src/2.0L/io/visetyscale.c.o: OPTFLAGS = -O2
build/src/2.0L/io/viswapbuf.c.o: OPTFLAGS = -O2
build/src/2.0L/io/viswapcontext.c.o: OPTFLAGS = -O2
build/src/2.0L/libc/ldiv.c.o: OPTFLAGS = -O2
build/src/2.0L/libc/sprintf.c.o: OPTFLAGS = -O2
build/src/2.0L/libc/syncprintf.c.o: OPTFLAGS = -O2
build/src/2.0L/libc/string.c.o: OPTFLAGS = -O2
build/src/2.0L/libc/xldtob.c.o: OPTFLAGS = -O2
build/src/2.0L/libc/xlitob.c.o: OPTFLAGS = -O2
build/src/2.0L/libc/xprintf.c.o: OPTFLAGS = -O2
build/src/2.0L/os/afterprenmi.c.o: OPTFLAGS = -O2
build/src/2.0L/os/createthread.c.o: OPTFLAGS = -O2
build/src/2.0L/os/destroythread.c.o: OPTFLAGS = -O2
build/src/2.0L/os/getmemsize.c.o: OPTFLAGS = -O2
build/src/2.0L/os/getthreadpri.c.o: OPTFLAGS = -O2
build/src/2.0L/os/gettime.c.o: OPTFLAGS = -O2
build/src/2.0L/os/initialize.c.o: OPTFLAGS = -O2
build/src/2.0L/os/initialize_emu.c.o: OPTFLAGS = -O2
build/src/2.0L/os/initialize_isv.c.o: OPTFLAGS = -O2
build/src/2.0L/os/initialize_kmc.c.o: OPTFLAGS = -O2
build/src/2.0L/os/initialize_msp.c.o: OPTFLAGS = -O2
build/src/2.0L/os/initrdb.c.o: OPTFLAGS = -O2
build/src/2.0L/os/jammesg.c.o: OPTFLAGS = -O2
build/src/2.0L/os/rdbsend.c.o: OPTFLAGS = -O2
build/src/2.0L/os/recvmesg.c.o: OPTFLAGS = -O2
build/src/2.0L/os/resetglobalintmask.c.o: OPTFLAGS = -O2
build/src/2.0L/os/sendmesg.c.o: OPTFLAGS = -O2
build/src/2.0L/os/seteventmesg.c.o: OPTFLAGS = -O2
build/src/2.0L/os/setglobalintmask.c.o: OPTFLAGS = -O2
build/src/2.0L/os/setthreadpri.c.o: OPTFLAGS = -O2
build/src/2.0L/os/settimer.c.o: OPTFLAGS = -O2
build/src/2.0L/os/startthread.c.o: OPTFLAGS = -O2
build/src/2.0L/os/timerintr.c.o: OPTFLAGS = -O2
build/src/2.0L/os/virtualtophysical.c.o: OPTFLAGS = -O2
build/src/2.0L/os/yieldthread.c.o: OPTFLAGS = -O2
build/src/2.0L/rmon/rmonbrk.c.o: OPTFLAGS = -O2
build/src/2.0L/rmon/rmonmem.c.o: OPTFLAGS = -O2
build/src/88CF0.c.o: OPTFLAGS = -O2
build/src/88CF0.c.o: CFLAGS = -G0 -mips3 -mgp32 -mfp32 -D_LANGUAGE_C -Wa,--force-n64align

# Files that have scommon
build/src/2.0L/gu/lookathil.c.o: CFLAGS = -G0 -mips3 -mgp32 -mfp32 -D_LANGUAGE_C -Wa,--force-n64align
build/src/gamemes.c.o: CFLAGS = -G0 -mips3 -mgp32 -mfp32 -D_LANGUAGE_C -Wa,--force-n64align
build/src/hmflight.c.o: CFLAGS = -G0 -mips3 -mgp32 -mfp32 -D_LANGUAGE_C -Wa,--force-n64align
build/src/pause.c.o: CFLAGS = -G0 -mips3 -mgp32 -mfp32 -D_LANGUAGE_C -Wa,--force-n64align
build/src/overlays/ovl_31_vine_with_me/%.c.o: CFLAGS = -G0 -mips3 -mgp32 -mfp32 -D_LANGUAGE_C -Wa,--force-n64align
build/src/overlays/ovl_33_end_of_the_line/%.c.o: OPTFLAGS = -O1 -funroll-loops
build/src/overlays/ovl_36_motor_rooter/system.c.o: CFLAGS = -G0 -mips3 -mgp32 -mfp32 -D_LANGUAGE_C -Wa,--force-n64align
build/src/overlays/ovl_37_silly_screws/%.c.o: CFLAGS = -G0 -mips3 -mgp32 -mfp32 -D_LANGUAGE_C -Wa,--force-n64align
build/src/overlays/ovl_39_tick_tock_hop/%.c.o: CFLAGS = -G0 -mips3 -mgp32 -mfp32 -D_LANGUAGE_C -Wa,--force-n64align
build/src/overlays/ovl_80_shared_board/ECA50.c.o: CFLAGS = -G0 -mips3 -mgp32 -mfp32 -D_LANGUAGE_C -Wa,--force-n64align

# libm uses IDO 5.3.
IDO_OBJECTS := $(sort $(filter $(BUILD_DIR)/src/libm/%.c.o,$(OBJECTS)))

# Compile selected .c files with IDO 5.3.
$(IDO_OBJECTS): $(BUILD_DIR)/%.c.o: %.c
	$(ECHO)$(PRINT)$(GREEN)Compiling C file: $(ENDGREEN)$(BLUE)$<$(ENDBLUE)$(ENDLINE)
	@mkdir -p $(dir $@)
	@$(CC_HOST) $(CFLAGS_CHECK) $(CPPFLAGS) -MMD -MP -MT $@ -MF $@.d $<
	$(V)$(IDO_CC) -O2 -G0 -mips1 -non_shared -Wab,-r4300_mul $(CPPFLAGS) -c -o $@ $<

# All other .c files are compiled with kmc gcc in two steps: .c -> .s, then .s -> .o.
#
# After function calls, gcc emits these instructions in the .s file including the blank new line
#    .set    macro
#    .set    reorder
#
# By stripping the blank newline between the steps, functions with nop issues will match.
# Objects that set NO_STRIP_NOP (e.g. libultra, not built with this pipeline originally) skip the strip.
GCC_OBJECTS := $(sort $(filter-out $(IDO_OBJECTS),$(filter $(BUILD_DIR)/src/%.c.o,$(OBJECTS))))
GCC_ASM     := $(GCC_OBJECTS:.o=.s)

.PRECIOUS: $(GCC_ASM)
-include $(GCC_ASM:=.d)

# .c -> .s  (plus the nop strip)
$(GCC_ASM): $(BUILD_DIR)/%.c.s: %.c tools/strip_nop.py
	$(ECHO)$(PRINT)$(GREEN)Compiling C file: $(ENDGREEN)$(BLUE)$<$(ENDBLUE)$(ENDLINE)
	@mkdir -p $(dir $@)
	@$(CC_HOST) $(CFLAGS_CHECK) $(CPPFLAGS) -MMD -MP -MT $@ -MF $@.d $<
	$(V)export COMPILER_PATH=tools/gcc_2.7.2/$(DETECTED_OS) && $(CC) $(OPTFLAGS) $(CFLAGS) $(CPPFLAGS) -S $< -o $@
	$(if $(NO_STRIP_NOP),,$(V)$(PYTHON) tools/strip_nop.py $@ $(STRIP_NOP_FLAGS))

# .s -> .o (use strip to fix objects so that they can be linked with modern gnu ld)
$(GCC_OBJECTS): $(BUILD_DIR)/%.c.o: $(BUILD_DIR)/%.c.s
	@mkdir -p $(dir $@)
	$(V)export COMPILER_PATH=tools/gcc_2.7.2/$(DETECTED_OS) && $(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
	@$(STRIP) $@ -N dummy-symbol-name

# Assemble .s files with modern gnu as
$(BUILD_DIR)/asm/%.s.o: asm/%.s
	$(ECHO)$(PRINT)$(GREEN)Assembling asm file: $(ENDGREEN)$(BLUE)$<$(ENDBLUE)$(ENDLINE)
	@mkdir -p $(shell dirname $@)
	$(V)$(AS) $(ASFLAGS) -o $@ $<

# Create .o files from .bin files.
$(BUILD_DIR)/%.bin.o: %.bin
	$(ECHO)$(PRINT)$(GREEN)objcopying binary file: $(ENDGREEN)$(BLUE)$<$(ENDBLUE)$(ENDLINE)
	@mkdir -p $(shell dirname $@)
	$(V)$(LD) -r -b binary -o $@ $<

# Link the .o files into the .elf
$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS)
	$(ECHO)$(PRINT)$(GREEN)Linking elf file: $(ENDGREEN)$(BLUE)$@$(ENDBLUE)$(ENDLINE)
	$(V)$(LD) $(LDFLAGS) -o $@

# Convert the .elf to the final rom
$(ROM): $(BUILD_DIR)/$(TARGET).elf
	$(ECHO)$(PRINT)$(GREEN)Creating z64: $(ENDGREEN)$(BLUE)$@$(ENDBLUE)$(ENDLINE)
	$(V)$(OBJCOPY) $< $@ -O binary
	$(V)$(N64CKSUM) $@
ifeq ($(COMPARE),1)
	@$(DIFF) $(BASEROM) $(ROM) && printf "OK\n" || (echo 'The build succeeded, but did not match the base ROM. This is expected if you are making changes to the game. To skip this check, use "make COMPARE=0".' && false)
endif

### Make Settings ###

.PHONY: all clean distclean test setup split

# Remove built-in implicit rules to improve performance
MAKEFLAGS += --no-builtin-rules

# Print target for debugging
print-% : ; $(info $* is a $(flavor $*) variable set to [$($*)]) @true
