/* HASH CRC-32:0xf97da3ac */
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
#ifndef _SYS_RESOURCE_H
#define _SYS_RESOURCE_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <bits/resource.h>
#include <bits/types.h>

__SYSDECL_BEGIN

/* Documentation taken from Glibc /usr/include/i386-linux-gnu/sys/resource.h */
/* Copyright (C) 1992-2016 Free Software Foundation, Inc.
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

#ifndef __id_t_defined
#define __id_t_defined
typedef __id_t id_t;
#endif /* !__id_t_defined */

#if defined(__USE_GNU) && defined(__COMPILER_PREFERR_ENUMS)
typedef enum __rlimit_resource __rlimit_resource_t;
typedef enum __rusage_who      __rusage_who_t;
typedef enum __priority_which  __priority_which_t;
#else /* __USE_GNU && __COMPILER_PREFERR_ENUMS */
typedef int __rlimit_resource_t;
typedef int __rusage_who_t;
typedef int __priority_which_t;
#endif /* !__USE_GNU || !__COMPILER_PREFERR_ENUMS */

#if defined(__CRT_HAVE_getrlimit64) && defined(__USE_FILE_OFFSET64)
/* Put the soft and hard limits for RESOURCE in *RLIMITS.
 * Returns 0 if successful, -1 if not (and sets errno) */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,getrlimit,(__rlimit_resource_t __resource, struct rlimit *__rlimits),getrlimit64,(__resource,__rlimits))
#elif defined(__CRT_HAVE_getrlimit) && !defined(__USE_FILE_OFFSET64)
/* Put the soft and hard limits for RESOURCE in *RLIMITS.
 * Returns 0 if successful, -1 if not (and sets errno) */
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,getrlimit,(__rlimit_resource_t __resource, struct rlimit *__rlimits),(__resource,__rlimits))
#elif defined(__CRT_HAVE___getrlimit) && !defined(__USE_FILE_OFFSET64)
/* Put the soft and hard limits for RESOURCE in *RLIMITS.
 * Returns 0 if successful, -1 if not (and sets errno) */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,getrlimit,(__rlimit_resource_t __resource, struct rlimit *__rlimits),__getrlimit,(__resource,__rlimits))
#endif /* getrlimit... */
#if defined(__CRT_HAVE_setrlimit64) && defined(__USE_FILE_OFFSET64)
/* Set the soft and hard limits for RESOURCE to *RLIMITS.
 * Only the super-user can increase hard limits.
 * Return 0 if successful, -1 if not (and sets errno) */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,setrlimit,(__rlimit_resource_t __resource, struct rlimit const *__rlimits),setrlimit64,(__resource,__rlimits))
#elif defined(__CRT_HAVE_setrlimit) && !defined(__USE_FILE_OFFSET64)
/* Set the soft and hard limits for RESOURCE to *RLIMITS.
 * Only the super-user can increase hard limits.
 * Return 0 if successful, -1 if not (and sets errno) */
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,setrlimit,(__rlimit_resource_t __resource, struct rlimit const *__rlimits),(__resource,__rlimits))
#endif /* setrlimit... */
#ifdef __CRT_HAVE_getrusage
/* Return resource usage information on process indicated by WHO
 * and put it in *USAGE. Returns 0 for success, -1 for failure */
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,getrusage,(__rusage_who_t __who, struct rusage *__usage),(__who,__usage))
#endif /* getrusage... */
/* TODO: getrusage64() (__USE_TIME64 & __USE_TIME_BITS64 integration) */
#ifdef __CRT_HAVE_getpriority
/* Return the highest priority of any process specified by WHICH and
 * WHO (see above); if WHO is zero, the current process, process group,
 * or user (as specified by WHO) is used.  A lower priority number means
 * higher priority. Priorities range from PRIO_MIN to PRIO_MAX (above) */
__CDECLARE(,int,__NOTHROW_NCX,getpriority,(__priority_which_t __which, id_t __who),(__which,__who))
#endif /* getpriority... */
#ifdef __CRT_HAVE_setpriority
/* Set the priority of all processes specified by WHICH and WHO (see above) to PRIO.
 * Returns 0 on success, -1 on errors */
__CDECLARE(,int,__NOTHROW_NCX,setpriority,(__priority_which_t __which, id_t __who, int __prio),(__which,__who,__prio))
#endif /* setpriority... */

#ifdef __USE_LARGEFILE64
#ifdef __CRT_HAVE_getrlimit64
/* Put the soft and hard limits for RESOURCE in *RLIMITS.
 * Returns 0 if successful, -1 if not (and sets errno) */
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,getrlimit64,(__rlimit_resource_t __resource, struct rlimit64 *__rlimits),(__resource,__rlimits))
#elif defined(__CRT_HAVE_getrlimit) && (__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* Put the soft and hard limits for RESOURCE in *RLIMITS.
 * Returns 0 if successful, -1 if not (and sets errno) */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,getrlimit64,(__rlimit_resource_t __resource, struct rlimit64 *__rlimits),getrlimit,(__resource,__rlimits))
#endif /* getrlimit64... */
#ifdef __CRT_HAVE_setrlimit64
/* Set the soft and hard limits for RESOURCE to *RLIMITS.
 * Only the super-user can increase hard limits.
 * Return 0 if successful, -1 if not (and sets errno) */
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,setrlimit64,(__rlimit_resource_t __resource, struct rlimit64 const *__rlimits),(__resource,__rlimits))
#elif defined(__CRT_HAVE_setrlimit) && (__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* Set the soft and hard limits for RESOURCE to *RLIMITS.
 * Only the super-user can increase hard limits.
 * Return 0 if successful, -1 if not (and sets errno) */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,setrlimit64,(__rlimit_resource_t __resource, struct rlimit64 const *__rlimits),setrlimit,(__resource,__rlimits))
#endif /* setrlimit64... */
#endif /* __USE_LARGEFILE64 */
#endif /* __CC__ */

__SYSDECL_END

#endif /* !_SYS_RESOURCE_H */
