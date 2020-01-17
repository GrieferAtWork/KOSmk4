/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _I386_KOS_KOS_KERNEL_UCONTEXT64_H
#define _I386_KOS_KOS_KERNEL_UCONTEXT64_H 1

#include <__stdinc.h>

#include <hybrid/__pointer.h>
#include <hybrid/host.h>

#include <bits/sigset.h>
#include <bits/sigstack64.h>
#include <kos/kernel/mcontext64.h>

__DECL_BEGIN

#ifdef __x86_64__
#define __OFFSET_UCONTEXT_MCONTEXT __OFFSET_UCONTEXT64_MCONTEXT
#define __OFFSET_UCONTEXT_SIGMASK  __OFFSET_UCONTEXT64_SIGMASK
#define __OFFSET_UCONTEXT_STACK    __OFFSET_UCONTEXT64_STACK
#define __OFFSET_UCONTEXT_LINK     __OFFSET_UCONTEXT64_LINK
#define __SIZEOF_UCONTEXT          __SIZEOF_UCONTEXT64
#define ucontext64     ucontext
#define ucontext64_t   ucontext_t
#endif /* __x86_64__ */


#define __OFFSET_UCONTEXT64_MCONTEXT 0
#define __OFFSET_UCONTEXT64_SIGMASK  736
#define __OFFSET_UCONTEXT64_STACK    864
#define __OFFSET_UCONTEXT64_LINK     888
#define __SIZEOF_UCONTEXT64          896
#ifdef __CC__
struct ucontext64; /* Userlevel context. */
typedef struct ucontext64 {
	mcontext64_t                      uc_mcontext;
	__sigset_t                        uc_sigmask;
	struct sigaltstack64              uc_stack;
	__HYBRID_PTR64(struct ucontext64) uc_link;
} ucontext64_t;
#endif /* __CC__ */


__DECL_END

#endif /* !_I386_KOS_KOS_KERNEL_UCONTEXT64_H */
