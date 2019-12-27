SHELL = /bin/bash
BINARY = kernel

BINDIR = ./bin
SRCDIR = ./src
INC=-I./include/
SRCS := $(shell find $(SRCDIR) -name *.c -or -name *.s)

RISCV_COMPILER = riscv64-unknown-elf-gcc
CC = $(RISCV_COMPILER)

GDB = riscv64-unknown-elf-gdb
GDB_PORT = 11111

OBJDIR = ./obj
OBJS := $(addsuffix .o,$(basename $(SRCDIR)))
DEPS := $(OBJS:.o=.d)


# -ffreestanding
CFLAGS = \
	-O0 \
	-mcmodel=medany \
	-lgcc \
	-march=rv64imafdc \
	-mabi=lp64d \
	$(INC)

LINKER_SCRIPT = riscv64-virt.ld

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
	qemu-system-riscv64 \
	-machine virt \
	-m 128M \
	-kernel $(BINARY) \
	-gdb tcp::$(GDB_PORT) \
	-S \

.PHONY: gdb
gdb:
	$(GDB) \
	-q \
	-ex 'file $(BINARY)' \
	-ex 'target remote localhost:$(GDB_PORT)' \
	-ex "b main"
