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
#ifndef _BITS_CRT_DB_GROUP_H
#define _BITS_CRT_DB_GROUP_H 1

#include <__stdinc.h>

#include <hybrid/typecore.h>

#ifdef __CC__
__DECL_BEGIN

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
	__SIZE_TYPE__  alias_members_len;
	char         **alias_members;
	__INT32_TYPE__ alias_local;
};

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("alias_local")
#pragma pop_macro("alias_members")
#pragma pop_macro("alias_members_len")
#pragma pop_macro("alias_name")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */


__DECL_END
#endif /* __CC__ */

#endif /* !_BITS_CRT_DB_GROUP_H */
