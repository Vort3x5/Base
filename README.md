# Base

**Minimalistyczny bootloader i kernel od zera**

## Po co?

- **Nauka OS dev** - bootowanie od BIOS do protected mode
- **Bare metal** - zero abstrakcji, pełna kontrola
- **Prawdziwy sprzęt** - działa na fizycznych maszynach

## Funkcje

- MBR bootloader (512B) → Second stage → 32-bit kernel
- Protected mode z GDT
- Memory mapping (BIOS E820)
- A20 Gate (3 metody fallback)
- IDT/ISR/IRQ 
- dynamic malloc
- VGA 80x25 text mode

## Quick Start

```bash
# Zainstaluj: fasm, i686-elf-gcc, qemu
make
qemu-system-i386 -drive file=bin/boot.img,format=raw
```

## Struktura

```
boot/     → Bootloader (ASM)
init/     → Kernel entry (Multiboot)
src/      → Kernel (C)
drivers/  → VGA, memory, interrupts
```

## Boot Flow

```
BIOS → boot.bin (0x7C00) → load.bin (0x1000) → Base.bin (0x100000)
       ├─ Load stages        ├─ E820 mmap         └─ C kernel
       └─ MBR magic          ├─ A20 enable
                             └─ GDT + PM switch
```

## Tech Stack

- FASM 
- i686-elf-toolchain
- Lua (auto kernel size calc)

---
