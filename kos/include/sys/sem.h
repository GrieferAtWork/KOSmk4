/* HASH CRC-32:0xa114bb8b */
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
#ifndef _SYS_SEM_H
#define _SYS_SEM_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#include <bits/os/sem.h>
#include <bits/os/sembuf.h>
#include <bits/os/timespec.h>

#ifdef __USE_GLIBC
#include <sys/ipc.h>

#include <stddef.h>
#endif /* __USE_GLIBC */

#ifdef __CC__

__SYSDECL_BEGIN

#ifndef __size_t_defined
#define __size_t_defined 1
typedef __size_t size_t;
#endif /* !__size_t_defined */

#ifndef __key_t_defined
#define __key_t_defined 1
typedef __key_t key_t;
#endif /* !__key_t_defined */

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
#endif /* __CC__ */

__SYSDECL_END

#endif /* !_SYS_SEM_H */
