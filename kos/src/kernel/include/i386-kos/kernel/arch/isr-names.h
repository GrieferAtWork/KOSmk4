/* Copyright (c) 2019 Griefer@Work                                            *
 *                                                                            *
 * This software is provided 'as-is', without any express or implied          *
 * warranty. In no event will the authors be held liable for any damages      *
 * arising from the use of this software.                                     *
 *                                                                            *
 * Permission is granted to anyone to use this software for any purpose,      *
 * including commercial applications, and to alter it and redistribute it     *
 * freely, subject to the following restrictions:                             *
 *                                                                            *
 * 1. The origin of this software must not be misrepresented; you must not    *
 *    claim that you wrote the original software. If you use this software    *
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_ISR_NAMES_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_ISR_NAMES_H 1

/* X86 ISR symbol assembly function names
 * These names are prefixed by either `__x86_def(isr|dpl|ist)' or `__x86_dbg(isr|dpl|ist)'
 *  - __x86_defisr_divide_by_zero
 *  - __x86_defdpl_divide_by_zero = 0
 *  - __x86_defist_divide_by_zero = 0
 *  - __x86_dbgisr_divide_by_zero = __x86_defisr_divide_by_zero
 *  - __x86_dbgdpl_divide_by_zero = __x86_defdpl_divide_by_zero
 *  - __x86_dbgist_divide_by_zero = __x86_defist_divide_by_zero
 *
 * Certain ISR ranges allow for additional symbols:
 *  - 0x00 - 0x1f: x86_handle_divide_by_zero
 *    This is a C-function defined declared as either:
 *    >> struct icpustate *FCALL x86_handle_divide_by_zero(struct icpustate *state);
 *    >> struct icpustate *FCALL x86_handle_divide_by_zero(struct icpustate *state, uintptr_t ecode);
 *    Depending on `ISR_X86_CONFIG_PUSHESERRORS(ISR_VECTOR_ID)'
 *  - 0x20 - 0x2f: x86_handle_ms_fastfail  (Same as `0x00 - 0x1f')
 *  - 0x81 - 0xed + 0xf1 - 0xff: kernel_isr_generic_00h
 *    This is a C-function defined declared as either:
 *    >> void FCALL kernel_isr_generic_00h(void);
 *
 */
