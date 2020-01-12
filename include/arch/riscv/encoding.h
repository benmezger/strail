#ifndef _ENCODING_H
#define _ENCODING_H

#if __riscv_xlen == 64
#define REGBYTES 8
#define STORE sd
#define LOAD ld

#else
#define REGBYTES 4
#define STORE sw
#define LOAD lw

#endif

#endif
