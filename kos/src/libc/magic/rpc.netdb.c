/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
%(c_prefix){
/* (#) Portability: GNU C Library (/inet/rpc/netdb.h) */
/* (#) Portability: diet libc     (/include/rpc/netdb.h) */
/* (#) Portability: libc6         (/include/rpc/netdb.h) */
/* (#) Portability: uClibc        (/include/rpc/netdb.h) */
}

%[define_replacement(fd_t = __fd_t)]
%[default:section(".text.crt{|.dos}.net.rpc")]

%{
#include <bits/types.h>
#include <bits/crt/db/rpcent.h>

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

#ifndef __size_t_defined
#define __size_t_defined 1
typedef __size_t size_t;
#endif /* !__size_t_defined */

}

[[cp_kos]]
void setrpcent(int stayopen);

void endrpcent();

[[cp_kos, decl_include("<bits/crt/db/rpcent.h>")]]
struct rpcent *getrpcbyname(char const *name);

[[cp_kos, decl_include("<bits/crt/db/rpcent.h>")]]
struct rpcent *getrpcbynumber(int number);

[[cp_kos, decl_include("<bits/crt/db/rpcent.h>")]]
struct rpcent *getrpcent();


%
%#ifdef __USE_MISC
[[cp_kos, decl_include("<bits/crt/db/rpcent.h>")]]
int getrpcbyname_r(char const *name, struct rpcent *result_buf,
                   char *buffer, size_t buflen,
                   struct rpcent **result); /* XXX: [[nonnull]] annotations? */
[[cp_kos, decl_include("<bits/crt/db/rpcent.h>")]]
int getrpcbynumber_r(int number, struct rpcent *result_buf,
                     char *buffer, size_t buflen,
                     struct rpcent **result); /* XXX: [[nonnull]] annotations? */
[[cp_kos, decl_include("<bits/crt/db/rpcent.h>")]]
int getrpcent_r(struct rpcent *result_buf,
                char *buffer, size_t buflen,
                struct rpcent **result); /* XXX: [[nonnull]] annotations? */
%#endif /* __USE_MISC */


%{

#endif /* __CC__ */

__SYSDECL_END

}
