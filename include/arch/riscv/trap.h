#ifndef _TRAP_H
#define _TRAP_H

typedef struct {
	long regs[32];
	long status;
	long epc;
	long badvaddr;
	long cause;
	long insn;

} trapframe_t;

/* Handle kernel traps */
int trap_handler(trapframe_t *);

#endif
