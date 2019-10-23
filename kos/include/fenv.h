/* HASH CRC-32:0x8b44019a */
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
#ifndef _FENV_H
#define _FENV_H 1

#ifdef _CXX_STDONLY_CFENV
#ifdef __CXX_SYSTEM_HEADER
#undef _FENV_H /* Allow the C-header to be re-included to import all std::-symbols into the global namespace. */
#else /* __CXX_SYSTEM_HEADER */
/* Import all symbols into the global namespace when re-including "fenv.h" after "cfenv" */
#ifndef __NO_FPU
#ifndef ___fenv_t_defined
#define ___fenv_t_defined 1
__NAMESPACE_STD_USING(fenv_t)
#endif /* !___fenv_t_defined */
#ifndef __fexcept_t_defined
#define __fexcept_t_defined 1
__NAMESPACE_STD_USING(fexcept_t)
#endif /* !__fexcept_t_defined */
#if !defined(__feclearexcept_defined) && defined(__std_feclearexcept_defined)
#define __feclearexcept_defined 1
__NAMESPACE_STD_USING(feclearexcept)
#endif /* !__feclearexcept_defined && !__std_feclearexcept_defined */
#if !defined(__fegetexceptflag_defined) && defined(__std_fegetexceptflag_defined)
#define __fegetexceptflag_defined 1
__NAMESPACE_STD_USING(fegetexceptflag)
#endif /* !__fegetexceptflag_defined && !__std_fegetexceptflag_defined */
#if !defined(__feraiseexcept_defined) && defined(__std_feraiseexcept_defined)
#define __feraiseexcept_defined 1
__NAMESPACE_STD_USING(feraiseexcept)
#endif /* !__feraiseexcept_defined && !__std_feraiseexcept_defined */
#if !defined(__fesetexceptflag_defined) && defined(__std_fesetexceptflag_defined)
#define __fesetexceptflag_defined 1
__NAMESPACE_STD_USING(fesetexceptflag)
#endif /* !__fesetexceptflag_defined && !__std_fesetexceptflag_defined */
#if !defined(__fetestexcept_defined) && defined(__std_fetestexcept_defined)
#define __fetestexcept_defined 1
__NAMESPACE_STD_USING(fetestexcept)
#endif /* !__fetestexcept_defined && !__std_fetestexcept_defined */
#if !defined(__fegetround_defined) && defined(__std_fegetround_defined)
#define __fegetround_defined 1
__NAMESPACE_STD_USING(fegetround)
#endif /* !__fegetround_defined && !__std_fegetround_defined */
#if !defined(__fesetround_defined) && defined(__std_fesetround_defined)
#define __fesetround_defined 1
__NAMESPACE_STD_USING(fesetround)
#endif /* !__fesetround_defined && !__std_fesetround_defined */
#if !defined(__fegetenv_defined) && defined(__std_fegetenv_defined)
#define __fegetenv_defined 1
__NAMESPACE_STD_USING(fegetenv)
#endif /* !__fegetenv_defined && !__std_fegetenv_defined */
#if !defined(__feholdexcept_defined) && defined(__std_feholdexcept_defined)
#define __feholdexcept_defined 1
__NAMESPACE_STD_USING(feholdexcept)
#endif /* !__feholdexcept_defined && !__std_feholdexcept_defined */
#if !defined(__fesetenv_defined) && defined(__std_fesetenv_defined)
#define __fesetenv_defined 1
__NAMESPACE_STD_USING(fesetenv)
#endif /* !__fesetenv_defined && !__std_fesetenv_defined */
#if !defined(__feupdateenv_defined) && defined(__std_feupdateenv_defined)
#define __feupdateenv_defined 1
__NAMESPACE_STD_USING(feupdateenv)
#endif /* !__feupdateenv_defined && !__std_feupdateenv_defined */
#endif /* !__NO_FPU */
#undef _CXX_STDONLY_CFENV
#endif /* !__CXX_SYSTEM_HEADER */
#else /* _CXX_STDONLY_CFENV */
#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#ifndef __NO_FPU
#include <features.h>

#include <bits/fenv.h>

/* Documentation comments are taken from glibc /usr/include/fenv.h */
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

__SYSDECL_BEGIN

#ifdef __CC__

__NAMESPACE_STD_BEGIN
#ifndef __std_fenv_t_defined
#define __std_fenv_t_defined 1
typedef struct __fenv_struct fenv_t;
#endif /* !__std_fenv_t_defined */
#ifndef __std_fexcept_t_defined
#define __std_fexcept_t_defined 1
typedef __fexcept_t fexcept_t;
#endif /* !__std_fexcept_t_defined */
__NAMESPACE_STD_END

#ifndef __CXX_SYSTEM_HEADER
#ifndef ___fenv_t_defined
#define ___fenv_t_defined 1
__NAMESPACE_STD_USING(fenv_t)
#endif /* !___fenv_t_defined */
#ifndef __fexcept_t_defined
#define __fexcept_t_defined 1
__NAMESPACE_STD_USING(fexcept_t)
#endif /* !__fexcept_t_defined */
#endif /* !__CXX_SYSTEM_HEADER */

