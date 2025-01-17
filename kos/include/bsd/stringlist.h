/* HASH CRC-32:0xcae40c6b */
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
/* (#) Portability: libbsd (/include/bsd/stringlist.h) */
#ifndef _BSD_STRINGLIST_H
#define _BSD_STRINGLIST_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <stringlist.h>

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __sl_delete_defined
#define __sl_delete_defined
#ifdef __CRT_HAVE_sl_delete
/* >> sl_delete(3) [NetBSD]
 * Remove an entry `name' from `sl'
 * When `freeit' is non-zero, a removed string is deallocated using `free(3)'
 * @return: 0:  Successfully removed a string equal to `name'
 * @return: -1: No string equal to `name' was found in `sl' */
__CDECLARE(__ATTR_WUNUSED __ATTR_IN(2) __ATTR_INOUT(1),int,__NOTHROW_NCX,sl_delete,(struct _stringlist *__sl, char const *__name, int __freeit),(__sl,__name,__freeit))
#else /* __CRT_HAVE_sl_delete */
#include <libc/local/stringlist/sl_delete.h>
/* >> sl_delete(3) [NetBSD]
 * Remove an entry `name' from `sl'
 * When `freeit' is non-zero, a removed string is deallocated using `free(3)'
 * @return: 0:  Successfully removed a string equal to `name'
 * @return: -1: No string equal to `name' was found in `sl' */
__NAMESPACE_LOCAL_USING_OR_IMPL(sl_delete, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(2) __ATTR_INOUT(1) int __NOTHROW_NCX(__LIBCCALL sl_delete)(struct _stringlist *__sl, char const *__name, int __freeit) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sl_delete))(__sl, __name, __freeit); })
#endif /* !__CRT_HAVE_sl_delete */
#endif /* !__sl_delete_defined */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_BSD_STRINGLIST_H */
