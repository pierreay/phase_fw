
# Makefile for library

# ARL = Arduino Runtime Library
PROJECT_NAME := ARL



# Types of builds taken care separately.
# DBG = Debug
# PRD = Prod (Release)

# Different Directories
SRC_DIR 		:= ./src/cores/arduino
DBG_OBJ_DIR 	:= ./debug/obj
PRD_OBJ_DIR 	:= ./prod/obj
INC_DIR_1		:= ./src/cores/arduino
INC_DIR_2		:= ./src/variants/eightanaloginputs

INC_DIRS 		:= ${INC_DIR_1} ${INC_DIR_2}
INC_DIRS_ARG	:= ${addprefix -I, ${INC_DIRS}}



# The Toolchain binaries
GCC := avr-gcc
GPP := avr-g++
OBJDMP := avr-objdump
OBJCPY := avr-objcopy
AR := avr-gcc-ar



# MCU specific settings
MCU := atmega328p
F_CPU := 16000000UL



# Compilation Flags
# Optimizations enabled and debug info preserved
DBG_CFLAGS := -c -g -Os -MMD -DF_CPU=${F_CPU} -mmcu=${MCU} ${INC_DIRS_ARG}
DBG_SFLAGS := -c -g -x assembler-with-cpp -MMD -DF_CPU=${F_CPU} -mmcu=${MCU} ${INC_DIRS_ARG}

# Optimizations enabled and debug info not preserved
PRD_CFLAGS := -c -Os -MMD -DF_CPU=${F_CPU} -mmcu=${MCU} ${INC_DIRS_ARG}
PRD_SFLAGS := -c -x assembler-with-cpp -MMD -DF_CPU=${F_CPU} -mmcu=${MCU} ${INC_DIRS_ARG}



# Notation
# DIR = Dircetory
# FNM = FileName
# EXT = Extention

# For a simple project, do not substitute %.c.o, but simply do %.o, it is fine
# C Source Files and respective Object Files
SRC_DIR_FNM_EXT_C := $(wildcard $(SRC_DIR)/*.c)
DBG_OBJ_DIR_FNM_EXT_C := $(patsubst $(SRC_DIR)/%.c,$(DBG_OBJ_DIR)/%.c.o,$(SRC_DIR_FNM_EXT_C))
PRD_OBJ_DIR_FNM_EXT_C := $(patsubst $(SRC_DIR)/%.c,$(PRD_OBJ_DIR)/%.c.o,$(SRC_DIR_FNM_EXT_C))



# CPP Source Files and respective Object Files
SRC_DIR_FNM_EXT_CPP := $(wildcard $(SRC_DIR)/*.cpp)
DBG_OBJ_DIR_FNM_EXT_CPP := $(patsubst $(SRC_DIR)/%.cpp,$(DBG_OBJ_DIR)/%.cpp.o,$(SRC_DIR_FNM_EXT_CPP))
PRD_OBJ_DIR_FNM_EXT_CPP := $(patsubst $(SRC_DIR)/%.cpp,$(PRD_OBJ_DIR)/%.cpp.o,$(SRC_DIR_FNM_EXT_CPP))



# Assembly Source Files and respective Object Files
SRC_DIR_FNM_EXT_S := $(wildcard $(SRC_DIR)/*.S)
DBG_OBJ_DIR_FNM_EXT_S := $(patsubst $(SRC_DIR)/%.S,$(DBG_OBJ_DIR)/%.S.o,$(SRC_DIR_FNM_EXT_S))
PRD_OBJ_DIR_FNM_EXT_S := $(patsubst $(SRC_DIR)/%.S,$(PRD_OBJ_DIR)/%.S.o,$(SRC_DIR_FNM_EXT_S))



# All Object Files
DBG_OBJ_DIR_FNM_EXT_ALL := ${DBG_OBJ_DIR_FNM_EXT_C} ${DBG_OBJ_DIR_FNM_EXT_CPP} ${DBG_OBJ_DIR_FNM_EXT_S}
PRD_OBJ_DIR_FNM_EXT_ALL := ${PRD_OBJ_DIR_FNM_EXT_C} ${PRD_OBJ_DIR_FNM_EXT_CPP} ${PRD_OBJ_DIR_FNM_EXT_S}



# Archive File
ARCHIVE_FNM_EXT := ${PROJECT_NAME}.a
DBG_ARCHIVE_DIR_FNM_EXT := ${addprefix ${DBG_OBJ_DIR}/, ${ARCHIVE_FNM_EXT}}
PRD_ARCHIVE_DIR_FNM_EXT := ${addprefix ${PRD_OBJ_DIR}/, ${ARCHIVE_FNM_EXT}}



# Files to Clean
CLN_FNM_EXT := *.o *.elf *.bin *.ali *.asm *.s *.S *.map *.hex *.d *.a
DBG_CLN_OBJ_DIR_FNM_EXT := ${addprefix ${DBG_OBJ_DIR}/, ${CLN_FNM_EXT}}
PRD_CLN_OBJ_DIR_FNM_EXT := ${addprefix ${PRD_OBJ_DIR}/, ${CLN_FNM_EXT}}



# Recipe all
all_dbg : compile_dbg archive_dbg

all_prd : compile_prd archive_prd



# Recipe Compile
compile_dbg : ${DBG_OBJ_DIR_FNM_EXT_C} ${DBG_OBJ_DIR_FNM_EXT_CPP} ${DBG_OBJ_DIR_FNM_EXT_S}

# compile C files
${DBG_OBJ_DIR}/%.c.o: ${SRC_DIR}/%.c
	$(GCC) $(DBG_CFLAGS) -o $@ $^

# compile C++ files
${DBG_OBJ_DIR}/%.cpp.o: ${SRC_DIR}/%.cpp
	$(GPP) $(DBG_CFLAGS) -o $@ $^

# compile Assembly files
${DBG_OBJ_DIR}/%.S.o: ${SRC_DIR}/%.S
	$(GCC) $(DBG_SFLAGS) -o $@ $^



compile_prd : ${PRD_OBJ_DIR_FNM_EXT_C} ${PRD_OBJ_DIR_FNM_EXT_CPP} ${PRD_OBJ_DIR_FNM_EXT_S}

# compile C files
${PRD_OBJ_DIR}/%.c.o: ${SRC_DIR}/%.c
	$(GCC) $(PRD_CFLAGS) -o $@ $^

# compile C++ files
${PRD_OBJ_DIR}/%.cpp.o: ${SRC_DIR}/%.cpp
	$(GPP) $(PRD_CFLAGS) -o $@ $^

# compile Assembly files
${PRD_OBJ_DIR}/%.S.o: ${SRC_DIR}/%.S
	$(GCC) $(PRD_SFLAGS) -o $@ $^






# Recipe Archive
archive_dbg : ${DBG_ARCHIVE_DIR_FNM_EXT} 

${DBG_ARCHIVE_DIR_FNM_EXT}: ${DBG_OBJ_DIR_FNM_EXT_ALL}
	${AR} rcs $@ $^



archive_prd : ${PRD_ARCHIVE_DIR_FNM_EXT} 

${PRD_ARCHIVE_DIR_FNM_EXT}: ${PRD_OBJ_DIR_FNM_EXT_ALL}
	${AR} rcs $@ $^





# Recipe Clean
clean_dbg :
	rm -rf ${DBG_CLN_OBJ_DIR_FNM_EXT}



clean_prd :
	rm -rf ${PRD_CLN_OBJ_DIR_FNM_EXT}



# TO DO in future, if required
# asm_dbg dasm_dbg
# asm_prd dasm_prd

