/* HASH CRC-32:0x9177a3a6 */
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
#ifndef _ALIASES_H
#define _ALIASES_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <sys/types.h>

/* Documentation taken from Glibc /usr/include/aliases.h */
/* Copyright (C) 1996-2016 Free Software Foundation, Inc.
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

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("alias_name")
#pragma push_macro("alias_members_len")
#pragma push_macro("alias_members")
#pragma push_macro("alias_local")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef alias_name
#undef alias_members_len
#undef alias_members
#undef alias_local
/* Structure to represent one entry of the alias data base. */
struct aliasent {
	char          *alias_name;
	size_t         alias_members_len;
	char         **alias_members;
	__INT32_TYPE__ alias_local;
};
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("alias_local")
#pragma pop_macro("alias_members")
#pragma pop_macro("alias_members_len")
#pragma pop_macro("alias_name")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

#if defined(__CRT_HAVE_setaliasent)
/* Open alias data base files */
__CDECLARE_VOID(,__NOTHROW_RPC_KOS,setaliasent,(void),())
#endif /* setaliasent... */
#if defined(__CRT_HAVE_endaliasent)
/* Close alias data base files */
__CDECLARE_VOID(,__NOTHROW_NCX,endaliasent,(void),())
#endif /* endaliasent... */
#if defined(__CRT_HAVE_getaliasent)
/* Get the next entry from the alias data base */
__CDECLARE(,struct aliasent *,__NOTHROW_RPC_KOS,getaliasent,(void),())
#endif /* getaliasent... */
#if defined(__CRT_HAVE_getaliasent_r)
/* Get the next entry from the alias data base and put it in RESULT_BUF */
__CDECLARE(__ATTR_NONNULL((1, 2, 4)),int,__NOTHROW_RPC_KOS,getaliasent_r,(struct aliasent *__restrict __result_buf, char *__restrict __buffer, size_t __buflen, struct aliasent **__restrict __result),(__result_buf,__buffer,__buflen,__result))
#endif /* getaliasent_r... */
#if defined(__CRT_HAVE_getaliasbyname)
/* Get alias entry corresponding to NAME */
__CDECLARE(__ATTR_NONNULL((1)),struct aliasent *,__NOTHROW_RPC_KOS,getaliasbyname,(char const *__name),(__name))
#endif /* getaliasbyname... */
#if defined(__CRT_HAVE_getaliasbyname_r)
/* Get alias entry corresponding to NAME and put it in RESULT_BUF */
__CDECLARE(__ATTR_NONNULL((1, 2, 3, 5)),int,__NOTHROW_RPC_KOS,getaliasbyname_r,(char const *__restrict __name, struct aliasent *__restrict __result_buf, char *__restrict __buffer, size_t __buflen, struct aliasent **__restrict __result),(__name,__result_buf,__buffer,__buflen,__result))
#endif /* getaliasbyname_r... */
#endif /* __CC__ */

__SYSDECL_END

#endif /* !_ALIASES_H */
