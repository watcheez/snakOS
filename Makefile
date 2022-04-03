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
LDFLAGS=--oformat binary -Ttext 0x1000
FINAL_BIN=snakOs.bin

all: $(BINDIR)/everything.bin $(BINDIR)/zeroes.bin
	cat $^ > $(FINAL_BIN)

$(BINDIR)/everything.bin: $(BINDIR)/boot.bin $(BINDIR)/full_kernel.bin
	cat $^ > $@

$(BINDIR)/boot.bin: $(SRCDIR)/boot.asm
	$(ASM) $< -f bin -o $@

$(BINDIR)/zeroes.bin: $(SRCDIR)/zeroes.asm
	$(ASM) $< -f bin -o $@

$(BINDIR)/full_kernel.bin: $(OBJDIR)/kernel_entry.o $(OBJDIR)/kernel.o $(OBJDIR)/print.o $(OBJDIR)/idt.o $(OBJDIR)/memfunc.o $(OBJDIR)/isrs.o
	$(LD) $(LDFLAGS) $^ -o $@

$(OBJDIR)/kernel_entry.o: $(SRCDIR)/kernel_entry.asm
	$(ASM) $(ASFLAGS) $< -o $@

$(COBJECTS): $(OBJDIR)/%.o: $(SRCDIR)/%.c $(HFILES)
	$(CC) $(CFLAGS) $(CPPFLAGS) $< -o $@


clean:
	rm -f obj/*.o

distclean: clean
	rm -f bin/*.bin
	rm -f *.bin
