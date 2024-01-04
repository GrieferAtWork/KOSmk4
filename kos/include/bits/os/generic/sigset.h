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
#ifndef _BITS_OS_GENERIC_SIGSET_H
#define _BITS_OS_GENERIC_SIGSET_H 1

/* File:
 *    <bits/os/generic/sigset.h>
 *
 * Definitions:
 *    - struct __sigset_struct { ... };
 *    - ulongptr_t __sigset_mask(signo_t signo);
 *    - ulongptr_t __sigset_word(signo_t signo);
 *    - #define __SIGSET_INIT(ulongptr_t f) { ... }
 */

#include <__stdinc.h>
#include <features.h>

#include <hybrid/typecore.h>

#include <asm/os/sigset.h> /* __SIZEOF_SIGSET_T__ */

#ifndef __ALIGNOF_SIGSET_T__
#define __ALIGNOF_SIGSET_T__ __SIZEOF_POINTER__
#endif /* !__ALIGNOF_SIGSET_T__ */

#define __SIGSET_NWORDS (__SIZEOF_SIGSET_T__ / __SIZEOF_POINTER__)

#ifdef __CC__
#if __ALIGNOF_SIGSET_T__ != __SIZEOF_POINTER__
__ATTR_ALIGNED(__ALIGNOF_SIGSET_T__)
struct __sigset_struct {
	__ULONGPTR_TYPE__ __val[__SIGSET_NWORDS];
};
#else /* __ALIGNOF_SIGSET_T__ != __SIZEOF_POINTER__ */
struct __sigset_struct {
	__ULONGPTR_TYPE__ __val[__SIGSET_NWORDS];
};
#endif /* __ALIGNOF_SIGSET_T__ == __SIZEOF_POINTER__ */

#ifdef __USE_KOS_KERNEL
struct __old_sigset_struct {
#if __SIZEOF_OLD_SIGSET_T__ == 4
	__ULONG32_TYPE__ __ss_sigmask;
#elif __SIZEOF_OLD_SIGSET_T__ == 8
	__ULONG64_TYPE__ __ss_sigmask;
#else /* __SIZEOF_OLD_SIGSET_T__ == ... */
	__BYTE_TYPE__ __ss_bits[__SIZEOF_OLD_SIGSET_T__];
#endif /* __SIZEOF_OLD_SIGSET_T__ != ... */
};
#endif /* __USE_KOS_KERNEL */

#if __SIGSET_NWORDS == 1
#define __SIGSET_INIT(f) \
	{                    \
		{ f }            \
	}
#elif __SIGSET_NWORDS == 2
#define __SIGSET_INIT(f) \
	{                    \
		{ f, f }         \
	}
#elif __SIGSET_NWORDS == 4
#define __SIGSET_INIT(f) \
	{                    \
		{ f, f, f, f }   \
	}
#elif __SIGSET_NWORDS == 8
#define __SIGSET_INIT(f)           \
	{                              \
		{ f, f, f, f, f, f, f, f } \
	}
#elif __SIGSET_NWORDS == 16
#define __SIGSET_INIT(f)                                   \
	{                                                      \
		{ f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f } \
	}
#elif __SIGSET_NWORDS == 32
#define __SIGSET_INIT(f)                                   \
	{                                                      \
		{ f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f,  \
		  f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f } \
	}
#elif __SIGSET_NWORDS == 64
#define __SIGSET_INIT(f)                                   \
	{                                                      \
		{ f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f,  \
		  f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f,  \
		  f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f,  \
		  f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f } \
	}
#else /* __SIGSET_NWORDS == ... */
#define __SIGSET_INIT(f)   { { [0 ... __SIGSET_NWORDS - 1] = f } }
#endif /* __SIGSET_NWORDS != ... */
#endif /* __CC__ */

/* Return the mask or index for a specific signal `sig' within some sigset. */
#define __sigset_mask(sig)   (__UINTPTR_C(1) << (((sig)-1) % (8 * __SIZEOF_POINTER__)))
#define __sigset_word(sig)   ((__CCAST(__ULONGPTR_TYPE__)(sig)-1) / (8 * __SIZEOF_POINTER__))
#define __sigset_word_c(sig) (((sig)-1) / (8 * __SIZEOF_POINTER__))

#endif /* !_BITS_OS_GENERIC_SIGSET_H */
