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
#ifndef _I386_KOS_KOS_KERNEL_SEGMENT_H
#define _I386_KOS_KOS_KERNEL_SEGMENT_H 1

#include <__stdinc.h>
#include <hybrid/host.h>
#include <hybrid/typecore.h>


#define OFFSET_SEGMENT_DESCRIPTOR_LIMIT0            0
#define OFFSET_SEGMENT_DESCRIPTOR_BASE0             2
#define OFFSET_SEGMENT_DESCRIPTOR_BASE1             4
#define OFFSET_SEGMENT_DESCRIPTOR_TYPE_S_DPL_P      5
#define OFFSET_SEGMENT_DESCRIPTOR_LIMIT1_AVL_L_DB_G 6
#define OFFSET_SEGMENT_DESCRIPTOR_BASE2             7
#define SIZEOF_SEGMENT_DESCRIPTOR                   8
#define SEGMENT_INDEX(offset) ((offset)/SIZEOF_SEGMENT_DESCRIPTOR)
#define SEGMENT_OFFSET(index) ((index)*SIZEOF_SEGMENT_DESCRIPTOR)


/* Initialize a generic segment descriptor.
 * @param: base:  Segment base address (0x00000000-0xffffffff)
 * @param: limit: Segment limit (without granularity) (0x00000-0xfffff)
 * @param: TYPE:  Segment type (One of `SEGMENT_DESCRIPTOR_TYPE_*')
 * @param: S:     S-bit: 1=code-or-data; 0=system-descriptor
 * @param: DPL:   Descriptor Privilege Level (0-3)
 * @param: P:     P-bit: Segment is present
 * @param: AVL:   Unused bit (available for use by system software)
 * @param: L:     L-bit: Set to 1 if this is a 64-bit code segment (for x86_64)
 * @param: DB:    D/B-bit: Default operand size (0=16, 1=32) (this affects the 66h-prefix)
 * @param: G:     G-bit: When set, `REAL_LIMIT = (LIMIT * 0x1000) + 0xfff' */
#define SEGMENT_DESCRIPTOR_INIT_U(base, limit, TYPE, S, DPL, P, AVL, L, DB, G)                         \
	(__CCAST(__UINT64_TYPE__)SEGMENT_DESCRIPTOR_INIT_UL(base, limit, TYPE, S, DPL, P, AVL, L, DB, G) | \
	 __CCAST(__UINT64_TYPE__)SEGMENT_DESCRIPTOR_INIT_UH(base, limit, TYPE, S, DPL, P, AVL, L, DB, G) << 32)
#define SEGMENT_DESCRIPTOR_INIT_UL(base, limit, TYPE, S, DPL, P, AVL, L, DB, G) \
	(__CCAST(__UINT32_TYPE__)((limit)&0xffff) |                                 \
	 __CCAST(__UINT32_TYPE__)(((base)&0xffff) << 16))
#define SEGMENT_DESCRIPTOR_INIT_UH(base, limit, TYPE, S, DPL, P, AVL, L, DB, G) \
	(__CCAST(__UINT32_TYPE__)(((base) >> 16) & 0xff) |                          \
	 __CCAST(__UINT32_TYPE__)(((TYPE)&0xf) << 8) |                              \
	 __CCAST(__UINT32_TYPE__)(((S)&1) << 12) |                                  \
	 __CCAST(__UINT32_TYPE__)(((DPL)&3) << 13) |                                \
	 __CCAST(__UINT32_TYPE__)(((P)&1) << 15) |                                  \
	 __CCAST(__UINT32_TYPE__)((limit)&0xf0000) |                                \
	 __CCAST(__UINT32_TYPE__)(((AVL)&1) << 20) |                                \
	 __CCAST(__UINT32_TYPE__)(((L)&1) << 21) |                                  \
	 __CCAST(__UINT32_TYPE__)(((DB)&1) << 22) |                                 \
	 __CCAST(__UINT32_TYPE__)(((G)&1) << 23) |                                  \
	 __CCAST(__UINT32_TYPE__)((base)&0xff000000))
#define SEGMENT_DESCRIPTOR_INIT(base, limit, TYPE, S, DPL, P, AVL, L, DB, G)     \
	{{{                                                                          \
		SEGMENT_DESCRIPTOR_INIT_UL(base, limit, TYPE, S, DPL, P, AVL, L, DB, G), \
		SEGMENT_DESCRIPTOR_INIT_UH(base, limit, TYPE, S, DPL, P, AVL, L, DB, G)  \
	}}}



/* Initialize a TSS segment descriptor.
 * @param: base:  Segment base address (0x00000000-0xffffffff)
 * @param: limit: Segment limit (without granularity) (0x00000-0xfffff)
 * @param: TYPE:  TSS type (One of `SEGMENT_DESCRIPTOR_TYPE_TSS_*')
 * @param: DPL:   Max CPL for which access to this TSS is allowed (0-3)
 * @param: P:     P-bit: Segment is present
 * @param: AVL:   Unused bit (available for use by system software)
 * @param: G:     G-bit: When set, `REAL_LIMIT = (LIMIT * 0x1000) + 0xfff' */
#define SEGMENT_TSS_INIT_U(base, limit, TYPE, DPL, P, AVL, G)                         \
	(__CCAST(__UINT64_TYPE__)SEGMENT_TSS_INIT_UL(base, limit, TYPE, DPL, P, AVL, G) | \
	 __CCAST(__UINT64_TYPE__)SEGMENT_TSS_INIT_UH(base, limit, TYPE, DPL, P, AVL, G) << 32)
#define SEGMENT_TSS_INIT_UL(base, limit, TYPE, DPL, P, AVL, G) \
	SEGMENT_DESCRIPTOR_INIT_UL(base, limit, TYPE, 0, DPL, P, AVL, 0, 0, G)
#define SEGMENT_TSS_INIT_UH(base, limit, TYPE, DPL, P, AVL, G) \
	SEGMENT_DESCRIPTOR_INIT_UH(base, limit, TYPE, 0, DPL, P, AVL, 0, 0, G)
