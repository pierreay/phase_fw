PROJECT_NAME := radio_test_pca10028

export OUTPUT_FILENAME
#MAKEFILE_NAME := $(CURDIR)/$(word $(words $(MAKEFILE_LIST)),$(MAKEFILE_LIST))
MAKEFILE_NAME := $(MAKEFILE_LIST)
MAKEFILE_DIR := $(dir $(MAKEFILE_NAME) ) 

NORDIC_SEMI_SDK = $(NORDIC_SEMI_SDK_V11)
TEMPLATE_PATH = $(NORDIC_SEMI_SDK)/components/toolchain/gcc
ifeq ($(OS),Windows_NT)
include $(TEMPLATE_PATH)/Makefile.windows
else
include $(TEMPLATE_PATH)/Makefile.posix
endif

MK := mkdir
RM := rm -rf

#echo suspend
ifeq ("$(VERBOSE)","1")
NO_ECHO := 
else
NO_ECHO := @
endif

# Toolchain commands
CC              := '$(GNU_INSTALL_ROOT)/bin/$(GNU_PREFIX)-gcc'
AS              := '$(GNU_INSTALL_ROOT)/bin/$(GNU_PREFIX)-as'
AR              := '$(GNU_INSTALL_ROOT)/bin/$(GNU_PREFIX)-ar' -r
LD              := '$(GNU_INSTALL_ROOT)/bin/$(GNU_PREFIX)-ld'
NM              := '$(GNU_INSTALL_ROOT)/bin/$(GNU_PREFIX)-nm'
OBJDUMP         := '$(GNU_INSTALL_ROOT)/bin/$(GNU_PREFIX)-objdump'
OBJCOPY         := '$(GNU_INSTALL_ROOT)/bin/$(GNU_PREFIX)-objcopy'
SIZE            := '$(GNU_INSTALL_ROOT)/bin/$(GNU_PREFIX)-size'

#function for removing duplicates in a list
remduplicates = $(strip $(if $1,$(firstword $1) $(call remduplicates,$(filter-out $(firstword $1),$1))))

#source common to all targets
C_SOURCE_FILES += \
$(abspath $(NORDIC_SEMI_SDK)/components/toolchain/system_nrf51.c) \
$(abspath ../../main.c) \
$(abspath ../../tinyaes/aes.c) \
$(abspath ../../radio_test.c) \
$(abspath $(NORDIC_SEMI_SDK)/components/libraries/util/app_error.c) \
$(abspath $(NORDIC_SEMI_SDK)/components/libraries/util/app_error_weak.c) \
$(abspath $(NORDIC_SEMI_SDK)/components/libraries/fifo/app_fifo.c) \
$(abspath $(NORDIC_SEMI_SDK)/components/libraries/util/app_util_platform.c) \
$(abspath $(NORDIC_SEMI_SDK)/components/libraries/util/nrf_assert.c) \
$(abspath $(NORDIC_SEMI_SDK)/components/libraries/uart/retarget.c) \
$(abspath $(NORDIC_SEMI_SDK)/components/libraries/uart/app_uart_fifo.c) \
$(abspath $(NORDIC_SEMI_SDK)/components/drivers_nrf/delay/nrf_delay.c) \
$(abspath $(NORDIC_SEMI_SDK)/components/drivers_nrf/common/nrf_drv_common.c) \
$(abspath $(NORDIC_SEMI_SDK)/components/drivers_nrf/uart/nrf_drv_uart.c) \

#assembly files common to all targets
ASM_SOURCE_FILES  = $(abspath $(NORDIC_SEMI_SDK)/components/toolchain/gcc/gcc_startup_nrf51.s)

