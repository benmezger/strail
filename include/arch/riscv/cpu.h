#ifndef _CPU_H
#define _CPU_H

/* From:
 * https://github.com/sifive/freedom-metal/blob/master/src/privilege.c
 * 2c96ceb44c9a6a489846aaaebf7bdc2dc710b80c
 */

#define clear_csr(reg, bit)                                                 \
	({                                                                  \
		unsigned long __tmp;                                        \
		if (__builtin_constant_p(bit) && (unsigned long)(bit) < 32) \
			asm volatile("csrrc %0, " #reg ", %1"               \
				     : "=r"(__tmp)                          \
				     : "i"(bit));                           \
		else                                                        \
			asm volatile("csrrc %0, " #reg ", %1"               \
				     : "=r"(__tmp)                          \
				     : "r"(bit));                           \
		__tmp;                                                      \
	})

#define set_csr(reg, bit)                                                   \
	({                                                                  \
		unsigned long __tmp;                                        \
		if (__builtin_constant_p(bit) && (unsigned long)(bit) < 32) \
			asm volatile("csrrs %0, " #reg ", %1"               \
				     : "=r"(__tmp)                          \
				     : "i"(bit));                           \
		else                                                        \
			asm volatile("csrrs %0, " #reg ", %1"               \
				     : "=r"(__tmp)                          \
				     : "r"(bit));                           \
		__tmp;                                                      \
	})

#endif
