/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _BITS_OS_KOS_MSGHDR_H
#define _BITS_OS_KOS_MSGHDR_H 1

#include <__stdinc.h>
#include <features.h>

#include <hybrid/typecore.h>

#include <bits/types.h>

__DECL_BEGIN


#define __OFFSET_MSGHDR_NAME       0
#define __OFFSET_MSGHDR_NAMELEN    __SIZEOF_POINTER__
#if __SIZEOF_SOCKLEN_T__ > __SIZEOF_POINTER__
#define __OFFSET_MSGHDR_IOV        (__SIZEOF_POINTER__ + __SIZEOF_SOCKLEN_T__)
#else /* __SIZEOF_SOCKLEN_T__ > __SIZEOF_POINTER__ */
#define __OFFSET_MSGHDR_IOV        (__SIZEOF_POINTER__ * 2)
#endif /* __SIZEOF_SOCKLEN_T__ <= __SIZEOF_POINTER__ */
#define __OFFSET_MSGHDR_IOVLEN     (__OFFSET_MSGHDR_IOV + __SIZEOF_POINTER__)
#define __OFFSET_MSGHDR_CONTROL    (__OFFSET_MSGHDR_IOV + __SIZEOF_POINTER__ + __SIZEOF_SIZE_T__)
#define __OFFSET_MSGHDR_CONTROLLEN (__OFFSET_MSGHDR_IOV + __SIZEOF_POINTER__ * 2 + __SIZEOF_SIZE_T__)
#define __OFFSET_MSGHDR_FLAGS      (__OFFSET_MSGHDR_IOV + __SIZEOF_POINTER__ * 2 + __SIZEOF_SIZE_T__ * 2)
#define __SIZEOF_MSGHDR            (__OFFSET_MSGHDR_IOV + __SIZEOF_POINTER__ * 3 + __SIZEOF_SIZE_T__ * 2)
#define __ALIGNOF_MSGHDR           __SIZEOF_POINTER__

#ifdef __CC__

/* Structure describing messages sent by `sendmsg' and received by `recvmsg'. */
struct iovec;
#ifdef __USE_KOS_ALTERATIONS
struct sockaddr;
struct cmsghdr;
#endif /* __USE_KOS_ALTERATIONS */

struct msghdr /*[PREFIX(msg_)]*/ {
#ifdef __USE_KOS_ALTERATIONS
	struct sockaddr *msg_name;      /* [out][0..msg_namelen] Address to send to/receive from. */
#else /* __USE_KOS_ALTERATIONS */
	void           *msg_name;       /* [out][0..msg_namelen][TYPE(struct sockaddr *)] Address to send to/receive from. */
#endif /* !__USE_KOS_ALTERATIONS */
	__socklen_t     msg_namelen;    /* [in|out][valid_if(msg_name != NULL)] Length of address data. */
#if __SIZEOF_POINTER__ > __SIZEOF_SOCKLEN_T__
	__byte_t      __msg_pad1[__SIZEOF_POINTER__ - __SIZEOF_SOCKLEN_T__];
#endif /* __SIZEOF_POINTER__ > __SIZEOF_SOCKLEN_T__ */
	struct iovec   *msg_iov;        /* [0..msg_iovlen] Vector of data to send/receive into. */
	__size_t        msg_iovlen;     /* Number of elements in the vector. */
#ifdef __USE_KOS_ALTERATIONS
	struct cmsghdr *msg_control;    /* [0..msg_controllen] Ancillary data (eg BSD filedesc passing). */
#else /* __USE_KOS_ALTERATIONS */
	void           *msg_control;    /* [0..msg_controllen][TYPE(struct cmsghdr32 *)] Ancillary data (eg BSD filedesc passing). */
#endif /* !__USE_KOS_ALTERATIONS */
	__size_t        msg_controllen; /* [in|out][valid_if(msg_control != NULL)] Ancillary data buffer length.
	                                 * !! The type should be socklen_t but the definition of the
	                                 *    kernel is incompatible with this. */
#ifdef __USE_KOS_ALTERATIONS
	__UINT32_TYPE__ msg_flags;      /* [out] Flags returned by recvmsg() (set of `MSG_EOR | MSG_TRUNC | MSG_CTRUNC | MSG_OOB | MSG_ERRQUEUE') */
#else /* __USE_KOS_ALTERATIONS */
	__INT32_TYPE__  msg_flags;      /* [out] Flags returned by recvmsg() (set of `MSG_EOR | MSG_TRUNC | MSG_CTRUNC | MSG_OOB | MSG_ERRQUEUE') */
#endif /* !__USE_KOS_ALTERATIONS */
#if __SIZEOF_POINTER__ > 4
	__INT32_TYPE__ __msg_pad2;      /* ... */
#endif /* __SIZEOF_POINTER__ > 4 */
};

#endif /* __CC__ */

__DECL_END

#endif /* !_BITS_OS_KOS_MSGHDR_H */
