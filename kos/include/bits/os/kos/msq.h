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
/*!replace_with_include <bits/os/msq.h>*/
#ifndef _BITS_OS_KOS_MSQ_H
#define _BITS_OS_KOS_MSQ_H 1

#include <__stdinc.h>
#include <features.h> /* __USE_MISC */

#include <bits/os/kos/ipc.h>
#include <bits/types.h>

__DECL_BEGIN

/* Types used in the structure definition.  */
#ifdef __CC__
typedef __syscall_ulong_t msgqnum_t;
typedef __syscall_ulong_t msglen_t;
#endif /* __CC__ */

/*[[[struct]]]*/
#ifdef __CC__
struct msqid_ds {
	struct ipc_perm msg_perm;   /* ??? */
	__time_t        msg_stime;  /* ??? */
#if __SIZEOF_TIME_T__ > __SIZEOF_SYSCALL_LONG_T__
#if __SIZEOF_TIME_T__ != __SIZEOF_SYSCALL_LONG_T__ * 2
#error "Unsupported configuration"
#endif /* __SIZEOF_TIME_T__ != __SIZEOF_SYSCALL_LONG_T__ * 2 */
#else /* __SIZEOF_TIME_T__ > __SIZEOF_SYSCALL_LONG_T__ */
	__syscall_ulong_t __glibc_reserved1;
#endif /* __SIZEOF_TIME_T__ <= __SIZEOF_SYSCALL_LONG_T__ */
	__time_t        msg_rtime;  /* ??? */
#if __SIZEOF_TIME_T__ <= __SIZEOF_SYSCALL_LONG_T__
	__syscall_ulong_t __glibc_reserved2;
#endif /* __SIZEOF_TIME_T__ <= __SIZEOF_SYSCALL_LONG_T__ */
	__time_t        msg_ctime;  /* ??? */
#if __SIZEOF_TIME_T__ <= __SIZEOF_SYSCALL_LONG_T__
	__syscall_ulong_t __glibc_reserved3;
#endif /* __SIZEOF_TIME_T__ <= __SIZEOF_SYSCALL_LONG_T__ */
#ifdef __USE_MISC
#ifdef __COMPILER_HAVE_TRANSPARENT_UNION
	union {
		__syscall_ulong_t   msg_cbytes; /* ??? */
		__syscall_ulong_t __msg_cbytes; /* ??? */
	};
#else /* __COMPILER_HAVE_TRANSPARENT_UNION */
	__syscall_ulong_t   msg_cbytes;     /* ??? */
#define __msg_cbytes    msg_cbytes
#endif /* !__COMPILER_HAVE_TRANSPARENT_UNION */
#else /* __USE_MISC */
	__syscall_ulong_t __msg_cbytes;     /* ??? */
#endif /* !__USE_MISC */
	msgqnum_t           msg_qnum;       /* ??? */
	msglen_t            msg_qbytes;     /* ??? */
	__pid_t             msg_lspid;      /* ??? */
	__pid_t             msg_lrpid;      /* ??? */
	__syscall_ulong_t __glibc_reserved4;
	__syscall_ulong_t __glibc_reserved5;
};
#endif /* __CC__ */
/*[[[end]]]*/


#ifdef __USE_MISC
/* Argument for `msgctl()' with IPC_INFO, MSG_INFO */
/*[[[struct]]]*/
#ifdef __CC__
struct msginfo {
	__INT32_TYPE__  msgpool; /* ??? */
	__INT32_TYPE__  msgmap;  /* ??? */
	__INT32_TYPE__  msgmax;  /* ??? */
	__INT32_TYPE__  msgmnb;  /* ??? */
	__INT32_TYPE__  msgmni;  /* ??? */
	__INT32_TYPE__  msgssz;  /* ??? */
	__INT32_TYPE__  msgtql;  /* ??? */
	__UINT16_TYPE__ msgseg;  /* ??? */
};
#endif /* __CC__ */
/*[[[end]]]*/
#endif /* __USE_MISC */

__DECL_END

#endif /* _BITS_OS_KOS_MSQ_H */
