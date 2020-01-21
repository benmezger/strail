#include <arch/riscv/encoding.h>
#include <arch/riscv/cpu.h>
#include <arch/riscv/trap.h>
#include <drivers/uart.h>

void
init_machine_mode()
{
	/* Enter machine mode */
	set_csr(mstatus, 0);

	/* Enable machine software interrupts */
	set_csr(mie, MIP_MSIP);

	/* delegate machine-mode trap to machine-mode trap */
	unsigned int interrupts = MIP_SSIP | MIP_STIP | MIP_SEIP;
	delegate_mode_trap(MACHINE_MODE, interrupts);
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

	uart_init((uint8_t *)UART_BASE_ADDRESS);
}
