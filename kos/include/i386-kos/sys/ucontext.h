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
#ifndef _I386_KOS_SYS_UCONTEXT_H
#define _I386_KOS_SYS_UCONTEXT_H 1
#define _SYS_UCONTEXT_H 1

#include <__stdinc.h>
#include <features.h>
#include <hybrid/typecore.h>
#include <hybrid/host.h>
#include <bits/types.h>
#include <bits/sigset.h>
#include <bits/sigcontext.h>
#include <bits/sigstack.h>


#if defined(__CRT_KOS_PRIMARY) && __KOS_VERSION__ >= 400
#include <kos/kernel/ucontext.h>
#endif /* __CRT_KOS_PRIMARY && __KOS_VERSION__ >= 400 */


__SYSDECL_BEGIN

#define __SIZEOF_GREG_T__  __SIZEOF_REGISTER__
#ifdef __CC__
#ifndef __greg_t_defined
#define __greg_t_defined 1
typedef __REGISTER_TYPE__ greg_t;
#endif /* !__greg_t_defined */
#endif

#if defined(__CRT_KOS_PRIMARY) && __KOS_VERSION__ >= 400

/* Everything is defined in `<kos/kernel/ucontext.h>' */

#elif defined(__CRT_KOS_PRIMARY) && __KOS_VERSION__ >= 300
/* KOS */

#define __UCONTEXT_REGNO_EDI    0  /* [P] Destination pointer */
#define __UCONTEXT_REGNO_ESI    1  /* [P] Source pointer */
#define __UCONTEXT_REGNO_EBP    2  /* [P] Frame base pointer */
#define __UCONTEXT_REGNO_ESP    3  /* [P] Stack pointer */
#define __UCONTEXT_REGNO_EBX    4  /* [P] Base register */
#define __UCONTEXT_REGNO_EDX    5  /* [C] Data register */
#define __UCONTEXT_REGNO_ECX    6  /* [C] Count register */
#define __UCONTEXT_REGNO_EAX    7  /* [C] Accumulator register */
#define __UCONTEXT_REGNO_GS     8  /* G segment register (Usually `SEGMENT_USER_GSBASE_RPL') */
#define __UCONTEXT_REGNO_FS     9  /* F segment register (Usually `SEGMENT_USER_FSBASE_RPL' / `SEGMENT_KERNEL_FSBASE') */
#define __UCONTEXT_REGNO_ES     10 /* E (source) segment register (Usually `SEGMENT_USER_DATA_RPL') */
#define __UCONTEXT_REGNO_DS     11 /* D (destination) segment register (Usually `SEGMENT_USER_DATA_RPL') */
#define __UCONTEXT_REGNO_EIP    12 /* Instruction pointer */
#define __UCONTEXT_REGNO_EFL    13 /* Flags register */
#define __UCONTEXT_REGNO_CS     14 /* Code segment (Ring #3, usually `SEGMENT_USER_CODE_RPL') */
#define __UCONTEXT_REGNO_SS     15 /* Stack segment (Ring #3, usually `SEGMENT_USER_DATA_RPL') */
#define NGREG                   16 /* Number of general registers. */

#ifdef __CC__
typedef greg_t gregset_t[NGREG]; /* Container for all general registers. */
#endif

#ifdef __USE_GNU
/* Number of each register is the `gregset_t' array. */
#define REG_GS     __UCONTEXT_REGNO_GS
#define REG_FS     __UCONTEXT_REGNO_FS
#define REG_ES     __UCONTEXT_REGNO_ES
#define REG_DS     __UCONTEXT_REGNO_DS
#define REG_EDI    __UCONTEXT_REGNO_EDI
#define REG_ESI    __UCONTEXT_REGNO_ESI
#define REG_EBP    __UCONTEXT_REGNO_EBP
#define REG_ESP    __UCONTEXT_REGNO_ESP
#define REG_EBX    __UCONTEXT_REGNO_EBX
#define REG_EDX    __UCONTEXT_REGNO_EDX
#define REG_ECX    __UCONTEXT_REGNO_ECX
#define REG_EAX    __UCONTEXT_REGNO_EAX
#define REG_EIP    __UCONTEXT_REGNO_EIP
#define REG_CS     __UCONTEXT_REGNO_CS
#define REG_EFL    __UCONTEXT_REGNO_EFL
#define REG_UESP   __UCONTEXT_REGNO_ESP
#define REG_SS     __UCONTEXT_REGNO_SS
#endif

