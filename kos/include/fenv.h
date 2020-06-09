/* HASH CRC-32:0x1dbffba2 */
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
__NAMESPACE_STD_USING(feclearexcept)
__NAMESPACE_STD_USING(feraiseexcept)
__NAMESPACE_STD_USING(fegetexceptflag)
__NAMESPACE_STD_USING(fesetexceptflag)
__NAMESPACE_STD_USING(fetestexcept)
__NAMESPACE_STD_USING(fegetround)
__NAMESPACE_STD_USING(fesetround)
__NAMESPACE_STD_USING(fegetenv)
__NAMESPACE_STD_USING(feholdexcept)
__NAMESPACE_STD_USING(fesetenv)
__NAMESPACE_STD_USING(feupdateenv)
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
#include <kos/anno.h>
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/fenv.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */

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
#ifdef __fast_feclearexcept_defined
/* Clear the supported exceptions represented by EXCEPTS */
__NAMESPACE_FAST_USING_OR_IMPL(feclearexcept, __FORCELOCAL int __NOTHROW(__LIBCCALL feclearexcept)(int __excepts) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(feclearexcept))(__excepts); })
#elif defined(__CRT_HAVE_feclearexcept)
/* Clear the supported exceptions represented by EXCEPTS */
__CDECLARE(,int,__NOTHROW,feclearexcept,(int __excepts),(__excepts))
#else /* ... */
__NAMESPACE_STD_END
#include <local/fenv/feclearexcept.h>
__NAMESPACE_STD_BEGIN
/* Clear the supported exceptions represented by EXCEPTS */
__NAMESPACE_LOCAL_USING_OR_IMPL(feclearexcept, __FORCELOCAL int __NOTHROW(__LIBCCALL feclearexcept)(int __excepts) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(feclearexcept))(__excepts); })
#endif /* !... */
#ifdef __fast_feraiseexcept_defined
/* Raise the supported exceptions represented by EXCEPTS */
__NAMESPACE_FAST_USING_OR_IMPL(feraiseexcept, __FORCELOCAL int (__LIBCCALL feraiseexcept)(int __excepts) __THROWS(...) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(feraiseexcept))(__excepts); })
#elif defined(__CRT_HAVE_feraiseexcept)
/* Raise the supported exceptions represented by EXCEPTS */
__CDECLARE(,int,__THROWING,feraiseexcept,(int __excepts),(__excepts))
#else /* ... */
__NAMESPACE_STD_END
#include <local/fenv/feraiseexcept.h>
__NAMESPACE_STD_BEGIN
/* Raise the supported exceptions represented by EXCEPTS */
__NAMESPACE_LOCAL_USING_OR_IMPL(feraiseexcept, __FORCELOCAL int (__LIBCCALL feraiseexcept)(int __excepts) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(feraiseexcept))(__excepts); })
#endif /* !... */
#ifdef __fast_fegetexceptflag_defined
/* Store implementation-defined representation of the exception
 * flags indicated by EXCEPTS in the object pointed to by FLAGP */
__NAMESPACE_FAST_USING_OR_IMPL(fegetexceptflag, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL fegetexceptflag)(fexcept_t *__flagp, int __excepts) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(fegetexceptflag))(__flagp, __excepts); })
#elif defined(__CRT_HAVE_fegetexceptflag)
/* Store implementation-defined representation of the exception
 * flags indicated by EXCEPTS in the object pointed to by FLAGP */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,fegetexceptflag,(fexcept_t *__flagp, int __excepts),(__flagp,__excepts))
#else /* ... */
__NAMESPACE_STD_END
#include <local/fenv/fegetexceptflag.h>
__NAMESPACE_STD_BEGIN
/* Store implementation-defined representation of the exception
 * flags indicated by EXCEPTS in the object pointed to by FLAGP */
__NAMESPACE_LOCAL_USING_OR_IMPL(fegetexceptflag, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL fegetexceptflag)(fexcept_t *__flagp, int __excepts) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fegetexceptflag))(__flagp, __excepts); })
#endif /* !... */
#ifdef __fast_fesetexceptflag_defined
/* Set complete status for exceptions indicated by EXCEPTS according
 * to the representation in the object pointed to by FLAGP */
