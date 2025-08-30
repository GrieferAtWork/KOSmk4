/* HASH CRC-32:0x1da4298a */
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
#include <bits/crt/fenv-impl.h>
#if defined(__CRT_HAVE_feraiseexcept) || defined(__arch_feraiseexcept)
__NAMESPACE_STD_USING(feraiseexcept)
#endif /* __CRT_HAVE_feraiseexcept || __arch_feraiseexcept */
#if defined(__CRT_HAVE_feclearexcept) || defined(__arch_feclearexcept)
__NAMESPACE_STD_USING(feclearexcept)
#endif /* __CRT_HAVE_feclearexcept || __arch_feclearexcept */
#if defined(__CRT_HAVE_fegetexceptflag) || defined(__arch_fegetexceptflag)
__NAMESPACE_STD_USING(fegetexceptflag)
#endif /* __CRT_HAVE_fegetexceptflag || __arch_fegetexceptflag */
#if defined(__CRT_HAVE_fesetexceptflag) || defined(__arch_fesetexceptflag)
__NAMESPACE_STD_USING(fesetexceptflag)
#endif /* __CRT_HAVE_fesetexceptflag || __arch_fesetexceptflag */
#if defined(__CRT_HAVE_fetestexcept) || defined(__arch_fetestexcept)
__NAMESPACE_STD_USING(fetestexcept)
#endif /* __CRT_HAVE_fetestexcept || __arch_fetestexcept */
#if defined(__CRT_HAVE_fegetround) || defined(__arch_fegetround)
__NAMESPACE_STD_USING(fegetround)
#endif /* __CRT_HAVE_fegetround || __arch_fegetround */
#if defined(__CRT_HAVE_fesetround) || defined(__arch_fesetround)
__NAMESPACE_STD_USING(fesetround)
#endif /* __CRT_HAVE_fesetround || __arch_fesetround */
#if defined(__CRT_HAVE_fegetenv) || defined(__arch_fegetenv)
__NAMESPACE_STD_USING(fegetenv)
#endif /* __CRT_HAVE_fegetenv || __arch_fegetenv */
#if defined(__CRT_HAVE_feholdexcept) || defined(__arch_feholdexcept)
__NAMESPACE_STD_USING(feholdexcept)
#endif /* __CRT_HAVE_feholdexcept || __arch_feholdexcept */
#if defined(__CRT_HAVE_fesetenv) || defined(__arch_fesetenv)
__NAMESPACE_STD_USING(fesetenv)
#endif /* __CRT_HAVE_fesetenv || __arch_fesetenv */
#if defined(__CRT_HAVE_feupdateenv) || defined(__arch_feupdateenv)
__NAMESPACE_STD_USING(feupdateenv)
#endif /* __CRT_HAVE_feupdateenv || __arch_feupdateenv */
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

#include <asm/crt/fenv.h>
#include <bits/crt/fenv.h>
#include <bits/crt/fenv-impl.h>
#include <kos/anno.h>


