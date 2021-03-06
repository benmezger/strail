#include <arch/riscv/cpu.h>
#include <arch/riscv/trap.h>
#include <drivers/uart.h>
#include <kernel/printk.h>

void
handle_machine_ecall(trapframe_t *frame)
{
	printk("[handle_machine_ecall] | frame %p", frame);
}

void
delegate_mode_trap(int mode, unsigned int interrupt)
{
	switch (mode) {
	case MACHINE_MODE:
		set_csr(mstatus, interrupt);
		break;
	case SUPERVISOR_MODE:
		set_csr(sstatus, interrupt);
		break;
	case USER_MODE:
		set_csr(ustatus, interrupt);
		break;
	}
}

int
trap_handler(trapframe_t *frame)
{
	printk("[trap_handler] | Handling trap %d\n", frame->cause);
	dump_stack(frame);
	uart_putc((uint8_t)frame->cause);
	trap_handlers[frame->cause](frame);
	return 1;
}
