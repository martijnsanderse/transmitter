# Tiva Makefile
# #####################################
#
# Part of the uCtools project
# uctools.github.com
#
#######################################
# user configuration:
#######################################
# TARGET: name of the output file
TARGET = main
# MCU: part number to build for
MCU = TM4C123GH6PM
# SOURCES: list of input source sources
SOURCES = main.c startup_gcc.c gpio.c spi.c ssd1325.c uart.c sys.c graphics.c
SOURCES += FreeRTOS/portable/GCC/ARM_CM4F/port.c
SOURCES += FreeRTOS/croutine.c 
SOURCES += FreeRTOS/event_groups.c 
SOURCES += FreeRTOS/list.c
SOURCES += FreeRTOS/queue.c
SOURCES += FreeRTOS/tasks.c
SOURCES += FreeRTOS/timers.c
SOURCES += FreeRTOS/portable/MemMang/heap_1.c
# INCLUDES: list of includes, by default, use Includes directory
INCLUDES = -I src -I src/FreeRTOS/include
# OUTDIR: directory to use for output
OUTDIR = build
# TIVAWARE_PATH: path to tivaware folder
TIVAWARE_PATH = $(HOME)/Projects/tivaware
# LIBS to link to
LIBS = -ldriver -L$(TIVAWARE_PATH)/driverlib/gcc
# LD_SCRIPT: linker script
LD_SCRIPT = $(MCU).ld


# define flags
CFLAGS = -g -mthumb -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard #-mfloat-abi=softfp
#CFLAGS += -Os 
CFLAGS += -ffunction-sections -fdata-sections -MD -std=c99 -Wall
CFLAGS += -pedantic -DPART_$(MCU) -c -I$(TIVAWARE_PATH)
CFLAGS += $(INCLUDES)
CFLAGS += -I src # for FreeRTOSConfig.h 
CFLAGS += -I src/FreeRTOS/portable/GCC/ARM_CM4F
#CFLAGS += -DTARGET_IS_BLIZZARD_RA1
LDFLAGS = -T $(LD_SCRIPT) --entry ResetISR --gc-sections 

#######################################
# end of user configuration
#######################################
#
#######################################
# binaries
#######################################
CC = arm-none-eabi-gcc
LD = arm-none-eabi-ld
OBJCOPY = arm-none-eabi-objcopy
RM      = rm -f
MKDIR	= mkdir -p
#######################################

LIBC:=${shell ${CC} ${CFLAGS} -print-file-name=libc.a}

# list of object files, placed in the build directory regardless of source path
OBJECTS = $(addprefix $(OUTDIR)/,$(notdir $(SOURCES:.c=.o)))

# default: build bin
all: $(OUTDIR)/$(TARGET).bin

$(OUTDIR)/%.o: src/%.c | $(OUTDIR)
	$(CC) -o $@ $^ $(CFLAGS)

# same rule for c files in sub directories in src.
# could probably done more efficient, but i don;t know how to yet..
$(OUTDIR)/%.o: src/FreeRTOS/%.c | $(OUTDIR)
	$(CC) -o $@ $^ $(CFLAGS)

$(OUTDIR)/%.o: src/FreeRTOS/portable/GCC/ARM_CM4F/%.c | $(OUTDIR)
	$(CC) -o $@ $^ $(CFLAGS)

$(OUTDIR)/%.o: src/FreeRTOS/portable/MemMang/%.c | $(OUTDIR)
	$(CC) -o $@ $^ $(CFLAGS)

$(OUTDIR)/a.out: $(OBJECTS)
	$(LD) -o $@ $^ $(LDFLAGS) $(LIBC) $(LIBS) 

$(OUTDIR)/main.bin: $(OUTDIR)/a.out
	$(OBJCOPY) -O binary $< $@

# create the output directory
$(OUTDIR):
	$(MKDIR) $(OUTDIR)

clean:
	-$(RM) $(OUTDIR)/*

.PHONY: all clean