#define SEGMENT_TSS_INIT(base, limit, TYPE, DPL, P, AVL, G)     \
	{{{                                                         \
		SEGMENT_TSS_INIT_UL(base, limit, TYPE, DPL, P, AVL, G), \
		SEGMENT_TSS_INIT_UH(base, limit, TYPE, DPL, P, AVL, G)  \
	}}}
#ifdef __x86_64__
/* Initialize the high-part of a TSS segment */
#define SEGMENT_TSS_HI_INIT_U(base, limit, TYPE, DPL, P, AVL, G)                         \
	(__CCAST(__UINT64_TYPE__)SEGMENT_TSS_HI_INIT_UL(base, limit, TYPE, DPL, P, AVL, G) | \
	 __CCAST(__UINT64_TYPE__)SEGMENT_TSS_HI_INIT_UH(base, limit, TYPE, DPL, P, AVL, G) << 32)
#define SEGMENT_TSS_HI_INIT_UL(base, limit, TYPE, DPL, P, AVL, G) \
	(__CCAST(__UINT32_TYPE__)((base) >> 32))
#define SEGMENT_TSS_HI_INIT_UH(base, limit, TYPE, DPL, P, AVL, G) \
	(__CCAST(__UINT32_TYPE__)0)
#define SEGMENT_TSS_HI_INIT(base, limit, TYPE, DPL, P, AVL, G)     \
	{{{                                                            \
		SEGMENT_TSS_HI_INIT_UL(base, limit, TYPE, DPL, P, AVL, G), \
		SEGMENT_TSS_HI_INIT_UH(base, limit, TYPE, DPL, P, AVL, G)  \
	}}}
#endif /* __x86_64__ */


/* Initialize a generic segment descriptor.
 * @param: base:  Segment base address (0x00000000-0xffffffff)
 * @param: limit: Segment limit (without granularity) (0x00000-0xfffff)
 * @param: DPL:   Descriptor Privilege Level (0-3)
 * @param: P:     P-bit: Segment is present
 * @param: AVL:   Unused bit (available for use by system software)
 * @param: G:     G-bit: When set, `REAL_LIMIT = (LIMIT * 0x1000) + 0xfff' */
#define SEGMENT_LDT_INIT_U(base, limit, DPL, P, AVL, G)                         \
	(__CCAST(__UINT64_TYPE__)SEGMENT_LDT_INIT_UL(base, limit, DPL, P, AVL, G) | \
	 __CCAST(__UINT64_TYPE__)SEGMENT_LDT_INIT_UH(base, limit, DPL, P, AVL, G) << 32)
#define SEGMENT_LDT_INIT_UL(base, limit, DPL, P, AVL, G) \
	SEGMENT_DESCRIPTOR_INIT_UL(base, limit, SEGMENT_DESCRIPTOR_TYPE_LDT, 0, DPL, P, AVL, 0, 0, G)
#define SEGMENT_LDT_INIT_UH(base, limit, DPL, P, AVL, G) \
	SEGMENT_DESCRIPTOR_INIT_UH(base, limit, SEGMENT_DESCRIPTOR_TYPE_LDT, 0, DPL, P, AVL, 0, 0, G)
#define SEGMENT_LDT_INIT(base, limit, DPL, P, AVL, G)     \
	{{{                                                   \
		SEGMENT_LDT_INIT_UL(base, limit, DPL, P, AVL, G), \
		SEGMENT_LDT_INIT_UH(base, limit, DPL, P, AVL, G)  \
	}}}
#ifdef __x86_64__
/* Initialize the high-part of a LDT segment */
#define SEGMENT_LDT_HI_INIT_U(base, limit, DPL, P, AVL, G)                         \
	(__CCAST(__UINT64_TYPE__)SEGMENT_LDT_HI_INIT_UL(base, limit, DPL, P, AVL, G) | \
	 __CCAST(__UINT64_TYPE__)SEGMENT_LDT_HI_INIT_UH(base, limit, DPL, P, AVL, G) << 32)
#define SEGMENT_LDT_HI_INIT_UL(base, limit, DPL, P, AVL, G) \
	(__CCAST(__UINT32_TYPE__)((base) >> 32))
#define SEGMENT_LDT_HI_INIT_UH(base, limit, DPL, P, AVL, G) \
	(__CCAST(__UINT32_TYPE__)0)
#define SEGMENT_LDT_HI_INIT(base, limit, DPL, P, AVL, G)     \
	{{{                                                      \
		SEGMENT_LDT_HI_INIT_UL(base, limit, DPL, P, AVL, G), \
		SEGMENT_LDT_HI_INIT_UH(base, limit, DPL, P, AVL, G)  \
	}}}
#endif /* __x86_64__ */




/* Initialize a Call Gate segment descriptor.
 * @param: offset:  Offset within `segment' (0x00000000-0xffffffff)
 * @param: segment: Target code segment (0x0000-0xffff)
 * @param: TYPE:    TSS type (One of `SEGMENT_DESCRIPTOR_TYPE_CALLGATE_*')
 * @param: ARGC:    Argument count (number of data-words, where word-size depends on gate type (16/32))
 *                  NOTE: This field isn't available on x86_64!
 * @param: DPL:     Max CPL for which access to this Call Gate is allowed (0-3)
 * @param: P:       P-bit: Segment is present */
#ifndef __x86_64__
#define SEGMENT_CALLGATE_INIT_U(offset, segment, TYPE, ARGC, DPL, P)                         \
	(__CCAST(__UINT64_TYPE__)SEGMENT_CALLGATE_INIT_UL(offset, segment, TYPE, ARGC, DPL, P) | \
	 __CCAST(__UINT64_TYPE__)SEGMENT_CALLGATE_INIT_UH(offset, segment, TYPE, ARGC, DPL, P) << 32)
