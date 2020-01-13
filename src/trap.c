#ifdef RISCV_ARCH
#include <arch/riscv/trap.h>
#endif

void
handle_machine_ecall(trapframe_t *trapframe)
{
	;
	;
}

int
trap_handler(trapframe_t *trapframe)
{

	trap_handlers[trapframe->cause](trapframe);
}
