/* HASH CRC-32:0x66f67d99 */
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
/* (#) Portability: MinGW        (/mingw-w64-headers/crt/new.h) */
/* (#) Portability: Windows Kits (/ucrt/new.h) */
/*!always_includes <crtdefs.h>*/
#ifndef _NEW_H
#define _NEW_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <crtdefs.h>

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef ___PNH_defined
#define ___PNH_defined
typedef int (__CRTDECL *_PNH)(size_t);
#endif /* !___PNH_defined */
#ifdef __CRT_HAVE__query_new_handler
__LIBC _PNH __NOTHROW_NCX(__LIBDCALL _query_new_handler)(void) __CASMNAME_SAME("_query_new_handler");
#endif /* __CRT_HAVE__query_new_handler */
#ifdef __CRT_HAVE__set_new_handler
__LIBC _PNH __NOTHROW_NCX(__LIBDCALL _set_new_handler)(_PNH __newhandler) __CASMNAME_SAME("_set_new_handler");
#endif /* __CRT_HAVE__set_new_handler */
#ifdef __CRT_HAVE__query_new_mode
__LIBC int __NOTHROW_NCX(__LIBDCALL _query_new_mode)(void) __CASMNAME_SAME("_query_new_mode");
#endif /* __CRT_HAVE__query_new_mode */
#ifdef __CRT_HAVE__set_new_mode
__LIBC int __NOTHROW_NCX(__LIBDCALL _set_new_mode)(int __newmode) __CASMNAME_SAME("_set_new_mode");
#endif /* __CRT_HAVE__set_new_mode */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_NEW_H */
