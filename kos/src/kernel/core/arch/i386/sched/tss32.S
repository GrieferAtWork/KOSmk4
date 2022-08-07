/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_CORE_ARCH_I386_SCHED_TSS32_S
#define GUARD_KERNEL_CORE_ARCH_I386_SCHED_TSS32_S 1
#define __ASSEMBLER__ 1

#include <kernel/compiler.h>

#include <asm/asmword.h>
#include <kos/kernel/x86/gdt.h>
#include <kos/kernel/paging.h>

.section .data.percpu.tss
INTERN_OBJECT(__kernel_percpu_tss)
	/* u16   t_link;   */ .word16 0
	/* u16 __t_zero0;  */ .word16 0
	EXTERN(__kernel_boottask_stack)
	/* u32   t_esp0    */ .word32 (__kernel_boottask_stack + KERNEL_STACKSIZE)
	/* u16   t_ss0;    */ .word16 SEGMENT_KERNEL_DATA
	/* u16 __t_zero1;  */ .word16 0
	/* u32   t_esp1;   */ .word32 (__kernel_boottask_stack + KERNEL_STACKSIZE)
	/* u16   t_ss1;    */ .word16 SEGMENT_KERNEL_DATA
	/* u16 __t_zero2;  */ .word16 0
	/* u32   t_esp2;   */ .word32 (__kernel_boottask_stack + KERNEL_STACKSIZE)
	/* u16   t_ss2;    */ .word16 SEGMENT_KERNEL_DATA
	/* u16 __t_zero3;  */ .word16 0
	EXTERN(pagedir_kernel_phys)
	/* u32   t_cr3;    */ .word32 pagedir_kernel_phys
	EXTERN(_start)
	/* u32   t_eip;    */ .word32 _start
	/* u32   t_eflags; */ .word32 0
	/* u32   t_eax;    */ .word32 0
	/* u32   t_ecx;    */ .word32 0
	/* u32   t_edx;    */ .word32 0
	/* u32   t_ebx;    */ .word32 0
	/* u32   t_esp;    */ .word32 (__kernel_boottask_stack + KERNEL_STACKSIZE)
	/* u32   t_ebp;    */ .word32 0
	/* u32   t_esi;    */ .word32 0
	/* u32   t_edi;    */ .word32 0
	/* u16   t_es;     */ .word16 SEGMENT_USER_DATA_RPL
	/* u16 __t_zero4;  */ .word16 0
	/* u16   t_cs;     */ .word16 SEGMENT_KERNEL_CODE
	/* u16 __t_zero5;  */ .word16 0
	/* u16   t_ss;     */ .word16 SEGMENT_KERNEL_DATA
	/* u16 __t_zero6;  */ .word16 0
	/* u16   t_ds;     */ .word16 SEGMENT_USER_DATA_RPL
	/* u16 __t_zero7;  */ .word16 0
	/* u16   t_fs;     */ .word16 SEGMENT_KERNEL_FSBASE
	/* u16 __t_zero8;  */ .word16 0
	/* u16   t_gs;     */ .word16 SEGMENT_USER_GSBASE_RPL
	/* u16 __t_zero9;  */ .word16 0
	/* u16   t_ldtr;   */ .word16 SEGMENT_NULL
	/* u16 __t_zeroa;  */ .word16 0
	/* u16   t_flags;  */ .word16 0
	EXTERN(__x86_cputss_iob_offset)
	/* u16   t_iomap;  */ .word16 __x86_cputss_iob_offset
END(__kernel_percpu_tss)

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_SCHED_TSS32_S */
