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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _BITS_SEM_H
#define _BITS_SEM_H 1

#include <__stdinc.h>
#include <bits/ipc.h>

/* Documentation taken from GLibc /usr/include/i386-linux-gnu/bits/sem.h */
/* Copyright (C) 2002-2016 Free Software Foundation, Inc.
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

__DECL_BEGIN

/* Flags for `semop'.  */
#define SEM_UNDO 0x1000 /* undo the operation on exit */

/* Commands for `semctl'.  */
#define GETPID   11 /* get sempid */
#define GETVAL   12 /* get semval */
#define GETALL   13 /* get all semval's */
#define GETNCNT  14 /* get semncnt */
#define GETZCNT  15 /* get semzcnt */
#define SETVAL   16 /* set semval */
#define SETALL   17 /* set all semval's */


/* Data structure describing a set of semaphores.  */
/*[[[struct]]]*/
#ifdef __CC__
struct semid_ds {
	struct ipc_perm     sem_perm; /* operation permission struct */
	__TM_TYPE(time)     sem_otime;       /* last semop() time */
#if __TM_SIZEOF(TIME) > __SIZEOF_SYSCALL_LONG_T__
#if __TM_SIZEOF(TIME) != __SIZEOF_SYSCALL_LONG_T__*2
#error "Unsupported configuration"
#endif
#else /* __TM_SIZEOF(TIME) > __SIZEOF_SYSCALL_LONG_T__ */
	__syscall_ulong_t __glibc_reserved1;
#endif /* __TM_SIZEOF(TIME) <= __SIZEOF_SYSCALL_LONG_T__ */
	__TM_TYPE(time)     sem_ctime; /* last time changed by semctl() */
#if __TM_SIZEOF(TIME) <= __SIZEOF_SYSCALL_LONG_T__
	__syscall_ulong_t __glibc_reserved2;
#endif /* __TM_SIZEOF(TIME) <= __SIZEOF_SYSCALL_LONG_T__ */
	__syscall_ulong_t   sem_nsems; /* number of semaphores in set */
	__syscall_ulong_t __glibc_reserved3;
	__syscall_ulong_t __glibc_reserved4;
};
#endif /* __CC__ */
/*[[[end]]]*/

/* The user should define a union like the following to use it for arguments for `semctl'.
 * >> union semun {
 * >>     int                 val;   // value for SETVAL
 * >>     struct semid_ds    *buf;   // buffer for IPC_STAT & IPC_SET
 * >>     unsigned short int *array; // array for GETALL & SETALL
 * >>     struct seminfo     *__buf; // buffer for IPC_INFO
 * >> };
 * 
 * Previous versions of this file used to define this union but this is
 * incorrect. One can test the macro _SEM_SEMUN_UNDEFINED to see whether
 * one must define the union or not.  */
#define _SEM_SEMUN_UNDEFINED 1

#ifdef __USE_MISC

/* ipcs ctl cmds */
#define SEM_STAT 18
#define SEM_INFO 19

/*[[[struct]]]*/
#ifdef __CC__
struct seminfo {
	__INT32_TYPE__ semmap;
	__INT32_TYPE__ semmni;
	__INT32_TYPE__ semmns;
	__INT32_TYPE__ semmnu;
	__INT32_TYPE__ semmsl;
	__INT32_TYPE__ semopm;
	__INT32_TYPE__ semume;
	__INT32_TYPE__ semusz;
	__INT32_TYPE__ semvmx;
	__INT32_TYPE__ semaem;
};
#endif /* __CC__ */
/*[[[end]]]*/

#endif /* __USE_MISC */

__DECL_END

#endif /* _BITS_SEM_H */
