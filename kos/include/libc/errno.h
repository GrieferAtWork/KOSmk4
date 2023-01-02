/* HASH CRC-32:0xa976a629 */
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
#ifndef _LIBC_ERRNO_H
#define _LIBC_ERRNO_H 1

#include <__stdinc.h>

#ifdef __CC__
#include <__crt.h>
#include "core/errno.h"

#include <asm/os/errno.h>
#include <bits/types.h>
#ifndef __libc_errno
#ifdef errno
#define __libc_errno errno
#else /* errno */
#if !defined(____libc___errno_location_defined) && defined(____libc_core___errno_location_defined)
#define ____libc___errno_location_defined
#define __libc___errno_location __libc_core___errno_location
#endif /* !____libc___errno_location_defined && ____libc_core___errno_location_defined */
#ifdef ____libc___errno_location_defined
#define __libc_errno (*__libc___errno_location())
#elif defined(__CRT_HAVE_errno) && 0
__DECL_BEGIN
__CSDECLARE(__ATTR_THREAD,__errno_t,errno)
__DECL_END
#define errno        errno
#define __libc_errno errno
#elif defined(__CRT_HAVE_errno)
__DECL_BEGIN
__CSDECLARE(,__errno_t,errno)
__DECL_END
#define errno        errno
#define __libc_errno errno
#endif /* ... */
#endif /* !__libc_errno */
#endif /* !errno */
#if !defined(__libc_geterrno) && defined(__libc_errno)
#define __libc_geterrno() __libc_errno
#endif /* !__libc_geterrno && __libc_errno */

#ifndef __libc_geterrno_or
#ifdef __libc_geterrno
#define __libc_geterrno_or(alt) __libc_geterrno()
#else /* __libc_geterrno */
#define __libc_geterrno_or(alt) alt
#endif /* !__libc_geterrno */
#endif /* !__libc_geterrno_or */

#ifndef __libc_seterrno
#ifdef __libc_errno
#define __libc_seterrno(val) (__libc_errno = (val), -1)
#else /* __libc_errno */
#define __libc_seterrno(val) (-1)
#endif /* !__libc_errno */
#endif /* !__libc_seterrno */

#endif /* __CC__ */

#endif /* !_LIBC_ERRNO_H */
