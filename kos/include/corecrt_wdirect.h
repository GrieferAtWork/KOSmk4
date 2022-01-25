/* HASH CRC-32:0x989ad3e5 */
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
/* (#) Portability: Windows Kits (/ucrt/corecrt_wdirect.h) */
#ifndef _CORECRT_WDIRECT_H
#define _CORECRT_WDIRECT_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <hybrid/typecore.h>
#include <bits/types.h>

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __size_t_defined
#define __size_t_defined
typedef __SIZE_TYPE__ size_t;
#endif /* !__size_t_defined */

#ifndef __ernno_t_defined
#define __ernno_t_defined
typedef __errno_t errno_t;
#endif /* !__ernno_t_defined */

#ifndef __wchar_t_defined
#define __wchar_t_defined
typedef __WCHAR_TYPE__ wchar_t;
#endif /* !__wchar_t_defined */

#ifdef __CRT_HAVE_wgetcwd
__CREDIRECT(,wchar_t *,__NOTHROW_RPC,_wgetcwd,(wchar_t *__buf, size_t __bufsize),wgetcwd,(__buf,__bufsize))
#elif defined(__CRT_HAVE__wgetcwd)
__CDECLARE(,wchar_t *,__NOTHROW_RPC,_wgetcwd,(wchar_t *__buf, size_t __bufsize),(__buf,__bufsize))
#elif (defined(__CRT_HAVE_getcwd) || defined(__CRT_HAVE__getcwd)) && (defined(__CRT_HAVE_convert_mbstowcs) || defined(__CRT_HAVE_convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))))
#include <libc/local/parts.wchar.unistd/wgetcwd.h>
__FORCELOCAL __ATTR_ARTIFICIAL wchar_t *__NOTHROW_RPC(__LIBCCALL _wgetcwd)(wchar_t *__buf, size_t __bufsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wgetcwd))(__buf, __bufsize); }
#endif /* ... */

__SYSDECL_END
#endif /* __CC__ */

#ifdef __USE_UTF
#if defined(_UCHAR_H) && !defined(_PARTS_UCHAR_DIRECT_H)
#include <parts/uchar/direct.h>
#endif /* _UCHAR_H && !_PARTS_UCHAR_DIRECT_H */
#endif /* __USE_UTF */

#endif /* !_CORECRT_WDIRECT_H */
