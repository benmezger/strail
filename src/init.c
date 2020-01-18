#ifdef RISCV_ARCH
#include <arch/riscv/cpu.h>
#endif

void
init_arch(void)
{
#ifdef RISCV_ARCH
	init_riscv();
#endif
}
