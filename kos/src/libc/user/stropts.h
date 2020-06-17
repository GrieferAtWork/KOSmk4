/* HASH CRC-32:0xe2255285 */
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
#ifndef GUARD_LIBC_USER_STROPTS_H
#define GUARD_LIBC_USER_STROPTS_H 1

#include "../api.h"
#include "../auto/stropts.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <stropts.h>

DECL_BEGIN

#ifndef __KERNEL__
/* Test whether FILDES is associated with a STREAM-based file */
INTDEF int NOTHROW(LIBCCALL libc_isastream)(fd_t fildes);
/* Receive next message from a STREAMS file */
INTDEF int NOTHROW_RPC(LIBCCALL libc_getmsg)(fd_t fildes, struct strbuf *__restrict ctlptr, struct strbuf *__restrict dataptr, int *__restrict flagsp);
/* Receive next message from a STREAMS file, with *FLAGSP allowing to control which message. */
INTDEF int NOTHROW_RPC(LIBCCALL libc_getpmsg)(fd_t fildes, struct strbuf *__restrict ctlptr, struct strbuf *__restrict dataptr, int *__restrict bandp, int *__restrict flagsp);
/* Send a message on a STREAM */
INTDEF int NOTHROW_RPC(LIBCCALL libc_putmsg)(fd_t fildes, struct strbuf const *ctlptr, struct strbuf const *dataptr, int flags);
/* Send a message on a STREAM to the BAND */
INTDEF int NOTHROW_RPC(LIBCCALL libc_putpmsg)(fd_t fildes, struct strbuf const *ctlptr, struct strbuf const *dataptr, int band, int flags);
/* Attach a STREAMS-based file descriptor FILDES to a file PATH in the file system name space */
INTDEF NONNULL((2)) int NOTHROW_RPC_KOS(LIBCCALL libc_fattach)(fd_t fildes, char const *__restrict path);
/* Detach a name PATH from a STREAMS-based file descriptor */
INTDEF NONNULL((1)) int NOTHROW_RPC_KOS(LIBCCALL libc_fdetach)(char const *__restrict path);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_STROPTS_H */
