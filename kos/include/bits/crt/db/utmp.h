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
/*!included_by <utmp.h>*/
#ifndef _BITS_CRT_DB_UTMP_H
#define _BITS_CRT_DB_UTMP_H 1

#include <__stdinc.h>

#include <hybrid/typecore.h>

#include <bits/types.h>
#include <bits/os/timeval.h>


/* The `struct utmp' type, describing entries in the utmp file.  GNU version.
   Copyright (C) 1993-2016 Free Software Foundation, Inc.
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

#define UT_LINESIZE    32
#define UT_NAMESIZE    32
#define UT_HOSTSIZE    256

#ifdef __CC__
__DECL_BEGIN

/* The structure describing an entry in the database of previous logins. */
struct lastlog {
	__time32_t ll_time;
	char       ll_line[UT_LINESIZE];
	char       ll_host[UT_HOSTSIZE];
};

/* The structure describing the status of a terminated process.
 * This type is used in `struct utmp' below. */
struct exit_status {
	__INT16_TYPE__ e_termination; /* Process termination status. */
	__INT16_TYPE__ e_exit;        /* Process exit status. */
};

/* The structure describing an entry in the user accounting database. */
struct utmp {
	__INT16_TYPE__     ut_type;              /* Type of login. */
	__pid_t            ut_pid;               /* Process ID of login process. */
	char               ut_line[UT_LINESIZE]; /* Device name. */
	char               ut_id[4];             /* Inittab ID. */
#ifdef __COMPILER_HAVE_TRANSPARENT_UNION
	union {
		char           ut_name[UT_NAMESIZE]; /* Username. */
		char           ut_user[UT_NAMESIZE]; /* Username. */
	};
#else /* __COMPILER_HAVE_TRANSPARENT_UNION */
#define ut_name        ut_user               /* Username. */
	char               ut_user[UT_NAMESIZE]; /* Username. */
#endif /* !__COMPILER_HAVE_TRANSPARENT_UNION */
	char               ut_host[UT_HOSTSIZE]; /* Hostname for remote login. */
	struct exit_status ut_exit;        /* Exit status of a process marked as DEAD_PROCESS. */
	/* The ut_session and ut_tv fields must be the same size when compiled
	 * 32- and 64-bit.  This allows  data files  and shared  memory to  be
	 * shared between 32- and 64-bit applications. */
	__LONG32_TYPE__        ut_session; /* Session ID, used for windowing. */
	union {
		__time32_t         ut_time;    /* Time entry was made. */
		__time32_t         ut_xtime;   /* Time entry was made. */
		struct __timeval32 ut_tv;      /* Time entry was made. */
	};
	union {
		__int32_t      ut_addr;           /* Internet address of remote host. */
		__int32_t      ut_addr_v6[4];     /* Internet address of remote host. */
	};
	char __glibc_reserved[20];         /* Reserved for future use. */
};

__DECL_END
#endif /* __CC__ */

/* Values for the `ut_type' field of a `struct utmp'. */
#define EMPTY           0 /* No valid user accounting information. */
#define RUN_LVL         1 /* The system's runlevel. */
#define BOOT_TIME       2 /* Time of system boot. */
#define NEW_TIME        3 /* Time after system clock changed. */
#define OLD_TIME        4 /* Time when system clock changed. */
#define INIT_PROCESS    5 /* Process spawned by the init process. */
#define LOGIN_PROCESS   6 /* Session leader of a logged in user. */
#define USER_PROCESS    7 /* Normal process. */
#define DEAD_PROCESS    8 /* Terminated process. */
#define ACCOUNTING      9

/* Old Linux name for the EMPTY type. */
#define UT_UNKNOWN      EMPTY

/* Tell the user that we  have a modern system  with
 * UT_HOST, UT_PID, UT_TYPE, UT_ID and UT_TV fields. */
#define _HAVE_UT_TYPE   1
#define _HAVE_UT_PID    1
#define _HAVE_UT_ID     1
#define _HAVE_UT_TV     1
#define _HAVE_UT_HOST   1

#endif /* !_BITS_CRT_DB_UTMP_H */