#define SEGMENT_CALLGATE_INIT_UL(offset, segment, TYPE, ARGC, DPL, P) \
	(__CCAST(__UINT32_TYPE__)((offset)&0xffff) |                      \
	 __CCAST(__UINT32_TYPE__)((segment)&0xffff) << 16)
#define SEGMENT_CALLGATE_INIT_UH(offset, segment, TYPE, ARGC, DPL, P) \
	(__CCAST(__UINT32_TYPE__)((ARGC)&0x1f) |                          \
	 __CCAST(__UINT32_TYPE__)(((TYPE)&0xf) << 8) |                    \
	 __CCAST(__UINT32_TYPE__)(((DPL)&3) << 13) |                      \
	 __CCAST(__UINT32_TYPE__)(((P)&1) << 15) |                        \
	 __CCAST(__UINT32_TYPE__)((offset)&0xffff0000))
#define SEGMENT_CALLGATE_INIT(offset, segment, TYPE, ARGC, DPL, P)     \
	{{{                                                           \
		SEGMENT_CALLGATE_INIT_UL(offset, segment, TYPE, ARGC, DPL, P), \
		SEGMENT_CALLGATE_INIT_UH(offset, segment, TYPE, ARGC, DPL, P)  \
	}}}
#else /* !__x86_64__ */
#define SEGMENT_CALLGATE_INIT_U(offset, segment, TYPE, DPL, P)                         \
	(__CCAST(__UINT64_TYPE__)SEGMENT_CALLGATE_INIT_UL(offset, segment, TYPE, DPL, P) | \
	 __CCAST(__UINT64_TYPE__)SEGMENT_CALLGATE_INIT_UH(offset, segment, TYPE, DPL, P) << 32)
#define SEGMENT_CALLGATE_INIT_UL(offset, segment, TYPE, DPL, P) \
	(__CCAST(__UINT32_TYPE__)((offset)&0xffff) |                \
	 __CCAST(__UINT32_TYPE__)((segment)&0xffff) << 16)
#define SEGMENT_CALLGATE_INIT_UH(offset, segment, TYPE, DPL, P) \
	(__CCAST(__UINT32_TYPE__)(((TYPE)&0xf) << 8) |              \
	 __CCAST(__UINT32_TYPE__)(((DPL)&3) << 13) |                \
	 __CCAST(__UINT32_TYPE__)(((P)&1) << 15) |                  \
	 __CCAST(__UINT32_TYPE__)((offset)&0xffff0000))
#define SEGMENT_CALLGATE_INIT(offset, segment, TYPE, DPL, P)     \
	{{{                                                     \
		SEGMENT_CALLGATE_INIT_UL(offset, segment, TYPE, DPL, P), \
		SEGMENT_CALLGATE_INIT_UH(offset, segment, TYPE, DPL, P)  \
	}}}
/* Initialize the high-part of a Call Gate segment */
#define SEGMENT_CALLGATE_HI_INIT_U(offset, segment, TYPE, DPL, P)                         \
	(__CCAST(__UINT64_TYPE__)SEGMENT_CALLGATE_HI_INIT_UL(offset, segment, TYPE, DPL, P) | \
	 __CCAST(__UINT64_TYPE__)SEGMENT_CALLGATE_HI_INIT_UH(offset, segment, TYPE, DPL, P) << 32)
#define SEGMENT_CALLGATE_HI_INIT_UL(offset, segment, TYPE, DPL, P) \
	(__CCAST(__UINT32_TYPE__)((offset) >> 32))
#define SEGMENT_CALLGATE_HI_INIT_UH(offset, segment, TYPE, DPL, P) \
	(__CCAST(__UINT32_TYPE__)0)
#define SEGMENT_CALLGATE_HI_INIT(offset, segment, TYPE, DPL, P)     \
	{{{                                                             \
		SEGMENT_CALLGATE_HI_INIT_UL(offset, segment, TYPE, DPL, P), \
		SEGMENT_CALLGATE_HI_INIT_UH(offset, segment, TYPE, DPL, P)  \
	}}}
#endif /* __x86_64__ */



/* Initialize an Interrupt/Trap Gate segment descriptor.
 * @param: offset:  Offset within `segment' (0x00000000-0xffffffff)
 * @param: segment: Target code segment (0x0000-0xffff)
 * @param: IST:     [x86_64 only] The Interrupt Stack table index+1, or ZERO to keep the previous stack
 * @param: TYPE:    TSS type (One of `SEGMENT_DESCRIPTOR_TYPE_(INTR|TRAP)GATE_*')
 *                  INTR: #IF is disabled upon entry
 *                  TRAP: #IF is left unchanged upon entry
 * @param: DPL:     Max CPL for which access to this Call Gate is allowed (0-3)
 * @param: P:       P-bit: Segment is present */
#ifndef __x86_64__
#define SEGMENT_INTRGATE_INIT_U(offset, segment, TYPE, DPL, P)                         \
	(__CCAST(__UINT64_TYPE__)SEGMENT_INTRGATE_INIT_UL(offset, segment, TYPE, DPL, P) | \
	 __CCAST(__UINT64_TYPE__)SEGMENT_INTRGATE_INIT_UH(offset, segment, TYPE, DPL, P) << 32)
#define SEGMENT_INTRGATE_INIT_UL(offset, segment, TYPE, DPL, P) \
	(__CCAST(__UINT32_TYPE__)((offset)&0xffff) |                \
	 __CCAST(__UINT32_TYPE__)((segment)&0xffff) << 16)
#define SEGMENT_INTRGATE_INIT_UH(offset, segment, TYPE, DPL, P) \
	(__CCAST(__UINT32_TYPE__)(((TYPE)&0xf) << 8) |              \
	 __CCAST(__UINT32_TYPE__)(((DPL)&3) << 13) |                \
	 __CCAST(__UINT32_TYPE__)(((P)&1) << 15) |                  \
	 __CCAST(__UINT32_TYPE__)((offset)&0xffff0000))
