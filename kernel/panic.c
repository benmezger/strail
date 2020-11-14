#include <kernel/panic.h>
#include <kernel/printk.h>

void
panic()
{
	printkln("[panic] | Panic");
	abort();
}

void
abort()
{
	for (;;) {
		asm("wfi");
	}
}
