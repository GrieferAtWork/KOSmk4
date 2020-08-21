/* HASH CRC-32:0x71fb4d5e */
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
#ifndef _STDLIB_H
#define _STDLIB_H 1

#ifdef _CXX_STDONLY_CSTDLIB
#ifdef __CXX_SYSTEM_HEADER
#undef _STDLIB_H /* Allow the C-header to be re-included to import all std::-symbols into the global namespace. */
#else /* __CXX_SYSTEM_HEADER */
/* Import all symbols into the global namespace when re-including "stdlib.h" after "cstdlib" */
#ifndef __size_t_defined
#define __size_t_defined 1
__NAMESPACE_STD_USING(size_t)
#endif /* !__size_t_defined */
#ifndef __div_t_defined
#define __div_t_defined 1
__NAMESPACE_STD_USING(div_t)
#endif /* !__div_t_defined */
#ifndef __ldiv_t_defined
#define __ldiv_t_defined 1
__NAMESPACE_STD_USING(ldiv_t)
#endif /* !__ldiv_t_defined */
#ifdef __USE_ISOC99
#ifndef __lldiv_t_defined
#define __lldiv_t_defined 1
__NAMESPACE_STD_USING(lldiv_t)
#endif /* !__lldiv_t_defined */
#endif /* __USE_ISOC99 */
__NAMESPACE_STD_USING(qsort)
__NAMESPACE_STD_USING(bsearch)
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
#include <local/environ.h>
#if defined(__CRT_HAVE_getenv) || defined(__LOCAL_environ)
__NAMESPACE_STD_USING(getenv)
#endif /* __CRT_HAVE_getenv || __LOCAL_environ */
__NAMESPACE_STD_USING(mblen)
__NAMESPACE_STD_USING(mbtowc)
__NAMESPACE_STD_USING(wctomb)
__NAMESPACE_STD_USING(mbstowcs)
__NAMESPACE_STD_USING(wcstombs)
#if !defined(__system_defined) && defined(__std_system_defined)
#define __system_defined 1
__NAMESPACE_STD_USING(system)
#endif /* !__system_defined && __std_system_defined */
#if !defined(__abort_defined) && defined(__std_abort_defined)
#define __abort_defined 1
__NAMESPACE_STD_USING(abort)
#endif /* !__abort_defined && __std_abort_defined */
#if !defined(__exit_defined) && defined(__std_exit_defined)
#define __exit_defined 1
__NAMESPACE_STD_USING(exit)
#endif /* !__exit_defined && __std_exit_defined */
#if defined(__CRT_HAVE_atexit) || defined(__CRT_HAVE_at_quick_exit)
__NAMESPACE_STD_USING(atexit)
#endif /* __CRT_HAVE_atexit || __CRT_HAVE_at_quick_exit */
#if defined(__USE_ISOC11) || defined(__USE_ISOCXX11)
#if defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE_exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE__Exit)
__NAMESPACE_STD_USING(quick_exit)
#endif /* __CRT_HAVE_quick_exit || __CRT_HAVE_exit || __CRT_HAVE__exit || __CRT_HAVE__Exit */
#if defined(__CRT_HAVE_at_quick_exit) || defined(__CRT_HAVE_atexit)
__NAMESPACE_STD_USING(at_quick_exit)
#endif /* __CRT_HAVE_at_quick_exit || __CRT_HAVE_atexit */
#endif /* __USE_ISOC11 || __USE_ISOCXX11 */
#ifdef __USE_ISOC99
#if defined(__CRT_HAVE__Exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE_exit)
__NAMESPACE_STD_USING(_Exit)
#endif /* __CRT_HAVE__Exit || __CRT_HAVE__exit || __CRT_HAVE_quick_exit || __CRT_HAVE_exit */
#endif /* __USE_ISOC99 */
#if !defined(__malloc_defined) && defined(__std_malloc_defined)
#define __malloc_defined 1
__NAMESPACE_STD_USING(malloc)
#endif /* !__malloc_defined && __std_malloc_defined */
#if !defined(__calloc_defined) && defined(__std_calloc_defined)
#define __calloc_defined 1
__NAMESPACE_STD_USING(calloc)
#endif /* !__calloc_defined && __std_calloc_defined */
#if !defined(__realloc_defined) && defined(__std_realloc_defined)
#define __realloc_defined 1
__NAMESPACE_STD_USING(realloc)
#endif /* !__realloc_defined && __std_realloc_defined */
#if !defined(__free_defined) && defined(__std_free_defined)
#define __free_defined 1
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
#define __strtoull_defined 1
__NAMESPACE_STD_USING(strtoull)
#endif /* !__strtoull_defined && __std_strtoull_defined */
#if !defined(__strtoll_defined) && defined(__std_strtoll_defined)
#define __strtoll_defined 1
__NAMESPACE_STD_USING(strtoll)
#endif /* !__strtoll_defined && __std_strtoll_defined */
#ifndef __NO_FPU
__NAMESPACE_STD_USING(atof)
__NAMESPACE_STD_USING(strtod)
#if !defined(__strtof_defined) && defined(__std_strtof_defined)
#define __strtof_defined 1
__NAMESPACE_STD_USING(strtof)
#endif /* !__strtof_defined && __std_strtof_defined */
#if !defined(__strtold_defined) && defined(__std_strtold_defined)
#define __strtold_defined 1
__NAMESPACE_STD_USING(strtold)
#endif /* !__strtold_defined && __std_strtold_defined */
#endif /* !__NO_FPU */
#if !defined(__aligned_alloc_defined) && defined(__std_aligned_alloc_defined)
#define __aligned_alloc_defined 1
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
#include <asm/stdlib.h>
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

#if defined(__USE_KOS) && defined(__USE_STRING_OVERLOADS)
#include <hybrid/__overflow.h>
#endif /* __USE_KOS && __USE_STRING_OVERLOADS */

#if defined(__USE_XOPEN) || defined(__USE_XOPEN2K8)
#include <parts/waitmacros.h>
#endif /* __USE_XOPEN || __USE_XOPEN2K8 */

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
#define __std_size_t_defined 1
__NAMESPACE_STD_BEGIN
typedef __SIZE_TYPE__ size_t;
__NAMESPACE_STD_END
#endif /* !__std_size_t_defined */

#ifndef __CXX_SYSTEM_HEADER
#ifndef __size_t_defined
#define __size_t_defined 1
__NAMESPACE_STD_USING(size_t)
#endif /* !__size_t_defined */
#endif /* !__CXX_SYSTEM_HEADER */

#ifndef __wchar_t_defined
#define __wchar_t_defined 1
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
#define __std_div_t_defined 1
typedef struct __div_struct div_t;
#endif /* !__std_div_t_defined */
#ifndef __std_ldiv_t_defined
#define __std_ldiv_t_defined 1
typedef struct __ldiv_struct ldiv_t;
#endif /* !__std_ldiv_t_defined */
#ifdef __USE_ISOC99
#ifndef __std_lldiv_t_defined
#define __std_lldiv_t_defined 1
typedef struct __lldiv_struct lldiv_t;
#endif /* !__std_lldiv_t_defined */
#endif /* __USE_ISOC99 */
__NAMESPACE_STD_END

#ifndef __CXX_SYSTEM_HEADER
#ifndef __div_t_defined
#define __div_t_defined 1
__NAMESPACE_STD_USING(div_t)
#endif /* !__div_t_defined */
#ifndef __ldiv_t_defined
#define __ldiv_t_defined 1
__NAMESPACE_STD_USING(ldiv_t)
#endif /* !__ldiv_t_defined */
#ifdef __USE_ISOC99
#ifndef __lldiv_t_defined
#define __lldiv_t_defined 1
__NAMESPACE_STD_USING(lldiv_t)
#endif /* !__lldiv_t_defined */
#endif /* __USE_ISOC99 */
#endif /* !__CXX_SYSTEM_HEADER */

#ifndef __COMPAR_FN_T
#define __COMPAR_FN_T 1
#ifndef ____compar_fn_t_defined
#define ____compar_fn_t_defined 1
typedef int (__LIBCCALL *__compar_fn_t)(void const *__a, void const *__b);
#endif /* !____compar_fn_t_defined */
#ifdef __USE_GNU
typedef __compar_fn_t comparison_fn_t;
#endif /* __USE_GNU */
#endif /* __COMPAR_FN_T */

#ifndef ____atexit_func_t_defined
#define ____atexit_func_t_defined 1
typedef void (__LIBCCALL *__atexit_func_t)(void);
#endif /* !____atexit_func_t_defined */

#ifdef __USE_GNU
#ifndef __compar_d_fn_t_defined
#define __compar_d_fn_t_defined 1
typedef int (__LIBKCALL *__compar_d_fn_t)(void const *__a, void const *__b, void *__arg);
#endif /* !__compar_d_fn_t_defined */
#ifdef __CRT_HAVE_qsort_r
__CDECLARE_VOID(__ATTR_NONNULL((1, 4)),__THROWING,qsort_r,(void *__pbase, __SIZE_TYPE__ __item_count, __SIZE_TYPE__ __item_size, __compar_d_fn_t __cmp, void *__arg),(__pbase,__item_count,__item_size,__cmp,__arg))
#else /* __CRT_HAVE_qsort_r */
#include <local/stdlib/qsort_r.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(qsort_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 4)) void (__LIBCCALL qsort_r)(void *__pbase, __SIZE_TYPE__ __item_count, __SIZE_TYPE__ __item_size, __compar_d_fn_t __cmp, void *__arg) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(qsort_r))(__pbase, __item_count, __item_size, __cmp, __arg); })
#endif /* !__CRT_HAVE_qsort_r */
#endif /* __USE_GNU */

#ifdef __USE_KOS
#ifndef __compar_d_fn_t_defined
#define __compar_d_fn_t_defined 1
typedef int (__LIBKCALL *__compar_d_fn_t)(void const *__a, void const *__b, void *__arg);
#endif /* !__compar_d_fn_t_defined */
#ifdef __CRT_HAVE_bsearch_r
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STDLIB_H_PROTO)
extern "C++" {
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2, 5)),void *,__THROWING,bsearch_r,(void const *__pkey, void *__pbase, __SIZE_TYPE__ __item_count, __SIZE_TYPE__ __item_size, __compar_d_fn_t __cmp, void *__arg),bsearch_r,(__pkey,__pbase,__item_count,__item_size,__cmp,__arg))
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2, 5)),void const *,__THROWING,bsearch_r,(void const *__pkey, void const *__pbase, __SIZE_TYPE__ __item_count, __SIZE_TYPE__ __item_size, __compar_d_fn_t __cmp, void *__arg),bsearch_r,(__pkey,__pbase,__item_count,__item_size,__cmp,__arg))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STDLIB_H_PROTO */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 2, 5)),void *,__THROWING,bsearch_r,(void const *__pkey, void const *__pbase, __SIZE_TYPE__ __item_count, __SIZE_TYPE__ __item_size, __compar_d_fn_t __cmp, void *__arg),(__pkey,__pbase,__item_count,__item_size,__cmp,__arg))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STDLIB_H_PROTO */
#else /* __CRT_HAVE_bsearch_r */
#include <local/stdlib/bsearch_r.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STDLIB_H_PROTO)
extern "C++" {
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 2, 5)) void *(__LIBCCALL bsearch_r)(void const *__pkey, void *__pbase, __SIZE_TYPE__ __item_count, __SIZE_TYPE__ __item_size, __compar_d_fn_t __cmp, void *__arg) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(bsearch_r))(__pkey, __pbase, __item_count, __item_size, __cmp, __arg); }
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 2, 5)) void const *(__LIBCCALL bsearch_r)(void const *__pkey, void const *__pbase, __SIZE_TYPE__ __item_count, __SIZE_TYPE__ __item_size, __compar_d_fn_t __cmp, void *__arg) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(bsearch_r))(__pkey, __pbase, __item_count, __item_size, __cmp, __arg); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STDLIB_H_PROTO */
__NAMESPACE_LOCAL_USING_OR_IMPL(bsearch_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 2, 5)) void *(__LIBCCALL bsearch_r)(void const *__pkey, void const *__pbase, __SIZE_TYPE__ __item_count, __SIZE_TYPE__ __item_size, __compar_d_fn_t __cmp, void *__arg) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(bsearch_r))(__pkey, __pbase, __item_count, __item_size, __cmp, __arg); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STDLIB_H_PROTO */
#endif /* !__CRT_HAVE_bsearch_r */
#endif /* __USE_KOS */

__NAMESPACE_STD_BEGIN
#ifdef __CRT_HAVE_qsort
__CDECLARE_VOID(__ATTR_NONNULL((1, 4)),__THROWING,qsort,(void *__pbase, size_t __item_count, size_t __item_size, __compar_fn_t __cmp),(__pbase,__item_count,__item_size,__cmp))
#else /* __CRT_HAVE_qsort */
__NAMESPACE_STD_END
#include <local/stdlib/qsort.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(qsort, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 4)) void (__LIBCCALL qsort)(void *__pbase, size_t __item_count, size_t __item_size, __compar_fn_t __cmp) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(qsort))(__pbase, __item_count, __item_size, __cmp); })
#endif /* !__CRT_HAVE_qsort */
#ifdef __CRT_HAVE_bsearch
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STDLIB_H_PROTO)
extern "C++" {
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2, 5)),void *,__THROWING,bsearch,(void const *__pkey, void *__pbase, size_t __item_count, size_t __item_size, __compar_fn_t __cmp),bsearch,(__pkey,__pbase,__item_count,__item_size,__cmp))
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2, 5)),void const *,__THROWING,bsearch,(void const *__pkey, void const *__pbase, size_t __item_count, size_t __item_size, __compar_fn_t __cmp),bsearch,(__pkey,__pbase,__item_count,__item_size,__cmp))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STDLIB_H_PROTO */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 2, 5)),void *,__THROWING,bsearch,(void const *__pkey, void const *__pbase, size_t __item_count, size_t __item_size, __compar_fn_t __cmp),(__pkey,__pbase,__item_count,__item_size,__cmp))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STDLIB_H_PROTO */
#else /* __CRT_HAVE_bsearch */
__NAMESPACE_STD_END
#include <local/stdlib/bsearch.h>
__NAMESPACE_STD_BEGIN
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STDLIB_H_PROTO)
extern "C++" {
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 2, 5)) void *(__LIBCCALL bsearch)(void const *__pkey, void *__pbase, size_t __item_count, size_t __item_size, __compar_fn_t __cmp) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(bsearch))(__pkey, __pbase, __item_count, __item_size, __cmp); }
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 2, 5)) void const *(__LIBCCALL bsearch)(void const *__pkey, void const *__pbase, size_t __item_count, size_t __item_size, __compar_fn_t __cmp) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(bsearch))(__pkey, __pbase, __item_count, __item_size, __cmp); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STDLIB_H_PROTO */
__NAMESPACE_LOCAL_USING_OR_IMPL(bsearch, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 2, 5)) void *(__LIBCCALL bsearch)(void const *__pkey, void const *__pbase, size_t __item_count, size_t __item_size, __compar_fn_t __cmp) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(bsearch))(__pkey, __pbase, __item_count, __item_size, __cmp); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STDLIB_H_PROTO */
#endif /* !__CRT_HAVE_bsearch */
#if __has_builtin(__builtin_labs) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_labs)
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,long,__NOTHROW,labs,(long __x),{ return __builtin_labs(__x); })
#elif defined(__CRT_HAVE_labs)
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,long,__NOTHROW,labs,(long __x),(__x))
#elif defined(__CRT_HAVE_abs) && __SIZEOF_LONG__ == __SIZEOF_INT__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long,__NOTHROW,labs,(long __x),abs,(__x))
#elif defined(__CRT_HAVE_llabs) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long,__NOTHROW,labs,(long __x),llabs,(__x))
#elif defined(__CRT_HAVE_imaxabs) && __SIZEOF_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long,__NOTHROW,labs,(long __x),imaxabs,(__x))
#elif defined(__CRT_HAVE__abs64) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long,__NOTHROW,labs,(long __x),_abs64,(__x))
#else /* ... */
__NAMESPACE_STD_END
#include <local/stdlib/labs.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(labs, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED long __NOTHROW(__LIBCCALL labs)(long __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(labs))(__x); })
#endif /* !... */
#ifdef __USE_ISOC99
#if __has_builtin(__builtin_llabs) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_llabs)
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,llabs,(__LONGLONG __x),{ return __builtin_llabs(__x); })
#elif defined(__CRT_HAVE_llabs)
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,llabs,(__LONGLONG __x),(__x))
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
#include <local/stdlib/llabs.h>
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
#elif defined(__CRT_HAVE_imaxdiv) && __SIZEOF_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,struct __ldiv_struct,__NOTHROW_NCX,ldiv,(long __numer, long __denom),imaxdiv,(__numer,__denom))
#else /* ... */
__NAMESPACE_STD_END
#include <local/stdlib/ldiv.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(ldiv, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED struct __ldiv_struct __NOTHROW_NCX(__LIBCCALL ldiv)(long __numer, long __denom) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ldiv))(__numer, __denom); })
#endif /* !... */
#ifdef __USE_ISOC99
#ifdef __CRT_HAVE_lldiv
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,struct __lldiv_struct,__NOTHROW_NCX,lldiv,(__LONGLONG __numer, __LONGLONG __denom),(__numer,__denom))
#elif defined(__CRT_HAVE_div) && __SIZEOF_LONG_LONG__ == __SIZEOF_INT__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,struct __lldiv_struct,__NOTHROW_NCX,lldiv,(__LONGLONG __numer, __LONGLONG __denom),div,(__numer,__denom))
#elif defined(__CRT_HAVE_ldiv) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,struct __lldiv_struct,__NOTHROW_NCX,lldiv,(__LONGLONG __numer, __LONGLONG __denom),ldiv,(__numer,__denom))
#elif defined(__CRT_HAVE_imaxdiv) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,struct __lldiv_struct,__NOTHROW_NCX,lldiv,(__LONGLONG __numer, __LONGLONG __denom),imaxdiv,(__numer,__denom))
#else /* ... */
__NAMESPACE_STD_END
#include <local/stdlib/lldiv.h>
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
#elif defined(__CRT_HAVE_imaxabs) && __SIZEOF_INT__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,abs,(int __x),imaxabs,(__x))
#elif defined(__CRT_HAVE__abs64) && __SIZEOF_INT__ == 8
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,abs,(int __x),_abs64,(__x))
#else /* ... */
__NAMESPACE_STD_END
#include <local/stdlib/abs.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(abs, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL abs)(int __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(abs))(__x); })
#endif /* !... */
#ifdef __CRT_HAVE_div
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,struct __div_struct,__NOTHROW_NCX,div,(int __numer, int __denom),(__numer,__denom))
#elif defined(__CRT_HAVE_ldiv) && __SIZEOF_INT__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,struct __div_struct,__NOTHROW_NCX,div,(int __numer, int __denom),ldiv,(__numer,__denom))
#elif defined(__CRT_HAVE_lldiv) && __SIZEOF_INT__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,struct __div_struct,__NOTHROW_NCX,div,(int __numer, int __denom),lldiv,(__numer,__denom))
#elif defined(__CRT_HAVE_imaxdiv) && __SIZEOF_INT__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,struct __div_struct,__NOTHROW_NCX,div,(int __numer, int __denom),imaxdiv,(__numer,__denom))
#else /* ... */
__NAMESPACE_STD_END
#include <local/stdlib/div.h>
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
#elif defined(__CRT_HAVE_imaxabs) && __SIZEOF_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long,__NOTHROW,abs,(long __x),imaxabs,(__x))
#elif defined(__CRT_HAVE__abs64) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long,__NOTHROW,abs,(long __x),_abs64,(__x))
#else /* ... */
} /* extern "C++" */
__NAMESPACE_STD_END
#include <local/stdlib/labs.h>
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
#elif defined(__CRT_HAVE_imaxdiv) && __SIZEOF_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,struct __ldiv_struct,__NOTHROW_NCX,div,(long __numer, long __denom),imaxdiv,(__numer,__denom))
#else /* ... */
} /* extern "C++" */
__NAMESPACE_STD_END
#include <local/stdlib/ldiv.h>
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
#include <local/stdlib/llabs.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __LONGLONG __NOTHROW(__LIBCCALL abs)(__LONGLONG __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(llabs))(__x); }
#endif /* !... */
#ifdef __CRT_HAVE_lldiv
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,struct __lldiv_struct,__NOTHROW_NCX,div,(__LONGLONG __numer, __LONGLONG __denom),lldiv,(__numer,__denom))
#elif defined(__CRT_HAVE_div) && __SIZEOF_LONG_LONG__ == __SIZEOF_INT__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,struct __lldiv_struct,__NOTHROW_NCX,div,(__LONGLONG __numer, __LONGLONG __denom),div,(__numer,__denom))
#elif defined(__CRT_HAVE_ldiv) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,struct __lldiv_struct,__NOTHROW_NCX,div,(__LONGLONG __numer, __LONGLONG __denom),ldiv,(__numer,__denom))
#elif defined(__CRT_HAVE_imaxdiv) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,struct __lldiv_struct,__NOTHROW_NCX,div,(__LONGLONG __numer, __LONGLONG __denom),imaxdiv,(__numer,__denom))
#else /* ... */
} /* extern "C++" */
__NAMESPACE_STD_END
#include <local/stdlib/lldiv.h>
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
/* Absolute value of X */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,abs,(float __x),fabsf,{ return __builtin_fabsf(__x); })
#elif defined(__CRT_HAVE_fabsf)
/* Absolute value of X */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,abs,(float __x),fabsf,(__x))
#elif defined(__CRT_HAVE___fabsf)
/* Absolute value of X */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,abs,(float __x),__fabsf,(__x))
#else /* ... */
} /* extern "C++" */
__NAMESPACE_STD_END
#include <local/math/fabsf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Absolute value of X */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL abs)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fabsf))(__x); }
#endif /* !... */
#if __has_builtin(__builtin_fabs) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fabs)
/* Absolute value of X */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,abs,(double __x),fabs,{ return __builtin_fabs(__x); })
#elif defined(__CRT_HAVE_fabs)
/* Absolute value of X */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,abs,(double __x),fabs,(__x))
#elif defined(__CRT_HAVE___fabs)
/* Absolute value of X */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,abs,(double __x),__fabs,(__x))
#else /* ... */
} /* extern "C++" */
__NAMESPACE_STD_END
#include <local/math/fabs.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Absolute value of X */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW(__LIBCCALL abs)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fabs))(__x); }
#endif /* !... */
} /* extern "C++" */
#ifdef __COMPILER_HAVE_LONGDOUBLE
extern "C++" {
#if __has_builtin(__builtin_fabsl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fabsl)
/* Absolute value of X */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,abs,(__LONGDOUBLE __x),fabsl,{ return __builtin_fabsl(__x); })
#elif defined(__CRT_HAVE_fabsl)
/* Absolute value of X */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,abs,(__LONGDOUBLE __x),fabsl,(__x))
#elif defined(__CRT_HAVE___fabsl)
/* Absolute value of X */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,abs,(__LONGDOUBLE __x),__fabsl,(__x))
#else /* ... */
} /* extern "C++" */
__NAMESPACE_STD_END
#include <local/math/fabsl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Absolute value of X */
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
#include <local/environ.h>
__NAMESPACE_STD_BEGIN
#ifdef __LOCAL_environ
__NAMESPACE_STD_END
#include <local/stdlib/getenv.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(getenv, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL getenv)(char const *__varname) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getenv))(__varname); })
#endif /* __LOCAL_environ */
#endif /* !__CRT_HAVE_getenv */
#ifdef __CRT_HAVE_mblen
__CDECLARE(,int,__NOTHROW_NCX,mblen,(char const *__str, size_t __maxlen),(__str,__maxlen))
#else /* __CRT_HAVE_mblen */
__NAMESPACE_STD_END
#include <local/stdlib/mblen.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(mblen, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_NCX(__LIBCCALL mblen)(char const *__str, size_t __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mblen))(__str, __maxlen); })
#endif /* !__CRT_HAVE_mblen */
#ifdef __CRT_HAVE_mbtowc
__CDECLARE(,int,__NOTHROW_NCX,mbtowc,(wchar_t *__restrict __pwc, char const *__restrict __str, size_t __maxlen),(__pwc,__str,__maxlen))
#else /* __CRT_HAVE_mbtowc */
__NAMESPACE_STD_END
#include <local/stdlib/mbtowc.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(mbtowc, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_NCX(__LIBCCALL mbtowc)(wchar_t *__restrict __pwc, char const *__restrict __str, size_t __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mbtowc))(__pwc, __str, __maxlen); })
#endif /* !__CRT_HAVE_mbtowc */
#ifdef __CRT_HAVE_wctomb
__CDECLARE(,int,__NOTHROW_NCX,wctomb,(char *__str, wchar_t __wc),(__str,__wc))
#else /* __CRT_HAVE_wctomb */
__NAMESPACE_STD_END
#include <local/stdlib/wctomb.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(wctomb, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_NCX(__LIBCCALL wctomb)(char *__str, wchar_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wctomb))(__str, __wc); })
#endif /* !__CRT_HAVE_wctomb */
#ifdef __CRT_HAVE_mbstowcs
__CDECLARE(__ATTR_NONNULL((1, 2)),size_t,__NOTHROW_NCX,mbstowcs,(wchar_t *__restrict __dst, char const *__restrict __src, size_t __dstlen),(__dst,__src,__dstlen))
#else /* __CRT_HAVE_mbstowcs */
__NAMESPACE_STD_END
#include <local/stdlib/mbstowcs.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(mbstowcs, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) size_t __NOTHROW_NCX(__LIBCCALL mbstowcs)(wchar_t *__restrict __dst, char const *__restrict __src, size_t __dstlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mbstowcs))(__dst, __src, __dstlen); })
#endif /* !__CRT_HAVE_mbstowcs */
#ifdef __CRT_HAVE_wcstombs
__CDECLARE(__ATTR_NONNULL((1, 2)),size_t,__NOTHROW_NCX,wcstombs,(char *__restrict __dst, wchar_t const *__restrict __src, size_t __dstlen),(__dst,__src,__dstlen))
#else /* __CRT_HAVE_wcstombs */
__NAMESPACE_STD_END
#include <local/stdlib/wcstombs.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstombs, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) size_t __NOTHROW_NCX(__LIBCCALL wcstombs)(char *__restrict __dst, wchar_t const *__restrict __src, size_t __dstlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstombs))(__dst, __src, __dstlen); })
#endif /* !__CRT_HAVE_wcstombs */
#ifndef __std_system_defined
#define __std_system_defined 1
#ifdef __system_defined
__NAMESPACE_GLB_USING_OR_IMPL(system, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_RPC(__LIBCCALL system)(char const *__command) { return (:: system)(__command); })
#elif defined(__CRT_HAVE_system)
__CDECLARE(,int,__NOTHROW_RPC,system,(char const *__command),(__command))
#else /* ... */
#undef __std_system_defined
#endif /* !... */
#endif /* !__std_system_defined */
#ifndef __std_abort_defined
#define __std_abort_defined 1
#ifdef __abort_defined
__NAMESPACE_GLB_USING_OR_IMPL(abort, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NORETURN void (__LIBCCALL abort)(void) __THROWS(...) { (:: abort)(); })
#elif __has_builtin(__builtin_abort) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_abort)
__CEIDECLARE(__ATTR_NORETURN,void,__THROWING,abort,(void),{ return __builtin_abort(); })
#elif defined(__CRT_HAVE_abort)
__CDECLARE_VOID(__ATTR_NORETURN,__THROWING,abort,(void),())
#elif defined(__CRT_HAVE__ZSt9terminatev)
__CREDIRECT_VOID(__ATTR_NORETURN,__THROWING,abort,(void),_ZSt9terminatev,())
#elif defined(__CRT_HAVE_$Qterminate$A$AYAXXZ)
__CREDIRECT_VOID(__ATTR_NORETURN,__THROWING,abort,(void),?terminate@@YAXXZ,())
#elif defined(__CRT_HAVE__Exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE_exit)
__NAMESPACE_STD_END
#include <local/stdlib/abort.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(abort, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NORETURN void (__LIBCCALL abort)(void) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(abort))(); })
#else /* ... */
#undef __std_abort_defined
#endif /* !... */
#endif /* !__std_abort_defined */
#ifndef __std_exit_defined
#define __std_exit_defined 1
#ifdef __exit_defined
__NAMESPACE_GLB_USING_OR_IMPL(exit, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NORETURN void (__LIBCCALL exit)(int __status) __THROWS(...) { (:: exit)(__status); })
#elif __has_builtin(__builtin_exit) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_exit)
__CEIDECLARE(__ATTR_NORETURN,void,__THROWING,exit,(int __status),{ return __builtin_exit(__status); })
#elif defined(__CRT_HAVE_exit)
__CDECLARE_VOID(__ATTR_NORETURN,__THROWING,exit,(int __status),(__status))
#elif defined(__CRT_HAVE_quick_exit)
__CREDIRECT_VOID(__ATTR_NORETURN,__THROWING,exit,(int __status),quick_exit,(__status))
#elif defined(__CRT_HAVE__exit)
__CREDIRECT_VOID(__ATTR_NORETURN,__THROWING,exit,(int __status),_exit,(__status))
#elif defined(__CRT_HAVE__Exit)
__CREDIRECT_VOID(__ATTR_NORETURN,__THROWING,exit,(int __status),_Exit,(__status))
#else /* ... */
#undef __std_exit_defined
#endif /* !... */
#endif /* !__std_exit_defined */
#ifdef __CRT_HAVE_atexit
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,atexit,(__atexit_func_t __func),(__func))
#elif defined(__CRT_HAVE_at_quick_exit)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,atexit,(__atexit_func_t __func),at_quick_exit,(__func))
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
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,at_quick_exit,(__atexit_func_t __func),(__func))
#elif defined(__CRT_HAVE_atexit)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,at_quick_exit,(__atexit_func_t __func),atexit,(__func))
#endif /* ... */
#endif /* __USE_ISOC11 || __USE_ISOCXX11 */
#ifdef __USE_ISOC99
#if __has_builtin(__builtin__Exit) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE__Exit)
__CEIDECLARE(__ATTR_NORETURN,void,__THROWING,_Exit,(int __status),{ return __builtin__Exit(__status); })
#elif __has_builtin(__builtin__exit) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE__exit)
__CEIREDIRECT(__ATTR_NORETURN,void,__THROWING,_Exit,(int __status),_exit,{ __builtin__exit(__status); })
#elif defined(__CRT_HAVE__Exit)
__CDECLARE_VOID(__ATTR_NORETURN,__THROWING,_Exit,(int __status),(__status))
#elif defined(__CRT_HAVE__exit)
__CREDIRECT_VOID(__ATTR_NORETURN,__THROWING,_Exit,(int __status),_exit,(__status))
#elif defined(__CRT_HAVE_quick_exit)
__CREDIRECT_VOID(__ATTR_NORETURN,__THROWING,_Exit,(int __status),quick_exit,(__status))
#elif defined(__CRT_HAVE_exit)
__CREDIRECT_VOID(__ATTR_NORETURN,__THROWING,_Exit,(int __status),exit,(__status))
#endif /* ... */
#endif /* __USE_ISOC99 */
#ifndef __std_malloc_defined
#define __std_malloc_defined 1
#ifdef __malloc_defined
__NAMESPACE_GLB_USING_OR_IMPL(malloc, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)) void *__NOTHROW_NCX(__LIBCCALL malloc)(size_t __num_bytes) { return (:: malloc)(__num_bytes); })
#elif __has_builtin(__builtin_malloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_malloc)
__CEIDECLARE(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,malloc,(size_t __num_bytes),{ return __builtin_malloc(__num_bytes); })
#elif defined(__CRT_HAVE_malloc)
__CDECLARE(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,malloc,(size_t __num_bytes),(__num_bytes))
#elif defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)
__NAMESPACE_STD_END
#include <local/stdlib/malloc.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(malloc, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)) void *__NOTHROW_NCX(__LIBCCALL malloc)(size_t __num_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(malloc))(__num_bytes); })
#else /* ... */
#undef __std_malloc_defined
#endif /* !... */
#endif /* !__std_malloc_defined */
#ifndef __std_calloc_defined
#define __std_calloc_defined 1
#ifdef __calloc_defined
__NAMESPACE_GLB_USING_OR_IMPL(calloc, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1, 2)) void *__NOTHROW_NCX(__LIBCCALL calloc)(size_t __count, size_t __num_bytes) { return (:: calloc)(__count, __num_bytes); })
#elif __has_builtin(__builtin_calloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_calloc)
__CEIDECLARE(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1, 2)),void *,__NOTHROW_NCX,calloc,(size_t __count, size_t __num_bytes),{ return __builtin_calloc(__count, __num_bytes); })
#elif defined(__CRT_HAVE_calloc)
__CDECLARE(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1, 2)),void *,__NOTHROW_NCX,calloc,(size_t __count, size_t __num_bytes),(__count,__num_bytes))
#elif defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)
__NAMESPACE_STD_END
#include <local/stdlib/calloc.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(calloc, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1, 2)) void *__NOTHROW_NCX(__LIBCCALL calloc)(size_t __count, size_t __num_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(calloc))(__count, __num_bytes); })
#else /* ... */
#undef __std_calloc_defined
#endif /* !... */
#endif /* !__std_calloc_defined */
#ifndef __std_realloc_defined
#define __std_realloc_defined 1
#ifdef __realloc_defined
__NAMESPACE_GLB_USING_OR_IMPL(realloc, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) void *__NOTHROW_NCX(__LIBCCALL realloc)(void *__mallptr, size_t __num_bytes) { return (:: realloc)(__mallptr, __num_bytes); })
#elif __has_builtin(__builtin_realloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_realloc)
__CEIDECLARE(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,realloc,(void *__mallptr, size_t __num_bytes),{ return __builtin_realloc(__mallptr, __num_bytes); })
#elif defined(__CRT_HAVE_realloc)
__CDECLARE(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,realloc,(void *__mallptr, size_t __num_bytes),(__mallptr,__num_bytes))
#else /* ... */
#undef __std_realloc_defined
#endif /* !... */
#endif /* !__std_realloc_defined */
#ifndef __std_free_defined
#define __std_free_defined 1
#ifdef __free_defined
__NAMESPACE_GLB_USING_OR_IMPL(free, __FORCELOCAL __ATTR_ARTIFICIAL void __NOTHROW_NCX(__LIBCCALL free)(void *__mallptr) { (:: free)(__mallptr); })
#elif __has_builtin(__builtin_free) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_free)
__CEIDECLARE(,void,__NOTHROW_NCX,free,(void *__mallptr),{ return __builtin_free(__mallptr); })
#elif defined(__CRT_HAVE_free)
__CDECLARE_VOID(,__NOTHROW_NCX,free,(void *__mallptr),(__mallptr))
#elif defined(__CRT_HAVE_cfree)
__CREDIRECT_VOID(,__NOTHROW_NCX,free,(void *__mallptr),cfree,(__mallptr))
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
#include <local/stdlib/srand.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(srand, __FORCELOCAL __ATTR_ARTIFICIAL void __NOTHROW(__LIBCCALL srand)(long __seed) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(srand))(__seed); })
#endif /* !... */
#ifdef __CRT_HAVE_rand
__CDECLARE(,int,__NOTHROW,rand,(void),())
#elif defined(__CRT_HAVE_random) && __SIZEOF_INT__ == __SIZEOF_LONG__
__CREDIRECT(,int,__NOTHROW,rand,(void),random,())
#else /* ... */
__NAMESPACE_STD_END
#include <local/stdlib/rand.h>
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
#include <local/stdlib/atoi.h>
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
#include <local/stdlib/atol.h>
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
#include <local/stdlib/atoll.h>
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
#elif defined(__CRT_HAVE__strtoui64) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,strtoul,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),_strtoui64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoumax) && __SIZEOF_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,strtoul,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoumax,(__nptr,__endptr,__base))
#else /* ... */
__NAMESPACE_STD_END
#include <local/stdlib/strtoul.h>
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
#elif defined(__CRT_HAVE__strtoi64) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),long,__NOTHROW_NCX,strtol,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),_strtoi64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoimax) && __SIZEOF_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),long,__NOTHROW_NCX,strtol,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoimax,(__nptr,__endptr,__base))
#elif __SIZEOF_LONG__ == 4
__NAMESPACE_STD_END
#include <local/stdlib/strto32.h>
__NAMESPACE_STD_BEGIN
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) long __NOTHROW_NCX(__LIBCCALL strtol)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base) { return (long)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strto32))(__nptr, __endptr, __base); }
#elif __SIZEOF_LONG__ == 8
__NAMESPACE_STD_END
#include <local/stdlib/strto64.h>
__NAMESPACE_STD_BEGIN
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) long __NOTHROW_NCX(__LIBCCALL strtol)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base) { return (long)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strto64))(__nptr, __endptr, __base); }
#else /* ... */
__NAMESPACE_STD_END
#include <local/stdlib/strtol.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(strtol, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) long __NOTHROW_NCX(__LIBCCALL strtol)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtol))(__nptr, __endptr, __base); })
#endif /* !... */
#ifdef __ULONGLONG
#ifdef __USE_ISOC99
#ifndef __std_strtoull_defined
#define __std_strtoull_defined 1
#ifdef __strtoull_defined
__NAMESPACE_GLB_USING_OR_IMPL(strtoull, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __ULONGLONG __NOTHROW_NCX(__LIBCCALL strtoull)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base) { return (:: strtoull)(__nptr, __endptr, __base); })
#elif defined(__CRT_HAVE_strtoull)
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,strtoull,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtouq)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,strtoull,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtouq,(__nptr,__endptr,__base))
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
#include <local/stdlib/strtou64.h>
__NAMESPACE_STD_BEGIN
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __ULONGLONG __NOTHROW_NCX(__LIBCCALL strtoull)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base) { return (__ULONGLONG)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtou64))(__nptr, __endptr, __base); }
#elif __SIZEOF_LONG__ == 4
__NAMESPACE_STD_END
#include <local/stdlib/strtou32.h>
__NAMESPACE_STD_BEGIN
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __ULONGLONG __NOTHROW_NCX(__LIBCCALL strtoull)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base) { return (__ULONGLONG)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtou32))(__nptr, __endptr, __base); }
#else /* ... */
__NAMESPACE_STD_END
#include <local/stdlib/strtoull.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(strtoull, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __ULONGLONG __NOTHROW_NCX(__LIBCCALL strtoull)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtoull))(__nptr, __endptr, __base); })
#endif /* !... */
#endif /* !__std_strtoull_defined */
#ifndef __std_strtoll_defined
#define __std_strtoll_defined 1
#ifdef __strtoll_defined
__NAMESPACE_GLB_USING_OR_IMPL(strtoll, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __LONGLONG __NOTHROW_NCX(__LIBCCALL strtoll)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base) { return (:: strtoll)(__nptr, __endptr, __base); })
#elif defined(__CRT_HAVE_strtoll)
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,strtoll,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoq)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,strtoll,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoq,(__nptr,__endptr,__base))
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
#include <local/stdlib/strto64.h>
__NAMESPACE_STD_BEGIN
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __LONGLONG __NOTHROW_NCX(__LIBCCALL strtoll)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base) { return (__LONGLONG)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strto64))(__nptr, __endptr, __base); }
#elif __SIZEOF_LONG__ == 4
__NAMESPACE_STD_END
#include <local/stdlib/strto32.h>
__NAMESPACE_STD_BEGIN
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __LONGLONG __NOTHROW_NCX(__LIBCCALL strtoll)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base) { return (__LONGLONG)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strto32))(__nptr, __endptr, __base); }
#else /* ... */
__NAMESPACE_STD_END
#include <local/stdlib/strtoll.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(strtoll, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __LONGLONG __NOTHROW_NCX(__LIBCCALL strtoll)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtoll))(__nptr, __endptr, __base); })
#endif /* !... */
#endif /* !__std_strtoll_defined */
#endif /* __USE_ISOC99 */
#endif /* __ULONGLONG */
#ifndef __NO_FPU
#ifdef __CRT_HAVE_atof
__CDECLARE(__ATTR_LEAF __ATTR_WUNUSED __ATTR_NONNULL((1)),double,__NOTHROW_NCX,atof,(char const *__restrict __nptr),(__nptr))
#else /* __CRT_HAVE_atof */
__NAMESPACE_STD_END
#include <local/stdlib/atof.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(atof, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_WUNUSED __ATTR_NONNULL((1)) double __NOTHROW_NCX(__LIBCCALL atof)(char const *__restrict __nptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(atof))(__nptr); })
#endif /* !__CRT_HAVE_atof */
#ifdef __CRT_HAVE_strtod
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),double,__NOTHROW_NCX,strtod,(char const *__restrict __nptr, char **__endptr),(__nptr,__endptr))
#elif defined(__CRT_HAVE_strtold) && __SIZEOF_LONG_DOUBLE__ == __SIZEOF_DOUBLE__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),double,__NOTHROW_NCX,strtod,(char const *__restrict __nptr, char **__endptr),strtold,(__nptr,__endptr))
#else /* ... */
__NAMESPACE_STD_END
#include <local/stdlib/strtod.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(strtod, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) double __NOTHROW_NCX(__LIBCCALL strtod)(char const *__restrict __nptr, char **__endptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtod))(__nptr, __endptr); })
#endif /* !... */
#ifdef __USE_ISOC99
#ifndef __std_strtof_defined
#define __std_strtof_defined 1
#ifdef __strtof_defined
__NAMESPACE_GLB_USING_OR_IMPL(strtof, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) float __NOTHROW_NCX(__LIBCCALL strtof)(char const *__restrict __nptr, char **__endptr) { return (:: strtof)(__nptr, __endptr); })
#elif defined(__CRT_HAVE_strtof)
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),float,__NOTHROW_NCX,strtof,(char const *__restrict __nptr, char **__endptr),(__nptr,__endptr))
#else /* ... */
__NAMESPACE_STD_END
#include <local/stdlib/strtof.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(strtof, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) float __NOTHROW_NCX(__LIBCCALL strtof)(char const *__restrict __nptr, char **__endptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtof))(__nptr, __endptr); })
#endif /* !... */
#endif /* !__std_strtof_defined */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#ifndef __std_strtold_defined
#define __std_strtold_defined 1
#ifdef __strtold_defined
__NAMESPACE_GLB_USING_OR_IMPL(strtold, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __LONGDOUBLE __NOTHROW_NCX(__LIBCCALL strtold)(char const *__restrict __nptr, char **__endptr) { return (:: strtold)(__nptr, __endptr); })
#elif defined(__CRT_HAVE_strtold)
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGDOUBLE,__NOTHROW_NCX,strtold,(char const *__restrict __nptr, char **__endptr),(__nptr,__endptr))
#elif defined(__CRT_HAVE_strtod) && __SIZEOF_LONG_DOUBLE__ == __SIZEOF_DOUBLE__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGDOUBLE,__NOTHROW_NCX,strtold,(char const *__restrict __nptr, char **__endptr),strtod,(__nptr,__endptr))
#else /* ... */
__NAMESPACE_STD_END
#include <local/stdlib/strtold.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(strtold, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __LONGDOUBLE __NOTHROW_NCX(__LIBCCALL strtold)(char const *__restrict __nptr, char **__endptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtold))(__nptr, __endptr); })
#endif /* !... */
#endif /* !__std_strtold_defined */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_ISOC99 */
#endif /* !__NO_FPU */
#ifdef __USE_ISOCXX17
#ifndef __std_aligned_alloc_defined
#define __std_aligned_alloc_defined 1
#ifdef __aligned_alloc_defined
__NAMESPACE_GLB_USING_OR_IMPL(aligned_alloc, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_ALIGN(1) __ATTR_ALLOC_SIZE((2)) void *__NOTHROW_NCX(__LIBCCALL aligned_alloc)(size_t __alignment, size_t __n_bytes) { return (void *)(:: aligned_alloc)(); })
#elif __has_builtin(__builtin_aligned_alloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_aligned_alloc)
__CEIDECLARE(__ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_ALIGN(1) __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,aligned_alloc,(size_t __alignment, size_t __n_bytes),{ return __builtin_aligned_alloc(__alignment, __n_bytes); })
#elif defined(__CRT_HAVE_memalign)
__CREDIRECT(__ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_ALIGN(1) __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,aligned_alloc,(size_t __alignment, size_t __n_bytes),memalign,(__alignment,__n_bytes))
#elif defined(__CRT_HAVE_aligned_alloc)
__CDECLARE(__ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_ALIGN(1) __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,aligned_alloc,(size_t __alignment, size_t __n_bytes),(__alignment,__n_bytes))
#elif defined(__CRT_HAVE_posix_memalign)
__NAMESPACE_STD_END
#include <local/malloc/memalign.h>
__NAMESPACE_STD_BEGIN
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_ALIGN(1) __ATTR_ALLOC_SIZE((2)) void *__NOTHROW_NCX(__LIBCCALL aligned_alloc)(size_t __alignment, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memalign))(__alignment, __n_bytes); }
#else /* ... */
#undef __std_aligned_alloc_defined
#endif /* !... */
#endif /* !__std_aligned_alloc_defined */
#endif /* __USE_ISOCXX17 */
__NAMESPACE_STD_END