#define SEGMENT_INTRGATE_INIT(offset, segment, TYPE, DPL, P)     \
	{{{                                                          \
		SEGMENT_INTRGATE_INIT_UL(offset, segment, TYPE, DPL, P), \
		SEGMENT_INTRGATE_INIT_UH(offset, segment, TYPE, DPL, P)  \
	}}}
#else /* !__x86_64__ */
#define SEGMENT_INTRGATE_INIT_U(offset, segment, IST, TYPE, DPL, P)                         \
	(__CCAST(__UINT64_TYPE__)SEGMENT_INTRGATE_INIT_UL(offset, segment, IST, TYPE, DPL, P) | \
	 __CCAST(__UINT64_TYPE__)SEGMENT_INTRGATE_INIT_UH(offset, segment, IST, TYPE, DPL, P) << 32)
#define SEGMENT_INTRGATE_INIT_UL(offset, segment, IST, TYPE, DPL, P) \
	(__CCAST(__UINT32_TYPE__)((offset)&0xffff) |                     \
	 __CCAST(__UINT32_TYPE__)((segment)&0xffff) << 16)
#define SEGMENT_INTRGATE_INIT_UH(offset, segment, IST, TYPE, DPL, P) \
	(__CCAST(__UINT32_TYPE__)((IST)&7) |                             \
	 __CCAST(__UINT32_TYPE__)(((TYPE)&0xf) << 8) |                   \
	 __CCAST(__UINT32_TYPE__)(((DPL)&3) << 13) |                     \
	 __CCAST(__UINT32_TYPE__)(((P)&1) << 15) |                       \
	 __CCAST(__UINT32_TYPE__)((offset)&0xffff0000))
#define SEGMENT_INTRGATE_INIT(offset, segment, IST, TYPE, DPL, P)     \
	{{{                                                               \
		SEGMENT_INTRGATE_INIT_UL(offset, segment, IST, TYPE, DPL, P), \
		SEGMENT_INTRGATE_INIT_UH(offset, segment, IST, TYPE, DPL, P)  \
	}}}
/* Initialize the high-part of a Call Gate segment */
#define SEGMENT_INTRGATE_HI_INIT_U(offset, segment, IST, TYPE, DPL, P)                         \
	(__CCAST(__UINT64_TYPE__)SEGMENT_INTRGATE_HI_INIT_UL(offset, segment, IST, TYPE, DPL, P) | \
	 __CCAST(__UINT64_TYPE__)SEGMENT_INTRGATE_HI_INIT_UH(offset, segment, IST, TYPE, DPL, P) << 32)
#define SEGMENT_INTRGATE_HI_INIT_UL(offset, segment, IST, TYPE, DPL, P) \
	(__CCAST(__UINT32_TYPE__)((offset) >> 32))
#define SEGMENT_INTRGATE_HI_INIT_UH(offset, segment, IST, TYPE, DPL, P) \
	(__CCAST(__UINT32_TYPE__)0)
#define SEGMENT_INTRGATE_HI_INIT(offset, segment, IST, TYPE, DPL, P)     \
	{{{                                                                  \
		SEGMENT_INTRGATE_HI_INIT_UL(offset, segment, IST, TYPE, DPL, P), \
		SEGMENT_INTRGATE_HI_INIT_UH(offset, segment, IST, TYPE, DPL, P)  \
	}}}
#endif /* __x86_64__ */



#ifndef __x86_64__
/* Initialize a Task Gate segment descriptor.
 * @param: segment: Target code segment (0x0000-0xffff)
 * @param: DPL:     Max CPL for which access to this Call Gate is allowed (0-3)
 * @param: P:       P-bit: Segment is present */
#define SEGMENT_TASKGATE_INIT_U(segment, DPL, P)                         \
	(__CCAST(__UINT64_TYPE__)SEGMENT_TASKGATE_INIT_UL(segment, DPL, P) | \
	 __CCAST(__UINT64_TYPE__)SEGMENT_TASKGATE_INIT_UH(segment, DPL, P) << 32)
#define SEGMENT_TASKGATE_INIT_UL(segment, DPL, P) \
	SEGMENT_CALLGATE_INIT_UL(0, segment, SEGMENT_DESCRIPTOR_TYPE_TASKGATE, 0, DPL, P)
#define SEGMENT_TASKGATE_INIT_UH(segment, DPL, P) \
	SEGMENT_CALLGATE_INIT_UH(0, segment, SEGMENT_DESCRIPTOR_TYPE_TASKGATE, 0, DPL, P)
#define SEGMENT_TASKGATE_INIT(segment, DPL, P)     \
	{{{                                            \
		SEGMENT_TASKGATE_INIT_UL(segment, DPL, P), \
		SEGMENT_TASKGATE_INIT_UH(segment, DPL, P)  \
	}}}
#endif /* !__x86_64__ */



/* Raw segment descriptor type codes. */
#define SEGMENT_DESCRIPTOR_TYPE_DATA_RD        0x0 /* Read-Only. */
#define SEGMENT_DESCRIPTOR_TYPE_DATA_RDA       0x1 /* Read-Only, accessed. */
#define SEGMENT_DESCRIPTOR_TYPE_DATA_RDWR      0x2 /* Read/Write. */
#define SEGMENT_DESCRIPTOR_TYPE_DATA_RDWRA     0x3 /* Read/Write, accessed. */
#define SEGMENT_DESCRIPTOR_TYPE_DATA_RDEXPD    0x4 /* Read-Only, expand-down. */
#define SEGMENT_DESCRIPTOR_TYPE_DATA_RDEXPDA   0x5 /* Read-Only, expand-down, accessed. */
#define SEGMENT_DESCRIPTOR_TYPE_DATA_RDWREXPD  0x6 /* Read/Write, expand-down. */
#define SEGMENT_DESCRIPTOR_TYPE_DATA_RDWREXPDA 0x7 /* Read/Write, expand-down, accessed. */
#define SEGMENT_DESCRIPTOR_TYPE_CODE_EX        0x8 /* Execute-Only. */
#define SEGMENT_DESCRIPTOR_TYPE_CODE_EXA       0x9 /* Execute-Only, accessed. */
#define SEGMENT_DESCRIPTOR_TYPE_CODE_EXRD      0xa /* Execute/Read. */
#define SEGMENT_DESCRIPTOR_TYPE_CODE_EXRDA     0xb /* Execute/Read, accessed. */
#define SEGMENT_DESCRIPTOR_TYPE_CODE_EXC       0xc /* Execute-Only, conforming. */
#define SEGMENT_DESCRIPTOR_TYPE_CODE_EXCA      0xd /* Execute-Only, conforming, accessed. */
#define SEGMENT_DESCRIPTOR_TYPE_CODE_EXRDC     0xe /* Execute/Read, conforming. */
#define SEGMENT_DESCRIPTOR_TYPE_CODE_EXRDCA    0xf /* Execute/Read, conforming, accessed. */

