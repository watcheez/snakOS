ASM=nasm
ASFLAGS=-f bin
LDFLAGS=
SOURCES=alphabet.asm
OBJECTS=$(SOURCES:.asm=.o)
EXECUTABLES=alphabet.bin keyboard.bin stack.bin test.bin disk.bin protected.bin
RUN_EMU=$(qemu-system-x86_64)make

all: $(EXECUTABLES)


#$(EXECUTABLE): $(OBJECTS)
#	$(LD) $(LDFLAGS) $(OBJECTS) -o $@

%.bin: %.asm
	$(ASM) $(ASFLAGS) $< -o $@

clean:
	rm -f *.o

distclean: clean
	rm -f *.bin
