#include <arch/riscv/cpu.h>
#include <arch/riscv/trap.h>

void
handle_machine_ecall(trapframe_t *frame)
{
	;
	;
}

void
delegate_mode_trap(enum riscv_opmode mode, unsigned int interrupt)
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
	trap_handlers[frame->cause](frame);
}
