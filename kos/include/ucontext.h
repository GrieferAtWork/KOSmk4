/* HASH 0x8257cb7d */
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
#ifndef _UCONTEXT_H
#define _UCONTEXT_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <sys/ucontext.h>

__SYSDECL_BEGIN

/* Comments taken from /usr/include/ucontext.h of a linux machine.
 * The following is the copyright notice found in the original file. */
/* Copyright (C) 1997-2016 Free Software Foundation, Inc.
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

#if defined(__CRT_HAVE_getcontext)
/* Get user context and store it in variable pointed to by UCP */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,getcontext,(ucontext_t *__restrict __ucp),(__ucp))
#endif /* getcontext... */

#if defined(__CRT_HAVE_setcontext)
/* Set user context from information of variable pointed to by UCP */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,setcontext,(ucontext_t const *__restrict __ucp),(__ucp))
#endif /* setcontext... */

#if defined(__CRT_HAVE_swapcontext)
/* Save current context in context variable pointed to by OUCP and set
 * context from variable pointed to by UCP */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,swapcontext,(ucontext_t *__restrict __oucp, ucontext_t const *__restrict __ucp),(__oucp,__ucp))
#endif /* swapcontext... */

typedef void (*__makecontext_func_t)(void);

#if defined(__CRT_HAVE_makecontext)
/* Manipulate user context UCP to continue with calling functions FUNC
 * and the ARGC-1 parameters following ARGC when the context is used
 * the next time in `setcontext' or `swapcontext'.
 * We cannot say anything about the parameters FUNC takes; `void'
 * is as good as any other choice */
__LIBC __ATTR_NONNULL((1, 2)) void __NOTHROW_NCX(__VLIBCCALL makecontext)(ucontext_t *__ucp, __makecontext_func_t __func, int ___argc, ...) __CASMNAME_SAME("makecontext");
#endif /* makecontext... */

#endif /* __CC__ */

__SYSDECL_END

#endif /* !_UCONTEXT_H */