#ifndef __CXX_SYSTEM_HEADER
__NAMESPACE_STD_USING(qsort)
__NAMESPACE_STD_USING(bsearch)
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
#include <local/environ.h>
#if defined(__CRT_HAVE_getenv) || defined(__LOCAL_environ)
__NAMESPACE_STD_USING(getenv)
#endif /* __CRT_HAVE_getenv || __LOCAL_environ */
__NAMESPACE_STD_USING(mblen)
__NAMESPACE_STD_USING(mbtowc)
__NAMESPACE_STD_USING(wctomb)
__NAMESPACE_STD_USING(mbstowcs)
__NAMESPACE_STD_USING(wcstombs)
#if !defined(__system_defined) && defined(__std_system_defined)
#define __system_defined 1
__NAMESPACE_STD_USING(system)
#endif /* !__system_defined && __std_system_defined */
#if !defined(__abort_defined) && defined(__std_abort_defined)
#define __abort_defined 1
__NAMESPACE_STD_USING(abort)
#endif /* !__abort_defined && __std_abort_defined */
#if !defined(__exit_defined) && defined(__std_exit_defined)
#define __exit_defined 1
__NAMESPACE_STD_USING(exit)
#endif /* !__exit_defined && __std_exit_defined */
#if defined(__CRT_HAVE_atexit) || defined(__CRT_HAVE_at_quick_exit)
__NAMESPACE_STD_USING(atexit)
#endif /* __CRT_HAVE_atexit || __CRT_HAVE_at_quick_exit */
#endif /* !__CXX_SYSTEM_HEADER */
#if defined(__USE_ISOC11) || defined(__USE_ISOCXX11)
#ifndef __CXX_SYSTEM_HEADER
#if defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE_exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE__Exit)
__NAMESPACE_STD_USING(quick_exit)
#endif /* __CRT_HAVE_quick_exit || __CRT_HAVE_exit || __CRT_HAVE__exit || __CRT_HAVE__Exit */
#if defined(__CRT_HAVE_at_quick_exit) || defined(__CRT_HAVE_atexit)
__NAMESPACE_STD_USING(at_quick_exit)
#endif /* __CRT_HAVE_at_quick_exit || __CRT_HAVE_atexit */
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
#define __malloc_defined 1
__NAMESPACE_STD_USING(malloc)
#endif /* !__malloc_defined && __std_malloc_defined */
#if !defined(__calloc_defined) && defined(__std_calloc_defined)
#define __calloc_defined 1
__NAMESPACE_STD_USING(calloc)
#endif /* !__calloc_defined && __std_calloc_defined */
#if !defined(__realloc_defined) && defined(__std_realloc_defined)
#define __realloc_defined 1
__NAMESPACE_STD_USING(realloc)
#endif /* !__realloc_defined && __std_realloc_defined */
#if !defined(__free_defined) && defined(__std_free_defined)
#define __free_defined 1
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
#define __strtoull_defined 1
__NAMESPACE_STD_USING(strtoull)
#endif /* !__strtoull_defined && __std_strtoull_defined */
#if !defined(__strtoll_defined) && defined(__std_strtoll_defined)
#define __strtoll_defined 1
__NAMESPACE_STD_USING(strtoll)
#endif /* !__strtoll_defined && __std_strtoll_defined */
#endif /* !__CXX_SYSTEM_HEADER */
#ifndef __NO_FPU
#ifndef __CXX_SYSTEM_HEADER
__NAMESPACE_STD_USING(atof)
__NAMESPACE_STD_USING(strtod)
#if !defined(__strtof_defined) && defined(__std_strtof_defined)
#define __strtof_defined 1
__NAMESPACE_STD_USING(strtof)
#endif /* !__strtof_defined && __std_strtof_defined */
#if !defined(__strtold_defined) && defined(__std_strtold_defined)
#define __strtold_defined 1
__NAMESPACE_STD_USING(strtold)
#endif /* !__strtold_defined && __std_strtold_defined */
#endif /* !__CXX_SYSTEM_HEADER */
#endif /* !__NO_FPU */

#ifdef __USE_MISC
#ifdef __ULONGLONG
#ifdef __CRT_HAVE_strtoll
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,strtoq,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoq)
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,strtoq,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),(__nptr,__endptr,__base))
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
#include <local/stdlib/strto64.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __LONGLONG __NOTHROW_NCX(__LIBCCALL strtoq)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base) { return (__LONGLONG)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strto64))(__nptr, __endptr, __base); }
#elif __SIZEOF_LONG__ == 4
#include <local/stdlib/strto32.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __LONGLONG __NOTHROW_NCX(__LIBCCALL strtoq)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base) { return (__LONGLONG)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strto32))(__nptr, __endptr, __base); }
#else /* ... */
#include <local/stdlib/strtoll.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __LONGLONG __NOTHROW_NCX(__LIBCCALL strtoq)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtoll))(__nptr, __endptr, __base); }
#endif /* !... */
#ifdef __CRT_HAVE_strtoull
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,strtouq,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtouq)
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,strtouq,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),(__nptr,__endptr,__base))
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
#include <local/stdlib/strtou64.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __ULONGLONG __NOTHROW_NCX(__LIBCCALL strtouq)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base) { return (__ULONGLONG)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtou64))(__nptr, __endptr, __base); }
#elif __SIZEOF_LONG__ == 4
#include <local/stdlib/strtou32.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __ULONGLONG __NOTHROW_NCX(__LIBCCALL strtouq)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base) { return (__ULONGLONG)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtou32))(__nptr, __endptr, __base); }
#else /* ... */
#include <local/stdlib/strtoull.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __ULONGLONG __NOTHROW_NCX(__LIBCCALL strtouq)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtoull))(__nptr, __endptr, __base); }
#endif /* !... */
#endif /* __ULONGLONG */
#endif /* __USE_MISC */
#ifdef __USE_KOS
#ifdef __CRT_HAVE_strtou32
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,strtou32,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoul) && __SIZEOF_LONG__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,strtou32,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoull) && __SIZEOF_LONG_LONG__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,strtou32,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtouq) && __SIZEOF_LONG_LONG__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,strtou32,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoumax) && __SIZEOF_INTMAX_T__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,strtou32,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoumax,(__nptr,__endptr,__base))
#else /* ... */
#include <local/stdlib/strtou32.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strtou32, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __UINT32_TYPE__ __NOTHROW_NCX(__LIBCCALL strtou32)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtou32))(__nptr, __endptr, __base); })
#endif /* !... */
#ifdef __CRT_HAVE_strto32
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,strto32,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtol) && __SIZEOF_LONG__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,strto32,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoll) && __SIZEOF_LONG_LONG__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,strto32,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoq) && __SIZEOF_LONG_LONG__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,strto32,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoimax) && __SIZEOF_INTMAX_T__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,strto32,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoimax,(__nptr,__endptr,__base))
#else /* ... */
#include <local/stdlib/strto32.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strto32, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __INT32_TYPE__ __NOTHROW_NCX(__LIBCCALL strto32)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strto32))(__nptr, __endptr, __base); })
#endif /* !... */
#ifdef __UINT64_TYPE__
#ifdef __CRT_HAVE_strtou64
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,strtou64,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__strtoui64)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,strtou64,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),_strtoui64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoul) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,strtou64,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoull) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,strtou64,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtouq) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,strtou64,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoumax) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,strtou64,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoumax,(__nptr,__endptr,__base))
#else /* ... */
#include <local/stdlib/strtou64.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strtou64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __UINT64_TYPE__ __NOTHROW_NCX(__LIBCCALL strtou64)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtou64))(__nptr, __endptr, __base); })
#endif /* !... */
#ifdef __CRT_HAVE_strto64
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,strto64,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__strtoi64)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,strto64,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),_strtoi64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtol) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,strto64,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoll) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,strto64,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoq) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,strto64,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoimax) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,strto64,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoimax,(__nptr,__endptr,__base))
#else /* ... */
#include <local/stdlib/strto64.h>
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
#elif defined(__CRT_HAVE_strtoumax_l) && __SIZEOF_INTMAX_T__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,strtou32_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoumax_l) && __SIZEOF_INTMAX_T__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,strtou32_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_strtoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___strtoumax_l) && __SIZEOF_INTMAX_T__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,strtou32_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__strtoumax_l,(__nptr,__endptr,__base,__locale))
#else /* ... */
#include <local/stdlib/strtou32_l.h>
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
#elif defined(__CRT_HAVE_strtoimax_l) && __SIZEOF_INTMAX_T__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,strto32_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoimax_l) && __SIZEOF_INTMAX_T__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,strto32_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_strtoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___strtoimax_l) && __SIZEOF_INTMAX_T__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,strto32_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__strtoimax_l,(__nptr,__endptr,__base,__locale))
#else /* ... */
#include <local/stdlib/strto32_l.h>
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
#elif defined(__CRT_HAVE_strtoumax_l) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,strtou64_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoumax_l) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,strtou64_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_strtoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___strtoumax_l) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,strtou64_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__strtoumax_l,(__nptr,__endptr,__base,__locale))
#else /* ... */
#include <local/stdlib/strtou64_l.h>
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
#elif defined(__CRT_HAVE_strtoimax_l) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,strto64_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoimax_l) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,strto64_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_strtoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___strtoimax_l) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,strto64_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__strtoimax_l,(__nptr,__endptr,__base,__locale))
#else /* ... */
#include <local/stdlib/strto64_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strto64_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __INT64_TYPE__ __NOTHROW_NCX(__LIBCCALL strto64_l)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strto64_l))(__nptr, __endptr, __base, __locale); })
#endif /* !... */
#endif /* __UINT64_TYPE__ */
#endif /* __USE_XOPEN2K8 */
#endif /* __USE_KOS */


#if defined(__USE_MISC) || defined(__USE_DOS) || \
   (defined(__USE_XOPEN_EXTENDED) && !defined(__USE_XOPEN2K8))
#ifndef __NO_FPU
#ifdef __CRT_HAVE_gcvt
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((3)),char *,__NOTHROW_NCX,gcvt,(double __val, int __ndigit, char *__buf),(__val,__ndigit,__buf))
#elif defined(__CRT_HAVE__gcvt)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((3)),char *,__NOTHROW_NCX,gcvt,(double __val, int __ndigit, char *__buf),_gcvt,(__val,__ndigit,__buf))
#else /* ... */
#include <local/stdlib/gcvt.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(gcvt, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((3)) char *__NOTHROW_NCX(__LIBCCALL gcvt)(double __val, int __ndigit, char *__buf) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(gcvt))(__val, __ndigit, __buf); })
#endif /* !... */
#endif /* !__NO_FPU */
#endif /* ... */

