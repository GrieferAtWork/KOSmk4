/* HASH CRC-32:0x569e9f88 */
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
/* (#) Portability: Cygwin        (/winsup/cygwin/include/sys/sem.h) */
/* (#) Portability: DragonFly BSD (/sys/sys/sem.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/sys/sem.h) */
/* (#) Portability: FreeBSD       (/sys/sys/sem.h) */
/* (#) Portability: GNU C Library (/sysvipc/sys/sem.h) */
/* (#) Portability: NetBSD        (/sys/sys/sem.h) */
/* (#) Portability: OpenBSD       (/sys/sys/sem.h) */
/* (#) Portability: OpenSolaris   (/usr/src/uts/common/sys/sem.h) */
/* (#) Portability: diet libc     (/include/sys/sem.h) */
/* (#) Portability: libc4/5       (/include/sys/sem.h) */
/* (#) Portability: mintlib       (/include/sys/sem.h) */
/* (#) Portability: musl libc     (/include/sys/sem.h) */
/* (#) Portability: uClibc        (/include/sys/sem.h) */
#ifndef _SYS_SEM_H
#define _SYS_SEM_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#include <asm/os/sem.h>
#include <bits/os/sem.h>
#include <bits/os/sembuf.h>
#include <sys/ipc.h> /* [n4217.pdf:12514] #include mandated by POSIX */

#ifdef __USE_GNU
#include <bits/os/timespec.h>
#endif /* __USE_GNU */

#ifdef __USE_GLIBC_BLOAT
#include <stddef.h>
#endif /* __USE_GLIBC_BLOAT */

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
#define __size_t_defined
typedef __SIZE_TYPE__ size_t;
#endif /* !__size_t_defined */

#ifndef __key_t_defined
#define __key_t_defined
typedef __key_t key_t;
#endif /* !__key_t_defined */

#ifndef __pid_t_defined
#define __pid_t_defined
typedef __pid_t pid_t;
#endif /* !__pid_t_defined */

#ifndef __time_t_defined
#define __time_t_defined
typedef __time_t time_t;
#endif /* !__time_t_defined */

#ifdef __CRT_HAVE_semctl
/* Semaphore control operation. */
__LIBC int __NOTHROW_NCX(__VLIBCCALL semctl)(int __semid, __STDC_INT_AS_UINT_T __semnum, __STDC_INT_AS_UINT_T __cmd, ...) __CASMNAME_SAME("semctl");
#endif /* __CRT_HAVE_semctl */
/* Get semaphore */
__CDECLARE_OPT(,int,__NOTHROW_NCX,semget,(key_t __key, __STDC_INT_AS_UINT_T __nsems, __STDC_INT_AS_UINT_T __semflg),(__key,__nsems,__semflg))
/* Operate on semaphore */
__CDECLARE_OPT(,int,__NOTHROW_NCX,semop,(int __semid, struct sembuf *__sops, size_t __nsops),(__semid,__sops,__nsops))
#ifdef __USE_GNU
/* Operate on semaphore with timeout */
__CDECLARE_OPT(,int,__NOTHROW_NCX,semtimedop,(int __semid, struct sembuf *__sops, size_t __nsops, struct timespec const *__timeout),(__semid,__sops,__nsops,__timeout))
#endif /* __USE_GNU */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_SYS_SEM_H */
