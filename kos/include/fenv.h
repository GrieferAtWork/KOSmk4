/* HASH CRC-32:0xae32ef92 */
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
/* (>) Standard: ISO C99 (ISO/IEC 9899:1999) */
/* (>) Standard: POSIX.1-2004 (Issue 6, IEEE Std 1003.1-2004) */
/* (#) Portability: Cygwin        (/newlib/libc/include/fenv.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/fenv.h) */
/* (#) Portability: GNU C Library (/math/fenv.h) */
/* (#) Portability: GNU Hurd      (/usr/include/fenv.h) */
/* (#) Portability: MSVC          (/include/fenv.h) */
/* (#) Portability: MinGW         (/mingw-w64-headers/crt/fenv.h) */
/* (#) Portability: NetBSD        (/include/fenv.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/fenv.h) */
/* (#) Portability: OpenBSD       (/include/fenv.h) */
/* (#) Portability: Windows Kits  (/ucrt/fenv.h) */
/* (#) Portability: diet libc     (/include/fenv.h) */
/* (#) Portability: libc6         (/include/fenv.h) */
/* (#) Portability: musl libc     (/include/fenv.h) */
/* (#) Portability: uClibc        (/include/fenv.h) */
#ifndef _FENV_H
#define _FENV_H 1

#ifdef _CXX_STDONLY_CFENV
#ifdef __CXX_SYSTEM_HEADER
#undef _FENV_H /* Allow the C-header to be re-included to import all std::-symbols into the global namespace. */
#else /* __CXX_SYSTEM_HEADER */
/* Import all symbols into the global namespace when re-including "fenv.h" after "cfenv" */
#ifndef __NO_FPU
#ifndef ___fenv_t_defined
#define ___fenv_t_defined
__NAMESPACE_STD_USING(fenv_t)
#endif /* !___fenv_t_defined */
#ifndef __fexcept_t_defined
#define __fexcept_t_defined
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

#include <bits/crt/fenv.h>
#include <kos/anno.h>
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/fenv.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */

#ifdef __CC__
__SYSDECL_BEGIN

__NAMESPACE_STD_BEGIN
#ifndef __std_fenv_t_defined
#define __std_fenv_t_defined
typedef struct __fenv_struct fenv_t;
#endif /* !__std_fenv_t_defined */
#ifndef __std_fexcept_t_defined
#define __std_fexcept_t_defined
typedef __fexcept_t fexcept_t;
#endif /* !__std_fexcept_t_defined */
__NAMESPACE_STD_END

#ifndef __CXX_SYSTEM_HEADER
#ifndef ___fenv_t_defined
#define ___fenv_t_defined
__NAMESPACE_STD_USING(fenv_t)
#endif /* !___fenv_t_defined */
#ifndef __fexcept_t_defined
#define __fexcept_t_defined
__NAMESPACE_STD_USING(fexcept_t)
#endif /* !__fexcept_t_defined */
#endif /* !__CXX_SYSTEM_HEADER */

__NAMESPACE_STD_BEGIN
#if defined(__fast_feclearexcept_defined) && defined(__CRT_HAVE_feclearexcept)
/* >> feclearexcept(3)
 * @param: excepts: Set of `FE_*' */
__CEIDECLARE(,int,__NOTHROW,feclearexcept,(int __excepts),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(feclearexcept))(__excepts); })
#elif defined(__fast_feclearexcept_defined)
/* >> feclearexcept(3)
 * @param: excepts: Set of `FE_*' */
__FORCELOCAL int __NOTHROW(__LIBCCALL feclearexcept)(int __excepts) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(feclearexcept))(__excepts); }
#elif defined(__CRT_HAVE_feclearexcept)
/* >> feclearexcept(3)
 * @param: excepts: Set of `FE_*' */
__CDECLARE(,int,__NOTHROW,feclearexcept,(int __excepts),(__excepts))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/fenv/feclearexcept.h>
__NAMESPACE_STD_BEGIN
/* >> feclearexcept(3)
 * @param: excepts: Set of `FE_*' */
__NAMESPACE_LOCAL_USING_OR_IMPL(feclearexcept, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW(__LIBCCALL feclearexcept)(int __excepts) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(feclearexcept))(__excepts); })
#endif /* !... */
#if defined(__fast_feraiseexcept_defined) && defined(__CRT_HAVE_feraiseexcept)
/* >> feraiseexcept(3)
 * @param: excepts: Set of `FE_*' */
