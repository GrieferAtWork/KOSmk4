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
#ifndef _I386_KOS_KOS_KERNEL_MCONTEXT32_H
#define _I386_KOS_KOS_KERNEL_MCONTEXT32_H 1

#include <__stdinc.h>
#include <hybrid/host.h>
#include <bits/types.h>
#include <features.h>

#ifdef __USE_KOS_KERNEL
#include <kos/kernel/cpu-state32.h>
#include <kos/kernel/fpu-state32.h>
#endif /* __USE_KOS_KERNEL */


#ifndef __x86_64__

#define __MCONTEXT_FLAG_NORMAL   __MCONTEXT32_FLAG_NORMAL
#define __MCONTEXT_FLAG_HAVECR2  __MCONTEXT32_FLAG_HAVECR2
#define __MCONTEXT_FLAG_HAVESFPU __MCONTEXT32_FLAG_HAVESFPU
#define __MCONTEXT_FLAG_HAVEXFPU __MCONTEXT32_FLAG_HAVEXFPU
#define __MCONTEXT_REGNO_EDI     __MCONTEXT32_REGNO_EDI
#define __MCONTEXT_REGNO_ESI     __MCONTEXT32_REGNO_ESI
#define __MCONTEXT_REGNO_EBP     __MCONTEXT32_REGNO_EBP
#define __MCONTEXT_REGNO_ESP     __MCONTEXT32_REGNO_ESP
#define __MCONTEXT_REGNO_EBX     __MCONTEXT32_REGNO_EBX
#define __MCONTEXT_REGNO_EDX     __MCONTEXT32_REGNO_EDX
#define __MCONTEXT_REGNO_ECX     __MCONTEXT32_REGNO_ECX
#define __MCONTEXT_REGNO_EAX     __MCONTEXT32_REGNO_EAX
#define __MCONTEXT_REGNO_GS      __MCONTEXT32_REGNO_GS
#define __MCONTEXT_REGNO_FS      __MCONTEXT32_REGNO_FS
#define __MCONTEXT_REGNO_ES      __MCONTEXT32_REGNO_ES
#define __MCONTEXT_REGNO_DS      __MCONTEXT32_REGNO_DS
#define __MCONTEXT_REGNO_CS      __MCONTEXT32_REGNO_CS
#define __MCONTEXT_REGNO_SS      __MCONTEXT32_REGNO_SS
#define __MCONTEXT_REGNO_EFL     __MCONTEXT32_REGNO_EFL
#define __MCONTEXT_REGNO_EIP     __MCONTEXT32_REGNO_EIP
#define __MCONTEXT_NGREG         __MCONTEXT32_NGREG
#define NGREG                    __MCONTEXT_NGREG

#ifdef __USE_KOS_KERNEL
#define MCONTEXT_FLAG_NORMAL   __MCONTEXT_FLAG_NORMAL
#define MCONTEXT_FLAG_HAVECR2  __MCONTEXT_FLAG_HAVECR2
#define MCONTEXT_FLAG_HAVESFPU __MCONTEXT_FLAG_HAVESFPU
#define MCONTEXT_FLAG_HAVEXFPU __MCONTEXT_FLAG_HAVEXFPU
#endif /* __USE_KOS_KERNEL */

#ifdef __USE_GNU
/* Number of each register is the `gregset_t' array. */
#define REG_GS     __MCONTEXT_REGNO_GS
#define REG_FS     __MCONTEXT_REGNO_FS
#define REG_ES     __MCONTEXT_REGNO_ES
#define REG_DS     __MCONTEXT_REGNO_DS
#define REG_EDI    __MCONTEXT_REGNO_EDI
#define REG_ESI    __MCONTEXT_REGNO_ESI
#define REG_EBP    __MCONTEXT_REGNO_EBP
#define REG_ESP    __MCONTEXT_REGNO_ESP
#define REG_EBX    __MCONTEXT_REGNO_EBX
#define REG_EDX    __MCONTEXT_REGNO_EDX
#define REG_ECX    __MCONTEXT_REGNO_ECX
#define REG_EAX    __MCONTEXT_REGNO_EAX
#define REG_EIP    __MCONTEXT_REGNO_EIP
#define REG_CS     __MCONTEXT_REGNO_CS
#define REG_EFL    __MCONTEXT_REGNO_EFL
#define REG_UESP   __MCONTEXT_REGNO_ESP
#define REG_SS     __MCONTEXT_REGNO_SS
#endif /* __USE_GNU */

#define __OFFSET_MCONTEXT_CPU   __OFFSET_MCONTEXT32_CPU
#define __OFFSET_MCONTEXT_FPU   __OFFSET_MCONTEXT32_FPU
#define __OFFSET_MCONTEXT_FLAGS __OFFSET_MCONTEXT32_FLAGS
#define __OFFSET_MCONTEXT_CR2   __OFFSET_MCONTEXT32_CR2
#define __SIZEOF_MCONTEXT       __SIZEOF_MCONTEXT32
#define __ALIGNOF_MCONTEXT      __ALIGNOF_MCONTEXT32

