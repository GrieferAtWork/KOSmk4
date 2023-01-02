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
#ifndef _I386_KOS_BITS_OS_LINUX_MCONTEXT64_H
#define _I386_KOS_BITS_OS_LINUX_MCONTEXT64_H 1

/* File:
 *    <i386-kos/bits/os/linux/mcontext64.h>
 *
 * Definitions:
 *    - typedef ... __gregset_linux64_t;
 *    - typedef ... __fpregset_linux64_t;
 *    - struct __mcontext_linux64 { ... };
 * #if defined(__linux__) && defined(__x86_64__)
 *    - typedef ... gregset_t;
 *    - typedef ... fpregset_t;
 *    - struct mcontext { ... };
 * #endif
 */

#include <__stdinc.h>

#include <hybrid/host.h>
#include <hybrid/typecore.h>
#include <hybrid/__pointer.h> /* __HYBRID_PTR64 */

#if defined(__linux__) && defined(__x86_64__)
#define __MCONTEXT_NGREG       __MCONTEXT_LINUX64_NGREG
#define __gregset_linux64_t    gregset_t
#define __fpregset_linux64_t   fpregset_t
#define __libc_linux64_xmmreg  _libc_xmmreg
#define __libc_linux64_fpxreg  _libc_fpxreg
#define __libc_linux64_fpstate _libc_fpstate
#define __mcontext_linux64     mcontext
#ifdef __USE_GNU
#define REG_R8      __MCONTEXT_LINUX64_REGNO_R8
#define REG_R9      __MCONTEXT_LINUX64_REGNO_R9
#define REG_R10     __MCONTEXT_LINUX64_REGNO_R10
#define REG_R11     __MCONTEXT_LINUX64_REGNO_R11
#define REG_R12     __MCONTEXT_LINUX64_REGNO_R12
#define REG_R13     __MCONTEXT_LINUX64_REGNO_R13
#define REG_R14     __MCONTEXT_LINUX64_REGNO_R14
#define REG_R15     __MCONTEXT_LINUX64_REGNO_R15
#define REG_RDI     __MCONTEXT_LINUX64_REGNO_RDI
#define REG_RSI     __MCONTEXT_LINUX64_REGNO_RSI
#define REG_RBP     __MCONTEXT_LINUX64_REGNO_RBP
#define REG_RBX     __MCONTEXT_LINUX64_REGNO_RBX
#define REG_RDX     __MCONTEXT_LINUX64_REGNO_RDX
#define REG_RAX     __MCONTEXT_LINUX64_REGNO_RAX
#define REG_RCX     __MCONTEXT_LINUX64_REGNO_RCX
#define REG_RSP     __MCONTEXT_LINUX64_REGNO_RSP
#define REG_RIP     __MCONTEXT_LINUX64_REGNO_RIP
#define REG_EFL     __MCONTEXT_LINUX64_REGNO_EFL
#define REG_CSGSFS  __MCONTEXT_LINUX64_REGNO_CSGSFS
#define REG_ERR     __MCONTEXT_LINUX64_REGNO_ERR
#define REG_TRAPNO  __MCONTEXT_LINUX64_REGNO_TRAPNO
#define REG_OLDMASK __MCONTEXT_LINUX64_REGNO_OLDMASK
#define REG_CR2     __MCONTEXT_LINUX64_REGNO_CR2
#endif /* __USE_GNU */
#define __MCONTEXT_REGNO_R8              __MCONTEXT_LINUX64_REGNO_R8
#define __MCONTEXT_REGNO_R9              __MCONTEXT_LINUX64_REGNO_R9
#define __MCONTEXT_REGNO_R10             __MCONTEXT_LINUX64_REGNO_R10
#define __MCONTEXT_REGNO_R11             __MCONTEXT_LINUX64_REGNO_R11
#define __MCONTEXT_REGNO_R12             __MCONTEXT_LINUX64_REGNO_R12
#define __MCONTEXT_REGNO_R13             __MCONTEXT_LINUX64_REGNO_R13
#define __MCONTEXT_REGNO_R14             __MCONTEXT_LINUX64_REGNO_R14
#define __MCONTEXT_REGNO_R15             __MCONTEXT_LINUX64_REGNO_R15
#define __MCONTEXT_REGNO_RDI             __MCONTEXT_LINUX64_REGNO_RDI
#define __MCONTEXT_REGNO_RSI             __MCONTEXT_LINUX64_REGNO_RSI
#define __MCONTEXT_REGNO_RBP             __MCONTEXT_LINUX64_REGNO_RBP
#define __MCONTEXT_REGNO_RBX             __MCONTEXT_LINUX64_REGNO_RBX
#define __MCONTEXT_REGNO_RDX             __MCONTEXT_LINUX64_REGNO_RDX
#define __MCONTEXT_REGNO_RAX             __MCONTEXT_LINUX64_REGNO_RAX
#define __MCONTEXT_REGNO_RCX             __MCONTEXT_LINUX64_REGNO_RCX
#define __MCONTEXT_REGNO_RSP             __MCONTEXT_LINUX64_REGNO_RSP
#define __MCONTEXT_REGNO_RIP             __MCONTEXT_LINUX64_REGNO_RIP
#define __MCONTEXT_REGNO_EFL             __MCONTEXT_LINUX64_REGNO_EFL
#define __MCONTEXT_REGNO_CSGSFS          __MCONTEXT_LINUX64_REGNO_CSGSFS
#define __MCONTEXT_REGNO_ERR             __MCONTEXT_LINUX64_REGNO_ERR
#define __MCONTEXT_REGNO_TRAPNO          __MCONTEXT_LINUX64_REGNO_TRAPNO
#define __MCONTEXT_REGNO_OLDMASK         __MCONTEXT_LINUX64_REGNO_OLDMASK
#define __MCONTEXT_REGNO_CR2             __MCONTEXT_LINUX64_REGNO_CR2
#define __OFFSET_LIBC_FPXREG_SIGNIFICAND __OFFSET_LIBC_LINUX64_FPXREG_SIGNIFICAND
#define __OFFSET_LIBC_FPXREG_EXPONENT    __OFFSET_LIBC_LINUX64_FPXREG_EXPONENT
#define __OFFSET_LIBC_FPXREG_PADDING     __OFFSET_LIBC_LINUX64_FPXREG_PADDING
#define __SIZEOF_LIBC_FPXREG             __SIZEOF_LIBC_LINUX64_FPXREG
#define __OFFSET_LIBC_XMMREG_ELEMENT     __OFFSET_LIBC_LINUX64_XMMREG_ELEMENT
#define __SIZEOF_LIBC_XMMREG             __SIZEOF_LIBC_LINUX64_XMMREG
#define __OFFSET_LIBC_FPSTATE_CWD        __OFFSET_LIBC_LINUX64_FPSTATE_CWD
#define __OFFSET_LIBC_FPSTATE_SWD        __OFFSET_LIBC_LINUX64_FPSTATE_SWD
#define __OFFSET_LIBC_FPSTATE_FTW        __OFFSET_LIBC_LINUX64_FPSTATE_FTW
#define __OFFSET_LIBC_FPSTATE_FOP        __OFFSET_LIBC_LINUX64_FPSTATE_FOP
#define __OFFSET_LIBC_FPSTATE_RIP        __OFFSET_LIBC_LINUX64_FPSTATE_RIP
#define __OFFSET_LIBC_FPSTATE_RDP        __OFFSET_LIBC_LINUX64_FPSTATE_RDP
#define __OFFSET_LIBC_FPSTATE_MXCSR      __OFFSET_LIBC_LINUX64_FPSTATE_MXCSR
#define __OFFSET_LIBC_FPSTATE_MXCR_MASK  __OFFSET_LIBC_LINUX64_FPSTATE_MXCR_MASK
#define __OFFSET_LIBC_FPSTATE_ST         __OFFSET_LIBC_LINUX64_FPSTATE_ST
#define __OFFSET_LIBC_FPSTATE_XMM        __OFFSET_LIBC_LINUX64_FPSTATE_XMM
#define __OFFSET_LIBC_FPSTATE_PADDING    __OFFSET_LIBC_LINUX64_FPSTATE_PADDING
#define __SIZEOF_LIBC_FPSTATE            __SIZEOF_LIBC_LINUX64_FPSTATE
#define __OFFSET_MCONTEXT_GREGS          __OFFSET_MCONTEXT_LINUX64_GREGS
#define __OFFSET_MCONTEXT_FPREGS         __OFFSET_MCONTEXT_LINUX64_FPREGS
#if defined(__USE_KOS_KERNEL) && defined(__KOS__)
#define __OFFSET_MCONTEXT_FS_BASE __OFFSET_MCONTEXT_LINUX64_FS_BASE
#define __OFFSET_MCONTEXT_GS_BASE __OFFSET_MCONTEXT_LINUX64_GS_BASE
#endif /* __USE_KOS_KERNEL && __KOS__ */
#define __SIZEOF_MCONTEXT  __SIZEOF_MCONTEXT_LINUX64
#define __ALIGNOF_MCONTEXT __ALIGNOF_MCONTEXT_LINUX64
#endif /* __linux__ && __x86_64__ */