#define __MCONTEXT_FNORMAL    0x0000 /* Normal context flags. */
#define __MCONTEXT_FHAVECR2   0x0001 /* The `m_cr2' field contains a valid value. */
#define __MCONTEXT_FHAVEFPU   0x1000 /* The `m_fpu' structure contains valid data and must be restored.
                                      * When not set: The FPU hasn't been initialized yet, and a context
                                      *               load will leave the FPU unmodified if it hasn't been
                                      *               initialized, or will default-initialize it if it
                                      *               had been initialized in the mean time. */


#ifdef __CC__
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("gregs")
#pragma push_macro("cr2")
#pragma push_macro("fpregs")
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
#undef gregs
#undef cr2
#undef fpregs
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
typedef struct _libc_fpstate fpregset_t[1];

#ifdef __USE_KOS_KERNEL
__SYSDECL_END
#include <kos/kernel/cpu-state.h>
#include <kos/kernel/fpu-state.h>
__SYSDECL_BEGIN
#endif /* __USE_KOS_KERNEL */

typedef struct __ATTR_PACKED mcontext {
	union __ATTR_PACKED {
		gregset_t              gregs;     /* GLibC API compatibility... */
		gregset_t              m_gregs;   /* General purpose register array. */
#ifdef __USE_KOS_KERNEL
		struct ucpustate       m_context; /* The user-space CPU context */
#endif /* __USE_KOS_KERNEL */
	};
	union __ATTR_PACKED {
		fpregset_t             fpregs;    /* GLibC API compatibility... */
#ifdef __USE_KOS_KERNEL
		struct fpustate        m_fpu;     /* FPU Context. */
#endif /* __USE_KOS_KERNEL */
	};
	__UINTPTR_TYPE__           m_flags;   /* Set of `__MCONTEXT_F*' */
	union __ATTR_PACKED {
		__ULONGPTR_TYPE__      cr2;       /* GLibC API compatibility... */
		__ULONGPTR_TYPE__      m_cr2;     /* The fault address of SIGSEGV. */
	};
} mcontext_t;

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
#pragma pop_macro("fpregs")
#pragma pop_macro("cr2")
#pragma pop_macro("gregs")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

/* Userlevel context. */
typedef struct __ATTR_PACKED ucontext {
	mcontext_t       uc_mcontext;
	__sigset_t       uc_sigmask;
	stack_t          uc_stack;
	struct ucontext *uc_link;
} ucontext_t;
#endif /* __CC__ */

#elif defined(__CRT_GLC_PRIMARY) || \
     (defined(__CRT_KOS_PRIMARY) && __KOS_VERSION__ < 300)
/* GLIBC */


/* Copyright (C) 2001-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#ifdef __CC__
#ifndef __greg_t_defined
#define __greg_t_defined 1
typedef __SREGISTER_TYPE__ greg_t;
#endif /* !__greg_t_defined */
#endif /* __CC__ */
#define __SIZEOF_GREG_T__  __SIZEOF_REGISTER__


#ifdef __x86_64__
#define NGREG  23 /* Number of general registers. */

#ifdef __CC__
typedef greg_t gregset_t[NGREG]; /* Container for all general registers. */
#endif /* __CC__ */

#ifdef __USE_GNU
/* Number of each register in the `gregset_t' array. */
#ifdef __CC__
enum {
	REG_R8 = 0,
	REG_R9,
	REG_R10,
	REG_R11,
	REG_R12,
	REG_R13,
	REG_R14,
	REG_R15,
	REG_RDI,
	REG_RSI,
	REG_RBP,
	REG_RBX,
	REG_RDX,
	REG_RAX,
	REG_RCX,
	REG_RSP,
	REG_RIP,
	REG_EFL,
	REG_CSGSFS, /* Actually short cs, gs, fs, __pad0. */
	REG_ERR,
	REG_TRAPNO,
	REG_OLDMASK,
	REG_CR2
};
#endif /* __CC__ */
#define REG_R8      0
#define REG_R9      1
#define REG_R10     2
#define REG_R11     3
#define REG_R12     4
#define REG_R13     5
#define REG_R14     6
#define REG_R15     7
#define REG_RDI     8
#define REG_RSI     9
#define REG_RBP     10
#define REG_RBX     11
#define REG_RDX     12
#define REG_RAX     13
#define REG_RCX     14
#define REG_RSP     15
#define REG_RIP     16
#define REG_EFL     17
#define REG_CSGSFS  18
#define REG_ERR     19
#define REG_TRAPNO  20
#define REG_OLDMASK 21
#define REG_CR2     22
#endif /* __USE_GNU */