#define gregset32_t  gregset_t
#define fpregset32_t fpregset_t
#define mcontext32   mcontext
#define mcontext32_t mcontext_t
#endif /* !__x86_64__ */

__DECL_BEGIN

#define __MCONTEXT32_FLAG_NORMAL    0x0000 /* Normal context flags. */
#define __MCONTEXT32_FLAG_HAVECR2   0x0001 /* The `mc_cr2' field contains a valid value. */
#define __MCONTEXT32_FLAG_HAVESFPU  0x1000 /* The `mc_fpu' structure contains valid data and must be restored.
                                            * When not set: The FPU hasn't been initialized yet, and a context
                                            *               load will leave the FPU unmodified if it hasn't been
                                            *               initialized, or will default-initialize it if it
                                            *               had been initialized in the mean time. */
#define __MCONTEXT32_FLAG_HAVEXFPU  0x2000 /* The `mc_fpu' structure uses the `f_xsave' variant (otherwise, the `f_ssave' variant is used) */


#define __MCONTEXT32_REGNO_EDI    0  /* [P] Destination pointer */
#define __MCONTEXT32_REGNO_ESI    1  /* [P] Source pointer */
#define __MCONTEXT32_REGNO_EBP    2  /* [P] Frame base pointer */
#define __MCONTEXT32_REGNO_ESP    3  /* [P] Stack pointer */
#define __MCONTEXT32_REGNO_EBX    4  /* [P] Base register */
#define __MCONTEXT32_REGNO_EDX    5  /* [C] Data register */
#define __MCONTEXT32_REGNO_ECX    6  /* [C] Count register */
#define __MCONTEXT32_REGNO_EAX    7  /* [C] Accumulator register */
#define __MCONTEXT32_REGNO_GS     8  /* G segment register (Usually `SEGMENT_USER_GSBASE_RPL') */
#define __MCONTEXT32_REGNO_FS     9  /* F segment register (Usually `SEGMENT_USER_FSBASE_RPL' / `SEGMENT_KERNEL_FSBASE') */
#define __MCONTEXT32_REGNO_ES     10 /* E (source) segment register (Usually `SEGMENT_USER_DATA_RPL') */
#define __MCONTEXT32_REGNO_DS     11 /* D (destination) segment register (Usually `SEGMENT_USER_DATA_RPL') */
#define __MCONTEXT32_REGNO_CS     12 /* Code segment (Ring #3, usually `SEGMENT_USER_CODE_RPL') */
#define __MCONTEXT32_REGNO_SS     13 /* Stack segment (Ring #3, usually `SEGMENT_USER_DATA_RPL') */
#define __MCONTEXT32_REGNO_EFL    14 /* Flags register */
#define __MCONTEXT32_REGNO_EIP    15 /* Instruction pointer */
#define __MCONTEXT32_NGREG        16 /* Number of general registers. */


#define __OFFSET_MCONTEXT32_CPU   0   /* [FIELD(gregs, mc_gregs, mc_context)] */
#define __OFFSET_MCONTEXT32_FPU   64  /* [FIELD(fpregs, mc_fpu)] */
#define __OFFSET_MCONTEXT32_FLAGS 576 /* [FIELD(mc_flags)] */
#define __OFFSET_MCONTEXT32_CR2   580 /* [FIELD(cr2, mc_cr2)] */
#define __SIZEOF_MCONTEXT32       592
#define __ALIGNOF_MCONTEXT32      16

#ifdef __CC__
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("gregs")
#pragma push_macro("fpregs")
#pragma push_macro("cr2")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef gregs
#undef fpregs
#undef cr2

typedef __uint32_t gregset32_t[__MCONTEXT32_NGREG];
typedef __ATTR_ALIGNED(__ALIGNOF_MCONTEXT32) __byte_t fpregset32_t[512];

/* Machine context. */
typedef struct __ATTR_ALIGNED(__ALIGNOF_MCONTEXT32) mcontext32 {
	union {
		gregset32_t            gregs;      /* GLibC API compatibility... */
		gregset32_t            mc_gregs;   /* General purpose register array. */
#ifdef __USE_KOS_KERNEL
		struct ucpustate32     mc_context; /* The user-space CPU context */
#endif /* __USE_KOS_KERNEL */
	};
	union {
		fpregset32_t           fpregs;     /* GLibC API compatibility... */
#ifdef __USE_KOS_KERNEL
		struct fpustate32      mc_fpu;     /* FPU Context. */
#endif /* __USE_KOS_KERNEL */
	};
	__ULONG32_TYPE__           mc_flags;   /* Set of `__MCONTEXT_F*' */
	union {
		__ULONG32_TYPE__       cr2;        /* GLibC API compatibility... */
		__ULONG32_TYPE__       mc_cr2;     /* The fault address of SIGSEGV. */
	};
	__ULONG32_TYPE__           mc_pad[2];  /* Padding... */
} mcontext32_t;

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("cr2")
#pragma pop_macro("fpregs")
#pragma pop_macro("gregs")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#endif /* __CC__ */

__DECL_END

#endif /* !_I386_KOS_KOS_KERNEL_MCONTEXT32_H */
