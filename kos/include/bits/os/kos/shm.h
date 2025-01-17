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
#ifndef _BITS_OS_KOS_SHM_H
#define _BITS_OS_KOS_SHM_H 1

#include <__stdinc.h>
#include <features.h> /* __USE_MISC */

#include <bits/os/kos/ipc.h> /* struct ipc_perm */
#include <bits/types.h>

#ifdef __CC__
__DECL_BEGIN

/* Type to count number of attaches.  */
typedef __syscall_ulong_t shmatt_t;

/* Data structure describing a shared memory segment.  */
struct shmid_ds {
	struct ipc_perm     shm_perm;   /* ??? */
	__size_t            shm_segsz;  /* ??? */
	__time32_t          shm_atime;  /* ??? */
#if __SIZEOF_POINTER__ > __SIZEOF_TIME32_T__
	__UINT32_TYPE__   __glibc_reserved1;
#endif /* __SIZEOF_POINTER__ > __SIZEOF_TIME32_T__ */
	__time32_t          shm_dtime;  /* ??? */
#if __SIZEOF_POINTER__ > __SIZEOF_TIME32_T__
	__UINT32_TYPE__   __glibc_reserved2;
#endif /* __SIZEOF_POINTER__ > __SIZEOF_TIME32_T__ */
	__time32_t          shm_ctime;  /* ??? */
#if __SIZEOF_POINTER__ > __SIZEOF_TIME32_T__
	__UINT32_TYPE__   __glibc_reserved3;
#endif /* __SIZEOF_POINTER__ > __SIZEOF_TIME32_T__ */
	__pid_t             shm_cpid;   /* ??? */
	__pid_t             shm_lpid;   /* ??? */
	shmatt_t            shm_nattch; /* ??? */
	__syscall_ulong_t __glibc_reserved4;
	__syscall_ulong_t __glibc_reserved5;
};

#ifdef __USE_MISC
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("shmmax")
#pragma push_macro("shmmin")
#pragma push_macro("shmmni")
#pragma push_macro("shmseg")
#pragma push_macro("shmall")
#pragma push_macro("used_ids")
#pragma push_macro("shm_tot")
#pragma push_macro("shm_rss")
#pragma push_macro("shm_swp")
#pragma push_macro("swap_attempts")
#pragma push_macro("swap_successes")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef shmmax
#undef shmmin
#undef shmmni
#undef shmseg
#undef shmall
#undef used_ids
#undef shm_tot
#undef shm_rss
#undef shm_swp
#undef swap_attempts
#undef swap_successes

struct shminfo {
	__syscall_ulong_t shmmax; /* ??? */
	__syscall_ulong_t shmmin; /* ??? */
	__syscall_ulong_t shmmni; /* ??? */
	__syscall_ulong_t shmseg; /* ??? */
	__syscall_ulong_t shmall; /* ??? */
	__syscall_ulong_t __glibc_reserved1;
	__syscall_ulong_t __glibc_reserved2;
	__syscall_ulong_t __glibc_reserved3;
	__syscall_ulong_t __glibc_reserved4;
};

struct shm_info {
	int               used_ids;       /* ??? */
#if __SIZEOF_INT__ < __SIZEOF_SYSCALL_LONG_T__
	__BYTE_TYPE__   __si_pad[__SIZEOF_SYSCALL_LONG_T__ - __SIZEOF_INT__]; /* ... */
#endif /* __SIZEOF_INT__ < __SIZEOF_SYSCALL_LONG_T__ */
	__syscall_ulong_t shm_tot;        /* ??? */
	__syscall_ulong_t shm_rss;        /* ??? */
	__syscall_ulong_t shm_swp;        /* ??? */
	__syscall_ulong_t swap_attempts;  /* ??? */
	__syscall_ulong_t swap_successes; /* ??? */
};

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("swap_successes")
#pragma pop_macro("swap_attempts")
#pragma pop_macro("shm_swp")
#pragma pop_macro("shm_rss")
#pragma pop_macro("shm_tot")
#pragma pop_macro("used_ids")
#pragma pop_macro("shmall")
#pragma pop_macro("shmseg")
#pragma pop_macro("shmmni")
#pragma pop_macro("shmmin")
#pragma pop_macro("shmmax")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#endif /* __USE_MISC */

__DECL_END
#endif /* __CC__ */

#endif /* !_BITS_OS_KOS_SHM_H */