#ifdef __USE_MISC
#ifndef __NO_FPU
#ifdef __CRT_HAVE_ecvt_r
__CDECLARE(__ATTR_NONNULL((3, 4, 5)),int,__NOTHROW_NCX,ecvt_r,(double __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign, char *__restrict __buf, __SIZE_TYPE__ __len),(__val,__ndigit,__decptr,__sign,__buf,__len))
#else /* __CRT_HAVE_ecvt_r */
#include <local/stdlib/ecvt_r.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(ecvt_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((3, 4, 5)) int __NOTHROW_NCX(__LIBCCALL ecvt_r)(double __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign, char *__restrict __buf, __SIZE_TYPE__ __len) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ecvt_r))(__val, __ndigit, __decptr, __sign, __buf, __len); })
#endif /* !__CRT_HAVE_ecvt_r */
#ifdef __CRT_HAVE_fcvt_r
__CDECLARE(__ATTR_NONNULL((3, 4, 5)),int,__NOTHROW_NCX,fcvt_r,(double __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign, char *__restrict __buf, __SIZE_TYPE__ __len),(__val,__ndigit,__decptr,__sign,__buf,__len))
#else /* __CRT_HAVE_fcvt_r */
#include <local/stdlib/fcvt_r.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fcvt_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((3, 4, 5)) int __NOTHROW_NCX(__LIBCCALL fcvt_r)(double __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign, char *__restrict __buf, __SIZE_TYPE__ __len) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fcvt_r))(__val, __ndigit, __decptr, __sign, __buf, __len); })
#endif /* !__CRT_HAVE_fcvt_r */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#ifdef __CRT_HAVE_qgcvt
__CDECLARE(__ATTR_NONNULL((3)),char *,__NOTHROW_NCX,qgcvt,(__LONGDOUBLE __val, int __ndigit, char *__buf),(__val,__ndigit,__buf))
#elif defined(__CRT_HAVE__gcvt) && __SIZEOF_LONG_DOUBLE__ == __SIZEOF_DOUBLE__
__CREDIRECT(__ATTR_NONNULL((3)),char *,__NOTHROW_NCX,qgcvt,(__LONGDOUBLE __val, int __ndigit, char *__buf),_gcvt,(__val,__ndigit,__buf))
#else /* ... */
#include <local/stdlib/qgcvt.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(qgcvt, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((3)) char *__NOTHROW_NCX(__LIBCCALL qgcvt)(__LONGDOUBLE __val, int __ndigit, char *__buf) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(qgcvt))(__val, __ndigit, __buf); })
#endif /* !... */
#ifdef __CRT_HAVE_qecvt_r
__CDECLARE(__ATTR_NONNULL((3, 4, 5)),int,__NOTHROW_NCX,qecvt_r,(__LONGDOUBLE __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign, char *__restrict __buf, __SIZE_TYPE__ __len),(__val,__ndigit,__decptr,__sign,__buf,__len))
#else /* __CRT_HAVE_qecvt_r */
#include <local/stdlib/qecvt_r.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(qecvt_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((3, 4, 5)) int __NOTHROW_NCX(__LIBCCALL qecvt_r)(__LONGDOUBLE __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign, char *__restrict __buf, __SIZE_TYPE__ __len) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(qecvt_r))(__val, __ndigit, __decptr, __sign, __buf, __len); })
#endif /* !__CRT_HAVE_qecvt_r */
#ifdef __CRT_HAVE_qfcvt_r
__CDECLARE(__ATTR_NONNULL((3, 4, 5)),int,__NOTHROW_NCX,qfcvt_r,(__LONGDOUBLE __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign, char *__restrict __buf, __SIZE_TYPE__ __len),(__val,__ndigit,__decptr,__sign,__buf,__len))
#else /* __CRT_HAVE_qfcvt_r */
#include <local/stdlib/qfcvt_r.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(qfcvt_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((3, 4, 5)) int __NOTHROW_NCX(__LIBCCALL qfcvt_r)(__LONGDOUBLE __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign, char *__restrict __buf, __SIZE_TYPE__ __len) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(qfcvt_r))(__val, __ndigit, __decptr, __sign, __buf, __len); })
#endif /* !__CRT_HAVE_qfcvt_r */
#ifdef __CRT_HAVE_qecvt
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((3, 4)),char *,__NOTHROW_NCX,qecvt,(__LONGDOUBLE __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign),(__val,__ndigit,__decptr,__sign))
#elif defined(__CRT_HAVE__ecvt)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((3, 4)),char *,__NOTHROW_NCX,qecvt,(__LONGDOUBLE __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign),_ecvt,(__val,__ndigit,__decptr,__sign))
#else /* ... */
#include <local/stdlib/qecvt.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(qecvt, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((3, 4)) char *__NOTHROW_NCX(__LIBCCALL qecvt)(__LONGDOUBLE __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(qecvt))(__val, __ndigit, __decptr, __sign); })
#endif /* !... */
#ifdef __CRT_HAVE_qfcvt
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((3, 4)),char *,__NOTHROW_NCX,qfcvt,(__LONGDOUBLE __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign),(__val,__ndigit,__decptr,__sign))
#elif defined(__CRT_HAVE__fcvt)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((3, 4)),char *,__NOTHROW_NCX,qfcvt,(__LONGDOUBLE __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign),_fcvt,(__val,__ndigit,__decptr,__sign))
#else /* ... */
#include <local/stdlib/qfcvt.h>
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
typedef void (__LIBKCALL *__on_exit_func_t)(int __status, void *__arg);
__CDECLARE_OPT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,on_exit,(__on_exit_func_t __func, void *__arg),(__func,__arg))
__CDECLARE_OPT(,int,__NOTHROW_NCX,clearenv,(void),())
#if defined(__CRT_HAVE_mkstemps64) && defined(__USE_FILE_OFFSET64)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,mkstemps,(char *__template_, int __suffixlen),mkstemps64,(__template_,__suffixlen))
#elif defined(__CRT_HAVE_mkstemps)
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,mkstemps,(char *__template_, int __suffixlen),(__template_,__suffixlen))
#endif /* ... */
#ifdef __CRT_HAVE_rpmatch
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,rpmatch,(char const *__response),(__response))
#else /* __CRT_HAVE_rpmatch */
#include <local/stdlib/rpmatch.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(rpmatch, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL rpmatch)(char const *__response) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rpmatch))(__response); })
#endif /* !__CRT_HAVE_rpmatch */
#ifdef __USE_LARGEFILE64
#ifdef __CRT_HAVE_mkstemps64
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,mkstemps64,(char *__template_, int __suffixlen),(__template_,__suffixlen))
#elif defined(__CRT_HAVE_mkstemps)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,mkstemps64,(char *__template_, int __suffixlen),mkstemps,(__template_,__suffixlen))
#endif /* ... */
#endif /* __USE_LARGEFILE64 */
#endif /* __USE_MISC */


#ifdef __USE_POSIX
#ifdef __CRT_HAVE_rand_r
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,rand_r,(unsigned int *__restrict __pseed),(__pseed))
#else /* __CRT_HAVE_rand_r */
#include <local/stdlib/rand_r.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(rand_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL rand_r)(unsigned int *__restrict __pseed) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rand_r))(__pseed); })
#endif /* !__CRT_HAVE_rand_r */
#endif /* __USE_POSIX */


#ifdef __USE_MISC
#ifndef __cfree_defined
#define __cfree_defined 1
#if __has_builtin(__builtin_free) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_free)
__CEIREDIRECT(,void,__NOTHROW_NCX,cfree,(void *__mallptr),free,{ return __builtin_free(__mallptr); })
#elif defined(__CRT_HAVE_free)
__CREDIRECT_VOID(,__NOTHROW_NCX,cfree,(void *__mallptr),free,(__mallptr))
#elif defined(__CRT_HAVE_cfree)
__CDECLARE_VOID(,__NOTHROW_NCX,cfree,(void *__mallptr),(__mallptr))
#else /* ... */
#undef __cfree_defined
#endif /* !... */
#endif /* !__cfree_defined */
#ifndef __NO_FPU
#ifndef __getloadavg_defined
#define __getloadavg_defined 1
#ifdef __CRT_HAVE_getloadavg
__CDECLARE(,int,__NOTHROW_RPC,getloadavg,(double __loadavg[], __STDC_INT_AS_SIZE_T __nelem),(__loadavg,__nelem))
#else /* __CRT_HAVE_getloadavg */
#undef __getloadavg_defined
#endif /* !__CRT_HAVE_getloadavg */
#endif /* !__getloadavg_defined */
#endif /* !__NO_FPU */
#endif /* __USE_MISC */


#if defined(__USE_MISC) || (defined(__USE_XOPEN_EXTENDED) && !defined(__USE_XOPEN2K))
#ifndef __valloc_defined
#define __valloc_defined 1
#ifdef __CRT_HAVE_valloc
__CDECLARE(__ATTR_MALL_PAGEALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,valloc,(__SIZE_TYPE__ __n_bytes),(__n_bytes))
#elif defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)
#include <local/malloc/valloc.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(valloc, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALL_PAGEALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)) void *__NOTHROW_NCX(__LIBCCALL valloc)(__SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(valloc))(__n_bytes); })
#else /* ... */
#undef __valloc_defined
#endif /* !... */
#endif /* !__valloc_defined */
#endif /* __USE_MISC || (__USE_XOPEN_EXTENDED && !__USE_XOPEN2K) */


#ifdef __USE_XOPEN2K
#ifndef __posix_memalign_defined
#define __posix_memalign_defined 1
#if __has_builtin(__builtin_posix_memalign) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_posix_memalign)
__CEIDECLARE(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,posix_memalign,(void **__restrict __pp, __SIZE_TYPE__ __alignment, __SIZE_TYPE__ __n_bytes),{ return __builtin_posix_memalign(__pp, __alignment, __n_bytes); })
#elif defined(__CRT_HAVE_posix_memalign)
__CDECLARE(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,posix_memalign,(void **__restrict __pp, __SIZE_TYPE__ __alignment, __SIZE_TYPE__ __n_bytes),(__pp,__alignment,__n_bytes))
#elif defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc)
#include <local/malloc/posix_memalign.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(posix_memalign, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __errno_t __NOTHROW_NCX(__LIBCCALL posix_memalign)(void **__restrict __pp, __SIZE_TYPE__ __alignment, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(posix_memalign))(__pp, __alignment, __n_bytes); })
#else /* ... */
#undef __posix_memalign_defined
#endif /* !... */
#endif /* !__posix_memalign_defined */
#endif /* __USE_XOPEN2K */


#ifdef __USE_ISOCXX17
#ifndef __CXX_SYSTEM_HEADER
#if !defined(__aligned_alloc_defined) && defined(__std_aligned_alloc_defined)
#define __aligned_alloc_defined 1
__NAMESPACE_STD_USING(aligned_alloc)
#endif /* !__aligned_alloc_defined && __std_aligned_alloc_defined */
#endif /* !__CXX_SYSTEM_HEADER */
#endif /* __USE_ISOCXX17 */

/* aligned_alloc() is defined by both c11 and c++17 */
#ifdef __USE_ISOC11
#ifndef __aligned_alloc_defined
#define __aligned_alloc_defined 1
#ifdef __std_aligned_alloc_defined
__NAMESPACE_STD_USING(aligned_alloc)
#elif __has_builtin(__builtin_aligned_alloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_aligned_alloc)
__CEIDECLARE(__ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_ALIGN(1) __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,aligned_alloc,(size_t __alignment, size_t __n_bytes),{ return __builtin_aligned_alloc(__alignment, __n_bytes); })
#elif defined(__CRT_HAVE_memalign)
__CREDIRECT(__ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_ALIGN(1) __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,aligned_alloc,(size_t __alignment, size_t __n_bytes),memalign,(__alignment,__n_bytes))
#elif defined(__CRT_HAVE_aligned_alloc)
__CDECLARE(__ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_ALIGN(1) __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,aligned_alloc,(size_t __alignment, size_t __n_bytes),(__alignment,__n_bytes))
#elif defined(__CRT_HAVE_posix_memalign)
#include <local/malloc/memalign.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_ALIGN(1) __ATTR_ALLOC_SIZE((2)) void *__NOTHROW_NCX(__LIBCCALL aligned_alloc)(size_t __alignment, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memalign))(__alignment, __n_bytes); }
#else /* ... */
#undef __aligned_alloc_defined
#endif /* !... */
#endif /* !__aligned_alloc_defined */
#endif /* __USE_ISOC11 */

#ifndef MB_CUR_MAX
#ifdef __CRT_HAVE___ctype_get_mb_cur_max
__CDECLARE(__ATTR_WUNUSED,__SIZE_TYPE__,__NOTHROW,__ctype_get_mb_cur_max,(void),())
#define MB_CUR_MAX  (__ctype_get_mb_cur_max())
#else /* __CRT_HAVE___ctype_get_mb_cur_max */
#define MB_CUR_MAX   7 /* == UNICODE_UTF8_CURLEN */
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
#elif defined(__CRT_HAVE_rand) && __SIZEOF_LONG__ == __SIZEOF_INT__
__CREDIRECT(,long,__NOTHROW_NCX,random,(void),rand,())
#else /* ... */
#include <local/stdlib/random.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(random, __FORCELOCAL __ATTR_ARTIFICIAL long __NOTHROW_NCX(__LIBCCALL random)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(random))(); })
#endif /* !... */
#ifdef __CRT_HAVE_srandom
__CDECLARE_VOID(,__NOTHROW_NCX,srandom,(unsigned int __seed),(__seed))
#elif defined(__CRT_HAVE_srand) && __SIZEOF_LONG__ == __SIZEOF_INT__
__CREDIRECT_VOID(,__NOTHROW_NCX,srandom,(unsigned int __seed),srand,(__seed))
#else /* ... */
#include <local/stdlib/srandom.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(srandom, __FORCELOCAL __ATTR_ARTIFICIAL void __NOTHROW_NCX(__LIBCCALL srandom)(unsigned int __seed) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(srandom))(__seed); })
#endif /* !... */
__CDECLARE_OPT(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,initstate,(unsigned int __seed, char *__statebuf, __SIZE_TYPE__ __statelen),(__seed,__statebuf,__statelen))
__CDECLARE_OPT(__ATTR_NONNULL((1)),char *,__NOTHROW_NCX,setstate,(char *__statebuf),(__statebuf))
__CDECLARE_OPT(__ATTR_WUNUSED,char *,__NOTHROW_NCX,l64a,(long __n),(__n))
__CDECLARE_OPT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),long,__NOTHROW_NCX,a64l,(char const *__s),(__s))
/* Load the filesystem location of a given file handle.
 * This function behaves similar to `readlink()', but will also function for
 * non-symlink paths, as well as always return an absolute (unambiguous) path
 * @param: resolved: A buffer of `PATH_MAX' bytes to-be filled with the resulting
 *                   path, or NULL to automatically `malloc()'ate and return a
 *                   buffer of sufficient size. */
__CDECLARE_OPT(__ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_RPC,realpath,(char const *__filename, char *__resolved),(__filename,__resolved))
#endif /* __USE_MISC || __USE_XOPEN_EXTENDED */

#if defined(__USE_MISC) || defined(__USE_XOPEN_EXTENDED) || defined(__USE_KOS)
/* NOTE: I didn't come up with this function (https://docs.oracle.com/cd/E36784_01/html/E36874/frealpath-3c.html),
 *       but it seems to be something that GLibc isn't implementing for some reason...
 *       Because of that, I didn't really know where to put this, so I put it in the
 *       same _SOURCE-block as its `realpath()' companion. */
/* Load the filesystem location of a given file handle.
 * This function behaves similar to `readlink("/proc/self/fd/%d" % fd)'
 * NOTE: You may also pass `NULL' for `resolved' to have a buffer of `buflen'
 *       bytes automatically allocated in the heap, ontop of which you may also
 *       pass `0' for `buflen' to automatically determine the required buffer size. */
__CDECLARE_OPT(__ATTR_WUNUSED,char *,__NOTHROW_RPC,frealpath,(__fd_t __fd, char *__resolved, __SIZE_TYPE__ __buflen),(__fd,__resolved,__buflen))
#endif /* __USE_MISC || __USE_XOPEN_EXTENDED || __USE_KOS */

#ifdef __USE_KOS
/* Load the filesystem location of a given file handle.
 * This function behaves similar to `readlink("/proc/self/fd/%d" % fd)'
 * @param flags: Set of `0 | AT_ALTPATH | AT_DOSPATH'
 * NOTE: You may use `AT_ALTPATH' to cause the path to be printed in alternate
 *       representation mode. This means that if the path would have normally
 *       been printed as a unix path, it would instead be printed as a DOS path.
 *       Similarly, the reverse also applies.
 * NOTE: You may also pass `NULL' for `resolved' to have a buffer of `buflen'
 *       bytes automatically allocated in the heap, ontop of which you may also
 *       pass `0' for `buflen' to automatically determine the required buffer size. */
__CDECLARE_OPT(__ATTR_WUNUSED,char *,__NOTHROW_RPC,frealpath4,(__fd_t __fd, char *__resolved, __SIZE_TYPE__ __buflen, __atflag_t __flags),(__fd,__resolved,__buflen,__flags))
/* Returns the absolute filesystem path for the specified file
 * When `AT_SYMLINK_NOFOLLOW' is given, a final symlink is not dereferenced,
 * causing the path to the symlink itself to be printed. - Otherwise, the
 * filed pointed to by the symblic link is printed.
 * NOTE: You may use `AT_ALTPATH' to cause the path to be printed in alternate
 *       representation mode. This means that if the path would have normally
 *       been printed as a unix path, it would instead be printed as a DOS path.
 *       Similarly, the reverse also applies.
 * NOTE: You may also pass `NULL' for `resolved' to have a buffer of `buflen'
 *       bytes automatically allocated in the heap, ontop of which you may also
 *       pass `0' for `buflen' to automatically determine the required buffer size.
 * @param flags: Set of `0 | AT_ALTPATH | AT_SYMLINK_NOFOLLOW | AT_DOSPATH'
 * @return: NULL: [errno=ERANGE]: `buflen' is too small to fit the entire path */
__CDECLARE_OPT(__ATTR_WUNUSED __ATTR_NONNULL((2)),char *,__NOTHROW_RPC,frealpathat,(__fd_t __dirfd, char const *__filename, char *__resolved, __SIZE_TYPE__ __buflen, __atflag_t __flags),(__dirfd,__filename,__resolved,__buflen,__flags))
#endif /* __USE_KOS */


#ifdef __USE_XOPEN2K
#ifdef __CRT_HAVE_setenv
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,setenv,(char const *__varname, char const *__val, int __replace),(__varname,__val,__replace))
#elif (defined(__CRT_HAVE_getenv) || defined(__LOCAL_environ)) && defined(__CRT_HAVE__putenv_s)
#include <local/stdlib/setenv.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(setenv, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL setenv)(char const *__varname, char const *__val, int __replace) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(setenv))(__varname, __val, __replace); })
#endif /* ... */
#ifdef __CRT_HAVE_unsetenv
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,unsetenv,(char const *__varname),(__varname))
#elif defined(__CRT_HAVE_putenv) || defined(__CRT_HAVE__putenv)
#include <local/stdlib/unsetenv.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(unsetenv, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL unsetenv)(char const *__varname) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unsetenv))(__varname); })
#endif /* ... */
#endif /* __USE_XOPEN2K */


#if (defined(__USE_MISC) || \
     (defined(__USE_XOPEN_EXTENDED) && !defined(__USE_XOPEN2K8)))
#ifndef __mktemp_defined
#define __mktemp_defined 1
#ifdef __CRT_HAVE_mktemp
__CDECLARE(__ATTR_NONNULL((1)),char *,__NOTHROW_NCX,mktemp,(char *__template_),(__template_))
#elif defined(__CRT_HAVE__mktemp)
__CREDIRECT(__ATTR_NONNULL((1)),char *,__NOTHROW_NCX,mktemp,(char *__template_),_mktemp,(__template_))
#elif defined(__CRT_HAVE___mktemp)
__CREDIRECT(__ATTR_NONNULL((1)),char *,__NOTHROW_NCX,mktemp,(char *__template_),__mktemp,(__template_))
#else /* ... */
#undef __mktemp_defined
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
#include <local/stdlib/ecvt.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(ecvt, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((3, 4)) char *__NOTHROW_NCX(__LIBCCALL ecvt)(double __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ecvt))(__val, __ndigit, __decptr, __sign); })
#endif /* !... */
#ifdef __CRT_HAVE_fcvt
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((3, 4)),char *,__NOTHROW_NCX,fcvt,(double __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign),(__val,__ndigit,__decptr,__sign))
#elif defined(__CRT_HAVE__ecvt)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((3, 4)),char *,__NOTHROW_NCX,fcvt,(double __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign),_ecvt,(__val,__ndigit,__decptr,__sign))
#else /* ... */
#include <local/stdlib/fcvt.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fcvt, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((3, 4)) char *__NOTHROW_NCX(__LIBCCALL fcvt)(double __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fcvt))(__val, __ndigit, __decptr, __sign); })
#endif /* !... */
#endif /* !__NO_FPU */
#endif /* __USE_MISC || __USE_DOS || (__USE_XOPEN_EXTENDED && !__USE_XOPEN2K8) */
#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K8)
#ifndef __getsubopt_defined
#define __getsubopt_defined 1
#ifdef __CRT_HAVE_getsubopt
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_NCX,getsubopt,(char **__restrict __optionp, char *const *__restrict __tokens, char **__restrict __valuep),(__optionp,__tokens,__valuep))
#else /* __CRT_HAVE_getsubopt */
#include <local/stdlib/getsubopt.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(getsubopt, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 2, 3)) int __NOTHROW_NCX(__LIBCCALL getsubopt)(char **__restrict __optionp, char *const *__restrict __tokens, char **__restrict __valuep) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getsubopt))(__optionp, __tokens, __valuep); })
#endif /* !__CRT_HAVE_getsubopt */
#endif /* !__getsubopt_defined */
#if defined(__CRT_HAVE_mkstemp64) && defined(__USE_FILE_OFFSET64)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,mkstemp,(char *__template_),mkstemp64,(__template_))
#elif defined(__CRT_HAVE_mkstemp)
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,mkstemp,(char *__template_),(__template_))
#elif defined(__CRT_HAVE_mkstemp64)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,mkstemp,(char *__template_),mkstemp64,(__template_))
#elif defined(__CRT_HAVE_mktemp) || defined(__CRT_HAVE__mktemp) || defined(__CRT_HAVE___mktemp)
#include <local/stdlib/mkstemp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(mkstemp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL mkstemp)(char *__template_) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mkstemp))(__template_); })
#endif /* ... */
#ifdef __USE_LARGEFILE64
#ifdef __CRT_HAVE_mkstemp64
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,mkstemp64,(char *__template_),(__template_))
#elif defined(__CRT_HAVE_mkstemp) && (!defined(__O_LARGEFILE) || !__O_LARGEFILE)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,mkstemp64,(char *__template_),mkstemp,(__template_))
#elif defined(__CRT_HAVE_mkstemp) || defined(__CRT_HAVE_mktemp) || defined(__CRT_HAVE__mktemp) || defined(__CRT_HAVE___mktemp)
#include <local/stdlib/mkstemp64.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(mkstemp64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL mkstemp64)(char *__template_) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mkstemp64))(__template_); })
#endif /* ... */
#endif /* __USE_LARGEFILE64 */
#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K8 */

#ifdef __USE_XOPEN2K8
#ifndef __mkdtemp_defined
#define __mkdtemp_defined 1
#ifdef __CRT_HAVE_mkdtemp
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,mkdtemp,(char *__template_),(__template_))
#elif defined(__CRT_HAVE__mktemp)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,mkdtemp,(char *__template_),_mktemp,(__template_))
#else /* ... */
#undef __mkdtemp_defined
#endif /* !... */
#endif /* !__mkdtemp_defined */
#endif /* __USE_XOPEN2K8 */

#ifdef __USE_XOPEN
#if !defined(__setkey_defined) && defined(__CRT_HAVE_setkey)
#define __setkey_defined 1
/* Setup DES tables according KEY */
__CDECLARE_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,setkey,(char const *__key),(__key))
#endif /* !__setkey_defined && __CRT_HAVE_setkey */
__CDECLARE_OPT(,int,__NOTHROW_NCX,grantpt,(__fd_t __fd),(__fd))
__CDECLARE_OPT(,int,__NOTHROW_NCX,unlockpt,(__fd_t __fd),(__fd))
#ifdef __CRT_HAVE_ptsname
/* Returns the name of the PTY slave (Pseudo TTY slave)
 * associated with the master descriptor `FD' */
__CDECLARE(__ATTR_WUNUSED,char *,__NOTHROW_NCX,ptsname,(__fd_t __fd),(__fd))
#elif defined(__CRT_HAVE_ptsname_r)
#include <local/stdlib/ptsname.h>
/* Returns the name of the PTY slave (Pseudo TTY slave)
 * associated with the master descriptor `FD' */
__NAMESPACE_LOCAL_USING_OR_IMPL(ptsname, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED char *__NOTHROW_NCX(__LIBCCALL ptsname)(__fd_t __fd) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ptsname))(__fd); })
#endif /* ... */
#endif /* __USE_XOPEN */

#ifdef __USE_XOPEN2KXSI
__CDECLARE_OPT(__ATTR_WUNUSED,__fd_t,__NOTHROW_RPC,posix_openpt,(__oflag_t __oflags),(__oflags))
#endif /* __USE_XOPEN2KXSI */
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
#include <local/stdlib/strto32_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) long __NOTHROW_NCX(__LIBCCALL strtol_l)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (long)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strto32_l))(__nptr, __endptr, __base, __locale); }
#elif __SIZEOF_LONG__ == 8
#include <local/stdlib/strto64_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) long __NOTHROW_NCX(__LIBCCALL strtol_l)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (long)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strto64_l))(__nptr, __endptr, __base, __locale); }
#else /* ... */
#include <local/stdlib/strtol_l.h>
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
#elif defined(__CRT_HAVE__strtoll_l) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,strtoul_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_strtoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___strtoll_l) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,strtoul_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__strtoll_l,(__nptr,__endptr,__base,__locale))
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
#include <local/stdlib/strtou32_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) unsigned long __NOTHROW_NCX(__LIBCCALL strtoul_l)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (unsigned long)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtou32_l))(__nptr, __endptr, __base, __locale); }
#elif __SIZEOF_LONG__ == 8
#include <local/stdlib/strtou64_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) unsigned long __NOTHROW_NCX(__LIBCCALL strtoul_l)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (unsigned long)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtou64_l))(__nptr, __endptr, __base, __locale); }
#else /* ... */
#include <local/stdlib/strtoul_l.h>
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
#include <local/stdlib/strto64_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __LONGLONG __NOTHROW_NCX(__LIBCCALL strtoll_l)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__LONGLONG)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strto64_l))(__nptr, __endptr, __base, __locale); }
#elif __SIZEOF_LONG_LONG__ == 8
#include <local/stdlib/strto32_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __LONGLONG __NOTHROW_NCX(__LIBCCALL strtoll_l)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__LONGLONG)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strto32_l))(__nptr, __endptr, __base, __locale); }
#else /* ... */
#include <local/stdlib/strtoll_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strtoll_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __LONGLONG __NOTHROW_NCX(__LIBCCALL strtoll_l)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtoll_l))(__nptr, __endptr, __base, __locale); })
#endif /* !... */
#ifdef __CRT_HAVE_strtoull_l
__CDECLARE(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,strtoull_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtoul_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,strtoull_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoul_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,strtoull_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_strtoul_l,(__nptr,__endptr,__base,__locale))
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
#include <local/stdlib/strtou64_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __ULONGLONG __NOTHROW_NCX(__LIBCCALL strtoull_l)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__ULONGLONG)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtou64_l))(__nptr, __endptr, __base, __locale); }
#elif __SIZEOF_LONG_LONG__ == 8
#include <local/stdlib/strtou32_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __ULONGLONG __NOTHROW_NCX(__LIBCCALL strtoull_l)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__ULONGLONG)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtou32_l))(__nptr, __endptr, __base, __locale); }
#else /* ... */
#include <local/stdlib/strtoull_l.h>
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
#include <local/stdlib/strtod_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strtod_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) double __NOTHROW_NCX(__LIBCCALL strtod_l)(char const *__restrict __nptr, char **__endptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtod_l))(__nptr, __endptr, __locale); })
#endif /* !... */
#ifdef __CRT_HAVE_strtof_l
__CDECLARE(__ATTR_NONNULL((1)),float,__NOTHROW_NCX,strtof_l,(char const *__restrict __nptr, char **__endptr, __locale_t __locale),(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE__strtof_l)
__CREDIRECT(__ATTR_NONNULL((1)),float,__NOTHROW_NCX,strtof_l,(char const *__restrict __nptr, char **__endptr, __locale_t __locale),_strtof_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE___strtof_l)
__CREDIRECT(__ATTR_NONNULL((1)),float,__NOTHROW_NCX,strtof_l,(char const *__restrict __nptr, char **__endptr, __locale_t __locale),__strtof_l,(__nptr,__endptr,__locale))
#else /* ... */
#include <local/stdlib/strtof_l.h>
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
#include <local/stdlib/strtold_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strtold_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __LONGDOUBLE __NOTHROW_NCX(__LIBCCALL strtold_l)(char const *__restrict __nptr, char **__endptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtold_l))(__nptr, __endptr, __locale); })
#endif /* !... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__NO_FPU */
#ifdef __CRT_HAVE_secure_getenv
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,secure_getenv,(char const *__varname),(__varname))
#elif defined(__CRT_HAVE___secure_getenv)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,secure_getenv,(char const *__varname),__secure_getenv,(__varname))
#elif defined(__CRT_HAVE_getenv)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,secure_getenv,(char const *__varname),getenv,(__varname))
#elif defined(__LOCAL_environ)
#include <local/stdlib/getenv.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL secure_getenv)(char const *__varname) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getenv))(__varname); }
#endif /* ... */
/* Returns the name of the PTY slave (Pseudo TTY slave)
 * associated with the master descriptor `FD' */
__CDECLARE_OPT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,ptsname_r,(__fd_t __fd, char *__buf, __SIZE_TYPE__ __buflen),(__fd,__buf,__buflen))
__CDECLARE_OPT(,int,__NOTHROW_RPC,getpt,(void),())
/* Return the result of `realpath(filename)' as a `malloc()'-allocated buffer
 * Upon error, `NULL' is returned instead */
