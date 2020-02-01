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
#ifndef _I386_KOS_BITS_MSGHDR_STRUCT64_H
#define _I386_KOS_BITS_MSGHDR_STRUCT64_H 1

#include <__stdinc.h>
#include <features.h>

#include <hybrid/__pointer.h>
#include <hybrid/host.h>
#include <hybrid/typecore.h>

#include <bits/types.h>

__DECL_BEGIN

#ifdef __x86_64__
#define msghdr64 msghdr
#define __OFFSET_MSGHDR_NAME       __OFFSET_MSGHDR64_NAME
#define __OFFSET_MSGHDR_NAMELEN    __OFFSET_MSGHDR64_NAMELEN
#define __OFFSET_MSGHDR_IOV        __OFFSET_MSGHDR64_IOV
#define __OFFSET_MSGHDR_IOVLEN     __OFFSET_MSGHDR64_IOVLEN
#define __OFFSET_MSGHDR_CONTROL    __OFFSET_MSGHDR64_CONTROL
#define __OFFSET_MSGHDR_CONTROLLEN __OFFSET_MSGHDR64_CONTROLLEN
#define __OFFSET_MSGHDR_FLAGS      __OFFSET_MSGHDR64_FLAGS
#define __SIZEOF_MSGHDR            __SIZEOF_MSGHDR64
#endif /* __x86_64__ */

#define __OFFSET_MSGHDR64_NAME       0
#define __OFFSET_MSGHDR64_NAMELEN    8
#define __OFFSET_MSGHDR64_IOV        16
#define __OFFSET_MSGHDR64_IOVLEN     24
#define __OFFSET_MSGHDR64_CONTROL    32
#define __OFFSET_MSGHDR64_CONTROLLEN 40
#define __OFFSET_MSGHDR64_FLAGS      48
#define __SIZEOF_MSGHDR64            56
#ifdef __CC__

#ifdef __x86_64__
struct iovec;
#else /* __x86_64__ */
struct iovec64;
#endif /* !__x86_64__ */
#ifdef __USE_KOS_KERNEL
struct sockaddr;
#ifdef __x86_64__
struct cmsghdr;
#else /* __x86_64__ */
struct cmsghdr64;
#endif /* !__x86_64__ */
#endif /* __USE_KOS_KERNEL */

/* Structure describing messages sent by `sendmsg' and received by `recvmsg'. */
struct msghdr64 /*[PREFIX(msg_)]*/ {
#ifdef __USE_KOS_KERNEL
	__HYBRID_PTR64(struct sockaddr) msg_name;      /* [TYPE(struct sockaddr *)] Address to send to/receive from. */
#else /* __USE_KOS_KERNEL */
	__HYBRID_PTR64(void)           msg_name;       /* [TYPE(struct sockaddr *)] Address to send to/receive from. */
#endif /* !__USE_KOS_KERNEL */
	__UINT32_TYPE__                msg_namelen;    /* Length of address data. */
	__UINT32_TYPE__              __msg_pad1;       /* ... */
#ifdef __x86_64__
	__HYBRID_PTR64(struct iovec)   msg_iov;        /* Vector of data to send/receive into. */
#else /* __x86_64__ */
	__HYBRID_PTR64(struct iovec64) msg_iov;        /* Vector of data to send/receive into. */
#endif /* !__x86_64__ */
	__UINT64_TYPE__                msg_iovlen;     /* Number of elements in the vector. */
#ifdef __USE_KOS_KERNEL
#ifdef __x86_64__
	__HYBRID_PTR64(struct cmsghdr) msg_control;    /* [TYPE(struct cmsghdr64 *)] Ancillary data (eg BSD filedesc passing). */
#else /* __x86_64__ */
	__HYBRID_PTR64(struct cmsghdr64) msg_control;  /* [TYPE(struct cmsghdr64 *)] Ancillary data (eg BSD filedesc passing). */
#endif /* !__x86_64__ */
#else /* __USE_KOS_KERNEL */
	__HYBRID_PTR64(void)           msg_control;    /* [TYPE(struct cmsghdr64 *)] Ancillary data (eg BSD filedesc passing). */
#endif /* !__USE_KOS_KERNEL */
	__UINT64_TYPE__                msg_controllen; /* Ancillary data buffer length. !! The type should be socklen_t but the definition of the kernel is incompatible with this. */
#ifdef __USE_KOS_KERNEL
	__UINT32_TYPE__                msg_flags;      /* Flags returned by recvmsg() */
#else /* __USE_KOS_KERNEL */
	__INT32_TYPE__                 msg_flags;      /* Flags returned by recvmsg() */
#endif /* !__USE_KOS_KERNEL */
	__UINT32_TYPE__              __msg_pad2;       /* ... */
};

#endif /* __CC__ */

__DECL_END

#endif /* !_I386_KOS_BITS_MSGHDR_STRUCT64_H */
