/* HASH CRC-32:0x1c4fa7d0 */
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
#ifndef _SYS_MSG_H
#define _SYS_MSG_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */


#include <features.h>
#include <sys/ipc.h>
#include <bits/msq.h>

/* Documentation taken from /usr/include/i386-linux-gnu/sys/msg.h */
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

__SYSDECL_BEGIN

#ifdef __CC__

#ifndef __time_t_defined
#define __time_t_defined 1
typedef __TM_TYPE(time) time_t;
#endif /* !__time_t_defined */

#ifndef __size_t_defined
#define __size_t_defined 1
typedef __size_t size_t;
#endif /* !__size_t_defined */

#ifndef __pid_t_defined
#define __pid_t_defined 1
typedef __pid_t pid_t;
#endif /* !__pid_t_defined */

#ifndef __ssize_t_defined
#define __ssize_t_defined 1
typedef __ssize_t ssize_t;
#endif /* !__ssize_t_defined */

/* The following System V style IPC functions implement a message queue system.
 * The definition is found in XPG2. */

#ifdef __USE_GNU
/* Template for struct to be used as argument for `msgsnd' and `msgrcv'.  */
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("mtype")
#pragma push_macro("mtext")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef mtype
#undef mtext
struct msgbuf {
	__syscall_slong_t               mtype;  /* type of received/sent message */
#ifdef __USE_KOS
	__COMPILER_FLEXIBLE_ARRAY(char, mtext); /* text of the message */
#else /* __USE_KOS */
	char                            mtext[1]; /* text of the message */
#endif /* !__USE_KOS */
};
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("mtext")
#pragma pop_macro("mtype")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#endif /* __USE_GNU */

#ifdef __CRT_HAVE_msgctl
/* Message queue control operation */
__CDECLARE(,int,__NOTHROW_NCX,msgctl,(int __msqid, int __cmd, struct msqid_ds *__buf),(__msqid,__cmd,__buf))
#endif /* msgctl... */
#ifdef __CRT_HAVE_msgget
/* Get messages queue */
__CDECLARE(,int,__NOTHROW_NCX,msgget,(key_t __key, int __msgflg),(__key,__msgflg))
#endif /* msgget... */
#ifdef __CRT_HAVE_msgrcv
/* Receive message from message queue */
__CDECLARE(,ssize_t,__NOTHROW_RPC,msgrcv,(int __msqid, void *__msgp, size_t __msgsz, __LONGPTR_TYPE__ __msgtyp, int __msgflg),(__msqid,__msgp,__msgsz,__msgtyp,__msgflg))
#endif /* msgrcv... */
#ifdef __CRT_HAVE_msgsnd
/* Send message to message queue */
__CDECLARE(,int,__NOTHROW_RPC,msgsnd,(int __msqid, const void *__msgp, size_t __msgsz, int __msgflg),(__msqid,__msgp,__msgsz,__msgflg))
#endif /* msgsnd... */

#endif /* __CC__ */

__SYSDECL_END

#endif /* !_SYS_MSG_H */
