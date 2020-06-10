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
%[default_impl_section(".text.crt.io.poll")]

%{
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

}

@@Semaphore control operation.  
int semctl(int semid,
           __STDC_INT_AS_UINT_T semnum,
           __STDC_INT_AS_UINT_T cmd, ...);

@@Get semaphore
int semget(key_t key,
           __STDC_INT_AS_UINT_T nsems,
           __STDC_INT_AS_UINT_T semflg);

@@Operate on semaphore
int semop(int semid, struct sembuf *sops, size_t nsops);

%#ifdef __USE_GNU
@@Operate on semaphore with timeout
int semtimedop(int semid,
               struct sembuf *sops, size_t nsops,
               struct timespec const *timeout);
/* TODO: semtimedop64(..., struct timespec64 const *timeout) */
%#endif /* __USE_GNU */

%{
#endif /* __CC__ */

__SYSDECL_END

}