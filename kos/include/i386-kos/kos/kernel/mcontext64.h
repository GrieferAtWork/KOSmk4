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
#ifndef _I386_KOS_KOS_KERNEL_MCONTEXT64_H
#define _I386_KOS_KOS_KERNEL_MCONTEXT64_H 1

#include <__stdinc.h>
#include <hybrid/host.h>
#include <bits/types.h>
#include <features.h>

#ifdef __USE_KOS_KERNEL
#include <kos/kernel/cpu-state64.h>
#include <kos/kernel/fpu-state64.h>
#endif /* __USE_KOS_KERNEL */


#ifdef __x86_64__
#define __MCONTEXT_FLAG_NORMAL   __MCONTEXT64_FLAG_NORMAL
#define __MCONTEXT_FLAG_HAVECR2  __MCONTEXT64_FLAG_HAVECR2
#define __MCONTEXT_FLAG_HAVESFPU __MCONTEXT64_FLAG_HAVESFPU
#define __MCONTEXT_FLAG_HAVEXFPU __MCONTEXT64_FLAG_HAVEXFPU
#define __MCONTEXT_REGNO_GSBASE  __MCONTEXT64_REGNO_GSBASE
#define __MCONTEXT_REGNO_FSBASE  __MCONTEXT64_REGNO_FSBASE
#define __MCONTEXT_REGNO_R15     __MCONTEXT64_REGNO_R15
#define __MCONTEXT_REGNO_R14     __MCONTEXT64_REGNO_R14
#define __MCONTEXT_REGNO_R13     __MCONTEXT64_REGNO_R13
#define __MCONTEXT_REGNO_R12     __MCONTEXT64_REGNO_R12
#define __MCONTEXT_REGNO_R11     __MCONTEXT64_REGNO_R11
#define __MCONTEXT_REGNO_R10     __MCONTEXT64_REGNO_R10
#define __MCONTEXT_REGNO_R9      __MCONTEXT64_REGNO_R9
#define __MCONTEXT_REGNO_R8      __MCONTEXT64_REGNO_R8
#define __MCONTEXT_REGNO_RDI     __MCONTEXT64_REGNO_RDI
#define __MCONTEXT_REGNO_RSI     __MCONTEXT64_REGNO_RSI
#define __MCONTEXT_REGNO_RBP     __MCONTEXT64_REGNO_RBP
#define __MCONTEXT_REGNO_RSP     __MCONTEXT64_REGNO_RSP
#define __MCONTEXT_REGNO_RBX     __MCONTEXT64_REGNO_RBX
#define __MCONTEXT_REGNO_RDX     __MCONTEXT64_REGNO_RDX
#define __MCONTEXT_REGNO_RCX     __MCONTEXT64_REGNO_RCX
#define __MCONTEXT_REGNO_RAX     __MCONTEXT64_REGNO_RAX
#define __MCONTEXT_REGNO_GS      __MCONTEXT64_REGNO_GS
#define __MCONTEXT_REGNO_FS      __MCONTEXT64_REGNO_FS
#define __MCONTEXT_REGNO_ES      __MCONTEXT64_REGNO_ES
#define __MCONTEXT_REGNO_DS      __MCONTEXT64_REGNO_DS
#define __MCONTEXT_REGNO_CS      __MCONTEXT64_REGNO_CS
#define __MCONTEXT_REGNO_SS      __MCONTEXT64_REGNO_SS
#define __MCONTEXT_REGNO_RFLAGS  __MCONTEXT64_REGNO_RFLAGS
#define __MCONTEXT_REGNO_RIP     __MCONTEXT64_REGNO_RIP
#define __MCONTEXT_NGREG         __MCONTEXT64_NGREG
#define NGREG                    __MCONTEXT_NGREG

#ifdef __USE_KOS_KERNEL
#define MCONTEXT_FLAG_NORMAL   __MCONTEXT_FLAG_NORMAL
#define MCONTEXT_FLAG_HAVECR2  __MCONTEXT_FLAG_HAVECR2
#define MCONTEXT_FLAG_HAVESFPU __MCONTEXT_FLAG_HAVESFPU
#define MCONTEXT_FLAG_HAVEXFPU __MCONTEXT_FLAG_HAVEXFPU
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
#define REG_CR2  (__OFFSET_MCONTEXT64_CR2/8)
#endif /* __USE_GNU */

#define __OFFSET_MCONTEXT_CPU   __OFFSET_MCONTEXT64_CPU
#define __OFFSET_MCONTEXT_FPU   __OFFSET_MCONTEXT64_FPU
#define __OFFSET_MCONTEXT_FLAGS __OFFSET_MCONTEXT64_FLAGS
#define __OFFSET_MCONTEXT_CR2   __OFFSET_MCONTEXT64_CR2
#define __SIZEOF_MCONTEXT       __SIZEOF_MCONTEXT64
#define __ALIGNOF_MCONTEXT      __ALIGNOF_MCONTEXT64