__CDECLARE_OPT(__ATTR_MALLOC __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_RPC,canonicalize_file_name,(char const *__filename),(__filename))
#if defined(__CRT_HAVE_mkostemp64) && defined(__USE_FILE_OFFSET64)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_RPC,mkostemp,(char *__template_, int __flags),mkostemp64,(__template_,__flags))
#elif defined(__CRT_HAVE_mkostemp)
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_RPC,mkostemp,(char *__template_, int __flags),(__template_,__flags))
#elif defined(__CRT_HAVE_mkostemp64)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_RPC,mkostemp,(char *__template_, int __flags),mkostemp64,(__template_,__flags))
#endif /* ... */
#if defined(__CRT_HAVE_mkostemps64) && defined(__USE_FILE_OFFSET64)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_RPC,mkostemps,(char *__template_, int __suffixlen, int __flags),mkostemps64,(__template_,__suffixlen,__flags))
#elif defined(__CRT_HAVE_mkostemps)
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_RPC,mkostemps,(char *__template_, int __suffixlen, int __flags),(__template_,__suffixlen,__flags))
#elif defined(__CRT_HAVE_mkostemps64)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_RPC,mkostemps,(char *__template_, int __suffixlen, int __flags),mkostemps64,(__template_,__suffixlen,__flags))
#endif /* ... */
#ifdef __USE_LARGEFILE64
#ifdef __CRT_HAVE_mkostemp64
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_RPC,mkostemp64,(char *__template_, int __flags),(__template_,__flags))
#elif defined(__CRT_HAVE_mkostemp) && (!defined(__O_LARGEFILE) || !__O_LARGEFILE)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_RPC,mkostemp64,(char *__template_, int __flags),mkostemp,(__template_,__flags))
#endif /* ... */
#ifdef __CRT_HAVE_mkostemps64
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_RPC,mkostemps64,(char *__template_, int __suffixlen, int __flags),(__template_,__suffixlen,__flags))
#elif defined(__CRT_HAVE_mkostemps) && (!defined(__O_LARGEFILE) || !__O_LARGEFILE)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_RPC,mkostemps64,(char *__template_, int __suffixlen, int __flags),mkostemps,(__template_,__suffixlen,__flags))
#endif /* ... */
#endif /* __USE_LARGEFILE64 */
#endif /* __USE_GNU */

#if defined(__USE_KOS) || defined(__USE_MISC) || defined(__USE_BSD)
#ifndef __reallocarray_defined
#define __reallocarray_defined 1
#ifdef __CRT_HAVE_reallocarray
__CDECLARE(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) __ATTR_ALLOC_SIZE((2, 3)),void *,__NOTHROW_NCX,reallocarray,(void *__ptr, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),(__ptr,__elem_count,__elem_size))
#elif defined(__CRT_HAVE_realloc)
#include <local/malloc/reallocarray.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(reallocarray, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) __ATTR_ALLOC_SIZE((2, 3)) void *__NOTHROW_NCX(__LIBCCALL reallocarray)(void *__ptr, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(reallocarray))(__ptr, __elem_count, __elem_size); })
#else /* ... */
#undef __reallocarray_defined
#endif /* !... */
#endif /* !__reallocarray_defined */
#endif /* __USE_KOS || __USE_MISC || __USE_BSD */

#ifdef __USE_KOS
#ifndef __recalloc_defined
#define __recalloc_defined 1
#ifdef __CRT_HAVE_recalloc
__CDECLARE(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,recalloc,(void *__mallptr, __SIZE_TYPE__ __num_bytes),(__mallptr,__num_bytes))
#elif defined(__CRT_HAVE_realloc) && (defined(__CRT_HAVE_malloc_usable_size) || defined(__CRT_HAVE__msize))
#include <local/malloc/recalloc.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(recalloc, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) void *__NOTHROW_NCX(__LIBCCALL recalloc)(void *__mallptr, __SIZE_TYPE__ __num_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(recalloc))(__mallptr, __num_bytes); })
#else /* ... */
#undef __recalloc_defined
#endif /* !... */
#endif /* !__recalloc_defined */
#ifndef __reallocv_defined
#define __reallocv_defined 1
#ifdef __CRT_HAVE_reallocarray
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) __ATTR_ALLOC_SIZE((2, 3)),void *,__NOTHROW_NCX,reallocv,(void *__ptr, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),reallocarray,(__ptr,__elem_count,__elem_size))
#elif defined(__CRT_HAVE_realloc)
#include <local/malloc/reallocarray.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) __ATTR_ALLOC_SIZE((2, 3)) void *__NOTHROW_NCX(__LIBCCALL reallocv)(void *__ptr, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(reallocarray))(__ptr, __elem_count, __elem_size); }
#else /* ... */
#undef __reallocv_defined
#endif /* !... */
#endif /* !__reallocv_defined */
#ifndef __recallocv_defined
#define __recallocv_defined 1
#ifdef __CRT_HAVE_recallocv
__CDECLARE(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2, 3)),void *,__NOTHROW_NCX,recallocv,(void *__mallptr, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),(__mallptr,__elem_count,__elem_size))
#elif defined(__CRT_HAVE__recalloc)
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2, 3)),void *,__NOTHROW_NCX,recallocv,(void *__mallptr, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),_recalloc,(__mallptr,__elem_count,__elem_size))
#elif defined(__CRT_HAVE_realloc) && (defined(__CRT_HAVE_malloc_usable_size) || defined(__CRT_HAVE__msize))
#include <local/malloc/recallocv.h>
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
#elif defined(__CRT_HAVE_realloc)
} /* extern "C++" */
#include <local/malloc/reallocarray.h>
extern "C++" {
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) __ATTR_ALLOC_SIZE((2, 3)) void *__NOTHROW_NCX(__LIBCCALL realloc)(void *__ptr, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(reallocarray))(__ptr, __elem_count, __elem_size); }
#endif /* ... */
#ifdef __CRT_HAVE_recallocv
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2, 3)),void *,__NOTHROW_NCX,recalloc,(void *__mallptr, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),recallocv,(__mallptr,__elem_count,__elem_size))
#elif defined(__CRT_HAVE__recalloc)
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2, 3)),void *,__NOTHROW_NCX,recalloc,(void *__mallptr, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),_recalloc,(__mallptr,__elem_count,__elem_size))
#elif defined(__CRT_HAVE_realloc) && (defined(__CRT_HAVE_malloc_usable_size) || defined(__CRT_HAVE__msize))
} /* extern "C++" */
#include <local/malloc/recallocv.h>
extern "C++" {
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2, 3)) void *__NOTHROW_NCX(__LIBCCALL recalloc)(void *__mallptr, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(recallocv))(__mallptr, __elem_count, __elem_size); }
#endif /* ... */
} /* extern "C++" */
#else /* __cplusplus */
#ifdef __malloc_defined
#define __PRIVATE_malloc_1 (malloc)
#define __PRIVATE_malloc_2 __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mallocv)
#undef malloc
#define malloc(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_malloc_, (__VA_ARGS__))(__VA_ARGS__)
#endif /* __malloc_defined */
#ifdef __calloc_defined
#define __PRIVATE_calloc_1(num_bytes) (calloc)(1, num_bytes)
#define __PRIVATE_calloc_2            (calloc)
#undef calloc
#define calloc(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_calloc_, (__VA_ARGS__))(__VA_ARGS__)
#endif /* __calloc_defined */
#if defined(__realloc_defined) && defined(__reallocarray_defined)
#define __PRIVATE_realloc_2 (realloc)
#define __PRIVATE_realloc_3 (reallocarray)
#undef realloc
#define realloc(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_realloc_, (__VA_ARGS__))(__VA_ARGS__)
#endif /* __realloc_defined && __reallocarray_defined */
#if defined(__recalloc_defined) && defined(__recallocv_defined)
#define __PRIVATE_recalloc_2 (recalloc)
#define __PRIVATE_recalloc_3 (recallocv)
#undef recalloc
#define recalloc(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_recalloc_, (__VA_ARGS__))(__VA_ARGS__)
#endif /* __recalloc_defined && __recallocv_defined */
#endif /* !__cplusplus */
#endif /* !__MALLOC_OVERLOADS_DEFINED */
#endif /* __USE_STRING_OVERLOADS */
#endif /* __USE_KOS */

#ifdef __USE_BSD
#ifdef __CRT_HAVE_reallocf
__CDECLARE(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,reallocf,(void *__mallptr, __SIZE_TYPE__ __num_bytes),(__mallptr,__num_bytes))
#elif defined(__CRT_HAVE_realloc) && (defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree))
#include <local/stdlib/reallocf.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(reallocf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) void *__NOTHROW_NCX(__LIBCCALL reallocf)(void *__mallptr, __SIZE_TYPE__ __num_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(reallocf))(__mallptr, __num_bytes); })
#endif /* ... */
#ifdef __CRT_HAVE_recallocarray
/* Same as `recallocv(mallptr, new_elem_count, elem_size)', but also ensure that
 * when `mallptr != NULL', memory pointed to by the old `mallptr...+=old_elem_count*elem_size'
 * is explicitly freed to zero (s.a. `freezero()') when reallocation must move the memory block */
__CDECLARE(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((3, 4)),void *,__NOTHROW_NCX,recallocarray,(void *__mallptr, __SIZE_TYPE__ __old_elem_count, __SIZE_TYPE__ __new_elem_count, __SIZE_TYPE__ __elem_size),(__mallptr,__old_elem_count,__new_elem_count,__elem_size))
#elif (defined(__CRT_HAVE_recallocv) || defined(__CRT_HAVE__recalloc) || defined(__CRT_HAVE_realloc)) && (defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)) && (defined(__CRT_HAVE_malloc_usable_size) || defined(__CRT_HAVE__msize))
#include <local/stdlib/recallocarray.h>
/* Same as `recallocv(mallptr, new_elem_count, elem_size)', but also ensure that
 * when `mallptr != NULL', memory pointed to by the old `mallptr...+=old_elem_count*elem_size'
 * is explicitly freed to zero (s.a. `freezero()') when reallocation must move the memory block */
__NAMESPACE_LOCAL_USING_OR_IMPL(recallocarray, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((3, 4)) void *__NOTHROW_NCX(__LIBCCALL recallocarray)(void *__mallptr, __SIZE_TYPE__ __old_elem_count, __SIZE_TYPE__ __new_elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(recallocarray))(__mallptr, __old_elem_count, __new_elem_count, __elem_size); })
#endif /* ... */
#ifdef __CRT_HAVE_freezero
/* Same as `free(mallptr)', but also ensure that the memory region
 * described by `mallptr...+=num_bytes' is explicitly freed to zero, or
 * immediately returned to the OS, rather than being left in cache
 * while still containing its previous contents. */
__CDECLARE_VOID(,__NOTHROW_NCX,freezero,(void *__mallptr, __SIZE_TYPE__ __num_bytes),(__mallptr,__num_bytes))
#elif defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree)
#include <local/stdlib/freezero.h>
/* Same as `free(mallptr)', but also ensure that the memory region
 * described by `mallptr...+=num_bytes' is explicitly freed to zero, or
 * immediately returned to the OS, rather than being left in cache
 * while still containing its previous contents. */
__NAMESPACE_LOCAL_USING_OR_IMPL(freezero, __FORCELOCAL __ATTR_ARTIFICIAL void __NOTHROW_NCX(__LIBCCALL freezero)(void *__mallptr, __SIZE_TYPE__ __num_bytes) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(freezero))(__mallptr, __num_bytes); })
#endif /* ... */
#endif /* __USE_BSD */
#ifdef __USE_SOLARIS
#ifndef __uid_t_defined
#define __uid_t_defined 1
typedef __uid_t uid_t; /* User ID */
#endif /* !__uid_t_defined */
#ifndef __closefrom_defined
#define __closefrom_defined 1
#ifdef __CRT_HAVE_closefrom
/* Close all file descriptors with indices `>= lowfd' (s.a. `fcntl(F_CLOSEM)') */
__CDECLARE_VOID(,__NOTHROW_NCX,closefrom,(__fd_t __lowfd),(__lowfd))
#else /* __CRT_HAVE_closefrom */
#include <asm/fcntl.h>
#if (defined(__CRT_HAVE_fcntl) || defined(__CRT_HAVE___fcntl)) && defined(__F_CLOSEM)
#include <local/unistd/closefrom.h>
/* Close all file descriptors with indices `>= lowfd' (s.a. `fcntl(F_CLOSEM)') */
__NAMESPACE_LOCAL_USING_OR_IMPL(closefrom, __FORCELOCAL __ATTR_ARTIFICIAL void __NOTHROW_NCX(__LIBCCALL closefrom)(__fd_t __lowfd) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(closefrom))(__lowfd); })
#else /* (__CRT_HAVE_fcntl || __CRT_HAVE___fcntl) && __F_CLOSEM */
#undef __closefrom_defined
#endif /* (!__CRT_HAVE_fcntl && !__CRT_HAVE___fcntl) || !__F_CLOSEM */
#endif /* !__CRT_HAVE_closefrom */
#endif /* !__closefrom_defined */
#ifndef __dup2_defined
#define __dup2_defined 1
#ifdef __CRT_HAVE_dup2
/* >> dup2(2)
 * @return: NEWFD: Returns the new handle upon success.
 * Duplicate a file referred to by `OLDFD' into `NEWFD' */
__CDECLARE(,__fd_t,__NOTHROW_NCX,dup2,(__fd_t __oldfd, __fd_t __newfd),(__oldfd,__newfd))
#elif defined(__CRT_HAVE__dup2)
/* >> dup2(2)
 * @return: NEWFD: Returns the new handle upon success.
 * Duplicate a file referred to by `OLDFD' into `NEWFD' */
__CREDIRECT(,__fd_t,__NOTHROW_NCX,dup2,(__fd_t __oldfd, __fd_t __newfd),_dup2,(__oldfd,__newfd))
#elif defined(__CRT_HAVE___dup2)
/* >> dup2(2)
 * @return: NEWFD: Returns the new handle upon success.
 * Duplicate a file referred to by `OLDFD' into `NEWFD' */
__CREDIRECT(,__fd_t,__NOTHROW_NCX,dup2,(__fd_t __oldfd, __fd_t __newfd),__dup2,(__oldfd,__newfd))
#else /* ... */
#undef __dup2_defined
#endif /* !... */
#endif /* !__dup2_defined */
#ifndef __getcwd_defined
#define __getcwd_defined 1
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
#define __getlogin_defined 1
#ifdef __CRT_HAVE_getlogin
__CDECLARE(__ATTR_WUNUSED,char *,__NOTHROW_NCX,getlogin,(void),())
#else /* __CRT_HAVE_getlogin */
#undef __getlogin_defined
#endif /* !__CRT_HAVE_getlogin */
#endif /* !__getlogin_defined */
#ifndef __getpass_defined
#define __getpass_defined 1
#ifdef __CRT_HAVE_getpass
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_RPC,getpass,(char const *__restrict __prompt),(__prompt))
#else /* __CRT_HAVE_getpass */
#undef __getpass_defined
#endif /* !__CRT_HAVE_getpass */
#endif /* !__getpass_defined */
#ifndef __getpw_defined
#define __getpw_defined 1
#ifdef __CRT_HAVE_getpw
/* Re-construct the password-file line for the given uid in the
 * given buffer. This knows the format that the caller will
 * expect, but this need not be the format of the password file */
__CDECLARE(,int,__NOTHROW_RPC,getpw,(__uid_t __uid, char *__buffer),(__uid,__buffer))
#elif defined(__CRT_HAVE_getpwuid)
#include <local/pwd/getpw.h>
/* Re-construct the password-file line for the given uid in the
 * given buffer. This knows the format that the caller will
 * expect, but this need not be the format of the password file */
__NAMESPACE_LOCAL_USING_OR_IMPL(getpw, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_RPC(__LIBCCALL getpw)(__uid_t __uid, char *__buffer) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getpw))(__uid, __buffer); })
#else /* ... */
#undef __getpw_defined
#endif /* !... */
#endif /* !__getpw_defined */
#ifndef __isatty_defined
#define __isatty_defined 1
#ifdef __CRT_HAVE_isatty
/* >> isatty(2)
 * @return: 1: Is a tty
 * @return: 0: Not a tty
 * Check if the given file handle `FD' refers to a TTY */
__CDECLARE(__ATTR_WUNUSED,int,__NOTHROW_NCX,isatty,(__fd_t __fd),(__fd))
#elif defined(__CRT_HAVE__isatty)
/* >> isatty(2)
 * @return: 1: Is a tty
 * @return: 0: Not a tty
 * Check if the given file handle `FD' refers to a TTY */
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW_NCX,isatty,(__fd_t __fd),_isatty,(__fd))
#else /* ... */
#undef __isatty_defined
#endif /* !... */
#endif /* !__isatty_defined */
#ifndef __memalign_defined
#define __memalign_defined 1
#if __has_builtin(__builtin_aligned_alloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_aligned_alloc)
__CEIREDIRECT(__ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_ALIGN(1) __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,memalign,(size_t __alignment, size_t __n_bytes),aligned_alloc,{ return __builtin_aligned_alloc(__alignment, __n_bytes); })
#elif defined(__CRT_HAVE_memalign)
__CDECLARE(__ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_ALIGN(1) __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,memalign,(size_t __alignment, size_t __n_bytes),(__alignment,__n_bytes))
#elif defined(__CRT_HAVE_aligned_alloc)
__CREDIRECT(__ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_ALIGN(1) __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,memalign,(size_t __alignment, size_t __n_bytes),aligned_alloc,(__alignment,__n_bytes))
#elif defined(__CRT_HAVE_posix_memalign)
#include <local/malloc/memalign.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(memalign, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_ALIGN(1) __ATTR_ALLOC_SIZE((2)) void *__NOTHROW_NCX(__LIBCCALL memalign)(size_t __alignment, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memalign))(__alignment, __n_bytes); })
#else /* ... */
#undef __memalign_defined
#endif /* !... */
#endif /* !__memalign_defined */
#ifndef __ttyname_defined
#define __ttyname_defined 1
#ifdef __CRT_HAVE_ttyname
/* >> ttyname(3)
 * Return the name of a TTY given its file descriptor */
__CDECLARE(__ATTR_WUNUSED,char *,__NOTHROW_RPC,ttyname,(__fd_t __fd),(__fd))
#else /* __CRT_HAVE_ttyname */
#undef __ttyname_defined
#endif /* !__CRT_HAVE_ttyname */
#endif /* !__ttyname_defined */
#ifdef __CRT_HAVE_getexecname
/* Returns the absolute filename of the main executable (s.a. `program_invocation_name') */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,char const *,__NOTHROW_NCX,getexecname,(void),())
#else /* __CRT_HAVE_getexecname */
#include <local/program_invocation_name.h>
#ifdef __LOCAL_program_invocation_name
#include <local/stdlib/getexecname.h>
/* Returns the absolute filename of the main executable (s.a. `program_invocation_name') */
__NAMESPACE_LOCAL_USING_OR_IMPL(getexecname, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED char const *__NOTHROW_NCX(__LIBCCALL getexecname)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getexecname))(); })
#endif /* __LOCAL_program_invocation_name */
#endif /* !__CRT_HAVE_getexecname */
#ifndef ____fdwalk_func_t_defined
#define ____fdwalk_func_t_defined 1
typedef int (__LIBKCALL *__fdwalk_func_t)(void *__cookie, __fd_t __fd);
#endif /* !____fdwalk_func_t_defined */
#ifdef __CRT_HAVE_fdwalk
/* Enumerate all open file descriptors by invoking `(*func)(cookie, FD)' for each of them
 * If during any of these invocations, `(*func)(...)' returns non-zero, enumeration stops,
 * and `fdwalk()' returns with that same value. If `(*func)(...)' is never called, or all
 * invocations return 0, `fdwalk()' will also return 0. */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,fdwalk,(__fdwalk_func_t __func, void *__cookie),(__func,__cookie))
#else /* __CRT_HAVE_fdwalk */
#include <asm/fcntl.h>
#if (defined(__CRT_HAVE_fcntl) || defined(__CRT_HAVE___fcntl)) && defined(__F_NEXT)
#include <local/stdlib/fdwalk.h>
/* Enumerate all open file descriptors by invoking `(*func)(cookie, FD)' for each of them
 * If during any of these invocations, `(*func)(...)' returns non-zero, enumeration stops,
 * and `fdwalk()' returns with that same value. If `(*func)(...)' is never called, or all
 * invocations return 0, `fdwalk()' will also return 0. */
__NAMESPACE_LOCAL_USING_OR_IMPL(fdwalk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL fdwalk)(__fdwalk_func_t __func, void *__cookie) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fdwalk))(__func, __cookie); })
#endif /* (__CRT_HAVE_fcntl || __CRT_HAVE___fcntl) && __F_NEXT */
#endif /* !__CRT_HAVE_fdwalk */
#endif /* __USE_SOLARIS */

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
#define __errno_t_defined 1
typedef int errno_t;
#endif /* !__errno_t_defined */

#ifndef _ONEXIT_T_DEFINED
#define _ONEXIT_T_DEFINED 1
typedef int (__LIBDCALL *_onexit_t)(void);
#endif  /* _ONEXIT_T_DEFINED */
#ifndef onexit_t
#define onexit_t _onexit_t
#endif /* !onexit_t */

#ifndef _CRT_ERRNO_DEFINED
#define _CRT_ERRNO_DEFINED 1
#ifndef errno
#ifndef ____errno_location_defined
#define ____errno_location_defined 1
#ifdef __CRT_HAVE___errno_location
__CDECLARE(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,__errno_t *,__NOTHROW_NCX,__errno_location,(void),())
#elif defined(__CRT_HAVE__errno)
__CREDIRECT(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,__errno_t *,__NOTHROW_NCX,__errno_location,(void),_errno,())
#elif defined(__CRT_HAVE___errno)
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

#ifndef ____doserrno_defined
#define ____doserrno_defined 1
#ifdef __CRT_HAVE___doserrno
__CDECLARE(__ATTR_CONST,__UINT32_TYPE__ *,__NOTHROW_NCX,__doserrno,(void),())
#else /* __CRT_HAVE___doserrno */
#undef ____doserrno_defined
#endif /* !__CRT_HAVE___doserrno */
#endif /* !____doserrno_defined */
__CDECLARE_OPT(,errno_t,__NOTHROW_NCX,_get_doserrno,(__UINT32_TYPE__ *__perr),(__perr))
__CDECLARE_OPT(,errno_t,__NOTHROW_NCX,_set_doserrno,(__UINT32_TYPE__ __err),(__err))
#ifdef ____doserrno_defined
#define _doserrno (*__doserrno())
#endif /* ____doserrno_defined */

#ifndef ___environ_defined
#define ___environ_defined 1
#undef _environ
#if defined(__CRT_HAVE_environ) && !defined(__NO_ASMNAME)
__LIBC char **_environ __ASMNAME("environ");
#define _environ _environ
#elif defined(__CRT_HAVE_environ)
#ifndef __environ_defined
#define __environ_defined 1
#undef environ
__LIBC char **environ;
#endif /* !__environ_defined */
#define _environ environ
#elif defined(__CRT_HAVE__environ)
__LIBC char **_environ;
#define _environ _environ
#elif defined(__CRT_HAVE___environ) && !defined(__NO_ASMNAME)
__LIBC char **_environ __ASMNAME("__environ");
#define _environ _environ
#elif defined(__CRT_HAVE___environ)
#ifndef ____environ_defined
#define ____environ_defined 1
#undef __environ
__LIBC char **__environ;
#endif /* !____environ_defined */
#define _environ __environ
#elif defined(__CRT_HAVE___p__environ)
#ifndef ____p__environ_defined
#define ____p__environ_defined 1
__CDECLARE(__ATTR_WUNUSED __ATTR_CONST __ATTR_RETNONNULL,char ***,__NOTHROW,__p__environ,(void),())
#endif /* !____p__environ_defined */
#define _environ (*__p__environ())
#else /* ... */
#undef ___environ_defined
#endif /* !... */
#endif /* !___environ_defined */

#ifndef __argc
#ifdef __CRT_HAVE___argc
__LIBC int __argc;
#define __argc __argc
#else /* __CRT_HAVE___argc */
#ifndef ____p___argc_defined
#define ____p___argc_defined 1
#ifdef __CRT_HAVE___p___argc
__CDECLARE(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,int *,__NOTHROW_NCX,__p___argc,(void),())
#else /* __CRT_HAVE___p___argc */
#undef ____p___argc_defined
#endif /* !__CRT_HAVE___p___argc */
#endif /* !____p___argc_defined */
#ifdef ____p___argc_defined
#define __argc (*__p___argc())
#endif /* ____p___argc_defined */
#endif /* !__CRT_HAVE___argc */
#endif /* !__argc */

#ifndef __argv
#ifdef __CRT_HAVE___argv
__LIBC char **__argv;
#else /* __CRT_HAVE___argv */
#ifndef ____p___argv_defined
#define ____p___argv_defined 1
#ifdef __CRT_HAVE___p___argv
__CDECLARE(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,char ***,__NOTHROW_NCX,__p___argv,(void),())
#else /* __CRT_HAVE___p___argv */
#undef ____p___argv_defined
#endif /* !__CRT_HAVE___p___argv */
#endif /* !____p___argv_defined */
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
#ifndef ____p___wargv_defined
#define ____p___wargv_defined 1
#ifdef __CRT_HAVE___p___wargv
__CDECLARE(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,wchar_t ***,__NOTHROW_NCX,__p___wargv,(void),())
#else /* __CRT_HAVE___p___wargv */
#undef ____p___wargv_defined
#endif /* !__CRT_HAVE___p___wargv */
#endif /* !____p___wargv_defined */
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
#ifndef ____p__wenviron_defined
#define ____p__wenviron_defined 1
#ifdef __CRT_HAVE___p__wenviron
__CDECLARE(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,wchar_t ***,__NOTHROW_NCX,__p__wenviron,(void),())
#else /* __CRT_HAVE___p__wenviron */
#undef ____p__wenviron_defined
#endif /* !__CRT_HAVE___p__wenviron */
#endif /* !____p__wenviron_defined */
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
#ifndef ____p__wpgmptr_defined
#define ____p__wpgmptr_defined 1
#ifdef __CRT_HAVE___p__wpgmptr
__CDECLARE(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,wchar_t **,__NOTHROW_NCX,__p__wpgmptr,(void),())
#else /* __CRT_HAVE___p__wpgmptr */
#undef ____p__wpgmptr_defined
#endif /* !__CRT_HAVE___p__wpgmptr */
#endif /* !____p__wpgmptr_defined */
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
#define ____p__pgmptr_defined 1
#ifdef __CRT_HAVE___p__pgmptr
/* Alias for argv[0], as passed to main() */
__CDECLARE(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,char **,__NOTHROW_NCX,__p__pgmptr,(void),())
#elif defined(__CRT_HAVE___p_program_invocation_name)
/* Alias for argv[0], as passed to main() */
__CREDIRECT(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,char **,__NOTHROW_NCX,__p__pgmptr,(void),__p_program_invocation_name,())
#else /* ... */
#include <local/program_invocation_name.h>
#ifdef __LOCAL_program_invocation_name_p
#include <local/stdlib/__p__pgmptr.h>
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
#ifndef ____p___initenv_defined
#define ____p___initenv_defined 1
#ifdef __CRT_HAVE___p___initenv
/* Access to the initial environment block */
__CDECLARE(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,char ***,__NOTHROW_NCX,__p___initenv,(void),())
#else /* __CRT_HAVE___p___initenv */
#undef ____p___initenv_defined
#endif /* !__CRT_HAVE___p___initenv */
#endif /* !____p___initenv_defined */
#ifdef ____p___initenv_defined
#define __initenv (*__p___initenv())
#endif /* ____p___initenv_defined */
#endif /* !__CRT_HAVE___initenv */
#endif /* !__initenv */
#ifndef __winitenv
#ifdef __CRT_HAVE___winitenv
__LIBC wchar_t **__winitenv;
#else /* __CRT_HAVE___winitenv */
#ifndef ____p___winitenv_defined
#define ____p___winitenv_defined 1
#ifdef __CRT_HAVE___p___winitenv
/* Access to the initial environment block */
__CDECLARE(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,wchar_t ***,__NOTHROW_NCX,__p___winitenv,(void),())
#else /* __CRT_HAVE___p___winitenv */
#undef ____p___winitenv_defined
#endif /* !__CRT_HAVE___p___winitenv */
#endif /* !____p___winitenv_defined */
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
#define ___purecall_handler_defined 1
typedef void (__LIBDCALL *_purecall_handler)(void);
#endif /* !___purecall_handler_defined */
__CDECLARE_OPT(,_purecall_handler,__NOTHROW_NCX,_set_purecall_handler,(_purecall_handler __handler),(__handler))
__CDECLARE_OPT(,_purecall_handler,__NOTHROW_NCX,_get_purecall_handler,(void),())

#ifndef ___invalid_parameter_handler_defined
#define ___invalid_parameter_handler_defined 1
typedef void (__LIBDCALL *_invalid_parameter_handler)(wchar_t const *, wchar_t const *, wchar_t const *, unsigned int, __UINTPTR_TYPE__);
#endif /* !___invalid_parameter_handler_defined */
__CDECLARE_OPT(,_invalid_parameter_handler,__NOTHROW_NCX,_set_invalid_parameter_handler,(_invalid_parameter_handler __handler),(__handler))
__CDECLARE_OPT(,_invalid_parameter_handler,__NOTHROW_NCX,_get_invalid_parameter_handler,(void),())