__NAMESPACE_STD_BEGIN
#ifndef __std_feclearexcept_defined
#define __std_feclearexcept_defined 1
#if defined(__CRT_HAVE_feclearexcept)
/* Clear the supported exceptions represented by EXCEPTS */
__CDECLARE(,int,__NOTHROW,feclearexcept,(int __excepts),(__excepts))
#else /* LIBC: feclearexcept */
#undef __std_feclearexcept_defined
#endif /* feclearexcept... */
#endif /* !__std_feclearexcept_defined */
#ifndef __std_fegetexceptflag_defined
#define __std_fegetexceptflag_defined 1
#if defined(__CRT_HAVE_fegetexceptflag)
/* Store implementation-defined representation of the exception
 * flags indicated by EXCEPTS in the object pointed to by FLAGP */
__CDECLARE(,int,__NOTHROW_NCX,fegetexceptflag,(fexcept_t *__flagp, int __excepts),(__flagp,__excepts))
#else /* LIBC: fegetexceptflag */
#undef __std_fegetexceptflag_defined
#endif /* fegetexceptflag... */
#endif /* !__std_fegetexceptflag_defined */
#ifndef __std_feraiseexcept_defined
#define __std_feraiseexcept_defined 1
#if defined(__CRT_HAVE_feraiseexcept)
/* Raise the supported exceptions represented by EXCEPTS */
__CDECLARE(,int,__NOTHROW,feraiseexcept,(int __excepts),(__excepts))
#else /* LIBC: feraiseexcept */
#undef __std_feraiseexcept_defined
#endif /* feraiseexcept... */
#endif /* !__std_feraiseexcept_defined */
#ifndef __std_fesetexceptflag_defined
#define __std_fesetexceptflag_defined 1
#if defined(__CRT_HAVE_fesetexceptflag)
/* Set complete status for exceptions indicated by EXCEPTS according
 * to the representation in the object pointed to by FLAGP */
__CDECLARE(,int,__NOTHROW_NCX,fesetexceptflag,(fexcept_t const *__flagp, int __excepts),(__flagp,__excepts))
#else /* LIBC: fesetexceptflag */
#undef __std_fesetexceptflag_defined
#endif /* fesetexceptflag... */
#endif /* !__std_fesetexceptflag_defined */
#ifndef __std_fetestexcept_defined
#define __std_fetestexcept_defined 1
#if defined(__CRT_HAVE_fetestexcept)
/* Determine which of subset of the exceptions
 * specified by EXCEPTS are currently set */
__CDECLARE(,int,__NOTHROW,fetestexcept,(int __excepts),(__excepts))
#else /* LIBC: fetestexcept */
#undef __std_fetestexcept_defined
#endif /* fetestexcept... */
#endif /* !__std_fetestexcept_defined */
#ifndef __std_fegetround_defined
#define __std_fegetround_defined 1
#if defined(__CRT_HAVE_fegetround)
/* Get current rounding direction */
__CDECLARE(__ATTR_PURE,int,__NOTHROW,fegetround,(void),())
#else /* LIBC: fegetround */
#undef __std_fegetround_defined
#endif /* fegetround... */
#endif /* !__std_fegetround_defined */
#ifndef __std_fesetround_defined
#define __std_fesetround_defined 1
#if defined(__CRT_HAVE_fesetround)
/* Establish the rounding direction represented by ROUND */
__CDECLARE(,int,__NOTHROW,fesetround,(int __rounding_direction),(__rounding_direction))
#else /* LIBC: fesetround */
#undef __std_fesetround_defined
#endif /* fesetround... */
#endif /* !__std_fesetround_defined */
#ifndef __std_fegetenv_defined
#define __std_fegetenv_defined 1
#if defined(__CRT_HAVE_fegetenv)
/* Store the current floating-point environment in the object pointed to by ENVP */
__CDECLARE(,int,__NOTHROW_NCX,fegetenv,(fenv_t *___envp),(___envp))
#else /* LIBC: fegetenv */
#undef __std_fegetenv_defined
#endif /* fegetenv... */
#endif /* !__std_fegetenv_defined */
#ifndef __std_feholdexcept_defined
#define __std_feholdexcept_defined 1
#if defined(__CRT_HAVE_feholdexcept)
/* Save the current environment in the object pointed to by ENVP, clear
 * exception flags and install a non-stop mode (if available) for all exceptions */
__CDECLARE(,int,__NOTHROW_NCX,feholdexcept,(fenv_t *___envp),(___envp))
#else /* LIBC: feholdexcept */
#undef __std_feholdexcept_defined
#endif /* feholdexcept... */
#endif /* !__std_feholdexcept_defined */
#ifndef __std_fesetenv_defined
#define __std_fesetenv_defined 1
#if defined(__CRT_HAVE_fesetenv)
/* Establish the floating-point environment represented by the object pointed to by ENVP */
__CDECLARE(,int,__NOTHROW_NCX,fesetenv,(fenv_t const *___envp),(___envp))
#else /* LIBC: fesetenv */
#undef __std_fesetenv_defined
#endif /* fesetenv... */
#endif /* !__std_fesetenv_defined */
#ifndef __std_feupdateenv_defined
#define __std_feupdateenv_defined 1
#if defined(__CRT_HAVE_feupdateenv)
/* Save current exceptions in temporary storage, install environment
 * represented by object pointed to by ENVP and raise exceptions
 * according to saved exceptions */
