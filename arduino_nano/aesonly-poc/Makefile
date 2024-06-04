
# name of the project,
# the executable and binary will have a filename same as project name
PROJECT_NAME := aesonly-poc



# Types of builds taken care separately.
# DBG = Debug
# PRD = Prod (Release)



# Different Directories (relative addresses with respect to this makefile location)

# directory where all the source files for current project are located.
SRC_DIR 		:= ./src

# directory where all the object files for current project are located.
DBG_OBJ_DIR 	:= ./debug/obj
PRD_OBJ_DIR 	:= ./prod/obj

# directory where all the assembly files (not source assembly) for current project are located.
DBG_ASM_DIR		:= ./debug/asm
PRD_ASM_DIR		:= ./prod/asm

# directory where all the disassembly files for current project are located.
DBG_DASM_DIR	:= ./debug/dasm
PRD_DASM_DIR	:= ./prod/dasm

# Root of the Arduino Runtime directory
RUNTIME_DIR 	:= ../ARL

# Root of the user libraries folder
LIB_ROOT_DIR	:= ./src/tinyaes

# various include directories where header files are located.
INC_DIR_1		:= ${RUNTIME_DIR}/src/cores/arduino
INC_DIR_2		:= ${RUNTIME_DIR}/src/variants/eightanaloginputs

# All the include directories combined
INC_DIRS 		:= ${INC_DIR_1} ${INC_DIR_2}
# suffix -I to all the include directories, to be used as command line argument
INC_DIRS_ARG	:= ${addprefix -I, ${INC_DIRS}}


# The Arduino Runtime Library Archive (aka Arduino Core - core.a originally)
DBG_ARL := ${RUNTIME_DIR}/debug/obj/ARL.a
PRD_ARL := ${RUNTIME_DIR}/prod/obj/ARL.a


# Uncomment if you are using the libraries
# -----------------------------------------------------------
# Individual User Library folders
#LIB_DIR_1 := ${LIB_ROOT_DIR}/avr-debug
# all the User library folders combined
#LIB_DIR_ALL := ${LIB_DIR_1}

# Object Directory for User Library 1 (Debug build)
#DBG_OBJ_DIR_LIB_1 := ${LIB_DIR_1}/debug/obj
# Object files for User Library 1 (Debug build)
#DBG_OBJ_DIR_FNM_EXT_LIB_1 := ${DBG_OBJ_DIR_LIB_1}/*.o

# Object Directory for User Library 1 (Prod build)
#PRD_OBJ_DIR_LIB_1 := ${LIB_DIR_1}/prod/obj
# Object files for User Library 1 (Prod build)
#PRD_OBJ_DIR_FNM_EXT_LIB_1 := ${PRD_OBJ_DIR_LIB_1}/*.o

# Object files for all the User Libraries (Debug build)
#DBG_OBJ_DIR_FNM_EXT_LIB_ALL := ${DBG_OBJ_DIR_FNM_EXT_LIB_1}
# Object files for all the User Libraries (Prod build)
#PRD_OBJ_DIR_FNM_EXT_LIB_ALL := ${PRD_OBJ_DIR_FNM_EXT_LIB_1}
# -----------------------------------------------------------


# The Toolchain binaries (Absolute addresses/paths)
# Change these values as per your installation.
# --------------------------------------------------------------------
# GCC - The GNU C Compiler
GCC := avr-gcc
# GPP - The GNU C++ Compiler
GPP := avr-g++
# OBJDMP - Objectdump utility, for listing symbols, generating disassemblies, etc.
OBJDMP := avr-objdump
# OBJCPY - Objectcopy utility, for converting one binary format to another (elf to hex)
OBJCPY := avr-objcopy
# AR - Archiver utility, for packing/unpacking object file archives
AR := avr-gcc-ar
# QEMU - AVR System Emulator, to run code in an emulator without uploading to arduino
QEMU := qemu-system-avr
# GDB - The GNU Debugger, to debug the program line by line (step)
GDB := avr-gdb
# AVRDUD - to upload the program to arduino
AVRDUD := avrdude



# MCU specific settings
# The Name of the microcontroller unit (MCU)
MCU := atmega328p
# The clock frequence (in Hz)
F_CPU := 16000000UL




# Compilation Flags
# compile only - do not link (-c), Optimizations enabled (-Os) and debug info preserved (-g)
DBG_CFLAGS := -c -g -Os -MMD -DF_CPU=${F_CPU} -mmcu=${MCU} ${INC_DIRS_ARG}
DBG_SFLAGS := -c -g -x assembler-with-cpp -MMD -DF_CPU=${F_CPU} -mmcu=${MCU} ${INC_DIRS_ARG}

