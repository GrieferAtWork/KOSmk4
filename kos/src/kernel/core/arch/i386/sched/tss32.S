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
#include <kernel/compiler.h>

#include <kos/kernel/gdt.h>
#include <kos/kernel/paging.h>


.section .data.percpu.tss
INTERN_OBJECT(__kernel_percpu_tss)
	/* u16   t_link; */   .word 0
	/* u16 __t_zero0; */  .word 0
	INTERN(__kernel_boottask_stack)
	/* u32   t_esp0 */    .long (__kernel_boottask_stack + KERNEL_STACKSIZE)
	/* u16   t_ss0; */    .word SEGMENT_KERNEL_DATA
	/* u16 __t_zero1; */  .word 0
	/* u32   t_esp1; */   .long (__kernel_boottask_stack + KERNEL_STACKSIZE)
	/* u16   t_ss1; */    .word SEGMENT_KERNEL_DATA
	/* u16 __t_zero2; */  .word 0
	/* u32   t_esp2; */   .long (__kernel_boottask_stack + KERNEL_STACKSIZE)
	/* u16   t_ss2; */    .word SEGMENT_KERNEL_DATA
	/* u16 __t_zero3; */  .word 0
	INTERN(pagedir_kernel_phys)
	/* u32   t_cr3; */    .long pagedir_kernel_phys
	INTERN(_start)
	/* u32   t_eip; */    .long _start
	/* u32   t_eflags; */ .long 0
	/* u32   t_eax; */    .long 0
	/* u32   t_ecx; */    .long 0
	/* u32   t_edx; */    .long 0
	/* u32   t_ebx; */    .long 0
	/* u32   t_esp; */    .long (__kernel_boottask_stack + KERNEL_STACKSIZE)
	/* u32   t_ebp; */    .long 0
	/* u32   t_esi; */    .long 0
	/* u32   t_edi; */    .long 0
	/* u16   t_es; */     .word SEGMENT_USER_DATA_RPL
	/* u16 __t_zero4; */  .word 0
	/* u16   t_cs; */     .word SEGMENT_KERNEL_CODE
	/* u16 __t_zero5; */  .word 0
	/* u16   t_ss; */     .word SEGMENT_KERNEL_DATA
	/* u16 __t_zero6; */  .word 0
	/* u16   t_ds; */     .word SEGMENT_USER_DATA_RPL
	/* u16 __t_zero7; */  .word 0
	/* u16   t_fs; */     .word SEGMENT_KERNEL_FSBASE
	/* u16 __t_zero8; */  .word 0
	/* u16   t_gs; */     .word SEGMENT_USER_GSBASE_RPL
	/* u16 __t_zero9; */  .word 0
	/* u16   t_ldtr; */   .word SEGMENT_NULL
	/* u16 __t_zeroa; */  .word 0
	/* u16   t_flags; */  .word 0
	INTERN(__x86_cputss_iob_offset)
	/* u16   t_iomap; */  .word __x86_cputss_iob_offset
END(__kernel_percpu_tss)