__CEIDECLARE(,int,__THROWING,feraiseexcept,(int __excepts),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(feraiseexcept))(__excepts); })
#elif defined(__fast_feraiseexcept_defined)
/* >> feraiseexcept(3)
 * @param: excepts: Set of `FE_*' */
__FORCELOCAL int (__LIBCCALL feraiseexcept)(int __excepts) __THROWS(...) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(feraiseexcept))(__excepts); }
#elif defined(__CRT_HAVE_feraiseexcept)
/* >> feraiseexcept(3)
 * @param: excepts: Set of `FE_*' */
__CDECLARE(,int,__THROWING,feraiseexcept,(int __excepts),(__excepts))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/fenv/feraiseexcept.h>
__NAMESPACE_STD_BEGIN
/* >> feraiseexcept(3)
 * @param: excepts: Set of `FE_*' */
__NAMESPACE_LOCAL_USING_OR_IMPL(feraiseexcept, __FORCELOCAL __ATTR_ARTIFICIAL int (__LIBCCALL feraiseexcept)(int __excepts) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(feraiseexcept))(__excepts); })
#endif /* !... */
#if defined(__fast_fegetexceptflag_defined) && defined(__CRT_HAVE_fegetexceptflag)
/* >> fegetexceptflag(3) */
__CEIDECLARE_GCCNCX(__ATTR_OUT(1),int,__NOTHROW_NCX,fegetexceptflag,(fexcept_t *__flagp, int __excepts),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(fegetexceptflag))(__flagp, __excepts); })
#elif defined(__fast_fegetexceptflag_defined)
/* >> fegetexceptflag(3) */
__FORCELOCAL __ATTR_OUT(1) int __NOTHROW_NCX(__LIBCCALL fegetexceptflag)(fexcept_t *__flagp, int __excepts) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(fegetexceptflag))(__flagp, __excepts); }
#elif defined(__CRT_HAVE_fegetexceptflag)
/* >> fegetexceptflag(3) */
__CDECLARE_GCCNCX(__ATTR_OUT(1),int,__NOTHROW_NCX,fegetexceptflag,(fexcept_t *__flagp, int __excepts),(__flagp,__excepts))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/fenv/fegetexceptflag.h>
__NAMESPACE_STD_BEGIN
/* >> fegetexceptflag(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(fegetexceptflag, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUT(1) int __NOTHROW_NCX(__LIBCCALL fegetexceptflag)(fexcept_t *__flagp, int __excepts) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fegetexceptflag))(__flagp, __excepts); })
#endif /* !... */
#if defined(__fast_fesetexceptflag_defined) && defined(__CRT_HAVE_fesetexceptflag)
/* >> fesetexceptflag(3) */
__CEIDECLARE_GCCNCX(__ATTR_IN(1),int,__NOTHROW_NCX,fesetexceptflag,(fexcept_t const *__flagp, int __excepts),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(fesetexceptflag))(__flagp, __excepts); })
#elif defined(__fast_fesetexceptflag_defined)
/* >> fesetexceptflag(3) */
__FORCELOCAL __ATTR_IN(1) int __NOTHROW_NCX(__LIBCCALL fesetexceptflag)(fexcept_t const *__flagp, int __excepts) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(fesetexceptflag))(__flagp, __excepts); }
#elif defined(__CRT_HAVE_fesetexceptflag)
/* >> fesetexceptflag(3) */
__CDECLARE_GCCNCX(__ATTR_IN(1),int,__NOTHROW_NCX,fesetexceptflag,(fexcept_t const *__flagp, int __excepts),(__flagp,__excepts))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/fenv/fesetexceptflag.h>
__NAMESPACE_STD_BEGIN
/* >> fesetexceptflag(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(fesetexceptflag, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) int __NOTHROW_NCX(__LIBCCALL fesetexceptflag)(fexcept_t const *__flagp, int __excepts) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fesetexceptflag))(__flagp, __excepts); })
#endif /* !... */
#if defined(__fast_fetestexcept_defined) && defined(__CRT_HAVE_fetestexcept)
/* >> fetestexcept(3) */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW,fetestexcept,(int __excepts),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(fetestexcept))(__excepts); })
#elif defined(__fast_fetestexcept_defined)
/* >> fetestexcept(3) */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW(__LIBCCALL fetestexcept)(int __excepts) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(fetestexcept))(__excepts); }
#elif defined(__CRT_HAVE_fetestexcept)
/* >> fetestexcept(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW,fetestexcept,(int __excepts),(__excepts))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/fenv/fetestexcept.h>
__NAMESPACE_STD_BEGIN
/* >> fetestexcept(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(fetestexcept, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW(__LIBCCALL fetestexcept)(int __excepts) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fetestexcept))(__excepts); })
#endif /* !... */
#if defined(__fast_fegetround_defined) && defined(__CRT_HAVE_fegetround)
/* >> fegetround(3)
 * Get the current rounding direction
 * @return: One of...
 *             ... `FE_TONEAREST':  round()
 *             ... `FE_DOWNWARD':   floor()
 *             ... `FE_UPWARD':     ceil()
 *             ... `FE_TOWARDZERO': trunc() */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW,fegetround,(void),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(fegetround))(); })
