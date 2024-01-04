/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _I386_KOS_BITS_OS_KOS_MCONTEXT32_H
#define _I386_KOS_BITS_OS_KOS_MCONTEXT32_H 1

/* File:
 *    <i386-kos/bits/os/kos/mcontext32.h>
 *
 * Definitions:
 * #if defined(__KOS__) && __KOS_VERSION__ >= 300
 *    - typedef ... __gregsetx32_t;
 *    - typedef ... __fpregsetx32_t;
 *    - struct __mcontextx32 { ... };
 * #if !defined(__x86_64__) && defined(__i386__)
 *    - typedef ... gregset_t;
 *    - typedef ... fpregset_t;
 *    - struct mcontext { ... };
 * #endif
 * #endif
 *
 */

#include <__stdinc.h>
#if defined(__KOS__) && __KOS_VERSION__ >= 300
#include <features.h>

#include <hybrid/host.h>

#include <bits/types.h>

#ifdef __USE_KOS_KERNEL
#include <kos/kernel/bits/cpu-state32.h>
#include <kos/kernel/bits/fpu-state32.h>
#endif /* __USE_KOS_KERNEL */

#if !defined(__x86_64__) && defined(__i386__)
#define __MCONTEXT_FLAG_NORMAL  __MCONTEXTX32_FLAG_NORMAL
#define __MCONTEXT_FLAG_HAVECR2 __MCONTEXTX32_FLAG_HAVECR2
#define __MCONTEXT_FLAG_HAVEFPU __MCONTEXTX32_FLAG_HAVEFPU
#define __MCONTEXT_REGNO_EDI    __MCONTEXTX32_REGNO_EDI
#define __MCONTEXT_REGNO_ESI    __MCONTEXTX32_REGNO_ESI
#define __MCONTEXT_REGNO_EBP    __MCONTEXTX32_REGNO_EBP
#define __MCONTEXT_REGNO_ESP    __MCONTEXTX32_REGNO_ESP
#define __MCONTEXT_REGNO_EBX    __MCONTEXTX32_REGNO_EBX
#define __MCONTEXT_REGNO_EDX    __MCONTEXTX32_REGNO_EDX
#define __MCONTEXT_REGNO_ECX    __MCONTEXTX32_REGNO_ECX
#define __MCONTEXT_REGNO_EAX    __MCONTEXTX32_REGNO_EAX
#define __MCONTEXT_REGNO_GS     __MCONTEXTX32_REGNO_GS
#define __MCONTEXT_REGNO_FS     __MCONTEXTX32_REGNO_FS
#define __MCONTEXT_REGNO_ES     __MCONTEXTX32_REGNO_ES
#define __MCONTEXT_REGNO_DS     __MCONTEXTX32_REGNO_DS
#define __MCONTEXT_REGNO_CS     __MCONTEXTX32_REGNO_CS
#define __MCONTEXT_REGNO_SS     __MCONTEXTX32_REGNO_SS
#define __MCONTEXT_REGNO_EFL    __MCONTEXTX32_REGNO_EFL
#define __MCONTEXT_REGNO_EIP    __MCONTEXTX32_REGNO_EIP
#define __MCONTEXT_NGREG        __MCONTEXTX32_NGREG

#ifdef __USE_KOS_KERNEL
#define MCONTEXT_FLAG_NORMAL  __MCONTEXT_FLAG_NORMAL
#define MCONTEXT_FLAG_HAVECR2 __MCONTEXT_FLAG_HAVECR2
#define MCONTEXT_FLAG_HAVEFPU __MCONTEXT_FLAG_HAVEFPU
#endif /* __USE_KOS_KERNEL */

