#include <kernel/printk.h>
#include <drivers/uart.h>

void
_printk(const char c)
{
	uart_putc(c);
}

void
iter_left_to_right(unsigned int n, void (*callback)(const char))
{
	unsigned int digit = 1000000000L;
	unsigned int base_n = 10 * n;

	if (n == 0) {
		(*callback)(n);
	} else {
		while (digit > base_n) {
			digit /= 10;
		}
		while (digit /= 10) {
			(*callback)(((n / digit) % 10) + '0');
		}
	}
}

void
printk(const char *fmt, ...)
{
	va_list argp;
	va_start(argp, fmt);

	int value;
	char c;

	while (*fmt != '\0') {
		if (*fmt == '%') {
			fmt++;
			if (*fmt == 'd') {
				value = va_arg(argp, int);
				iter_left_to_right(value, _printk);
				fmt++;
				continue;
			}
			if (*fmt == 'c') {
				_printk(va_arg(argp, int));
				fmt++;
				continue;
			} else {
				_printk(*fmt);
				fmt++;
				continue;
			}
		} else {
			_printk(*fmt);
			fmt++;
		}
	}
	va_end(argp);
}
