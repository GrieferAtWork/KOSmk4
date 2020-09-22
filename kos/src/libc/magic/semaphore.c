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

%[define_replacement(fd_t = __fd_t)]
%[define_replacement(oflag_t = __oflag_t)]
%[define_replacement(timespec32 = __timespec32)]
%[define_replacement(timespec64 = __timespec64)]
%[define_replacement(sem_t = sem_t)]
%[default:section(".text.crt{|.dos}.sched.semaphore")]

%{
#include <features.h>
#include <sys/types.h>
#include <bits/types.h>
#include <bits/crt/semaphore.h>
#ifdef __USE_XOPEN2K
#include <bits/os/timespec.h>
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
}

@@Initialize semaphore object SEM to VALUE.
@@If PSHARED then share it with other processes
[[decl_include("<bits/crt/semaphore.h>")]]
int sem_init([[nonnull]] sem_t *sem, int pshared, unsigned int value);

@@Free resources associated with semaphore object SEM
[[decl_include("<bits/crt/semaphore.h>")]]
int sem_destroy([[nonnull]] sem_t *sem);

@@Open a named semaphore NAME with open flags OFLAGS
[[cp_kos, vartypes($mode_t, unsigned int)]]
[[decl_include("<bits/crt/semaphore.h>")]]
sem_t *sem_open([[nonnull]] char const *name, $oflag_t oflags, ...);

@@Close descriptor for named semaphore SEM
[[decl_include("<bits/crt/semaphore.h>")]]
int sem_close([[nonnull]] sem_t *sem);

@@Remove named semaphore NAME
[[cp_kos]]
int sem_unlink([[nonnull]] const char *name);

@@Wait for SEM being posted
[[cp, decl_include("<bits/crt/semaphore.h>")]]
int sem_wait([[nonnull]] sem_t *sem);

[[cp, doc_alias(sem_timedwait), ignore, nocrt, alias("sem_timedwait")]]
[[decl_include("<bits/crt/semaphore.h>", "<bits/os/timespec.h>")]]
int sem_timedwait32([[nonnull]] sem_t *__restrict sem,
                    [[nonnull]] struct $timespec32 const *__restrict abstime);


%
%#ifdef __USE_XOPEN2K
@@Similar to `sem_wait' but wait only until ABSTIME
[[cp, no_crt_self_import, decl_include("<bits/crt/semaphore.h>", "<bits/os/timespec.h>")]]
[[if(!defined(__USE_TIME_BITS64)), preferred_alias("sem_timedwait")]]
[[if(defined(__USE_TIME_BITS64)), preferred_alias("sem_timedwait64")]]
[[userimpl, requires($has_function(sem_timedwait32) || $has_function(sem_timedwait64))]]
int sem_timedwait([[nonnull]] sem_t *__restrict sem,
                  [[nonnull]] struct timespec const *__restrict abstime) {
@@pp_if $has_function(sem_timedwait32)@@
	struct timespec32 ts32;
	ts32.tv_sec = (time32_t)abstime->tv_sec;
	ts32.tv_nsec = abstime->tv_nsec;
	return sem_timedwait32(sem, &ts32);
@@pp_else@@
	struct timespec64 ts64;
	ts64.tv_sec = (time64_t)abstime->tv_sec;
	ts64.tv_nsec = abstime->tv_nsec;
	return sem_timedwait64(sem, &ts64);
@@pp_endif@@
}

%
%#ifdef __USE_TIME64
[[cp, time64_variant_of(sem_timedwait)]]
[[userimpl, requires_function(sem_timedwait32)]]
[[decl_include("<bits/crt/semaphore.h>", "<bits/os/timespec.h>")]]
int sem_timedwait64([[nonnull]] sem_t *__restrict sem,
                    [[nonnull]] struct timespec64 const *__restrict abstime) {
	struct timespec32 ts32;
	ts32.tv_sec  = (time32_t)abstime->tv_sec;
	ts32.tv_nsec = abstime->tv_nsec;
	return sem_timedwait32(sem, &ts32);
}
%#endif /* __USE_TIME64 */
%#endif /* __USE_XOPEN2K */

@@Test whether SEM is posted
[[decl_include("<bits/crt/semaphore.h>")]]
int sem_trywait([[nonnull]] sem_t *sem);

@@Post SEM
[[decl_include("<bits/crt/semaphore.h>")]]
int sem_post([[nonnull]] sem_t *sem);

@@Get current value of SEM and store it in *SVAL
[[decl_include("<bits/crt/semaphore.h>")]]
int sem_getvalue([[nonnull]] sem_t *__restrict sem,
                 [[nonnull]] int *__restrict sval);


%{
#endif /* __CC__ */

__SYSDECL_END

}