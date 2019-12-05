/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _BITS_MSQ_H
#define _BITS_MSQ_H 1

#include <__stdinc.h>
#include <features.h>

#include <hybrid/typecore.h>

#include <bits/types.h>

/* Documentation taken from /usr/include/i386-linux/gnu/bits/msq.h */
/* Copyright (C) 1995-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

__DECL_BEGIN

/* Define options for message queue functions.  */
#define MSG_NOERROR 010000 /* no error if message is too big */
#ifdef __USE_GNU
#define MSG_EXCEPT  020000 /* recv any msg except of specified type */
#define MSG_COPY    040000 /* copy (not remove) all queue messages */
#endif /* __USE_GNU */

/* Types used in the structure definition.  */
#ifdef __CC__
typedef __syscall_ulong_t msgqnum_t;
typedef __syscall_ulong_t msglen_t;
#endif /* __CC__ */

/* Structure of record for one message inside the kernel.
 * The type `struct msg' is opaque.  */
/*[[[struct]]]*/
#ifdef __CC__
struct msqid_ds {
	struct ipc_perm msg_perm;   /* structure describing operation permission */
	__TM_TYPE(time) msg_stime;  /* time of last msgsnd command */
#if __TM_SIZEOF(TIME) > __SIZEOF_SYSCALL_LONG_T__
#if __TM_SIZEOF(TIME) != __SIZEOF_SYSCALL_LONG_T__*2
#error "Unsupported configuration"
#endif /* __TM_SIZEOF(TIME) != __SIZEOF_SYSCALL_LONG_T__*2 */
#else /* __TM_SIZEOF(TIME) > __SIZEOF_SYSCALL_LONG_T__ */
	__syscall_ulong_t __glibc_reserved1;
#endif /* __TM_SIZEOF(TIME) <= __SIZEOF_SYSCALL_LONG_T__ */
	__TM_TYPE(time) msg_rtime;  /* time of last msgrcv command */
#if __TM_SIZEOF(TIME) <= __SIZEOF_SYSCALL_LONG_T__
	__syscall_ulong_t __glibc_reserved2;
#endif /* __TM_SIZEOF(TIME) <= __SIZEOF_SYSCALL_LONG_T__ */
	__TM_TYPE(time) msg_ctime;  /* time of last change */
#if __TM_SIZEOF(TIME) <= __SIZEOF_SYSCALL_LONG_T__
	__syscall_ulong_t __glibc_reserved3;
#endif /* __TM_SIZEOF(TIME) <= __SIZEOF_SYSCALL_LONG_T__ */
#ifdef __USE_MISC
#ifdef __COMPILER_HAVE_TRANSPARENT_UNION
	union {
		__syscall_ulong_t   msg_cbytes; /* current number of bytes on queue */
		__syscall_ulong_t __msg_cbytes; /* current number of bytes on queue */
	};
#else /* __COMPILER_HAVE_TRANSPARENT_UNION */
	__syscall_ulong_t   msg_cbytes;     /* current number of bytes on queue */
#define __msg_cbytes    msg_cbytes
#endif /* !__COMPILER_HAVE_TRANSPARENT_UNION */
#else /* __USE_MISC */
	__syscall_ulong_t __msg_cbytes;     /* current number of bytes on queue */
#endif /* !__USE_MISC */
	msgqnum_t           msg_qnum;       /* number of messages currently on queue */
	msglen_t            msg_qbytes;     /* max number of bytes allowed on queue */
	__pid_t             msg_lspid;      /* pid of last msgsnd() */
	__pid_t             msg_lrpid;      /* pid of last msgrcv() */
	__syscall_ulong_t __glibc_reserved4;
	__syscall_ulong_t __glibc_reserved5;
};
#endif /* __CC__ */
/*[[[end]]]*/


#ifdef __USE_MISC

/* ipcs ctl commands */
#define MSG_STAT 11
#define MSG_INFO 12

/* buffer for msgctl calls IPC_INFO, MSG_INFO */
/*[[[struct]]]*/
#ifdef __CC__
struct msginfo {
	__INT32_TYPE__  msgpool;
	__INT32_TYPE__  msgmap;
	__INT32_TYPE__  msgmax;
	__INT32_TYPE__  msgmnb;
	__INT32_TYPE__  msgmni;
	__INT32_TYPE__  msgssz;
	__INT32_TYPE__  msgtql;
	__UINT16_TYPE__ msgseg;
};
#endif /* __CC__ */
/*[[[end]]]*/

#endif /* __USE_MISC */


__DECL_END

#endif /* _BITS_MSQ_H */