#ifdef __x86_64__
/*      SEGMENT_DESCRIPTOR_TYPE_            0x0  * RESERVED */
/*      SEGMENT_DESCRIPTOR_TYPE_            0x1  * RESERVED */
#define SEGMENT_DESCRIPTOR_TYPE_LDT         0x2 /* Local descriptor table */
/*      SEGMENT_DESCRIPTOR_TYPE_            0x3  * RESERVED */
/*      SEGMENT_DESCRIPTOR_TYPE_            0x4  * RESERVED */
/*      SEGMENT_DESCRIPTOR_TYPE_            0x5  * RESERVED */
/*      SEGMENT_DESCRIPTOR_TYPE_            0x6  * RESERVED */
/*      SEGMENT_DESCRIPTOR_TYPE_            0x7  * RESERVED */
/*      SEGMENT_DESCRIPTOR_TYPE_            0x8  * RESERVED */
#define SEGMENT_DESCRIPTOR_TYPE_TSS_64_AVL  0x9 /* 64-bit TSS (available) */
/*      SEGMENT_DESCRIPTOR_TYPE_            0xa  * RESERVED */
#define SEGMENT_DESCRIPTOR_TYPE_TSS_64_BSY  0xb /* 64-bit TSS (busy) */
#define SEGMENT_DESCRIPTOR_TYPE_CALLGATE_64 0xc /* 64-bit Call Gate */
/*      SEGMENT_DESCRIPTOR_TYPE_            0xd  * RESERVED */
#define SEGMENT_DESCRIPTOR_TYPE_INTRGATE_64 0xe /* 64-bit Interrupt Gate */
#define SEGMENT_DESCRIPTOR_TYPE_TRAPGATE_64 0xf /* 64-bit Trap Gate */
#else /* __x86_64__ */
/*      SEGMENT_DESCRIPTOR_TYPE_            0x0  * RESERVED */
#define SEGMENT_DESCRIPTOR_TYPE_TSS_16_AVL  0x1 /* 16-bit TSS (available) */
#define SEGMENT_DESCRIPTOR_TYPE_LDT         0x2 /* Local descriptor table */
#define SEGMENT_DESCRIPTOR_TYPE_TSS_16_BSY  0x3 /* 16-bit TSS (busy) */
#define SEGMENT_DESCRIPTOR_TYPE_CALLGATE_16 0x4 /* 16-bit Call Gate */
#define SEGMENT_DESCRIPTOR_TYPE_TASKGATE    0x5 /* Task Gate */
#define SEGMENT_DESCRIPTOR_TYPE_INTRGATE_16 0x6 /* 16-bit Interrupt Gate */
#define SEGMENT_DESCRIPTOR_TYPE_TRAPGATE_16 0x7 /* 16-bit Trap Gate */
/*      SEGMENT_DESCRIPTOR_TYPE_            0x8  * RESERVED */
#define SEGMENT_DESCRIPTOR_TYPE_TSS_32_AVL  0x9 /* 32-bit TSS (available) */
/*      SEGMENT_DESCRIPTOR_TYPE_            0xa  * RESERVED */
#define SEGMENT_DESCRIPTOR_TYPE_TSS_32_BSY  0xb /* 32-bit TSS (busy) */
#define SEGMENT_DESCRIPTOR_TYPE_CALLGATE_32 0xc /* 32-bit Call Gate */
/*      SEGMENT_DESCRIPTOR_TYPE_            0xd  * RESERVED */
#define SEGMENT_DESCRIPTOR_TYPE_INTRGATE_32 0xe /* 32-bit Interrupt Gate */
#define SEGMENT_DESCRIPTOR_TYPE_TRAPGATE_32 0xf /* 32-bit Trap Gate */
#endif /* !__x86_64__ */



#ifdef __x86_64__
#define SEGMENT_DESCRIPTOR_TYPE_TSS_AVL  SEGMENT_DESCRIPTOR_TYPE_TSS_64_AVL
#define SEGMENT_DESCRIPTOR_TYPE_TSS_BSY  SEGMENT_DESCRIPTOR_TYPE_TSS_64_BSY
#define SEGMENT_DESCRIPTOR_TYPE_CALLGATE SEGMENT_DESCRIPTOR_TYPE_CALLGATE_64
#define SEGMENT_DESCRIPTOR_TYPE_INTRGATE SEGMENT_DESCRIPTOR_TYPE_INTRGATE_64
#define SEGMENT_DESCRIPTOR_TYPE_TRAPGATE SEGMENT_DESCRIPTOR_TYPE_TRAPGATE_64
#else /* __x86_64__ */
#define SEGMENT_DESCRIPTOR_TYPE_TSS_AVL  SEGMENT_DESCRIPTOR_TYPE_TSS_32_AVL
#define SEGMENT_DESCRIPTOR_TYPE_TSS_BSY  SEGMENT_DESCRIPTOR_TYPE_TSS_32_BSY
#define SEGMENT_DESCRIPTOR_TYPE_CALLGATE SEGMENT_DESCRIPTOR_TYPE_CALLGATE_32
#define SEGMENT_DESCRIPTOR_TYPE_INTRGATE SEGMENT_DESCRIPTOR_TYPE_INTRGATE_32
#define SEGMENT_DESCRIPTOR_TYPE_TRAPGATE SEGMENT_DESCRIPTOR_TYPE_TRAPGATE_32
#endif /* !__x86_64__ */




