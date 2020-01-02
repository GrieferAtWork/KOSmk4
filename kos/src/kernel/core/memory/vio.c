/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
#ifndef GUARD_KERNEL_SRC_MEMORY_VIO_C
#define GUARD_KERNEL_SRC_MEMORY_VIO_C 1

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/types.h>
#include <kernel/vio.h>

#include <hybrid/unaligned.h>

#include <assert.h>
#include <string.h>

DECL_BEGIN

#ifdef CONFIG_VIO

PRIVATE ATTR_NORETURN void KCALL
vio_illegal_read(struct vio_args const *__restrict args, pos_t addr) {
	addr -= (pos_t)args->va_access_partoff;
	addr += (pos_t)args->va_access_pageid * PAGESIZE;
	THROW(E_SEGFAULT_NOTREADABLE, (uintptr_t)addr,
	      E_SEGFAULT_CONTEXT_VIO);
}

PRIVATE ATTR_NORETURN void KCALL
vio_illegal_write(struct vio_args const *__restrict args, pos_t addr) {
	addr -= (pos_t)args->va_access_partoff;
	addr += (pos_t)args->va_access_pageid * PAGESIZE;
	THROW(E_SEGFAULT_READONLY, (uintptr_t)addr,
	      E_SEGFAULT_CONTEXT_VIO | E_SEGFAULT_CONTEXT_WRITING);
}

#ifdef CONFIG_VIO_HAS_INT128_CMPXCH
PRIVATE ATTR_NORETURN void KCALL
vio_nonatomic_operation128(struct vio_args const *__restrict args,
                           pos_t addr, uint128_t oldval, uint128_t newval) {
	addr -= (pos_t)args->va_access_partoff;
	addr += (pos_t)args->va_access_pageid * PAGESIZE;
	if ((uintptr_t)(uintptr_t)addr & 15) {
		THROW(E_SEGFAULT_UNALIGNED, (uintptr_t)addr,
		      E_SEGFAULT_CONTEXT_VIO, 16);
	}
	THROW(E_SEGFAULT_NOTATOMIC, (uintptr_t)addr,
	      E_SEGFAULT_CONTEXT_VIO | E_SEGFAULT_CONTEXT_WRITING, 16,
	      uint128_vec64_significand(oldval, 0),
		  uint128_vec64_significand(oldval, 1),
		  uint128_vec64_significand(newval, 0),
		  uint128_vec64_significand(newval, 1));
}
#endif /* CONFIG_VIO_HAS_INT128_CMPXCH */

#if defined(CONFIG_VIO_HAS_QWORD) || defined(CONFIG_VIO_HAS_QWORD_CMPXCH)
PRIVATE ATTR_NORETURN void KCALL
vio_nonatomic_operation64(struct vio_args const *__restrict args,
                          pos_t addr, u64 oldval, u64 newval) {
	addr -= (pos_t)args->va_access_partoff;
	addr += (pos_t)args->va_access_pageid * PAGESIZE;
	if ((uintptr_t)(uintptr_t)addr & 7) {
		THROW(E_SEGFAULT_UNALIGNED, (uintptr_t)addr,
		      E_SEGFAULT_CONTEXT_VIO, 8);
	}
#ifdef __x86_64__
	THROW(E_SEGFAULT_NOTATOMIC, (uintptr_t)addr,
	      E_SEGFAULT_CONTEXT_VIO | E_SEGFAULT_CONTEXT_WRITING, 8,
	      oldval, 0, newval);
#else /* __x86_64__ */
	THROW(E_SEGFAULT_NOTATOMIC, (uintptr_t)addr,
	      E_SEGFAULT_CONTEXT_VIO | E_SEGFAULT_CONTEXT_WRITING, 8,
	      (u32)oldval, (u32)(oldval >> 32),
	      (u32)newval, (u32)(newval >> 32));
#endif /* !__x86_64__ */
}
#endif /* CONFIG_VIO_HAS_QWORD || CONFIG_VIO_HAS_QWORD_CMPXCH */

PRIVATE ATTR_NORETURN void KCALL
vio_nonatomic_operation32(struct vio_args const *__restrict args,
                          pos_t addr, u32 oldval, u32 newval) {
	addr -= (pos_t)args->va_access_partoff;
	addr += (pos_t)args->va_access_pageid * PAGESIZE;
	if ((uintptr_t)(uintptr_t)addr & 3) {
		THROW(E_SEGFAULT_UNALIGNED, (uintptr_t)addr,
		      E_SEGFAULT_CONTEXT_VIO, 4);
	}
	THROW(E_SEGFAULT_NOTATOMIC, (uintptr_t)addr,
	      E_SEGFAULT_CONTEXT_VIO | E_SEGFAULT_CONTEXT_WRITING, 4,
	      oldval, 0, newval);
}

PRIVATE ATTR_NORETURN void KCALL
vio_nonatomic_operation16(struct vio_args const *__restrict args,
                          pos_t addr, u16 oldval, u16 newval) {
	addr -= (pos_t)args->va_access_partoff;
	addr += (pos_t)args->va_access_pageid * PAGESIZE;
	if ((uintptr_t)(uintptr_t)addr & 2) {
		THROW(E_SEGFAULT_UNALIGNED, (uintptr_t)addr,
		      E_SEGFAULT_CONTEXT_VIO, 2);
	}
	THROW(E_SEGFAULT_NOTATOMIC, (uintptr_t)addr,
	      E_SEGFAULT_CONTEXT_VIO | E_SEGFAULT_CONTEXT_WRITING, 2,
	      oldval, 0, newval);
}

PRIVATE ATTR_NORETURN void KCALL
vio_nonatomic_operation8(struct vio_args const *__restrict args,
                         pos_t addr, u8 oldval, u8 newval) {
	addr -= (pos_t)args->va_access_partoff;
	addr += (pos_t)args->va_access_pageid * PAGESIZE;
	THROW(E_SEGFAULT_NOTATOMIC, (uintptr_t)addr,
	      E_SEGFAULT_CONTEXT_VIO | E_SEGFAULT_CONTEXT_WRITING, 1,
	      oldval, 0, newval);
}

typedef union ATTR_PACKED {
	u16 w;
	u16 w_0;
	u8 b[2];
} word;

typedef union ATTR_PACKED {
	u32 l;
	u32 l_0;
	u16 w[2];
	u8 b[4];
	struct ATTR_PACKED {
		u16 w_0; /* WORD @ +0 */
		u16 w_2; /* WORD @ +2 */
	};
	struct ATTR_PACKED {
		u8 __pad0;
		u16 w_1; /* WORD @ +1 */
	};
} dword;

typedef union ATTR_PACKED {
	u64 q;
	u64 q_0;
	u32 l[2];
	u16 w[4];
	u8 b[8];
	struct ATTR_PACKED {
		u16 w_0; /* WORD @ +0 */
		u16 w_2; /* WORD @ +2 */
		u16 w_4; /* WORD @ +4 */
		u16 w_6; /* WORD @ +6 */
	};
	struct ATTR_PACKED {
		u32 l_0; /* DWORD @ +0 */
		u32 l_4; /* DWORD @ +4 */
	};
	struct ATTR_PACKED {
		u8 __pad0;
		u16 w_1; /* WORD @ +1 */
		u16 w_3; /* WORD @ +3 */
		u16 w_5; /* WORD @ +5 */
	};
	struct ATTR_PACKED {
		u8 __pad1;
		u32 l_1; /* DWORD @ +1 */
	};
	struct ATTR_PACKED {
		u16 __pad2;
		u32 l_2; /* DWORD @ +2 */
	};
	struct ATTR_PACKED {
		u8 __pad3[3];
		u32 l_3; /* DWORD @ +3 */
	};
} qword;

typedef union ATTR_PACKED {
	u64 q[2];
	u32 l[4];
	u16 w[8];
	u8 b[16];
	struct ATTR_PACKED {
		u16 w_0;  /* WORD @ +0 */
		u16 w_2;  /* WORD @ +2 */
		u16 w_4;  /* WORD @ +4 */
		u16 w_6;  /* WORD @ +6 */
		u16 w_8;  /* WORD @ +8 */
		u16 w_10; /* WORD @ +10 */
		u16 w_12; /* WORD @ +12 */
		u16 w_14; /* WORD @ +14 */
	};
	struct ATTR_PACKED {
		u32 l_0;  /* DWORD @ +0 */
		u32 l_4;  /* DWORD @ +4 */
		u32 l_8;  /* DWORD @ +8 */
		u32 l_12; /* DWORD @ +12 */
	};
	struct ATTR_PACKED {
		u64 q_0; /* QWORD @ +0 */
		u64 q_8; /* QWORD @ +8 */
	};
	struct ATTR_PACKED {
		u8 __pad0;
		u16 w_1;  /* WORD @ +1 */
		u16 w_3;  /* WORD @ +3 */
		u16 w_5;  /* WORD @ +5 */
		u16 w_7;  /* WORD @ +7 */
		u16 w_9;  /* WORD @ +9 */
		u16 w_11; /* WORD @ +11 */
		u16 w_13; /* WORD @ +13 */
	};
	struct ATTR_PACKED {
		u8 __pad1;
		u32 l_1; /* DWORD @ +1 */
		u32 l_5; /* DWORD @ +5 */
		u32 l_9; /* DWORD @ +9 */
	};
	struct ATTR_PACKED {
		u16 __pad2;
		u32 l_2;  /* DWORD @ +2 */
		u32 l_6;  /* DWORD @ +6 */
		u32 l_10; /* DWORD @ +10 */
	};
	struct ATTR_PACKED {
		u8 __pad3[3];
		u32 l_3;  /* DWORD @ +3 */
		u32 l_7;  /* DWORD @ +7 */
		u32 l_11; /* DWORD @ +11 */
	};
	struct ATTR_PACKED {
		u8 __pad5;
		u64 q_1; /* QWORD @ +1 */
	};
	struct ATTR_PACKED {
		u16 __pad6;
		u64 q_2; /* QWORD @ +2 */
	};
	struct ATTR_PACKED {
		u8 __pad7[3];
		u64 q_3; /* QWORD @ +3 */
	};
	struct ATTR_PACKED {
		u32 __pad8;
		u64 q_4; /* QWORD @ +4 */
	};
	struct ATTR_PACKED {
		u8 __pad9[5];
		u64 q_5; /* QWORD @ +5 */
	};
	struct ATTR_PACKED {
		u8 __pad10[6];
		u64 q_6; /* QWORD @ +6 */
	};
	struct ATTR_PACKED {
		u8 __pad11[7];
		u64 q_7; /* QWORD @ +7 */
	};
} xword; /* Hex-word (16-bit) */


#define B(off)   ((x).b[off])
#define W(off)   ((x).w_##off)
#define L(off)   ((x).l_##off)
#define Q(off)   ((x).q_##off)

#ifdef CONFIG_VIO_HAS_QWORD
#define IQ(...) __VA_ARGS__
#else
#define IQ(...) /* nothing */
#endif

/* Naming: [BWLQ][MASK] where MASK is the a mask `addr & mask' describing an offset into `x' */
#define B1     x.b[(uintptr_t)addr & 1]
#define B3     x.b[(uintptr_t)addr & 3]
#define B7     x.b[(uintptr_t)addr & 7]

#define W2     x.w[((uintptr_t)addr & 2) >> 1]
#define W3     (*(u16 *)((u8 *)&(x) + ((uintptr_t)addr & 3)))
#define W6     x.w[((uintptr_t)addr & 6) >> 1]
#define W7     (*(u16 *)((u8 *)&(x) + ((uintptr_t)addr & 7)))

#define L3     (*(u32 *)((u8 *)&(x) + ((uintptr_t)addr & 3)))
#define L4     x.l[((uintptr_t)addr & 4) >> 2]
#define L7     (*(u32 *)((u8 *)&(x) + ((uintptr_t)addr & 7)))

#define Q3     (*(u64 *)((u8 *)&(x) + ((uintptr_t)addr & 3)))
#define Q7     (*(u64 *)((u8 *)&(x) + ((uintptr_t)addr & 7)))

/* Aligned base-addresses */
#define AW     (addr & ~1) /* word-aligned */
#define AL     (addr & ~3) /* dword-aligned */
#define AQ     (addr & ~7) /* qword-aligned */

/* The max address mask that could ever be relevant. */
#ifdef CONFIG_VIO_HAS_QWORD
#define MMASK    7
#define CASEB    case 1: case 3: case 5: case 7:
#define CASEW    case 2: case 6:
#define CASEL    case 4:
#define CASEQ    case 0:
#else /* CONFIG_VIO_HAS_QWORD */
#define MMASK  3
#define CASEB    case 1: case 3:
#define CASEW    case 2:
#define CASEL    case 0:
#define CASEQ    /* nothing */
#endif /* !CONFIG_VIO_HAS_QWORD */




