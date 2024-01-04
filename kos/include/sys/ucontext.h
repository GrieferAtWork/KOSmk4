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
/* (#) Portability: Cygwin        (/winsup/cygwin/include/sys/ucontext.h) */
/* (#) Portability: DragonFly BSD (/sys/sys/ucontext.h) */
/* (#) Portability: FreeBSD       (/sys/sys/ucontext.h) */
/* (#) Portability: GNU C Library (/sysdeps/[...]/sys/ucontext.h) */
/* (#) Portability: NetBSD        (/sys/sys/ucontext.h) */
/* (#) Portability: OpenSolaris   (/usr/src/uts/[...]/sys/ucontext.h) */
/* (#) Portability: diet libc     (/include/sys/ucontext.h) */
/* (#) Portability: mintlib       (/include/sys/ucontext.h) */
/* (#) Portability: musl libc     (/include/sys/ucontext.h) */
#ifndef _SYS_UCONTEXT_H
#define _SYS_UCONTEXT_H 1

#include <__stdinc.h>
#include <features.h>

#include <bits/os/mcontext.h> /* struct mcontext */
#include <bits/os/ucontext.h> /* struct ucontext */

#ifdef __MCONTEXT_NGREG
#define NGREG __MCONTEXT_NGREG
#endif /* __MCONTEXT_NGREG */

#define __SIZEOF_GREG_T__  __SIZEOF_REGISTER__

#ifdef __CC__
__DECL_BEGIN

#ifndef __greg_t_defined
#define __greg_t_defined
#if defined(__KOS__) && __KOS_VERSION__ >= 300
typedef __REGISTER_TYPE__ greg_t;
#else /* __KOS__ && __KOS_VERSION__ >= 300 */
typedef __SREGISTER_TYPE__ greg_t;
#endif /* !__KOS__ || __KOS_VERSION__ < 300 */
#endif /* !__greg_t_defined */

#ifndef __ucontext_t_defined
#define __ucontext_t_defined
typedef struct ucontext ucontext_t;
#endif /* !__ucontext_t_defined */

#ifndef __mcontext_t_defined
#define __mcontext_t_defined
typedef struct mcontext mcontext_t;
#endif /* !__mcontext_t_defined */

__DECL_END
#endif /* __CC__ */

#endif /* !_SYS_UCONTEXT_H */