#ifdef __USE_GNU
/* Number of each register is the `gregset_t' array. */
#define REG_GS     __MCONTEXTX32_REGNO_GS
#define REG_FS     __MCONTEXTX32_REGNO_FS
#define REG_ES     __MCONTEXTX32_REGNO_ES
#define REG_DS     __MCONTEXTX32_REGNO_DS
#define REG_EDI    __MCONTEXTX32_REGNO_EDI
#define REG_ESI    __MCONTEXTX32_REGNO_ESI
#define REG_EBP    __MCONTEXTX32_REGNO_EBP
#define REG_ESP    __MCONTEXTX32_REGNO_ESP
#define REG_EBX    __MCONTEXTX32_REGNO_EBX
#define REG_EDX    __MCONTEXTX32_REGNO_EDX
#define REG_ECX    __MCONTEXTX32_REGNO_ECX
#define REG_EAX    __MCONTEXTX32_REGNO_EAX
#define REG_EIP    __MCONTEXTX32_REGNO_EIP
#define REG_CS     __MCONTEXTX32_REGNO_CS
#define REG_EFL    __MCONTEXTX32_REGNO_EFL
#define REG_UESP   __MCONTEXTX32_REGNO_ESP
#define REG_SS     __MCONTEXTX32_REGNO_SS
#endif /* __USE_GNU */

#define __OFFSET_MCONTEXT_CPU   __OFFSET_MCONTEXTX32_CPU
#define __OFFSET_MCONTEXT_FPU   __OFFSET_MCONTEXTX32_FPU
#define __OFFSET_MCONTEXT_FLAGS __OFFSET_MCONTEXTX32_FLAGS
#define __OFFSET_MCONTEXT_CR2   __OFFSET_MCONTEXTX32_CR2
#define __SIZEOF_MCONTEXT       __SIZEOF_MCONTEXTX32
#define __ALIGNOF_MCONTEXT      __ALIGNOF_MCONTEXTX32

#define __gregsetx32_t  gregset_t
#define __fpregsetx32_t fpregset_t
#define __mcontextx32   mcontext
#endif /* !__x86_64__ && __i386__ */

__DECL_BEGIN

#define __MCONTEXTX32_FLAG_NORMAL  0x0000 /* Normal context flags. */
#define __MCONTEXTX32_FLAG_HAVECR2 0x0001 /* The `mc_cr2' field contains a valid value. */
#define __MCONTEXTX32_FLAG_HAVEFPU 0x1000 /* The `mc_fpu' structure contains valid data and must be restored.
                                           * When not set: The FPU hasn't been  initialized yet, and a  context
                                           *               load will leave the FPU unmodified if it hasn't been
                                           *               initialized, or will default-initialize itself if it
                                           *               had been initialized in the mean time. */


#define __MCONTEXTX32_REGNO_EDI    0  /* [P] Destination pointer */
#define __MCONTEXTX32_REGNO_ESI    1  /* [P] Source pointer */
#define __MCONTEXTX32_REGNO_EBP    2  /* [P] Frame base pointer */
#define __MCONTEXTX32_REGNO_ESP    3  /* [P] Stack pointer */
#define __MCONTEXTX32_REGNO_EBX    4  /* [P] Base register */
#define __MCONTEXTX32_REGNO_EDX    5  /* [C] Data register */
#define __MCONTEXTX32_REGNO_ECX    6  /* [C] Count register */
#define __MCONTEXTX32_REGNO_EAX    7  /* [C] Accumulator register */
#define __MCONTEXTX32_REGNO_GS     8  /* G segment register (Usually `SEGMENT_USER_GSBASE_RPL') */
#define __MCONTEXTX32_REGNO_FS     9  /* F segment register (Usually `SEGMENT_USER_FSBASE_RPL' / `SEGMENT_KERNEL_FSBASE') */
#define __MCONTEXTX32_REGNO_ES     10 /* E (source) segment register (Usually `SEGMENT_USER_DATA_RPL') */
#define __MCONTEXTX32_REGNO_DS     11 /* D (destination) segment register (Usually `SEGMENT_USER_DATA_RPL') */
#define __MCONTEXTX32_REGNO_CS     12 /* Code segment (Ring #3, usually `SEGMENT_USER_CODE_RPL') */
#define __MCONTEXTX32_REGNO_SS     13 /* Stack segment (Ring #3, usually `SEGMENT_USER_DATA_RPL') */
#define __MCONTEXTX32_REGNO_EFL    14 /* Flags register */
#define __MCONTEXTX32_REGNO_EIP    15 /* Instruction pointer */
#define __MCONTEXTX32_NGREG        16 /* Number of general registers. */


