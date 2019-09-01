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

%[define_replacement(fd_t = __fd_t)]
%[default_impl_section(.text.crt.database.utmpx)]

%{
#include <features.h>
#include <sys/time.h>
#include <bits/utmpx.h>
#include <bits/types.h>

/* Documentation taken from Glibc /usr/include/utmp.h */
/* Copyright (C) 1993-2016 Free Software Foundation, Inc.
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

__SYSDECL_BEGIN

#ifdef __USE_GNU
/* Compatibility names for the strings of the canonical file names.  */
#define UTMPX_FILE      _PATH_UTMPX
#define UTMPX_FILENAME  _PATH_UTMPX
#define WTMPX_FILE      _PATH_WTMPX
#define WTMPX_FILENAME  _PATH_WTMPX
#endif /* __USE_GNU */

#ifdef __CC__

#ifdef __USE_GNU
struct utmp;
#endif /* __USE_GNU */

#ifndef __pid_t_defined
#define __pid_t_defined 1
typedef __pid_t pid_t;
#endif /* !__pid_t_defined */

}

@@Open user accounting database
[cp] setutxent:();

@@Close user accounting database
[cp_nokos] endutxent:();

@@Get the next entry from the user accounting database
[cp] getutxent:() -> struct utmpx *;

@@Get the user accounting database entry corresponding to ID
[cp] getutxid:(struct utmpx const *id) -> struct utmpx *;

@@Get the user accounting database entry corresponding to LINE
[cp] getutxline:(struct utmpx const *line) -> struct utmpx *;

@@Write the entry UTMPX into the user accounting database
[cp] pututxline:(struct utmpx const *utmpx) -> struct utmpx *;

%
%#ifdef __USE_GNU
@@Change name of the utmpx file to be examined.
@@This function is not part of POSIX and therefore no official cancellation point
[cp] utmpxname:(char const *file) -> int;

@@Append entry UTMP to the wtmpx-like file WTMPX_FILE.
@@This function is not part of POSIX and therefore no official cancellation point
[cp] updwtmpx:(char const *wtmpx_file, struct utmpx const *utmpx);

@@Copy the information in UTMPX to UTMP.
@@This function is not part of POSIX and therefore no official cancellation point
[cp] getutmp:(struct utmpx const *utmpx, struct utmp *utmp);

@@Copy the information in UTMP to UTMPX.
@@This function is not part of POSIX and therefore no official cancellation point
[cp] getutmpx:(struct utmp const *utmp, struct utmpx *utmpx);
%#endif /* __USE_GNU */


%{
#endif /* __CC__ */

__SYSDECL_END

}