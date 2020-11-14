#include <kernel/init.h>
#include <kernel/panic.h>
#include <kernel/printk.h>

int
main()
{
	init_arch();
	printk("[main] | Exiting main");
	panic();
}
