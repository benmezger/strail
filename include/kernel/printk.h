#ifndef _PRINTK_H
#define _PRINTK_H

#include <stdint.h>
#include <stdarg.h>

void _printk(const char);
void printk(const char *fmt, ...);
void iter_left_to_right(unsigned int, void (*f)(const char));
void _printk_hex(uintptr_t);

#endif