#elif defined(__fast_fegetround_defined)
/* >> fegetround(3)
 * Get the current rounding direction
 * @return: One of...
 *             ... `FE_TONEAREST':  round()
 *             ... `FE_DOWNWARD':   floor()
 *             ... `FE_UPWARD':     ceil()
 *             ... `FE_TOWARDZERO': trunc() */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW(__LIBCCALL fegetround)(void) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(fegetround))(); }
#elif defined(__CRT_HAVE_fegetround)
/* >> fegetround(3)
 * Get the current rounding direction
 * @return: One of...
 *             ... `FE_TONEAREST':  round()
 *             ... `FE_DOWNWARD':   floor()
 *             ... `FE_UPWARD':     ceil()
 *             ... `FE_TOWARDZERO': trunc() */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW,fegetround,(void),())
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/fenv/fegetround.h>
__NAMESPACE_STD_BEGIN
/* >> fegetround(3)
 * Get the current rounding direction
 * @return: One of...
 *             ... `FE_TONEAREST':  round()
 *             ... `FE_DOWNWARD':   floor()
 *             ... `FE_UPWARD':     ceil()
 *             ... `FE_TOWARDZERO': trunc() */
__NAMESPACE_LOCAL_USING_OR_IMPL(fegetround, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW(__LIBCCALL fegetround)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fegetround))(); })
#endif /* !... */
#if defined(__fast_fesetround_defined) && defined(__CRT_HAVE_fesetround)
/* >> fesetround(3)
 * Set the current rounding direction
 * @param: rounding_direction: One of...
 *             ... `FE_TONEAREST':  round()
 *             ... `FE_DOWNWARD':   floor()
 *             ... `FE_UPWARD':     ceil()
 *             ... `FE_TOWARDZERO': trunc() */
__CEIDECLARE(,int,__NOTHROW,fesetround,(int __rounding_direction),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(fesetround))(__rounding_direction); })
#elif defined(__fast_fesetround_defined)
/* >> fesetround(3)
 * Set the current rounding direction
 * @param: rounding_direction: One of...
 *             ... `FE_TONEAREST':  round()
 *             ... `FE_DOWNWARD':   floor()
 *             ... `FE_UPWARD':     ceil()
 *             ... `FE_TOWARDZERO': trunc() */
__FORCELOCAL int __NOTHROW(__LIBCCALL fesetround)(int __rounding_direction) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(fesetround))(__rounding_direction); }
#elif defined(__CRT_HAVE_fesetround)
/* >> fesetround(3)
 * Set the current rounding direction
 * @param: rounding_direction: One of...
 *             ... `FE_TONEAREST':  round()
 *             ... `FE_DOWNWARD':   floor()
 *             ... `FE_UPWARD':     ceil()
 *             ... `FE_TOWARDZERO': trunc() */
__CDECLARE(,int,__NOTHROW,fesetround,(int __rounding_direction),(__rounding_direction))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/fenv/fesetround.h>
__NAMESPACE_STD_BEGIN
/* >> fesetround(3)
 * Set the current rounding direction
 * @param: rounding_direction: One of...
 *             ... `FE_TONEAREST':  round()
 *             ... `FE_DOWNWARD':   floor()
 *             ... `FE_UPWARD':     ceil()
 *             ... `FE_TOWARDZERO': trunc() */
