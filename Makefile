SHELL = /bin/bash
BINARY = kernel
ARCH = riscv

BINDIR = ./bin
SRCDIR = src
INC=-I./include/
SRCS = $(shell find $(SRCDIR) -name *.c -or -name *.S -maxdepth 1)
SRCS += $(shell find $(SRCDIR)/drivers -name *.c -or -name *.S)

ARCH_SRCS := $(shell find $(SRCDIR)/arch/$(ARCH) -name *.c -or -name *.S)
SRCS += $(ARCH_SRCS)

ifeq ($(ARCH),riscv)
CFLAGS += \
	-march=rv64imafdc \
	-mcmodel=medany \
	-mabi=lp64d
LINKER_SCRIPT = riscv64-virt.ld
CC = riscv64-unknown-elf-gcc
GDB = riscv64-unknown-elf-gdb
endif

GDB_PORT = 11111

OBJDIR = ./obj
OBJS := $(addsuffix .o,$(basename $(SRCDIR)))
DEPS := $(OBJS:.o=.d)

# -ffreestanding
CFLAGS += \
	-D$(shell echo $(ARCH)_ARCH | tr a-z A-Z) \
	-O0 \
	-lgcc \
	$(INC)


# -nodefaultlibs
LDFLAGS= \
	-Wl,--gc-sections -nostartfiles -nodefaultlibs \
	-Wl,-T,$(LINKER_SCRIPT)

# make DEBUG=1
DEBUG ?= 0
ifeq ($(DEBUG), 1)
    CFLAGS += -g -DDEBUG
else
    CFLAGS += -DNDEBUG
endif

.PHONY:	all
all: $(BINARY)

$(BINARY): clean
	$(CC) $(CFLAGS) $(LDFLAGS) $(SRCS) -o $(BINARY)

.PHONY: clean
clean:
	rm -r -f $(BINARY)

.PHONY: qemu
qemu:
	echo "CTRL-a-x to quit Qemu when running -nographic"
	qemu-system-riscv64 \
	-machine virt \
	-m 128M \
	-kernel $(BINARY) \
	-gdb tcp::$(GDB_PORT) \
	-S \
	-nographic

.PHONY: gdb
gdb:
	$(GDB) \
	-q \
	-ex 'file $(BINARY)' \
	-ex 'target remote localhost:$(GDB_PORT)' \
	-ex "b main"
