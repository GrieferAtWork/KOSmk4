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

%[define_replacement(id_t = __id_t)]
%[default_impl_section(.text.crt.sched.resource)]

%{
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

}


@@Put the soft and hard limits for RESOURCE in *RLIMITS.
@@Returns 0 if successful, -1 if not (and sets errno)
[if(defined(__USE_FILE_OFFSET64)), preferred_alias(getrlimit64)]
[if(!defined(__USE_FILE_OFFSET64)), preferred_alias(getrlimit, __getrlimit)]
getrlimit:(__rlimit_resource_t resource, [nonnull] struct rlimit *rlimits) -> int;

@@Set the soft and hard limits for RESOURCE to *RLIMITS.
@@Only the super-user can increase hard limits.
@@Return 0 if successful, -1 if not (and sets errno)
[if(defined(__USE_FILE_OFFSET64)), preferred_alias(setrlimit64)]
[if(!defined(__USE_FILE_OFFSET64)), preferred_alias(setrlimit)]
setrlimit:(__rlimit_resource_t resource, [nonnull] struct rlimit const *rlimits) -> int;

@@Return resource usage information on process indicated by WHO
@@and put it in *USAGE. Returns 0 for success, -1 for failure
getrusage:(__rusage_who_t who, [nonnull] struct rusage *usage) -> int;

%/* TODO: getrusage64() (__USE_TIME64 & __USE_TIME_BITS64 integration) */

@@Return the highest priority of any process specified by WHICH and
@@WHO (see above); if WHO is zero, the current process, process group,
@@or user (as specified by WHO) is used.  A lower priority number means
@@higher priority. Priorities range from PRIO_MIN to PRIO_MAX (above)
getpriority:(__priority_which_t which, id_t who) -> int;

@@Set the priority of all processes specified by WHICH and WHO (see above) to PRIO.
@@Returns 0 on success, -1 on errors
setpriority:(__priority_which_t which, id_t who, int prio) -> int;

%
%#ifdef __USE_LARGEFILE64
[off64_variant_of(getrlimit)]
getrlimit64:(__rlimit_resource_t resource, [nonnull] struct rlimit64 *rlimits) -> int;
[off64_variant_of(setrlimit)]
setrlimit64:(__rlimit_resource_t resource, [nonnull] struct rlimit64 const *rlimits) -> int;
%#endif /* __USE_LARGEFILE64 */


%{
#endif /* __CC__ */

__SYSDECL_END

}