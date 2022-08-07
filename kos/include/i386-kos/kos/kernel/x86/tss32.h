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
#ifndef _I386_KOS_KOS_KERNEL_X86_TSS32_H
#define _I386_KOS_KOS_KERNEL_X86_TSS32_H 1

#include <__stdinc.h>

#include <hybrid/__bitfield.h>
#include <hybrid/host.h>
#include <hybrid/typecore.h>

#ifndef __x86_64__
#define OFFSET_TSS_LINK   OFFSET_TSS32_LINK
#define OFFSET_TSS_ESP0   OFFSET_TSS32_ESP0
#define OFFSET_TSS_SS0    OFFSET_TSS32_SS0
#define OFFSET_TSS_ESP1   OFFSET_TSS32_ESP1
#define OFFSET_TSS_SS1    OFFSET_TSS32_SS1
#define OFFSET_TSS_ESP2   OFFSET_TSS32_ESP2
#define OFFSET_TSS_SS2    OFFSET_TSS32_SS2
#define OFFSET_TSS_CR3    OFFSET_TSS32_CR3
#define OFFSET_TSS_EIP    OFFSET_TSS32_EIP
#define OFFSET_TSS_EFLAGS OFFSET_TSS32_EFLAGS
#define OFFSET_TSS_EAX    OFFSET_TSS32_EAX
#define OFFSET_TSS_ECX    OFFSET_TSS32_ECX
#define OFFSET_TSS_EDX    OFFSET_TSS32_EDX
#define OFFSET_TSS_EBX    OFFSET_TSS32_EBX
#define OFFSET_TSS_ESP    OFFSET_TSS32_ESP
#define OFFSET_TSS_EBP    OFFSET_TSS32_EBP
#define OFFSET_TSS_ESI    OFFSET_TSS32_ESI
#define OFFSET_TSS_EDI    OFFSET_TSS32_EDI
#define OFFSET_TSS_ES     OFFSET_TSS32_ES
#define OFFSET_TSS_CS     OFFSET_TSS32_CS
#define OFFSET_TSS_SS     OFFSET_TSS32_SS
#define OFFSET_TSS_DS     OFFSET_TSS32_DS
#define OFFSET_TSS_FS     OFFSET_TSS32_FS
#define OFFSET_TSS_GS     OFFSET_TSS32_GS
#define OFFSET_TSS_LDTR   OFFSET_TSS32_LDTR
#define OFFSET_TSS_FLAGS  OFFSET_TSS32_FLAGS
#define OFFSET_TSS_IOMAP  OFFSET_TSS32_IOMAP
#define SIZEOF_TSS        SIZEOF_TSS32
#define ALIGNOF_TSS       ALIGNOF_TSS32
#define tss32             tss
#endif /* !__x86_64__ */

#define OFFSET_TSS32_LINK   0
#define OFFSET_TSS32_ESP0   4
#define OFFSET_TSS32_SS0    8
#define OFFSET_TSS32_ESP1   12
#define OFFSET_TSS32_SS1    16
#define OFFSET_TSS32_ESP2   20
#define OFFSET_TSS32_SS2    24
#define OFFSET_TSS32_CR3    28
#define OFFSET_TSS32_EIP    32
#define OFFSET_TSS32_EFLAGS 36
#define OFFSET_TSS32_EAX    40
#define OFFSET_TSS32_ECX    44
#define OFFSET_TSS32_EDX    48
#define OFFSET_TSS32_EBX    52
#define OFFSET_TSS32_ESP    56
#define OFFSET_TSS32_EBP    60
#define OFFSET_TSS32_ESI    64
#define OFFSET_TSS32_EDI    68
#define OFFSET_TSS32_ES     72
#define OFFSET_TSS32_CS     76
#define OFFSET_TSS32_SS     80
#define OFFSET_TSS32_DS     84
#define OFFSET_TSS32_FS     88
#define OFFSET_TSS32_GS     92
#define OFFSET_TSS32_LDTR   96
#define OFFSET_TSS32_FLAGS  100
#define OFFSET_TSS32_IOMAP  102
#define SIZEOF_TSS32        104
#define ALIGNOF_TSS32       4


/* NOTE: Documentation is taken/derived from:
 *   `Volume 3 (3A, 3B, 3C & 3D): System Programming Guide'
 *   `Figure 7-2.  32-Bit Task-State Segment (TSS)' */
#ifdef __CC__
__DECL_BEGIN

