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
#ifndef _BITS_IPC_H
#define _BITS_IPC_H 1

#include <__stdinc.h>
#include <features.h>
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

/* Mode bits for `msgget', `semget', and `shmget'. */
#define IPC_CREAT  01000 /* Create key if key does not exist. */
#define IPC_EXCL   02000 /* Fail if key exists. */
#define IPC_NOWAIT 04000 /* Return error on wait. */

/* Control commands for `msgctl', `semctl', and `shmctl'. */
#define IPC_RMID    0 /* Remove identifier. */
#define IPC_SET     1 /* Set `ipc_perm' options. */
#define IPC_STAT    2 /* Get `ipc_perm' options. */
#ifdef __USE_GNU
#define IPC_INFO    3 /* See ipcs. */
#endif /* __USE_GNU */

/* Special key values. */
#define IPC_PRIVATE  (__CCAST(__key_t)0) /* Private key. */


#ifdef __CC__
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("key")
#pragma push_macro("uid")
#pragma push_macro("gid")
#pragma push_macro("cuid")
#pragma push_macro("cgid")
#pragma push_macro("mode")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef key
#undef uid
#undef gid
#undef cuid
#undef cgid
#undef mode

/* Data structure used to pass permission information to IPC operations. */
struct ipc_perm {
#if defined(__COMPILER_HAVE_TRANSPARENT_UNION) && !defined(__key)
	union {
		__key_t        key; /* Key. */
		__key_t      __key; /* Key. */
	};
#else /* __COMPILER_HAVE_TRANSPARENT_UNION && !__key */
#ifndef __key
#define __key          key
#endif /* !__key */
	__key_t            key;    /* Key. */
#endif /* !__COMPILER_HAVE_TRANSPARENT_UNION || __key */
	__uid_t            uid;    /* Owner's user ID. */
	__gid_t            gid;    /* Owner's group ID. */
	__uid_t            cuid;   /* Creator's user ID. */
	__gid_t            cgid;   /* Creator's group ID. */
	unsigned short int mode;   /* Read/write permission. */
	unsigned short int __pad1;
	unsigned short int __seq;  /* Sequence number. */
	unsigned short int __pad2;
	__syscall_ulong_t  __glibc_reserved1;
	__syscall_ulong_t  __glibc_reserved2;
};

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("mode")
#pragma pop_macro("cgid")
#pragma pop_macro("cuid")
#pragma pop_macro("gid")
#pragma pop_macro("uid")
#pragma pop_macro("key")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#endif /* __CC__ */

__SYSDECL_END

#endif /* !_BITS_IPC_H */
