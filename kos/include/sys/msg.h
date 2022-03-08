/* HASH CRC-32:0xf0d85caa */
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
/* (>) Standard: POSIX.1b (Issue 2, IEEE Std 1003.1b-1993) */
/* (#) Portability: Cygwin        (/winsup/cygwin/include/sys/msg.h) */
/* (#) Portability: FreeBSD       (/sys/sys/msg.h) */
/* (#) Portability: GNU C Library (/sysvipc/sys/msg.h) */
/* (#) Portability: NetBSD        (/sys/sys/msg.h) */
/* (#) Portability: OpenBSD       (/sys/sys/msg.h) */
/* (#) Portability: OpenSolaris   (/usr/src/uts/common/sys/msg.h) */
/* (#) Portability: diet libc     (/include/sys/msg.h) */
/* (#) Portability: libc4/5       (/include/sys/msg.h) */
/* (#) Portability: musl libc     (/include/sys/msg.h) */
/* (#) Portability: uClibc        (/include/sys/msg.h) */
#ifndef _SYS_MSG_H
#define _SYS_MSG_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <bits/os/msq.h>
#include <sys/ipc.h> /* [n4217.pdf:12344] #include mandated by POSIX */

#ifdef __USE_GNU
#include <bits/os/msgbuf.h> /* `struct msgbuf' */
#endif /* __USE_GNU */

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __time_t_defined
#define __time_t_defined
typedef __TM_TYPE(time) time_t;
#endif /* !__time_t_defined */

#ifndef __size_t_defined
#define __size_t_defined
typedef __size_t size_t;
#endif /* !__size_t_defined */

#ifndef __pid_t_defined
#define __pid_t_defined
typedef __pid_t pid_t;
#endif /* !__pid_t_defined */

#ifndef __ssize_t_defined
#define __ssize_t_defined
typedef __ssize_t ssize_t;
#endif /* !__ssize_t_defined */

#ifndef __key_t_defined
#define __key_t_defined
typedef __key_t key_t;
#endif /* !__key_t_defined */

__CDECLARE_OPT(,int,__NOTHROW_NCX,msgctl,(int __msqid, __STDC_INT_AS_UINT_T __cmd, struct msqid_ds *__buf),(__msqid,__cmd,__buf))
__CDECLARE_OPT(,int,__NOTHROW_NCX,msgget,(key_t __key, __STDC_INT_AS_UINT_T __msgflg),(__key,__msgflg))
#ifdef __CRT_HAVE_msgrcv
__CDECLARE(,ssize_t,__NOTHROW_RPC,msgrcv,(int __msqid, void *__msgp, size_t __msgsz, __LONGPTR_TYPE__ __msgtyp, __STDC_INT_AS_UINT_T __msgflg),(__msqid,__msgp,__msgsz,__msgtyp,__msgflg))
#elif defined(__CRT_HAVE___libc_msgrcv)
__CREDIRECT(,ssize_t,__NOTHROW_RPC,msgrcv,(int __msqid, void *__msgp, size_t __msgsz, __LONGPTR_TYPE__ __msgtyp, __STDC_INT_AS_UINT_T __msgflg),__libc_msgrcv,(__msqid,__msgp,__msgsz,__msgtyp,__msgflg))
#endif /* ... */
#ifdef __CRT_HAVE_msgsnd
__CDECLARE(,int,__NOTHROW_RPC,msgsnd,(int __msqid, const void *__msgp, size_t __msgsz, __STDC_INT_AS_UINT_T __msgflg),(__msqid,__msgp,__msgsz,__msgflg))
#elif defined(__CRT_HAVE___libc_msgsnd)
__CREDIRECT(,int,__NOTHROW_RPC,msgsnd,(int __msqid, const void *__msgp, size_t __msgsz, __STDC_INT_AS_UINT_T __msgflg),__libc_msgsnd,(__msqid,__msgp,__msgsz,__msgflg))
#endif /* ... */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_SYS_MSG_H */
