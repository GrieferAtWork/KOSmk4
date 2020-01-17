/* HASH CRC-32:0xa33cc852 */
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
#ifndef _EXECINFO_H
#define _EXECINFO_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <bits/types.h>

__SYSDECL_BEGIN

/* Documentation taken from Glibc /usr/include/execinfo.h */
/* Copyright (C) 1998-2016 Free Software Foundation, Inc.
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


#ifdef __CC__
#ifdef __CRT_HAVE_backtrace
/* Store up to SIZE return address of the current program state
 * in ARRAY and return the exact number of values stored */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,backtrace,(void **__array, int __size),(__array,__size))
#elif defined(__CRT_HAVE___backtrace)
/* Store up to SIZE return address of the current program state
 * in ARRAY and return the exact number of values stored */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,backtrace,(void **__array, int __size),__backtrace,(__array,__size))
#endif /* backtrace... */
#ifdef __CRT_HAVE_backtrace_symbols
/* Return names of functions from the backtrace list
 * in ARRAY in a newly malloc()ed memory block */
__CDECLARE(__ATTR_NONNULL((1)),char **,__NOTHROW_NCX,backtrace_symbols,(void *const *__array, int __size),(__array,__size))
#elif defined(__CRT_HAVE___backtrace_symbols)
/* Return names of functions from the backtrace list
 * in ARRAY in a newly malloc()ed memory block */
__CREDIRECT(__ATTR_NONNULL((1)),char **,__NOTHROW_NCX,backtrace_symbols,(void *const *__array, int __size),__backtrace_symbols,(__array,__size))
#endif /* backtrace_symbols... */
#ifdef __CRT_HAVE_backtrace_symbols_fd
/* This function is similar to backtrace_symbols()
 * but it writes the result immediately to a file */
__CDECLARE_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,backtrace_symbols_fd,(void *const *__array, int __size, __fd_t __fd),(__array,__size,__fd))
#elif defined(__CRT_HAVE___backtrace_symbols_fd)
/* This function is similar to backtrace_symbols()
 * but it writes the result immediately to a file */
__CREDIRECT_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,backtrace_symbols_fd,(void *const *__array, int __size, __fd_t __fd),__backtrace_symbols_fd,(__array,__size,__fd))
#endif /* backtrace_symbols_fd... */
#endif /* __CC__ */

__SYSDECL_END

#endif /* !_EXECINFO_H */