#ifdef __CRT_HAVE__get_pgmptr
__CDECLARE(,errno_t,__NOTHROW_NCX,_get_pgmptr,(char **__pvalue),(__pvalue))
#else /* __CRT_HAVE__get_pgmptr */
#include <local/program_invocation_name.h>
#ifdef __LOCAL_program_invocation_name
#include <local/stdlib/_get_pgmptr.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_get_pgmptr, __FORCELOCAL __ATTR_ARTIFICIAL errno_t __NOTHROW_NCX(__LIBCCALL _get_pgmptr)(char **__pvalue) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_get_pgmptr))(__pvalue); })
#endif /* __LOCAL_program_invocation_name */
#endif /* !__CRT_HAVE__get_pgmptr */
#ifdef __CRT_HAVE__get_wpgmptr
__CDECLARE(,errno_t,__NOTHROW_NCX,_get_wpgmptr,(wchar_t **__pvalue),(__pvalue))
#elif defined(__CRT_HAVE___p__wpgmptr)
#include <local/stdlib/_get_wpgmptr.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_get_wpgmptr, __FORCELOCAL __ATTR_ARTIFICIAL errno_t __NOTHROW_NCX(__LIBCCALL _get_wpgmptr)(wchar_t **__pvalue) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_get_wpgmptr))(__pvalue); })
#endif /* ... */

#ifdef __CRT_HAVE__fmode
__LIBC int _fmode;
#else /* ... */
#ifndef ____p__fmode_defined
#define ____p__fmode_defined 1
#ifdef __CRT_HAVE___p__fmode
__CDECLARE(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,int *,__NOTHROW_NCX,__p__fmode,(void),())
#else /* __CRT_HAVE___p__fmode */
#undef ____p__fmode_defined
#endif /* !__CRT_HAVE___p__fmode */
#endif /* !____p__fmode_defined */
#ifdef ____p__fmode_defined
#define _fmode (*__p__fmode())
#endif /* ____p__fmode_defined */
#endif /* !... */
__CDECLARE_OPT(,errno_t,__NOTHROW_NCX,_set_fmode,(int __mode),(__mode))
__CDECLARE_OPT(,errno_t,__NOTHROW_NCX,_get_fmode,(int *__pmode),(__pmode))

__CDECLARE_OPT(,unsigned int,__NOTHROW_NCX,_set_abort_behavior,(unsigned int __flags, unsigned int __mask),(__flags,__mask))

#ifdef __INT64_TYPE__
#if defined(_MSC_VER) && defined(__LIBCCALL_IS_LIBDCALL)
extern __ATTR_CONST __INT64_TYPE__ (__LIBDCALL _abs64)(__INT64_TYPE__ __x);
#pragma intrinsic(_abs64)
#else /* _MSC_VER && __LIBCCALL_IS_LIBDCALL */
#ifdef __CRT_HAVE__abs64
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__INT64_TYPE__,__NOTHROW,_abs64,(__INT64_TYPE__ __x),(__x))
#elif defined(__CRT_HAVE_abs) && __SIZEOF_INT__ == 8
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__INT64_TYPE__,__NOTHROW,_abs64,(__INT64_TYPE__ __x),abs,(__x))
#elif defined(__CRT_HAVE_llabs) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__INT64_TYPE__,__NOTHROW,_abs64,(__INT64_TYPE__ __x),llabs,(__x))
#elif defined(__CRT_HAVE_imaxabs) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__INT64_TYPE__,__NOTHROW,_abs64,(__INT64_TYPE__ __x),imaxabs,(__x))
#elif __SIZEOF_INT__ == 8
#include <local/stdlib/abs.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __INT64_TYPE__ __NOTHROW(__LIBCCALL _abs64)(__INT64_TYPE__ __x) { return (__INT64_TYPE__)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(abs))((int)__x); }
#elif __SIZEOF_LONG_LONG__ == 8
#include <local/stdlib/llabs.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __INT64_TYPE__ __NOTHROW(__LIBCCALL _abs64)(__INT64_TYPE__ __x) { return (__INT64_TYPE__)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(llabs))((__LONGLONG)__x); }
#else /* ... */
#include <local/stdlib/_abs64.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_abs64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __INT64_TYPE__ __NOTHROW(__LIBCCALL _abs64)(__INT64_TYPE__ __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_abs64))(__x); })
#endif /* !... */
#endif /* !_MSC_VER || !__LIBCCALL_IS_LIBDCALL */
#endif /* __INT64_TYPE__ */
#ifndef __NO_FPU
#ifdef __CRT_HAVE__atof_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),double,__NOTHROW_NCX,_atof_l,(char const *__restrict __nptr, __locale_t __locale),(__nptr,__locale))
#else /* __CRT_HAVE__atof_l */
#include <local/stdlib/_atof_l.h>
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
#include <local/stdlib/_atoi_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_atoi_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL _atoi_l)(char const *__restrict __nptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_atoi_l))(__nptr, __locale); })
#endif /* !... */
#ifdef __CRT_HAVE__atol_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),long int,__NOTHROW_NCX,_atol_l,(char const *__restrict __nptr, __locale_t __locale),(__nptr,__locale))
#elif defined(__CRT_HAVE__atoi_l) && __SIZEOF_LONG__ == __SIZEOF_INT__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),long int,__NOTHROW_NCX,_atol_l,(char const *__restrict __nptr, __locale_t __locale),_atoi_l,(__nptr,__locale))
#elif defined(__CRT_HAVE__atoll_l) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),long int,__NOTHROW_NCX,_atol_l,(char const *__restrict __nptr, __locale_t __locale),_atoll_l,(__nptr,__locale))
#else /* ... */
#include <local/stdlib/_atol_l.h>
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
#include <local/stdlib/_atoll_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_atoll_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __LONGLONG __NOTHROW_NCX(__LIBCCALL _atoll_l)(char const *__restrict __nptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_atoll_l))(__nptr, __locale); })
#endif /* !... */
#endif /* __LONGLONG */

#ifdef _MSC_VER
extern unsigned short (_byteswap_ushort)(unsigned short __x);
extern unsigned long (_byteswap_ulong)(unsigned long __x);
extern unsigned __int64 (_byteswap_uint64)(unsigned __int64 __x);
#pragma intrinsic(_byteswap_ushort)
#pragma intrinsic(_byteswap_ulong)
#pragma intrinsic(_byteswap_uint64)
#else /* _MSC_VER */
#ifdef __CRT_HAVE__byteswap_ushort
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__UINT16_TYPE__,__NOTHROW_NCX,_byteswap_ushort,(__UINT16_TYPE__ __val),(__val))
#else /* __CRT_HAVE__byteswap_ushort */
#include <local/stdlib/_byteswap_ushort.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_byteswap_ushort, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __UINT16_TYPE__ __NOTHROW_NCX(__LIBCCALL _byteswap_ushort)(__UINT16_TYPE__ __val) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_byteswap_ushort))(__val); })
#endif /* !__CRT_HAVE__byteswap_ushort */
#ifdef __CRT_HAVE__byteswap_ulong
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__UINT32_TYPE__,__NOTHROW_NCX,_byteswap_ulong,(__UINT32_TYPE__ __val),(__val))
#else /* __CRT_HAVE__byteswap_ulong */
#include <local/stdlib/_byteswap_ulong.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_byteswap_ulong, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __UINT32_TYPE__ __NOTHROW_NCX(__LIBCCALL _byteswap_ulong)(__UINT32_TYPE__ __val) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_byteswap_ulong))(__val); })
#endif /* !__CRT_HAVE__byteswap_ulong */
#ifdef __UINT64_TYPE__
#ifdef __CRT_HAVE__byteswap_uint64
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__UINT64_TYPE__,__NOTHROW_NCX,_byteswap_uint64,(__UINT64_TYPE__ __val),(__val))
#else /* __CRT_HAVE__byteswap_uint64 */
#include <local/stdlib/_byteswap_uint64.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_byteswap_uint64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __UINT64_TYPE__ __NOTHROW_NCX(__LIBCCALL _byteswap_uint64)(__UINT64_TYPE__ __val) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_byteswap_uint64))(__val); })
#endif /* !__CRT_HAVE__byteswap_uint64 */
#endif /* __UINT64_TYPE__ */
#define _byteswap_ushort(x) __hybrid_bswap16(x)
#define _byteswap_ulong(x)  __hybrid_bswap32(x)
#ifdef __UINT64_TYPE__
#define _byteswap_uint64(x) __hybrid_bswap64(x)
#endif /* __UINT64_TYPE__ */
#endif /* !_MSC_VER */
#ifdef __USE_DOS_SLIB
#ifndef __rsize_t_defined
#define __rsize_t_defined 1
typedef __SIZE_TYPE__ rsize_t;
#endif /* !__rsize_t_defined */

#ifndef _CRT_ALGO_DEFINED
#define _CRT_ALGO_DEFINED 1
#ifndef __dos_compar_d_fn_t_defined
#define __dos_compar_d_fn_t_defined 1
typedef int (__LIBDCALL *__dos_compar_d_fn_t)(void *__arg, void const *__a, void const *__b);
#endif /* !__dos_compar_d_fn_t_defined */
#ifdef __CRT_HAVE_bsearch_s
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 2, 5)),void *,__THROWING,bsearch_s,(void const *__key, void const *__base, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size, __dos_compar_d_fn_t __compar, void *__arg),(__key,__base,__elem_count,__elem_size,__compar,__arg))
#else /* __CRT_HAVE_bsearch_s */
#include <local/stdlib/bsearch_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(bsearch_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 2, 5)) void *(__LIBCCALL bsearch_s)(void const *__key, void const *__base, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size, __dos_compar_d_fn_t __compar, void *__arg) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(bsearch_s))(__key, __base, __elem_count, __elem_size, __compar, __arg); })
#endif /* !__CRT_HAVE_bsearch_s */
#ifdef __CRT_HAVE_qsort_s
__CDECLARE_VOID(__ATTR_NONNULL((1, 4)),__THROWING,qsort_s,(void *__base, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size, __dos_compar_d_fn_t __compar, void *__arg),(__base,__elem_count,__elem_size,__compar,__arg))
#else /* __CRT_HAVE_qsort_s */
#include <local/stdlib/qsort_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(qsort_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 4)) void (__LIBCCALL qsort_s)(void *__base, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size, __dos_compar_d_fn_t __compar, void *__arg) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(qsort_s))(__base, __elem_count, __elem_size, __compar, __arg); })
#endif /* !__CRT_HAVE_qsort_s */
#endif  /* _CRT_ALGO_DEFINED */

__CDECLARE_OPT(__ATTR_NONNULL((1, 2, 4)),errno_t,__NOTHROW_NCX,getenv_s,(__SIZE_TYPE__ *__psize, char *__buf, rsize_t __buflen, char const *__varname),(__psize,__buf,__buflen,__varname))
__CDECLARE_OPT(__ATTR_NONNULL((1, 2, 3)),errno_t,__NOTHROW_NCX,_dupenv_s,(char **__restrict __pbuf, __SIZE_TYPE__ *__pbuflen, char const *__varname),(__pbuf,__pbuflen,__varname))
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
#include <local/stdlib/itoa.h>
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
#include <local/stdlib/ltoa.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) char *__NOTHROW_NCX(__LIBCCALL _ltoa)(long __val, char *__buf, int __radix) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ltoa))(__val, __buf, __radix); }
#endif /* !... */
#ifdef __CRT_HAVE_ultoa
__CREDIRECT(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,_ultoa,(unsigned long __val, char *__buf, int __radix),ultoa,(__val,__buf,__radix))
#elif defined(__CRT_HAVE__ultoa)
__CDECLARE(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,_ultoa,(unsigned long __val, char *__buf, int __radix),(__val,__buf,__radix))
#elif defined(__CRT_HAVE__ui64toa) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,_ultoa,(unsigned long __val, char *__buf, int __radix),_ui64toa,(__val,__buf,__radix))
#else /* ... */
#include <local/stdlib/ultoa.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) char *__NOTHROW_NCX(__LIBCCALL _ultoa)(unsigned long __val, char *__buf, int __radix) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ultoa))(__val, __buf, __radix); }
#endif /* !... */
#ifdef __CRT_HAVE__itoa_s
__CDECLARE(__ATTR_NONNULL((2)),errno_t,__NOTHROW_NCX,_itoa_s,(int __val, char *__buf, __SIZE_TYPE__ __buflen, int __radix),(__val,__buf,__buflen,__radix))
#elif defined(__CRT_HAVE__ltoa_s) && __SIZEOF_INT__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_NONNULL((2)),errno_t,__NOTHROW_NCX,_itoa_s,(int __val, char *__buf, __SIZE_TYPE__ __buflen, int __radix),_ltoa_s,(__val,__buf,__buflen,__radix))
#elif defined(__CRT_HAVE__i64toa_s) && __SIZEOF_INT__ == 8
__CREDIRECT(__ATTR_NONNULL((2)),errno_t,__NOTHROW_NCX,_itoa_s,(int __val, char *__buf, __SIZE_TYPE__ __buflen, int __radix),_i64toa_s,(__val,__buf,__buflen,__radix))
#else /* ... */
#include <local/stdlib/_itoa_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_itoa_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) errno_t __NOTHROW_NCX(__LIBCCALL _itoa_s)(int __val, char *__buf, __SIZE_TYPE__ __buflen, int __radix) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_itoa_s))(__val, __buf, __buflen, __radix); })
#endif /* !... */
#ifdef __CRT_HAVE__ltoa_s
__CDECLARE(__ATTR_NONNULL((2)),errno_t,__NOTHROW_NCX,_ltoa_s,(long __val, char *__buf, __SIZE_TYPE__ __buflen, int __radix),(__val,__buf,__buflen,__radix))
#elif defined(__CRT_HAVE__itoa_s) && __SIZEOF_LONG__ == __SIZEOF_INT__
__CREDIRECT(__ATTR_NONNULL((2)),errno_t,__NOTHROW_NCX,_ltoa_s,(long __val, char *__buf, __SIZE_TYPE__ __buflen, int __radix),_itoa_s,(__val,__buf,__buflen,__radix))
#elif defined(__CRT_HAVE__i64toa_s) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_NONNULL((2)),errno_t,__NOTHROW_NCX,_ltoa_s,(long __val, char *__buf, __SIZE_TYPE__ __buflen, int __radix),_i64toa_s,(__val,__buf,__buflen,__radix))
#else /* ... */
#include <local/stdlib/_ltoa_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_ltoa_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) errno_t __NOTHROW_NCX(__LIBCCALL _ltoa_s)(long __val, char *__buf, __SIZE_TYPE__ __buflen, int __radix) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_ltoa_s))(__val, __buf, __buflen, __radix); })
#endif /* !... */
#ifdef __CRT_HAVE__ultoa_s
__CDECLARE(__ATTR_NONNULL((2)),errno_t,__NOTHROW_NCX,_ultoa_s,(unsigned long __val, char *__buf, __SIZE_TYPE__ __buflen, int __radix),(__val,__buf,__buflen,__radix))
#elif defined(__CRT_HAVE__ui64toa_s) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_NONNULL((2)),errno_t,__NOTHROW_NCX,_ultoa_s,(unsigned long __val, char *__buf, __SIZE_TYPE__ __buflen, int __radix),_ui64toa_s,(__val,__buf,__buflen,__radix))
#else /* ... */
#include <local/stdlib/_ultoa_s.h>
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
#include <local/stdlib/_i64toa.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_i64toa, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) char *__NOTHROW_NCX(__LIBCCALL _i64toa)(__INT64_TYPE__ __val, char *__buf, int __radix) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_i64toa))(__val, __buf, __radix); })
#endif /* !... */
#ifdef __CRT_HAVE__ui64toa
__CDECLARE(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,_ui64toa,(__UINT64_TYPE__ __val, char *__buf, int __radix),(__val,__buf,__radix))
#elif defined(__CRT_HAVE_ultoa) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,_ui64toa,(__UINT64_TYPE__ __val, char *__buf, int __radix),ultoa,(__val,__buf,__radix))
#elif defined(__CRT_HAVE__ultoa) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,_ui64toa,(__UINT64_TYPE__ __val, char *__buf, int __radix),_ultoa,(__val,__buf,__radix))
#else /* ... */
#include <local/stdlib/_ui64toa.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_ui64toa, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) char *__NOTHROW_NCX(__LIBCCALL _ui64toa)(__UINT64_TYPE__ __val, char *__buf, int __radix) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_ui64toa))(__val, __buf, __radix); })
#endif /* !... */
#ifdef __CRT_HAVE__i64toa_s
__CDECLARE(__ATTR_NONNULL((2)),errno_t,__NOTHROW_NCX,_i64toa_s,(__INT64_TYPE__ __val, char *__buf, __SIZE_TYPE__ __buflen, int __radix),(__val,__buf,__buflen,__radix))
#elif defined(__CRT_HAVE__ltoa_s) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_NONNULL((2)),errno_t,__NOTHROW_NCX,_i64toa_s,(__INT64_TYPE__ __val, char *__buf, __SIZE_TYPE__ __buflen, int __radix),_ltoa_s,(__val,__buf,__buflen,__radix))
#elif defined(__CRT_HAVE__itoa_s) && __SIZEOF_INT__ == 8
__CREDIRECT(__ATTR_NONNULL((2)),errno_t,__NOTHROW_NCX,_i64toa_s,(__INT64_TYPE__ __val, char *__buf, __SIZE_TYPE__ __buflen, int __radix),_itoa_s,(__val,__buf,__buflen,__radix))
#else /* ... */
#include <local/stdlib/_i64toa_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_i64toa_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) errno_t __NOTHROW_NCX(__LIBCCALL _i64toa_s)(__INT64_TYPE__ __val, char *__buf, __SIZE_TYPE__ __buflen, int __radix) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_i64toa_s))(__val, __buf, __buflen, __radix); })
#endif /* !... */
#ifdef __CRT_HAVE__ui64toa_s
__CDECLARE(__ATTR_NONNULL((2)),errno_t,__NOTHROW_NCX,_ui64toa_s,(__UINT64_TYPE__ __val, char *__buf, __SIZE_TYPE__ __buflen, int __radix),(__val,__buf,__buflen,__radix))
#elif defined(__CRT_HAVE__ultoa_s) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_NONNULL((2)),errno_t,__NOTHROW_NCX,_ui64toa_s,(__UINT64_TYPE__ __val, char *__buf, __SIZE_TYPE__ __buflen, int __radix),_ultoa_s,(__val,__buf,__buflen,__radix))
#else /* ... */
#include <local/stdlib/_ui64toa_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_ui64toa_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) errno_t __NOTHROW_NCX(__LIBCCALL _ui64toa_s)(__UINT64_TYPE__ __val, char *__buf, __SIZE_TYPE__ __buflen, int __radix) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_ui64toa_s))(__val, __buf, __buflen, __radix); })
#endif /* !... */
#ifdef __CRT_HAVE_strto64
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_strtoi64,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strto64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__strtoi64)
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_strtoi64,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtol) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_strtoi64,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoll) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_strtoi64,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoq) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_strtoi64,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoimax) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_strtoi64,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoimax,(__nptr,__endptr,__base))
#else /* ... */
#include <local/stdlib/strto64.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __INT64_TYPE__ __NOTHROW_NCX(__LIBCCALL _strtoi64)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strto64))(__nptr, __endptr, __base); }
#endif /* !... */
#ifdef __CRT_HAVE_strtou64
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,_strtoui64,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtou64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__strtoui64)
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,_strtoui64,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoul) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,_strtoui64,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoull) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,_strtoui64,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtouq) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,_strtoui64,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoumax) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,_strtoui64,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoumax,(__nptr,__endptr,__base))
#else /* ... */
#include <local/stdlib/strtou64.h>
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
#elif defined(__CRT_HAVE_strtoimax_l) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_strtoi64_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoimax_l) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_strtoi64_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_strtoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___strtoimax_l) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_strtoi64_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__strtoimax_l,(__nptr,__endptr,__base,__locale))
#else /* ... */
#include <local/stdlib/strto64_l.h>
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
#elif defined(__CRT_HAVE_strtoumax_l) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,_strtoui64_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoumax_l) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,_strtoui64_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_strtoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___strtoumax_l) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,_strtoui64_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__strtoumax_l,(__nptr,__endptr,__base,__locale))
#else /* ... */
#include <local/stdlib/strtou64_l.h>
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
#include <local/stdlib/_atoi64.h>
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
#include <local/stdlib/_atoi64_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_atoi64_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __INT64_TYPE__ __NOTHROW_NCX(__LIBCCALL _atoi64_l)(char const *__restrict __nptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_atoi64_l))(__nptr, __locale); })
#endif /* !... */
#endif /* __UINT64_TYPE__ */
#ifdef __CRT_HAVE__mbstrlen
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,_mbstrlen,(char const *__str),(__str))
#else /* __CRT_HAVE__mbstrlen */
#include <local/stdlib/_mbstrlen.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_mbstrlen, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL _mbstrlen)(char const *__str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_mbstrlen))(__str); })
#endif /* !__CRT_HAVE__mbstrlen */
#ifdef __CRT_HAVE__mbstrnlen
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,_mbstrnlen,(char const *__str, __SIZE_TYPE__ __maxlen),(__str,__maxlen))
#else /* __CRT_HAVE__mbstrnlen */
#include <local/stdlib/_mbstrnlen.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_mbstrnlen, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL _mbstrnlen)(char const *__str, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_mbstrnlen))(__str, __maxlen); })
#endif /* !__CRT_HAVE__mbstrnlen */
#ifdef __CRT_HAVE__mbstrlen_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,_mbstrlen_l,(char const *__str, __locale_t __locale),(__str,__locale))
#else /* __CRT_HAVE__mbstrlen_l */
#include <local/stdlib/_mbstrlen_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_mbstrlen_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL _mbstrlen_l)(char const *__str, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_mbstrlen_l))(__str, __locale); })
#endif /* !__CRT_HAVE__mbstrlen_l */
#ifdef __CRT_HAVE__mbstrnlen_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,_mbstrnlen_l,(char const *__str, __SIZE_TYPE__ __maxlen, __locale_t __locale),(__str,__maxlen,__locale))
#else /* __CRT_HAVE__mbstrnlen_l */
#include <local/stdlib/_mbstrnlen_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_mbstrnlen_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL _mbstrnlen_l)(char const *__str, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_mbstrnlen_l))(__str, __maxlen, __locale); })
#endif /* !__CRT_HAVE__mbstrnlen_l */
#ifdef __CRT_HAVE__mblen_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,_mblen_l,(char const *__str, __SIZE_TYPE__ __maxlen, __locale_t __locale),(__str,__maxlen,__locale))
#else /* __CRT_HAVE__mblen_l */
#include <local/stdlib/_mblen_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_mblen_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL _mblen_l)(char const *__str, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_mblen_l))(__str, __maxlen, __locale); })
#endif /* !__CRT_HAVE__mblen_l */
#ifdef __CRT_HAVE__mbtowc_l
__CDECLARE(,int,__NOTHROW_NCX,_mbtowc_l,(wchar_t *__dst, char const *__src, __SIZE_TYPE__ __srclen, __locale_t __locale),(__dst,__src,__srclen,__locale))
#else /* __CRT_HAVE__mbtowc_l */
#include <local/stdlib/_mbtowc_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_mbtowc_l, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_NCX(__LIBCCALL _mbtowc_l)(wchar_t *__dst, char const *__src, __SIZE_TYPE__ __srclen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_mbtowc_l))(__dst, __src, __srclen, __locale); })
#endif /* !__CRT_HAVE__mbtowc_l */
#ifdef __CRT_HAVE__mbstowcs_l
__CDECLARE(,__SIZE_TYPE__,__NOTHROW_NCX,_mbstowcs_l,(wchar_t *__dst, char const *__src, __SIZE_TYPE__ __dstlen, __locale_t __locale),(__dst,__src,__dstlen,__locale))
#else /* __CRT_HAVE__mbstowcs_l */
#include <local/stdlib/_mbstowcs_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_mbstowcs_l, __FORCELOCAL __ATTR_ARTIFICIAL __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL _mbstowcs_l)(wchar_t *__dst, char const *__src, __SIZE_TYPE__ __dstlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_mbstowcs_l))(__dst, __src, __dstlen, __locale); })
#endif /* !__CRT_HAVE__mbstowcs_l */
#ifdef __CRT_HAVE__mbstowcs_s
__CDECLARE(,errno_t,__NOTHROW_NCX,_mbstowcs_s,(__SIZE_TYPE__ *__presult, wchar_t *__dst, __SIZE_TYPE__ __dstsize, char const *__src, __SIZE_TYPE__ __dstlen),(__presult,__dst,__dstsize,__src,__dstlen))
#else /* __CRT_HAVE__mbstowcs_s */
#include <local/stdlib/_mbstowcs_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_mbstowcs_s, __FORCELOCAL __ATTR_ARTIFICIAL errno_t __NOTHROW_NCX(__LIBCCALL _mbstowcs_s)(__SIZE_TYPE__ *__presult, wchar_t *__dst, __SIZE_TYPE__ __dstsize, char const *__src, __SIZE_TYPE__ __dstlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_mbstowcs_s))(__presult, __dst, __dstsize, __src, __dstlen); })
#endif /* !__CRT_HAVE__mbstowcs_s */
#ifdef __CRT_HAVE_mbstowcs_s
__CDECLARE(,errno_t,__NOTHROW_NCX,mbstowcs_s,(__SIZE_TYPE__ *__presult, wchar_t *__dst, __SIZE_TYPE__ __dstsize, char const *__src, __SIZE_TYPE__ __dstlen),(__presult,__dst,__dstsize,__src,__dstlen))
#else /* __CRT_HAVE_mbstowcs_s */
#include <local/stdlib/mbstowcs_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(mbstowcs_s, __FORCELOCAL __ATTR_ARTIFICIAL errno_t __NOTHROW_NCX(__LIBCCALL mbstowcs_s)(__SIZE_TYPE__ *__presult, wchar_t *__dst, __SIZE_TYPE__ __dstsize, char const *__src, __SIZE_TYPE__ __dstlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mbstowcs_s))(__presult, __dst, __dstsize, __src, __dstlen); })
#endif /* !__CRT_HAVE_mbstowcs_s */
#ifdef __CRT_HAVE__mbstowcs_s_l
__CDECLARE(,errno_t,__NOTHROW_NCX,_mbstowcs_s_l,(__SIZE_TYPE__ *__presult, wchar_t *__dst, __SIZE_TYPE__ __dstsize, char const *__src, __SIZE_TYPE__ __dstlen, __locale_t __locale),(__presult,__dst,__dstsize,__src,__dstlen,__locale))
#else /* __CRT_HAVE__mbstowcs_s_l */
#include <local/stdlib/_mbstowcs_s_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_mbstowcs_s_l, __FORCELOCAL __ATTR_ARTIFICIAL errno_t __NOTHROW_NCX(__LIBCCALL _mbstowcs_s_l)(__SIZE_TYPE__ *__presult, wchar_t *__dst, __SIZE_TYPE__ __dstsize, char const *__src, __SIZE_TYPE__ __dstlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_mbstowcs_s_l))(__presult, __dst, __dstsize, __src, __dstlen, __locale); })
#endif /* !__CRT_HAVE__mbstowcs_s_l */
#ifdef __CRT_HAVE_rand_s
__CDECLARE(__ATTR_NONNULL((1)),errno_t,__NOTHROW_NCX,rand_s,(unsigned int *__restrict __randval),(__randval))
#else /* __CRT_HAVE_rand_s */
#include <local/stdlib/rand_s.h>
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
#include <local/stdlib/strto32_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) long __NOTHROW_NCX(__LIBCCALL _strtol_l)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (long)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strto32_l))(__nptr, __endptr, __base, __locale); }
#elif __SIZEOF_LONG__ == 8
#include <local/stdlib/strto64_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) long __NOTHROW_NCX(__LIBCCALL _strtol_l)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (long)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strto64_l))(__nptr, __endptr, __base, __locale); }
#else /* ... */
#include <local/stdlib/strtol_l.h>
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
#elif defined(__CRT_HAVE__strtoll_l) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,_strtoul_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_strtoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___strtoll_l) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,_strtoul_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__strtoll_l,(__nptr,__endptr,__base,__locale))
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
#include <local/stdlib/strtou32_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) unsigned long __NOTHROW_NCX(__LIBCCALL _strtoul_l)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (unsigned long)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtou32_l))(__nptr, __endptr, __base, __locale); }
#elif __SIZEOF_LONG__ == 8
#include <local/stdlib/strtou64_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) unsigned long __NOTHROW_NCX(__LIBCCALL _strtoul_l)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (unsigned long)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtou64_l))(__nptr, __endptr, __base, __locale); }
#else /* ... */
#include <local/stdlib/strtoul_l.h>
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
#include <local/stdlib/strto64_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __LONGLONG __NOTHROW_NCX(__LIBCCALL _strtoll_l)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__LONGLONG)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strto64_l))(__nptr, __endptr, __base, __locale); }
#elif __SIZEOF_LONG_LONG__ == 8
#include <local/stdlib/strto32_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __LONGLONG __NOTHROW_NCX(__LIBCCALL _strtoll_l)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__LONGLONG)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strto32_l))(__nptr, __endptr, __base, __locale); }
#else /* ... */
#include <local/stdlib/strtoll_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __LONGLONG __NOTHROW_NCX(__LIBCCALL _strtoll_l)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtoll_l))(__nptr, __endptr, __base, __locale); }
#endif /* !... */
#ifdef __CRT_HAVE_strtoull_l
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,_strtoull_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtoul_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,_strtoull_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoul_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,_strtoull_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_strtoul_l,(__nptr,__endptr,__base,__locale))
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
#include <local/stdlib/strtou64_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __ULONGLONG __NOTHROW_NCX(__LIBCCALL _strtoull_l)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__ULONGLONG)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtou64_l))(__nptr, __endptr, __base, __locale); }
#elif __SIZEOF_LONG_LONG__ == 8
#include <local/stdlib/strtou32_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __ULONGLONG __NOTHROW_NCX(__LIBCCALL _strtoull_l)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__ULONGLONG)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtou32_l))(__nptr, __endptr, __base, __locale); }
#else /* ... */
#include <local/stdlib/strtoull_l.h>
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
#include <local/stdlib/strtod_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) double __NOTHROW_NCX(__LIBCCALL _strtod_l)(char const *__restrict __nptr, char **__endptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtod_l))(__nptr, __endptr, __locale); }
#endif /* !... */
#ifdef __CRT_HAVE_strtof_l
__CREDIRECT(__ATTR_NONNULL((1)),float,__NOTHROW_NCX,_strtof_l,(char const *__restrict __nptr, char **__endptr, __locale_t __locale),strtof_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE__strtof_l)
__CDECLARE(__ATTR_NONNULL((1)),float,__NOTHROW_NCX,_strtof_l,(char const *__restrict __nptr, char **__endptr, __locale_t __locale),(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE___strtof_l)
__CREDIRECT(__ATTR_NONNULL((1)),float,__NOTHROW_NCX,_strtof_l,(char const *__restrict __nptr, char **__endptr, __locale_t __locale),__strtof_l,(__nptr,__endptr,__locale))
#else /* ... */
#include <local/stdlib/strtof_l.h>
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
#include <local/stdlib/strtold_l.h>
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
#include <local/stdlib/_wctomb_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wctomb_l, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_NCX(__LIBCCALL _wctomb_l)(char *__buf, wchar_t __wc, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wctomb_l))(__buf, __wc, __locale); })
#endif /* !__CRT_HAVE__wctomb_l */

#ifdef __USE_DOS_SLIB
#ifdef __CRT_HAVE_wctomb_s
__CDECLARE(__ATTR_NONNULL((1, 2)),errno_t,__NOTHROW_NCX,wctomb_s,(int *__presult, char *__buf, rsize_t __buflen, wchar_t __wc),(__presult,__buf,__buflen,__wc))
#else /* __CRT_HAVE_wctomb_s */
#include <local/stdlib/wctomb_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wctomb_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) errno_t __NOTHROW_NCX(__LIBCCALL wctomb_s)(int *__presult, char *__buf, rsize_t __buflen, wchar_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wctomb_s))(__presult, __buf, __buflen, __wc); })
#endif /* !__CRT_HAVE_wctomb_s */
#endif /* __USE_DOS_SLIB */
#ifdef __CRT_HAVE__wctomb_s_l
__CDECLARE(__ATTR_NONNULL((1, 2)),errno_t,__NOTHROW_NCX,_wctomb_s_l,(int *__presult, char *__buf, __SIZE_TYPE__ __buflen, wchar_t __wc, __locale_t __locale),(__presult,__buf,__buflen,__wc,__locale))
#else /* __CRT_HAVE__wctomb_s_l */
#include <local/stdlib/_wctomb_s_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wctomb_s_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) errno_t __NOTHROW_NCX(__LIBCCALL _wctomb_s_l)(int *__presult, char *__buf, __SIZE_TYPE__ __buflen, wchar_t __wc, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wctomb_s_l))(__presult, __buf, __buflen, __wc, __locale); })
#endif /* !__CRT_HAVE__wctomb_s_l */
#ifdef __CRT_HAVE__wcstombs_s_l
__CDECLARE(__ATTR_NONNULL((1, 2, 4)),errno_t,__NOTHROW_NCX,_wcstombs_s_l,(__SIZE_TYPE__ *__presult, char *__buf, __SIZE_TYPE__ __buflen, wchar_t const *__src, __SIZE_TYPE__ __maxlen, __locale_t __locale),(__presult,__buf,__buflen,__src,__maxlen,__locale))
#else /* __CRT_HAVE__wcstombs_s_l */
#include <local/stdlib/_wcstombs_s_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wcstombs_s_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2, 4)) errno_t __NOTHROW_NCX(__LIBCCALL _wcstombs_s_l)(__SIZE_TYPE__ *__presult, char *__buf, __SIZE_TYPE__ __buflen, wchar_t const *__src, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wcstombs_s_l))(__presult, __buf, __buflen, __src, __maxlen, __locale); })
#endif /* !__CRT_HAVE__wcstombs_s_l */
#ifdef __CRT_HAVE__wcstombs_l
__CDECLARE(__ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,_wcstombs_l,(char *__dst, wchar_t const *__src, __SIZE_TYPE__ __maxlen, __locale_t __locale),(__dst,__src,__maxlen,__locale))
#else /* __CRT_HAVE__wcstombs_l */
#include <local/stdlib/_wcstombs_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wcstombs_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL _wcstombs_l)(char *__dst, wchar_t const *__src, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wcstombs_l))(__dst, __src, __maxlen, __locale); })
#endif /* !__CRT_HAVE__wcstombs_l */
#ifdef __CRT_HAVE_wcstombs_s
__CDECLARE(__ATTR_NONNULL((1, 2, 4)),errno_t,__NOTHROW_NCX,wcstombs_s,(__SIZE_TYPE__ *__presult, char *__buf, __SIZE_TYPE__ __buflen, wchar_t const *__src, __SIZE_TYPE__ __maxlen),(__presult,__buf,__buflen,__src,__maxlen))
#else /* __CRT_HAVE_wcstombs_s */
#include <local/stdlib/wcstombs_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstombs_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2, 4)) errno_t __NOTHROW_NCX(__LIBCCALL wcstombs_s)(__SIZE_TYPE__ *__presult, char *__buf, __SIZE_TYPE__ __buflen, wchar_t const *__src, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstombs_s))(__presult, __buf, __buflen, __src, __maxlen); })
#endif /* !__CRT_HAVE_wcstombs_s */

/* DOS malloc extensions */
#ifdef __CRT_HAVE_recallocv
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2, 3)),void *,__NOTHROW_NCX,_recalloc,(void *__mallptr, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),recallocv,(__mallptr,__elem_count,__elem_size))
#elif defined(__CRT_HAVE__recalloc)
__CDECLARE(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2, 3)),void *,__NOTHROW_NCX,_recalloc,(void *__mallptr, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),(__mallptr,__elem_count,__elem_size))
#elif defined(__CRT_HAVE_realloc) && (defined(__CRT_HAVE_malloc_usable_size) || defined(__CRT_HAVE__msize))
#include <local/malloc/recallocv.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2, 3)) void *__NOTHROW_NCX(__LIBCCALL _recalloc)(void *__mallptr, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(recallocv))(__mallptr, __elem_count, __elem_size); }
#endif /* ... */
#ifdef __CRT_HAVE__aligned_malloc
__CDECLARE(__ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_ALIGN(2) __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,_aligned_malloc,(__SIZE_TYPE__ __num_bytes, __SIZE_TYPE__ __min_alignment),(__num_bytes,__min_alignment))
#elif defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)
#include <local/stdlib/_aligned_malloc.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_aligned_malloc, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_ALIGN(2) __ATTR_ALLOC_SIZE((1)) void *__NOTHROW_NCX(__LIBCCALL _aligned_malloc)(__SIZE_TYPE__ __num_bytes, __SIZE_TYPE__ __min_alignment) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_aligned_malloc))(__num_bytes, __min_alignment); })
#endif /* ... */
#ifdef __CRT_HAVE__aligned_offset_malloc
__CDECLARE(__ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,_aligned_offset_malloc,(__SIZE_TYPE__ __num_bytes, __SIZE_TYPE__ __min_alignment, __SIZE_TYPE__ __offset),(__num_bytes,__min_alignment,__offset))
#elif defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)
#include <local/stdlib/_aligned_offset_malloc.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_aligned_offset_malloc, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)) void *__NOTHROW_NCX(__LIBCCALL _aligned_offset_malloc)(__SIZE_TYPE__ __num_bytes, __SIZE_TYPE__ __min_alignment, __SIZE_TYPE__ __offset) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_aligned_offset_malloc))(__num_bytes, __min_alignment, __offset); })
#endif /* ... */
#ifdef __CRT_HAVE__aligned_realloc
__CDECLARE(__ATTR_WUNUSED __ATTR_ALLOC_ALIGN(3) __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,_aligned_realloc,(void *__aligned_mallptr, __SIZE_TYPE__ __newsize, __SIZE_TYPE__ __min_alignment),(__aligned_mallptr,__newsize,__min_alignment))
#elif (defined(__CRT_HAVE__aligned_malloc) || defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)) && (defined(__CRT_HAVE__aligned_free) || defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree))
#include <local/stdlib/_aligned_realloc.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_aligned_realloc, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_ALLOC_ALIGN(3) __ATTR_ALLOC_SIZE((2)) void *__NOTHROW_NCX(__LIBCCALL _aligned_realloc)(void *__aligned_mallptr, __SIZE_TYPE__ __newsize, __SIZE_TYPE__ __min_alignment) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_aligned_realloc))(__aligned_mallptr, __newsize, __min_alignment); })
#endif /* ... */
#ifdef __CRT_HAVE__aligned_recalloc
__CDECLARE(__ATTR_WUNUSED __ATTR_ALLOC_ALIGN(4) __ATTR_ALLOC_SIZE((2, 3)),void *,__NOTHROW_NCX,_aligned_recalloc,(void *__aligned_mallptr, __SIZE_TYPE__ __count, __SIZE_TYPE__ __num_bytes, __SIZE_TYPE__ __min_alignment),(__aligned_mallptr,__count,__num_bytes,__min_alignment))
#elif (defined(__CRT_HAVE__aligned_malloc) || defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)) && (defined(__CRT_HAVE__aligned_free) || defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree))
#include <local/stdlib/_aligned_recalloc.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_aligned_recalloc, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_ALLOC_ALIGN(4) __ATTR_ALLOC_SIZE((2, 3)) void *__NOTHROW_NCX(__LIBCCALL _aligned_recalloc)(void *__aligned_mallptr, __SIZE_TYPE__ __count, __SIZE_TYPE__ __num_bytes, __SIZE_TYPE__ __min_alignment) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_aligned_recalloc))(__aligned_mallptr, __count, __num_bytes, __min_alignment); })
#endif /* ... */
#ifdef __CRT_HAVE__aligned_offset_realloc
__CDECLARE(__ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,_aligned_offset_realloc,(void *__aligned_mallptr, __SIZE_TYPE__ __newsize, __SIZE_TYPE__ __min_alignment, __SIZE_TYPE__ __offset),(__aligned_mallptr,__newsize,__min_alignment,__offset))
#elif (defined(__CRT_HAVE__aligned_offset_malloc) || defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)) && (defined(__CRT_HAVE__aligned_free) || defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree))
#include <local/stdlib/_aligned_offset_realloc.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_aligned_offset_realloc, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) void *__NOTHROW_NCX(__LIBCCALL _aligned_offset_realloc)(void *__aligned_mallptr, __SIZE_TYPE__ __newsize, __SIZE_TYPE__ __min_alignment, __SIZE_TYPE__ __offset) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_aligned_offset_realloc))(__aligned_mallptr, __newsize, __min_alignment, __offset); })
#endif /* ... */
#ifdef __CRT_HAVE__aligned_offset_recalloc
__CDECLARE(__ATTR_WUNUSED __ATTR_ALLOC_SIZE((2, 3)),void *,__NOTHROW_NCX,_aligned_offset_recalloc,(void *__aligned_mallptr, __SIZE_TYPE__ __count, __SIZE_TYPE__ __num_bytes, __SIZE_TYPE__ __min_alignment, __SIZE_TYPE__ __offset),(__aligned_mallptr,__count,__num_bytes,__min_alignment,__offset))
#elif (defined(__CRT_HAVE__aligned_offset_malloc) || defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)) && (defined(__CRT_HAVE__aligned_free) || defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree))
#include <local/stdlib/_aligned_offset_recalloc.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_aligned_offset_recalloc, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2, 3)) void *__NOTHROW_NCX(__LIBCCALL _aligned_offset_recalloc)(void *__aligned_mallptr, __SIZE_TYPE__ __count, __SIZE_TYPE__ __num_bytes, __SIZE_TYPE__ __min_alignment, __SIZE_TYPE__ __offset) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_aligned_offset_recalloc))(__aligned_mallptr, __count, __num_bytes, __min_alignment, __offset); })
#endif /* ... */
#ifdef __CRT_HAVE__aligned_msize
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,__SIZE_TYPE__,__NOTHROW_NCX,_aligned_msize,(void *__aligned_mallptr, __SIZE_TYPE__ __min_alignment, __SIZE_TYPE__ __offset),(__aligned_mallptr,__min_alignment,__offset))
#else /* __CRT_HAVE__aligned_msize */
#include <local/stdlib/_aligned_msize.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_aligned_msize, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL _aligned_msize)(void *__aligned_mallptr, __SIZE_TYPE__ __min_alignment, __SIZE_TYPE__ __offset) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_aligned_msize))(__aligned_mallptr, __min_alignment, __offset); })
#endif /* !__CRT_HAVE__aligned_msize */
#ifdef __CRT_HAVE__aligned_free
__CDECLARE_VOID(,__NOTHROW_NCX,_aligned_free,(void *__aligned_mallptr),(__aligned_mallptr))
#elif defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree)
#include <local/stdlib/_aligned_free.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_aligned_free, __FORCELOCAL __ATTR_ARTIFICIAL void __NOTHROW_NCX(__LIBCCALL _aligned_free)(void *__aligned_mallptr) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_aligned_free))(__aligned_mallptr); })
#endif /* ... */

