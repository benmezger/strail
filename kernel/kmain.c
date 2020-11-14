#include <kernel/init.h>
#include <kernel/panic.h>
#include <kernel/printk.h>

int
main()
{
	init_arch();
	printkln("[main] | Exiting main");
	panic();
}
