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
#ifndef _I386_KOS_BITS_OS_KOS_MMSGHDR32_H
#define _I386_KOS_BITS_OS_KOS_MMSGHDR32_H 1

#include <__stdinc.h>
#include <features.h>

#include <hybrid/host.h>
#include <hybrid/typecore.h>

#include <bits/os/kos/msghdr32.h>

__DECL_BEGIN

#if defined(__i386__) && !defined(__x86_64__)
#define __OFFSET_MMSGHDR_HDR __OFFSET_MMSGHDRX32_HDR
#define __OFFSET_MMSGHDR_LEN __OFFSET_MMSGHDRX32_LEN
#define __SIZEOF_MMSGHDR     __SIZEOF_MMSGHDRX32
#define __ALIGNOF_MMSGHDR    __ALIGNOF_MMSGHDRX32
#define __mmsghdrx32         mmsghdr
#endif /* __i386__ && !__x86_64__ */

#define __OFFSET_MMSGHDRX32_HDR  0
#define __OFFSET_MMSGHDRX32_LEN  28
#define __SIZEOF_MMSGHDRX32      32
#define __ALIGNOF_MMSGHDRX32     __ALIGNOF_INT32__

#ifdef __USE_KOS_KERNEL
#define mmsghdrx32 __mmsghdrx32
#endif /* !__USE_KOS_KERNEL */

#ifdef __CC__
/* For `recvmmsg' and `sendmmsg'. */
struct __mmsghdrx32 /*[NAME(mmsghdrx32)][PREFIX(msg_)]*/ {
	struct __msghdrx32 msg_hdr; /* Actual message header. */
	__UINT32_TYPE__    msg_len; /* Number of received or sent bytes for the entry. */
};
#endif /* __CC__ */

__DECL_END

#endif /* !_I386_KOS_BITS_OS_KOS_MMSGHDR32_H */
