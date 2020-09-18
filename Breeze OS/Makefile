#
#	Makefile for the BreezeKernel by V01D
#
#	Optional arguments: clean_build=(some_value) quiet=(some_value) release=(some_value)
#	Example: make all clean_build=1 quiet=1
#	
#	clean_build --> Puts all object files into obj/. If not specified, all object files will be put in the directory of the makefile
#	quiet --> If passed as an argument, the compilation commands will not be shown, i.e. gcc command will be supressed
#	release --> Removes debugging symbols and debugging define directives. Should only be run if an official release is planned.
#	
#	Cleaning object files:
#		make clean clean_build=1 ~ Clean object files inside of obj/
#		make clean		 ~ Clean object files in directory of the makefile
#		
#		
#		
#	All make commands:
#		make purge ~ Remove all object files in the current directory + obj/, remove .elf files in the current directory, and remove the iso/ folder. (Flags can be applied)
#		make clean ~ Clean object files. (Flags can be applied)
#		make all   ~ compile all C and ASM files in the src dir to object files, and link them. (Flags can be applied)
#		make run   ~ Run the kernel.elf with the -kernel flag in qemu
#		make run_iso ~ Run the iso file in qemu 
#		make run_debug ~ Run the kernel.elf file in Qemu with the -s -S flags for gdb.
#		make iso:  ~ Create a bootable ISO file using grub-mkrescue (The flags "quiet" can be applied)
#		make setup ~ Run chmod +x scripts/*.sh
#		make install ~ Must be run.
#		


CFILES := $(shell find src/ -type f -name '*.c')
ASMFILES  := $(shell find src/ -type f -name '*.asm')
OBJ_C     := $(CFILES:.c=.o)
OBJ_ASM   := $(ASMFILES:.asm=.o)
OBJ = $(OBJ_C) $(OBJ_ASM)

#GCC Compiler flags
CFLAGS = -Iincludes/ -g -ffreestanding -nostdlib -m32 ${DDIRECTIVE} -c
# Change ${DDIRECTIVE_RELEASE} to ${DDIRECTIVE_RELEASE_RAW_SPEED} if you wish for no delay during printing to the screen. This will make the text unreadable, but the OS boots up a bit faster
CFLAGS_RELEASE = -Iincludes/ -ffreestanding -nostdlib -m32 ${DDIRECTIVE_RELEASE} -c
CC_VERBOSE = gcc
CC = @gcc

#Nasm Compiler flags
NFLAGS = -f elf32 -F dwarf -g
NFLAGS_RELEASE = -f elf32
NASM_VERBOSE = nasm
NASM = @nasm
TARGET = kernel.elf
LD = @ld
LD_VERBOSE = ld
LDFLAGS = -m elf_i386 -T link.ld
ISO_DIR_GRUB = iso/boot/grub
ISO_DIR_ELF = iso/boot
ISO = BreezeOS.iso
#Define directives  
# FLAGS: -DDEBUG Prints kernel logs to the screen, -DFLAKE_VERSION Specifies version of the FLAKE Shell. (Will be printed) upon initializing Flake, -DVERBOSE If this is set, then the screen will spit out verbose logs about what it is doing. -DVM_(QEMU, VBOX, BOCHS) (example -DVM_QEMU) ~ specifies whether or not a VM is used. This info is need for shutting down the VM and other stuff.

DDIRECTIVE = -DVERBOSE -DDEBUG -DFLAKE_VERSION=\"0.0\" -DVM_QEMU -Daesthetic
DDIRECTIVE_RELEASE = -DVERBOSE -DFLAKE_VERSION=\"0.0\" -Daesthetic
DDIRECTIVE_RELEASE_RAW_SPEED = -DVERBOSE -DFLAKE_VERSION=\"0.0\"

HFILE_INSTALL_DIR = /usr/include/BreezeOS

