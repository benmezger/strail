.macro SAVE_CONTEXT
        sw ra, 24(sp)    # save return address to the stack
        sw t0, 20(sp)    # save temporary
        sw t1, 16(sp)    # save temporary
        sw t2, 12(sp)    # save temporary
        sw t3, 8(sp)     # save temporary
        sw a0, 4(sp)     # save first argument to function
.endm

.macro RESTORE_CONTEXT
        ld ra, 24(sp)    # save return address to the stack
        ld t0, 20(sp)    # save temporary
        ld t1, 16(sp)    # save temporary
        ld t2, 12(sp)    # save temporary
        ld t3, 8(sp)     # save temporary
        ld a0, 4(sp)     # save first argument to function
.endm

.section .text
.align 4

_trap_entry:
        addi sp, sp, -28 # Allocate stack frame
        SAVE_CONTEXT
        csrr a0, mcause # write mcause to first function argument
        csrr a1, mtval # write mtval (exception specific information) to second function argument
        jal trap_handler

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
