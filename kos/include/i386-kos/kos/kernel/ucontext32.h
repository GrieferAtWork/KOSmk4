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
#ifndef _I386_KOS_KOS_KERNEL_UCONTEXT32_H
#define _I386_KOS_KOS_KERNEL_UCONTEXT32_H 1

#include <__stdinc.h>
#include <hybrid/host.h>
#include <hybrid/__pointer.h>
#include <kos/kernel/mcontext32.h>
#include <bits/sigset.h>
#include <bits/sigstack32.h>

__DECL_BEGIN

#ifndef __x86_64__
#define __OFFSET_UCONTEXT_MCONTEXT __OFFSET_UCONTEXT32_MCONTEXT
#define __OFFSET_UCONTEXT_SIGMASK  __OFFSET_UCONTEXT32_SIGMASK
#define __OFFSET_UCONTEXT_STACK    __OFFSET_UCONTEXT32_STACK
#define __OFFSET_UCONTEXT_LINK     __OFFSET_UCONTEXT32_LINK
#define __SIZEOF_UCONTEXT          __SIZEOF_UCONTEXT32
#define ucontext32     ucontext
#define ucontext32_t   ucontext_t
#endif /* !__x86_64__ */


#define __OFFSET_UCONTEXT32_MCONTEXT 0
#define __OFFSET_UCONTEXT32_SIGMASK  592
#define __OFFSET_UCONTEXT32_STACK    720
#define __OFFSET_UCONTEXT32_LINK     732
#define __SIZEOF_UCONTEXT32          736

#ifdef __CC__
struct ucontext32; /* Userlevel context. */
typedef struct ucontext32 {
	mcontext32_t                      uc_mcontext;
	__sigset_t                        uc_sigmask;
	struct sigaltstack32              uc_stack;
	__HYBRID_PTR32(struct ucontext32) uc_link;
} ucontext32_t;
#endif /* __CC__ */


__DECL_END

#endif /* !_I386_KOS_KOS_KERNEL_UCONTEXT32_H */
