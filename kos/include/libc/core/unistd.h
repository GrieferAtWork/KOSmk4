/* HASH CRC-32:0x50c6b6ad */
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
#ifndef _LIBC_CORE_UNISTD_H
#define _LIBC_CORE_UNISTD_H 1

#include <__stdinc.h>

#ifdef __CC__
#include <__crt.h>
#include <hybrid/typecore.h>

__SYSDECL_BEGIN

#ifndef ____libc_core_getpagesize_defined
#define ____libc_core_getpagesize_defined
#include <asm/pagesize.h>
#if defined(__CRT_HAVE_getpagesize) && defined(__ARCH_PAGESIZE)
#include <features.h>
/* >> getpagesize(3)
 * Return the size of a PAGE (in bytes) */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__STDC_INT_AS_SIZE_T,__NOTHROW,__libc_core_getpagesize,(void),getpagesize,{ return __ARCH_PAGESIZE; })
#elif defined(__CRT_HAVE_getpagesize)
#include <features.h>
/* >> getpagesize(3)
 * Return the size of a PAGE (in bytes) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__STDC_INT_AS_SIZE_T,__NOTHROW,__libc_core_getpagesize,(void),getpagesize,())
#elif defined(__CRT_HAVE___getpagesize)
#include <features.h>
/* >> getpagesize(3)
 * Return the size of a PAGE (in bytes) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__STDC_INT_AS_SIZE_T,__NOTHROW,__libc_core_getpagesize,(void),__getpagesize,())
#elif defined(__ARCH_PAGESIZE)
#include <features.h>
/* >> getpagesize(3)
 * Return the size of a PAGE (in bytes) */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __STDC_INT_AS_SIZE_T __NOTHROW(__LIBCCALL __libc_core_getpagesize)(void) { return __ARCH_PAGESIZE; }
#else /* ... */
#undef ____libc_core_getpagesize_defined
#endif /* !... */
#endif /* !____libc_core_getpagesize_defined */
#if !defined(____libc_core_syscall_defined) && defined(__CRT_HAVE_syscall)
#define ____libc_core_syscall_defined
#include <bits/types.h>
/* >> syscall(2), syscall64(2) */
__CVREDIRECT(,__LONGPTR_TYPE__,__NOTHROW_RPC,__libc_core_syscall,(__LONGPTR_TYPE__ __sysno),syscall,(__sysno),__sysno,6,(__syscall_ulong_t,__syscall_ulong_t,__syscall_ulong_t,__syscall_ulong_t,__syscall_ulong_t,__syscall_ulong_t))
#endif /* !____libc_core_syscall_defined && __CRT_HAVE_syscall */
#ifndef ____libc_core_syscall64_defined
#define ____libc_core_syscall64_defined
#ifdef __CRT_HAVE_syscall
#include <bits/types.h>
/* >> syscall(2), syscall64(2) */
__CVREDIRECT(,__LONG64_TYPE__,__NOTHROW_RPC,__libc_core_syscall64,(__syscall_ulong_t __sysno),syscall,(__sysno),__sysno,6,(__syscall_ulong_t,__syscall_ulong_t,__syscall_ulong_t,__syscall_ulong_t,__syscall_ulong_t,__syscall_ulong_t))
#elif defined(__CRT_HAVE_syscall64)
#include <bits/types.h>
/* >> syscall(2), syscall64(2) */
__CVREDIRECT(,__LONG64_TYPE__,__NOTHROW_RPC,__libc_core_syscall64,(__syscall_ulong_t __sysno),syscall64,(__sysno),__sysno,6,(__syscall_ulong_t,__syscall_ulong_t,__syscall_ulong_t,__syscall_ulong_t,__syscall_ulong_t,__syscall_ulong_t))
#elif defined(__CRT_HAVE___syscall)
#include <bits/types.h>
/* >> syscall(2), syscall64(2) */
__CVREDIRECT(,__LONG64_TYPE__,__NOTHROW_RPC,__libc_core_syscall64,(__syscall_ulong_t __sysno),__syscall,(__sysno),__sysno,6,(__syscall_ulong_t,__syscall_ulong_t,__syscall_ulong_t,__syscall_ulong_t,__syscall_ulong_t,__syscall_ulong_t))
#else /* ... */
#undef ____libc_core_syscall64_defined
#endif /* !... */
#endif /* !____libc_core_syscall64_defined */

__SYSDECL_END

#endif /* __CC__ */

#endif /* !_LIBC_CORE_UNISTD_H */