/*[[[enum]]]*/
#ifdef __CC__
enum {
#ifdef __FE_INVALID
	FE_INVALID   = __FE_INVALID,
#endif /* __FE_INVALID */
#ifdef __FE_DIVBYZERO
	FE_DIVBYZERO = __FE_DIVBYZERO,
#endif /* __FE_DIVBYZERO */
#ifdef __FE_OVERFLOW
	FE_OVERFLOW  = __FE_OVERFLOW,
#endif /* __FE_OVERFLOW */
#ifdef __FE_UNDERFLOW
	FE_UNDERFLOW = __FE_UNDERFLOW,
#endif /* __FE_UNDERFLOW */
#ifdef __FE_INEXACT
	FE_INEXACT   = __FE_INEXACT
#endif /* __FE_INEXACT */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#ifdef __FE_INVALID
#define FE_INVALID   FE_INVALID
#endif /* __FE_INVALID */
#ifdef __FE_DIVBYZERO
#define FE_DIVBYZERO FE_DIVBYZERO
#endif /* __FE_DIVBYZERO */
#ifdef __FE_OVERFLOW
#define FE_OVERFLOW  FE_OVERFLOW
#endif /* __FE_OVERFLOW */
#ifdef __FE_UNDERFLOW
#define FE_UNDERFLOW FE_UNDERFLOW
#endif /* __FE_UNDERFLOW */
#ifdef __FE_INEXACT
#define FE_INEXACT   FE_INEXACT
#endif /* __FE_INEXACT */
#else /* __COMPILER_PREFERR_ENUMS */
#ifdef __FE_INVALID
#define FE_INVALID   __FE_INVALID
#endif /* __FE_INVALID */
#ifdef __FE_DIVBYZERO
#define FE_DIVBYZERO __FE_DIVBYZERO
#endif /* __FE_DIVBYZERO */
#ifdef __FE_OVERFLOW
#define FE_OVERFLOW  __FE_OVERFLOW
#endif /* __FE_OVERFLOW */
#ifdef __FE_UNDERFLOW
#define FE_UNDERFLOW __FE_UNDERFLOW
#endif /* __FE_UNDERFLOW */
#ifdef __FE_INEXACT
#define FE_INEXACT   __FE_INEXACT
#endif /* __FE_INEXACT */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/

#ifndef FE_ALL_EXCEPT
#define FE_ALL_EXCEPT __FE_ALL_EXCEPT
#endif /* !FE_ALL_EXCEPT */

/*[[[enum]]]*/
#ifdef __CC__
enum {
#ifdef __FE_TONEAREST
	FE_TONEAREST  = __FE_TONEAREST, /* round() */
#endif /* __FE_TONEAREST */
#ifdef __FE_DOWNWARD
	FE_DOWNWARD   = __FE_DOWNWARD,  /* floor() */
#endif /* __FE_DOWNWARD */
#ifdef __FE_UPWARD
	FE_UPWARD     = __FE_UPWARD,    /* ceil() */
#endif /* __FE_UPWARD */
#ifdef __FE_TOWARDZERO
	FE_TOWARDZERO = __FE_TOWARDZERO /* trunc() */
#endif /* __FE_TOWARDZERO */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#ifdef __FE_TONEAREST
#define FE_TONEAREST  FE_TONEAREST  /* round() */
#endif /* __FE_TONEAREST */
#ifdef __FE_DOWNWARD
#define FE_DOWNWARD   FE_DOWNWARD   /* floor() */
#endif /* __FE_DOWNWARD */
#ifdef __FE_UPWARD
#define FE_UPWARD     FE_UPWARD     /* ceil() */
#endif /* __FE_UPWARD */
#ifdef __FE_TOWARDZERO
#define FE_TOWARDZERO FE_TOWARDZERO /* trunc() */
#endif /* __FE_TOWARDZERO */
#else /* __COMPILER_PREFERR_ENUMS */
#ifdef __FE_TONEAREST
#define FE_TONEAREST  __FE_TONEAREST  /* round() */
#endif /* __FE_TONEAREST */
#ifdef __FE_DOWNWARD
#define FE_DOWNWARD   __FE_DOWNWARD   /* floor() */
#endif /* __FE_DOWNWARD */
#ifdef __FE_UPWARD
#define FE_UPWARD     __FE_UPWARD     /* ceil() */
#endif /* __FE_UPWARD */
#ifdef __FE_TOWARDZERO
#define FE_TOWARDZERO __FE_TOWARDZERO /* trunc() */
#endif /* __FE_TOWARDZERO */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/


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

/* If the default argument is used we use this value. */
#if !defined(FE_DFL_ENV) && defined(__FE_DFL_ENV)
#define FE_DFL_ENV __FE_DFL_ENV
#endif /* !FE_DFL_ENV && __FE_DFL_ENV */

#ifdef __USE_GNU
/* Floating-point environment where none of the exception is masked. */
#if !defined(FE_NOMASK_ENV) && defined(__FE_NOMASK_ENV)
#define FE_NOMASK_ENV __FE_NOMASK_ENV
#endif /* !FE_NOMASK_ENV && __FE_NOMASK_ENV */
#endif /* __USE_GNU */

__NAMESPACE_STD_BEGIN
#if defined(__CRT_HAVE_feraiseexcept) && defined(__arch_feraiseexcept)
/* >> feraiseexcept(3)
 * @param: excepts: Set of `FE_*'
 * @return: == 0 : All exceptions indicated by `excepts' were railed
 * @return: != 0 : At least one exception of `excepts' could not be raised */
__CEIDECLARE(,int,__THROWING(...),feraiseexcept,(int __excepts),{ return __arch_feraiseexcept(__excepts); })
#elif defined(__CRT_HAVE_feraiseexcept)
/* >> feraiseexcept(3)
 * @param: excepts: Set of `FE_*'
 * @return: == 0 : All exceptions indicated by `excepts' were railed
 * @return: != 0 : At least one exception of `excepts' could not be raised */
__CDECLARE(,int,__THROWING(...),feraiseexcept,(int __excepts),(__excepts))
#elif defined(__arch_feraiseexcept)
/* >> feraiseexcept(3)
 * @param: excepts: Set of `FE_*'
 * @return: == 0 : All exceptions indicated by `excepts' were railed
 * @return: != 0 : At least one exception of `excepts' could not be raised */
__LOCAL int (__LIBCCALL feraiseexcept)(int __excepts) __THROWS(...) { return __arch_feraiseexcept(__excepts); }
#endif /* ... */
#if defined(__CRT_HAVE_feclearexcept) && defined(__arch_feclearexcept)
/* >> feclearexcept(3)
 * @param: excepts: Set of `FE_*'
 * @return: == 0 : All exceptions indicated by `excepts' were cleared
 * @return: != 0 : At least one exception of `excepts' could not be cleared */
__CEIDECLARE(,int,__NOTHROW,feclearexcept,(int __excepts),{ return __arch_feclearexcept(__excepts); })
#elif defined(__CRT_HAVE_feclearexcept)
/* >> feclearexcept(3)
 * @param: excepts: Set of `FE_*'
 * @return: == 0 : All exceptions indicated by `excepts' were cleared
 * @return: != 0 : At least one exception of `excepts' could not be cleared */
__CDECLARE(,int,__NOTHROW,feclearexcept,(int __excepts),(__excepts))
#elif defined(__arch_feclearexcept)
/* >> feclearexcept(3)
 * @param: excepts: Set of `FE_*'
 * @return: == 0 : All exceptions indicated by `excepts' were cleared
 * @return: != 0 : At least one exception of `excepts' could not be cleared */
__LOCAL int __NOTHROW(__LIBCCALL feclearexcept)(int __excepts) { return __arch_feclearexcept(__excepts); }
#endif /* ... */
#if defined(__CRT_HAVE_fegetexceptflag) && defined(__arch_fegetexceptflag)
/* >> fegetexceptflag(3)
 * @return: == 0 : Success
 * @return: != 0 : Unspecified error */
__CEIDECLARE_GCCNCX(__ATTR_OUT(1),int,__NOTHROW_NCX,fegetexceptflag,(fexcept_t *__flagp, int __excepts),{ return __arch_fegetexceptflag(__flagp, __excepts); })
#elif defined(__CRT_HAVE_fegetexceptflag)
/* >> fegetexceptflag(3)
 * @return: == 0 : Success
 * @return: != 0 : Unspecified error */
__CDECLARE_GCCNCX(__ATTR_OUT(1),int,__NOTHROW_NCX,fegetexceptflag,(fexcept_t *__flagp, int __excepts),(__flagp,__excepts))
#elif defined(__arch_fegetexceptflag)
/* >> fegetexceptflag(3)
 * @return: == 0 : Success
 * @return: != 0 : Unspecified error */
__LOCAL __ATTR_OUT(1) int __NOTHROW_NCX(__LIBCCALL fegetexceptflag)(fexcept_t *__flagp, int __excepts) { return __arch_fegetexceptflag(__flagp, __excepts); }
#endif /* ... */
#if defined(__CRT_HAVE_fesetexceptflag) && defined(__arch_fesetexceptflag)
/* >> fesetexceptflag(3)
 * @return: == 0 : Success
 * @return: != 0 : Unspecified error */
__CEIDECLARE_GCCNCX(__ATTR_IN(1),int,__NOTHROW_NCX,fesetexceptflag,(fexcept_t const *__flagp, int __excepts),{ return __arch_fesetexceptflag(__flagp, __excepts); })
#elif defined(__CRT_HAVE_fesetexceptflag)
/* >> fesetexceptflag(3)
 * @return: == 0 : Success
 * @return: != 0 : Unspecified error */
__CDECLARE_GCCNCX(__ATTR_IN(1),int,__NOTHROW_NCX,fesetexceptflag,(fexcept_t const *__flagp, int __excepts),(__flagp,__excepts))
#elif defined(__arch_fesetexceptflag)
/* >> fesetexceptflag(3)
 * @return: == 0 : Success
 * @return: != 0 : Unspecified error */
__LOCAL __ATTR_IN(1) int __NOTHROW_NCX(__LIBCCALL fesetexceptflag)(fexcept_t const *__flagp, int __excepts) { return __arch_fesetexceptflag(__flagp, __excepts); }
#endif /* ... */
#if defined(__CRT_HAVE_fetestexcept) && defined(__arch_fetestexcept)
/* >> fetestexcept(3) */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW,fetestexcept,(int __excepts),{ /* Do `COMPILER_IMPURE()' to supress a false warning: * https://gcc.gnu.org/bugzilla/show_bug.cgi?id=105682 */ __COMPILER_IMPURE(); return __arch_fetestexcept(__excepts); })
#elif defined(__CRT_HAVE_fetestexcept)
/* >> fetestexcept(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW,fetestexcept,(int __excepts),(__excepts))
#elif defined(__arch_fetestexcept)
/* >> fetestexcept(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW(__LIBCCALL fetestexcept)(int __excepts) { /* Do `COMPILER_IMPURE()' to supress a false warning: * https://gcc.gnu.org/bugzilla/show_bug.cgi?id=105682 */ __COMPILER_IMPURE(); return __arch_fetestexcept(__excepts); }
#endif /* ... */
#if defined(__CRT_HAVE_fegetround) && defined(__arch_fegetround)
/* >> fegetround(3)
 * Get the current rounding direction
 * @return: One of...
 *             ... `FE_TONEAREST':  round()
 *             ... `FE_DOWNWARD':   floor()
 *             ... `FE_UPWARD':     ceil()
 *             ... `FE_TOWARDZERO': trunc() */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW,fegetround,(void),{ __COMPILER_IMPURE(); return __arch_fegetround(); })
