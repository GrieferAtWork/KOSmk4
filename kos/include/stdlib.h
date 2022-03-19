/* HASH CRC-32:0x10cfe7bb */
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
/* (>) Standard: ISO C89 (ANSI X3.159-1989) */
/* (>) Standard: POSIX.1c (Issue 3, IEEE Std 1003.1c-1995) */
/* (#) Portability: Cygwin        (/newlib/libc/include/stdlib.h) */
/* (#) Portability: DJGPP         (/include/stdlib.h) */
/* (#) Portability: FreeBSD       (/include/stdlib.h) */
/* (#) Portability: GNU C Library (/stdlib/stdlib.h) */
/* (#) Portability: MSVC          (/include/stdlib.h) */
/* (#) Portability: MinGW         (/mingw-w64-headers/crt/stdlib.h) */
/* (#) Portability: NetBSD        (/include/stdlib.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/stdlib.h) */
/* (#) Portability: OpenBSD       (/include/stdlib.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/stdlib.h) */
/* (#) Portability: Windows Kits  (/ucrt/stdlib.h) */
/* (#) Portability: diet libc     (/include/stdlib.h) */
/* (#) Portability: libbsd        (/include/bsd/stdlib.h) */
/* (#) Portability: libc4/5       (/include/stdlib.h) */
/* (#) Portability: libc6         (/include/stdlib.h) */
/* (#) Portability: musl libc     (/include/stdlib.h) */
/* (#) Portability: uClibc        (/include/stdlib.h) */
#ifndef _STDLIB_H
#define _STDLIB_H 1

#ifdef _CXX_STDONLY_CSTDLIB
#ifdef __CXX_SYSTEM_HEADER
#undef _STDLIB_H /* Allow the C-header to be re-included to import all std::-symbols into the global namespace. */
#else /* __CXX_SYSTEM_HEADER */
/* Import all symbols into the global namespace when re-including "stdlib.h" after "cstdlib" */
#ifndef __size_t_defined
#define __size_t_defined
__NAMESPACE_STD_USING(size_t)
#endif /* !__size_t_defined */
#ifndef __div_t_defined
#define __div_t_defined
__NAMESPACE_STD_USING(div_t)
#endif /* !__div_t_defined */
#ifndef __ldiv_t_defined
#define __ldiv_t_defined
__NAMESPACE_STD_USING(ldiv_t)
#endif /* !__ldiv_t_defined */
#ifdef __USE_ISOC99
#ifndef __lldiv_t_defined
#define __lldiv_t_defined
__NAMESPACE_STD_USING(lldiv_t)
#endif /* !__lldiv_t_defined */
#endif /* __USE_ISOC99 */
#if !defined(__qsort_defined) && defined(__std_qsort_defined)
#define __qsort_defined
__NAMESPACE_STD_USING(qsort)
#endif /* !__qsort_defined && __std_qsort_defined */
#if !defined(__bsearch_defined) && defined(__std_bsearch_defined)
#define __bsearch_defined
__NAMESPACE_STD_USING(bsearch)
#endif /* !__bsearch_defined && __std_bsearch_defined */
__NAMESPACE_STD_USING(labs)
#ifdef __USE_ISOC99
__NAMESPACE_STD_USING(llabs)
#endif /* __USE_ISOC99 */
__NAMESPACE_STD_USING(ldiv)
#ifdef __USE_ISOC99
__NAMESPACE_STD_USING(lldiv)
#endif /* __USE_ISOC99 */
__NAMESPACE_STD_USING(abs)
__NAMESPACE_STD_USING(div)
#include <libc/template/environ.h>
#if defined(__CRT_HAVE_getenv) || defined(__LOCAL_environ)
__NAMESPACE_STD_USING(getenv)
#endif /* __CRT_HAVE_getenv || __LOCAL_environ */
__NAMESPACE_STD_USING(mblen)
__NAMESPACE_STD_USING(mbtowc)
__NAMESPACE_STD_USING(wctomb)
__NAMESPACE_STD_USING(mbstowcs)
__NAMESPACE_STD_USING(wcstombs)
#if !defined(__system_defined) && defined(__std_system_defined)
#define __system_defined
__NAMESPACE_STD_USING(system)
#endif /* !__system_defined && __std_system_defined */
#if !defined(__abort_defined) && defined(__std_abort_defined)
#define __abort_defined
__NAMESPACE_STD_USING(abort)
#endif /* !__abort_defined && __std_abort_defined */
#if !defined(__exit_defined) && defined(__std_exit_defined)
#define __exit_defined
__NAMESPACE_STD_USING(exit)
#endif /* !__exit_defined && __std_exit_defined */
#if defined(__CRT_HAVE_atexit) || defined(__CRT_HAVE__crt_atexit) || defined(__CRT_HAVE_at_quick_exit) || defined(__CRT_HAVE__crt_at_quick_exit)
__NAMESPACE_STD_USING(atexit)
#endif /* __CRT_HAVE_atexit || __CRT_HAVE__crt_atexit || __CRT_HAVE_at_quick_exit || __CRT_HAVE__crt_at_quick_exit */
#if defined(__USE_ISOC11) || defined(__USE_ISOCXX11)
#if defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE_exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE__Exit)
__NAMESPACE_STD_USING(quick_exit)
#endif /* __CRT_HAVE_quick_exit || __CRT_HAVE_exit || __CRT_HAVE__exit || __CRT_HAVE__Exit */
#if defined(__CRT_HAVE_at_quick_exit) || defined(__CRT_HAVE__crt_at_quick_exit) || defined(__CRT_HAVE_atexit) || defined(__CRT_HAVE__crt_atexit)
__NAMESPACE_STD_USING(at_quick_exit)
#endif /* __CRT_HAVE_at_quick_exit || __CRT_HAVE__crt_at_quick_exit || __CRT_HAVE_atexit || __CRT_HAVE__crt_atexit */
#endif /* __USE_ISOC11 || __USE_ISOCXX11 */
#ifdef __USE_ISOC99
#if defined(__CRT_HAVE__Exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE_exit)
__NAMESPACE_STD_USING(_Exit)
#endif /* __CRT_HAVE__Exit || __CRT_HAVE__exit || __CRT_HAVE_quick_exit || __CRT_HAVE_exit */
#endif /* __USE_ISOC99 */
#if !defined(__malloc_defined) && defined(__std_malloc_defined)
#define __malloc_defined
__NAMESPACE_STD_USING(malloc)
#endif /* !__malloc_defined && __std_malloc_defined */
#if !defined(__calloc_defined) && defined(__std_calloc_defined)
#define __calloc_defined
__NAMESPACE_STD_USING(calloc)
#endif /* !__calloc_defined && __std_calloc_defined */
#if !defined(__realloc_defined) && defined(__std_realloc_defined)
#define __realloc_defined
__NAMESPACE_STD_USING(realloc)
#endif /* !__realloc_defined && __std_realloc_defined */
#if !defined(__free_defined) && defined(__std_free_defined)
#define __free_defined
__NAMESPACE_STD_USING(free)
#endif /* !__free_defined && __std_free_defined */
__NAMESPACE_STD_USING(srand)
__NAMESPACE_STD_USING(rand)
__NAMESPACE_STD_USING(atoi)
__NAMESPACE_STD_USING(atol)
__NAMESPACE_STD_USING(atoll)
__NAMESPACE_STD_USING(strtoul)
__NAMESPACE_STD_USING(strtol)
#if !defined(__strtoull_defined) && defined(__std_strtoull_defined)
#define __strtoull_defined
__NAMESPACE_STD_USING(strtoull)
#endif /* !__strtoull_defined && __std_strtoull_defined */
#if !defined(__strtoll_defined) && defined(__std_strtoll_defined)
#define __strtoll_defined
__NAMESPACE_STD_USING(strtoll)
#endif /* !__strtoll_defined && __std_strtoll_defined */
#ifndef __NO_FPU
__NAMESPACE_STD_USING(atof)
__NAMESPACE_STD_USING(strtod)
#if !defined(__strtof_defined) && defined(__std_strtof_defined)
#define __strtof_defined
__NAMESPACE_STD_USING(strtof)
#endif /* !__strtof_defined && __std_strtof_defined */
#if !defined(__strtold_defined) && defined(__std_strtold_defined)
#define __strtold_defined
__NAMESPACE_STD_USING(strtold)
#endif /* !__strtold_defined && __std_strtold_defined */
#endif /* !__NO_FPU */
#if !defined(__aligned_alloc_defined) && defined(__std_aligned_alloc_defined)
#define __aligned_alloc_defined
__NAMESPACE_STD_USING(aligned_alloc)
#endif /* !__aligned_alloc_defined && __std_aligned_alloc_defined */
#undef _CXX_STDONLY_CSTDLIB
#endif /* !__CXX_SYSTEM_HEADER */
#else /* _CXX_STDONLY_CSTDLIB */
#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#include <hybrid/typecore.h>

#include <asm/crt/stdlib.h>
#include <asm/os/oflags.h> /* __O_LARGEFILE */
#include <asm/os/stdlib.h>
#include <bits/types.h>
#include <kos/anno.h>

#ifdef __USE_MISC
#include <alloca.h>
#endif /* __USE_MISC */

#ifdef __USE_DOS
#include <hybrid/__byteswap.h>
#include <bits/crt/sys_errlist.h>
#include <xlocale.h>
#endif /* __USE_DOS */

#ifdef __USE_GNU
#include <xlocale.h>
#endif /* __USE_GNU */

#ifdef __USE_SOLARIS
#include <getopt.h>
#endif /* __USE_SOLARIS */

#ifdef __USE_NETBSD
#include <asm/crt/humanize_number.h>
#endif /* __USE_NETBSD */

#if defined(__USE_KOS) && defined(__USE_STRING_OVERLOADS)
#include <hybrid/__overflow.h>
#endif /* __USE_KOS && __USE_STRING_OVERLOADS */

#if defined(__USE_XOPEN) || defined(__USE_XOPEN2K8)
#include <parts/waitmacros.h>
#endif /* __USE_XOPEN || __USE_XOPEN2K8 */

#if defined(__USE_KOS) && defined(__USE_STRING_OVERLOADS)
#include <hybrid/__overflow.h>
#ifndef __cplusplus
#include <hybrid/pp/__va_nargs.h>
#endif /* !__cplusplus */
#endif /* __USE_KOS && __USE_STRING_OVERLOADS */

__SYSDECL_BEGIN

#ifdef __RAND_MAX
#define RAND_MAX __RAND_MAX
#endif /* __RAND_MAX */
#ifdef __EXIT_SUCCESS
#define EXIT_SUCCESS __EXIT_SUCCESS
#endif /* __EXIT_SUCCESS */
#ifdef __EXIT_FAILURE
#define EXIT_FAILURE __EXIT_FAILURE
#endif /* __EXIT_FAILURE */

#ifdef __CC__

#ifndef __std_size_t_defined
#define __std_size_t_defined
__NAMESPACE_STD_BEGIN
typedef __SIZE_TYPE__ size_t;
__NAMESPACE_STD_END
#endif /* !__std_size_t_defined */

#ifndef __CXX_SYSTEM_HEADER
#ifndef __size_t_defined
#define __size_t_defined
__NAMESPACE_STD_USING(size_t)
#endif /* !__size_t_defined */
#endif /* !__CXX_SYSTEM_HEADER */

#ifndef __wchar_t_defined
#define __wchar_t_defined
typedef __WCHAR_TYPE__ wchar_t;
#endif /* !__wchar_t_defined */

#ifndef NULL
#define NULL __NULLPTR
#endif /* !NULL */

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("quot")
#pragma push_macro("rem")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef quot
#undef rem
struct __div_struct {
	int quot;
	int rem;
};
struct __ldiv_struct {
	long quot;
	long rem;
};
#ifdef __USE_ISOC99
struct __lldiv_struct {
	__LONGLONG quot;
	__LONGLONG rem;
};
#endif /* __USE_ISOC99 */
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("rem")
#pragma pop_macro("quot")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

__NAMESPACE_STD_BEGIN
#ifndef __std_div_t_defined
#define __std_div_t_defined
typedef struct __div_struct div_t;
#endif /* !__std_div_t_defined */
#ifndef __std_ldiv_t_defined
#define __std_ldiv_t_defined
typedef struct __ldiv_struct ldiv_t;
#endif /* !__std_ldiv_t_defined */
#ifdef __USE_ISOC99
#ifndef __std_lldiv_t_defined
#define __std_lldiv_t_defined
typedef struct __lldiv_struct lldiv_t;
#endif /* !__std_lldiv_t_defined */
#endif /* __USE_ISOC99 */
__NAMESPACE_STD_END

#ifndef __CXX_SYSTEM_HEADER
#ifndef __div_t_defined
#define __div_t_defined
__NAMESPACE_STD_USING(div_t)
#endif /* !__div_t_defined */
#ifndef __ldiv_t_defined
#define __ldiv_t_defined
__NAMESPACE_STD_USING(ldiv_t)
#endif /* !__ldiv_t_defined */
#ifdef __USE_ISOC99
#ifndef __lldiv_t_defined
#define __lldiv_t_defined
__NAMESPACE_STD_USING(lldiv_t)
#endif /* !__lldiv_t_defined */
#endif /* __USE_ISOC99 */
#endif /* !__CXX_SYSTEM_HEADER */

#ifndef __COMPAR_FN_T
#define __COMPAR_FN_T 1
#ifndef ____compar_fn_t_defined
#define ____compar_fn_t_defined
typedef int (__LIBCCALL *__compar_fn_t)(void const *__a, void const *__b);
#endif /* !____compar_fn_t_defined */
#ifdef __USE_GNU
typedef __compar_fn_t comparison_fn_t;
#endif /* __USE_GNU */
#endif /* __COMPAR_FN_T */


#ifdef __USE_KOS
#ifndef __compar_d_fn_t_defined
#define __compar_d_fn_t_defined
typedef int (__LIBCCALL *__compar_d_fn_t)(void const *__a, void const *__b, void *__arg);
#endif /* !__compar_d_fn_t_defined */
#ifdef __CRT_HAVE_bsearch_r
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STDLIB_H_PROTO)
extern "C++" {
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2, 5)),void *,__THROWING,bsearch_r,(void const *__pkey, void *__pbase, __SIZE_TYPE__ __item_count, __SIZE_TYPE__ __item_size, int (__LIBCCALL *__compar)(void const *__a, void const *__b, void *__arg), void *__arg),bsearch_r,(__pkey,__pbase,__item_count,__item_size,__compar,__arg))
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2, 5)),void const *,__THROWING,bsearch_r,(void const *__pkey, void const *__pbase, __SIZE_TYPE__ __item_count, __SIZE_TYPE__ __item_size, int (__LIBCCALL *__compar)(void const *__a, void const *__b, void *__arg), void *__arg),bsearch_r,(__pkey,__pbase,__item_count,__item_size,__compar,__arg))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STDLIB_H_PROTO */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 2, 5)),void *,__THROWING,bsearch_r,(void const *__pkey, void const *__pbase, __SIZE_TYPE__ __item_count, __SIZE_TYPE__ __item_size, int (__LIBCCALL *__compar)(void const *__a, void const *__b, void *__arg), void *__arg),(__pkey,__pbase,__item_count,__item_size,__compar,__arg))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STDLIB_H_PROTO */
#else /* __CRT_HAVE_bsearch_r */
#include <libc/local/stdlib/bsearch_r.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STDLIB_H_PROTO)
extern "C++" {
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 2, 5)) void *(__LIBCCALL bsearch_r)(void const *__pkey, void *__pbase, __SIZE_TYPE__ __item_count, __SIZE_TYPE__ __item_size, int (__LIBCCALL *__compar)(void const *__a, void const *__b, void *__arg), void *__arg) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(bsearch_r))(__pkey, __pbase, __item_count, __item_size, __compar, __arg); }
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 2, 5)) void const *(__LIBCCALL bsearch_r)(void const *__pkey, void const *__pbase, __SIZE_TYPE__ __item_count, __SIZE_TYPE__ __item_size, int (__LIBCCALL *__compar)(void const *__a, void const *__b, void *__arg), void *__arg) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(bsearch_r))(__pkey, __pbase, __item_count, __item_size, __compar, __arg); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STDLIB_H_PROTO */
__NAMESPACE_LOCAL_USING_OR_IMPL(bsearch_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 2, 5)) void *(__LIBCCALL bsearch_r)(void const *__pkey, void const *__pbase, __SIZE_TYPE__ __item_count, __SIZE_TYPE__ __item_size, int (__LIBCCALL *__compar)(void const *__a, void const *__b, void *__arg), void *__arg) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(bsearch_r))(__pkey, __pbase, __item_count, __item_size, __compar, __arg); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STDLIB_H_PROTO */
#endif /* !__CRT_HAVE_bsearch_r */
#endif /* __USE_KOS */

__NAMESPACE_STD_BEGIN
#ifndef __std_qsort_defined
#define __std_qsort_defined
#ifdef __qsort_defined
__NAMESPACE_GLB_USING_OR_IMPL(qsort, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 4)) void (__LIBCCALL qsort)(void *__pbase, size_t __item_count, size_t __item_size, int (__LIBCCALL *__compar)(void const *__a, void const *__b)) __THROWS(...) { :: qsort(__pbase, __item_count, __item_size, __compar); })
#elif defined(__CRT_HAVE_qsort)
__CDECLARE_VOID(__ATTR_NONNULL((1, 4)),__THROWING,qsort,(void *__pbase, size_t __item_count, size_t __item_size, int (__LIBCCALL *__compar)(void const *__a, void const *__b)),(__pbase,__item_count,__item_size,__compar))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/stdlib/qsort.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(qsort, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 4)) void (__LIBCCALL qsort)(void *__pbase, size_t __item_count, size_t __item_size, int (__LIBCCALL *__compar)(void const *__a, void const *__b)) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(qsort))(__pbase, __item_count, __item_size, __compar); })
#endif /* !... */
#endif /* !__std_qsort_defined */
#ifndef __std_bsearch_defined
#define __std_bsearch_defined
#ifdef __bsearch_defined
#if !defined(__COMPILER_HAVE_BUG_BLOATY_CXX_USING) || defined(__NO_NAMESPACE_STD)
__NAMESPACE_GLB_USING(bsearch)
#else /* !__COMPILER_HAVE_BUG_BLOATY_CXX_USING || __NO_NAMESPACE_STD */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STDLIB_H_PROTO)
extern "C++" {
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 2, 5)) void *(__LIBCCALL bsearch)(void const *__pkey, void *__pbase, size_t __item_count, size_t __item_size, int (__LIBCCALL *__compar)(void const *__a, void const *__b)) __THROWS(...) { return :: bsearch(__pkey, __pbase, __item_count, __item_size, __compar); }
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 2, 5)) void const *(__LIBCCALL bsearch)(void const *__pkey, void const *__pbase, size_t __item_count, size_t __item_size, int (__LIBCCALL *__compar)(void const *__a, void const *__b)) __THROWS(...) { return :: bsearch(__pkey, __pbase, __item_count, __item_size, __compar); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STDLIB_H_PROTO */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 2, 5)) void *(__LIBCCALL bsearch)(void const *__pkey, void const *__pbase, size_t __item_count, size_t __item_size, int (__LIBCCALL *__compar)(void const *__a, void const *__b)) __THROWS(...) { return :: bsearch(__pkey, __pbase, __item_count, __item_size, __compar); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STDLIB_H_PROTO */
#endif /* __COMPILER_HAVE_BUG_BLOATY_CXX_USING && !__NO_NAMESPACE_STD */
#elif defined(__CRT_HAVE_bsearch)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STDLIB_H_PROTO)
extern "C++" {
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2, 5)),void *,__THROWING,bsearch,(void const *__pkey, void *__pbase, size_t __item_count, size_t __item_size, int (__LIBCCALL *__compar)(void const *__a, void const *__b)),bsearch,(__pkey,__pbase,__item_count,__item_size,__compar))
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2, 5)),void const *,__THROWING,bsearch,(void const *__pkey, void const *__pbase, size_t __item_count, size_t __item_size, int (__LIBCCALL *__compar)(void const *__a, void const *__b)),bsearch,(__pkey,__pbase,__item_count,__item_size,__compar))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STDLIB_H_PROTO */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 2, 5)),void *,__THROWING,bsearch,(void const *__pkey, void const *__pbase, size_t __item_count, size_t __item_size, int (__LIBCCALL *__compar)(void const *__a, void const *__b)),(__pkey,__pbase,__item_count,__item_size,__compar))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STDLIB_H_PROTO */
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/stdlib/bsearch.h>
__NAMESPACE_STD_BEGIN
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STDLIB_H_PROTO)
extern "C++" {
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 2, 5)) void *(__LIBCCALL bsearch)(void const *__pkey, void *__pbase, size_t __item_count, size_t __item_size, int (__LIBCCALL *__compar)(void const *__a, void const *__b)) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(bsearch))(__pkey, __pbase, __item_count, __item_size, __compar); }
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 2, 5)) void const *(__LIBCCALL bsearch)(void const *__pkey, void const *__pbase, size_t __item_count, size_t __item_size, int (__LIBCCALL *__compar)(void const *__a, void const *__b)) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(bsearch))(__pkey, __pbase, __item_count, __item_size, __compar); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STDLIB_H_PROTO */
__NAMESPACE_LOCAL_USING_OR_IMPL(bsearch, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 2, 5)) void *(__LIBCCALL bsearch)(void const *__pkey, void const *__pbase, size_t __item_count, size_t __item_size, int (__LIBCCALL *__compar)(void const *__a, void const *__b)) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(bsearch))(__pkey, __pbase, __item_count, __item_size, __compar); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STDLIB_H_PROTO */
#endif /* !... */
#endif /* !__std_bsearch_defined */
#if __has_builtin(__builtin_labs) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_labs)
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,long,__NOTHROW,labs,(long __x),{ return __builtin_labs(__x); })
#elif defined(__CRT_HAVE_labs)
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,long,__NOTHROW,labs,(long __x),(__x))
#elif defined(__CRT_HAVE_abs) && __SIZEOF_LONG__ == __SIZEOF_INT__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long,__NOTHROW,labs,(long __x),abs,(__x))
#elif defined(__CRT_HAVE_llabs) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long,__NOTHROW,labs,(long __x),llabs,(__x))
#elif defined(__CRT_HAVE_qabs) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long,__NOTHROW,labs,(long __x),qabs,(__x))
#elif defined(__CRT_HAVE_imaxabs) && __SIZEOF_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long,__NOTHROW,labs,(long __x),imaxabs,(__x))
#elif defined(__CRT_HAVE__abs64) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long,__NOTHROW,labs,(long __x),_abs64,(__x))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/stdlib/labs.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(labs, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED long __NOTHROW(__LIBCCALL labs)(long __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(labs))(__x); })
#endif /* !... */
#ifdef __USE_ISOC99
#if __has_builtin(__builtin_llabs) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_llabs)
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,llabs,(__LONGLONG __x),{ return __builtin_llabs(__x); })
#elif defined(__CRT_HAVE_llabs)
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,llabs,(__LONGLONG __x),(__x))
#elif defined(__CRT_HAVE_qabs)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,llabs,(__LONGLONG __x),qabs,(__x))
#elif defined(__CRT_HAVE_abs) && __SIZEOF_LONG_LONG__ == __SIZEOF_INT__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,llabs,(__LONGLONG __x),abs,(__x))
#elif defined(__CRT_HAVE_labs) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,llabs,(__LONGLONG __x),labs,(__x))
#elif defined(__CRT_HAVE_imaxabs) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,llabs,(__LONGLONG __x),imaxabs,(__x))
#elif defined(__CRT_HAVE__abs64) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,llabs,(__LONGLONG __x),_abs64,(__x))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/stdlib/llabs.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(llabs, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __LONGLONG __NOTHROW(__LIBCCALL llabs)(__LONGLONG __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(llabs))(__x); })
#endif /* !... */
#endif /* __USE_ISOC99 */
#ifdef __CRT_HAVE_ldiv
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,struct __ldiv_struct,__NOTHROW_NCX,ldiv,(long __numer, long __denom),(__numer,__denom))
#elif defined(__CRT_HAVE_div) && __SIZEOF_LONG__ == __SIZEOF_INT__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,struct __ldiv_struct,__NOTHROW_NCX,ldiv,(long __numer, long __denom),div,(__numer,__denom))
#elif defined(__CRT_HAVE_lldiv) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,struct __ldiv_struct,__NOTHROW_NCX,ldiv,(long __numer, long __denom),lldiv,(__numer,__denom))
#elif defined(__CRT_HAVE_qdiv) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,struct __ldiv_struct,__NOTHROW_NCX,ldiv,(long __numer, long __denom),qdiv,(__numer,__denom))
#elif defined(__CRT_HAVE_imaxdiv) && __SIZEOF_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,struct __ldiv_struct,__NOTHROW_NCX,ldiv,(long __numer, long __denom),imaxdiv,(__numer,__denom))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/stdlib/ldiv.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(ldiv, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED struct __ldiv_struct __NOTHROW_NCX(__LIBCCALL ldiv)(long __numer, long __denom) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ldiv))(__numer, __denom); })
#endif /* !... */
#ifdef __USE_ISOC99
#ifdef __CRT_HAVE_lldiv
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,struct __lldiv_struct,__NOTHROW_NCX,lldiv,(__LONGLONG __numer, __LONGLONG __denom),(__numer,__denom))
#elif defined(__CRT_HAVE_qdiv)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,struct __lldiv_struct,__NOTHROW_NCX,lldiv,(__LONGLONG __numer, __LONGLONG __denom),qdiv,(__numer,__denom))
#elif defined(__CRT_HAVE_div) && __SIZEOF_LONG_LONG__ == __SIZEOF_INT__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,struct __lldiv_struct,__NOTHROW_NCX,lldiv,(__LONGLONG __numer, __LONGLONG __denom),div,(__numer,__denom))
#elif defined(__CRT_HAVE_ldiv) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,struct __lldiv_struct,__NOTHROW_NCX,lldiv,(__LONGLONG __numer, __LONGLONG __denom),ldiv,(__numer,__denom))
#elif defined(__CRT_HAVE_imaxdiv) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,struct __lldiv_struct,__NOTHROW_NCX,lldiv,(__LONGLONG __numer, __LONGLONG __denom),imaxdiv,(__numer,__denom))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/stdlib/lldiv.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(lldiv, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED struct __lldiv_struct __NOTHROW_NCX(__LIBCCALL lldiv)(__LONGLONG __numer, __LONGLONG __denom) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lldiv))(__numer, __denom); })
#endif /* !... */
#endif /* __USE_ISOC99 */
#if __has_builtin(__builtin_abs) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_abs)
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,abs,(int __x),{ return __builtin_abs(__x); })
#elif defined(__CRT_HAVE_abs)
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,abs,(int __x),(__x))
#elif defined(__CRT_HAVE_labs) && __SIZEOF_INT__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,abs,(int __x),labs,(__x))
#elif defined(__CRT_HAVE_llabs) && __SIZEOF_INT__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,abs,(int __x),llabs,(__x))
#elif defined(__CRT_HAVE_qabs) && __SIZEOF_INT__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,abs,(int __x),qabs,(__x))
#elif defined(__CRT_HAVE_imaxabs) && __SIZEOF_INT__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,abs,(int __x),imaxabs,(__x))
#elif defined(__CRT_HAVE__abs64) && __SIZEOF_INT__ == 8
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,abs,(int __x),_abs64,(__x))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/stdlib/abs.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(abs, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL abs)(int __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(abs))(__x); })
#endif /* !... */
#ifdef __CRT_HAVE_div
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,struct __div_struct,__NOTHROW_NCX,div,(int __numer, int __denom),(__numer,__denom))
#elif defined(__CRT_HAVE_ldiv) && __SIZEOF_INT__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,struct __div_struct,__NOTHROW_NCX,div,(int __numer, int __denom),ldiv,(__numer,__denom))
#elif defined(__CRT_HAVE_lldiv) && __SIZEOF_INT__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,struct __div_struct,__NOTHROW_NCX,div,(int __numer, int __denom),lldiv,(__numer,__denom))
#elif defined(__CRT_HAVE_qdiv) && __SIZEOF_INT__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,struct __div_struct,__NOTHROW_NCX,div,(int __numer, int __denom),qdiv,(__numer,__denom))
#elif defined(__CRT_HAVE_imaxdiv) && __SIZEOF_INT__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,struct __div_struct,__NOTHROW_NCX,div,(int __numer, int __denom),imaxdiv,(__numer,__denom))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/stdlib/div.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(div, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED struct __div_struct __NOTHROW_NCX(__LIBCCALL div)(int __numer, int __denom) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(div))(__numer, __denom); })
#endif /* !... */
#ifdef __cplusplus
#ifdef __CORRECT_ISO_CPP_STDLIB_H_PROTO
extern "C++" {
#if __has_builtin(__builtin_labs) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_labs)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long,__NOTHROW,abs,(long __x),labs,{ return __builtin_labs(__x); })
#elif defined(__CRT_HAVE_labs)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long,__NOTHROW,abs,(long __x),labs,(__x))
#elif defined(__CRT_HAVE_abs) && __SIZEOF_LONG__ == __SIZEOF_INT__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long,__NOTHROW,abs,(long __x),abs,(__x))
#elif defined(__CRT_HAVE_llabs) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long,__NOTHROW,abs,(long __x),llabs,(__x))
#elif defined(__CRT_HAVE_qabs) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long,__NOTHROW,abs,(long __x),qabs,(__x))
#elif defined(__CRT_HAVE_imaxabs) && __SIZEOF_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long,__NOTHROW,abs,(long __x),imaxabs,(__x))
#elif defined(__CRT_HAVE__abs64) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long,__NOTHROW,abs,(long __x),_abs64,(__x))
#else /* ... */
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/stdlib/labs.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED long __NOTHROW(__LIBCCALL abs)(long __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(labs))(__x); }
#endif /* !... */
#ifdef __CRT_HAVE_ldiv
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,struct __ldiv_struct,__NOTHROW_NCX,div,(long __numer, long __denom),ldiv,(__numer,__denom))
#elif defined(__CRT_HAVE_div) && __SIZEOF_LONG__ == __SIZEOF_INT__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,struct __ldiv_struct,__NOTHROW_NCX,div,(long __numer, long __denom),div,(__numer,__denom))
#elif defined(__CRT_HAVE_lldiv) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,struct __ldiv_struct,__NOTHROW_NCX,div,(long __numer, long __denom),lldiv,(__numer,__denom))
#elif defined(__CRT_HAVE_qdiv) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,struct __ldiv_struct,__NOTHROW_NCX,div,(long __numer, long __denom),qdiv,(__numer,__denom))
#elif defined(__CRT_HAVE_imaxdiv) && __SIZEOF_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,struct __ldiv_struct,__NOTHROW_NCX,div,(long __numer, long __denom),imaxdiv,(__numer,__denom))
#else /* ... */
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/stdlib/ldiv.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED struct __ldiv_struct __NOTHROW_NCX(__LIBCCALL div)(long __numer, long __denom) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ldiv))(__numer, __denom); }
#endif /* !... */
} /* extern "C++" */
#if defined(__USE_ISOC99) && defined(__COMPILER_HAVE_LONGLONG)
extern "C++" {
#if __has_builtin(__builtin_llabs) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_llabs)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,abs,(__LONGLONG __x),llabs,{ return __builtin_llabs(__x); })
#elif defined(__CRT_HAVE_llabs)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,abs,(__LONGLONG __x),llabs,(__x))
#elif defined(__CRT_HAVE_qabs)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,abs,(__LONGLONG __x),qabs,(__x))
#elif defined(__CRT_HAVE_abs) && __SIZEOF_LONG_LONG__ == __SIZEOF_INT__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,abs,(__LONGLONG __x),abs,(__x))
#elif defined(__CRT_HAVE_labs) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,abs,(__LONGLONG __x),labs,(__x))
#elif defined(__CRT_HAVE_imaxabs) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,abs,(__LONGLONG __x),imaxabs,(__x))
#elif defined(__CRT_HAVE__abs64) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,abs,(__LONGLONG __x),_abs64,(__x))
#else /* ... */
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/stdlib/llabs.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __LONGLONG __NOTHROW(__LIBCCALL abs)(__LONGLONG __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(llabs))(__x); }
#endif /* !... */
#ifdef __CRT_HAVE_lldiv
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,struct __lldiv_struct,__NOTHROW_NCX,div,(__LONGLONG __numer, __LONGLONG __denom),lldiv,(__numer,__denom))
#elif defined(__CRT_HAVE_qdiv)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,struct __lldiv_struct,__NOTHROW_NCX,div,(__LONGLONG __numer, __LONGLONG __denom),qdiv,(__numer,__denom))
#elif defined(__CRT_HAVE_div) && __SIZEOF_LONG_LONG__ == __SIZEOF_INT__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,struct __lldiv_struct,__NOTHROW_NCX,div,(__LONGLONG __numer, __LONGLONG __denom),div,(__numer,__denom))
#elif defined(__CRT_HAVE_ldiv) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,struct __lldiv_struct,__NOTHROW_NCX,div,(__LONGLONG __numer, __LONGLONG __denom),ldiv,(__numer,__denom))
#elif defined(__CRT_HAVE_imaxdiv) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,struct __lldiv_struct,__NOTHROW_NCX,div,(__LONGLONG __numer, __LONGLONG __denom),imaxdiv,(__numer,__denom))
#else /* ... */
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/stdlib/lldiv.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED struct __lldiv_struct __NOTHROW_NCX(__LIBCCALL div)(__LONGLONG __numer, __LONGLONG __denom) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lldiv))(__numer, __denom); }
#endif /* !... */
} /* extern "C++" */
#endif /* __USE_ISOC99 && __COMPILER_HAVE_LONGLONG */
#endif /* __CORRECT_ISO_CPP_STDLIB_H_PROTO */
#if defined(__CORRECT_ISO_CPP_MATH_H_PROTO) && !defined(__NO_FPU)
extern "C++" {
#if __has_builtin(__builtin_fabsf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fabsf)
/* >> fabsf(3), fabs(3), fabsl(3)
 * Absolute value of `x' */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,abs,(float __x),fabsf,{ return __builtin_fabsf(__x); })
#elif defined(__CRT_HAVE_fabsf)
/* >> fabsf(3), fabs(3), fabsl(3)
 * Absolute value of `x' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,abs,(float __x),fabsf,(__x))
#elif defined(__CRT_HAVE___fabsf)
/* >> fabsf(3), fabs(3), fabsl(3)
 * Absolute value of `x' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,abs,(float __x),__fabsf,(__x))
#else /* ... */
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/fabsf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* >> fabsf(3), fabs(3), fabsl(3)
 * Absolute value of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL abs)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fabsf))(__x); }
#endif /* !... */
#if __has_builtin(__builtin_fabs) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fabs)
/* >> fabsf(3), fabs(3), fabsl(3)
 * Absolute value of `x' */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,abs,(double __x),fabs,{ return __builtin_fabs(__x); })
#elif defined(__CRT_HAVE_fabs)
/* >> fabsf(3), fabs(3), fabsl(3)
 * Absolute value of `x' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,abs,(double __x),fabs,(__x))
#elif defined(__CRT_HAVE___fabs)
/* >> fabsf(3), fabs(3), fabsl(3)
 * Absolute value of `x' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,abs,(double __x),__fabs,(__x))
#else /* ... */
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/fabs.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* >> fabsf(3), fabs(3), fabsl(3)
 * Absolute value of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW(__LIBCCALL abs)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fabs))(__x); }
#endif /* !... */
} /* extern "C++" */
#ifdef __COMPILER_HAVE_LONGDOUBLE
extern "C++" {
#if __has_builtin(__builtin_fabsl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fabsl)
/* >> fabsf(3), fabs(3), fabsl(3)
 * Absolute value of `x' */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,abs,(__LONGDOUBLE __x),fabsl,{ return __builtin_fabsl(__x); })
#elif defined(__CRT_HAVE_fabsl)
/* >> fabsf(3), fabs(3), fabsl(3)
 * Absolute value of `x' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,abs,(__LONGDOUBLE __x),fabsl,(__x))
#elif defined(__CRT_HAVE___fabsl)
/* >> fabsf(3), fabs(3), fabsl(3)
 * Absolute value of `x' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,abs,(__LONGDOUBLE __x),__fabsl,(__x))
#else /* ... */
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/fabsl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* >> fabsf(3), fabs(3), fabsl(3)
 * Absolute value of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL abs)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fabsl))(__x); }
#endif /* !... */
} /* extern "C++" */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __CORRECT_ISO_CPP_MATH_H_PROTO && !__NO_FPU */
#endif /* __cplusplus */
#ifdef __CRT_HAVE_getenv
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,getenv,(char const *__varname),(__varname))
#else /* __CRT_HAVE_getenv */
__NAMESPACE_STD_END
#include <libc/template/environ.h>
__NAMESPACE_STD_BEGIN
#ifdef __LOCAL_environ
__NAMESPACE_STD_END
#include <libc/local/stdlib/getenv.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(getenv, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL getenv)(char const *__varname) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getenv))(__varname); })
#endif /* __LOCAL_environ */
#endif /* !__CRT_HAVE_getenv */
#ifdef __CRT_HAVE_mblen
__CDECLARE(,int,__NOTHROW_NCX,mblen,(char const *__str, size_t __maxlen),(__str,__maxlen))
#else /* __CRT_HAVE_mblen */
__NAMESPACE_STD_END
#include <libc/local/stdlib/mblen.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(mblen, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_NCX(__LIBCCALL mblen)(char const *__str, size_t __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mblen))(__str, __maxlen); })
#endif /* !__CRT_HAVE_mblen */
#ifdef __CRT_HAVE_mbtowc
__CDECLARE(,int,__NOTHROW_NCX,mbtowc,(wchar_t *__restrict __pwc, char const *__restrict __str, size_t __maxlen),(__pwc,__str,__maxlen))
#else /* __CRT_HAVE_mbtowc */
__NAMESPACE_STD_END
#include <libc/local/stdlib/mbtowc.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(mbtowc, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_NCX(__LIBCCALL mbtowc)(wchar_t *__restrict __pwc, char const *__restrict __str, size_t __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mbtowc))(__pwc, __str, __maxlen); })
#endif /* !__CRT_HAVE_mbtowc */
#ifdef __CRT_HAVE_wctomb
__CDECLARE(,int,__NOTHROW_NCX,wctomb,(char *__str, wchar_t __wc),(__str,__wc))
#else /* __CRT_HAVE_wctomb */
__NAMESPACE_STD_END
#include <libc/local/stdlib/wctomb.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(wctomb, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_NCX(__LIBCCALL wctomb)(char *__str, wchar_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wctomb))(__str, __wc); })
#endif /* !__CRT_HAVE_wctomb */
#ifdef __CRT_HAVE_mbstowcs
__CDECLARE(__ATTR_NONNULL((1, 2)),size_t,__NOTHROW_NCX,mbstowcs,(wchar_t *__restrict __dst, char const *__restrict __src, size_t __dstlen),(__dst,__src,__dstlen))
#else /* __CRT_HAVE_mbstowcs */
__NAMESPACE_STD_END
#include <libc/local/stdlib/mbstowcs.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(mbstowcs, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) size_t __NOTHROW_NCX(__LIBCCALL mbstowcs)(wchar_t *__restrict __dst, char const *__restrict __src, size_t __dstlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mbstowcs))(__dst, __src, __dstlen); })
#endif /* !__CRT_HAVE_mbstowcs */
#ifdef __CRT_HAVE_wcstombs
__CDECLARE(__ATTR_NONNULL((1, 2)),size_t,__NOTHROW_NCX,wcstombs,(char *__restrict __dst, wchar_t const *__restrict __src, size_t __dstlen),(__dst,__src,__dstlen))
#else /* __CRT_HAVE_wcstombs */
__NAMESPACE_STD_END
#include <libc/local/stdlib/wcstombs.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstombs, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) size_t __NOTHROW_NCX(__LIBCCALL wcstombs)(char *__restrict __dst, wchar_t const *__restrict __src, size_t __dstlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstombs))(__dst, __src, __dstlen); })
#endif /* !__CRT_HAVE_wcstombs */
#ifndef __std_system_defined
#define __std_system_defined
#ifdef __system_defined
/* >> system(3)
 * Execute a given `command' on the system interpreter (as in `sh -c $command')
 * The   return   value   is   the   exit   status   after   running  `command'
 * When `command' is `NULL' only check if a system interpreter is available.
 * When  no   system   interpreter   is  available,   `127'   is   returned. */
__NAMESPACE_GLB_USING_OR_IMPL(system, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_RPC(__LIBCCALL system)(char const *__command) { return :: system(__command); })
#elif defined(__CRT_HAVE_system)
/* >> system(3)
 * Execute a given `command' on the system interpreter (as in `sh -c $command')
 * The   return   value   is   the   exit   status   after   running  `command'
 * When `command' is `NULL' only check if a system interpreter is available.
 * When  no   system   interpreter   is  available,   `127'   is   returned. */
__CDECLARE(,int,__NOTHROW_RPC,system,(char const *__command),(__command))
#elif defined(__CRT_HAVE___libc_system)
/* >> system(3)
 * Execute a given `command' on the system interpreter (as in `sh -c $command')
 * The   return   value   is   the   exit   status   after   running  `command'
 * When `command' is `NULL' only check if a system interpreter is available.
 * When  no   system   interpreter   is  available,   `127'   is   returned. */
__CREDIRECT(,int,__NOTHROW_RPC,system,(char const *__command),__libc_system,(__command))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/template/environ.h>
__NAMESPACE_STD_BEGIN
#if (defined(__CRT_HAVE_shexec) || defined(__CRT_HAVE_execl) || defined(__CRT_HAVE__execl) || defined(__CRT_HAVE_execv) || defined(__CRT_HAVE__execv) || ((defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve) || defined(__CRT_HAVE___execve) || defined(__CRT_HAVE___libc_execve)) && defined(__LOCAL_environ))) && (defined(__CRT_HAVE__Exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE_exit)) && (defined(__CRT_HAVE_waitpid) || defined(__CRT_HAVE___waitpid)) && (defined(__CRT_HAVE_vfork) || defined(__CRT_HAVE___vfork) || defined(__CRT_HAVE___libc_vfork) || defined(__CRT_HAVE_fork) || defined(__CRT_HAVE___fork) || defined(__CRT_HAVE___libc_fork))
__NAMESPACE_STD_END
#include <libc/local/stdlib/system.h>
__NAMESPACE_STD_BEGIN
/* >> system(3)
 * Execute a given `command' on the system interpreter (as in `sh -c $command')
 * The   return   value   is   the   exit   status   after   running  `command'
 * When `command' is `NULL' only check if a system interpreter is available.
 * When  no   system   interpreter   is  available,   `127'   is   returned. */
__NAMESPACE_LOCAL_USING_OR_IMPL(system, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_RPC(__LIBCCALL system)(char const *__command) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(system))(__command); })
#else /* (__CRT_HAVE_shexec || __CRT_HAVE_execl || __CRT_HAVE__execl || __CRT_HAVE_execv || __CRT_HAVE__execv || ((__CRT_HAVE_execve || __CRT_HAVE__execve || __CRT_HAVE___execve || __CRT_HAVE___libc_execve) && __LOCAL_environ)) && (__CRT_HAVE__Exit || __CRT_HAVE__exit || __CRT_HAVE_quick_exit || __CRT_HAVE_exit) && (__CRT_HAVE_waitpid || __CRT_HAVE___waitpid) && (__CRT_HAVE_vfork || __CRT_HAVE___vfork || __CRT_HAVE___libc_vfork || __CRT_HAVE_fork || __CRT_HAVE___fork || __CRT_HAVE___libc_fork) */
#undef __std_system_defined
#endif /* (!__CRT_HAVE_shexec && !__CRT_HAVE_execl && !__CRT_HAVE__execl && !__CRT_HAVE_execv && !__CRT_HAVE__execv && ((!__CRT_HAVE_execve && !__CRT_HAVE__execve && !__CRT_HAVE___execve && !__CRT_HAVE___libc_execve) || !__LOCAL_environ)) || (!__CRT_HAVE__Exit && !__CRT_HAVE__exit && !__CRT_HAVE_quick_exit && !__CRT_HAVE_exit) || (!__CRT_HAVE_waitpid && !__CRT_HAVE___waitpid) || (!__CRT_HAVE_vfork && !__CRT_HAVE___vfork && !__CRT_HAVE___libc_vfork && !__CRT_HAVE_fork && !__CRT_HAVE___fork && !__CRT_HAVE___libc_fork) */
#endif /* !... */
#endif /* !__std_system_defined */
#ifndef __std_abort_defined
#define __std_abort_defined
#ifdef __abort_defined
__NAMESPACE_GLB_USING_OR_IMPL(abort, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NORETURN void (__LIBCCALL abort)(void) __THROWS(...) { :: abort(); })
#elif __has_builtin(__builtin_abort) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_abort)
__CEIDECLARE_GCCNCX(__ATTR_NORETURN,void,__THROWING,abort,(void),{ __builtin_abort(); })
#elif defined(__CRT_HAVE_abort)
__CDECLARE_VOID_GCCNCX(__ATTR_NORETURN,__THROWING,abort,(void),())
#elif defined(__CRT_HAVE__ZSt9terminatev)
__CREDIRECT_VOID_GCCNCX(__ATTR_NORETURN,__THROWING,abort,(void),_ZSt9terminatev,())
#elif defined(__CRT_HAVE_terminate)
__CREDIRECT_VOID_GCCNCX(__ATTR_NORETURN,__THROWING,abort,(void),terminate,())
#elif defined(__CRT_HAVE___chk_fail)
__CREDIRECT_VOID_GCCNCX(__ATTR_NORETURN,__THROWING,abort,(void),__chk_fail,())
#elif defined(__CRT_HAVE_$Qterminate$A$AYAXXZ)
__CREDIRECT_VOID_GCCNCX(__ATTR_NORETURN,__THROWING,abort,(void),?terminate@@YAXXZ,())
#elif defined(__CRT_HAVE__Exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE_exit)
__NAMESPACE_STD_END
#include <libc/local/stdlib/abort.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(abort, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NORETURN void (__LIBCCALL abort)(void) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(abort))(); })
#else /* ... */
#undef __std_abort_defined
#endif /* !... */
#endif /* !__std_abort_defined */
#ifndef __std_exit_defined
#define __std_exit_defined
#ifdef __exit_defined
__NAMESPACE_GLB_USING_OR_IMPL(exit, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NORETURN void (__LIBCCALL exit)(int __status) __THROWS(...) { :: exit(__status); })
#elif __has_builtin(__builtin_exit) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_exit)
__CEIDECLARE_GCCNCX(__ATTR_NORETURN,void,__THROWING,exit,(int __status),{ __builtin_exit(__status); })
#elif defined(__CRT_HAVE_exit)
__CDECLARE_VOID_GCCNCX(__ATTR_NORETURN,__THROWING,exit,(int __status),(__status))
#elif defined(__CRT_HAVE_quick_exit)
__CREDIRECT_VOID_GCCNCX(__ATTR_NORETURN,__THROWING,exit,(int __status),quick_exit,(__status))
#elif defined(__CRT_HAVE__exit)
__CREDIRECT_VOID_GCCNCX(__ATTR_NORETURN,__THROWING,exit,(int __status),_exit,(__status))
#elif defined(__CRT_HAVE__Exit)
__CREDIRECT_VOID_GCCNCX(__ATTR_NORETURN,__THROWING,exit,(int __status),_Exit,(__status))
#else /* ... */
#undef __std_exit_defined
#endif /* !... */
#endif /* !__std_exit_defined */
#ifdef __CRT_HAVE_atexit
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,atexit,(void (__LIBCCALL *__func)(void)),(__func))
#elif defined(__CRT_HAVE__crt_atexit)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,atexit,(void (__LIBCCALL *__func)(void)),_crt_atexit,(__func))
#elif defined(__CRT_HAVE_at_quick_exit)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,atexit,(void (__LIBCCALL *__func)(void)),at_quick_exit,(__func))
#elif defined(__CRT_HAVE__crt_at_quick_exit)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,atexit,(void (__LIBCCALL *__func)(void)),_crt_at_quick_exit,(__func))
#endif /* ... */
#if defined(__USE_ISOC11) || defined(__USE_ISOCXX11)
#ifdef __CRT_HAVE_quick_exit
__CDECLARE_VOID(__ATTR_NORETURN,__THROWING,quick_exit,(int __status),(__status))
#elif defined(__CRT_HAVE_exit)
__CREDIRECT_VOID(__ATTR_NORETURN,__THROWING,quick_exit,(int __status),exit,(__status))
#elif defined(__CRT_HAVE__exit)
__CREDIRECT_VOID(__ATTR_NORETURN,__THROWING,quick_exit,(int __status),_exit,(__status))
#elif defined(__CRT_HAVE__Exit)
__CREDIRECT_VOID(__ATTR_NORETURN,__THROWING,quick_exit,(int __status),_Exit,(__status))
#endif /* ... */
#ifdef __CRT_HAVE_at_quick_exit
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,at_quick_exit,(void (__LIBCCALL *__func)(void)),(__func))
#elif defined(__CRT_HAVE__crt_at_quick_exit)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,at_quick_exit,(void (__LIBCCALL *__func)(void)),_crt_at_quick_exit,(__func))
#elif defined(__CRT_HAVE_atexit)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,at_quick_exit,(void (__LIBCCALL *__func)(void)),atexit,(__func))
#elif defined(__CRT_HAVE__crt_atexit)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,at_quick_exit,(void (__LIBCCALL *__func)(void)),_crt_atexit,(__func))
#endif /* ... */
#endif /* __USE_ISOC11 || __USE_ISOCXX11 */
#ifdef __USE_ISOC99
#if __has_builtin(__builtin__Exit) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE__Exit)
__CEIDECLARE_GCCNCX(__ATTR_NORETURN,void,__THROWING,_Exit,(int __status),{ __builtin__Exit(__status); })
#elif __has_builtin(__builtin__exit) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE__exit)
__CEIREDIRECT_GCCNCX(__ATTR_NORETURN,void,__THROWING,_Exit,(int __status),_exit,{ __builtin__exit(__status); })
#elif defined(__CRT_HAVE__Exit)
__CDECLARE_VOID_GCCNCX(__ATTR_NORETURN,__THROWING,_Exit,(int __status),(__status))
#elif defined(__CRT_HAVE__exit)
__CREDIRECT_VOID_GCCNCX(__ATTR_NORETURN,__THROWING,_Exit,(int __status),_exit,(__status))
#elif defined(__CRT_HAVE_quick_exit)
__CREDIRECT_VOID_GCCNCX(__ATTR_NORETURN,__THROWING,_Exit,(int __status),quick_exit,(__status))
#elif defined(__CRT_HAVE_exit)
__CREDIRECT_VOID_GCCNCX(__ATTR_NORETURN,__THROWING,_Exit,(int __status),exit,(__status))
#endif /* ... */
#endif /* __USE_ISOC99 */
#ifndef __std_malloc_defined
#define __std_malloc_defined
#ifdef __malloc_defined
__NAMESPACE_GLB_USING_OR_IMPL(malloc, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)) void *__NOTHROW_NCX(__LIBCCALL malloc)(size_t __num_bytes) { return :: malloc(__num_bytes); })
#elif __has_builtin(__builtin_malloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_malloc)
__CEIDECLARE_GCCNCX(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,malloc,(size_t __num_bytes),{ return __builtin_malloc(__num_bytes); })
#elif defined(__CRT_HAVE_malloc)
__CDECLARE_GCCNCX(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,malloc,(size_t __num_bytes),(__num_bytes))
#elif defined(__CRT_HAVE___libc_malloc)
__CREDIRECT_GCCNCX(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,malloc,(size_t __num_bytes),__libc_malloc,(__num_bytes))
#elif defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)
__NAMESPACE_STD_END
#include <libc/local/stdlib/malloc.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(malloc, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)) void *__NOTHROW_NCX(__LIBCCALL malloc)(size_t __num_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(malloc))(__num_bytes); })
#else /* ... */
#undef __std_malloc_defined
#endif /* !... */
#endif /* !__std_malloc_defined */
#ifndef __std_calloc_defined
#define __std_calloc_defined
#ifdef __calloc_defined
__NAMESPACE_GLB_USING_OR_IMPL(calloc, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1, 2)) void *__NOTHROW_NCX(__LIBCCALL calloc)(size_t __count, size_t __num_bytes) { return :: calloc(__count, __num_bytes); })
#elif __has_builtin(__builtin_calloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_calloc)
__CEIDECLARE_GCCNCX(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1, 2)),void *,__NOTHROW_NCX,calloc,(size_t __count, size_t __num_bytes),{ return __builtin_calloc(__count, __num_bytes); })
#elif defined(__CRT_HAVE_calloc)
__CDECLARE_GCCNCX(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1, 2)),void *,__NOTHROW_NCX,calloc,(size_t __count, size_t __num_bytes),(__count,__num_bytes))
#elif defined(__CRT_HAVE___libc_calloc)
__CREDIRECT_GCCNCX(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1, 2)),void *,__NOTHROW_NCX,calloc,(size_t __count, size_t __num_bytes),__libc_calloc,(__count,__num_bytes))
#elif defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)
__NAMESPACE_STD_END
#include <libc/local/stdlib/calloc.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(calloc, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1, 2)) void *__NOTHROW_NCX(__LIBCCALL calloc)(size_t __count, size_t __num_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(calloc))(__count, __num_bytes); })
#else /* ... */
#undef __std_calloc_defined
#endif /* !... */
#endif /* !__std_calloc_defined */
#ifndef __std_realloc_defined
#define __std_realloc_defined
#ifdef __realloc_defined
__NAMESPACE_GLB_USING_OR_IMPL(realloc, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) void *__NOTHROW_NCX(__LIBCCALL realloc)(void *__mallptr, size_t __num_bytes) { return :: realloc(__mallptr, __num_bytes); })
#elif __has_builtin(__builtin_realloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_realloc)
__CEIDECLARE_GCCNCX(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,realloc,(void *__mallptr, size_t __num_bytes),{ return __builtin_realloc(__mallptr, __num_bytes); })
#elif defined(__CRT_HAVE_realloc)
__CDECLARE_GCCNCX(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,realloc,(void *__mallptr, size_t __num_bytes),(__mallptr,__num_bytes))
#elif defined(__CRT_HAVE___libc_realloc)
__CREDIRECT_GCCNCX(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,realloc,(void *__mallptr, size_t __num_bytes),__libc_realloc,(__mallptr,__num_bytes))
#else /* ... */
#undef __std_realloc_defined
#endif /* !... */
#endif /* !__std_realloc_defined */
#ifndef __std_free_defined
#define __std_free_defined
#ifdef __free_defined
__NAMESPACE_GLB_USING_OR_IMPL(free, __FORCELOCAL __ATTR_ARTIFICIAL void __NOTHROW_NCX(__LIBCCALL free)(void *__mallptr) { :: free(__mallptr); })
#elif __has_builtin(__builtin_free) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_free)
__CEIDECLARE_GCCNCX(,void,__NOTHROW_NCX,free,(void *__mallptr),{ __builtin_free(__mallptr); })
#elif defined(__CRT_HAVE_free)
__CDECLARE_VOID_GCCNCX(,__NOTHROW_NCX,free,(void *__mallptr),(__mallptr))
#elif defined(__CRT_HAVE_cfree)
__CREDIRECT_VOID_GCCNCX(,__NOTHROW_NCX,free,(void *__mallptr),cfree,(__mallptr))
#elif defined(__CRT_HAVE___libc_free)
__CREDIRECT_VOID_GCCNCX(,__NOTHROW_NCX,free,(void *__mallptr),__libc_free,(__mallptr))
#else /* ... */
#undef __std_free_defined
#endif /* !... */
#endif /* !__std_free_defined */
#ifdef __CRT_HAVE_srand
__CDECLARE_VOID(,__NOTHROW,srand,(long __seed),(__seed))
#elif defined(__CRT_HAVE_srandom) && __SIZEOF_INT__ == __SIZEOF_LONG__
__CREDIRECT_VOID(,__NOTHROW,srand,(long __seed),srandom,(__seed))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/stdlib/srand.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(srand, __FORCELOCAL __ATTR_ARTIFICIAL void __NOTHROW(__LIBCCALL srand)(long __seed) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(srand))(__seed); })
#endif /* !... */
#ifdef __CRT_HAVE_rand
__CDECLARE(,int,__NOTHROW,rand,(void),())
#elif defined(__CRT_HAVE_random) && __SIZEOF_INT__ == __SIZEOF_LONG__
__CREDIRECT(,int,__NOTHROW,rand,(void),random,())
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/stdlib/rand.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(rand, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW(__LIBCCALL rand)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rand))(); })
#endif /* !... */
#ifdef __CRT_HAVE_atoi
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,atoi,(char const *__restrict __nptr),(__nptr))
#elif defined(__CRT_HAVE_atol) && __SIZEOF_INT__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,atoi,(char const *__restrict __nptr),atol,(__nptr))
#elif defined(__CRT_HAVE_atoll) && __SIZEOF_INT__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,atoi,(char const *__restrict __nptr),atoll,(__nptr))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/stdlib/atoi.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(atoi, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL atoi)(char const *__restrict __nptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(atoi))(__nptr); })
#endif /* !... */
#ifdef __CRT_HAVE_atol
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),long,__NOTHROW_NCX,atol,(char const *__restrict __nptr),(__nptr))
#elif defined(__CRT_HAVE_atoi) && __SIZEOF_LONG__ == __SIZEOF_INT__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),long,__NOTHROW_NCX,atol,(char const *__restrict __nptr),atoi,(__nptr))
#elif defined(__CRT_HAVE_atoll) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),long,__NOTHROW_NCX,atol,(char const *__restrict __nptr),atoll,(__nptr))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/stdlib/atol.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(atol, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) long __NOTHROW_NCX(__LIBCCALL atol)(char const *__restrict __nptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(atol))(__nptr); })
#endif /* !... */
#ifdef __CRT_HAVE_atoll
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,atoll,(char const *__restrict __nptr),(__nptr))
#elif defined(__CRT_HAVE_atoi) && __SIZEOF_LONG_LONG__ == __SIZEOF_INT__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,atoll,(char const *__restrict __nptr),atoi,(__nptr))
#elif defined(__CRT_HAVE_atol) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,atoll,(char const *__restrict __nptr),atol,(__nptr))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/stdlib/atoll.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(atoll, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __LONGLONG __NOTHROW_NCX(__LIBCCALL atoll)(char const *__restrict __nptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(atoll))(__nptr); })
#endif /* !... */
#ifdef __CRT_HAVE_strtoul
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,strtoul,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtou32) && __SIZEOF_LONG__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,strtoul,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtou32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtou64) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,strtoul,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtou64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoull) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,strtoul,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtouq) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,strtoul,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE___strtouq) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,strtoul,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),__strtouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__strtoui64) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,strtoul,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),_strtoui64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoumax) && __SIZEOF_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,strtoul,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoumax,(__nptr,__endptr,__base))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/stdlib/strtoul.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(strtoul, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) unsigned long __NOTHROW_NCX(__LIBCCALL strtoul)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtoul))(__nptr, __endptr, __base); })
#endif /* !... */
#ifdef __CRT_HAVE_strtol
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),long,__NOTHROW_NCX,strtol,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strto32) && __SIZEOF_LONG__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),long,__NOTHROW_NCX,strtol,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strto32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strto64) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),long,__NOTHROW_NCX,strtol,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strto64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoll) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),long,__NOTHROW_NCX,strtol,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoq) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),long,__NOTHROW_NCX,strtol,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE___strtoq) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),long,__NOTHROW_NCX,strtol,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),__strtoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__strtoi64) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),long,__NOTHROW_NCX,strtol,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),_strtoi64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoimax) && __SIZEOF_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),long,__NOTHROW_NCX,strtol,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoimax,(__nptr,__endptr,__base))
#elif __SIZEOF_LONG__ == 4
__NAMESPACE_STD_END
#include <libc/local/stdlib/strto32.h>
__NAMESPACE_STD_BEGIN
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) long __NOTHROW_NCX(__LIBCCALL strtol)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base) { return (long)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strto32))(__nptr, __endptr, __base); }
#elif __SIZEOF_LONG__ == 8
__NAMESPACE_STD_END
#include <libc/local/stdlib/strto64.h>
__NAMESPACE_STD_BEGIN
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) long __NOTHROW_NCX(__LIBCCALL strtol)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base) { return (long)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strto64))(__nptr, __endptr, __base); }
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/stdlib/strtol.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(strtol, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) long __NOTHROW_NCX(__LIBCCALL strtol)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtol))(__nptr, __endptr, __base); })
#endif /* !... */
#ifdef __LONGLONG
#ifdef __USE_ISOC99
#ifndef __std_strtoull_defined
#define __std_strtoull_defined
#ifdef __strtoull_defined
__NAMESPACE_GLB_USING_OR_IMPL(strtoull, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __ULONGLONG __NOTHROW_NCX(__LIBCCALL strtoull)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base) { return :: strtoull(__nptr, __endptr, __base); })
#elif defined(__CRT_HAVE_strtoull)
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,strtoull,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtouq)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,strtoull,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE___strtouq)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,strtoull,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),__strtouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtou64) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,strtoull,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtou64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtou32) && __SIZEOF_LONG_LONG__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,strtoull,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtou32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoul) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,strtoull,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__strtoui64) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,strtoull,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),_strtoui64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoumax) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,strtoull,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoumax,(__nptr,__endptr,__base))
#elif __SIZEOF_LONG__ == 8
__NAMESPACE_STD_END
#include <libc/local/stdlib/strtou64.h>
__NAMESPACE_STD_BEGIN
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __ULONGLONG __NOTHROW_NCX(__LIBCCALL strtoull)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base) { return (__ULONGLONG)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtou64))(__nptr, __endptr, __base); }
#elif __SIZEOF_LONG__ == 4
__NAMESPACE_STD_END
#include <libc/local/stdlib/strtou32.h>
__NAMESPACE_STD_BEGIN
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __ULONGLONG __NOTHROW_NCX(__LIBCCALL strtoull)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base) { return (__ULONGLONG)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtou32))(__nptr, __endptr, __base); }
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/stdlib/strtoull.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(strtoull, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __ULONGLONG __NOTHROW_NCX(__LIBCCALL strtoull)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtoull))(__nptr, __endptr, __base); })
#endif /* !... */
#endif /* !__std_strtoull_defined */
#ifndef __std_strtoll_defined
#define __std_strtoll_defined
#ifdef __strtoll_defined
__NAMESPACE_GLB_USING_OR_IMPL(strtoll, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __LONGLONG __NOTHROW_NCX(__LIBCCALL strtoll)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base) { return :: strtoll(__nptr, __endptr, __base); })
#elif defined(__CRT_HAVE_strtoll)
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,strtoll,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoq)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,strtoll,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE___strtoq)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,strtoll,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),__strtoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strto64) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,strtoll,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strto64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strto32) && __SIZEOF_LONG_LONG__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,strtoll,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strto32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtol) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,strtoll,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__strtoi64) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,strtoll,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),_strtoi64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoimax) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,strtoll,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoimax,(__nptr,__endptr,__base))
#elif __SIZEOF_LONG__ == 8
__NAMESPACE_STD_END
#include <libc/local/stdlib/strto64.h>
__NAMESPACE_STD_BEGIN
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __LONGLONG __NOTHROW_NCX(__LIBCCALL strtoll)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base) { return (__LONGLONG)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strto64))(__nptr, __endptr, __base); }
#elif __SIZEOF_LONG__ == 4
__NAMESPACE_STD_END
#include <libc/local/stdlib/strto32.h>
__NAMESPACE_STD_BEGIN
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __LONGLONG __NOTHROW_NCX(__LIBCCALL strtoll)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base) { return (__LONGLONG)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strto32))(__nptr, __endptr, __base); }
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/stdlib/strtoll.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(strtoll, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __LONGLONG __NOTHROW_NCX(__LIBCCALL strtoll)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtoll))(__nptr, __endptr, __base); })
#endif /* !... */
#endif /* !__std_strtoll_defined */
#endif /* __USE_ISOC99 */
#endif /* __LONGLONG */
#ifndef __NO_FPU
#ifdef __CRT_HAVE_atof
__CDECLARE(__ATTR_LEAF __ATTR_WUNUSED __ATTR_NONNULL((1)),double,__NOTHROW_NCX,atof,(char const *__restrict __nptr),(__nptr))
#else /* __CRT_HAVE_atof */
__NAMESPACE_STD_END
#include <libc/local/stdlib/atof.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(atof, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_WUNUSED __ATTR_NONNULL((1)) double __NOTHROW_NCX(__LIBCCALL atof)(char const *__restrict __nptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(atof))(__nptr); })
#endif /* !__CRT_HAVE_atof */
#ifdef __CRT_HAVE_strtod
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),double,__NOTHROW_NCX,strtod,(char const *__restrict __nptr, char **__endptr),(__nptr,__endptr))
#elif defined(__CRT_HAVE_strtold) && __SIZEOF_LONG_DOUBLE__ == __SIZEOF_DOUBLE__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),double,__NOTHROW_NCX,strtod,(char const *__restrict __nptr, char **__endptr),strtold,(__nptr,__endptr))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/stdlib/strtod.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(strtod, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) double __NOTHROW_NCX(__LIBCCALL strtod)(char const *__restrict __nptr, char **__endptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtod))(__nptr, __endptr); })
#endif /* !... */
#ifdef __USE_ISOC99
#ifndef __std_strtof_defined
#define __std_strtof_defined
#ifdef __strtof_defined
__NAMESPACE_GLB_USING_OR_IMPL(strtof, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) float __NOTHROW_NCX(__LIBCCALL strtof)(char const *__restrict __nptr, char **__endptr) { return :: strtof(__nptr, __endptr); })
#elif defined(__CRT_HAVE_strtof)
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),float,__NOTHROW_NCX,strtof,(char const *__restrict __nptr, char **__endptr),(__nptr,__endptr))
#elif defined(__CRT_HAVE___strtof)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),float,__NOTHROW_NCX,strtof,(char const *__restrict __nptr, char **__endptr),__strtof,(__nptr,__endptr))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/stdlib/strtof.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(strtof, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) float __NOTHROW_NCX(__LIBCCALL strtof)(char const *__restrict __nptr, char **__endptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtof))(__nptr, __endptr); })
#endif /* !... */
#endif /* !__std_strtof_defined */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#ifndef __std_strtold_defined
#define __std_strtold_defined
#ifdef __strtold_defined
__NAMESPACE_GLB_USING_OR_IMPL(strtold, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __LONGDOUBLE __NOTHROW_NCX(__LIBCCALL strtold)(char const *__restrict __nptr, char **__endptr) { return :: strtold(__nptr, __endptr); })
#elif defined(__CRT_HAVE_strtold)
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGDOUBLE,__NOTHROW_NCX,strtold,(char const *__restrict __nptr, char **__endptr),(__nptr,__endptr))
#elif defined(__CRT_HAVE___strtold)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGDOUBLE,__NOTHROW_NCX,strtold,(char const *__restrict __nptr, char **__endptr),__strtold,(__nptr,__endptr))
#elif defined(__CRT_HAVE_strtod) && __SIZEOF_LONG_DOUBLE__ == __SIZEOF_DOUBLE__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGDOUBLE,__NOTHROW_NCX,strtold,(char const *__restrict __nptr, char **__endptr),strtod,(__nptr,__endptr))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/stdlib/strtold.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(strtold, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __LONGDOUBLE __NOTHROW_NCX(__LIBCCALL strtold)(char const *__restrict __nptr, char **__endptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtold))(__nptr, __endptr); })
#endif /* !... */
#endif /* !__std_strtold_defined */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_ISOC99 */
#endif /* !__NO_FPU */
#ifdef __USE_ISOCXX17
#ifndef __std_aligned_alloc_defined
#define __std_aligned_alloc_defined
#ifdef __aligned_alloc_defined
__NAMESPACE_GLB_USING_OR_IMPL(aligned_alloc, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_ALIGN(1) __ATTR_ALLOC_SIZE((2)) void *__NOTHROW_NCX(__LIBCCALL aligned_alloc)(size_t __alignment, size_t __n_bytes) { return (void *):: aligned_alloc(); })
#elif __has_builtin(__builtin_aligned_alloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_aligned_alloc)
__CEIDECLARE_GCCNCX(__ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_ALIGN(1) __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,aligned_alloc,(size_t __alignment, size_t __n_bytes),{ return __builtin_aligned_alloc(__alignment, __n_bytes); })
#elif defined(__CRT_HAVE_memalign)
__CREDIRECT_GCCNCX(__ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_ALIGN(1) __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,aligned_alloc,(size_t __alignment, size_t __n_bytes),memalign,(__alignment,__n_bytes))
#elif defined(__CRT_HAVE_aligned_alloc)
__CDECLARE_GCCNCX(__ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_ALIGN(1) __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,aligned_alloc,(size_t __alignment, size_t __n_bytes),(__alignment,__n_bytes))
#elif defined(__CRT_HAVE___libc_memalign)
__CREDIRECT_GCCNCX(__ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_ALIGN(1) __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,aligned_alloc,(size_t __alignment, size_t __n_bytes),__libc_memalign,(__alignment,__n_bytes))
#elif defined(__CRT_HAVE_posix_memalign)
__NAMESPACE_STD_END
#include <libc/local/malloc/memalign.h>
__NAMESPACE_STD_BEGIN
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_ALIGN(1) __ATTR_ALLOC_SIZE((2)) void *__NOTHROW_NCX(__LIBCCALL aligned_alloc)(size_t __alignment, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memalign))(__alignment, __n_bytes); }
#else /* ... */
#undef __std_aligned_alloc_defined
#endif /* !... */
#endif /* !__std_aligned_alloc_defined */
#endif /* __USE_ISOCXX17 */
__NAMESPACE_STD_END

#ifndef __CXX_SYSTEM_HEADER
#if !defined(__qsort_defined) && defined(__std_qsort_defined)
#define __qsort_defined
__NAMESPACE_STD_USING(qsort)
#endif /* !__qsort_defined && __std_qsort_defined */
#if !defined(__bsearch_defined) && defined(__std_bsearch_defined)
#define __bsearch_defined
__NAMESPACE_STD_USING(bsearch)
#endif /* !__bsearch_defined && __std_bsearch_defined */
__NAMESPACE_STD_USING(labs)
#endif /* !__CXX_SYSTEM_HEADER */
#ifdef __USE_ISOC99
#ifndef __CXX_SYSTEM_HEADER
__NAMESPACE_STD_USING(llabs)
#endif /* !__CXX_SYSTEM_HEADER */
#endif /* __USE_ISOC99 */
#ifndef __CXX_SYSTEM_HEADER
__NAMESPACE_STD_USING(ldiv)
#endif /* !__CXX_SYSTEM_HEADER */
#ifdef __USE_ISOC99
#ifndef __CXX_SYSTEM_HEADER
__NAMESPACE_STD_USING(lldiv)
#endif /* !__CXX_SYSTEM_HEADER */
#endif /* __USE_ISOC99 */
#ifndef __CXX_SYSTEM_HEADER
__NAMESPACE_STD_USING(abs)
__NAMESPACE_STD_USING(div)
#include <libc/template/environ.h>
#if defined(__CRT_HAVE_getenv) || defined(__LOCAL_environ)
__NAMESPACE_STD_USING(getenv)
#endif /* __CRT_HAVE_getenv || __LOCAL_environ */
__NAMESPACE_STD_USING(mblen)
__NAMESPACE_STD_USING(mbtowc)
__NAMESPACE_STD_USING(wctomb)
__NAMESPACE_STD_USING(mbstowcs)
__NAMESPACE_STD_USING(wcstombs)
#if !defined(__system_defined) && defined(__std_system_defined)
#define __system_defined
__NAMESPACE_STD_USING(system)
#endif /* !__system_defined && __std_system_defined */
#if !defined(__abort_defined) && defined(__std_abort_defined)
#define __abort_defined
__NAMESPACE_STD_USING(abort)
#endif /* !__abort_defined && __std_abort_defined */
#if !defined(__exit_defined) && defined(__std_exit_defined)
#define __exit_defined
__NAMESPACE_STD_USING(exit)
#endif /* !__exit_defined && __std_exit_defined */
#if defined(__CRT_HAVE_atexit) || defined(__CRT_HAVE__crt_atexit) || defined(__CRT_HAVE_at_quick_exit) || defined(__CRT_HAVE__crt_at_quick_exit)
__NAMESPACE_STD_USING(atexit)
#endif /* __CRT_HAVE_atexit || __CRT_HAVE__crt_atexit || __CRT_HAVE_at_quick_exit || __CRT_HAVE__crt_at_quick_exit */
#endif /* !__CXX_SYSTEM_HEADER */
#if defined(__USE_ISOC11) || defined(__USE_ISOCXX11)
#ifndef __CXX_SYSTEM_HEADER
#if defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE_exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE__Exit)
__NAMESPACE_STD_USING(quick_exit)
#endif /* __CRT_HAVE_quick_exit || __CRT_HAVE_exit || __CRT_HAVE__exit || __CRT_HAVE__Exit */
#if defined(__CRT_HAVE_at_quick_exit) || defined(__CRT_HAVE__crt_at_quick_exit) || defined(__CRT_HAVE_atexit) || defined(__CRT_HAVE__crt_atexit)
__NAMESPACE_STD_USING(at_quick_exit)
#endif /* __CRT_HAVE_at_quick_exit || __CRT_HAVE__crt_at_quick_exit || __CRT_HAVE_atexit || __CRT_HAVE__crt_atexit */
#endif /* !__CXX_SYSTEM_HEADER */
#endif /* __USE_ISOC11 || __USE_ISOCXX11 */
#ifdef __USE_ISOC99
#ifndef __CXX_SYSTEM_HEADER
#if defined(__CRT_HAVE__Exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE_exit)
__NAMESPACE_STD_USING(_Exit)
#endif /* __CRT_HAVE__Exit || __CRT_HAVE__exit || __CRT_HAVE_quick_exit || __CRT_HAVE_exit */
#endif /* !__CXX_SYSTEM_HEADER */
#endif /* __USE_ISOC99 */
#ifndef __CXX_SYSTEM_HEADER
#if !defined(__malloc_defined) && defined(__std_malloc_defined)
#define __malloc_defined
__NAMESPACE_STD_USING(malloc)
#endif /* !__malloc_defined && __std_malloc_defined */
#if !defined(__calloc_defined) && defined(__std_calloc_defined)
#define __calloc_defined
__NAMESPACE_STD_USING(calloc)
#endif /* !__calloc_defined && __std_calloc_defined */
#if !defined(__realloc_defined) && defined(__std_realloc_defined)
#define __realloc_defined
__NAMESPACE_STD_USING(realloc)
#endif /* !__realloc_defined && __std_realloc_defined */
#if !defined(__free_defined) && defined(__std_free_defined)
#define __free_defined
__NAMESPACE_STD_USING(free)
#endif /* !__free_defined && __std_free_defined */
__NAMESPACE_STD_USING(srand)
__NAMESPACE_STD_USING(rand)
__NAMESPACE_STD_USING(atoi)
__NAMESPACE_STD_USING(atol)
#endif /* !__CXX_SYSTEM_HEADER */
#if defined(__LONGLONG) && defined(__USE_ISOC99)
#ifndef __CXX_SYSTEM_HEADER
__NAMESPACE_STD_USING(atoll)
#endif /* !__CXX_SYSTEM_HEADER */
#endif /* __LONGLONG && __USE_ISOC99 */
#ifndef __CXX_SYSTEM_HEADER
__NAMESPACE_STD_USING(strtoul)
__NAMESPACE_STD_USING(strtol)
#if !defined(__strtoull_defined) && defined(__std_strtoull_defined)
#define __strtoull_defined
__NAMESPACE_STD_USING(strtoull)
#endif /* !__strtoull_defined && __std_strtoull_defined */
#if !defined(__strtoll_defined) && defined(__std_strtoll_defined)
#define __strtoll_defined
__NAMESPACE_STD_USING(strtoll)
#endif /* !__strtoll_defined && __std_strtoll_defined */
#endif /* !__CXX_SYSTEM_HEADER */
#ifndef __NO_FPU
#ifndef __CXX_SYSTEM_HEADER
__NAMESPACE_STD_USING(atof)
__NAMESPACE_STD_USING(strtod)
#if !defined(__strtof_defined) && defined(__std_strtof_defined)
#define __strtof_defined
__NAMESPACE_STD_USING(strtof)
#endif /* !__strtof_defined && __std_strtof_defined */
#if !defined(__strtold_defined) && defined(__std_strtold_defined)
#define __strtold_defined
__NAMESPACE_STD_USING(strtold)
#endif /* !__strtold_defined && __std_strtold_defined */
#endif /* !__CXX_SYSTEM_HEADER */
#endif /* !__NO_FPU */

#if !defined(__NO_FPU) && (defined(__USE_GNU) || defined(__STDC_WANT_IEC_60559_BFP_EXT__))
__CDECLARE_OPT(__ATTR_NONNULL((3)),__STDC_INT32_AS_SIZE_T,__NOTHROW_NCX,strfromd,(char *__restrict __buf, __SIZE_TYPE__ __buflen, char const *__restrict __format, double __fp),(__buf,__buflen,__format,__fp))
__CDECLARE_OPT(__ATTR_NONNULL((3)),__STDC_INT32_AS_SIZE_T,__NOTHROW_NCX,strfromf,(char *__restrict __buf, __SIZE_TYPE__ __buflen, char const *__restrict __format, float __fp),(__buf,__buflen,__format,__fp))
#ifdef __COMPILER_HAVE_LONGDOUBLE
__CDECLARE_OPT(__ATTR_NONNULL((3)),__STDC_INT32_AS_SIZE_T,__NOTHROW_NCX,strfroml,(char *__restrict __buf, __SIZE_TYPE__ __buflen, char const *__restrict __format, __LONGDOUBLE __fp),(__buf,__buflen,__format,__fp))
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__NO_FPU  && (__USE_GNU || __STDC_WANT_IEC_60559_BFP_EXT__)*/

#ifdef __USE_KOS
#ifdef __CRT_HAVE_strtou32_r
/* >> strto32_r(3), strtou32_r(3), strto64_r(3), strtou64_r(3)
 * Safely parse & return an integer from `nptr', and store any potential
 * errors in `*error' (if non-NULL).  The following errors are  defined:
 *  - 0:         Success
 *  - ECANCELED: Nothing was parsed.
 *               In this case, `*endptr' is set to the original `nptr'
 *               (iow: leading spaces are _not_ skipped in `*endptr'),
 *               and the returned integer is `0'
 *  - ERANGE:    Integer over- or under-flow while parsing.
 *               In this case, `*endptr' is still updated correctly,  and
 *               the  returned integer is the closest representable value
 *               to the integer given in `nptr' (i.e. `U?INTn_(MIN|MAX)')
 *               This error supersedes `EINVAL' if both conditions apply.
 *  - EINVAL:    Only when `endptr == NULL': The parsed number is followed
 *               by   at  least  1  additional  non-whitespace  character.
 *               The returned integer value is not affected by this error. */
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,strtou32_r,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),(__nptr,__endptr,__base,__error))
#else /* __CRT_HAVE_strtou32_r */
#include <libc/local/stdlib/strtou32_r.h>
/* >> strto32_r(3), strtou32_r(3), strto64_r(3), strtou64_r(3)
 * Safely parse & return an integer from `nptr', and store any potential
 * errors in `*error' (if non-NULL).  The following errors are  defined:
 *  - 0:         Success
 *  - ECANCELED: Nothing was parsed.
 *               In this case, `*endptr' is set to the original `nptr'
 *               (iow: leading spaces are _not_ skipped in `*endptr'),
 *               and the returned integer is `0'
 *  - ERANGE:    Integer over- or under-flow while parsing.
 *               In this case, `*endptr' is still updated correctly,  and
 *               the  returned integer is the closest representable value
 *               to the integer given in `nptr' (i.e. `U?INTn_(MIN|MAX)')
 *               This error supersedes `EINVAL' if both conditions apply.
 *  - EINVAL:    Only when `endptr == NULL': The parsed number is followed
 *               by   at  least  1  additional  non-whitespace  character.
 *               The returned integer value is not affected by this error. */
__NAMESPACE_LOCAL_USING_OR_IMPL(strtou32_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __UINT32_TYPE__ __NOTHROW_NCX(__LIBCCALL strtou32_r)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtou32_r))(__nptr, __endptr, __base, __error); })
#endif /* !__CRT_HAVE_strtou32_r */
#ifdef __CRT_HAVE_strto32_r
/* >> strto32_r(3), strtou32_r(3), strto64_r(3), strtou64_r(3)
 * Safely parse & return an integer from `nptr', and store any potential
 * errors in `*error' (if non-NULL).  The following errors are  defined:
 *  - 0:         Success
 *  - ECANCELED: Nothing was parsed.
 *               In this case, `*endptr' is set to the original `nptr'
 *               (iow: leading spaces are _not_ skipped in `*endptr'),
 *               and the returned integer is `0'
 *  - ERANGE:    Integer over- or under-flow while parsing.
 *               In this case, `*endptr' is still updated correctly,  and
 *               the  returned integer is the closest representable value
 *               to the integer given in `nptr' (i.e. `U?INTn_(MIN|MAX)')
 *               This error supersedes `EINVAL' if both conditions apply.
 *  - EINVAL:    Only when `endptr == NULL': The parsed number is followed
 *               by   at  least  1  additional  non-whitespace  character.
 *               The returned integer value is not affected by this error. */
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,strto32_r,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),(__nptr,__endptr,__base,__error))
#else /* __CRT_HAVE_strto32_r */
#include <libc/local/stdlib/strto32_r.h>
/* >> strto32_r(3), strtou32_r(3), strto64_r(3), strtou64_r(3)
 * Safely parse & return an integer from `nptr', and store any potential
 * errors in `*error' (if non-NULL).  The following errors are  defined:
 *  - 0:         Success
 *  - ECANCELED: Nothing was parsed.
 *               In this case, `*endptr' is set to the original `nptr'
 *               (iow: leading spaces are _not_ skipped in `*endptr'),
 *               and the returned integer is `0'
 *  - ERANGE:    Integer over- or under-flow while parsing.
 *               In this case, `*endptr' is still updated correctly,  and
 *               the  returned integer is the closest representable value
 *               to the integer given in `nptr' (i.e. `U?INTn_(MIN|MAX)')
 *               This error supersedes `EINVAL' if both conditions apply.
 *  - EINVAL:    Only when `endptr == NULL': The parsed number is followed
 *               by   at  least  1  additional  non-whitespace  character.
 *               The returned integer value is not affected by this error. */
__NAMESPACE_LOCAL_USING_OR_IMPL(strto32_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __INT32_TYPE__ __NOTHROW_NCX(__LIBCCALL strto32_r)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strto32_r))(__nptr, __endptr, __base, __error); })
#endif /* !__CRT_HAVE_strto32_r */
#ifdef __UINT64_TYPE__
#ifdef __CRT_HAVE_strtou64_r
/* >> strto32_r(3), strtou32_r(3), strto64_r(3), strtou64_r(3)
 * Safely parse & return an integer from `nptr', and store any potential
 * errors in `*error' (if non-NULL).  The following errors are  defined:
 *  - 0:         Success
 *  - ECANCELED: Nothing was parsed.
 *               In this case, `*endptr' is set to the original `nptr'
 *               (iow: leading spaces are _not_ skipped in `*endptr'),
 *               and the returned integer is `0'
 *  - ERANGE:    Integer over- or under-flow while parsing.
 *               In this case, `*endptr' is still updated correctly,  and
 *               the  returned integer is the closest representable value
 *               to the integer given in `nptr' (i.e. `U?INTn_(MIN|MAX)')
 *               This error supersedes `EINVAL' if both conditions apply.
 *  - EINVAL:    Only when `endptr == NULL': The parsed number is followed
 *               by   at  least  1  additional  non-whitespace  character.
 *               The returned integer value is not affected by this error. */
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,strtou64_r,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),(__nptr,__endptr,__base,__error))
#else /* __CRT_HAVE_strtou64_r */
#include <libc/local/stdlib/strtou64_r.h>
/* >> strto32_r(3), strtou32_r(3), strto64_r(3), strtou64_r(3)
 * Safely parse & return an integer from `nptr', and store any potential
 * errors in `*error' (if non-NULL).  The following errors are  defined:
 *  - 0:         Success
 *  - ECANCELED: Nothing was parsed.
 *               In this case, `*endptr' is set to the original `nptr'
 *               (iow: leading spaces are _not_ skipped in `*endptr'),
 *               and the returned integer is `0'
 *  - ERANGE:    Integer over- or under-flow while parsing.
 *               In this case, `*endptr' is still updated correctly,  and
 *               the  returned integer is the closest representable value
 *               to the integer given in `nptr' (i.e. `U?INTn_(MIN|MAX)')
 *               This error supersedes `EINVAL' if both conditions apply.
 *  - EINVAL:    Only when `endptr == NULL': The parsed number is followed
 *               by   at  least  1  additional  non-whitespace  character.
 *               The returned integer value is not affected by this error. */
__NAMESPACE_LOCAL_USING_OR_IMPL(strtou64_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __UINT64_TYPE__ __NOTHROW_NCX(__LIBCCALL strtou64_r)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtou64_r))(__nptr, __endptr, __base, __error); })
#endif /* !__CRT_HAVE_strtou64_r */
#ifdef __CRT_HAVE_strto64_r
/* >> strto32_r(3), strtou32_r(3), strto64_r(3), strtou64_r(3)
 * Safely parse & return an integer from `nptr', and store any potential
 * errors in `*error' (if non-NULL).  The following errors are  defined:
 *  - 0:         Success
 *  - ECANCELED: Nothing was parsed.
 *               In this case, `*endptr' is set to the original `nptr'
 *               (iow: leading spaces are _not_ skipped in `*endptr'),
 *               and the returned integer is `0'
 *  - ERANGE:    Integer over- or under-flow while parsing.
 *               In this case, `*endptr' is still updated correctly,  and
 *               the  returned integer is the closest representable value
 *               to the integer given in `nptr' (i.e. `U?INTn_(MIN|MAX)')
 *               This error supersedes `EINVAL' if both conditions apply.
 *  - EINVAL:    Only when `endptr == NULL': The parsed number is followed
 *               by   at  least  1  additional  non-whitespace  character.
 *               The returned integer value is not affected by this error. */
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,strto64_r,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),(__nptr,__endptr,__base,__error))
#else /* __CRT_HAVE_strto64_r */
#include <libc/local/stdlib/strto64_r.h>
/* >> strto32_r(3), strtou32_r(3), strto64_r(3), strtou64_r(3)
 * Safely parse & return an integer from `nptr', and store any potential
 * errors in `*error' (if non-NULL).  The following errors are  defined:
 *  - 0:         Success
 *  - ECANCELED: Nothing was parsed.
 *               In this case, `*endptr' is set to the original `nptr'
 *               (iow: leading spaces are _not_ skipped in `*endptr'),
 *               and the returned integer is `0'
 *  - ERANGE:    Integer over- or under-flow while parsing.
 *               In this case, `*endptr' is still updated correctly,  and
 *               the  returned integer is the closest representable value
 *               to the integer given in `nptr' (i.e. `U?INTn_(MIN|MAX)')
 *               This error supersedes `EINVAL' if both conditions apply.
 *  - EINVAL:    Only when `endptr == NULL': The parsed number is followed
 *               by   at  least  1  additional  non-whitespace  character.
 *               The returned integer value is not affected by this error. */
__NAMESPACE_LOCAL_USING_OR_IMPL(strto64_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __INT64_TYPE__ __NOTHROW_NCX(__LIBCCALL strto64_r)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strto64_r))(__nptr, __endptr, __base, __error); })
#endif /* !__CRT_HAVE_strto64_r */
#endif /* __UINT64_TYPE__ */
#if defined(__CRT_HAVE_strto32_r) && __SIZEOF_LONG__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),long,__NOTHROW_NCX,strtol_r,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),strto32_r,(__nptr,__endptr,__base,__error))
#elif defined(__CRT_HAVE_strto64_r) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),long,__NOTHROW_NCX,strtol_r,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),strto64_r,(__nptr,__endptr,__base,__error))
#elif __SIZEOF_LONG__ == 4
#include <libc/local/stdlib/strto32_r.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) long __NOTHROW_NCX(__LIBCCALL strtol_r)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (long)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strto32_r))(__nptr, __endptr, __base, __error); }
#elif __SIZEOF_LONG__ == 8
#include <libc/local/stdlib/strto64_r.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) long __NOTHROW_NCX(__LIBCCALL strtol_r)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (long)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strto64_r))(__nptr, __endptr, __base, __error); }
#else /* ... */
#include <libc/local/stdlib/strtol_r.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strtol_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) long __NOTHROW_NCX(__LIBCCALL strtol_r)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtol_r))(__nptr, __endptr, __base, __error); })
#endif /* !... */
#if defined(__CRT_HAVE_strtou32_r) && __SIZEOF_LONG__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,strtoul_r,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),strtou32_r,(__nptr,__endptr,__base,__error))
#elif defined(__CRT_HAVE_strtou64_r) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,strtoul_r,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),strtou64_r,(__nptr,__endptr,__base,__error))
#elif __SIZEOF_LONG__ == 4
#include <libc/local/stdlib/strtou32_r.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) unsigned long __NOTHROW_NCX(__LIBCCALL strtoul_r)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (unsigned long)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtou32_r))(__nptr, __endptr, __base, __error); }
#elif __SIZEOF_LONG__ == 8
#include <libc/local/stdlib/strtou64_r.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) unsigned long __NOTHROW_NCX(__LIBCCALL strtoul_r)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (unsigned long)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtou64_r))(__nptr, __endptr, __base, __error); }
#else /* ... */
#include <libc/local/stdlib/strtoul_r.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strtoul_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) unsigned long __NOTHROW_NCX(__LIBCCALL strtoul_r)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtoul_r))(__nptr, __endptr, __base, __error); })
#endif /* !... */
#ifdef __LONGLONG
#if defined(__CRT_HAVE_strto64_r) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,strtoll_r,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),strto64_r,(__nptr,__endptr,__base,__error))
#elif defined(__CRT_HAVE_strto32_r) && __SIZEOF_LONG_LONG__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,strtoll_r,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),strto32_r,(__nptr,__endptr,__base,__error))
#elif __SIZEOF_LONG_LONG__ == 8
#include <libc/local/stdlib/strto64_r.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __LONGLONG __NOTHROW_NCX(__LIBCCALL strtoll_r)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (__LONGLONG)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strto64_r))(__nptr, __endptr, __base, __error); }
#elif __SIZEOF_LONG_LONG__ == 4
#include <libc/local/stdlib/strto32_r.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __LONGLONG __NOTHROW_NCX(__LIBCCALL strtoll_r)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (__LONGLONG)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strto32_r))(__nptr, __endptr, __base, __error); }
#else /* ... */
#include <libc/local/stdlib/strtoll_r.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strtoll_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __LONGLONG __NOTHROW_NCX(__LIBCCALL strtoll_r)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtoll_r))(__nptr, __endptr, __base, __error); })
#endif /* !... */
#if defined(__CRT_HAVE_strtou64_r) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,strtoull_r,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),strtou64_r,(__nptr,__endptr,__base,__error))
#elif defined(__CRT_HAVE_strtou32_r) && __SIZEOF_LONG_LONG__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,strtoull_r,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),strtou32_r,(__nptr,__endptr,__base,__error))
#elif __SIZEOF_LONG_LONG__ == 8
#include <libc/local/stdlib/strtou64_r.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __ULONGLONG __NOTHROW_NCX(__LIBCCALL strtoull_r)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (__ULONGLONG)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtou64_r))(__nptr, __endptr, __base, __error); }
#elif __SIZEOF_LONG_LONG__ == 4
#include <libc/local/stdlib/strtou32_r.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __ULONGLONG __NOTHROW_NCX(__LIBCCALL strtoull_r)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (__ULONGLONG)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtou32_r))(__nptr, __endptr, __base, __error); }
#else /* ... */
#include <libc/local/stdlib/strtoull_r.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strtoull_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __ULONGLONG __NOTHROW_NCX(__LIBCCALL strtoull_r)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtoull_r))(__nptr, __endptr, __base, __error); })
#endif /* !... */
#endif /* __LONGLONG */
#ifdef __CRT_HAVE_strtou32
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string  (radix=`base') from `nptr'  into an  integer,
 * and store a  pointer to  the end  of the  number in  `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid   integer   (`U?INTn_(MIN|MAX))'.   (though   note   that
 * `endptr'  (if  non-NULL)  is  still  updated  in  this   case!)
 * Upon success, `errno' is left  unchanged, and the integer  repr
 * of the parsed number is  returned. When no integer was  parsed,
 * then `0' is returned, `*endptr'  is set to `nptr', but  `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,strtou32,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoul) && __SIZEOF_LONG__ == 4
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string  (radix=`base') from `nptr'  into an  integer,
 * and store a  pointer to  the end  of the  number in  `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid   integer   (`U?INTn_(MIN|MAX))'.   (though   note   that
 * `endptr'  (if  non-NULL)  is  still  updated  in  this   case!)
 * Upon success, `errno' is left  unchanged, and the integer  repr
 * of the parsed number is  returned. When no integer was  parsed,
 * then `0' is returned, `*endptr'  is set to `nptr', but  `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,strtou32,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoull) && __SIZEOF_LONG_LONG__ == 4
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string  (radix=`base') from `nptr'  into an  integer,
 * and store a  pointer to  the end  of the  number in  `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid   integer   (`U?INTn_(MIN|MAX))'.   (though   note   that
 * `endptr'  (if  non-NULL)  is  still  updated  in  this   case!)
 * Upon success, `errno' is left  unchanged, and the integer  repr
 * of the parsed number is  returned. When no integer was  parsed,
 * then `0' is returned, `*endptr'  is set to `nptr', but  `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,strtou32,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtouq) && __SIZEOF_LONG_LONG__ == 4
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string  (radix=`base') from `nptr'  into an  integer,
 * and store a  pointer to  the end  of the  number in  `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid   integer   (`U?INTn_(MIN|MAX))'.   (though   note   that
 * `endptr'  (if  non-NULL)  is  still  updated  in  this   case!)
 * Upon success, `errno' is left  unchanged, and the integer  repr
 * of the parsed number is  returned. When no integer was  parsed,
 * then `0' is returned, `*endptr'  is set to `nptr', but  `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,strtou32,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE___strtouq) && __SIZEOF_LONG_LONG__ == 4
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string  (radix=`base') from `nptr'  into an  integer,
 * and store a  pointer to  the end  of the  number in  `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid   integer   (`U?INTn_(MIN|MAX))'.   (though   note   that
 * `endptr'  (if  non-NULL)  is  still  updated  in  this   case!)
 * Upon success, `errno' is left  unchanged, and the integer  repr
 * of the parsed number is  returned. When no integer was  parsed,
 * then `0' is returned, `*endptr'  is set to `nptr', but  `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,strtou32,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),__strtouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoumax) && __SIZEOF_INTMAX_T__ == 4
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string  (radix=`base') from `nptr'  into an  integer,
 * and store a  pointer to  the end  of the  number in  `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid   integer   (`U?INTn_(MIN|MAX))'.   (though   note   that
 * `endptr'  (if  non-NULL)  is  still  updated  in  this   case!)
 * Upon success, `errno' is left  unchanged, and the integer  repr
 * of the parsed number is  returned. When no integer was  parsed,
 * then `0' is returned, `*endptr'  is set to `nptr', but  `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,strtou32,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoumax,(__nptr,__endptr,__base))
#else /* ... */
#include <libc/local/stdlib/strtou32.h>
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string  (radix=`base') from `nptr'  into an  integer,
 * and store a  pointer to  the end  of the  number in  `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid   integer   (`U?INTn_(MIN|MAX))'.   (though   note   that
 * `endptr'  (if  non-NULL)  is  still  updated  in  this   case!)
 * Upon success, `errno' is left  unchanged, and the integer  repr
 * of the parsed number is  returned. When no integer was  parsed,
 * then `0' is returned, `*endptr'  is set to `nptr', but  `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__NAMESPACE_LOCAL_USING_OR_IMPL(strtou32, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __UINT32_TYPE__ __NOTHROW_NCX(__LIBCCALL strtou32)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtou32))(__nptr, __endptr, __base); })
#endif /* !... */
#ifdef __CRT_HAVE_strto32
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string  (radix=`base') from `nptr'  into an  integer,
 * and store a  pointer to  the end  of the  number in  `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid   integer   (`U?INTn_(MIN|MAX))'.   (though   note   that
 * `endptr'  (if  non-NULL)  is  still  updated  in  this   case!)
 * Upon success, `errno' is left  unchanged, and the integer  repr
 * of the parsed number is  returned. When no integer was  parsed,
 * then `0' is returned, `*endptr'  is set to `nptr', but  `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,strto32,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtol) && __SIZEOF_LONG__ == 4
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string  (radix=`base') from `nptr'  into an  integer,
 * and store a  pointer to  the end  of the  number in  `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid   integer   (`U?INTn_(MIN|MAX))'.   (though   note   that
 * `endptr'  (if  non-NULL)  is  still  updated  in  this   case!)
 * Upon success, `errno' is left  unchanged, and the integer  repr
 * of the parsed number is  returned. When no integer was  parsed,
 * then `0' is returned, `*endptr'  is set to `nptr', but  `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,strto32,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoll) && __SIZEOF_LONG_LONG__ == 4
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string  (radix=`base') from `nptr'  into an  integer,
 * and store a  pointer to  the end  of the  number in  `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid   integer   (`U?INTn_(MIN|MAX))'.   (though   note   that
 * `endptr'  (if  non-NULL)  is  still  updated  in  this   case!)
 * Upon success, `errno' is left  unchanged, and the integer  repr
 * of the parsed number is  returned. When no integer was  parsed,
 * then `0' is returned, `*endptr'  is set to `nptr', but  `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,strto32,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoq) && __SIZEOF_LONG_LONG__ == 4
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string  (radix=`base') from `nptr'  into an  integer,
 * and store a  pointer to  the end  of the  number in  `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid   integer   (`U?INTn_(MIN|MAX))'.   (though   note   that
 * `endptr'  (if  non-NULL)  is  still  updated  in  this   case!)
 * Upon success, `errno' is left  unchanged, and the integer  repr
 * of the parsed number is  returned. When no integer was  parsed,
 * then `0' is returned, `*endptr'  is set to `nptr', but  `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,strto32,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE___strtoq) && __SIZEOF_LONG_LONG__ == 4
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string  (radix=`base') from `nptr'  into an  integer,
 * and store a  pointer to  the end  of the  number in  `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid   integer   (`U?INTn_(MIN|MAX))'.   (though   note   that
 * `endptr'  (if  non-NULL)  is  still  updated  in  this   case!)
 * Upon success, `errno' is left  unchanged, and the integer  repr
 * of the parsed number is  returned. When no integer was  parsed,
 * then `0' is returned, `*endptr'  is set to `nptr', but  `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,strto32,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),__strtoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoimax) && __SIZEOF_INTMAX_T__ == 4
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string  (radix=`base') from `nptr'  into an  integer,
 * and store a  pointer to  the end  of the  number in  `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid   integer   (`U?INTn_(MIN|MAX))'.   (though   note   that
 * `endptr'  (if  non-NULL)  is  still  updated  in  this   case!)
 * Upon success, `errno' is left  unchanged, and the integer  repr
 * of the parsed number is  returned. When no integer was  parsed,
 * then `0' is returned, `*endptr'  is set to `nptr', but  `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,strto32,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoimax,(__nptr,__endptr,__base))
#else /* ... */
#include <libc/local/stdlib/strto32.h>
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string  (radix=`base') from `nptr'  into an  integer,
 * and store a  pointer to  the end  of the  number in  `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid   integer   (`U?INTn_(MIN|MAX))'.   (though   note   that
 * `endptr'  (if  non-NULL)  is  still  updated  in  this   case!)
 * Upon success, `errno' is left  unchanged, and the integer  repr
 * of the parsed number is  returned. When no integer was  parsed,
 * then `0' is returned, `*endptr'  is set to `nptr', but  `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__NAMESPACE_LOCAL_USING_OR_IMPL(strto32, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __INT32_TYPE__ __NOTHROW_NCX(__LIBCCALL strto32)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strto32))(__nptr, __endptr, __base); })
#endif /* !... */
#ifdef __UINT64_TYPE__
#ifdef __CRT_HAVE_strtou64
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string  (radix=`base') from `nptr'  into an  integer,
 * and store a  pointer to  the end  of the  number in  `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid   integer   (`U?INTn_(MIN|MAX))'.   (though   note   that
 * `endptr'  (if  non-NULL)  is  still  updated  in  this   case!)
 * Upon success, `errno' is left  unchanged, and the integer  repr
 * of the parsed number is  returned. When no integer was  parsed,
 * then `0' is returned, `*endptr'  is set to `nptr', but  `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,strtou64,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__strtoui64)
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string  (radix=`base') from `nptr'  into an  integer,
 * and store a  pointer to  the end  of the  number in  `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid   integer   (`U?INTn_(MIN|MAX))'.   (though   note   that
 * `endptr'  (if  non-NULL)  is  still  updated  in  this   case!)
 * Upon success, `errno' is left  unchanged, and the integer  repr
 * of the parsed number is  returned. When no integer was  parsed,
 * then `0' is returned, `*endptr'  is set to `nptr', but  `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,strtou64,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),_strtoui64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoul) && __SIZEOF_LONG__ == 8
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string  (radix=`base') from `nptr'  into an  integer,
 * and store a  pointer to  the end  of the  number in  `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid   integer   (`U?INTn_(MIN|MAX))'.   (though   note   that
 * `endptr'  (if  non-NULL)  is  still  updated  in  this   case!)
 * Upon success, `errno' is left  unchanged, and the integer  repr
 * of the parsed number is  returned. When no integer was  parsed,
 * then `0' is returned, `*endptr'  is set to `nptr', but  `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,strtou64,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoull) && __SIZEOF_LONG_LONG__ == 8
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string  (radix=`base') from `nptr'  into an  integer,
 * and store a  pointer to  the end  of the  number in  `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid   integer   (`U?INTn_(MIN|MAX))'.   (though   note   that
 * `endptr'  (if  non-NULL)  is  still  updated  in  this   case!)
 * Upon success, `errno' is left  unchanged, and the integer  repr
 * of the parsed number is  returned. When no integer was  parsed,
 * then `0' is returned, `*endptr'  is set to `nptr', but  `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,strtou64,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtouq) && __SIZEOF_LONG_LONG__ == 8
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string  (radix=`base') from `nptr'  into an  integer,
 * and store a  pointer to  the end  of the  number in  `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid   integer   (`U?INTn_(MIN|MAX))'.   (though   note   that
 * `endptr'  (if  non-NULL)  is  still  updated  in  this   case!)
 * Upon success, `errno' is left  unchanged, and the integer  repr
 * of the parsed number is  returned. When no integer was  parsed,
 * then `0' is returned, `*endptr'  is set to `nptr', but  `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,strtou64,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE___strtouq) && __SIZEOF_LONG_LONG__ == 8
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string  (radix=`base') from `nptr'  into an  integer,
 * and store a  pointer to  the end  of the  number in  `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid   integer   (`U?INTn_(MIN|MAX))'.   (though   note   that
 * `endptr'  (if  non-NULL)  is  still  updated  in  this   case!)
 * Upon success, `errno' is left  unchanged, and the integer  repr
 * of the parsed number is  returned. When no integer was  parsed,
 * then `0' is returned, `*endptr'  is set to `nptr', but  `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,strtou64,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),__strtouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoumax) && __SIZEOF_INTMAX_T__ == 8
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string  (radix=`base') from `nptr'  into an  integer,
 * and store a  pointer to  the end  of the  number in  `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid   integer   (`U?INTn_(MIN|MAX))'.   (though   note   that
 * `endptr'  (if  non-NULL)  is  still  updated  in  this   case!)
 * Upon success, `errno' is left  unchanged, and the integer  repr
 * of the parsed number is  returned. When no integer was  parsed,
 * then `0' is returned, `*endptr'  is set to `nptr', but  `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,strtou64,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoumax,(__nptr,__endptr,__base))
#else /* ... */
#include <libc/local/stdlib/strtou64.h>
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string  (radix=`base') from `nptr'  into an  integer,
 * and store a  pointer to  the end  of the  number in  `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid   integer   (`U?INTn_(MIN|MAX))'.   (though   note   that
 * `endptr'  (if  non-NULL)  is  still  updated  in  this   case!)
 * Upon success, `errno' is left  unchanged, and the integer  repr
 * of the parsed number is  returned. When no integer was  parsed,
 * then `0' is returned, `*endptr'  is set to `nptr', but  `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__NAMESPACE_LOCAL_USING_OR_IMPL(strtou64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __UINT64_TYPE__ __NOTHROW_NCX(__LIBCCALL strtou64)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtou64))(__nptr, __endptr, __base); })
#endif /* !... */
#ifdef __CRT_HAVE_strto64
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string  (radix=`base') from `nptr'  into an  integer,
 * and store a  pointer to  the end  of the  number in  `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid   integer   (`U?INTn_(MIN|MAX))'.   (though   note   that
 * `endptr'  (if  non-NULL)  is  still  updated  in  this   case!)
 * Upon success, `errno' is left  unchanged, and the integer  repr
 * of the parsed number is  returned. When no integer was  parsed,
 * then `0' is returned, `*endptr'  is set to `nptr', but  `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,strto64,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__strtoi64)
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string  (radix=`base') from `nptr'  into an  integer,
 * and store a  pointer to  the end  of the  number in  `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid   integer   (`U?INTn_(MIN|MAX))'.   (though   note   that
 * `endptr'  (if  non-NULL)  is  still  updated  in  this   case!)
 * Upon success, `errno' is left  unchanged, and the integer  repr
 * of the parsed number is  returned. When no integer was  parsed,
 * then `0' is returned, `*endptr'  is set to `nptr', but  `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,strto64,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),_strtoi64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtol) && __SIZEOF_LONG__ == 8
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string  (radix=`base') from `nptr'  into an  integer,
 * and store a  pointer to  the end  of the  number in  `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid   integer   (`U?INTn_(MIN|MAX))'.   (though   note   that
 * `endptr'  (if  non-NULL)  is  still  updated  in  this   case!)
 * Upon success, `errno' is left  unchanged, and the integer  repr
 * of the parsed number is  returned. When no integer was  parsed,
 * then `0' is returned, `*endptr'  is set to `nptr', but  `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,strto64,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoll) && __SIZEOF_LONG_LONG__ == 8
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string  (radix=`base') from `nptr'  into an  integer,
 * and store a  pointer to  the end  of the  number in  `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid   integer   (`U?INTn_(MIN|MAX))'.   (though   note   that
 * `endptr'  (if  non-NULL)  is  still  updated  in  this   case!)
 * Upon success, `errno' is left  unchanged, and the integer  repr
 * of the parsed number is  returned. When no integer was  parsed,
 * then `0' is returned, `*endptr'  is set to `nptr', but  `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,strto64,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoq) && __SIZEOF_LONG_LONG__ == 8
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string  (radix=`base') from `nptr'  into an  integer,
 * and store a  pointer to  the end  of the  number in  `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid   integer   (`U?INTn_(MIN|MAX))'.   (though   note   that
 * `endptr'  (if  non-NULL)  is  still  updated  in  this   case!)
 * Upon success, `errno' is left  unchanged, and the integer  repr
 * of the parsed number is  returned. When no integer was  parsed,
 * then `0' is returned, `*endptr'  is set to `nptr', but  `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,strto64,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE___strtoq) && __SIZEOF_LONG_LONG__ == 8
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string  (radix=`base') from `nptr'  into an  integer,
 * and store a  pointer to  the end  of the  number in  `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid   integer   (`U?INTn_(MIN|MAX))'.   (though   note   that
 * `endptr'  (if  non-NULL)  is  still  updated  in  this   case!)
 * Upon success, `errno' is left  unchanged, and the integer  repr
 * of the parsed number is  returned. When no integer was  parsed,
 * then `0' is returned, `*endptr'  is set to `nptr', but  `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,strto64,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),__strtoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoimax) && __SIZEOF_INTMAX_T__ == 8
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string  (radix=`base') from `nptr'  into an  integer,
 * and store a  pointer to  the end  of the  number in  `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid   integer   (`U?INTn_(MIN|MAX))'.   (though   note   that
 * `endptr'  (if  non-NULL)  is  still  updated  in  this   case!)
 * Upon success, `errno' is left  unchanged, and the integer  repr
 * of the parsed number is  returned. When no integer was  parsed,
 * then `0' is returned, `*endptr'  is set to `nptr', but  `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,strto64,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoimax,(__nptr,__endptr,__base))
#else /* ... */
#include <libc/local/stdlib/strto64.h>
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string  (radix=`base') from `nptr'  into an  integer,
 * and store a  pointer to  the end  of the  number in  `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid   integer   (`U?INTn_(MIN|MAX))'.   (though   note   that
 * `endptr'  (if  non-NULL)  is  still  updated  in  this   case!)
 * Upon success, `errno' is left  unchanged, and the integer  repr
 * of the parsed number is  returned. When no integer was  parsed,
 * then `0' is returned, `*endptr'  is set to `nptr', but  `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__NAMESPACE_LOCAL_USING_OR_IMPL(strto64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __INT64_TYPE__ __NOTHROW_NCX(__LIBCCALL strto64)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strto64))(__nptr, __endptr, __base); })
#endif /* !... */
#endif /* __UINT64_TYPE__ */

#ifdef __USE_XOPEN2K8
#ifdef __CRT_HAVE_strtou32_l
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,strtou32_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtoul_l) && __SIZEOF_LONG__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,strtou32_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoul_l) && __SIZEOF_LONG__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,strtou32_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_strtoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___strtoul_l) && __SIZEOF_LONG__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,strtou32_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__strtoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtoull_l) && __SIZEOF_LONG_LONG__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,strtou32_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoull_l) && __SIZEOF_LONG_LONG__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,strtou32_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_strtoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___strtoull_l) && __SIZEOF_LONG_LONG__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,strtou32_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__strtoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtouq_l) && __SIZEOF_LONG_LONG__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,strtou32_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtouq_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtoumax_l) && __SIZEOF_INTMAX_T__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,strtou32_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoumax_l) && __SIZEOF_INTMAX_T__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,strtou32_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_strtoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___strtoumax_l) && __SIZEOF_INTMAX_T__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,strtou32_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__strtoumax_l,(__nptr,__endptr,__base,__locale))
#else /* ... */
#include <libc/local/stdlib/strtou32_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strtou32_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __UINT32_TYPE__ __NOTHROW_NCX(__LIBCCALL strtou32_l)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtou32_l))(__nptr, __endptr, __base, __locale); })
#endif /* !... */
#ifdef __CRT_HAVE_strto32_l
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,strto32_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtol_l) && __SIZEOF_LONG__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,strto32_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtol_l) && __SIZEOF_LONG__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,strto32_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_strtol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___strtol_l) && __SIZEOF_LONG__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,strto32_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__strtol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtoll_l) && __SIZEOF_LONG_LONG__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,strto32_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoll_l) && __SIZEOF_LONG_LONG__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,strto32_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_strtoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___strtoll_l) && __SIZEOF_LONG_LONG__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,strto32_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__strtoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtoq_l) && __SIZEOF_LONG_LONG__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,strto32_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtoq_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtoimax_l) && __SIZEOF_INTMAX_T__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,strto32_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoimax_l) && __SIZEOF_INTMAX_T__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,strto32_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_strtoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___strtoimax_l) && __SIZEOF_INTMAX_T__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,strto32_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__strtoimax_l,(__nptr,__endptr,__base,__locale))
#else /* ... */
#include <libc/local/stdlib/strto32_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strto32_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __INT32_TYPE__ __NOTHROW_NCX(__LIBCCALL strto32_l)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strto32_l))(__nptr, __endptr, __base, __locale); })
#endif /* !... */
#ifdef __UINT64_TYPE__
#ifdef __CRT_HAVE_strtou64_l
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,strtou64_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoui64_l)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,strtou64_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_strtoui64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtoul_l) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,strtou64_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoul_l) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,strtou64_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_strtoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___strtoul_l) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,strtou64_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__strtoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtoull_l) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,strtou64_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoull_l) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,strtou64_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_strtoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___strtoull_l) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,strtou64_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__strtoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtouq_l) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,strtou64_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtouq_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtoumax_l) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,strtou64_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoumax_l) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,strtou64_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_strtoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___strtoumax_l) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,strtou64_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__strtoumax_l,(__nptr,__endptr,__base,__locale))
#else /* ... */
#include <libc/local/stdlib/strtou64_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strtou64_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __UINT64_TYPE__ __NOTHROW_NCX(__LIBCCALL strtou64_l)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtou64_l))(__nptr, __endptr, __base, __locale); })
#endif /* !... */
#ifdef __CRT_HAVE_strto64_l
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,strto64_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoi64_l)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,strto64_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_strtoi64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtol_l) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,strto64_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtol_l) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,strto64_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_strtol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___strtol_l) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,strto64_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__strtol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtoll_l) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,strto64_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoll_l) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,strto64_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_strtoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___strtoll_l) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,strto64_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__strtoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtoq_l) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,strto64_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtoq_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtoimax_l) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,strto64_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoimax_l) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,strto64_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_strtoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___strtoimax_l) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,strto64_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__strtoimax_l,(__nptr,__endptr,__base,__locale))
#else /* ... */
#include <libc/local/stdlib/strto64_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strto64_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __INT64_TYPE__ __NOTHROW_NCX(__LIBCCALL strto64_l)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strto64_l))(__nptr, __endptr, __base, __locale); })
#endif /* !... */
#endif /* __UINT64_TYPE__ */
#endif /* __USE_XOPEN2K8 */

/* >> char itoa_digit(bool upper, uint8_t digit); */
#define itoa_digit(upper, digit) \
	_itoa_digits[(digit) + (!!(upper) << 6)]

/* >> char itoa_decimal(uint8_t digit);
 * Same as `itoa_digit()', but weak undefined behavior when `digit >= 10' */
#define itoa_decimal(digit) \
	(char)('0' + (digit))

/* >> char const _itoa_digits[101] =
 * >> "0123456789abcdefghijklmnopqrstuvwxyz\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
 * >> "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"; // << offset from base: 64 */
#ifndef _itoa_digits
#ifdef __LOCAL_itoa_digits
#define _itoa_digits __LOCAL_itoa_digits
#elif defined(__CRT_HAVE__itoa_digits)
__LIBC char const _itoa_digits[101] __CASMNAME_SAME("_itoa_digits");
#define _itoa_digits _itoa_digits
#elif defined(__cplusplus)
#define _itoa_digits __LOCAL_itoa_digits_fp()
__ATTR_FORCEINLINE __ATTR_UNUSED __ATTR_VISIBILITY("hidden")
char const *(__LOCAL_itoa_digits_fp)(void) {
	__ATTR_VISIBILITY("hidden")
	static __LOCAL_LIBC_CONST_DATA_SECTION(_itoa_digits) char const ___itoa_digits_p[101] =
	"0123456789abcdefghijklmnopqrstuvwxyz\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	return ___itoa_digits_p;
}
#else /* ... */
__LOCAL_LIBC_CONST_DATA(_itoa_digits) char const _itoa_digits[101] =
"0123456789abcdefghijklmnopqrstuvwxyz\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
#define _itoa_digits _itoa_digits
#endif /* !... */
#endif /* !_itoa_digits */

/* >> char const _itoa_lower_digits[37] = "0123456789abcdefghijklmnopqrstuvwxyz"; */
#ifndef _itoa_lower_digits
#ifdef __LOCAL_itoa_lower_digits
#define _itoa_lower_digits __LOCAL_itoa_lower_digits
#elif defined(__CRT_HAVE__itoa_digits)
#define _itoa_lower_digits (_itoa_digits + 0)
#elif defined(__CRT_HAVE__itoa_lower_digits)
__LIBC char const _itoa_lower_digits[37] __CASMNAME_SAME("_itoa_lower_digits");
#define _itoa_lower_digits _itoa_lower_digits
#else /* ... */
#define _itoa_lower_digits (_itoa_digits + 0)
#endif /* !... */
#endif /* !_itoa_lower_digits */

/* >> char const _itoa_upper_digits[37] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"; */
#ifndef _itoa_upper_digits
#ifdef __LOCAL_itoa_upper_digits
#define _itoa_upper_digits __LOCAL_itoa_upper_digits
#elif defined(__CRT_HAVE__itoa_digits)
#define _itoa_upper_digits (_itoa_digits + 64)
#elif defined(__CRT_HAVE__itoa_upper_digits)
__LIBC char const _itoa_upper_digits[37] __CASMNAME_SAME("_itoa_upper_digits");
#define _itoa_upper_digits _itoa_upper_digits
#else /* ... */
#define _itoa_upper_digits (_itoa_digits + 64)
#endif /* !... */
#endif /* !_itoa_upper_digits */

#endif /* __USE_KOS */

#if (defined(__USE_MISC) || defined(__USE_DOS) || \
     (defined(__USE_XOPEN_EXTENDED) && !defined(__USE_XOPEN2K8)))
#ifndef __NO_FPU
#ifdef __CRT_HAVE_gcvt
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((3)),char *,__NOTHROW_NCX,gcvt,(double __val, int __ndigit, char *__buf),(__val,__ndigit,__buf))
#elif defined(__CRT_HAVE__gcvt)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((3)),char *,__NOTHROW_NCX,gcvt,(double __val, int __ndigit, char *__buf),_gcvt,(__val,__ndigit,__buf))
#else /* ... */
#include <libc/local/stdlib/gcvt.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(gcvt, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((3)) char *__NOTHROW_NCX(__LIBCCALL gcvt)(double __val, int __ndigit, char *__buf) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(gcvt))(__val, __ndigit, __buf); })
#endif /* !... */
#endif /* !__NO_FPU */
#endif /* ... */

#ifdef __USE_POSIX
#ifdef __CRT_HAVE_rand_r
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,rand_r,(unsigned int *__restrict __pseed),(__pseed))
#else /* __CRT_HAVE_rand_r */
#include <libc/local/stdlib/rand_r.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(rand_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL rand_r)(unsigned int *__restrict __pseed) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rand_r))(__pseed); })
#endif /* !__CRT_HAVE_rand_r */
#endif /* __USE_POSIX */

#ifdef __USE_MISC
#ifdef __LONGLONG
#ifdef __CRT_HAVE_strtoll
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,strtoq,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoq)
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,strtoq,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE___strtoq)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,strtoq,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),__strtoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strto64) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,strtoq,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strto64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strto32) && __SIZEOF_LONG_LONG__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,strtoq,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strto32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtol) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,strtoq,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__strtoi64) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,strtoq,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),_strtoi64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoimax) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,strtoq,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoimax,(__nptr,__endptr,__base))
#elif __SIZEOF_LONG__ == 8
#include <libc/local/stdlib/strto64.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __LONGLONG __NOTHROW_NCX(__LIBCCALL strtoq)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base) { return (__LONGLONG)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strto64))(__nptr, __endptr, __base); }
#elif __SIZEOF_LONG__ == 4
#include <libc/local/stdlib/strto32.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __LONGLONG __NOTHROW_NCX(__LIBCCALL strtoq)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base) { return (__LONGLONG)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strto32))(__nptr, __endptr, __base); }
#else /* ... */
#include <libc/local/stdlib/strtoll.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __LONGLONG __NOTHROW_NCX(__LIBCCALL strtoq)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtoll))(__nptr, __endptr, __base); }
#endif /* !... */
#ifdef __CRT_HAVE_strtoull
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,strtouq,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtouq)
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,strtouq,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE___strtouq)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,strtouq,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),__strtouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtou64) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,strtouq,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtou64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtou32) && __SIZEOF_LONG_LONG__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,strtouq,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtou32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoul) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,strtouq,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__strtoui64) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,strtouq,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),_strtoui64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoumax) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,strtouq,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoumax,(__nptr,__endptr,__base))
#elif __SIZEOF_LONG__ == 8
#include <libc/local/stdlib/strtou64.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __ULONGLONG __NOTHROW_NCX(__LIBCCALL strtouq)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base) { return (__ULONGLONG)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtou64))(__nptr, __endptr, __base); }
#elif __SIZEOF_LONG__ == 4
#include <libc/local/stdlib/strtou32.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __ULONGLONG __NOTHROW_NCX(__LIBCCALL strtouq)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base) { return (__ULONGLONG)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtou32))(__nptr, __endptr, __base); }
#else /* ... */
#include <libc/local/stdlib/strtoull.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __ULONGLONG __NOTHROW_NCX(__LIBCCALL strtouq)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtoull))(__nptr, __endptr, __base); }
#endif /* !... */
#endif /* __LONGLONG */
#ifndef __NO_FPU
#ifdef __CRT_HAVE_ecvt_r
__CDECLARE(__ATTR_NONNULL((3, 4, 5)),int,__NOTHROW_NCX,ecvt_r,(double __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign, char *__restrict __buf, __SIZE_TYPE__ __len),(__val,__ndigit,__decptr,__sign,__buf,__len))
#else /* __CRT_HAVE_ecvt_r */
#include <libc/local/stdlib/ecvt_r.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(ecvt_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((3, 4, 5)) int __NOTHROW_NCX(__LIBCCALL ecvt_r)(double __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign, char *__restrict __buf, __SIZE_TYPE__ __len) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ecvt_r))(__val, __ndigit, __decptr, __sign, __buf, __len); })
#endif /* !__CRT_HAVE_ecvt_r */
#ifdef __CRT_HAVE_fcvt_r
__CDECLARE(__ATTR_NONNULL((3, 4, 5)),int,__NOTHROW_NCX,fcvt_r,(double __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign, char *__restrict __buf, __SIZE_TYPE__ __len),(__val,__ndigit,__decptr,__sign,__buf,__len))
#else /* __CRT_HAVE_fcvt_r */
#include <libc/local/stdlib/fcvt_r.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fcvt_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((3, 4, 5)) int __NOTHROW_NCX(__LIBCCALL fcvt_r)(double __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign, char *__restrict __buf, __SIZE_TYPE__ __len) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fcvt_r))(__val, __ndigit, __decptr, __sign, __buf, __len); })
#endif /* !__CRT_HAVE_fcvt_r */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#ifdef __CRT_HAVE_qgcvt
__CDECLARE(__ATTR_NONNULL((3)),char *,__NOTHROW_NCX,qgcvt,(__LONGDOUBLE __val, int __ndigit, char *__buf),(__val,__ndigit,__buf))
#elif defined(__CRT_HAVE_gcvt) && __SIZEOF_LONG_DOUBLE__ == __SIZEOF_DOUBLE__
__CREDIRECT(__ATTR_NONNULL((3)),char *,__NOTHROW_NCX,qgcvt,(__LONGDOUBLE __val, int __ndigit, char *__buf),gcvt,(__val,__ndigit,__buf))
#elif defined(__CRT_HAVE__gcvt) && __SIZEOF_LONG_DOUBLE__ == __SIZEOF_DOUBLE__
__CREDIRECT(__ATTR_NONNULL((3)),char *,__NOTHROW_NCX,qgcvt,(__LONGDOUBLE __val, int __ndigit, char *__buf),_gcvt,(__val,__ndigit,__buf))
#else /* ... */
#include <libc/local/stdlib/qgcvt.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(qgcvt, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((3)) char *__NOTHROW_NCX(__LIBCCALL qgcvt)(__LONGDOUBLE __val, int __ndigit, char *__buf) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(qgcvt))(__val, __ndigit, __buf); })
#endif /* !... */
#ifdef __CRT_HAVE_qecvt_r
__CDECLARE(__ATTR_NONNULL((3, 4, 5)),int,__NOTHROW_NCX,qecvt_r,(__LONGDOUBLE __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign, char *__restrict __buf, __SIZE_TYPE__ __len),(__val,__ndigit,__decptr,__sign,__buf,__len))
#else /* __CRT_HAVE_qecvt_r */
#include <libc/local/stdlib/qecvt_r.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(qecvt_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((3, 4, 5)) int __NOTHROW_NCX(__LIBCCALL qecvt_r)(__LONGDOUBLE __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign, char *__restrict __buf, __SIZE_TYPE__ __len) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(qecvt_r))(__val, __ndigit, __decptr, __sign, __buf, __len); })
#endif /* !__CRT_HAVE_qecvt_r */
#ifdef __CRT_HAVE_qfcvt_r
__CDECLARE(__ATTR_NONNULL((3, 4, 5)),int,__NOTHROW_NCX,qfcvt_r,(__LONGDOUBLE __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign, char *__restrict __buf, __SIZE_TYPE__ __len),(__val,__ndigit,__decptr,__sign,__buf,__len))
#else /* __CRT_HAVE_qfcvt_r */
#include <libc/local/stdlib/qfcvt_r.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(qfcvt_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((3, 4, 5)) int __NOTHROW_NCX(__LIBCCALL qfcvt_r)(__LONGDOUBLE __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign, char *__restrict __buf, __SIZE_TYPE__ __len) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(qfcvt_r))(__val, __ndigit, __decptr, __sign, __buf, __len); })
#endif /* !__CRT_HAVE_qfcvt_r */
#ifdef __CRT_HAVE_qecvt
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((3, 4)),char *,__NOTHROW_NCX,qecvt,(__LONGDOUBLE __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign),(__val,__ndigit,__decptr,__sign))
#elif defined(__CRT_HAVE_ecvt) && __SIZEOF_LONG_DOUBLE__ == __SIZEOF_DOUBLE__
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((3, 4)),char *,__NOTHROW_NCX,qecvt,(__LONGDOUBLE __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign),ecvt,(__val,__ndigit,__decptr,__sign))
#elif defined(__CRT_HAVE__ecvt) && __SIZEOF_LONG_DOUBLE__ == __SIZEOF_DOUBLE__
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((3, 4)),char *,__NOTHROW_NCX,qecvt,(__LONGDOUBLE __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign),_ecvt,(__val,__ndigit,__decptr,__sign))
#else /* ... */
#include <libc/local/stdlib/qecvt.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(qecvt, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((3, 4)) char *__NOTHROW_NCX(__LIBCCALL qecvt)(__LONGDOUBLE __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(qecvt))(__val, __ndigit, __decptr, __sign); })
#endif /* !... */
#ifdef __CRT_HAVE_qfcvt
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((3, 4)),char *,__NOTHROW_NCX,qfcvt,(__LONGDOUBLE __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign),(__val,__ndigit,__decptr,__sign))
#elif defined(__CRT_HAVE_fcvt) && __SIZEOF_LONG_DOUBLE__ == __SIZEOF_DOUBLE__
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((3, 4)),char *,__NOTHROW_NCX,qfcvt,(__LONGDOUBLE __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign),fcvt,(__val,__ndigit,__decptr,__sign))
#elif defined(__CRT_HAVE__fcvt) && __SIZEOF_LONG_DOUBLE__ == __SIZEOF_DOUBLE__
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((3, 4)),char *,__NOTHROW_NCX,qfcvt,(__LONGDOUBLE __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign),_fcvt,(__val,__ndigit,__decptr,__sign))
#else /* ... */
#include <libc/local/stdlib/qfcvt.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(qfcvt, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((3, 4)) char *__NOTHROW_NCX(__LIBCCALL qfcvt)(__LONGDOUBLE __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(qfcvt))(__val, __ndigit, __decptr, __sign); })
#endif /* !... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__NO_FPU */
struct drand48_data {
	unsigned short __x[3];
	unsigned short __old_x[3];
	unsigned short __c;
	unsigned short __init;
	__ULONGLONG    __a;
};
#ifndef __NO_FPU
__CDECLARE_OPT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,drand48_r,(struct drand48_data *__restrict __buffer, double *__restrict __result),(__buffer,__result))
__CDECLARE_OPT(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_NCX,erand48_r,(unsigned short __xsubi[3], struct drand48_data *__restrict __buffer, double *__restrict __result),(__xsubi,__buffer,__result))
#endif /* !__NO_FPU */
__CDECLARE_OPT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,lrand48_r,(struct drand48_data *__restrict __buffer, long *__restrict __result),(__buffer,__result))
__CDECLARE_OPT(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_NCX,nrand48_r,(unsigned short __xsubi[3], struct drand48_data *__restrict __buffer, long *__restrict __result),(__xsubi,__buffer,__result))
__CDECLARE_OPT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,mrand48_r,(struct drand48_data *__restrict __buffer, long *__restrict __result),(__buffer,__result))
__CDECLARE_OPT(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_NCX,jrand48_r,(unsigned short __xsubi[3], struct drand48_data *__restrict __buffer, long *__restrict __result),(__xsubi,__buffer,__result))
__CDECLARE_OPT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,srand48_r,(long __seedval, struct drand48_data *__buffer),(__seedval,__buffer))
__CDECLARE_OPT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,seed48_r,(unsigned short __seed16v[3], struct drand48_data *__buffer),(__seed16v,__buffer))
__CDECLARE_OPT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,lcong48_r,(unsigned short __param[7], struct drand48_data *__buffer),(__param,__buffer))
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("fptr")
#pragma push_macro("rptr")
#pragma push_macro("state")
#pragma push_macro("rand_type")
#pragma push_macro("rand_deg")
#pragma push_macro("rand_sep")
#pragma push_macro("end_ptr")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef fptr
#undef rptr
#undef state
#undef rand_type
#undef rand_deg
#undef rand_sep
#undef end_ptr
struct random_data {
	__INT32_TYPE__ *fptr;
	__INT32_TYPE__ *rptr;
	__INT32_TYPE__ *state;
	int             rand_type;
	int             rand_deg;
	int             rand_sep;
	__INT32_TYPE__ *end_ptr;
};
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("end_ptr")
#pragma pop_macro("rand_sep")
#pragma pop_macro("rand_deg")
#pragma pop_macro("rand_type")
#pragma pop_macro("state")
#pragma pop_macro("rptr")
#pragma pop_macro("fptr")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
__CDECLARE_OPT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,random_r,(struct random_data *__restrict __buf, __INT32_TYPE__ *__restrict __result),(__buf,__result))
__CDECLARE_OPT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,srandom_r,(unsigned int __seed, struct random_data *__buf),(__seed,__buf))
__CDECLARE_OPT(__ATTR_NONNULL((2, 4)),int,__NOTHROW_NCX,initstate_r,(unsigned int __seed, char *__restrict __statebuf, __SIZE_TYPE__ __statelen, struct random_data *__restrict __buf),(__seed,__statebuf,__statelen,__buf))
__CDECLARE_OPT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,setstate_r,(char *__restrict __statebuf, struct random_data *__restrict __buf),(__statebuf,__buf))
__CDECLARE_OPT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,on_exit,(void (__LIBCCALL *__func)(int __status, void *__arg), void *__arg),(__func,__arg))
#ifdef __CRT_HAVE_clearenv
__CDECLARE(,int,__NOTHROW_NCX,clearenv,(void),())
#elif defined(__LOCAL_environ)
#include <libc/local/stdlib/clearenv.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(clearenv, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_NCX(__LIBCCALL clearenv)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(clearenv))(); })
#endif /* ... */
#ifndef __mkstemps_defined
#define __mkstemps_defined
#include <asm/os/oflags.h>
#if defined(__CRT_HAVE_mkstemps) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
/* >> mkstemps(3), mkstemps64(3)
 * Replace the last 6 characters of `template_' (which are followed by exactly
 * `suffixlen' more characters that are left alone), which must be filled with
 * all  'X'-characters before the  call (else errno=EINVAL  + return -1), with
 * random  characters such that the filename described by `template_' will not
 * already  exists. Then, create a new file  with `O_RDWR' and return the file
 * descriptor of that file.
 * @param: suffixlen: The #  of trailing  characters to-be  ignored
 *                    after the required 6 trailing 'X'-characters. */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,mkstemps,(char *__template_, __STDC_INT_AS_SIZE_T __suffixlen),(__template_,__suffixlen))
#elif defined(__CRT_HAVE_mkstemps64)
/* >> mkstemps(3), mkstemps64(3)
 * Replace the last 6 characters of `template_' (which are followed by exactly
 * `suffixlen' more characters that are left alone), which must be filled with
 * all  'X'-characters before the  call (else errno=EINVAL  + return -1), with
 * random  characters such that the filename described by `template_' will not
 * already  exists. Then, create a new file  with `O_RDWR' and return the file
 * descriptor of that file.
 * @param: suffixlen: The #  of trailing  characters to-be  ignored
 *                    after the required 6 trailing 'X'-characters. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,mkstemps,(char *__template_, __STDC_INT_AS_SIZE_T __suffixlen),mkstemps64,(__template_,__suffixlen))
#else /* ... */
#include <asm/os/fcntl.h>
#if (defined(__CRT_HAVE_mkostemps) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)) || defined(__CRT_HAVE_mkostemps64) || defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))
#include <libc/local/stdlib/mkstemps.h>
/* >> mkstemps(3), mkstemps64(3)
 * Replace the last 6 characters of `template_' (which are followed by exactly
 * `suffixlen' more characters that are left alone), which must be filled with
 * all  'X'-characters before the  call (else errno=EINVAL  + return -1), with
 * random  characters such that the filename described by `template_' will not
 * already  exists. Then, create a new file  with `O_RDWR' and return the file
 * descriptor of that file.
 * @param: suffixlen: The #  of trailing  characters to-be  ignored
 *                    after the required 6 trailing 'X'-characters. */
__NAMESPACE_LOCAL_USING_OR_IMPL(mkstemps, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __fd_t __NOTHROW_RPC(__LIBCCALL mkstemps)(char *__template_, __STDC_INT_AS_SIZE_T __suffixlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mkstemps))(__template_, __suffixlen); })
#else /* (__CRT_HAVE_mkostemps && (!__USE_FILE_OFFSET64 || !__O_LARGEFILE || !__O_LARGEFILE)) || __CRT_HAVE_mkostemps64 || __CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat)) */
#undef __mkstemps_defined
#endif /* (!__CRT_HAVE_mkostemps || (__USE_FILE_OFFSET64 && __O_LARGEFILE && __O_LARGEFILE)) && !__CRT_HAVE_mkostemps64 && !__CRT_HAVE_open64 && !__CRT_HAVE___open64 && !__CRT_HAVE_open && !__CRT_HAVE__open && !__CRT_HAVE___open && !__CRT_HAVE___libc_open && (!__AT_FDCWD || (!__CRT_HAVE_openat64 && !__CRT_HAVE_openat)) */
#endif /* !... */
#endif /* !__mkstemps_defined */
#ifdef __CRT_HAVE_rpmatch
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,rpmatch,(char const *__response),(__response))
#else /* __CRT_HAVE_rpmatch */
#include <libc/local/stdlib/rpmatch.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(rpmatch, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL rpmatch)(char const *__response) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rpmatch))(__response); })
#endif /* !__CRT_HAVE_rpmatch */
#ifndef __cfree_defined
#define __cfree_defined
#if __has_builtin(__builtin_free) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_free)
__CEIREDIRECT(,void,__NOTHROW_NCX,cfree,(void *__mallptr),free,{ __builtin_free(__mallptr); })
#elif defined(__CRT_HAVE_free)
__CREDIRECT_VOID(,__NOTHROW_NCX,cfree,(void *__mallptr),free,(__mallptr))
#elif defined(__CRT_HAVE_cfree)
__CDECLARE_VOID(,__NOTHROW_NCX,cfree,(void *__mallptr),(__mallptr))
#elif defined(__CRT_HAVE___libc_free)
__CREDIRECT_VOID(,__NOTHROW_NCX,cfree,(void *__mallptr),__libc_free,(__mallptr))
#else /* ... */
#undef __cfree_defined
#endif /* !... */
#endif /* !__cfree_defined */
#ifndef __NO_FPU
#if !defined(__getloadavg_defined) && defined(__CRT_HAVE_getloadavg)
#define __getloadavg_defined
__CDECLARE(,int,__NOTHROW_RPC,getloadavg,(double __loadavg[], __STDC_INT_AS_SIZE_T __nelem),(__loadavg,__nelem))
#endif /* !__getloadavg_defined && __CRT_HAVE_getloadavg */
#endif /* !__NO_FPU */
#ifdef __USE_LARGEFILE64
#include <asm/os/oflags.h>
#if defined(__CRT_HAVE_mkstemps) && (!defined(__O_LARGEFILE) || !__O_LARGEFILE)
/* >> mkstemps(3), mkstemps64(3)
 * Replace the last 6 characters of `template_' (which are followed by exactly
 * `suffixlen' more characters that are left alone), which must be filled with
 * all  'X'-characters before the  call (else errno=EINVAL  + return -1), with
 * random  characters such that the filename described by `template_' will not
 * already  exists. Then, create a new file  with `O_RDWR' and return the file
 * descriptor of that file.
 * @param: suffixlen: The #  of trailing  characters to-be  ignored
 *                    after the required 6 trailing 'X'-characters. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,mkstemps64,(char *__template_, __STDC_INT_AS_SIZE_T __suffixlen),mkstemps,(__template_,__suffixlen))
#elif defined(__CRT_HAVE_mkstemps64)
/* >> mkstemps(3), mkstemps64(3)
 * Replace the last 6 characters of `template_' (which are followed by exactly
 * `suffixlen' more characters that are left alone), which must be filled with
 * all  'X'-characters before the  call (else errno=EINVAL  + return -1), with
 * random  characters such that the filename described by `template_' will not
 * already  exists. Then, create a new file  with `O_RDWR' and return the file
 * descriptor of that file.
 * @param: suffixlen: The #  of trailing  characters to-be  ignored
 *                    after the required 6 trailing 'X'-characters. */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,mkstemps64,(char *__template_, __STDC_INT_AS_SIZE_T __suffixlen),(__template_,__suffixlen))
#else /* ... */
#include <asm/os/fcntl.h>
#if (defined(__CRT_HAVE_mkostemps) && (!defined(__O_LARGEFILE) || !__O_LARGEFILE)) || defined(__CRT_HAVE_mkostemps64) || defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))
#include <libc/local/stdlib/mkstemps64.h>
/* >> mkstemps(3), mkstemps64(3)
 * Replace the last 6 characters of `template_' (which are followed by exactly
 * `suffixlen' more characters that are left alone), which must be filled with
 * all  'X'-characters before the  call (else errno=EINVAL  + return -1), with
 * random  characters such that the filename described by `template_' will not
 * already  exists. Then, create a new file  with `O_RDWR' and return the file
 * descriptor of that file.
 * @param: suffixlen: The #  of trailing  characters to-be  ignored
 *                    after the required 6 trailing 'X'-characters. */
__NAMESPACE_LOCAL_USING_OR_IMPL(mkstemps64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __fd_t __NOTHROW_RPC(__LIBCCALL mkstemps64)(char *__template_, __STDC_INT_AS_SIZE_T __suffixlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mkstemps64))(__template_, __suffixlen); })
#endif /* (__CRT_HAVE_mkostemps && (!__O_LARGEFILE || !__O_LARGEFILE)) || __CRT_HAVE_mkostemps64 || __CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat)) */
#endif /* !... */
#endif /* __USE_LARGEFILE64 */
#endif /* __USE_MISC */

#if defined(__USE_MISC) || (defined(__USE_XOPEN_EXTENDED) && !defined(__USE_XOPEN2K))
#ifndef __valloc_defined
#define __valloc_defined
#ifdef __CRT_HAVE_valloc
__CDECLARE(__ATTR_MALL_PAGEALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,valloc,(__SIZE_TYPE__ __n_bytes),(__n_bytes))
#elif defined(__CRT_HAVE___libc_valloc)
__CREDIRECT(__ATTR_MALL_PAGEALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,valloc,(__SIZE_TYPE__ __n_bytes),__libc_valloc,(__n_bytes))
#elif defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)
#include <libc/local/malloc/valloc.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(valloc, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALL_PAGEALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)) void *__NOTHROW_NCX(__LIBCCALL valloc)(__SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(valloc))(__n_bytes); })
#else /* ... */
#undef __valloc_defined
#endif /* !... */
#endif /* !__valloc_defined */
#endif /* __USE_MISC || (__USE_XOPEN_EXTENDED && !__USE_XOPEN2K) */

#ifdef __USE_XOPEN2K
#ifndef __posix_memalign_defined
#define __posix_memalign_defined
#if __has_builtin(__builtin_posix_memalign) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_posix_memalign)
__CEIDECLARE_GCCNCX(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,posix_memalign,(void **__restrict __pp, __SIZE_TYPE__ __alignment, __SIZE_TYPE__ __n_bytes),{ return __builtin_posix_memalign(__pp, __alignment, __n_bytes); })
#elif defined(__CRT_HAVE_posix_memalign)
__CDECLARE_GCCNCX(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,posix_memalign,(void **__restrict __pp, __SIZE_TYPE__ __alignment, __SIZE_TYPE__ __n_bytes),(__pp,__alignment,__n_bytes))
#elif defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign)
#include <libc/local/malloc/posix_memalign.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(posix_memalign, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __errno_t __NOTHROW_NCX(__LIBCCALL posix_memalign)(void **__restrict __pp, __SIZE_TYPE__ __alignment, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(posix_memalign))(__pp, __alignment, __n_bytes); })
#else /* ... */
#undef __posix_memalign_defined
#endif /* !... */
#endif /* !__posix_memalign_defined */
#ifdef __CRT_HAVE_setenv
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,setenv,(char const *__varname, char const *__val, int __replace),(__varname,__val,__replace))
#elif (defined(__CRT_HAVE_getenv) || defined(__LOCAL_environ)) && defined(__CRT_HAVE__putenv_s)
#include <libc/local/stdlib/setenv.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(setenv, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL setenv)(char const *__varname, char const *__val, int __replace) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(setenv))(__varname, __val, __replace); })
#endif /* ... */
#ifdef __CRT_HAVE_unsetenv
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,unsetenv,(char const *__varname),(__varname))
#elif defined(__CRT_HAVE_putenv) || defined(__CRT_HAVE__putenv)
#include <libc/local/stdlib/unsetenv.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(unsetenv, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL unsetenv)(char const *__varname) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unsetenv))(__varname); })
#endif /* ... */
#endif /* __USE_XOPEN2K */

#ifdef __USE_ISOCXX17
#ifndef __CXX_SYSTEM_HEADER
#if !defined(__aligned_alloc_defined) && defined(__std_aligned_alloc_defined)
#define __aligned_alloc_defined
__NAMESPACE_STD_USING(aligned_alloc)
#endif /* !__aligned_alloc_defined && __std_aligned_alloc_defined */
#endif /* !__CXX_SYSTEM_HEADER */
#endif /* __USE_ISOCXX17 */

/* aligned_alloc() is defined by both c11 and c++17 */
#ifdef __USE_ISOC11
#ifndef __aligned_alloc_defined
#define __aligned_alloc_defined
#ifdef __std_aligned_alloc_defined
__NAMESPACE_STD_USING(aligned_alloc)
#elif __has_builtin(__builtin_aligned_alloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_aligned_alloc)
__CEIDECLARE_GCCNCX(__ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_ALIGN(1) __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,aligned_alloc,(size_t __alignment, size_t __n_bytes),{ return __builtin_aligned_alloc(__alignment, __n_bytes); })
#elif defined(__CRT_HAVE_memalign)
__CREDIRECT_GCCNCX(__ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_ALIGN(1) __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,aligned_alloc,(size_t __alignment, size_t __n_bytes),memalign,(__alignment,__n_bytes))
#elif defined(__CRT_HAVE_aligned_alloc)
__CDECLARE_GCCNCX(__ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_ALIGN(1) __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,aligned_alloc,(size_t __alignment, size_t __n_bytes),(__alignment,__n_bytes))
#elif defined(__CRT_HAVE___libc_memalign)
__CREDIRECT_GCCNCX(__ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_ALIGN(1) __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,aligned_alloc,(size_t __alignment, size_t __n_bytes),__libc_memalign,(__alignment,__n_bytes))
#elif defined(__CRT_HAVE_posix_memalign)
#include <libc/local/malloc/memalign.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_ALIGN(1) __ATTR_ALLOC_SIZE((2)) void *__NOTHROW_NCX(__LIBCCALL aligned_alloc)(size_t __alignment, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memalign))(__alignment, __n_bytes); }
#else /* ... */
#undef __aligned_alloc_defined
#endif /* !... */
#endif /* !__aligned_alloc_defined */
#endif /* __USE_ISOC11 */

#ifndef MB_CUR_MAX
#ifdef __LOCAL_MB_CUR_MAX
#define MB_CUR_MAX __LOCAL_MB_CUR_MAX
#elif defined(__mb_cur_max)
#define MB_CUR_MAX ((__SIZE_TYPE__)__mb_cur_max)
#elif defined(__ctype_get_mb_cur_max) || defined(____ctype_get_mb_cur_max_defined)
#define MB_CUR_MAX __ctype_get_mb_cur_max()
#elif defined(___mb_cur_max_func) || defined(_____mb_cur_max_func_defined)
#define MB_CUR_MAX ((__SIZE_TYPE__)___mb_cur_max_func())
#elif defined(__p___mb_cur_max) || defined(____p___mb_cur_max_defined)
#define MB_CUR_MAX ((__SIZE_TYPE__)*__p___mb_cur_max())
#elif defined(__CRT_HAVE___ctype_get_mb_cur_max)
#define ____ctype_get_mb_cur_max_defined
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__SIZE_TYPE__,__NOTHROW,__ctype_get_mb_cur_max,(void),())
#define MB_CUR_MAX __ctype_get_mb_cur_max()
#elif defined(__CRT_HAVE____mb_cur_max_func)
#define _____mb_cur_max_func_defined
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,___mb_cur_max_func,(void),())
#define MB_CUR_MAX ((__SIZE_TYPE__)___mb_cur_max_func())
#elif defined(__CRT_HAVE___p___mb_cur_max)
#define ____p___mb_cur_max_defined
__CDECLARE(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,int *,__NOTHROW,__p___mb_cur_max,(void),())
#define MB_CUR_MAX ((__SIZE_TYPE__)*__p___mb_cur_max())
#elif defined(__CRT_HAVE___mb_cur_max)
__LIBC int __mb_cur_max __CASMNAME_SAME("__mb_cur_max");
#define __mb_cur_max __mb_cur_max
#define MB_CUR_MAX   ((__SIZE_TYPE__)__mb_cur_max)
#else /* __CRT_HAVE___ctype_get_mb_cur_max */
#define MB_CUR_MAX 7 /* == UNICODE_UTF8_CURLEN */
#endif /* !__CRT_HAVE___ctype_get_mb_cur_max */
#endif /* !MB_CUR_MAX */

#if defined(__USE_MISC) || defined(__USE_XOPEN)
#ifndef __NO_FPU
__CDECLARE_OPT(,double,__NOTHROW_NCX,drand48,(void),())
#endif /* !__NO_FPU */
__CDECLARE_OPT(,long,__NOTHROW_NCX,lrand48,(void),())
__CDECLARE_OPT(,long,__NOTHROW_NCX,mrand48,(void),())
#ifndef __NO_FPU
__CDECLARE_OPT(__ATTR_NONNULL((1)),double,__NOTHROW_NCX,erand48,(unsigned short __xsubi[3]),(__xsubi))
#endif /* !__NO_FPU */
__CDECLARE_OPT(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,nrand48,(unsigned short __xsubi[3]),(__xsubi))
__CDECLARE_OPT(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,jrand48,(unsigned short __xsubi[3]),(__xsubi))
__CDECLARE_VOID_OPT(,__NOTHROW_NCX,srand48,(long __seedval),(__seedval))
__CDECLARE_OPT(__ATTR_NONNULL((1)),unsigned short *,__NOTHROW_NCX,seed48,(unsigned short __seed16v[3]),(__seed16v))
__CDECLARE_VOID_OPT(__ATTR_NONNULL((1)),__NOTHROW_NCX,lcong48,(unsigned short __param[7]),(__param))
#endif /* __USE_MISC || __USE_XOPEN */

#if defined(__USE_MISC) || defined(__USE_XOPEN) || defined(__USE_DOS)
#ifdef __CRT_HAVE_putenv
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,putenv,(char *__string),(__string))
#elif defined(__CRT_HAVE__putenv)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,putenv,(char *__string),_putenv,(__string))
#endif /* ... */
#endif /* __USE_MISC || __USE_XOPEN || __USE_DOS */

#if defined(__USE_MISC) || defined(__USE_XOPEN_EXTENDED)
#ifdef __CRT_HAVE_random
__CDECLARE(,long,__NOTHROW_NCX,random,(void),())
#elif defined(__CRT_HAVE___random)
__CREDIRECT(,long,__NOTHROW_NCX,random,(void),__random,())
#elif defined(__CRT_HAVE_rand) && __SIZEOF_LONG__ == __SIZEOF_INT__
__CREDIRECT(,long,__NOTHROW_NCX,random,(void),rand,())
#else /* ... */
#include <libc/local/stdlib/random.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(random, __FORCELOCAL __ATTR_ARTIFICIAL long __NOTHROW_NCX(__LIBCCALL random)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(random))(); })
#endif /* !... */
#ifdef __CRT_HAVE_srandom
__CDECLARE_VOID(,__NOTHROW_NCX,srandom,(unsigned int __seed),(__seed))
#elif defined(__CRT_HAVE___srandom)
__CREDIRECT_VOID(,__NOTHROW_NCX,srandom,(unsigned int __seed),__srandom,(__seed))
#elif defined(__CRT_HAVE_srand) && __SIZEOF_LONG__ == __SIZEOF_INT__
__CREDIRECT_VOID(,__NOTHROW_NCX,srandom,(unsigned int __seed),srand,(__seed))
#else /* ... */
#include <libc/local/stdlib/srandom.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(srandom, __FORCELOCAL __ATTR_ARTIFICIAL void __NOTHROW_NCX(__LIBCCALL srandom)(unsigned int __seed) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(srandom))(__seed); })
#endif /* !... */
#ifdef __CRT_HAVE_initstate
__CDECLARE(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,initstate,(unsigned int __seed, char *__statebuf, __SIZE_TYPE__ __statelen),(__seed,__statebuf,__statelen))
#elif defined(__CRT_HAVE___initstate)
__CREDIRECT(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,initstate,(unsigned int __seed, char *__statebuf, __SIZE_TYPE__ __statelen),__initstate,(__seed,__statebuf,__statelen))
#endif /* ... */
#ifdef __CRT_HAVE_setstate
__CDECLARE(__ATTR_NONNULL((1)),char *,__NOTHROW_NCX,setstate,(char *__statebuf),(__statebuf))
#elif defined(__CRT_HAVE___setstate)
__CREDIRECT(__ATTR_NONNULL((1)),char *,__NOTHROW_NCX,setstate,(char *__statebuf),__setstate,(__statebuf))
#endif /* ... */
#ifdef __CRT_HAVE_l64a
/* >> l64a(3), a64l(3)
 * Convert between `long' and base-64 encoded integer strings. */
__CDECLARE(__ATTR_RETNONNULL __ATTR_WUNUSED,char *,__NOTHROW_NCX,l64a,(long __n),(__n))
#else /* __CRT_HAVE_l64a */
#include <libc/local/stdlib/l64a.h>
/* >> l64a(3), a64l(3)
 * Convert between `long' and base-64 encoded integer strings. */
__NAMESPACE_LOCAL_USING_OR_IMPL(l64a, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_WUNUSED char *__NOTHROW_NCX(__LIBCCALL l64a)(long __n) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(l64a))(__n); })
#endif /* !__CRT_HAVE_l64a */
#ifdef __CRT_HAVE_a64l
/* >> l64a(3), a64l(3)
 * Convert between `long' and base-64 encoded integer strings. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),long,__NOTHROW_NCX,a64l,(char const *__s),(__s))
#else /* __CRT_HAVE_a64l */
#include <libc/local/stdlib/a64l.h>
/* >> l64a(3), a64l(3)
 * Convert between `long' and base-64 encoded integer strings. */
__NAMESPACE_LOCAL_USING_OR_IMPL(a64l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) long __NOTHROW_NCX(__LIBCCALL a64l)(char const *__s) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(a64l))(__s); })
#endif /* !__CRT_HAVE_a64l */
#ifdef __CRT_HAVE_realpath
/* >> realpath(3)
 * Load the filesystem location of a given file handle.
 * This  function behaves similar to `readlink()', but will also function for
 * non-symlink paths, as well as always return an absolute (unambiguous) path
 * @param: resolved: A buffer of `PATH_MAX' bytes to-be filled with the resulting
 *                   path, or NULL  to automatically `malloc()'ate  and return  a
 *                   buffer of sufficient size. */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_RPC,realpath,(char const *__filename, char *__resolved),(__filename,__resolved))
#else /* __CRT_HAVE_realpath */
#include <asm/os/fcntl.h>
#if defined(__AT_FDCWD) && defined(__CRT_HAVE_frealpathat)
#include <libc/local/stdlib/realpath.h>
/* >> realpath(3)
 * Load the filesystem location of a given file handle.
 * This  function behaves similar to `readlink()', but will also function for
 * non-symlink paths, as well as always return an absolute (unambiguous) path
 * @param: resolved: A buffer of `PATH_MAX' bytes to-be filled with the resulting
 *                   path, or NULL  to automatically `malloc()'ate  and return  a
 *                   buffer of sufficient size. */
__NAMESPACE_LOCAL_USING_OR_IMPL(realpath, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) char *__NOTHROW_RPC(__LIBCCALL realpath)(char const *__filename, char *__resolved) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(realpath))(__filename, __resolved); })
#endif /* __AT_FDCWD && __CRT_HAVE_frealpathat */
#endif /* !__CRT_HAVE_realpath */
#endif /* __USE_MISC || __USE_XOPEN_EXTENDED */

#if defined(__USE_MISC) || defined(__USE_XOPEN_EXTENDED) || defined(__USE_KOS)
/* NOTE: I didn't come up with this function (https://docs.oracle.com/cd/E36784_01/html/E36874/frealpath-3c.html),
 *       but it seems to be something that GLibc isn't implementing for some reason...
 *       Because of that, I didn't really know where to put this, so I put it in the
 *       same _SOURCE-block as its `realpath()' companion. */
#ifdef __CRT_HAVE_frealpath
/* >> frealpath(3)
 * Load the filesystem location of a given file handle.
 * This function behaves similar to `readlink("/proc/self/fd/%d" % fd)'
 * NOTE: You may  also pass  `NULL' for  `resolved' to  have a  buffer of  `buflen'
 *       bytes  automatically allocated  in the heap,  ontop of which  you may also
 *       pass `0' for `buflen' to automatically determine the required buffer size. */
__CDECLARE(__ATTR_WUNUSED,char *,__NOTHROW_RPC,frealpath,(__fd_t __fd, char *__resolved, __SIZE_TYPE__ __buflen),(__fd,__resolved,__buflen))
#elif defined(__CRT_HAVE_frealpath4)
#include <libc/local/stdlib/frealpath.h>
/* >> frealpath(3)
 * Load the filesystem location of a given file handle.
 * This function behaves similar to `readlink("/proc/self/fd/%d" % fd)'
 * NOTE: You may  also pass  `NULL' for  `resolved' to  have a  buffer of  `buflen'
 *       bytes  automatically allocated  in the heap,  ontop of which  you may also
 *       pass `0' for `buflen' to automatically determine the required buffer size. */
__NAMESPACE_LOCAL_USING_OR_IMPL(frealpath, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED char *__NOTHROW_RPC(__LIBCCALL frealpath)(__fd_t __fd, char *__resolved, __SIZE_TYPE__ __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(frealpath))(__fd, __resolved, __buflen); })
#endif /* ... */
#endif /* __USE_MISC || __USE_XOPEN_EXTENDED || __USE_KOS */

#ifdef __USE_KOS
/* >> frealpath4(2)
 * Load the filesystem location of a given file handle.
 * This function behaves similar to `readlink("/proc/self/fd/%d" % fd)'
 * @param flags: Set of `0 | AT_ALTPATH | AT_DOSPATH'
 * NOTE: You  may use `AT_ALTPATH' to cause the  path to be printed in alternate
 *       representation  mode. This means  that if the  path would have normally
 *       been printed as a unix path, it would instead be printed as a DOS path.
 *       Similarly, the reverse also applies.
 * NOTE: You may  also pass  `NULL' for  `resolved' to  have a  buffer of  `buflen'
 *       bytes  automatically allocated  in the heap,  ontop of which  you may also
 *       pass `0' for `buflen' to automatically determine the required buffer size. */
__CDECLARE_OPT(__ATTR_WUNUSED,char *,__NOTHROW_RPC,frealpath4,(__fd_t __fd, char *__resolved, __SIZE_TYPE__ __buflen, __atflag_t __flags),(__fd,__resolved,__buflen,__flags))
/* >> frealpathat(2)
 * Returns the absolute filesystem path for the specified file
 * When `AT_SYMLINK_NOFOLLOW' is given, a final symlink is not dereferenced,
 * causing the path to  the symlink itself to  be printed. - Otherwise,  the
 * file pointed to by the symblic link is printed.
 * NOTE: You  may use `AT_ALTPATH' to cause the  path to be printed in alternate
 *       representation  mode. This means  that if the  path would have normally
 *       been printed as a unix path, it would instead be printed as a DOS path.
 *       Similarly, the reverse also applies.
 * NOTE: You may  also pass  `NULL' for  `resolved' to  have a  buffer of  `buflen'
 *       bytes  automatically allocated  in the heap,  ontop of which  you may also
 *       pass `0' for `buflen' to automatically determine the required buffer size.
 * @param flags: Set of `0 | AT_ALTPATH | AT_SYMLINK_NOFOLLOW | AT_DOSPATH'
 * @return: NULL: [errno=ERANGE]: `buflen' is too small to fit the entire path */
__CDECLARE_OPT(__ATTR_WUNUSED __ATTR_NONNULL((2)),char *,__NOTHROW_RPC,frealpathat,(__fd_t __dirfd, char const *__filename, char *__resolved, __SIZE_TYPE__ __buflen, __atflag_t __flags),(__dirfd,__filename,__resolved,__buflen,__flags))
#endif /* __USE_KOS */


#if (defined(__USE_MISC) || \
     (defined(__USE_XOPEN_EXTENDED) && !defined(__USE_XOPEN2K8)))
#ifndef __mktemp_defined
#define __mktemp_defined
#ifdef __CRT_HAVE_mktemp
/* >> mktemp(3)
 * Badly designed version of  `mkstemp' that won't actually  create
 * the temporary file, meaning that by the time the caller tries to
 * create the  file themselves,  another process  may have  already
 * created it.
 * Also: when no  temporary filename  can be  created, rather  than
 *       returning something  sensible like  `NULL', this  function
 *       will instead set `template_' to an empty string, and still
 *       re-return it like it would if everything had worked! */
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,mktemp,(char *__template_),(__template_))
#elif defined(__CRT_HAVE__mktemp)
/* >> mktemp(3)
 * Badly designed version of  `mkstemp' that won't actually  create
 * the temporary file, meaning that by the time the caller tries to
 * create the  file themselves,  another process  may have  already
 * created it.
 * Also: when no  temporary filename  can be  created, rather  than
 *       returning something  sensible like  `NULL', this  function
 *       will instead set `template_' to an empty string, and still
 *       re-return it like it would if everything had worked! */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,mktemp,(char *__template_),_mktemp,(__template_))
#elif defined(__CRT_HAVE___mktemp)
/* >> mktemp(3)
 * Badly designed version of  `mkstemp' that won't actually  create
 * the temporary file, meaning that by the time the caller tries to
 * create the  file themselves,  another process  may have  already
 * created it.
 * Also: when no  temporary filename  can be  created, rather  than
 *       returning something  sensible like  `NULL', this  function
 *       will instead set `template_' to an empty string, and still
 *       re-return it like it would if everything had worked! */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,mktemp,(char *__template_),__mktemp,(__template_))
#else /* ... */
#include <asm/os/fcntl.h>
#include <bits/os/stat.h>
#if defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat))) || (defined(__CRT_HAVE_kstat) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE_kstat64) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE__stat64) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__stat64i32) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__stati64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && defined(__USE_FILE_OFFSET64)) || (defined(__CRT_HAVE__stat32i64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && defined(__USE_FILE_OFFSET64)) || (defined(__CRT_HAVE__stat) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && !defined(__USE_FILE_OFFSET64)) || (defined(__CRT_HAVE__stat32) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && !defined(__USE_FILE_OFFSET64)) || (defined(__CRT_HAVE_stat) && (!defined(__USE_FILE_OFFSET64) || defined(__STAT32_MATCHES_STAT64))) || (defined(__CRT_HAVE_stat64) && (defined(__USE_FILE_OFFSET64) || defined(__STAT32_MATCHES_STAT64)))
#include <libc/local/stdlib/mktemp.h>
/* >> mktemp(3)
 * Badly designed version of  `mkstemp' that won't actually  create
 * the temporary file, meaning that by the time the caller tries to
 * create the  file themselves,  another process  may have  already
 * created it.
 * Also: when no  temporary filename  can be  created, rather  than
 *       returning something  sensible like  `NULL', this  function
 *       will instead set `template_' to an empty string, and still
 *       re-return it like it would if everything had worked! */
__NAMESPACE_LOCAL_USING_OR_IMPL(mktemp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL mktemp)(char *__template_) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mktemp))(__template_); })
#else /* __CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat)) || (__CRT_HAVE_kstat && __CRT_KOS_PRIMARY) || (__CRT_HAVE_kstat64 && __CRT_KOS_PRIMARY) || (__CRT_HAVE__stat64 && __CRT_DOS_PRIMARY && __USE_TIME_BITS64) || (__CRT_HAVE__stat64i32 && __CRT_DOS_PRIMARY && __USE_TIME_BITS64) || (__CRT_HAVE__stati64 && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64 && __USE_FILE_OFFSET64) || (__CRT_HAVE__stat32i64 && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64 && __USE_FILE_OFFSET64) || (__CRT_HAVE__stat && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64 && !__USE_FILE_OFFSET64) || (__CRT_HAVE__stat32 && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64 && !__USE_FILE_OFFSET64) || (__CRT_HAVE_stat && (!__USE_FILE_OFFSET64 || __STAT32_MATCHES_STAT64)) || (__CRT_HAVE_stat64 && (__USE_FILE_OFFSET64 || __STAT32_MATCHES_STAT64)) */
#undef __mktemp_defined
#endif /* !__CRT_HAVE_open64 && !__CRT_HAVE___open64 && !__CRT_HAVE_open && !__CRT_HAVE__open && !__CRT_HAVE___open && !__CRT_HAVE___libc_open && (!__AT_FDCWD || (!__CRT_HAVE_openat64 && !__CRT_HAVE_openat)) && (!__CRT_HAVE_kstat || !__CRT_KOS_PRIMARY) && (!__CRT_HAVE_kstat64 || !__CRT_KOS_PRIMARY) && (!__CRT_HAVE__stat64 || !__CRT_DOS_PRIMARY || !__USE_TIME_BITS64) && (!__CRT_HAVE__stat64i32 || !__CRT_DOS_PRIMARY || !__USE_TIME_BITS64) && (!__CRT_HAVE__stati64 || !__CRT_DOS_PRIMARY || __USE_TIME_BITS64 || !__USE_FILE_OFFSET64) && (!__CRT_HAVE__stat32i64 || !__CRT_DOS_PRIMARY || __USE_TIME_BITS64 || !__USE_FILE_OFFSET64) && (!__CRT_HAVE__stat || !__CRT_DOS_PRIMARY || __USE_TIME_BITS64 || __USE_FILE_OFFSET64) && (!__CRT_HAVE__stat32 || !__CRT_DOS_PRIMARY || __USE_TIME_BITS64 || __USE_FILE_OFFSET64) && (!__CRT_HAVE_stat || (__USE_FILE_OFFSET64 && !__STAT32_MATCHES_STAT64)) && (!__CRT_HAVE_stat64 || (!__USE_FILE_OFFSET64 && !__STAT32_MATCHES_STAT64)) */
#endif /* !... */
#endif /* !__mktemp_defined */
#endif /* __USE_MISC || (__USE_XOPEN_EXTENDED && !__USE_XOPEN2K8) */


#if (defined(__USE_MISC) || defined(__USE_DOS) || \
     (defined(__USE_XOPEN_EXTENDED) && !defined(__USE_XOPEN2K8)))
#ifndef __NO_FPU
#ifdef __CRT_HAVE_ecvt
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((3, 4)),char *,__NOTHROW_NCX,ecvt,(double __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign),(__val,__ndigit,__decptr,__sign))
#elif defined(__CRT_HAVE__ecvt)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((3, 4)),char *,__NOTHROW_NCX,ecvt,(double __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign),_ecvt,(__val,__ndigit,__decptr,__sign))
#else /* ... */
#include <libc/local/stdlib/ecvt.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(ecvt, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((3, 4)) char *__NOTHROW_NCX(__LIBCCALL ecvt)(double __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ecvt))(__val, __ndigit, __decptr, __sign); })
#endif /* !... */
#ifdef __CRT_HAVE_fcvt
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((3, 4)),char *,__NOTHROW_NCX,fcvt,(double __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign),(__val,__ndigit,__decptr,__sign))
#elif defined(__CRT_HAVE__fcvt)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((3, 4)),char *,__NOTHROW_NCX,fcvt,(double __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign),_fcvt,(__val,__ndigit,__decptr,__sign))
#else /* ... */
#include <libc/local/stdlib/fcvt.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fcvt, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((3, 4)) char *__NOTHROW_NCX(__LIBCCALL fcvt)(double __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fcvt))(__val, __ndigit, __decptr, __sign); })
#endif /* !... */
#endif /* !__NO_FPU */
#endif /* __USE_MISC || __USE_DOS || (__USE_XOPEN_EXTENDED && !__USE_XOPEN2K8) */
#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K8)
#ifndef __getsubopt_defined
#define __getsubopt_defined
#ifdef __CRT_HAVE_getsubopt
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_NCX,getsubopt,(char **__restrict __optionp, char *const *__restrict __tokens, char **__restrict __valuep),(__optionp,__tokens,__valuep))
#else /* __CRT_HAVE_getsubopt */
#include <libc/local/stdlib/getsubopt.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(getsubopt, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 2, 3)) int __NOTHROW_NCX(__LIBCCALL getsubopt)(char **__restrict __optionp, char *const *__restrict __tokens, char **__restrict __valuep) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getsubopt))(__optionp, __tokens, __valuep); })
#endif /* !__CRT_HAVE_getsubopt */
#endif /* !__getsubopt_defined */
#if defined(__CRT_HAVE_mkstemp) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
/* >> mkstemp(3), mkstemp64(3)
 * Replace the last 6 characters of  `template_', which must be filled  with
 * all  'X'-characters  before the  call  (else errno=EINVAL  +  return -1),
 * with random characters  such that the  filename described by  `template_'
 * will not already exists. Then, create a new file with `O_RDWR' and return
 * the file descriptor of that file. */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,mkstemp,(char *__template_),(__template_))
#elif defined(__CRT_HAVE_mkstemp64)
/* >> mkstemp(3), mkstemp64(3)
 * Replace the last 6 characters of  `template_', which must be filled  with
 * all  'X'-characters  before the  call  (else errno=EINVAL  +  return -1),
 * with random characters  such that the  filename described by  `template_'
 * will not already exists. Then, create a new file with `O_RDWR' and return
 * the file descriptor of that file. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,mkstemp,(char *__template_),mkstemp64,(__template_))
#else /* ... */
#include <asm/os/fcntl.h>
#if (defined(__CRT_HAVE_mkstemps) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)) || defined(__CRT_HAVE_mkstemps64) || (defined(__CRT_HAVE_mkostemps) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)) || defined(__CRT_HAVE_mkostemps64) || defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))
#include <libc/local/stdlib/mkstemp.h>
/* >> mkstemp(3), mkstemp64(3)
 * Replace the last 6 characters of  `template_', which must be filled  with
 * all  'X'-characters  before the  call  (else errno=EINVAL  +  return -1),
 * with random characters  such that the  filename described by  `template_'
 * will not already exists. Then, create a new file with `O_RDWR' and return
 * the file descriptor of that file. */
__NAMESPACE_LOCAL_USING_OR_IMPL(mkstemp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __fd_t __NOTHROW_RPC(__LIBCCALL mkstemp)(char *__template_) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mkstemp))(__template_); })
#endif /* (__CRT_HAVE_mkstemps && (!__USE_FILE_OFFSET64 || !__O_LARGEFILE || !__O_LARGEFILE)) || __CRT_HAVE_mkstemps64 || (__CRT_HAVE_mkostemps && (!__USE_FILE_OFFSET64 || !__O_LARGEFILE || !__O_LARGEFILE)) || __CRT_HAVE_mkostemps64 || __CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat)) */
#endif /* !... */
#ifdef __USE_LARGEFILE64
#if defined(__CRT_HAVE_mkstemp) && (!defined(__O_LARGEFILE) || !__O_LARGEFILE)
/* >> mkstemp(3), mkstemp64(3)
 * Replace the last 6 characters of  `template_', which must be filled  with
 * all  'X'-characters  before the  call  (else errno=EINVAL  +  return -1),
 * with random characters  such that the  filename described by  `template_'
 * will not already exists. Then, create a new file with `O_RDWR' and return
 * the file descriptor of that file. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,mkstemp64,(char *__template_),mkstemp,(__template_))
#elif defined(__CRT_HAVE_mkstemp64)
/* >> mkstemp(3), mkstemp64(3)
 * Replace the last 6 characters of  `template_', which must be filled  with
 * all  'X'-characters  before the  call  (else errno=EINVAL  +  return -1),
 * with random characters  such that the  filename described by  `template_'
 * will not already exists. Then, create a new file with `O_RDWR' and return
 * the file descriptor of that file. */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,mkstemp64,(char *__template_),(__template_))
#else /* ... */
#include <asm/os/fcntl.h>
#if (defined(__CRT_HAVE_mkstemps) && (!defined(__O_LARGEFILE) || !__O_LARGEFILE)) || defined(__CRT_HAVE_mkstemps64) || (defined(__CRT_HAVE_mkostemps) && (!defined(__O_LARGEFILE) || !__O_LARGEFILE)) || defined(__CRT_HAVE_mkostemps64) || defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))
#include <libc/local/stdlib/mkstemp64.h>
/* >> mkstemp(3), mkstemp64(3)
 * Replace the last 6 characters of  `template_', which must be filled  with
 * all  'X'-characters  before the  call  (else errno=EINVAL  +  return -1),
 * with random characters  such that the  filename described by  `template_'
 * will not already exists. Then, create a new file with `O_RDWR' and return
 * the file descriptor of that file. */
__NAMESPACE_LOCAL_USING_OR_IMPL(mkstemp64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __fd_t __NOTHROW_RPC(__LIBCCALL mkstemp64)(char *__template_) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mkstemp64))(__template_); })
#endif /* (__CRT_HAVE_mkstemps && (!__O_LARGEFILE || !__O_LARGEFILE)) || __CRT_HAVE_mkstemps64 || (__CRT_HAVE_mkostemps && (!__O_LARGEFILE || !__O_LARGEFILE)) || __CRT_HAVE_mkostemps64 || __CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat)) */
#endif /* !... */
#endif /* __USE_LARGEFILE64 */
#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K8 */

#ifdef __USE_XOPEN2K8
#ifdef __CRT_HAVE_mkdtemp
/* >> mkdtemp(3)
 * Replace the last 6 characters of `template_', which must be filled with
 * all  'X'-characters before  the call  (else errno=EINVAL  + return -1),
 * with random characters such that the pathname described by  `template_'
 * will not already exists. Then, create a new directory with `mode=0700',
 * and re-return `template_' to indicate success.
 * On error, `NULL' will be returned, and the contents of `template_' are undefined. */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_RPC,mkdtemp,(char *__template_),(__template_))
#else /* __CRT_HAVE_mkdtemp */
#include <asm/os/fcntl.h>
#if defined(__CRT_HAVE_mkdir) || defined(__CRT_HAVE___mkdir) || defined(__CRT_HAVE___libc_mkdir) || (defined(__CRT_DOS_PRIMARY) && defined(__CRT_HAVE__mkdir)) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_mkdirat) || defined(__CRT_HAVE_fmkdirat)))
#include <libc/local/stdlib/mkdtemp.h>
/* >> mkdtemp(3)
 * Replace the last 6 characters of `template_', which must be filled with
 * all  'X'-characters before  the call  (else errno=EINVAL  + return -1),
 * with random characters such that the pathname described by  `template_'
 * will not already exists. Then, create a new directory with `mode=0700',
 * and re-return `template_' to indicate success.
 * On error, `NULL' will be returned, and the contents of `template_' are undefined. */
__NAMESPACE_LOCAL_USING_OR_IMPL(mkdtemp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) char *__NOTHROW_RPC(__LIBCCALL mkdtemp)(char *__template_) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mkdtemp))(__template_); })
#endif /* __CRT_HAVE_mkdir || __CRT_HAVE___mkdir || __CRT_HAVE___libc_mkdir || (__CRT_DOS_PRIMARY && __CRT_HAVE__mkdir) || (__AT_FDCWD && (__CRT_HAVE_mkdirat || __CRT_HAVE_fmkdirat)) */
#endif /* !__CRT_HAVE_mkdtemp */
#endif /* __USE_XOPEN2K8 */

#ifdef __USE_XOPEN
#if !defined(__setkey_defined) && defined(__CRT_HAVE_setkey)
#define __setkey_defined
/* >> setkey(3), setkey_r(3) */
__CDECLARE_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,setkey,(char const *__key),(__key))
#endif /* !__setkey_defined && __CRT_HAVE_setkey */
__CDECLARE_OPT(,int,__NOTHROW_NCX,grantpt,(__fd_t __fd),(__fd))
#ifdef __CRT_HAVE_unlockpt
__CDECLARE(,int,__NOTHROW_NCX,unlockpt,(__fd_t __fd),(__fd))
#else /* __CRT_HAVE_unlockpt */
#include <asm/os/tty.h>
#if (defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)) && defined(__TIOCSPTLCK)
#include <libc/local/stdlib/unlockpt.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(unlockpt, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_NCX(__LIBCCALL unlockpt)(__fd_t __fd) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unlockpt))(__fd); })
#endif /* (__CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) && __TIOCSPTLCK */
#endif /* !__CRT_HAVE_unlockpt */
#ifdef __CRT_HAVE_ptsname
/* >> ptsname(3)
 * Returns the name of the PTY slave (Pseudo TTY slave)
 * associated   with   the   master   descriptor   `fd' */
__CDECLARE(__ATTR_WUNUSED,char *,__NOTHROW_NCX,ptsname,(__fd_t __fd),(__fd))
#elif defined(__CRT_HAVE_ptsname_r)
#include <libc/local/stdlib/ptsname.h>
/* >> ptsname(3)
 * Returns the name of the PTY slave (Pseudo TTY slave)
 * associated   with   the   master   descriptor   `fd' */
__NAMESPACE_LOCAL_USING_OR_IMPL(ptsname, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED char *__NOTHROW_NCX(__LIBCCALL ptsname)(__fd_t __fd) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ptsname))(__fd); })
#endif /* ... */
#endif /* __USE_XOPEN */

#ifdef __USE_XOPEN2KXSI
__CDECLARE_OPT(__ATTR_WUNUSED,__fd_t,__NOTHROW_RPC,posix_openpt,(__oflag_t __oflags),(__oflags))
#endif /* __USE_XOPEN2KXSI */
#if defined(__USE_GNU) || defined(__USE_NETBSD)
/* Returns the name of the PTY slave (Pseudo TTY slave)
 * associated   with   the   master   descriptor   `fd' */
__CDECLARE_OPT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,ptsname_r,(__fd_t __fd, char *__buf, __SIZE_TYPE__ __buflen),(__fd,__buf,__buflen))
#endif /* __USE_GNU || __USE_NETBSD */
#ifdef __USE_GNU
#ifdef __CRT_HAVE_strtol_l
__CDECLARE(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,strtol_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtol_l)
__CREDIRECT(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,strtol_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_strtol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___strtol_l)
__CREDIRECT(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,strtol_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__strtol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtoll_l) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,strtol_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoll_l) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,strtol_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_strtoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___strtoll_l) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,strtol_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__strtoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtoq_l) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,strtol_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtoq_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strto32_l) && __SIZEOF_LONG__ == 4
__CREDIRECT(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,strtol_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strto32_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strto64_l) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,strtol_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strto64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtoimax_l) && __SIZEOF_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,strtol_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoimax_l) && __SIZEOF_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,strtol_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_strtoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___strtoimax_l) && __SIZEOF_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,strtol_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__strtoimax_l,(__nptr,__endptr,__base,__locale))
#elif __SIZEOF_LONG__ == 4
#include <libc/local/stdlib/strto32_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) long __NOTHROW_NCX(__LIBCCALL strtol_l)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (long)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strto32_l))(__nptr, __endptr, __base, __locale); }
#elif __SIZEOF_LONG__ == 8
#include <libc/local/stdlib/strto64_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) long __NOTHROW_NCX(__LIBCCALL strtol_l)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (long)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strto64_l))(__nptr, __endptr, __base, __locale); }
#else /* ... */
#include <libc/local/stdlib/strtol_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strtol_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) long __NOTHROW_NCX(__LIBCCALL strtol_l)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtol_l))(__nptr, __endptr, __base, __locale); })
#endif /* !... */
#ifdef __CRT_HAVE_strtoul_l
__CDECLARE(__ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,strtoul_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoul_l)
__CREDIRECT(__ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,strtoul_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_strtoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___strtoul_l)
__CREDIRECT(__ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,strtoul_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__strtoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtoull_l) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,strtoul_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoull_l) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,strtoul_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_strtoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___strtoull_l) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,strtoul_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__strtoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtouq_l) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,strtoul_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtouq_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtou32_l) && __SIZEOF_LONG__ == 4
__CREDIRECT(__ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,strtoul_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtou32_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtou64_l) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,strtoul_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtou64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtoumax_l) && __SIZEOF_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,strtoul_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoumax_l) && __SIZEOF_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,strtoul_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_strtoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___strtoumax_l) && __SIZEOF_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,strtoul_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__strtoumax_l,(__nptr,__endptr,__base,__locale))
#elif __SIZEOF_LONG__ == 4
#include <libc/local/stdlib/strtou32_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) unsigned long __NOTHROW_NCX(__LIBCCALL strtoul_l)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (unsigned long)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtou32_l))(__nptr, __endptr, __base, __locale); }
#elif __SIZEOF_LONG__ == 8
#include <libc/local/stdlib/strtou64_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) unsigned long __NOTHROW_NCX(__LIBCCALL strtoul_l)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (unsigned long)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtou64_l))(__nptr, __endptr, __base, __locale); }
#else /* ... */
#include <libc/local/stdlib/strtoul_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strtoul_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) unsigned long __NOTHROW_NCX(__LIBCCALL strtoul_l)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtoul_l))(__nptr, __endptr, __base, __locale); })
#endif /* !... */
#ifdef __LONGLONG
#ifdef __CRT_HAVE_strtoll_l
__CDECLARE(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,strtoll_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoll_l)
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,strtoll_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_strtoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___strtoll_l)
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,strtoll_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__strtoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtol_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,strtoll_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtol_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,strtoll_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_strtol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___strtol_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,strtoll_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__strtol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strto64_l) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,strtoll_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strto64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strto32_l) && __SIZEOF_LONG_LONG__ == 4
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,strtoll_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strto32_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtoimax_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,strtoll_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoimax_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,strtoll_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_strtoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___strtoimax_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,strtoll_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__strtoimax_l,(__nptr,__endptr,__base,__locale))
#elif __SIZEOF_LONG_LONG__ == 4
#include <libc/local/stdlib/strto64_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __LONGLONG __NOTHROW_NCX(__LIBCCALL strtoll_l)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__LONGLONG)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strto64_l))(__nptr, __endptr, __base, __locale); }
#elif __SIZEOF_LONG_LONG__ == 8
#include <libc/local/stdlib/strto32_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __LONGLONG __NOTHROW_NCX(__LIBCCALL strtoll_l)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__LONGLONG)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strto32_l))(__nptr, __endptr, __base, __locale); }
#else /* ... */
#include <libc/local/stdlib/strtoll_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strtoll_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __LONGLONG __NOTHROW_NCX(__LIBCCALL strtoll_l)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtoll_l))(__nptr, __endptr, __base, __locale); })
#endif /* !... */
#ifdef __CRT_HAVE_strtoull_l
__CDECLARE(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,strtoull_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoull_l)
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,strtoull_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_strtoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___strtoull_l)
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,strtoull_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__strtoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtoul_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,strtoull_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoul_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,strtoull_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_strtoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___strtoul_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,strtoull_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__strtoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtou64_l) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,strtoull_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtou64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtou32_l) && __SIZEOF_LONG_LONG__ == 4
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,strtoull_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtou32_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtoumax_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,strtoull_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoumax_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,strtoull_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_strtoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___strtoumax_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,strtoull_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__strtoumax_l,(__nptr,__endptr,__base,__locale))
#elif __SIZEOF_LONG_LONG__ == 4
#include <libc/local/stdlib/strtou64_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __ULONGLONG __NOTHROW_NCX(__LIBCCALL strtoull_l)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__ULONGLONG)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtou64_l))(__nptr, __endptr, __base, __locale); }
#elif __SIZEOF_LONG_LONG__ == 8
#include <libc/local/stdlib/strtou32_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __ULONGLONG __NOTHROW_NCX(__LIBCCALL strtoull_l)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__ULONGLONG)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtou32_l))(__nptr, __endptr, __base, __locale); }
#else /* ... */
#include <libc/local/stdlib/strtoull_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strtoull_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __ULONGLONG __NOTHROW_NCX(__LIBCCALL strtoull_l)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtoull_l))(__nptr, __endptr, __base, __locale); })
#endif /* !... */
#endif /* __LONGLONG */
#ifndef __NO_FPU
#ifdef __CRT_HAVE_strtod_l
__CDECLARE(__ATTR_NONNULL((1)),double,__NOTHROW_NCX,strtod_l,(char const *__restrict __nptr, char **__endptr, __locale_t __locale),(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE__strtod_l)
__CREDIRECT(__ATTR_NONNULL((1)),double,__NOTHROW_NCX,strtod_l,(char const *__restrict __nptr, char **__endptr, __locale_t __locale),_strtod_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE___strtod_l)
__CREDIRECT(__ATTR_NONNULL((1)),double,__NOTHROW_NCX,strtod_l,(char const *__restrict __nptr, char **__endptr, __locale_t __locale),__strtod_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE_strtold_l) && __SIZEOF_LONG_DOUBLE__ == __SIZEOF_DOUBLE__
__CREDIRECT(__ATTR_NONNULL((1)),double,__NOTHROW_NCX,strtod_l,(char const *__restrict __nptr, char **__endptr, __locale_t __locale),strtold_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE__strtold_l) && __SIZEOF_LONG_DOUBLE__ == __SIZEOF_DOUBLE__
__CREDIRECT(__ATTR_NONNULL((1)),double,__NOTHROW_NCX,strtod_l,(char const *__restrict __nptr, char **__endptr, __locale_t __locale),_strtold_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE___strtold_l) && __SIZEOF_LONG_DOUBLE__ == __SIZEOF_DOUBLE__
__CREDIRECT(__ATTR_NONNULL((1)),double,__NOTHROW_NCX,strtod_l,(char const *__restrict __nptr, char **__endptr, __locale_t __locale),__strtold_l,(__nptr,__endptr,__locale))
#else /* ... */
#include <libc/local/stdlib/strtod_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strtod_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) double __NOTHROW_NCX(__LIBCCALL strtod_l)(char const *__restrict __nptr, char **__endptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtod_l))(__nptr, __endptr, __locale); })
#endif /* !... */
#ifdef __CRT_HAVE_strtof_l
__CDECLARE(__ATTR_NONNULL((1)),float,__NOTHROW_NCX,strtof_l,(char const *__restrict __nptr, char **__endptr, __locale_t __locale),(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE__strtof_l)
__CREDIRECT(__ATTR_NONNULL((1)),float,__NOTHROW_NCX,strtof_l,(char const *__restrict __nptr, char **__endptr, __locale_t __locale),_strtof_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE___strtof_l)
__CREDIRECT(__ATTR_NONNULL((1)),float,__NOTHROW_NCX,strtof_l,(char const *__restrict __nptr, char **__endptr, __locale_t __locale),__strtof_l,(__nptr,__endptr,__locale))
#else /* ... */
#include <libc/local/stdlib/strtof_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strtof_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) float __NOTHROW_NCX(__LIBCCALL strtof_l)(char const *__restrict __nptr, char **__endptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtof_l))(__nptr, __endptr, __locale); })
#endif /* !... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#ifdef __CRT_HAVE_strtold_l
__CDECLARE(__ATTR_NONNULL((1)),__LONGDOUBLE,__NOTHROW_NCX,strtold_l,(char const *__restrict __nptr, char **__endptr, __locale_t __locale),(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE__strtold_l)
__CREDIRECT(__ATTR_NONNULL((1)),__LONGDOUBLE,__NOTHROW_NCX,strtold_l,(char const *__restrict __nptr, char **__endptr, __locale_t __locale),_strtold_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE___strtold_l)
__CREDIRECT(__ATTR_NONNULL((1)),__LONGDOUBLE,__NOTHROW_NCX,strtold_l,(char const *__restrict __nptr, char **__endptr, __locale_t __locale),__strtold_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE_strtod_l) && __SIZEOF_LONG_DOUBLE__ == __SIZEOF_DOUBLE__
__CREDIRECT(__ATTR_NONNULL((1)),__LONGDOUBLE,__NOTHROW_NCX,strtold_l,(char const *__restrict __nptr, char **__endptr, __locale_t __locale),strtod_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE__strtod_l) && __SIZEOF_LONG_DOUBLE__ == __SIZEOF_DOUBLE__
__CREDIRECT(__ATTR_NONNULL((1)),__LONGDOUBLE,__NOTHROW_NCX,strtold_l,(char const *__restrict __nptr, char **__endptr, __locale_t __locale),_strtod_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE___strtod_l) && __SIZEOF_LONG_DOUBLE__ == __SIZEOF_DOUBLE__
__CREDIRECT(__ATTR_NONNULL((1)),__LONGDOUBLE,__NOTHROW_NCX,strtold_l,(char const *__restrict __nptr, char **__endptr, __locale_t __locale),__strtod_l,(__nptr,__endptr,__locale))
#else /* ... */
#include <libc/local/stdlib/strtold_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strtold_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __LONGDOUBLE __NOTHROW_NCX(__LIBCCALL strtold_l)(char const *__restrict __nptr, char **__endptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtold_l))(__nptr, __endptr, __locale); })
#endif /* !... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__NO_FPU */
#ifdef __CRT_HAVE_secure_getenv
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,secure_getenv,(char const *__varname),(__varname))
#elif defined(__CRT_HAVE___secure_getenv)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,secure_getenv,(char const *__varname),__secure_getenv,(__varname))
#elif defined(__CRT_HAVE___libc_secure_getenv)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,secure_getenv,(char const *__varname),__libc_secure_getenv,(__varname))
#elif defined(__CRT_HAVE_getenv)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,secure_getenv,(char const *__varname),getenv,(__varname))
#elif defined(__LOCAL_environ)
#include <libc/local/stdlib/getenv.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL secure_getenv)(char const *__varname) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getenv))(__varname); }
#endif /* ... */
__CDECLARE_OPT(,int,__NOTHROW_RPC,getpt,(void),())
/* Return the result of `realpath(filename)' as a `malloc()'-allocated buffer
 * Upon error, `NULL' is returned instead */
__CDECLARE_OPT(__ATTR_MALLOC __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_RPC,canonicalize_file_name,(char const *__filename),(__filename))
#endif /* __USE_GNU */

#if defined(__USE_KOS) || defined(__USE_MISC) || defined(__USE_BSD)
#ifndef __reallocarray_defined
#define __reallocarray_defined
#ifdef __CRT_HAVE_reallocarray
__CDECLARE(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) __ATTR_ALLOC_SIZE((2, 3)),void *,__NOTHROW_NCX,reallocarray,(void *__ptr, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),(__ptr,__elem_count,__elem_size))
#elif defined(__CRT_HAVE_reallocarr)
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) __ATTR_ALLOC_SIZE((2, 3)),void *,__NOTHROW_NCX,reallocarray,(void *__ptr, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),reallocarr,(__ptr,__elem_count,__elem_size))
#elif defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)
#include <libc/local/malloc/reallocarray.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(reallocarray, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) __ATTR_ALLOC_SIZE((2, 3)) void *__NOTHROW_NCX(__LIBCCALL reallocarray)(void *__ptr, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(reallocarray))(__ptr, __elem_count, __elem_size); })
#else /* ... */
#undef __reallocarray_defined
#endif /* !... */
#endif /* !__reallocarray_defined */
#endif /* __USE_KOS || __USE_MISC || __USE_BSD */

#ifdef __USE_KOS
#ifndef __recalloc_defined
#define __recalloc_defined
#ifdef __CRT_HAVE_recalloc
__CDECLARE(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,recalloc,(void *__mallptr, __SIZE_TYPE__ __num_bytes),(__mallptr,__num_bytes))
#elif (defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_malloc_usable_size) || defined(__CRT_HAVE__msize))
#include <libc/local/malloc/recalloc.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(recalloc, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) void *__NOTHROW_NCX(__LIBCCALL recalloc)(void *__mallptr, __SIZE_TYPE__ __num_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(recalloc))(__mallptr, __num_bytes); })
#else /* ... */
#undef __recalloc_defined
#endif /* !... */
#endif /* !__recalloc_defined */
#ifndef __reallocv_defined
#define __reallocv_defined
#ifdef __CRT_HAVE_reallocarray
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) __ATTR_ALLOC_SIZE((2, 3)),void *,__NOTHROW_NCX,reallocv,(void *__ptr, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),reallocarray,(__ptr,__elem_count,__elem_size))
#elif defined(__CRT_HAVE_reallocarr)
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) __ATTR_ALLOC_SIZE((2, 3)),void *,__NOTHROW_NCX,reallocv,(void *__ptr, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),reallocarr,(__ptr,__elem_count,__elem_size))
#elif defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)
#include <libc/local/malloc/reallocarray.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) __ATTR_ALLOC_SIZE((2, 3)) void *__NOTHROW_NCX(__LIBCCALL reallocv)(void *__ptr, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(reallocarray))(__ptr, __elem_count, __elem_size); }
#else /* ... */
#undef __reallocv_defined
#endif /* !... */
#endif /* !__reallocv_defined */
#ifndef __recallocv_defined
#define __recallocv_defined
#ifdef __CRT_HAVE_recallocv
__CDECLARE(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2, 3)),void *,__NOTHROW_NCX,recallocv,(void *__mallptr, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),(__mallptr,__elem_count,__elem_size))
#elif defined(__CRT_HAVE__recalloc)
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2, 3)),void *,__NOTHROW_NCX,recallocv,(void *__mallptr, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),_recalloc,(__mallptr,__elem_count,__elem_size))
#elif (defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_malloc_usable_size) || defined(__CRT_HAVE__msize))
#include <libc/local/malloc/recallocv.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(recallocv, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2, 3)) void *__NOTHROW_NCX(__LIBCCALL recallocv)(void *__mallptr, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(recallocv))(__mallptr, __elem_count, __elem_size); })
#else /* ... */
#undef __recallocv_defined
#endif /* !... */
#endif /* !__recallocv_defined */


#ifdef __USE_STRING_OVERLOADS
#ifndef __MALLOC_OVERLOADS_DEFINED
#define __MALLOC_OVERLOADS_DEFINED 1
#ifdef __malloc_defined
__NAMESPACE_LOCAL_BEGIN
__FORCELOCAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1, 2))
void *__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(mallocv))(__SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) {
	__SIZE_TYPE__ __total_size;
	if (__hybrid_overflow_umul(__elem_count, __elem_size, &__total_size))
		__total_size = (__SIZE_TYPE__)-1; /* Force down-stream failure */
	return (malloc)(__total_size);
}
__NAMESPACE_LOCAL_END
#endif /* __malloc_defined */
#ifdef __cplusplus
extern "C++" {
#ifdef __malloc_defined
__FORCELOCAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1, 2))
void *__NOTHROW_NCX(__LIBCCALL malloc)(__SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mallocv)(__elem_count, __elem_size); }
#endif /* __malloc_defined */
#ifdef __calloc_defined
__FORCELOCAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1))
void *__NOTHROW_NCX(__LIBCCALL calloc)(__SIZE_TYPE__ __num_bytes) { return (calloc)(1, __num_bytes); }
#endif /* __calloc_defined */
} /* extern "C++" */
extern "C++" {
#ifdef __CRT_HAVE_reallocarray
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) __ATTR_ALLOC_SIZE((2, 3)),void *,__NOTHROW_NCX,realloc,(void *__ptr, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),reallocarray,(__ptr,__elem_count,__elem_size))
#elif defined(__CRT_HAVE_reallocarr)
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) __ATTR_ALLOC_SIZE((2, 3)),void *,__NOTHROW_NCX,realloc,(void *__ptr, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),reallocarr,(__ptr,__elem_count,__elem_size))
#elif defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)
} /* extern "C++" */
#include <libc/local/malloc/reallocarray.h>
extern "C++" {
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) __ATTR_ALLOC_SIZE((2, 3)) void *__NOTHROW_NCX(__LIBCCALL realloc)(void *__ptr, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(reallocarray))(__ptr, __elem_count, __elem_size); }
#endif /* ... */
#ifdef __CRT_HAVE_recallocv
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2, 3)),void *,__NOTHROW_NCX,recalloc,(void *__mallptr, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),recallocv,(__mallptr,__elem_count,__elem_size))
#elif defined(__CRT_HAVE__recalloc)
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2, 3)),void *,__NOTHROW_NCX,recalloc,(void *__mallptr, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),_recalloc,(__mallptr,__elem_count,__elem_size))
#elif (defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_malloc_usable_size) || defined(__CRT_HAVE__msize))
} /* extern "C++" */
#include <libc/local/malloc/recallocv.h>
extern "C++" {
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2, 3)) void *__NOTHROW_NCX(__LIBCCALL recalloc)(void *__mallptr, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(recallocv))(__mallptr, __elem_count, __elem_size); }
#endif /* ... */
} /* extern "C++" */
#elif defined(__HYBRID_PP_VA_OVERLOAD)
#ifdef __malloc_defined
#define __PRIVATE_malloc_1 (malloc)
#define __PRIVATE_malloc_2 __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mallocv)
#undef malloc
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define malloc(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_malloc_, (__VA_ARGS__))(__VA_ARGS__)
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#define malloc(args...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_malloc_, (args))(args)
#endif /* ... */
#endif /* __malloc_defined */
#ifdef __calloc_defined
#define __PRIVATE_calloc_1(num_bytes) (calloc)(1, num_bytes)
#define __PRIVATE_calloc_2            (calloc)
#undef calloc
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define calloc(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_calloc_, (__VA_ARGS__))(__VA_ARGS__)
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#define calloc(args...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_calloc_, (args))(args)
#endif /* ... */
#endif /* __calloc_defined */
#if defined(__realloc_defined) && defined(__reallocarray_defined)
#define __PRIVATE_realloc_2 (realloc)
#define __PRIVATE_realloc_3 (reallocarray)
#undef realloc
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define realloc(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_realloc_, (__VA_ARGS__))(__VA_ARGS__)
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#define realloc(args...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_realloc_, (args))(args)
#endif /* ... */
#endif /* __realloc_defined && __reallocarray_defined */
#if defined(__recalloc_defined) && defined(__recallocv_defined)
#define __PRIVATE_recalloc_2 (recalloc)
#define __PRIVATE_recalloc_3 (recallocv)
#undef recalloc
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define recalloc(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_recalloc_, (__VA_ARGS__))(__VA_ARGS__)
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#define recalloc(args...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_recalloc_, (args))(args)
#endif /* ... */
#endif /* __recalloc_defined && __recallocv_defined */
#endif /* ... */
#endif /* !__MALLOC_OVERLOADS_DEFINED */
#endif /* __USE_STRING_OVERLOADS */
#ifndef __shexec_defined
#define __shexec_defined
#ifdef __CRT_HAVE_shexec
/* >> shexec(3)
 * Execute command with the system interpreter (such as: `/bin/sh -c $command')
 * This  function is used  to implement `system(3)' and  `popen(3)', and may be
 * used to invoke the system interpreter.
 * This function only returns on failure (similar to exec(2)), and will never
 * return on success (since in that case, the calling program will have  been
 * replaced by the system shell)
 * The shell paths attempted by this function are system-dependent, but before any
 * of them are tested, this function will try to use `secure_getenv("SHELL")',  if
 * and only if that variable is defined and starts with a '/'-character. */
__CDECLARE(,int,__NOTHROW_RPC,shexec,(char const *__command),(__command))
#elif defined(__CRT_HAVE_execl) || defined(__CRT_HAVE__execl) || defined(__CRT_HAVE_execv) || defined(__CRT_HAVE__execv) || ((defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve) || defined(__CRT_HAVE___execve) || defined(__CRT_HAVE___libc_execve)) && defined(__LOCAL_environ))
#include <libc/local/stdlib/shexec.h>
/* >> shexec(3)
 * Execute command with the system interpreter (such as: `/bin/sh -c $command')
 * This  function is used  to implement `system(3)' and  `popen(3)', and may be
 * used to invoke the system interpreter.
 * This function only returns on failure (similar to exec(2)), and will never
 * return on success (since in that case, the calling program will have  been
 * replaced by the system shell)
 * The shell paths attempted by this function are system-dependent, but before any
 * of them are tested, this function will try to use `secure_getenv("SHELL")',  if
 * and only if that variable is defined and starts with a '/'-character. */
__NAMESPACE_LOCAL_USING_OR_IMPL(shexec, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_RPC(__LIBCCALL shexec)(char const *__command) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(shexec))(__command); })
#else /* ... */
#undef __shexec_defined
#endif /* !... */
#endif /* !__shexec_defined */
#endif /* __USE_KOS */

#ifdef __USE_SOLARIS
#ifndef __uid_t_defined
#define __uid_t_defined
typedef __uid_t uid_t; /* User ID */
#endif /* !__uid_t_defined */
#ifndef __closefrom_defined
#define __closefrom_defined
#ifdef __CRT_HAVE_closefrom
/* >> closefrom(2)
 * Close all file descriptors with indices `>= lowfd' (s.a. `fcntl(F_CLOSEM)') */
__CDECLARE_VOID(,__NOTHROW_NCX,closefrom,(__fd_t __lowfd),(__lowfd))
#else /* __CRT_HAVE_closefrom */
#include <asm/os/fcntl.h>
#if ((defined(__CRT_HAVE_fcntl) || defined(__CRT_HAVE___fcntl) || defined(__CRT_HAVE___libc_fcntl)) && defined(__F_CLOSEM)) || defined(__CRT_HAVE_close_range)
#include <libc/local/unistd/closefrom.h>
/* >> closefrom(2)
 * Close all file descriptors with indices `>= lowfd' (s.a. `fcntl(F_CLOSEM)') */
__NAMESPACE_LOCAL_USING_OR_IMPL(closefrom, __FORCELOCAL __ATTR_ARTIFICIAL void __NOTHROW_NCX(__LIBCCALL closefrom)(__fd_t __lowfd) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(closefrom))(__lowfd); })
#else /* ((__CRT_HAVE_fcntl || __CRT_HAVE___fcntl || __CRT_HAVE___libc_fcntl) && __F_CLOSEM) || __CRT_HAVE_close_range */
#undef __closefrom_defined
#endif /* ((!__CRT_HAVE_fcntl && !__CRT_HAVE___fcntl && !__CRT_HAVE___libc_fcntl) || !__F_CLOSEM) && !__CRT_HAVE_close_range */
#endif /* !__CRT_HAVE_closefrom */
#endif /* !__closefrom_defined */
#ifndef __dup2_defined
#define __dup2_defined
#ifdef __CRT_HAVE_dup2
/* >> dup2(2)
 * @return: newfd: Returns the new handle upon success.
 * Duplicate a file referred to by `oldfd' into `newfd' */
__CDECLARE(,__fd_t,__NOTHROW_NCX,dup2,(__fd_t __oldfd, __fd_t __newfd),(__oldfd,__newfd))
#elif defined(__CRT_HAVE__dup2)
/* >> dup2(2)
 * @return: newfd: Returns the new handle upon success.
 * Duplicate a file referred to by `oldfd' into `newfd' */
__CREDIRECT(,__fd_t,__NOTHROW_NCX,dup2,(__fd_t __oldfd, __fd_t __newfd),_dup2,(__oldfd,__newfd))
#elif defined(__CRT_HAVE___dup2)
/* >> dup2(2)
 * @return: newfd: Returns the new handle upon success.
 * Duplicate a file referred to by `oldfd' into `newfd' */
__CREDIRECT(,__fd_t,__NOTHROW_NCX,dup2,(__fd_t __oldfd, __fd_t __newfd),__dup2,(__oldfd,__newfd))
#elif defined(__CRT_HAVE___libc_dup2)
/* >> dup2(2)
 * @return: newfd: Returns the new handle upon success.
 * Duplicate a file referred to by `oldfd' into `newfd' */
__CREDIRECT(,__fd_t,__NOTHROW_NCX,dup2,(__fd_t __oldfd, __fd_t __newfd),__libc_dup2,(__oldfd,__newfd))
#else /* ... */
#undef __dup2_defined
#endif /* !... */
#endif /* !__dup2_defined */
#ifndef __getcwd_defined
#define __getcwd_defined
#ifdef __CRT_HAVE_getcwd
/* >> getcwd(2)
 * Return the path of the current working directory, relative to the filesystem root set by `chdir(2)' */
__CDECLARE(,char *,__NOTHROW_RPC,getcwd,(char *__buf, size_t __bufsize),(__buf,__bufsize))
#elif defined(__CRT_HAVE__getcwd)
/* >> getcwd(2)
 * Return the path of the current working directory, relative to the filesystem root set by `chdir(2)' */
__CREDIRECT(,char *,__NOTHROW_RPC,getcwd,(char *__buf, size_t __bufsize),_getcwd,(__buf,__bufsize))
#else /* ... */
#undef __getcwd_defined
#endif /* !... */
#endif /* !__getcwd_defined */
#ifndef __getlogin_defined
#define __getlogin_defined
#ifdef __CRT_HAVE_getlogin
/* >> getlogin(3)
 * Return the login name for the current user, or `NULL' on error.
 * s.a. `getlogin_r()' and `cuserid()' */
__CDECLARE(__ATTR_WUNUSED,char *,__NOTHROW_NCX,getlogin,(void),())
#elif defined(__CRT_HAVE_cuserid) || defined(__CRT_HAVE_getlogin_r) || defined(__CRT_HAVE_getenv) || defined(__LOCAL_environ) || (defined(__CRT_HAVE_getpwuid_r) && (defined(__CRT_HAVE_geteuid) || defined(__CRT_HAVE___geteuid) || defined(__CRT_HAVE___libc_geteuid)))
#include <libc/local/unistd/getlogin.h>
/* >> getlogin(3)
 * Return the login name for the current user, or `NULL' on error.
 * s.a. `getlogin_r()' and `cuserid()' */
__NAMESPACE_LOCAL_USING_OR_IMPL(getlogin, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED char *__NOTHROW_NCX(__LIBCCALL getlogin)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getlogin))(); })
#else /* ... */
#undef __getlogin_defined
#endif /* !... */
#endif /* !__getlogin_defined */
#ifndef __getpass_defined
#define __getpass_defined
#ifdef __CRT_HAVE_getpass
/* >> getpass(3), getpassphrase(3) */
__CDECLARE(__ATTR_WUNUSED,char *,__NOTHROW_RPC,getpass,(char const *__restrict __prompt),(__prompt))
#elif defined(__CRT_HAVE_getpassphrase)
/* >> getpass(3), getpassphrase(3) */
__CREDIRECT(__ATTR_WUNUSED,char *,__NOTHROW_RPC,getpass,(char const *__restrict __prompt),getpassphrase,(__prompt))
#else /* ... */
#include <asm/os/stdio.h>
#if defined(__CRT_HAVE_getpass_r) || defined(__CRT_HAVE_getpassfd) || defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read) || defined(__CRT_HAVE___libc_read) || defined(__CRT_HAVE_readpassphrase)
#include <libc/local/unistd/getpass.h>
/* >> getpass(3), getpassphrase(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(getpass, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED char *__NOTHROW_RPC(__LIBCCALL getpass)(char const *__restrict __prompt) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getpass))(__prompt); })
#else /* __CRT_HAVE_getpass_r || __CRT_HAVE_getpassfd || __CRT_HAVE_read || __CRT_HAVE__read || __CRT_HAVE___read || __CRT_HAVE___libc_read || __CRT_HAVE_readpassphrase */
#undef __getpass_defined
#endif /* !__CRT_HAVE_getpass_r && !__CRT_HAVE_getpassfd && !__CRT_HAVE_read && !__CRT_HAVE__read && !__CRT_HAVE___read && !__CRT_HAVE___libc_read && !__CRT_HAVE_readpassphrase */
#endif /* !... */
#endif /* !__getpass_defined */
#ifndef __getpw_defined
#define __getpw_defined
#ifdef __CRT_HAVE_getpw
/* >> getpw(3)
 * Re-construct the password-file line for the given uid in the
 * given  buffer. This  knows the  format that  the caller will
 * expect, but this need not be the format of the password file */
__CDECLARE(,int,__NOTHROW_RPC,getpw,(__uid_t __uid, char *__buffer),(__uid,__buffer))
#elif defined(__CRT_HAVE_getpwuid)
#include <libc/local/pwd/getpw.h>
/* >> getpw(3)
 * Re-construct the password-file line for the given uid in the
 * given  buffer. This  knows the  format that  the caller will
 * expect, but this need not be the format of the password file */
__NAMESPACE_LOCAL_USING_OR_IMPL(getpw, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_RPC(__LIBCCALL getpw)(__uid_t __uid, char *__buffer) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getpw))(__uid, __buffer); })
#else /* ... */
#undef __getpw_defined
#endif /* !... */
#endif /* !__getpw_defined */
#ifndef __isatty_defined
#define __isatty_defined
#ifdef __CRT_HAVE_isatty
/* >> isatty(2)
 * Check if the given file handle `fd' refers to a TTY
 * @return: 1: Is a tty
 * @return: 0: Not a tty (`errno' was modified, and is usually set to `ENOTTY') */
__CDECLARE(__ATTR_WUNUSED,int,__NOTHROW_NCX,isatty,(__fd_t __fd),(__fd))
#elif defined(__CRT_HAVE__isatty)
/* >> isatty(2)
 * Check if the given file handle `fd' refers to a TTY
 * @return: 1: Is a tty
 * @return: 0: Not a tty (`errno' was modified, and is usually set to `ENOTTY') */
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW_NCX,isatty,(__fd_t __fd),_isatty,(__fd))
#elif defined(__CRT_HAVE___isatty)
/* >> isatty(2)
 * Check if the given file handle `fd' refers to a TTY
 * @return: 1: Is a tty
 * @return: 0: Not a tty (`errno' was modified, and is usually set to `ENOTTY') */
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW_NCX,isatty,(__fd_t __fd),__isatty,(__fd))
#else /* ... */
#include <asm/os/tty.h>
#if defined(__CRT_HAVE_tcgetattr) || defined(__CRT_HAVE___tcgetattr) || ((defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)) && defined(__TCGETA))
#include <libc/local/unistd/isatty.h>
/* >> isatty(2)
 * Check if the given file handle `fd' refers to a TTY
 * @return: 1: Is a tty
 * @return: 0: Not a tty (`errno' was modified, and is usually set to `ENOTTY') */
__NAMESPACE_LOCAL_USING_OR_IMPL(isatty, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL isatty)(__fd_t __fd) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isatty))(__fd); })
#else /* __CRT_HAVE_tcgetattr || __CRT_HAVE___tcgetattr || ((__CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) && __TCGETA) */
#undef __isatty_defined
#endif /* !__CRT_HAVE_tcgetattr && !__CRT_HAVE___tcgetattr && ((!__CRT_HAVE_ioctl && !__CRT_HAVE___ioctl && !__CRT_HAVE___libc_ioctl) || !__TCGETA) */
#endif /* !... */
#endif /* !__isatty_defined */
#ifndef __memalign_defined
#define __memalign_defined
#if __has_builtin(__builtin_aligned_alloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_aligned_alloc)
__CEIREDIRECT(__ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_ALIGN(1) __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,memalign,(size_t __alignment, size_t __n_bytes),aligned_alloc,{ return __builtin_aligned_alloc(__alignment, __n_bytes); })
#elif defined(__CRT_HAVE_memalign)
__CDECLARE(__ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_ALIGN(1) __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,memalign,(size_t __alignment, size_t __n_bytes),(__alignment,__n_bytes))
#elif defined(__CRT_HAVE_aligned_alloc)
__CREDIRECT(__ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_ALIGN(1) __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,memalign,(size_t __alignment, size_t __n_bytes),aligned_alloc,(__alignment,__n_bytes))
#elif defined(__CRT_HAVE___libc_memalign)
__CREDIRECT(__ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_ALIGN(1) __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,memalign,(size_t __alignment, size_t __n_bytes),__libc_memalign,(__alignment,__n_bytes))
#elif defined(__CRT_HAVE_posix_memalign)
#include <libc/local/malloc/memalign.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(memalign, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_ALIGN(1) __ATTR_ALLOC_SIZE((2)) void *__NOTHROW_NCX(__LIBCCALL memalign)(size_t __alignment, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memalign))(__alignment, __n_bytes); })
#else /* ... */
#undef __memalign_defined
#endif /* !... */
#endif /* !__memalign_defined */
#ifndef __ttyname_defined
#define __ttyname_defined
#ifdef __CRT_HAVE_ttyname
/* >> ttyname(3)
 * Return the name of a TTY given its file descriptor */
__CDECLARE(__ATTR_WUNUSED,char *,__NOTHROW_RPC,ttyname,(__fd_t __fd),(__fd))
#elif defined(__CRT_HAVE___ttyname)
/* >> ttyname(3)
 * Return the name of a TTY given its file descriptor */
__CREDIRECT(__ATTR_WUNUSED,char *,__NOTHROW_RPC,ttyname,(__fd_t __fd),__ttyname,(__fd))
#elif defined(__CRT_HAVE_ttyname_r)
#include <libc/local/unistd/ttyname.h>
/* >> ttyname(3)
 * Return the name of a TTY given its file descriptor */
__NAMESPACE_LOCAL_USING_OR_IMPL(ttyname, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED char *__NOTHROW_RPC(__LIBCCALL ttyname)(__fd_t __fd) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ttyname))(__fd); })
#else /* ... */
#undef __ttyname_defined
#endif /* !... */
#endif /* !__ttyname_defined */
#ifdef __CRT_HAVE_getexecname
/* Returns the absolute filename of the main executable (s.a. `program_invocation_name') */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,char const *,__NOTHROW_NCX,getexecname,(void),())
#else /* __CRT_HAVE_getexecname */
#include <libc/template/program_invocation_name.h>
#ifdef __LOCAL_program_invocation_name
#include <libc/local/stdlib/getexecname.h>
/* Returns the absolute filename of the main executable (s.a. `program_invocation_name') */
__NAMESPACE_LOCAL_USING_OR_IMPL(getexecname, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED char const *__NOTHROW_NCX(__LIBCCALL getexecname)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getexecname))(); })
#endif /* __LOCAL_program_invocation_name */
#endif /* !__CRT_HAVE_getexecname */
#ifdef __CRT_HAVE_fdwalk
/* Enumerate all open file descriptors by  invoking `(*walk)(arg, <fd>)' for each of  them
 * If during any of these invocations, `(*walk)(...)' returns non-zero, enumeration stops,
 * and  `fdwalk()' returns with that same value. If `(*walk)(...)' is never called, or all
 * invocations return 0, `fdwalk()' will also return 0. */
__CDECLARE(__ATTR_NONNULL((1)),int,__THROWING,fdwalk,(int (__LIBCCALL *__walk)(void *__arg, __fd_t __fd), void *__arg),(__walk,__arg))
#else /* __CRT_HAVE_fdwalk */
#include <asm/os/fcntl.h>
#if (defined(__CRT_HAVE_fcntl) || defined(__CRT_HAVE___fcntl) || defined(__CRT_HAVE___libc_fcntl)) && defined(__F_NEXT)
#include <libc/local/stdlib/fdwalk.h>
/* Enumerate all open file descriptors by  invoking `(*walk)(arg, <fd>)' for each of  them
 * If during any of these invocations, `(*walk)(...)' returns non-zero, enumeration stops,
 * and  `fdwalk()' returns with that same value. If `(*walk)(...)' is never called, or all
 * invocations return 0, `fdwalk()' will also return 0. */
__NAMESPACE_LOCAL_USING_OR_IMPL(fdwalk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int (__LIBCCALL fdwalk)(int (__LIBCCALL *__walk)(void *__arg, __fd_t __fd), void *__arg) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fdwalk))(__walk, __arg); })
#endif /* (__CRT_HAVE_fcntl || __CRT_HAVE___fcntl || __CRT_HAVE___libc_fcntl) && __F_NEXT */
#endif /* !__CRT_HAVE_fdwalk */
#ifdef __CRT_HAVE_getpass
/* >> getpass(3), getpassphrase(3) */
__CREDIRECT(__ATTR_WUNUSED,char *,__NOTHROW_RPC,getpassphrase,(char const *__restrict __prompt),getpass,(__prompt))
#elif defined(__CRT_HAVE_getpassphrase)
/* >> getpass(3), getpassphrase(3) */
__CDECLARE(__ATTR_WUNUSED,char *,__NOTHROW_RPC,getpassphrase,(char const *__restrict __prompt),(__prompt))
#else /* ... */
#include <asm/os/stdio.h>
#if defined(__CRT_HAVE_getpass_r) || defined(__CRT_HAVE_getpassfd) || defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read) || defined(__CRT_HAVE___libc_read) || defined(__CRT_HAVE_readpassphrase)
#include <libc/local/unistd/getpass.h>
/* >> getpass(3), getpassphrase(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED char *__NOTHROW_RPC(__LIBCCALL getpassphrase)(char const *__restrict __prompt) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getpass))(__prompt); }
#endif /* __CRT_HAVE_getpass_r || __CRT_HAVE_getpassfd || __CRT_HAVE_read || __CRT_HAVE__read || __CRT_HAVE___read || __CRT_HAVE___libc_read || __CRT_HAVE_readpassphrase */
#endif /* !... */
#ifdef __LONGLONG
#ifdef __CRT_HAVE_lltostr
__CDECLARE(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((2)),char *,__NOTHROW_NCX,lltostr,(__LONGLONG ___value, char *__buf),(___value,__buf))
#else /* __CRT_HAVE_lltostr */
#include <libc/local/stdlib/lltostr.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(lltostr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((2)) char *__NOTHROW_NCX(__LIBCCALL lltostr)(__LONGLONG ___value, char *__buf) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lltostr))(___value, __buf); })
#endif /* !__CRT_HAVE_lltostr */
#ifdef __CRT_HAVE_ulltostr
__CDECLARE(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((2)),char *,__NOTHROW_NCX,ulltostr,(__ULONGLONG ___value, char *__buf),(___value,__buf))
#else /* __CRT_HAVE_ulltostr */
#include <libc/local/stdlib/ulltostr.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(ulltostr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((2)) char *__NOTHROW_NCX(__LIBCCALL ulltostr)(__ULONGLONG ___value, char *__buf) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ulltostr))(___value, __buf); })
#endif /* !__CRT_HAVE_ulltostr */
#endif /* __LONGLONG */
#endif /* __USE_SOLARIS */

#ifdef __USE_BSD
#ifndef __reallocf_defined
#define __reallocf_defined
#ifdef __CRT_HAVE_reallocf
__CDECLARE(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,reallocf,(void *__mallptr, __SIZE_TYPE__ __num_bytes),(__mallptr,__num_bytes))
#elif defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)
#include <libc/local/stdlib/reallocf.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(reallocf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) void *__NOTHROW_NCX(__LIBCCALL reallocf)(void *__mallptr, __SIZE_TYPE__ __num_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(reallocf))(__mallptr, __num_bytes); })
#else /* ... */
#undef __reallocf_defined
#endif /* !... */
#endif /* !__reallocf_defined */
#ifndef __recallocarray_defined
#define __recallocarray_defined
#ifdef __CRT_HAVE_recallocarray
/* >> recallocarray(3)
 * Same   as    `recallocv(mallptr, new_elem_count, elem_size)',   but    also   ensure    that
 * when `mallptr != NULL', memory pointed to by the old  `mallptr...+=old_elem_count*elem_size'
 * is explicitly freed to zero (s.a. `freezero()') when reallocation must move the memory block */
__CDECLARE(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((3, 4)),void *,__NOTHROW_NCX,recallocarray,(void *__mallptr, __SIZE_TYPE__ __old_elem_count, __SIZE_TYPE__ __new_elem_count, __SIZE_TYPE__ __elem_size),(__mallptr,__old_elem_count,__new_elem_count,__elem_size))
#elif (defined(__CRT_HAVE_recallocv) || defined(__CRT_HAVE__recalloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && (defined(__CRT_HAVE_malloc_usable_size) || defined(__CRT_HAVE__msize))
#include <libc/local/stdlib/recallocarray.h>
/* >> recallocarray(3)
 * Same   as    `recallocv(mallptr, new_elem_count, elem_size)',   but    also   ensure    that
 * when `mallptr != NULL', memory pointed to by the old  `mallptr...+=old_elem_count*elem_size'
 * is explicitly freed to zero (s.a. `freezero()') when reallocation must move the memory block */
__NAMESPACE_LOCAL_USING_OR_IMPL(recallocarray, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((3, 4)) void *__NOTHROW_NCX(__LIBCCALL recallocarray)(void *__mallptr, __SIZE_TYPE__ __old_elem_count, __SIZE_TYPE__ __new_elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(recallocarray))(__mallptr, __old_elem_count, __new_elem_count, __elem_size); })
#else /* ... */
#undef __recallocarray_defined
#endif /* !... */
#endif /* !__recallocarray_defined */
#ifndef __freezero_defined
#define __freezero_defined
#ifdef __CRT_HAVE_freezero
/* >> freezero(3)
 * Same as  `free(mallptr)', but  also ensure  that the  memory  region
 * described by `mallptr...+=num_bytes' is explicitly freed to zero, or
 * immediately returned  to the  OS, rather  than being  left in  cache
 * while still containing its previous contents. */
__CDECLARE_VOID(,__NOTHROW_NCX,freezero,(void *__mallptr, __SIZE_TYPE__ __num_bytes),(__mallptr,__num_bytes))
#elif defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
#include <libc/local/stdlib/freezero.h>
/* >> freezero(3)
 * Same as  `free(mallptr)', but  also ensure  that the  memory  region
 * described by `mallptr...+=num_bytes' is explicitly freed to zero, or
 * immediately returned  to the  OS, rather  than being  left in  cache
 * while still containing its previous contents. */
__NAMESPACE_LOCAL_USING_OR_IMPL(freezero, __FORCELOCAL __ATTR_ARTIFICIAL void __NOTHROW_NCX(__LIBCCALL freezero)(void *__mallptr, __SIZE_TYPE__ __num_bytes) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(freezero))(__mallptr, __num_bytes); })
#else /* ... */
#undef __freezero_defined
#endif /* !... */
#endif /* !__freezero_defined */
#if !defined(__getbsize_defined) && defined(__CRT_HAVE_getbsize)
#define __getbsize_defined
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,getbsize,(int *__headerlenp, __LONGPTR_TYPE__ *__blocksizep),(__headerlenp,__blocksizep))
#endif /* !__getbsize_defined && __CRT_HAVE_getbsize */
#if !defined(__daemon_defined) && defined(__CRT_HAVE_daemon)
#define __daemon_defined
/* >> daemon(3) */
__CDECLARE(,int,__NOTHROW_RPC,daemon,(__STDC_INT_AS_UINT_T __nochdir, __STDC_INT_AS_UINT_T __noclose),(__nochdir,__noclose))
#endif /* !__daemon_defined && __CRT_HAVE_daemon */
#ifdef __CRT_HAVE_l64a_r
/* >> l64a_r(3)
 * Reentrant variant of `l64a(3)'. Note that the max required buffer size
 * @param: buf:     Target buffer (with a size of `bufsize' bytes)
 * @param: bufsize: Buffer size (including a trailing NUL-character)
 * @return: 0 : Success
 * @return: -1: Buffer too small (`errno' was not modified) */
__CDECLARE(,int,__NOTHROW_NCX,l64a_r,(long __n, char *__buf, __STDC_INT_AS_SIZE_T __bufsize),(__n,__buf,__bufsize))
#else /* __CRT_HAVE_l64a_r */
#include <libc/local/stdlib/l64a_r.h>
/* >> l64a_r(3)
 * Reentrant variant of `l64a(3)'. Note that the max required buffer size
 * @param: buf:     Target buffer (with a size of `bufsize' bytes)
 * @param: bufsize: Buffer size (including a trailing NUL-character)
 * @return: 0 : Success
 * @return: -1: Buffer too small (`errno' was not modified) */
__NAMESPACE_LOCAL_USING_OR_IMPL(l64a_r, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_NCX(__LIBCCALL l64a_r)(long __n, char *__buf, __STDC_INT_AS_SIZE_T __bufsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(l64a_r))(__n, __buf, __bufsize); })
#endif /* !__CRT_HAVE_l64a_r */
#ifndef __getprogname_defined
#define __getprogname_defined
#ifdef __CRT_HAVE_getprogname
/* >> getprogname(3), setprogname(3) */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,char const *,__NOTHROW_NCX,getprogname,(void),())
#else /* __CRT_HAVE_getprogname */
#include <libc/template/program_invocation_name.h>
#ifdef __LOCAL_program_invocation_short_name
#include <libc/local/stdlib/getprogname.h>
/* >> getprogname(3), setprogname(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(getprogname, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED char const *__NOTHROW_NCX(__LIBCCALL getprogname)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getprogname))(); })
#else /* __LOCAL_program_invocation_short_name */
#undef __getprogname_defined
#endif /* !__LOCAL_program_invocation_short_name */
#endif /* !__CRT_HAVE_getprogname */
#endif /* !__getprogname_defined */
#ifndef __setprogname_defined
#define __setprogname_defined
#ifdef __CRT_HAVE_setprogname
/* >> getprogname(3), setprogname(3) */
__CDECLARE_VOID(,__NOTHROW_NCX,setprogname,(char const *__name),(__name))
#else /* __CRT_HAVE_setprogname */
#include <libc/template/program_invocation_name.h>
#ifdef __LOCAL_program_invocation_short_name_p
#include <libc/local/stdlib/setprogname.h>
/* >> getprogname(3), setprogname(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(setprogname, __FORCELOCAL __ATTR_ARTIFICIAL void __NOTHROW_NCX(__LIBCCALL setprogname)(char const *__name) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(setprogname))(__name); })
#else /* __LOCAL_program_invocation_short_name_p */
#undef __setprogname_defined
#endif /* !__LOCAL_program_invocation_short_name_p */
#endif /* !__CRT_HAVE_setprogname */
#endif /* !__setprogname_defined */
#ifndef __heapsort_defined
#define __heapsort_defined
#ifdef __CRT_HAVE_heapsort
__CDECLARE(__ATTR_NONNULL((1, 4)),int,__THROWING,heapsort,(void *__pbase, __SIZE_TYPE__ __item_count, __SIZE_TYPE__ __item_size, int (__LIBCCALL *__compar)(void const *__a, void const *__b)),(__pbase,__item_count,__item_size,__compar))
#else /* __CRT_HAVE_heapsort */
#include <libc/local/stdlib/heapsort.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(heapsort, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 4)) int (__LIBCCALL heapsort)(void *__pbase, __SIZE_TYPE__ __item_count, __SIZE_TYPE__ __item_size, int (__LIBCCALL *__compar)(void const *__a, void const *__b)) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(heapsort))(__pbase, __item_count, __item_size, __compar); })
#endif /* !__CRT_HAVE_heapsort */
#endif /* !__heapsort_defined */
#ifndef __mergesort_defined
#define __mergesort_defined
#ifdef __CRT_HAVE_mergesort
__CDECLARE(__ATTR_NONNULL((1, 4)),int,__THROWING,mergesort,(void *__pbase, __SIZE_TYPE__ __item_count, __SIZE_TYPE__ __item_size, int (__LIBCCALL *__compar)(void const *__a, void const *__b)),(__pbase,__item_count,__item_size,__compar))
#else /* __CRT_HAVE_mergesort */
#include <libc/local/stdlib/mergesort.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(mergesort, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 4)) int (__LIBCCALL mergesort)(void *__pbase, __SIZE_TYPE__ __item_count, __SIZE_TYPE__ __item_size, int (__LIBCCALL *__compar)(void const *__a, void const *__b)) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mergesort))(__pbase, __item_count, __item_size, __compar); })
#endif /* !__CRT_HAVE_mergesort */
#endif /* !__mergesort_defined */
#if !defined(__radixsort_defined) && defined(__CRT_HAVE_radixsort)
#define __radixsort_defined
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,radixsort,(unsigned char const **__base, int __item_count, unsigned char const *__table, unsigned __endbyte),(__base,__item_count,__table,__endbyte))
#endif /* !__radixsort_defined && __CRT_HAVE_radixsort */
#if !defined(__sradixsort_defined) && defined(__CRT_HAVE_sradixsort)
#define __sradixsort_defined
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,sradixsort,(unsigned char const **__base, int __item_count, unsigned char const *__table, unsigned __endbyte),(__base,__item_count,__table,__endbyte))
#endif /* !__sradixsort_defined && __CRT_HAVE_sradixsort */

#ifdef __LONGLONG
#ifndef __strtonum_defined
#define __strtonum_defined
#ifdef __CRT_HAVE_strtonum
/* >> strtonum(3)
 * Similar to `strtoi()'  with `base=10',  but return  human-
 * readable error messages in `*p_errstr' on error (alongside
 * `return==0') (or `NULL' on success).
 * The following messages are defined:
 *   - "too large": Numeric value is too great (`ERANGE' && greater than `hi')
 *   - "too small": Numeric value is too small (`ERANGE' && less than `lo')
 *   - "invalid":   Any other error (`ENOTSUP' or `ECANCELED')
 * @return: 0 : [*p_errstr != NULL] Error
 * @return: 0 : [*p_errstr == NULL] Success
 * @return: * : [*p_errstr == NULL] Success */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 4)),__LONGLONG,__NOTHROW_NCX,strtonum,(char const *__nptr, __LONGLONG __lo, __LONGLONG __hi, char const **__p_errstr),(__nptr,__lo,__hi,__p_errstr))
#else /* __CRT_HAVE_strtonum */
#include <libc/local/stdlib/strtonum.h>
/* >> strtonum(3)
 * Similar to `strtoi()'  with `base=10',  but return  human-
 * readable error messages in `*p_errstr' on error (alongside
 * `return==0') (or `NULL' on success).
 * The following messages are defined:
 *   - "too large": Numeric value is too great (`ERANGE' && greater than `hi')
 *   - "too small": Numeric value is too small (`ERANGE' && less than `lo')
 *   - "invalid":   Any other error (`ENOTSUP' or `ECANCELED')
 * @return: 0 : [*p_errstr != NULL] Error
 * @return: 0 : [*p_errstr == NULL] Success
 * @return: * : [*p_errstr == NULL] Success */
__NAMESPACE_LOCAL_USING_OR_IMPL(strtonum, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 4)) __LONGLONG __NOTHROW_NCX(__LIBCCALL strtonum)(char const *__nptr, __LONGLONG __lo, __LONGLONG __hi, char const **__p_errstr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtonum))(__nptr, __lo, __hi, __p_errstr); })
#endif /* !__CRT_HAVE_strtonum */
#endif /* !__strtonum_defined */
#endif /* __LONGLONG */
#endif /* __USE_BSD */

#if defined(__USE_GNU) || defined(__USE_BSD)
#ifndef __compar_d_fn_t_defined
#define __compar_d_fn_t_defined
typedef int (__LIBCCALL *__compar_d_fn_t)(void const *__a, void const *__b, void *__arg);
#endif /* !__compar_d_fn_t_defined */
#ifdef __CRT_HAVE_qsort_r
/* >> qsort_r(3) */
__CDECLARE_VOID(__ATTR_NONNULL((1, 4)),__THROWING,qsort_r,(void *__pbase, __SIZE_TYPE__ __item_count, __SIZE_TYPE__ __item_size, int (__LIBCCALL *__compar)(void const *__a, void const *__b, void *__arg), void *__arg),(__pbase,__item_count,__item_size,__compar,__arg))
#elif defined(__CRT_HAVE__quicksort)
/* >> qsort_r(3) */
__CREDIRECT_VOID(__ATTR_NONNULL((1, 4)),__THROWING,qsort_r,(void *__pbase, __SIZE_TYPE__ __item_count, __SIZE_TYPE__ __item_size, int (__LIBCCALL *__compar)(void const *__a, void const *__b, void *__arg), void *__arg),_quicksort,(__pbase,__item_count,__item_size,__compar,__arg))
#else /* ... */
#include <libc/local/stdlib/qsort_r.h>
/* >> qsort_r(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(qsort_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 4)) void (__LIBCCALL qsort_r)(void *__pbase, __SIZE_TYPE__ __item_count, __SIZE_TYPE__ __item_size, int (__LIBCCALL *__compar)(void const *__a, void const *__b, void *__arg), void *__arg) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(qsort_r))(__pbase, __item_count, __item_size, __compar, __arg); })
#endif /* !... */
#if defined(__CRT_HAVE_mkostemp) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
/* >> mkostemp(3), mkostemp64(3)
 * Replace  the  last 6  characters of  `template_' (which  are followed  by exactly
 * `suffixlen'  more  characters that  are left  alone), which  must be  filled with
 * all  'X'-characters  before  the  call  (else  errno=EINVAL  +  return  -1), with
 * random  characters  such  that the  filename  described by  `template_'  will not
 * already exists. Then, create a new file with `O_RDWR | flags' and return the file
 * descriptor of that file.
 * @param: flags: Additional  flags  to pass  to `open(2)',
 *                but `O_ACCMODE' is always set to `O_RDWR' */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_NCX,mkostemp,(char *__template_, __oflag_t __flags),(__template_,__flags))
#elif defined(__CRT_HAVE_mkostemp64)
/* >> mkostemp(3), mkostemp64(3)
 * Replace  the  last 6  characters of  `template_' (which  are followed  by exactly
 * `suffixlen'  more  characters that  are left  alone), which  must be  filled with
 * all  'X'-characters  before  the  call  (else  errno=EINVAL  +  return  -1), with
 * random  characters  such  that the  filename  described by  `template_'  will not
 * already exists. Then, create a new file with `O_RDWR | flags' and return the file
 * descriptor of that file.
 * @param: flags: Additional  flags  to pass  to `open(2)',
 *                but `O_ACCMODE' is always set to `O_RDWR' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_NCX,mkostemp,(char *__template_, __oflag_t __flags),mkostemp64,(__template_,__flags))
#else /* ... */
#include <asm/os/fcntl.h>
#if (defined(__CRT_HAVE_mkostemps) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)) || defined(__CRT_HAVE_mkostemps64) || defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))
#include <libc/local/stdlib/mkostemp.h>
/* >> mkostemp(3), mkostemp64(3)
 * Replace  the  last 6  characters of  `template_' (which  are followed  by exactly
 * `suffixlen'  more  characters that  are left  alone), which  must be  filled with
 * all  'X'-characters  before  the  call  (else  errno=EINVAL  +  return  -1), with
 * random  characters  such  that the  filename  described by  `template_'  will not
 * already exists. Then, create a new file with `O_RDWR | flags' and return the file
 * descriptor of that file.
 * @param: flags: Additional  flags  to pass  to `open(2)',
 *                but `O_ACCMODE' is always set to `O_RDWR' */
__NAMESPACE_LOCAL_USING_OR_IMPL(mkostemp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __fd_t __NOTHROW_NCX(__LIBCCALL mkostemp)(char *__template_, __oflag_t __flags) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mkostemp))(__template_, __flags); })
#endif /* (__CRT_HAVE_mkostemps && (!__USE_FILE_OFFSET64 || !__O_LARGEFILE || !__O_LARGEFILE)) || __CRT_HAVE_mkostemps64 || __CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat)) */
#endif /* !... */
#if defined(__CRT_HAVE_mkostemps) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_NCX,mkostemps,(char *__template_, __STDC_INT_AS_SIZE_T __suffixlen, __oflag_t __flags),(__template_,__suffixlen,__flags))
#elif defined(__CRT_HAVE_mkostemps64)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_NCX,mkostemps,(char *__template_, __STDC_INT_AS_SIZE_T __suffixlen, __oflag_t __flags),mkostemps64,(__template_,__suffixlen,__flags))
#else /* ... */
#include <asm/os/fcntl.h>
#if defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))
#include <libc/local/stdlib/mkostemps.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(mkostemps, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __fd_t __NOTHROW_NCX(__LIBCCALL mkostemps)(char *__template_, __STDC_INT_AS_SIZE_T __suffixlen, __oflag_t __flags) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mkostemps))(__template_, __suffixlen, __flags); })
#endif /* __CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat)) */
#endif /* !... */
#ifdef __USE_LARGEFILE64
#if defined(__CRT_HAVE_mkostemp) && (!defined(__O_LARGEFILE) || !__O_LARGEFILE)
/* >> mkostemp(3), mkostemp64(3)
 * Replace  the  last 6  characters of  `template_' (which  are followed  by exactly
 * `suffixlen'  more  characters that  are left  alone), which  must be  filled with
 * all  'X'-characters  before  the  call  (else  errno=EINVAL  +  return  -1), with
 * random  characters  such  that the  filename  described by  `template_'  will not
 * already exists. Then, create a new file with `O_RDWR | flags' and return the file
 * descriptor of that file.
 * @param: flags: Additional  flags  to pass  to `open(2)',
 *                but `O_ACCMODE' is always set to `O_RDWR' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_NCX,mkostemp64,(char *__template_, __oflag_t __flags),mkostemp,(__template_,__flags))
#elif defined(__CRT_HAVE_mkostemp64)
/* >> mkostemp(3), mkostemp64(3)
 * Replace  the  last 6  characters of  `template_' (which  are followed  by exactly
 * `suffixlen'  more  characters that  are left  alone), which  must be  filled with
 * all  'X'-characters  before  the  call  (else  errno=EINVAL  +  return  -1), with
 * random  characters  such  that the  filename  described by  `template_'  will not
 * already exists. Then, create a new file with `O_RDWR | flags' and return the file
 * descriptor of that file.
 * @param: flags: Additional  flags  to pass  to `open(2)',
 *                but `O_ACCMODE' is always set to `O_RDWR' */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_NCX,mkostemp64,(char *__template_, __oflag_t __flags),(__template_,__flags))
#else /* ... */
#include <asm/os/fcntl.h>
#if (defined(__CRT_HAVE_mkostemps) && (!defined(__O_LARGEFILE) || !__O_LARGEFILE)) || defined(__CRT_HAVE_mkostemps64) || defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))
#include <libc/local/stdlib/mkostemp64.h>
/* >> mkostemp(3), mkostemp64(3)
 * Replace  the  last 6  characters of  `template_' (which  are followed  by exactly
 * `suffixlen'  more  characters that  are left  alone), which  must be  filled with
 * all  'X'-characters  before  the  call  (else  errno=EINVAL  +  return  -1), with
 * random  characters  such  that the  filename  described by  `template_'  will not
 * already exists. Then, create a new file with `O_RDWR | flags' and return the file
 * descriptor of that file.
 * @param: flags: Additional  flags  to pass  to `open(2)',
 *                but `O_ACCMODE' is always set to `O_RDWR' */
__NAMESPACE_LOCAL_USING_OR_IMPL(mkostemp64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __fd_t __NOTHROW_NCX(__LIBCCALL mkostemp64)(char *__template_, __oflag_t __flags) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mkostemp64))(__template_, __flags); })
#endif /* (__CRT_HAVE_mkostemps && (!__O_LARGEFILE || !__O_LARGEFILE)) || __CRT_HAVE_mkostemps64 || __CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat)) */
#endif /* !... */
#if defined(__CRT_HAVE_mkostemps) && (!defined(__O_LARGEFILE) || !__O_LARGEFILE)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_NCX,mkostemps64,(char *__template_, __STDC_INT_AS_SIZE_T __suffixlen, __oflag_t __flags),mkostemps,(__template_,__suffixlen,__flags))
#elif defined(__CRT_HAVE_mkostemps64)
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_NCX,mkostemps64,(char *__template_, __STDC_INT_AS_SIZE_T __suffixlen, __oflag_t __flags),(__template_,__suffixlen,__flags))
#else /* ... */
#include <asm/os/fcntl.h>
#if defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))
#include <libc/local/stdlib/mkostemps64.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(mkostemps64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __fd_t __NOTHROW_NCX(__LIBCCALL mkostemps64)(char *__template_, __STDC_INT_AS_SIZE_T __suffixlen, __oflag_t __flags) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mkostemps64))(__template_, __suffixlen, __flags); })
#endif /* __CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat)) */
#endif /* !... */
#endif /* __USE_LARGEFILE64 */
#endif /* __USE_GNU || __USE_BSD */

#ifdef __USE_NETBSD
#ifndef __dev_t_defined
#define __dev_t_defined
typedef __dev_t dev_t;
#endif /* !__dev_t_defined */
#ifndef __mode_t_defined
#define __mode_t_defined
typedef __mode_t mode_t;
#endif /* !__mode_t_defined */
#ifdef __CRT_HAVE_devname
/* >> devname(3), devname_r(3) */
__CDECLARE(__ATTR_CONST,char *,__NOTHROW_NCX,devname,(dev_t __dev, mode_t __type),(__dev,__type))
#elif defined(__CRT_HAVE___devname50)
/* >> devname(3), devname_r(3) */
__CREDIRECT(__ATTR_CONST,char *,__NOTHROW_NCX,devname,(dev_t __dev, mode_t __type),__devname50,(__dev,__type))
#elif defined(__CRT_HAVE_devname_r)
#include <libc/local/stdlib/devname.h>
/* >> devname(3), devname_r(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(devname, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST char *__NOTHROW_NCX(__LIBCCALL devname)(dev_t __dev, mode_t __type) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(devname))(__dev, __type); })
#endif /* ... */
/* >> devname(3), devname_r(3) */
__CDECLARE_OPT(__ATTR_NONNULL((3)),int,__NOTHROW_NCX,devname_r,(dev_t __dev, mode_t __type, char *__buf, __SIZE_TYPE__ __len),(__dev,__type,__buf,__len))

/* Flags for `humanize_number(3)::flags' */
#if !defined(HN_DECIMAL) && defined(__HN_DECIMAL)
#define HN_DECIMAL      __HN_DECIMAL
#endif /* !HN_DECIMAL && __HN_DECIMAL */
#if !defined(HN_NOSPACE) && defined(__HN_NOSPACE)
#define HN_NOSPACE      __HN_NOSPACE
#endif /* !HN_NOSPACE && __HN_NOSPACE */
#if !defined(HN_B) && defined(__HN_B)
#define HN_B            __HN_B
#endif /* !HN_B && __HN_B */
#if !defined(HN_DIVISOR_1000) && defined(__HN_DIVISOR_1000)
#define HN_DIVISOR_1000 __HN_DIVISOR_1000
#endif /* !HN_DIVISOR_1000 && __HN_DIVISOR_1000 */
#if !defined(HN_IEC_PREFIXES) && defined(__HN_IEC_PREFIXES)
#define HN_IEC_PREFIXES __HN_IEC_PREFIXES
#endif /* !HN_IEC_PREFIXES && __HN_IEC_PREFIXES */

/* Flags for `humanize_number(3)::scale' */
#if !defined(HN_GETSCALE) && defined(__HN_GETSCALE)
#define HN_GETSCALE     __HN_GETSCALE
#endif /* !HN_GETSCALE && __HN_GETSCALE */
#if !defined(HN_AUTOSCALE) && defined(__HN_AUTOSCALE)
#define HN_AUTOSCALE    __HN_AUTOSCALE
#endif /* !HN_AUTOSCALE && __HN_AUTOSCALE */

#if !defined(__humanize_number_defined) && defined(__CRT_HAVE_humanize_number)
#define __humanize_number_defined
/* >> humanize_number(3), dehumanize_number(3)
 * @param: scale: Set of `HN_GETSCALE | HN_AUTOSCALE'
 * @param: flags: Set of `HN_DECIMAL | HN_NOSPACE | HN_B | HN_DIVISOR_1000 | HN_IEC_PREFIXES' */
__CDECLARE(,int,__NOTHROW_NCX,humanize_number,(char *__buf, __SIZE_TYPE__ __len, __INT64_TYPE__ __bytes, char const *__suffix, int __scale, int __flags),(__buf,__len,__bytes,__suffix,__scale,__flags))
#endif /* !__humanize_number_defined && __CRT_HAVE_humanize_number */
#if !defined(__dehumanize_number_defined) && defined(__CRT_HAVE_dehumanize_number)
#define __dehumanize_number_defined
/* >> humanize_number(3), dehumanize_number(3)
 * @param: scale: Set of `HN_GETSCALE | HN_AUTOSCALE'
 * @param: flags: Set of `HN_DECIMAL | HN_NOSPACE | HN_B | HN_DIVISOR_1000 | HN_IEC_PREFIXES' */
__CDECLARE(,int,__NOTHROW_NCX,dehumanize_number,(char const *__str, __INT64_TYPE__ *__size),(__str,__size))
#endif /* !__dehumanize_number_defined && __CRT_HAVE_dehumanize_number */
#if !defined(__setproctitle_defined) && defined(__CRT_HAVE_setproctitle)
#define __setproctitle_defined
/* >> setproctitle(3) */
__LIBC __ATTR_LIBC_PRINTF(1, 2) __ATTR_NONNULL((1)) void __NOTHROW_NCX(__VLIBCCALL setproctitle)(char const *__format, ...) __CASMNAME_SAME("setproctitle");
#endif /* !__setproctitle_defined && __CRT_HAVE_setproctitle */
#ifdef __CRT_HAVE_reallocarray
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) __ATTR_ALLOC_SIZE((2, 3)),void *,__NOTHROW_NCX,reallocarr,(void *__ptr, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),reallocarray,(__ptr,__elem_count,__elem_size))
#elif defined(__CRT_HAVE_reallocarr)
__CDECLARE(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) __ATTR_ALLOC_SIZE((2, 3)),void *,__NOTHROW_NCX,reallocarr,(void *__ptr, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),(__ptr,__elem_count,__elem_size))
#elif defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)
#include <libc/local/malloc/reallocarray.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) __ATTR_ALLOC_SIZE((2, 3)) void *__NOTHROW_NCX(__LIBCCALL reallocarr)(void *__ptr, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(reallocarray))(__ptr, __elem_count, __elem_size); }
#endif /* ... */
#ifdef __LONGLONG
#ifdef __CRT_HAVE_strsuftoll
/* >> strsuftoll(3)
 * Same as `strsuftollx(3)', but if an error happens, make
 * use of `errx(3)' to terminate the program, rather  than
 * return to the caller. */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__LONGLONG,__NOTHROW_NCX,strsuftoll,(char const *__desc, char const *__val, __LONGLONG __lo, __LONGLONG __hi),(__desc,__val,__lo,__hi))
#else /* __CRT_HAVE_strsuftoll */
#include <libc/template/stdstreams.h>
#include <libc/template/program_invocation_name.h>
#if defined(__CRT_HAVE_errx) || defined(__CRT_HAVE_verrx) || ((defined(__CRT_HAVE_vwarnx) || (defined(__LOCAL_stderr) && defined(__LOCAL_program_invocation_short_name) && (defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)))) && (defined(__CRT_HAVE_exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE__Exit)))
#include <libc/local/stdlib/strsuftoll.h>
/* >> strsuftoll(3)
 * Same as `strsuftollx(3)', but if an error happens, make
 * use of `errx(3)' to terminate the program, rather  than
 * return to the caller. */
__NAMESPACE_LOCAL_USING_OR_IMPL(strsuftoll, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __LONGLONG __NOTHROW_NCX(__LIBCCALL strsuftoll)(char const *__desc, char const *__val, __LONGLONG __lo, __LONGLONG __hi) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strsuftoll))(__desc, __val, __lo, __hi); })
#endif /* __CRT_HAVE_errx || __CRT_HAVE_verrx || ((__CRT_HAVE_vwarnx || (__LOCAL_stderr && __LOCAL_program_invocation_short_name && (__CRT_HAVE_putc || __CRT_HAVE_fputc || __CRT_HAVE__IO_putc || __CRT_HAVE_putc_unlocked || __CRT_HAVE_fputc_unlocked || __CRT_HAVE__putc_nolock || __CRT_HAVE__fputc_nolock || (__CRT_DOS && (__CRT_HAVE__flsbuf || __CRT_HAVE___swbuf)) || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock))) && (__CRT_HAVE_exit || __CRT_HAVE_quick_exit || __CRT_HAVE__exit || __CRT_HAVE__Exit)) */
#endif /* !__CRT_HAVE_strsuftoll */
#ifdef __CRT_HAVE_strsuftollx
/* >> strsuftollx(3) */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__LONGLONG,__NOTHROW_NCX,strsuftollx,(char const *__desc, char const *__val, __LONGLONG __lo, __LONGLONG __hi, char *__errbuf, __SIZE_TYPE__ __errbuflen),(__desc,__val,__lo,__hi,__errbuf,__errbuflen))
#else /* __CRT_HAVE_strsuftollx */
#include <libc/local/stdlib/strsuftollx.h>
/* >> strsuftollx(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(strsuftollx, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __LONGLONG __NOTHROW_NCX(__LIBCCALL strsuftollx)(char const *__desc, char const *__val, __LONGLONG __lo, __LONGLONG __hi, char *__errbuf, __SIZE_TYPE__ __errbuflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strsuftollx))(__desc, __val, __lo, __hi, __errbuf, __errbuflen); })
#endif /* !__CRT_HAVE_strsuftollx */
typedef struct __lldiv_struct qdiv_t;
#if __has_builtin(__builtin_llabs) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_llabs)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,qabs,(__LONGLONG __x),llabs,{ return __builtin_llabs(__x); })
#elif defined(__CRT_HAVE_llabs)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,qabs,(__LONGLONG __x),llabs,(__x))
#elif defined(__CRT_HAVE_qabs)
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,qabs,(__LONGLONG __x),(__x))
#elif defined(__CRT_HAVE_abs) && __SIZEOF_LONG_LONG__ == __SIZEOF_INT__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,qabs,(__LONGLONG __x),abs,(__x))
#elif defined(__CRT_HAVE_labs) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,qabs,(__LONGLONG __x),labs,(__x))
#elif defined(__CRT_HAVE_imaxabs) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,qabs,(__LONGLONG __x),imaxabs,(__x))
#elif defined(__CRT_HAVE__abs64) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,qabs,(__LONGLONG __x),_abs64,(__x))
#else /* ... */
#include <libc/local/stdlib/llabs.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __LONGLONG __NOTHROW(__LIBCCALL qabs)(__LONGLONG __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(llabs))(__x); }
#endif /* !... */
#ifdef __CRT_HAVE_lldiv
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,struct __lldiv_struct,__NOTHROW_NCX,qdiv,(__LONGLONG __numer, __LONGLONG __denom),lldiv,(__numer,__denom))
#elif defined(__CRT_HAVE_qdiv)
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,struct __lldiv_struct,__NOTHROW_NCX,qdiv,(__LONGLONG __numer, __LONGLONG __denom),(__numer,__denom))
#elif defined(__CRT_HAVE_div) && __SIZEOF_LONG_LONG__ == __SIZEOF_INT__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,struct __lldiv_struct,__NOTHROW_NCX,qdiv,(__LONGLONG __numer, __LONGLONG __denom),div,(__numer,__denom))
#elif defined(__CRT_HAVE_ldiv) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,struct __lldiv_struct,__NOTHROW_NCX,qdiv,(__LONGLONG __numer, __LONGLONG __denom),ldiv,(__numer,__denom))
#elif defined(__CRT_HAVE_imaxdiv) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,struct __lldiv_struct,__NOTHROW_NCX,qdiv,(__LONGLONG __numer, __LONGLONG __denom),imaxdiv,(__numer,__denom))
#else /* ... */
#include <libc/local/stdlib/lldiv.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED struct __lldiv_struct __NOTHROW_NCX(__LIBCCALL qdiv)(__LONGLONG __numer, __LONGLONG __denom) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lldiv))(__numer, __denom); }
#endif /* !... */
#ifdef __CRT_HAVE_strtoll_l
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,strtoq_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoll_l)
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,strtoq_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_strtoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___strtoll_l)
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,strtoq_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__strtoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtol_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,strtoq_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtol_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,strtoq_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_strtol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___strtol_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,strtoq_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__strtol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strto64_l) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,strtoq_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strto64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strto32_l) && __SIZEOF_LONG_LONG__ == 4
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,strtoq_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strto32_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtoimax_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,strtoq_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoimax_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,strtoq_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_strtoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___strtoimax_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,strtoq_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__strtoimax_l,(__nptr,__endptr,__base,__locale))
#elif __SIZEOF_LONG_LONG__ == 4
#include <libc/local/stdlib/strto64_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __LONGLONG __NOTHROW_NCX(__LIBCCALL strtoq_l)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__LONGLONG)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strto64_l))(__nptr, __endptr, __base, __locale); }
#elif __SIZEOF_LONG_LONG__ == 8
#include <libc/local/stdlib/strto32_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __LONGLONG __NOTHROW_NCX(__LIBCCALL strtoq_l)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__LONGLONG)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strto32_l))(__nptr, __endptr, __base, __locale); }
#else /* ... */
#include <libc/local/stdlib/strtoll_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __LONGLONG __NOTHROW_NCX(__LIBCCALL strtoq_l)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtoll_l))(__nptr, __endptr, __base, __locale); }
#endif /* !... */
#ifdef __CRT_HAVE_strtoull_l
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,strtouq_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoull_l)
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,strtouq_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_strtoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___strtoull_l)
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,strtouq_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__strtoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtoul_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,strtouq_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoul_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,strtouq_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_strtoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___strtoul_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,strtouq_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__strtoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtou64_l) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,strtouq_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtou64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtou32_l) && __SIZEOF_LONG_LONG__ == 4
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,strtouq_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtou32_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtoumax_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,strtouq_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoumax_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,strtouq_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_strtoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___strtoumax_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,strtouq_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__strtoumax_l,(__nptr,__endptr,__base,__locale))
#elif __SIZEOF_LONG_LONG__ == 4
#include <libc/local/stdlib/strtou64_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __ULONGLONG __NOTHROW_NCX(__LIBCCALL strtouq_l)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__ULONGLONG)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtou64_l))(__nptr, __endptr, __base, __locale); }
#elif __SIZEOF_LONG_LONG__ == 8
#include <libc/local/stdlib/strtou32_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __ULONGLONG __NOTHROW_NCX(__LIBCCALL strtouq_l)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__ULONGLONG)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtou32_l))(__nptr, __endptr, __base, __locale); }
#else /* ... */
#include <libc/local/stdlib/strtoull_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __ULONGLONG __NOTHROW_NCX(__LIBCCALL strtouq_l)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtoull_l))(__nptr, __endptr, __base, __locale); }
#endif /* !... */
#endif /* __LONGLONG */
#endif /* __USE_NETBSD */

#endif /* __CC__ */

#define __DOS_MAX_PATH         260
#define __DOS_MAX_DRIVE        3
#define __DOS_MAX_DIR          256
#define __DOS_MAX_FNAME        256
#define __DOS_MAX_EXT          256
#define __DOS_OUT_TO_DEFAULT   0
#define __DOS_OUT_TO_STDERR    1
#define __DOS_OUT_TO_MSGBOX    2
#define __DOS_REPORT_ERRMODE   3
#define __DOS_WRITE_ABORT_MSG  0x1
#define __DOS_CALL_REPORTFAULT 0x2
#define __DOS_MAX_ENV          0x7fff

#ifdef __USE_DOS
__SYSDECL_END

#include <hybrid/__minmax.h>

__SYSDECL_BEGIN

#define __min(a, b) __hybrid_min(a, b)
#define __max(a, b) __hybrid_max(a, b)
#ifndef __cplusplus
#define min(a, b) __hybrid_min(a, b)
#define max(a, b) __hybrid_max(a, b)
#endif /* !__cplusplus */

#define _MAX_PATH         __DOS_MAX_PATH
#define _MAX_DRIVE        __DOS_MAX_DRIVE
#define _MAX_DIR          __DOS_MAX_DIR
#define _MAX_FNAME        __DOS_MAX_FNAME
#define _MAX_EXT          __DOS_MAX_EXT
#define _OUT_TO_DEFAULT   __DOS_OUT_TO_DEFAULT
#define _OUT_TO_STDERR    __DOS_OUT_TO_STDERR
#define _OUT_TO_MSGBOX    __DOS_OUT_TO_MSGBOX
#define _REPORT_ERRMODE   __DOS_REPORT_ERRMODE
#define _WRITE_ABORT_MSG  __DOS_WRITE_ABORT_MSG
#define _CALL_REPORTFAULT __DOS_CALL_REPORTFAULT
#define _MAX_ENV          __DOS_MAX_ENV

#ifdef __CC__

#ifndef __errno_t_defined
#define __errno_t_defined
typedef __errno_t errno_t;
#endif /* !__errno_t_defined */

#ifndef _ONEXIT_T_DEFINED
#define _ONEXIT_T_DEFINED 1
typedef int (__LIBDCALL *_onexit_t)(void);
#endif /* !_ONEXIT_T_DEFINED */
#ifndef onexit_t
#define onexit_t _onexit_t
#endif /* !onexit_t */

#ifndef _CRT_ERRNO_DEFINED
#define _CRT_ERRNO_DEFINED 1
#ifndef errno
#ifndef ____errno_location_defined
#define ____errno_location_defined
#ifdef __CRT_HAVE___errno_location
/* >> __errno_location(3) */
__CDECLARE(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,__errno_t *,__NOTHROW_NCX,__errno_location,(void),())
#elif defined(__CRT_HAVE__errno)
/* >> __errno_location(3) */
__CREDIRECT(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,__errno_t *,__NOTHROW_NCX,__errno_location,(void),_errno,())
#elif defined(__CRT_HAVE___errno)
/* >> __errno_location(3) */
__CREDIRECT(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,__errno_t *,__NOTHROW_NCX,__errno_location,(void),__errno,())
#else /* ... */
#undef ____errno_location_defined
#endif /* !... */
#endif /* !____errno_location_defined */
#ifdef ____errno_location_defined
#define errno (*__errno_location())
#endif /* ____errno_location_defined */
#endif /* !errno */
__CDECLARE_OPT(,errno_t,__NOTHROW_NCX,_get_errno,(errno_t *__perr),(__perr))
__CDECLARE_OPT(,errno_t,__NOTHROW_NCX,_set_errno,(errno_t __err),(__err))
#endif /* !_CRT_ERRNO_DEFINED */
#if !defined(____doserrno_defined) && defined(__CRT_HAVE___doserrno)
#define ____doserrno_defined
__CDECLARE(__ATTR_CONST,__UINT32_TYPE__ *,__NOTHROW_NCX,__doserrno,(void),())
#endif /* !____doserrno_defined && __CRT_HAVE___doserrno */
__CDECLARE_OPT(,errno_t,__NOTHROW_NCX,_get_doserrno,(__UINT32_TYPE__ *__perr),(__perr))
__CDECLARE_OPT(,errno_t,__NOTHROW_NCX,_set_doserrno,(__UINT32_TYPE__ __err),(__err))
#ifdef ____doserrno_defined
#define _doserrno (*__doserrno())
#endif /* ____doserrno_defined */

#ifndef _environ
#if defined(environ)
#define _environ environ
#elif defined(__environ)
#define _environ __environ
#elif defined(__LOCAL_environ)
#define _environ __LOCAL_environ
#elif defined(__CRT_HAVE_environ)
#ifdef __NO_ASMNAME
__LIBC char **environ;
#define environ  environ
#define _environ environ
#else /* __NO_ASMNAME */
__LIBC char **_environ __CASMNAME("environ");
#define _environ _environ
#endif /* !__NO_ASMNAME */
#elif defined(__CRT_HAVE__environ)
__LIBC char **_environ;
#define _environ _environ
#elif defined(__CRT_HAVE___environ)
#ifdef __NO_ASMNAME
__LIBC char **__environ;
#define __environ __environ
#define _environ  __environ
#else /* __NO_ASMNAME */
__LIBC char **_environ __CASMNAME("__environ");
#define _environ _environ
#endif /* !__NO_ASMNAME */
#elif defined(____p__environ_defined)
#define _environ (*__p__environ())
#elif defined(__CRT_HAVE___p__environ)
#define ____p__environ_defined
__CDECLARE(__ATTR_WUNUSED __ATTR_CONST __ATTR_RETNONNULL,char ***,__NOTHROW,__p__environ,(void),())
#define _environ (*__p__environ())
#elif defined(__CRT_HAVE__get_environ)
#ifndef ___get_environ_defined
#define ___get_environ_defined
__CDECLARE(,int,__NOTHROW,_get_environ,(char ***__p_environ),())
#endif /* !___get_environ_defined */
#ifndef _____get_environ_wrapper_defined
#define _____get_environ_wrapper_defined
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST char **
__NOTHROW(__LIBCCALL ___get_environ_wrapper)(void) {
	char **__result;
	if __unlikely(_get_environ(&__result) != 0)
		__result = __NULLPTR;
	return __result;
}
#endif /* !_____get_environ_wrapper_defined */
#define _environ ___get_environ_wrapper()
#endif /* !... */
#endif /* !_environ */

#ifndef __argc
#ifdef __CRT_HAVE___argc
__LIBC int __argc;
#define __argc __argc
#else /* __CRT_HAVE___argc */
#if !defined(____p___argc_defined) && defined(__CRT_HAVE___p___argc)
#define ____p___argc_defined
__CDECLARE(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,int *,__NOTHROW_NCX,__p___argc,(void),())
#endif /* !____p___argc_defined && __CRT_HAVE___p___argc */
#ifdef ____p___argc_defined
#define __argc (*__p___argc())
#endif /* ____p___argc_defined */
#endif /* !__CRT_HAVE___argc */
#endif /* !__argc */

#ifndef __argv
#ifdef __CRT_HAVE___argv
__LIBC char **__argv;
#else /* __CRT_HAVE___argv */
#if !defined(____p___argv_defined) && defined(__CRT_HAVE___p___argv)
#define ____p___argv_defined
__CDECLARE(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,char ***,__NOTHROW_NCX,__p___argv,(void),())
#endif /* !____p___argv_defined && __CRT_HAVE___p___argv */
#ifdef ____p___argv_defined
#define __argv (*__p___argv())
#endif /* ____p___argv_defined */
#endif /* !__CRT_HAVE___argv */
#endif /* !__argv */

#ifndef __wargv
#ifdef __CRT_HAVE___wargv
__LIBC wchar_t **__wargv;
#define __wargv __wargv
#else /* __CRT_HAVE___wargv */
#if !defined(____p___wargv_defined) && defined(__CRT_HAVE___p___wargv)
#define ____p___wargv_defined
__CDECLARE(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,wchar_t ***,__NOTHROW_NCX,__p___wargv,(void),())
#endif /* !____p___wargv_defined && __CRT_HAVE___p___wargv */
#ifdef ____p___wargv_defined
#define __wargv (*__p___wargv())
#endif /* ____p___wargv_defined */
#endif /* !__CRT_HAVE___wargv */
#endif /* !__wargv */

#ifndef _wenviron
#ifdef __CRT_HAVE__wenviron
__LIBC wchar_t **_wenviron;
#define _wenviron _wenviron
#else /* __CRT_HAVE__wenviron */
#if !defined(____p__wenviron_defined) && defined(__CRT_HAVE___p__wenviron)
#define ____p__wenviron_defined
__CDECLARE(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,wchar_t ***,__NOTHROW_NCX,__p__wenviron,(void),())
#endif /* !____p__wenviron_defined && __CRT_HAVE___p__wenviron */
#ifdef ____p__wenviron_defined
#define _wenviron (*__p__wenviron())
#endif /* ____p__wenviron_defined */
#endif /* !__CRT_HAVE__wenviron */
#endif /* !_wenviron */

#ifndef _wpgmptr
#ifdef __CRT_HAVE__wpgmptr
__LIBC wchar_t *_wpgmptr;
#define _wpgmptr _wpgmptr
#else /* __CRT_HAVE__wpgmptr */
#if !defined(____p__wpgmptr_defined) && defined(__CRT_HAVE___p__wpgmptr)
#define ____p__wpgmptr_defined
__CDECLARE(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,wchar_t **,__NOTHROW_NCX,__p__wpgmptr,(void),())
#endif /* !____p__wpgmptr_defined && __CRT_HAVE___p__wpgmptr */
#ifdef ____p__wpgmptr_defined
#define _wpgmptr (*__p__wpgmptr())
#endif /* ____p__wpgmptr_defined */
#endif /* !__CRT_HAVE__wpgmptr */
#endif /* !_wpgmptr */

/* Alias for argv[0], as passed to main()
 * HINT: The GNU equivalent of this is `program_invocation_name' */
#ifndef _pgmptr
#ifdef program_invocation_name
#define _pgmptr   program_invocation_name
#elif defined(__progname_full)
#define _pgmptr   __progname_full
#elif defined(__CRT_HAVE_program_invocation_name)
#ifndef __NO_ASMNAME
__LIBC char *_pgmptr __ASMNAME("program_invocation_name");
#define _pgmptr   _pgmptr
#else /* !__NO_ASMNAME */
__LIBC char *program_invocation_name;
#define program_invocation_name program_invocation_name
#define _pgmptr                 program_invocation_name
#endif /* __NO_ASMNAME */
#elif defined(__CRT_HAVE__pgmptr)
__LIBC char *_pgmptr;
#define _pgmptr   _pgmptr
#elif defined(__CRT_HAVE___progname_full)
#ifndef __NO_ASMNAME
__LIBC char *_pgmptr __ASMNAME("__progname_full");
#define _pgmptr   _pgmptr
#else /* !__NO_ASMNAME */
__LIBC char *__progname_full;
#define __progname_full __progname_full
#define _pgmptr         __progname_full
#endif /* __NO_ASMNAME */
#else /* ... */
#ifndef ____p__pgmptr_defined
#define ____p__pgmptr_defined
#ifdef __CRT_HAVE___p__pgmptr
/* Alias for argv[0], as passed to main() */
__CDECLARE(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,char **,__NOTHROW_NCX,__p__pgmptr,(void),())
#elif defined(__CRT_HAVE___p_program_invocation_name)
/* Alias for argv[0], as passed to main() */
__CREDIRECT(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,char **,__NOTHROW_NCX,__p__pgmptr,(void),__p_program_invocation_name,())
#else /* ... */
#include <libc/template/program_invocation_name.h>
#ifdef __LOCAL_program_invocation_name_p
#include <libc/local/stdlib/__p__pgmptr.h>
/* Alias for argv[0], as passed to main() */
__NAMESPACE_LOCAL_USING_OR_IMPL(__p__pgmptr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED char **__NOTHROW_NCX(__LIBCCALL __p__pgmptr)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__p__pgmptr))(); })
#else /* __LOCAL_program_invocation_name_p */
#undef ____p__pgmptr_defined
#endif /* !__LOCAL_program_invocation_name_p */
#endif /* !... */
#endif /* !____p__pgmptr_defined */
#ifdef ____p__pgmptr_defined
#define _pgmptr   (*__p__pgmptr())
#endif /* ____p__pgmptr_defined */
#endif /* !... */
#endif /* !_pgmptr */

#ifdef __USE_KOS
#ifndef __initenv
#ifdef __CRT_HAVE___initenv
__LIBC char **__initenv;
#else /* __CRT_HAVE___initenv */
#if !defined(____p___initenv_defined) && defined(__CRT_HAVE___p___initenv)
#define ____p___initenv_defined
/* Access to the initial environment block */
__CDECLARE(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,char ***,__NOTHROW_NCX,__p___initenv,(void),())
#endif /* !____p___initenv_defined && __CRT_HAVE___p___initenv */
#ifdef ____p___initenv_defined
#define __initenv (*__p___initenv())
#endif /* ____p___initenv_defined */
#endif /* !__CRT_HAVE___initenv */
#endif /* !__initenv */
#ifndef __winitenv
#ifdef __CRT_HAVE___winitenv
__LIBC wchar_t **__winitenv;
#else /* __CRT_HAVE___winitenv */
#if !defined(____p___winitenv_defined) && defined(__CRT_HAVE___p___winitenv)
#define ____p___winitenv_defined
/* Access to the initial environment block */
__CDECLARE(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,wchar_t ***,__NOTHROW_NCX,__p___winitenv,(void),())
#endif /* !____p___winitenv_defined && __CRT_HAVE___p___winitenv */
#ifdef ____p___winitenv_defined
#define __winitenv (*__p___winitenv())
#endif /* ____p___winitenv_defined */
#endif /* !__CRT_HAVE___winitenv */
#endif /* !__winitenv */
#endif /* __USE_KOS */

#ifndef _countof
#define _countof(a) __COMPILER_LENOF(a)
#endif /* !_countof */

#ifndef ___purecall_handler_defined
#define ___purecall_handler_defined
typedef void (__LIBDCALL *_purecall_handler)(void);
#endif /* !___purecall_handler_defined */
__CDECLARE_OPT(,_purecall_handler,__NOTHROW_NCX,_set_purecall_handler,(_purecall_handler __handler),(__handler))
__CDECLARE_OPT(,_purecall_handler,__NOTHROW_NCX,_get_purecall_handler,(void),())

#ifndef ___invalid_parameter_handler_defined
#define ___invalid_parameter_handler_defined
typedef void (__LIBDCALL *_invalid_parameter_handler)(__WCHAR16_TYPE__ const *__expr,
                                                      __WCHAR16_TYPE__ const *__func,
                                                      __WCHAR16_TYPE__ const *__file,
                                                      unsigned int __line,
                                                      __UINTPTR_TYPE__ __zero);
#endif /* !___invalid_parameter_handler_defined */
__CDECLARE_OPT(,_invalid_parameter_handler,__NOTHROW_NCX,_set_invalid_parameter_handler,(_invalid_parameter_handler __handler),(__handler))
__CDECLARE_OPT(,_invalid_parameter_handler,__NOTHROW_NCX,_get_invalid_parameter_handler,(void),())
#ifdef __CRT_HAVE__get_pgmptr
__CDECLARE(,errno_t,__NOTHROW_NCX,_get_pgmptr,(char **__pvalue),(__pvalue))
#else /* __CRT_HAVE__get_pgmptr */
#include <libc/template/program_invocation_name.h>
#ifdef __LOCAL_program_invocation_name
#include <libc/local/stdlib/_get_pgmptr.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_get_pgmptr, __FORCELOCAL __ATTR_ARTIFICIAL errno_t __NOTHROW_NCX(__LIBCCALL _get_pgmptr)(char **__pvalue) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_get_pgmptr))(__pvalue); })
#endif /* __LOCAL_program_invocation_name */
#endif /* !__CRT_HAVE__get_pgmptr */
#ifdef __CRT_HAVE__get_wpgmptr
__CDECLARE(,errno_t,__NOTHROW_NCX,_get_wpgmptr,(wchar_t **__pvalue),(__pvalue))
#elif defined(__CRT_HAVE___p__wpgmptr)
#include <libc/local/stdlib/_get_wpgmptr.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_get_wpgmptr, __FORCELOCAL __ATTR_ARTIFICIAL errno_t __NOTHROW_NCX(__LIBCCALL _get_wpgmptr)(wchar_t **__pvalue) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_get_wpgmptr))(__pvalue); })
#endif /* ... */
#ifdef __CRT_HAVE__fmode
__LIBC int _fmode;
#else /* ... */
#if !defined(____p__fmode_defined) && defined(__CRT_HAVE___p__fmode)
#define ____p__fmode_defined
__CDECLARE(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,int *,__NOTHROW_NCX,__p__fmode,(void),())
#endif /* !____p__fmode_defined && __CRT_HAVE___p__fmode */
#ifdef ____p__fmode_defined
#define _fmode (*__p__fmode())
#endif /* ____p__fmode_defined */
#endif /* !... */
__CDECLARE_OPT(,errno_t,__NOTHROW_NCX,_set_fmode,(int __mode),(__mode))
__CDECLARE_OPT(,errno_t,__NOTHROW_NCX,_get_fmode,(int *__pmode),(__pmode))
__CDECLARE_OPT(,unsigned int,__NOTHROW_NCX,_set_abort_behavior,(unsigned int __flags, unsigned int __mask),(__flags,__mask))
#ifdef __INT64_TYPE__
#if defined(_MSC_VER) && defined(__LIBCCALL_IS_LIBDCALL)
#ifndef _abs64
#define _abs64 _abs64
extern __ATTR_CONST __INT64_TYPE__ (__LIBDCALL _abs64)(__INT64_TYPE__ __x);
#pragma intrinsic(_abs64)
#endif /* !_abs64 */
#else /* _MSC_VER && __LIBCCALL_IS_LIBDCALL */
#ifdef __CRT_HAVE__abs64
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__INT64_TYPE__,__NOTHROW,_abs64,(__INT64_TYPE__ __x),(__x))
#elif defined(__CRT_HAVE_abs) && __SIZEOF_INT__ == 8
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__INT64_TYPE__,__NOTHROW,_abs64,(__INT64_TYPE__ __x),abs,(__x))
#elif defined(__CRT_HAVE_llabs) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__INT64_TYPE__,__NOTHROW,_abs64,(__INT64_TYPE__ __x),llabs,(__x))
#elif defined(__CRT_HAVE_qabs) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__INT64_TYPE__,__NOTHROW,_abs64,(__INT64_TYPE__ __x),qabs,(__x))
#elif defined(__CRT_HAVE_imaxabs) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__INT64_TYPE__,__NOTHROW,_abs64,(__INT64_TYPE__ __x),imaxabs,(__x))
#elif __SIZEOF_INT__ == 8
#include <libc/local/stdlib/abs.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __INT64_TYPE__ __NOTHROW(__LIBCCALL _abs64)(__INT64_TYPE__ __x) { return (__INT64_TYPE__)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(abs))((int)__x); }
#elif __SIZEOF_LONG_LONG__ == 8
#include <libc/local/stdlib/llabs.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __INT64_TYPE__ __NOTHROW(__LIBCCALL _abs64)(__INT64_TYPE__ __x) { return (__INT64_TYPE__)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(llabs))((__LONGLONG)__x); }
#else /* ... */
#include <libc/local/stdlib/_abs64.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_abs64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __INT64_TYPE__ __NOTHROW(__LIBCCALL _abs64)(__INT64_TYPE__ __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_abs64))(__x); })
#endif /* !... */
#endif /* !_MSC_VER || !__LIBCCALL_IS_LIBDCALL */
#endif /* __INT64_TYPE__ */
#ifndef __NO_FPU
#ifdef __CRT_HAVE__atof_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),double,__NOTHROW_NCX,_atof_l,(char const *__restrict __nptr, __locale_t __locale),(__nptr,__locale))
#else /* __CRT_HAVE__atof_l */
#include <libc/local/stdlib/_atof_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_atof_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) double __NOTHROW_NCX(__LIBCCALL _atof_l)(char const *__restrict __nptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_atof_l))(__nptr, __locale); })
#endif /* !__CRT_HAVE__atof_l */
#endif /* !__NO_FPU */
#ifdef __CRT_HAVE__atoi_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,_atoi_l,(char const *__restrict __nptr, __locale_t __locale),(__nptr,__locale))
#elif defined(__CRT_HAVE__atol_l) && __SIZEOF_INT__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,_atoi_l,(char const *__restrict __nptr, __locale_t __locale),_atol_l,(__nptr,__locale))
#elif defined(__CRT_HAVE__atoll_l) && __SIZEOF_INT__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,_atoi_l,(char const *__restrict __nptr, __locale_t __locale),_atoll_l,(__nptr,__locale))
#else /* ... */
#include <libc/local/stdlib/_atoi_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_atoi_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL _atoi_l)(char const *__restrict __nptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_atoi_l))(__nptr, __locale); })
#endif /* !... */
#ifdef __CRT_HAVE__atol_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),long int,__NOTHROW_NCX,_atol_l,(char const *__restrict __nptr, __locale_t __locale),(__nptr,__locale))
#elif defined(__CRT_HAVE__atoi_l) && __SIZEOF_LONG__ == __SIZEOF_INT__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),long int,__NOTHROW_NCX,_atol_l,(char const *__restrict __nptr, __locale_t __locale),_atoi_l,(__nptr,__locale))
#elif defined(__CRT_HAVE__atoll_l) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),long int,__NOTHROW_NCX,_atol_l,(char const *__restrict __nptr, __locale_t __locale),_atoll_l,(__nptr,__locale))
#else /* ... */
#include <libc/local/stdlib/_atol_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_atol_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) long int __NOTHROW_NCX(__LIBCCALL _atol_l)(char const *__restrict __nptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_atol_l))(__nptr, __locale); })
#endif /* !... */
#ifdef __LONGLONG
#ifdef __CRT_HAVE__atoll_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,_atoll_l,(char const *__restrict __nptr, __locale_t __locale),(__nptr,__locale))
#elif defined(__CRT_HAVE__atol_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,_atoll_l,(char const *__restrict __nptr, __locale_t __locale),_atol_l,(__nptr,__locale))
#elif defined(__CRT_HAVE__atoi_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INT__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,_atoll_l,(char const *__restrict __nptr, __locale_t __locale),_atoi_l,(__nptr,__locale))
#else /* ... */
#include <libc/local/stdlib/_atoll_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_atoll_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __LONGLONG __NOTHROW_NCX(__LIBCCALL _atoll_l)(char const *__restrict __nptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_atoll_l))(__nptr, __locale); })
#endif /* !... */
#endif /* __LONGLONG */

#ifdef _MSC_VER
#ifndef _byteswap_ushort
#define _byteswap_ushort _byteswap_ushort
extern unsigned short (_byteswap_ushort)(unsigned short __x);
#pragma intrinsic(_byteswap_ushort)
#endif /* !_byteswap_ushort */
#ifndef _byteswap_ulong
#define _byteswap_ulong _byteswap_ulong
extern unsigned long (_byteswap_ulong)(unsigned long __x);
#pragma intrinsic(_byteswap_ulong)
#endif /* !_byteswap_ulong */
#ifndef _byteswap_uint64
#define _byteswap_uint64 _byteswap_uint64
extern unsigned __int64 (_byteswap_uint64)(unsigned __int64 __x);
#pragma intrinsic(_byteswap_uint64)
#endif /* !_byteswap_uint64 */
#else /* _MSC_VER */
#ifdef __CRT_HAVE__byteswap_ushort
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__UINT16_TYPE__,__NOTHROW_NCX,_byteswap_ushort,(__UINT16_TYPE__ __val),(__val))
#else /* __CRT_HAVE__byteswap_ushort */
#include <libc/local/stdlib/_byteswap_ushort.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_byteswap_ushort, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __UINT16_TYPE__ __NOTHROW_NCX(__LIBCCALL _byteswap_ushort)(__UINT16_TYPE__ __val) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_byteswap_ushort))(__val); })
#endif /* !__CRT_HAVE__byteswap_ushort */
#ifdef __CRT_HAVE__byteswap_ulong
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__UINT32_TYPE__,__NOTHROW_NCX,_byteswap_ulong,(__UINT32_TYPE__ __val),(__val))
#else /* __CRT_HAVE__byteswap_ulong */
#include <libc/local/stdlib/_byteswap_ulong.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_byteswap_ulong, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __UINT32_TYPE__ __NOTHROW_NCX(__LIBCCALL _byteswap_ulong)(__UINT32_TYPE__ __val) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_byteswap_ulong))(__val); })
#endif /* !__CRT_HAVE__byteswap_ulong */
#ifdef __UINT64_TYPE__
#ifdef __CRT_HAVE__byteswap_uint64
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__UINT64_TYPE__,__NOTHROW_NCX,_byteswap_uint64,(__UINT64_TYPE__ __val),(__val))
#else /* __CRT_HAVE__byteswap_uint64 */
#include <libc/local/stdlib/_byteswap_uint64.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_byteswap_uint64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __UINT64_TYPE__ __NOTHROW_NCX(__LIBCCALL _byteswap_uint64)(__UINT64_TYPE__ __val) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_byteswap_uint64))(__val); })
#endif /* !__CRT_HAVE__byteswap_uint64 */
#endif /* __UINT64_TYPE__ */
#ifndef _byteswap_ushort
#define _byteswap_ushort(x) __hybrid_bswap16(x)
#endif /* !_byteswap_ushort */
#ifndef _byteswap_ulong
#define _byteswap_ulong(x)  __hybrid_bswap32(x)
#endif /* !_byteswap_ulong */
#ifdef __UINT64_TYPE__
#ifndef _byteswap_uint64
#define _byteswap_uint64(x) __hybrid_bswap64(x)
#endif /* !_byteswap_uint64 */
#endif /* __UINT64_TYPE__ */
#endif /* !_MSC_VER */
#ifdef __USE_DOS_SLIB
#ifndef __rsize_t_defined
#define __rsize_t_defined
typedef __SIZE_TYPE__ rsize_t;
#endif /* !__rsize_t_defined */

#ifndef _CRT_ALGO_DEFINED
#define _CRT_ALGO_DEFINED 1
#ifndef __bsearch_s_defined
#define __bsearch_s_defined
#ifdef __CRT_HAVE_bsearch_s
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 2, 5)),void *,__THROWING,bsearch_s,(void const *__key, void const *__base, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size, int (__LIBCCALL *__compar)(void *__arg, void const *__a, void const *__b), void *__arg),(__key,__base,__elem_count,__elem_size,__compar,__arg))
#else /* __CRT_HAVE_bsearch_s */
#include <libc/local/stdlib/bsearch_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(bsearch_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 2, 5)) void *(__LIBCCALL bsearch_s)(void const *__key, void const *__base, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size, int (__LIBCCALL *__compar)(void *__arg, void const *__a, void const *__b), void *__arg) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(bsearch_s))(__key, __base, __elem_count, __elem_size, __compar, __arg); })
#endif /* !__CRT_HAVE_bsearch_s */
#endif /* !__bsearch_s_defined */
#ifndef __qsort_s_defined
#define __qsort_s_defined
#ifdef __CRT_HAVE_qsort_s
__CDECLARE_VOID(__ATTR_NONNULL((1, 4)),__THROWING,qsort_s,(void *__base, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size, int (__LIBCCALL *__compar)(void *__arg, void const *__a, void const *__b), void *__arg),(__base,__elem_count,__elem_size,__compar,__arg))
#else /* __CRT_HAVE_qsort_s */
#include <libc/local/stdlib/qsort_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(qsort_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 4)) void (__LIBCCALL qsort_s)(void *__base, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size, int (__LIBCCALL *__compar)(void *__arg, void const *__a, void const *__b), void *__arg) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(qsort_s))(__base, __elem_count, __elem_size, __compar, __arg); })
#endif /* !__CRT_HAVE_qsort_s */
#endif /* !__qsort_s_defined */
#endif  /* _CRT_ALGO_DEFINED */

#ifdef __CRT_HAVE_getenv_s
__CDECLARE(__ATTR_NONNULL((1, 2, 4)),errno_t,__NOTHROW_NCX,getenv_s,(__SIZE_TYPE__ *__preqsize, char *__buf, rsize_t __bufsize, char const *__varname),(__preqsize,__buf,__bufsize,__varname))
#elif defined(__CRT_HAVE_getenv) || defined(__LOCAL_environ)
#include <libc/local/stdlib/getenv_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(getenv_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2, 4)) errno_t __NOTHROW_NCX(__LIBCCALL getenv_s)(__SIZE_TYPE__ *__preqsize, char *__buf, rsize_t __bufsize, char const *__varname) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getenv_s))(__preqsize, __buf, __bufsize, __varname); })
#endif /* ... */
#ifdef __CRT_HAVE__dupenv_s
__CDECLARE(__ATTR_NONNULL((1, 2, 3)),errno_t,__NOTHROW_NCX,_dupenv_s,(char **__restrict __pbuf, __SIZE_TYPE__ *__pbuflen, char const *__varname),(__pbuf,__pbuflen,__varname))
#elif (defined(__CRT_HAVE_getenv) || defined(__LOCAL_environ)) && (defined(__CRT_HAVE_strdup) || defined(__CRT_HAVE__strdup) || defined(__CRT_HAVE__mbsdup) || defined(__CRT_HAVE___strdup) || defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign))
#include <libc/local/stdlib/_dupenv_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_dupenv_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2, 3)) errno_t __NOTHROW_NCX(__LIBCCALL _dupenv_s)(char **__restrict __pbuf, __SIZE_TYPE__ *__pbuflen, char const *__varname) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_dupenv_s))(__pbuf, __pbuflen, __varname); })
#endif /* ... */
#endif /* __USE_DOS_SLIB */
#ifdef __CRT_HAVE_itoa
__CREDIRECT(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,_itoa,(int __val, char *__buf, int __radix),itoa,(__val,__buf,__radix))
#elif defined(__CRT_HAVE__itoa)
__CDECLARE(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,_itoa,(int __val, char *__buf, int __radix),(__val,__buf,__radix))
#elif defined(__CRT_HAVE__ltoa) && __SIZEOF_INT__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,_itoa,(int __val, char *__buf, int __radix),_ltoa,(__val,__buf,__radix))
#elif defined(__CRT_HAVE_ltoa) && __SIZEOF_INT__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,_itoa,(int __val, char *__buf, int __radix),ltoa,(__val,__buf,__radix))
#elif defined(__CRT_HAVE__i64toa) && __SIZEOF_INT__ == 8
__CREDIRECT(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,_itoa,(int __val, char *__buf, int __radix),_i64toa,(__val,__buf,__radix))
#else /* ... */
#include <libc/local/stdlib/itoa.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) char *__NOTHROW_NCX(__LIBCCALL _itoa)(int __val, char *__buf, int __radix) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(itoa))(__val, __buf, __radix); }
#endif /* !... */
#ifdef __CRT_HAVE_ltoa
__CREDIRECT(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,_ltoa,(long __val, char *__buf, int __radix),ltoa,(__val,__buf,__radix))
#elif defined(__CRT_HAVE__ltoa)
__CDECLARE(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,_ltoa,(long __val, char *__buf, int __radix),(__val,__buf,__radix))
#elif defined(__CRT_HAVE_itoa) && __SIZEOF_LONG__ == __SIZEOF_INT__
__CREDIRECT(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,_ltoa,(long __val, char *__buf, int __radix),itoa,(__val,__buf,__radix))
#elif defined(__CRT_HAVE__itoa) && __SIZEOF_LONG__ == __SIZEOF_INT__
__CREDIRECT(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,_ltoa,(long __val, char *__buf, int __radix),_itoa,(__val,__buf,__radix))
#elif defined(__CRT_HAVE__i64toa) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,_ltoa,(long __val, char *__buf, int __radix),_i64toa,(__val,__buf,__radix))
#else /* ... */
#include <libc/local/stdlib/ltoa.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) char *__NOTHROW_NCX(__LIBCCALL _ltoa)(long __val, char *__buf, int __radix) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ltoa))(__val, __buf, __radix); }
#endif /* !... */
#ifdef __CRT_HAVE_ultoa
__CREDIRECT(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,_ultoa,(unsigned long __val, char *__buf, int __radix),ultoa,(__val,__buf,__radix))
#elif defined(__CRT_HAVE__ultoa)
__CDECLARE(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,_ultoa,(unsigned long __val, char *__buf, int __radix),(__val,__buf,__radix))
#elif defined(__CRT_HAVE__ui64toa) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,_ultoa,(unsigned long __val, char *__buf, int __radix),_ui64toa,(__val,__buf,__radix))
#else /* ... */
#include <libc/local/stdlib/ultoa.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) char *__NOTHROW_NCX(__LIBCCALL _ultoa)(unsigned long __val, char *__buf, int __radix) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ultoa))(__val, __buf, __radix); }
#endif /* !... */
#ifdef __CRT_HAVE__itoa_s
__CDECLARE(__ATTR_NONNULL((2)),errno_t,__NOTHROW_NCX,_itoa_s,(int __val, char *__buf, __SIZE_TYPE__ __buflen, int __radix),(__val,__buf,__buflen,__radix))
#elif defined(__CRT_HAVE__ltoa_s) && __SIZEOF_INT__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_NONNULL((2)),errno_t,__NOTHROW_NCX,_itoa_s,(int __val, char *__buf, __SIZE_TYPE__ __buflen, int __radix),_ltoa_s,(__val,__buf,__buflen,__radix))
#elif defined(__CRT_HAVE__i64toa_s) && __SIZEOF_INT__ == 8
__CREDIRECT(__ATTR_NONNULL((2)),errno_t,__NOTHROW_NCX,_itoa_s,(int __val, char *__buf, __SIZE_TYPE__ __buflen, int __radix),_i64toa_s,(__val,__buf,__buflen,__radix))
#else /* ... */
#include <libc/local/stdlib/_itoa_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_itoa_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) errno_t __NOTHROW_NCX(__LIBCCALL _itoa_s)(int __val, char *__buf, __SIZE_TYPE__ __buflen, int __radix) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_itoa_s))(__val, __buf, __buflen, __radix); })
#endif /* !... */
#ifdef __CRT_HAVE__ltoa_s
__CDECLARE(__ATTR_NONNULL((2)),errno_t,__NOTHROW_NCX,_ltoa_s,(long __val, char *__buf, __SIZE_TYPE__ __buflen, int __radix),(__val,__buf,__buflen,__radix))
#elif defined(__CRT_HAVE__itoa_s) && __SIZEOF_LONG__ == __SIZEOF_INT__
__CREDIRECT(__ATTR_NONNULL((2)),errno_t,__NOTHROW_NCX,_ltoa_s,(long __val, char *__buf, __SIZE_TYPE__ __buflen, int __radix),_itoa_s,(__val,__buf,__buflen,__radix))
#elif defined(__CRT_HAVE__i64toa_s) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_NONNULL((2)),errno_t,__NOTHROW_NCX,_ltoa_s,(long __val, char *__buf, __SIZE_TYPE__ __buflen, int __radix),_i64toa_s,(__val,__buf,__buflen,__radix))
#else /* ... */
#include <libc/local/stdlib/_ltoa_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_ltoa_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) errno_t __NOTHROW_NCX(__LIBCCALL _ltoa_s)(long __val, char *__buf, __SIZE_TYPE__ __buflen, int __radix) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_ltoa_s))(__val, __buf, __buflen, __radix); })
#endif /* !... */
#ifdef __CRT_HAVE__ultoa_s
__CDECLARE(__ATTR_NONNULL((2)),errno_t,__NOTHROW_NCX,_ultoa_s,(unsigned long __val, char *__buf, __SIZE_TYPE__ __buflen, int __radix),(__val,__buf,__buflen,__radix))
#elif defined(__CRT_HAVE__ui64toa_s) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_NONNULL((2)),errno_t,__NOTHROW_NCX,_ultoa_s,(unsigned long __val, char *__buf, __SIZE_TYPE__ __buflen, int __radix),_ui64toa_s,(__val,__buf,__buflen,__radix))
#else /* ... */
#include <libc/local/stdlib/_ultoa_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_ultoa_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) errno_t __NOTHROW_NCX(__LIBCCALL _ultoa_s)(unsigned long __val, char *__buf, __SIZE_TYPE__ __buflen, int __radix) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_ultoa_s))(__val, __buf, __buflen, __radix); })
#endif /* !... */

#ifdef __UINT64_TYPE__
#ifdef __CRT_HAVE__i64toa
__CDECLARE(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,_i64toa,(__INT64_TYPE__ __val, char *__buf, int __radix),(__val,__buf,__radix))
#elif defined(__CRT_HAVE_itoa) && __SIZEOF_INT__ == 8
__CREDIRECT(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,_i64toa,(__INT64_TYPE__ __val, char *__buf, int __radix),itoa,(__val,__buf,__radix))
#elif defined(__CRT_HAVE__itoa) && __SIZEOF_INT__ == 8
__CREDIRECT(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,_i64toa,(__INT64_TYPE__ __val, char *__buf, int __radix),_itoa,(__val,__buf,__radix))
#elif defined(__CRT_HAVE_ltoa) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,_i64toa,(__INT64_TYPE__ __val, char *__buf, int __radix),ltoa,(__val,__buf,__radix))
#elif defined(__CRT_HAVE__ltoa) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,_i64toa,(__INT64_TYPE__ __val, char *__buf, int __radix),_ltoa,(__val,__buf,__radix))
#else /* ... */
#include <libc/local/stdlib/_i64toa.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_i64toa, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) char *__NOTHROW_NCX(__LIBCCALL _i64toa)(__INT64_TYPE__ __val, char *__buf, int __radix) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_i64toa))(__val, __buf, __radix); })
#endif /* !... */
#ifdef __CRT_HAVE__ui64toa
__CDECLARE(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,_ui64toa,(__UINT64_TYPE__ __val, char *__buf, int __radix),(__val,__buf,__radix))
#elif defined(__CRT_HAVE_ultoa) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,_ui64toa,(__UINT64_TYPE__ __val, char *__buf, int __radix),ultoa,(__val,__buf,__radix))
#elif defined(__CRT_HAVE__ultoa) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,_ui64toa,(__UINT64_TYPE__ __val, char *__buf, int __radix),_ultoa,(__val,__buf,__radix))
#else /* ... */
#include <libc/local/stdlib/_ui64toa.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_ui64toa, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) char *__NOTHROW_NCX(__LIBCCALL _ui64toa)(__UINT64_TYPE__ __val, char *__buf, int __radix) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_ui64toa))(__val, __buf, __radix); })
#endif /* !... */
#ifdef __CRT_HAVE__i64toa_s
__CDECLARE(__ATTR_NONNULL((2)),errno_t,__NOTHROW_NCX,_i64toa_s,(__INT64_TYPE__ __val, char *__buf, __SIZE_TYPE__ __buflen, int __radix),(__val,__buf,__buflen,__radix))
#elif defined(__CRT_HAVE__ltoa_s) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_NONNULL((2)),errno_t,__NOTHROW_NCX,_i64toa_s,(__INT64_TYPE__ __val, char *__buf, __SIZE_TYPE__ __buflen, int __radix),_ltoa_s,(__val,__buf,__buflen,__radix))
#elif defined(__CRT_HAVE__itoa_s) && __SIZEOF_INT__ == 8
__CREDIRECT(__ATTR_NONNULL((2)),errno_t,__NOTHROW_NCX,_i64toa_s,(__INT64_TYPE__ __val, char *__buf, __SIZE_TYPE__ __buflen, int __radix),_itoa_s,(__val,__buf,__buflen,__radix))
#else /* ... */
#include <libc/local/stdlib/_i64toa_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_i64toa_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) errno_t __NOTHROW_NCX(__LIBCCALL _i64toa_s)(__INT64_TYPE__ __val, char *__buf, __SIZE_TYPE__ __buflen, int __radix) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_i64toa_s))(__val, __buf, __buflen, __radix); })
#endif /* !... */
#ifdef __CRT_HAVE__ui64toa_s
__CDECLARE(__ATTR_NONNULL((2)),errno_t,__NOTHROW_NCX,_ui64toa_s,(__UINT64_TYPE__ __val, char *__buf, __SIZE_TYPE__ __buflen, int __radix),(__val,__buf,__buflen,__radix))
#elif defined(__CRT_HAVE__ultoa_s) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_NONNULL((2)),errno_t,__NOTHROW_NCX,_ui64toa_s,(__UINT64_TYPE__ __val, char *__buf, __SIZE_TYPE__ __buflen, int __radix),_ultoa_s,(__val,__buf,__buflen,__radix))
#else /* ... */
#include <libc/local/stdlib/_ui64toa_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_ui64toa_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) errno_t __NOTHROW_NCX(__LIBCCALL _ui64toa_s)(__UINT64_TYPE__ __val, char *__buf, __SIZE_TYPE__ __buflen, int __radix) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_ui64toa_s))(__val, __buf, __buflen, __radix); })
#endif /* !... */
#ifdef __CRT_HAVE_strto64
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string  (radix=`base') from `nptr'  into an  integer,
 * and store a  pointer to  the end  of the  number in  `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid   integer   (`U?INTn_(MIN|MAX))'.   (though   note   that
 * `endptr'  (if  non-NULL)  is  still  updated  in  this   case!)
 * Upon success, `errno' is left  unchanged, and the integer  repr
 * of the parsed number is  returned. When no integer was  parsed,
 * then `0' is returned, `*endptr'  is set to `nptr', but  `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_strtoi64,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strto64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__strtoi64)
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string  (radix=`base') from `nptr'  into an  integer,
 * and store a  pointer to  the end  of the  number in  `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid   integer   (`U?INTn_(MIN|MAX))'.   (though   note   that
 * `endptr'  (if  non-NULL)  is  still  updated  in  this   case!)
 * Upon success, `errno' is left  unchanged, and the integer  repr
 * of the parsed number is  returned. When no integer was  parsed,
 * then `0' is returned, `*endptr'  is set to `nptr', but  `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_strtoi64,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtol) && __SIZEOF_LONG__ == 8
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string  (radix=`base') from `nptr'  into an  integer,
 * and store a  pointer to  the end  of the  number in  `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid   integer   (`U?INTn_(MIN|MAX))'.   (though   note   that
 * `endptr'  (if  non-NULL)  is  still  updated  in  this   case!)
 * Upon success, `errno' is left  unchanged, and the integer  repr
 * of the parsed number is  returned. When no integer was  parsed,
 * then `0' is returned, `*endptr'  is set to `nptr', but  `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_strtoi64,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoll) && __SIZEOF_LONG_LONG__ == 8
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string  (radix=`base') from `nptr'  into an  integer,
 * and store a  pointer to  the end  of the  number in  `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid   integer   (`U?INTn_(MIN|MAX))'.   (though   note   that
 * `endptr'  (if  non-NULL)  is  still  updated  in  this   case!)
 * Upon success, `errno' is left  unchanged, and the integer  repr
 * of the parsed number is  returned. When no integer was  parsed,
 * then `0' is returned, `*endptr'  is set to `nptr', but  `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_strtoi64,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoq) && __SIZEOF_LONG_LONG__ == 8
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string  (radix=`base') from `nptr'  into an  integer,
 * and store a  pointer to  the end  of the  number in  `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid   integer   (`U?INTn_(MIN|MAX))'.   (though   note   that
 * `endptr'  (if  non-NULL)  is  still  updated  in  this   case!)
 * Upon success, `errno' is left  unchanged, and the integer  repr
 * of the parsed number is  returned. When no integer was  parsed,
 * then `0' is returned, `*endptr'  is set to `nptr', but  `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_strtoi64,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE___strtoq) && __SIZEOF_LONG_LONG__ == 8
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string  (radix=`base') from `nptr'  into an  integer,
 * and store a  pointer to  the end  of the  number in  `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid   integer   (`U?INTn_(MIN|MAX))'.   (though   note   that
 * `endptr'  (if  non-NULL)  is  still  updated  in  this   case!)
 * Upon success, `errno' is left  unchanged, and the integer  repr
 * of the parsed number is  returned. When no integer was  parsed,
 * then `0' is returned, `*endptr'  is set to `nptr', but  `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_strtoi64,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),__strtoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoimax) && __SIZEOF_INTMAX_T__ == 8
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string  (radix=`base') from `nptr'  into an  integer,
 * and store a  pointer to  the end  of the  number in  `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid   integer   (`U?INTn_(MIN|MAX))'.   (though   note   that
 * `endptr'  (if  non-NULL)  is  still  updated  in  this   case!)
 * Upon success, `errno' is left  unchanged, and the integer  repr
 * of the parsed number is  returned. When no integer was  parsed,
 * then `0' is returned, `*endptr'  is set to `nptr', but  `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_strtoi64,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoimax,(__nptr,__endptr,__base))
#else /* ... */
#include <libc/local/stdlib/strto64.h>
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string  (radix=`base') from `nptr'  into an  integer,
 * and store a  pointer to  the end  of the  number in  `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid   integer   (`U?INTn_(MIN|MAX))'.   (though   note   that
 * `endptr'  (if  non-NULL)  is  still  updated  in  this   case!)
 * Upon success, `errno' is left  unchanged, and the integer  repr
 * of the parsed number is  returned. When no integer was  parsed,
 * then `0' is returned, `*endptr'  is set to `nptr', but  `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __INT64_TYPE__ __NOTHROW_NCX(__LIBCCALL _strtoi64)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strto64))(__nptr, __endptr, __base); }
#endif /* !... */
#ifdef __CRT_HAVE_strtou64
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string  (radix=`base') from `nptr'  into an  integer,
 * and store a  pointer to  the end  of the  number in  `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid   integer   (`U?INTn_(MIN|MAX))'.   (though   note   that
 * `endptr'  (if  non-NULL)  is  still  updated  in  this   case!)
 * Upon success, `errno' is left  unchanged, and the integer  repr
 * of the parsed number is  returned. When no integer was  parsed,
 * then `0' is returned, `*endptr'  is set to `nptr', but  `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,_strtoui64,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtou64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__strtoui64)
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string  (radix=`base') from `nptr'  into an  integer,
 * and store a  pointer to  the end  of the  number in  `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid   integer   (`U?INTn_(MIN|MAX))'.   (though   note   that
 * `endptr'  (if  non-NULL)  is  still  updated  in  this   case!)
 * Upon success, `errno' is left  unchanged, and the integer  repr
 * of the parsed number is  returned. When no integer was  parsed,
 * then `0' is returned, `*endptr'  is set to `nptr', but  `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,_strtoui64,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoul) && __SIZEOF_LONG__ == 8
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string  (radix=`base') from `nptr'  into an  integer,
 * and store a  pointer to  the end  of the  number in  `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid   integer   (`U?INTn_(MIN|MAX))'.   (though   note   that
 * `endptr'  (if  non-NULL)  is  still  updated  in  this   case!)
 * Upon success, `errno' is left  unchanged, and the integer  repr
 * of the parsed number is  returned. When no integer was  parsed,
 * then `0' is returned, `*endptr'  is set to `nptr', but  `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,_strtoui64,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoull) && __SIZEOF_LONG_LONG__ == 8
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string  (radix=`base') from `nptr'  into an  integer,
 * and store a  pointer to  the end  of the  number in  `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid   integer   (`U?INTn_(MIN|MAX))'.   (though   note   that
 * `endptr'  (if  non-NULL)  is  still  updated  in  this   case!)
 * Upon success, `errno' is left  unchanged, and the integer  repr
 * of the parsed number is  returned. When no integer was  parsed,
 * then `0' is returned, `*endptr'  is set to `nptr', but  `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,_strtoui64,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtouq) && __SIZEOF_LONG_LONG__ == 8
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string  (radix=`base') from `nptr'  into an  integer,
 * and store a  pointer to  the end  of the  number in  `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid   integer   (`U?INTn_(MIN|MAX))'.   (though   note   that
 * `endptr'  (if  non-NULL)  is  still  updated  in  this   case!)
 * Upon success, `errno' is left  unchanged, and the integer  repr
 * of the parsed number is  returned. When no integer was  parsed,
 * then `0' is returned, `*endptr'  is set to `nptr', but  `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,_strtoui64,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE___strtouq) && __SIZEOF_LONG_LONG__ == 8
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string  (radix=`base') from `nptr'  into an  integer,
 * and store a  pointer to  the end  of the  number in  `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid   integer   (`U?INTn_(MIN|MAX))'.   (though   note   that
 * `endptr'  (if  non-NULL)  is  still  updated  in  this   case!)
 * Upon success, `errno' is left  unchanged, and the integer  repr
 * of the parsed number is  returned. When no integer was  parsed,
 * then `0' is returned, `*endptr'  is set to `nptr', but  `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,_strtoui64,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),__strtouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoumax) && __SIZEOF_INTMAX_T__ == 8
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string  (radix=`base') from `nptr'  into an  integer,
 * and store a  pointer to  the end  of the  number in  `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid   integer   (`U?INTn_(MIN|MAX))'.   (though   note   that
 * `endptr'  (if  non-NULL)  is  still  updated  in  this   case!)
 * Upon success, `errno' is left  unchanged, and the integer  repr
 * of the parsed number is  returned. When no integer was  parsed,
 * then `0' is returned, `*endptr'  is set to `nptr', but  `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,_strtoui64,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoumax,(__nptr,__endptr,__base))
#else /* ... */
#include <libc/local/stdlib/strtou64.h>
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string  (radix=`base') from `nptr'  into an  integer,
 * and store a  pointer to  the end  of the  number in  `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid   integer   (`U?INTn_(MIN|MAX))'.   (though   note   that
 * `endptr'  (if  non-NULL)  is  still  updated  in  this   case!)
 * Upon success, `errno' is left  unchanged, and the integer  repr
 * of the parsed number is  returned. When no integer was  parsed,
 * then `0' is returned, `*endptr'  is set to `nptr', but  `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __UINT64_TYPE__ __NOTHROW_NCX(__LIBCCALL _strtoui64)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtou64))(__nptr, __endptr, __base); }
#endif /* !... */
#ifdef __CRT_HAVE_strto64_l
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_strtoi64_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strto64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoi64_l)
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_strtoi64_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtol_l) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_strtoi64_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtol_l) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_strtoi64_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_strtol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___strtol_l) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_strtoi64_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__strtol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtoll_l) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_strtoi64_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoll_l) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_strtoi64_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_strtoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___strtoll_l) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_strtoi64_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__strtoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtoq_l) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_strtoi64_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtoq_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtoimax_l) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_strtoi64_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoimax_l) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_strtoi64_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_strtoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___strtoimax_l) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_strtoi64_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__strtoimax_l,(__nptr,__endptr,__base,__locale))
#else /* ... */
#include <libc/local/stdlib/strto64_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __INT64_TYPE__ __NOTHROW_NCX(__LIBCCALL _strtoi64_l)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strto64_l))(__nptr, __endptr, __base, __locale); }
#endif /* !... */
#ifdef __CRT_HAVE_strtou64_l
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,_strtoui64_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtou64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoui64_l)
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,_strtoui64_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtoul_l) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,_strtoui64_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoul_l) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,_strtoui64_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_strtoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___strtoul_l) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,_strtoui64_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__strtoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtoull_l) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,_strtoui64_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoull_l) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,_strtoui64_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_strtoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___strtoull_l) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,_strtoui64_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__strtoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtouq_l) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,_strtoui64_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtouq_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtoumax_l) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,_strtoui64_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoumax_l) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,_strtoui64_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_strtoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___strtoumax_l) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,_strtoui64_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__strtoumax_l,(__nptr,__endptr,__base,__locale))
#else /* ... */
#include <libc/local/stdlib/strtou64_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __UINT64_TYPE__ __NOTHROW_NCX(__LIBCCALL _strtoui64_l)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtou64_l))(__nptr, __endptr, __base, __locale); }
#endif /* !... */
#ifdef __CRT_HAVE__atoi64
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_atoi64,(char const *__restrict __nptr),(__nptr))
#elif defined(__CRT_HAVE_atoi) && __SIZEOF_INT__ == 8
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_atoi64,(char const *__restrict __nptr),atoi,(__nptr))
#elif defined(__CRT_HAVE_atol) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_atoi64,(char const *__restrict __nptr),atol,(__nptr))
#elif defined(__CRT_HAVE_atoll) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_atoi64,(char const *__restrict __nptr),atoll,(__nptr))
#else /* ... */
#include <libc/local/stdlib/_atoi64.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_atoi64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __INT64_TYPE__ __NOTHROW_NCX(__LIBCCALL _atoi64)(char const *__restrict __nptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_atoi64))(__nptr); })
#endif /* !... */
#ifdef __CRT_HAVE__atoi64_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_atoi64_l,(char const *__restrict __nptr, __locale_t __locale),(__nptr,__locale))
#elif defined(__CRT_HAVE__atoi_l) && __SIZEOF_INT__ == 8
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_atoi64_l,(char const *__restrict __nptr, __locale_t __locale),_atoi_l,(__nptr,__locale))
#elif defined(__CRT_HAVE__atol_l) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_atoi64_l,(char const *__restrict __nptr, __locale_t __locale),_atol_l,(__nptr,__locale))
#elif defined(__CRT_HAVE__atoll_l) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_atoi64_l,(char const *__restrict __nptr, __locale_t __locale),_atoll_l,(__nptr,__locale))
#else /* ... */
#include <libc/local/stdlib/_atoi64_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_atoi64_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __INT64_TYPE__ __NOTHROW_NCX(__LIBCCALL _atoi64_l)(char const *__restrict __nptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_atoi64_l))(__nptr, __locale); })
#endif /* !... */
#endif /* __UINT64_TYPE__ */
#ifdef __CRT_HAVE__mbstrlen
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,_mbstrlen,(char const *__str),(__str))
#else /* __CRT_HAVE__mbstrlen */
#include <libc/local/stdlib/_mbstrlen.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_mbstrlen, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL _mbstrlen)(char const *__str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_mbstrlen))(__str); })
#endif /* !__CRT_HAVE__mbstrlen */
#ifdef __CRT_HAVE__mbstrnlen
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,_mbstrnlen,(char const *__str, __SIZE_TYPE__ __maxlen),(__str,__maxlen))
#else /* __CRT_HAVE__mbstrnlen */
#include <libc/local/stdlib/_mbstrnlen.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_mbstrnlen, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL _mbstrnlen)(char const *__str, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_mbstrnlen))(__str, __maxlen); })
#endif /* !__CRT_HAVE__mbstrnlen */
#ifdef __CRT_HAVE__mbstrlen_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,_mbstrlen_l,(char const *__str, __locale_t __locale),(__str,__locale))
#else /* __CRT_HAVE__mbstrlen_l */
#include <libc/local/stdlib/_mbstrlen_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_mbstrlen_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL _mbstrlen_l)(char const *__str, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_mbstrlen_l))(__str, __locale); })
#endif /* !__CRT_HAVE__mbstrlen_l */
#ifdef __CRT_HAVE__mbstrnlen_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,_mbstrnlen_l,(char const *__str, __SIZE_TYPE__ __maxlen, __locale_t __locale),(__str,__maxlen,__locale))
#else /* __CRT_HAVE__mbstrnlen_l */
#include <libc/local/stdlib/_mbstrnlen_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_mbstrnlen_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL _mbstrnlen_l)(char const *__str, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_mbstrnlen_l))(__str, __maxlen, __locale); })
#endif /* !__CRT_HAVE__mbstrnlen_l */
#ifdef __CRT_HAVE__mblen_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,_mblen_l,(char const *__str, __SIZE_TYPE__ __maxlen, __locale_t __locale),(__str,__maxlen,__locale))
#else /* __CRT_HAVE__mblen_l */
#include <libc/local/stdlib/_mblen_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_mblen_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL _mblen_l)(char const *__str, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_mblen_l))(__str, __maxlen, __locale); })
#endif /* !__CRT_HAVE__mblen_l */
#ifdef __CRT_HAVE__mbtowc_l
__CDECLARE(,int,__NOTHROW_NCX,_mbtowc_l,(wchar_t *__dst, char const *__src, __SIZE_TYPE__ __srclen, __locale_t __locale),(__dst,__src,__srclen,__locale))
#else /* __CRT_HAVE__mbtowc_l */
#include <libc/local/stdlib/_mbtowc_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_mbtowc_l, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_NCX(__LIBCCALL _mbtowc_l)(wchar_t *__dst, char const *__src, __SIZE_TYPE__ __srclen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_mbtowc_l))(__dst, __src, __srclen, __locale); })
#endif /* !__CRT_HAVE__mbtowc_l */
#ifdef __CRT_HAVE__mbstowcs_l
__CDECLARE(,__SIZE_TYPE__,__NOTHROW_NCX,_mbstowcs_l,(wchar_t *__dst, char const *__src, __SIZE_TYPE__ __dstlen, __locale_t __locale),(__dst,__src,__dstlen,__locale))
#else /* __CRT_HAVE__mbstowcs_l */
#include <libc/local/stdlib/_mbstowcs_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_mbstowcs_l, __FORCELOCAL __ATTR_ARTIFICIAL __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL _mbstowcs_l)(wchar_t *__dst, char const *__src, __SIZE_TYPE__ __dstlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_mbstowcs_l))(__dst, __src, __dstlen, __locale); })
#endif /* !__CRT_HAVE__mbstowcs_l */
#ifdef __CRT_HAVE__mbstowcs_s
__CDECLARE(,errno_t,__NOTHROW_NCX,_mbstowcs_s,(__SIZE_TYPE__ *__presult, wchar_t *__dst, __SIZE_TYPE__ __dstsize, char const *__src, __SIZE_TYPE__ __dstlen),(__presult,__dst,__dstsize,__src,__dstlen))
#else /* __CRT_HAVE__mbstowcs_s */
#include <libc/local/stdlib/_mbstowcs_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_mbstowcs_s, __FORCELOCAL __ATTR_ARTIFICIAL errno_t __NOTHROW_NCX(__LIBCCALL _mbstowcs_s)(__SIZE_TYPE__ *__presult, wchar_t *__dst, __SIZE_TYPE__ __dstsize, char const *__src, __SIZE_TYPE__ __dstlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_mbstowcs_s))(__presult, __dst, __dstsize, __src, __dstlen); })
#endif /* !__CRT_HAVE__mbstowcs_s */
#ifdef __CRT_HAVE_mbstowcs_s
__CDECLARE(,errno_t,__NOTHROW_NCX,mbstowcs_s,(__SIZE_TYPE__ *__presult, wchar_t *__dst, __SIZE_TYPE__ __dstsize, char const *__src, __SIZE_TYPE__ __dstlen),(__presult,__dst,__dstsize,__src,__dstlen))
#else /* __CRT_HAVE_mbstowcs_s */
#include <libc/local/stdlib/mbstowcs_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(mbstowcs_s, __FORCELOCAL __ATTR_ARTIFICIAL errno_t __NOTHROW_NCX(__LIBCCALL mbstowcs_s)(__SIZE_TYPE__ *__presult, wchar_t *__dst, __SIZE_TYPE__ __dstsize, char const *__src, __SIZE_TYPE__ __dstlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mbstowcs_s))(__presult, __dst, __dstsize, __src, __dstlen); })
#endif /* !__CRT_HAVE_mbstowcs_s */
#ifdef __CRT_HAVE__mbstowcs_s_l
__CDECLARE(,errno_t,__NOTHROW_NCX,_mbstowcs_s_l,(__SIZE_TYPE__ *__presult, wchar_t *__dst, __SIZE_TYPE__ __dstsize, char const *__src, __SIZE_TYPE__ __dstlen, __locale_t __locale),(__presult,__dst,__dstsize,__src,__dstlen,__locale))
#else /* __CRT_HAVE__mbstowcs_s_l */
#include <libc/local/stdlib/_mbstowcs_s_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_mbstowcs_s_l, __FORCELOCAL __ATTR_ARTIFICIAL errno_t __NOTHROW_NCX(__LIBCCALL _mbstowcs_s_l)(__SIZE_TYPE__ *__presult, wchar_t *__dst, __SIZE_TYPE__ __dstsize, char const *__src, __SIZE_TYPE__ __dstlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_mbstowcs_s_l))(__presult, __dst, __dstsize, __src, __dstlen, __locale); })
#endif /* !__CRT_HAVE__mbstowcs_s_l */
#ifdef __CRT_HAVE_rand_s
__CDECLARE(__ATTR_NONNULL((1)),errno_t,__NOTHROW_NCX,rand_s,(unsigned int *__restrict __randval),(__randval))
#else /* __CRT_HAVE_rand_s */
#include <libc/local/stdlib/rand_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(rand_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) errno_t __NOTHROW_NCX(__LIBCCALL rand_s)(unsigned int *__restrict __randval) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rand_s))(__randval); })
#endif /* !__CRT_HAVE_rand_s */
#ifdef __CRT_HAVE_strtol_l
__CREDIRECT(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,_strtol_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtol_l)
__CDECLARE(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,_strtol_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___strtol_l)
__CREDIRECT(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,_strtol_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__strtol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtoll_l) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,_strtol_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoll_l) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,_strtol_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_strtoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___strtoll_l) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,_strtol_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__strtoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtoq_l) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,_strtol_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtoq_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strto32_l) && __SIZEOF_LONG__ == 4
__CREDIRECT(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,_strtol_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strto32_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strto64_l) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,_strtol_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strto64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtoimax_l) && __SIZEOF_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,_strtol_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoimax_l) && __SIZEOF_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,_strtol_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_strtoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___strtoimax_l) && __SIZEOF_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,_strtol_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__strtoimax_l,(__nptr,__endptr,__base,__locale))
#elif __SIZEOF_LONG__ == 4
#include <libc/local/stdlib/strto32_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) long __NOTHROW_NCX(__LIBCCALL _strtol_l)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (long)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strto32_l))(__nptr, __endptr, __base, __locale); }
#elif __SIZEOF_LONG__ == 8
#include <libc/local/stdlib/strto64_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) long __NOTHROW_NCX(__LIBCCALL _strtol_l)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (long)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strto64_l))(__nptr, __endptr, __base, __locale); }
#else /* ... */
#include <libc/local/stdlib/strtol_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) long __NOTHROW_NCX(__LIBCCALL _strtol_l)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtol_l))(__nptr, __endptr, __base, __locale); }
#endif /* !... */
#ifdef __CRT_HAVE_strtoul_l
__CREDIRECT(__ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,_strtoul_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoul_l)
__CDECLARE(__ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,_strtoul_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___strtoul_l)
__CREDIRECT(__ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,_strtoul_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__strtoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtoull_l) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,_strtoul_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoull_l) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,_strtoul_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_strtoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___strtoull_l) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,_strtoul_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__strtoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtouq_l) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,_strtoul_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtouq_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtou32_l) && __SIZEOF_LONG__ == 4
__CREDIRECT(__ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,_strtoul_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtou32_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtou64_l) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,_strtoul_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtou64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtoumax_l) && __SIZEOF_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,_strtoul_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoumax_l) && __SIZEOF_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,_strtoul_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_strtoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___strtoumax_l) && __SIZEOF_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,_strtoul_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__strtoumax_l,(__nptr,__endptr,__base,__locale))
#elif __SIZEOF_LONG__ == 4
#include <libc/local/stdlib/strtou32_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) unsigned long __NOTHROW_NCX(__LIBCCALL _strtoul_l)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (unsigned long)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtou32_l))(__nptr, __endptr, __base, __locale); }
#elif __SIZEOF_LONG__ == 8
#include <libc/local/stdlib/strtou64_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) unsigned long __NOTHROW_NCX(__LIBCCALL _strtoul_l)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (unsigned long)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtou64_l))(__nptr, __endptr, __base, __locale); }
#else /* ... */
#include <libc/local/stdlib/strtoul_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) unsigned long __NOTHROW_NCX(__LIBCCALL _strtoul_l)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtoul_l))(__nptr, __endptr, __base, __locale); }
#endif /* !... */
#ifdef __CRT_HAVE_strtoll_l
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,_strtoll_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoll_l)
__CDECLARE(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,_strtoll_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___strtoll_l)
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,_strtoll_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__strtoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtol_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,_strtoll_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtol_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,_strtoll_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_strtol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___strtol_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,_strtoll_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__strtol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strto64_l) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,_strtoll_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strto64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strto32_l) && __SIZEOF_LONG_LONG__ == 4
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,_strtoll_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strto32_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtoimax_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,_strtoll_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoimax_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,_strtoll_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_strtoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___strtoimax_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,_strtoll_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__strtoimax_l,(__nptr,__endptr,__base,__locale))
#elif __SIZEOF_LONG_LONG__ == 4
#include <libc/local/stdlib/strto64_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __LONGLONG __NOTHROW_NCX(__LIBCCALL _strtoll_l)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__LONGLONG)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strto64_l))(__nptr, __endptr, __base, __locale); }
#elif __SIZEOF_LONG_LONG__ == 8
#include <libc/local/stdlib/strto32_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __LONGLONG __NOTHROW_NCX(__LIBCCALL _strtoll_l)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__LONGLONG)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strto32_l))(__nptr, __endptr, __base, __locale); }
#else /* ... */
#include <libc/local/stdlib/strtoll_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __LONGLONG __NOTHROW_NCX(__LIBCCALL _strtoll_l)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtoll_l))(__nptr, __endptr, __base, __locale); }
#endif /* !... */
#ifdef __CRT_HAVE_strtoull_l
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,_strtoull_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoull_l)
__CDECLARE(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,_strtoull_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___strtoull_l)
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,_strtoull_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__strtoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtoul_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,_strtoull_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoul_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,_strtoull_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_strtoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___strtoul_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,_strtoull_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__strtoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtou64_l) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,_strtoull_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtou64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtou32_l) && __SIZEOF_LONG_LONG__ == 4
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,_strtoull_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtou32_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtoumax_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,_strtoull_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoumax_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,_strtoull_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_strtoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___strtoumax_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,_strtoull_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__strtoumax_l,(__nptr,__endptr,__base,__locale))
#elif __SIZEOF_LONG_LONG__ == 4
#include <libc/local/stdlib/strtou64_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __ULONGLONG __NOTHROW_NCX(__LIBCCALL _strtoull_l)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__ULONGLONG)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtou64_l))(__nptr, __endptr, __base, __locale); }
#elif __SIZEOF_LONG_LONG__ == 8
#include <libc/local/stdlib/strtou32_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __ULONGLONG __NOTHROW_NCX(__LIBCCALL _strtoull_l)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__ULONGLONG)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtou32_l))(__nptr, __endptr, __base, __locale); }
#else /* ... */
#include <libc/local/stdlib/strtoull_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __ULONGLONG __NOTHROW_NCX(__LIBCCALL _strtoull_l)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtoull_l))(__nptr, __endptr, __base, __locale); }
#endif /* !... */
#ifndef __NO_FPU
#ifdef __CRT_HAVE_strtod_l
__CREDIRECT(__ATTR_NONNULL((1)),double,__NOTHROW_NCX,_strtod_l,(char const *__restrict __nptr, char **__endptr, __locale_t __locale),strtod_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE__strtod_l)
__CDECLARE(__ATTR_NONNULL((1)),double,__NOTHROW_NCX,_strtod_l,(char const *__restrict __nptr, char **__endptr, __locale_t __locale),(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE___strtod_l)
__CREDIRECT(__ATTR_NONNULL((1)),double,__NOTHROW_NCX,_strtod_l,(char const *__restrict __nptr, char **__endptr, __locale_t __locale),__strtod_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE_strtold_l) && __SIZEOF_LONG_DOUBLE__ == __SIZEOF_DOUBLE__
__CREDIRECT(__ATTR_NONNULL((1)),double,__NOTHROW_NCX,_strtod_l,(char const *__restrict __nptr, char **__endptr, __locale_t __locale),strtold_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE__strtold_l) && __SIZEOF_LONG_DOUBLE__ == __SIZEOF_DOUBLE__
__CREDIRECT(__ATTR_NONNULL((1)),double,__NOTHROW_NCX,_strtod_l,(char const *__restrict __nptr, char **__endptr, __locale_t __locale),_strtold_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE___strtold_l) && __SIZEOF_LONG_DOUBLE__ == __SIZEOF_DOUBLE__
__CREDIRECT(__ATTR_NONNULL((1)),double,__NOTHROW_NCX,_strtod_l,(char const *__restrict __nptr, char **__endptr, __locale_t __locale),__strtold_l,(__nptr,__endptr,__locale))
#else /* ... */
#include <libc/local/stdlib/strtod_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) double __NOTHROW_NCX(__LIBCCALL _strtod_l)(char const *__restrict __nptr, char **__endptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtod_l))(__nptr, __endptr, __locale); }
#endif /* !... */
#ifdef __CRT_HAVE_strtof_l
__CREDIRECT(__ATTR_NONNULL((1)),float,__NOTHROW_NCX,_strtof_l,(char const *__restrict __nptr, char **__endptr, __locale_t __locale),strtof_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE__strtof_l)
__CDECLARE(__ATTR_NONNULL((1)),float,__NOTHROW_NCX,_strtof_l,(char const *__restrict __nptr, char **__endptr, __locale_t __locale),(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE___strtof_l)
__CREDIRECT(__ATTR_NONNULL((1)),float,__NOTHROW_NCX,_strtof_l,(char const *__restrict __nptr, char **__endptr, __locale_t __locale),__strtof_l,(__nptr,__endptr,__locale))
#else /* ... */
#include <libc/local/stdlib/strtof_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) float __NOTHROW_NCX(__LIBCCALL _strtof_l)(char const *__restrict __nptr, char **__endptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtof_l))(__nptr, __endptr, __locale); }
#endif /* !... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#ifdef __CRT_HAVE_strtold_l
__CREDIRECT(__ATTR_NONNULL((1)),__LONGDOUBLE,__NOTHROW_NCX,_strtold_l,(char const *__restrict __nptr, char **__endptr, __locale_t __locale),strtold_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE__strtold_l)
__CDECLARE(__ATTR_NONNULL((1)),__LONGDOUBLE,__NOTHROW_NCX,_strtold_l,(char const *__restrict __nptr, char **__endptr, __locale_t __locale),(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE___strtold_l)
__CREDIRECT(__ATTR_NONNULL((1)),__LONGDOUBLE,__NOTHROW_NCX,_strtold_l,(char const *__restrict __nptr, char **__endptr, __locale_t __locale),__strtold_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE_strtod_l) && __SIZEOF_LONG_DOUBLE__ == __SIZEOF_DOUBLE__
__CREDIRECT(__ATTR_NONNULL((1)),__LONGDOUBLE,__NOTHROW_NCX,_strtold_l,(char const *__restrict __nptr, char **__endptr, __locale_t __locale),strtod_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE__strtod_l) && __SIZEOF_LONG_DOUBLE__ == __SIZEOF_DOUBLE__
__CREDIRECT(__ATTR_NONNULL((1)),__LONGDOUBLE,__NOTHROW_NCX,_strtold_l,(char const *__restrict __nptr, char **__endptr, __locale_t __locale),_strtod_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE___strtod_l) && __SIZEOF_LONG_DOUBLE__ == __SIZEOF_DOUBLE__
__CREDIRECT(__ATTR_NONNULL((1)),__LONGDOUBLE,__NOTHROW_NCX,_strtold_l,(char const *__restrict __nptr, char **__endptr, __locale_t __locale),__strtod_l,(__nptr,__endptr,__locale))
#else /* ... */
#include <libc/local/stdlib/strtold_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __LONGDOUBLE __NOTHROW_NCX(__LIBCCALL _strtold_l)(char const *__restrict __nptr, char **__endptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtold_l))(__nptr, __endptr, __locale); }
#endif /* !... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__NO_FPU */

#ifndef _CRT_SYSTEM_DEFINED
#define _CRT_SYSTEM_DEFINED 1
#endif /* !_CRT_SYSTEM_DEFINED */

#ifdef __CRT_HAVE__wctomb_l
__CDECLARE(,int,__NOTHROW_NCX,_wctomb_l,(char *__buf, wchar_t __wc, __locale_t __locale),(__buf,__wc,__locale))
#else /* __CRT_HAVE__wctomb_l */
#include <libc/local/stdlib/_wctomb_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wctomb_l, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_NCX(__LIBCCALL _wctomb_l)(char *__buf, wchar_t __wc, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wctomb_l))(__buf, __wc, __locale); })
#endif /* !__CRT_HAVE__wctomb_l */

#ifdef __USE_DOS_SLIB
#ifdef __CRT_HAVE_wctomb_s
__CDECLARE(__ATTR_NONNULL((1, 2)),errno_t,__NOTHROW_NCX,wctomb_s,(int *__presult, char *__buf, rsize_t __buflen, wchar_t __wc),(__presult,__buf,__buflen,__wc))
#else /* __CRT_HAVE_wctomb_s */
#include <libc/local/stdlib/wctomb_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wctomb_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) errno_t __NOTHROW_NCX(__LIBCCALL wctomb_s)(int *__presult, char *__buf, rsize_t __buflen, wchar_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wctomb_s))(__presult, __buf, __buflen, __wc); })
#endif /* !__CRT_HAVE_wctomb_s */
#endif /* __USE_DOS_SLIB */
#ifdef __CRT_HAVE__wctomb_s_l
__CDECLARE(__ATTR_NONNULL((1, 2)),errno_t,__NOTHROW_NCX,_wctomb_s_l,(int *__presult, char *__buf, __SIZE_TYPE__ __buflen, wchar_t __wc, __locale_t __locale),(__presult,__buf,__buflen,__wc,__locale))
#else /* __CRT_HAVE__wctomb_s_l */
#include <libc/local/stdlib/_wctomb_s_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wctomb_s_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) errno_t __NOTHROW_NCX(__LIBCCALL _wctomb_s_l)(int *__presult, char *__buf, __SIZE_TYPE__ __buflen, wchar_t __wc, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wctomb_s_l))(__presult, __buf, __buflen, __wc, __locale); })
#endif /* !__CRT_HAVE__wctomb_s_l */
#ifdef __CRT_HAVE__wcstombs_s_l
__CDECLARE(__ATTR_NONNULL((1, 2, 4)),errno_t,__NOTHROW_NCX,_wcstombs_s_l,(__SIZE_TYPE__ *__presult, char *__buf, __SIZE_TYPE__ __buflen, wchar_t const *__src, __SIZE_TYPE__ __maxlen, __locale_t __locale),(__presult,__buf,__buflen,__src,__maxlen,__locale))
#else /* __CRT_HAVE__wcstombs_s_l */
#include <libc/local/stdlib/_wcstombs_s_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wcstombs_s_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2, 4)) errno_t __NOTHROW_NCX(__LIBCCALL _wcstombs_s_l)(__SIZE_TYPE__ *__presult, char *__buf, __SIZE_TYPE__ __buflen, wchar_t const *__src, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wcstombs_s_l))(__presult, __buf, __buflen, __src, __maxlen, __locale); })
#endif /* !__CRT_HAVE__wcstombs_s_l */
#ifdef __CRT_HAVE__wcstombs_l
__CDECLARE(__ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,_wcstombs_l,(char *__dst, wchar_t const *__src, __SIZE_TYPE__ __maxlen, __locale_t __locale),(__dst,__src,__maxlen,__locale))
#else /* __CRT_HAVE__wcstombs_l */
#include <libc/local/stdlib/_wcstombs_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wcstombs_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL _wcstombs_l)(char *__dst, wchar_t const *__src, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wcstombs_l))(__dst, __src, __maxlen, __locale); })
#endif /* !__CRT_HAVE__wcstombs_l */
#ifdef __CRT_HAVE_wcstombs_s
__CDECLARE(__ATTR_NONNULL((1, 2, 4)),errno_t,__NOTHROW_NCX,wcstombs_s,(__SIZE_TYPE__ *__presult, char *__buf, __SIZE_TYPE__ __buflen, wchar_t const *__src, __SIZE_TYPE__ __maxlen),(__presult,__buf,__buflen,__src,__maxlen))
#else /* __CRT_HAVE_wcstombs_s */
#include <libc/local/stdlib/wcstombs_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstombs_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2, 4)) errno_t __NOTHROW_NCX(__LIBCCALL wcstombs_s)(__SIZE_TYPE__ *__presult, char *__buf, __SIZE_TYPE__ __buflen, wchar_t const *__src, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstombs_s))(__presult, __buf, __buflen, __src, __maxlen); })
#endif /* !__CRT_HAVE_wcstombs_s */

#define _CVTBUFSIZE   349
#ifdef __CRT_HAVE__fullpath
/* >> _fullpath(3)
 * s.a. `realpath(3)', `frealpathat(3)' */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((2)),char *,__NOTHROW_RPC,_fullpath,(char *__buf, char const *__path, __SIZE_TYPE__ __buflen),(__buf,__path,__buflen))
#else /* __CRT_HAVE__fullpath */
#include <asm/os/fcntl.h>
#if defined(__AT_FDCWD) && defined(__CRT_HAVE_frealpathat)
#include <libc/local/stdlib/_fullpath.h>
/* >> _fullpath(3)
 * s.a. `realpath(3)', `frealpathat(3)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(_fullpath, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((2)) char *__NOTHROW_RPC(__LIBCCALL _fullpath)(char *__buf, char const *__path, __SIZE_TYPE__ __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_fullpath))(__buf, __path, __buflen); })
#endif /* __AT_FDCWD && __CRT_HAVE_frealpathat */
#endif /* !__CRT_HAVE__fullpath */
#ifndef __NO_FPU
#ifdef __CRT_HAVE__ecvt_s
__CDECLARE(__ATTR_NONNULL((1, 5, 6)),errno_t,__NOTHROW_NCX,_ecvt_s,(char *__buf, __SIZE_TYPE__ __buflen, double __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign),(__buf,__buflen,__val,__ndigit,__decptr,__sign))
#else /* __CRT_HAVE__ecvt_s */
#include <libc/local/stdlib/_ecvt_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_ecvt_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 5, 6)) errno_t __NOTHROW_NCX(__LIBCCALL _ecvt_s)(char *__buf, __SIZE_TYPE__ __buflen, double __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_ecvt_s))(__buf, __buflen, __val, __ndigit, __decptr, __sign); })
#endif /* !__CRT_HAVE__ecvt_s */
#ifdef __CRT_HAVE__fcvt_s
__CDECLARE(__ATTR_NONNULL((1, 5, 6)),errno_t,__NOTHROW_NCX,_fcvt_s,(char *__buf, __SIZE_TYPE__ __buflen, double __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign),(__buf,__buflen,__val,__ndigit,__decptr,__sign))
#else /* __CRT_HAVE__fcvt_s */
#include <libc/local/stdlib/_fcvt_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_fcvt_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 5, 6)) errno_t __NOTHROW_NCX(__LIBCCALL _fcvt_s)(char *__buf, __SIZE_TYPE__ __buflen, double __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_fcvt_s))(__buf, __buflen, __val, __ndigit, __decptr, __sign); })
#endif /* !__CRT_HAVE__fcvt_s */
#ifdef __CRT_HAVE__gcvt_s
__CDECLARE(__ATTR_NONNULL((1)),errno_t,__NOTHROW_NCX,_gcvt_s,(char *__buf, __SIZE_TYPE__ __buflen, double __val, int __ndigit),(__buf,__buflen,__val,__ndigit))
#else /* __CRT_HAVE__gcvt_s */
#include <libc/local/stdlib/_gcvt_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_gcvt_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) errno_t __NOTHROW_NCX(__LIBCCALL _gcvt_s)(char *__buf, __SIZE_TYPE__ __buflen, double __val, int __ndigit) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_gcvt_s))(__buf, __buflen, __val, __ndigit); })
#endif /* !__CRT_HAVE__gcvt_s */
#ifdef __CRT_HAVE_ecvt
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((3, 4)),char *,__NOTHROW_NCX,_ecvt,(double __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign),ecvt,(__val,__ndigit,__decptr,__sign))
#elif defined(__CRT_HAVE__ecvt)
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((3, 4)),char *,__NOTHROW_NCX,_ecvt,(double __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign),(__val,__ndigit,__decptr,__sign))
#else /* ... */
#include <libc/local/stdlib/ecvt.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((3, 4)) char *__NOTHROW_NCX(__LIBCCALL _ecvt)(double __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ecvt))(__val, __ndigit, __decptr, __sign); }
#endif /* !... */
#ifdef __CRT_HAVE_fcvt
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((3, 4)),char *,__NOTHROW_NCX,_fcvt,(double __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign),fcvt,(__val,__ndigit,__decptr,__sign))
#elif defined(__CRT_HAVE__fcvt)
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((3, 4)),char *,__NOTHROW_NCX,_fcvt,(double __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign),(__val,__ndigit,__decptr,__sign))
#else /* ... */
#include <libc/local/stdlib/fcvt.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((3, 4)) char *__NOTHROW_NCX(__LIBCCALL _fcvt)(double __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fcvt))(__val, __ndigit, __decptr, __sign); }
#endif /* !... */
#ifdef __CRT_HAVE_gcvt
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((3)),char *,__NOTHROW_NCX,_gcvt,(double __val, int __ndigit, char *__buf),gcvt,(__val,__ndigit,__buf))
#elif defined(__CRT_HAVE__gcvt)
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((3)),char *,__NOTHROW_NCX,_gcvt,(double __val, int __ndigit, char *__buf),(__val,__ndigit,__buf))
#else /* ... */
#include <libc/local/stdlib/gcvt.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((3)) char *__NOTHROW_NCX(__LIBCCALL _gcvt)(double __val, int __ndigit, char *__buf) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(gcvt))(__val, __ndigit, __buf); }
#endif /* !... */
#ifdef __CRT_HAVE__atoflt
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_atoflt,(float *__restrict __result, char const *__restrict __nptr),(__result,__nptr))
#else /* __CRT_HAVE__atoflt */
#include <libc/local/stdlib/_atoflt.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_atoflt, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _atoflt)(float *__restrict __result, char const *__restrict __nptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_atoflt))(__result, __nptr); })
#endif /* !__CRT_HAVE__atoflt */
#ifdef __CRT_HAVE__atoflt_l
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_atoflt_l,(float *__restrict __result, char const *__restrict __nptr, __locale_t __locale),(__result,__nptr,__locale))
#else /* __CRT_HAVE__atoflt_l */
#include <libc/local/stdlib/_atoflt_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_atoflt_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _atoflt_l)(float *__restrict __result, char const *__restrict __nptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_atoflt_l))(__result, __nptr, __locale); })
#endif /* !__CRT_HAVE__atoflt_l */
#ifdef __CRT_HAVE__atodbl
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_atodbl,(double *__restrict __result, char __KOS_FIXED_CONST *__restrict __nptr),(__result,__nptr))
#elif defined(__CRT_HAVE__atoldbl) && __SIZEOF_DOUBLE__ == __SIZEOF_LONG_DOUBLE__
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_atodbl,(double *__restrict __result, char __KOS_FIXED_CONST *__restrict __nptr),_atoldbl,(__result,__nptr))
#else /* ... */
#include <libc/local/stdlib/_atodbl.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_atodbl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _atodbl)(double *__restrict __result, char __KOS_FIXED_CONST *__restrict __nptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_atodbl))(__result, __nptr); })
#endif /* !... */
#ifdef __CRT_HAVE__atodbl_l
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_atodbl_l,(double *__restrict __result, char __KOS_FIXED_CONST *__restrict __nptr, __locale_t __locale),(__result,__nptr,__locale))
#elif defined(__CRT_HAVE__atoldbl_l) && __SIZEOF_DOUBLE__ == __SIZEOF_LONG_DOUBLE__
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_atodbl_l,(double *__restrict __result, char __KOS_FIXED_CONST *__restrict __nptr, __locale_t __locale),_atoldbl_l,(__result,__nptr,__locale))
#else /* ... */
#include <libc/local/stdlib/_atodbl_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_atodbl_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _atodbl_l)(double *__restrict __result, char __KOS_FIXED_CONST *__restrict __nptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_atodbl_l))(__result, __nptr, __locale); })
#endif /* !... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#ifdef __CRT_HAVE__atoldbl
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_atoldbl,(__LONGDOUBLE *__restrict __result, char __KOS_FIXED_CONST *__restrict __nptr),(__result,__nptr))
#elif defined(__CRT_HAVE__atodbl) && __SIZEOF_DOUBLE__ == __SIZEOF_LONG_DOUBLE__
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_atoldbl,(__LONGDOUBLE *__restrict __result, char __KOS_FIXED_CONST *__restrict __nptr),_atodbl,(__result,__nptr))
#else /* ... */
#include <libc/local/stdlib/_atoldbl.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_atoldbl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _atoldbl)(__LONGDOUBLE *__restrict __result, char __KOS_FIXED_CONST *__restrict __nptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_atoldbl))(__result, __nptr); })
#endif /* !... */
#ifdef __CRT_HAVE__atoldbl_l
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_atoldbl_l,(__LONGDOUBLE *__restrict __result, char __KOS_FIXED_CONST *__restrict __nptr, __locale_t __locale),(__result,__nptr,__locale))
#elif defined(__CRT_HAVE__atodbl_l) && __SIZEOF_DOUBLE__ == __SIZEOF_LONG_DOUBLE__
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_atoldbl_l,(__LONGDOUBLE *__restrict __result, char __KOS_FIXED_CONST *__restrict __nptr, __locale_t __locale),_atodbl_l,(__result,__nptr,__locale))
#else /* ... */
#include <libc/local/stdlib/_atoldbl_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_atoldbl_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _atoldbl_l)(__LONGDOUBLE *__restrict __result, char __KOS_FIXED_CONST *__restrict __nptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_atoldbl_l))(__result, __nptr, __locale); })
#endif /* !... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__NO_FPU */
#ifdef __CRT_HAVE__rotl
__CDECLARE(__ATTR_CONST,unsigned int,__NOTHROW,_rotl,(unsigned int __val, int __shift),(__val,__shift))
#elif defined(__CRT_HAVE__lrotl) && __SIZEOF_INT__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_CONST,unsigned int,__NOTHROW,_rotl,(unsigned int __val, int __shift),_lrotl,(__val,__shift))
#elif defined(__CRT_HAVE__rotl64) && __SIZEOF_INT__ == 8
__CREDIRECT(__ATTR_CONST,unsigned int,__NOTHROW,_rotl,(unsigned int __val, int __shift),_rotl64,(__val,__shift))
#else /* ... */
#include <libc/local/stdlib/_rotl.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_rotl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST unsigned int __NOTHROW(__LIBCCALL _rotl)(unsigned int __val, int __shift) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_rotl))(__val, __shift); })
#endif /* !... */
#ifdef __CRT_HAVE__rotr
__CDECLARE(__ATTR_CONST,unsigned int,__NOTHROW,_rotr,(unsigned int __val, int __shift),(__val,__shift))
#elif defined(__CRT_HAVE__lrotr) && __SIZEOF_INT__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_CONST,unsigned int,__NOTHROW,_rotr,(unsigned int __val, int __shift),_lrotr,(__val,__shift))
#elif defined(__CRT_HAVE__rotr64) && __SIZEOF_INT__ == 8
__CREDIRECT(__ATTR_CONST,unsigned int,__NOTHROW,_rotr,(unsigned int __val, int __shift),_rotr64,(__val,__shift))
#else /* ... */
#include <libc/local/stdlib/_rotr.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_rotr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST unsigned int __NOTHROW(__LIBCCALL _rotr)(unsigned int __val, int __shift) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_rotr))(__val, __shift); })
#endif /* !... */
#ifdef __UINT64_TYPE__
#ifdef __CRT_HAVE__rotl64
__CDECLARE(__ATTR_CONST,__UINT64_TYPE__,__NOTHROW,_rotl64,(__UINT64_TYPE__ __val, int __shift),(__val,__shift))
#elif defined(__CRT_HAVE__lrotl) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_CONST,__UINT64_TYPE__,__NOTHROW,_rotl64,(__UINT64_TYPE__ __val, int __shift),_lrotl,(__val,__shift))
#elif defined(__CRT_HAVE__rotl) && __SIZEOF_INT__ == 8
__CREDIRECT(__ATTR_CONST,__UINT64_TYPE__,__NOTHROW,_rotl64,(__UINT64_TYPE__ __val, int __shift),_rotl,(__val,__shift))
#else /* ... */
#include <libc/local/stdlib/_rotl64.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_rotl64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __UINT64_TYPE__ __NOTHROW(__LIBCCALL _rotl64)(__UINT64_TYPE__ __val, int __shift) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_rotl64))(__val, __shift); })
#endif /* !... */
#ifdef __CRT_HAVE__rotr64
__CDECLARE(__ATTR_CONST,__UINT64_TYPE__,__NOTHROW,_rotr64,(__UINT64_TYPE__ __val, int __shift),(__val,__shift))
#elif defined(__CRT_HAVE__lrotr) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_CONST,__UINT64_TYPE__,__NOTHROW,_rotr64,(__UINT64_TYPE__ __val, int __shift),_lrotr,(__val,__shift))
#elif defined(__CRT_HAVE__rotr) && __SIZEOF_INT__ == 8
__CREDIRECT(__ATTR_CONST,__UINT64_TYPE__,__NOTHROW,_rotr64,(__UINT64_TYPE__ __val, int __shift),_rotr,(__val,__shift))
#else /* ... */
#include <libc/local/stdlib/_rotr64.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_rotr64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __UINT64_TYPE__ __NOTHROW(__LIBCCALL _rotr64)(__UINT64_TYPE__ __val, int __shift) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_rotr64))(__val, __shift); })
#endif /* !... */
#endif /* __UINT64_TYPE__ */
#ifdef __CRT_HAVE__lrotl
__CDECLARE(__ATTR_CONST,unsigned long,__NOTHROW,_lrotl,(unsigned long __val, int __shift),(__val,__shift))
#elif defined(__CRT_HAVE__rotl) && __SIZEOF_LONG__ == __SIZEOF_INT__
__CREDIRECT(__ATTR_CONST,unsigned long,__NOTHROW,_lrotl,(unsigned long __val, int __shift),_rotl,(__val,__shift))
#elif defined(__CRT_HAVE__rotl64) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_CONST,unsigned long,__NOTHROW,_lrotl,(unsigned long __val, int __shift),_rotl64,(__val,__shift))
#else /* ... */
#include <libc/local/stdlib/_lrotl.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_lrotl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST unsigned long __NOTHROW(__LIBCCALL _lrotl)(unsigned long __val, int __shift) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_lrotl))(__val, __shift); })
#endif /* !... */
#ifdef __CRT_HAVE__lrotr
__CDECLARE(__ATTR_CONST,unsigned long,__NOTHROW,_lrotr,(unsigned long __val, int __shift),(__val,__shift))
#elif defined(__CRT_HAVE__rotr) && __SIZEOF_LONG__ == __SIZEOF_INT__
__CREDIRECT(__ATTR_CONST,unsigned long,__NOTHROW,_lrotr,(unsigned long __val, int __shift),_rotr,(__val,__shift))
#elif defined(__CRT_HAVE__rotr64) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_CONST,unsigned long,__NOTHROW,_lrotr,(unsigned long __val, int __shift),_rotr64,(__val,__shift))
#else /* ... */
#include <libc/local/stdlib/_lrotr.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_lrotr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST unsigned long __NOTHROW(__LIBCCALL _lrotr)(unsigned long __val, int __shift) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_lrotr))(__val, __shift); })
#endif /* !... */

#ifndef _CRT_PERROR_DEFINED
#define _CRT_PERROR_DEFINED 1
#ifndef __perror_defined
#define __perror_defined
#ifdef __std_perror_defined
/* >> perror(3)
 * Print a given `message' alongside `strerror(errno)' to stderr:
 * >> if (message) {
 * >>     fprintf(stderr, "%s: %s\n", message, strerror(errno));
 * >> } else {
 * >>     fprintf(stderr, "%s\n", strerror(errno));
 * >> } */
__NAMESPACE_STD_USING(perror)
#elif defined(__CRT_HAVE_perror)
/* >> perror(3)
 * Print a given `message' alongside `strerror(errno)' to stderr:
 * >> if (message) {
 * >>     fprintf(stderr, "%s: %s\n", message, strerror(errno));
 * >> } else {
 * >>     fprintf(stderr, "%s\n", strerror(errno));
 * >> } */
__CDECLARE_VOID(,__NOTHROW_RPC,perror,(char const *__message),(__message))
#elif defined(__CRT_HAVE__IO_perror)
/* >> perror(3)
 * Print a given `message' alongside `strerror(errno)' to stderr:
 * >> if (message) {
 * >>     fprintf(stderr, "%s: %s\n", message, strerror(errno));
 * >> } else {
 * >>     fprintf(stderr, "%s\n", strerror(errno));
 * >> } */
__CREDIRECT_VOID(,__NOTHROW_RPC,perror,(char const *__message),_IO_perror,(__message))
#else /* ... */
#include <libc/template/stdstreams.h>
#include <libc/errno.h>
#if defined(__LOCAL_stderr) && defined(__libc_geterrno) && (defined(__CRT_HAVE_fprintf) || defined(__CRT_HAVE__IO_fprintf) || defined(__CRT_HAVE_fprintf_s) || defined(__CRT_HAVE_fprintf_unlocked) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock))
#include <libc/local/stdio/perror.h>
/* >> perror(3)
 * Print a given `message' alongside `strerror(errno)' to stderr:
 * >> if (message) {
 * >>     fprintf(stderr, "%s: %s\n", message, strerror(errno));
 * >> } else {
 * >>     fprintf(stderr, "%s\n", strerror(errno));
 * >> } */
__NAMESPACE_LOCAL_USING_OR_IMPL(perror, __FORCELOCAL __ATTR_ARTIFICIAL void __NOTHROW_RPC(__LIBCCALL perror)(char const *__message) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(perror))(__message); })
#else /* __LOCAL_stderr && __libc_geterrno && (__CRT_HAVE_fprintf || __CRT_HAVE__IO_fprintf || __CRT_HAVE_fprintf_s || __CRT_HAVE_fprintf_unlocked || __CRT_HAVE_vfprintf || __CRT_HAVE_vfprintf_s || __CRT_HAVE__IO_vfprintf || __CRT_HAVE_vfprintf_unlocked || __CRT_HAVE_file_printer || __CRT_HAVE_file_printer_unlocked || __CRT_HAVE_putc || __CRT_HAVE_fputc || __CRT_HAVE__IO_putc || __CRT_HAVE_putc_unlocked || __CRT_HAVE_fputc_unlocked || __CRT_HAVE__putc_nolock || __CRT_HAVE__fputc_nolock || (__CRT_DOS && (__CRT_HAVE__flsbuf || __CRT_HAVE___swbuf)) || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock) */
#undef __perror_defined
#endif /* !__LOCAL_stderr || !__libc_geterrno || (!__CRT_HAVE_fprintf && !__CRT_HAVE__IO_fprintf && !__CRT_HAVE_fprintf_s && !__CRT_HAVE_fprintf_unlocked && !__CRT_HAVE_vfprintf && !__CRT_HAVE_vfprintf_s && !__CRT_HAVE__IO_vfprintf && !__CRT_HAVE_vfprintf_unlocked && !__CRT_HAVE_file_printer && !__CRT_HAVE_file_printer_unlocked && !__CRT_HAVE_putc && !__CRT_HAVE_fputc && !__CRT_HAVE__IO_putc && !__CRT_HAVE_putc_unlocked && !__CRT_HAVE_fputc_unlocked && !__CRT_HAVE__putc_nolock && !__CRT_HAVE__fputc_nolock && (!__CRT_DOS || (!__CRT_HAVE__flsbuf && !__CRT_HAVE___swbuf)) && !__CRT_HAVE_fwrite && !__CRT_HAVE__IO_fwrite && !__CRT_HAVE_fwrite_s && !__CRT_HAVE_fwrite_unlocked && !__CRT_HAVE__fwrite_nolock) */
#endif /* !... */
#endif /* !__perror_defined */
#endif  /* _CRT_PERROR_DEFINED */

#ifdef __CRT_HAVE_putenv
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,_putenv,(char *__string),putenv,(__string))
#elif defined(__CRT_HAVE__putenv)
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,_putenv,(char *__string),(__string))
#endif /* ... */
#ifdef __CRT_HAVE_swab
/* >> swab(3)
 * Copy `n_bytes & ~1' (FLOOR_ALIGN(n_bytes, 2)) from `from' to `to',
 * exchanging the order of even and odd bytes ("123456" --> "214365")
 * When `n_bytes <= 1', don't do anything and return immediately */
__CREDIRECT_VOID(__ATTR_NONNULL((1, 2)),__NOTHROW_NCX,_swab,(void const *__restrict __from, void *__restrict __to, __STDC_INT_AS_SSIZE_T __n_bytes),swab,(__from,__to,__n_bytes))
#elif defined(__CRT_HAVE__swab)
/* >> swab(3)
 * Copy `n_bytes & ~1' (FLOOR_ALIGN(n_bytes, 2)) from `from' to `to',
 * exchanging the order of even and odd bytes ("123456" --> "214365")
 * When `n_bytes <= 1', don't do anything and return immediately */
__CDECLARE_VOID(__ATTR_NONNULL((1, 2)),__NOTHROW_NCX,_swab,(void const *__restrict __from, void *__restrict __to, __STDC_INT_AS_SSIZE_T __n_bytes),(__from,__to,__n_bytes))
#else /* ... */
#include <libc/local/unistd/swab.h>
/* >> swab(3)
 * Copy `n_bytes & ~1' (FLOOR_ALIGN(n_bytes, 2)) from `from' to `to',
 * exchanging the order of even and odd bytes ("123456" --> "214365")
 * When `n_bytes <= 1', don't do anything and return immediately */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) void __NOTHROW_NCX(__LIBCCALL _swab)(void const *__restrict __from, void *__restrict __to, __STDC_INT_AS_SSIZE_T __n_bytes) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(swab))(__from, __to, __n_bytes); }
#endif /* !... */
#ifdef __CRT_HAVE__putenv_s
__CDECLARE(,errno_t,__NOTHROW_NCX,_putenv_s,(char const *__varname, char const *__val),(__varname,__val))
#elif defined(__CRT_HAVE_setenv)
#include <libc/local/stdlib/_putenv_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_putenv_s, __FORCELOCAL __ATTR_ARTIFICIAL errno_t __NOTHROW_NCX(__LIBCCALL _putenv_s)(char const *__varname, char const *__val) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_putenv_s))(__varname, __val); })
#endif /* ... */
#ifdef __CRT_HAVE__searchenv
__CDECLARE_VOID(__ATTR_NONNULL((1, 2, 3)),__NOTHROW_RPC,_searchenv,(char const *__file, char const *__envvar, char *__restrict __resultpath),(__file,__envvar,__resultpath))
#elif defined(__CRT_HAVE__searchenv_s)
#include <libc/local/stdlib/_searchenv.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_searchenv, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2, 3)) void __NOTHROW_RPC(__LIBCCALL _searchenv)(char const *__file, char const *__envvar, char *__restrict __resultpath) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_searchenv))(__file, __envvar, __resultpath); })
#endif /* ... */
__CDECLARE_OPT(__ATTR_NONNULL((1, 2, 3)),errno_t,__NOTHROW_RPC,_searchenv_s,(char const *__file, char const *__envvar, char *__restrict __resultpath, __SIZE_TYPE__ __buflen),(__file,__envvar,__resultpath,__buflen))
#ifdef __CRT_HAVE__makepath
__CDECLARE_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,_makepath,(char *__restrict __buf, char const *__drive, char const *__dir, char const *__file, char const *__ext),(__buf,__drive,__dir,__file,__ext))
#else /* __CRT_HAVE__makepath */
#include <libc/local/stdlib/_makepath.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_makepath, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) void __NOTHROW_NCX(__LIBCCALL _makepath)(char *__restrict __buf, char const *__drive, char const *__dir, char const *__file, char const *__ext) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_makepath))(__buf, __drive, __dir, __file, __ext); })
#endif /* !__CRT_HAVE__makepath */
#ifdef __CRT_HAVE__splitpath
__CDECLARE_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,_splitpath,(char const *__restrict __abspath, char *__drive, char *__dir, char *__file, char *__ext),(__abspath,__drive,__dir,__file,__ext))
#else /* __CRT_HAVE__splitpath */
#include <libc/local/stdlib/_splitpath.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_splitpath, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) void __NOTHROW_NCX(__LIBCCALL _splitpath)(char const *__restrict __abspath, char *__drive, char *__dir, char *__file, char *__ext) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_splitpath))(__abspath, __drive, __dir, __file, __ext); })
#endif /* !__CRT_HAVE__splitpath */
#ifdef __CRT_HAVE__makepath_s
__CDECLARE(__ATTR_NONNULL((1)),errno_t,__NOTHROW_NCX,_makepath_s,(char *__buf, __SIZE_TYPE__ __buflen, char const *__drive, char const *__dir, char const *__file, char const *__ext),(__buf,__buflen,__drive,__dir,__file,__ext))
#else /* __CRT_HAVE__makepath_s */
#include <libc/local/stdlib/_makepath_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_makepath_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) errno_t __NOTHROW_NCX(__LIBCCALL _makepath_s)(char *__buf, __SIZE_TYPE__ __buflen, char const *__drive, char const *__dir, char const *__file, char const *__ext) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_makepath_s))(__buf, __buflen, __drive, __dir, __file, __ext); })
#endif /* !__CRT_HAVE__makepath_s */
#ifdef __CRT_HAVE__splitpath_s
__CDECLARE(__ATTR_NONNULL((1)),errno_t,__NOTHROW_NCX,_splitpath_s,(char const *__restrict __abspath, char *__drive, __SIZE_TYPE__ __drivelen, char *__dir, __SIZE_TYPE__ __dirlen, char *__file, __SIZE_TYPE__ __filelen, char *__ext, __SIZE_TYPE__ __extlen),(__abspath,__drive,__drivelen,__dir,__dirlen,__file,__filelen,__ext,__extlen))
#else /* __CRT_HAVE__splitpath_s */
#include <libc/local/stdlib/_splitpath_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_splitpath_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) errno_t __NOTHROW_NCX(__LIBCCALL _splitpath_s)(char const *__restrict __abspath, char *__drive, __SIZE_TYPE__ __drivelen, char *__dir, __SIZE_TYPE__ __dirlen, char *__file, __SIZE_TYPE__ __filelen, char *__ext, __SIZE_TYPE__ __extlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_splitpath_s))(__abspath, __drive, __drivelen, __dir, __dirlen, __file, __filelen, __ext, __extlen); })
#endif /* !__CRT_HAVE__splitpath_s */
__CDECLARE_VOID_OPT(,__NOTHROW_NCX,_seterrormode,(int __mode),(__mode))
__CDECLARE_OPT(,int,__NOTHROW_NCX,_set_error_mode,(int __mode),(__mode))
__CDECLARE_VOID_OPT(,__NOTHROW_NCX,_beep,(unsigned int __freq, unsigned int __duration),(__freq,__duration))
#ifdef __CRT_HAVE__sleep
/* >> _sleep(3)
 * Sleep for `milli' milliseconds (1/1.000 seconds) */
__CDECLARE_VOID(,__NOTHROW_RPC,_sleep,(__UINT32_TYPE__ __milli),(__milli))
#elif defined(__CRT_HAVE___crtSleep)
/* >> _sleep(3)
 * Sleep for `milli' milliseconds (1/1.000 seconds) */
__CREDIRECT_VOID(,__NOTHROW_RPC,_sleep,(__UINT32_TYPE__ __milli),__crtSleep,(__milli))
#elif defined(__CRT_HAVE_nanosleep64) || defined(__CRT_HAVE_nanosleep) || defined(__CRT_HAVE___nanosleep) || defined(__CRT_HAVE___libc_nanosleep)
#include <libc/local/stdlib/_sleep.h>
/* >> _sleep(3)
 * Sleep for `milli' milliseconds (1/1.000 seconds) */
__NAMESPACE_LOCAL_USING_OR_IMPL(_sleep, __FORCELOCAL __ATTR_ARTIFICIAL void __NOTHROW_RPC(__LIBCCALL _sleep)(__UINT32_TYPE__ __milli) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_sleep))(__milli); })
#endif /* ... */

#ifndef environ
#ifdef __CRT_HAVE_environ
__LIBC char **environ;
#define environ environ
#elif defined(_environ)
#define environ _environ
#elif defined(__environ)
#define environ __environ
#elif defined(__LOCAL_environ)
#define environ __LOCAL_environ
#elif defined(__CRT_HAVE__environ)
#ifdef __NO_ASMNAME
__LIBC char **_environ;
#define _environ _environ
#define environ  _environ
#else /* __NO_ASMNAME */
__LIBC char **environ __CASMNAME("_environ");
#define environ environ
#endif /* !__NO_ASMNAME */
#elif defined(__CRT_HAVE___environ)
#ifdef __NO_ASMNAME
__LIBC char **__environ;
#define __environ _environ
#define environ   __environ
#else /* __NO_ASMNAME */
__LIBC char **environ __CASMNAME("__environ");
#define environ environ
#endif /* !__NO_ASMNAME */
#elif defined(____p__environ_defined)
#define environ (*__p__environ())
#elif defined(__CRT_HAVE___p__environ)
#define ____p__environ_defined
__CDECLARE(__ATTR_WUNUSED __ATTR_CONST __ATTR_RETNONNULL,char ***,__NOTHROW,__p__environ,(void),())
#define environ (*__p__environ())
#elif defined(__CRT_HAVE__get_environ)
#ifndef ___get_environ_defined
#define ___get_environ_defined
__CDECLARE(,int,__NOTHROW,_get_environ,(char ***__p_environ),())
#endif /* !___get_environ_defined */
#ifndef _____get_environ_wrapper_defined
#define _____get_environ_wrapper_defined
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST char **
__NOTHROW(__LIBCCALL ___get_environ_wrapper)(void) {
	char const **__result;
	if __unlikely(_get_environ(&__result) != 0)
		__result = __NULLPTR;
	return __result;
}
#endif /* !_____get_environ_wrapper_defined */
#define environ ___get_environ_wrapper()
#endif /* !... */
#endif /* !environ */

#ifndef __swab_defined
#define __swab_defined
#ifdef __CRT_HAVE_swab
/* >> swab(3)
 * Copy `n_bytes & ~1' (FLOOR_ALIGN(n_bytes, 2)) from `from' to `to',
 * exchanging the order of even and odd bytes ("123456" --> "214365")
 * When `n_bytes <= 1', don't do anything and return immediately */
__CDECLARE_VOID(__ATTR_NONNULL((1, 2)),__NOTHROW_NCX,swab,(void const *__restrict __from, void *__restrict __to, __STDC_INT_AS_SSIZE_T __n_bytes),(__from,__to,__n_bytes))
#elif defined(__CRT_HAVE__swab)
/* >> swab(3)
 * Copy `n_bytes & ~1' (FLOOR_ALIGN(n_bytes, 2)) from `from' to `to',
 * exchanging the order of even and odd bytes ("123456" --> "214365")
 * When `n_bytes <= 1', don't do anything and return immediately */
__CREDIRECT_VOID(__ATTR_NONNULL((1, 2)),__NOTHROW_NCX,swab,(void const *__restrict __from, void *__restrict __to, __STDC_INT_AS_SSIZE_T __n_bytes),_swab,(__from,__to,__n_bytes))
#else /* ... */
#include <libc/local/unistd/swab.h>
/* >> swab(3)
 * Copy `n_bytes & ~1' (FLOOR_ALIGN(n_bytes, 2)) from `from' to `to',
 * exchanging the order of even and odd bytes ("123456" --> "214365")
 * When `n_bytes <= 1', don't do anything and return immediately */
__NAMESPACE_LOCAL_USING_OR_IMPL(swab, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) void __NOTHROW_NCX(__LIBCCALL swab)(void const *__restrict __from, void *__restrict __to, __STDC_INT_AS_SSIZE_T __n_bytes) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(swab))(__from, __to, __n_bytes); })
#endif /* !... */
#endif /* !__swab_defined */



#ifdef __CRT_HAVE_itoa
__CDECLARE(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,itoa,(int __val, char *__buf, int __radix),(__val,__buf,__radix))
#elif defined(__CRT_HAVE__itoa)
__CREDIRECT(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,itoa,(int __val, char *__buf, int __radix),_itoa,(__val,__buf,__radix))
#elif defined(__CRT_HAVE__ltoa) && __SIZEOF_INT__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,itoa,(int __val, char *__buf, int __radix),_ltoa,(__val,__buf,__radix))
#elif defined(__CRT_HAVE_ltoa) && __SIZEOF_INT__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,itoa,(int __val, char *__buf, int __radix),ltoa,(__val,__buf,__radix))
#elif defined(__CRT_HAVE__i64toa) && __SIZEOF_INT__ == 8
__CREDIRECT(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,itoa,(int __val, char *__buf, int __radix),_i64toa,(__val,__buf,__radix))
#else /* ... */
#include <libc/local/stdlib/itoa.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(itoa, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) char *__NOTHROW_NCX(__LIBCCALL itoa)(int __val, char *__buf, int __radix) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(itoa))(__val, __buf, __radix); })
#endif /* !... */
#ifdef __CRT_HAVE_ltoa
__CDECLARE(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,ltoa,(long __val, char *__buf, int __radix),(__val,__buf,__radix))
#elif defined(__CRT_HAVE__ltoa)
__CREDIRECT(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,ltoa,(long __val, char *__buf, int __radix),_ltoa,(__val,__buf,__radix))
#elif defined(__CRT_HAVE_itoa) && __SIZEOF_LONG__ == __SIZEOF_INT__
__CREDIRECT(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,ltoa,(long __val, char *__buf, int __radix),itoa,(__val,__buf,__radix))
#elif defined(__CRT_HAVE__itoa) && __SIZEOF_LONG__ == __SIZEOF_INT__
__CREDIRECT(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,ltoa,(long __val, char *__buf, int __radix),_itoa,(__val,__buf,__radix))
#elif defined(__CRT_HAVE__i64toa) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,ltoa,(long __val, char *__buf, int __radix),_i64toa,(__val,__buf,__radix))
#else /* ... */
#include <libc/local/stdlib/ltoa.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(ltoa, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) char *__NOTHROW_NCX(__LIBCCALL ltoa)(long __val, char *__buf, int __radix) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ltoa))(__val, __buf, __radix); })
#endif /* !... */
#ifdef __CRT_HAVE_ultoa
__CDECLARE(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,ultoa,(unsigned long __val, char *__buf, int __radix),(__val,__buf,__radix))
#elif defined(__CRT_HAVE__ultoa)
__CREDIRECT(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,ultoa,(unsigned long __val, char *__buf, int __radix),_ultoa,(__val,__buf,__radix))
#elif defined(__CRT_HAVE__ui64toa) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,ultoa,(unsigned long __val, char *__buf, int __radix),_ui64toa,(__val,__buf,__radix))
#else /* ... */
#include <libc/local/stdlib/ultoa.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(ultoa, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) char *__NOTHROW_NCX(__LIBCCALL ultoa)(unsigned long __val, char *__buf, int __radix) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ultoa))(__val, __buf, __radix); })
#endif /* !... */
#ifdef __CRT_HAVE_onexit
__CREDIRECT(,onexit_t,__NOTHROW_NCX,_onexit,(onexit_t __func),onexit,(__func))
#elif defined(__CRT_HAVE__onexit)
__CDECLARE(,onexit_t,__NOTHROW_NCX,_onexit,(onexit_t __func),(__func))
#endif /* ... */
#ifdef __CRT_HAVE_onexit
__CDECLARE(,onexit_t,__NOTHROW_NCX,onexit,(onexit_t __func),(__func))
#elif defined(__CRT_HAVE__onexit)
__CREDIRECT(,onexit_t,__NOTHROW_NCX,onexit,(onexit_t __func),_onexit,(__func))
#endif /* ... */

#endif /* __CC__ */
#endif /* __USE_DOS */

__SYSDECL_END

#if defined(__USE_DOS) && !defined(__USE_DOS_CLEAN)
#include <corecrt_malloc.h>  /* Include <malloc.h> instead */
#include <corecrt_search.h>  /* Include <search.h> instead */
#include <corecrt_wstdlib.h> /* Include <wchar.h> instead */
#endif /* __USE_DOS && !__USE_DOS_CLEAN */

#ifdef __USE_UTF
#if defined(_UCHAR_H) && !defined(_PARTS_UCHAR_STDLIB_H)
#include <parts/uchar/stdlib.h>
#endif /* _UCHAR_H && !_PARTS_UCHAR_STDLIB_H */
#endif /* __USE_UTF */

#ifdef __USE_KOS
#if defined(_WCHAR_H) && !defined(_PARTS_WCHAR_STDLIB_H)
#include <parts/wchar/stdlib.h>
#endif /* _WCHAR_H && !_PARTS_WCHAR_STDLIB_H */
#endif /* __USE_KOS */

#ifdef __CXX_SYSTEM_HEADER
#define _CXX_STDONLY_CSTDLIB
#undef _STDLIB_H
#endif /* __CXX_SYSTEM_HEADER */
#endif /* !_CXX_STDONLY_CSTDLIB */
#endif /* !_STDLIB_H */
