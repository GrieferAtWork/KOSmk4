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
#ifndef _I386_KOS_BITS_OS_LINUX_MCONTEXT32_H
#define _I386_KOS_BITS_OS_LINUX_MCONTEXT32_H 1

/* File:
 *    <i386-kos/bits/os/linux/mcontext32.h>
 *
 * Definitions:
 *    - typedef ... __gregset_linux32_t;
 *    - typedef ... __fpregset_linux32_t;
 *    - struct __mcontext_linux32 { ... };
 * #if defined(__linux__) && (!defined(__x86_64__) && defined(__i386__))
 *    - typedef ... gregset_t;
 *    - typedef ... fpregset_t;
 *    - struct mcontext { ... };
 * #endif
 */

#include <__stdinc.h>
#include <features.h>

#include <hybrid/host.h>
#include <hybrid/typecore.h>
#include <hybrid/__pointer.h> /* __HYBRID_PTR32 */

#if ((defined(__linux__) || (defined(__KOS__) && __KOS_VERSION__ < 300)) && \
     (!defined(__x86_64__) && defined(__i386__)))
#define __MCONTEXT_NGREG       __MCONTEXT_LINUX32_NGREG
#define __gregset_linux32_t    gregset_t
#define __fpregset_linux32_t   fpregset_t
#define __libc_linux32_fpreg   _libc_fpreg
#define __libc_linux32_fpstate _libc_fpstate
#define __mcontext_linux32     mcontext
#ifdef __USE_GNU
/* Number of each register is the `__gregset_linux32_t' array. */
#define REG_GS     __MCONTEXT_LINUX32_REGNO_GS
#define REG_FS     __MCONTEXT_LINUX32_REGNO_FS
#define REG_ES     __MCONTEXT_LINUX32_REGNO_ES
#define REG_DS     __MCONTEXT_LINUX32_REGNO_DS
#define REG_EDI    __MCONTEXT_LINUX32_REGNO_EDI
#define REG_ESI    __MCONTEXT_LINUX32_REGNO_ESI
#define REG_EBP    __MCONTEXT_LINUX32_REGNO_EBP
#define REG_ESP    __MCONTEXT_LINUX32_REGNO_ESP
#define REG_EBX    __MCONTEXT_LINUX32_REGNO_EBX
#define REG_EDX    __MCONTEXT_LINUX32_REGNO_EDX
#define REG_ECX    __MCONTEXT_LINUX32_REGNO_ECX
#define REG_EAX    __MCONTEXT_LINUX32_REGNO_EAX
#define REG_TRAPNO __MCONTEXT_LINUX32_REGNO_TRAPNO
#define REG_ERR    __MCONTEXT_LINUX32_REGNO_ERR
#define REG_EIP    __MCONTEXT_LINUX32_REGNO_EIP
#define REG_CS     __MCONTEXT_LINUX32_REGNO_CS
#define REG_EFL    __MCONTEXT_LINUX32_REGNO_EFL
#define REG_UESP   __MCONTEXT_LINUX32_REGNO_UESP
#define REG_SS     __MCONTEXT_LINUX32_REGNO_SS
#endif /* __USE_GNU */
#define __MCONTEXT_REGNO_GS             __MCONTEXT_LINUX32_REGNO_GS
#define __MCONTEXT_REGNO_FS             __MCONTEXT_LINUX32_REGNO_FS
#define __MCONTEXT_REGNO_ES             __MCONTEXT_LINUX32_REGNO_ES
#define __MCONTEXT_REGNO_DS             __MCONTEXT_LINUX32_REGNO_DS
#define __MCONTEXT_REGNO_EDI            __MCONTEXT_LINUX32_REGNO_EDI
#define __MCONTEXT_REGNO_ESI            __MCONTEXT_LINUX32_REGNO_ESI
#define __MCONTEXT_REGNO_EBP            __MCONTEXT_LINUX32_REGNO_EBP
#define __MCONTEXT_REGNO_ESP            __MCONTEXT_LINUX32_REGNO_ESP
#define __MCONTEXT_REGNO_EBX            __MCONTEXT_LINUX32_REGNO_EBX
#define __MCONTEXT_REGNO_EDX            __MCONTEXT_LINUX32_REGNO_EDX
#define __MCONTEXT_REGNO_ECX            __MCONTEXT_LINUX32_REGNO_ECX
#define __MCONTEXT_REGNO_EAX            __MCONTEXT_LINUX32_REGNO_EAX
#define __MCONTEXT_REGNO_TRAPNO         __MCONTEXT_LINUX32_REGNO_TRAPNO
#define __MCONTEXT_REGNO_ERR            __MCONTEXT_LINUX32_REGNO_ERR
#define __MCONTEXT_REGNO_EIP            __MCONTEXT_LINUX32_REGNO_EIP
#define __MCONTEXT_REGNO_CS             __MCONTEXT_LINUX32_REGNO_CS
#define __MCONTEXT_REGNO_EFL            __MCONTEXT_LINUX32_REGNO_EFL
#define __MCONTEXT_REGNO_UESP           __MCONTEXT_LINUX32_REGNO_UESP
#define __MCONTEXT_REGNO_SS             __MCONTEXT_LINUX32_REGNO_SS
#define __OFFSET_LIBC_FPREG_SIGNIFICAND __OFFSET_LIBC_LINUX32_FPREG_SIGNIFICAND
#define __OFFSET_LIBC_FPREG_EXPONENT    __OFFSET_LIBC_LINUX32_FPREG_EXPONENT
#define __SIZEOF_LIBC_FPREG             __SIZEOF_LIBC_LINUX32_FPREG
#define __OFFSET_LIBC_FPSTATE_CW        __OFFSET_LIBC_LINUX32_FPSTATE_CW
#define __OFFSET_LIBC_FPSTATE_SW        __OFFSET_LIBC_LINUX32_FPSTATE_SW
#define __OFFSET_LIBC_FPSTATE_TAG       __OFFSET_LIBC_LINUX32_FPSTATE_TAG
#define __OFFSET_LIBC_FPSTATE_IPOFF     __OFFSET_LIBC_LINUX32_FPSTATE_IPOFF
#define __OFFSET_LIBC_FPSTATE_CSSEL     __OFFSET_LIBC_LINUX32_FPSTATE_CSSEL
#define __OFFSET_LIBC_FPSTATE_DATAOFF   __OFFSET_LIBC_LINUX32_FPSTATE_DATAOFF
#define __OFFSET_LIBC_FPSTATE_DATASEL   __OFFSET_LIBC_LINUX32_FPSTATE_DATASEL
#define __OFFSET_LIBC_FPSTATE_ST        __OFFSET_LIBC_LINUX32_FPSTATE_ST
#define __OFFSET_LIBC_FPSTATE_STATUS    __OFFSET_LIBC_LINUX32_FPSTATE_STATUS
#define __SIZEOF_LIBC_FPSTATE           __SIZEOF_LIBC_LINUX32_FPSTATE
#define __OFFSET_MCONTEXT_GREGS         __OFFSET_MCONTEXT_LINUX32_GREGS
#define __OFFSET_MCONTEXT_FPREGS        __OFFSET_MCONTEXT_LINUX32_FPREGS
#define __OFFSET_MCONTEXT_OLDMASK       __OFFSET_MCONTEXT_LINUX32_OLDMASK
#define __OFFSET_MCONTEXT_CR2           __OFFSET_MCONTEXT_LINUX32_CR2
#define __SIZEOF_MCONTEXT               __SIZEOF_MCONTEXT_LINUX32
#define __ALIGNOF_MCONTEXT              __ALIGNOF_MCONTEXT_LINUX32
#endif /* (__linux__ || (__KOS__ && __KOS_VERSION__ < 300)) && (!__x86_64__ && __i386__) */

