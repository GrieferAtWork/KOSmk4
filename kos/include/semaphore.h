/* HASH CRC-32:0x994bc6ee */
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
#ifndef _SEMAPHORE_H
#define _SEMAPHORE_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <sys/types.h>
#include <bits/types.h>
#include <bits/crt/semaphore.h>
#ifdef __USE_XOPEN2K
#include <bits/timespec.h>
#endif /* __USE_XOPEN2K */

__SYSDECL_BEGIN

/* Documentation taken from /usr/include/semaphore.h */
/* Copyright (C) 2002-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */


#ifdef __CC__
/* Initialize semaphore object SEM to VALUE.
 * If PSHARED then share it with other processes */
__CDECLARE_OPT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,sem_init,(sem_t *__sem, int __pshared, unsigned int __value),(__sem,__pshared,__value))
/* Free resources associated with semaphore object SEM */
__CDECLARE_OPT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,sem_destroy,(sem_t *__sem),(__sem))
#ifdef __CRT_HAVE_sem_open
/* Open a named semaphore NAME with open flags OFLAGS */
__LIBC __ATTR_NONNULL((1)) sem_t *__NOTHROW_RPC_KOS(__VLIBCCALL sem_open)(char const *__name, __oflag_t __oflags, ...) __CASMNAME_SAME("sem_open");
#endif /* __CRT_HAVE_sem_open */
/* Close descriptor for named semaphore SEM */
__CDECLARE_OPT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,sem_close,(sem_t *__sem),(__sem))
/* Remove named semaphore NAME */
__CDECLARE_OPT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC_KOS,sem_unlink,(const char *__name),(__name))
/* Wait for SEM being posted */
__CDECLARE_OPT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,sem_wait,(sem_t *__sem),(__sem))

#ifdef __USE_XOPEN2K
#if defined(__CRT_HAVE_sem_timedwait) && !defined(__USE_TIME_BITS64)
/* Similar to `sem_wait' but wait only until ABSTIME */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,sem_timedwait,(sem_t *__restrict __sem, struct timespec const *__restrict __abstime),(__sem,__abstime))
#elif defined(__CRT_HAVE_sem_timedwait64) && defined(__USE_TIME_BITS64)
/* Similar to `sem_wait' but wait only until ABSTIME */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,sem_timedwait,(sem_t *__restrict __sem, struct timespec const *__restrict __abstime),sem_timedwait64,(__sem,__abstime))
#elif defined(__CRT_HAVE_sem_timedwait64) || defined(__CRT_HAVE_sem_timedwait)
#include <local/semaphore/sem_timedwait.h>
/* Similar to `sem_wait' but wait only until ABSTIME */
__NAMESPACE_LOCAL_USING_OR_IMPL(sem_timedwait, __FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL sem_timedwait)(sem_t *__restrict __sem, struct timespec const *__restrict __abstime) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sem_timedwait))(__sem, __abstime); })
#endif /* ... */

#ifdef __USE_TIME64
#ifdef __CRT_HAVE_sem_timedwait64
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,sem_timedwait64,(sem_t *__restrict __sem, struct timespec64 const *__restrict __abstime),(__sem,__abstime))
#elif defined(__CRT_HAVE_sem_timedwait) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,sem_timedwait64,(sem_t *__restrict __sem, struct timespec64 const *__restrict __abstime),sem_timedwait,(__sem,__abstime))
#elif defined(__CRT_HAVE_sem_timedwait)
#include <local/semaphore/sem_timedwait64.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(sem_timedwait64, __FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL sem_timedwait64)(sem_t *__restrict __sem, struct timespec64 const *__restrict __abstime) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sem_timedwait64))(__sem, __abstime); })
#endif /* ... */
#endif /* __USE_TIME64 */
#endif /* __USE_XOPEN2K */
/* Test whether SEM is posted */
__CDECLARE_OPT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,sem_trywait,(sem_t *__sem),(__sem))
/* Post SEM */
__CDECLARE_OPT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,sem_post,(sem_t *__sem),(__sem))
/* Get current value of SEM and store it in *SVAL */
__CDECLARE_OPT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,sem_getvalue,(sem_t *__restrict __sem, int *__restrict __sval),(__sem,__sval))
#endif /* __CC__ */

__SYSDECL_END

#endif /* !_SEMAPHORE_H */