#includes common to all targets
INC_PATHS  = -I$(abspath ../../config/radio_test_pca10028)
INC_PATHS += -I$(abspath ../../config)
INC_PATHS += -I$(abspath ../../bsp)
INC_PATHS += -I$(abspath ../../tinyaes)
INC_PATHS += -I$(abspath $(NORDIC_SEMI_SDK)/components/drivers_nrf/nrf_soc_nosd)
INC_PATHS += -I$(abspath $(NORDIC_SEMI_SDK)/components/device)
INC_PATHS += -I$(abspath $(NORDIC_SEMI_SDK)/components/libraries/uart)
INC_PATHS += -I$(abspath $(NORDIC_SEMI_SDK)/components/drivers_nrf/hal)
INC_PATHS += -I$(abspath $(NORDIC_SEMI_SDK)/components/drivers_nrf/delay)
INC_PATHS += -I$(abspath $(NORDIC_SEMI_SDK)/components/toolchain/CMSIS/Include)
INC_PATHS += -I$(abspath ../..)
INC_PATHS += -I$(abspath $(NORDIC_SEMI_SDK)/components/libraries/util)
INC_PATHS += -I$(abspath $(NORDIC_SEMI_SDK)/components/drivers_nrf/uart)
INC_PATHS += -I$(abspath $(NORDIC_SEMI_SDK)/components/drivers_nrf/common)
INC_PATHS += -I$(abspath $(NORDIC_SEMI_SDK)/components/toolchain)
INC_PATHS += -I$(abspath $(NORDIC_SEMI_SDK)/components/drivers_nrf/config)
INC_PATHS += -I$(abspath $(NORDIC_SEMI_SDK)/components/libraries/fifo)
INC_PATHS += -I$(abspath $(NORDIC_SEMI_SDK)/components/toolchain/gcc)

OBJECT_DIRECTORY = _build
LISTING_DIRECTORY = $(OBJECT_DIRECTORY)
OUTPUT_BINARY_DIRECTORY = $(OBJECT_DIRECTORY)

# Sorting removes duplicates
BUILD_DIRECTORIES := $(sort $(OBJECT_DIRECTORY) $(OUTPUT_BINARY_DIRECTORY) $(LISTING_DIRECTORY) )

#flags common to all targets
CFLAGS  = -DNRF51
CFLAGS += -DBOARD_PCA10028
CFLAGS += -DBSP_DEFINES_ONLY
CFLAGS += -mcpu=cortex-m0
CFLAGS += -mthumb -mabi=aapcs --std=gnu99
# NOTE: Do not forget that optimization levels O0 or O3 will change leakage
# duration --- and maybe characteristics?
CFLAGS += -Wall -O3 -g3
CFLAGS += -mfloat-abi=soft
# keep every function in separate section. This will allow linker to dump unused functions
CFLAGS += -ffunction-sections -fdata-sections -fno-strict-aliasing
CFLAGS += -fno-builtin --short-enums 
# keep every function in separate section. This will allow linker to dump unused functions
LDFLAGS += -Xlinker -Map=$(LISTING_DIRECTORY)/$(OUTPUT_FILENAME).map
LDFLAGS += -mthumb -mabi=aapcs -L $(TEMPLATE_PATH) -T$(LINKER_SCRIPT)
LDFLAGS += -mcpu=cortex-m0
# let linker to dump unused sections
LDFLAGS += -Wl,--gc-sections
# use newlib in nano version
LDFLAGS += --specs=nano.specs -lc -lnosys

# Assembler flags
ASMFLAGS += -x assembler-with-cpp
ASMFLAGS += -DNRF51
ASMFLAGS += -DBOARD_PCA10028
ASMFLAGS += -DBSP_DEFINES_ONLY

#default target - first one defined
default: clean nrf51422_xxac

#building all targets
all: clean
	$(NO_ECHO)$(MAKE) -f $(MAKEFILE_NAME) -C $(MAKEFILE_DIR) -e cleanobj
	$(NO_ECHO)$(MAKE) -f $(MAKEFILE_NAME) -C $(MAKEFILE_DIR) -e nrf51422_xxac

#target for printing all targets
help:
	@echo following targets are available:
	@echo 	nrf51422_xxac

C_SOURCE_FILE_NAMES = $(notdir $(C_SOURCE_FILES))
C_PATHS = $(call remduplicates, $(dir $(C_SOURCE_FILES) ) )
C_OBJECTS = $(addprefix $(OBJECT_DIRECTORY)/, $(C_SOURCE_FILE_NAMES:.c=.o) )