/* Invoke VIO callbacks, automatically substituting operators for one-another.
 * If an operation is impossible, these functions will throw a SEGFAULT exception. */
PUBLIC NONNULL((1)) u8 KCALL vio_readb(struct vio_args *__restrict args, pos_t addr) {
	struct vm_datablock_type_vio const *type = args->va_type;
	if (type->dtv_read.f_byte) return (*type->dtv_read.f_byte)(args, addr);
	if (type->dtv_read.f_word) { word x = { (*type->dtv_read.f_word)(args, AW) }; return B1; }
	if (type->dtv_read.f_dword) { dword x = { (*type->dtv_read.f_dword)(args, AL) }; return B3; }
	IQ(if (type->dtv_read.f_qword) { qword x = { (*type->dtv_read.f_qword)(args, AQ) }; return B7; })
	if (type->dtv_cmpxch.f_byte) return (*type->dtv_cmpxch.f_byte)(args, addr, 0, 0, true);
	if (type->dtv_cmpxch.f_word) { word x = { (*type->dtv_cmpxch.f_word)(args, AW, 0, 0, true) }; return B1; }
	if (type->dtv_cmpxch.f_dword) { dword x = { (*type->dtv_cmpxch.f_dword)(args, AL, 0, 0, true) }; return B3; }
	IQ(if (type->dtv_cmpxch.f_qword) { qword x = { (*type->dtv_cmpxch.f_qword)(args, AQ, 0, 0, true) }; return B7; })
	if (type->dtv_add.f_byte) return (*type->dtv_add.f_byte)(args, addr, 0, true);
	if (type->dtv_add.f_word) { word x = { (*type->dtv_add.f_word)(args, AW, 0, true) }; return B1; }
	if (type->dtv_add.f_dword) { dword x = { (*type->dtv_add.f_dword)(args, AL, 0, true) }; return B3; }
	IQ(if (type->dtv_add.f_qword) { qword x = { (*type->dtv_add.f_qword)(args, AQ, 0, true) }; return B7; })
	if (type->dtv_sub.f_byte) return (*type->dtv_sub.f_byte)(args, addr, 0, true);
	if (type->dtv_sub.f_word) { word x = { (*type->dtv_sub.f_word)(args, AW, 0, true) }; return B1; }
	if (type->dtv_sub.f_dword) { dword x = { (*type->dtv_sub.f_dword)(args, AL, 0, true) }; return B3; }
	IQ(if (type->dtv_sub.f_qword) { qword x = { (*type->dtv_sub.f_qword)(args, AQ, 0, true) }; return B7; })
	if (type->dtv_and.f_byte) return (*type->dtv_and.f_byte)(args, addr, (u8)~0, true);
	if (type->dtv_and.f_word) { word x = { (*type->dtv_and.f_word)(args, AW, (u16)~0, true) }; return B1; }
	if (type->dtv_and.f_dword) { dword x = { (*type->dtv_and.f_dword)(args, AL, (u32)~0, true) }; return B3; }
	IQ(if (type->dtv_and.f_qword) { qword x = { (*type->dtv_and.f_qword)(args, AQ, (u64)~0, true) }; return B7; })
	if (type->dtv_or.f_byte) return (*type->dtv_or.f_byte)(args, addr, 0, true);
	if (type->dtv_or.f_word) { word x = { (*type->dtv_or.f_word)(args, AW, 0, true) }; return B1; }
	if (type->dtv_or.f_dword) { dword x = { (*type->dtv_or.f_dword)(args, AL, 0, true) }; return B3; }
	IQ(if (type->dtv_or.f_qword) { qword x = { (*type->dtv_or.f_qword)(args, AQ, 0, true) }; return B7; })
	if (type->dtv_xor.f_byte) return (*type->dtv_xor.f_byte)(args, addr, 0, true);
	if (type->dtv_xor.f_word) { word x = { (*type->dtv_xor.f_word)(args, AW, 0, true) }; return B1; }
	if (type->dtv_xor.f_dword) { dword x = { (*type->dtv_xor.f_dword)(args, AL, 0, true) }; return B3; }
	IQ(if (type->dtv_xor.f_qword) { qword x = { (*type->dtv_xor.f_qword)(args, AQ, 0, true) }; return B7; })
	vio_illegal_read(args, addr);
}