__NAMESPACE_FAST_USING_OR_IMPL(fesetexceptflag, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL fesetexceptflag)(fexcept_t const *__flagp, int __excepts) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(fesetexceptflag))(__flagp, __excepts); })
#elif defined(__CRT_HAVE_fesetexceptflag)
/* Set complete status for exceptions indicated by EXCEPTS according
 * to the representation in the object pointed to by FLAGP */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,fesetexceptflag,(fexcept_t const *__flagp, int __excepts),(__flagp,__excepts))
#else /* ... */
__NAMESPACE_STD_END
#include <local/fenv/fesetexceptflag.h>
__NAMESPACE_STD_BEGIN
/* Set complete status for exceptions indicated by EXCEPTS according
 * to the representation in the object pointed to by FLAGP */
__NAMESPACE_LOCAL_USING_OR_IMPL(fesetexceptflag, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL fesetexceptflag)(fexcept_t const *__flagp, int __excepts) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fesetexceptflag))(__flagp, __excepts); })
#endif /* !... */
#ifdef __fast_fetestexcept_defined
/* Determine which of subset of the exceptions
 * specified by EXCEPTS are currently set */
__NAMESPACE_FAST_USING_OR_IMPL(fetestexcept, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW(__LIBCCALL fetestexcept)(int __excepts) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(fetestexcept))(__excepts); })
#elif defined(__CRT_HAVE_fetestexcept)
/* Determine which of subset of the exceptions
 * specified by EXCEPTS are currently set */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW,fetestexcept,(int __excepts),(__excepts))
#else /* ... */
__NAMESPACE_STD_END
#include <local/fenv/fetestexcept.h>
__NAMESPACE_STD_BEGIN
/* Determine which of subset of the exceptions
 * specified by EXCEPTS are currently set */
__NAMESPACE_LOCAL_USING_OR_IMPL(fetestexcept, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW(__LIBCCALL fetestexcept)(int __excepts) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fetestexcept))(__excepts); })
#endif /* !... */
#ifdef __fast_fegetround_defined
/* Get current rounding direction
 * @return: One of...
 *             ... `FE_TONEAREST':  round()
 *             ... `FE_DOWNWARD':   floor()
 *             ... `FE_UPWARD':     ceil()
 *             ... `FE_TOWARDZERO': trunc() */
__NAMESPACE_FAST_USING_OR_IMPL(fegetround, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW(__LIBCCALL fegetround)(void) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(fegetround))(); })
#elif defined(__CRT_HAVE_fegetround)
/* Get current rounding direction
 * @return: One of...
 *             ... `FE_TONEAREST':  round()
 *             ... `FE_DOWNWARD':   floor()
 *             ... `FE_UPWARD':     ceil()
 *             ... `FE_TOWARDZERO': trunc() */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW,fegetround,(void),())
#else /* ... */
__NAMESPACE_STD_END
#include <local/fenv/fegetround.h>
__NAMESPACE_STD_BEGIN
/* Get current rounding direction
 * @return: One of...
 *             ... `FE_TONEAREST':  round()
 *             ... `FE_DOWNWARD':   floor()
 *             ... `FE_UPWARD':     ceil()
 *             ... `FE_TOWARDZERO': trunc() */
__NAMESPACE_LOCAL_USING_OR_IMPL(fegetround, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW(__LIBCCALL fegetround)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fegetround))(); })
#endif /* !... */
#ifdef __fast_fesetround_defined
/* Establish the rounding direction represented by `rounding_direction'
 * @param: rounding_direction: One of...
 *             ... `FE_TONEAREST':  round()
 *             ... `FE_DOWNWARD':   floor()
 *             ... `FE_UPWARD':     ceil()
 *             ... `FE_TOWARDZERO': trunc() */
__NAMESPACE_FAST_USING_OR_IMPL(fesetround, __FORCELOCAL int __NOTHROW(__LIBCCALL fesetround)(int __rounding_direction) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(fesetround))(__rounding_direction); })
#elif defined(__CRT_HAVE_fesetround)
/* Establish the rounding direction represented by `rounding_direction'
 * @param: rounding_direction: One of...
 *             ... `FE_TONEAREST':  round()
 *             ... `FE_DOWNWARD':   floor()
 *             ... `FE_UPWARD':     ceil()
 *             ... `FE_TOWARDZERO': trunc() */