#define _CVTBUFSIZE   349
__CDECLARE_OPT(,char *,__NOTHROW_RPC,_fullpath,(char *__buf, char const *__path, __SIZE_TYPE__ __buflen),(__buf,__path,__buflen))
#ifndef __NO_FPU
#ifdef __CRT_HAVE__ecvt_s
__CDECLARE(__ATTR_NONNULL((1, 5, 6)),errno_t,__NOTHROW_NCX,_ecvt_s,(char *__buf, __SIZE_TYPE__ __buflen, double __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign),(__buf,__buflen,__val,__ndigit,__decptr,__sign))
#else /* __CRT_HAVE__ecvt_s */
#include <local/stdlib/_ecvt_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_ecvt_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 5, 6)) errno_t __NOTHROW_NCX(__LIBCCALL _ecvt_s)(char *__buf, __SIZE_TYPE__ __buflen, double __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_ecvt_s))(__buf, __buflen, __val, __ndigit, __decptr, __sign); })
#endif /* !__CRT_HAVE__ecvt_s */
#ifdef __CRT_HAVE__fcvt_s
__CDECLARE(__ATTR_NONNULL((1, 5, 6)),errno_t,__NOTHROW_NCX,_fcvt_s,(char *__buf, __SIZE_TYPE__ __buflen, double __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign),(__buf,__buflen,__val,__ndigit,__decptr,__sign))
#else /* __CRT_HAVE__fcvt_s */
#include <local/stdlib/_fcvt_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_fcvt_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 5, 6)) errno_t __NOTHROW_NCX(__LIBCCALL _fcvt_s)(char *__buf, __SIZE_TYPE__ __buflen, double __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_fcvt_s))(__buf, __buflen, __val, __ndigit, __decptr, __sign); })
#endif /* !__CRT_HAVE__fcvt_s */
#ifdef __CRT_HAVE__gcvt_s
__CDECLARE(__ATTR_NONNULL((1)),errno_t,__NOTHROW_NCX,_gcvt_s,(char *__buf, __SIZE_TYPE__ __buflen, double __val, int __ndigit),(__buf,__buflen,__val,__ndigit))
#else /* __CRT_HAVE__gcvt_s */
#include <local/stdlib/_gcvt_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_gcvt_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) errno_t __NOTHROW_NCX(__LIBCCALL _gcvt_s)(char *__buf, __SIZE_TYPE__ __buflen, double __val, int __ndigit) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_gcvt_s))(__buf, __buflen, __val, __ndigit); })
#endif /* !__CRT_HAVE__gcvt_s */
#ifdef __CRT_HAVE_ecvt
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((3, 4)),char *,__NOTHROW_NCX,_ecvt,(double __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign),ecvt,(__val,__ndigit,__decptr,__sign))
#elif defined(__CRT_HAVE__ecvt)
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((3, 4)),char *,__NOTHROW_NCX,_ecvt,(double __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign),(__val,__ndigit,__decptr,__sign))
#else /* ... */
#include <local/stdlib/ecvt.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((3, 4)) char *__NOTHROW_NCX(__LIBCCALL _ecvt)(double __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ecvt))(__val, __ndigit, __decptr, __sign); }
#endif /* !... */
#ifdef __CRT_HAVE_fcvt
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((3, 4)),char *,__NOTHROW_NCX,_fcvt,(double __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign),fcvt,(__val,__ndigit,__decptr,__sign))
#elif defined(__CRT_HAVE__ecvt)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((3, 4)),char *,__NOTHROW_NCX,_fcvt,(double __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign),_ecvt,(__val,__ndigit,__decptr,__sign))
#else /* ... */
#include <local/stdlib/fcvt.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((3, 4)) char *__NOTHROW_NCX(__LIBCCALL _fcvt)(double __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fcvt))(__val, __ndigit, __decptr, __sign); }
#endif /* !... */
#ifdef __CRT_HAVE_gcvt
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((3)),char *,__NOTHROW_NCX,_gcvt,(double __val, int __ndigit, char *__buf),gcvt,(__val,__ndigit,__buf))
#elif defined(__CRT_HAVE__gcvt)
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((3)),char *,__NOTHROW_NCX,_gcvt,(double __val, int __ndigit, char *__buf),(__val,__ndigit,__buf))
#else /* ... */
#include <local/stdlib/gcvt.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((3)) char *__NOTHROW_NCX(__LIBCCALL _gcvt)(double __val, int __ndigit, char *__buf) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(gcvt))(__val, __ndigit, __buf); }
#endif /* !... */
#ifdef __CRT_HAVE__atoflt
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_atoflt,(float *__restrict __result, char const *__restrict __nptr),(__result,__nptr))
#else /* __CRT_HAVE__atoflt */
#include <local/stdlib/_atoflt.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_atoflt, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _atoflt)(float *__restrict __result, char const *__restrict __nptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_atoflt))(__result, __nptr); })
#endif /* !__CRT_HAVE__atoflt */
#ifdef __CRT_HAVE__atoflt_l
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_atoflt_l,(float *__restrict __result, char const *__restrict __nptr, __locale_t __locale),(__result,__nptr,__locale))
#else /* __CRT_HAVE__atoflt_l */
#include <local/stdlib/_atoflt_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_atoflt_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _atoflt_l)(float *__restrict __result, char const *__restrict __nptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_atoflt_l))(__result, __nptr, __locale); })
#endif /* !__CRT_HAVE__atoflt_l */
#ifdef __CRT_HAVE__atodbl
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_atodbl,(double *__restrict __result, char __KOS_FIXED_CONST *__restrict __nptr),(__result,__nptr))
#elif defined(__CRT_HAVE__atoldbl) && __SIZEOF_DOUBLE__ == __SIZEOF_LONG_DOUBLE__
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_atodbl,(double *__restrict __result, char __KOS_FIXED_CONST *__restrict __nptr),_atoldbl,(__result,__nptr))
#else /* ... */
#include <local/stdlib/_atodbl.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_atodbl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _atodbl)(double *__restrict __result, char __KOS_FIXED_CONST *__restrict __nptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_atodbl))(__result, __nptr); })
#endif /* !... */
#ifdef __CRT_HAVE__atodbl_l
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_atodbl_l,(double *__restrict __result, char __KOS_FIXED_CONST *__restrict __nptr, __locale_t __locale),(__result,__nptr,__locale))
#elif defined(__CRT_HAVE__atoldbl_l) && __SIZEOF_DOUBLE__ == __SIZEOF_LONG_DOUBLE__
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_atodbl_l,(double *__restrict __result, char __KOS_FIXED_CONST *__restrict __nptr, __locale_t __locale),_atoldbl_l,(__result,__nptr,__locale))
#else /* ... */
#include <local/stdlib/_atodbl_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_atodbl_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _atodbl_l)(double *__restrict __result, char __KOS_FIXED_CONST *__restrict __nptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_atodbl_l))(__result, __nptr, __locale); })
#endif /* !... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#ifdef __CRT_HAVE__atoldbl
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_atoldbl,(__LONGDOUBLE *__restrict __result, char __KOS_FIXED_CONST *__restrict __nptr),(__result,__nptr))
#elif defined(__CRT_HAVE__atodbl) && __SIZEOF_DOUBLE__ == __SIZEOF_LONG_DOUBLE__
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_atoldbl,(__LONGDOUBLE *__restrict __result, char __KOS_FIXED_CONST *__restrict __nptr),_atodbl,(__result,__nptr))
#else /* ... */
#include <local/stdlib/_atoldbl.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_atoldbl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _atoldbl)(__LONGDOUBLE *__restrict __result, char __KOS_FIXED_CONST *__restrict __nptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_atoldbl))(__result, __nptr); })
#endif /* !... */
#ifdef __CRT_HAVE__atoldbl_l
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_atoldbl_l,(__LONGDOUBLE *__restrict __result, char __KOS_FIXED_CONST *__restrict __nptr, __locale_t __locale),(__result,__nptr,__locale))
#elif defined(__CRT_HAVE__atodbl_l) && __SIZEOF_DOUBLE__ == __SIZEOF_LONG_DOUBLE__
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_atoldbl_l,(__LONGDOUBLE *__restrict __result, char __KOS_FIXED_CONST *__restrict __nptr, __locale_t __locale),_atodbl_l,(__result,__nptr,__locale))
#else /* ... */
#include <local/stdlib/_atoldbl_l.h>
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
#include <local/stdlib/_rotl.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_rotl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST unsigned int __NOTHROW(__LIBCCALL _rotl)(unsigned int __val, int __shift) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_rotl))(__val, __shift); })
#endif /* !... */
#ifdef __CRT_HAVE__rotr
__CDECLARE(__ATTR_CONST,unsigned int,__NOTHROW,_rotr,(unsigned int __val, int __shift),(__val,__shift))
#elif defined(__CRT_HAVE__lrotr) && __SIZEOF_INT__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_CONST,unsigned int,__NOTHROW,_rotr,(unsigned int __val, int __shift),_lrotr,(__val,__shift))
#elif defined(__CRT_HAVE__rotr64) && __SIZEOF_INT__ == 8
__CREDIRECT(__ATTR_CONST,unsigned int,__NOTHROW,_rotr,(unsigned int __val, int __shift),_rotr64,(__val,__shift))
#else /* ... */
#include <local/stdlib/_rotr.h>
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
#include <local/stdlib/_rotl64.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_rotl64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __UINT64_TYPE__ __NOTHROW(__LIBCCALL _rotl64)(__UINT64_TYPE__ __val, int __shift) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_rotl64))(__val, __shift); })
#endif /* !... */
#ifdef __CRT_HAVE__rotr64
__CDECLARE(__ATTR_CONST,__UINT64_TYPE__,__NOTHROW,_rotr64,(__UINT64_TYPE__ __val, int __shift),(__val,__shift))
#elif defined(__CRT_HAVE__lrotr) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_CONST,__UINT64_TYPE__,__NOTHROW,_rotr64,(__UINT64_TYPE__ __val, int __shift),_lrotr,(__val,__shift))
#elif defined(__CRT_HAVE__rotr) && __SIZEOF_INT__ == 8
__CREDIRECT(__ATTR_CONST,__UINT64_TYPE__,__NOTHROW,_rotr64,(__UINT64_TYPE__ __val, int __shift),_rotr,(__val,__shift))
#else /* ... */
#include <local/stdlib/_rotr64.h>
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
#include <local/stdlib/_lrotl.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_lrotl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST unsigned long __NOTHROW(__LIBCCALL _lrotl)(unsigned long __val, int __shift) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_lrotl))(__val, __shift); })
#endif /* !... */
#ifdef __CRT_HAVE__lrotr
__CDECLARE(__ATTR_CONST,unsigned long,__NOTHROW,_lrotr,(unsigned long __val, int __shift),(__val,__shift))
#elif defined(__CRT_HAVE__rotr) && __SIZEOF_LONG__ == __SIZEOF_INT__
__CREDIRECT(__ATTR_CONST,unsigned long,__NOTHROW,_lrotr,(unsigned long __val, int __shift),_rotr,(__val,__shift))
#elif defined(__CRT_HAVE__rotr64) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_CONST,unsigned long,__NOTHROW,_lrotr,(unsigned long __val, int __shift),_rotr64,(__val,__shift))
#else /* ... */
#include <local/stdlib/_lrotr.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_lrotr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST unsigned long __NOTHROW(__LIBCCALL _lrotr)(unsigned long __val, int __shift) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_lrotr))(__val, __shift); })
#endif /* !... */

#ifndef _CRT_PERROR_DEFINED
#define _CRT_PERROR_DEFINED 1
#ifndef __perror_defined
#define __perror_defined 1
#ifdef __std_perror_defined
/* Print a given `MESSAGE' alongside `strerror(errno)' to stderr:
 * >> if (message) {
 * >>     fprintf(stderr, "%s: %s\n", message, strerror(errno));
 * >> } else {
 * >>     fprintf(stderr, "%s\n", strerror(errno));
 * >> } */
__NAMESPACE_STD_USING(perror)
#elif defined(__CRT_HAVE_perror)
/* Print a given `MESSAGE' alongside `strerror(errno)' to stderr:
 * >> if (message) {
 * >>     fprintf(stderr, "%s: %s\n", message, strerror(errno));
 * >> } else {
 * >>     fprintf(stderr, "%s\n", strerror(errno));
 * >> } */
__CDECLARE_VOID(,__NOTHROW_RPC,perror,(char const *__message),(__message))
#else /* ... */
#include <__crt.h>
#include <parts/errno.h>
#if !defined(__NO_STDSTREAMS) && defined(__libc_geterrno) && (defined(__CRT_HAVE_fprintf) || defined(__CRT_HAVE__IO_fprintf) || defined(__CRT_HAVE_fprintf_s) || defined(__CRT_HAVE_fprintf_unlocked) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock))
#include <local/stdio/perror.h>
/* Print a given `MESSAGE' alongside `strerror(errno)' to stderr:
 * >> if (message) {
 * >>     fprintf(stderr, "%s: %s\n", message, strerror(errno));
 * >> } else {
 * >>     fprintf(stderr, "%s\n", strerror(errno));
 * >> } */
__NAMESPACE_LOCAL_USING_OR_IMPL(perror, __FORCELOCAL __ATTR_ARTIFICIAL void __NOTHROW_RPC(__LIBCCALL perror)(char const *__message) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(perror))(__message); })
#else /* !__NO_STDSTREAMS && __libc_geterrno && (__CRT_HAVE_fprintf || __CRT_HAVE__IO_fprintf || __CRT_HAVE_fprintf_s || __CRT_HAVE_fprintf_unlocked || __CRT_HAVE_vfprintf || __CRT_HAVE_vfprintf_s || __CRT_HAVE__IO_vfprintf || __CRT_HAVE_vfprintf_unlocked || __CRT_HAVE_file_printer || __CRT_HAVE_file_printer_unlocked || __CRT_HAVE_fputc || __CRT_HAVE_putc || __CRT_HAVE__IO_putc || __CRT_HAVE_fputc_unlocked || __CRT_HAVE_putc_unlocked || (__CRT_DOS && __CRT_HAVE__flsbuf) || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock) */
#undef __perror_defined
#endif /* __NO_STDSTREAMS || !__libc_geterrno || (!__CRT_HAVE_fprintf && !__CRT_HAVE__IO_fprintf && !__CRT_HAVE_fprintf_s && !__CRT_HAVE_fprintf_unlocked && !__CRT_HAVE_vfprintf && !__CRT_HAVE_vfprintf_s && !__CRT_HAVE__IO_vfprintf && !__CRT_HAVE_vfprintf_unlocked && !__CRT_HAVE_file_printer && !__CRT_HAVE_file_printer_unlocked && !__CRT_HAVE_fputc && !__CRT_HAVE_putc && !__CRT_HAVE__IO_putc && !__CRT_HAVE_fputc_unlocked && !__CRT_HAVE_putc_unlocked && (!__CRT_DOS || !__CRT_HAVE__flsbuf) && !__CRT_HAVE_fwrite && !__CRT_HAVE__IO_fwrite && !__CRT_HAVE_fwrite_s && !__CRT_HAVE_fwrite_unlocked && !__CRT_HAVE__fwrite_nolock) */
#endif /* !... */
#endif /* !__perror_defined */
#endif  /* _CRT_PERROR_DEFINED */

