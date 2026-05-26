.global _start

/* * AArch64 Exception Vector Table must be 2KB (0x800) aligned.
 * We provide a dummy one to satisfy VBAR_EL3 requirements.
 */
.section .text.boot
.align 11

_start:
    /* -----------------------------------------------------------
     * 1. Mask All Interrupts (DAIF)
     * We don't want interrupts interrupting our initialization.
     * ----------------------------------------------------------- */
    msr     daifset, #0xf

    /* -----------------------------------------------------------
     * 2. Multicore Check
     * Ensure only Core 0 runs this initialization.
     * ----------------------------------------------------------- */
    mrs     x0, mpidr_el1
    and     x0, x0, #0xFF
    cbz     x0, core0_init

secondary_hang:
    wfe
    b       secondary_hang

core0_init:
    /* -----------------------------------------------------------
     * 3. Initialize SCTLR_EL3 (System Control Register)
     * We Ensure MMU (M), Instruction Cache (I), and Data Cache (C) are OFF.
     * Running with caches ON without MMU setup is dangerous.
     * ----------------------------------------------------------- */
    mrs     x0, sctlr_el3
    bic     x0, x0, #(1 << 0)   /* Clear M bit (Disable MMU) */
    bic     x0, x0, #(1 << 2)   /* Clear C bit (Disable D-Cache) */
    bic     x0, x0, #(1 << 12)  /* Clear I bit (Disable I-Cache) */
    msr     sctlr_el3, x0
    isb

    /* -----------------------------------------------------------
     * 4. Enable Floating Point / NEON (CPTR_EL3)
     * If we don't do this, any access to Q0-Q31 registers traps.
     * GCC often uses these registers even for non-math memory moves.
     * ----------------------------------------------------------- */
    mrs     x0, cptr_el3
    bic     x0, x0, #(1 << 10)  /* Clear TFP (Trap Floating Point) bit */
    msr     cptr_el3, x0
    isb

    /* -----------------------------------------------------------
     * 5. Set Vector Base Address (VBAR_EL3)
     * Point it to our start (even if we don't handle exceptions yet).
     * ----------------------------------------------------------- */
    ldr     x0, =_start
    msr     vbar_el3, x0

    /* -----------------------------------------------------------
     * 6. Setup Stack Pointer for EL3
     * ----------------------------------------------------------- */
    ldr     x0, =__stack_top
    mov     sp, x0

    /* -----------------------------------------------------------
     * 7. Zero BSS
     * ----------------------------------------------------------- */
    ldr     x0, =__bss_start
    ldr     x1, =__bss_end
    sub     x2, x1, x0
    cbz     x2, enter_main

zero_loop:
    str     xzr, [x0], #8
    sub     x2, x2, #8
    cbnz    x2, zero_loop

    /* -----------------------------------------------------------
     * 8. Jump to C
     * ----------------------------------------------------------- */
enter_main:
    bl      main

hang:
    b       hang