__CDECLARE(,int,__NOTHROW,fesetround,(int __rounding_direction),(__rounding_direction))
#else /* ... */
__NAMESPACE_STD_END
#include <local/fenv/fesetround.h>
__NAMESPACE_STD_BEGIN
/* Establish the rounding direction represented by `rounding_direction'
 * @param: rounding_direction: One of...
 *             ... `FE_TONEAREST':  round()
 *             ... `FE_DOWNWARD':   floor()
 *             ... `FE_UPWARD':     ceil()
 *             ... `FE_TOWARDZERO': trunc() */
__NAMESPACE_LOCAL_USING_OR_IMPL(fesetround, __FORCELOCAL int __NOTHROW(__LIBCCALL fesetround)(int __rounding_direction) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fesetround))(__rounding_direction); })
#endif /* !... */
#ifdef __fast_fegetenv_defined
/* Store the current floating-point environment in the object pointed to by ENVP */
__NAMESPACE_FAST_USING_OR_IMPL(fegetenv, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL fegetenv)(fenv_t *___envp) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(fegetenv))(___envp); })
#elif defined(__CRT_HAVE_fegetenv)
/* Store the current floating-point environment in the object pointed to by ENVP */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,fegetenv,(fenv_t *___envp),(___envp))
#else /* ... */
__NAMESPACE_STD_END
#include <local/fenv/fegetenv.h>
__NAMESPACE_STD_BEGIN
/* Store the current floating-point environment in the object pointed to by ENVP */
__NAMESPACE_LOCAL_USING_OR_IMPL(fegetenv, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL fegetenv)(fenv_t *___envp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fegetenv))(___envp); })
#endif /* !... */
#ifdef __fast_feholdexcept_defined
/* Save the current environment in the object pointed to by ENVP, clear
 * exception flags and install a non-stop mode (if available) for all exceptions */
__NAMESPACE_FAST_USING_OR_IMPL(feholdexcept, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL feholdexcept)(fenv_t *___envp) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(feholdexcept))(___envp); })
#elif defined(__CRT_HAVE_feholdexcept)
/* Save the current environment in the object pointed to by ENVP, clear
 * exception flags and install a non-stop mode (if available) for all exceptions */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,feholdexcept,(fenv_t *___envp),(___envp))
#else /* ... */
__NAMESPACE_STD_END
#include <local/fenv/feholdexcept.h>
__NAMESPACE_STD_BEGIN
/* Save the current environment in the object pointed to by ENVP, clear
 * exception flags and install a non-stop mode (if available) for all exceptions */
__NAMESPACE_LOCAL_USING_OR_IMPL(feholdexcept, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL feholdexcept)(fenv_t *___envp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(feholdexcept))(___envp); })
#endif /* !... */
#ifdef __fast_fesetenv_defined
/* Establish the floating-point environment represented by the object pointed to by ENVP */
__NAMESPACE_FAST_USING_OR_IMPL(fesetenv, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL fesetenv)(fenv_t const *___envp) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(fesetenv))(___envp); })
#elif defined(__CRT_HAVE_fesetenv)
/* Establish the floating-point environment represented by the object pointed to by ENVP */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,fesetenv,(fenv_t const *___envp),(___envp))
#else /* ... */
__NAMESPACE_STD_END
#include <local/fenv/fesetenv.h>
__NAMESPACE_STD_BEGIN
/* Establish the floating-point environment represented by the object pointed to by ENVP */
__NAMESPACE_LOCAL_USING_OR_IMPL(fesetenv, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL fesetenv)(fenv_t const *___envp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fesetenv))(___envp); })
#endif /* !... */
#ifdef __fast_feupdateenv_defined
/* Save current exceptions in temporary storage, install environment
 * represented by object pointed to by ENVP and raise exceptions
 * according to saved exceptions */
__NAMESPACE_FAST_USING_OR_IMPL(feupdateenv, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL feupdateenv)(fenv_t const *___envp) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(feupdateenv))(___envp); })
#elif defined(__CRT_HAVE_feupdateenv)
/* Save current exceptions in temporary storage, install environment
 * represented by object pointed to by ENVP and raise exceptions
 * according to saved exceptions */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,feupdateenv,(fenv_t const *___envp),(___envp))
#else /* ... */
__NAMESPACE_STD_END
#include <local/fenv/feupdateenv.h>
__NAMESPACE_STD_BEGIN
/* Save current exceptions in temporary storage, install environment
 * represented by object pointed to by ENVP and raise exceptions
 * according to saved exceptions */
