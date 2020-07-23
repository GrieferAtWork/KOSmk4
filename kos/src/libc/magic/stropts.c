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

%[define_replacement(uid_t = __uid_t)]
%[default:section(".text.crt{|.dos}.io.stropts")]

%{
#include <features.h>

#include <bits/types.h>
#include <bits/xtitypes.h>
#include <bits/stropts.h>

/* Documentation taken from Glibc /usr/include/stropts.h */
/* Copyright (C) 1998-2016 Free Software Foundation, Inc.
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

#ifdef __CC__

#ifndef __gid_t_defined
#define __gid_t_defined 1
typedef __gid_t gid_t;
#endif /* !__gid_t_defined */

#ifndef __uid_t_defined
#define __uid_t_defined 1
typedef __uid_t uid_t;
#endif /* !__uid_t_defined */

typedef __t_scalar_t  t_scalar_t;
typedef __t_uscalar_t t_uscalar_t;

}

@@Test whether FILDES is associated with a STREAM-based file
[[nothrow, decl_include("<bits/types.h>")]]
int isastream($fd_t fildes);

@@Receive next message from a STREAMS file
[[cp, decl_include("<bits/types.h>", "<bits/stropts.h>")]]
int getmsg($fd_t fildes,
           struct strbuf *__restrict ctlptr,
           struct strbuf *__restrict dataptr,
           __STDC_INT_AS_UINT_T *__restrict flagsp);

@@Receive next message from a STREAMS file, with *FLAGSP allowing to control which message.
[[cp, decl_include("<bits/types.h>", "<bits/stropts.h>")]]
int getpmsg($fd_t fildes,
            struct strbuf *__restrict ctlptr,
            struct strbuf *__restrict dataptr,
            int *__restrict bandp,
            __STDC_INT_AS_UINT_T *__restrict flagsp);

%[insert:extern(ioctl)]

@@Send a message on a STREAM
[[cp, decl_include("<features.h>", "<bits/types.h>", "<bits/stropts.h>")]]
int putmsg($fd_t fildes,
           struct strbuf const *ctlptr,
           struct strbuf const *dataptr,
           __STDC_INT_AS_UINT_T flags);

@@Send a message on a STREAM to the BAND
[[cp, decl_include("<features.h>", "<bits/types.h>", "<bits/stropts.h>")]]
int putpmsg($fd_t fildes,
            struct strbuf const *ctlptr,
            struct strbuf const *dataptr,
            __STDC_INT_AS_UINT_T band,
            __STDC_INT_AS_UINT_T flags);

@@Attach a STREAMS-based file descriptor FILDES to a file PATH in the file system name space
[[guard, cp_kos, decl_include("<bits/types.h>")]]
int fattach($fd_t fildes, [[nonnull]] char const *__restrict path);

@@Detach a name PATH from a STREAMS-based file descriptor
[[guard, cp_kos]]
int fdetach([[nonnull]] char const *__restrict path);


%{
#endif /* __CC__ */

__SYSDECL_END

}