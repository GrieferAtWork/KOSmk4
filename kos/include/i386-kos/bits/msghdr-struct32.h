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
#ifndef _I386_KOS_BITS_MSGHDR_STRUCT32_H
#define _I386_KOS_BITS_MSGHDR_STRUCT32_H 1

#include <__stdinc.h>
#include <features.h>

#include <hybrid/__pointer.h>
#include <hybrid/host.h>
#include <hybrid/typecore.h>

#include <bits/types.h>

__DECL_BEGIN

#if !defined(__x86_64__) && defined(__i386__)
#define msghdr32 msghdr
#define __OFFSET_MSGHDR_NAME       __OFFSET_MSGHDR32_NAME
#define __OFFSET_MSGHDR_NAMELEN    __OFFSET_MSGHDR32_NAMELEN
#define __OFFSET_MSGHDR_IOV        __OFFSET_MSGHDR32_IOV
#define __OFFSET_MSGHDR_IOVLEN     __OFFSET_MSGHDR32_IOVLEN
#define __OFFSET_MSGHDR_CONTROL    __OFFSET_MSGHDR32_CONTROL
#define __OFFSET_MSGHDR_CONTROLLEN __OFFSET_MSGHDR32_CONTROLLEN
#define __OFFSET_MSGHDR_FLAGS      __OFFSET_MSGHDR32_FLAGS
#define __SIZEOF_MSGHDR            __SIZEOF_MSGHDR32
#endif /* !__x86_64__ && __i386__ */

#define __OFFSET_MSGHDR32_NAME       0
#define __OFFSET_MSGHDR32_NAMELEN    4
#define __OFFSET_MSGHDR32_IOV        8
#define __OFFSET_MSGHDR32_IOVLEN     12
#define __OFFSET_MSGHDR32_CONTROL    16
#define __OFFSET_MSGHDR32_CONTROLLEN 20
#define __OFFSET_MSGHDR32_FLAGS      24
#define __SIZEOF_MSGHDR32            28
#ifdef __CC__

#if defined(__i386__) && !defined(__x86_64__)
struct iovec;
#else /* __i386__ && !__x86_64__ */
struct iovec32;
#endif /* !__i386__ || __x86_64__ */
#ifdef __USE_KOS_KERNEL
struct sockaddr;
#if defined(__i386__) && !defined(__x86_64__)
struct cmsghdr;
#else /* __i386__ && !__x86_64__ */
struct cmsghdr32;
#endif /* !__i386__ || __x86_64__ */
#endif /* __USE_KOS_KERNEL */


/* Structure describing messages sent by `sendmsg' and received by `recvmsg'. */
struct msghdr32 /*[PREFIX(msg_)]*/ { /* TODO: Rename to msghdrx32 */
#ifdef __USE_KOS_KERNEL
	__HYBRID_PTR32(struct sockaddr) msg_name;      /* [out][0..msg_namelen] Address to send to/receive from. */
#else /* __USE_KOS_KERNEL */
	__HYBRID_PTR32(void)           msg_name;       /* [out][0..msg_namelen][TYPE(struct sockaddr *)] Address to send to/receive from. */
#endif /* !__USE_KOS_KERNEL */
	__UINT32_TYPE__                msg_namelen;    /* [in|out][valid_if(msg_name != NULL)] Length of address data. */
#if defined(__i386__) && !defined(__x86_64__)
	__HYBRID_PTR32(struct iovec)   msg_iov;        /* [0..msg_iovlen] Vector of data to send/receive into. */
#else /* __i386__ && !__x86_64__ */
	__HYBRID_PTR32(struct iovec32) msg_iov;        /* [0..msg_iovlen] Vector of data to send/receive into. */
#endif /* !__i386__ || __x86_64__ */
	__UINT32_TYPE__                msg_iovlen;     /* Number of elements in the vector. */
#ifdef __USE_KOS_KERNEL
#if defined(__i386__) && !defined(__x86_64__)
	__HYBRID_PTR32(struct cmsghdr) msg_control;    /* [0..msg_controllen] Ancillary data (eg BSD filedesc passing). */
#else /* __i386__ && !__x86_64__ */
	__HYBRID_PTR32(struct cmsghdr32) msg_control;  /* [0..msg_controllen] Ancillary data (eg BSD filedesc passing). */
#endif /* !__i386__ || __x86_64__ */
#else /* __USE_KOS_KERNEL */
	__HYBRID_PTR32(void)           msg_control;    /* [0..msg_controllen][TYPE(struct cmsghdr32 *)] Ancillary data (eg BSD filedesc passing). */
#endif /* !__USE_KOS_KERNEL */
	__UINT32_TYPE__                msg_controllen; /* [in|out][valid_if(msg_control != NULL)] Ancillary data buffer length.
	                                                * !! The type should be socklen_t but the definition of the
	                                                *    kernel is incompatible with this. */
#ifdef __USE_KOS_KERNEL
	__UINT32_TYPE__                msg_flags;      /* [out] Flags returned by recvmsg() (set of `MSG_EOR | MSG_TRUNC | MSG_CTRUNC | MSG_OOB | MSG_ERRQUEUE') */
#else /* __USE_KOS_KERNEL */
	__INT32_TYPE__                 msg_flags;      /* [out] Flags returned by recvmsg() (set of `MSG_EOR | MSG_TRUNC | MSG_CTRUNC | MSG_OOB | MSG_ERRQUEUE') */
#endif /* !__USE_KOS_KERNEL */
};

#endif /* __CC__ */

__DECL_END

#endif /* !_I386_KOS_BITS_MSGHDR_STRUCT32_H */
