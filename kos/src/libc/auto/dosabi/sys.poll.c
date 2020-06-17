/* HASH CRC-32:0x8d2c9cfd */
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
#ifndef GUARD_LIBC_AUTO_DOSABI_SYS_POLL_C
#define GUARD_LIBC_AUTO_DOSABI_SYS_POLL_C 1

#include "../../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../../user/sys.poll.h"

DECL_BEGIN

/* @param timeout: Timeout in milliseconds (or negative for infinity) */
INTERN ATTR_SECTION(".text.crt.dos.io.poll") NONNULL((1)) int
NOTHROW_RPC(LIBDCALL libd_poll)(struct pollfd *fds,
                                nfds_t nfds,
                                int timeout) {
	return libc_poll(fds, nfds, timeout);
}
INTERN ATTR_SECTION(".text.crt.dos.io.poll") NONNULL((1)) int
NOTHROW_RPC(LIBDCALL libd_ppoll)(struct pollfd *fds,
                                 nfds_t nfds,
                                 struct timespec const *timeout,
                                 sigset_t const *ss) {
	return libc_ppoll(fds, nfds, timeout, ss);
}
INTERN ATTR_SECTION(".text.crt.dos.io.poll") NONNULL((1)) int
NOTHROW_RPC(LIBDCALL libd_ppoll64)(struct pollfd *fds,
                                   nfds_t nfds,
                                   struct timespec64 const *timeout,
                                   sigset_t const *ss) {
	return libc_ppoll64(fds, nfds, timeout, ss);
}

DECL_END

DEFINE_PUBLIC_ALIAS(DOS$__poll, libd_poll);
DEFINE_PUBLIC_ALIAS(DOS$poll, libd_poll);
DEFINE_PUBLIC_ALIAS(DOS$ppoll, libd_ppoll);
DEFINE_PUBLIC_ALIAS(DOS$ppoll64, libd_ppoll64);

#endif /* !GUARD_LIBC_AUTO_DOSABI_SYS_POLL_C */