#define __LIBC_FPXREG_OFFSETOF_SIGNIFICAND 0
#define __LIBC_FPXREG_OFFSETOF_EXPONENT    8
#define __LIBC_FPXREG_OFFSETOF_PADDING     10
#define __LIBC_FPXREG_SIZE                 16


#ifdef __CC__
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("significand")
#pragma push_macro("exponent")
#pragma push_macro("padding")
#endif
#undef significand
#undef exponent
#undef padding
struct _libc_fpxreg {
	__UINT16_TYPE__ significand[4];
	__UINT16_TYPE__ exponent;
	__UINT16_TYPE__ padding[3];
};
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("padding")
#pragma pop_macro("exponent")
#pragma pop_macro("significand")
#endif
#endif /* __CC__ */

#define __LIBC_XMMREG_OFFSETOF_ELEMENT     0
#define __LIBC_XMMREG_SIZE                 16
#ifdef __CC__
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("element")
#endif
#undef element
struct _libc_xmmreg {
	__uint32_t element[4];
};
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("element")
#endif
#endif /* __CC__ */

#define __LIBC_FPSTATE_OFFSETOF_CWD        0
#define __LIBC_FPSTATE_OFFSETOF_SWD        2
#define __LIBC_FPSTATE_OFFSETOF_FTW        4
#define __LIBC_FPSTATE_OFFSETOF_FOP        6
#define __LIBC_FPSTATE_OFFSETOF_RIP        8
#define __LIBC_FPSTATE_OFFSETOF_RDP        16
#define __LIBC_FPSTATE_OFFSETOF_MXCSR      24
#define __LIBC_FPSTATE_OFFSETOF_MXCR_MASK  28
#define __LIBC_FPSTATE_OFFSETOF_ST         32
#define __LIBC_FPSTATE_OFFSETOF_XMM        160
#define __LIBC_FPSTATE_OFFSETOF_PADDING    416
#define __LIBC_FPSTATE_SIZE                512

#ifdef __CC__
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("cwd")
#pragma push_macro("swd")
#pragma push_macro("ftw")
#pragma push_macro("fop")
#pragma push_macro("rip")
#pragma push_macro("rdp")
#pragma push_macro("mxcsr")
#pragma push_macro("mxcr_mask")
#pragma push_macro("_st")
#pragma push_macro("_xmm")
#pragma push_macro("padding")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef cwd
#undef swd
#undef ftw
#undef fop
#undef rip
#undef rdp
#undef mxcsr
#undef mxcr_mask
#undef _st
#undef _xmm
#undef padding
struct _libc_fpstate {
	/* 64-bit FXSAVE format. */
	__uint16_t          cwd;
	__uint16_t          swd;
	__uint16_t          ftw;
	__uint16_t          fop;
	__uint64_t          rip;
	__uint64_t          rdp;
	__uint32_t          mxcsr;
	__uint32_t          mxcr_mask;
	struct _libc_fpxreg _st[8];
	struct _libc_xmmreg _xmm[16];
	__uint32_t          padding[24];
};
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("padding")
#pragma pop_macro("_xmm")
#pragma pop_macro("_st")
#pragma pop_macro("mxcr_mask")
#pragma pop_macro("mxcsr")
#pragma pop_macro("rdp")
#pragma pop_macro("rip")
#pragma pop_macro("fop")
#pragma pop_macro("ftw")
#pragma pop_macro("swd")
#pragma pop_macro("cwd")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

/* Structure to describe FPU registers. */
typedef struct _libc_fpstate *fpregset_t;
#endif


