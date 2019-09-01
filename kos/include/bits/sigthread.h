/* HASH 0x7b554986 */
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
#ifndef _BITS_SIGTHREAD_H
#define _BITS_SIGTHREAD_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <bits/pthreadtypes.h>
#include <bits/sigval.h> /* union sigval */

__SYSDECL_BEGIN

#ifdef __CC__

struct __sigset_struct;

#ifndef __pthread_sigmask_defined
#define __pthread_sigmask_defined 1
#if defined(__CRT_HAVE_pthread_sigmask)
__CDECLARE(,int,__NOTHROW_NCX,pthread_sigmask,(int __how, struct __sigset_struct const *__restrict __newmask, struct __sigset_struct *__restrict __oldmask),(__how,__newmask,__oldmask))
#else /* LIBC: pthread_sigmask */
#undef __pthread_sigmask_defined
#endif /* pthread_sigmask... */
#endif /* !__pthread_sigmask_defined */
#ifndef __pthread_kill_defined
#define __pthread_kill_defined 1
#if defined(__CRT_HAVE_pthread_kill)
__CDECLARE(,int,__NOTHROW_NCX,pthread_kill,(pthread_t __threadid, int __signo),(__threadid,__signo))
#else /* LIBC: pthread_kill */
#undef __pthread_kill_defined
#endif /* pthread_kill... */
#endif /* !__pthread_kill_defined */
#ifdef __USE_GNU
#ifndef __pthread_sigqueue_defined
#define __pthread_sigqueue_defined 1
#if defined(__CRT_HAVE_pthread_sigqueue)
__CDECLARE(,int,__NOTHROW_NCX,pthread_sigqueue,(pthread_t __threadid, int __signo, union sigval const __value),(__threadid,__signo,__value))
#else /* LIBC: pthread_sigqueue */
#undef __pthread_sigqueue_defined
#endif /* pthread_sigqueue... */
#endif /* !__pthread_sigqueue_defined */
#endif /* __USE_GNU */
#endif /* __CC__ */

__SYSDECL_END

#endif /* !_BITS_SIGTHREAD_H */