#elif defined(__CRT_HAVE_fegetround)
/* >> fegetround(3)
 * Get the current rounding direction
 * @return: One of...
 *             ... `FE_TONEAREST':  round()
 *             ... `FE_DOWNWARD':   floor()
 *             ... `FE_UPWARD':     ceil()
 *             ... `FE_TOWARDZERO': trunc() */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW,fegetround,(void),())
#elif defined(__arch_fegetround)
/* >> fegetround(3)
 * Get the current rounding direction
 * @return: One of...
 *             ... `FE_TONEAREST':  round()
 *             ... `FE_DOWNWARD':   floor()
 *             ... `FE_UPWARD':     ceil()
 *             ... `FE_TOWARDZERO': trunc() */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW(__LIBCCALL fegetround)(void) { __COMPILER_IMPURE(); return __arch_fegetround(); }
#endif /* ... */
#if defined(__CRT_HAVE_fesetround) && defined(__arch_fesetround)
/* >> fesetround(3)
 * Set the current rounding direction
 * @param: rounding_direction: One of...
 *             ... `FE_TONEAREST':  round()
 *             ... `FE_DOWNWARD':   floor()
 *             ... `FE_UPWARD':     ceil()
 *             ... `FE_TOWARDZERO': trunc() */
__CEIDECLARE(,int,__NOTHROW,fesetround,(int __rounding_direction),{ return __arch_fesetround(__rounding_direction); })
#elif defined(__CRT_HAVE_fesetround)
/* >> fesetround(3)
 * Set the current rounding direction
 * @param: rounding_direction: One of...
 *             ... `FE_TONEAREST':  round()
 *             ... `FE_DOWNWARD':   floor()
 *             ... `FE_UPWARD':     ceil()
 *             ... `FE_TOWARDZERO': trunc() */
