#include <drivers/uart.h>
#include <kernel/types.h>

volatile uint8_t *uart_base = (uint8_t *)UART_BASE_ADDRESS;

/* TODO: This is not the place for this. Move this somewhere else
 */

void mmio_write(volatile uint8_t *, int, char);

void
mmio_write(volatile uint8_t *address, int offset, char value)
{
	*(address + offset) = value;
}

void
uart_init()
{

	/* Enable 8-bit word-lenght */
	mmio_write(uart_base, UART_LCR_REG, (1 << 0) | (1 << 1));

	/* Enable FIFO */
	// mmio_write(base_addr, UART_FIFO_REG, 1 << 0);
}

void
uart_putc(uint8_t c)
{

	mmio_write(uart_base, 0, c);
}

void
uart_puts(uint8_t *c)
{
	while (*c && *c != '\0') {
		uart_putc(*c);
		c++;
	}
}