__NAMESPACE_LOCAL_USING_OR_IMPL(feupdateenv, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL feupdateenv)(fenv_t const *___envp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(feupdateenv))(___envp); })
#endif /* !... */
__NAMESPACE_STD_END

#ifndef __CXX_SYSTEM_HEADER
__NAMESPACE_STD_USING(feclearexcept)
__NAMESPACE_STD_USING(feraiseexcept)
__NAMESPACE_STD_USING(fegetexceptflag)
__NAMESPACE_STD_USING(fesetexceptflag)
__NAMESPACE_STD_USING(fetestexcept)
__NAMESPACE_STD_USING(fegetround)
__NAMESPACE_STD_USING(fesetround)
__NAMESPACE_STD_USING(fegetenv)
__NAMESPACE_STD_USING(feholdexcept)
__NAMESPACE_STD_USING(fesetenv)
__NAMESPACE_STD_USING(feupdateenv)
#endif /* !__CXX_SYSTEM_HEADER */
#ifdef __USE_GNU
#ifdef __fast_feenableexcept_defined
/* Enable individual exceptions.  Will not enable more exceptions than
 * EXCEPTS specifies.  Returns the previous enabled exceptions if all
 * exceptions are successfully set, otherwise returns -1 */
__NAMESPACE_FAST_USING_OR_IMPL(feenableexcept, __FORCELOCAL int __NOTHROW(__LIBCCALL feenableexcept)(int __excepts) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(feenableexcept))(__excepts); })
#elif defined(__CRT_HAVE_feenableexcept)
/* Enable individual exceptions.  Will not enable more exceptions than
 * EXCEPTS specifies.  Returns the previous enabled exceptions if all
 * exceptions are successfully set, otherwise returns -1 */
__CDECLARE(,int,__NOTHROW,feenableexcept,(int __excepts),(__excepts))
#else /* ... */
#include <local/fenv/feenableexcept.h>
/* Enable individual exceptions.  Will not enable more exceptions than
 * EXCEPTS specifies.  Returns the previous enabled exceptions if all
 * exceptions are successfully set, otherwise returns -1 */
__NAMESPACE_LOCAL_USING_OR_IMPL(feenableexcept, __FORCELOCAL int __NOTHROW(__LIBCCALL feenableexcept)(int __excepts) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(feenableexcept))(__excepts); })
#endif /* !... */
#ifdef __fast_fedisableexcept_defined
/* Disable individual exceptions.  Will not disable more exceptions than
 * EXCEPTS specifies.  Returns the previous enabled exceptions if all
 * exceptions are successfully disabled, otherwise returns -1 */
__NAMESPACE_FAST_USING_OR_IMPL(fedisableexcept, __FORCELOCAL int __NOTHROW(__LIBCCALL fedisableexcept)(int __excepts) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(fedisableexcept))(__excepts); })
#elif defined(__CRT_HAVE_fedisableexcept)
/* Disable individual exceptions.  Will not disable more exceptions than
 * EXCEPTS specifies.  Returns the previous enabled exceptions if all
 * exceptions are successfully disabled, otherwise returns -1 */
__CDECLARE(,int,__NOTHROW,fedisableexcept,(int __excepts),(__excepts))
#else /* ... */
#include <local/fenv/fedisableexcept.h>
/* Disable individual exceptions.  Will not disable more exceptions than
 * EXCEPTS specifies.  Returns the previous enabled exceptions if all
 * exceptions are successfully disabled, otherwise returns -1 */
__NAMESPACE_LOCAL_USING_OR_IMPL(fedisableexcept, __FORCELOCAL int __NOTHROW(__LIBCCALL fedisableexcept)(int __excepts) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fedisableexcept))(__excepts); })
#endif /* !... */
#ifdef __fast_fegetexcept_defined
/* Return enabled exceptions */
__NAMESPACE_FAST_USING_OR_IMPL(fegetexcept, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW(__LIBCCALL fegetexcept)(void) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(fegetexcept))(); })
#elif defined(__CRT_HAVE_fegetexcept)
/* Return enabled exceptions */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW,fegetexcept,(void),())
#else /* ... */
#include <local/fenv/fegetexcept.h>
/* Return enabled exceptions */
__NAMESPACE_LOCAL_USING_OR_IMPL(fegetexcept, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW(__LIBCCALL fegetexcept)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fegetexcept))(); })
#endif /* !... */
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
