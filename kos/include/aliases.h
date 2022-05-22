/* HASH CRC-32:0xa6e62b3 */
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
/* (#) Portability: GNU C Library (/inet/aliases.h) */
/* (#) Portability: libc6         (/include/aliases.h) */
#ifndef _ALIASES_H
#define _ALIASES_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#include <bits/crt/db/aliases.h>
#include <bits/types.h>

#ifdef __USE_GLIBC
#include <sys/types.h>
#endif /* __USE_GLIBC */

#ifdef __CC__
__SYSDECL_BEGIN

/* >> setaliasent(3)
 * Rewind/Open the internal mail alias database file (which is located in `/etc/aliases') */
__CDECLARE_VOID_OPT(,__NOTHROW_RPC_KOS,setaliasent,(void),())
/* >> endaliasent(3)
 * Close the internal mail alias database file (s.a. `setaliasent(3)') */
__CDECLARE_VOID_OPT(,__NOTHROW_NCX,endaliasent,(void),())
/* >> getaliasent(3)
 * Read  the  entry entry  from  the mail  alias  alias database.
 * If the database hadn't already been opened, this function will
 * open  it the same  way that a  call to `setaliasent(3)' would.
 * @return: * :   A pointer to an internal, statically allocated structure
 * @return: NULL: [errno=<unchanged>] Database end has been reached
 * @return: NULL: [errno=ENOENT]      Database end has been reached
 * @return: NULL: [errno=*]           Error */
__CDECLARE_OPT(__ATTR_WUNUSED,struct aliasent *,__NOTHROW_RPC_KOS,getaliasent,(void),())
/* >> getaliasent_r(3)
 * Reentrant variant of `getaliasent(3)' (s.a. similar functions such as `getpwent_r(3)') */
__CDECLARE_OPT(__ATTR_ACCESS_WR(1) __ATTR_ACCESS_WR(4) __ATTR_ACCESS_WRS(2, 3),__errno_t,__NOTHROW_RPC_KOS,getaliasent_r,(struct aliasent *__restrict __result_buf, char *__restrict __buffer, size_t __buflen, struct aliasent **__restrict __result),(__result_buf,__buffer,__buflen,__result))
/* >> getaliasbyname(3)
 * Find a database entry associated with the given `name'
 * @return: * :   A pointer to an internal, statically allocated structure
 * @return: NULL: [errno=ENOENT] No entry matching `name'
 * @return: NULL: [errno=*]      Error */
__CDECLARE_OPT(__ATTR_WUNUSED __ATTR_ACCESS_RO(1),struct aliasent *,__NOTHROW_RPC_KOS,getaliasbyname,(char const *__name),(__name))
/* >> getaliasbyname_r(3)
 * Reentrant variant of `getaliasbyname(3)' (s.a. similar functions such as `getpwnam_r(3)') */
__CDECLARE_OPT(__ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR(2) __ATTR_ACCESS_WR(5) __ATTR_ACCESS_WRS(3, 4),__errno_t,__NOTHROW_RPC_KOS,getaliasbyname_r,(char const *__restrict __name, struct aliasent *__restrict __result_buf, char *__restrict __buffer, size_t __buflen, struct aliasent **__restrict __result),(__name,__result_buf,__buffer,__buflen,__result))

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_ALIASES_H */
