/* HASH CRC-32:0x47277f76 */
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_AUTO_SYS_SOCKET_C
#define GUARD_LIBC_AUTO_SYS_SOCKET_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../user/sys.socket.h"

DECL_BEGIN

#ifndef __KERNEL__
#include <bits/types.h>
INTERN ATTR_SECTION(".text.crt.net.socket") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) struct cmsghdr *
NOTHROW_NCX(LIBCCALL libc___cmsg_nxthdr)(struct msghdr *mhdr,
                                         struct cmsghdr *cmsg) {
	byte_t *ctrl_end;
	/* If the current header is incomplete, then there is no next header.
	 * XXX: This should really never happen, since `CMSG_FIRSTHDR()' already
	 *      checks  this,  however  linux   also  does  this  check,   so... */
	if unlikely((size_t)cmsg->cmsg_len < __OFFSET_CMSGHDR_DATA)
		goto eof;
	/* Walk to the next header */
	cmsg = (struct cmsghdr *)((byte_t *)cmsg + ((cmsg->cmsg_len + __ALIGNOF_CMSGHDR - 1) & ~(__ALIGNOF_CMSGHDR - 1)));
	/* Verify that the next header is in-bounds. */
	ctrl_end = (byte_t *)mhdr->msg_control + mhdr->msg_controllen;
	if unlikely((byte_t *)cmsg + __OFFSET_CMSGHDR_DATA > ctrl_end)
		goto eof;
	if ((byte_t *)cmsg + ((cmsg->cmsg_len + __ALIGNOF_CMSGHDR - 1) & ~(__ALIGNOF_CMSGHDR - 1)) > ctrl_end)
		goto eof;
	__builtin_assume(cmsg != NULL);
	return cmsg;
eof:
	return NULL;
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(__cmsg_nxthdr, libc___cmsg_nxthdr);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_SYS_SOCKET_C */