# compile only - do not link (-c), Optimizations enabled (-Os) and debug info not preserved
PRD_CFLAGS := -c -Os -MMD -DF_CPU=${F_CPU} -mmcu=${MCU} ${INC_DIRS_ARG}
PRD_SFLAGS := -c -x assembler-with-cpp -MMD -DF_CPU=${F_CPU} -mmcu=${MCU} ${INC_DIRS_ARG}

# Linker Flags, not so much as all the additional flags are there in recipe 
# because they depend on the target name 
DBG_LDFLAGS := -mmcu=${MCU}
PRD_LDFLAGS := -mmcu=${MCU}
# ${INC_DIRS_ARG}


# Notation
# DIR = Dircetory
# FNM = FileName
# EXT = Extention

# Src Files , this is not used anymore now.
# SRC_FNM := blink_arduino	#name only, no extension


# C Source Files (.c) and respective Object Files
SRC_DIR_FNM_EXT_C := $(wildcard $(SRC_DIR)/*.c)
# Object files to be obtained by compiling C source files (Debug Build)
DBG_OBJ_DIR_FNM_EXT_C := $(patsubst $(SRC_DIR)/%.c,$(DBG_OBJ_DIR)/%.c.o,$(SRC_DIR_FNM_EXT_C))
# Object files to be obtained by compiling C source files (Prod Build)
PRD_OBJ_DIR_FNM_EXT_C := $(patsubst $(SRC_DIR)/%.c,$(PRD_OBJ_DIR)/%.c.o,$(SRC_DIR_FNM_EXT_C))



# C++ (CPP) Source Files (.cpp) and respective Object Files
SRC_DIR_FNM_EXT_CPP := $(wildcard $(SRC_DIR)/*.cpp)
# Object files to be obtained by compiling C++ source files (Debug Build)
DBG_OBJ_DIR_FNM_EXT_CPP := $(patsubst $(SRC_DIR)/%.cpp,$(DBG_OBJ_DIR)/%.cpp.o,$(SRC_DIR_FNM_EXT_CPP))
# Object files to be obtained by compiling C++ source files (Prod Build)
PRD_OBJ_DIR_FNM_EXT_CPP := $(patsubst $(SRC_DIR)/%.cpp,$(PRD_OBJ_DIR)/%.cpp.o,$(SRC_DIR_FNM_EXT_CPP))



# Assembly Source Files (.S) and respective Object Files
SRC_DIR_FNM_EXT_S := $(wildcard $(SRC_DIR)/*.S)
# Object files to be obtained by compiling Assembly source files (Debug Build)
DBG_OBJ_DIR_FNM_EXT_S := $(patsubst $(SRC_DIR)/%.S,$(DBG_OBJ_DIR)/%.S.o,$(SRC_DIR_FNM_EXT_S))
# Object files to be obtained by compiling Assembly source files (Prod Build)
PRD_OBJ_DIR_FNM_EXT_S := $(patsubst $(SRC_DIR)/%.S,$(PRD_OBJ_DIR)/%.S.o,$(SRC_DIR_FNM_EXT_S))



# All Object Files (Debug Build)
DBG_OBJ_DIR_FNM_EXT_ALL := ${DBG_OBJ_DIR_FNM_EXT_C} ${DBG_OBJ_DIR_FNM_EXT_CPP} ${DBG_OBJ_DIR_FNM_EXT_S}
# All Object Files (Prod Build)
PRD_OBJ_DIR_FNM_EXT_ALL := ${PRD_OBJ_DIR_FNM_EXT_C} ${PRD_OBJ_DIR_FNM_EXT_CPP} ${PRD_OBJ_DIR_FNM_EXT_S}



# Executable Elf (Debug Build)
DBG_EXE_FNM := ${PROJECT_NAME}
DBG_EXE_FNM_EXT := ${addsuffix .elf, ${DBG_EXE_FNM}}
DBG_EXE_DIR_FNM_EXT := ${addprefix ${DBG_OBJ_DIR}/, ${DBG_EXE_FNM_EXT}}
# Executable Elf (Prod Build)
PRD_EXE_FNM := ${PROJECT_NAME}
PRD_EXE_FNM_EXT := ${addsuffix .elf, ${PRD_EXE_FNM}}
PRD_EXE_DIR_FNM_EXT := ${addprefix ${PRD_OBJ_DIR}/, ${PRD_EXE_FNM_EXT}}



# Binary (here Hex) (Debug Build)
DBG_BIN_FNM := ${DBG_EXE_FNM}
DBG_BIN_FNM_EXT := ${addsuffix .hex, ${DBG_BIN_FNM}}
DBG_BIN_DIR_FNM_EXT := ${addprefix ${DBG_OBJ_DIR}/, ${DBG_BIN_FNM_EXT}}
# Binary (here Hex) (Prod Build)
PRD_BIN_FNM := ${PRD_EXE_FNM} 
PRD_BIN_FNM_EXT := ${addsuffix .hex, ${PRD_BIN_FNM}}
PRD_BIN_DIR_FNM_EXT := ${addprefix ${PRD_OBJ_DIR}/, ${PRD_BIN_FNM_EXT}}



# Assembler output files (Debug Build)
DBG_ASM_FNM_EXT := ${addsuffix .s, ${SRC_FNM}}
DBG_ASM_DIR_FNM_EXT := ${addprefix ${DBG_ASM_DIR}/, ${DBG_ASM_FNM_EXT}}
# Assembler output files (Prod Build)
PRD_ASM_FNM_EXT := ${addsuffix .s, ${SRC_FNM}}
PRD_ASM_DIR_FNM_EXT := ${addprefix ${PRD_ASM_DIR}/, ${PRD_ASM_FNM_EXT}}



# Disassembly files (Debug Build)
DBG_DASM_FNM_EXT := ${addsuffix .asm, ${SRC_FNM}}
DBG_DASM_DIR_FNM_EXT := ${addprefix ${DBG_DASM_DIR}/, ${DBG_DASM_FNM_EXT}} ${addsuffix .asm, ${DBG_DASM_DIR}/${DBG_EXE_FNM}}
DBG_DASM_I_FNM_EXT := ${addsuffix _i.asm, ${SRC_FNM}}
DBG_DASM_I_DIR_FNM_EXT := ${addprefix ${DBG_DASM_DIR}/, ${DBG_DASM_I_FNM_EXT}} ${addsuffix _i.asm, ${DBG_DASM_DIR}/${DBG_EXE_FNM}}
# Disassembly files (Prod Build)
# BTW, interactive disassembly doesn't make any sense for prod (release) build
PRD_DASM_FNM_EXT := ${addsuffix .asm, ${SRC_FNM}}
PRD_DASM_DIR_FNM_EXT := ${addprefix ${PRD_DASM_DIR}/, ${PRD_DASM_FNM_EXT}} ${addsuffix .asm, ${PRD_DASM_DIR}/${PRD_EXE_FNM}}
PRD_DASM_I_FNM_EXT := ${addsuffix _i.asm, ${SRC_FNM}}
PRD_DASM_I_DIR_FNM_EXT := ${addprefix ${PRD_DASM_DIR}/, ${PRD_DASM_I_FNM_EXT}} ${addsuffix _i.asm, ${PRD_DASM_DIR}/${PRD_EXE_FNM}}




# File with following extensions to be Cleaned(Deleted)
CLN_FNM_EXT := *.o *.elf *.bin *.ali *.asm *.s *.S *.map *.hex *.d
# Files to be deleted (Debug Build)
DBG_CLN_OBJ_DIR_FNM_EXT := ${addprefix ${DBG_OBJ_DIR}/, ${CLN_FNM_EXT}}
DBG_CLN_ASM_DIR_FNM_EXT := ${DBG_ASM_DIR}/*.s
DBG_CLN_DASM_DIR_FNM_EXT := ${DBG_DASM_DIR}/*.asm
# Files to be deleted (Prod Build)
PRD_CLN_OBJ_DIR_FNM_EXT := ${addprefix ${PRD_OBJ_DIR}/, ${CLN_FNM_EXT}}
PRD_CLN_ASM_DIR_FNM_EXT := ${PRD_ASM_DIR}/*.s
PRD_CLN_DASM_DIR_FNM_EXT := ${PRD_DASM_DIR}/*.asm



# Recipe Build Libraries (Debug Build)
# This will call "make all_dbg" for all the libaries
lib_all_dbg:
	for d in ${LIB_DIR_ALL} ; do \
		$(MAKE) -w -C $$d all_dbg ; \
	done

# Recipe Clean Libraries (Debug Build)
# This will call "make clean_dbg" for all the libaries
lib_clean_dbg:
	for d in ${LIB_DIR_ALL} ; do \
		$(MAKE) -w -C $$d clean_dbg ; \
	done

# Recipe Build Libraries (Prod Build)
# This will call "make all_prd" for all the libaries
lib_all_prd:
	for d in ${LIB_DIR_ALL} ; do \
		$(MAKE) -w -C $$d all_prd ; \
	done

# Recipe Clean Libraries (Prod Build)
# This will call "make clean_prd" for all the libaries
lib_clean_prd:
	for d in ${LIB_DIR_ALL} ; do \
		$(MAKE) -w -C $$d clean_prd ; \
	done







# Recipe Bin (here .elf to .hex) (Debug Build)
bin_dbg : ${DBG_BIN_DIR_FNM_EXT}
# Recipe Bin (here .elf to .hex) (Prod Build)
bin_prd : ${PRD_BIN_DIR_FNM_EXT}







# Recipe all (Debug Build)
# It does :
#	- build libraries (lib_all_dbg)
#	- compile source files (compile_dbg)
#	- link all the object files (link_dbg)
# Not using below as no libraries
#all_dbg : lib_all_dbg compile_dbg link_dbg 
all_dbg : clean_dbg compile_dbg link_dbg bin_dbg 
# Recipe all (Prod Build)
all_prd : compile_prd link_prd




# Disassembly (both full disassembly and source-intermixed disassemnly)
# Recipe disasm (Debug Build)
disasm_dbg : ${DBG_DASM_DIR_FNM_EXT} ${DBG_DASM_I_DIR_FNM_EXT}
# Recipe disasm (Prod Build)
disasm_prd : ${PRD_DASM_DIR_FNM_EXT} ${PRD_DASM_I_DIR_FNM_EXT}


# Recipe asmble (Debug Build) - TO DO (Doesn't work now)
asmble_dbg : ${DBG_ASM_DIR_FNM_EXT}
# Recipe asmble (Prod Build) - TO DO (Doesn't work now)
asmble_prd : ${PRD_ASM_DIR_FNM_EXT}




# Recipe Compile (Compile all source files into object files) (Debug Build)
compile_dbg : ${DBG_OBJ_DIR_FNM_EXT_ALL}


# compile C files
${DBG_OBJ_DIR}/%.c.o: ${SRC_DIR}/%.c
	$(GCC) $(DBG_CFLAGS) -o $@ $^

# compile C++ files
${DBG_OBJ_DIR}/%.cpp.o: ${SRC_DIR}/%.cpp
	$(GPP) $(DBG_CFLAGS) -o $@ $^

# compile Assembly files
${DBG_OBJ_DIR}/%.S.o: ${SRC_DIR}/%.S
	$(GCC) $(DBG_SFLAGS) -o $@ $^



# Recipe Compile (Compile all source files into object files) (Prod Build)
compile_prd : ${PRD_OBJ_DIR_FNM_EXT_ALL}

# compile C files
${PRD_OBJ_DIR}/%.c.o: ${SRC_DIR}/%.c
	$(GCC) $(PRD_CFLAGS) -o $@ $^

# compile C++ files
${PRD_OBJ_DIR}/%.cpp.o: ${SRC_DIR}/%.cpp
	$(GPP) $(PRD_CFLAGS) -o $@ $^

# compile Assembly files
${PRD_OBJ_DIR}/%.S.o: ${SRC_DIR}/%.S
	$(GCC) $(PRD_SFLAGS) -o $@ $^






# Recipe Link (Debug Build)
link_dbg : ${DBG_EXE_DIR_FNM_EXT}

${DBG_EXE_DIR_FNM_EXT}: ${DBG_OBJ_DIR_FNM_EXT_ALL}
	$(GCC) $(DBG_LDFLAGS) -Wl,-Map=$@.map -o $@ $^ ${DBG_OBJ_DIR_FNM_EXT_LIB_ALL} ${DBG_ARL}


# Recipe Link (Prod Build)
link_prd : ${PRD_EXE_DIR_FNM_EXT}

${PRD_EXE_DIR_FNM_EXT}: ${PRD_OBJ_DIR_FNM_EXT_ALL}
	$(GCC) $(PRD_LDFLAGS) -Wl,-Map=$@.map -o $@ $^ ${PRD_OBJ_DIR_FNM_EXT_LIB_ALL} ${PRD_ARL}






# Bin (Hex) Full Recipe (Debug Build)
${DBG_BIN_DIR_FNM_EXT}:
	$(OBJCPY) -O ihex -R .eeprom ${DBG_EXE_DIR_FNM_EXT} $@

# Bin (Hex) Full Recipe (prod Build)
${PRD_BIN_DIR_FNM_EXT}:
	$(OBJCPY) -O ihex -R .eeprom ${PRD_EXE_DIR_FNM_EXT} $@





# Assemble Only Full Recipe (Debug Build)
# Assemble C source files
${DBG_ASM_DIR}/%.s: ${SRC_DIR}/%.c
	$(GCC) $(DBG_SFLAGS) -o $@ $^

# Assemble CPP source files
${DBG_ASM_DIR}/%.s: ${SRC_DIR}/%.cpp
	$(GPP) $(DBG_SFLAGS) -o $@ $^


# Assemble Only Full Recipe (Prod Build)
# Assemble C source files
${PRD_ASM_DIR}/%.s: ${SRC_DIR}/%.c
	$(GCC) $(PRD_SFLAGS) -o $@ $^

# Assemble CPP source files
${PRD_ASM_DIR}/%.s: ${SRC_DIR}/%.cpp
	$(GPP) $(PRD_SFLAGS) -o $@ $^







# Disassemble Full Recipe
# Source intermixed disassembly (Debug Build)
${DBG_DASM_DIR}/%_i.asm: ${DBG_OBJ_DIR}/%.o
	$(OBJDMP) -S $^ > $@

${DBG_DASM_DIR}/%_i.asm: ${DBG_OBJ_DIR}/%.elf
	$(OBJDMP) -S $^ > $@

# Full disassembly (Debug Build)
${DBG_DASM_DIR}/%.asm: ${DBG_OBJ_DIR}/%.o
	$(OBJDMP) -D $^ > $@

${DBG_DASM_DIR}/%.asm: ${DBG_OBJ_DIR}/%.elf
	$(OBJDMP) -D $^ > $@


# Source intermixed disassembly (Prod Build)
${PRD_DASM_DIR}/%_i.asm: ${PRD_OBJ_DIR}/%.o
	$(OBJDMP) -S $^ > $@

${PRD_DASM_DIR}/%_i.asm: ${PRD_OBJ_DIR}/%.elf
	$(OBJDMP) -S $^ > $@

# Full disassembly (Prod Build)
${PRD_DASM_DIR}/%.asm: ${PRD_OBJ_DIR}/%.o
	$(OBJDMP) -D $^ > $@

${PRD_DASM_DIR}/%.asm: ${PRD_OBJ_DIR}/%.elf
	$(OBJDMP) -D $^ > $@








# print the header of elf (Debug Build)
header_dbg : ${DBG_EXE_DIR_FNM_EXT}
	$(OBJDMP) -h $^

# print the header of elf (Prod Build)
header_prd : ${PRD_EXE_DIR_FNM_EXT}
	$(OBJDMP) -h $^









# clean all the object files (Project + Libraries) (Debug build)
# Not using below as no libraries
#clean_all_dbg : clean_dbg lib_clean_dbg
clean_all_dbg : clean_dbg

# clean all the object files for current project (Debug Build)
clean_dbg :
	rm -rf ${DBG_CLN_OBJ_DIR_FNM_EXT} ${DBG_CLN_DASM_DIR_FNM_EXT} ${DBG_CLN_ASM_DIR_FNM_EXT}

# clean all the object files (Project + Libraries) (Prod build)
#clean_all_prd : clean_prd lib_clean_prd
clean_all_prd : clean_prd
# clean all the object files for current project (Prod Build)
clean_prd :
	rm -rf ${PRD_CLN_OBJ_DIR_FNM_EXT} ${PRD_CLN_DASM_DIR_FNM_EXT} ${PRD_CLN_ASM_DIR_FNM_EXT}







# call like > make load_dbg PORT=COM7
# Upload debug binary (.hex) to arduino

# Note that arduino nano (with Old Bootloader) won't work at 115200 Baudrate,
# it works at 57600 baudrate only.
# refer 
# https://arduino.stackexchange.com/questions/804/arduino-nano-uploading-gives-error-avrdude-stk500-recv-programmer-is-not-re

load_dbg :
	${AVRDUD} -D -c arduino -p ${MCU} -P ${PORT} -b 115200 -U flash:w:${DBG_BIN_DIR_FNM_EXT}

# Upload prod binary (.hex) to arduino 
load_prd :
	${AVRDUD} -D -c arduino -p ${MCU} -P ${PORT} -b 115200 -U flash:w:${PRD_BIN_DIR_FNM_EXT}






# Launch Debugger (avr-gdb)
dbg :
	$(GDB)