ASM_SOURCE_FILE_NAMES = $(notdir $(ASM_SOURCE_FILES))
ASM_PATHS = $(call remduplicates, $(dir $(ASM_SOURCE_FILES) ))
ASM_OBJECTS = $(addprefix $(OBJECT_DIRECTORY)/, $(ASM_SOURCE_FILE_NAMES:.s=.o) )

vpath %.c $(C_PATHS)
vpath %.s $(ASM_PATHS)

OBJECTS = $(C_OBJECTS) $(ASM_OBJECTS)

nrf51422_xxac: OUTPUT_FILENAME := nrf51422_xxac
nrf51422_xxac: LINKER_SCRIPT=radio_test_gcc_nrf51.ld

nrf51422_xxac: $(BUILD_DIRECTORIES) $(OBJECTS)
	@echo Linking target: $(OUTPUT_FILENAME).out
	$(NO_ECHO)$(CC) $(LDFLAGS) $(OBJECTS) $(LIBS) -lm -o $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).out
	$(NO_ECHO)$(MAKE) -f $(MAKEFILE_NAME) -C $(MAKEFILE_DIR) -e finalize

## Create build directories
$(BUILD_DIRECTORIES):
	echo $(MAKEFILE_NAME)
	$(MK) $@

# Create objects from C SRC files
$(OBJECT_DIRECTORY)/%.o: %.c
	@echo Compiling file: $(notdir $<)
	$(NO_ECHO)$(CC) $(CFLAGS) $(INC_PATHS) -c -o $@ $<

# Assemble files
$(OBJECT_DIRECTORY)/%.o: %.s
	@echo Assembly file: $(notdir $<)
	$(NO_ECHO)$(CC) $(ASMFLAGS) $(INC_PATHS) -c -o $@ $<
# Link
$(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).out: $(BUILD_DIRECTORIES) $(OBJECTS)
	@echo Linking target: $(OUTPUT_FILENAME).out
	$(NO_ECHO)$(CC) $(LDFLAGS) $(OBJECTS) $(LIBS) -lm -o $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).out
## Create binary .bin file from the .out file
$(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).bin: $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).out
	@echo Preparing: $(OUTPUT_FILENAME).bin
	$(NO_ECHO)$(OBJCOPY) -O binary $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).out $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).bin

## Create binary .hex file from the .out file
$(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).hex: $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).out
	@echo Preparing: $(OUTPUT_FILENAME).hex
	$(NO_ECHO)$(OBJCOPY) -O ihex $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).out $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).hex

finalize: genbin genhex echosize

genbin:
	@echo Preparing: $(OUTPUT_FILENAME).bin
	$(NO_ECHO)$(OBJCOPY) -O binary $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).out $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).bin

## Create binary .hex file from the .out file
genhex: 
	@echo Preparing: $(OUTPUT_FILENAME).hex
	$(NO_ECHO)$(OBJCOPY) -O ihex $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).out $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).hex
echosize:
	-@echo ''
	$(NO_ECHO)$(SIZE) $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).out
	-@echo ''

clean:
	$(RM) $(BUILD_DIRECTORIES)

cleanobj:
	$(RM) $(BUILD_DIRECTORIES)/*.o
flash: nrf51422_xxac
	@echo Flashing: $(OUTPUT_BINARY_DIRECTORY)/$<.hex
	nrfjprog --program $(OUTPUT_BINARY_DIRECTORY)/$<.hex -f nrf51  --chiperase
	nrfjprog --reset -f nrf51

# NOTE: PA: Added for easy debugging through JLink. Do not work with OpenOCD.

gdb-server: nrf51422_xxac
	JLinkGDBServerCLExe -device nrf51422_xxac -if swd -port 2331

gdb-client: nrf51422_xxac
	gdb -ex "target extended-remote localhost:2331" $(OUTPUT_BINARY_DIRECTORY)/$<.out
