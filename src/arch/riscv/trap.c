#include <arch/riscv/cpu.h>
#include <arch/riscv/trap.h>

int
trap_handler(trapframe_t *frame)
{

	if (frame->cause > 15) {
		return;
	}

	trap_handlers[frame->cause](frame);
}
