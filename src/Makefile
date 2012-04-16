# ----------------------------------------------------------------------------
#         ATMEL Microcontroller Software Support 
# ----------------------------------------------------------------------------
# Copyright (c) 2008, Atmel Corporation
#
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# - Redistributions of source code must retain the above copyright notice,
# this list of conditions and the disclaimer below.
#
# Atmel's name may not be used to endorse or promote products derived from
# this software without specific prior written permission.
#
# DISCLAIMER: THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR
# IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
# DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
# LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
# OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
# LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
# NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
# EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
# ----------------------------------------------------------------------------

# 	Makefile for compiling the USB CDC serial project

#-------------------------------------------------------------------------------
#		User-modifiable options
#-------------------------------------------------------------------------------

# Chip & board used for compilation
# (can be overriden by adding CHIP=chip and BOARD=board to the command-line)
CHIP  = at91sam3u4
BOARD = 4pi

# Trace level used for compilation
# (can be overriden by adding TRACE_LEVEL=#number to the command-line)
# TRACE_LEVEL_DEBUG      5
# TRACE_LEVEL_INFO       4
# TRACE_LEVEL_WARNING    3
# TRACE_LEVEL_ERROR      2
# TRACE_LEVEL_FATAL      1
# TRACE_LEVEL_NO_TRACE   0
TRACE_LEVEL = 3

# Optimization level, put in comment for debugging
OPTIMIZATION = -Os

# AT91 library directory
AT91LIB = ../at91lib

# External library
EXT_LIBS= ../external_libs

# Output file basename
OUTPUT = smoothie-$(BOARD)-$(CHIP)

# Compile with chip specific features
include $(AT91LIB)/boards/$(BOARD)/$(CHIP)/chip.mak

# Compile for all memories available on the board (this sets $(MEMORIES))
include $(AT91LIB)/boards/$(BOARD)/board.mak

# Output directories
BIN = bin
OBJ = obj

#-------------------------------------------------------------------------------
#		Tools
#-------------------------------------------------------------------------------

# Tool suffix when cross-compiling
CROSS_COMPILE = arm-none-eabi-

# Compilation tools
CC = $(CROSS_COMPILE)gcc
CCPP = $(CROSS_COMPILE)g++
SIZE = $(CROSS_COMPILE)size
OBJCOPY = $(CROSS_COMPILE)objcopy

# Flags
INCLUDES += -I$(AT91LIB)/boards/$(BOARD)
INCLUDES += -I$(AT91LIB)/peripherals
INCLUDES += -I$(AT91LIB)/components
INCLUDES += -I$(AT91LIB)/usb/device
INCLUDES += -I$(AT91LIB)/usb/common
INCLUDES += -I$(AT91LIB)
INCLUDES += -I$(EXT_LIBS)
INCLUDES += -I.

ifeq ($(CHIP_CORE), cortexm3)
TARGET_OPTS = -mcpu=cortex-m3 -mthumb
else
TARGET_OPTS = 
endif

CFLAGS += $(TARGET_OPTS)
CFLAGS += -Wall -mlong-calls -ffunction-sections
CFLAGS += -g $(OPTIMIZATION) $(INCLUDES) -D$(CHIP) -DTRACE_LEVEL=$(TRACE_LEVEL)
ASFLAGS = $(TARGET_OPTS) -Wall -g $(OPTIMIZATION) $(INCLUDES) -D$(CHIP) -D__ASSEMBLY__
LDFLAGS = -g $(OPTIMIZATION) -nostartfiles $(TARGET_OPTS) -Wl,--gc-sections -lc
CPPFLAGS += $(TARGET_OPTS) -mlong-calls -ffunction-sections -g $(OPTIMIZATION) $(INCLUDES) -D$(CHIP) -DTRACE_LEVEL=$(TRACE_LEVEL) -fno-rtti -fno-exceptions
LIBSTDCPP = -lstdc++
#-------------------------------------------------------------------------------
#		Files
#-------------------------------------------------------------------------------

# Directories where source files can be found
USB = $(AT91LIB)/usb
UTILITY = $(AT91LIB)/utility
PERIPH = $(AT91LIB)/peripherals
BOARDS = $(AT91LIB)/boards

VPATH += $(USB)/device/cdc-serial
VPATH += $(USB)/device/core
VPATH += $(USB)/common/core
VPATH += $(USB)/common/cdc
VPATH += $(UTILITY)
VPATH += $(PERIPH)/dbgu
VPATH += $(PERIPH)/irq
VPATH += $(PERIPH)/usart
VPATH += $(PERIPH)/pio
VPATH += $(PERIPH)/tc
VPATH += $(PERIPH)/pmc
VPATH += $(PERIPH)/cp15
VPATH += $(BOARDS)/$(BOARD)
VPATH += $(BOARDS)/$(BOARD)/$(CHIP)
VPATH += $(EXT_LIBS)/cmsis
VPATH += $(PERIPH)/systick
VPATH += ./libs
VPATH += ./libs/platform
VPATH += ./modules/communication
VPATH += ./modules/communication/utils
VPATH += ./modules/robot
VPATH += ./modules/robot/arm_solutions
VPATH += .

