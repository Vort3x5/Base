ASM := fasm
CC := i686-elf-gcc
LD := i686-elf-ld
CFLAGS := -O1 -std=gnu99 -nostdlib -ffreestanding -I include/ \
		  -Wno-shift-count-overflow -Wno-int-to-pointer-cast

C_SRCS := $(wildcard src/*.c drivers/*.c)
ASM_SRCS := $(wildcard init/*.asm)
BOOT_SRCS := $(wildcard boot/src/*.asm)

C_OBJS := $(patsubst %.c, obj/%.o, $(notdir $(C_SRCS)))
ASM_OBJS := $(patsubst %.asm, obj/%.o, $(notdir $(ASM_SRCS)))

BOOT_BINS := $(patsubst %.asm, bin/%.bin, $(notdir $(BOOT_SRCS)))

LLD := obj/entry.o $(C_OBJS)

DRIVE := /dev/sdb

all: dirs Base.bin kernel_info $(BOOT_BINS)
	dd if=./bin/boot.bin of=$(DRIVE) bs=512 count=1
	dd if=./bin/load.bin of=$(DRIVE) bs=512 seek=1
	dd if=./bin/Base.bin of=$(DRIVE) bs=512 seek=3

bin/%.bin: boot/src/%.asm
	$(ASM) $< $@

kernel_info:
	lua scripts/kernel_size.lua

# $(CC) $(CFLAGS) -e _Start -Ttext 0x1000 -o bin/$@ $^
Base.bin: $(ASM_OBJS) $(C_OBJS)
	$(LD) --Ttext 0x100000 -s --oformat binary -e _Start -o bin/$@ $(LLD)

obj/%.o: drivers/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

obj/%.o: init/%.asm
	$(ASM) $< $@

dirs:
	mkdir -p obj/
	mkdir -p bin/
	mkdir -p iso/

clean:
	rm -rf boot.iso bin/ iso/ obj/
	
# sudo chown <username> $(DRIVE)
release:
	qemu-system-i386 -hdb $(DRIVE)

.PHONY: clean release debug
