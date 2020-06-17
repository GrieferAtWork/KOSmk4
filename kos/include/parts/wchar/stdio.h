/* HASH CRC-32:0x26c7b8b8 */
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
#ifndef _PARTS_WCHAR_STDIO_H
#define _PARTS_WCHAR_STDIO_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#ifndef _STDIO_H
#include <stdio.h>
#endif /* !_STDIO_H */
#ifndef _WCHAR_H
#include <wchar.h>
#endif /* !_WCHAR_H */
#include <bits/types.h>

__SYSDECL_BEGIN

#ifdef __CC__

#ifndef __wremove_defined
#define __wremove_defined 1
#ifdef __CRT_HAVE_wremove
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,wremove,(wchar_t const *__filename),(__filename))
#elif defined(__CRT_HAVE__wremove)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,wremove,(wchar_t const *__filename),_wremove,(__filename))
#else /* ... */
#undef __wremove_defined
#endif /* !... */
#endif /* !__wremove_defined */
#ifdef __CRT_HAVE_wfopen
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__FILE *,__NOTHROW_NCX,wfopen,(wchar_t const *__filename, wchar_t const *__mode),(__filename,__mode))
#elif defined(__CRT_HAVE__wfopen)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__FILE *,__NOTHROW_NCX,wfopen,(wchar_t const *__filename, wchar_t const *__mode),_wfopen,(__filename,__mode))
#endif /* ... */
#ifdef __CRT_HAVE_wfreopen
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__FILE *,__NOTHROW_NCX,wfreopen,(wchar_t const *__filename, wchar_t const *__mode, __FILE *__stream),(__filename,__mode,__stream))
#elif defined(__CRT_HAVE__wfreopen)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__FILE *,__NOTHROW_NCX,wfreopen,(wchar_t const *__filename, wchar_t const *__mode, __FILE *__stream),_wfreopen,(__filename,__mode,__stream))
#endif /* ... */
#ifndef __wpopen_defined
#define __wpopen_defined 1
#ifdef __CRT_HAVE_wpopen
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__FILE *,__NOTHROW_NCX,wpopen,(wchar_t const *__command, wchar_t const *__mode),(__command,__mode))
#elif defined(__CRT_HAVE__wpopen)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__FILE *,__NOTHROW_NCX,wpopen,(wchar_t const *__command, wchar_t const *__mode),_wpopen,(__command,__mode))
#else /* ... */
#undef __wpopen_defined
#endif /* !... */
#endif /* !__wpopen_defined */

#endif /* __CC__ */

__SYSDECL_END

#endif /* !_PARTS_WCHAR_STDIO_H */
