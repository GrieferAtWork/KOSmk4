/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/*!replace_with_include <bits/os/mcontext.h>*/
#ifndef _I386_KOS_BITS_OS_KOS_MCONTEXT64_H
#define _I386_KOS_BITS_OS_KOS_MCONTEXT64_H 1

/* File:
 *    <i386-kos/bits/os/kos/mcontext64.h>
 *
 * Definitions:
 * #ifdef __KOS__
 *    - typedef ... __gregsetx64_t;
 *    - typedef ... __fpregsetx64_t;
 *    - struct __mcontextx64 { ... };
 * #ifdef __x86_64__
 *    - typedef ... gregset_t;
 *    - typedef ... fpregset_t;
 *    - struct mcontext { ... };
 * #endif
 * #endif
 *
 */

#include <__stdinc.h>
#ifdef __KOS__
#include <features.h>

#include <hybrid/host.h>

#include <bits/types.h>

#ifdef __USE_KOS_KERNEL
#include <kos/kernel/bits/cpu-state64.h>
#include <kos/kernel/bits/fpu-state64.h>
#endif /* __USE_KOS_KERNEL */


#ifdef __x86_64__
#define __MCONTEXT_FLAG_NORMAL  __MCONTEXTX64_FLAG_NORMAL
#define __MCONTEXT_FLAG_HAVECR2 __MCONTEXTX64_FLAG_HAVECR2
#define __MCONTEXT_FLAG_HAVEFPU __MCONTEXTX64_FLAG_HAVEFPU
#define __MCONTEXT_REGNO_GSBASE __MCONTEXTX64_REGNO_GSBASE
#define __MCONTEXT_REGNO_FSBASE __MCONTEXTX64_REGNO_FSBASE
#define __MCONTEXT_REGNO_R15    __MCONTEXTX64_REGNO_R15
#define __MCONTEXT_REGNO_R14    __MCONTEXTX64_REGNO_R14
#define __MCONTEXT_REGNO_R13    __MCONTEXTX64_REGNO_R13
#define __MCONTEXT_REGNO_R12    __MCONTEXTX64_REGNO_R12
#define __MCONTEXT_REGNO_R11    __MCONTEXTX64_REGNO_R11
#define __MCONTEXT_REGNO_R10    __MCONTEXTX64_REGNO_R10
#define __MCONTEXT_REGNO_R9     __MCONTEXTX64_REGNO_R9
#define __MCONTEXT_REGNO_R8     __MCONTEXTX64_REGNO_R8
#define __MCONTEXT_REGNO_RDI    __MCONTEXTX64_REGNO_RDI
#define __MCONTEXT_REGNO_RSI    __MCONTEXTX64_REGNO_RSI
#define __MCONTEXT_REGNO_RBP    __MCONTEXTX64_REGNO_RBP
#define __MCONTEXT_REGNO_RSP    __MCONTEXTX64_REGNO_RSP
#define __MCONTEXT_REGNO_RBX    __MCONTEXTX64_REGNO_RBX
#define __MCONTEXT_REGNO_RDX    __MCONTEXTX64_REGNO_RDX
#define __MCONTEXT_REGNO_RCX    __MCONTEXTX64_REGNO_RCX
#define __MCONTEXT_REGNO_RAX    __MCONTEXTX64_REGNO_RAX
#define __MCONTEXT_REGNO_GS     __MCONTEXTX64_REGNO_GS
#define __MCONTEXT_REGNO_FS     __MCONTEXTX64_REGNO_FS
#define __MCONTEXT_REGNO_ES     __MCONTEXTX64_REGNO_ES
#define __MCONTEXT_REGNO_DS     __MCONTEXTX64_REGNO_DS
#define __MCONTEXT_REGNO_CS     __MCONTEXTX64_REGNO_CS
#define __MCONTEXT_REGNO_SS     __MCONTEXTX64_REGNO_SS
#define __MCONTEXT_REGNO_RFLAGS __MCONTEXTX64_REGNO_RFLAGS
#define __MCONTEXT_REGNO_RIP    __MCONTEXTX64_REGNO_RIP
#define __MCONTEXT_NGREG        __MCONTEXTX64_NGREG

#ifdef __USE_KOS_KERNEL
#define MCONTEXT_FLAG_NORMAL  __MCONTEXT_FLAG_NORMAL
#define MCONTEXT_FLAG_HAVECR2 __MCONTEXT_FLAG_HAVECR2
#define MCONTEXT_FLAG_HAVEFPU __MCONTEXT_FLAG_HAVEFPU
#endif /* __USE_KOS_KERNEL */
#ifdef __USE_GNU
/* Number of each register is the `gregset_t' array. */
#define REG_R8   __MCONTEXT_REGNO_R8
#define REG_R9   __MCONTEXT_REGNO_R9
#define REG_R10  __MCONTEXT_REGNO_R10
#define REG_R11  __MCONTEXT_REGNO_R11
#define REG_R12  __MCONTEXT_REGNO_R12
#define REG_R13  __MCONTEXT_REGNO_R13
#define REG_R14  __MCONTEXT_REGNO_R14
#define REG_R15  __MCONTEXT_REGNO_R15
#define REG_RDI  __MCONTEXT_REGNO_RDI
#define REG_RSI  __MCONTEXT_REGNO_RSI
#define REG_RBP  __MCONTEXT_REGNO_RBP
#define REG_RBX  __MCONTEXT_REGNO_RBX
#define REG_RDX  __MCONTEXT_REGNO_RDX
#define REG_RAX  __MCONTEXT_REGNO_RAX
#define REG_RCX  __MCONTEXT_REGNO_RCX
#define REG_RSP  __MCONTEXT_REGNO_RSP
#define REG_RIP  __MCONTEXT_REGNO_RIP
#define REG_EFL  __MCONTEXT_REGNO_RFLAGS
#define REG_CR2  (__OFFSET_MCONTEXTX64_CR2 / 8)
#endif /* __USE_GNU */

