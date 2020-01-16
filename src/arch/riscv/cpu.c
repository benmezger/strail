#include <arch/riscv/encoding.h>
#include <arch/riscv/cpu.h>

void
init_machine_mode()
{
	/* Enter machine mode */
	set_csr(mstatus, 0);

	/* Enable software interrupts */
	set_csr(mie, MIP_MSIP);
}

void
init_supervisor_mode()
{
	/* Enter machine mode */
	set_csr(mstatus, 0);

	/* Enable software interrupts */
	set_csr(mie, MIP_MSIP);
}

void
init_riscv()
{
	/* initialize machine mode */
	init_machine_mode();
}
