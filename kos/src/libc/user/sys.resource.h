/* HASH CRC-32:0x7ccd5149 */
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
#ifndef GUARD_LIBC_USER_SYS_RESOURCE_H
#define GUARD_LIBC_USER_SYS_RESOURCE_H 1

#include "../api.h"
#include "../auto/sys.resource.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <sys/resource.h>

DECL_BEGIN

#ifndef __KERNEL__
/* Put the soft and hard limits for RESOURCE in *RLIMITS.
 * Returns 0 if successful, -1 if not (and sets errno) */
INTDEF NONNULL((2)) int NOTHROW_NCX(LIBCCALL libc_getrlimit)(__rlimit_resource_t resource, struct rlimit *rlimits);
/* Set the soft and hard limits for RESOURCE to *RLIMITS.
 * Only the super-user can increase hard limits.
 * Return 0 if successful, -1 if not (and sets errno) */
INTDEF NONNULL((2)) int NOTHROW_NCX(LIBCCALL libc_setrlimit)(__rlimit_resource_t resource, struct rlimit const *rlimits);
/* Return resource usage information on process indicated by WHO
 * and put it in *USAGE. Returns 0 for success, -1 for failure */
INTDEF NONNULL((2)) int NOTHROW_NCX(LIBCCALL libc_getrusage)(__rusage_who_t who, struct rusage *usage);
/* Return the highest priority of any process specified by WHICH and
 * WHO (see above); if WHO is zero, the current process, process group,
 * or user (as specified by WHO) is used.  A lower priority number means
 * higher priority. Priorities range from PRIO_MIN to PRIO_MAX (above) */
INTDEF int NOTHROW_NCX(LIBCCALL libc_getpriority)(__priority_which_t which, id_t who);
/* Set the priority of all processes specified by WHICH and WHO (see above) to PRIO.
 * Returns 0 on success, -1 on errors */
INTDEF int NOTHROW_NCX(LIBCCALL libc_setpriority)(__priority_which_t which, id_t who, int prio);
/* Put the soft and hard limits for RESOURCE in *RLIMITS.
 * Returns 0 if successful, -1 if not (and sets errno) */
INTDEF NONNULL((2)) int NOTHROW_NCX(LIBCCALL libc_getrlimit64)(__rlimit_resource_t resource, struct rlimit64 *rlimits);
/* Set the soft and hard limits for RESOURCE to *RLIMITS.
 * Only the super-user can increase hard limits.
 * Return 0 if successful, -1 if not (and sets errno) */
INTDEF NONNULL((2)) int NOTHROW_NCX(LIBCCALL libc_setrlimit64)(__rlimit_resource_t resource, struct rlimit64 const *rlimits);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_RESOURCE_H */
