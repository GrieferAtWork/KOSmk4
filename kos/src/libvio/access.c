/*[[[magic
// Optimize this file for size
local opt = options.setdefault("GCC.options", []);
opt.removeif([](e) -> e.startswith("-O"));
opt.append("-Os");
]]]*/
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
#ifndef GUARD_LIBVIO_ACCESS_C
#define GUARD_LIBVIO_ACCESS_C 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

#include "api.h"
/**/

#ifdef LIBVIO_CONFIG_ENABLED
#include <hybrid/unaligned.h>

#include <kos/except.h>

#include <assert.h>
#include <string.h>

#include "access.h"

#ifdef __KERNEL__
#include <sched/rpc.h>
#include <sched/task.h>
#else /* __KERNEL__ */
#include <hybrid/sched/yield.h>
#endif /* !__KERNEL__ */

#ifdef LIBVIO_CONFIG_HAVE_XWORD_CMPXCH
#include <int128.h>
#endif /* LIBVIO_CONFIG_HAVE_XWORD_CMPXCH */

DECL_BEGIN

#ifdef __KERNEL__
#define LOOPHINT() (task_serve(), task_yield())
#else /* __KERNEL__ */
#define LOOPHINT() SCHED_YIELD()
#endif /* !__KERNEL__ */


PRIVATE ATTR_NORETURN void CC
libvio_illegal_read(struct vioargs const *__restrict args, vio_addr_t addr) {
	THROW(E_SEGFAULT_NOTREADABLE,
	      vioargs_faultaddr(args, addr),
	      E_SEGFAULT_CONTEXT_VIO);
}

PRIVATE ATTR_NORETURN void CC
libvio_illegal_write(struct vioargs const *__restrict args, vio_addr_t addr) {
	THROW(E_SEGFAULT_READONLY,
	      vioargs_faultaddr(args, addr),
	      E_SEGFAULT_CONTEXT_VIO | E_SEGFAULT_CONTEXT_WRITING);
}

#ifdef LIBVIO_CONFIG_HAVE_XWORD_CMPXCH
PRIVATE ATTR_NORETURN void CC
libvio_nonatomic_operation128(struct vioargs const *__restrict args,
                              vio_addr_t addr, uint128_t oldval, uint128_t newval) {
	void *ptr = vioargs_faultaddr(args, addr);
	if ((uintptr_t)ptr & 15) {
		THROW(E_SEGFAULT_UNALIGNED, ptr,
		      E_SEGFAULT_CONTEXT_VIO, 16);
	}
	THROW(E_SEGFAULT_NOTATOMIC, ptr,
	      E_SEGFAULT_CONTEXT_VIO, 16,
	      uint128_vec64_significand(oldval, 0),
	      uint128_vec64_significand(oldval, 1),
	      uint128_vec64_significand(newval, 0),
	      uint128_vec64_significand(newval, 1));
}
#endif /* LIBVIO_CONFIG_HAVE_XWORD_CMPXCH */

#if defined(LIBVIO_CONFIG_HAVE_QWORD) || defined(LIBVIO_CONFIG_HAVE_QWORD_CMPXCH)
PRIVATE ATTR_NORETURN void CC
libvio_nonatomic_operation64(struct vioargs const *__restrict args,
                             vio_addr_t addr, u64 oldval, u64 newval) {
	void *ptr = vioargs_faultaddr(args, addr);
	if ((uintptr_t)ptr & 7) {
		THROW(E_SEGFAULT_UNALIGNED, ptr,
		      E_SEGFAULT_CONTEXT_VIO, 8);
	}
#if __SIZEOF_POINTER__ >= 8
	THROW(E_SEGFAULT_NOTATOMIC, ptr,
	      E_SEGFAULT_CONTEXT_VIO, 8,
	      oldval, 0, newval);
#else /* __SIZEOF_POINTER__ >= 8 */
	THROW(E_SEGFAULT_NOTATOMIC, ptr,
	      E_SEGFAULT_CONTEXT_VIO, 8,
	      (u32)oldval, (u32)(oldval >> 32),
	      (u32)newval, (u32)(newval >> 32));
#endif /* __SIZEOF_POINTER__ < 8 */
}
#endif /* LIBVIO_CONFIG_HAVE_QWORD || LIBVIO_CONFIG_HAVE_QWORD_CMPXCH */

PRIVATE ATTR_NORETURN void CC
libvio_nonatomic_operation32(struct vioargs const *__restrict args,
                             vio_addr_t addr, u32 oldval, u32 newval) {
	void *ptr = vioargs_faultaddr(args, addr);
	if ((uintptr_t)ptr & 3) {
		THROW(E_SEGFAULT_UNALIGNED, ptr,
		      E_SEGFAULT_CONTEXT_VIO, 4);
	}
	THROW(E_SEGFAULT_NOTATOMIC, ptr,
	      E_SEGFAULT_CONTEXT_VIO, 4,
	      oldval, 0, newval);
}

PRIVATE ATTR_NORETURN void CC
libvio_nonatomic_operation16(struct vioargs const *__restrict args,
                             vio_addr_t addr, u16 oldval, u16 newval) {
	void *ptr = vioargs_faultaddr(args, addr);
	if ((uintptr_t)ptr & 1) {
		THROW(E_SEGFAULT_UNALIGNED, ptr,
		      E_SEGFAULT_CONTEXT_VIO, 2);
	}
	THROW(E_SEGFAULT_NOTATOMIC, ptr,
	      E_SEGFAULT_CONTEXT_VIO, 2,
	      oldval, 0, newval);
}

