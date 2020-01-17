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
#ifndef _BITS_SHM_H
#define _BITS_SHM_H 1

#include <__stdinc.h>
#include <features.h>

#include <hybrid/host.h>

#include <asm/pagesize.h>
#include <bits/types.h>

__SYSDECL_BEGIN

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

/* Permission flag for shmget. */
#define SHM_W  0x080 /* or S_IWUGO from <linux/stat.h> */
#define SHM_R  0x100 /* or S_IRUGO from <linux/stat.h> */

/* Flags for `shmat'. */
#define SHM_RDONLY 0x1000 /* attach read-only else read-write. */
#define SHM_RND    0x2000 /* round attach address to SHMLBA. */
#define SHM_REMAP  0x4000 /* take-over region on attach. */
#define SHM_EXEC   0x8000 /* execution access. */

/* Commands for `shmctl'. */
#define SHM_LOCK   11 /* lock segment (root only). */
#define SHM_UNLOCK 12 /* unlock segment (root only). */

/* Segment low boundary address multiple.  */
#ifndef SHMLBA
#ifdef __ARCH_PAGESIZE
#define SHMLBA __ARCH_PAGESIZE
#elif defined(__CC__) && defined(__CRT_HAVE_getpagesize)
#ifndef ____libc_getpagesize_defined
#define ____libc_getpagesize_defined 1
__CREDIRECT(__ATTR_CONST,int,__NOTHROW,__libc_getpagesize,(void),getpagesize,())
#endif /* !____libc_getpagesize_defined */
#define SHMLBA __libc_getpagesize()
#endif
#endif /* !SHMLBA */

#ifdef __CC__
/* Type to count number of attaches.  */
typedef __syscall_ulong_t shmatt_t;

/* Data structure describing a shared memory segment.  */
struct shmid_ds {
	struct ipc_perm     shm_perm;  /* operation permission struct. */
	size_t              shm_segsz; /* size of segment in bytes. */
	__time32_t          shm_atime; /* time of last shmat(). */
#if __SIZEOF_POINTER__ <= 4
	__UINT32_TYPE__   __glibc_reserved1;
#endif /* __SIZEOF_POINTER__ <= 4 */
	__time32_t          shm_dtime; /* time of last shmdt(). */
#if __SIZEOF_POINTER__ <= 4
	__UINT32_TYPE__   __glibc_reserved2;
#endif /* __SIZEOF_POINTER__ <= 4 */
	__time32_t          shm_ctime; /* time of last change by shmctl(). */
#if __SIZEOF_POINTER__ <= 4
	__UINT32_TYPE__   __glibc_reserved3;
#endif /* __SIZEOF_POINTER__ <= 4 */
	__pid_t             shm_cpid;  /* pid of creator. */
	__pid_t             shm_lpid;  /* pid of last shmop. */
	shmatt_t            shm_nattch; /* number of current attaches. */
	__syscall_ulong_t __glibc_reserved4;
	__syscall_ulong_t __glibc_reserved5;
};
#endif /* __CC__ */

#ifdef __USE_MISC
/* ipcs ctl commands */
#define SHM_STAT        13
#define SHM_INFO        14

/* shm_mode upper byte flags. */
#define SHM_DEST      0x0200 /* segment will be destroyed on last detach. */
#define SHM_LOCKED    0x0400 /* segment will not be swapped. */
#define SHM_HUGETLB   0x0800 /* segment is mapped via hugetlb. */
#define SHM_NORESERVE 0x1000 /* don't check for reservations. */


#ifdef __CC__
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
	__syscall_ulong_t shmmax;
	__syscall_ulong_t shmmin;
	__syscall_ulong_t shmmni;
	__syscall_ulong_t shmseg;
	__syscall_ulong_t shmall;
	__syscall_ulong_t __glibc_reserved1;
	__syscall_ulong_t __glibc_reserved2;
	__syscall_ulong_t __glibc_reserved3;
	__syscall_ulong_t __glibc_reserved4;
};

struct shm_info {
	int               used_ids;
	__syscall_ulong_t shm_tot; /* total allocated shm. */
	__syscall_ulong_t shm_rss; /* total resident shm. */
	__syscall_ulong_t shm_swp; /* total swapped shm. */
	__syscall_ulong_t swap_attempts;
	__syscall_ulong_t swap_successes;
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
#endif /* __CC__ */

#endif /* __USE_MISC */

__SYSDECL_END

#endif /* !_BITS_SHM_H */
