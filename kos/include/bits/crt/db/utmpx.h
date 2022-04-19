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
#ifndef _BITS_CRT_DB_UTMPX_H
#define _BITS_CRT_DB_UTMPX_H 1

#include <__stdinc.h>

#include <hybrid/typecore.h>

#include <bits/os/timeval.h>
#include <bits/types.h>

/* Documentation taken from Glibc /usr/include/i386-linux-gnu/bits/utmpx.h */
/* Structures and definitions for the user accounting database.  GNU version.
   Copyright (C) 1997-2016 Free Software Foundation, Inc.
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

#ifdef __USE_GNU
#include <paths.h>
#if !defined(_PATH_UTMPX) && defined(_PATH_UTMP)
#define _PATH_UTMPX _PATH_UTMP
#endif /* !_PATH_UTMPX && _PATH_UTMP */
#if !defined(_PATH_WTMPX) && defined(_PATH_WTMP)
#define _PATH_WTMPX _PATH_WTMP
#endif /* !_PATH_WTMPX && _PATH_WTMP */
#endif /* __USE_GNU */

#define __UT_LINESIZE  32
#define __UT_NAMESIZE  32
#define __UT_HOSTSIZE  256

/* Values for the `ut_type' field of a `struct utmpx'.  */
#define EMPTY         0 /* No valid user accounting information. */
#ifdef __USE_GNU
#define RUN_LVL       1 /* The system's runlevel. */
#endif /* __USE_GNU */
#define BOOT_TIME     2 /* Time of system boot. */
#define NEW_TIME      3 /* Time after system clock changed. */
#define OLD_TIME      4 /* Time when system clock changed. */
#define INIT_PROCESS  5 /* Process spawned by the init process. */
#define LOGIN_PROCESS 6 /* Session leader of a logged in user. */
#define USER_PROCESS  7 /* Normal process. */
#define DEAD_PROCESS  8 /* Terminated process. */

#ifdef __USE_GNU
#define ACCOUNTING 9 /* System accounting. */
#endif /* __USE_GNU */

#ifdef __CC__
__DECL_BEGIN

/* The structure describing the status of a terminated process.
 * This type is used in `struct utmpx' below. */
struct __exit_status {
#ifdef __USE_GNU
	__INT16_TYPE__   e_termination; /* Process termination status. */
	__INT16_TYPE__   e_exit;        /* Process exit status. */
#else /* __USE_GNU */
	__INT16_TYPE__ __e_termination; /* Process termination status. */
	__INT16_TYPE__ __e_exit;        /* Process exit status. */
#endif /* !__USE_GNU */
};

/* The structure describing an entry in the user accounting database. */
struct utmpx {
	__INT16_TYPE__       ut_type;                /* Type of login. */
	__INT16_TYPE__     __ut_pad;                 /* Hidden padding made visible... */
	__pid_t              ut_pid;                 /* Process ID of login process. */
	char                 ut_line[__UT_LINESIZE]; /* Devicename. */
	char                 ut_id[4];               /* Inittab ID. */
#ifdef __COMPILER_HAVE_TRANSPARENT_UNION
	union {
		char             ut_name[__UT_NAMESIZE]; /* Username. */
		char             ut_user[__UT_NAMESIZE]; /* Username. */
	};
#else /* __COMPILER_HAVE_TRANSPARENT_UNION */
#define ut_name          ut_user                 /* Username. */
	char                 ut_user[__UT_NAMESIZE]; /* Username. */
#endif /* !__COMPILER_HAVE_TRANSPARENT_UNION */
	char                 ut_host[__UT_HOSTSIZE]; /* Hostname for remote login. */
	struct __exit_status ut_exit;                /* Exit status of a process marked as DEAD_PROCESS. */
	/* The fields ut_session and ut_tv must be the same size when compiled
	 * 32- and  64-bit. This allows  files and shared  memory to be shared
	 * between 32- and 64-bit applications. */
	__LONG32_TYPE__      ut_session;             /* Session ID, used for windowing. */
	struct __timeval32   ut_tv;                  /* Time entry was made. */
	__int32_t            ut_addr_v6[4];          /* Internet address of remote host. */
	char               __glibc_reserved[20];     /* Reserved for future use. */
};

__DECL_END
#endif /* __CC__ */

#endif /* !_BITS_CRT_DB_UTMPX_H */