__NAMESPACE_LOCAL_USING_OR_IMPL(fesetround, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW(__LIBCCALL fesetround)(int __rounding_direction) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fesetround))(__rounding_direction); })
#endif /* !... */
#if defined(__fast_fegetenv_defined) && defined(__CRT_HAVE_fegetenv)
/* >> fegetenv(3) */
__CEIDECLARE_GCCNCX(__ATTR_OUT(1),int,__NOTHROW_NCX,fegetenv,(fenv_t *___envp),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(fegetenv))(___envp); })
#elif defined(__fast_fegetenv_defined)
/* >> fegetenv(3) */
__FORCELOCAL __ATTR_OUT(1) int __NOTHROW_NCX(__LIBCCALL fegetenv)(fenv_t *___envp) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(fegetenv))(___envp); }
#elif defined(__CRT_HAVE_fegetenv)
/* >> fegetenv(3) */
__CDECLARE_GCCNCX(__ATTR_OUT(1),int,__NOTHROW_NCX,fegetenv,(fenv_t *___envp),(___envp))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/fenv/fegetenv.h>
__NAMESPACE_STD_BEGIN
/* >> fegetenv(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(fegetenv, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUT(1) int __NOTHROW_NCX(__LIBCCALL fegetenv)(fenv_t *___envp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fegetenv))(___envp); })
#endif /* !... */
#if defined(__fast_feholdexcept_defined) && defined(__CRT_HAVE_feholdexcept)
/* >> feholdexcept(3) */
__CEIDECLARE_GCCNCX(__ATTR_OUT(1),int,__NOTHROW_NCX,feholdexcept,(fenv_t *___envp),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(feholdexcept))(___envp); })
#elif defined(__fast_feholdexcept_defined)
/* >> feholdexcept(3) */
__FORCELOCAL __ATTR_OUT(1) int __NOTHROW_NCX(__LIBCCALL feholdexcept)(fenv_t *___envp) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(feholdexcept))(___envp); }
#elif defined(__CRT_HAVE_feholdexcept)
/* >> feholdexcept(3) */
__CDECLARE_GCCNCX(__ATTR_OUT(1),int,__NOTHROW_NCX,feholdexcept,(fenv_t *___envp),(___envp))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/fenv/feholdexcept.h>
__NAMESPACE_STD_BEGIN
/* >> feholdexcept(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(feholdexcept, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUT(1) int __NOTHROW_NCX(__LIBCCALL feholdexcept)(fenv_t *___envp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(feholdexcept))(___envp); })
#endif /* !... */
#if defined(__fast_fesetenv_defined) && defined(__CRT_HAVE_fesetenv)
/* >> fesetenv(3) */
__CEIDECLARE_GCCNCX(__ATTR_IN(1),int,__NOTHROW_NCX,fesetenv,(fenv_t const *___envp),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(fesetenv))(___envp); })
#elif defined(__fast_fesetenv_defined)
/* >> fesetenv(3) */
__FORCELOCAL __ATTR_IN(1) int __NOTHROW_NCX(__LIBCCALL fesetenv)(fenv_t const *___envp) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(fesetenv))(___envp); }
#elif defined(__CRT_HAVE_fesetenv)
/* >> fesetenv(3) */
__CDECLARE_GCCNCX(__ATTR_IN(1),int,__NOTHROW_NCX,fesetenv,(fenv_t const *___envp),(___envp))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/fenv/fesetenv.h>
__NAMESPACE_STD_BEGIN
/* >> fesetenv(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(fesetenv, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) int __NOTHROW_NCX(__LIBCCALL fesetenv)(fenv_t const *___envp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fesetenv))(___envp); })
#endif /* !... */
#if defined(__fast_feupdateenv_defined) && defined(__CRT_HAVE_feupdateenv)
/* >> feupdateenv(3) */
__CEIDECLARE_GCCNCX(__ATTR_IN(1),int,__NOTHROW_NCX,feupdateenv,(fenv_t const *___envp),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(feupdateenv))(___envp); })
#elif defined(__fast_feupdateenv_defined)
/* >> feupdateenv(3) */
__FORCELOCAL __ATTR_IN(1) int __NOTHROW_NCX(__LIBCCALL feupdateenv)(fenv_t const *___envp) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(feupdateenv))(___envp); }
#elif defined(__CRT_HAVE_feupdateenv)
/* >> feupdateenv(3) */
__CDECLARE_GCCNCX(__ATTR_IN(1),int,__NOTHROW_NCX,feupdateenv,(fenv_t const *___envp),(___envp))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/fenv/feupdateenv.h>
__NAMESPACE_STD_BEGIN
/* >> feupdateenv(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(feupdateenv, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) int __NOTHROW_NCX(__LIBCCALL feupdateenv)(fenv_t const *___envp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(feupdateenv))(___envp); })
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
#if defined(__fast_feenableexcept_defined) && defined(__CRT_HAVE_feenableexcept)
/* >> feenableexcept(3) */
__CEIDECLARE(,int,__NOTHROW,feenableexcept,(int __excepts),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(feenableexcept))(__excepts); })
#elif defined(__fast_feenableexcept_defined)
/* >> feenableexcept(3) */
__FORCELOCAL int __NOTHROW(__LIBCCALL feenableexcept)(int __excepts) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(feenableexcept))(__excepts); }
#elif defined(__CRT_HAVE_feenableexcept)
/* >> feenableexcept(3) */
__CDECLARE(,int,__NOTHROW,feenableexcept,(int __excepts),(__excepts))
#else /* ... */
#include <libc/local/fenv/feenableexcept.h>
/* >> feenableexcept(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(feenableexcept, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW(__LIBCCALL feenableexcept)(int __excepts) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(feenableexcept))(__excepts); })
#endif /* !... */
#if defined(__fast_fedisableexcept_defined) && defined(__CRT_HAVE_fedisableexcept)
/* >> fedisableexcept(3) */
__CEIDECLARE(,int,__NOTHROW,fedisableexcept,(int __excepts),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(fedisableexcept))(__excepts); })
#elif defined(__fast_fedisableexcept_defined)
/* >> fedisableexcept(3) */
__FORCELOCAL int __NOTHROW(__LIBCCALL fedisableexcept)(int __excepts) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(fedisableexcept))(__excepts); }
#elif defined(__CRT_HAVE_fedisableexcept)
/* >> fedisableexcept(3) */
__CDECLARE(,int,__NOTHROW,fedisableexcept,(int __excepts),(__excepts))
#else /* ... */
#include <libc/local/fenv/fedisableexcept.h>
/* >> fedisableexcept(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(fedisableexcept, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW(__LIBCCALL fedisableexcept)(int __excepts) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fedisableexcept))(__excepts); })
#endif /* !... */
#if defined(__fast_fegetexcept_defined) && defined(__CRT_HAVE_fegetexcept)
/* >> fegetexcept(3) */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW,fegetexcept,(void),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(fegetexcept))(); })
#elif defined(__fast_fegetexcept_defined)
/* >> fegetexcept(3) */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW(__LIBCCALL fegetexcept)(void) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(fegetexcept))(); }
#elif defined(__CRT_HAVE_fegetexcept)
/* >> fegetexcept(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW,fegetexcept,(void),())
#else /* ... */
#include <libc/local/fenv/fegetexcept.h>
/* >> fegetexcept(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(fegetexcept, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW(__LIBCCALL fegetexcept)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fegetexcept))(); })
#endif /* !... */
#endif /* __USE_GNU */

