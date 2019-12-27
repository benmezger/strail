#ifndef _CPU_H
#define _CPU_H

/* From:
 * https://github.com/sifive/freedom-metal/blob/master/src/privilege.c
 * 2c96ceb44c9a6a489846aaaebf7bdc2dc710b80c
 */
#define MSTATUS_MIE_OFFSET 3
#define MSTATUS_MPIE_OFFSET 7

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

#define disable_irq()                                   \
	({                                              \
		clear_csr(mie, MSTATUS_MEIP_OFFSET);    \
		clear_csr(mstatus, MSTATUS_MIE_OFFSET); \
	})

#endif
