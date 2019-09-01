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
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_REALMODE_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_REALMODE_H 1

#include <kernel/compiler.h>
#include <kernel/types.h>
#include <kos/kernel/cpu-state.h>
#include <kos/kernel/paging.h>

DECL_BEGIN

#undef CONFIG_USE_LIBVM86_FOR_REALMODE

#if 0 /* TODO: It does work to correctly emulate QEMU's e820 function, but
       *       there are many other functions which exist, and even then:
       *       the current implementation is still really badly hacked
       *       together and still makes use of actual low memory for storing
       *       buffers, instead of making use of the page-translation function
       *       to simply emulate a low-memory environment by adding KERNEL_BASE
       * -> In other words: It works, but until libvm86 gets hardened more, I'm
       *    not comfortable in using it by default (also: Once libvm86 does become
       *    the default, add a kernel commandline option to force use of an actual
       *    realmode environment when calling bios functions) */
#define CONFIG_USE_LIBVM86_FOR_REALMODE 1
#endif

#define OFFSET_RMCPUSTATE_INTNO  0
#define OFFSET_RMCPUSTATE_DS     4
#define OFFSET_RMCPUSTATE_ES     6
#define OFFSET_RMCPUSTATE_FS     8
#define OFFSET_RMCPUSTATE_GS     10
#define OFFSET_RMCPUSTATE_EFLAGS 12
#define OFFSET_RMCPUSTATE_EAX    16
#define OFFSET_RMCPUSTATE_ECX    20
#define OFFSET_RMCPUSTATE_EDX    24
#define OFFSET_RMCPUSTATE_EBX    28
#define OFFSET_RMCPUSTATE_EBP    32
#define OFFSET_RMCPUSTATE_ESI    36
#define OFFSET_RMCPUSTATE_EDI    40
#define SIZEOF_RMCPUSTATE        44
#ifdef __CC__
struct __ATTR_PACKED rmcpustate { /* rm -- RealMode */
	/* CPU state used to describe the register state
	 * when performing a realmode bios interrupt.
	 * NOTE: `%ss:%esp' is always set to be
	 *        a small, but proper stack. */
	u8  rmcs_intno;  /* The BIOS interrupt number to trigger */
	u8  rmcs_pad[3]; /* ... */
	u16 rmcs_ds;     /* D (destination) segment register */
	u16 rmcs_es;     /* E (source) segment register */
	u16 rmcs_fs;     /* F segment register */
	u16 rmcs_gs;     /* G segment register */
	u32 rmcs_eflags; /* Flags register */
	u32 rmcs_eax;    /* [C] Accumulator register */
	u32 rmcs_ecx;    /* [C] Count register */
	u32 rmcs_edx;    /* [C] Data register */
	u32 rmcs_ebx;    /* [P] Base register */
	u32 rmcs_ebp;    /* [P] Frame base pointer */
	u32 rmcs_esi;    /* [P] Source pointer */
	u32 rmcs_edi;    /* [P] Destination pointer */
};
#endif /* __CC__ */


#ifdef __CC__
/* Perform a real-mode BIOS interrupt with the given register state,
 * before saving the updated state and returning from this function
 * normally.
 * This is used during early boot in order to query the BIOS on available
 * RAM, as well as other initialization-specific functionality, but is
 * never called again once early boot finishes (which is by this function
 * is also part of the kernel's .free section) */
INTDEF FREE void NOTHROW(FCALL x86_realmode_interrupt)(struct rmcpustate *__restrict state);
INTDEF FREE void NOTHROW(KCALL x86_realmode_initialize)(void);
INTDEF FREE void NOTHROW(KCALL x86_realmode_finalize)(void);

/* A small data buffer usable for input/output of realmode data. */
INTDEF byte_t *x86_realmode_buffer_addr;
#ifdef __INTELLISENSE__
INTDEF u16 x86_realmode_buffer_offset;
INTDEF u16 x86_realmode_buffer_segment;
#else
#define x86_realmode_buffer_offset  ((u16)((uintptr_t)x86_realmode_buffer_addr & 0xffff))
#define x86_realmode_buffer_segment ((u16)(((uintptr_t)x86_realmode_buffer_addr & 0xf0000) >> 4))
#endif

#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_REALMODE_H */