#if defined(__USE_GNU) || defined(__STDC_WANT_IEC_60559_BFP_EXT__)
typedef unsigned int femode_t;
#define FE_DFL_MODE ((femode_t const *)-1)
__CDECLARE_OPT(,int,__NOTHROW_NCX,fesetexcept,(int __excepts),(__excepts))
__CDECLARE_OPT(,int,__NOTHROW_NCX,fetestexceptflag,(__fexcept_t const *__flagp, int __excepts),(__flagp,__excepts))
__CDECLARE_OPT(,int,__NOTHROW_NCX,fegetmode,(femode_t *__modep),(__modep))
__CDECLARE_OPT(,int,__NOTHROW_NCX,fesetmode,(femode_t const *__modep),(__modep))
#if defined(FE_INVALID) && defined(__SUPPORT_SNAN__)
#define FE_SNANS_ALWAYS_SIGNAL 1
#endif /* FE_INVALID && __SUPPORT_SNAN__ */
#endif /* __USE_GNU || __STDC_WANT_IEC_60559_BFP_EXT__ */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !__NO_FPU */
#ifdef __CXX_SYSTEM_HEADER
#define _CXX_STDONLY_CFENV
#undef _FENV_H
#endif /* __CXX_SYSTEM_HEADER */
#endif /* !_CXX_STDONLY_CFENV */
#endif /* !_FENV_H */
