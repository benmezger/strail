int
main()
{
	int x = 1;
	asm volatile("ecall");
	return x;
}
