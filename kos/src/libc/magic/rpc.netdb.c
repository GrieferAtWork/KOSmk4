/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
%(c_prefix){
/* (#) Portability: GNU C Library (/inet/rpc/netdb.h) */
/* (#) Portability: GNU Hurd      (/usr/include/rpc/netdb.h) */
/* (#) Portability: diet libc     (/include/rpc/netdb.h) */
/* (#) Portability: libc6         (/include/rpc/netdb.h) */
/* (#) Portability: mintlib       (/include/rpc/netdb.h) */
/* (#) Portability: uClibc        (/include/rpc/netdb.h) */
}

%[define_replacement(fd_t = __fd_t)]
%[default:section(".text.crt{|.dos}.net.rpc")]

%[define_decl_include("<bits/crt/db/rpcent.h>": ["struct rpcent"])]


%[insert:prefix(
#include <bits/types.h>
)]%[insert:prefix(
#include <bits/crt/db/rpcent.h>
)]%{

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __size_t_defined
#define __size_t_defined
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
[[cp_kos, decl_include("<bits/crt/db/rpcent.h>", "<hybrid/typecore.h>")]]
[[export_as("__getrpcbyname_r")]] /* From Glibc 2.0.4 */
int getrpcbyname_r(char const *name, struct rpcent *result_buf,
                   char *buffer, size_t buflen,
                   struct rpcent **result); /* XXX: [[nonnull]] annotations? */
[[cp_kos, decl_include("<bits/crt/db/rpcent.h>", "<hybrid/typecore.h>")]]
[[export_as("__getrpcbynumber_r")]] /* From Glibc 2.0.4 */
int getrpcbynumber_r(int number, struct rpcent *result_buf,
                     char *buffer, size_t buflen,
                     struct rpcent **result); /* XXX: [[nonnull]] annotations? */
[[cp_kos, decl_include("<bits/crt/db/rpcent.h>", "<hybrid/typecore.h>")]]
[[export_as("__getrpcent_r")]] /* From Glibc 2.0.4 */
int getrpcent_r(struct rpcent *result_buf,
                char *buffer, size_t buflen,
                struct rpcent **result); /* XXX: [[nonnull]] annotations? */
%#endif /* __USE_MISC */


%{

__SYSDECL_END
#endif /* __CC__ */

}
