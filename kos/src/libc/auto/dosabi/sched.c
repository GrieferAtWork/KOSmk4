/* HASH CRC-32:0xe6ca589e */
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
#ifndef GUARD_LIBC_AUTO_DOSABI_SCHED_C
#define GUARD_LIBC_AUTO_DOSABI_SCHED_C 1

#include "../../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../../user/sched.h"

DECL_BEGIN

INTERN ATTR_SECTION(".text.crt.dos.sched.param") int
NOTHROW_NCX(LIBDCALL libd_sched_setparam)(pid_t pid,
                                          struct sched_param const *param) {
	return libc_sched_setparam(pid, param);
}
INTERN ATTR_SECTION(".text.crt.dos.sched.param") int
NOTHROW_NCX(LIBDCALL libd_sched_getparam)(pid_t pid,
                                          struct sched_param *param) {
	return libc_sched_getparam(pid, param);
}
INTERN ATTR_SECTION(".text.crt.dos.sched.param") int
NOTHROW_NCX(LIBDCALL libd_sched_setscheduler)(pid_t pid,
                                              int policy,
                                              struct sched_param const *param) {
	return libc_sched_setscheduler(pid, policy, param);
}
INTERN ATTR_SECTION(".text.crt.dos.sched.param") int
NOTHROW_NCX(LIBDCALL libd_sched_getscheduler)(pid_t pid) {
	return libc_sched_getscheduler(pid);
}
INTERN ATTR_SECTION(".text.crt.dos.sched.param") int
NOTHROW_NCX(LIBDCALL libd_sched_get_priority_max)(int algorithm) {
	return libc_sched_get_priority_max(algorithm);
}
INTERN ATTR_SECTION(".text.crt.dos.sched.param") int
NOTHROW_NCX(LIBDCALL libd_sched_get_priority_min)(int algorithm) {
	return libc_sched_get_priority_min(algorithm);
}
INTERN ATTR_SECTION(".text.crt.dos.sched.param") int
NOTHROW_NCX(LIBDCALL libd_sched_setaffinity)(pid_t pid,
                                             size_t cpusetsize,
                                             cpu_set_t const *cpuset) {
	return libc_sched_setaffinity(pid, cpusetsize, cpuset);
}
INTERN ATTR_SECTION(".text.crt.dos.sched.param") int
NOTHROW_NCX(LIBDCALL libd_sched_getaffinity)(pid_t pid,
                                             size_t cpusetsize,
                                             cpu_set_t *cpuset) {
	return libc_sched_getaffinity(pid, cpusetsize, cpuset);
}
INTERN ATTR_SECTION(".text.crt.dos.sched.param") int
NOTHROW_NCX(LIBDCALL libd_sched_rr_get_interval)(pid_t pid,
                                                 struct timespec *tms) {
	return libc_sched_rr_get_interval(pid, tms);
}
INTERN ATTR_SECTION(".text.crt.dos.sched.param") int
NOTHROW_NCX(LIBDCALL libd_sched_rr_get_interval64)(pid_t pid,
                                                   struct timespec64 *tms) {
	return libc_sched_rr_get_interval64(pid, tms);
}

DECL_END

DEFINE_PUBLIC_ALIAS(DOS$sched_setparam, libd_sched_setparam);
DEFINE_PUBLIC_ALIAS(DOS$__sched_getparam, libd_sched_getparam);
DEFINE_PUBLIC_ALIAS(DOS$sched_getparam, libd_sched_getparam);
DEFINE_PUBLIC_ALIAS(DOS$__sched_setscheduler, libd_sched_setscheduler);
DEFINE_PUBLIC_ALIAS(DOS$sched_setscheduler, libd_sched_setscheduler);
DEFINE_PUBLIC_ALIAS(DOS$__sched_getscheduler, libd_sched_getscheduler);
DEFINE_PUBLIC_ALIAS(DOS$sched_getscheduler, libd_sched_getscheduler);
DEFINE_PUBLIC_ALIAS(DOS$__sched_get_priority_max, libd_sched_get_priority_max);
DEFINE_PUBLIC_ALIAS(DOS$sched_get_priority_max, libd_sched_get_priority_max);
DEFINE_PUBLIC_ALIAS(DOS$__sched_get_priority_min, libd_sched_get_priority_min);
DEFINE_PUBLIC_ALIAS(DOS$sched_get_priority_min, libd_sched_get_priority_min);
DEFINE_PUBLIC_ALIAS(DOS$sched_setaffinity, libd_sched_setaffinity);
DEFINE_PUBLIC_ALIAS(DOS$sched_getaffinity, libd_sched_getaffinity);
DEFINE_PUBLIC_ALIAS(DOS$sched_rr_get_interval, libd_sched_rr_get_interval);
DEFINE_PUBLIC_ALIAS(DOS$sched_rr_get_interval64, libd_sched_rr_get_interval64);

#endif /* !GUARD_LIBC_AUTO_DOSABI_SCHED_C */
