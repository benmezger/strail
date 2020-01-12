#ifdef RISCV_ARCH
#include <arch/riscv/trap.h>
#endif

int
trap_handler(int mcause, int mtval)
{
	return mcause + mtval;
}