__DECL_BEGIN

#define __MCONTEXT_LINUX64_NGREG 23 /* Number of general registers. */
#ifdef __CC__
typedef __INT64_TYPE__ __gregset_linux64_t[__MCONTEXT_LINUX64_NGREG]; /* Container for all general registers. */
#endif /* __CC__ */

/* Number of each register in the `__gregset_linux64_t' array. */

#define __MCONTEXT_LINUX64_REGNO_R8      0
#define __MCONTEXT_LINUX64_REGNO_R9      1
#define __MCONTEXT_LINUX64_REGNO_R10     2
#define __MCONTEXT_LINUX64_REGNO_R11     3
#define __MCONTEXT_LINUX64_REGNO_R12     4
#define __MCONTEXT_LINUX64_REGNO_R13     5
#define __MCONTEXT_LINUX64_REGNO_R14     6
#define __MCONTEXT_LINUX64_REGNO_R15     7
#define __MCONTEXT_LINUX64_REGNO_RDI     8
#define __MCONTEXT_LINUX64_REGNO_RSI     9
#define __MCONTEXT_LINUX64_REGNO_RBP     10
#define __MCONTEXT_LINUX64_REGNO_RBX     11
#define __MCONTEXT_LINUX64_REGNO_RDX     12
#define __MCONTEXT_LINUX64_REGNO_RAX     13
#define __MCONTEXT_LINUX64_REGNO_RCX     14
#define __MCONTEXT_LINUX64_REGNO_RSP     15
#define __MCONTEXT_LINUX64_REGNO_RIP     16
#define __MCONTEXT_LINUX64_REGNO_EFL     17
#define __MCONTEXT_LINUX64_REGNO_CSGSFS  18
#define __MCONTEXT_LINUX64_REGNO_ERR     19
#define __MCONTEXT_LINUX64_REGNO_TRAPNO  20
#define __MCONTEXT_LINUX64_REGNO_OLDMASK 21
#define __MCONTEXT_LINUX64_REGNO_CR2     22