__CDECLARE(,int,__NOTHROW,fesetround,(int __rounding_direction),(__rounding_direction))
#elif defined(__arch_fesetround)
/* >> fesetround(3)
 * Set the current rounding direction
 * @param: rounding_direction: One of...
 *             ... `FE_TONEAREST':  round()
 *             ... `FE_DOWNWARD':   floor()
 *             ... `FE_UPWARD':     ceil()
 *             ... `FE_TOWARDZERO': trunc() */
__LOCAL int __NOTHROW(__LIBCCALL fesetround)(int __rounding_direction) { return __arch_fesetround(__rounding_direction); }
#endif /* ... */
#if defined(__CRT_HAVE_fegetenv) && defined(__arch_fegetenv)
/* >> fegetenv(3) */
__CEIDECLARE_GCCNCX(__ATTR_OUT(1),int,__NOTHROW_NCX,fegetenv,(fenv_t *___envp),{ return __arch_fegetenv(___envp); })
#elif defined(__CRT_HAVE_fegetenv)
/* >> fegetenv(3) */
__CDECLARE_GCCNCX(__ATTR_OUT(1),int,__NOTHROW_NCX,fegetenv,(fenv_t *___envp),(___envp))
#elif defined(__arch_fegetenv)
/* >> fegetenv(3) */
__LOCAL __ATTR_OUT(1) int __NOTHROW_NCX(__LIBCCALL fegetenv)(fenv_t *___envp) { return __arch_fegetenv(___envp); }
#endif /* ... */
#if defined(__CRT_HAVE_feholdexcept) && defined(__arch_feholdexcept)
/* >> feholdexcept(3) */
__CEIDECLARE_GCCNCX(__ATTR_OUT(1),int,__NOTHROW_NCX,feholdexcept,(fenv_t *___envp),{ return __arch_feholdexcept(___envp); })
#elif defined(__CRT_HAVE_feholdexcept)
/* >> feholdexcept(3) */
__CDECLARE_GCCNCX(__ATTR_OUT(1),int,__NOTHROW_NCX,feholdexcept,(fenv_t *___envp),(___envp))
#elif defined(__arch_feholdexcept)
/* >> feholdexcept(3) */
__LOCAL __ATTR_OUT(1) int __NOTHROW_NCX(__LIBCCALL feholdexcept)(fenv_t *___envp) { return __arch_feholdexcept(___envp); }
#endif /* ... */
#if defined(__CRT_HAVE_fesetenv) && defined(__arch_fesetenv)
/* >> fesetenv(3) */
__CEIDECLARE_GCCNCX(__ATTR_IN(1),int,__NOTHROW_NCX,fesetenv,(fenv_t const *___envp),{ return __arch_fesetenv(___envp); })
#elif defined(__CRT_HAVE_fesetenv)
/* >> fesetenv(3) */
__CDECLARE_GCCNCX(__ATTR_IN(1),int,__NOTHROW_NCX,fesetenv,(fenv_t const *___envp),(___envp))
#elif defined(__arch_fesetenv)
/* >> fesetenv(3) */
__LOCAL __ATTR_IN(1) int __NOTHROW_NCX(__LIBCCALL fesetenv)(fenv_t const *___envp) { return __arch_fesetenv(___envp); }
#endif /* ... */
#if defined(__CRT_HAVE_feupdateenv) && defined(__arch_feupdateenv)
/* >> feupdateenv(3) */
__CEIDECLARE_GCCNCX(__ATTR_IN(1),int,__NOTHROW_NCX,feupdateenv,(fenv_t const *___envp),{ return __arch_feupdateenv(___envp); })
#elif defined(__CRT_HAVE_feupdateenv)
/* >> feupdateenv(3) */
__CDECLARE_GCCNCX(__ATTR_IN(1),int,__NOTHROW_NCX,feupdateenv,(fenv_t const *___envp),(___envp))
#elif defined(__arch_feupdateenv)
/* >> feupdateenv(3) */
__LOCAL __ATTR_IN(1) int __NOTHROW_NCX(__LIBCCALL feupdateenv)(fenv_t const *___envp) { return __arch_feupdateenv(___envp); }
#endif /* ... */
__NAMESPACE_STD_END