PRIVATE ATTR_NORETURN void CC
libvio_nonatomic_operation8(struct vioargs const *__restrict args,
                            vio_addr_t addr, u8 oldval, u8 newval) {
	void *ptr = vioargs_faultaddr(args, addr);
	THROW(E_SEGFAULT_NOTATOMIC, ptr,
	      E_SEGFAULT_CONTEXT_VIO, 1,
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
#ifdef LIBVIO_CONFIG_HAVE_XWORD_CMPXCH
	uint128_t x;
#endif /* LIBVIO_CONFIG_HAVE_XWORD_CMPXCH */
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

#ifdef LIBVIO_CONFIG_HAVE_QWORD
#define IQ(...) __VA_ARGS__
#else /* LIBVIO_CONFIG_HAVE_QWORD */
#define IQ(...) /* nothing */
#endif /* !LIBVIO_CONFIG_HAVE_QWORD */

/* Naming: [BWLQ][MASK] where MASK is the a mask `addr & mask' describing an offset into `x' */
#define B1     x.b[(uintptr_t)addr & 1]
#define BX1    x.b[((uintptr_t)addr & 1) ^ 1]
#define B3     x.b[(uintptr_t)addr & 3]
#define B7     x.b[(uintptr_t)addr & 7]
#define B15    x.b[(uintptr_t)addr & 15]

#define W2     x.w[((uintptr_t)addr & 2) >> 1]
#define WX2    x.w[(((uintptr_t)addr & 2) ^ 2) >> 1]
#define W3     (*(u16 *)(x.b + ((uintptr_t)addr & 3)))
#define W6     x.w[((uintptr_t)addr & 6) >> 1]
#define W7     (*(u16 *)(x.b + ((uintptr_t)addr & 7)))
#define W14    x.w[((uintptr_t)addr & 14) >> 1]
#define W15    (*(u16 *)(x.b + ((uintptr_t)addr & 15)))

#define L3     (*(u32 *)(x.b + ((uintptr_t)addr & 3)))
#define L4     x.l[((uintptr_t)addr & 4) >> 2]
#define LX4    x.l[(((uintptr_t)addr & 4) ^ 4) >> 2]
#define L7     (*(u32 *)(x.b + ((uintptr_t)addr & 7)))
#define L12    x.l[((uintptr_t)addr & 12) >> 2]
#define L15    (*(u32 *)(x.b + ((uintptr_t)addr & 15)))

#define Q3     (*(u64 *)(x.b + ((uintptr_t)addr & 3)))
#define Q7     (*(u64 *)(x.b + ((uintptr_t)addr & 7)))
#define Q8     x.q[((uintptr_t)addr & 8) >> 3]
#define QX8    x.q[(((uintptr_t)addr & 8) ^ 8) >> 3]
#define Q15    (*(u64 *)(x.b + ((uintptr_t)addr & 15)))

/* Aligned base-addresses */
#define AW     (addr & ~1)  /* word-aligned */
#define AL     (addr & ~3)  /* dword-aligned */
#define AQ     (addr & ~7)  /* qword-aligned */
#define AX     (addr & ~15) /* xword-aligned */



/* Invoke  VIO  callbacks, automatically  substituting operators  for one-another.
 * If an operation is impossible, these functions will throw a SEGFAULT exception. */
INTERN NONNULL((1)) u8 CC
libvio_readb(struct vioargs *__restrict args, vio_addr_t addr) {
	struct vio_ops const *ops = args->va_ops;
	if (ops->vo_read.f_byte) return (*ops->vo_read.f_byte)(args, addr);
	if (ops->vo_read.f_word) { word x = { (*ops->vo_read.f_word)(args, AW) }; return B1; }
	if (ops->vo_read.f_dword) { dword x = { (*ops->vo_read.f_dword)(args, AL) }; return B3; }
	IQ(if (ops->vo_read.f_qword) { qword x = { (*ops->vo_read.f_qword)(args, AQ) }; return B7; })
	if (ops->vo_cmpxch.f_byte) return (*ops->vo_cmpxch.f_byte)(args, addr, 0, 0, false);
	if (ops->vo_cmpxch.f_word) { word x = { (*ops->vo_cmpxch.f_word)(args, AW, 0, 0, false) }; return B1; }
	if (ops->vo_cmpxch.f_dword) { dword x = { (*ops->vo_cmpxch.f_dword)(args, AL, 0, 0, false) }; return B3; }
	IQ(if (ops->vo_cmpxch.f_qword) { qword x = { (*ops->vo_cmpxch.f_qword)(args, AQ, 0, 0, false) }; return B7; })
	if (ops->vo_add.f_byte) return (*ops->vo_add.f_byte)(args, addr, 0, false);
	if (ops->vo_add.f_word) { word x = { (*ops->vo_add.f_word)(args, AW, 0, false) }; return B1; }
	if (ops->vo_add.f_dword) { dword x = { (*ops->vo_add.f_dword)(args, AL, 0, false) }; return B3; }
	IQ(if (ops->vo_add.f_qword) { qword x = { (*ops->vo_add.f_qword)(args, AQ, 0, false) }; return B7; })
	if (ops->vo_sub.f_byte) return (*ops->vo_sub.f_byte)(args, addr, 0, false);
	if (ops->vo_sub.f_word) { word x = { (*ops->vo_sub.f_word)(args, AW, 0, false) }; return B1; }
	if (ops->vo_sub.f_dword) { dword x = { (*ops->vo_sub.f_dword)(args, AL, 0, false) }; return B3; }
	IQ(if (ops->vo_sub.f_qword) { qword x = { (*ops->vo_sub.f_qword)(args, AQ, 0, false) }; return B7; })
	if (ops->vo_and.f_byte) return (*ops->vo_and.f_byte)(args, addr, (u8)~0, false);
	if (ops->vo_and.f_word) { word x = { (*ops->vo_and.f_word)(args, AW, (u16)~0, false) }; return B1; }
	if (ops->vo_and.f_dword) { dword x = { (*ops->vo_and.f_dword)(args, AL, (u32)~0, false) }; return B3; }
	IQ(if (ops->vo_and.f_qword) { qword x = { (*ops->vo_and.f_qword)(args, AQ, ~(u64)0, false) }; return B7; })
	if (ops->vo_or.f_byte) return (*ops->vo_or.f_byte)(args, addr, 0, false);
	if (ops->vo_or.f_word) { word x = { (*ops->vo_or.f_word)(args, AW, 0, false) }; return B1; }
	if (ops->vo_or.f_dword) { dword x = { (*ops->vo_or.f_dword)(args, AL, 0, false) }; return B3; }
	IQ(if (ops->vo_or.f_qword) { qword x = { (*ops->vo_or.f_qword)(args, AQ, 0, false) }; return B7; })
	if (ops->vo_xor.f_byte) return (*ops->vo_xor.f_byte)(args, addr, 0, false);
	if (ops->vo_xor.f_word) { word x = { (*ops->vo_xor.f_word)(args, AW, 0, false) }; return B1; }
	if (ops->vo_xor.f_dword) { dword x = { (*ops->vo_xor.f_dword)(args, AL, 0, false) }; return B3; }
	IQ(if (ops->vo_xor.f_qword) { qword x = { (*ops->vo_xor.f_qword)(args, AQ, 0, false) }; return B7; })
	libvio_illegal_read(args, addr);
}



INTERN NONNULL((1)) u16 CC
libvio_readw(struct vioargs *__restrict args, vio_addr_t addr) {
	struct vio_ops const *ops = args->va_ops;
	if (((uintptr_t)addr & 1) != 1) {
		if (ops->vo_read.f_word) return (*ops->vo_read.f_word)(args, addr);
		if (ops->vo_cmpxch.f_word) return (*ops->vo_cmpxch.f_word)(args, addr, 0, 0, false);
		if (ops->vo_add.f_word) return (*ops->vo_add.f_word)(args, addr, 0, false);
		if (ops->vo_sub.f_word) return (*ops->vo_sub.f_word)(args, addr, 0, false);
		if (ops->vo_and.f_word) return (*ops->vo_and.f_word)(args, addr, (u16)~0, false);
		if (ops->vo_or.f_word) return (*ops->vo_or.f_word)(args, addr, 0, false);
		if (ops->vo_xor.f_word) return (*ops->vo_xor.f_word)(args, addr, 0, false);
	}
	if (((uintptr_t)addr & 3) != 3) {
		if (ops->vo_read.f_dword) { dword x = { (*ops->vo_read.f_dword)(args, AL) }; return W3; }
		if (ops->vo_cmpxch.f_dword) { dword x = { (*ops->vo_cmpxch.f_dword)(args, AL, 0, 0, false) }; return W3; }
		if (ops->vo_add.f_dword) { dword x = { (*ops->vo_add.f_dword)(args, AL, 0, false) }; return W3; }
		if (ops->vo_sub.f_dword) { dword x = { (*ops->vo_sub.f_dword)(args, AL, 0, false) }; return W3; }
		if (ops->vo_and.f_dword) { dword x = { (*ops->vo_and.f_dword)(args, AL, (u32)~0, false) }; return W3; }
		if (ops->vo_or.f_dword) { dword x = { (*ops->vo_or.f_dword)(args, AL, 0, false) }; return W3; }
		if (ops->vo_xor.f_dword) { dword x = { (*ops->vo_xor.f_dword)(args, AL, 0, false) }; return W3; }
	}
#ifdef LIBVIO_CONFIG_HAVE_QWORD
	if (((uintptr_t)addr & 7) != 7) {
		if (ops->vo_read.f_qword) { qword x = { (*ops->vo_read.f_qword)(args, AQ) }; return W7; }
		if (ops->vo_cmpxch.f_qword) { qword x = { (*ops->vo_cmpxch.f_qword)(args, AQ, 0, 0, false) }; return W7; }
		if (ops->vo_add.f_qword) { qword x = { (*ops->vo_add.f_qword)(args, AQ, 0, false) }; return W7; }
		if (ops->vo_sub.f_qword) { qword x = { (*ops->vo_sub.f_qword)(args, AQ, 0, false) }; return W7; }
		if (ops->vo_and.f_qword) { qword x = { (*ops->vo_and.f_qword)(args, AQ, ~(u64)0, false) }; return W7; }
		if (ops->vo_or.f_qword) { qword x = { (*ops->vo_or.f_qword)(args, AQ, 0, false) }; return W7; }
		if (ops->vo_xor.f_qword) { qword x = { (*ops->vo_xor.f_qword)(args, AQ, 0, false) }; return W7; }
	}
#endif /* LIBVIO_CONFIG_HAVE_QWORD */
#define READ_2X_READB(func, ...)                                     \
	if (ops->func.f_byte) {                                          \
		word x;                                                      \
		x.b[0] = (*ops->func.f_byte)(args, addr, ##__VA_ARGS__);     \
		x.b[1] = (*ops->func.f_byte)(args, addr + 1, ##__VA_ARGS__); \
		return x.w;                                                  \
	}
	READ_2X_READB(vo_read)
	READ_2X_READB(vo_cmpxch, 0, 0, false)
	READ_2X_READB(vo_add, 0, false)
	READ_2X_READB(vo_sub, 0, false)
	READ_2X_READB(vo_and, (u8)~0, false)
	READ_2X_READB(vo_or, 0, false)
	READ_2X_READB(vo_xor, 0, false)
#undef READ_2X_READB
#define READ_2X_READW(func, ...)                                     \
	if (ops->func.f_word) {                                          \
		dword x;                                                     \
		x.w[0] = (*ops->func.f_word)(args, addr - 1, ##__VA_ARGS__); \
		x.w[1] = (*ops->func.f_word)(args, addr + 1, ##__VA_ARGS__); \
		return x.w_1;                                                \
	}
	if (((uintptr_t)addr & 1) == 1) {
		READ_2X_READW(vo_read)
		READ_2X_READW(vo_cmpxch, 0, 0, false)
		READ_2X_READW(vo_add, 0, false)
		READ_2X_READW(vo_sub, 0, false)
		READ_2X_READW(vo_and, (u16)~0, false)
		READ_2X_READW(vo_or, 0, false)
		READ_2X_READW(vo_xor, 0, false)
	}
#undef READ_2X_READW
	if (((uintptr_t)addr & 3) == 3) {
#define READ_2X_READL(func, ...)                                          \
		if (ops->func.f_dword) {                                          \
			qword x;                                                      \
			x.l[0] = (*ops->func.f_dword)(args, addr - 3, ##__VA_ARGS__); \
			x.l[1] = (*ops->func.f_dword)(args, addr + 1, ##__VA_ARGS__); \
			return x.w_3;                                                 \
		}
		READ_2X_READL(vo_read)
		READ_2X_READL(vo_cmpxch, 0, 0, false)
		READ_2X_READL(vo_add, 0, false)
		READ_2X_READL(vo_sub, 0, false)
		READ_2X_READL(vo_and, (u32)~0, false)
		READ_2X_READL(vo_or, 0, false)
		READ_2X_READL(vo_xor, 0, false)
	}
#undef READ_2X_READL
#ifdef LIBVIO_CONFIG_HAVE_QWORD
	if (((uintptr_t)addr & 7) == 7) {
#define READ_2X_READQ(func, ...)                                          \
		if (ops->func.f_qword) {                                          \
			xword x;                                                      \
			x.q[0] = (*ops->func.f_qword)(args, addr - 3, ##__VA_ARGS__); \
			x.q[1] = (*ops->func.f_qword)(args, addr + 1, ##__VA_ARGS__); \
			return x.w_7;                                                 \
		}
		READ_2X_READQ(vo_read)
		READ_2X_READQ(vo_cmpxch, 0, 0, false)
		READ_2X_READQ(vo_add, 0, false)
		READ_2X_READQ(vo_sub, 0, false)
		READ_2X_READQ(vo_and, ~(u64)0, false)
		READ_2X_READQ(vo_or, 0, false)
		READ_2X_READQ(vo_xor, 0, false)
	}
#undef READ_2X_READQ
#endif /* LIBVIO_CONFIG_HAVE_QWORD */
	libvio_illegal_read(args, addr);
}

INTERN NONNULL((1)) u32 CC
libvio_readl(struct vioargs *__restrict args, vio_addr_t addr) {
	struct vio_ops const *ops = args->va_ops;
	if (((uintptr_t)addr & 3) == 0) {
		if (ops->vo_read.f_dword) return (*ops->vo_read.f_dword)(args, addr);
		if (ops->vo_cmpxch.f_dword) return (*ops->vo_cmpxch.f_dword)(args, addr, 0, 0, false);
		if (ops->vo_add.f_dword) return (*ops->vo_add.f_dword)(args, addr, 0, false);
		if (ops->vo_sub.f_dword) return (*ops->vo_sub.f_dword)(args, addr, 0, false);
		if (ops->vo_and.f_dword) return (*ops->vo_and.f_dword)(args, addr, (u32)~0, false);
		if (ops->vo_or.f_dword) return (*ops->vo_or.f_dword)(args, addr, 0, false);
		if (ops->vo_xor.f_dword) return (*ops->vo_xor.f_dword)(args, addr, 0, false);
	}
#ifdef LIBVIO_CONFIG_HAVE_QWORD
	if (((uintptr_t)addr & 7) <= 3) {
		if (ops->vo_read.f_qword) { qword x = { (*ops->vo_read.f_qword)(args, AQ) }; return L7; }
		if (ops->vo_cmpxch.f_qword) { qword x = { (*ops->vo_cmpxch.f_qword)(args, AQ, 0, 0, false) }; return L7; }
		if (ops->vo_add.f_qword) { qword x = { (*ops->vo_add.f_qword)(args, AQ, 0, false) }; return L7; }
		if (ops->vo_sub.f_qword) { qword x = { (*ops->vo_sub.f_qword)(args, AQ, 0, false) }; return L7; }
		if (ops->vo_and.f_qword) { qword x = { (*ops->vo_and.f_qword)(args, AQ, ~(u64)0, false) }; return L7; }
		if (ops->vo_or.f_qword) { qword x = { (*ops->vo_or.f_qword)(args, AQ, 0, false) }; return L7; }
		if (ops->vo_xor.f_qword) { qword x = { (*ops->vo_xor.f_qword)(args, AQ, 0, false) }; return L7; }
	}
#endif /* LIBVIO_CONFIG_HAVE_QWORD */
#define READ_2X_READW(func, ...)                                   \
	if (ops->func.f_word) {                                        \
		dword x;                                                   \
		x.w[0] = (*ops->func.f_word)(args, AW, ##__VA_ARGS__);     \
		x.w[1] = (*ops->func.f_word)(args, AW + 2, ##__VA_ARGS__); \
		return x.l;                                                \
	}
	if (((uintptr_t)addr & 1) != 1) {
		READ_2X_READW(vo_read)
		READ_2X_READW(vo_cmpxch, 0, 0, false)
		READ_2X_READW(vo_add, 0, false)
		READ_2X_READW(vo_sub, 0, false)
		READ_2X_READW(vo_and, (u16)~0, false)
		READ_2X_READW(vo_or, 0, false)
		READ_2X_READW(vo_xor, 0, false)
	}
#undef READ_2X_READW
#define READ_2X_READL(func, ...)                                    \
	if (ops->func.f_dword) {                                        \
		qword x;                                                    \
		x.l[0] = (*ops->func.f_dword)(args, AL, ##__VA_ARGS__);     \
		x.l[1] = (*ops->func.f_dword)(args, AL + 4, ##__VA_ARGS__); \
		return L3;                                                  \
	}
	READ_2X_READL(vo_read)
	READ_2X_READL(vo_cmpxch, 0, 0, false)
	READ_2X_READL(vo_add, 0, false)
	READ_2X_READL(vo_sub, 0, false)
	READ_2X_READL(vo_and, (u32)~0, false)
	READ_2X_READL(vo_or, 0, false)
	READ_2X_READL(vo_xor, 0, false)
#undef READ_2X_READL
#ifdef LIBVIO_CONFIG_HAVE_QWORD
#define READ_2X_READQ(func, ...)                                    \
	if (ops->func.f_qword) {                                        \
		xword x;                                                    \
		x.q[0] = (*ops->func.f_qword)(args, AQ, ##__VA_ARGS__);     \
		x.q[1] = (*ops->func.f_qword)(args, AQ + 8, ##__VA_ARGS__); \
		return L7;                                                  \
	}
	READ_2X_READQ(vo_read)
	READ_2X_READQ(vo_cmpxch, 0, 0, false)
	READ_2X_READQ(vo_add, 0, false)
	READ_2X_READQ(vo_sub, 0, false)
	READ_2X_READQ(vo_and, ~(u64)0, false)
	READ_2X_READQ(vo_or, 0, false)
	READ_2X_READQ(vo_xor, 0, false)
#undef READ_2X_READQ
#endif /* LIBVIO_CONFIG_HAVE_QWORD */
#define READ_3X_READW(func, ...)                                     \
	if (ops->func.f_word) {                                          \
		qword x;                                                     \
		x.w[0] = (*ops->func.f_word)(args, addr - 1, ##__VA_ARGS__); \
		x.w[1] = (*ops->func.f_word)(args, addr + 1, ##__VA_ARGS__); \
		x.w[2] = (*ops->func.f_word)(args, addr + 3, ##__VA_ARGS__); \
		return x.l_1;                                                \
	}
	READ_3X_READW(vo_read)
	READ_3X_READW(vo_cmpxch, 0, 0, false)
	READ_3X_READW(vo_add, 0, false)
	READ_3X_READW(vo_sub, 0, false)
	READ_3X_READW(vo_and, (u16)~0, false)
	READ_3X_READW(vo_or, 0, false)
	READ_3X_READW(vo_xor, 0, false)
#undef READ_3X_READW
#define READ_4X_READB(func, ...)                                     \
	if (ops->func.f_byte) {                                          \
		dword x;                                                     \
		x.b[0] = (*ops->func.f_byte)(args, addr + 0, ##__VA_ARGS__); \
		x.b[1] = (*ops->func.f_byte)(args, addr + 1, ##__VA_ARGS__); \
		x.b[2] = (*ops->func.f_byte)(args, addr + 2, ##__VA_ARGS__); \
		x.b[3] = (*ops->func.f_byte)(args, addr + 3, ##__VA_ARGS__); \
		return x.l;                                                  \
	}
	READ_4X_READB(vo_read)
	READ_4X_READB(vo_cmpxch, 0, 0, false)
	READ_4X_READB(vo_add, 0, false)
	READ_4X_READB(vo_sub, 0, false)
	READ_4X_READB(vo_and, (u8)~0, false)
	READ_4X_READB(vo_or, 0, false)
	READ_4X_READB(vo_xor, 0, false)
#undef READ_4X_READB
	libvio_illegal_read(args, addr);
}

INTERN NONNULL((1)) u16 CC
libvio_readw_aligned(struct vioargs *__restrict args, vio_addr_t addr) {
	struct vio_ops const *ops = args->va_ops;
	assert(((uintptr_t)addr & 1) == 0);
	if (ops->vo_read.f_word) return (*ops->vo_read.f_word)(args, addr);
	if (ops->vo_cmpxch.f_word) return (*ops->vo_cmpxch.f_word)(args, addr, 0, 0, false);
	if (ops->vo_add.f_word) return (*ops->vo_add.f_word)(args, addr, 0, false);
	if (ops->vo_sub.f_word) return (*ops->vo_sub.f_word)(args, addr, 0, false);
	if (ops->vo_and.f_word) return (*ops->vo_and.f_word)(args, addr, (u16)~0, false);
	if (ops->vo_or.f_word) return (*ops->vo_or.f_word)(args, addr, 0, false);
	if (ops->vo_xor.f_word) return (*ops->vo_xor.f_word)(args, addr, 0, false);
	if (ops->vo_read.f_dword) { dword x = { (*ops->vo_read.f_dword)(args, AL) }; return W2; }
	if (ops->vo_cmpxch.f_dword) { dword x = { (*ops->vo_cmpxch.f_dword)(args, AL, 0, 0, false) }; return W2; }
	if (ops->vo_add.f_dword) { dword x = { (*ops->vo_add.f_dword)(args, AL, 0, false) }; return W2; }
	if (ops->vo_sub.f_dword) { dword x = { (*ops->vo_sub.f_dword)(args, AL, 0, false) }; return W2; }
	if (ops->vo_and.f_dword) { dword x = { (*ops->vo_and.f_dword)(args, AL, (u32)~0, false) }; return W2; }
	if (ops->vo_or.f_dword) { dword x = { (*ops->vo_or.f_dword)(args, AL, 0, false) }; return W2; }
	if (ops->vo_xor.f_dword) { dword x = { (*ops->vo_xor.f_dword)(args, AL, 0, false) }; return W2; }
#ifdef LIBVIO_CONFIG_HAVE_QWORD
	if (ops->vo_read.f_qword) { qword x = { (*ops->vo_read.f_qword)(args, AQ) }; return W6; }
	if (ops->vo_cmpxch.f_qword) { qword x = { (*ops->vo_cmpxch.f_qword)(args, AQ, 0, 0, false) }; return W6; }
	if (ops->vo_add.f_qword) { qword x = { (*ops->vo_add.f_qword)(args, AQ, 0, false) }; return W6; }
	if (ops->vo_sub.f_qword) { qword x = { (*ops->vo_sub.f_qword)(args, AQ, 0, false) }; return W6; }
	if (ops->vo_and.f_qword) { qword x = { (*ops->vo_and.f_qword)(args, AQ, ~(u64)0, false) }; return W6; }
	if (ops->vo_or.f_qword) { qword x = { (*ops->vo_or.f_qword)(args, AQ, 0, false) }; return W6; }
	if (ops->vo_xor.f_qword) { qword x = { (*ops->vo_xor.f_qword)(args, AQ, 0, false) }; return W6; }
#endif /* LIBVIO_CONFIG_HAVE_QWORD */
#define READ_2X_READB(func, ...)                                     \
	if (ops->func.f_byte) {                                          \
		word x;                                                      \
		x.b[0] = (*ops->func.f_byte)(args, addr, ##__VA_ARGS__);     \
		x.b[1] = (*ops->func.f_byte)(args, addr + 1, ##__VA_ARGS__); \
		return x.w;                                                  \
	}
	READ_2X_READB(vo_read)
	READ_2X_READB(vo_cmpxch, 0, 0, false)
	READ_2X_READB(vo_add, 0, false)
	READ_2X_READB(vo_sub, 0, false)
	READ_2X_READB(vo_and, (u8)~0, false)
	READ_2X_READB(vo_or, 0, false)
	READ_2X_READB(vo_xor, 0, false)
#undef READ_2X_READB
	libvio_illegal_read(args, addr);
}

INTERN NONNULL((1)) u32 CC
libvio_readl_aligned(struct vioargs *__restrict args, vio_addr_t addr) {
	struct vio_ops const *ops = args->va_ops;
	assert(((uintptr_t)addr & 3) == 0);
	if (ops->vo_read.f_dword) return (*ops->vo_read.f_dword)(args, addr);
	if (ops->vo_cmpxch.f_dword) return (*ops->vo_cmpxch.f_dword)(args, addr, 0, 0, false);
	if (ops->vo_add.f_dword) return (*ops->vo_add.f_dword)(args, addr, 0, false);
	if (ops->vo_sub.f_dword) return (*ops->vo_sub.f_dword)(args, addr, 0, false);
	if (ops->vo_and.f_dword) return (*ops->vo_and.f_dword)(args, addr, (u16)~0, false);
	if (ops->vo_or.f_dword) return (*ops->vo_or.f_dword)(args, addr, 0, false);
	if (ops->vo_xor.f_dword) return (*ops->vo_xor.f_dword)(args, addr, 0, false);
#ifdef LIBVIO_CONFIG_HAVE_QWORD
	if (ops->vo_read.f_qword) { qword x = { (*ops->vo_read.f_qword)(args, AQ) }; return L4; }
	if (ops->vo_cmpxch.f_qword) { qword x = { (*ops->vo_cmpxch.f_qword)(args, AQ, 0, 0, false) }; return L4; }
	if (ops->vo_add.f_qword) { qword x = { (*ops->vo_add.f_qword)(args, AQ, 0, false) }; return L4; }
	if (ops->vo_sub.f_qword) { qword x = { (*ops->vo_sub.f_qword)(args, AQ, 0, false) }; return L4; }
	if (ops->vo_and.f_qword) { qword x = { (*ops->vo_and.f_qword)(args, AQ, ~(u64)0, false) }; return L4; }
	if (ops->vo_or.f_qword) { qword x = { (*ops->vo_or.f_qword)(args, AQ, 0, false) }; return L4; }
	if (ops->vo_xor.f_qword) { qword x = { (*ops->vo_xor.f_qword)(args, AQ, 0, false) }; return L4; }
#endif /* LIBVIO_CONFIG_HAVE_QWORD */
#define READ_2X_READW(func, ...)                                     \
	if (ops->func.f_word) {                                          \
		dword x;                                                     \
		x.w[0] = (*ops->func.f_word)(args, addr + 0, ##__VA_ARGS__); \
		x.w[1] = (*ops->func.f_word)(args, addr + 2, ##__VA_ARGS__); \
		return x.l;                                                  \
	}
	READ_2X_READW(vo_read)
	READ_2X_READW(vo_cmpxch, 0, 0, false)
	READ_2X_READW(vo_add, 0, false)
	READ_2X_READW(vo_sub, 0, false)
	READ_2X_READW(vo_and, (u8)~0, false)
	READ_2X_READW(vo_or, 0, false)
	READ_2X_READW(vo_xor, 0, false)
#undef READ_2X_READW
#define READ_4X_READB(func, ...)                                     \
	if (ops->func.f_byte) {                                          \
		dword x;                                                     \
		x.b[0] = (*ops->func.f_byte)(args, addr + 0, ##__VA_ARGS__); \
		x.b[1] = (*ops->func.f_byte)(args, addr + 1, ##__VA_ARGS__); \
		x.b[2] = (*ops->func.f_byte)(args, addr + 2, ##__VA_ARGS__); \
		x.b[3] = (*ops->func.f_byte)(args, addr + 3, ##__VA_ARGS__); \
		return x.l;                                                  \
	}
	READ_4X_READB(vo_read)
	READ_4X_READB(vo_cmpxch, 0, 0, false)
	READ_4X_READB(vo_add, 0, false)
	READ_4X_READB(vo_sub, 0, false)
	READ_4X_READB(vo_and, (u8)~0, false)
	READ_4X_READB(vo_or, 0, false)
	READ_4X_READB(vo_xor, 0, false)
#undef READ_4X_READB
	libvio_illegal_read(args, addr);
}


#ifdef LIBVIO_CONFIG_HAVE_QWORD
INTERN NONNULL((1)) u64 CC
libvio_readq(struct vioargs *__restrict args, vio_addr_t addr) {
	struct vio_ops const *ops = args->va_ops;
	if (((uintptr_t)addr & 7) == 0) {
		if (ops->vo_read.f_qword) return (*ops->vo_read.f_qword)(args, addr);
		if (ops->vo_cmpxch.f_qword) return (*ops->vo_cmpxch.f_qword)(args, addr, 0, 0, false);
		if (ops->vo_add.f_qword) return (*ops->vo_add.f_qword)(args, addr, 0, false);
		if (ops->vo_sub.f_qword) return (*ops->vo_sub.f_qword)(args, addr, 0, false);
		if (ops->vo_and.f_qword) return (*ops->vo_and.f_qword)(args, addr, ~(u64)0, false);
		if (ops->vo_or.f_qword) return (*ops->vo_or.f_qword)(args, addr, 0, false);
		if (ops->vo_xor.f_qword) return (*ops->vo_xor.f_qword)(args, addr, 0, false);
	}
#define READ_2X_READL(func, ...)                                      \
	if (ops->func.f_dword) {                                          \
		qword x;                                                      \
		x.l[0] = (*ops->func.f_dword)(args, addr, ##__VA_ARGS__);     \
		x.l[1] = (*ops->func.f_dword)(args, addr + 4, ##__VA_ARGS__); \
		return x.q;                                                   \
	}
	if (((uintptr_t)addr & 3) == 0) {
		READ_2X_READL(vo_read)
		READ_2X_READL(vo_cmpxch, 0, 0, false)
		READ_2X_READL(vo_add, 0, false)
		READ_2X_READL(vo_sub, 0, false)
		READ_2X_READL(vo_and, (u32)~0, false)
		READ_2X_READL(vo_or, 0, false)
		READ_2X_READL(vo_xor, 0, false)
	}
#undef READ_2X_READL
#define READ_2X_READQ(func, ...)                                    \
	if (ops->func.f_qword) {                                        \
		xword x;                                                    \
		x.q[0] = (*ops->func.f_qword)(args, AQ, ##__VA_ARGS__);     \
		x.q[1] = (*ops->func.f_qword)(args, AQ + 8, ##__VA_ARGS__); \
		return Q7;                                                  \
	}
	READ_2X_READQ(vo_read)
	READ_2X_READQ(vo_cmpxch, 0, 0, false)
	READ_2X_READQ(vo_add, 0, false)
	READ_2X_READQ(vo_sub, 0, false)
	READ_2X_READQ(vo_and, ~(u64)0, false)
	READ_2X_READQ(vo_or, 0, false)
	READ_2X_READQ(vo_xor, 0, false)
#undef READ_2X_READQ
#define READ_3X_READL(func, ...)                                    \
	if (ops->func.f_dword) {                                        \
		xword x;                                                    \
		x.l[0] = (*ops->func.f_dword)(args, AL, ##__VA_ARGS__);     \
		x.l[1] = (*ops->func.f_dword)(args, AL + 4, ##__VA_ARGS__); \
		x.l[2] = (*ops->func.f_dword)(args, AL + 8, ##__VA_ARGS__); \
		return Q3;                                                  \
	}
	READ_3X_READL(vo_read)
	READ_3X_READL(vo_cmpxch, 0, 0, false)
	READ_3X_READL(vo_add, 0, false)
	READ_3X_READL(vo_sub, 0, false)
	READ_3X_READL(vo_and, (u32)~0, false)
	READ_3X_READL(vo_or, 0, false)
	READ_3X_READL(vo_xor, 0, false)
#undef READ_3X_READL
#define READ_4X_READW(func, ...)                                     \
	if (ops->func.f_word) {                                          \
		qword x;                                                     \
		x.w[0] = (*ops->func.f_word)(args, addr, ##__VA_ARGS__);     \
		x.w[1] = (*ops->func.f_word)(args, addr + 2, ##__VA_ARGS__); \
		x.w[2] = (*ops->func.f_word)(args, addr + 4, ##__VA_ARGS__); \
		x.w[3] = (*ops->func.f_word)(args, addr + 6, ##__VA_ARGS__); \
		return x.q;                                                  \
	}
	if (((uintptr_t)addr & 1) == 0) {
		READ_4X_READW(vo_read)
		READ_4X_READW(vo_cmpxch, 0, 0, false)
		READ_4X_READW(vo_add, 0, false)
		READ_4X_READW(vo_sub, 0, false)
		READ_4X_READW(vo_and, (u16)~0, false)
		READ_4X_READW(vo_or, 0, false)
		READ_4X_READW(vo_xor, 0, false)
	}
#undef READ_4X_READW
#define READ_5X_READW(func, ...)                                     \
	if (ops->func.f_word) {                                          \
		xword x;                                                     \
		x.w[0] = (*ops->func.f_word)(args, addr - 1, ##__VA_ARGS__); \
		x.w[1] = (*ops->func.f_word)(args, addr + 1, ##__VA_ARGS__); \
		x.w[2] = (*ops->func.f_word)(args, addr + 3, ##__VA_ARGS__); \
		x.w[3] = (*ops->func.f_word)(args, addr + 5, ##__VA_ARGS__); \
		x.w[3] = (*ops->func.f_word)(args, addr + 7, ##__VA_ARGS__); \
		return x.q_1;                                                \
	}
	READ_5X_READW(vo_read)
	READ_5X_READW(vo_cmpxch, 0, 0, false)
	READ_5X_READW(vo_add, 0, false)
	READ_5X_READW(vo_sub, 0, false)
	READ_5X_READW(vo_and, (u16)~0, false)
	READ_5X_READW(vo_or, 0, false)
	READ_5X_READW(vo_xor, 0, false)
#undef READ_5X_READW
#define READ_8X_READB(func, ...)                                     \
	if (ops->func.f_byte) {                                          \
		qword x;                                                     \
		x.b[0] = (*ops->func.f_byte)(args, addr + 0, ##__VA_ARGS__); \
		x.b[1] = (*ops->func.f_byte)(args, addr + 1, ##__VA_ARGS__); \
		x.b[2] = (*ops->func.f_byte)(args, addr + 2, ##__VA_ARGS__); \
		x.b[3] = (*ops->func.f_byte)(args, addr + 3, ##__VA_ARGS__); \
		x.b[4] = (*ops->func.f_byte)(args, addr + 4, ##__VA_ARGS__); \
		x.b[5] = (*ops->func.f_byte)(args, addr + 5, ##__VA_ARGS__); \
		x.b[6] = (*ops->func.f_byte)(args, addr + 6, ##__VA_ARGS__); \
		x.b[7] = (*ops->func.f_byte)(args, addr + 7, ##__VA_ARGS__); \
		return x.q;                                                  \
	}
	READ_8X_READB(vo_read)
	READ_8X_READB(vo_cmpxch, 0, 0, false)
	READ_8X_READB(vo_add, 0, false)
	READ_8X_READB(vo_sub, 0, false)
	READ_8X_READB(vo_and, (u8)~0, false)
	READ_8X_READB(vo_or, 0, false)
	READ_8X_READB(vo_xor, 0, false)
#undef READ_8X_READB
	libvio_illegal_read(args, addr);
}

INTERN NONNULL((1)) u64 CC
libvio_readq_aligned(struct vioargs *__restrict args, vio_addr_t addr) {
	struct vio_ops const *ops = args->va_ops;
	assert(((uintptr_t)addr & 7) == 0);
	if (ops->vo_read.f_qword) return (*ops->vo_read.f_qword)(args, addr);
	if (ops->vo_cmpxch.f_qword) return (*ops->vo_cmpxch.f_qword)(args, addr, 0, 0, false);
	if (ops->vo_add.f_qword) return (*ops->vo_add.f_qword)(args, addr, 0, false);
	if (ops->vo_sub.f_qword) return (*ops->vo_sub.f_qword)(args, addr, 0, false);
	if (ops->vo_and.f_qword) return (*ops->vo_and.f_qword)(args, addr, ~(u64)0, false);
	if (ops->vo_or.f_qword) return (*ops->vo_or.f_qword)(args, addr, 0, false);
	if (ops->vo_xor.f_qword) return (*ops->vo_xor.f_qword)(args, addr, 0, false);
#define READ_2X_READL(func, ...)                                      \
	if (ops->func.f_dword) {                                          \
		qword x;                                                      \
		x.l[0] = (*ops->func.f_dword)(args, addr, ##__VA_ARGS__);     \
		x.l[1] = (*ops->func.f_dword)(args, addr + 4, ##__VA_ARGS__); \
		return x.q;                                                   \
	}
	READ_2X_READL(vo_read)
	READ_2X_READL(vo_cmpxch, 0, 0, false)
	READ_2X_READL(vo_add, 0, false)
	READ_2X_READL(vo_sub, 0, false)
	READ_2X_READL(vo_and, (u32)~0, false)
	READ_2X_READL(vo_or, 0, false)
	READ_2X_READL(vo_xor, 0, false)
#undef READ_2X_READL
#define READ_4X_READW(func, ...)                                     \
	if (ops->func.f_word) {                                          \
		qword x;                                                     \
		x.w[0] = (*ops->func.f_word)(args, addr, ##__VA_ARGS__);     \
		x.w[1] = (*ops->func.f_word)(args, addr + 2, ##__VA_ARGS__); \
		x.w[2] = (*ops->func.f_word)(args, addr + 4, ##__VA_ARGS__); \
		x.w[3] = (*ops->func.f_word)(args, addr + 6, ##__VA_ARGS__); \
		return x.q;                                                  \
	}
	READ_4X_READW(vo_read)
	READ_4X_READW(vo_cmpxch, 0, 0, false)
	READ_4X_READW(vo_add, 0, false)
	READ_4X_READW(vo_sub, 0, false)
	READ_4X_READW(vo_and, (u16)~0, false)
	READ_4X_READW(vo_or, 0, false)
	READ_4X_READW(vo_xor, 0, false)
#undef READ_4X_READW
#define READ_8X_READB(func, ...)                                     \
	if (ops->func.f_byte) {                                          \
		qword x;                                                     \
		x.b[0] = (*ops->func.f_byte)(args, addr + 0, ##__VA_ARGS__); \
		x.b[1] = (*ops->func.f_byte)(args, addr + 1, ##__VA_ARGS__); \
		x.b[2] = (*ops->func.f_byte)(args, addr + 2, ##__VA_ARGS__); \
		x.b[3] = (*ops->func.f_byte)(args, addr + 3, ##__VA_ARGS__); \
		x.b[4] = (*ops->func.f_byte)(args, addr + 4, ##__VA_ARGS__); \
		x.b[5] = (*ops->func.f_byte)(args, addr + 5, ##__VA_ARGS__); \
		x.b[6] = (*ops->func.f_byte)(args, addr + 6, ##__VA_ARGS__); \
		x.b[7] = (*ops->func.f_byte)(args, addr + 7, ##__VA_ARGS__); \
		return x.q;                                                  \
	}
	READ_8X_READB(vo_read)
	READ_8X_READB(vo_cmpxch, 0, 0, false)
	READ_8X_READB(vo_add, 0, false)
	READ_8X_READB(vo_sub, 0, false)
	READ_8X_READB(vo_and, (u8)~0, false)
	READ_8X_READB(vo_or, 0, false)
	READ_8X_READB(vo_xor, 0, false)
#undef READ_8X_READB
	libvio_illegal_read(args, addr);
}
#endif /* LIBVIO_CONFIG_HAVE_QWORD */


PRIVATE NONNULL((1)) void CC
_do_writeb_vo_cmpxch(struct vio_ops const *__restrict ops,
                     struct vioargs *__restrict args,
                     vio_addr_t addr, u8 value) {
	u8 oldval = 0;
	if (ops->vo_read.f_byte)
		oldval = (*ops->vo_read.f_byte)(args, addr);
	for (;;) {
		u8 real_oldval;
		real_oldval = (*ops->vo_cmpxch.f_byte)(args, addr, oldval, value, false);
		if (real_oldval == oldval)
			break;
		oldval = real_oldval;
		LOOPHINT();
	}
}

PRIVATE NONNULL((1)) void CC
_do_writew_vo_cmpxch(struct vio_ops const *__restrict ops,
                     struct vioargs *__restrict args,
                     vio_addr_t addr, u16 value) {
	u16 oldval = 0;
	if (ops->vo_read.f_word)
		oldval = (*ops->vo_read.f_word)(args, addr);
	for (;;) {
		u16 real_oldval;
		real_oldval = (*ops->vo_cmpxch.f_word)(args, addr, oldval, value, false);
		if (real_oldval == oldval)
			break;
		oldval = real_oldval;
		LOOPHINT();
	}
}

PRIVATE NONNULL((1)) void CC
_do_writel_vo_cmpxch(struct vio_ops const *__restrict ops,
                     struct vioargs *__restrict args,
                     vio_addr_t addr, u32 value) {
	u32 oldval = 0;
	if (ops->vo_read.f_dword)
		oldval = (*ops->vo_read.f_dword)(args, addr);
	for (;;) {
		u32 real_oldval;
		real_oldval = (*ops->vo_cmpxch.f_dword)(args, addr, oldval, value, false);
		if (real_oldval == oldval)
			break;
		oldval = real_oldval;
		LOOPHINT();
	}
}

#if defined(LIBVIO_CONFIG_HAVE_QWORD) || defined(LIBVIO_CONFIG_HAVE_QWORD_CMPXCH)
PRIVATE NONNULL((1)) void CC
_do_writeq_vo_cmpxch(struct vio_ops const *__restrict ops,
                     struct vioargs *__restrict args,
                     vio_addr_t addr, u64 value) {
	u64 oldval = 0;
#ifdef LIBVIO_CONFIG_HAVE_QWORD
	if (ops->vo_read.f_qword)
		oldval = (*ops->vo_read.f_qword)(args, addr);
#endif /* LIBVIO_CONFIG_HAVE_QWORD */
	for (;;) {
		u64 real_oldval;
		real_oldval = (*ops->vo_cmpxch.f_qword)(args, addr, oldval, value, false);
		if (real_oldval == oldval)
			break;
		oldval = real_oldval;
		LOOPHINT();
	}
}
#endif /* LIBVIO_CONFIG_HAVE_QWORD || LIBVIO_CONFIG_HAVE_QWORD_CMPXCH */

#ifdef LIBVIO_CONFIG_HAVE_XWORD_CMPXCH
PRIVATE NONNULL((1)) void CC
_do_writex_vo_cmpxch(struct vio_ops const *__restrict ops,
                     struct vioargs *__restrict args,
                     vio_addr_t addr, uint128_t value) {
	uint128_t oldval;
	uint128_setzero(oldval);
	for (;;) {
		uint128_t real_oldval;
		real_oldval = (*ops->vo_cmpxch.f_xword)(args, addr, oldval, value, false);
		if (int128_eq128(real_oldval, oldval))
			break;
		oldval = real_oldval;
		LOOPHINT();
	}
}
#endif /* LIBVIO_CONFIG_HAVE_XWORD_CMPXCH */

#define do_writeb_vo_write(addr, value)  (*ops->vo_write.f_byte)(args, addr, value)
#define do_writeb_vo_xch(addr, value)    (*ops->vo_xch.f_byte)(args, addr, value, false)
#define do_writeb_vo_cmpxch(addr, value) _do_writeb_vo_cmpxch(ops, args, addr, value)

#define do_writew_vo_write(addr, value)  (*ops->vo_write.f_word)(args, addr, value)
#define do_writew_vo_xch(addr, value)    (*ops->vo_xch.f_word)(args, addr, value, false)
#define do_writew_vo_cmpxch(addr, value) _do_writew_vo_cmpxch(ops, args, addr, value)

#define do_writel_vo_write(addr, value)  (*ops->vo_write.f_dword)(args, addr, value)
#define do_writel_vo_xch(addr, value)    (*ops->vo_xch.f_dword)(args, addr, value, false)
#define do_writel_vo_cmpxch(addr, value) _do_writel_vo_cmpxch(ops, args, addr, value)

#ifdef LIBVIO_CONFIG_HAVE_QWORD
#define do_writeq_vo_write(addr, value)  (*ops->vo_write.f_qword)(args, addr, value)
#define do_writeq_vo_xch(addr, value)    (*ops->vo_xch.f_qword)(args, addr, value, false)
#endif /* LIBVIO_CONFIG_HAVE_QWORD */
#if defined(LIBVIO_CONFIG_HAVE_QWORD) || defined(LIBVIO_CONFIG_HAVE_QWORD_CMPXCH)
#define do_writeq_vo_cmpxch(addr, value) _do_writeq_vo_cmpxch(ops, args, addr, value)
#endif /* LIBVIO_CONFIG_HAVE_QWORD || LIBVIO_CONFIG_HAVE_QWORD_CMPXCH */
#ifdef LIBVIO_CONFIG_HAVE_XWORD_CMPXCH
#define do_writex_vo_cmpxch(addr, value) _do_writex_vo_cmpxch(ops, args, addr, value)
#endif /* LIBVIO_CONFIG_HAVE_XWORD_CMPXCH */

#ifndef __INTELLISENSE__
DECL_END

#define WRITE_METHOD vo_write
#include "access-write.c.inl"

#define WRITE_METHOD vo_xch
#include "access-write.c.inl"

#define WRITE_METHOD vo_cmpxch
#include "access-write.c.inl"

DECL_BEGIN
#endif /* !__INTELLISENSE__ */

INTERN NONNULL((1)) void CC
libvio_writeb(struct vioargs *__restrict args, vio_addr_t addr, u8 value) {
	struct vio_ops const *ops = args->va_ops;
#ifndef __INTELLISENSE__
	if (libvio_writeb_vo_write(ops, args, addr, value))
		return;
	if (libvio_writeb_vo_xch(ops, args, addr, value))
		return;
	if (libvio_writeb_vo_cmpxch(ops, args, addr, value))
		return;
#endif /* !__INTELLISENSE__ */
	libvio_illegal_write(args, addr);
}


INTERN NONNULL((1)) void CC
libvio_writew(struct vioargs *__restrict args, vio_addr_t addr, u16 value) {
	struct vio_ops const *ops = args->va_ops;
#ifndef __INTELLISENSE__
	if (libvio_writew_vo_write(ops, args, addr, value))
		return;
	if (libvio_writew_vo_xch(ops, args, addr, value))
		return;
	if (libvio_writew_vo_cmpxch(ops, args, addr, value))
		return;
#endif /* !__INTELLISENSE__ */
	libvio_illegal_write(args, addr);
}

INTERN NONNULL((1)) void CC
libvio_writew_aligned(struct vioargs *__restrict args, vio_addr_t addr, u16 value) {
	struct vio_ops const *ops = args->va_ops;
#ifndef __INTELLISENSE__
	if (libvio_writew_aligned_vo_write(ops, args, addr, value))
		return;
	if (libvio_writew_aligned_vo_xch(ops, args, addr, value))
		return;
	if (libvio_writew_aligned_vo_cmpxch(ops, args, addr, value))
		return;
#endif /* !__INTELLISENSE__ */
	libvio_illegal_write(args, addr);
}

INTERN NONNULL((1)) void CC
libvio_writel(struct vioargs *__restrict args,
              vio_addr_t addr, u32 value) {
	struct vio_ops const *ops = args->va_ops;
#ifndef __INTELLISENSE__
	if (libvio_writel_vo_write(ops, args, addr, value))
		return;
	if (libvio_writel_vo_xch(ops, args, addr, value))
		return;
	if (libvio_writel_vo_cmpxch(ops, args, addr, value))
		return;
#endif /* !__INTELLISENSE__ */
	libvio_illegal_write(args, addr);
}

INTERN NONNULL((1)) void CC
libvio_writel_aligned(struct vioargs *__restrict args,
                      vio_addr_t addr, u32 value) {
	struct vio_ops const *ops = args->va_ops;
#ifndef __INTELLISENSE__
	if (libvio_writel_aligned_vo_write(ops, args, addr, value))
		return;
	if (libvio_writel_aligned_vo_xch(ops, args, addr, value))
		return;
	if (libvio_writel_aligned_vo_cmpxch(ops, args, addr, value))
		return;
#endif /* !__INTELLISENSE__ */
	libvio_illegal_write(args, addr);
}

#ifdef LIBVIO_CONFIG_HAVE_QWORD
INTERN NONNULL((1)) void CC
libvio_writeq(struct vioargs *__restrict args,
              vio_addr_t addr, u64 value) {
	struct vio_ops const *ops = args->va_ops;
#ifndef __INTELLISENSE__
	if (libvio_writeq_vo_write(ops, args, addr, value))
		return;
	if (libvio_writeq_vo_xch(ops, args, addr, value))
		return;
	if (libvio_writeq_vo_cmpxch(ops, args, addr, value))
		return;
#endif /* !__INTELLISENSE__ */
	libvio_illegal_write(args, addr);
}
INTERN NONNULL((1)) void CC
libvio_writeq_aligned(struct vioargs *__restrict args,
                      vio_addr_t addr, u64 value) {
	struct vio_ops const *ops = args->va_ops;
#ifndef __INTELLISENSE__
	if (libvio_writeq_aligned_vo_write(ops, args, addr, value))
		return;
	if (libvio_writeq_aligned_vo_xch(ops, args, addr, value))
		return;
	if (libvio_writeq_aligned_vo_cmpxch(ops, args, addr, value))
		return;
#endif /* !__INTELLISENSE__ */
	libvio_illegal_write(args, addr);
}
#endif /* LIBVIO_CONFIG_HAVE_QWORD */


INTERN NONNULL((1)) u8 CC
libvio_cmpxchb(struct vioargs *__restrict args,
               vio_addr_t addr, u8 oldvalue, u8 newvalue, bool atomic) {
	struct vio_ops const *ops = args->va_ops;
	if (ops->vo_cmpxch.f_byte)
		return (*ops->vo_cmpxch.f_byte)(args, addr, oldvalue, newvalue, atomic);
	if (ops->vo_cmpxch.f_word) {
		word oldval, oldval2, newval;
		oldval.b[((uintptr_t)addr ^ 1) & 1] = libvio_readb(args, addr ^ 1);
		oldval.b[(uintptr_t)addr & 1]       = oldvalue;
		newval                              = oldval;
		newval.b[(uintptr_t)addr & 1]       = newvalue;
		while ((oldval2.w = (*ops->vo_cmpxch.f_word)(args, addr & ~1, oldval.w, newval.w, atomic)) != oldval.w) {
			oldval = newval = oldval2;
			oldval.b[(uintptr_t)addr & 1] = oldvalue;
			newval.b[(uintptr_t)addr & 1] = newvalue;
		}
		return oldval2.b[(uintptr_t)addr & 1];
	}
	if (ops->vo_cmpxch.f_dword) {
		dword oldval, oldval2, newval;
		oldval.l                      = libvio_readl(args, addr & ~3);
		oldval.b[(uintptr_t)addr & 3] = oldvalue;
		newval                        = oldval;
		newval.b[(uintptr_t)addr & 3] = newvalue;
		while ((oldval2.l = (*ops->vo_cmpxch.f_dword)(args, addr & ~3, oldval.l, newval.l, atomic)) != oldval.l) {
			oldval = newval = oldval2;
			oldval.b[(uintptr_t)addr & 3] = oldvalue;
			newval.b[(uintptr_t)addr & 3] = newvalue;
		}
		return oldval2.b[(uintptr_t)addr & 3];
	}
#if defined(LIBVIO_CONFIG_HAVE_QWORD) || defined(LIBVIO_CONFIG_HAVE_QWORD_CMPXCH)
	if (ops->vo_cmpxch.f_qword) {
		qword oldval, oldval2, newval;
#ifdef LIBVIO_CONFIG_HAVE_QWORD
		oldval.q = libvio_readq(args, addr & ~7);
#else /* LIBVIO_CONFIG_HAVE_QWORD */
		oldval.l[0] = libvio_readl(args, (addr & ~7));
		oldval.l[1] = libvio_readl(args, (addr & ~7) + 4);
#endif /* !LIBVIO_CONFIG_HAVE_QWORD */
		oldval.b[(uintptr_t)addr & 7] = oldvalue;
		newval                        = oldval;
		newval.b[(uintptr_t)addr & 7] = newvalue;
		while ((oldval2.q = (*ops->vo_cmpxch.f_qword)(args, addr & ~7, oldval.q, newval.q, atomic)) != oldval.q) {
			oldval = newval = oldval2;
			oldval.b[(uintptr_t)addr & 7] = oldvalue;
			newval.b[(uintptr_t)addr & 7] = newvalue;
		}
		return oldval2.b[(uintptr_t)addr & 7];
	}
#endif /* LIBVIO_CONFIG_HAVE_QWORD || LIBVIO_CONFIG_HAVE_QWORD_CMPXCH */
	/* Non-atomic compare-exchange */
	if (atomic)
		libvio_nonatomic_operation8(args, addr, oldvalue, newvalue);
	{
		u8 result = libvio_readb(args, addr);
		if (result == oldvalue)
			libvio_writeb(args, addr, newvalue);
		return result;
	}
}


INTERN NONNULL((1)) u16 CC
libvio_cmpxchw(struct vioargs *__restrict args,
               vio_addr_t addr, u16 oldvalue, u16 newvalue, bool atomic) {
	struct vio_ops const *ops = args->va_ops;
	if (ops->vo_cmpxch.f_word && ((uintptr_t)addr & 1) == 0)
		return (*ops->vo_cmpxch.f_word)(args, addr, oldvalue, newvalue, atomic);
	if (ops->vo_cmpxch.f_dword && ((uintptr_t)addr & 3) <= 2) {
		dword oldval, oldval2, newval;
		oldval.l                                          = libvio_readl(args, addr & ~3);
		(*(u16 *)((u8 *)&oldval + ((uintptr_t)addr & 3))) = oldvalue;
		newval                                            = oldval;
		(*(u16 *)((u8 *)&newval + ((uintptr_t)addr & 3))) = oldvalue;
		while ((oldval2.l = (*ops->vo_cmpxch.f_dword)(args, addr & ~3, oldval.l, newval.l, atomic)) != oldval.l) {
			oldval = newval = oldval2;
			(*(u16 *)((u8 *)&oldval + ((uintptr_t)addr & 3))) = oldvalue;
			(*(u16 *)((u8 *)&newval + ((uintptr_t)addr & 3))) = oldvalue;
		}
		return (*(u16 *)((u8 *)&oldval2 + ((uintptr_t)addr & 3)));
	}
#if defined(LIBVIO_CONFIG_HAVE_QWORD) || defined(LIBVIO_CONFIG_HAVE_QWORD_CMPXCH)
	if (ops->vo_cmpxch.f_qword && ((uintptr_t)addr & 7) <= 6) {
		qword oldval, oldval2, newval;
#ifdef LIBVIO_CONFIG_HAVE_QWORD
		oldval.q = libvio_readq(args, addr & ~7);
#else /* LIBVIO_CONFIG_HAVE_QWORD */
		oldval.l[0] = libvio_readl(args, (addr & ~7));
		oldval.l[1] = libvio_readl(args, (addr & ~7) + 4);
#endif /* !LIBVIO_CONFIG_HAVE_QWORD */
		(*(u16 *)((u8 *)&oldval + ((uintptr_t)addr & 7))) = oldvalue;
		newval                                            = oldval;
		(*(u16 *)((u8 *)&newval + ((uintptr_t)addr & 7))) = newvalue;
		while ((oldval2.q = (*ops->vo_cmpxch.f_qword)(args, addr & ~7, oldval.q, newval.q, atomic)) != oldval.q) {
			oldval = newval = oldval2;
			(*(u16 *)((u8 *)&oldval + ((uintptr_t)addr & 7))) = oldvalue;
			(*(u16 *)((u8 *)&newval + ((uintptr_t)addr & 7))) = newvalue;
		}
		return (*(u16 *)((u8 *)&oldval2 + ((uintptr_t)addr & 7)));
	}
#endif /* LIBVIO_CONFIG_HAVE_QWORD || LIBVIO_CONFIG_HAVE_QWORD_CMPXCH */
	/* Non-atomic compare-exchange */
	if (atomic)
		libvio_nonatomic_operation16(args, addr, oldvalue, newvalue);
	{
		u16 result = libvio_readw(args, addr);
		if (result == oldvalue)
			libvio_writew(args, addr, newvalue);
		return result;
	}
}


INTERN NONNULL((1)) u32 CC
libvio_cmpxchl(struct vioargs *__restrict args,
               vio_addr_t addr, u32 oldvalue, u32 newvalue, bool atomic) {
	struct vio_ops const *ops = args->va_ops;
	if (ops->vo_cmpxch.f_dword && ((uintptr_t)addr & 3) == 0)
		return (*ops->vo_cmpxch.f_dword)(args, addr, oldvalue, newvalue, atomic);
#if defined(LIBVIO_CONFIG_HAVE_QWORD) || defined(LIBVIO_CONFIG_HAVE_QWORD_CMPXCH)
	if (ops->vo_cmpxch.f_qword && ((uintptr_t)addr & 7) <= 4) {
		qword oldval, oldval2, newval;
#ifdef LIBVIO_CONFIG_HAVE_QWORD
		oldval.q = libvio_readq(args, addr & ~7);
#else /* LIBVIO_CONFIG_HAVE_QWORD */
		oldval.l[0] = libvio_readl(args, (addr & ~7));
		oldval.l[1] = libvio_readl(args, (addr & ~7) + 4);
#endif /* !LIBVIO_CONFIG_HAVE_QWORD */
		(*(u32 *)((u8 *)&oldval + ((uintptr_t)addr & 7))) = oldvalue;
		newval                                            = oldval;
		(*(u32 *)((u8 *)&newval + ((uintptr_t)addr & 7))) = newvalue;
		while ((oldval2.q = (*ops->vo_cmpxch.f_qword)(args, addr & ~7, oldval.q, newval.q, atomic)) != oldval.q) {
			oldval = newval = oldval2;
			(*(u32 *)((u8 *)&oldval + ((uintptr_t)addr & 7))) = oldvalue;
			(*(u32 *)((u8 *)&newval + ((uintptr_t)addr & 7))) = newvalue;
		}
		return (*(u32 *)((u8 *)&oldval2 + ((uintptr_t)addr & 7)));
	}
#endif /* LIBVIO_CONFIG_HAVE_QWORD || LIBVIO_CONFIG_HAVE_QWORD_CMPXCH */
	/* Non-atomic compare-exchange */
	if (atomic)
		libvio_nonatomic_operation32(args, addr, oldvalue, newvalue);
	{
		u32 result = libvio_readl(args, addr);
		if (result == oldvalue)
			libvio_writel(args, addr, newvalue);
		return result;
	}
}

#if defined(LIBVIO_CONFIG_HAVE_QWORD) || defined(LIBVIO_CONFIG_HAVE_QWORD_CMPXCH)
INTERN NONNULL((1)) u64 CC
libvio_cmpxchq(struct vioargs *__restrict args,
               vio_addr_t addr, u64 oldvalue, u64 newvalue, bool atomic) {
	struct vio_ops const *ops = args->va_ops;
	if (ops->vo_cmpxch.f_qword && ((uintptr_t)addr & 7) == 0)
		return (*ops->vo_cmpxch.f_qword)(args, addr, oldvalue, newvalue, atomic);
	/* Non-atomic compare-exchange */
	if (atomic)
		libvio_nonatomic_operation64(args, addr, oldvalue, newvalue);
	{
#ifdef LIBVIO_CONFIG_HAVE_QWORD
		u64 result = libvio_readq(args, addr);
		if (result == oldvalue)
			libvio_writeq(args, addr, newvalue);
		return result;
#else /* LIBVIO_CONFIG_HAVE_QWORD */
		qword result;
		result.l[0] = libvio_readl(args, addr);
		result.l[1] = libvio_readl(args, addr + 4);
		if (result.q == oldvalue) {
			result.q = newvalue;
			libvio_writel(args, addr + 0, result.l[0]);
			libvio_writel(args, addr + 4, result.l[1]);
		}
		return oldvalue;
#endif /* !LIBVIO_CONFIG_HAVE_QWORD */
	}
}
#endif /* LIBVIO_CONFIG_HAVE_QWORD || LIBVIO_CONFIG_HAVE_QWORD_CMPXCH */

#ifdef LIBVIO_CONFIG_HAVE_XWORD_CMPXCH
INTERN NONNULL((1)) uint128_t CC
libvio_cmpxchx(struct vioargs *__restrict args,
               vio_addr_t addr, uint128_t oldvalue,
               uint128_t newvalue, bool atomic) {
	struct vio_ops const *ops = args->va_ops;
	if (ops->vo_cmpxch.f_xword && ((uintptr_t)addr & 15) == 0)
		return (*ops->vo_cmpxch.f_xword)(args, addr, oldvalue, newvalue, atomic);
	/* Non-atomic compare-exchange */
	if (atomic)
		libvio_nonatomic_operation128(args, addr, oldvalue, newvalue);
	{
		union {
			uint128_t x;
			u64       q[2];
			u32       l[4];
		} result;
#ifdef LIBVIO_CONFIG_HAVE_QWORD
		result.q[0] = libvio_readq(args, addr + 0);
		result.q[1] = libvio_readq(args, addr + 8);
		if (bcmp(&result, &oldvalue, 16) == 0) {
			libvio_writeq(args, addr + 0, uint128_vec64(newvalue)[0]);
			libvio_writeq(args, addr + 8, uint128_vec64(newvalue)[1]);
		}
#else /* LIBVIO_CONFIG_HAVE_QWORD */
		result.l[0] = libvio_readl(args, addr + 0);
		result.l[1] = libvio_readl(args, addr + 4);
		result.l[2] = libvio_readl(args, addr + 8);
		result.l[3] = libvio_readl(args, addr + 12);
		if (bcmp(&result, &oldvalue, 16) == 0) {
			libvio_writel(args, addr + 0,  uint128_vec32(newvalue)[0]);
			libvio_writel(args, addr + 4,  uint128_vec32(newvalue)[1]);
			libvio_writel(args, addr + 8,  uint128_vec32(newvalue)[2]);
			libvio_writel(args, addr + 12, uint128_vec32(newvalue)[3]);
		}
#endif /* !LIBVIO_CONFIG_HAVE_QWORD */
		return result.x;
	}
}
#endif /* LIBVIO_CONFIG_HAVE_XWORD_CMPXCH */

INTERN NONNULL((1)) u8 CC
libvio_cmpxch_or_writeb(struct vioargs *__restrict args,
                        vio_addr_t addr, u8 oldvalue,
                        u8 newvalue, bool atomic) {
	struct vio_ops const *ops = args->va_ops;
	if (ops->vo_cmpxch.f_byte)
		return (*ops->vo_cmpxch.f_byte)(args, addr, oldvalue, newvalue, atomic);
	if (ops->vo_cmpxch.f_word) {
		word oldval, oldval2, newval;
		oldval.b[((uintptr_t)addr ^ 1) & 1] = libvio_readb(args, addr ^ 1);
		oldval.b[(uintptr_t)addr & 1]       = oldvalue;
		newval                              = oldval;
		newval.b[(uintptr_t)addr & 1]       = newvalue;
		while ((oldval2.w = (*ops->vo_cmpxch.f_word)(args, addr & ~1, oldval.w, newval.w, atomic)) != oldval.w) {
			oldval = newval = oldval2;
			oldval.b[(uintptr_t)addr & 1] = oldvalue;
			newval.b[(uintptr_t)addr & 1] = newvalue;
		}
		return oldval2.b[(uintptr_t)addr & 1];
	}
	if (ops->vo_cmpxch.f_dword) {
		dword oldval, oldval2, newval;
		oldval.l                      = libvio_readl(args, addr & ~3);
		oldval.b[(uintptr_t)addr & 3] = oldvalue;
		newval                        = oldval;
		newval.b[(uintptr_t)addr & 3] = newvalue;
		while ((oldval2.l = (*ops->vo_cmpxch.f_dword)(args, addr & ~3, oldval.l, newval.l, atomic)) != oldval.l) {
			oldval = newval = oldval2;
			oldval.b[(uintptr_t)addr & 3] = oldvalue;
			newval.b[(uintptr_t)addr & 3] = newvalue;
		}
		return oldval2.b[(uintptr_t)addr & 3];
	}
#if defined(LIBVIO_CONFIG_HAVE_QWORD) || defined(LIBVIO_CONFIG_HAVE_QWORD_CMPXCH)
	if (ops->vo_cmpxch.f_qword) {
		qword oldval, oldval2, newval;
#ifdef LIBVIO_CONFIG_HAVE_QWORD
		oldval.q = libvio_readq(args, addr & ~7);
#else /* LIBVIO_CONFIG_HAVE_QWORD */
		oldval.l[0] = libvio_readl(args, (addr & ~7));
		oldval.l[1] = libvio_readl(args, (addr & ~7) + 4);
#endif /* !LIBVIO_CONFIG_HAVE_QWORD */
		oldval.b[(uintptr_t)addr & 7] = oldvalue;
		newval                        = oldval;
		newval.b[(uintptr_t)addr & 7] = newvalue;
		while ((oldval2.q = (*ops->vo_cmpxch.f_qword)(args, addr & ~7, oldval.q, newval.q, atomic)) != oldval.q) {
			oldval = newval = oldval2;
			oldval.b[(uintptr_t)addr & 7] = oldvalue;
			newval.b[(uintptr_t)addr & 7] = newvalue;
		}
		return oldval2.b[(uintptr_t)addr & 7];
	}
#endif /* LIBVIO_CONFIG_HAVE_QWORD || LIBVIO_CONFIG_HAVE_QWORD_CMPXCH */
	/* Non-atomic compare-exchange */
	if (atomic)
		libvio_nonatomic_operation8(args, addr, oldvalue, newvalue);
	libvio_writeb(args, addr, newvalue);
	return oldvalue;
}


INTERN NONNULL((1)) u16 CC
libvio_cmpxch_or_writew(struct vioargs *__restrict args,
                     vio_addr_t addr, u16 oldvalue,
                     u16 newvalue, bool atomic) {
	struct vio_ops const *ops = args->va_ops;
	if (ops->vo_cmpxch.f_word && ((uintptr_t)addr & 1) == 0)
		return (*ops->vo_cmpxch.f_word)(args, addr, oldvalue, newvalue, atomic);
	if (ops->vo_cmpxch.f_dword && ((uintptr_t)addr & 3) <= 2) {
		dword oldval, oldval2, newval;
		oldval.l                                          = libvio_readl(args, addr & ~3);
		(*(u16 *)((u8 *)&oldval + ((uintptr_t)addr & 3))) = oldvalue;
		newval                                            = oldval;
		(*(u16 *)((u8 *)&newval + ((uintptr_t)addr & 3))) = oldvalue;
		while ((oldval2.l = (*ops->vo_cmpxch.f_dword)(args, addr & ~3, oldval.l, newval.l, atomic)) != oldval.l) {
			oldval = newval = oldval2;
			(*(u16 *)((u8 *)&oldval + ((uintptr_t)addr & 3))) = oldvalue;
			(*(u16 *)((u8 *)&newval + ((uintptr_t)addr & 3))) = oldvalue;
		}
		return (*(u16 *)((u8 *)&oldval2 + ((uintptr_t)addr & 3)));
	}
#if defined(LIBVIO_CONFIG_HAVE_QWORD) || defined(LIBVIO_CONFIG_HAVE_QWORD_CMPXCH)
	if (ops->vo_cmpxch.f_qword && ((uintptr_t)addr & 7) <= 6) {
		qword oldval, oldval2, newval;
#ifdef LIBVIO_CONFIG_HAVE_QWORD
		oldval.q = libvio_readq(args, addr & ~7);
#else /* LIBVIO_CONFIG_HAVE_QWORD */
		oldval.l[0] = libvio_readl(args, (addr & ~7));
		oldval.l[1] = libvio_readl(args, (addr & ~7) + 4);
#endif /* !LIBVIO_CONFIG_HAVE_QWORD */
		(*(u16 *)((u8 *)&oldval + ((uintptr_t)addr & 7))) = oldvalue;
		newval                                            = oldval;
		(*(u16 *)((u8 *)&newval + ((uintptr_t)addr & 7))) = newvalue;
		while ((oldval2.q = (*ops->vo_cmpxch.f_qword)(args, addr & ~7, oldval.q, newval.q, atomic)) != oldval.q) {
			oldval = newval = oldval2;
			(*(u16 *)((u8 *)&oldval + ((uintptr_t)addr & 7))) = oldvalue;
			(*(u16 *)((u8 *)&newval + ((uintptr_t)addr & 7))) = newvalue;
		}
		return (*(u16 *)((u8 *)&oldval2 + ((uintptr_t)addr & 7)));
	}
#endif /* LIBVIO_CONFIG_HAVE_QWORD || LIBVIO_CONFIG_HAVE_QWORD_CMPXCH */
	/* Non-atomic compare-exchange */
	if (atomic)
		libvio_nonatomic_operation16(args, addr, oldvalue, newvalue);
	libvio_writew(args, addr, newvalue);
	return oldvalue;
}


INTERN NONNULL((1)) u32 CC
libvio_cmpxch_or_writel(struct vioargs *__restrict args,
                        vio_addr_t addr, u32 oldvalue,
                        u32 newvalue, bool atomic) {
	struct vio_ops const *ops = args->va_ops;
	if (ops->vo_cmpxch.f_dword && ((uintptr_t)addr & 3) == 0)
		return (*ops->vo_cmpxch.f_dword)(args, addr, oldvalue, newvalue, atomic);
#if defined(LIBVIO_CONFIG_HAVE_QWORD) || defined(LIBVIO_CONFIG_HAVE_QWORD_CMPXCH)
	if (ops->vo_cmpxch.f_qword && ((uintptr_t)addr & 7) <= 4) {
		qword oldval, oldval2, newval;
#ifdef LIBVIO_CONFIG_HAVE_QWORD
		oldval.q = libvio_readq(args, addr & ~7);
#else /* LIBVIO_CONFIG_HAVE_QWORD */
		oldval.l[0] = libvio_readl(args, (addr & ~7));
		oldval.l[1] = libvio_readl(args, (addr & ~7) + 4);
#endif /* !LIBVIO_CONFIG_HAVE_QWORD */
		(*(u32 *)((u8 *)&oldval + ((uintptr_t)addr & 7))) = oldvalue;
		newval                                            = oldval;
		(*(u32 *)((u8 *)&newval + ((uintptr_t)addr & 7))) = newvalue;
		while ((oldval2.q = (*ops->vo_cmpxch.f_qword)(args, addr & ~7, oldval.q, newval.q, atomic)) != oldval.q) {
			oldval = newval = oldval2;
			(*(u32 *)((u8 *)&oldval + ((uintptr_t)addr & 7))) = oldvalue;
			(*(u32 *)((u8 *)&newval + ((uintptr_t)addr & 7))) = newvalue;
		}
		return (*(u32 *)((u8 *)&oldval2 + ((uintptr_t)addr & 7)));
	}
#endif /* LIBVIO_CONFIG_HAVE_QWORD || LIBVIO_CONFIG_HAVE_QWORD_CMPXCH */
	/* Non-atomic compare-exchange */
	if (atomic)
		libvio_nonatomic_operation32(args, addr, oldvalue, newvalue);
	libvio_writel(args, addr, newvalue);
	return oldvalue;
}

#ifdef LIBVIO_CONFIG_HAVE_QWORD
INTERN NONNULL((1)) u64 CC
libvio_cmpxch_or_writeq(struct vioargs *__restrict args,
                        vio_addr_t addr, u64 oldvalue,
                        u64 newvalue, bool atomic) {
	struct vio_ops const *ops = args->va_ops;
	if (ops->vo_cmpxch.f_qword && ((uintptr_t)addr & 7) == 0)
		return (*ops->vo_cmpxch.f_qword)(args, addr, oldvalue, newvalue, atomic);
	/* Non-atomic compare-exchange */
	if (atomic)
		libvio_nonatomic_operation64(args, addr, oldvalue, newvalue);
	libvio_writeq(args, addr, newvalue);
	return oldvalue;
}
#endif /* LIBVIO_CONFIG_HAVE_QWORD */



/* Copy memory to/from VIO, or exchange memory with VIO
 * NOTE: `oldbuf' and `newbuf' may no overlap, though with the exception that they are allowed to be identical */
INTERN NONNULL((1)) void CC
libvio_xchwithvio(struct vioargs *__restrict args,
                  vio_addr_t offset,
                  NCX void *oldbuf,
                  NCX void const *newbuf,
                  size_t num_bytes, bool atomic)
		THROWS(E_SEGFAULT, ...) {
	if (!num_bytes)
		return;
	if (offset & 1) {
		u8 temp;
		temp = libvio_xchb(args, offset, UNALIGNED_GET8(newbuf), atomic);
		UNALIGNED_SET8(oldbuf, temp);
		oldbuf = (byte_t *)oldbuf + 1;
		newbuf = (byte_t const *)newbuf + 1;
		--num_bytes;
		++offset;
	}
	if ((offset & 2) && num_bytes >= 2) {
		u16 temp;
		temp = libvio_xchw(args, offset, UNALIGNED_GET16(oldbuf), atomic);
		UNALIGNED_SET16(oldbuf, temp);
		oldbuf = (byte_t *)oldbuf + 2;
		newbuf = (byte_t const *)newbuf + 2;
		num_bytes -= 2;
		offset += 2;
	}
#ifdef LIBVIO_CONFIG_HAVE_QWORD
	if ((offset & 4) && num_bytes >= 4) {
		u32 temp;
		temp = libvio_xchl(args, offset, UNALIGNED_GET32(oldbuf), atomic);
		UNALIGNED_SET32(oldbuf, temp);
		oldbuf = (byte_t *)oldbuf + 4;
		newbuf = (byte_t const *)newbuf + 4;
		num_bytes -= 4;
		offset += 4;
	}
	while (num_bytes >= 8) {
		u64 temp;
		temp = libvio_xchq(args, offset, UNALIGNED_GET64(oldbuf), atomic);
		UNALIGNED_SET64(oldbuf, temp);
		oldbuf = (byte_t *)oldbuf + 8;
		newbuf = (byte_t const *)newbuf + 8;
		num_bytes -= 8;
		offset += 8;
	}
	if (num_bytes >= 4) {
		u32 temp;
		temp = libvio_xchl(args, offset, UNALIGNED_GET32(oldbuf), atomic);
		UNALIGNED_SET32(oldbuf, temp);
		oldbuf = (byte_t *)oldbuf + 4;
		newbuf = (byte_t const *)newbuf + 4;
		num_bytes -= 4;
		offset += 4;
	}
#else /* LIBVIO_CONFIG_HAVE_QWORD */
	while (num_bytes >= 4) {
		u32 temp;
		temp = libvio_xchl(args, offset, UNALIGNED_GET32(oldbuf), atomic);
		UNALIGNED_SET32(oldbuf, temp);
		oldbuf = (byte_t *)oldbuf + 4;
		newbuf = (byte_t const *)newbuf + 4;
		num_bytes -= 4;
		offset += 4;
	}
#endif /* !LIBVIO_CONFIG_HAVE_QWORD */
	assert(num_bytes <= 3);
	if (num_bytes >= 2) {
		u16 temp;
		temp = libvio_xchw(args, offset, UNALIGNED_GET16(oldbuf), atomic);
		UNALIGNED_SET16(oldbuf, temp);
		oldbuf = (byte_t *)oldbuf + 2;
		newbuf = (byte_t const *)newbuf + 2;
		num_bytes -= 2;
		offset += 2;
	}
	if (num_bytes) {
		u8 temp;
		temp = libvio_xchb(args, offset, UNALIGNED_GET8(oldbuf), atomic);
		UNALIGNED_SET8(oldbuf, temp);
	}
}

INTERN NONNULL((1)) void CC
libvio_copyfromvio(struct vioargs *__restrict args,
                   vio_addr_t offset,
                   NCX void *buf,
                   size_t num_bytes)
		THROWS(E_SEGFAULT, ...) {
	if (!num_bytes)
		return;
	if (offset & 1) {
#if defined(LIBVIO_CONFIG_HAVE_QWORD) && __SIZEOF_BUSINT__ >= 8
		if (!(offset & 6) && num_bytes >= 7) {
			/* Of a word:    WWWWWWWW
			 * we only want:  RRRRRRR */
			qword q;
			q.q = libvio_readq_aligned(args, offset - 1);
			buf = mempcpy(buf, q.b + 1, 7);
			num_bytes -= 7;
			offset += 7;
		} else if (!(offset & 4) && num_bytes >= 5) {
			/* Of a word:    WWWWWWWW
			 * we only want:    RRRRR */
			qword q;
			q.q = libvio_readq_aligned(args, offset - 3);
			buf = mempcpy(buf, q.b + 3, 5);
			num_bytes -= 5;
			offset += 5;
		} else
#endif /* LIBVIO_CONFIG_HAVE_QWORD && __SIZEOF_BUSINT__ >= 8 */
#if __SIZEOF_BUSINT__ >= 4
		if (!(offset & 2) && num_bytes >= 3) {
			/* Of a word:    WWWW
			 * we only want:  RRR */
			dword d;
			d.l = libvio_readl_aligned(args, offset - 1);
			memcpy(buf, d.b + 1, 3);
			buf = (byte_t *)buf + 3;
			num_bytes -= 3;
			offset += 3;
		} else
#endif /* __SIZEOF_BUSINT__ >= 4 */
		{
			u8 temp;
			temp = libvio_readb_aligned(args, offset);
			*(u8 *)buf = temp;
			buf = (byte_t *)buf + 1;
			--num_bytes;
			++offset;
		}
	}
	if ((offset & 2) && num_bytes >= 2) {
#if defined(LIBVIO_CONFIG_HAVE_QWORD) && __SIZEOF_BUSINT__ >= 8
		if (!(offset & 4) && num_bytes >= 6) {
			/* Of a word:    WWWWWWWW
			 * we only want:   RRRRRR */
			qword q;
			q.q = libvio_readq_aligned(args, offset - 2);
			buf = mempcpy(buf, q.b + 2, 6);
			num_bytes -= 6;
			offset += 6;
		} else
#endif /* LIBVIO_CONFIG_HAVE_QWORD && __SIZEOF_BUSINT__ >= 8 */
		{
			u16 temp;
			temp = libvio_readw_aligned(args, offset);
			UNALIGNED_SET16(buf, temp);
			buf = (byte_t *)buf + 2;
			num_bytes -= 2;
			offset += 2;
		}
	}
#ifdef LIBVIO_CONFIG_HAVE_QWORD
	if ((offset & 4) && num_bytes >= 4) {
		u32 temp = libvio_readl_aligned(args, offset);
		UNALIGNED_SET32(buf, temp);
		buf = (byte_t *)buf + 4;
		num_bytes -= 4;
		offset += 4;
	}
	while (num_bytes >= 8) {
		u64 temp = libvio_readq_aligned(args, offset);
		UNALIGNED_SET64(buf, temp);
		buf = (byte_t *)buf + 8;
		num_bytes -= 8;
		offset += 8;
	}
	if (num_bytes >= 4) {
		u32 temp;
#if __SIZEOF_BUSINT__ >= 8
		if (num_bytes > 4 && (offset & 7) == 0) {
			/* Optimization: Only perform a single dispatch by doing an 8-byte read! */
			qword q;
			q.q = libvio_readq_aligned(args, offset);
			__builtin_assume(num_bytes == 5 ||
			                 num_bytes == 6 ||
			                 num_bytes == 7);
			memcpy(buf, q.b, num_bytes);
			return;
		}
#endif /* __SIZEOF_BUSINT__ >= 8 */
		temp = libvio_readl_aligned(args, offset);
		UNALIGNED_SET32(buf, temp);
		buf = (byte_t *)buf + 4;
		num_bytes -= 4;
		offset += 4;
	}
#else /* LIBVIO_CONFIG_HAVE_QWORD */
	while (num_bytes >= 4) {
		u32 temp = libvio_readl_aligned(args, offset);
		UNALIGNED_SET32(buf, temp);
		buf = (byte_t *)buf + 4;
		num_bytes -= 4;
		offset += 4;
	}
#endif /* !LIBVIO_CONFIG_HAVE_QWORD */
	assert(num_bytes <= 3);
	if (num_bytes >= 2) {
		u16 temp;
#if __SIZEOF_BUSINT__ >= 4
		if (num_bytes == 3 && (offset & 3) == 0) {
			/* Optimization: Only perform a single dispatch by doing a 4-byte read! */
			dword d;
			d.l = libvio_readl_aligned(args, offset);
			memcpy(buf, d.b, 3);
			return;
		}
#endif /* __SIZEOF_BUSINT__ >= 4 */
		temp = libvio_readw_aligned(args, offset);
		UNALIGNED_SET16(buf, temp);
		buf = (byte_t *)buf + 2;
		num_bytes -= 2;
		offset += 2;
	}
	if (num_bytes) {
		u8 temp = libvio_readb_aligned(args, offset);
		*(u8 *)buf = temp;
	}
}

INTERN NONNULL((1)) void CC
libvio_copytovio(struct vioargs *__restrict args,
                 vio_addr_t offset,
                 NCX void const *buf,
                 size_t num_bytes)
		THROWS(E_SEGFAULT, ...) {
	if (!num_bytes)
		return;
	if (offset & 1) {
		u8 temp = UNALIGNED_GET8(buf);
		libvio_writeb_aligned(args, offset, temp);
		buf = (byte_t *)buf + 1;
		--num_bytes;
		++offset;
	}
	if ((offset & 2) && num_bytes >= 2) {
		u16 temp = UNALIGNED_GET16(buf);
		libvio_writew_aligned(args, offset, temp);
		buf = (byte_t *)buf + 2;
		num_bytes -= 2;
		offset += 2;
	}
#ifdef LIBVIO_CONFIG_HAVE_QWORD
	if ((offset & 4) && num_bytes >= 4) {
		u32 temp = UNALIGNED_GET32(buf);
		libvio_writel_aligned(args, offset, temp);
		buf = (byte_t *)buf + 4;
		num_bytes -= 4;
		offset += 4;
	}
	while (num_bytes >= 8) {
		u64 temp = UNALIGNED_GET64(buf);
		libvio_writeq_aligned(args, offset, temp);
		buf = (byte_t *)buf + 8;
		num_bytes -= 8;
		offset += 8;
	}
	if (num_bytes >= 4) {
		u32 temp = UNALIGNED_GET32(buf);
		libvio_writel_aligned(args, offset, temp);
		buf = (byte_t *)buf + 4;
		num_bytes -= 4;
		offset += 4;
	}
#else /* LIBVIO_CONFIG_HAVE_QWORD */
	while (num_bytes >= 4) {
		u32 temp = UNALIGNED_GET32(buf);
		libvio_writel_aligned(args, offset, temp);
		buf = (byte_t *)buf + 4;
		num_bytes -= 4;
		offset += 4;
	}
#endif /* !LIBVIO_CONFIG_HAVE_QWORD */
	assert(num_bytes <= 3);
	if (num_bytes >= 2) {
		u16 temp = UNALIGNED_GET16(buf);
		libvio_writew_aligned(args, offset, temp);
		buf = (byte_t *)buf + 2;
		num_bytes -= 2;
		offset += 2;
	}
	if (num_bytes) {
		u8 temp = UNALIGNED_GET8(buf);
		libvio_writeb_aligned(args, offset, temp);
	}
}

INTERN NONNULL((1)) void CC
libvio_memset(struct vioargs *__restrict args,
              vio_addr_t offset,
              int byte,
              size_t num_bytes)
		THROWS(E_SEGFAULT, ...) {
	if (!num_bytes)
		return;
	if (offset & 1) {
		libvio_writeb_aligned(args, offset, (u8)byte);
		--num_bytes;
		++offset;
	}
	if ((offset & 2) && num_bytes >= 2) {
		u16 temp = (u16)byte | (u16)byte << 8;
		libvio_writew_aligned(args, offset, temp);
		num_bytes -= 2;
		offset += 2;
	}
#ifdef LIBVIO_CONFIG_HAVE_QWORD
	if ((offset & 4) && num_bytes >= 4) {
		u32 temp = (u32)byte | (u32)byte << 8 |
		           (u32)byte << 16 | (u32)byte << 24;
		libvio_writel_aligned(args, offset, temp);
		num_bytes -= 4;
		offset += 4;
	}
	if (num_bytes >= 8) {
		u64 temp = (u64)byte | (u64)byte << 8 |
		           (u64)byte << 16 | (u64)byte << 24 |
		           (u64)byte << 32 | (u64)byte << 40 |
		           (u64)byte << 48 | (u64)byte << 56;
		while (num_bytes >= 8) {
			libvio_writeq_aligned(args, offset, temp);
			num_bytes -= 8;
			offset += 8;
		}
	}
	if (num_bytes >= 4) {
		u32 temp = (u32)byte | (u32)byte << 8 |
		           (u32)byte << 16 | (u32)byte << 24;
		libvio_writel_aligned(args, offset, temp);
		num_bytes -= 4;
		offset += 4;
	}
#else /* LIBVIO_CONFIG_HAVE_QWORD */
	if (num_bytes >= 4) {
		u32 temp = (u32)byte | (u32)byte << 8 |
		           (u32)byte << 16 | (u32)byte << 24;
		while (num_bytes >= 4) {
			libvio_writel_aligned(args, offset, temp);
			num_bytes -= 4;
			offset += 4;
		}
	}
#endif /* !LIBVIO_CONFIG_HAVE_QWORD */
	assert(num_bytes <= 3);
	if (num_bytes >= 2) {
		u16 temp = (u16)byte | (u16)byte << 8;
		libvio_writew_aligned(args, offset, temp);
		num_bytes -= 2;
		offset += 2;
	}
	if (num_bytes) {
		libvio_writeb_aligned(args, offset, (u8)byte);
	}
}

DECL_END

#ifndef __INTELLISENSE__

#define DEFINE_VIO_NAME              xch
#define DEFINE_VIO_OP(oldval, value) value
#include "access-arith-impl.c.inl"

#define DEFINE_VIO_NAME              add
#define DEFINE_VIO_OP(oldval, value) oldval + value
#include "access-arith-impl.c.inl"

#define DEFINE_VIO_NAME              sub
#define DEFINE_VIO_OP(oldval, value) oldval - value
#include "access-arith-impl.c.inl"

#define DEFINE_VIO_NAME              and
#define DEFINE_VIO_OP(oldval, value) oldval & value
#include "access-arith-impl.c.inl"

#define DEFINE_VIO_NAME              or
#define DEFINE_VIO_OP(oldval, value) oldval | value
#include "access-arith-impl.c.inl"

#define DEFINE_VIO_NAME              xor
#define DEFINE_VIO_OP(oldval, value) oldval ^ value
#include "access-arith-impl.c.inl"


#define DEFINE_IO_READ 1
#include "access-copy.c.inl"
#define DEFINE_IO_WRITE 1
#include "access-copy.c.inl"

#endif /* !__INTELLISENSE__ */

DECL_BEGIN

DEFINE_PUBLIC_ALIAS(vio_readb, libvio_readb);
DEFINE_PUBLIC_ALIAS(vio_readw, libvio_readw);
DEFINE_PUBLIC_ALIAS(vio_readl, libvio_readl);
DEFINE_PUBLIC_ALIAS(vio_writeb, libvio_writeb);
DEFINE_PUBLIC_ALIAS(vio_writew, libvio_writew);
DEFINE_PUBLIC_ALIAS(vio_writel, libvio_writel);
DEFINE_PUBLIC_ALIAS(vio_cmpxchb, libvio_cmpxchb);
DEFINE_PUBLIC_ALIAS(vio_cmpxchw, libvio_cmpxchw);
DEFINE_PUBLIC_ALIAS(vio_cmpxchl, libvio_cmpxchl);
DEFINE_PUBLIC_ALIAS(vio_cmpxch_or_writeb, libvio_cmpxch_or_writeb);
DEFINE_PUBLIC_ALIAS(vio_cmpxch_or_writew, libvio_cmpxch_or_writew);
DEFINE_PUBLIC_ALIAS(vio_cmpxch_or_writel, libvio_cmpxch_or_writel);
DEFINE_PUBLIC_ALIAS(vio_xchb, libvio_xchb);
DEFINE_PUBLIC_ALIAS(vio_xchw, libvio_xchw);
DEFINE_PUBLIC_ALIAS(vio_xchl, libvio_xchl);
DEFINE_PUBLIC_ALIAS(vio_addb, libvio_addb);
DEFINE_PUBLIC_ALIAS(vio_addw, libvio_addw);
DEFINE_PUBLIC_ALIAS(vio_addl, libvio_addl);
DEFINE_PUBLIC_ALIAS(vio_subb, libvio_subb);
DEFINE_PUBLIC_ALIAS(vio_subw, libvio_subw);
DEFINE_PUBLIC_ALIAS(vio_subl, libvio_subl);
DEFINE_PUBLIC_ALIAS(vio_andb, libvio_andb);
DEFINE_PUBLIC_ALIAS(vio_andw, libvio_andw);
DEFINE_PUBLIC_ALIAS(vio_andl, libvio_andl);
DEFINE_PUBLIC_ALIAS(vio_orb, libvio_orb);
DEFINE_PUBLIC_ALIAS(vio_orw, libvio_orw);
DEFINE_PUBLIC_ALIAS(vio_orl, libvio_orl);
DEFINE_PUBLIC_ALIAS(vio_xorb, libvio_xorb);
DEFINE_PUBLIC_ALIAS(vio_xorw, libvio_xorw);
DEFINE_PUBLIC_ALIAS(vio_xorl, libvio_xorl);
DEFINE_PUBLIC_ALIAS(vio_xchwithvio, libvio_xchwithvio);
DEFINE_PUBLIC_ALIAS(vio_copyfromvio, libvio_copyfromvio);
DEFINE_PUBLIC_ALIAS(vio_copytovio, libvio_copytovio);
DEFINE_PUBLIC_ALIAS(vio_memset, libvio_memset);
DEFINE_PUBLIC_ALIAS(vio_readw_aligned, libvio_readw_aligned);
DEFINE_PUBLIC_ALIAS(vio_readl_aligned, libvio_readl_aligned);
DEFINE_PUBLIC_ALIAS(vio_writew_aligned, libvio_writew_aligned);
DEFINE_PUBLIC_ALIAS(vio_writel_aligned, libvio_writel_aligned);
#ifdef __KERNEL__
DEFINE_PUBLIC_ALIAS(vio_copyfromvio_to_phys, libvio_copyfromvio_to_phys);
DEFINE_PUBLIC_ALIAS(vio_copytovio_from_phys, libvio_copytovio_from_phys);
#endif /* __KERNEL__ */
#ifdef LIBVIO_CONFIG_HAVE_QWORD
DEFINE_PUBLIC_ALIAS(vio_cmpxch_or_writeq, libvio_cmpxch_or_writeq);
DEFINE_PUBLIC_ALIAS(vio_readq, libvio_readq);
DEFINE_PUBLIC_ALIAS(vio_writeq, libvio_writeq);
DEFINE_PUBLIC_ALIAS(vio_xchq, libvio_xchq);
DEFINE_PUBLIC_ALIAS(vio_addq, libvio_addq);
DEFINE_PUBLIC_ALIAS(vio_subq, libvio_subq);
DEFINE_PUBLIC_ALIAS(vio_andq, libvio_andq);
DEFINE_PUBLIC_ALIAS(vio_orq, libvio_orq);
DEFINE_PUBLIC_ALIAS(vio_xorq, libvio_xorq);
DEFINE_PUBLIC_ALIAS(vio_readq_aligned, libvio_readq_aligned);
DEFINE_PUBLIC_ALIAS(vio_writeq_aligned, libvio_writeq_aligned);
#endif /* LIBVIO_CONFIG_HAVE_QWORD */
#if defined(LIBVIO_CONFIG_HAVE_QWORD) || defined(LIBVIO_CONFIG_HAVE_QWORD_CMPXCH)
DEFINE_PUBLIC_ALIAS(vio_cmpxchq, libvio_cmpxchq);
#endif /* LIBVIO_CONFIG_HAVE_QWORD || LIBVIO_CONFIG_HAVE_QWORD_CMPXCH */
#ifdef LIBVIO_CONFIG_HAVE_XWORD_CMPXCH
DEFINE_PUBLIC_ALIAS(vio_cmpxchx, libvio_cmpxchx);
#endif /* LIBVIO_CONFIG_HAVE_XWORD_CMPXCH */

DECL_END

#endif /* LIBVIO_CONFIG_ENABLED */

#endif /* !GUARD_LIBVIO_ACCESS_C */