#define __MCONTEXT_OFFSETOF_GREGS      0
#define __MCONTEXT_OFFSETOF_FPREGS    (__SIZEOF_GREG_T__*NGREG)
#if defined(__USE_KOS) || defined(__KERNEL__)
#define __MCONTEXT_OFFSETOF_FS_BASE   (__SIZEOF_GREG_T__*NGREG+__SIZEOF_POINTER__)
#define __MCONTEXT_OFFSETOF_GS_BASE   (__SIZEOF_GREG_T__*NGREG+2*__SIZEOF_POINTER__)
#endif
#define __MCONTEXT_SIZE               (__SIZEOF_GREG_T__*NGREG+9*__SIZEOF_POINTER__)
#ifdef __CC__
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("gregs")
#pragma push_macro("fpregs")
#if defined(__USE_KOS) || defined(__KERNEL__)
#pragma push_macro("fs_base")
#pragma push_macro("gs_base")
#endif
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef gregs
#undef fpregs
#if defined(__USE_KOS) || defined(__KERNEL__)
#undef fs_base
#undef gs_base
#endif
/* Context to describe whole processor state. */
typedef struct mcontext {
	gregset_t        gregs;
	fpregset_t       fpregs;  /* Note that fpregs is a pointer. */
#if defined(__USE_KOS) || defined(__KERNEL__)
	__UINTPTR_TYPE__ fs_base; /* User-space `fs_base' address. */
	__UINTPTR_TYPE__ gs_base; /* User-space `gs_base' address. */
	__UINTPTR_TYPE__ __reserved1[6];
#else
	__UINTPTR_TYPE__ __reserved1[8];
#endif
} mcontext_t;
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#if defined(__USE_KOS) || defined(__KERNEL__)
#pragma pop_macro("gs_base")
#pragma pop_macro("fs_base")
#endif
#pragma pop_macro("fpregs")
#pragma pop_macro("gregs")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#endif


#define __UCONTEXT_OFFSETOF_FLAGS        0
#define __UCONTEXT_OFFSETOF_LINK         __SIZEOF_POINTER__
#define __UCONTEXT_OFFSETOF_STACK     (2*__SIZEOF_POINTER__)
#define __UCONTEXT_OFFSETOF_MCONTEXT  (2*__SIZEOF_POINTER__+__STACK_SIZE)
#define __UCONTEXT_OFFSETOF_SIGMASK   (2*__SIZEOF_POINTER__+__STACK_SIZE+__MCONTEXT_SIZE)
#define __UCONTEXT_OFFSETOF_FPREGS    (2*__SIZEOF_POINTER__+__STACK_SIZE+__MCONTEXT_SIZE+__SIZEOF_SIGSET_T__)
#define __UCONTEXT_SIZE               (2*__SIZEOF_POINTER__+__STACK_SIZE+__MCONTEXT_SIZE+__SIZEOF_SIGSET_T__+__LIBC_FPSTATE_SIZE)

#ifdef __CC__
/* Userlevel context. */
typedef struct ucontext {
	__ULONGPTR_TYPE__    uc_flags;
	struct ucontext     *uc_link;
	stack_t              uc_stack;
	mcontext_t           uc_mcontext;
	__sigset_t           uc_sigmask;
	struct _libc_fpstate __fpregs_mem;
} ucontext_t;
#endif /* __CC__ */

#else /* __x86_64__ */

#define NGREG    19 /* Number of general registers. */
#ifdef __CC__
typedef greg_t gregset_t[NGREG]; /* Container for all general registers. */
#endif

