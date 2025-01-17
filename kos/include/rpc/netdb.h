/* HASH CRC-32:0x4e959308 */
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
/* (#) Portability: GNU C Library (/inet/rpc/netdb.h) */
/* (#) Portability: GNU Hurd      (/usr/include/rpc/netdb.h) */
/* (#) Portability: diet libc     (/include/rpc/netdb.h) */
/* (#) Portability: libc6         (/include/rpc/netdb.h) */
/* (#) Portability: mintlib       (/include/rpc/netdb.h) */
/* (#) Portability: uClibc        (/include/rpc/netdb.h) */
#ifndef _RPC_NETDB_H
#define _RPC_NETDB_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <bits/types.h>
#include <bits/crt/db/rpcent.h>

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __size_t_defined
#define __size_t_defined
typedef __size_t size_t;
#endif /* !__size_t_defined */

__CDECLARE_VOID_OPT(,__NOTHROW_RPC_KOS,setrpcent,(int __stayopen),(__stayopen))
__CDECLARE_VOID_OPT(,__NOTHROW_NCX,endrpcent,(void),())
__CDECLARE_OPT(,struct rpcent *,__NOTHROW_RPC_KOS,getrpcbyname,(char const *__name),(__name))
__CDECLARE_OPT(,struct rpcent *,__NOTHROW_RPC_KOS,getrpcbynumber,(int __number),(__number))
__CDECLARE_OPT(,struct rpcent *,__NOTHROW_RPC_KOS,getrpcent,(void),())

#ifdef __USE_MISC
__CDECLARE_OPT(,int,__NOTHROW_RPC_KOS,getrpcbyname_r,(char const *__name, struct rpcent *__result_buf, char *__buffer, size_t __buflen, struct rpcent **__result),(__name,__result_buf,__buffer,__buflen,__result))
__CDECLARE_OPT(,int,__NOTHROW_RPC_KOS,getrpcbynumber_r,(int __number, struct rpcent *__result_buf, char *__buffer, size_t __buflen, struct rpcent **__result),(__number,__result_buf,__buffer,__buflen,__result))
__CDECLARE_OPT(,int,__NOTHROW_RPC_KOS,getrpcent_r,(struct rpcent *__result_buf, char *__buffer, size_t __buflen, struct rpcent **__result),(__result_buf,__buffer,__buflen,__result))
#endif /* __USE_MISC */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_RPC_NETDB_H */
