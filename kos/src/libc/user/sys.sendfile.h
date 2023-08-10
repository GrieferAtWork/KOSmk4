/* HASH CRC-32:0xfff39dc7 */
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
#ifndef GUARD_LIBC_USER_SYS_SENDFILE_H
#define GUARD_LIBC_USER_SYS_SENDFILE_H 1

#include "../api.h"
#include "../auto/sys.sendfile.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <sys/sendfile.h>

DECL_BEGIN

#ifndef __KERNEL__
INTDEF ATTR_FDREAD(2) ATTR_FDWRITE(1) ATTR_INOUT_OPT(3) ssize_t NOTHROW_NCX(LIBCCALL libc_sendfile)(fd_t out_fd, fd_t in_fd, off_t *offset, size_t count);
INTDEF ATTR_FDREAD(2) ATTR_FDWRITE(1) ATTR_INOUT_OPT(3) ssize_t NOTHROW_NCX(LIBCCALL libc_sendfile64)(fd_t out_fd, fd_t in_fd, off64_t *offset, size_t count);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_SENDFILE_H */
