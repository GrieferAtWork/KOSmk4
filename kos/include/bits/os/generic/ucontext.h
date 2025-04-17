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
/*!replace_with_include <bits/os/ucontext.h>*/
#ifndef _BITS_OS_GENERIC_UCONTEXT_H
#define _BITS_OS_GENERIC_UCONTEXT_H 1

/* File:
 *    <bits/os/kos/ucontext.h>
 *
 * Definitions:
 *    - struct ucontext { ... };
 */

#include <__stdinc.h>

#include <hybrid/typecore.h>

#include <bits/os/mcontext.h> /* struct mcontext */
#include <bits/os/sigset.h>   /* struct __sigset_struct */
#include <bits/os/sigstack.h> /* struct sigaltstack */

#undef __ARCH_HAVE_UCONTEXT_FLAGS
#define __ARCH_HAVE_UCONTEXT_FLAGS

#ifndef __ALIGNOF_UCONTEXT
#if defined(__ALIGNOF_MCONTEXT) && (__ALIGNOF_MCONTEXT > __SIZEOF_POINTER__)
#define __ALIGNOF_UCONTEXT __ALIGNOF_MCONTEXT
#else /* __ALIGNOF_MCONTEXT */
#define __ALIGNOF_UCONTEXT __SIZEOF_POINTER__
#endif /* !__ALIGNOF_MCONTEXT */
#endif /* !__ALIGNOF_UCONTEXT */

#ifdef __ARCH_HAVE_UCONTEXT_FLAGS
#define __OFFSET_UCONTEXT_FLAGS 0
#define __OFFSET_UCONTEXT_LINK  __SIZEOF_POINTER__
#else /* __ARCH_HAVE_UCONTEXT_FLAGS */
#define __OFFSET_UCONTEXT_LINK  0
#endif /* !__ARCH_HAVE_UCONTEXT_FLAGS */
#define __OFFSET_UCONTEXT_STACK    (__OFFSET_UCONTEXT_LINK + __SIZEOF_POINTER__)
#define __OFFSET_UCONTEXT_MCONTEXT (__OFFSET_UCONTEXT_LINK + __SIZEOF_POINTER__ + __SIZEOF_SIGALTSTACK)
#if (__SIZEOF_MCONTEXT % __ALIGNOF_SIGSET_T__) == 0
#define __OFFSET_UCONTEXT_SIGMASK  (__OFFSET_UCONTEXT_LINK + __SIZEOF_POINTER__ + __SIZEOF_SIGALTSTACK + __SIZEOF_MCONTEXT)
#else /*  (__SIZEOF_MCONTEXT % __ALIGNOF_SIGSET_T__) == 0 */
#define __OFFSET_UCONTEXT_SIGMASK  (__OFFSET_UCONTEXT_LINK + __SIZEOF_POINTER__ + __SIZEOF_SIGALTSTACK + __SIZEOF_MCONTEXT + __ALIGNOF_SIGSET_T__ - (__SIZEOF_MCONTEXT % __ALIGNOF_SIGSET_T__))
#endif /* (__SIZEOF_MCONTEXT % __ALIGNOF_SIGSET_T__) != 0 */

#ifdef __CC__
__DECL_BEGIN

/* Userlevel context. */
struct __ATTR_ALIGNED(__ALIGNOF_UCONTEXT) ucontext /*[NAME(ucontext)][PREFIX(uc_)]*/ {
#ifdef __ARCH_HAVE_UCONTEXT_FLAGS
	__ULONGPTR_TYPE__      uc_flags;    /* Set of `UC_*' (arch-specific; none may actually be defined) */
#endif /* __ARCH_HAVE_UCONTEXT_FLAGS */
	struct ucontext       *uc_link;
	struct sigaltstack     uc_stack;
	struct mcontext        uc_mcontext;
#if (__SIZEOF_MCONTEXT % __ALIGNOF_SIGSET_T__) != 0
	__BYTE_TYPE__        __uc_pad[__ALIGNOF_SIGSET_T__ - (__SIZEOF_MCONTEXT % __ALIGNOF_SIGSET_T__)];
#endif /* (__SIZEOF_MCONTEXT % __ALIGNOF_SIGSET_T__) != 0 */
	struct __sigset_struct uc_sigmask;
};

__DECL_END
#endif /* __CC__ */

#endif /* !_BITS_OS_GENERIC_UCONTEXT_H */