PUBLIC NONNULL((1)) u16 KCALL vio_readw(struct vio_args *__restrict args, pos_t addr) {
	struct vm_datablock_type_vio const *type = args->va_type;
	if (((uintptr_t)addr & 1) != 1) {
		if (type->dtv_read.f_word) return (*type->dtv_read.f_word)(args, addr);
		if (type->dtv_cmpxch.f_word) return (*type->dtv_cmpxch.f_word)(args, addr, 0, 0, true);
		if (type->dtv_add.f_word) return (*type->dtv_add.f_word)(args, addr, 0, true);
		if (type->dtv_sub.f_word) return (*type->dtv_sub.f_word)(args, addr, 0, true);
		if (type->dtv_and.f_word) return (*type->dtv_and.f_word)(args, addr, (u16)~0, true);
		if (type->dtv_or.f_word) return (*type->dtv_or.f_word)(args, addr, 0, true);
		if (type->dtv_xor.f_word) return (*type->dtv_xor.f_word)(args, addr, 0, true);
	}
	if (((uintptr_t)addr & 3) != 3) {
		if (type->dtv_read.f_dword) { dword x = { (*type->dtv_read.f_dword)(args, AL) }; return W3; }
		if (type->dtv_cmpxch.f_dword) { dword x = { (*type->dtv_cmpxch.f_dword)(args, AL, 0, 0, true) }; return W3; }
		if (type->dtv_add.f_dword) { dword x = { (*type->dtv_add.f_dword)(args, AL, 0, true) }; return W3; }
		if (type->dtv_sub.f_dword) { dword x = { (*type->dtv_sub.f_dword)(args, AL, 0, true) }; return W3; }
		if (type->dtv_and.f_dword) { dword x = { (*type->dtv_and.f_dword)(args, AL, (u32)~0, true) }; return W3; }
		if (type->dtv_or.f_dword) { dword x = { (*type->dtv_or.f_dword)(args, AL, 0, true) }; return W3; }
		if (type->dtv_xor.f_dword) { dword x = { (*type->dtv_xor.f_dword)(args, AL, 0, true) }; return W3; }
	}
#ifdef CONFIG_VIO_HAS_QWORD
	if (((uintptr_t)addr & 7) != 7) {
		if (type->dtv_read.f_qword) { qword x = { (*type->dtv_read.f_qword)(args, AQ) }; return W7; }
		if (type->dtv_cmpxch.f_qword) { qword x = { (*type->dtv_cmpxch.f_qword)(args, AQ, 0, 0, true) }; return W7; }
		if (type->dtv_add.f_qword) { qword x = { (*type->dtv_add.f_qword)(args, AQ, 0, true) }; return W7; }
		if (type->dtv_sub.f_qword) { qword x = { (*type->dtv_sub.f_qword)(args, AQ, 0, true) }; return W7; }
		if (type->dtv_and.f_qword) { qword x = { (*type->dtv_and.f_qword)(args, AQ, (u64)~0, true) }; return W7; }
		if (type->dtv_or.f_qword) { qword x = { (*type->dtv_or.f_qword)(args, AQ, 0, true) }; return W7; }
		if (type->dtv_xor.f_qword) { qword x = { (*type->dtv_xor.f_qword)(args, AQ, 0, true) }; return W7; }
	}
#endif /* CONFIG_VIO_HAS_QWORD */
#define READ_2X_READB(func, ...)                                      \
	if (type->func.f_byte) {                                          \
		word x;                                                       \
		x.b[0] = (*type->func.f_byte)(args, addr, ##__VA_ARGS__);     \
		x.b[1] = (*type->func.f_byte)(args, addr + 1, ##__VA_ARGS__); \
		return x.w;                                                   \
	}
	READ_2X_READB(dtv_read)
	READ_2X_READB(dtv_cmpxch, 0, 0, true)
	READ_2X_READB(dtv_add, 0, true)
	READ_2X_READB(dtv_sub, 0, true)
	READ_2X_READB(dtv_and, (u8)~0, true)
	READ_2X_READB(dtv_or, 0, true)
	READ_2X_READB(dtv_xor, 0, true)
#undef READ_2X_READB
#define READ_2X_READW(func, ...)                                      \
	if (type->func.f_word) {                                          \
		dword x;                                                      \
		x.w[0] = (*type->func.f_word)(args, addr - 1, ##__VA_ARGS__); \
		x.w[1] = (*type->func.f_word)(args, addr + 1, ##__VA_ARGS__); \
		return x.w_1;                                                 \
	}
	if (((uintptr_t)addr & 1) == 1) {
		READ_2X_READW(dtv_read)
		READ_2X_READW(dtv_cmpxch, 0, 0, true)
		READ_2X_READW(dtv_add, 0, true)
		READ_2X_READW(dtv_sub, 0, true)
		READ_2X_READW(dtv_and, (u16)~0, true)
		READ_2X_READW(dtv_or, 0, true)
		READ_2X_READW(dtv_xor, 0, true)
	}
#undef READ_2X_READW
	if (((uintptr_t)addr & 3) == 3) {
#define READ_2X_READL(func, ...)                                           \
		if (type->func.f_dword) {                                          \
			qword x;                                                       \
			x.l[0] = (*type->func.f_dword)(args, addr - 3, ##__VA_ARGS__); \
			x.l[1] = (*type->func.f_dword)(args, addr + 1, ##__VA_ARGS__); \
			return x.w_3;                                                  \
		}
		READ_2X_READL(dtv_read)
		READ_2X_READL(dtv_cmpxch, 0, 0, true)
		READ_2X_READL(dtv_add, 0, true)
		READ_2X_READL(dtv_sub, 0, true)
		READ_2X_READL(dtv_and, (u32)~0, true)
		READ_2X_READL(dtv_or, 0, true)
		READ_2X_READL(dtv_xor, 0, true)
	}
#undef READ_2X_READL
#ifdef CONFIG_VIO_HAS_QWORD
	if (((uintptr_t)addr & 7) == 7) {
#define READ_2X_READQ(func, ...)                                           \
		if (type->func.f_qword) {                                          \
			xword x;                                                       \
			x.q[0] = (*type->func.f_qword)(args, addr - 3, ##__VA_ARGS__); \
			x.q[1] = (*type->func.f_qword)(args, addr + 1, ##__VA_ARGS__); \
			return x.w_7;                                                  \
		}
		READ_2X_READQ(dtv_read)
		READ_2X_READQ(dtv_cmpxch, 0, 0, true)
		READ_2X_READQ(dtv_add, 0, true)
		READ_2X_READQ(dtv_sub, 0, true)
		READ_2X_READQ(dtv_and, (u64)~0, true)
		READ_2X_READQ(dtv_or, 0, true)
		READ_2X_READQ(dtv_xor, 0, true)
	}
#undef READ_2X_READQ
#endif /* CONFIG_VIO_HAS_QWORD */
	vio_illegal_read(args, addr);
}

PUBLIC NONNULL((1)) u32 KCALL vio_readl(struct vio_args *__restrict args, pos_t addr) {
	struct vm_datablock_type_vio const *type = args->va_type;
	if (((uintptr_t)addr & 3) == 0) {
		if (type->dtv_read.f_dword) return (*type->dtv_read.f_dword)(args, addr);
		if (type->dtv_cmpxch.f_dword) return (*type->dtv_cmpxch.f_dword)(args, addr, 0, 0, true);
		if (type->dtv_add.f_dword) return (*type->dtv_add.f_dword)(args, addr, 0, true);
		if (type->dtv_sub.f_dword) return (*type->dtv_sub.f_dword)(args, addr, 0, true);
		if (type->dtv_and.f_dword) return (*type->dtv_and.f_dword)(args, addr, (u32)~0, true);
		if (type->dtv_or.f_dword) return (*type->dtv_or.f_dword)(args, addr, 0, true);
		if (type->dtv_xor.f_dword) return (*type->dtv_xor.f_dword)(args, addr, 0, true);
	}
#ifdef CONFIG_VIO_HAS_QWORD
	if (((uintptr_t)addr & 7) <= 3) {
		if (type->dtv_read.f_qword) { qword x = { (*type->dtv_read.f_qword)(args, AQ) }; return L7; }
		if (type->dtv_cmpxch.f_qword) { qword x = { (*type->dtv_cmpxch.f_qword)(args, AQ, 0, 0, true) }; return L7; }
		if (type->dtv_add.f_qword) { qword x = { (*type->dtv_add.f_qword)(args, AQ, 0, true) }; return L7; }
		if (type->dtv_sub.f_qword) { qword x = { (*type->dtv_sub.f_qword)(args, AQ, 0, true) }; return L7; }
		if (type->dtv_and.f_qword) { qword x = { (*type->dtv_and.f_qword)(args, AQ, (u64)~0, true) }; return L7; }
		if (type->dtv_or.f_qword) { qword x = { (*type->dtv_or.f_qword)(args, AQ, 0, true) }; return L7; }
		if (type->dtv_xor.f_qword) { qword x = { (*type->dtv_xor.f_qword)(args, AQ, 0, true) }; return L7; }
	}
#endif /* CONFIG_VIO_HAS_QWORD */
#define READ_2X_READW(func, ...)                                    \
	if (type->func.f_word) {                                        \
		dword x;                                                    \
		x.w[0] = (*type->func.f_word)(args, AW, ##__VA_ARGS__);     \
		x.w[1] = (*type->func.f_word)(args, AW + 2, ##__VA_ARGS__); \
		return x.l;                                                 \
	}
	if (((uintptr_t)addr & 1) != 1) {
		READ_2X_READW(dtv_read)
		READ_2X_READW(dtv_cmpxch, 0, 0, true)
		READ_2X_READW(dtv_add, 0, true)
		READ_2X_READW(dtv_sub, 0, true)
		READ_2X_READW(dtv_and, (u16)~0, true)
		READ_2X_READW(dtv_or, 0, true)
		READ_2X_READW(dtv_xor, 0, true)
	}
#undef READ_2X_READW
#define READ_2X_READL(func, ...)                                     \
	if (type->func.f_dword) {                                        \
		qword x;                                                     \
		x.l[0] = (*type->func.f_dword)(args, AL, ##__VA_ARGS__);     \
		x.l[1] = (*type->func.f_dword)(args, AL + 4, ##__VA_ARGS__); \
		return L3;                                                   \
	}
	READ_2X_READL(dtv_read)
	READ_2X_READL(dtv_cmpxch, 0, 0, true)
	READ_2X_READL(dtv_add, 0, true)
	READ_2X_READL(dtv_sub, 0, true)
	READ_2X_READL(dtv_and, (u32)~0, true)
	READ_2X_READL(dtv_or, 0, true)
	READ_2X_READL(dtv_xor, 0, true)
#undef READ_2X_READL
#ifdef CONFIG_VIO_HAS_QWORD
#define READ_2X_READQ(func, ...)                                     \
	if (type->func.f_qword) {                                        \
		xword x;                                                     \
		x.q[0] = (*type->func.f_qword)(args, AQ, ##__VA_ARGS__);     \
		x.q[1] = (*type->func.f_qword)(args, AQ + 8, ##__VA_ARGS__); \
		return L7;                                                   \
	}
	READ_2X_READQ(dtv_read)
	READ_2X_READQ(dtv_cmpxch, 0, 0, true)
	READ_2X_READQ(dtv_add, 0, true)
	READ_2X_READQ(dtv_sub, 0, true)
	READ_2X_READQ(dtv_and, (u64)~0, true)
	READ_2X_READQ(dtv_or, 0, true)
	READ_2X_READQ(dtv_xor, 0, true)
#undef READ_2X_READQ
#endif /* CONFIG_VIO_HAS_QWORD */
#define READ_3X_READW(func, ...)                                      \
	if (type->func.f_word) {                                          \
		qword x;                                                      \
		x.w[0] = (*type->func.f_word)(args, addr - 1, ##__VA_ARGS__); \
		x.w[1] = (*type->func.f_word)(args, addr + 1, ##__VA_ARGS__); \
		x.w[2] = (*type->func.f_word)(args, addr + 3, ##__VA_ARGS__); \
		return x.l_1;                                                 \
	}
	READ_3X_READW(dtv_read)
	READ_3X_READW(dtv_cmpxch, 0, 0, true)
	READ_3X_READW(dtv_add, 0, true)
	READ_3X_READW(dtv_sub, 0, true)
	READ_3X_READW(dtv_and, (u16)~0, true)
	READ_3X_READW(dtv_or, 0, true)
	READ_3X_READW(dtv_xor, 0, true)
#undef READ_3X_READW
#define READ_4X_READB(func, ...)                                      \
	if (type->func.f_byte) {                                          \
		dword x;                                                      \
		x.b[0] = (*type->func.f_byte)(args, addr + 0, ##__VA_ARGS__); \
		x.b[1] = (*type->func.f_byte)(args, addr + 1, ##__VA_ARGS__); \
		x.b[2] = (*type->func.f_byte)(args, addr + 2, ##__VA_ARGS__); \
		x.b[3] = (*type->func.f_byte)(args, addr + 3, ##__VA_ARGS__); \
		return x.l;                                                   \
	}
	READ_4X_READB(dtv_read)
	READ_4X_READB(dtv_cmpxch, 0, 0, true)
	READ_4X_READB(dtv_add, 0, true)
	READ_4X_READB(dtv_sub, 0, true)
	READ_4X_READB(dtv_and, (u8)~0, true)
	READ_4X_READB(dtv_or, 0, true)
	READ_4X_READB(dtv_xor, 0, true)
#undef READ_4X_READB
	vio_illegal_read(args, addr);
}

PUBLIC NONNULL((1)) u16 KCALL vio_readw_aligned(struct vio_args *__restrict args, pos_t addr) {
	struct vm_datablock_type_vio const *type = args->va_type;
	assert(((uintptr_t)addr & 1) == 0);
	if (type->dtv_read.f_word) return (*type->dtv_read.f_word)(args, addr);
	if (type->dtv_cmpxch.f_word) return (*type->dtv_cmpxch.f_word)(args, addr, 0, 0, true);
	if (type->dtv_add.f_word) return (*type->dtv_add.f_word)(args, addr, 0, true);
	if (type->dtv_sub.f_word) return (*type->dtv_sub.f_word)(args, addr, 0, true);
	if (type->dtv_and.f_word) return (*type->dtv_and.f_word)(args, addr, (u16)~0, true);
	if (type->dtv_or.f_word) return (*type->dtv_or.f_word)(args, addr, 0, true);
	if (type->dtv_xor.f_word) return (*type->dtv_xor.f_word)(args, addr, 0, true);
	if (type->dtv_read.f_dword) { dword x = { (*type->dtv_read.f_dword)(args, AL) }; return W2; }
	if (type->dtv_cmpxch.f_dword) { dword x = { (*type->dtv_cmpxch.f_dword)(args, AL, 0, 0, true) }; return W2; }
	if (type->dtv_add.f_dword) { dword x = { (*type->dtv_add.f_dword)(args, AL, 0, true) }; return W2; }
	if (type->dtv_sub.f_dword) { dword x = { (*type->dtv_sub.f_dword)(args, AL, 0, true) }; return W2; }
	if (type->dtv_and.f_dword) { dword x = { (*type->dtv_and.f_dword)(args, AL, (u32)~0, true) }; return W2; }
	if (type->dtv_or.f_dword) { dword x = { (*type->dtv_or.f_dword)(args, AL, 0, true) }; return W2; }
	if (type->dtv_xor.f_dword) { dword x = { (*type->dtv_xor.f_dword)(args, AL, 0, true) }; return W2; }
#ifdef CONFIG_VIO_HAS_QWORD
	if (type->dtv_read.f_qword) { qword x = { (*type->dtv_read.f_qword)(args, AQ) }; return W6; }
	if (type->dtv_cmpxch.f_qword) { qword x = { (*type->dtv_cmpxch.f_qword)(args, AQ, 0, 0, true) }; return W6; }
	if (type->dtv_add.f_qword) { qword x = { (*type->dtv_add.f_qword)(args, AQ, 0, true) }; return W6; }
	if (type->dtv_sub.f_qword) { qword x = { (*type->dtv_sub.f_qword)(args, AQ, 0, true) }; return W6; }
	if (type->dtv_and.f_qword) { qword x = { (*type->dtv_and.f_qword)(args, AQ, (u64)~0, true) }; return W6; }
	if (type->dtv_or.f_qword) { qword x = { (*type->dtv_or.f_qword)(args, AQ, 0, true) }; return W6; }
	if (type->dtv_xor.f_qword) { qword x = { (*type->dtv_xor.f_qword)(args, AQ, 0, true) }; return W6; }
#endif /* CONFIG_VIO_HAS_QWORD */
#define READ_2X_READB(func, ...)                                      \
	if (type->func.f_byte) {                                          \
		word x;                                                       \
		x.b[0] = (*type->func.f_byte)(args, addr, ##__VA_ARGS__);     \
		x.b[1] = (*type->func.f_byte)(args, addr + 1, ##__VA_ARGS__); \
		return x.w;                                                   \
	}
	READ_2X_READB(dtv_read)
	READ_2X_READB(dtv_cmpxch, 0, 0, true)
	READ_2X_READB(dtv_add, 0, true)
	READ_2X_READB(dtv_sub, 0, true)
	READ_2X_READB(dtv_and, (u8)~0, true)
	READ_2X_READB(dtv_or, 0, true)
	READ_2X_READB(dtv_xor, 0, true)
#undef READ_2X_READB
	vio_illegal_read(args, addr);
}

PUBLIC NONNULL((1)) u32 KCALL vio_readl_aligned(struct vio_args *__restrict args, pos_t addr) {
	struct vm_datablock_type_vio const *type = args->va_type;
	assert(((uintptr_t)addr & 3) == 0);
	if (type->dtv_read.f_dword) return (*type->dtv_read.f_dword)(args, addr);
	if (type->dtv_cmpxch.f_dword) return (*type->dtv_cmpxch.f_dword)(args, addr, 0, 0, true);
	if (type->dtv_add.f_dword) return (*type->dtv_add.f_dword)(args, addr, 0, true);
	if (type->dtv_sub.f_dword) return (*type->dtv_sub.f_dword)(args, addr, 0, true);
	if (type->dtv_and.f_dword) return (*type->dtv_and.f_dword)(args, addr, (u16)~0, true);
	if (type->dtv_or.f_dword) return (*type->dtv_or.f_dword)(args, addr, 0, true);
	if (type->dtv_xor.f_dword) return (*type->dtv_xor.f_dword)(args, addr, 0, true);
#ifdef CONFIG_VIO_HAS_QWORD
	if (type->dtv_read.f_qword) { qword x = { (*type->dtv_read.f_qword)(args, AQ) }; return L4; }
	if (type->dtv_cmpxch.f_qword) { qword x = { (*type->dtv_cmpxch.f_qword)(args, AQ, 0, 0, true) }; return L4; }
	if (type->dtv_add.f_qword) { qword x = { (*type->dtv_add.f_qword)(args, AQ, 0, true) }; return L4; }
	if (type->dtv_sub.f_qword) { qword x = { (*type->dtv_sub.f_qword)(args, AQ, 0, true) }; return L4; }
	if (type->dtv_and.f_qword) { qword x = { (*type->dtv_and.f_qword)(args, AQ, (u64)~0, true) }; return L4; }
	if (type->dtv_or.f_qword) { qword x = { (*type->dtv_or.f_qword)(args, AQ, 0, true) }; return L4; }
	if (type->dtv_xor.f_qword) { qword x = { (*type->dtv_xor.f_qword)(args, AQ, 0, true) }; return L4; }
#endif /* CONFIG_VIO_HAS_QWORD */
#define READ_2X_READW(func, ...)                                      \
	if (type->func.f_word) {                                          \
		dword x;                                                      \
		x.w[0] = (*type->func.f_word)(args, addr + 0, ##__VA_ARGS__); \
		x.w[1] = (*type->func.f_word)(args, addr + 2, ##__VA_ARGS__); \
		return x.l;                                                   \
	}
	READ_2X_READW(dtv_read)
	READ_2X_READW(dtv_cmpxch, 0, 0, true)
	READ_2X_READW(dtv_add, 0, true)
	READ_2X_READW(dtv_sub, 0, true)
	READ_2X_READW(dtv_and, (u8)~0, true)
	READ_2X_READW(dtv_or, 0, true)
	READ_2X_READW(dtv_xor, 0, true)
#undef READ_2X_READW
#define READ_4X_READB(func, ...)                                      \
	if (type->func.f_byte) {                                          \
		dword x;                                                      \
		x.b[0] = (*type->func.f_byte)(args, addr + 0, ##__VA_ARGS__); \
		x.b[1] = (*type->func.f_byte)(args, addr + 1, ##__VA_ARGS__); \
		x.b[2] = (*type->func.f_byte)(args, addr + 2, ##__VA_ARGS__); \
		x.b[3] = (*type->func.f_byte)(args, addr + 3, ##__VA_ARGS__); \
		return x.l;                                                   \
	}
	READ_4X_READB(dtv_read)
	READ_4X_READB(dtv_cmpxch, 0, 0, true)
	READ_4X_READB(dtv_add, 0, true)
	READ_4X_READB(dtv_sub, 0, true)
	READ_4X_READB(dtv_and, (u8)~0, true)
	READ_4X_READB(dtv_or, 0, true)
	READ_4X_READB(dtv_xor, 0, true)
#undef READ_4X_READB
	vio_illegal_read(args, addr);
}


#ifdef CONFIG_VIO_HAS_QWORD
PUBLIC NONNULL((1)) u64 KCALL vio_readq(struct vio_args *__restrict args, pos_t addr) {
	struct vm_datablock_type_vio const *type = args->va_type;
	if (((uintptr_t)addr & 7) == 0) {
		if (type->dtv_read.f_qword) return (*type->dtv_read.f_qword)(args, addr);
		if (type->dtv_cmpxch.f_qword) return (*type->dtv_cmpxch.f_qword)(args, addr, 0, 0, true);
		if (type->dtv_add.f_qword) return (*type->dtv_add.f_qword)(args, addr, 0, true);
		if (type->dtv_sub.f_qword) return (*type->dtv_sub.f_qword)(args, addr, 0, true);
		if (type->dtv_and.f_qword) return (*type->dtv_and.f_qword)(args, addr, (u64)~0, true);
		if (type->dtv_or.f_qword) return (*type->dtv_or.f_qword)(args, addr, 0, true);
		if (type->dtv_xor.f_qword) return (*type->dtv_xor.f_qword)(args, addr, 0, true);
	}
#define READ_2X_READL(func, ...)                                       \
	if (type->func.f_dword) {                                          \
		qword x;                                                       \
		x.l[0] = (*type->func.f_dword)(args, addr, ##__VA_ARGS__);     \
		x.l[1] = (*type->func.f_dword)(args, addr + 4, ##__VA_ARGS__); \
		return x.q;                                                    \
	}
	if (((uintptr_t)addr & 3) == 0) {
		READ_2X_READL(dtv_read)
		READ_2X_READL(dtv_cmpxch, 0, 0, true)
		READ_2X_READL(dtv_add, 0, true)
		READ_2X_READL(dtv_sub, 0, true)
		READ_2X_READL(dtv_and, (u32)~0, true)
		READ_2X_READL(dtv_or, 0, true)
		READ_2X_READL(dtv_xor, 0, true)
	}
#undef READ_2X_READL
#define READ_2X_READQ(func, ...)                                     \
	if (type->func.f_qword) {                                        \
		xword x;                                                     \
		x.q[0] = (*type->func.f_qword)(args, AQ, ##__VA_ARGS__);     \
		x.q[1] = (*type->func.f_qword)(args, AQ + 8, ##__VA_ARGS__); \
		return Q7;                                                   \
	}
	READ_2X_READQ(dtv_read)
	READ_2X_READQ(dtv_cmpxch, 0, 0, true)
	READ_2X_READQ(dtv_add, 0, true)
	READ_2X_READQ(dtv_sub, 0, true)
	READ_2X_READQ(dtv_and, (u64)~0, true)
	READ_2X_READQ(dtv_or, 0, true)
	READ_2X_READQ(dtv_xor, 0, true)
#undef READ_2X_READQ
#define READ_3X_READL(func, ...)                                     \
	if (type->func.f_dword) {                                        \
		xword x;                                                     \
		x.l[0] = (*type->func.f_dword)(args, AL, ##__VA_ARGS__);     \
		x.l[1] = (*type->func.f_dword)(args, AL + 4, ##__VA_ARGS__); \
		x.l[2] = (*type->func.f_dword)(args, AL + 8, ##__VA_ARGS__); \
		return Q3;                                                   \
	}
	READ_3X_READL(dtv_read)
	READ_3X_READL(dtv_cmpxch, 0, 0, true)
	READ_3X_READL(dtv_add, 0, true)
	READ_3X_READL(dtv_sub, 0, true)
	READ_3X_READL(dtv_and, (u32)~0, true)
	READ_3X_READL(dtv_or, 0, true)
	READ_3X_READL(dtv_xor, 0, true)
#undef READ_3X_READL
#define READ_4X_READW(func, ...)                                      \
	if (type->func.f_word) {                                          \
		qword x;                                                      \
		x.w[0] = (*type->func.f_word)(args, addr, ##__VA_ARGS__);     \
		x.w[1] = (*type->func.f_word)(args, addr + 2, ##__VA_ARGS__); \
		x.w[2] = (*type->func.f_word)(args, addr + 4, ##__VA_ARGS__); \
		x.w[3] = (*type->func.f_word)(args, addr + 6, ##__VA_ARGS__); \
		return x.q;                                                   \
	}
	if (((uintptr_t)addr & 1) == 0) {
		READ_4X_READW(dtv_read)
		READ_4X_READW(dtv_cmpxch, 0, 0, true)
		READ_4X_READW(dtv_add, 0, true)
		READ_4X_READW(dtv_sub, 0, true)
		READ_4X_READW(dtv_and, (u16)~0, true)
		READ_4X_READW(dtv_or, 0, true)
		READ_4X_READW(dtv_xor, 0, true)
	}
#undef READ_4X_READW
#define READ_5X_READW(func, ...)                                      \
	if (type->func.f_word) {                                          \
		xword x;                                                      \
		x.w[0] = (*type->func.f_word)(args, addr - 1, ##__VA_ARGS__); \
		x.w[1] = (*type->func.f_word)(args, addr + 1, ##__VA_ARGS__); \
		x.w[2] = (*type->func.f_word)(args, addr + 3, ##__VA_ARGS__); \
		x.w[3] = (*type->func.f_word)(args, addr + 5, ##__VA_ARGS__); \
		x.w[3] = (*type->func.f_word)(args, addr + 7, ##__VA_ARGS__); \
		return x.q_1;                                                 \
	}
	READ_5X_READW(dtv_read)
	READ_5X_READW(dtv_cmpxch, 0, 0, true)
	READ_5X_READW(dtv_add, 0, true)
	READ_5X_READW(dtv_sub, 0, true)
	READ_5X_READW(dtv_and, (u16)~0, true)
	READ_5X_READW(dtv_or, 0, true)
	READ_5X_READW(dtv_xor, 0, true)
#undef READ_5X_READW
#define READ_8X_READB(func, ...)                                      \
	if (type->func.f_byte) {                                          \
		qword x;                                                      \
		x.b[0] = (*type->func.f_byte)(args, addr + 0, ##__VA_ARGS__); \
		x.b[1] = (*type->func.f_byte)(args, addr + 1, ##__VA_ARGS__); \
		x.b[2] = (*type->func.f_byte)(args, addr + 2, ##__VA_ARGS__); \
		x.b[3] = (*type->func.f_byte)(args, addr + 3, ##__VA_ARGS__); \
		x.b[4] = (*type->func.f_byte)(args, addr + 4, ##__VA_ARGS__); \
		x.b[5] = (*type->func.f_byte)(args, addr + 5, ##__VA_ARGS__); \
		x.b[6] = (*type->func.f_byte)(args, addr + 6, ##__VA_ARGS__); \
		x.b[7] = (*type->func.f_byte)(args, addr + 7, ##__VA_ARGS__); \
		return x.q;                                                   \
	}
	READ_8X_READB(dtv_read)
	READ_8X_READB(dtv_cmpxch, 0, 0, true)
	READ_8X_READB(dtv_add, 0, true)
	READ_8X_READB(dtv_sub, 0, true)
	READ_8X_READB(dtv_and, (u8)~0, true)
	READ_8X_READB(dtv_or, 0, true)
	READ_8X_READB(dtv_xor, 0, true)
#undef READ_8X_READB
	vio_illegal_read(args, addr);
}
PUBLIC NONNULL((1)) u64 KCALL vio_readq_aligned(struct vio_args *__restrict args, pos_t addr) {
	struct vm_datablock_type_vio const *type = args->va_type;
	assert(((uintptr_t)addr & 7) == 0);
	if (type->dtv_read.f_qword) return (*type->dtv_read.f_qword)(args, addr);
	if (type->dtv_cmpxch.f_qword) return (*type->dtv_cmpxch.f_qword)(args, addr, 0, 0, true);
	if (type->dtv_add.f_qword) return (*type->dtv_add.f_qword)(args, addr, 0, true);
	if (type->dtv_sub.f_qword) return (*type->dtv_sub.f_qword)(args, addr, 0, true);
	if (type->dtv_and.f_qword) return (*type->dtv_and.f_qword)(args, addr, (u64)~0, true);
	if (type->dtv_or.f_qword) return (*type->dtv_or.f_qword)(args, addr, 0, true);
	if (type->dtv_xor.f_qword) return (*type->dtv_xor.f_qword)(args, addr, 0, true);
#define READ_2X_READL(func, ...)                                       \
	if (type->func.f_dword) {                                          \
		qword x;                                                       \
		x.l[0] = (*type->func.f_dword)(args, addr, ##__VA_ARGS__);     \
		x.l[1] = (*type->func.f_dword)(args, addr + 4, ##__VA_ARGS__); \
		return x.q;                                                    \
	}
	READ_2X_READL(dtv_read)
	READ_2X_READL(dtv_cmpxch, 0, 0, true)
	READ_2X_READL(dtv_add, 0, true)
	READ_2X_READL(dtv_sub, 0, true)
	READ_2X_READL(dtv_and, (u32)~0, true)
	READ_2X_READL(dtv_or, 0, true)
	READ_2X_READL(dtv_xor, 0, true)
#undef READ_2X_READL
#define READ_4X_READW(func, ...)                                      \
	if (type->func.f_word) {                                          \
		qword x;                                                      \
		x.w[0] = (*type->func.f_word)(args, addr, ##__VA_ARGS__);     \
		x.w[1] = (*type->func.f_word)(args, addr + 2, ##__VA_ARGS__); \
		x.w[2] = (*type->func.f_word)(args, addr + 4, ##__VA_ARGS__); \
		x.w[3] = (*type->func.f_word)(args, addr + 6, ##__VA_ARGS__); \
		return x.q;                                                   \
	}
	READ_4X_READW(dtv_read)
	READ_4X_READW(dtv_cmpxch, 0, 0, true)
	READ_4X_READW(dtv_add, 0, true)
	READ_4X_READW(dtv_sub, 0, true)
	READ_4X_READW(dtv_and, (u16)~0, true)
	READ_4X_READW(dtv_or, 0, true)
	READ_4X_READW(dtv_xor, 0, true)
#undef READ_4X_READW
#define READ_8X_READB(func, ...)                                      \
	if (type->func.f_byte) {                                          \
		qword x;                                                      \
		x.b[0] = (*type->func.f_byte)(args, addr + 0, ##__VA_ARGS__); \
		x.b[1] = (*type->func.f_byte)(args, addr + 1, ##__VA_ARGS__); \
		x.b[2] = (*type->func.f_byte)(args, addr + 2, ##__VA_ARGS__); \
		x.b[3] = (*type->func.f_byte)(args, addr + 3, ##__VA_ARGS__); \
		x.b[4] = (*type->func.f_byte)(args, addr + 4, ##__VA_ARGS__); \
		x.b[5] = (*type->func.f_byte)(args, addr + 5, ##__VA_ARGS__); \
		x.b[6] = (*type->func.f_byte)(args, addr + 6, ##__VA_ARGS__); \
		x.b[7] = (*type->func.f_byte)(args, addr + 7, ##__VA_ARGS__); \
		return x.q;                                                   \
	}
	READ_8X_READB(dtv_read)
	READ_8X_READB(dtv_cmpxch, 0, 0, true)
	READ_8X_READB(dtv_add, 0, true)
	READ_8X_READB(dtv_sub, 0, true)
	READ_8X_READB(dtv_and, (u8)~0, true)
	READ_8X_READB(dtv_or, 0, true)
	READ_8X_READB(dtv_xor, 0, true)
#undef READ_8X_READB
	vio_illegal_read(args, addr);
}
#endif /* CONFIG_VIO_HAS_QWORD */

#define IF_WW(name, ...) { __auto_type func = type->dtv_write.name; if (func) { __VA_ARGS__ } }
#define IF_WX(name, ...) { __auto_type func = type->dtv_xch.name; if (func) { __VA_ARGS__ } }

PUBLIC NONNULL((1)) void KCALL vio_writeb(struct vio_args *__restrict args, pos_t addr, u8 value) {
	struct vm_datablock_type_vio const *type = args->va_type;
	IF_WW(f_byte, { (*func)(args, addr, value); return; })
	IF_WX(f_byte, { (*func)(args, addr, value, false); return; })
	/* Atomic writes are impossible - Try them as non-atomic ones */
	IF_WW(f_word, {
		word x;
		x.b[(uintptr_t)addr & 1] = value;
		x.b[((uintptr_t)addr ^ 1) & 1] = vio_readb(args, addr ^ 1);
		(*func)(args, addr, x.w);
		return;
	})
	IF_WX(f_word, {
		word x;
		x.b[(uintptr_t)addr & 1] = value;
		x.b[((uintptr_t)addr ^ 1) & 1] = vio_readb(args, addr ^ 1);
		(*func)(args, addr, x.w, false);
		return;
	})
	IF_WW(f_dword, {
		dword x = { vio_readl_aligned(args, AL) };
		B3 = value;
		(*func)(args, addr, x.l);
		return;
	})
	IF_WX(f_dword, {
		dword x = { vio_readl_aligned(args, AL) };
		B3 = value;
		(*func)(args, addr, x.l, false);
		return;
	})
#ifdef CONFIG_VIO_HAS_QWORD
	IF_WW(f_qword, {
		qword x = { vio_readq_aligned(args, AQ) };
		B7 = value;
		(*func)(args, addr, x.q);
		return;
	})
	IF_WX(f_qword, {
		qword x = { vio_readq_aligned(args, AQ) };
		B7 = value;
		(*func)(args, addr, x.q, false);
		return;
	})
#endif /* CONFIG_VIO_HAS_QWORD */
	vio_illegal_write(args, addr);
}



PUBLIC NONNULL((1)) void KCALL
vio_writew(struct vio_args *__restrict args, pos_t addr, u16 value) {
	struct vm_datablock_type_vio const *type = args->va_type;
	if (((uintptr_t)addr & 1) == 0) {
		IF_WW(f_word, { (*func)(args, addr, value); return; })
		IF_WX(f_word, { (*func)(args, addr, value, false); return; })
	}
	IF_WW(f_byte, {
		word x = { value };
		(*func)(args, addr & ~1, x.b[0]);
		(*func)(args, addr | 1, x.b[1]);
		return;
	})
	IF_WX(f_byte, {
		word x = { value };
		(*func)(args, addr & ~1, x.b[0], false);
		(*func)(args, addr | 1, x.b[1], false);
		return;
	})
	if (((uintptr_t)addr & 3) != 3) {
		IF_WW(f_dword, {
			dword x = { vio_readl_aligned(args, addr & ~3) };
			W3 = value;
			(*func)(args, addr & ~3, x.l);
			return;
		})
		IF_WX(f_dword, {
			dword x = { vio_readl_aligned(args, addr & ~3) };
			W3 = value;
			(*func)(args, addr & ~3, x.l, false);
			return;
		})
	}
#ifdef CONFIG_VIO_HAS_QWORD
	if (((uintptr_t)addr & 7) != 7) {
		IF_WW(f_qword, {
			qword x = { vio_readq_aligned(args, addr & ~7) };
			W7 = value;
			(*func)(args, addr & ~7, x.q);
			return;
		})
		IF_WX(f_qword, {
			qword x = { vio_readq_aligned(args, addr & ~7) };
			W7 = value;
			(*func)(args, addr & ~7, x.q, false);
			return;
		})
	}
#endif /* CONFIG_VIO_HAS_QWORD */
	IF_WW(f_word, {
		dword x = { vio_readl_aligned(args, addr & ~3) };
		W3 = value;
		(*func)(args, addr & ~3, x.w[0]);
		(*func)(args, (addr & ~3) + 2, x.w[0]);
		return;
	})
	IF_WX(f_word, {
		dword x = { vio_readl_aligned(args, addr & ~3) };
		W3 = value;
		(*func)(args, addr & ~3, x.w[0], false);
		(*func)(args, (addr & ~3) + 2, x.w[0], false);
		return;
	})
	vio_illegal_write(args, addr);
}

PUBLIC NONNULL((1)) void KCALL
vio_writew_aligned(struct vio_args *__restrict args, pos_t addr, u16 value) {
	struct vm_datablock_type_vio const *type = args->va_type;
	assert(((uintptr_t)addr & 1) == 0);
	IF_WW(f_word, { (*func)(args, addr, value); return; })
	IF_WX(f_word, { (*func)(args, addr, value, false); return; })
	IF_WW(f_byte, {
		word x = { value };
		(*func)(args, addr + 0, x.b[0]);
		(*func)(args, addr + 1, x.b[1]);
		return;
	})
	IF_WX(f_byte, {
		word x = { value };
		(*func)(args, addr + 0, x.b[0], false);
		(*func)(args, addr + 1, x.b[1], false);
		return;
	})
	if (!((uintptr_t)addr & 2)) {
		IF_WW(f_dword, {
			dword x = { vio_readl_aligned(args, addr & ~3) };
			W2 = value;
			(*func)(args, addr & ~3, x.l);
			return;
		})
		IF_WX(f_dword, {
			dword x = { vio_readl_aligned(args, addr & ~3) };
			W2 = value;
			(*func)(args, addr & ~3, x.l, false);
			return;
		})
	}
#ifdef CONFIG_VIO_HAS_QWORD
	if (((uintptr_t)addr & 7) != 7) {
		IF_WW(f_qword, {
			qword x = { vio_readq_aligned(args, addr & ~7) };
			W6 = value;
			(*func)(args, addr & ~7, x.q);
			return;
		})
		IF_WX(f_qword, {
			qword x = { vio_readq_aligned(args, addr & ~7) };
			W6 = value;
			(*func)(args, addr & ~7, x.q, false);
			return;
		})
	}
#endif /* CONFIG_VIO_HAS_QWORD */
	vio_illegal_write(args, addr);
}

PUBLIC NONNULL((1)) void KCALL
vio_writel(struct vio_args *__restrict args,
           pos_t addr, u32 value) {
	struct vm_datablock_type_vio const *type = args->va_type;
	if (((uintptr_t)addr & 3) == 0) {
		IF_WW(f_dword, { (*func)(args, addr, value); return; })
		IF_WX(f_dword, { (*func)(args, addr, value, false); return; })
	}
	if (((uintptr_t)addr & 1) == 0) {
		IF_WW(f_word, {
			dword x = { value };
			(*func)(args, addr + 0, x.w[0]);
			(*func)(args, addr + 2, x.w[1]);
			return;
		})
		IF_WX(f_word, {
			dword x = { value };
			(*func)(args, addr + 0, x.w[0], false);
			(*func)(args, addr + 2, x.w[1], false);
			return;
		})
	}
	IF_WW(f_byte, {
		dword x = { value };
		(*func)(args, addr + 0, x.b[0]);
		(*func)(args, addr + 1, x.b[1]);
		(*func)(args, addr + 2, x.b[2]);
		(*func)(args, addr + 3, x.b[3]);
		return;
	})
	IF_WX(f_byte, {
		dword x = { value };
		(*func)(args, addr + 0, x.b[0], false);
		(*func)(args, addr + 1, x.b[1], false);
		(*func)(args, addr + 2, x.b[2], false);
		(*func)(args, addr + 3, x.b[3], false);
		return;
	})
	if (((uintptr_t)addr & 1) == 1) {
		IF_WW(f_word, {
			qword x;
			x.b[0] = vio_readb(args, addr - 1);
			x.b[5] = vio_readb(args, addr + 4);
			x.l_1 = value;
			(*func)(args, addr - 1, x.w[0]);
			(*func)(args, addr + 1, x.w[1]);
			(*func)(args, addr + 3, x.w[2]);
			return;
		})
		IF_WX(f_word, {
			qword x;
			x.b[0] = vio_readb(args, addr - 1);
			x.b[5] = vio_readb(args, addr + 4);
			x.l_1 = value;
			(*func)(args, addr - 1, x.w[0], false);
			(*func)(args, addr + 1, x.w[1], false);
			(*func)(args, addr + 3, x.w[2], false);
			return;
		})
	}
#ifdef CONFIG_VIO_HAS_QWORD
	IF_WW(f_qword, {
		qword x;
		x.q = vio_readq(args, addr & ~7);
		L7 = value;
		(*func)(args, addr, value);
		return;
	})
	IF_WX(f_qword, {
		qword x;
		x.q = vio_readq(args, addr & ~7);
		L7 = value;
		(*func)(args, addr, value, false);
		return;
	})
#endif /* CONFIG_VIO_HAS_QWORD */
	if (((uintptr_t)addr & 3) != 0) {
#ifdef CONFIG_VIO_HAS_QWORD
		IF_WW(f_dword, {
			qword x;
			x.q = vio_readq_aligned(args, addr & ~7);
			L3 = value;
			(*func)(args, (addr & ~3), x.l_0);
			(*func)(args, (addr & ~3) + 4, x.l_4);
			return;
		})
		IF_WX(f_dword, {
			qword x;
			x.q = vio_readq_aligned(args, addr & ~7);
			L3 = value;
			(*func)(args, (addr & ~3), x.l_0, false);
			(*func)(args, (addr & ~3) + 4, x.l_4, false);
			return;
		})
#else
		IF_WW(f_dword, {
			qword x;
			x.l_0 = vio_readl_aligned(args, (addr & ~7));
			x.l_4 = vio_readl_aligned(args, (addr & ~7) + 4);
			L3 = value;
			(*func)(args, (addr & ~3), x.l_0);
			(*func)(args, (addr & ~3) + 4, x.l_4);
			return;
		})
		IF_WX(f_dword, {
			qword x;
			x.l_0 = vio_readl_aligned(args, (addr & ~7));
			x.l_4 = vio_readl_aligned(args, (addr & ~7) + 4);
			L3 = value;
			(*func)(args, (addr & ~3), x.l_0, false);
			(*func)(args, (addr & ~3) + 4, x.l_4, false);
			return;
		})
#endif
	}
#ifdef CONFIG_VIO_HAS_QWORD
	IF_WW(f_qword, {
		qword x = { vio_readq_aligned(args, addr & ~7) };
		L3 = value;
		(*func)(args, addr & ~7, x.q);
		return;
	})
	IF_WX(f_qword, {
		qword x = { vio_readq_aligned(args, addr & ~7) };
		L3 = value;
		(*func)(args, addr & ~7, x.q, false);
		return;
	})
#endif /* CONFIG_VIO_HAS_QWORD */
	vio_illegal_write(args, addr);
}

PUBLIC NONNULL((1)) void KCALL
vio_writel_aligned(struct vio_args *__restrict args,
                   pos_t addr, u32 value) {
	struct vm_datablock_type_vio const *type = args->va_type;
	assert(((uintptr_t)addr & 3) == 0);
	IF_WW(f_dword, { (*func)(args, addr, value); return; })
	IF_WX(f_dword, { (*func)(args, addr, value, false); return; })
	IF_WW(f_word, {
		dword x = { value };
		(*func)(args, addr + 0, x.w[0]);
		(*func)(args, addr + 2, x.w[1]);
		return;
	})
	IF_WX(f_word, {
		dword x = { value };
		(*func)(args, addr + 0, x.w[0], false);
		(*func)(args, addr + 2, x.w[1], false);
		return;
	})
	IF_WW(f_byte, {
		dword x = { value };
		(*func)(args, addr + 0, x.b[0]);
		(*func)(args, addr + 1, x.b[1]);
		(*func)(args, addr + 2, x.b[2]);
		(*func)(args, addr + 3, x.b[3]);
		return;
	})
	IF_WX(f_byte, {
		dword x = { value };
		(*func)(args, addr + 0, x.b[0], false);
		(*func)(args, addr + 1, x.b[1], false);
		(*func)(args, addr + 2, x.b[2], false);
		(*func)(args, addr + 3, x.b[3], false);
		return;
	})
#ifdef CONFIG_VIO_HAS_QWORD
	IF_WW(f_qword, {
		qword x;
		x.q = vio_readq(args, addr & ~4);
		L4 = value;
		(*func)(args, addr, x.q);
		return;
	})
	IF_WX(f_qword, {
		qword x;
		x.q = vio_readq(args, addr & ~4);
		L4 = value;
		(*func)(args, addr, x.q, false);
		return;
	})
#endif /* CONFIG_VIO_HAS_QWORD */
	vio_illegal_write(args, addr);
}

#ifdef CONFIG_VIO_HAS_QWORD
PUBLIC NONNULL((1)) void KCALL
vio_writeq(struct vio_args *__restrict args,
           pos_t addr, u64 value) {
	struct vm_datablock_type_vio const *type = args->va_type;
	if (((uintptr_t)addr & 7) == 0) {
		IF_WW(f_qword, { (*func)(args, addr, value); return; })
		IF_WX(f_qword, { (*func)(args, addr, value, false); return; })
	}
	if (((uintptr_t)addr & 3) == 0) {
		IF_WW(f_dword, {
			qword x = { value };
			(*func)(args, addr + 0, x.l[0]);
			(*func)(args, addr + 4, x.l[1]);
			return;
		})
		IF_WX(f_dword, {
			qword x = { value };
			(*func)(args, addr + 0, x.l[0], false);
			(*func)(args, addr + 4, x.l[1], false);
			return;
		})
	}
	if (((uintptr_t)addr & 1) == 0) {
		IF_WW(f_word, {
			qword x = { value };
			(*func)(args, addr + 0, x.w[0]);
			(*func)(args, addr + 2, x.w[1]);
			(*func)(args, addr + 4, x.w[2]);
			(*func)(args, addr + 6, x.w[3]);
			return;
		})
		IF_WX(f_word, {
			qword x = { value };
			(*func)(args, addr + 0, x.w[0], false);
			(*func)(args, addr + 2, x.w[1], false);
			(*func)(args, addr + 4, x.w[2], false);
			(*func)(args, addr + 6, x.w[3], false);
			return;
		})
	}
	IF_WW(f_byte, {
		qword x = { value };
		(*func)(args, addr + 0, x.b[0]);
		(*func)(args, addr + 1, x.b[1]);
		(*func)(args, addr + 2, x.b[2]);
		(*func)(args, addr + 3, x.b[3]);
		(*func)(args, addr + 4, x.b[4]);
		(*func)(args, addr + 5, x.b[5]);
		(*func)(args, addr + 6, x.b[6]);
		(*func)(args, addr + 7, x.b[7]);
		return;
	})
	IF_WX(f_byte, {
		qword x = { value };
		(*func)(args, addr + 0, x.b[0], false);
		(*func)(args, addr + 1, x.b[1], false);
		(*func)(args, addr + 2, x.b[2], false);
		(*func)(args, addr + 3, x.b[3], false);
		(*func)(args, addr + 4, x.b[4], false);
		(*func)(args, addr + 5, x.b[5], false);
		(*func)(args, addr + 6, x.b[6], false);
		(*func)(args, addr + 7, x.b[7], false);
		return;
	})
	if (((uintptr_t)addr & 1) == 1) {
		IF_WW(f_word, {
			xword x;
			x.b[0] = vio_readb(args, addr - 1);
			x.b[9] = vio_readb(args, addr + 8);
			x.q_1 = value;
			(*func)(args, addr - 1, x.w[0]);
			(*func)(args, addr + 1, x.w[1]);
			(*func)(args, addr + 3, x.w[2]);
			(*func)(args, addr + 5, x.w[3]);
			(*func)(args, addr + 7, x.w[4]);
			return;
		})
		IF_WX(f_word, {
			xword x;
			x.b[0] = vio_readb(args, addr - 1);
			x.b[9] = vio_readb(args, addr + 8);
			x.q_1 = value;
			(*func)(args, addr - 1, x.w[0], false);
			(*func)(args, addr + 1, x.w[1], false);
			(*func)(args, addr + 3, x.w[2], false);
			(*func)(args, addr + 5, x.w[3], false);
			(*func)(args, addr + 7, x.w[4], false);
			return;
		})
	}
	if (((uintptr_t)addr & 3) != 0) {
		IF_WW(f_dword, {
			xword x;
			x.q[0] = vio_readq_aligned(args, addr & ~7);
			x.q[1] = vio_readq_aligned(args, (addr & ~7) + 8);
			Q7 = value;
			(*func)(args, (addr & ~3), x.l_0);
			(*func)(args, (addr & ~3) + 4, x.l_4);
			(*func)(args, (addr & ~3) + 8, x.l_8);
			(*func)(args, (addr & ~3) + 12, x.l_12);
			return;
		})
		IF_WX(f_dword, {
			xword x;
			x.q[0] = vio_readq_aligned(args, addr & ~7);
			x.q[1] = vio_readq_aligned(args, (addr & ~7) + 8);
			Q7 = value;
			(*func)(args, (addr & ~3), x.l_0, false);
			(*func)(args, (addr & ~3) + 4, x.l_4, false);
			(*func)(args, (addr & ~3) + 8, x.l_8, false);
			(*func)(args, (addr & ~3) + 12, x.l_12, false);
			return;
		})
	}
	IF_WW(f_qword, {
		xword x;
		x.q[0] = vio_readq_aligned(args, addr & ~7);
		x.q[1] = vio_readq_aligned(args, (addr & ~7) + 8);
		Q7 = value;
		(*func)(args, addr & ~7, x.q[0]);
		(*func)(args, (addr & ~7) + 8, x.q[0]);
		return;
	})
	IF_WX(f_qword, {
		xword x;
		x.q[0] = vio_readq_aligned(args, addr & ~7);
		x.q[1] = vio_readq_aligned(args, (addr & ~7) + 8);
		Q7 = value;
		(*func)(args, addr & ~7, x.q[0], false);
		(*func)(args, (addr & ~7) + 8, x.q[0], false);
		return;
	})
	vio_illegal_write(args, addr);
}
PUBLIC NONNULL((1)) void KCALL
vio_writeq_aligned(struct vio_args *__restrict args,
                   pos_t addr, u64 value) {
	struct vm_datablock_type_vio const *type = args->va_type;
	assert(((uintptr_t)addr & 7) == 0);
	IF_WW(f_qword, { (*func)(args, addr, value); return; })
	IF_WX(f_qword, { (*func)(args, addr, value, false); return; })
	IF_WW(f_dword, {
		qword x = { value };
		(*func)(args, addr + 0, x.l[0]);
		(*func)(args, addr + 4, x.l[1]);
		return;
	})
	IF_WX(f_dword, {
		qword x = { value };
		(*func)(args, addr + 0, x.l[0], false);
		(*func)(args, addr + 4, x.l[1], false);
		return;
	})
	IF_WW(f_word, {
		qword x = { value };
		(*func)(args, addr + 0, x.w[0]);
		(*func)(args, addr + 2, x.w[1]);
		(*func)(args, addr + 4, x.w[2]);
		(*func)(args, addr + 6, x.w[3]);
		return;
	})
	IF_WX(f_word, {
		qword x = { value };
		(*func)(args, addr + 0, x.w[0], false);
		(*func)(args, addr + 2, x.w[1], false);
		(*func)(args, addr + 4, x.w[2], false);
		(*func)(args, addr + 6, x.w[3], false);
		return;
	})
	IF_WW(f_byte, {
		qword x = { value };
		(*func)(args, addr + 0, x.b[0]);
		(*func)(args, addr + 1, x.b[1]);
		(*func)(args, addr + 2, x.b[2]);
		(*func)(args, addr + 3, x.b[3]);
		(*func)(args, addr + 4, x.b[4]);
		(*func)(args, addr + 5, x.b[5]);
		(*func)(args, addr + 6, x.b[6]);
		(*func)(args, addr + 7, x.b[7]);
		return;
	})
	IF_WX(f_byte, {
		qword x = { value };
		(*func)(args, addr + 0, x.b[0], false);
		(*func)(args, addr + 1, x.b[1], false);
		(*func)(args, addr + 2, x.b[2], false);
		(*func)(args, addr + 3, x.b[3], false);
		(*func)(args, addr + 4, x.b[4], false);
		(*func)(args, addr + 5, x.b[5], false);
		(*func)(args, addr + 6, x.b[6], false);
		(*func)(args, addr + 7, x.b[7], false);
		return;
	})
	vio_illegal_write(args, addr);
}
#endif /* CONFIG_VIO_HAS_QWORD */


PUBLIC NONNULL((1)) u8 KCALL
vio_cmpxchb(struct vio_args *__restrict args,
            pos_t addr, u8 oldvalue, u8 newvalue, bool atomic) {
	struct vm_datablock_type_vio const *type = args->va_type;
	if (type->dtv_cmpxch.f_byte)
		return (*type->dtv_cmpxch.f_byte)(args, addr, oldvalue, newvalue, atomic);
	if (type->dtv_cmpxch.f_word) {
		word oldval, oldval2, newval;
		oldval.b[((uintptr_t)addr ^ 1) & 1] = vio_readb(args, addr ^ 1);
		oldval.b[(uintptr_t)addr & 1]       = oldvalue;
		newval                              = oldval;
		newval.b[(uintptr_t)addr & 1]       = newvalue;
		while ((oldval2.w = (*type->dtv_cmpxch.f_word)(args, addr & ~1, oldval.w, newval.w, atomic)) != oldval.w) {
			oldval = newval = oldval2;
			oldval.b[(uintptr_t)addr & 1] = oldvalue;
			newval.b[(uintptr_t)addr & 1] = newvalue;
		}
		return oldval2.b[(uintptr_t)addr & 1];
	}
	if (type->dtv_cmpxch.f_dword) {
		dword oldval, oldval2, newval;
		oldval.l                      = vio_readl(args, addr & ~3);
		oldval.b[(uintptr_t)addr & 3] = oldvalue;
		newval                        = oldval;
		newval.b[(uintptr_t)addr & 3] = newvalue;
		while ((oldval2.l = (*type->dtv_cmpxch.f_dword)(args, addr & ~3, oldval.l, newval.l, atomic)) != oldval.l) {
			oldval = newval = oldval2;
			oldval.b[(uintptr_t)addr & 3] = oldvalue;
			newval.b[(uintptr_t)addr & 3] = newvalue;
		}
		return oldval2.b[(uintptr_t)addr & 3];
	}
#if defined(CONFIG_VIO_HAS_QWORD) || defined(CONFIG_VIO_HAS_QWORD_CMPXCH)
	if (type->dtv_cmpxch.f_qword) {
		qword oldval, oldval2, newval;
#ifdef CONFIG_VIO_HAS_QWORD
		oldval.q = vio_readq(args, addr & ~7);
#else
		oldval.l[0] = vio_readl(args, (addr & ~7));
		oldval.l[1] = vio_readl(args, (addr & ~7) + 4);
#endif
		oldval.b[(uintptr_t)addr & 7] = oldvalue;
		newval                        = oldval;
		newval.b[(uintptr_t)addr & 7] = newvalue;
		while ((oldval2.q = (*type->dtv_cmpxch.f_qword)(args, addr & ~7, oldval.q, newval.q, atomic)) != oldval.q) {
			oldval = newval = oldval2;
			oldval.b[(uintptr_t)addr & 7] = oldvalue;
			newval.b[(uintptr_t)addr & 7] = newvalue;
		}
		return oldval2.b[(uintptr_t)addr & 7];
	}
#endif /* CONFIG_VIO_HAS_QWORD || CONFIG_VIO_HAS_QWORD_CMPXCH */
	/* Non-atomic compare-exchange */
	if (atomic)
		vio_nonatomic_operation8(args, addr, oldvalue, newvalue);
	{
		u8 result = vio_readb(args, addr);
		if (result == oldvalue)
			vio_writeb(args, addr, newvalue);
		return result;
	}
}


PUBLIC NONNULL((1)) u16 KCALL
vio_cmpxchw(struct vio_args *__restrict args,
            pos_t addr, u16 oldvalue, u16 newvalue, bool atomic) {
	struct vm_datablock_type_vio const *type = args->va_type;
	if (type->dtv_cmpxch.f_word && ((uintptr_t)addr & 1) == 0)
		return (*type->dtv_cmpxch.f_word)(args, addr, oldvalue, newvalue, atomic);
	if (type->dtv_cmpxch.f_dword && ((uintptr_t)addr & 3) <= 2) {
		dword oldval, oldval2, newval;
		oldval.l                                          = vio_readl(args, addr & ~3);
		(*(u16 *)((u8 *)&oldval + ((uintptr_t)addr & 3))) = oldvalue;
		newval                                            = oldval;
		(*(u16 *)((u8 *)&newval + ((uintptr_t)addr & 3))) = oldvalue;
		while ((oldval2.l = (*type->dtv_cmpxch.f_dword)(args, addr & ~3, oldval.l, newval.l, atomic)) != oldval.l) {
			oldval = newval = oldval2;
			(*(u16 *)((u8 *)&oldval + ((uintptr_t)addr & 3))) = oldvalue;
			(*(u16 *)((u8 *)&newval + ((uintptr_t)addr & 3))) = oldvalue;
		}
		return (*(u16 *)((u8 *)&oldval2 + ((uintptr_t)addr & 3)));
	}
#if defined(CONFIG_VIO_HAS_QWORD) || defined(CONFIG_VIO_HAS_QWORD_CMPXCH)
	if (type->dtv_cmpxch.f_qword && ((uintptr_t)addr & 7) <= 6) {
		qword oldval, oldval2, newval;
#ifdef CONFIG_VIO_HAS_QWORD
		oldval.q = vio_readq(args, addr & ~7);
#else /* CONFIG_VIO_HAS_QWORD */
		oldval.l[0] = vio_readl(args, (addr & ~7));
		oldval.l[1] = vio_readl(args, (addr & ~7) + 4);
#endif /* !CONFIG_VIO_HAS_QWORD */
		(*(u16 *)((u8 *)&oldval + ((uintptr_t)addr & 7))) = oldvalue;
		newval                                            = oldval;
		(*(u16 *)((u8 *)&newval + ((uintptr_t)addr & 7))) = newvalue;
		while ((oldval2.q = (*type->dtv_cmpxch.f_qword)(args, addr & ~7, oldval.q, newval.q, atomic)) != oldval.q) {
			oldval = newval = oldval2;
			(*(u16 *)((u8 *)&oldval + ((uintptr_t)addr & 7))) = oldvalue;
			(*(u16 *)((u8 *)&newval + ((uintptr_t)addr & 7))) = newvalue;
		}
		return (*(u16 *)((u8 *)&oldval2 + ((uintptr_t)addr & 7)));
	}
#endif /* CONFIG_VIO_HAS_QWORD || CONFIG_VIO_HAS_QWORD_CMPXCH */
	/* Non-atomic compare-exchange */
	if (atomic)
		vio_nonatomic_operation16(args, addr, oldvalue, newvalue);
	{
		u16 result = vio_readw(args, addr);
		if (result == oldvalue)
			vio_writew(args, addr, newvalue);
		return result;
	}
}


PUBLIC NONNULL((1)) u32 KCALL
vio_cmpxchl(struct vio_args *__restrict args,
            pos_t addr, u32 oldvalue, u32 newvalue, bool atomic) {
	struct vm_datablock_type_vio const *type = args->va_type;
	if (type->dtv_cmpxch.f_dword && ((uintptr_t)addr & 3) == 0)
		return (*type->dtv_cmpxch.f_dword)(args, addr, oldvalue, newvalue, atomic);
#if defined(CONFIG_VIO_HAS_QWORD) || defined(CONFIG_VIO_HAS_QWORD_CMPXCH)
	if (type->dtv_cmpxch.f_qword && ((uintptr_t)addr & 7) <= 4) {
		qword oldval, oldval2, newval;
#ifdef CONFIG_VIO_HAS_QWORD
		oldval.q = vio_readq(args, addr & ~7);
#else /* CONFIG_VIO_HAS_QWORD */
		oldval.l[0] = vio_readl(args, (addr & ~7));
		oldval.l[1] = vio_readl(args, (addr & ~7) + 4);
#endif /* !CONFIG_VIO_HAS_QWORD */
		(*(u32 *)((u8 *)&oldval + ((uintptr_t)addr & 7))) = oldvalue;
		newval                                            = oldval;
		(*(u32 *)((u8 *)&newval + ((uintptr_t)addr & 7))) = newvalue;
		while ((oldval2.q = (*type->dtv_cmpxch.f_qword)(args, addr & ~7, oldval.q, newval.q, atomic)) != oldval.q) {
			oldval = newval = oldval2;
			(*(u32 *)((u8 *)&oldval + ((uintptr_t)addr & 7))) = oldvalue;
			(*(u32 *)((u8 *)&newval + ((uintptr_t)addr & 7))) = newvalue;
		}
		return (*(u32 *)((u8 *)&oldval2 + ((uintptr_t)addr & 7)));
	}
#endif /* CONFIG_VIO_HAS_QWORD || CONFIG_VIO_HAS_QWORD_CMPXCH */
	/* Non-atomic compare-exchange */
	if (atomic)
		vio_nonatomic_operation32(args, addr, oldvalue, newvalue);
	{
		u32 result = vio_readl(args, addr);
		if (result == oldvalue)
			vio_writel(args, addr, newvalue);
		return result;
	}
}

#if defined(CONFIG_VIO_HAS_QWORD) || defined(CONFIG_VIO_HAS_QWORD_CMPXCH)
PUBLIC NONNULL((1)) u64 KCALL
vio_cmpxchq(struct vio_args *__restrict args,
            pos_t addr, u64 oldvalue, u64 newvalue, bool atomic) {
	struct vm_datablock_type_vio const *type = args->va_type;
	if (type->dtv_cmpxch.f_qword && ((uintptr_t)addr & 7) == 0)
		return (*type->dtv_cmpxch.f_qword)(args, addr, oldvalue, newvalue, atomic);
	/* Non-atomic compare-exchange */
	if (atomic)
		vio_nonatomic_operation64(args, addr, oldvalue, newvalue);
	{
#ifdef CONFIG_VIO_HAS_QWORD
		u64 result = vio_readq(args, addr);
		if (result == oldvalue)
			vio_writeq(args, addr, newvalue);
		return result;
#else /* CONFIG_VIO_HAS_QWORD */
		qword result;
		result.l[0] = vio_readl(args, addr);
		result.l[1] = vio_readl(args, addr + 4);
		if (result.q == oldvalue) {
			result.q = newvalue;
			vio_writel(args, addr + 0, result.l[0]);
			vio_writel(args, addr + 4, result.l[1]);
		}
		return oldvalue;
#endif /* !CONFIG_VIO_HAS_QWORD */
	}
}
#endif /* CONFIG_VIO_HAS_QWORD || CONFIG_VIO_HAS_QWORD_CMPXCH */

#ifdef CONFIG_VIO_HAS_INT128_CMPXCH
PUBLIC NONNULL((1)) uint128_t KCALL
vio_cmpxch128(struct vio_args *__restrict args,
              pos_t addr, uint128_t oldvalue,
              uint128_t newvalue, bool atomic) {
	struct vm_datablock_type_vio const *type = args->va_type;
	if (type->dtv_cmpxch.f_int128 && ((uintptr_t)addr & 15) == 0)
		return (*type->dtv_cmpxch.f_int128)(args, addr, oldvalue, newvalue, atomic);
	/* Non-atomic compare-exchange */
	if (atomic)
		vio_nonatomic_operation128(args, addr, oldvalue, newvalue);
	{
		union {
			uint128_t v128; /* FIXME: Intellisense says default constructor deleted */
			u64       v64[2];
			u32       v32[4];
		} result;
#ifdef CONFIG_VIO_HAS_QWORD
		result.v64[0] = vio_readq(args, addr + 0);
		result.v64[1] = vio_readq(args, addr + 8);
		if (memcmp(&result, &oldvalue, 16) == 0) {
			vio_writeq(args, addr + 0, ((u64 *)&newvalue)[0]);
			vio_writeq(args, addr + 8, ((u64 *)&newvalue)[1]);
		}
#else /* CONFIG_VIO_HAS_QWORD */
		result.v32[0] = vio_readl(args, addr + 0);
		result.v32[1] = vio_readl(args, addr + 4);
		result.v32[2] = vio_readl(args, addr + 8);
		result.v32[3] = vio_readl(args, addr + 12);
		if (memcmp(&result, &oldvalue, 16) == 0) {
			vio_writel(args, addr + 0,  ((u32 *)&newvalue)[0]);
			vio_writel(args, addr + 4,  ((u32 *)&newvalue)[1]);
			vio_writel(args, addr + 8,  ((u32 *)&newvalue)[2]);
			vio_writel(args, addr + 12, ((u32 *)&newvalue)[3]);
		}
#endif /* !CONFIG_VIO_HAS_QWORD */
		return result.v128;
	}
}
#endif /* CONFIG_VIO_HAS_INT128_CMPXCH */

PUBLIC NONNULL((1)) u8 KCALL
vio_cmpxch_or_writeb(struct vio_args *__restrict args,
                     pos_t addr, u8 oldvalue,
                     u8 newvalue, bool atomic) {
	struct vm_datablock_type_vio const *type = args->va_type;
	if (type->dtv_cmpxch.f_byte)
		return (*type->dtv_cmpxch.f_byte)(args, addr, oldvalue, newvalue, atomic);
	if (type->dtv_cmpxch.f_word) {
		word oldval, oldval2, newval;
		oldval.b[((uintptr_t)addr ^ 1) & 1] = vio_readb(args, addr ^ 1);
		oldval.b[(uintptr_t)addr & 1]       = oldvalue;
		newval                              = oldval;
		newval.b[(uintptr_t)addr & 1]       = newvalue;
		while ((oldval2.w = (*type->dtv_cmpxch.f_word)(args, addr & ~1, oldval.w, newval.w, atomic)) != oldval.w) {
			oldval = newval = oldval2;
			oldval.b[(uintptr_t)addr & 1] = oldvalue;
			newval.b[(uintptr_t)addr & 1] = newvalue;
		}
		return oldval2.b[(uintptr_t)addr & 1];
	}
	if (type->dtv_cmpxch.f_dword) {
		dword oldval, oldval2, newval;
		oldval.l                      = vio_readl(args, addr & ~3);
		oldval.b[(uintptr_t)addr & 3] = oldvalue;
		newval                        = oldval;
		newval.b[(uintptr_t)addr & 3] = newvalue;
		while ((oldval2.l = (*type->dtv_cmpxch.f_dword)(args, addr & ~3, oldval.l, newval.l, atomic)) != oldval.l) {
			oldval = newval = oldval2;
			oldval.b[(uintptr_t)addr & 3] = oldvalue;
			newval.b[(uintptr_t)addr & 3] = newvalue;
		}
		return oldval2.b[(uintptr_t)addr & 3];
	}
#if defined(CONFIG_VIO_HAS_QWORD) || defined(CONFIG_VIO_HAS_QWORD_CMPXCH)
	if (type->dtv_cmpxch.f_qword) {
		qword oldval, oldval2, newval;
#ifdef CONFIG_VIO_HAS_QWORD
		oldval.q = vio_readq(args, addr & ~7);
#else /* CONFIG_VIO_HAS_QWORD */
		oldval.l[0] = vio_readl(args, (addr & ~7));
		oldval.l[1] = vio_readl(args, (addr & ~7) + 4);
#endif /* !CONFIG_VIO_HAS_QWORD */
		oldval.b[(uintptr_t)addr & 7] = oldvalue;
		newval                        = oldval;
		newval.b[(uintptr_t)addr & 7] = newvalue;
		while ((oldval2.q = (*type->dtv_cmpxch.f_qword)(args, addr & ~7, oldval.q, newval.q, atomic)) != oldval.q) {
			oldval = newval = oldval2;
			oldval.b[(uintptr_t)addr & 7] = oldvalue;
			newval.b[(uintptr_t)addr & 7] = newvalue;
		}
		return oldval2.b[(uintptr_t)addr & 7];
	}
#endif /* CONFIG_VIO_HAS_QWORD || CONFIG_VIO_HAS_QWORD_CMPXCH */
	/* Non-atomic compare-exchange */
	if (atomic)
		vio_nonatomic_operation8(args, addr, oldvalue, newvalue);
	vio_writeb(args, addr, newvalue);
	return oldvalue;
}


PUBLIC NONNULL((1)) u16 KCALL
vio_cmpxch_or_writew(struct vio_args *__restrict args,
                     pos_t addr, u16 oldvalue,
                     u16 newvalue, bool atomic) {
	struct vm_datablock_type_vio const *type = args->va_type;
	if (type->dtv_cmpxch.f_word && ((uintptr_t)addr & 1) == 0)
		return (*type->dtv_cmpxch.f_word)(args, addr, oldvalue, newvalue, atomic);
	if (type->dtv_cmpxch.f_dword && ((uintptr_t)addr & 3) <= 2) {
		dword oldval, oldval2, newval;
		oldval.l                                          = vio_readl(args, addr & ~3);
		(*(u16 *)((u8 *)&oldval + ((uintptr_t)addr & 3))) = oldvalue;
		newval                                            = oldval;
		(*(u16 *)((u8 *)&newval + ((uintptr_t)addr & 3))) = oldvalue;
		while ((oldval2.l = (*type->dtv_cmpxch.f_dword)(args, addr & ~3, oldval.l, newval.l, atomic)) != oldval.l) {
			oldval = newval = oldval2;
			(*(u16 *)((u8 *)&oldval + ((uintptr_t)addr & 3))) = oldvalue;
			(*(u16 *)((u8 *)&newval + ((uintptr_t)addr & 3))) = oldvalue;
		}
		return (*(u16 *)((u8 *)&oldval2 + ((uintptr_t)addr & 3)));
	}
#if defined(CONFIG_VIO_HAS_QWORD) || defined(CONFIG_VIO_HAS_QWORD_CMPXCH)
	if (type->dtv_cmpxch.f_qword && ((uintptr_t)addr & 7) <= 6) {
		qword oldval, oldval2, newval;
#ifdef CONFIG_VIO_HAS_QWORD
		oldval.q = vio_readq(args, addr & ~7);
#else /* CONFIG_VIO_HAS_QWORD */
		oldval.l[0] = vio_readl(args, (addr & ~7));
		oldval.l[1] = vio_readl(args, (addr & ~7) + 4);
#endif /* !CONFIG_VIO_HAS_QWORD */
		(*(u16 *)((u8 *)&oldval + ((uintptr_t)addr & 7))) = oldvalue;
		newval                                            = oldval;
		(*(u16 *)((u8 *)&newval + ((uintptr_t)addr & 7))) = newvalue;
		while ((oldval2.q = (*type->dtv_cmpxch.f_qword)(args, addr & ~7, oldval.q, newval.q, atomic)) != oldval.q) {
			oldval = newval = oldval2;
			(*(u16 *)((u8 *)&oldval + ((uintptr_t)addr & 7))) = oldvalue;
			(*(u16 *)((u8 *)&newval + ((uintptr_t)addr & 7))) = newvalue;
		}
		return (*(u16 *)((u8 *)&oldval2 + ((uintptr_t)addr & 7)));
	}
#endif /* CONFIG_VIO_HAS_QWORD || CONFIG_VIO_HAS_QWORD_CMPXCH */
	/* Non-atomic compare-exchange */
	if (atomic)
		vio_nonatomic_operation16(args, addr, oldvalue, newvalue);
	vio_writew(args, addr, newvalue);
	return oldvalue;
}


PUBLIC NONNULL((1)) u32 KCALL
vio_cmpxch_or_writel(struct vio_args *__restrict args,
                     pos_t addr, u32 oldvalue,
                     u32 newvalue, bool atomic) {
	struct vm_datablock_type_vio const *type = args->va_type;
	if (type->dtv_cmpxch.f_dword && ((uintptr_t)addr & 3) == 0)
		return (*type->dtv_cmpxch.f_dword)(args, addr, oldvalue, newvalue, atomic);
#if defined(CONFIG_VIO_HAS_QWORD) || defined(CONFIG_VIO_HAS_QWORD_CMPXCH)
	if (type->dtv_cmpxch.f_qword && ((uintptr_t)addr & 7) <= 4) {
		qword oldval, oldval2, newval;
#ifdef CONFIG_VIO_HAS_QWORD
		oldval.q = vio_readq(args, addr & ~7);
#else /* CONFIG_VIO_HAS_QWORD */
		oldval.l[0] = vio_readl(args, (addr & ~7));
		oldval.l[1] = vio_readl(args, (addr & ~7) + 4);
#endif /* !CONFIG_VIO_HAS_QWORD */
		(*(u32 *)((u8 *)&oldval + ((uintptr_t)addr & 7))) = oldvalue;
		newval                                            = oldval;
		(*(u32 *)((u8 *)&newval + ((uintptr_t)addr & 7))) = newvalue;
		while ((oldval2.q = (*type->dtv_cmpxch.f_qword)(args, addr & ~7, oldval.q, newval.q, atomic)) != oldval.q) {
			oldval = newval = oldval2;
			(*(u32 *)((u8 *)&oldval + ((uintptr_t)addr & 7))) = oldvalue;
			(*(u32 *)((u8 *)&newval + ((uintptr_t)addr & 7))) = newvalue;
		}
		return (*(u32 *)((u8 *)&oldval2 + ((uintptr_t)addr & 7)));
	}
#endif /* CONFIG_VIO_HAS_QWORD || CONFIG_VIO_HAS_QWORD_CMPXCH */
	/* Non-atomic compare-exchange */
	if (atomic)
		vio_nonatomic_operation32(args, addr, oldvalue, newvalue);
	vio_writel(args, addr, newvalue);
	return oldvalue;
}

#ifdef CONFIG_VIO_HAS_QWORD
PUBLIC NONNULL((1)) u64 KCALL
vio_cmpxch_or_writeq(struct vio_args *__restrict args,
                     pos_t addr, u64 oldvalue,
                     u64 newvalue, bool atomic) {
	struct vm_datablock_type_vio const *type = args->va_type;
	if (type->dtv_cmpxch.f_qword && ((uintptr_t)addr & 7) == 0)
		return (*type->dtv_cmpxch.f_qword)(args, addr, oldvalue, newvalue, atomic);
	/* Non-atomic compare-exchange */
	if (atomic)
		vio_nonatomic_operation64(args, addr, oldvalue, newvalue);
	vio_writeq(args, addr, newvalue);
	return oldvalue;
}
#endif /* CONFIG_VIO_HAS_QWORD */



/* Copy memory to/from VIO */
PUBLIC NONNULL((1)) void KCALL
vio_copyfromvio(struct vio_args *__restrict args,
                pos_t offset,
                USER CHECKED void *buf,
                size_t num_bytes)
		THROWS(E_SEGFAULT, ...) {
	if (!num_bytes)
		return;
	if (offset & 1) {
		u8 temp = vio_readb_aligned(args, offset);
		*(u8 *)buf = temp;
		buf = (byte_t *)buf + 1;
		--num_bytes;
		++offset;
	}
	if ((offset & 2) && num_bytes >= 2) {
		u16 temp = vio_readw_aligned(args, offset);
		UNALIGNED_SET16((u16 *)buf, temp);
		buf = (byte_t *)buf + 2;
		num_bytes -= 2;
		offset += 2;
	}
#ifdef CONFIG_VIO_HAS_QWORD
	if ((offset & 4) && num_bytes >= 4) {
		u32 temp = vio_readl_aligned(args, offset);
		UNALIGNED_SET32((u32 *)buf, temp);
		buf = (byte_t *)buf + 4;
		num_bytes -= 4;
		offset += 4;
	}
	while (num_bytes >= 8) {
		u64 temp = vio_readq_aligned(args, offset);
		UNALIGNED_SET64((u64 *)buf, temp);
		buf = (byte_t *)buf + 8;
		num_bytes -= 8;
		offset += 8;
	}
	if (num_bytes >= 4) {
		u32 temp = vio_readl_aligned(args, offset);
		UNALIGNED_SET32((u32 *)buf, temp);
		buf = (byte_t *)buf + 4;
		num_bytes -= 4;
		offset += 4;
	}
#else /* CONFIG_VIO_HAS_QWORD */
	while (num_bytes >= 4) {
		u32 temp = vio_readl_aligned(args, offset);
		UNALIGNED_SET32((u32 *)buf, temp);
		buf = (byte_t *)buf + 4;
		num_bytes -= 4;
		offset += 4;
	}
#endif /* !CONFIG_VIO_HAS_QWORD */
	assert(num_bytes <= 3);
	if (num_bytes >= 2) {
		u16 temp = vio_readw_aligned(args, offset);
		UNALIGNED_SET16((u16 *)buf, temp);
		buf = (byte_t *)buf + 2;
		num_bytes -= 2;
		offset += 2;
	}
	if (num_bytes) {
		u8 temp = vio_readb_aligned(args, offset);
		*(u8 *)buf = temp;
	}
}

PUBLIC NONNULL((1)) void KCALL
vio_copytovio(struct vio_args *__restrict args,
              pos_t offset,
              USER CHECKED void const *buf,
              size_t num_bytes)
		THROWS(E_SEGFAULT, ...) {
	if (!num_bytes)
		return;
	if (offset & 1) {
		u8 temp = *(u8 *)buf;
		vio_writeb_aligned(args, offset, temp);
		buf = (byte_t *)buf + 1;
		--num_bytes;
		++offset;
	}
	if ((offset & 2) && num_bytes >= 2) {
		u16 temp = UNALIGNED_GET16((u16 *)buf);
		vio_writew_aligned(args, offset, temp);
		buf = (byte_t *)buf + 2;
		num_bytes -= 2;
		offset += 2;
	}
#ifdef CONFIG_VIO_HAS_QWORD
	if ((offset & 4) && num_bytes >= 4) {
		u32 temp = UNALIGNED_GET32((u32 *)buf);
		vio_writel_aligned(args, offset, temp);
		buf = (byte_t *)buf + 4;
		num_bytes -= 4;
		offset += 4;
	}
	while (num_bytes >= 8) {
		u64 temp = UNALIGNED_GET64((u64 *)buf);
		vio_writeq_aligned(args, offset, temp);
		buf = (byte_t *)buf + 8;
		num_bytes -= 8;
		offset += 8;
	}
	if (num_bytes >= 4) {
		u32 temp = UNALIGNED_GET32((u32 *)buf);
		vio_writel_aligned(args, offset, temp);
		buf = (byte_t *)buf + 4;
		num_bytes -= 4;
		offset += 4;
	}
#else /* CONFIG_VIO_HAS_QWORD */
	while (num_bytes >= 4) {
		u32 temp = UNALIGNED_GET32((u32 *)buf);
		vio_writel_aligned(args, offset, temp);
		buf = (byte_t *)buf + 4;
		num_bytes -= 4;
		offset += 4;
	}
#endif /* !CONFIG_VIO_HAS_QWORD */
	assert(num_bytes <= 3);
	if (num_bytes >= 2) {
		u16 temp = UNALIGNED_GET16((u16 *)buf);
		vio_writew_aligned(args, offset, temp);
		buf = (byte_t *)buf + 2;
		num_bytes -= 2;
		offset += 2;
	}
	if (num_bytes) {
		u8 temp = *(u8 *)buf;
		vio_writeb_aligned(args, offset, temp);
	}
}

PUBLIC NONNULL((1)) void KCALL
vio_memset(struct vio_args *__restrict args,
           pos_t offset,
           int byte,
           size_t num_bytes)
		THROWS(E_SEGFAULT, ...) {
	if (!num_bytes)
		return;
	if (offset & 1) {
		vio_writeb_aligned(args, offset, (u8)byte);
		--num_bytes;
		++offset;
	}
	if ((offset & 2) && num_bytes >= 2) {
		u16 temp = (u16)byte | (u16)byte << 8;
		vio_writew_aligned(args, offset, temp);
		num_bytes -= 2;
		offset += 2;
	}
#ifdef CONFIG_VIO_HAS_QWORD
	if ((offset & 4) && num_bytes >= 4) {
		u32 temp = (u32)byte | (u32)byte << 8 |
		           (u32)byte << 16 | (u32)byte << 24;
		vio_writel_aligned(args, offset, temp);
		num_bytes -= 4;
		offset += 4;
	}
	if (num_bytes >= 8) {
		u64 temp = (u64)byte | (u64)byte << 8 |
		           (u64)byte << 16 | (u64)byte << 24 |
		           (u64)byte << 32 | (u64)byte << 40 |
		           (u64)byte << 48 | (u64)byte << 56;
		while (num_bytes >= 8) {
			vio_writeq_aligned(args, offset, temp);
			num_bytes -= 8;
			offset += 8;
		}
	}
	if (num_bytes >= 4) {
		u32 temp = (u32)byte | (u32)byte << 8 |
		           (u32)byte << 16 | (u32)byte << 24;
		vio_writel_aligned(args, offset, temp);
		num_bytes -= 4;
		offset += 4;
	}
#else /* CONFIG_VIO_HAS_QWORD */
	if (num_bytes >= 4) {
		u32 temp = (u32)byte | (u32)byte << 8 |
		           (u32)byte << 16 | (u32)byte << 24;
		while (num_bytes >= 4) {
			vio_writel_aligned(args, offset, temp);
			num_bytes -= 4;
			offset += 4;
		}
	}
#endif /* !CONFIG_VIO_HAS_QWORD */
	assert(num_bytes <= 3);
	if (num_bytes >= 2) {
		u16 temp = (u16)byte | (u16)byte << 8;
		vio_writew_aligned(args, offset, temp);
		num_bytes -= 2;
		offset += 2;
	}
	if (num_bytes) {
		vio_writeb_aligned(args, offset, (u8)byte);
	}
}


#endif /* CONFIG_VIO */

DECL_END

#ifndef __INTELLISENSE__
#ifdef CONFIG_VIO

#define DEFINE_VIO_NAME              xch
#define DEFINE_VIO_OP(oldval, value) value
#include "vio-arith-impl.c.inl"

#define DEFINE_VIO_NAME              add
#define DEFINE_VIO_OP(oldval, value) oldval + value
#include "vio-arith-impl.c.inl"

#define DEFINE_VIO_NAME              sub
#define DEFINE_VIO_OP(oldval, value) oldval - value
#include "vio-arith-impl.c.inl"

#define DEFINE_VIO_NAME              and
#define DEFINE_VIO_OP(oldval, value) oldval & value
#include "vio-arith-impl.c.inl"

#define DEFINE_VIO_NAME              or
#define DEFINE_VIO_OP(oldval, value) oldval | value
#include "vio-arith-impl.c.inl"

#define DEFINE_VIO_NAME              xor
#define DEFINE_VIO_OP(oldval, value) oldval ^ value
#include "vio-arith-impl.c.inl"


#define DEFINE_IO_READ 1
#include "vio-copy.c.inl"
#define DEFINE_IO_WRITE 1
#include "vio-copy.c.inl"

#endif /* CONFIG_VIO */
#endif /* !__INTELLISENSE__ */


#endif /* !GUARD_KERNEL_SRC_MEMORY_VIO_C */
