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
%(c_prefix){
/* (>) Standard: POSIX.1b (Issue 2, IEEE Std 1003.1b-1993) */
/* (#) Portability: Cygwin        (/winsup/cygwin/include/sys/sem.h) */
/* (#) Portability: FreeBSD       (/sys/sys/sem.h) */
/* (#) Portability: GNU C Library (/sysvipc/sys/sem.h) */
/* (#) Portability: NetBSD        (/sys/sys/sem.h) */
/* (#) Portability: OpenBSD       (/sys/sys/sem.h) */
/* (#) Portability: OpenSolaris   (/usr/src/uts/common/sys/sem.h) */
/* (#) Portability: diet libc     (/include/sys/sem.h) */
/* (#) Portability: libc4/5       (/include/sys/sem.h) */
/* (#) Portability: musl libc     (/include/sys/sem.h) */
/* (#) Portability: uClibc        (/include/sys/sem.h) */
}

%[define_replacement(fd_t = __fd_t)]
%[default:section(".text.crt{|.dos}.io.poll")]

%[insert:prefix(
#include <features.h>
)]%{

}%[insert:prefix(
#include <asm/os/sem.h>
)]%[insert:prefix(
#include <bits/os/sem.h>
)]%[insert:prefix(
#include <bits/os/sembuf.h>
)]%{
#include <sys/ipc.h> /* [n4217.pdf:12514] #include mandated by POSIX */

#ifdef __USE_GNU
#include <bits/os/timespec.h>
#endif /* __USE_GNU */

#ifdef __USE_GLIBC
#include <stddef.h>
#endif /* __USE_GLIBC */

/* Flags for `semop'. */
#if !defined(SEM_UNDO) && defined(__SEM_UNDO)
#define SEM_UNDO __SEM_UNDO /* ??? */
#endif /* !SEM_UNDO && __SEM_UNDO */

/* Commands for `semctl'.  */
#if !defined(GETPID) && defined(__GETPID)
#define GETPID  __GETPID /* ??? */
#endif /* !GETPID && __GETPID */
#if !defined(GETVAL) && defined(__GETVAL)
#define GETVAL  __GETVAL /* ??? */
#endif /* !GETVAL && __GETVAL */
#if !defined(GETALL) && defined(__GETALL)
#define GETALL  __GETALL /* ??? */
#endif /* !GETALL && __GETALL */
#if !defined(GETNCNT) && defined(__GETNCNT)
#define GETNCNT __GETNCNT /* ??? */
#endif /* !GETNCNT && __GETNCNT */
#if !defined(GETZCNT) && defined(__GETZCNT)
#define GETZCNT __GETZCNT /* ??? */
#endif /* !GETZCNT && __GETZCNT */
#if !defined(SETVAL) && defined(__SETVAL)
#define SETVAL  __SETVAL /* ??? */
#endif /* !SETVAL && __SETVAL */
#if !defined(SETALL) && defined(__SETALL)
#define SETALL  __SETALL /* ??? */
#endif /* !SETALL && __SETALL */

/* ipcs ctl cmds */
#if !defined(SEM_STAT) && defined(__SEM_STAT)
#define SEM_STAT __SEM_STAT /* ??? */
#endif /* !SEM_STAT && __SEM_STAT */
#if !defined(SEM_INFO) && defined(__SEM_INFO)
#define SEM_INFO __SEM_INFO /* ??? */
#endif /* !SEM_INFO && __SEM_INFO */

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __size_t_defined
#define __size_t_defined 1
typedef __SIZE_TYPE__ size_t;
#endif /* !__size_t_defined */

#ifndef __key_t_defined
#define __key_t_defined 1
typedef __key_t key_t;
#endif /* !__key_t_defined */

#ifndef __pid_t_defined
#define __pid_t_defined 1
typedef __pid_t pid_t;
#endif /* !__pid_t_defined */

#ifndef __time_t_defined
#define __time_t_defined 1
typedef __TM_TYPE(time) time_t;
#endif /* !__time_t_defined */

}

@@Semaphore control operation.
[[decl_include("<features.h>")]]
int semctl(int semid,
           __STDC_INT_AS_UINT_T semnum,
           __STDC_INT_AS_UINT_T cmd, ...);

@@Get semaphore
[[decl_include("<features.h>")]]
int semget(key_t key,
           __STDC_INT_AS_UINT_T nsems,
           __STDC_INT_AS_UINT_T semflg);

@@Operate on semaphore
[[decl_include("<bits/os/sembuf.h>")]]
int semop(int semid, struct sembuf *sops, size_t nsops);

%#ifdef __USE_GNU
@@Operate on semaphore with timeout
[[decl_include("<bits/os/sembuf.h>")]]
[[decl_include("<bits/os/timespec.h>")]]
int semtimedop(int semid,
               struct sembuf *sops, size_t nsops,
               struct timespec const *timeout);
/* TODO: semtimedop64(..., struct timespec64 const *timeout) */
%#endif /* __USE_GNU */

%{

__SYSDECL_END
#endif /* __CC__ */

}
