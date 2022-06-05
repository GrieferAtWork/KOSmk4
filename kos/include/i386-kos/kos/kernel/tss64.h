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
#ifndef _I386_KOS_KOS_KERNEL_TSS64_H
#define _I386_KOS_KOS_KERNEL_TSS64_H 1

#include <__stdinc.h>
#include <hybrid/host.h>
#include <hybrid/typecore.h>

#ifdef __x86_64__
#define OFFSET_TSS_RSP0  OFFSET_TSS64_RSP0
#define OFFSET_TSS_RSP1  OFFSET_TSS64_RSP1
#define OFFSET_TSS_RSP2  OFFSET_TSS64_RSP2
#define OFFSET_TSS_IST1  OFFSET_TSS64_IST1
#define OFFSET_TSS_IST2  OFFSET_TSS64_IST2
#define OFFSET_TSS_IST3  OFFSET_TSS64_IST3
#define OFFSET_TSS_IST4  OFFSET_TSS64_IST4
#define OFFSET_TSS_IST5  OFFSET_TSS64_IST5
#define OFFSET_TSS_IST6  OFFSET_TSS64_IST6
#define OFFSET_TSS_IST7  OFFSET_TSS64_IST7
#define OFFSET_TSS_IST   OFFSET_TSS64_IST
#define OFFSET_TSS_IOMAP OFFSET_TSS64_IOMAP
#define SIZEOF_TSS       SIZEOF_TSS64
#define ALIGNOF_TSS      ALIGNOF_TSS64
#define tss64            tss
#endif /* __x86_64__ */

#define OFFSET_TSS64_RSP0    4
#define OFFSET_TSS64_RSP1    12
#define OFFSET_TSS64_RSP2    20
#define OFFSET_TSS64_IST1    36
#define OFFSET_TSS64_IST2    44
#define OFFSET_TSS64_IST3    52
#define OFFSET_TSS64_IST4    60
#define OFFSET_TSS64_IST5    68
#define OFFSET_TSS64_IST6    76
#define OFFSET_TSS64_IST7    84
#define OFFSET_TSS64_IST(n) (36 + ((n) - 1) * 8)
#define OFFSET_TSS64_IOMAP   102
#define SIZEOF_TSS64         104
#define ALIGNOF_TSS64        __ALIGNOF_INT64__


/* NOTE: Documentation is taken/derived from:
 *   `Volume 3 (3A, 3B, 3C & 3D): System Programming Guide'
 *   `Figure 7-11.  64-Bit TSS Format' */
#ifdef __CC__
__DECL_BEGIN

struct __ATTR_ALIGNED(ALIGNOF_TSS64) __ATTR_PACKED tss64 /*[PREFIX(t_)]*/ {
	__UINT32_TYPE__ __t_zero0; /* ... */
	/* The full 64-bit canonical forms of the stack pointers (RSP) for privilege levels 0-2. */
	__UINT64_TYPE__   t_rsp0;  /* Very important: The stack that is switched to when an interrupt switches to the kernel (Ring #0) */
	__UINT64_TYPE__   t_rsp1;  /* Stack used when transitioning from ring 2/3 to ring 1 */
	__UINT64_TYPE__   t_rsp2;  /* Stack used when transitioning from ring 3 to ring 2 */
	__UINT32_TYPE__ __t_zero1; /* ... */
	__UINT32_TYPE__ __t_zero2; /* ... */
	/* The full 64-bit canonical forms of the interrupt stack table (IST) pointers
	 * NOTE: This works hand-in-hand with `struct segment::s_intrgate::ig_ist' */
	union __ATTR_PACKED {
		__UINT64_TYPE__ t_ist[7]; /* NOTE: This array starts at 1! */
		struct __ATTR_PACKED {
			__UINT64_TYPE__ t_ist1;
			__UINT64_TYPE__ t_ist2;
			__UINT64_TYPE__ t_ist3;
			__UINT64_TYPE__ t_ist4;
			__UINT64_TYPE__ t_ist5;
			__UINT64_TYPE__ t_ist6;
			__UINT64_TYPE__ t_ist7;
		};
	};
	__UINT32_TYPE__ __t_zero3; /* ... */
	__UINT32_TYPE__ __t_zero4; /* ... */
	__UINT16_TYPE__ __t_zero5; /* ... */
	__UINT16_TYPE__   t_iomap; /* The 16-bit offset to the I/O permission bit map from the 64-bit TSS base. */
};

__DECL_END
#endif /* __CC__ */

#endif /* !_I386_KOS_KOS_KERNEL_TSS64_H */
