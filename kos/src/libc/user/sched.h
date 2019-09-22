/* HASH CRC-32:0xcb4f00d7 */
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
#ifndef GUARD_LIBC_USER_SCHED_H
#define GUARD_LIBC_USER_SCHED_H 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include <sched.h>

DECL_BEGIN

INTDEF int NOTHROW_NCX(LIBCCALL libc_sched_setparam)(pid_t pid, struct sched_param const *param);
INTDEF int NOTHROW_NCX(LIBCCALL libc_sched_getparam)(pid_t pid, struct sched_param *param);
INTDEF int NOTHROW_NCX(LIBCCALL libc_sched_setscheduler)(pid_t pid, int policy, struct sched_param const *param);
INTDEF int NOTHROW_NCX(LIBCCALL libc_sched_getscheduler)(pid_t pid);
/* @return: 1: Another thread was executed prior to the function returning
 *             The thread may not necessarily be apart of the calling process
 * @return: 0: The function returned immediately when no other thread was executed */
INTDEF int NOTHROW_NCX(LIBCCALL libc_sched_yield)(void);
INTDEF int NOTHROW_NCX(LIBCCALL libc_sched_get_priority_max)(int algorithm);
INTDEF int NOTHROW_NCX(LIBCCALL libc_sched_get_priority_min)(int algorithm);
INTDEF int NOTHROW_NCX(LIBCCALL libc_sched_setaffinity)(pid_t pid, size_t cpusetsize, cpu_set_t const *cpuset);
INTDEF int NOTHROW_NCX(LIBCCALL libc_sched_getaffinity)(pid_t pid, size_t cpusetsize, cpu_set_t *cpuset);
INTDEF int NOTHROW_NCX(LIBCCALL libc_sched_rr_get_interval)(pid_t pid, struct timespec *tms);
INTDEF int NOTHROW_NCX(LIBCCALL libc_sched_rr_get_interval64)(pid_t pid, struct timespec64 *tms);

DECL_END

#endif /* !GUARD_LIBC_USER_SCHED_H */
