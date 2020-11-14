CC = riscv64-unknown-elf-gcc
SHELL = /bin/bash
BINARY = bin
HOST = riscv
GDB_PORT = 11111
GDB=riscv64-unknown-elf-gdb

CFLAGS ?= -O2
CPPFLAGS ?=
LDFLAGS ?=
LIBS ?=

include lib/make.config
include kernel/make.config

DESTDIR ?=
CFLAGS := $(CFLAGS) $(KERNEL_CFLAGS)
CPPFLAGS := $(CPPFLAGS) -Iinclude
LDFLAGS := $(LDFLAGS) -Wl,--gc-sections -nostartfiles -nodefaultlibs
LIBS := $(LIBS) -nostdlib -lgcc

ARCHDIR = arch/$(HOST)
include $(ARCHDIR)/make.config

CFLAGS := $(CFLAGS) $(KERNEL_ARCH_CFLAGS)
LDFLAGS := $(LDFLAGS) $(KERNEL_ARCH_LDFLAGS)
LIBS := $(LIBS) $(KERNEL_ARCH_LIBS)

include drivers/make.config

# make DEBUG=1
DEBUG ?= 0
ifeq ($(DEBUG), 1)
    CFLAGS += -g -DDEBUG
else
    CFLAGS += -DNDEBUG
endif

OBJS = \
	$(KERNEL_LIBS) \
	$(KERNEL_OBJS) \
	$(KERNEL_ARCH_OBJS) \
	$(KERNEL_DRIVER_OBJS)

LINK_LIST = \
	$(LDFLAGS) \
	$(OBJS) \
	$(LIBS)


.PHONY: all clean quemu rebuild
.SUFFIXES: .o .c .S

all: rebuild

rebuild:
	$(MAKE) clean
	$(MAKE) $(BINARY)

$(BINARY): $(OBJS)
	$(CC) -o $@ $(CPPFLAGS) $(CFLAGS) $(LINK_LIST)

.c.o:
	$(CC) -MD -c $< -o $@ -std=gnu11 $(CFLAGS) $(CPPFLAGS)
.S.o:
	$(CC) -MD -c $< -o $@  $(CFLAGS) $(CPPFLAGS)

clean:
	rm -r -f $(BINARY)
	rm -f $(OBJS) *.o */*.o */*/*.o
	rm -f $(OBJS:.o=.d) *.d */*.d */*/*.d

qemu-gdb:
	echo "CTRL-a-x to quit Qemu when running -nographic"
	qemu-system-riscv64 \
	-machine virt \
	-m 128M \
	-kernel $(BINARY) \
	-gdb tcp::$(GDB_PORT) \
	-bios none \
	-S \
	-nographic

qemu:
	echo "CTRL-a-x to quit Qemu when running -nographic"
	qemu-system-riscv64 \
	-machine virt \
	-m 128M \
	-kernel $(BINARY) \
	-bios none \
	-nographic

.PHONY: gdb
gdb:
	$(GDB) \
	-q \
	-ex 'file $(BINARY)' \
	-ex 'target remote localhost:$(GDB_PORT)' \
	-ex "b main"