#define __OFFSET_LIBC_LINUX64_FPXREG_SIGNIFICAND 0
#define __OFFSET_LIBC_LINUX64_FPXREG_EXPONENT    8
#define __OFFSET_LIBC_LINUX64_FPXREG_PADDING     10
#define __SIZEOF_LIBC_LINUX64_FPXREG             16

#ifdef __CC__
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("significand")
#pragma push_macro("exponent")
#pragma push_macro("padding")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef significand
#undef exponent
#undef padding
struct __libc_linux64_fpxreg /*[NAME(libc_linux64_fpxreg)][PREFIX()]*/ {
	__UINT16_TYPE__ significand[4];
	__UINT16_TYPE__ exponent;
	__UINT16_TYPE__ padding[3];
};
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("padding")
#pragma pop_macro("exponent")
#pragma pop_macro("significand")
#endif /* !__COMPILER_HAVE_PRAGMA_PUSHMACRO */
#endif /* __CC__ */

#define __OFFSET_LIBC_LINUX64_XMMREG_ELEMENT 0
#define __SIZEOF_LIBC_LINUX64_XMMREG         16
#ifdef __CC__
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("element")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef element
struct __libc_linux64_xmmreg /*[NAME(libc_linux64_xmmreg)][PREFIX()]*/ {
	__UINT32_TYPE__ element[4];
};
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("element")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#endif /* __CC__ */

