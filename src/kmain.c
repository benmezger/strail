#include <kernel/init.h>

int
main()
{
	init_arch();
	asm("ecall");
}
