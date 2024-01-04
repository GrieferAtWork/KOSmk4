/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _I386_KOS_BITS_OS_KOS_MMSGHDR64_H
#define _I386_KOS_BITS_OS_KOS_MMSGHDR64_H 1

#include <__stdinc.h>
#include <features.h>

#include <hybrid/host.h>
#include <hybrid/typecore.h>

#include <bits/os/kos/msghdr64.h>

__DECL_BEGIN

#ifdef __x86_64__
#define __OFFSET_MMSGHDR_HDR __OFFSET_MMSGHDRX64_HDR
#define __OFFSET_MMSGHDR_LEN __OFFSET_MMSGHDRX64_LEN
#define __SIZEOF_MMSGHDR     __SIZEOF_MMSGHDRX64
#define __ALIGNOF_MMSGHDR    __ALIGNOF_MMSGHDRX64
#define __mmsghdrx64         mmsghdr
#endif /* __x86_64__ */

#define __OFFSET_MMSGHDRX64_HDR  0
#define __OFFSET_MMSGHDRX64_LEN  56
#if __ALIGNOF_INT64__ > 4
#define __SIZEOF_MMSGHDRX64      64
#else /* __ALIGNOF_INT64__ > 4 */
#define __SIZEOF_MMSGHDRX64      60
#endif /* __ALIGNOF_INT64__ <= 4 */
#define __ALIGNOF_MMSGHDRX64     __ALIGNOF_INT64__

#ifdef __USE_KOS_KERNEL
#define mmsghdrx64 __mmsghdrx64
#endif /* !__USE_KOS_KERNEL */

#ifdef __CC__
/* For `recvmmsg' and `sendmmsg'. */
struct __mmsghdrx64 /*[NAME(mmsghdrx64)][PREFIX(msg_)]*/ {
	struct __msghdrx64 msg_hdr; /* Actual message header. */
	__UINT32_TYPE__    msg_len; /* Number of received or sent bytes for the entry. */
#if __ALIGNOF_INT64__ > 4
	__BYTE_TYPE__    __msg_pad[__ALIGNOF_INT64__ - 4]; /* ... */
#endif /* __ALIGNOF_INT64__ > 4 */
};
#endif /* __CC__ */

__DECL_END

#endif /* !_I386_KOS_BITS_OS_KOS_MMSGHDR64_H */