COM_COLOR   = \033[0;34m
OBJ_COLOR   = \033[0;36m
OK_COLOR    = \033[0;32m
ORANGE  = \033[0;33m
NO_COLOR    = \033[m
BOLD	    = \u001b[40;1m
LIGHT_YELLOW = \e[93m
LIGHT_BLUE = \e[96m
NASM_COM = \e[94m
LIGHT_CYAN = \e[96m
RED = \e[91m
RESET = \e[39m


# create all the required descriptors, load the gdt like I did in my 32 bit GDT, and then I call flush_gdt (specified in link below)
# https://github.com/sigma-os/Sigma/blob/master/kernel/source/arch/x86_64/interrupts.asm#L337-L356 ~ gdt in 64 bit is in there
# About the GDT in 64 bit mode:
# but in kernel mode you only need a code selector really
# the rest can be set to 0  (except for userland, that needs a datasegment)

# list of things that need to be done for a 64 bit os:

# if you want some guidance
# after the GDT its a good idea to do your IDT
# then the TSS
# then start using ISTs
# then do a more robust paging implementation + physical memory manager + heap
# after that a whole world opens up
# you can focus on a lot of drivers
# if you want a shell to run i'd write an AHCI driver (sata disks) some filesystem driver and basic userland support
# with that i mean some syscalls and executable loading

all: $(TARGET)
	@printf "[$(OK_COLOR)OK$(RESET)] Completed compilation\n";
	
$(TARGET) : $(OBJ)
	@printf "$(LIGHT_YELLOW)Linking $(OBJ_COLOR) object $(RESET) files.$(RESET)\n";
ifdef clean_build
ifndef quiet
	mv $(OBJ) ./obj
	@printf "[$(RED)NOTE$(RESET)] Using clean build - Recompilation will occur every time you run make\n";
	$(LD_VERBOSE) $(LDFLAGS) -o $(TARGET) obj/*.o
else
	@mv $(OBJ) ./obj
	@printf "[$(RED)NOTE$(RESET)] Using clean build - Recompilation will occur every time you run make\n";
	$(LD) $(LDFLAGS) -o $(TARGET) obj/*.o
endif
else
ifndef quiet
	mv $(OBJ) .
	$(LD) $(LDFLAGS) -o $(TARGET) *.o
else
	@mv $(OBJ) .
	$(LD) $(LDFLAGS) -o $(TARGET) *.o
endif
endif
		
	@printf "[$(OK_COLOR)OK$(RESET)] Created $(TARGET)\n";

clean:
ifdef clean_build
ifndef quiet
	@printf "Cleaning object files.\n";
	rm obj/*.o
else
	@printf "Cleaning object files.\n";
	@rm obj/*.o
endif
else
ifdef quiet
	@printf "Cleaning object files.\n";
	@rm *.o
else
	@printf "Cleaning object files.\n";
	rm *.o
endif
endif

run:
	qemu-system-i386 -kernel $(TARGET)

run_debug:
	# qemu-system-x86_64 -cdrom BreezeOS.iso # Debugging also works by writing data to com1: -serial file:serial.log, debugging via gdb: -s -S
	qemu-system-i386 -kernel $(TARGET) -S -s
	
run_iso:
	qemu-system-i386 -cdrom $(ISO)
	
iso: $(ISO)
	@printf "[$(OK_COLOR)OK$(RESET)] Created $(ISO)\n";
	@printf "[$(LIGHT_YELLOW)LOG$(RESET)] Checking if multiboot works...\n";
	@./scripts/check-multiboot.sh

$(ISO): grub_
	
grub_:
ifndef quiet
	@printf "[$(LIGHT_YELLOW)LOG$(RESET)] Creating iso folder structure....\n";
	@printf "[$(OK_COLOR)OK$(RESET)] Created iso folder structure\n";
	mkdir -p $(ISO_DIR_GRUB)
	cp $(TARGET) $(ISO_DIR_ELF)/$(TARGET)
	cp grub/grub.cfg $(ISO_DIR_GRUB)/grub.cfg
	@printf "[$(LIGHT_YELLOW)LOG$(RESET)] Creating ISO....\n";
	grub-mkrescue -o $(ISO) iso
# 	grub-mkimage
else
	@printf "[$(LIGHT_YELLOW)LOG$(RESET)] Creating iso folder structure....\n";
	@printf "[$(OK_COLOR)OK$(RESET)] Created iso folder structure\n";
	@mkdir -p $(ISO_DIR_GRUB)
	@cp $(TARGET) $(ISO_DIR_ELF)/$(TARGET)
	@cp grub/grub.cfg $(ISO_DIR_GRUB)/grub.cfg
	@printf "[$(LIGHT_YELLOW)LOG$(RESET)] Creating ISO....\n";
	@grub-mkrescue -o $(ISO) iso 1>/dev/null
endif
	
notify_asm:
	@printf "$(NASM_COM)\e[4mCOMPILING NASM CODE\e[24m...\n$(RESET)";

notify_gcc:
	@printf "$(ORANGE)\e[4mCOMPILING C CODE\e[24m...\n$(RESET)";
	
purge:
ifndef quiet
	@printf "$(RED)Purging project files...\n$(RESET)";
	rm obj/*.o || echo ""
	rm *.o || echo ""
	rm *.elf || echo ""
	rm -rf iso/ || echo ""
else
	@printf "$(RED)Purging project files...\n$(RESET)";
	@rm obj/*.o 2>/dev/null || echo ""
	@rm *.o 2>/dev/null || echo ""
	@rm *.elf || echo ""
	@rm -rf iso/ || echo ""
endif
	
	
setup:
	chmod +x scripts/*.sh

install:
	@printf "Moving header files into $(LIGHT_YELLOW)$(HFILE_INSTALL_DIR)$(RESET)\n";
	@sudo rm -rf $(HFILE_INSTALL_DIR) || echo ""
	@sudo cp -r includes/ $(HFILE_INSTALL_DIR)
	@printf "[$(OK_COLOR)OK$(RESET)] Done.\n";
	
%.o : %.asm notify_asm
ifdef quiet
	@printf "$(OK_COLOR)Compiling $(COM_COLOR)$<...\n$(RESET)";
ifdef release
	$(NASM) $(NFLAGS_RELEASE) $< -o $@
else
	$(NASM) $(NFLAGS) $< -o $@
endif

else

ifdef release
	@printf "$(OK_COLOR)Compiling $(COM_COLOR)$<...\n$(RESET)";
	$(NASM_VERBOSE) $(NFLAGS_RELEASE) $< -o $@
else
	@printf "$(OK_COLOR)Compiling $(COM_COLOR)$<...\n$(RESET)";
	$(NASM_VERBOSE) $(NFLAGS) $< -o $@
endif
endif
	
	
%.o : %.c notify_gcc
ifdef quiet
	@printf "$(OK_COLOR)Compiling $(COM_COLOR)$<...\n$(RESET)";
ifdef release
	$(CC) $(CFLAGS_RELEASE) $< -o $@
else
	$(CC) $(CFLAGS) $< -o $@
endif
else
	@printf "$(OK_COLOR)Compiling $(COM_COLOR)$<...\n$(RESET)";
ifdef release
	$(CC_VERBOSE) $(CFLAGS_RELEASE) $< -o $@
else
	$(CC_VERBOSE) $(CFLAGS) $< -o $@
endif
endif