__DECL_BEGIN

#ifdef __CC__
/* GDT/LDT/IDT segment entry.
 * NOTE: On x86_64, IDT entries always have a fixed length of 16  bytes,
 *       with every first entry being one of the low-segment fields, and
 *       every second being the associated *_hi entry. */
struct __ATTR_PACKED segment {
	union __ATTR_PACKED {
		struct __ATTR_PACKED { __UINT32_TYPE__ s_ul, s_uh; }; /* 32-bit, unsigned control words */
		struct __ATTR_PACKED { __INT32_TYPE__  s_sl, s_sh; }; /* 32-bit, signed control words */
#ifdef __UINT64_TYPE__
		__UINT64_TYPE__ s_u; /* 64-bit, unsigned control word */
		__INT64_TYPE__  s_s; /* 64-bit, signed control word */
#endif /* __UINT64_TYPE__ */
		struct __ATTR_PACKED {
			__UINT16_TYPE__ d_limit0; /* [valid_if(d_present == 1)] Bit 00-15 of the segment limit. */
			__UINT16_TYPE__ d_base0;  /* [valid_if(d_present == 1)] Bit 00-15 of the segment base. */
			__UINT8_TYPE__  d_base1;  /* [valid_if(d_present == 1)] Bit 16-23 of the segment base. */
			union __ATTR_PACKED {
				__UINT8_TYPE__ d_type_s_dpl_p; /* Segment TYPE, S, DPL and P bits. */
				struct __ATTR_PACKED {
					unsigned int dtb_accessed : 1; /* A-bit: Accessed */
					unsigned int dtb_wr : 1;       /* W/R-bit: Writable(dtb_code=0) / Readable(dtb_code=1) */
					unsigned int dtb_ec : 1;       /* E/C-bit: Expand-down(dtb_code=0) / Conforming(dtb_code=1) */
					unsigned int dtb_code : 1;     /* When set: is a code segment. */
				} d_type_bits;
				struct __ATTR_PACKED {
					unsigned int d_type: 4;           /* Segment TYPE (One of `SEGMENT_DESCRIPTOR_TYPE_*') */
					unsigned int d_code_or_data: 1;   /* S-bit: 1=code-or-data; 0=system-descriptor */
					unsigned int d_dpl: 2;            /* Descriptor Privilege Level (0-3) */
					unsigned int d_present: 1;        /* P-bit: Segment is present. */
				};
			};
			union __ATTR_PACKED {
				__UINT8_TYPE__ d_limit1_avl_l_db_g;   /* [valid_if(d_present == 1)] Segment limit 16-19, AVL, L, D/B and G bits. */
				struct __ATTR_PACKED {
					unsigned int d_limit1: 4;         /* [valid_if(d_present == 1)] Segment limit 16-19 */
					unsigned int d_avl: 1;            /* [valid_if(d_present == 1)] Unused bit (available for use by system software; unused in KOS) */
					unsigned int d_long: 1;           /* [valid_if(d_present == 1)] L-bit: Set to 1 if this is a 64-bit code segment (for x86_64). */
					unsigned int d_defop: 1;          /* [valid_if(d_present == 1)] D/B-bit: Default operand size (0=16, 1=32) (this affects the 66h-prefix).
					                                   * NOTE: When `d_long' is set, then this bit _must_ be cleared! */
					unsigned int d_granularity: 1;    /* [valid_if(d_present == 1)] G-bit: When set, `REAL_LIMIT = (LIMIT * 0x1000) + 0xfff'. */
				};
			};
			__UINT8_TYPE__  d_base2;  /* [valid_if(d_present == 1)] Bit 24-31 of the segment base. */
		} s_descriptor; /* Segment descriptor. */



		struct __ATTR_PACKED {
			__UINT16_TYPE__ t_limit0; /* Bit 00-15 of the segment limit. */
			__UINT16_TYPE__ t_base0;  /* Bit 00-15 of the segment base. */
			__UINT8_TYPE__  t_base1;  /* Bit 16-23 of the segment base. */
			union __ATTR_PACKED {
				__UINT8_TYPE__ t_busy_dpl_p; /* TSS BUSY, DPL and P bits. */
				struct __ATTR_PACKED {
					unsigned int __dtb_accessed : 1; /* A-bit: Always 1 */
					unsigned int ttb_busy: 1;        /* TSS BUSY bit. */
					unsigned int __ttb_ec : 1;       /* E/C-bit: Always 0 */
#ifdef __x86_64__
					unsigned int __ttb_code : 1;     /* Always 1 */
#else /* __x86_64__ */
					unsigned int ttb_is32 : 1;       /* code-bit: 1=32-bit tss; 0=16-bit tss */
#endif /* !__x86_64__ */
				} t_type_bits;
				struct __ATTR_PACKED {
					unsigned int t_type: 4;           /* Segment TYPE (One of `SEGMENT_DESCRIPTOR_TYPE_TSS_*') */
					unsigned int __t_code_or_data: 1; /* S-bit: Always 0 */
					unsigned int t_dpl: 2;            /* Max CPL for which access to this TSS is allowed (0-3) */
					unsigned int t_present: 1;        /* P-bit: Segment is present. */
				};
			};
			union __ATTR_PACKED {
				__UINT8_TYPE__ t_limit1_avl_g;   /* Segment limit 16-19, AVL and G bits. */
				struct __ATTR_PACKED {
					unsigned int t_limit1: 4;         /* Segment limit 16-19 */
					unsigned int t_avl: 1;            /* Unused bit (available for use by system software; unused in KOS) */
					unsigned int __t_long: 1;         /* L-bit: Always 0. */
					unsigned int __t_defop: 1;        /* D/B-bit: Always 0. */
					unsigned int t_granularity: 1;    /* G-bit: When set, `REAL_LIMIT = (LIMIT * 0x1000) + 0xfff'. */
				};
			};
			__UINT8_TYPE__  t_base2;  /* Bit 24-31 of the segment base. */
		} s_tss; /* TSS descriptor */



