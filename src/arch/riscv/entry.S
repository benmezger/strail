#ifdef RISCV_ARCH
#include <arch/riscv/encoding.h>
#endif

.macro SAVE_CONTEXT
        addi sp, sp, -32 * REGBYTES
        STORE ra, 1 * REGBYTES(sp)
        STORE sp, 2 * REGBYTES(sp)
        STORE gp, 3 * REGBYTES(sp)
        STORE tp, 4 * REGBYTES(sp)
        STORE t0, 5 * REGBYTES(sp)
        STORE t1, 6 * REGBYTES(sp)
        STORE t2, 7 * REGBYTES(sp)
        STORE fp, 8 * REGBYTES(sp)
        STORE s1, 9 * REGBYTES(sp)
        STORE a0, 10 * REGBYTES(sp)
        STORE a1, 11 * REGBYTES(sp)
        STORE a2, 12 * REGBYTES(sp)
        STORE a3, 13 * REGBYTES(sp)
        STORE a4, 14 * REGBYTES(sp)
        STORE a5, 15 * REGBYTES(sp)
        STORE a6, 16 * REGBYTES(sp)
        STORE a7, 17 * REGBYTES(sp)
        STORE s2, 18 * REGBYTES(sp)
        STORE s3, 19 * REGBYTES(sp)
        STORE s4, 20 * REGBYTES(sp)
        STORE s5, 21 * REGBYTES(sp)
        STORE s6, 22 * REGBYTES(sp)
        STORE s7, 23 * REGBYTES(sp)
        STORE s8, 24 * REGBYTES(sp)
        STORE s9, 25 * REGBYTES(sp)
        STORE s10, 26 * REGBYTES(sp)
        STORE s11, 27 * REGBYTES(sp)
        STORE t3, 28 * REGBYTES(sp)
        STORE t4, 29 * REGBYTES(sp)
        STORE t5, 30 * REGBYTES(sp)
        STORE t6, 31 * REGBYTES(sp)
.endm

.macro RESTORE_CONTEXT
        LOAD ra, 1 * REGBYTES(sp)
        LOAD sp, 2 * REGBYTES(sp)
        LOAD gp, 3 * REGBYTES(sp)
        LOAD tp, 4 * REGBYTES(sp)
        LOAD t0, 5 * REGBYTES(sp)
        LOAD t1, 6 * REGBYTES(sp)
        LOAD t2, 7 * REGBYTES(sp)
        LOAD fp, 8 * REGBYTES(sp)
        LOAD s1, 9 * REGBYTES(sp)
        LOAD a0, 10 * REGBYTES(sp)
        LOAD a1, 11 * REGBYTES(sp)
        LOAD a2, 12 * REGBYTES(sp)
        LOAD a3, 13 * REGBYTES(sp)
        LOAD a4, 14 * REGBYTES(sp)
        LOAD a5, 15 * REGBYTES(sp)
        LOAD a6, 16 * REGBYTES(sp)
        LOAD a7, 17 * REGBYTES(sp)
        LOAD s2, 18 * REGBYTES(sp)
        LOAD s3, 19 * REGBYTES(sp)
        LOAD s4, 20 * REGBYTES(sp)
        LOAD s5, 21 * REGBYTES(sp)
        LOAD s6, 22 * REGBYTES(sp)
        LOAD s7, 23 * REGBYTES(sp)
        LOAD s8, 24 * REGBYTES(sp)
        LOAD s9, 25 * REGBYTES(sp)
        LOAD s10, 26 * REGBYTES(sp)
        LOAD s11, 27 * REGBYTES(sp)
        LOAD t3, 28 * REGBYTES(sp)
        LOAD t4, 29 * REGBYTES(sp)
        LOAD t5, 30 * REGBYTES(sp)
        LOAD t6, 31 * REGBYTES(sp)

        addi sp, sp, 32 * REGBYTES
.endm

.section .text
.align 4

_trap_entry:
        SAVE_CONTEXT
        # csrr a0, mcause # write mcause to first function argument
        # csrr a1, mtval # write exception specific information to second argument
        # csrr a2, mpec # write machine exeception program counter to third argument
        mv a0, sp # move sp to the first argument
        jal trap_handler

        # Set exception pc back to sp
        csrw mepc, a0

        # Remain in M-mode after mret
        li t0, 8
        csrrs zero, mstatus, t0
        RESTORE_CONTEXT
        mret

.globl _setup_mtrap
_setup_mtrap:
        la t0, _trap_entry # load address of mtrap_handler
        csrw mtvec, t0 # write handler and address mode

        # Set DIRECT_MODE access to
        slli t0, t0, 1 # shift address left by one ; LSB will be 0 (DIRECT_MODE)

        # enable machine-mode interrupt (mstatus.MIE = 1)
        li t0, 8
        csrrs zero, mstatus, t0
        ret
.end