CPP_OBJECTS += tinynew.o Kernel.o Config.o Module.o utils.o Pinll.o SlowTicker.o Hook.o StepTicker.o
CPP_OBJECTS += Robot.o Stepper.o Planner.o Pauser.o Player.o SerialConsole.o
CPP_OBJECTS += Gcode.o GcodeDispatch.o Block.o CartesianSolution.o BaseSolution.o
CPP_OBJECTS += main.o

# Objects built from C source files
C_OBJECTS += samserial.o
C_OBJECTS += syscalls.o
C_OBJECTS += tc.o
C_OBJECTS += CDCDSerialDriver.o
C_OBJECTS += CDCDSerialDriverDescriptors.o
C_OBJECTS += CDCSetControlLineStateRequest.o
C_OBJECTS += CDCLineCoding.o
C_OBJECTS += USBD_OTGHS.o
C_OBJECTS += USBD_UDP.o
C_OBJECTS += USBD_UDPHS.o
C_OBJECTS += USBDDriver.o
C_OBJECTS += USBDCallbacks_Initialized.o
C_OBJECTS += USBDCallbacks_Reset.o
#C_OBJECTS += USBDCallbacks_Resumed.o
#C_OBJECTS += USBDCallbacks_Suspended.o
C_OBJECTS += USBDDriverCb_CfgChanged.o
C_OBJECTS += USBDDriverCb_IfSettingChanged.o
C_OBJECTS += USBSetAddressRequest.o
C_OBJECTS += USBGenericDescriptor.o
C_OBJECTS += USBInterfaceRequest.o
C_OBJECTS += USBGenericRequest.o
C_OBJECTS += USBGetDescriptorRequest.o
C_OBJECTS += USBSetConfigurationRequest.o
C_OBJECTS += USBFeatureRequest.o
C_OBJECTS += USBEndpointDescriptor.o
C_OBJECTS += USBConfigurationDescriptor.o
C_OBJECTS += led.o
C_OBJECTS += string.o
C_OBJECTS += stdio.o
C_OBJECTS += dbgu.o
C_OBJECTS += usart.o
C_OBJECTS += pio.o
C_OBJECTS += pio_it.o
C_OBJECTS += pmc.o
C_OBJECTS += trace.o
C_OBJECTS += board_memories.o
C_OBJECTS += board_lowlevel.o

# Objects for different chips
ifeq ($(CHIP_CORE), cortexm3)
C_OBJECTS += nvic.o
C_OBJECTS += exceptions.o
C_OBJECTS += board_cstartup_gnu.o
C_OBJECTS += core_cm3.o
else
C_OBJECTS += aic.o
C_OBJECTS += cp15.o
endif

# Objects built from Assembly source files
ifneq ($(CHIP_CORE), cortexm3)
ASM_OBJECTS += board_cstartup.o
ASM_OBJECTS += cp15_asm.o
endif

# Append OBJ and BIN directories to output filename
OUTPUT := $(BIN)/$(OUTPUT)

#-------------------------------------------------------------------------------
#		Rules
#-------------------------------------------------------------------------------

all: $(BIN) $(OBJ) $(MEMORIES)

$(BIN) $(OBJ):
	mkdir $@

define RULES
C_OBJECTS_$(1) = $(addprefix $(OBJ)/$(1)_, $(C_OBJECTS))
CPP_OBJECTS_$(1) = $(addprefix $(OBJ)/$(1)_, $(CPP_OBJECTS))
ASM_OBJECTS_$(1) = $(addprefix $(OBJ)/$(1)_, $(ASM_OBJECTS))

$(1): $$(ASM_OBJECTS_$(1)) $$(C_OBJECTS_$(1)) $$(CPP_OBJECTS_$(1))
	$(CCPP) $(LDFLAGS) -T"$(AT91LIB)/boards/$(BOARD)/$(CHIP)/$$@.lds" -o $(OUTPUT)-$$@.elf $(LIBSTDCPP) $$^ 
	$(OBJCOPY) -O binary $(OUTPUT)-$$@.elf $(OUTPUT)-$$@.bin
	$(SIZE) $$^ $(OUTPUT)-$$@.elf

$$(C_OBJECTS_$(1)): $(OBJ)/$(1)_%.o: %.c Makefile $(OBJ) $(BIN)
	$(CC) $(CFLAGS) -D$(1) -c -o $$@ $$<

$$(CPP_OBJECTS_$(1)): $(OBJ)/$(1)_%.o: %.cpp Makefile $(OBJ) $(BIN)
	$(CCPP) $(CPPFLAGS) -D$(1) -c -o $$@ $$<

$$(ASM_OBJECTS_$(1)): $(OBJ)/$(1)_%.o: %.S Makefile $(OBJ) $(BIN)
	$(CC) $(ASFLAGS) -D$(1) -c -o $$@ $$<

debug_$(1): $(1)
	perl ../resources/gdb/debug.pl $(OUTPUT)-$(1).elf

endef

$(foreach MEMORY, $(MEMORIES), $(eval $(call RULES,$(MEMORY))))

clean:
	-rm -f $(OBJ)/*.o $(BIN)/*.bin $(BIN)/*.elf

