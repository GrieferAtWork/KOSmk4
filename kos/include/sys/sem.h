/* HASH CRC-32:0x3bd4afe7 */
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
#ifndef _SYS_SEM_H
#define _SYS_SEM_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <stddef.h>
#include <bits/timespec.h>
#include <sys/ipc.h>
#include <bits/sem.h>

/* Documentation taken from GLibc /usr/include/i386-linux-gnu/sys/sem.h */
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


#ifdef __CC__

__SYSDECL_BEGIN

#ifndef __size_t_defined
#define __size_t_defined 1
typedef __size_t size_t;
#endif /* !__size_t_defined */

/* Structure used for argument to `semop' to describe operations.  */
struct sembuf {
	__UINT16_TYPE__ sem_num; /* semaphore number */
	__INT16_TYPE__  sem_op;  /* semaphore operation */
	__INT16_TYPE__  sem_flg; /* operation flag */
};

#ifdef __CRT_HAVE_semctl
/* Semaphore control operation. */
__LIBC int __NOTHROW_NCX(__VLIBCCALL semctl)(int __semid, int __semnum, int __cmd, ...) __CASMNAME_SAME("semctl");
#endif /* semctl... */
#ifdef __CRT_HAVE_semget
/* Get semaphore */
__CDECLARE(,int,__NOTHROW_NCX,semget,(key_t __key, int __nsems, int __semflg),(__key,__nsems,__semflg))
#endif /* semget... */
#ifdef __CRT_HAVE_semop
/* Operate on semaphore */
__CDECLARE(,int,__NOTHROW_NCX,semop,(int __semid, struct sembuf *__sops, size_t __nsops),(__semid,__sops,__nsops))
#endif /* semop... */
#ifdef __USE_GNU
#ifdef __CRT_HAVE_semtimedop
/* Operate on semaphore with timeout */
__CDECLARE(,int,__NOTHROW_NCX,semtimedop,(int __semid, struct sembuf *__sops, size_t __nsops, struct timespec const *__timeout),(__semid,__sops,__nsops,__timeout))
#endif /* semtimedop... */
#endif /* __USE_GNU */
#endif /* __CC__ */

__SYSDECL_END

#endif /* !_SYS_SEM_H */