#define __OFFSET_MCONTEXT_CPU   __OFFSET_MCONTEXTX64_CPU
#define __OFFSET_MCONTEXT_FPU   __OFFSET_MCONTEXTX64_FPU
#define __OFFSET_MCONTEXT_FLAGS __OFFSET_MCONTEXTX64_FLAGS
#define __OFFSET_MCONTEXT_CR2   __OFFSET_MCONTEXTX64_CR2
#define __SIZEOF_MCONTEXT       __SIZEOF_MCONTEXTX64
#define __ALIGNOF_MCONTEXT      __ALIGNOF_MCONTEXTX64

#define __gregsetx64_t  gregset_t
#define __fpregsetx64_t fpregset_t
#define __mcontextx64   mcontext
#endif /* __x86_64__ */

__DECL_BEGIN

#define __MCONTEXTX64_FLAG_NORMAL  0x0000 /* Normal context flags. */
#define __MCONTEXTX64_FLAG_HAVECR2 0x0001 /* The `mc_cr2' field contains a valid value. */
#define __MCONTEXTX64_FLAG_HAVEFPU 0x1000 /* The `mc_fpu' structure contains valid data and must be restored.
                                           * When not set: The FPU hasn't been  initialized yet, and a  context
                                           *               load will leave the FPU unmodified if it hasn't been
                                           *               initialized, or will default-initialize itself if it
                                           *               had been initialized in the mean time. */


#define __MCONTEXTX64_REGNO_GS      0
#define __MCONTEXTX64_REGNO_FS      1
#define __MCONTEXTX64_REGNO_ES      2
#define __MCONTEXTX64_REGNO_DS      3
#define __MCONTEXTX64_REGNO_GSBASE  4
#define __MCONTEXTX64_REGNO_FSBASE  5
#define __MCONTEXTX64_REGNO_CS      6
#define __MCONTEXTX64_REGNO_SS      7
#define __MCONTEXTX64_REGNO_R15     8
#define __MCONTEXTX64_REGNO_R14     9
#define __MCONTEXTX64_REGNO_R13     10
#define __MCONTEXTX64_REGNO_R12     11
#define __MCONTEXTX64_REGNO_R11     12
#define __MCONTEXTX64_REGNO_R10     13
#define __MCONTEXTX64_REGNO_R9      14
#define __MCONTEXTX64_REGNO_R8      15
#define __MCONTEXTX64_REGNO_RDI     16
#define __MCONTEXTX64_REGNO_RSI     17
#define __MCONTEXTX64_REGNO_RBP     18
#define __MCONTEXTX64_REGNO_RSP     19
#define __MCONTEXTX64_REGNO_RBX     20
#define __MCONTEXTX64_REGNO_RDX     21
#define __MCONTEXTX64_REGNO_RCX     22
#define __MCONTEXTX64_REGNO_RAX     23
#define __MCONTEXTX64_REGNO_RFLAGS  24
#define __MCONTEXTX64_REGNO_RIP     25
#define __MCONTEXTX64_NGREG         26

#define __OFFSET_MCONTEXTX64_CPU   0   /* [FIELD(gregs, mc_gregs, mc_context)] */
#define __OFFSET_MCONTEXTX64_FPU   208 /* [FIELD(fpregs, mc_fpu)] */
#define __OFFSET_MCONTEXTX64_FLAGS 720 /* [FIELD(mc_flags)] */
#define __OFFSET_MCONTEXTX64_CR2   728 /* [FIELD(cr2, mc_cr2)] */
#define __SIZEOF_MCONTEXTX64       736
#define __ALIGNOF_MCONTEXTX64      16

#ifdef __CC__
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("gregs")
#pragma push_macro("fpregs")
#pragma push_macro("cr2")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef gregs
#undef fpregs
#undef cr2

typedef __uint64_t __gregsetx64_t[__MCONTEXTX64_NGREG];
typedef __ATTR_ALIGNED(__ALIGNOF_MCONTEXTX64) __byte_t __fpregsetx64_t[512];

/* Machine context. */
struct __ATTR_ALIGNED(__ALIGNOF_MCONTEXTX64) __mcontextx64 /*[NAME(mcontextx64)][PREFIX(mc_)]*/ {
	union {
		__gregsetx64_t         gregs;      /* GLibC API compatibility... */
		__gregsetx64_t         mc_gregs;   /* General purpose register array. */
#ifdef __USE_KOS_KERNEL
		struct ucpustate64     mc_context; /* The user-space CPU context */
#endif /* __USE_KOS_KERNEL */
	};
	union {
		__fpregsetx64_t        fpregs;     /* GLibC API compatibility... */
#ifdef __USE_KOS_KERNEL
		struct fpustate64      mc_fpu;     /* FPU Context. */
#endif /* __USE_KOS_KERNEL */
	};
	__ULONG64_TYPE__           mc_flags;   /* Set of `__MCONTEXT_F*' */
	union {
		__ULONG64_TYPE__       cr2;        /* GLibC API compatibility... */
		__ULONG64_TYPE__       mc_cr2;     /* The fault address of SIGSEGV. */
	};
};

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("cr2")
#pragma pop_macro("fpregs")
#pragma pop_macro("gregs")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#endif /* __CC__ */

__DECL_END
#endif /* __KOS__ */

#endif /* !_I386_KOS_BITS_OS_KOS_MCONTEXT64_H */
