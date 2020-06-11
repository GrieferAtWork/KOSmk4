/* HASH CRC-32:0xe66cb7bd */
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
#ifndef GUARD_LIBC_USER_SYS_SENDFILE_H
#define GUARD_LIBC_USER_SYS_SENDFILE_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <sys/sendfile.h>

DECL_BEGIN

#ifndef __KERNEL__
/* Send up to COUNT bytes from file associated with IN_FD starting at *OFFSET
 * to descriptor OUT_FD. Set *OFFSET to the IN_FD's file position following the
 * read bytes. If OFFSET is a null pointer, use the normal file position instead.
 * Return the number of written bytes, or -1 in case of error */
INTDEF ssize_t NOTHROW_NCX(LIBCCALL libc_sendfile)(fd_t out_fd, fd_t in_fd, off_t *offset, size_t count);
/* Send up to COUNT bytes from file associated with IN_FD starting at *OFFSET
 * to descriptor OUT_FD. Set *OFFSET to the IN_FD's file position following the
 * read bytes. If OFFSET is a null pointer, use the normal file position instead.
 * Return the number of written bytes, or -1 in case of error */
INTDEF ssize_t NOTHROW_NCX(LIBCCALL libc_sendfile64)(fd_t out_fd, fd_t in_fd, off64_t *offset, size_t count);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_SENDFILE_H */
