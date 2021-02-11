/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _KOS_BITS_UAIO_H
#define _KOS_BITS_UAIO_H 1

#include <__stdinc.h>

#include <bits/types.h>

__DECL_BEGIN

#ifdef __CC__

#ifndef __lfutex_t_defined
#define __lfutex_t_defined 1
typedef __uintptr_t lfutex_t;
#endif /* !__lfutex_t_defined */

typedef __uintptr_t uaio_id_t;

struct iovec;
struct sockaddr;

struct uaio {
	struct uaio           *ua_next;     /* [0..1][in] Next AIO operation to-be performed. */
	__fd_t                 ua_fd;       /* [in] The file descriptor on which to perform AIO */
	__uint16_t             ua_op;       /* [in] The operation to-be performed (one of `UAIO_OP_*') */
	__uint16_t             ua_flag;     /* [in] AIO operation flags (set of `UAIO_F_*'). */
	uaio_id_t              ua_id;       /* [out] ID assigned by the kernel for this AIO operation.
	                                     * This ID can  be used to  query the  completion-progress
	                                     * of this AIO operation (s.a. `HOP_UAIO_PROGRESS') */
	__size_t               ua_result;   /* [out] AIO success return value (written just before
	                                     *       the status is set to `UAIO_STATUS_SUCCESS'). */
	__uintptr_t            ua_status;   /* [in|out] The current status (must be pre-initialize to `UAIO_STATUS_PENDING')
	                                     * NOTE: In order to  prevent infinite recursion  of uaio objects  pointing
	                                     *       back on themselves, the underlying UAIO object will stop execution
	                                     *       and indicate UAIO completion (read(&c, 1) returns c=0) when a UAIO
	                                     *       descriptor is encountered that has `ua_status' field with a  value
	                                     *       different from  `UAIO_STATUS_PENDING',  `UAIO_STATUS_RUNNING'  and
	                                     *       `UAIO_STATUS_CANCEL' (only these  3 values are  accepted as  valid
	                                     *       status values for which UAIO can be initiated)
	                                     * -> Since the kernel  _always_ writes  a value  that differs  from these  3
	                                     *    values when the operation completes on  its own, a UAIO structure  that
	                                     *    points  back to itself will automatically terminate once it reaches the
	                                     *    first  entry that had already been completed, thus making it impossible
	                                     *    to have the kernel keep on executing UAIO operations without eventually
	                                     *    finishing all enqueued operations. */
	lfutex_t              *ua_changed;  /* [0..1][in] A futex that is broadcast when `ua_status' is changed,
	                                     *            though  do note the  special case for `UAIO_F_RUNSTAT'
	                                     *            and `UAIO_STATUS_RUNNING'.
	                                     * Set to `NULL' to disable futex notification for this operation. */
	struct exception_data *ua_error;    /* [0..1][in] Exception  data  filled  in  if  something  goes  wrong.
	                                     * The pointed-to memory region is written before `UAIO_STATUS_FAILED'
	                                     * is indicated. */
	union {

		struct {
			void     *ur_buf;    /* [0..ur_buflen][in] Target buffer. */
			__size_t  ur_buflen; /* [in] # of bytes in `ur_buf'. */
			__pos64_t ur_pos;    /* Absolute file offset from where to read. */
		} ua_read; /* UAIO_OP_READ */

		struct {
			struct iovec const *ur_iov;    /* [0..ur_iovlen][in] Target IO vector. */
			__size_t            ur_iovlen; /* [in] # of entires within the `ur_iov' vector. */
			__pos64_t           ur_pos;    /* Absolute file offset from where to read. */
		} ua_readv; /* UAIO_OP_READV */

		struct {
			void const *uw_buf;    /* [0..ur_buflen][in] Source buffer. */
			__size_t    uw_buflen; /* [in] # of bytes in `ur_buf'. */
			__pos64_t   uw_pos;    /* Absolute file offset from where to read. */
		} ua_write; /* UAIO_OP_WRITE */

		struct {
			struct iovec const *uw_iov;    /* [0..ur_iovlen][in] Source IO vector. */
			__size_t            uw_iovlen; /* [in] # of entires within the `ur_iov' vector. */
			__pos64_t           uw_pos;    /* Absolute file offset from where to read. */
		} ua_writev; /* UAIO_OP_WRITEV */

		struct {
			struct sockaddr const *uc_addr;    /* [1..uc_addrlen][in] Connect target socket address */
			__socklen_t            uc_addrlen; /* [in] Length of `uc_addr' */
		} ua_connect; /* UAIO_OP_CONNECT */