#ifndef __CXX_SYSTEM_HEADER
#if defined(__CRT_HAVE_feraiseexcept) || defined(__arch_feraiseexcept)
__NAMESPACE_STD_USING(feraiseexcept)
#endif /* __CRT_HAVE_feraiseexcept || __arch_feraiseexcept */
#if defined(__CRT_HAVE_feclearexcept) || defined(__arch_feclearexcept)
__NAMESPACE_STD_USING(feclearexcept)
#endif /* __CRT_HAVE_feclearexcept || __arch_feclearexcept */
#if defined(__CRT_HAVE_fegetexceptflag) || defined(__arch_fegetexceptflag)
__NAMESPACE_STD_USING(fegetexceptflag)
#endif /* __CRT_HAVE_fegetexceptflag || __arch_fegetexceptflag */
#if defined(__CRT_HAVE_fesetexceptflag) || defined(__arch_fesetexceptflag)
__NAMESPACE_STD_USING(fesetexceptflag)
#endif /* __CRT_HAVE_fesetexceptflag || __arch_fesetexceptflag */
#if defined(__CRT_HAVE_fetestexcept) || defined(__arch_fetestexcept)
__NAMESPACE_STD_USING(fetestexcept)
#endif /* __CRT_HAVE_fetestexcept || __arch_fetestexcept */
#if defined(__CRT_HAVE_fegetround) || defined(__arch_fegetround)
__NAMESPACE_STD_USING(fegetround)
#endif /* __CRT_HAVE_fegetround || __arch_fegetround */
#if defined(__CRT_HAVE_fesetround) || defined(__arch_fesetround)
__NAMESPACE_STD_USING(fesetround)
#endif /* __CRT_HAVE_fesetround || __arch_fesetround */
#if defined(__CRT_HAVE_fegetenv) || defined(__arch_fegetenv)
__NAMESPACE_STD_USING(fegetenv)
#endif /* __CRT_HAVE_fegetenv || __arch_fegetenv */
#if defined(__CRT_HAVE_feholdexcept) || defined(__arch_feholdexcept)
__NAMESPACE_STD_USING(feholdexcept)
#endif /* __CRT_HAVE_feholdexcept || __arch_feholdexcept */
#if defined(__CRT_HAVE_fesetenv) || defined(__arch_fesetenv)
__NAMESPACE_STD_USING(fesetenv)
#endif /* __CRT_HAVE_fesetenv || __arch_fesetenv */
#if defined(__CRT_HAVE_feupdateenv) || defined(__arch_feupdateenv)
__NAMESPACE_STD_USING(feupdateenv)
#endif /* __CRT_HAVE_feupdateenv || __arch_feupdateenv */
#endif /* !__CXX_SYSTEM_HEADER */
#ifdef __USE_GNU
#if defined(__CRT_HAVE_feenableexcept) && defined(__arch_feenableexcept)
/* >> feenableexcept(3)
 * @return: * : The old set of enabled exceptions */
