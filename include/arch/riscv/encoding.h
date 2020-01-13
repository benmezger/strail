#ifndef _ENCODING_H
#define _ENCODING_H

/*
 * https://content.riscv.org/wp-content/uploads/2017/05/riscv-privileged-v1.10.pdf
 * Section 3.1.6
 */
#define MSTATUS_UIE 1 << 0
#define MSTATUS_SIE 1 << 1
#define MSTATUS_MIE 1 << 3
#define MSTATUS_UPIE 1 << 4
#define MSTATUS_SPIE 1 << 5
#define MSTATUS_MPIE 1 << 7
#define MSTATUS_SPP 1 << 8
#define MSTATUS_MPP (1 << 12) + (1 << 11)
#define MSTATUS_MPRV 1 << 17
#define MSTATUS_SUM 1 << 18
#define MSTATUS_MXR 1 << 19
#define MSTATUS_TVM 1 << 20
#define MSTATUS_TW 1 << 21
#define MSTATUS_TSR 1 << 22
#define MSTATUS32_SD 1 << 31
#define MSTATUS64_SD 1 << (__riscv_xlen - 1)

/*
 * https://content.riscv.org/wp-content/uploads/2017/05/riscv-privileged-v1.10.pdf
 * Section 3.1.14
 */
#define MIP_MEIP 1 << 11
#define MIP_SEIP 1 << 9
#define MIP_UEIP 1 << 8
#define MIP_MTIP 1 << 7
#define MIP_STIP 1 << 5
#define MIP_UTIP 1 << 4
#define MIP_MSIP 1 << 3
#define MIP_SSIP 1 << 1
#define MIP_USIP 1 << 0

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
