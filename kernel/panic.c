#include <kernel/panic.h>
#include <kernel/printk.h>

void
panic()
{
	printk("[panic] | Panic");
	abort();
}

void
abort()
{
	for (;;) {
		asm("wfi");
	}
}
