/* HASH CRC-32:0x792ad3c6 */
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
#ifndef GUARD_LIBC_USER_SYS_RANDOM_H
#define GUARD_LIBC_USER_SYS_RANDOM_H 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include <sys/random.h>

DECL_BEGIN

/* Ask the kernel for up to `NUM_BYTES' bytes of random data, which
 * should then be written to `BUFFER'.
 * @param: FLAGS: Set of `GRND_NONBLOCK | GRND_RANDOM'
 * @return: * :   The actual number of returned random bytes.
 *                If `GRND_NONBLOCK' was passed, or if the calling thread
 *                was interrupted, this may be less than `NUM_BYTES'
 * @return: -1:   Error (s.a. `errno') Note that in the event of the
 *                calling thread being interrupted, EINTR is only set
 *                if no random data had already been retrieved from
 *                the kernel's random data sink. */
INTDEF WUNUSED NONNULL((1)) ssize_t NOTHROW_NCX(LIBCCALL libc_getrandom)(void *buf, size_t num_bytes, unsigned int flags);
/* Similar to `getrandom(BUF, NUM_BYTES, GRND_RANDOM)', however
 * the case where the calling thread is interrupted, causing an
 * less than `NUM_BYTES' of data to be read is handled by reading
 * more random data until all of `NUM_BYTES' have been read.
 * Note that portable applications should be aware that certain
 * implementations of this function disallow calls where `NUM_BYTES'
 * is larger than `256'
 * Also note that any other than `EFAULT' and `ENOSYS' are translated into `EIO'
 * @return:  0: Success
 * @return: -1: Error (see `errno') */
INTDEF WUNUSED NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_getentropy)(void *buf, size_t num_bytes);

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_RANDOM_H */
