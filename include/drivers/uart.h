#ifndef _UART_H
#define _UART_H

#include <kernel/types.h>

/* 16550 driver for Qemu's riscv-virt serial port */

#define UART_BASE_ADDRESS 0x10000000

/* register offsets
 * See: https://www.scs.stanford.edu/10wi-cs140/pintos/specs/pc16550d.pdf
 */
#define UART_LCR_REG 0x03
#define UART_FIFO_REG 0x02

/*
 * Initialize uart
 * Arg0: uart base address
 */
void uart_init(uint8_t *);

/*
 x* Write character to the uart device
 * Arg0: a character
 */
void uart_putc(uint8_t);

/*
 x* Write a string to the uart device
 * Arg0: a character
 */
void uart_puts(uint8_t *);

#endif