__DECL_BEGIN

#define __MCONTEXT_LINUX32_NGREG 19 /* Number of general registers. */

/* Number of each register is the `__gregset_linux32_t' array. */
#define __MCONTEXT_LINUX32_REGNO_GS     0
#define __MCONTEXT_LINUX32_REGNO_FS     1
#define __MCONTEXT_LINUX32_REGNO_ES     2
#define __MCONTEXT_LINUX32_REGNO_DS     3
#define __MCONTEXT_LINUX32_REGNO_EDI    4
#define __MCONTEXT_LINUX32_REGNO_ESI    5
#define __MCONTEXT_LINUX32_REGNO_EBP    6
#define __MCONTEXT_LINUX32_REGNO_ESP    7
#define __MCONTEXT_LINUX32_REGNO_EBX    8
#define __MCONTEXT_LINUX32_REGNO_EDX    9
#define __MCONTEXT_LINUX32_REGNO_ECX    10
#define __MCONTEXT_LINUX32_REGNO_EAX    11
#define __MCONTEXT_LINUX32_REGNO_TRAPNO 12
#define __MCONTEXT_LINUX32_REGNO_ERR    13
#define __MCONTEXT_LINUX32_REGNO_EIP    14
#define __MCONTEXT_LINUX32_REGNO_CS     15
#define __MCONTEXT_LINUX32_REGNO_EFL    16
#define __MCONTEXT_LINUX32_REGNO_UESP   17
#define __MCONTEXT_LINUX32_REGNO_SS     18