#ifdef __USE_GNU
/* Number of each register is the `gregset_t' array. */
/*[[[enum]]]*/
#ifdef __CC__
enum {
	REG_GS     = 0,
	REG_FS     = 1,
	REG_ES     = 2,
	REG_DS     = 3,
	REG_EDI    = 4,
	REG_ESI    = 5,
	REG_EBP    = 6,
	REG_ESP    = 7,
	REG_EBX    = 8,
	REG_EDX    = 9,
	REG_ECX    = 10,
	REG_EAX    = 11,
	REG_TRAPNO = 12,
	REG_ERR    = 13,
	REG_EIP    = 14,
	REG_CS     = 15,
	REG_EFL    = 16,
	REG_UESP   = 17,
	REG_SS     = 18
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#define REG_GS     REG_GS
#define REG_FS     REG_FS
#define REG_ES     REG_ES
#define REG_DS     REG_DS
#define REG_EDI    REG_EDI
#define REG_ESI    REG_ESI
#define REG_EBP    REG_EBP
#define REG_ESP    REG_ESP
#define REG_EBX    REG_EBX
#define REG_EDX    REG_EDX
#define REG_ECX    REG_ECX
#define REG_EAX    REG_EAX
#define REG_TRAPNO REG_TRAPNO
#define REG_ERR    REG_ERR
#define REG_EIP    REG_EIP
#define REG_CS     REG_CS
#define REG_EFL    REG_EFL
#define REG_UESP   REG_UESP
#define REG_SS     REG_SS
#else /* __COMPILER_PREFERR_ENUMS */
#define REG_GS     0
#define REG_FS     1
#define REG_ES     2
#define REG_DS     3
#define REG_EDI    4
#define REG_ESI    5
#define REG_EBP    6
#define REG_ESP    7
#define REG_EBX    8
#define REG_EDX    9
#define REG_ECX    10
#define REG_EAX    11
#define REG_TRAPNO 12
#define REG_ERR    13
#define REG_EIP    14
#define REG_CS     15
#define REG_EFL    16
#define REG_UESP   17
#define REG_SS     18
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* __USE_GNU */

#define __LIBC_FPREG_OFFSETOF_SIGNIFICAND 0
#define __LIBC_FPREG_OFFSETOF_EXPONENT    8
#define __LIBC_FPREG_SIZE                 10

#ifdef __CC__
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("significand")
#pragma push_macro("exponent")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef significand
#undef exponent
struct _libc_fpreg {
	/* Definitions taken from the kernel headers. */
	unsigned short int significand[4];
	unsigned short int exponent;
};
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("exponent")
#pragma pop_macro("significand")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#endif /* __CC__ */

#define __LIBC_FPSTATE_OFFSETOF_CW       0
#define __LIBC_FPSTATE_OFFSETOF_SW       4
#define __LIBC_FPSTATE_OFFSETOF_TAG      8
#define __LIBC_FPSTATE_OFFSETOF_IPOFF    12
#define __LIBC_FPSTATE_OFFSETOF_CSSEL    16
#define __LIBC_FPSTATE_OFFSETOF_DATAOFF  20
#define __LIBC_FPSTATE_OFFSETOF_DATASEL  24
#define __LIBC_FPSTATE_OFFSETOF_ST       28
#define __LIBC_FPSTATE_OFFSETOF_STATUS   108
#define __LIBC_FPSTATE_SIZE              112

#ifdef __CC__
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
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
#undef cw
#undef sw
#undef tag
#undef ipoff
#undef cssel
#undef dataoff
#undef datasel
#undef _st
#undef status
struct _libc_fpstate {
	__ULONGPTR_TYPE__  cw;
	__ULONGPTR_TYPE__  sw;
	__ULONGPTR_TYPE__  tag;
	__ULONGPTR_TYPE__  ipoff;
	__ULONGPTR_TYPE__  cssel;
	__ULONGPTR_TYPE__  dataoff;
	__ULONGPTR_TYPE__  datasel;
	struct _libc_fpreg _st[8];
	__ULONGPTR_TYPE__  status;
};
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
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

/* Structure to describe FPU registers. */
typedef struct _libc_fpstate *fpregset_t;
#endif /* __CC__ */


#define __MCONTEXT_OFFSETOF_GREGS      0
#define __MCONTEXT_OFFSETOF_FPREGS    (__SIZEOF_GREG_T__*NGREG)
#define __MCONTEXT_OFFSETOF_OLDMASK   (__SIZEOF_GREG_T__*NGREG+4)
#define __MCONTEXT_OFFSETOF_CR2       (__SIZEOF_GREG_T__*NGREG+8)
#define __MCONTEXT_SIZE               (__SIZEOF_GREG_T__*NGREG+12)
#ifdef __CC__
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("gregs")
#pragma push_macro("fpregs")
#pragma push_macro("oldmask")
#pragma push_macro("cr2")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef gregs
#undef fpregs
#undef oldmask
#undef cr2
typedef struct mcontext {
	/* Context to describe whole processor state. */
	gregset_t gregs;
	/* Due to Linux's history we have to use a pointer here.
	 * The SysV/i386 ABI requires a struct with the values. */
	fpregset_t fpregs;
	__ULONGPTR_TYPE__ oldmask;
	__ULONGPTR_TYPE__ cr2;
} mcontext_t;
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("cr2")
#pragma pop_macro("oldmask")
#pragma pop_macro("fpregs")
#pragma pop_macro("gregs")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#endif /* __CC__ */

#define __UCONTEXT_OFFSETOF_FLAGS        0
#define __UCONTEXT_OFFSETOF_LINK         __SIZEOF_POINTER__
#define __UCONTEXT_OFFSETOF_STACK     (2*__SIZEOF_POINTER__)
#define __UCONTEXT_OFFSETOF_MCONTEXT  (2*__SIZEOF_POINTER__+__STACK_SIZE)
#define __UCONTEXT_OFFSETOF_SIGMASK   (2*__SIZEOF_POINTER__+__STACK_SIZE+__MCONTEXT_SIZE)
#define __UCONTEXT_OFFSETOF_FPREGS    (2*__SIZEOF_POINTER__+__STACK_SIZE+__MCONTEXT_SIZE+__SIZEOF_SIGSET_T__)
#define __UCONTEXT_SIZE               (2*__SIZEOF_POINTER__+__STACK_SIZE+__MCONTEXT_SIZE+__SIZEOF_SIGSET_T__+__LIBC_FPSTATE_SIZE)

#ifdef __CC__
/* Userlevel context. */
typedef struct ucontext {
	__ULONGPTR_TYPE__    uc_flags;
	struct ucontext     *uc_link;
	stack_t              uc_stack;
	mcontext_t           uc_mcontext;
	__sigset_t           uc_sigmask;
	struct _libc_fpstate __fpregs_mem;
} ucontext_t;
#endif /* __CC__ */
#endif /* !__x86_64__ */


#elif defined(__CRT_CYG_PRIMARY)
/* CYGWIN */

#ifdef __CC__
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("significand")
#pragma push_macro("exponent")
#pragma push_macro("_fpstate")
#pragma push_macro("ctxflags")
#pragma push_macro("cs")
#pragma push_macro("ds")
#pragma push_macro("es")
#pragma push_macro("fs")
#pragma push_macro("gs")
#pragma push_macro("ss")
#pragma push_macro("eflags")
#pragma push_macro("dr0")
#pragma push_macro("dr1")
#pragma push_macro("dr2")
#pragma push_macro("dr3")
#pragma push_macro("dr6")
#pragma push_macro("dr7")
#pragma push_macro("oldmask")
#pragma push_macro("cr2")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

#undef significand
#undef exponent
#undef _fpstate
#undef ctxflags
#undef cs
#undef ds
#undef es
#undef fs
#undef gs
#undef ss
#undef eflags
#undef dr0
#undef dr1
#undef dr2
#undef dr3
#undef dr6
#undef dr7
#undef oldmask
#undef cr2

#ifdef __x86_64__
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("_uc_fpxreg")
#pragma push_macro("_uc_xmmreg")
#pragma push_macro("element")
#pragma push_macro("cwd")
#pragma push_macro("swd")
#pragma push_macro("ftw")
#pragma push_macro("fop")
#pragma push_macro("rdp")
#pragma push_macro("mxcr_mask")
#pragma push_macro("st")
#pragma push_macro("xmm")
#pragma push_macro("padding")
#pragma push_macro("p1home")
#pragma push_macro("p2home")
#pragma push_macro("p3home")
#pragma push_macro("p4home")
#pragma push_macro("p5home")
#pragma push_macro("p6home")
#pragma push_macro("mxcsr")
#pragma push_macro("rax")
#pragma push_macro("rcx")
#pragma push_macro("rdx")
#pragma push_macro("rbx")
#pragma push_macro("rsp")
#pragma push_macro("rbp")
#pragma push_macro("rsi")
#pragma push_macro("rdi")
#pragma push_macro("r8")
#pragma push_macro("r9")
#pragma push_macro("r10")
#pragma push_macro("r11")
#pragma push_macro("r12")
#pragma push_macro("r13")
#pragma push_macro("r14")
#pragma push_macro("r15")
#pragma push_macro("rip")
#pragma push_macro("fpregs")
#pragma push_macro("vregs")
#pragma push_macro("vcx")
#pragma push_macro("dbc")
#pragma push_macro("btr")
#pragma push_macro("bfr")
#pragma push_macro("etr")
#pragma push_macro("efr")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

#undef _uc_fpxreg
#undef _uc_xmmreg
#undef element
#undef cwd
#undef swd
#undef ftw
#undef fop
#undef rdp
#undef mxcr_mask
#undef st
#undef xmm
#undef padding
#undef p1home
#undef p2home
#undef p3home
#undef p4home
#undef p5home
#undef p6home
#undef mxcsr
#undef rax
#undef rcx
#undef rdx
#undef rbx
#undef rsp
#undef rbp
#undef rsi
#undef rdi
#undef r8
#undef r9
#undef r10
#undef r11
#undef r12
#undef r13
#undef r14
#undef r15
#undef rip
#undef fpregs
#undef vregs
#undef vcx
#undef dbc
#undef btr
#undef bfr
#undef etr
#undef efr

struct _uc_fpxreg {
	__uint16_t significand[4];
	__uint16_t exponent;
	__uint16_t padding[3];
};
struct _uc_xmmreg {
	__uint32_t element[4];
};
struct _fpstate {
	__uint16_t        cwd;
	__uint16_t        swd;
	__uint16_t        ftw;
	__uint16_t        fop;
	__uint64_t        rip;
	__uint64_t        rdp;
	__uint32_t        mxcsr;
	__uint32_t        mxcr_mask;
	struct _uc_fpxreg st[8];
	struct _uc_xmmreg xmm[16];
	__uint32_t        padding[24];
};

struct __ATTR_ALIGNED(16) mcontext {
	__uint64_t      p1home;
	__uint64_t      p2home;
	__uint64_t      p3home;
	__uint64_t      p4home;
	__uint64_t      p5home;
	__uint64_t      p6home;
	__uint32_t      ctxflags;
	__uint32_t      mxcsr;
	__uint16_t      cs;
	__uint16_t      ds;
	__uint16_t      es;
	__uint16_t      fs;
	__uint16_t      gs;
	__uint16_t      ss;
	__uint32_t      eflags;
	__uint64_t      dr0;
	__uint64_t      dr1;
	__uint64_t      dr2;
	__uint64_t      dr3;
	__uint64_t      dr6;
	__uint64_t      dr7;
	__uint64_t      rax;
	__uint64_t      rcx;
	__uint64_t      rdx;
	__uint64_t      rbx;
	__uint64_t      rsp;
	__uint64_t      rbp;
	__uint64_t      rsi;
	__uint64_t      rdi;
	__uint64_t      r8;
	__uint64_t      r9;
	__uint64_t      r10;
	__uint64_t      r11;
	__uint64_t      r12;
	__uint64_t      r13;
	__uint64_t      r14;
	__uint64_t      r15;
	__uint64_t      rip;
	struct _fpstate fpregs;
	__uint64_t      vregs[52];
	__uint64_t      vcx;
	__uint64_t      dbc;
	__uint64_t      btr;
	__uint64_t      bfr;
	__uint64_t      etr;
	__uint64_t      efr;
	__uint64_t      oldmask;
	__uint64_t      cr2;
};

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("efr")
#pragma pop_macro("etr")
#pragma pop_macro("bfr")
#pragma pop_macro("btr")
#pragma pop_macro("dbc")
#pragma pop_macro("vcx")
#pragma pop_macro("vregs")
#pragma pop_macro("fpregs")
#pragma pop_macro("rip")
#pragma pop_macro("r15")
#pragma pop_macro("r14")
#pragma pop_macro("r13")
#pragma pop_macro("r12")
#pragma pop_macro("r11")
#pragma pop_macro("r10")
#pragma pop_macro("r9")
#pragma pop_macro("r8")
#pragma pop_macro("rdi")
#pragma pop_macro("rsi")
#pragma pop_macro("rbp")
#pragma pop_macro("rsp")
#pragma pop_macro("rbx")
#pragma pop_macro("rdx")
#pragma pop_macro("rcx")
#pragma pop_macro("rax")
#pragma pop_macro("mxcsr")
#pragma pop_macro("p6home")
#pragma pop_macro("p5home")
#pragma pop_macro("p4home")
#pragma pop_macro("p3home")
#pragma pop_macro("p2home")
#pragma pop_macro("p1home")
#pragma pop_macro("padding")
#pragma pop_macro("xmm")
#pragma pop_macro("st")
#pragma pop_macro("mxcr_mask")
#pragma pop_macro("rdp")
#pragma pop_macro("fop")
#pragma pop_macro("ftw")
#pragma pop_macro("swd")
#pragma pop_macro("cwd")
#pragma pop_macro("element")
#pragma pop_macro("_uc_xmmreg")
#pragma pop_macro("_uc_fpxreg")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

#else /* __x86_64__ */

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("_uc_fpreg")
#pragma push_macro("cw")
#pragma push_macro("sw")
#pragma push_macro("tag")
#pragma push_macro("ipoff")
#pragma push_macro("cssel")
#pragma push_macro("dataoff")
#pragma push_macro("datasel")
#pragma push_macro("_st")
#pragma push_macro("nxst")
#pragma push_macro("fpstate")
#pragma push_macro("edi")
#pragma push_macro("esi")
#pragma push_macro("ebx")
#pragma push_macro("edx")
#pragma push_macro("ecx")
#pragma push_macro("eax")
#pragma push_macro("ebp")
#pragma push_macro("eip")
#pragma push_macro("esp")
#pragma push_macro("reserved")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef _uc_fpreg
#undef cw
#undef sw
#undef tag
#undef ipoff
#undef cssel
#undef dataoff
#undef datasel
#undef _st
#undef nxst
#undef fpstate
#undef edi
#undef esi
#undef ebx
#undef edx
#undef ecx
#undef eax
#undef ebp
#undef eip
#undef esp
#undef reserved

struct _uc_fpreg {
	__uint16_t significand[4];
	__uint16_t exponent;
};
struct _fpstate {
	__uint32_t       cw;
	__uint32_t       sw;
	__uint32_t       tag;
	__uint32_t       ipoff;
	__uint32_t       cssel;
	__uint32_t       dataoff;
	__uint32_t       datasel;
	struct _uc_fpreg _st[8];
	__uint32_t       nxst;
};
struct mcontext {
	__uint32_t      ctxflags;
	__uint32_t      dr0;
	__uint32_t      dr1;
	__uint32_t      dr2;
	__uint32_t      dr3;
	__uint32_t      dr6;
	__uint32_t      dr7;
	struct _fpstate fpstate;
	__uint32_t      gs;
	__uint32_t      fs;
	__uint32_t      es;
	__uint32_t      ds;
	__uint32_t      edi;
	__uint32_t      esi;
	__uint32_t      ebx;
	__uint32_t      edx;
	__uint32_t      ecx;
	__uint32_t      eax;
	__uint32_t      ebp;
	__uint32_t      eip;
	__uint32_t      cs;
	__uint32_t      eflags;
	__uint32_t      esp;
	__uint32_t      ss;
	__uint32_t      reserved[128];
	__uint32_t      oldmask;
	__uint32_t      cr2;
};

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("reserved")
#pragma pop_macro("esp")
#pragma pop_macro("eip")
#pragma pop_macro("ebp")
#pragma pop_macro("eax")
#pragma pop_macro("ecx")
#pragma pop_macro("edx")
#pragma pop_macro("ebx")
#pragma pop_macro("esi")
#pragma pop_macro("edi")
#pragma pop_macro("fpstate")
#pragma pop_macro("nxst")
#pragma pop_macro("_st")
#pragma pop_macro("datasel")
#pragma pop_macro("dataoff")
#pragma pop_macro("cssel")
#pragma pop_macro("ipoff")
#pragma pop_macro("tag")
#pragma pop_macro("sw")
#pragma pop_macro("cw")
#pragma pop_macro("_uc_fpreg")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

#endif /* !__x86_64__ */

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("cr2")
#pragma pop_macro("oldmask")
#pragma pop_macro("dr7")
#pragma pop_macro("dr6")
#pragma pop_macro("dr3")
#pragma pop_macro("dr2")
#pragma pop_macro("dr1")
#pragma pop_macro("dr0")
#pragma pop_macro("eflags")
#pragma pop_macro("ss")
#pragma pop_macro("gs")
#pragma pop_macro("fs")
#pragma pop_macro("es")
#pragma pop_macro("ds")
#pragma pop_macro("cs")
#pragma pop_macro("ctxflags")
#pragma pop_macro("_fpstate")
#pragma pop_macro("exponent")
#pragma pop_macro("significand")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

typedef struct mcontext mcontext_t;

/* Userlevel context. */
typedef __ATTR_ALIGNED(16) struct ucontext {
	mcontext_t         uc_mcontext;
	struct ucontext   *uc_link;
	__sigset_t         uc_sigmask;
	stack_t            uc_stack;
	unsigned long int  uc_flags;
} ucontext_t;
#endif /* __CC__ */


#endif /* ... */

__SYSDECL_END

#endif /* !_I386_KOS_SYS_UCONTEXT_H */