		struct {
			void               *ur_buf;            /* [out][0..ur_buflen][in] Target buffer. */
			__size_t            ur_buflen;         /* [in] Length of `ur_buf' in bytes. */
			struct cmsghdr     *ur_msg_control;    /* [out][0..ur_msg_controllen][in] s.a. `msghdr::msg_control' */
			__size_t            ur_msg_controllen; /* [in|out] s.a. `msghdr::msg_controllen' */
			struct sockaddr    *ur_msg_name;       /* [out][0..ur_addrlen][in] s.a. `msghdr::msg_name' */
			__socklen_t         ur_msg_namelen;    /* [in] s.a. `msghdr::msg_namelen' */
			__uint32_t          ur_msg_flags;      /* [in]  Message flags (set of `MSG_ERRQUEUE | MSG_OOB | MSG_PEEK | MSG_TRUNC | MSG_WAITALL').
			                                        * [out] Receive status (set of `MSG_EOR | MSG_TRUNC | MSG_CTRUNC | MSG_OOB | MSG_ERRQUEUE') */
		} ua_recv; /* UAIO_OP_RECV */

		struct {
			struct iovec const *ur_iov;            /* [out][0..ur_iovlen][in] Target IO vector. */
			__size_t            ur_iovlen;         /* [in] # of entires within the `ur_iov' vector. */
			struct cmsghdr     *ur_msg_control;    /* [out][0..ur_msg_controllen][in] s.a. `msghdr::msg_control' */
			__size_t            ur_msg_controllen; /* [in|out] s.a. `msghdr::msg_controllen' */
			struct sockaddr    *ur_msg_name;       /* [out][0..ur_addrlen][in] s.a. `msghdr::msg_name' */
			__socklen_t         ur_msg_namelen;    /* [in] s.a. `msghdr::msg_namelen' */
			__uint32_t          ur_msg_flags;      /* [in]  Message flags (set of `MSG_ERRQUEUE | MSG_OOB | MSG_PEEK | MSG_TRUNC | MSG_WAITALL').
			                                        * [out] Receive status (set of `MSG_EOR | MSG_TRUNC | MSG_CTRUNC | MSG_OOB | MSG_ERRQUEUE') */
		} ua_recvv; /* UAIO_OP_RECVV */

		struct {
			void const            *ur_buf;            /* [in][0..ur_buflen][in] Target buffer. */
			__size_t               ur_buflen;         /* [in] Length of `ur_buf' in bytes. */
			struct cmsghdr const  *ur_msg_control;    /* [in][0..ur_msg_controllen][in] s.a. `msghdr::msg_control' */
			__size_t               ur_msg_controllen; /* [in|out] s.a. `msghdr::msg_controllen' */
			struct sockaddr const *ur_msg_name;       /* [in][0..ur_addrlen][in] s.a. `msghdr::msg_name' */
			__socklen_t            ur_msg_namelen;    /* [in] s.a. `msghdr::msg_namelen' */
			__uint32_t             ur_msg_flags;      /* [in] Message flags (set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_EOR | MSG_MORE | MSG_OOB').
			                                           * NOTE: `MSG_NOSIGNAL' is always implied; i.e. `SIGPIPE' is never raised! */
		} ua_send; /* UAIO_OP_SEND */

		struct {
			struct iovec const    *ur_iov;            /* [in][0..ur_iovlen][in] Target IO vector. */
			__size_t               ur_iovlen;         /* [in] # of entires within the `ur_iov' vector. */
			struct cmsghdr const  *ur_msg_control;    /* [in][0..ur_msg_controllen][in] s.a. `msghdr::msg_control' */
			__size_t               ur_msg_controllen; /* [in|out] s.a. `msghdr::msg_controllen' */
			struct sockaddr const *ur_msg_name;       /* [in][0..ur_addrlen][in] s.a. `msghdr::msg_name' */
			__socklen_t            ur_msg_namelen;    /* [in] s.a. `msghdr::msg_namelen' */
			__uint32_t             ur_msg_flags;      /* [in] Message flags (set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_EOR | MSG_MORE | MSG_OOB').
			                                           * NOTE: `MSG_NOSIGNAL' is always implied; i.e. `SIGPIPE' is never raised! */
		} ua_sendv; /* UAIO_OP_SENDV */

	} ua_args; /* AIO operation arguments. */
};

#endif /* __CC__ */

__DECL_END

#endif /* !_KOS_BITS_UAIO_H */
