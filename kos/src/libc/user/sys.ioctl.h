/* HASH CRC-32:0x7cf3bd92 */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_SYS_IOCTL_H
#define GUARD_LIBC_USER_SYS_IOCTL_H 1

#include "../api.h"
#include "../auto/sys.ioctl.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <sys/ioctl.h>

DECL_BEGIN

#ifndef __KERNEL__
/* Perform the I/O control operation specified by REQUEST on FD.
 * One argument may follow; its presence and type depend on REQUEST.
 * Return value depends on REQUEST. Usually -1 indicates error */
INTDEF __STDC_INT_AS_SSIZE_T NOTHROW_RPC(VLIBCCALL libc_ioctl)(fd_t fd, ulongptr_t request, ...);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_IOCTL_H */
