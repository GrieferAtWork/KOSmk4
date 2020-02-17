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
#ifndef _KOS_HOP_API_H
#define _KOS_HOP_API_H 1

#include <__stdinc.h>
#include <__crt.h>
#include <bits/types.h>
#include <hybrid/typecore.h>

#if defined(__KERNEL__) && __SIZEOF_SIZE_T__ < 8
#define __HOP_SIZE64_FIELD(name) union { __size_t name; __uint64_t __##name##64; }
#else /* __KERNEL__ */
/* For compatibility, user-space must always write the full 64-bit field,
 * while the kernel will only ever read a size_t-sized field.
 * This is required when a 32-bit application is running under a 64-bit kernel,
 * allowing the kernel to not have to look out for user-space running in
 * compatibility mode, but can instead always read the full 64-bit value,
 * with is simply zero-extended from 32-bit by user-space. */
#define __HOP_SIZE64_FIELD(name) __uint64_t name
#endif /* !__KERNEL__ */

#ifndef __HOP_PAD_POINTER
#if __SIZEOF_POINTER__ < 8
#define __HOP_PAD_POINTER(name) __uint32_t name;
#else /* __SIZEOF_POINTER__ < 8 */
#define __HOP_PAD_POINTER(name) /* nothing */
#endif /* __SIZEOF_POINTER__ >= 8 */
#endif /* !__HOP_PAD_POINTER */

#ifdef __CC__
__SYSDECL_BEGIN

/* Perform a handle operation specified by `cmd' */
#if defined(__CRT_HAVE_hop)
__LIBC __syscall_slong_t __NOTHROW_NCX(__VLIBCCALL hop)(__fd_t __fd, __syscall_ulong_t __cmd, ... /*, void *arg*/) __CASMNAME_SAME("hop");
#endif /* hop... */
#if defined(__CRT_HAVE_hopf)
__LIBC __syscall_slong_t __NOTHROW_NCX(__VLIBCCALL hopf)(__fd_t __fd, __syscall_ulong_t __cmd, __iomode_t __mode, ... /*, void *arg*/) __CASMNAME_SAME("hopf");
#endif /* hopf... */
#if defined(__CRT_HAVE_Hop)
__LIBC __syscall_slong_t __NOTHROW_NCX(__VLIBCCALL Hop)(__fd_t __fd, __syscall_ulong_t __cmd, ... /*, void *arg*/) __CASMNAME_SAME("Hop");
#endif /* hop... */
#if defined(__CRT_HAVE_Hopf)
__LIBC __syscall_slong_t __NOTHROW_NCX(__VLIBCCALL Hopf)(__fd_t __fd, __syscall_ulong_t __cmd, __iomode_t __mode, ... /*, void *arg*/) __CASMNAME_SAME("Hopf");
#endif /* hopf... */

__SYSDECL_END
#endif /* __CC__ */


#endif /* !_KOS_HOP_API_H */
