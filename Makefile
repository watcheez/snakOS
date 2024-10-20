ASM=nasm
ASFLAGS=-f elf
CC=i386-elf-gcc
CFLAGS=-ffreestanding -m32 -g -c
CPPFLAGS=-I$(INCLUDEDIR)
LD=i386-elf-ld
SRCDIR=./src
BINDIR=./bin
OBJDIR=./obj
INCLUDEDIR=./include
ENTRY_ASMFILES=$(wildcard $(SRCDIR)/*_entry.asm)
CFILES=$(wildcard $(SRCDIR)/*.c)
HFILES=$(wildcard $(INCLUDEDIR)/*.h)
COBJECTS=$(CFILES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
ASMOBJECTS=$(ENTRY_ASMFILES:$(SRCDIR)/%_entry.asm=$(OBJDIR)/%_entry.o)
LDFLAGS=--oformat binary -Ttext 0x7e00
FINAL_BIN=snakOs.bin

all: $(BINDIR)/everything.bin $(BINDIR)/zeroes.bin
	cat $^ > $(FINAL_BIN)

$(BINDIR)/everything.bin: $(BINDIR)/boot.bin $(BINDIR)/full_kernel.bin
	cat $^ > $@

$(BINDIR)/boot.bin: $(SRCDIR)/boot.asm
	mkdir -p $(BINDIR)
	$(ASM) $< -f bin -o $@

$(BINDIR)/zeroes.bin: $(SRCDIR)/zeroes.asm
	mkdir -p $(BINDIR)
	$(ASM) $< -f bin -o $@

$(BINDIR)/full_kernel.bin: $(OBJDIR)/kernel_entry.o $(OBJDIR)/kernel.o $(OBJDIR)/idt.o $(OBJDIR)/memfunc.o $(OBJDIR)/isrs.o $(OBJDIR)/irq.o $(OBJDIR)/vga.o $(OBJDIR)/timer.o $(OBJDIR)/kb.o $(OBJDIR)/mainmenu.o $(OBJDIR)/game.o 
	mkdir -p $(BINDIR)
	$(LD) $(LDFLAGS) $^ -o $@

$(OBJDIR)/kernel_entry.o: $(SRCDIR)/kernel_entry.asm
	mkdir -p $(OBJDIR)
	$(ASM) $(ASFLAGS) $< -o $@

$(COBJECTS): $(OBJDIR)/%.o: $(SRCDIR)/%.c $(HFILES)
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) $< -o $@


clean:
	rm -f obj/*.o

distclean: clean
	rm -f bin/*.bin
	rm -f *.bin
