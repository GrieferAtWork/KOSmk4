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
%[default_impl_section(".text.crt.fs.statfs.statfs")]

%{
#include <features.h>
#include <sys/types.h>
#include <bits/statfs.h>

__SYSDECL_BEGIN

/* Documentation (partially) derived from Glibc /usr/include/i386-linux-gnu/sys/statfs.h */
/* Definitions for getting information about a filesystem.
   Copyright (C) 1996-2016 Free Software Foundation, Inc.
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

}

@@Return information about the filesystem on which FILE resides
[[no_crt_self_import, export_as("__statfs")]]
[[if(!defined(__USE_FILE_OFFSET64)), preferred_alias("statfs", "__statfs")]]
[[if(defined(__USE_FILE_OFFSET64)), preferred_alias("statfs64")]]
int statfs([[nonnull]] char const *file, [[nonnull]] struct statfs *buf);

@@Return information about the filesystem containing the file FILDES refers to
[[no_crt_self_import]]
[[if(!defined(__USE_FILE_OFFSET64)), preferred_alias("fstatfs")]]
[[if(defined(__USE_FILE_OFFSET64)), preferred_alias("fstatfs64")]]
int fstatfs($fd_t filedes, [[nonnull]] struct statfs *buf);

%
%#ifdef __USE_LARGEFILE64

%#ifndef statfs64
[[doc_alias("statfs"), statfs64_variant_of(statfs)]]
int statfs64([[nonnull]] const char *file, [[nonnull]] struct statfs64 *buf);
%#endif /* !statfs64 */

[[doc_alias("fstatfs"), statfs64_variant_of(fstatfs)]]
int fstatfs64($fd_t filedes, [[nonnull]] struct statfs64 *buf);
%#endif /* __USE_LARGEFILE64 */


%{
#endif /* __CC__ */

__SYSDECL_END

}