#ifdef __CC__
typedef __UINT32_TYPE__ __gregset_linux32_t[__MCONTEXT_LINUX32_NGREG]; /* Container for all general registers. */
#endif /* __CC__ */


#define __OFFSET_LIBC_LINUX32_FPREG_SIGNIFICAND 0
#define __OFFSET_LIBC_LINUX32_FPREG_EXPONENT    8
#define __SIZEOF_LIBC_LINUX32_FPREG             10

#ifdef __CC__
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("significand")
#pragma push_macro("exponent")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef significand
#undef exponent
struct __libc_linux32_fpreg /*[NAME(libc_linux32_fpreg)][PREFIX()]*/ {
	/* Definitions taken from the kernel headers. */
	__UINT16_TYPE__ significand[4];
	__UINT16_TYPE__ exponent;
};
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("exponent")
#pragma pop_macro("significand")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#endif /* __CC__ */

#define __OFFSET_LIBC_LINUX32_FPSTATE_CW      0
#define __OFFSET_LIBC_LINUX32_FPSTATE_SW      4
#define __OFFSET_LIBC_LINUX32_FPSTATE_TAG     8
#define __OFFSET_LIBC_LINUX32_FPSTATE_IPOFF   12
#define __OFFSET_LIBC_LINUX32_FPSTATE_CSSEL   16
#define __OFFSET_LIBC_LINUX32_FPSTATE_DATAOFF 20
#define __OFFSET_LIBC_LINUX32_FPSTATE_DATASEL 24
#define __OFFSET_LIBC_LINUX32_FPSTATE_ST      28 /* [FIELD(_st)] */
#define __OFFSET_LIBC_LINUX32_FPSTATE_STATUS  108
#define __SIZEOF_LIBC_LINUX32_FPSTATE         112

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
struct __libc_linux32_fpstate /*[NAME(libc_linux32_fpstate)][PREFIX()]*/ {
	__ULONG32_TYPE__            cw;
	__ULONG32_TYPE__            sw;
	__ULONG32_TYPE__            tag;
	__ULONG32_TYPE__            ipoff;
	__ULONG32_TYPE__            cssel;
	__ULONG32_TYPE__            dataoff;
	__ULONG32_TYPE__            datasel;
	struct __libc_linux32_fpreg _st[8];
	__ULONG32_TYPE__            status;
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
typedef __HYBRID_PTR32(struct __libc_linux32_fpstate) __fpregset_linux32_t;
#endif /* __CC__ */


#define __OFFSET_MCONTEXT_LINUX32_GREGS   0
#define __OFFSET_MCONTEXT_LINUX32_FPREGS  (4 * __MCONTEXT_LINUX32_NGREG)
#define __OFFSET_MCONTEXT_LINUX32_OLDMASK (4 * __MCONTEXT_LINUX32_NGREG + 4)
#define __OFFSET_MCONTEXT_LINUX32_CR2     (4 * __MCONTEXT_LINUX32_NGREG + 8)
#define __SIZEOF_MCONTEXT_LINUX32         (4 * __MCONTEXT_LINUX32_NGREG + 12)
#define __ALIGNOF_MCONTEXT_LINUX32        4
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
struct __mcontext_linux32 /*[NAME(mcontext_linux32)][PREFIX()]*/ {
	/* Context to describe whole processor state. */
	__gregset_linux32_t  gregs;
	__fpregset_linux32_t fpregs; /* Due to Linux's history we have to use a pointer here.
	                              * The SysV/i386 ABI requires a struct with the  values. */
	__ULONG32_TYPE__     oldmask;
	__ULONG32_TYPE__     cr2;
};
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("cr2")
#pragma pop_macro("oldmask")
#pragma pop_macro("fpregs")
#pragma pop_macro("gregs")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#endif /* __CC__ */

__DECL_END

#endif /* !_I386_KOS_BITS_OS_LINUX_MCONTEXT32_H */
