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

%{
#include <bits/types.h>

__SYSDECL_BEGIN

/* Comments and definitions are derived from GNU C /usr/include/i386-linux-gnu/sys/times.h: */
/* Copyright (C) 1991-2016 Free Software Foundation, Inc.
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

#ifndef __clock_t_defined
#define __clock_t_defined 1
typedef __typedef_clock_t clock_t;
#endif /* !__clock_t_defined */

/* Structure describing CPU time used by a process and its children.  */
struct tms {
	clock_t tms_utime;  /* User CPU time. */
	clock_t tms_stime;  /* System CPU time. */
	clock_t tms_cutime; /* User CPU time of dead children. */
	clock_t tms_cstime; /* System CPU time of dead children. */
};

}

@@Store the CPU time used by this process and all its
@@dead children (and their dead children) in BUFFER.
@@Return the elapsed real time, or (clock_t) -1 for errors.
@@All times are in CLK_TCKths of a second
clock_t times(struct tms *buffer);

%{
#endif /* __CC__ */

__SYSDECL_END

}