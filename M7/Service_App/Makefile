##########################################################################################################################
# Makefile    J.W.Bruce (C) 2023
##########################################################################################################################

#Get current user
user := $(shell whoami)
########################################
# determine OS
########################################
ifeq ($(OS),Windows_NT)
    MAKECLEANCMD = del
    MAKECLEANFLAGS = /f
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
		MAKECLEANCMD = rm
		MAKECLEANFLAGS = -fR
    endif
    ifeq ($(UNAME_S),Darwin)
		MAKECLEANCMD = rm
		MAKECLEANFLAGS = -fR
    endif
endif


######################################
# target
######################################
all: $(TARGET)

TARGET = m7_lcd_test

######################################
# building variables
######################################
# debug build?
DEBUG = 1
# optimization
OPT = -Og

#######################################
# paths
#######################################
# Build path
BUILD_DIR = build

# CM3 and GCC Paths

# Do not modify these paths
ifdef CPATH
  CM3_DIR = /home/triston/libopencm3
  GCC_PATH = /home/triston/gcc-arm-none-eabi-10.3-2021.10/bin
  ESOS_DIR = /home/triston/esos32
else
  # Your paths here
	ifeq ($(user), kshelton)
	CM3_DIR = /home/kshelton/Documents/GitHub/libopencm3
#   GCC_PATH = /home/kshelton/Documents/RandCode/arm-gnu-toolchain-12.2.rel1-x86_64-arm-none-eabi/bin
	ESOS_DIR = /home/kshelton/Documents/GitHub/esos32
	endif
endif

######################################
# source
######################################
# C sources
C_SOURCES =  \
src/m7_lcd_test.c \
src/keypad.c \
local/esos_stm32l4_ptb_sui.c \
$(ESOS_DIR)/src/esos.c \
$(ESOS_DIR)/src/esos_cb.c \
$(ESOS_DIR)/src/esos_sui.c \
$(ESOS_DIR)/src/esos_utils.c \
$(ESOS_DIR)/src/esos_comm.c \
$(ESOS_DIR)/src/esos_mail.c \
$(ESOS_DIR)/src/stm32l4_ocm3/esos_stm32l4_tick.c \
$(ESOS_DIR)/src/stm32l4_ocm3/esos_stm32l4_utils.c \
$(ESOS_DIR)/src/stm32l4_ocm3/esos_stm32l4_rs232.c \
$(ESOS_DIR)/src/stm32l4_ocm3/esos_stm32l4_edub_4bit_lcd44780wo.c \
$(ESOS_DIR)/src/esos_lcd44780wo.c \

# ASM sources
ASM_SOURCES =  \

#######################################
# binaries
#######################################
PREFIX = arm-none-eabi-
# The gcc compiler bin path can be either defined in make command via GCC_PATH variable (> make GCC_PATH=xxx)
# either it can be added to the PATH environment variable.

ifdef GCC_PATH
CC = $(GCC_PATH)/$(PREFIX)gcc
AS = $(GCC_PATH)/$(PREFIX)gcc -x assembler-with-cpp
CP = $(GCC_PATH)/$(PREFIX)objcopy
SZ = $(GCC_PATH)/$(PREFIX)size
else
CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size
endif
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S
 
#######################################
# CFLAGS
#######################################
# cpu
CPU = -mcpu=cortex-m4

# fpu
FPU = -mfpu=fpv4-sp-d16

# float-abi
FLOAT-ABI = -mfloat-abi=hard

# mcu
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)

# macros for gcc
# AS defines
AS_DEFS = 

# C defines
C_DEFS =  						\
-DSTM32L4						\
-DSTM32L452xx  					\
-DHARDWARE_PLATFORM=NUCLEO64	\
-DESOS_USE_SERIAL_PORT			\
-D__EDUB_BOAR					\
-DESOS_USE_LCD_4BIT


# AS includes
AS_INCLUDES = 

# C includes
C_INCLUDES =  \
-Iinclude \
-Ilocal \
-I$(ESOS_DIR)/include \
-I$(ESOS_DIR)/include/stm32l4_ocm3 \
-I$(CM3_DIR)/include \
-L$(CM3_DIR)/lib



# compile gcc flags
ASFLAGS = $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

CFLAGS = $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections -nostartfiles -specs=nosys.specs

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif


# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"


#######################################
# LDFLAGS
#######################################
# link script
LDSCRIPT = ld.stm32.basic

# libraries
LIBS = -lc -lm -lnosys -lopencm3_stm32l4
LIBDIR = -L$(CM3_DIR)/lib
LDFLAGS = $(MCU) -specs=nano.specs -specs=nosys.specs -T $(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections -nostartfiles

# default action: build all
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin


#######################################
# build the application
#######################################
# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))
# list of ASM program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR) 
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.S: %.c Makefile | $(BUILD_DIR)
	$(AS) -S $(CFLAGS)  $< -o $@
    
$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile $(CM3_DIR)/lib/libopencm3_stm32l4.a
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(HEX) $< $@
	
$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(BIN) $< $@	
	
$(BUILD_DIR):
	mkdir $@		

#######################################
# clean up
#######################################
clean:
	-$(MAKECLEANCMD) $(MAKECLEANFLAGS) $(BUILD_DIR)
	rm -f *.lst *.i *.s *.o *.d *.elf *.bin *.map
  
#######################################
# dependencies
#######################################
-include $(wildcard $(BUILD_DIR)/*.d)

# *** EOF ***