#define gregset64_t  gregset_t
#define fpregset64_t fpregset_t
#define mcontext64   mcontext
#define mcontext64_t mcontext_t
#endif /* __x86_64__ */

__DECL_BEGIN

#define __MCONTEXT64_FLAG_NORMAL    0x0000 /* Normal context flags. */
#define __MCONTEXT64_FLAG_HAVECR2   0x0001 /* The `mc_cr2' field contains a valid value. */
#define __MCONTEXT64_FLAG_HAVESFPU  0x1000 /* The `mc_fpu' structure contains valid data and must be restored.
                                            * When not set: The FPU hasn't been initialized yet, and a context
                                            *               load will leave the FPU unmodified if it hasn't been
                                            *               initialized, or will default-initialize it if it
                                            *               had been initialized in the mean time. */
#define __MCONTEXT64_FLAG_HAVEXFPU  0x2000 /* The `mc_fpu' structure uses the `f_xsave' variant (otherwise, the `f_ssave' variant is used) */


#define __MCONTEXT64_REGNO_GSBASE  0
#define __MCONTEXT64_REGNO_FSBASE  1
#define __MCONTEXT64_REGNO_R15     2
#define __MCONTEXT64_REGNO_R14     3
#define __MCONTEXT64_REGNO_R13     4
#define __MCONTEXT64_REGNO_R12     5
#define __MCONTEXT64_REGNO_R11     6
#define __MCONTEXT64_REGNO_R10     7
#define __MCONTEXT64_REGNO_R9      8
#define __MCONTEXT64_REGNO_R8      9
#define __MCONTEXT64_REGNO_RDI     10
#define __MCONTEXT64_REGNO_RSI     11
#define __MCONTEXT64_REGNO_RBP     12
#define __MCONTEXT64_REGNO_RSP     13
#define __MCONTEXT64_REGNO_RBX     14
#define __MCONTEXT64_REGNO_RDX     15
#define __MCONTEXT64_REGNO_RCX     16
#define __MCONTEXT64_REGNO_RAX     17
#define __MCONTEXT64_REGNO_GS      18
#define __MCONTEXT64_REGNO_FS      19
#define __MCONTEXT64_REGNO_ES      20
#define __MCONTEXT64_REGNO_DS      21
#define __MCONTEXT64_REGNO_CS      22
#define __MCONTEXT64_REGNO_SS      23
#define __MCONTEXT64_REGNO_RFLAGS  24
#define __MCONTEXT64_REGNO_RIP     25
#define __MCONTEXT64_NGREG         26

#define __OFFSET_MCONTEXT64_CPU   0   /* [FIELD(gregs, mc_gregs, mc_context)] */
#define __OFFSET_MCONTEXT64_FPU   208 /* [FIELD(fpregs, mc_fpu)] */
#define __OFFSET_MCONTEXT64_FLAGS 720 /* [FIELD(mc_flags)] */
#define __OFFSET_MCONTEXT64_CR2   728 /* [FIELD(cr2, mc_cr2)] */
#define __SIZEOF_MCONTEXT64       736
#define __ALIGNOF_MCONTEXT64      16

#ifdef __CC__
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("gregs")
#pragma push_macro("fpregs")
#pragma push_macro("cr2")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef gregs
#undef fpregs
#undef cr2

typedef __uint64_t gregset64_t[__MCONTEXT64_NGREG];
typedef __ATTR_ALIGNED(__ALIGNOF_MCONTEXT64) __byte_t fpregset64_t[512];

/* Machine context. */
typedef struct __ATTR_ALIGNED(__ALIGNOF_MCONTEXT64) mcontext64 {
	union {
		gregset64_t            gregs;      /* GLibC API compatibility... */
		gregset64_t            mc_gregs;   /* General purpose register array. */
#ifdef __USE_KOS_KERNEL
		struct ucpustate64     mc_context; /* The user-space CPU context */
#endif /* __USE_KOS_KERNEL */
	};
	union {
		fpregset64_t           fpregs;     /* GLibC API compatibility... */
#ifdef __USE_KOS_KERNEL
		struct fpustate64      mc_fpu;     /* FPU Context. */
#endif /* __USE_KOS_KERNEL */
	};
	__ULONG64_TYPE__           mc_flags;   /* Set of `__MCONTEXT_F*' */
	union {
		__ULONG64_TYPE__       cr2;        /* GLibC API compatibility... */
		__ULONG64_TYPE__       mc_cr2;     /* The fault address of SIGSEGV. */
	};
} mcontext64_t;

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("cr2")
#pragma pop_macro("fpregs")
#pragma pop_macro("gregs")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#endif /* __CC__ */

__DECL_END

#endif /* !_I386_KOS_KOS_KERNEL_MCONTEXT64_H */