#define __OFFSET_LIBC_LINUX64_FPSTATE_CWD       0
#define __OFFSET_LIBC_LINUX64_FPSTATE_SWD       2
#define __OFFSET_LIBC_LINUX64_FPSTATE_FTW       4
#define __OFFSET_LIBC_LINUX64_FPSTATE_FOP       6
#define __OFFSET_LIBC_LINUX64_FPSTATE_RIP       8
#define __OFFSET_LIBC_LINUX64_FPSTATE_RDP       16
#define __OFFSET_LIBC_LINUX64_FPSTATE_MXCSR     24
#define __OFFSET_LIBC_LINUX64_FPSTATE_MXCR_MASK 28
#define __OFFSET_LIBC_LINUX64_FPSTATE_ST        32 /* [FIELD(_st)] */
#define __OFFSET_LIBC_LINUX64_FPSTATE_XMM       160 /* [FIELD(_xmm)] */
#define __OFFSET_LIBC_LINUX64_FPSTATE_PADDING   416
#define __SIZEOF_LIBC_LINUX64_FPSTATE           512

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
struct __libc_linux64_fpstate /*[NAME(libc_linux64_fpstate)][PREFIX()]*/ {
	/* 64-bit FXSAVE format. */
	__UINT16_TYPE__              cwd;
	__UINT16_TYPE__              swd;
	__UINT16_TYPE__              ftw;
	__UINT16_TYPE__              fop;
	__UINT64_TYPE__              rip;
	__UINT64_TYPE__              rdp;
	__UINT32_TYPE__              mxcsr;
	__UINT32_TYPE__              mxcr_mask;
	struct __libc_linux64_fpxreg _st[8];
	struct __libc_linux64_xmmreg _xmm[16];
	__UINT32_TYPE__              padding[24];
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
typedef __HYBRID_PTR64(struct __libc_linux64_fpstate) __fpregset_linux64_t;
#endif /* __CC__ */


#define __OFFSET_MCONTEXT_LINUX64_GREGS  0
#define __OFFSET_MCONTEXT_LINUX64_FPREGS (8 * __MCONTEXT_LINUX64_NGREG)
#if defined(__USE_KOS_KERNEL) && defined(__KOS__)
#define __OFFSET_MCONTEXT_LINUX64_FS_BASE (8 * __MCONTEXT_LINUX64_NGREG + 8)
#define __OFFSET_MCONTEXT_LINUX64_GS_BASE (8 * __MCONTEXT_LINUX64_NGREG + 2 * 8)
#endif /* __USE_KOS_KERNEL && __KOS__ */
#define __SIZEOF_MCONTEXT_LINUX64  (8 * __MCONTEXT_LINUX64_NGREG + 9 * 8)
#define __ALIGNOF_MCONTEXT_LINUX64 8

#ifdef __CC__
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("gregs")
#pragma push_macro("fpregs")
#if defined(__USE_KOS_KERNEL) && defined(__KOS__)
#pragma push_macro("fs_base")
#pragma push_macro("gs_base")
#endif /* __USE_KOS_KERNEL && __KOS__ */
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef gregs
#undef fpregs
#if defined(__USE_KOS_KERNEL) && defined(__KOS__)
#undef fs_base
#undef gs_base
#endif /* __USE_KOS_KERNEL && __KOS__ */
/* Context to describe whole processor state. */
struct __ATTR_ALIGNED(__ALIGNOF_MCONTEXT_LINUX64) __mcontext_linux64 /*[NAME(mcontext_linux64)][PREFIX()]*/ {
	__gregset_linux64_t  gregs;
	__fpregset_linux64_t fpregs;  /* Note that fpregs is a pointer. */
#if defined(__USE_KOS_KERNEL) && defined(__KOS__)
	__UINT64_TYPE__      fs_base; /* User-space `fs_base' address. */
	__UINT64_TYPE__      gs_base; /* User-space `gs_base' address. */
	__UINT64_TYPE__    __reserved1[6];
#else /* __USE_KOS_KERNEL && __KOS__ */
	__UINT64_TYPE__    __reserved1[8];
#endif /* !__USE_KOS_KERNEL || !__KOS__ */
};

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#if defined(__USE_KOS_KERNEL) && defined(__KOS__)
#pragma pop_macro("gs_base")
#pragma pop_macro("fs_base")
#endif /* __USE_KOS_KERNEL && __KOS__ */
#pragma pop_macro("fpregs")
#pragma pop_macro("gregs")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#endif /* __CC__ */

__DECL_END

#endif /* !_I386_KOS_BITS_OS_LINUX_MCONTEXT64_H */
