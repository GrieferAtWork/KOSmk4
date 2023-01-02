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
%(c_prefix){
/* (>) Standard: POSIX.1b (Issue 2, IEEE Std 1003.1b-1993) */
/* (#) Portability: Cygwin        (/winsup/cygwin/include/sys/msg.h) */
/* (#) Portability: DragonFly BSD (/sys/sys/msg.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/sys/msg.h) */
/* (#) Portability: FreeBSD       (/sys/sys/msg.h) */
/* (#) Portability: GNU C Library (/sysvipc/sys/msg.h) */
/* (#) Portability: NetBSD        (/sys/sys/msg.h) */
/* (#) Portability: OpenBSD       (/sys/sys/msg.h) */
/* (#) Portability: OpenSolaris   (/usr/src/uts/common/sys/msg.h) */
/* (#) Portability: diet libc     (/include/sys/msg.h) */
/* (#) Portability: libc4/5       (/include/sys/msg.h) */
/* (#) Portability: mintlib       (/include/sys/msg.h) */
/* (#) Portability: musl libc     (/include/sys/msg.h) */
/* (#) Portability: uClibc        (/include/sys/msg.h) */
}

%[define_replacement(fd_t = __fd_t)]
%[define_replacement(longptr_t = __LONGPTR_TYPE__)]
%[default:section(".text.crt{|.dos}.sched.msg")]

%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <bits/os/msq.h>
)]%{
#include <sys/ipc.h> /* [n4217.pdf:12344] #include mandated by POSIX */

#ifdef __USE_GNU
#include <bits/os/msgbuf.h> /* `struct msgbuf' */
#endif /* __USE_GNU */

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __time_t_defined
#define __time_t_defined
typedef __time_t time_t;
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

}

[[decl_include("<features.h>", "<bits/os/msq.h>")]]
int msgctl(int msqid, __STDC_INT_AS_UINT_T cmd, struct msqid_ds *buf);

[[decl_include("<features.h>", "<bits/types.h>")]]
int msgget(key_t key, __STDC_INT_AS_UINT_T msgflg);

[[cp, decl_include("<features.h>", "<hybrid/typecore.h>"), export_alias("__libc_msgrcv")]]
ssize_t msgrcv(int msqid, void *msgp, size_t msgsz,
               $longptr_t msgtyp, __STDC_INT_AS_UINT_T msgflg);

[[cp, decl_include("<features.h>", "<hybrid/typecore.h>"), export_alias("__libc_msgsnd")]]
int msgsnd(int msqid, const void *msgp,
           size_t msgsz, __STDC_INT_AS_UINT_T msgflg);

%{

__SYSDECL_END
#endif /* __CC__ */

}
