/* HASH CRC-32:0x642ba841 */
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
/* (>) Standard: POSIX.1b (Issue 2, IEEE Std 1003.1b-1993) */
/* (#) Portability: Cygwin        (/winsup/cygwin/include/sys/shm.h) */
/* (#) Portability: DragonFly BSD (/sys/sys/shm.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/sys/shm.h) */
/* (#) Portability: FreeBSD       (/sys/sys/shm.h) */
/* (#) Portability: GNU C Library (/sysvipc/sys/shm.h) */
/* (#) Portability: NetBSD        (/sys/sys/shm.h) */
/* (#) Portability: OpenBSD       (/sys/sys/shm.h) */
/* (#) Portability: OpenSolaris   (/usr/src/uts/common/sys/shm.h) */
/* (#) Portability: diet libc     (/include/sys/shm.h) */
/* (#) Portability: libc4/5       (/include/sys/shm.h) */
/* (#) Portability: mintlib       (/include/sys/shm.h) */
/* (#) Portability: musl libc     (/include/sys/shm.h) */
/* (#) Portability: uClibc        (/include/sys/shm.h) */
/*!always_includes <sys/ipc.h>*/
#ifndef _SYS_SHM_H
#define _SYS_SHM_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#include <asm/os/shm.h>
#include <asm/pagesize.h> /* __ARCH_PAGESIZE */
#include <bits/os/shm.h>
#include <sys/ipc.h> /* [n4217.pdf:12556] #include mandated by POSIX */

/* Permission flag for use with `shmget()'. */
#ifndef SHM_W
#ifdef __SHM_W
#define SHM_W __SHM_W /* or S_IWUGO */
#else /* __SHM_W */
#define SHM_W 0222    /* or S_IWUGO */
#endif /* !__SHM_W */
#endif /* !SHM_W */
#ifndef SHM_R
#ifdef __SHM_R
#define SHM_R __SHM_R /* or S_IRUGO */
#else /* __SHM_R */
#define SHM_R 0444    /* or S_IRUGO */
#endif /* !__SHM_R */
#endif /* !SHM_R */

/* Flags for use with `shmat()'. */
#if !defined(SHM_RDONLY) && defined(__SHM_RDONLY)
#define SHM_RDONLY __SHM_RDONLY /* ??? */
#endif /* !SHM_RDONLY && __SHM_RDONLY */
#if !defined(SHM_RND) && defined(__SHM_RND)
#define SHM_RND    __SHM_RND    /* ??? */
#endif /* !SHM_RND && __SHM_RND */
#if !defined(SHM_REMAP) && defined(__SHM_REMAP)
#define SHM_REMAP  __SHM_REMAP  /* ??? */
#endif /* !SHM_REMAP && __SHM_REMAP */
#if !defined(SHM_EXEC) && defined(__SHM_EXEC)
#define SHM_EXEC   __SHM_EXEC   /* ??? */
#endif /* !SHM_EXEC && __SHM_EXEC */

/* Command codes for use with `shmctl()'. */
#if !defined(SHM_LOCK) && defined(__SHM_LOCK)
#define SHM_LOCK   __SHM_LOCK   /* ??? */
#endif /* !SHM_LOCK && __SHM_LOCK */
#if !defined(SHM_UNLOCK) && defined(__SHM_UNLOCK)
#define SHM_UNLOCK __SHM_UNLOCK /* ??? */
#endif /* !SHM_UNLOCK && __SHM_UNLOCK */

/* Segment low boundary address multiple.  */
#ifndef SHMLBA
#ifdef __SHMLBA
#define SHMLBA __SHMLBA
#elif defined(__ARCH_PAGESIZE)
#define SHMLBA __ARCH_PAGESIZE
#else /* __ARCH_PAGESIZE */
#include <libc/unistd.h>
#ifdef ____libc_getpagesize_defined
#define SHMLBA __libc_getpagesize()
#endif /* ____libc_getpagesize_defined */
#endif /* ... */
#endif /* !SHMLBA */

#ifdef __USE_MISC
/* ipcs ctl commands */
#if !defined(SHM_STAT) && defined(__SHM_STAT)
#define SHM_STAT __SHM_STAT /* ??? */
#endif /* !SHM_STAT && __SHM_STAT */
#if !defined(SHM_INFO) && defined(__SHM_INFO)
#define SHM_INFO __SHM_INFO /* ??? */
#endif /* !SHM_INFO && __SHM_INFO */

/* shm_mode upper byte flags. */
#if !defined(SHM_DEST) && defined(__SHM_DEST)
#define SHM_DEST      __SHM_DEST      /* ??? */
#endif /* !SHM_DEST && __SHM_DEST */
#if !defined(SHM_LOCKED) && defined(__SHM_LOCKED)
#define SHM_LOCKED    __SHM_LOCKED    /* ??? */
#endif /* !SHM_LOCKED && __SHM_LOCKED */
#if !defined(SHM_HUGETLB) && defined(__SHM_HUGETLB)
#define SHM_HUGETLB   __SHM_HUGETLB   /* ??? */
#endif /* !SHM_HUGETLB && __SHM_HUGETLB */
#if !defined(SHM_NORESERVE) && defined(__SHM_NORESERVE)
#define SHM_NORESERVE __SHM_NORESERVE /* ??? */
#endif /* !SHM_NORESERVE && __SHM_NORESERVE */
#endif /* __USE_MISC */


#ifdef __CC__
__SYSDECL_BEGIN

#ifdef __USE_XOPEN
#ifndef __pid_t_defined
#define __pid_t_defined
typedef __pid_t pid_t;
#endif /* __pid_t_defined */
#endif /* __USE_XOPEN */

#ifndef __size_t_defined
#define __size_t_defined
typedef __SIZE_TYPE__ size_t;
#endif /* !__size_t_defined */

#ifndef __key_t_defined
#define __key_t_defined
typedef __key_t key_t;
#endif /* !__key_t_defined */

#ifndef __time_t_defined
#define __time_t_defined
typedef __time_t time_t;
#endif /* !__time_t_defined */

__CDECLARE_OPT(,int,__NOTHROW_NCX,shmctl,(int __shmid, __STDC_INT_AS_UINT_T __cmd, struct shmid_ds *__buf),(__shmid,__cmd,__buf))
__CDECLARE_OPT(,int,__NOTHROW_NCX,shmget,(key_t __key, size_t __size, __STDC_INT_AS_UINT_T __shmflg),(__key,__size,__shmflg))
__CDECLARE_OPT(,void *,__NOTHROW_NCX,shmat,(int __shmid, void const *__shmaddr, __STDC_INT_AS_UINT_T __shmflg),(__shmid,__shmaddr,__shmflg))
__CDECLARE_OPT(,int,__NOTHROW_NCX,shmdt,(void const *__shmaddr),(__shmaddr))

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_SYS_SHM_H */
