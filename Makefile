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

floppy: dirs Base.bin kernel_info $(BOOT_BINS)
	dd if=./bin/boot.bin of=iso/boot.iso bs=512 count=1
	dd if=./bin/load.bin of=iso/boot.iso bs=512 seek=1
	dd if=./bin/Base.bin of=iso/boot.iso bs=512 seek=3

GRUB: dirs Base
	mkdir -p iso/boot/grub
	grub-file --is-x86-multiboot bin/Base
	cp bin/Base iso/boot/boot.iso
	./scripts/grub.sh
	grub-mkrescue -o iso/boot.iso iso
	qemu-system-i386 -audio driver=alsa,model=ac97,id=alsa -cdrom iso/boot.iso -s -S &
	gdb -x scripts/db_grub.gdb

bin/%.bin: boot/src/%.asm
	$(ASM) $< $@

kernel_info:
	lua scripts/kernel_size.lua

# $(CC) $(CFLAGS) -e _Start -Ttext 0x1000 -o bin/$@ $^
Base.bin: $(ASM_OBJS) $(C_OBJS)
	$(LD) --Ttext 0x100000 -s --oformat binary -e _Start -o bin/$@ $(LLD)

Base: $(ASM_OBJS) $(C_OBJS)
	$(CC) $(CFLAGS) -T scripts/grub.ld -o bin/$@ $(LLD)

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
	
# for GRUB use cdrom
# qemu-system-i386 -cdrom iso/boot.iso
#
# for floppy
# qemu-system-i386 -audiodev pa,id=snd0 -machine pcspk-audiodev=snd0 -fda iso/boot.iso

# sudo chown <username> $(DRIVE)
release:
	qemu-system-i386 -audio driver=alsa,model=ac97,id=alsa -hdb $(DRIVE)
	# qemu-system-i386 -audio driver=alsa,model=ac97,id=alsa -cdrom iso/boot.iso

# bochs -f .bochsrc
debug:
	qemu-system-i386 -audio driver=alsa,model=ac97,id=alsa -hdb $(DRIVE) -s -S &
	gdb -x scripts/db_input.gdb
	# qemu-system-i386 -cdrom iso/boot.iso

.PHONY: GRUB clean release debug