__CEIDECLARE(,int,__NOTHROW,feenableexcept,(int __excepts),{ return __arch_feenableexcept(__excepts); })
#elif defined(__CRT_HAVE_feenableexcept)
/* >> feenableexcept(3)
 * @return: * : The old set of enabled exceptions */
__CDECLARE(,int,__NOTHROW,feenableexcept,(int __excepts),(__excepts))
#elif defined(__arch_feenableexcept)
/* >> feenableexcept(3)
 * @return: * : The old set of enabled exceptions */
__LOCAL int __NOTHROW(__LIBCCALL feenableexcept)(int __excepts) { return __arch_feenableexcept(__excepts); }
#endif /* ... */
#if defined(__CRT_HAVE_fedisableexcept) && defined(__arch_fedisableexcept)
/* >> fedisableexcept(3)
 * @return: * : The old set of enabled exceptions */
__CEIDECLARE(,int,__NOTHROW,fedisableexcept,(int __excepts),{ return __arch_fedisableexcept(__excepts); })
#elif defined(__CRT_HAVE_fedisableexcept)
/* >> fedisableexcept(3)
 * @return: * : The old set of enabled exceptions */
__CDECLARE(,int,__NOTHROW,fedisableexcept,(int __excepts),(__excepts))
#elif defined(__arch_fedisableexcept)
/* >> fedisableexcept(3)
 * @return: * : The old set of enabled exceptions */