#define ISR_X86_00 divide_by_zero         /* #DE  Divide-by-zero */
#define ISR_X86_01 debugtrap              /* #DB  Debug */
#define ISR_X86_02 non_maskable_interrupt /* #NMI Non-maskable Interrupt */
#define ISR_X86_03 breakpoint             /* #BP  Breakpoint */
#define ISR_X86_04 overflow               /* #OF  Overflow */
#define ISR_X86_05 bound_range            /* #BR  Bound Range Exceeded */
#define ISR_X86_06 illegal_instruction    /* #UD  Invalid Opcode */
#define ISR_X86_07 device_not_available   /* #NM  Device Not Available */
#define ISR_X86_08 double_fault           /* #DF  Double Fault */
#define ISR_X86_09 coprocessor_fault      /* #CSO Coprocessor Segment Overrun (unused on 486+) */
#define ISR_X86_0a invalid_tss            /* #TS  Invalid TSS */
#define ISR_X86_0b segment_not_present    /* #NP  Segment Not Present */
#define ISR_X86_0c stackfault             /* #SS  Stack-Segment Fault */
#define ISR_X86_0d gpf                    /* #GP  General Protection Fault */
#define ISR_X86_0e pagefault              /* #PF  Page Fault */
#define ISR_X86_0f 0fh                    /* Reserved (exception)... */
#define ISR_X86_10 fpu_x87                /* #MF  x87 Floating-Point Exception */
#define ISR_X86_11 bad_alignment          /* #AC  Alignment Check */
#define ISR_X86_12 machine_check          /* #MC  Machine Check */
#define ISR_X86_13 fpu_simd               /* #XM  SIMD Floating-Point Exception */
#define ISR_X86_14 virtualization_error   /* #VE  Virtualization Exception */
#define ISR_X86_15 15h
#define ISR_X86_16 16h
#define ISR_X86_17 17h
#define ISR_X86_18 18h
#define ISR_X86_19 19h
#define ISR_X86_1a 1ah
#define ISR_X86_1b 1bh
#define ISR_X86_1c 1ch
#define ISR_X86_1d 1dh
#define ISR_X86_1e security_exception /* #SX  Security Exception. */
#define ISR_X86_1f 1fh
#define ISR_X86_20 20h
#define ISR_X86_21 21h
#define ISR_X86_22 22h
#define ISR_X86_23 23h
#define ISR_X86_24 24h
#define ISR_X86_25 25h
#define ISR_X86_26 26h
#define ISR_X86_27 27h
#define ISR_X86_28 28h
#define ISR_X86_29 ms_fastfail /* __fastfail() */
#define ISR_X86_2a 2ah
#define ISR_X86_2b 2bh
#define ISR_X86_2c 2ch
#define ISR_X86_2d 2dh
#define ISR_X86_2e 2eh
#define ISR_X86_2f 2fh
#define ISR_X86_30 30h
#define ISR_X86_31 31h
#define ISR_X86_32 32h
#define ISR_X86_33 33h
#define ISR_X86_34 34h
#define ISR_X86_35 35h
#define ISR_X86_36 36h
#define ISR_X86_37 37h
#define ISR_X86_38 38h
#define ISR_X86_39 39h
#define ISR_X86_3a 3ah
#define ISR_X86_3b 3bh
#define ISR_X86_3c 3ch
#define ISR_X86_3d 3dh
#define ISR_X86_3e 3eh
#define ISR_X86_3f 3fh
#define ISR_X86_40 40h
#define ISR_X86_41 41h
#define ISR_X86_42 42h
#define ISR_X86_43 43h
#define ISR_X86_44 44h
#define ISR_X86_45 45h
#define ISR_X86_46 46h
#define ISR_X86_47 47h
#define ISR_X86_48 48h
#define ISR_X86_49 49h
#define ISR_X86_4a 4ah
#define ISR_X86_4b 4bh
#define ISR_X86_4c 4ch
#define ISR_X86_4d 4dh
#define ISR_X86_4e 4eh
#define ISR_X86_4f 4fh
#define ISR_X86_50 50h
#define ISR_X86_51 51h
#define ISR_X86_52 52h
#define ISR_X86_53 53h
#define ISR_X86_54 54h
#define ISR_X86_55 55h
#define ISR_X86_56 56h
#define ISR_X86_57 57h
#define ISR_X86_58 58h
#define ISR_X86_59 59h
#define ISR_X86_5a 5ah
#define ISR_X86_5b 5bh
#define ISR_X86_5c 5ch
#define ISR_X86_5d 5dh
#define ISR_X86_5e 5eh
#define ISR_X86_5f 5fh
#define ISR_X86_60 60h
#define ISR_X86_61 61h
#define ISR_X86_62 62h
#define ISR_X86_63 63h
#define ISR_X86_64 64h
#define ISR_X86_65 65h
#define ISR_X86_66 66h
#define ISR_X86_67 67h
#define ISR_X86_68 68h
#define ISR_X86_69 69h
#define ISR_X86_6a 6ah
#define ISR_X86_6b 6bh
#define ISR_X86_6c 6ch
#define ISR_X86_6d 6dh
#define ISR_X86_6e 6eh
#define ISR_X86_6f 6fh
#define ISR_X86_70 70h
#define ISR_X86_71 71h
#define ISR_X86_72 72h
#define ISR_X86_73 73h
#define ISR_X86_74 74h
#define ISR_X86_75 75h
#define ISR_X86_76 76h
#define ISR_X86_77 77h
#define ISR_X86_78 78h
#define ISR_X86_79 79h
#define ISR_X86_7a 7ah
#define ISR_X86_7b 7bh
#define ISR_X86_7c 7ch
#define ISR_X86_7d 7dh
#define ISR_X86_7e 7eh
#define ISR_X86_7f 7fh
#define ISR_X86_80 syscall
#define ISR_X86_81 generic_00h
#define ISR_X86_82 generic_01h
#define ISR_X86_83 generic_02h
#define ISR_X86_84 generic_03h
#define ISR_X86_85 generic_04h
#define ISR_X86_86 generic_05h
#define ISR_X86_87 generic_06h
#define ISR_X86_88 generic_07h
#define ISR_X86_89 generic_08h
#define ISR_X86_8a generic_09h
#define ISR_X86_8b generic_0ah
#define ISR_X86_8c generic_0bh
#define ISR_X86_8d generic_0ch
#define ISR_X86_8e generic_0dh
#define ISR_X86_8f generic_0eh
#define ISR_X86_90 generic_0fh
#define ISR_X86_91 generic_10h
#define ISR_X86_92 generic_11h
#define ISR_X86_93 generic_12h
#define ISR_X86_94 generic_13h
#define ISR_X86_95 generic_14h
#define ISR_X86_96 generic_15h
#define ISR_X86_97 generic_16h
#define ISR_X86_98 generic_17h
#define ISR_X86_99 generic_18h
#define ISR_X86_9a generic_19h
#define ISR_X86_9b generic_1ah
#define ISR_X86_9c generic_1bh
#define ISR_X86_9d generic_1ch
#define ISR_X86_9e generic_1dh
#define ISR_X86_9f generic_1eh
#define ISR_X86_a0 generic_1fh
#define ISR_X86_a1 generic_20h
#define ISR_X86_a2 generic_21h
#define ISR_X86_a3 generic_22h
#define ISR_X86_a4 generic_23h
#define ISR_X86_a5 generic_24h
#define ISR_X86_a6 generic_25h
#define ISR_X86_a7 generic_26h
#define ISR_X86_a8 generic_27h
#define ISR_X86_a9 generic_28h
#define ISR_X86_aa generic_29h
#define ISR_X86_ab generic_2ah
#define ISR_X86_ac generic_2bh
#define ISR_X86_ad generic_2ch
#define ISR_X86_ae generic_2dh
#define ISR_X86_af generic_2eh
#define ISR_X86_b0 generic_2fh
#define ISR_X86_b1 generic_30h
#define ISR_X86_b2 generic_31h
#define ISR_X86_b3 generic_32h
#define ISR_X86_b4 generic_33h
#define ISR_X86_b5 generic_34h
#define ISR_X86_b6 generic_35h
#define ISR_X86_b7 generic_36h
#define ISR_X86_b8 generic_37h
#define ISR_X86_b9 generic_38h
#define ISR_X86_ba generic_39h
#define ISR_X86_bb generic_3ah
#define ISR_X86_bc generic_3bh
#define ISR_X86_bd generic_3ch
#define ISR_X86_be generic_3dh
#define ISR_X86_bf generic_3eh
#define ISR_X86_c0 generic_3fh
#define ISR_X86_c1 generic_40h
#define ISR_X86_c2 generic_41h
#define ISR_X86_c3 generic_42h
#define ISR_X86_c4 generic_43h
#define ISR_X86_c5 generic_44h
#define ISR_X86_c6 generic_45h
#define ISR_X86_c7 generic_46h
#define ISR_X86_c8 generic_47h
#define ISR_X86_c9 generic_48h
#define ISR_X86_ca generic_49h
#define ISR_X86_cb generic_4ah
#define ISR_X86_cc generic_4bh
#define ISR_X86_cd generic_4ch
#define ISR_X86_ce generic_4dh
#define ISR_X86_cf generic_4eh
#define ISR_X86_d0 generic_4fh
#define ISR_X86_d1 generic_50h
#define ISR_X86_d2 generic_51h
#define ISR_X86_d3 generic_52h
#define ISR_X86_d4 generic_53h
#define ISR_X86_d5 generic_54h
#define ISR_X86_d6 generic_55h
#define ISR_X86_d7 generic_56h
#define ISR_X86_d8 generic_57h
#define ISR_X86_d9 generic_58h
#define ISR_X86_da generic_59h
#define ISR_X86_db generic_5ah
#define ISR_X86_dc generic_5bh
#define ISR_X86_dd generic_5ch
#define ISR_X86_de generic_5dh
#define ISR_X86_df generic_5eh
#define ISR_X86_e0 generic_5fh
#define ISR_X86_e1 generic_60h
#define ISR_X86_e2 generic_61h
#define ISR_X86_e3 generic_62h
#define ISR_X86_e4 generic_63h
#define ISR_X86_e5 generic_64h
#define ISR_X86_e6 generic_65h
#define ISR_X86_e7 generic_66h
#define ISR_X86_e8 generic_67h
#define ISR_X86_e9 generic_68h
#define ISR_X86_ea generic_69h
#define ISR_X86_eb generic_6ah
#define ISR_X86_ec generic_6bh
#define ISR_X86_ed generic_6ch
#define ISR_X86_ee apic_ipi
#define ISR_X86_ef apic_spurious
#define ISR_X86_f0 preemption /* aka `__x86_isr_pic1_0' */
#define ISR_X86_f1 specific_00h
#define ISR_X86_f2 specific_01h
#define ISR_X86_f3 specific_02h
#define ISR_X86_f4 specific_03h
#define ISR_X86_f5 specific_04h
#define ISR_X86_f6 specific_05h
#define ISR_X86_f7 specific_06h
#define ISR_X86_f8 specific_07h
#define ISR_X86_f9 specific_08h
#define ISR_X86_fa specific_09h
#define ISR_X86_fb specific_0ah
#define ISR_X86_fc specific_0bh
#define ISR_X86_fd specific_0ch
#define ISR_X86_fe specific_0dh
#define ISR_X86_ff specific_0eh

#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_ISR_NAMES_H */
