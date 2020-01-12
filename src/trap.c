#ifdef RISCV_ARCH
#include <arch/riscv/trap.h>
#endif

int
trap_handler(trapframe_t *trapframe)
{
	return 0;
}
