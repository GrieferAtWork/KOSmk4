/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _BITS_OS_KOS_MMSGHDR_H
#define _BITS_OS_KOS_MMSGHDR_H 1

#include <__stdinc.h>

#include <hybrid/typecore.h>

#include <bits/os/msghdr.h>

__DECL_BEGIN

#define __OFFSET_MMSGHDR_HDR  0
#define __OFFSET_MMSGHDR_LEN  __SIZEOF_MSGHDR
#if __ALIGNOF_MSGHDR > 4
#define __SIZEOF_MMSGHDR      (__SIZEOF_MSGHDR + __ALIGNOF_MSGHDR)
#else /* __ALIGNOF_MSGHDR > 4 */
#define __SIZEOF_MMSGHDR      (__SIZEOF_MSGHDR + 4)
#endif /* __ALIGNOF_MSGHDR <= 4 */
#define __ALIGNOF_MMSGHDR     __ALIGNOF_MSGHDR

#ifdef __CC__
/* For `recvmmsg' and `sendmmsg'. */
struct mmsghdr /*[PREFIX(msg_)]*/ {
	struct msghdr   msg_hdr; /* Actual message header. */
	__UINT32_TYPE__ msg_len; /* Number of received or sent bytes for the entry. */
#if __ALIGNOF_MSGHDR > 4
	__BYTE_TYPE__ __msg_pad[__ALIGNOF_MSGHDR - 4]; /* ... */
#endif /* __ALIGNOF_MSGHDR > 4 */
};
#endif /* __CC__ */

__DECL_END

#endif /* !_BITS_OS_KOS_MMSGHDR_H */