#ifdef __CRT_HAVE_putenv
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,_putenv,(char *__string),putenv,(__string))
#elif defined(__CRT_HAVE__putenv)
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,_putenv,(char *__string),(__string))
#endif /* ... */
#ifdef __CRT_HAVE_swab
/* Copy `n_bytes & ~1' (FLOOR_ALIGN(n_bytes, 2)) from `from' to `to',
 * exchanging the order of even and odd bytes ("123456" --> "214365")
 * When `n_bytes <= 1', don't do anything and return immediately */
__CREDIRECT_VOID(__ATTR_NONNULL((1, 2)),__NOTHROW_NCX,_swab,(void const *__restrict __from, void *__restrict __to, __STDC_INT_AS_SSIZE_T __n_bytes),swab,(__from,__to,__n_bytes))
#elif defined(__CRT_HAVE__swab)
/* Copy `n_bytes & ~1' (FLOOR_ALIGN(n_bytes, 2)) from `from' to `to',
 * exchanging the order of even and odd bytes ("123456" --> "214365")
 * When `n_bytes <= 1', don't do anything and return immediately */
__CDECLARE_VOID(__ATTR_NONNULL((1, 2)),__NOTHROW_NCX,_swab,(void const *__restrict __from, void *__restrict __to, __STDC_INT_AS_SSIZE_T __n_bytes),(__from,__to,__n_bytes))
#else /* ... */
#include <local/unistd/swab.h>
/* Copy `n_bytes & ~1' (FLOOR_ALIGN(n_bytes, 2)) from `from' to `to',
 * exchanging the order of even and odd bytes ("123456" --> "214365")
 * When `n_bytes <= 1', don't do anything and return immediately */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) void __NOTHROW_NCX(__LIBCCALL _swab)(void const *__restrict __from, void *__restrict __to, __STDC_INT_AS_SSIZE_T __n_bytes) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(swab))(__from, __to, __n_bytes); }
#endif /* !... */
#ifdef __CRT_HAVE__putenv_s
__CDECLARE(,errno_t,__NOTHROW_NCX,_putenv_s,(char const *__varname, char const *__val),(__varname,__val))
#elif defined(__CRT_HAVE_setenv)
#include <local/stdlib/_putenv_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_putenv_s, __FORCELOCAL __ATTR_ARTIFICIAL errno_t __NOTHROW_NCX(__LIBCCALL _putenv_s)(char const *__varname, char const *__val) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_putenv_s))(__varname, __val); })
#endif /* ... */
#ifdef __CRT_HAVE__searchenv
__CDECLARE_VOID(__ATTR_NONNULL((1, 2, 3)),__NOTHROW_RPC,_searchenv,(char const *__file, char const *__envvar, char *__restrict __resultpath),(__file,__envvar,__resultpath))
#elif defined(__CRT_HAVE__searchenv_s)
#include <local/stdlib/_searchenv.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_searchenv, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2, 3)) void __NOTHROW_RPC(__LIBCCALL _searchenv)(char const *__file, char const *__envvar, char *__restrict __resultpath) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_searchenv))(__file, __envvar, __resultpath); })
#endif /* ... */
__CDECLARE_OPT(__ATTR_NONNULL((1, 2, 3)),errno_t,__NOTHROW_RPC,_searchenv_s,(char const *__file, char const *__envvar, char *__restrict __resultpath, __SIZE_TYPE__ __buflen),(__file,__envvar,__resultpath,__buflen))
#ifdef __CRT_HAVE__makepath
__CDECLARE_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,_makepath,(char *__restrict __buf, char const *__drive, char const *__dir, char const *__file, char const *__ext),(__buf,__drive,__dir,__file,__ext))
#else /* __CRT_HAVE__makepath */
#include <local/stdlib/_makepath.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_makepath, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) void __NOTHROW_NCX(__LIBCCALL _makepath)(char *__restrict __buf, char const *__drive, char const *__dir, char const *__file, char const *__ext) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_makepath))(__buf, __drive, __dir, __file, __ext); })
#endif /* !__CRT_HAVE__makepath */
#ifdef __CRT_HAVE__splitpath
__CDECLARE_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,_splitpath,(char const *__restrict __abspath, char *__drive, char *__dir, char *__file, char *__ext),(__abspath,__drive,__dir,__file,__ext))
#else /* __CRT_HAVE__splitpath */
#include <local/stdlib/_splitpath.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_splitpath, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) void __NOTHROW_NCX(__LIBCCALL _splitpath)(char const *__restrict __abspath, char *__drive, char *__dir, char *__file, char *__ext) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_splitpath))(__abspath, __drive, __dir, __file, __ext); })
#endif /* !__CRT_HAVE__splitpath */
#ifdef __CRT_HAVE__makepath_s
__CDECLARE(__ATTR_NONNULL((1)),errno_t,__NOTHROW_NCX,_makepath_s,(char *__buf, __SIZE_TYPE__ __buflen, char const *__drive, char const *__dir, char const *__file, char const *__ext),(__buf,__buflen,__drive,__dir,__file,__ext))
#else /* __CRT_HAVE__makepath_s */
#include <local/stdlib/_makepath_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_makepath_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) errno_t __NOTHROW_NCX(__LIBCCALL _makepath_s)(char *__buf, __SIZE_TYPE__ __buflen, char const *__drive, char const *__dir, char const *__file, char const *__ext) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_makepath_s))(__buf, __buflen, __drive, __dir, __file, __ext); })
#endif /* !__CRT_HAVE__makepath_s */
#ifdef __CRT_HAVE__splitpath_s
__CDECLARE(__ATTR_NONNULL((1)),errno_t,__NOTHROW_NCX,_splitpath_s,(char const *__restrict __abspath, char *__drive, __SIZE_TYPE__ __drivelen, char *__dir, __SIZE_TYPE__ __dirlen, char *__file, __SIZE_TYPE__ __filelen, char *__ext, __SIZE_TYPE__ __extlen),(__abspath,__drive,__drivelen,__dir,__dirlen,__file,__filelen,__ext,__extlen))
#else /* __CRT_HAVE__splitpath_s */
#include <local/stdlib/_splitpath_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_splitpath_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) errno_t __NOTHROW_NCX(__LIBCCALL _splitpath_s)(char const *__restrict __abspath, char *__drive, __SIZE_TYPE__ __drivelen, char *__dir, __SIZE_TYPE__ __dirlen, char *__file, __SIZE_TYPE__ __filelen, char *__ext, __SIZE_TYPE__ __extlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_splitpath_s))(__abspath, __drive, __drivelen, __dir, __dirlen, __file, __filelen, __ext, __extlen); })
#endif /* !__CRT_HAVE__splitpath_s */

__CDECLARE_VOID_OPT(,__NOTHROW_NCX,_seterrormode,(int __mode),(__mode))
__CDECLARE_OPT(,int,__NOTHROW_NCX,_set_error_mode,(int __mode),(__mode))

__CDECLARE_VOID_OPT(,__NOTHROW_NCX,_beep,(unsigned int __freq, unsigned int __duration),(__freq,__duration))
#ifdef __CRT_HAVE_sleep
/* >> sleep(3)
 * Sleep for up to `SECONDS' seconds */
__CREDIRECT_VOID(,__NOTHROW_RPC,_sleep,(__UINT32_TYPE__ __duration),sleep,(__duration))
#elif defined(__CRT_HAVE__sleep)
#include <local/unistd/sleep.h>
/* >> sleep(3)
 * Sleep for up to `SECONDS' seconds */
__FORCELOCAL __ATTR_ARTIFICIAL void __NOTHROW_RPC(__LIBCCALL _sleep)(__UINT32_TYPE__ __duration) { (void)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sleep))((unsigned int)__duration); }
#endif /* ... */

#ifndef __cplusplus
#define min(a, b)   __min(a, b)
#define max(a, b)   __max(a, b)
#endif /* !__cplusplus */

#ifndef __environ_defined
#define __environ_defined 1
#undef environ
#if defined(__CRT_HAVE_environ)
__LIBC char **environ;
#define environ environ
#elif defined(__CRT_HAVE__environ) && !defined(__NO_ASMNAME)
__LIBC char **environ __ASMNAME("_environ");
#define environ environ
#elif defined(__CRT_HAVE__environ)
#ifndef ___environ_defined
#define ___environ_defined 1
#undef _environ
__LIBC char **_environ;
#endif /* !___environ_defined */
#define environ _environ
#elif defined(__CRT_HAVE___environ) && !defined(__NO_ASMNAME)
__LIBC char **environ __ASMNAME("__environ");
#define environ environ
#elif defined(__CRT_HAVE___environ)
#ifndef ____environ_defined
#define ____environ_defined 1
#undef __environ
__LIBC char **__environ;
#endif /* !____environ_defined */
#define environ __environ
#elif defined(__CRT_HAVE___p__environ)
#ifndef ____p__environ_defined
#define ____p__environ_defined 1
__CDECLARE(__ATTR_WUNUSED __ATTR_CONST __ATTR_RETNONNULL,char ***,__NOTHROW,__p__environ,(void),())
#endif /* !____p__environ_defined */
#define environ (*__p__environ())
#else /* ... */
#undef __environ_defined
#endif /* !... */
#endif /* !__environ_defined */

#ifndef __swab_defined
#define __swab_defined 1
#ifdef __CRT_HAVE_swab
/* Copy `n_bytes & ~1' (FLOOR_ALIGN(n_bytes, 2)) from `from' to `to',
 * exchanging the order of even and odd bytes ("123456" --> "214365")
 * When `n_bytes <= 1', don't do anything and return immediately */
__CDECLARE_VOID(__ATTR_NONNULL((1, 2)),__NOTHROW_NCX,swab,(void const *__restrict __from, void *__restrict __to, __STDC_INT_AS_SSIZE_T __n_bytes),(__from,__to,__n_bytes))
#elif defined(__CRT_HAVE__swab)
/* Copy `n_bytes & ~1' (FLOOR_ALIGN(n_bytes, 2)) from `from' to `to',
 * exchanging the order of even and odd bytes ("123456" --> "214365")
 * When `n_bytes <= 1', don't do anything and return immediately */