__CDECLARE(,int,__NOTHROW_NCX,feupdateenv,(fenv_t const *___envp),(___envp))
#else /* LIBC: feupdateenv */
#undef __std_feupdateenv_defined
#endif /* feupdateenv... */
#endif /* !__std_feupdateenv_defined */
__NAMESPACE_STD_END

#ifndef __CXX_SYSTEM_HEADER
#if !defined(__feclearexcept_defined) && defined(__std_feclearexcept_defined)
#define __feclearexcept_defined 1
__NAMESPACE_STD_USING(feclearexcept)
#endif /* !__feclearexcept_defined && !__std_feclearexcept_defined */
#if !defined(__fegetexceptflag_defined) && defined(__std_fegetexceptflag_defined)
#define __fegetexceptflag_defined 1
__NAMESPACE_STD_USING(fegetexceptflag)
#endif /* !__fegetexceptflag_defined && !__std_fegetexceptflag_defined */
#if !defined(__feraiseexcept_defined) && defined(__std_feraiseexcept_defined)
#define __feraiseexcept_defined 1
__NAMESPACE_STD_USING(feraiseexcept)
#endif /* !__feraiseexcept_defined && !__std_feraiseexcept_defined */
#if !defined(__fesetexceptflag_defined) && defined(__std_fesetexceptflag_defined)
#define __fesetexceptflag_defined 1
__NAMESPACE_STD_USING(fesetexceptflag)
#endif /* !__fesetexceptflag_defined && !__std_fesetexceptflag_defined */
#if !defined(__fetestexcept_defined) && defined(__std_fetestexcept_defined)
#define __fetestexcept_defined 1
__NAMESPACE_STD_USING(fetestexcept)
#endif /* !__fetestexcept_defined && !__std_fetestexcept_defined */
#if !defined(__fegetround_defined) && defined(__std_fegetround_defined)
#define __fegetround_defined 1
__NAMESPACE_STD_USING(fegetround)
#endif /* !__fegetround_defined && !__std_fegetround_defined */
#if !defined(__fesetround_defined) && defined(__std_fesetround_defined)
#define __fesetround_defined 1
__NAMESPACE_STD_USING(fesetround)
#endif /* !__fesetround_defined && !__std_fesetround_defined */
#if !defined(__fegetenv_defined) && defined(__std_fegetenv_defined)
#define __fegetenv_defined 1
__NAMESPACE_STD_USING(fegetenv)
#endif /* !__fegetenv_defined && !__std_fegetenv_defined */
#if !defined(__feholdexcept_defined) && defined(__std_feholdexcept_defined)
#define __feholdexcept_defined 1
__NAMESPACE_STD_USING(feholdexcept)
#endif /* !__feholdexcept_defined && !__std_feholdexcept_defined */
#if !defined(__fesetenv_defined) && defined(__std_fesetenv_defined)
#define __fesetenv_defined 1
__NAMESPACE_STD_USING(fesetenv)
#endif /* !__fesetenv_defined && !__std_fesetenv_defined */
#if !defined(__feupdateenv_defined) && defined(__std_feupdateenv_defined)
#define __feupdateenv_defined 1
__NAMESPACE_STD_USING(feupdateenv)
#endif /* !__feupdateenv_defined && !__std_feupdateenv_defined */
#endif /* !__CXX_SYSTEM_HEADER */
#ifdef __USE_GNU
#if defined(__CRT_HAVE_feenableexcept)
/* Enable individual exceptions.  Will not enable more exceptions than
 * EXCEPTS specifies.  Returns the previous enabled exceptions if all
 * exceptions are successfully set, otherwise returns -1 */
__CDECLARE(,int,__NOTHROW,feenableexcept,(int __excepts),(__excepts))
#endif /* feenableexcept... */
#if defined(__CRT_HAVE_fedisableexcept)
/* Disable individual exceptions.  Will not disable more exceptions than
 * EXCEPTS specifies.  Returns the previous enabled exceptions if all
 * exceptions are successfully disabled, otherwise returns -1 */
__CDECLARE(,int,__NOTHROW,fedisableexcept,(int __excepts),(__excepts))
#endif /* fedisableexcept... */
#if defined(__CRT_HAVE_fegetexcept)
/* Return enabled exceptions */
__CDECLARE(,int,__NOTHROW,fegetexcept,(void),())
#endif /* fegetexcept... */
#endif /* __USE_GNU */

#endif /* __CC__ */

__SYSDECL_END

#endif /* !__NO_FPU */
#ifdef __CXX_SYSTEM_HEADER
#define _CXX_STDONLY_CFENV 1
#undef _FENV_H
#endif /* __CXX_SYSTEM_HEADER */
#endif /* !_CXX_STDONLY_CFENV */
#endif /* !_FENV_H */
