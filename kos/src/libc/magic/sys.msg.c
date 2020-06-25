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

%[define_replacement(fd_t = __fd_t)]
%[define_replacement(longptr_t = __LONGPTR_TYPE__)]
%[default:section(".text.crt{|.dos}.sched.msg")]

%{

#include <features.h>
#include <bits/msq.h>

#ifdef __USE_GNU
#include <bits/msgbuf.h> /* struct msgbuf */
#endif /* __USE_GNU */

#ifdef __USE_GLIBC
#include <sys/ipc.h>
#endif /* __USE_GLIBC */

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

#ifndef __key_t_defined
#define __key_t_defined 1
typedef __key_t key_t;
#endif /* !__key_t_defined */

/* The following System V style IPC functions implement a message queue system.
 * The definition is found in XPG2. */

}

@@Message queue control operation
[[decl_include("<features.h>", "<bits/msq.h>")]]
int msgctl(int msqid, __STDC_INT_AS_UINT_T cmd, struct msqid_ds *buf);

@@Get messages queue
[[decl_include("<features.h>", "<bits/types.h>")]]
int msgget(key_t key, __STDC_INT_AS_UINT_T msgflg);

@@Receive message from message queue
[[cp, decl_include("<features.h>")]]
ssize_t msgrcv(int msqid, void *msgp, size_t msgsz,
               $longptr_t msgtyp, __STDC_INT_AS_UINT_T msgflg);

@@Send message to message queue
[[cp, decl_include("<features.h>")]]
int msgsnd(int msqid, const void *msgp,
           size_t msgsz, __STDC_INT_AS_UINT_T msgflg);

%{

#endif /* __CC__ */

__SYSDECL_END

}