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
#ifndef _BITS_OS_KOS_SEM_H
#define _BITS_OS_KOS_SEM_H 1

#include <__stdinc.h>
#include <features.h> /* __USE_MISC */

#include <bits/os/ipc.h> /* struct ipc_perm */

__DECL_BEGIN

/* A set of semaphores. */
/*[[[struct]]]*/
#ifdef __CC__
struct semid_ds {
	struct ipc_perm     sem_perm;        /* ??? */
	__time_t            sem_otime;       /* ??? */
#if __SIZEOF_TIME_T__ > __SIZEOF_SYSCALL_LONG_T__
#if __SIZEOF_TIME_T__ != __SIZEOF_SYSCALL_LONG_T__ * 2
#error "Unsupported configuration"
#endif /* __SIZEOF_TIME_T__ != __SIZEOF_SYSCALL_LONG_T__ * 2 */
#else /* __SIZEOF_TIME_T__ > __SIZEOF_SYSCALL_LONG_T__ */
	__syscall_ulong_t __glibc_reserved1;
#endif /* __SIZEOF_TIME_T__ <= __SIZEOF_SYSCALL_LONG_T__ */
	__time_t            sem_ctime;       /* ??? */
#if __SIZEOF_TIME_T__ <= __SIZEOF_SYSCALL_LONG_T__
	__syscall_ulong_t __glibc_reserved2;
#endif /* __SIZEOF_TIME_T__ <= __SIZEOF_SYSCALL_LONG_T__ */
	__syscall_ulong_t   sem_nsems;       /* ??? */
	__syscall_ulong_t __glibc_reserved3;
	__syscall_ulong_t __glibc_reserved4;
};
#endif /* __CC__ */
/*[[[end]]]*/

#ifdef __USE_MISC
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

#endif /* _BITS_OS_KOS_SEM_H */