__LOCAL int __NOTHROW(__LIBCCALL fedisableexcept)(int __excepts) { return __arch_fedisableexcept(__excepts); }
#endif /* ... */
#if defined(__CRT_HAVE_fegetexcept) && defined(__arch_fegetexcept)
/* >> fegetexcept(3) */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW,fegetexcept,(void),{ __COMPILER_IMPURE(); return __arch_fegetexcept(); })
#elif defined(__CRT_HAVE_fegetexcept)
/* >> fegetexcept(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW,fegetexcept,(void),())
#elif defined(__arch_fegetexcept)
/* >> fegetexcept(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW(__LIBCCALL fegetexcept)(void) { __COMPILER_IMPURE(); return __arch_fegetexcept(); }
#endif /* ... */
#endif /* __USE_GNU */

#if defined(__USE_GNU) || defined(__STDC_WANT_IEC_60559_BFP_EXT__)
typedef __femode_t femode_t;
#if !defined(FE_DFL_MODE) && defined(__FE_DFL_MODE)
#define FE_DFL_MODE __FE_DFL_MODE
#endif /* !FE_DFL_MODE && __FE_DFL_MODE */
#if defined(__CRT_HAVE_fesetexcept) && defined(__arch_fesetexcept)
__CEIDECLARE(,int,__NOTHROW,fesetexcept,(int __excepts),{ return __arch_fesetexcept(__excepts); })
#elif defined(__CRT_HAVE_fesetexcept)
__CDECLARE(,int,__NOTHROW,fesetexcept,(int __excepts),(__excepts))
#elif defined(__arch_fesetexcept)
__LOCAL int __NOTHROW(__LIBCCALL fesetexcept)(int __excepts) { return __arch_fesetexcept(__excepts); }
#endif /* ... */
#if defined(__CRT_HAVE_fetestexceptflag) && defined(__arch_fetestexceptflag)
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,fetestexceptflag,(__fexcept_t const *__flagp, int __excepts),{ return __arch_fetestexceptflag(__flagp, __excepts); })
#elif defined(__CRT_HAVE_fetestexceptflag)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,fetestexceptflag,(__fexcept_t const *__flagp, int __excepts),(__flagp,__excepts))
#elif defined(__arch_fetestexceptflag)
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL fetestexceptflag)(__fexcept_t const *__flagp, int __excepts) { return __arch_fetestexceptflag(__flagp, __excepts); }
#endif /* ... */
#if defined(__CRT_HAVE_fegetmode) && defined(__arch_fegetmode)
__CEIDECLARE(__ATTR_OUT(1),int,__NOTHROW_NCX,fegetmode,(femode_t *__modep),{ return __arch_fegetmode(__modep); })
#elif defined(__CRT_HAVE_fegetmode)
__CDECLARE(__ATTR_OUT(1),int,__NOTHROW_NCX,fegetmode,(femode_t *__modep),(__modep))
#elif defined(__arch_fegetmode)
__LOCAL __ATTR_OUT(1) int __NOTHROW_NCX(__LIBCCALL fegetmode)(femode_t *__modep) { return __arch_fegetmode(__modep); }
#endif /* ... */
#if defined(__CRT_HAVE_fesetmode) && defined(__arch_fesetmode)
__CEIDECLARE(,int,__NOTHROW_NCX,fesetmode,(femode_t const *__modep),{ return __arch_fesetmode(__modep); })
#elif defined(__CRT_HAVE_fesetmode)
__CDECLARE(,int,__NOTHROW_NCX,fesetmode,(femode_t const *__modep),(__modep))
#elif defined(__arch_fesetmode)
__LOCAL int __NOTHROW_NCX(__LIBCCALL fesetmode)(femode_t const *__modep) { return __arch_fesetmode(__modep); }
#endif /* ... */

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
