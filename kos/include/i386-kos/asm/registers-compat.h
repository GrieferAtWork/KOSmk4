/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    in a product, an acknowledgement (see the following) in the product     *
 *    documentation is required:                                              *
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _I386_KOS_ASM_REGISTERS_COMPAT_H
#define _I386_KOS_ASM_REGISTERS_COMPAT_H 1

#include <hybrid/host.h>
#include <asm/registers.h>

/* General-purpose registers. */
#ifdef __x86_64__
#define X86_REGISTER_GENERAL_PURPOSE_PAX  X86_REGISTER_GENERAL_PURPOSE_RAX /* %pax */
#define X86_REGISTER_GENERAL_PURPOSE_PCX  X86_REGISTER_GENERAL_PURPOSE_RCX /* %pcx */
#define X86_REGISTER_GENERAL_PURPOSE_PDX  X86_REGISTER_GENERAL_PURPOSE_RDX /* %pdx */
#define X86_REGISTER_GENERAL_PURPOSE_PBX  X86_REGISTER_GENERAL_PURPOSE_RBX /* %pbx */
#define X86_REGISTER_GENERAL_PURPOSE_PSP  X86_REGISTER_GENERAL_PURPOSE_RSP /* %psp */
#define X86_REGISTER_GENERAL_PURPOSE_PBP  X86_REGISTER_GENERAL_PURPOSE_RBP /* %pbp */
#define X86_REGISTER_GENERAL_PURPOSE_PSI  X86_REGISTER_GENERAL_PURPOSE_RSI /* %psi */
#define X86_REGISTER_GENERAL_PURPOSE_PDI  X86_REGISTER_GENERAL_PURPOSE_RDI /* %pdi */
#define X86_REGISTER_GENERAL_PURPOSE_P8   X86_REGISTER_GENERAL_PURPOSE_R8  /* %p8 */
#define X86_REGISTER_GENERAL_PURPOSE_P9   X86_REGISTER_GENERAL_PURPOSE_R9  /* %p9 */
#define X86_REGISTER_GENERAL_PURPOSE_P10  X86_REGISTER_GENERAL_PURPOSE_R10 /* %p10 */
#define X86_REGISTER_GENERAL_PURPOSE_P11  X86_REGISTER_GENERAL_PURPOSE_R11 /* %p11 */
#define X86_REGISTER_GENERAL_PURPOSE_P12  X86_REGISTER_GENERAL_PURPOSE_R12 /* %p12 */
#define X86_REGISTER_GENERAL_PURPOSE_P13  X86_REGISTER_GENERAL_PURPOSE_R13 /* %p13 */
#define X86_REGISTER_GENERAL_PURPOSE_P14  X86_REGISTER_GENERAL_PURPOSE_R14 /* %p14 */
#define X86_REGISTER_GENERAL_PURPOSE_P15  X86_REGISTER_GENERAL_PURPOSE_R15 /* %p15 */
#define X86_REGISTER_MISC_PFLAGS          X86_REGISTER_MISC_RFLAGS         /* %pflags */
#define X86_REGISTER_MISC_PIP             X86_REGISTER_MISC_RIP            /* %pip */
#define X86_REGISTER_MISC_FSBASE          X86_REGISTER_MISC_FSBASEQ        /* %fs.base */
#define X86_REGISTER_MISC_GSBASE          X86_REGISTER_MISC_GSBASEQ        /* %gs.base */
#define X86_REGISTER_MISC_KGSBASE         X86_REGISTER_MISC_GSBASEQ        /* %kernel_gs.base */
#define X86_REGISTER_MISC_GDT_BASE        X86_REGISTER_MISC_GDT_BASEQ      /* %gdt.base */
#define X86_REGISTER_MISC_IDT_BASE        X86_REGISTER_MISC_IDT_BASEQ      /* %idt.base */
#define X86_REGISTER_MISC_FIP             X86_REGISTER_MISC_FIPQ           /* %fip */
#define X86_REGISTER_MISC_FDP             X86_REGISTER_MISC_FDPQ           /* %fdp */
#define X86_REGISTER_SIZEMASK_PBYTE       X86_REGISTER_SIZEMASK_8BYTE
#else /* __x86_64__ */
#define X86_REGISTER_GENERAL_PURPOSE_PAX  X86_REGISTER_GENERAL_PURPOSE_EAX /* %pax */
#define X86_REGISTER_GENERAL_PURPOSE_PCX  X86_REGISTER_GENERAL_PURPOSE_ECX /* %pcx */
#define X86_REGISTER_GENERAL_PURPOSE_PDX  X86_REGISTER_GENERAL_PURPOSE_EDX /* %pdx */
#define X86_REGISTER_GENERAL_PURPOSE_PBX  X86_REGISTER_GENERAL_PURPOSE_EBX /* %pbx */
#define X86_REGISTER_GENERAL_PURPOSE_PSP  X86_REGISTER_GENERAL_PURPOSE_ESP /* %psp */
#define X86_REGISTER_GENERAL_PURPOSE_PBP  X86_REGISTER_GENERAL_PURPOSE_EBP /* %pbp */
#define X86_REGISTER_GENERAL_PURPOSE_PSI  X86_REGISTER_GENERAL_PURPOSE_ESI /* %psi */
#define X86_REGISTER_GENERAL_PURPOSE_PDI  X86_REGISTER_GENERAL_PURPOSE_EDI /* %pdi */
#define X86_REGISTER_MISC_PFLAGS          X86_REGISTER_MISC_EFLAGS         /* %pflags */
#define X86_REGISTER_MISC_PIP             X86_REGISTER_MISC_EIP            /* %pip */
#define X86_REGISTER_MISC_FSBASE          X86_REGISTER_MISC_FSBASEL        /* %fs.base */
#define X86_REGISTER_MISC_GSBASE          X86_REGISTER_MISC_GSBASEL        /* %gs.base */
#define X86_REGISTER_MISC_GDT_BASE        X86_REGISTER_MISC_GDT_BASEL      /* %gdt.base */
#define X86_REGISTER_MISC_IDT_BASE        X86_REGISTER_MISC_IDT_BASEL      /* %idt.base */
#define X86_REGISTER_MISC_FIP             X86_REGISTER_MISC_FIPL           /* %fip */
#define X86_REGISTER_MISC_FDP             X86_REGISTER_MISC_FDPL           /* %fdp */
#define X86_REGISTER_SIZEMASK_PBYTE       X86_REGISTER_SIZEMASK_4BYTE
#endif /* !__x86_64__ */

#endif /* !_I386_KOS_ASM_REGISTERS_COMPAT_H */
