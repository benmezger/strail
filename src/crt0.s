/* Move section to .init that is allocatable and executable. */
.section .init, "ax"
.align 2
.global _start

_start:
        .cfi_startproc
        .cfi_undefined ra

        # _setup_mtrap if interrupt is not enabled
        #csrr t0, mstatus
        #beqz t0, _setup_mtrap

        .option push
        .option norelax

        la gp, __global_pointer$
        .option pop

        la sp, __stack_top
        add s0, sp, zero


        jal _setup_mtrap
        jal zero, main
        .cfi_endproc
        .end
