#include <arch/riscv/encoding.h>
#include <arch/riscv/cpu.h>
#include <arch/riscv/trap.h>
#include <drivers/uart.h>
#include <kernel/printk.h>

void
dump_stack(trapframe_t *frame)
{
	printk("[dump_stack] | Printing stackframe of %p\n", frame);

	int i;
	for (i = 1; i < 30; i++) {
		printk("Reg %d = %x\n", i, frame->regs[i]);
	}

	printk("\n");
	printk("Reg mstatus = %x\n", frame->status);
	printk("Reg epc = %x\n", frame->epc);
	printk("Reg badvaddr = %x\n", frame->badvaddr);
	printk("Reg cause = %x\n", frame->cause);
	printk("Reg insn = %x\n", frame->insn);
}

void
init_machine_mode()
{
	/* Enter machine mode */
	printk("[init_machine_mode] | Entering machine-mode\n");
	set_csr(mstatus, 0);

	/* Enable machine software interrupts */
	printk("[init_machine_mode] | Enabling Machine SIP \n");
	set_csr(mie, MIP_MSIP);

	/* delegate machine-mode trap to machine-mode trap */
	printk(
	    "[init_machine_mode] | Delegating traps to SSIP STIP and SEIP\n");
	unsigned int interrupts = MIP_SSIP | MIP_STIP | MIP_SEIP;
	delegate_mode_trap(MACHINE_MODE, interrupts);
}

void
init_riscv()
{
	/* initialize uart */
	uart_init();
	/* initialize machine mode */
	init_machine_mode();

	printk("[init_riscv] | Initialized RISC-V's machine-mode\n");

	// asm("mret");
}
