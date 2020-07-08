/* HASH CRC-32:0xd4064dc0 */
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
#ifndef _LIBGEN_H
#define _LIBGEN_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

__SYSDECL_BEGIN

#ifdef __CC__

#ifdef __CRT_HAVE_dirname
/* Return directory part of PATH or "." if none is available */
__CDECLARE(__ATTR_RETNONNULL,char *,__NOTHROW_NCX,dirname,(char *__path),(__path))
#else /* __CRT_HAVE_dirname */
#include <local/libgen/dirname.h>
/* Return directory part of PATH or "." if none is available */
__NAMESPACE_LOCAL_USING_OR_IMPL(dirname, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL char *__NOTHROW_NCX(__LIBCCALL dirname)(char *__path) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(dirname))(__path); })
#endif /* !__CRT_HAVE_dirname */
#ifdef __CRT_HAVE___xpg_basename
/* Return final component of PATH.
 * This is the weird XPG version of this function. It sometimes will
 * modify its argument. Therefore we normally use the GNU version (in
 * <string.h>) and only if this header is included make the XPG
 * version available under the real name */
__CDECLARE(__ATTR_RETNONNULL,char *,__NOTHROW_NCX,__xpg_basename,(char *__filename),(__filename))
#else /* __CRT_HAVE___xpg_basename */
#include <local/libgen/__xpg_basename.h>
/* Return final component of PATH.
 * This is the weird XPG version of this function. It sometimes will
 * modify its argument. Therefore we normally use the GNU version (in
 * <string.h>) and only if this header is included make the XPG
 * version available under the real name */
__NAMESPACE_LOCAL_USING_OR_IMPL(__xpg_basename, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL char *__NOTHROW_NCX(__LIBCCALL __xpg_basename)(char *__filename) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__xpg_basename))(__filename); })
#endif /* !__CRT_HAVE___xpg_basename */
#define basename(path) __xpg_basename(path)

#endif /* __CC__ */

__SYSDECL_END

#endif /* !_LIBGEN_H */