struct __ATTR_ALIGNED(ALIGNOF_TSS32) __ATTR_PACKED tss32 /*[PREFIX(t_)]*/ {
	__UINT16_TYPE__   t_link;  /* Contains the segment selector for the TSS of the previous task  (updated
	                            * on a task switch that was initiated by a call, interrupt, or exception).
	                            * This  field (which  is sometimes called  the back link  field) permits a
	                            * task switch back to the previous task by using the IRET instruction. */
	__UINT16_TYPE__ __t_zero0; /* Reserved... */
	/* These stack pointers  consist of a  logical address made  up of the  segment selector  for
	 * the stack segment (SS0, SS1, and SS2) and an offset into the stack (ESP0, ESP1, and ESP2).
	 * Note that  the  values  in  these  fields are  static  for  a  particular  task;  whereas,
	 * the SS and ESP values will change if stack switching occurs within the task */
	__UINT32_TYPE__   t_esp0;  /* Very important: The stack that is switched to when an interrupt switches to the kernel (Ring #0) */
	__UINT16_TYPE__   t_ss0;   /* Stack segment for `t_esp0' */
	__UINT16_TYPE__ __t_zero1; /* ... */
	__UINT32_TYPE__   t_esp1;  /* Stack used when transitioning from ring 2/3 to ring 1 */
	__UINT16_TYPE__   t_ss1;   /* Stack segment for `t_esp1' */
	__UINT16_TYPE__ __t_zero2; /* ... */
	__UINT32_TYPE__   t_esp2;  /* Stack used when transitioning from ring 3 to ring 2 */
	__UINT16_TYPE__   t_ss2;   /* Stack segment for `t_esp2' */
	__UINT16_TYPE__ __t_zero3; /* ... */
	/* NOTE: As you can see, there is no `t_esp3' (ring #3 is userspace). So with that in mind,
	 *       the  existing stack is re-used when an  interrupt happens while inside the kernel,
	 *       meaning  that kernel-space  IRQ recursion is  implicitly possible, yet  one has to
	 *       keep in mind that the stack must always be of sufficient size! */


	__UINT32_TYPE__   t_cr3;    /* Contains the base physical address of the page directory to be used by the task.
	                             * Control register CR3 is also known  as the page-directory base register  (PDBR). */
	__UINT32_TYPE__   t_eip;    /* State of the EIP register prior to the task switch. */
	__UINT32_TYPE__   t_eflags; /* State of the EFAGS register prior to the task switch. */
	__UINT32_TYPE__   t_eax;    /* State of the EAX register prior to the task switch. */
	__UINT32_TYPE__   t_ecx;    /* State of the ECX register prior to the task switch. */
	__UINT32_TYPE__   t_edx;    /* State of the EDX register prior to the task switch. */
	__UINT32_TYPE__   t_ebx;    /* State of the EBX register prior to the task switch. */
	__UINT32_TYPE__   t_esp;    /* State of the ESP register prior to the task switch. */
	__UINT32_TYPE__   t_ebp;    /* State of the EBP register prior to the task switch. */
	__UINT32_TYPE__   t_esi;    /* State of the ESI register prior to the task switch. */
	__UINT32_TYPE__   t_edi;    /* State of the EDI register prior to the task switch. */
	__UINT16_TYPE__   t_es;     /* Segment selectors stored in the ES register prior to the task switch. */
	__UINT16_TYPE__ __t_zero4;  /* ... */
	__UINT16_TYPE__   t_cs;     /* Segment selectors stored in the CS register prior to the task switch. */
	__UINT16_TYPE__ __t_zero5;  /* ... */
	__UINT16_TYPE__   t_ss;     /* Segment selectors stored in the SS register prior to the task switch. */
	__UINT16_TYPE__ __t_zero6;  /* ... */
	__UINT16_TYPE__   t_ds;     /* Segment selectors stored in the DS register prior to the task switch. */
	__UINT16_TYPE__ __t_zero7;  /* ... */
	__UINT16_TYPE__   t_fs;     /* Segment selectors stored in the FS register prior to the task switch. */
	__UINT16_TYPE__ __t_zero8;  /* ... */
	__UINT16_TYPE__   t_gs;     /* Segment selectors stored in the GS register prior to the task switch. */
	__UINT16_TYPE__ __t_zero9;  /* ... */
	__UINT16_TYPE__   t_ldtr;   /* Contains the segment selector for the task's LDT. */
	__UINT16_TYPE__ __t_zeroa;  /* ... */
	union __ATTR_PACKED {
		__UINT16_TYPE__ t_flags; /* TSS flags (bit 1 is the `T' (debug trap) bit) */
		struct __ATTR_PACKED {
			__HYBRID_BITFIELD16_T   t_trap : 1;   /* When set, the T flag  causes the processor to raise  a
			                                       * debug exception when a task switch to this task occurs */
			__HYBRID_BITFIELD16_T __t_zerob : 15; /* ... */
		};
	};
	__UINT16_TYPE__   t_iomap;  /* Contains a 16-bit offset from the base of the TSS to the I/O permission
	                             * bit  map and interrupt redirection bitmap. When present, these maps are
	                             * stored in the TSS at higher addresses. The I/O map base address  points
	                             * to the beginning  of the  I/O permission  bit map  and the  end of  the
	                             * interrupt redirection bit map */
};

__DECL_END
#endif /* __CC__ */

#endif /* !_I386_KOS_KOS_KERNEL_X86_TSS32_H */