		struct __ATTR_PACKED {
			__UINT16_TYPE__ cg_offset0; /* Bit 00-15 of the offset within the target segment. */
			__UINT16_TYPE__ cg_segment; /* Target code segment (%cs when the call-gate is invoked). */
#ifdef __x86_64__
			__UINT8_TYPE__  __cg_zero;  /* Always 0 */
#else /* __x86_64__ */
			union __ATTR_PACKED {
				__UINT8_TYPE__ cg_argc_zero; /* Argument count and 0 bits. */
				struct __ATTR_PACKED {
					unsigned int cg_argc: 5;   /* Argument count (number of data-words, where word-size depends on gate type (16/32)) */
					unsigned int __cg_zero: 3; /* Always 0 */
				};
			};
#endif /* !__x86_64__ */
			union __ATTR_PACKED {
				__UINT8_TYPE__ cg_type_dpl_p; /* Call gate TYPE, DPL and P bits. */
				struct __ATTR_PACKED {
					unsigned int __cgtb_accessed : 1; /* A-bit: Always 0 */
					unsigned int __cgtb_wr : 1;       /* W/R-bit: Always 0 */
					unsigned int __cgtb_ec : 1;       /* E/C-bit: Always 1 */
#ifdef __x86_64__
					unsigned int __cgtb_code : 1;     /* Always 1 */
#else /* __x86_64__ */
					unsigned int cgtb_is32 : 1;       /* code-bit: 1=32-bit gate; 0=16-bit gate */
#endif /* !__x86_64__ */
				} cg_type_bits;
				struct __ATTR_PACKED {
					unsigned int cg_type: 4;           /* Segment TYPE (One of `SEGMENT_DESCRIPTOR_TYPE_CALLGATE_*') */
					unsigned int __cg_code_or_data: 1; /* S-bit: Always 0 */
					unsigned int cg_dpl: 2;            /* Max CPL for which access to this Call Gate is allowed (0-3) */
					unsigned int cg_present: 1;        /* P-bit: Segment is present. */
				};
			};
			__UINT16_TYPE__ cg_offset1; /* Bit 16-31 of the offset within the target segment. */
		} s_callgate; /* Call gate descriptor. */



		struct __ATTR_PACKED {
			__UINT16_TYPE__ ig_offset0; /* Bit 00-15 of the offset within the target segment. */
			__UINT16_TYPE__ ig_segment; /* Target code segment (%cs when the Interrupt/Trap-gate is invoked). */
#ifdef __x86_64__
			union __ATTR_PACKED {
				__UINT8_TYPE__ ig_ist_zero;     /* IST and ZERO bits */
				struct __ATTR_PACKED {
					unsigned int ig_ist : 3;    /* Interrupt stack table index+1 (or 0 if the stack isn't changed) */
					unsigned int __ig_zero : 5; /* Always 0 */
				};
			};
#else /* __x86_64__ */
			__UINT8_TYPE__  __ig_zero;  /* Always 0 */
#endif /* !__x86_64__ */
			union __ATTR_PACKED {
				__UINT8_TYPE__ ig_type_dpl_p; /* Interrupt/Trap gate TYPE, DPL and P bits. */
				struct __ATTR_PACKED {
					unsigned int igtb_istrap : 1; /* A-bit: 0=interrupt gate, 1=trap gate */
					unsigned int __igtb_wr : 1;   /* W/R-bit: Always 1 */
					unsigned int __igtb_ec : 1;   /* E/C-bit: Always 1 */
#ifdef __x86_64__
					unsigned int __igtb_code : 1; /* Always 1 */
#else /* __x86_64__ */
					unsigned int igtb_is32 : 1;   /* code-bit: 1=32-bit gate; 0=16-bit gate */
#endif /* !__x86_64__ */
				} ig_type_bits;
				struct __ATTR_PACKED {
					unsigned int ig_type: 4;           /* Segment TYPE (One of `SEGMENT_DESCRIPTOR_TYPE_INTRGATE_*') */
					unsigned int __cg_code_or_data: 1; /* S-bit: Always 0 */
					unsigned int ig_dpl: 2;            /* Max CPL for which access to this Interrupt/Trap Gate is allowed (0-3) */
					unsigned int ig_present: 1;        /* P-bit: Segment is present. */
				};
			};
			__UINT16_TYPE__ ig_offset1; /* Bit 16-31 of the offset within the target segment. */
		} s_intrgate; /* Interrupt/Trap gate descriptor. */



#ifndef __x86_64__
		/* Task gates are only available in 32-bit mode. */
		struct __ATTR_PACKED {
			__UINT16_TYPE__ __tg_offset0; /* Always 0 */
			__UINT16_TYPE__ tg_segment;   /* Target code segment (%cs when the Task-gate is invoked). */
			__UINT8_TYPE__  __tg_zero;    /* Always 0 */
			union __ATTR_PACKED {
				__UINT8_TYPE__ tg_type_dpl_p; /* Task gate TYPE, DPL and P bits. */
				struct __ATTR_PACKED {
					unsigned int __igtb_accessed : 1; /* A-bit: Always 1 */
					unsigned int __igtb_wr : 1;       /* W/R-bit: Always 0 */
					unsigned int __igtb_ec : 1;       /* E/C-bit: Always 1 */
					unsigned int __igtb_code : 1;     /* Code-bit: Always 0 */
				} tg_type_bits;
				struct __ATTR_PACKED {
					unsigned int tg_type: 4;           /* Segment TYPE (One of `SEGMENT_DESCRIPTOR_TYPE_TRAPGATE_*') */
					unsigned int __cg_code_or_data: 1; /* S-bit: Always 0 */
					unsigned int tg_dpl: 2;            /* Max CPL for which access to this Task Gate is allowed (0-3) */
					unsigned int tg_present: 1;        /* P-bit: Segment is present. */
				};
			};
			__UINT16_TYPE__ __tg_offset1; /* Always 0 */
		} s_taskgate; /* Task gate descriptor. */
#endif /* !__x86_64__ */


