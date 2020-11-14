#include <stdint.h>
#include <kernel/printk.h>
#include <drivers/uart.h>
#include <string.h>

void
_printk(const char c)
{
	uart_putc(c);
}

void
_printks(const char *c)
{
	while (*c != '\0') {
		uart_putc(*c);
		c++;
	}
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

char hex_digit(int);
char
hex_digit(int v)
{
	if (v >= 0 && v < 10) {
		return '0' + v;
	}
	return 'a' + v - 10;
}

void
_printk_hex(uintptr_t ptr)
{

	_printk('0');
	_printk('x');

	int i;
	for (i = (sizeof(ptr) << 3) - 4; i >= 0; i -= 4) {
		_printk(hex_digit((ptr >> i) & 0xF));
	}
}

void
printk(const char *fmt, ...)
{
	va_list argp;
	va_start(argp, fmt);

	int value, i;
	uintptr_t ptr;
	char c;

	while (*fmt != '\0') {
		if (*fmt == '%') {
			fmt++;
			switch (*fmt) {
			case 'd':
				value = va_arg(argp, int);
				iter_left_to_right(value, _printk);
				fmt++;
				continue;
			case 'c':
				_printk(va_arg(argp, int));
				fmt++;
				continue;
			case 's':
				_printks(va_arg(argp, const char *));
				fmt++;
				continue;
			case 'x':
				ptr = va_arg(argp, uintptr_t);
				_printk_hex(ptr);
				fmt++;
				continue;
			case 'p':
				ptr = va_arg(argp, uintptr_t);
				_printk_hex(ptr);
				fmt++;
				continue;
			default:
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

void
printkln(const char *fmt, ...)
{
	va_list argp;
	printk(fmt, argp);
	_printk('\n');
}
