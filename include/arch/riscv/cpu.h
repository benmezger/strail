#ifndef _CPU_H
#define _CPU_H

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

#define cpu_hartid()                                                   \
	({                                                             \
		int _mhartid;                                          \
		__asm__ volatile("csrr %0, mhartid" : "=r"(_mhartid)); \
		_mhartid;                                              \
	})

#define read_csr(reg)                                         \
	({                                                    \
		unsigned long __tmp;                          \
		asm volatile("csrr %0, " #reg : "=r"(__tmp)); \
		__tmp;                                        \
	})

#endif