__CREDIRECT_VOID(__ATTR_NONNULL((1, 2)),__NOTHROW_NCX,swab,(void const *__restrict __from, void *__restrict __to, __STDC_INT_AS_SSIZE_T __n_bytes),_swab,(__from,__to,__n_bytes))
#else /* ... */
#include <local/unistd/swab.h>
/* Copy `n_bytes & ~1' (FLOOR_ALIGN(n_bytes, 2)) from `from' to `to',
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
#include <local/stdlib/itoa.h>
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
#include <local/stdlib/ltoa.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(ltoa, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) char *__NOTHROW_NCX(__LIBCCALL ltoa)(long __val, char *__buf, int __radix) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ltoa))(__val, __buf, __radix); })
#endif /* !... */
#ifdef __CRT_HAVE_ultoa
__CDECLARE(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,ultoa,(unsigned long __val, char *__buf, int __radix),(__val,__buf,__radix))
#elif defined(__CRT_HAVE__ultoa)
__CREDIRECT(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,ultoa,(unsigned long __val, char *__buf, int __radix),_ultoa,(__val,__buf,__radix))
#elif defined(__CRT_HAVE__ui64toa) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,ultoa,(unsigned long __val, char *__buf, int __radix),_ui64toa,(__val,__buf,__radix))
#else /* ... */
#include <local/stdlib/ultoa.h>
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
#ifndef _WSTDLIB_DEFINED
#define _WSTDLIB_DEFINED
#ifndef ___wgetenv_defined
#define ___wgetenv_defined 1
#ifdef __CRT_HAVE__wgetenv
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,_wgetenv,(wchar_t const *__varname),(__varname))
#else /* __CRT_HAVE__wgetenv */
#undef ___wgetenv_defined
#endif /* !__CRT_HAVE__wgetenv */
#endif /* !___wgetenv_defined */
#ifndef ___wgetenv_s_defined
#define ___wgetenv_s_defined 1
#ifdef __CRT_HAVE__wgetenv_s
__CDECLARE(__ATTR_NONNULL((1, 4)),errno_t,__NOTHROW_NCX,_wgetenv_s,(__SIZE_TYPE__ *__return_size, wchar_t *__buf, __SIZE_TYPE__ __buflen, wchar_t const *__varname),(__return_size,__buf,__buflen,__varname))
#else /* __CRT_HAVE__wgetenv_s */
#undef ___wgetenv_s_defined
#endif /* !__CRT_HAVE__wgetenv_s */
#endif /* !___wgetenv_s_defined */
#ifndef ___wdupenv_s_defined
#define ___wdupenv_s_defined 1
#ifdef __CRT_HAVE__wdupenv_s
__CDECLARE(__ATTR_NONNULL((1, 2, 3)),errno_t,__NOTHROW_NCX,_wdupenv_s,(wchar_t **__pbuf, __SIZE_TYPE__ *__pbuflen, wchar_t const *__varname),(__pbuf,__pbuflen,__varname))
#else /* __CRT_HAVE__wdupenv_s */
#undef ___wdupenv_s_defined
#endif /* !__CRT_HAVE__wdupenv_s */
#endif /* !___wdupenv_s_defined */
#ifndef _CRT_WSYSTEM_DEFINED
#define _CRT_WSYSTEM_DEFINED 1
#ifdef __CRT_HAVE_wsystem
__CREDIRECT(,int,__NOTHROW_RPC,_wsystem,(wchar_t const *__cmd),wsystem,(__cmd))
#elif defined(__CRT_HAVE__wsystem)
__CDECLARE(,int,__NOTHROW_RPC,_wsystem,(wchar_t const *__cmd),(__cmd))
#else /* ... */
#undef _CRT_WSYSTEM_DEFINED
#endif /* !... */
#endif /* !_CRT_WSYSTEM_DEFINED */
#ifndef __wcstol_defined
#define __wcstol_defined 1
#ifdef __std_wcstol_defined
__NAMESPACE_STD_USING(wcstol)
#elif defined(__CRT_HAVE_wcstol)
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),long,__NOTHROW_NCX,wcstol,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoll) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),long,__NOTHROW_NCX,wcstol,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoq) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),long,__NOTHROW_NCX,wcstol,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcsto32) && __SIZEOF_LONG__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),long,__NOTHROW_NCX,wcstol,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcsto32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcsto64) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),long,__NOTHROW_NCX,wcstol,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcsto64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__wcstoi64) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),long,__NOTHROW_NCX,wcstol,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoi64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoimax) && __SIZEOF_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),long,__NOTHROW_NCX,wcstol,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoimax,(__nptr,__endptr,__base))
#else /* ... */
#include <local/wchar/wcstol.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstol, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) long __NOTHROW_NCX(__LIBCCALL wcstol)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstol))(__nptr, __endptr, __base); })
#endif /* !... */
#endif /* !__wcstol_defined */
#ifndef __wcstoll_defined
#define __wcstoll_defined 1
#ifdef __std_wcstoll_defined
__NAMESPACE_STD_USING(wcstoll)
#elif defined(__CRT_HAVE_wcstoll)
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,wcstoll,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoq)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,wcstoll,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstol) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,wcstoll,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcsto64) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,wcstoll,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcsto64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__wcstoi64) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,wcstoll,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoi64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcsto32) && __SIZEOF_LONG_LONG__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,wcstoll,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcsto32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoimax) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,wcstoll,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoimax,(__nptr,__endptr,__base))
#else /* ... */
#include <local/wchar/wcstoll.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstoll, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __LONGLONG __NOTHROW_NCX(__LIBCCALL wcstoll)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoll))(__nptr, __endptr, __base); })
#endif /* !... */
#endif /* !__wcstoll_defined */
#ifndef __wcstoul_defined
#define __wcstoul_defined 1
#ifdef __std_wcstoul_defined
__NAMESPACE_STD_USING(wcstoul)
#elif defined(__CRT_HAVE_wcstoul)
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,wcstoul,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoull) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,wcstoul,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstouq) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,wcstoul,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstou32) && __SIZEOF_LONG__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,wcstoul,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstou32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstou64) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,wcstoul,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstou64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__wcstoui64) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,wcstoul,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoui64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoumax) && __SIZEOF_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,wcstoul,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoumax,(__nptr,__endptr,__base))
#else /* ... */
#include <local/wchar/wcstoul.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstoul, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) unsigned long __NOTHROW_NCX(__LIBCCALL wcstoul)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoul))(__nptr, __endptr, __base); })
#endif /* !... */
#endif /* !__wcstoul_defined */
#ifndef __wcstoull_defined
#define __wcstoull_defined 1
#ifdef __std_wcstoull_defined
__NAMESPACE_STD_USING(wcstoull)
#elif defined(__CRT_HAVE_wcstoull)
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,wcstoull,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstouq)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,wcstoull,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoul) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,wcstoull,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstou32) && __SIZEOF_LONG_LONG__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,wcstoull,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstou32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstou64) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,wcstoull,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstou64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__wcstoui64) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,wcstoull,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoui64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoumax) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,wcstoull,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoumax,(__nptr,__endptr,__base))
#else /* ... */
#include <local/wchar/wcstoull.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstoull, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __ULONGLONG __NOTHROW_NCX(__LIBCCALL wcstoull)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoull))(__nptr, __endptr, __base); })
#endif /* !... */
#endif /* !__wcstoull_defined */
#ifndef ___wcstol_l_defined
#define ___wcstol_l_defined 1
#ifdef __CRT_HAVE_wcstol_l
__CREDIRECT(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,_wcstol_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstol_l)
__CDECLARE(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,_wcstol_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstol_l)
__CREDIRECT(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,_wcstol_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstol_l,(__nptr,__endptr,__base,__locale))
#else /* ... */
#include <local/wchar/wcstol_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) long __NOTHROW_NCX(__LIBCCALL _wcstol_l)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstol_l))(__nptr, __endptr, __base, __locale); }
#endif /* !... */
#endif /* !___wcstol_l_defined */
#ifndef ___wcstoul_l_defined
#define ___wcstoul_l_defined 1
#ifdef __CRT_HAVE_wcstoul_l
__CREDIRECT(__ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,_wcstoul_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoul_l)
__CDECLARE(__ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,_wcstoul_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoul_l)
__CREDIRECT(__ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,_wcstoul_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoul_l,(__nptr,__endptr,__base,__locale))
#else /* ... */
#include <local/wchar/wcstoul_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) unsigned long __NOTHROW_NCX(__LIBCCALL _wcstoul_l)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoul_l))(__nptr, __endptr, __base, __locale); }
#endif /* !... */
#endif /* !___wcstoul_l_defined */
#ifndef __NO_FPU
#ifndef __wcstof_defined
#define __wcstof_defined 1
#ifdef __std_wcstof_defined
__NAMESPACE_STD_USING(wcstof)
#elif defined(__CRT_HAVE_wcstof)
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),float,__NOTHROW_NCX,wcstof,(wchar_t const *__restrict __nptr, wchar_t **__endptr),(__nptr,__endptr))
#else /* ... */
#include <local/wchar/wcstof.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstof, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) float __NOTHROW_NCX(__LIBCCALL wcstof)(wchar_t const *__restrict __nptr, wchar_t **__endptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstof))(__nptr, __endptr); })
#endif /* !... */
#endif /* !__wcstof_defined */
#ifndef __wcstod_defined
#define __wcstod_defined 1
#ifdef __std_wcstod_defined
__NAMESPACE_STD_USING(wcstod)
#elif defined(__CRT_HAVE_wcstod)
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),double,__NOTHROW_NCX,wcstod,(wchar_t const *__restrict __nptr, wchar_t **__endptr),(__nptr,__endptr))
#else /* ... */
#include <local/wchar/wcstod.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstod, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) double __NOTHROW_NCX(__LIBCCALL wcstod)(wchar_t const *__restrict __nptr, wchar_t **__endptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstod))(__nptr, __endptr); })
#endif /* !... */
#endif /* !__wcstod_defined */
#ifndef ___wcstof_l_defined
#define ___wcstof_l_defined 1
#ifdef __CRT_HAVE_wcstof_l
__CREDIRECT(__ATTR_NONNULL((1)),float,__NOTHROW_NCX,_wcstof_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __locale_t __locale),wcstof_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE__wcstof_l)
__CDECLARE(__ATTR_NONNULL((1)),float,__NOTHROW_NCX,_wcstof_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __locale_t __locale),(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE___wcstof_l)
__CREDIRECT(__ATTR_NONNULL((1)),float,__NOTHROW_NCX,_wcstof_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __locale_t __locale),__wcstof_l,(__nptr,__endptr,__locale))
#else /* ... */
#include <local/wchar/wcstof_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) float __NOTHROW_NCX(__LIBCCALL _wcstof_l)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstof_l))(__nptr, __endptr, __locale); }
#endif /* !... */
#endif /* !___wcstof_l_defined */
#ifndef ___wcstod_l_defined
#define ___wcstod_l_defined 1
#ifdef __CRT_HAVE_wcstod_l
__CREDIRECT(__ATTR_NONNULL((1)),double,__NOTHROW_NCX,_wcstod_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __locale_t __locale),wcstod_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE__wcstod_l)
__CDECLARE(__ATTR_NONNULL((1)),double,__NOTHROW_NCX,_wcstod_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __locale_t __locale),(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE___wcstod_l)
__CREDIRECT(__ATTR_NONNULL((1)),double,__NOTHROW_NCX,_wcstod_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __locale_t __locale),__wcstod_l,(__nptr,__endptr,__locale))
#else /* ... */
#include <local/wchar/wcstod_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) double __NOTHROW_NCX(__LIBCCALL _wcstod_l)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstod_l))(__nptr, __endptr, __locale); }
#endif /* !... */
#endif /* !___wcstod_l_defined */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#ifndef __wcstold_defined
#define __wcstold_defined 1
#ifdef __std_wcstold_defined
__NAMESPACE_STD_USING(wcstold)
#elif defined(__CRT_HAVE_wcstold)
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGDOUBLE,__NOTHROW_NCX,wcstold,(wchar_t const *__restrict __nptr, wchar_t **__endptr),(__nptr,__endptr))
#else /* ... */
#include <local/wchar/wcstold.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstold, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __LONGDOUBLE __NOTHROW_NCX(__LIBCCALL wcstold)(wchar_t const *__restrict __nptr, wchar_t **__endptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstold))(__nptr, __endptr); })
#endif /* !... */
#endif /* !__wcstold_defined */
#ifndef ___wcstold_l_defined
#define ___wcstold_l_defined 1
#ifdef __CRT_HAVE_wcstold_l
__CREDIRECT(__ATTR_NONNULL((1)),__LONGDOUBLE,__NOTHROW_NCX,_wcstold_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __locale_t __locale),wcstold_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE__wcstold_l)
__CDECLARE(__ATTR_NONNULL((1)),__LONGDOUBLE,__NOTHROW_NCX,_wcstold_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __locale_t __locale),(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE___wcstold_l)
__CREDIRECT(__ATTR_NONNULL((1)),__LONGDOUBLE,__NOTHROW_NCX,_wcstold_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __locale_t __locale),__wcstold_l,(__nptr,__endptr,__locale))
#else /* ... */
#include <local/wchar/wcstold_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __LONGDOUBLE __NOTHROW_NCX(__LIBCCALL _wcstold_l)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstold_l))(__nptr, __endptr, __locale); }
#endif /* !... */
#endif /* !___wcstold_l_defined */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#ifndef ___wtof_defined
#define ___wtof_defined 1
#ifdef __CRT_HAVE__wtof
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),double,__NOTHROW_NCX,_wtof,(wchar_t const *__nptr),(__nptr))
#else /* __CRT_HAVE__wtof */
#include <local/stdlib/_wtof.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wtof, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) double __NOTHROW_NCX(__LIBCCALL _wtof)(wchar_t const *__nptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wtof))(__nptr); })
#endif /* !__CRT_HAVE__wtof */
#endif /* !___wtof_defined */
#ifndef ___wtof_l_defined
#define ___wtof_l_defined 1
#ifdef __CRT_HAVE__wtof_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),double,__NOTHROW_NCX,_wtof_l,(wchar_t const *__nptr, __locale_t __locale),(__nptr,__locale))
#else /* __CRT_HAVE__wtof_l */
#include <local/stdlib/_wtof_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wtof_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) double __NOTHROW_NCX(__LIBCCALL _wtof_l)(wchar_t const *__nptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wtof_l))(__nptr, __locale); })
#endif /* !__CRT_HAVE__wtof_l */
#endif /* !___wtof_l_defined */
#endif /* !__NO_FPU */
#ifndef ___itow_defined
#define ___itow_defined 1
#ifdef __CRT_HAVE__itow
__CDECLARE(__ATTR_NONNULL((2)),wchar_t *,__NOTHROW_NCX,_itow,(int __val, wchar_t *__buf, int __radix),(__val,__buf,__radix))
#else /* __CRT_HAVE__itow */
#include <local/stdlib/_itow.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_itow, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) wchar_t *__NOTHROW_NCX(__LIBCCALL _itow)(int __val, wchar_t *__buf, int __radix) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_itow))(__val, __buf, __radix); })
#endif /* !__CRT_HAVE__itow */
#endif /* !___itow_defined */
#ifndef ___ltow_defined
#define ___ltow_defined 1
#ifdef __CRT_HAVE__ltow
__CDECLARE(__ATTR_NONNULL((2)),wchar_t *,__NOTHROW_NCX,_ltow,(long __val, wchar_t *__buf, int __radix),(__val,__buf,__radix))
#else /* __CRT_HAVE__ltow */
#include <local/stdlib/_ltow.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_ltow, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) wchar_t *__NOTHROW_NCX(__LIBCCALL _ltow)(long __val, wchar_t *__buf, int __radix) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_ltow))(__val, __buf, __radix); })
#endif /* !__CRT_HAVE__ltow */
#endif /* !___ltow_defined */
#ifndef ___ultow_defined
#define ___ultow_defined 1
#ifdef __CRT_HAVE__ultow
__CDECLARE(__ATTR_NONNULL((2)),wchar_t *,__NOTHROW_NCX,_ultow,(unsigned long __val, wchar_t *__buf, int __radix),(__val,__buf,__radix))
#else /* __CRT_HAVE__ultow */
#include <local/stdlib/_ultow.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_ultow, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) wchar_t *__NOTHROW_NCX(__LIBCCALL _ultow)(unsigned long __val, wchar_t *__buf, int __radix) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_ultow))(__val, __buf, __radix); })
#endif /* !__CRT_HAVE__ultow */
#endif /* !___ultow_defined */
#ifndef ___i64tow_defined
#define ___i64tow_defined 1
#ifdef __CRT_HAVE__i64tow
__CDECLARE(__ATTR_NONNULL((2)),wchar_t *,__NOTHROW_NCX,_i64tow,(__INT64_TYPE__ __val, wchar_t *__buf, int __radix),(__val,__buf,__radix))
#else /* __CRT_HAVE__i64tow */
#include <local/stdlib/_i64tow.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_i64tow, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) wchar_t *__NOTHROW_NCX(__LIBCCALL _i64tow)(__INT64_TYPE__ __val, wchar_t *__buf, int __radix) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_i64tow))(__val, __buf, __radix); })
#endif /* !__CRT_HAVE__i64tow */
#endif /* !___i64tow_defined */
#ifndef ___ui64tow_defined
#define ___ui64tow_defined 1
#ifdef __CRT_HAVE__ui64tow
__CDECLARE(__ATTR_NONNULL((2)),wchar_t *,__NOTHROW_NCX,_ui64tow,(__UINT64_TYPE__ __val, wchar_t *__buf, int __radix),(__val,__buf,__radix))
#else /* __CRT_HAVE__ui64tow */
#include <local/stdlib/_ui64tow.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_ui64tow, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) wchar_t *__NOTHROW_NCX(__LIBCCALL _ui64tow)(__UINT64_TYPE__ __val, wchar_t *__buf, int __radix) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_ui64tow))(__val, __buf, __radix); })
#endif /* !__CRT_HAVE__ui64tow */
#endif /* !___ui64tow_defined */
#ifndef ___itow_s_defined
#define ___itow_s_defined 1
#ifdef __CRT_HAVE__itow_s
__CDECLARE(__ATTR_NONNULL((2)),errno_t,__NOTHROW_NCX,_itow_s,(int __val, wchar_t *__buf, __SIZE_TYPE__ __buflen, int __radix),(__val,__buf,__buflen,__radix))
#else /* __CRT_HAVE__itow_s */
#include <local/stdlib/_itow_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_itow_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) errno_t __NOTHROW_NCX(__LIBCCALL _itow_s)(int __val, wchar_t *__buf, __SIZE_TYPE__ __buflen, int __radix) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_itow_s))(__val, __buf, __buflen, __radix); })
#endif /* !__CRT_HAVE__itow_s */
#endif /* !___itow_s_defined */
#ifndef ___ltow_s_defined
#define ___ltow_s_defined 1
#ifdef __CRT_HAVE__ltow_s
__CDECLARE(__ATTR_NONNULL((2)),errno_t,__NOTHROW_NCX,_ltow_s,(long __val, wchar_t *__buf, __SIZE_TYPE__ __buflen, int __radix),(__val,__buf,__buflen,__radix))
#else /* __CRT_HAVE__ltow_s */
#include <local/stdlib/_ltow_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_ltow_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) errno_t __NOTHROW_NCX(__LIBCCALL _ltow_s)(long __val, wchar_t *__buf, __SIZE_TYPE__ __buflen, int __radix) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_ltow_s))(__val, __buf, __buflen, __radix); })
#endif /* !__CRT_HAVE__ltow_s */
#endif /* !___ltow_s_defined */
#ifndef ___ultow_s_defined
#define ___ultow_s_defined 1
#ifdef __CRT_HAVE__ultow_s
__CDECLARE(__ATTR_NONNULL((2)),errno_t,__NOTHROW_NCX,_ultow_s,(unsigned long __val, wchar_t *__buf, __SIZE_TYPE__ __buflen, int __radix),(__val,__buf,__buflen,__radix))
#else /* __CRT_HAVE__ultow_s */
#include <local/stdlib/_ultow_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_ultow_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) errno_t __NOTHROW_NCX(__LIBCCALL _ultow_s)(unsigned long __val, wchar_t *__buf, __SIZE_TYPE__ __buflen, int __radix) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_ultow_s))(__val, __buf, __buflen, __radix); })
#endif /* !__CRT_HAVE__ultow_s */
#endif /* !___ultow_s_defined */
#ifndef ___i64tow_s_defined
#define ___i64tow_s_defined 1
#ifdef __CRT_HAVE__i64tow_s
__CDECLARE(__ATTR_NONNULL((2)),errno_t,__NOTHROW_NCX,_i64tow_s,(__INT64_TYPE__ __val, wchar_t *__buf, __SIZE_TYPE__ __buflen, int __radix),(__val,__buf,__buflen,__radix))
#else /* __CRT_HAVE__i64tow_s */
#include <local/stdlib/_i64tow_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_i64tow_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) errno_t __NOTHROW_NCX(__LIBCCALL _i64tow_s)(__INT64_TYPE__ __val, wchar_t *__buf, __SIZE_TYPE__ __buflen, int __radix) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_i64tow_s))(__val, __buf, __buflen, __radix); })
#endif /* !__CRT_HAVE__i64tow_s */
#endif /* !___i64tow_s_defined */
#ifndef ___ui64tow_s_defined
#define ___ui64tow_s_defined 1
#ifdef __CRT_HAVE__ui64tow_s
__CDECLARE(__ATTR_NONNULL((2)),errno_t,__NOTHROW_NCX,_ui64tow_s,(__UINT64_TYPE__ __val, wchar_t *__buf, __SIZE_TYPE__ __buflen, int __radix),(__val,__buf,__buflen,__radix))
#else /* __CRT_HAVE__ui64tow_s */
#include <local/stdlib/_ui64tow_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_ui64tow_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) errno_t __NOTHROW_NCX(__LIBCCALL _ui64tow_s)(__UINT64_TYPE__ __val, wchar_t *__buf, __SIZE_TYPE__ __buflen, int __radix) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_ui64tow_s))(__val, __buf, __buflen, __radix); })
#endif /* !__CRT_HAVE__ui64tow_s */
#endif /* !___ui64tow_s_defined */
#ifndef ___wtoi_defined
#define ___wtoi_defined 1
#ifdef __CRT_HAVE_wtoi
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,_wtoi,(wchar_t const *__nptr),wtoi,(__nptr))
#elif defined(__CRT_HAVE__wtoi)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,_wtoi,(wchar_t const *__nptr),(__nptr))
#elif defined(__CRT_HAVE_wtol) && __SIZEOF_INT__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,_wtoi,(wchar_t const *__nptr),wtol,(__nptr))
#elif defined(__CRT_HAVE__wtol) && __SIZEOF_INT__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,_wtoi,(wchar_t const *__nptr),_wtol,(__nptr))
#elif defined(__CRT_HAVE_wtoll) && __SIZEOF_INT__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,_wtoi,(wchar_t const *__nptr),wtoll,(__nptr))
#elif defined(__CRT_HAVE__wtoll) && __SIZEOF_INT__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,_wtoi,(wchar_t const *__nptr),_wtoll,(__nptr))
#elif defined(__CRT_HAVE__wtoi64) && __SIZEOF_INT__ == 8
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,_wtoi,(wchar_t const *__nptr),_wtoi64,(__nptr))
#else /* ... */
#include <local/parts.wchar.stdlib/wtoi.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL _wtoi)(wchar_t const *__nptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wtoi))(__nptr); }
#endif /* !... */
#endif /* !___wtoi_defined */
#ifndef ___wtol_defined
#define ___wtol_defined 1
#ifdef __CRT_HAVE_wtol
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),long,__NOTHROW_NCX,_wtol,(wchar_t const *__nptr),wtol,(__nptr))
#elif defined(__CRT_HAVE__wtol)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),long,__NOTHROW_NCX,_wtol,(wchar_t const *__nptr),(__nptr))
#elif defined(__CRT_HAVE_wtoi) && __SIZEOF_LONG__ == __SIZEOF_INT__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),long,__NOTHROW_NCX,_wtol,(wchar_t const *__nptr),wtoi,(__nptr))
#elif defined(__CRT_HAVE__wtoi) && __SIZEOF_LONG__ == __SIZEOF_INT__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),long,__NOTHROW_NCX,_wtol,(wchar_t const *__nptr),_wtoi,(__nptr))
#elif defined(__CRT_HAVE_wtoll) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),long,__NOTHROW_NCX,_wtol,(wchar_t const *__nptr),wtoll,(__nptr))
#elif defined(__CRT_HAVE__wtoll) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),long,__NOTHROW_NCX,_wtol,(wchar_t const *__nptr),_wtoll,(__nptr))
#elif defined(__CRT_HAVE__wtoi64) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),long,__NOTHROW_NCX,_wtol,(wchar_t const *__nptr),_wtoi64,(__nptr))
#else /* ... */
#include <local/parts.wchar.stdlib/wtol.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) long __NOTHROW_NCX(__LIBCCALL _wtol)(wchar_t const *__nptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wtol))(__nptr); }
#endif /* !... */
#endif /* !___wtol_defined */
#ifndef ___wtoi64_defined
#define ___wtoi64_defined 1
#ifdef __CRT_HAVE__wtoi64
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_wtoi64,(wchar_t const *__restrict __nptr),(__nptr))
#elif defined(__CRT_HAVE__wtoi) && __SIZEOF_INT__ == 8
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_wtoi64,(wchar_t const *__restrict __nptr),_wtoi,(__nptr))
#elif defined(__CRT_HAVE__wtol) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_wtoi64,(wchar_t const *__restrict __nptr),_wtol,(__nptr))
#elif defined(__CRT_HAVE__wtoll) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_wtoi64,(wchar_t const *__restrict __nptr),_wtoll,(__nptr))
#else /* ... */
#include <local/stdlib/_wtoi64.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wtoi64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __INT64_TYPE__ __NOTHROW_NCX(__LIBCCALL _wtoi64)(wchar_t const *__restrict __nptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wtoi64))(__nptr); })
#endif /* !... */
#endif /* !___wtoi64_defined */
#ifndef ___wcstoi64_defined
#define ___wcstoi64_defined 1
#ifdef __CRT_HAVE_wcsto64
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_wcstoi64,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcsto64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__wcstoi64)
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_wcstoi64,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstol) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_wcstoi64,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoll) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_wcstoi64,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoq) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_wcstoi64,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoimax) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_wcstoi64,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoimax,(__nptr,__endptr,__base))
#else /* ... */
#include <local/wchar/wcsto64.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __INT64_TYPE__ __NOTHROW_NCX(__LIBCCALL _wcstoi64)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsto64))(__nptr, __endptr, __base); }
#endif /* !... */
#endif /* !___wcstoi64_defined */
#ifndef ___wcstoui64_defined
#define ___wcstoui64_defined 1
#ifdef __CRT_HAVE_wcstou64
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,_wcstoui64,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstou64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__wcstoui64)
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,_wcstoui64,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoul) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,_wcstoui64,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoull) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,_wcstoui64,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstouq) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,_wcstoui64,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoumax) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,_wcstoui64,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoumax,(__nptr,__endptr,__base))
#else /* ... */
#include <local/wchar/wcstou64.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __UINT64_TYPE__ __NOTHROW_NCX(__LIBCCALL _wcstoui64)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstou64))(__nptr, __endptr, __base); }
#endif /* !... */
#endif /* !___wcstoui64_defined */
#ifndef ___wtoi_l_defined
#define ___wtoi_l_defined 1
#ifdef __CRT_HAVE__wtoi_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,_wtoi_l,(wchar_t const *__restrict __nptr, __locale_t __locale),(__nptr,__locale))
#elif defined(__CRT_HAVE__wtol_l) && __SIZEOF_INT__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,_wtoi_l,(wchar_t const *__restrict __nptr, __locale_t __locale),_wtol_l,(__nptr,__locale))
#elif defined(__CRT_HAVE__wtoll_l) && __SIZEOF_INT__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,_wtoi_l,(wchar_t const *__restrict __nptr, __locale_t __locale),_wtoll_l,(__nptr,__locale))
#elif defined(__CRT_HAVE__wtoi64_l) && __SIZEOF_INT__ == 8
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,_wtoi_l,(wchar_t const *__restrict __nptr, __locale_t __locale),_wtoi64_l,(__nptr,__locale))
#else /* ... */
#include <local/stdlib/_wtoi_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wtoi_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL _wtoi_l)(wchar_t const *__restrict __nptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wtoi_l))(__nptr, __locale); })
#endif /* !... */
#endif /* !___wtoi_l_defined */
#ifndef ___wtol_l_defined
#define ___wtol_l_defined 1
#ifdef __CRT_HAVE__wtol_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),long int,__NOTHROW_NCX,_wtol_l,(wchar_t const *__restrict __nptr, __locale_t __locale),(__nptr,__locale))
#elif defined(__CRT_HAVE__wtoi_l) && __SIZEOF_LONG__ == __SIZEOF_INT__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),long int,__NOTHROW_NCX,_wtol_l,(wchar_t const *__restrict __nptr, __locale_t __locale),_wtoi_l,(__nptr,__locale))
#elif defined(__CRT_HAVE__wtoll_l) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),long int,__NOTHROW_NCX,_wtol_l,(wchar_t const *__restrict __nptr, __locale_t __locale),_wtoll_l,(__nptr,__locale))
#elif defined(__CRT_HAVE__wtoi64_l) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),long int,__NOTHROW_NCX,_wtol_l,(wchar_t const *__restrict __nptr, __locale_t __locale),_wtoi64_l,(__nptr,__locale))
#else /* ... */
#include <local/stdlib/_wtol_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wtol_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) long int __NOTHROW_NCX(__LIBCCALL _wtol_l)(wchar_t const *__restrict __nptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wtol_l))(__nptr, __locale); })
#endif /* !... */
#endif /* !___wtol_l_defined */
#ifndef ___wtoi64_l_defined
#define ___wtoi64_l_defined 1
#ifdef __CRT_HAVE__wtoi64_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_wtoi64_l,(wchar_t const *__restrict __nptr, __locale_t __locale),(__nptr,__locale))
#elif defined(__CRT_HAVE__wtoi_l) && __SIZEOF_INT__ == 8
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_wtoi64_l,(wchar_t const *__restrict __nptr, __locale_t __locale),_wtoi_l,(__nptr,__locale))
#elif defined(__CRT_HAVE__wtol_l) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_wtoi64_l,(wchar_t const *__restrict __nptr, __locale_t __locale),_wtol_l,(__nptr,__locale))
#elif defined(__CRT_HAVE__wtoll_l) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_wtoi64_l,(wchar_t const *__restrict __nptr, __locale_t __locale),_wtoll_l,(__nptr,__locale))
#else /* ... */
#include <local/stdlib/_wtoi64_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wtoi64_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __INT64_TYPE__ __NOTHROW_NCX(__LIBCCALL _wtoi64_l)(wchar_t const *__restrict __nptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wtoi64_l))(__nptr, __locale); })
#endif /* !... */
#endif /* !___wtoi64_l_defined */
#ifndef ___wcstoi64_l_defined
#define ___wcstoi64_l_defined 1
#ifdef __CRT_HAVE_wcsto64_l
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_wcstoi64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcsto64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoi64_l)
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_wcstoi64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstol_l) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_wcstoi64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstol_l) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_wcstoi64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstol_l) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_wcstoi64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoll_l) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_wcstoi64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoll_l) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_wcstoi64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoll_l) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_wcstoi64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoimax_l) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_wcstoi64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoimax_l) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_wcstoi64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoimax_l) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_wcstoi64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoimax_l,(__nptr,__endptr,__base,__locale))
#else /* ... */
#include <local/wchar/wcsto64_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __INT64_TYPE__ __NOTHROW_NCX(__LIBCCALL _wcstoi64_l)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsto64_l))(__nptr, __endptr, __base, __locale); }
#endif /* !... */
#endif /* !___wcstoi64_l_defined */
#ifndef ___wcstoui64_l_defined
#define ___wcstoui64_l_defined 1
#ifdef __CRT_HAVE_wcstou64_l
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,_wcstoui64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstou64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoui64_l)
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,_wcstoui64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoul_l) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,_wcstoui64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoul_l) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,_wcstoui64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoul_l) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,_wcstoui64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoull_l) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,_wcstoui64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoull_l) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,_wcstoui64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoull_l) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,_wcstoui64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoumax_l) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,_wcstoui64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoumax_l) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,_wcstoui64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoumax_l) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,_wcstoui64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoumax_l,(__nptr,__endptr,__base,__locale))
#else /* ... */
#include <local/wchar/wcstou64_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __UINT64_TYPE__ __NOTHROW_NCX(__LIBCCALL _wcstoui64_l)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstou64_l))(__nptr, __endptr, __base, __locale); }
#endif /* !... */
#endif /* !___wcstoui64_l_defined */
#ifdef __LONGLONG
#ifndef ___wcstoll_l_defined
#define ___wcstoll_l_defined 1
#ifdef __CRT_HAVE_wcstoll_l
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,_wcstoll_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoll_l)
__CDECLARE(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,_wcstoll_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoll_l)
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,_wcstoll_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstol_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,_wcstoll_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstol_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,_wcstoll_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstol_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,_wcstoll_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoi64_l) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,_wcstoll_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoi64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoimax_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,_wcstoll_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoimax_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,_wcstoll_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoimax_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,_wcstoll_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoimax_l,(__nptr,__endptr,__base,__locale))
#else /* ... */
#include <local/wchar/wcstoll_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __LONGLONG __NOTHROW_NCX(__LIBCCALL _wcstoll_l)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoll_l))(__nptr, __endptr, __base, __locale); }
#endif /* !... */
#endif /* !___wcstoll_l_defined */
#ifndef ___wcstoull_l_defined
#define ___wcstoull_l_defined 1
#ifdef __CRT_HAVE_wcstoull_l
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,_wcstoull_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoull_l)
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,_wcstoull_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoul_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,_wcstoull_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoul_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,_wcstoull_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoul_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,_wcstoull_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoui64_l) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,_wcstoull_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoui64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoumax_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,_wcstoull_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoumax_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,_wcstoull_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoumax_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,_wcstoull_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoumax_l,(__nptr,__endptr,__base,__locale))
#else /* ... */
#include <local/wchar/wcstoull_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __ULONGLONG __NOTHROW_NCX(__LIBCCALL _wcstoull_l)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoull_l))(__nptr, __endptr, __base, __locale); }
#endif /* !... */
#endif /* !___wcstoull_l_defined */
#ifndef ___wtoll_defined
#define ___wtoll_defined 1
#ifdef __CRT_HAVE_wtoll
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,_wtoll,(wchar_t const *__nptr),wtoll,(__nptr))
#elif defined(__CRT_HAVE__wtoll)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,_wtoll,(wchar_t const *__nptr),(__nptr))
#elif defined(__CRT_HAVE_wtoi) && __SIZEOF_LONG_LONG__ == __SIZEOF_INT__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,_wtoll,(wchar_t const *__nptr),wtoi,(__nptr))
#elif defined(__CRT_HAVE__wtoi) && __SIZEOF_LONG_LONG__ == __SIZEOF_INT__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,_wtoll,(wchar_t const *__nptr),_wtoi,(__nptr))
#elif defined(__CRT_HAVE_wtol) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,_wtoll,(wchar_t const *__nptr),wtol,(__nptr))
#elif defined(__CRT_HAVE__wtol) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,_wtoll,(wchar_t const *__nptr),_wtol,(__nptr))
#elif defined(__CRT_HAVE__wtoi64) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,_wtoll,(wchar_t const *__nptr),_wtoi64,(__nptr))
#else /* ... */
#include <local/parts.wchar.stdlib/wtoll.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __LONGLONG __NOTHROW_NCX(__LIBCCALL _wtoll)(wchar_t const *__nptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wtoll))(__nptr); }
#endif /* !... */
#endif /* !___wtoll_defined */
#ifndef ___wtoll_l_defined
#define ___wtoll_l_defined 1
#ifdef __CRT_HAVE__wtoll_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,_wtoll_l,(wchar_t const *__restrict __nptr, __locale_t __locale),(__nptr,__locale))
#elif defined(__CRT_HAVE__wtoi_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INT__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,_wtoll_l,(wchar_t const *__restrict __nptr, __locale_t __locale),_wtoi_l,(__nptr,__locale))
#elif defined(__CRT_HAVE__wtol_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,_wtoll_l,(wchar_t const *__restrict __nptr, __locale_t __locale),_wtol_l,(__nptr,__locale))
#elif defined(__CRT_HAVE__wtoi64_l) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,_wtoll_l,(wchar_t const *__restrict __nptr, __locale_t __locale),_wtoi64_l,(__nptr,__locale))
#else /* ... */
#include <local/stdlib/_wtoll_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wtoll_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __LONGLONG __NOTHROW_NCX(__LIBCCALL _wtoll_l)(wchar_t const *__restrict __nptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wtoll_l))(__nptr, __locale); })
#endif /* !... */
#endif /* !___wtoll_l_defined */
#endif /* __LONGLONG */
#endif /* !_WSTDLIB_DEFINED */
#ifndef _WSTDLIBP_DEFINED
#define _WSTDLIBP_DEFINED 1
#ifndef ___wfullpath_defined
#define ___wfullpath_defined 1
#ifdef __CRT_HAVE__wfullpath
__CDECLARE(,wchar_t *,__NOTHROW_NCX,_wfullpath,(wchar_t *__buf, wchar_t const *__path, __SIZE_TYPE__ __buflen),(__buf,__path,__buflen))
#else /* __CRT_HAVE__wfullpath */
#undef ___wfullpath_defined
#endif /* !__CRT_HAVE__wfullpath */
#endif /* !___wfullpath_defined */
#ifndef ___wmakepath_s_defined
#define ___wmakepath_s_defined 1
#ifdef __CRT_HAVE__wmakepath_s
__CDECLARE(__ATTR_NONNULL((1)),errno_t,__NOTHROW_NCX,_wmakepath_s,(wchar_t *__buf, __SIZE_TYPE__ __buflen, wchar_t const *__drive, wchar_t const *__dir, wchar_t const *__file, wchar_t const *__ext),(__buf,__buflen,__drive,__dir,__file,__ext))
#else /* __CRT_HAVE__wmakepath_s */
#include <local/stdlib/_wmakepath_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wmakepath_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) errno_t __NOTHROW_NCX(__LIBCCALL _wmakepath_s)(wchar_t *__buf, __SIZE_TYPE__ __buflen, wchar_t const *__drive, wchar_t const *__dir, wchar_t const *__file, wchar_t const *__ext) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wmakepath_s))(__buf, __buflen, __drive, __dir, __file, __ext); })
#endif /* !__CRT_HAVE__wmakepath_s */
#endif /* !___wmakepath_s_defined */
#ifndef ___wmakepath_defined
#define ___wmakepath_defined 1
#ifdef __CRT_HAVE__wmakepath
__CDECLARE_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,_wmakepath,(wchar_t *__restrict __buf, wchar_t const *__drive, wchar_t const *__dir, wchar_t const *__file, wchar_t const *__ext),(__buf,__drive,__dir,__file,__ext))
#else /* __CRT_HAVE__wmakepath */
#include <local/stdlib/_wmakepath.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wmakepath, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) void __NOTHROW_NCX(__LIBCCALL _wmakepath)(wchar_t *__restrict __buf, wchar_t const *__drive, wchar_t const *__dir, wchar_t const *__file, wchar_t const *__ext) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wmakepath))(__buf, __drive, __dir, __file, __ext); })
#endif /* !__CRT_HAVE__wmakepath */
#endif /* !___wmakepath_defined */
#ifndef _CRT_WPERROR_DEFINED
#define _CRT_WPERROR_DEFINED 1
#ifdef __CRT_HAVE__wperror
__CDECLARE_VOID(__ATTR_COLD,__THROWING,_wperror,(__WCHAR_TYPE__ const *__restrict __message),(__message))
#else /* __CRT_HAVE__wperror */
#include <__crt.h>
#include <parts/errno.h>
#if !defined(__NO_STDSTREAMS) && defined(__libc_geterrno) && (defined(__CRT_HAVE_fprintf) || defined(__CRT_HAVE__IO_fprintf) || defined(__CRT_HAVE_fprintf_s) || defined(__CRT_HAVE_fprintf_unlocked) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock))
#include <local/stdio/_wperror.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wperror, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_COLD void (__LIBCCALL _wperror)(__WCHAR_TYPE__ const *__restrict __message) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wperror))(__message); })
#else /* !__NO_STDSTREAMS && __libc_geterrno && (__CRT_HAVE_fprintf || __CRT_HAVE__IO_fprintf || __CRT_HAVE_fprintf_s || __CRT_HAVE_fprintf_unlocked || __CRT_HAVE_vfprintf || __CRT_HAVE_vfprintf_s || __CRT_HAVE__IO_vfprintf || __CRT_HAVE_vfprintf_unlocked || __CRT_HAVE_file_printer || __CRT_HAVE_file_printer_unlocked || __CRT_HAVE_fputc || __CRT_HAVE_putc || __CRT_HAVE__IO_putc || __CRT_HAVE_fputc_unlocked || __CRT_HAVE_putc_unlocked || (__CRT_DOS && __CRT_HAVE__flsbuf) || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock) */
#undef _CRT_WPERROR_DEFINED
#endif /* __NO_STDSTREAMS || !__libc_geterrno || (!__CRT_HAVE_fprintf && !__CRT_HAVE__IO_fprintf && !__CRT_HAVE_fprintf_s && !__CRT_HAVE_fprintf_unlocked && !__CRT_HAVE_vfprintf && !__CRT_HAVE_vfprintf_s && !__CRT_HAVE__IO_vfprintf && !__CRT_HAVE_vfprintf_unlocked && !__CRT_HAVE_file_printer && !__CRT_HAVE_file_printer_unlocked && !__CRT_HAVE_fputc && !__CRT_HAVE_putc && !__CRT_HAVE__IO_putc && !__CRT_HAVE_fputc_unlocked && !__CRT_HAVE_putc_unlocked && (!__CRT_DOS || !__CRT_HAVE__flsbuf) && !__CRT_HAVE_fwrite && !__CRT_HAVE__IO_fwrite && !__CRT_HAVE_fwrite_s && !__CRT_HAVE_fwrite_unlocked && !__CRT_HAVE__fwrite_nolock) */
#endif /* !__CRT_HAVE__wperror */
#endif /* !_CRT_WPERROR_DEFINED */
#ifndef ___wputenv_defined
#define ___wputenv_defined 1
#ifdef __CRT_HAVE__wputenv
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,_wputenv,(wchar_t *__string),(__string))
#else /* __CRT_HAVE__wputenv */
#undef ___wputenv_defined
#endif /* !__CRT_HAVE__wputenv */
#endif /* !___wputenv_defined */
#ifndef ___wputenv_s_defined
#define ___wputenv_s_defined 1
#ifdef __CRT_HAVE__wputenv_s
__CDECLARE(,errno_t,__NOTHROW_NCX,_wputenv_s,(wchar_t const *__varname, wchar_t const *__val),(__varname,__val))
#else /* __CRT_HAVE__wputenv_s */
#undef ___wputenv_s_defined
#endif /* !__CRT_HAVE__wputenv_s */
#endif /* !___wputenv_s_defined */
#ifndef ___wsearchenv_s_defined
#define ___wsearchenv_s_defined 1
#ifdef __CRT_HAVE__wsearchenv_s
__CDECLARE(__ATTR_NONNULL((1, 2, 3)),errno_t,__NOTHROW_RPC,_wsearchenv_s,(wchar_t const *__file, wchar_t const *__envvar, wchar_t *__restrict __resultpath, __SIZE_TYPE__ __buflen),(__file,__envvar,__resultpath,__buflen))
#else /* __CRT_HAVE__wsearchenv_s */
#undef ___wsearchenv_s_defined
#endif /* !__CRT_HAVE__wsearchenv_s */
#endif /* !___wsearchenv_s_defined */
#ifndef ___wsearchenv_defined
#define ___wsearchenv_defined 1
#ifdef __CRT_HAVE__wsearchenv
__CDECLARE_VOID(__ATTR_NONNULL((1, 2, 3)),__NOTHROW_RPC,_wsearchenv,(wchar_t const *__file, wchar_t const *__envvar, wchar_t *__restrict __resultpath),(__file,__envvar,__resultpath))
#elif defined(__CRT_HAVE__wsearchenv_s)
#include <local/stdlib/_wsearchenv.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wsearchenv, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2, 3)) void __NOTHROW_RPC(__LIBCCALL _wsearchenv)(wchar_t const *__file, wchar_t const *__envvar, wchar_t *__restrict __resultpath) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wsearchenv))(__file, __envvar, __resultpath); })
#else /* ... */
#undef ___wsearchenv_defined
#endif /* !... */
#endif /* !___wsearchenv_defined */
#ifndef ___wsplitpath_defined
#define ___wsplitpath_defined 1
#ifdef __CRT_HAVE__wsplitpath
__CDECLARE_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,_wsplitpath,(wchar_t const *__restrict __abspath, wchar_t *__drive, wchar_t *__dir, wchar_t *__file, wchar_t *__ext),(__abspath,__drive,__dir,__file,__ext))
#else /* __CRT_HAVE__wsplitpath */
#include <local/stdlib/_wsplitpath.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wsplitpath, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) void __NOTHROW_NCX(__LIBCCALL _wsplitpath)(wchar_t const *__restrict __abspath, wchar_t *__drive, wchar_t *__dir, wchar_t *__file, wchar_t *__ext) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wsplitpath))(__abspath, __drive, __dir, __file, __ext); })
#endif /* !__CRT_HAVE__wsplitpath */
#endif /* !___wsplitpath_defined */
#ifndef ___wsplitpath_s_defined
#define ___wsplitpath_s_defined 1
#ifdef __CRT_HAVE__wsplitpath_s
__CDECLARE(__ATTR_NONNULL((1)),errno_t,__NOTHROW_NCX,_wsplitpath_s,(wchar_t const *__restrict __abspath, wchar_t *__drive, __SIZE_TYPE__ __drivelen, wchar_t *__dir, __SIZE_TYPE__ __dirlen, wchar_t *__file, __SIZE_TYPE__ __filelen, wchar_t *__ext, __SIZE_TYPE__ __extlen),(__abspath,__drive,__drivelen,__dir,__dirlen,__file,__filelen,__ext,__extlen))
#else /* __CRT_HAVE__wsplitpath_s */
#include <local/stdlib/_wsplitpath_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wsplitpath_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) errno_t __NOTHROW_NCX(__LIBCCALL _wsplitpath_s)(wchar_t const *__restrict __abspath, wchar_t *__drive, __SIZE_TYPE__ __drivelen, wchar_t *__dir, __SIZE_TYPE__ __dirlen, wchar_t *__file, __SIZE_TYPE__ __filelen, wchar_t *__ext, __SIZE_TYPE__ __extlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wsplitpath_s))(__abspath, __drive, __drivelen, __dir, __dirlen, __file, __filelen, __ext, __extlen); })
#endif /* !__CRT_HAVE__wsplitpath_s */
#endif /* !___wsplitpath_s_defined */
#endif /* !_WSTDLIBP_DEFINED */

#endif /* __CC__ */
#endif /* __USE_DOS */



__SYSDECL_END

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
#define _CXX_STDONLY_CSTDLIB 1
#undef _STDLIB_H
#endif /* __CXX_SYSTEM_HEADER */
#endif /* !_CXX_STDONLY_CSTDLIB */
#endif /* !_STDLIB_H */