		/* On x86_64 a couple of descriptors take up 2 consecutive GDT/LDT entries.
		 * These  are  the  data  formats   for  the  second  entry   respectively. */
#ifdef __x86_64__
		struct __ATTR_PACKED {
			__UINT32_TYPE__ th_base3;        /* Bit 32-63 of the segment base. */
			__UINT8_TYPE__  th_reserved0;    /* Reserved (initialize to 0). */
			unsigned int    th_zero: 4;      /* Always 0 */
			unsigned int    th_reserved1: 4; /* Reserved (initialize to 0). */
			__UINT16_TYPE__ th_reserved2;    /* Reserved (initialize to 0). */
		} s_tss_hi; /* TSS descriptor (high part) */

		struct __ATTR_PACKED {
			__UINT32_TYPE__ cgh_offset3;      /* Bit 32-63 of the offset. */
			__UINT8_TYPE__  cgh_reserved0;    /* Reserved (initialize to 0). */
			unsigned int    cgh_zero: 4;      /* Always 0 */
			unsigned int    cgh_reserved1: 4; /* Reserved (initialize to 0). */
			__UINT16_TYPE__ cgh_reserved2;    /* Reserved (initialize to 0). */
		} s_callgate_hi; /* Call gate descriptor (high part) */

		struct __ATTR_PACKED {
			__UINT32_TYPE__ igh_offset3;      /* Bit 32-63 of the offset. */
			__UINT8_TYPE__  igh_reserved0;    /* Reserved (initialize to 0). */
			unsigned int    igh_zero: 4;      /* Always 0 */
			unsigned int    igh_reserved1: 4; /* Reserved (initialize to 0). */
			__UINT16_TYPE__ igh_reserved2;    /* Reserved (initialize to 0). */
		} s_intrgate_hi; /* Interrupt/Trap gate descriptor (high part) */

		struct __ATTR_PACKED {
			__UINT32_TYPE__ lh_base3;        /* Bit 32-63 of the LDT address. */
			__UINT8_TYPE__  lh_reserved0;    /* Reserved (initialize to 0). */
			unsigned int    lh_zero: 4;      /* Always 0 */
			unsigned int    lh_reserved1: 4; /* Reserved (initialize to 0). */
			__UINT16_TYPE__ lh_reserved2;    /* Reserved (initialize to 0). */
		} s_ldt_hi; /* LDT descriptor (high part) */
#endif /* __x86_64__ */
	};
};

__LOCAL __ATTR_LEAF __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__
__NOTHROW_NCX(segment_rdbase)(struct segment *__restrict __self) {
	__UINT32_TYPE__ __result;
	__result  = (__UINT32_TYPE__)__self->s_descriptor.d_base0;
	__result |= (__UINT32_TYPE__)__self->s_descriptor.d_base1 << 16;
	__result |= (__UINT32_TYPE__)__self->s_descriptor.d_base2 << 24;
	return __result;
}

__LOCAL __ATTR_LEAF __ATTR_NONNULL((1)) void
__NOTHROW_NCX(segment_wrbase)(struct segment *__restrict __self,
                              __UINT32_TYPE__ __val) {
	__self->s_descriptor.d_base0 = (__UINT16_TYPE__)(__val & 0xffff);
	__self->s_descriptor.d_base1 = (__UINT8_TYPE__)((__val >> 16) & 0xff);
	__self->s_descriptor.d_base2 = (__UINT8_TYPE__)((__val >> 24) & 0xff);
}


#ifdef __x86_64__
__LOCAL __ATTR_LEAF __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__
__NOTHROW_NCX(segment_rdbaseX)(struct segment *__restrict __self) {
	__UINT64_TYPE__ __result;
	__result = segment_rdbase(__self);
	__result |= (__UINT64_TYPE__)__self[1].s_tss_hi.th_base3 << 32;
	return __result;
}

__LOCAL __ATTR_LEAF __ATTR_NONNULL((1)) void
__NOTHROW_NCX(segment_wrbaseX)(struct segment *__restrict __self,
                               __UINT64_TYPE__ __val) {
	segment_wrbase(__self, (__UINT32_TYPE__)__val);
	__self[1].s_tss_hi.th_base3 = (__UINT32_TYPE__)(__val >> 32);
}

#else /* __x86_64__ */
#define segment_rdbaseX  segment_rdbase
#define segment_wrbaseX  segment_wrbase
#endif /* !__x86_64__ */




__LOCAL __ATTR_LEAF __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__
__NOTHROW_NCX(segment_rdlimit)(struct segment *__restrict __self) {
	__UINT32_TYPE__ __result;
	__result  = __self->s_descriptor.d_limit0;
	__result |= __self->s_descriptor.d_limit1 << 16;
	if (__self->s_descriptor.d_granularity)
		__result = (__result << 12) | 0xfff;
	return __result;
}
#endif /* __CC__ */




#ifdef __x86_64__
#define SIZEOF_IDT_SEGMENT 16
#else /* __x86_64__ */
#define SIZEOF_IDT_SEGMENT 8
#endif /* !__x86_64__ */

#ifdef __CC__
struct idt_segment {
	struct segment i_seg; /* IDT segment. */
#ifdef __x86_64__
	struct segment i_ext; /* High segment extension */
#endif /* __x86_64__ */
};
#endif /* __CC__ */


__DECL_END

#endif /* !_I386_KOS_KOS_KERNEL_SEGMENT_H */