#define __OFFSET_MCONTEXTX32_CPU   0   /* [FIELD(gregs, mc_gregs, mc_context)] */
#define __OFFSET_MCONTEXTX32_FPU   64  /* [FIELD(fpregs, mc_fpu)] */
#define __OFFSET_MCONTEXTX32_FLAGS 576 /* [FIELD(mc_flags)] */
#define __OFFSET_MCONTEXTX32_CR2   580 /* [FIELD(cr2, mc_cr2)] */
#define __SIZEOF_MCONTEXTX32       592
#define __ALIGNOF_MCONTEXTX32      16

#ifdef __CC__
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("gregs")
#pragma push_macro("fpregs")
#pragma push_macro("cr2")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef gregs
#undef fpregs
#undef cr2

typedef __uint32_t __gregsetx32_t[__MCONTEXTX32_NGREG];

#if __KOS_VERSION__ >= 400
typedef __ATTR_ALIGNED(__ALIGNOF_MCONTEXTX32) __byte_t __fpregsetx32_t[512];
#else /* __KOS_VERSION__ >= 400 */
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("significand")
#pragma push_macro("exponent")
#pragma push_macro("cw")
#pragma push_macro("sw")
#pragma push_macro("tag")
#pragma push_macro("ipoff")
#pragma push_macro("cssel")
#pragma push_macro("dataoff")
#pragma push_macro("datasel")
#pragma push_macro("_st")
#pragma push_macro("status")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef significand
#undef exponent
#undef cw
#undef sw
#undef tag
#undef ipoff
#undef cssel
#undef dataoff
#undef datasel
#undef _st
#undef status

struct _libc_fpreg {
	__UINT16_TYPE__    significand[4];
	__UINT16_TYPE__    exponent;
};
struct __ATTR_PACKED _libc_fpstate {
	__UINT16_TYPE__     cw;
	__UINT16_TYPE__     sw;
	__UINT8_TYPE__      tag;
	__UINT8_TYPE__    __pad0[3];
	__UINT32_TYPE__     ipoff;
	__UINT16_TYPE__     cssel;
	__UINT8_TYPE__    __pad1[2];
	__UINT32_TYPE__     dataoff;
	__UINT16_TYPE__     datasel;
	__UINT8_TYPE__    __pad2[2];
	__UINT32_TYPE__     status;
	__UINT8_TYPE__    __pad3[4];
	struct _libc_fpreg  _st[8];
};
typedef struct _libc_fpstate __fpregsetx32_t[1];
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("status")
#pragma pop_macro("_st")
#pragma pop_macro("datasel")
#pragma pop_macro("dataoff")
#pragma pop_macro("cssel")
#pragma pop_macro("ipoff")
#pragma pop_macro("tag")
#pragma pop_macro("sw")
#pragma pop_macro("cw")
#pragma pop_macro("exponent")
#pragma pop_macro("significand")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#endif /* __KOS_VERSION__ < 400 */

/* Machine context. */
struct __ATTR_ALIGNED(__ALIGNOF_MCONTEXTX32) __mcontextx32 /*[NAME(mcontextx32)][PREFIX(mc_)]*/ {
	union {
		__gregsetx32_t         gregs;      /* GLibC API compatibility... */
		__gregsetx32_t         mc_gregs;   /* General purpose register array. */
#ifdef __USE_KOS_KERNEL
		struct ucpustate32     mc_context; /* The user-space CPU context */
#endif /* __USE_KOS_KERNEL */
	};
#ifdef __USE_KOS_KERNEL
	union {
		__fpregsetx32_t        fpregs;     /* GLibC API compatibility... */
		struct fpustate32      mc_fpu;     /* FPU Context. */
	};
#else /* __USE_KOS_KERNEL */
	__fpregsetx32_t            fpregs;     /* GLibC API compatibility... */
#endif /* !__USE_KOS_KERNEL */
	__ULONG32_TYPE__           mc_flags;   /* Set of `__MCONTEXT_F*' */
	union {
		__ULONG32_TYPE__       cr2;        /* GLibC API compatibility... */
		__ULONG32_TYPE__       mc_cr2;     /* The fault address of SIGSEGV. */
	};
	__ULONG32_TYPE__           mc_pad[2];  /* Padding... */
};

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("cr2")
#pragma pop_macro("fpregs")
#pragma pop_macro("gregs")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#endif /* __CC__ */

__DECL_END
#endif /* __KOS__ && __KOS_VERSION__ >= 300 */

#endif /* !_I386_KOS_BITS_OS_KOS_MCONTEXT32_H */
