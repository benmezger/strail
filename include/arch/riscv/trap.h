#ifndef _TRAP_H
#define _TRAP_H

#include "encoding.h"
#include "cpu.h"

#define TRAP_CAUSE_MISALIGNED_FETCH 0x0
#define TRAP_CAUSE_FETCH_ACCESS 0x1
#define TRAP_CAUSE_ILLEGAL_INSTRUCTION 0x2
#define TRAP_CAUSE_BREAKPOINT 0x3
#define TRAP_CAUSE_MISALIGNED_LOAD 0x4
#define TRAP_CAUSE_LOAD_ACCESS 0x5
#define TRAP_CAUSE_MISALIGNED_STORE 0x6
#define TRAP_CAUSE_STORE_ACCESS 0x7
#define TRAP_CAUSE_USER_ECALL 0x8
#define TRAP_CAUSE_SUPERVISOR_ECALL 0x9
#define TRAP_CAUSE_HYPERVISOR_ECALL 0xa
#define TRAP_CAUSE_MACHINE_ECALL 0xb
#define TRAP_CAUSE_FETCH_PAGE_FAULT 0xc
#define TRAP_CAUSE_LOAD_PAGE_FAULT 0xd
#define TRAP_CAUSE_STORE_PAGE_FAULT 0xf

typedef struct {
	long regs[32];
	long status;
	long epc;
	long badvaddr;
	/*
	 * (cause) mcause register is set if trap was caused by an interrupt
	 */
	long cause;
	long insn;
} trapframe_t __attribute__((aligned(REGBYTES)));

typedef void (*trap_callback)(trapframe_t *);

void handle_machine_ecall(trapframe_t *);

static trap_callback trap_handlers[] = {
	[TRAP_CAUSE_MACHINE_ECALL] = handle_machine_ecall,
};

void delegate_mode_trap(int, unsigned int);

/* Handle kernel traps */
int _trap_handler(trapframe_t *);

#endif
