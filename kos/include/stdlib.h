/* HASH CRC-32:0x7db39028 */
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
#if !defined(__getenv_defined) && defined(__std_getenv_defined)
#define __getenv_defined 1
__NAMESPACE_STD_USING(getenv)
#endif /* !__getenv_defined && !__std_getenv_defined */
__NAMESPACE_STD_USING(mblen)
__NAMESPACE_STD_USING(mbtowc)
__NAMESPACE_STD_USING(wctomb)
__NAMESPACE_STD_USING(mbstowcs)
__NAMESPACE_STD_USING(wcstombs)
#if !defined(__system_defined) && defined(__std_system_defined)
#define __system_defined 1
__NAMESPACE_STD_USING(system)
#endif /* !__system_defined && !__std_system_defined */
#if !defined(__abort_defined) && defined(__std_abort_defined)
#define __abort_defined 1
__NAMESPACE_STD_USING(abort)
#endif /* !__abort_defined && !__std_abort_defined */
#if !defined(__exit_defined) && defined(__std_exit_defined)
#define __exit_defined 1
__NAMESPACE_STD_USING(exit)
#endif /* !__exit_defined && !__std_exit_defined */
#if !defined(__atexit_defined) && defined(__std_atexit_defined)
#define __atexit_defined 1
__NAMESPACE_STD_USING(atexit)
#endif /* !__atexit_defined && !__std_atexit_defined */
#if defined(__USE_ISOC11) || defined(__USE_ISOCXX11)
#if !defined(__quick_exit_defined) && defined(__std_quick_exit_defined)
#define __quick_exit_defined 1
__NAMESPACE_STD_USING(quick_exit)
#endif /* !__quick_exit_defined && !__std_quick_exit_defined */
#if !defined(__at_quick_exit_defined) && defined(__std_at_quick_exit_defined)
#define __at_quick_exit_defined 1
__NAMESPACE_STD_USING(at_quick_exit)
#endif /* !__at_quick_exit_defined && !__std_at_quick_exit_defined */
#endif /* __USE_ISOC11 || __USE_ISOCXX11 */
#ifdef __USE_ISOC99
#if !defined(___Exit_defined) && defined(__std__Exit_defined)
#define ___Exit_defined 1
__NAMESPACE_STD_USING(_Exit)
#endif /* !___Exit_defined && !__std__Exit_defined */
#endif /* __USE_ISOC99 */
#if !defined(__malloc_defined) && defined(__std_malloc_defined)
#define __malloc_defined 1
__NAMESPACE_STD_USING(malloc)
#endif /* !__malloc_defined && !__std_malloc_defined */
#if !defined(__calloc_defined) && defined(__std_calloc_defined)
#define __calloc_defined 1
__NAMESPACE_STD_USING(calloc)
#endif /* !__calloc_defined && !__std_calloc_defined */
#if !defined(__realloc_defined) && defined(__std_realloc_defined)
#define __realloc_defined 1
__NAMESPACE_STD_USING(realloc)
#endif /* !__realloc_defined && !__std_realloc_defined */
#if !defined(__free_defined) && defined(__std_free_defined)
#define __free_defined 1
__NAMESPACE_STD_USING(free)
#endif /* !__free_defined && !__std_free_defined */
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
#endif /* !__strtoull_defined && !__std_strtoull_defined */
#if !defined(__strtoll_defined) && defined(__std_strtoll_defined)
#define __strtoll_defined 1
__NAMESPACE_STD_USING(strtoll)
#endif /* !__strtoll_defined && !__std_strtoll_defined */
#ifndef __NO_FPU
__NAMESPACE_STD_USING(atof)
__NAMESPACE_STD_USING(strtod)
#if !defined(__strtof_defined) && defined(__std_strtof_defined)
#define __strtof_defined 1
__NAMESPACE_STD_USING(strtof)
#endif /* !__strtof_defined && !__std_strtof_defined */
#if !defined(__strtold_defined) && defined(__std_strtold_defined)
#define __strtold_defined 1
__NAMESPACE_STD_USING(strtold)
#endif /* !__strtold_defined && !__std_strtold_defined */
#endif /* !__NO_FPU */
#if !defined(__aligned_alloc_defined) && defined(__std_aligned_alloc_defined)
#define __aligned_alloc_defined 1
__NAMESPACE_STD_USING(aligned_alloc)
#endif /* !__aligned_alloc_defined && !__std_aligned_alloc_defined */
#undef _CXX_STDONLY_CSTDLIB
#endif /* !__CXX_SYSTEM_HEADER */
#else /* _CXX_STDONLY_CSTDLIB */
#include "__stdinc.h"
#include "__crt.h"
#include <kos/anno.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <bits/types.h>
#include <hybrid/typecore.h>
#ifdef __USE_MISC
#include <alloca.h>
#endif /* __USE_MISC */
#ifdef __USE_DOS
#include <xlocale.h>
#include <bits/byteswap.h>
#endif /* __USE_DOS */
#ifdef __USE_GNU
#include <xlocale.h>
#endif /* __USE_GNU */

__SYSDECL_BEGIN

#ifdef __CRT_DOS_PRIMARY
#define RAND_MAX 0x7fff /* TODO: Check what this really is */
#elif defined(__CRT_KOS_PRIMARY)
#define RAND_MAX 0x7fffffff
#elif defined(__CRT_GLC_PRIMARY)
#define RAND_MAX 0x7fff /* TODO: Check what this really is */
#elif defined(__CRT_CYG_PRIMARY)
#define RAND_MAX 0x7fff /* TODO: Check what this really is */
#else
#define RAND_MAX 0x7fff
#endif

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

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

#if defined(__USE_XOPEN) || defined(__USE_XOPEN2K8)
#ifndef __WAIT_MACROS_DEFINED
#define __WAIT_MACROS_DEFINED 1
#include <bits/waitflags.h>
#include <bits/waitstatus.h>

#ifdef __USE_MISC
#if defined(__GNUC__) && !defined(__cplusplus)
#   define __WAIT_INT(status) (__extension__(((union{ __typeof__(status) __inval; int __ival; }) { .__inval = (status) }).__ival))
#else /* __GNUC__ && !__cplusplus */
#   define __WAIT_INT(status) (*(int *)&(status))
#endif /* !__GNUC__ || __cplusplus */
#ifdef __NO_ATTR_TRANSPARENT_UNION
#   define __WAIT_STATUS      void *
#   define __WAIT_STATUS_DEFN void *
#else
typedef union {
	union wait *__uptr;
	int        *__iptr;
} __WAIT_STATUS __ATTR_TRANSPARENT_UNION;
#   define __WAIT_STATUS_DEFN int *
#endif
#else /* __USE_MISC */
#   define __WAIT_INT(status)  (status)
#   define __WAIT_STATUS        int *
#   define __WAIT_STATUS_DEFN   int *
#endif /* !__USE_MISC */
#   define WEXITSTATUS(status)  __WEXITSTATUS(__WAIT_INT(status))
#   define WTERMSIG(status)     __WTERMSIG(__WAIT_INT(status))
#   define WSTOPSIG(status)     __WSTOPSIG(__WAIT_INT(status))
#   define WIFEXITED(status)    __WIFEXITED(__WAIT_INT(status))
#   define WIFSIGNALED(status)  __WIFSIGNALED(__WAIT_INT(status))
#   define WIFSTOPPED(status)   __WIFSTOPPED(__WAIT_INT(status))
#ifdef __WIFCONTINUED
#   define WIFCONTINUED(status) __WIFCONTINUED(__WAIT_INT(status))
#endif
#endif /* !__WAIT_MACROS_DEFINED */
#endif /* __USE_XOPEN || __USE_XOPEN2K8 */

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
typedef int (__LIBCCALL *__compar_fn_t)(void const *__a, void const *__b);
#ifdef __USE_GNU
typedef __compar_fn_t comparison_fn_t;
#endif /* __USE_GNU */
#endif /* __COMPAR_FN_T */

#ifndef ____atexit_func_t_defined
#define ____atexit_func_t_defined 1
typedef void (*__LIBCCALL __atexit_func_t)(void);
#endif /* !____atexit_func_t_defined */

#ifdef __USE_GNU
#ifndef __compar_d_fn_t_defined
#define __compar_d_fn_t_defined 1
typedef int (__LIBCCALL *__compar_d_fn_t)(void const *__a, void const *__b, void *__arg);
#endif /* !__compar_d_fn_t_defined */
#ifdef __CRT_HAVE_qsort_r
__CDECLARE_VOID(__ATTR_NONNULL((1, 4)),,qsort_r,(void *__pbase, __SIZE_TYPE__ __item_count, __SIZE_TYPE__ __item_size, __compar_d_fn_t __cmp, void *__arg),(__pbase,__item_count,__item_size,__cmp,__arg)) __THROWS(...)
#else /* LIBC: qsort_r */
#include <local/stdlib/qsort_r.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(qsort_r, __FORCELOCAL __ATTR_NONNULL((1, 4)) void (__LIBCCALL qsort_r)(void *__pbase, __SIZE_TYPE__ __item_count, __SIZE_TYPE__ __item_size, __compar_d_fn_t __cmp, void *__arg) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(qsort_r))(__pbase, __item_count, __item_size, __cmp, __arg); })
#endif /* qsort_r... */
#endif /* __USE_GNU */

#ifdef __USE_KOS
#ifndef __compar_d_fn_t_defined
#define __compar_d_fn_t_defined 1
typedef int (__LIBCCALL *__compar_d_fn_t)(void const *__a, void const *__b, void *__arg);
#endif /* !__compar_d_fn_t_defined */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STDLIB_H_PROTO)
#ifdef __CRT_HAVE_bsearch_r
extern "C++" {
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2, 5)),void *,__NOTHROW_NCX,bsearch_r,(void const *__pkey, void *__pbase, __SIZE_TYPE__ __item_count, __SIZE_TYPE__ __item_size, __compar_d_fn_t __cmp, void *__arg),bsearch_r,(__pkey, __pbase, __item_count, __item_size, __cmp, __arg))
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2, 5)),void const *,__NOTHROW_NCX,bsearch_r,(void const *__pkey, void const *__pbase, __SIZE_TYPE__ __item_count, __SIZE_TYPE__ __item_size, __compar_d_fn_t __cmp, void *__arg),bsearch_r,(__pkey, __pbase, __item_count, __item_size, __cmp, __arg))
}
#else /* LIBC: bsearch_r */
#include <local/stdlib/bsearch_r.h>
extern "C++" {
__FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((1, 2, 5)) void *__NOTHROW_NCX(__LIBCCALL bsearch_r)(void const *__pkey, void *__pbase, __SIZE_TYPE__ __item_count, __SIZE_TYPE__ __item_size, __compar_d_fn_t __cmp, void *__arg) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(bsearch_r))(__pkey, __pbase, __item_count, __item_size, __cmp, __arg); }
__FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((1, 2, 5)) void const *__NOTHROW_NCX(__LIBCCALL bsearch_r)(void const *__pkey, void const *__pbase, __SIZE_TYPE__ __item_count, __SIZE_TYPE__ __item_size, __compar_d_fn_t __cmp, void *__arg) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(bsearch_r))(__pkey, __pbase, __item_count, __item_size, __cmp, __arg); }
}
#endif /* bsearch_r... */
#else /* __cplusplus && __CORRECT_ISO_CPP_STDLIB_H_PROTO */
#ifdef __CRT_HAVE_bsearch_r
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 2, 5)),void *,__NOTHROW_NCX,bsearch_r,(void const *__pkey, void const *__pbase, __SIZE_TYPE__ __item_count, __SIZE_TYPE__ __item_size, __compar_d_fn_t __cmp, void *__arg),(__pkey,__pbase,__item_count,__item_size,__cmp,__arg))
#else /* LIBC: bsearch_r */
#include <local/stdlib/bsearch_r.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(bsearch_r, __FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((1, 2, 5)) void *__NOTHROW_NCX(__LIBCCALL bsearch_r)(void const *__pkey, void const *__pbase, __SIZE_TYPE__ __item_count, __SIZE_TYPE__ __item_size, __compar_d_fn_t __cmp, void *__arg) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(bsearch_r))(__pkey, __pbase, __item_count, __item_size, __cmp, __arg); })
#endif /* bsearch_r... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STDLIB_H_PROTO */
#endif /* __USE_KOS */

__NAMESPACE_STD_BEGIN
#ifdef __CRT_HAVE_qsort
__CDECLARE_VOID(__ATTR_NONNULL((1, 4)),,qsort,(void *__pbase, size_t __item_count, size_t __item_size, __compar_fn_t __cmp),(__pbase,__item_count,__item_size,__cmp)) __THROWS(...)
#else /* LIBC: qsort */
__NAMESPACE_STD_END
#include <local/stdlib/qsort.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(qsort, __FORCELOCAL __ATTR_NONNULL((1, 4)) void (__LIBCCALL qsort)(void *__pbase, size_t __item_count, size_t __item_size, __compar_fn_t __cmp) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(qsort))(__pbase, __item_count, __item_size, __cmp); })
#endif /* qsort... */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STDLIB_H_PROTO)
#ifdef __CRT_HAVE_bsearch
extern "C++" {
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2, 5)),void *,__NOTHROW_NCX,bsearch,(void const *__pkey, void *__pbase, size_t __item_count, size_t __item_size, __compar_fn_t __cmp),bsearch,(__pkey, __pbase, __item_count, __item_size, __cmp))
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2, 5)),void const *,__NOTHROW_NCX,bsearch,(void const *__pkey, void const *__pbase, size_t __item_count, size_t __item_size, __compar_fn_t __cmp),bsearch,(__pkey, __pbase, __item_count, __item_size, __cmp))
}
#else /* LIBC: bsearch */
__NAMESPACE_STD_END
#include <local/stdlib/bsearch.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
__FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((1, 2, 5)) void *__NOTHROW_NCX(__LIBCCALL bsearch)(void const *__pkey, void *__pbase, size_t __item_count, size_t __item_size, __compar_fn_t __cmp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(bsearch))(__pkey, __pbase, __item_count, __item_size, __cmp); }
__FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((1, 2, 5)) void const *__NOTHROW_NCX(__LIBCCALL bsearch)(void const *__pkey, void const *__pbase, size_t __item_count, size_t __item_size, __compar_fn_t __cmp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(bsearch))(__pkey, __pbase, __item_count, __item_size, __cmp); }
}
#endif /* bsearch... */
#else /* __cplusplus && __CORRECT_ISO_CPP_STDLIB_H_PROTO */
#ifdef __CRT_HAVE_bsearch
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 2, 5)),void *,__NOTHROW_NCX,bsearch,(void const *__pkey, void const *__pbase, size_t __item_count, size_t __item_size, __compar_fn_t __cmp),(__pkey,__pbase,__item_count,__item_size,__cmp))
#else /* LIBC: bsearch */
__NAMESPACE_STD_END
#include <local/stdlib/bsearch.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(bsearch, __FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((1, 2, 5)) void *__NOTHROW_NCX(__LIBCCALL bsearch)(void const *__pkey, void const *__pbase, size_t __item_count, size_t __item_size, __compar_fn_t __cmp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(bsearch))(__pkey, __pbase, __item_count, __item_size, __cmp); })
#endif /* bsearch... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STDLIB_H_PROTO */
#if __has_builtin(__builtin_labs) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_labs)
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED long __NOTHROW(__LIBCCALL labs)(long __x) { return __builtin_labs(__x); }
#elif defined(__CRT_HAVE_labs)
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,long,__NOTHROW,labs,(long __x),(__x))
#elif defined(__CRT_HAVE_abs) && (__SIZEOF_LONG__ == __SIZEOF_INT__)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long,__NOTHROW,labs,(long __x),abs,(__x))
#elif defined(__CRT_HAVE_llabs) && (__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long,__NOTHROW,labs,(long __x),llabs,(__x))
#elif defined(__CRT_HAVE_imaxabs) && (__SIZEOF_LONG__ == __SIZEOF_INTMAX_T__)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long,__NOTHROW,labs,(long __x),imaxabs,(__x))
#else /* LIBC: labs */
__NAMESPACE_STD_END
#include <local/stdlib/labs.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(labs, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED long __NOTHROW(__LIBCCALL labs)(long __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(labs))(__x); })
#endif /* labs... */
#ifdef __USE_ISOC99
#if __has_builtin(__builtin_llabs) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_llabs)
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __LONGLONG __NOTHROW(__LIBCCALL llabs)(__LONGLONG __x) { return __builtin_llabs(__x); }
#elif defined(__CRT_HAVE_llabs)
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,llabs,(__LONGLONG __x),(__x))
#elif defined(__CRT_HAVE_abs) && (__SIZEOF_LONG_LONG__ == __SIZEOF_INT__)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,llabs,(__LONGLONG __x),abs,(__x))
#elif defined(__CRT_HAVE_labs) && (__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,llabs,(__LONGLONG __x),labs,(__x))
#elif defined(__CRT_HAVE_imaxabs) && (__SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,llabs,(__LONGLONG __x),imaxabs,(__x))
#else /* LIBC: llabs */
__NAMESPACE_STD_END
#include <local/stdlib/llabs.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(llabs, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __LONGLONG __NOTHROW(__LIBCCALL llabs)(__LONGLONG __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(llabs))(__x); })
#endif /* llabs... */
#endif /* __USE_ISOC99 */
#ifdef __CRT_HAVE_ldiv
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,struct __ldiv_struct,__NOTHROW_NCX,ldiv,(long __numer, long __denom),(__numer,__denom))
#elif defined(__CRT_HAVE_div) && (__SIZEOF_LONG__ == __SIZEOF_INT__)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,struct __ldiv_struct,__NOTHROW_NCX,ldiv,(long __numer, long __denom),div,(__numer,__denom))
#elif defined(__CRT_HAVE_lldiv) && (__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,struct __ldiv_struct,__NOTHROW_NCX,ldiv,(long __numer, long __denom),lldiv,(__numer,__denom))
#elif defined(__CRT_HAVE_imaxdiv) && (__SIZEOF_LONG__ == __SIZEOF_INTMAX_T__)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,struct __ldiv_struct,__NOTHROW_NCX,ldiv,(long __numer, long __denom),imaxdiv,(__numer,__denom))
#else /* LIBC: ldiv */
__NAMESPACE_STD_END
#include <local/stdlib/ldiv.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(ldiv, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED struct __ldiv_struct __NOTHROW_NCX(__LIBCCALL ldiv)(long __numer, long __denom) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ldiv))(__numer, __denom); })
#endif /* ldiv... */
#ifdef __USE_ISOC99
#ifdef __CRT_HAVE_lldiv
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,struct __lldiv_struct,__NOTHROW_NCX,lldiv,(__LONGLONG __numer, __LONGLONG __denom),(__numer,__denom))
#elif defined(__CRT_HAVE_div) && (__SIZEOF_LONG_LONG__ == __SIZEOF_INT__)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,struct __lldiv_struct,__NOTHROW_NCX,lldiv,(__LONGLONG __numer, __LONGLONG __denom),div,(__numer,__denom))
#elif defined(__CRT_HAVE_ldiv) && (__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,struct __lldiv_struct,__NOTHROW_NCX,lldiv,(__LONGLONG __numer, __LONGLONG __denom),ldiv,(__numer,__denom))
#elif defined(__CRT_HAVE_imaxdiv) && (__SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,struct __lldiv_struct,__NOTHROW_NCX,lldiv,(__LONGLONG __numer, __LONGLONG __denom),imaxdiv,(__numer,__denom))
#else /* LIBC: lldiv */
__NAMESPACE_STD_END
#include <local/stdlib/lldiv.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(lldiv, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED struct __lldiv_struct __NOTHROW_NCX(__LIBCCALL lldiv)(__LONGLONG __numer, __LONGLONG __denom) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lldiv))(__numer, __denom); })
#endif /* lldiv... */
#endif /* __USE_ISOC99 */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STDLIB_H_PROTO)
extern "C++" {
#ifdef __CRT_HAVE_abs
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,abs,(int __x),abs,(__x))
#elif defined(__CRT_HAVE_labs) && __SIZEOF_INT__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,abs,(int __x),labs,(__x))
#elif defined(__CRT_HAVE_llabs) && __SIZEOF_INT__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,abs,(int __x),llabs,(__x))
#elif defined(__CRT_HAVE_imaxabs) && __SIZEOF_INT__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,abs,(int __x),imaxabs,(__x))
#elif __has_builtin(__builtin_abs) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_abs)
__LOCAL __ATTR_CONST __ATTR_WUNUSED int (__LIBCCALL abs)(int __x) { return __builtin_abs(__x); }
#else /* abs... */
__LOCAL __ATTR_CONST __ATTR_WUNUSED int (__LIBCCALL abs)(int __x) { return __x < 0 ? -__x : __x; }
#endif /* !abs... */
#ifdef __CRT_HAVE_labs
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long,__NOTHROW,abs,(long __x),labs,(__x))
#elif defined(__CRT_HAVE_abs) && __SIZEOF_LONG__ == __SIZEOF_INT__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long,__NOTHROW,abs,(long __x),abs,(__x))
#elif defined(__CRT_HAVE_llabs) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long,__NOTHROW,abs,(long __x),llabs,(__x))
#elif defined(__CRT_HAVE_imaxabs) && __SIZEOF_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long,__NOTHROW,abs,(long __x),imaxabs,(__x))
#else /* lbas... */
__LOCAL __ATTR_CONST __ATTR_WUNUSED long (__LIBCCALL abs)(long __x) { return (labs)(__x); }
#endif /* !lbas... */
#ifdef __CRT_HAVE_div
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,struct __div_struct,__NOTHROW_NCX,div,(int __numer, int __denom),div,(__numer,__denom))
#elif defined(__CRT_HAVE_ldiv) && __SIZEOF_INT__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,struct __div_struct,__NOTHROW_NCX,div,(int __numer, int __denom),ldiv,(__numer,__denom))
#elif defined(__CRT_HAVE_lldiv) && __SIZEOF_INT__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,struct __div_struct,__NOTHROW_NCX,div,(int __numer, int __denom),lldiv,(__numer,__denom))
#elif defined(__CRT_HAVE_imaxdiv) && __SIZEOF_INT__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,struct __div_struct,__NOTHROW_NCX,div,(int __numer, int __denom),imaxdiv,(__numer,__denom))
#else /* div... */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED struct __div_struct (__LIBCCALL div)(int __numer, int __denom) { div_t __result; __result.quot = __numer / __denom; __result.rem = __numer % __denom; return __result; }
#endif /* !div... */
#ifdef __CRT_HAVE_ldiv
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,struct __ldiv_struct,__NOTHROW_NCX,div,(long __numer, long __denom),ldiv,(__numer,__denom))
#elif defined(__CRT_HAVE_div) && __SIZEOF_LONG__ == __SIZEOF_INT__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,struct __ldiv_struct,__NOTHROW_NCX,div,(long __numer, long __denom),div,(__numer,__denom))
#elif defined(__CRT_HAVE_lldiv) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,struct __ldiv_struct,__NOTHROW_NCX,div,(long __numer, long __denom),lldiv,(__numer,__denom))
#elif defined(__CRT_HAVE_imaxdiv) && __SIZEOF_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,struct __ldiv_struct,__NOTHROW_NCX,div,(long __numer, long __denom),imaxdiv,(__numer,__denom))
#else /* ldiv... */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED struct __ldiv_struct (__LIBCCALL div)(long __numer, long __denom) { return ldiv(__numer, __denom); }
#endif /* !ldiv... */
#ifdef __USE_ISOC99
#ifdef __CRT_HAVE_llabs
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,abs,(__LONGLONG __x),llabs,(__x))
#elif defined(__CRT_HAVE_abs) && __SIZEOF_LONG_LONG__ == __SIZEOF_INT__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,abs,(__LONGLONG __x),abs,(__x))
#elif defined(__CRT_HAVE_labs) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,abs,(__LONGLONG __x),labs,(__x))
#elif defined(__CRT_HAVE_imaxabs) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,abs,(__LONGLONG __x),imaxabs,(__x))
#else /* llabs... */
__LOCAL __ATTR_CONST __ATTR_WUNUSED __LONGLONG (__LIBCCALL abs)(__LONGLONG __x) { return (llabs)(__x); }
#endif /* !llabs... */
#ifdef __CRT_HAVE_lldiv
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,struct __lldiv_struct,__NOTHROW_NCX,div,(__LONGLONG __numer, __LONGLONG __denom),lldiv,(__numer,__denom))
#elif defined(__CRT_HAVE_div) && __SIZEOF_LONG_LONG__ == __SIZEOF_INT__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,struct __lldiv_struct,__NOTHROW_NCX,div,(__LONGLONG __numer, __LONGLONG __denom),div,(__numer,__denom))
#elif defined(__CRT_HAVE_div) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,struct __lldiv_struct,__NOTHROW_NCX,div,(__LONGLONG __numer, __LONGLONG __denom),ldiv,(__numer,__denom))
#elif defined(__CRT_HAVE_div) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,struct __lldiv_struct,__NOTHROW_NCX,div,(__LONGLONG __numer, __LONGLONG __denom),imaxdiv,(__numer,__denom))
#else /* lldiv... */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED struct __lldiv_struct (__LIBCCALL div)(__LONGLONG __numer, __LONGLONG __denom) { return lldiv(__numer, __denom); }
#endif /* !lldiv... */
#endif /* __USE_ISOC99 */
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STDLIB_H_PROTO */
#if __has_builtin(__builtin_abs) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_abs)
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL abs)(int __x) { return __builtin_abs(__x); }
#elif defined(__CRT_HAVE_abs)
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,abs,(int __x),(__x))
#elif defined(__CRT_HAVE_labs) && (__SIZEOF_INT__ == __SIZEOF_LONG__)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,abs,(int __x),labs,(__x))
#elif defined(__CRT_HAVE_llabs) && (__SIZEOF_INT__ == __SIZEOF_LONG_LONG__)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,abs,(int __x),llabs,(__x))
#elif defined(__CRT_HAVE_imaxabs) && (__SIZEOF_INT__ == __SIZEOF_INTMAX_T__)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,abs,(int __x),imaxabs,(__x))
#else /* LIBC: abs */
__NAMESPACE_STD_END
#include <local/stdlib/abs.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(abs, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL abs)(int __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(abs))(__x); })
#endif /* abs... */
#ifdef __CRT_HAVE_div
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,struct __div_struct,__NOTHROW_NCX,div,(int __numer, int __denom),(__numer,__denom))
#elif defined(__CRT_HAVE_ldiv) && (__SIZEOF_INT__ == __SIZEOF_LONG__)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,struct __div_struct,__NOTHROW_NCX,div,(int __numer, int __denom),ldiv,(__numer,__denom))
#elif defined(__CRT_HAVE_lldiv) && (__SIZEOF_INT__ == __SIZEOF_LONG_LONG__)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,struct __div_struct,__NOTHROW_NCX,div,(int __numer, int __denom),lldiv,(__numer,__denom))
#elif defined(__CRT_HAVE_imaxdiv) && (__SIZEOF_INT__ == __SIZEOF_INTMAX_T__)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,struct __div_struct,__NOTHROW_NCX,div,(int __numer, int __denom),imaxdiv,(__numer,__denom))
#else /* LIBC: div */
__NAMESPACE_STD_END
#include <local/stdlib/div.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(div, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED struct __div_struct __NOTHROW_NCX(__LIBCCALL div)(int __numer, int __denom) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(div))(__numer, __denom); })
#endif /* div... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STDLIB_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_MATH_H_PROTO) && !defined(__NO_FPU)
extern "C++" {
/* Also provide abs() for floating point types. */
#if __has_builtin(__builtin_fabsf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fabsf)
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST float __NOTHROW(__LIBCCALL abs)(float __x) { return __builtin_fabsf(__x); }
#else /* __builtin_fabsf && __LIBC_BIND_CRTBUILTINS && __CRT_HAVE_fabsf */
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST float __NOTHROW(__LIBCCALL abs)(float __x) { return __x < 0 ? -__x : __x; }
#endif /* !__builtin_fabsf || !__LIBC_BIND_CRTBUILTINS || !__CRT_HAVE_fabsf */
#if __has_builtin(__builtin_fabs) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fabs)
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST double __NOTHROW(__LIBCCALL abs)(double __x) { return __builtin_fabs(__x); }
#else /* __builtin_fabs && __LIBC_BIND_CRTBUILTINS && __CRT_HAVE_fabs */
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST double __NOTHROW(__LIBCCALL abs)(double __x) { return __x < 0 ? -__x : __x; }
#endif /* !__builtin_fabs || !__LIBC_BIND_CRTBUILTINS || !__CRT_HAVE_fabs */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if __has_builtin(__builtin_fabsl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fabsl)
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST long double __NOTHROW(__LIBCCALL abs)(long double __x) { return __builtin_fabsl(__x); }
#else /* __builtin_fabsl && __LIBC_BIND_CRTBUILTINS && __CRT_HAVE_fabsl */
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST long double __NOTHROW(__LIBCCALL abs)(long double __x) { return __x < 0 ? -__x : __x; }
#endif /* !__builtin_fabsl || !__LIBC_BIND_CRTBUILTINS || !__CRT_HAVE_fabsl */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#ifdef __COMPILER_HAVE_FLOAT128
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __float128 __NOTHROW(__LIBCCALL abs)(__float128 __x) { return __x < 0 ? -__x : __x; }
#endif /* __COMPILER_HAVE_FLOAT128 */
} /* extern "C++" */
#endif /* __cplusplus && __CORRECT_ISO_CPP_MATH_H_PROTO && !__NO_FPU */
#ifndef __std_getenv_defined
#define __std_getenv_defined 1
#ifdef __CRT_HAVE_getenv
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,getenv,(char const *__varname),(__varname))
#else /* LIBC: getenv */
#undef __std_getenv_defined
#endif /* getenv... */
#endif /* !__std_getenv_defined */
#ifdef __CRT_HAVE_mblen
__CDECLARE(,int,__NOTHROW_NCX,mblen,(char const *__str, size_t __maxlen),(__str,__maxlen))
#else /* LIBC: mblen */
__NAMESPACE_STD_END
#include <local/stdlib/mblen.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(mblen, __FORCELOCAL int __NOTHROW_NCX(__LIBCCALL mblen)(char const *__str, size_t __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mblen))(__str, __maxlen); })
#endif /* mblen... */
#ifdef __CRT_HAVE_mbtowc
__CDECLARE(,int,__NOTHROW_NCX,mbtowc,(wchar_t *__restrict __pwc, char const *__restrict __str, size_t __maxlen),(__pwc,__str,__maxlen))
#else /* LIBC: mbtowc */
__NAMESPACE_STD_END
#include <local/stdlib/mbtowc.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(mbtowc, __FORCELOCAL int __NOTHROW_NCX(__LIBCCALL mbtowc)(wchar_t *__restrict __pwc, char const *__restrict __str, size_t __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mbtowc))(__pwc, __str, __maxlen); })
#endif /* mbtowc... */
#ifdef __CRT_HAVE_wctomb
__CDECLARE(,int,__NOTHROW_NCX,wctomb,(char *__str, wchar_t __wc),(__str,__wc))
#else /* LIBC: wctomb */
__NAMESPACE_STD_END
#include <local/stdlib/wctomb.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(wctomb, __FORCELOCAL int __NOTHROW_NCX(__LIBCCALL wctomb)(char *__str, wchar_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wctomb))(__str, __wc); })
#endif /* wctomb... */
#ifdef __CRT_HAVE_mbstowcs
__CDECLARE(,size_t,__NOTHROW_NCX,mbstowcs,(wchar_t *__restrict __dst, char const *__restrict __src, size_t __dstlen),(__dst,__src,__dstlen))
#else /* LIBC: mbstowcs */
__NAMESPACE_STD_END
#include <local/stdlib/mbstowcs.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(mbstowcs, __FORCELOCAL size_t __NOTHROW_NCX(__LIBCCALL mbstowcs)(wchar_t *__restrict __dst, char const *__restrict __src, size_t __dstlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mbstowcs))(__dst, __src, __dstlen); })
#endif /* mbstowcs... */
#ifdef __CRT_HAVE_wcstombs
__CDECLARE(,size_t,__NOTHROW_NCX,wcstombs,(char *__restrict __dst, wchar_t const *__restrict __src, size_t __dstlen),(__dst,__src,__dstlen))
#else /* LIBC: wcstombs */
__NAMESPACE_STD_END
#include <local/stdlib/wcstombs.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstombs, __FORCELOCAL size_t __NOTHROW_NCX(__LIBCCALL wcstombs)(char *__restrict __dst, wchar_t const *__restrict __src, size_t __dstlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstombs))(__dst, __src, __dstlen); })
#endif /* wcstombs... */
#ifndef __std_system_defined
#define __std_system_defined 1
#ifdef __system_defined
__NAMESPACE_GLB_USING(system)
#elif defined(__CRT_HAVE_system)
__CDECLARE(,int,__NOTHROW_RPC,system,(char const *__restrict __command),(__command))
#else /* LIBC: system */
#undef __std_system_defined
#endif /* system... */
#endif /* !__std_system_defined */
#ifndef __std_abort_defined
#define __std_abort_defined 1
#ifdef __abort_defined
__NAMESPACE_GLB_USING(abort)
#elif __has_builtin(__builtin_abort) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_abort)
__FORCELOCAL __ATTR_NORETURN void (__LIBCCALL abort)(void) { __builtin_abort(); }
#elif defined(__CRT_HAVE_abort)
__CDECLARE_VOID(__ATTR_NORETURN,,abort,(void),())
#elif defined(__CRT_HAVE__ZSt9terminatev)
__CREDIRECT_VOID(__ATTR_NORETURN,,abort,(void),_ZSt9terminatev,())
#else /* LIBC: abort */
#undef __std_abort_defined
#endif /* abort... */
#endif /* !__std_abort_defined */
#ifndef __std_exit_defined
#define __std_exit_defined 1
#ifdef __exit_defined
__NAMESPACE_GLB_USING(exit)
#elif __has_builtin(__builtin_exit) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_exit)
__FORCELOCAL __ATTR_NORETURN void (__LIBCCALL exit)(int __status) __THROWS(...) { __builtin_exit(__status); }
#elif defined(__CRT_HAVE_exit)
__CDECLARE_VOID(__ATTR_NORETURN,,exit,(int __status),(__status)) __THROWS(...)
#elif defined(__CRT_HAVE_quick_exit)
__CREDIRECT_VOID(__ATTR_NORETURN,,exit,(int __status),quick_exit,(__status)) __THROWS(...)
#elif defined(__CRT_HAVE__exit)
__CREDIRECT_VOID(__ATTR_NORETURN,,exit,(int __status),_exit,(__status)) __THROWS(...)
#elif defined(__CRT_HAVE__Exit)
__CREDIRECT_VOID(__ATTR_NORETURN,,exit,(int __status),_Exit,(__status)) __THROWS(...)
#else /* LIBC: exit */
#undef __std_exit_defined
#endif /* exit... */
#endif /* !__std_exit_defined */
#ifndef __std_atexit_defined
#define __std_atexit_defined 1
#ifdef __CRT_HAVE_atexit
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,atexit,(__atexit_func_t __func),(__func))
#elif defined(__CRT_HAVE_at_quick_exit)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,atexit,(__atexit_func_t __func),at_quick_exit,(__func))
#else /* LIBC: atexit */
#undef __std_atexit_defined
#endif /* atexit... */
#endif /* !__std_atexit_defined */
#if defined(__USE_ISOC11) || defined(__USE_ISOCXX11)
#ifndef __std_quick_exit_defined
#define __std_quick_exit_defined 1
#ifdef __CRT_HAVE_quick_exit
__CDECLARE_VOID(__ATTR_NORETURN,,quick_exit,(int __status),(__status)) __THROWS(...)
#elif defined(__CRT_HAVE_exit)
__CREDIRECT_VOID(__ATTR_NORETURN,,quick_exit,(int __status),exit,(__status)) __THROWS(...)
#elif defined(__CRT_HAVE__exit)
__CREDIRECT_VOID(__ATTR_NORETURN,,quick_exit,(int __status),_exit,(__status)) __THROWS(...)
#elif defined(__CRT_HAVE__Exit)
__CREDIRECT_VOID(__ATTR_NORETURN,,quick_exit,(int __status),_Exit,(__status)) __THROWS(...)
#else /* LIBC: quick_exit */
#undef __std_quick_exit_defined
#endif /* quick_exit... */
#endif /* !__std_quick_exit_defined */
#ifndef __std_at_quick_exit_defined
#define __std_at_quick_exit_defined 1
#ifdef __CRT_HAVE_at_quick_exit
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,at_quick_exit,(__atexit_func_t __func),(__func))
#elif defined(__CRT_HAVE_atexit)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,at_quick_exit,(__atexit_func_t __func),atexit,(__func))
#else /* LIBC: at_quick_exit */
#undef __std_at_quick_exit_defined
#endif /* at_quick_exit... */
#endif /* !__std_at_quick_exit_defined */
#endif /* __USE_ISOC11 || __USE_ISOCXX11 */
#ifdef __USE_ISOC99
#ifndef __std__Exit_defined
#define __std__Exit_defined 1
#if __has_builtin(__builtin__Exit) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE__Exit)
__FORCELOCAL __ATTR_NORETURN void (__LIBCCALL _Exit)(int __status) { __builtin__Exit(__status); }
#elif defined(__CRT_HAVE__Exit)
__CDECLARE_VOID(__ATTR_NORETURN,,_Exit,(int __status),(__status))
#elif defined(__CRT_HAVE__exit)
__CREDIRECT_VOID(__ATTR_NORETURN,,_Exit,(int __status),_exit,(__status))
#elif defined(__CRT_HAVE_quick_exit)
__CREDIRECT_VOID(__ATTR_NORETURN,,_Exit,(int __status),quick_exit,(__status))
#elif defined(__CRT_HAVE_exit)
__CREDIRECT_VOID(__ATTR_NORETURN,,_Exit,(int __status),exit,(__status))
#else /* LIBC: _Exit */
#undef __std__Exit_defined
#endif /* _Exit... */
#endif /* !__std__Exit_defined */
#endif /* __USE_ISOC99 */
#ifndef __std_malloc_defined
#define __std_malloc_defined 1
#ifdef __malloc_defined
__NAMESPACE_GLB_USING(malloc)
#elif __has_builtin(__builtin_malloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_malloc)
__FORCELOCAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)) void *__NOTHROW_NCX(__LIBCCALL malloc)(size_t __n_bytes) { return __builtin_malloc(__n_bytes); }
#elif defined(__CRT_HAVE_malloc)
__CDECLARE(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,malloc,(size_t __n_bytes),(__n_bytes))
#elif defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_posix_memalign) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc)
__NAMESPACE_STD_END
#include <local/stdlib/malloc.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(malloc, __FORCELOCAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)) void *__NOTHROW_NCX(__LIBCCALL malloc)(size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(malloc))(__n_bytes); })
#else /* CUSTOM: malloc */
#undef __std_malloc_defined
#endif /* malloc... */
#endif /* !__std_malloc_defined */
#ifndef __std_calloc_defined
#define __std_calloc_defined 1
#ifdef __calloc_defined
__NAMESPACE_GLB_USING(calloc)
#elif __has_builtin(__builtin_calloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_calloc)
__FORCELOCAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1, 2)) void *__NOTHROW_NCX(__LIBCCALL calloc)(size_t __count, size_t __n_bytes) { return __builtin_calloc(__count, __n_bytes); }
#elif defined(__CRT_HAVE_calloc)
__CDECLARE(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1, 2)),void *,__NOTHROW_NCX,calloc,(size_t __count, size_t __n_bytes),(__count,__n_bytes))
#elif defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_posix_memalign) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_malloc)
__NAMESPACE_STD_END
#include <local/stdlib/calloc.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(calloc, __FORCELOCAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1, 2)) void *__NOTHROW_NCX(__LIBCCALL calloc)(size_t __count, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(calloc))(__count, __n_bytes); })
#else /* CUSTOM: calloc */
#undef __std_calloc_defined
#endif /* calloc... */
#endif /* !__std_calloc_defined */
#ifndef __std_realloc_defined
#define __std_realloc_defined 1
#ifdef __realloc_defined
__NAMESPACE_GLB_USING(realloc)
#elif __has_builtin(__builtin_realloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_realloc)
__FORCELOCAL __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) void *__NOTHROW_NCX(__LIBCCALL realloc)(void *__mallptr, size_t __n_bytes) { return __builtin_realloc(__mallptr, __n_bytes); }
#elif defined(__CRT_HAVE_realloc)
__CDECLARE(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,realloc,(void *__mallptr, size_t __n_bytes),(__mallptr,__n_bytes))
#else /* LIBC: realloc */
#undef __std_realloc_defined
#endif /* realloc... */
#endif /* !__std_realloc_defined */
#ifndef __std_free_defined
#define __std_free_defined 1
#ifdef __free_defined
__NAMESPACE_GLB_USING(free)
#elif __has_builtin(__builtin_free) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_free)
__FORCELOCAL void __NOTHROW_NCX(__LIBCCALL free)(void *__mallptr) { return __builtin_free(__mallptr); }
#elif defined(__CRT_HAVE_free)
__CDECLARE_VOID(,__NOTHROW_NCX,free,(void *__mallptr),(__mallptr))
#elif defined(__CRT_HAVE_cfree)
__CREDIRECT_VOID(,__NOTHROW_NCX,free,(void *__mallptr),cfree,(__mallptr))
#else /* LIBC: free */
#undef __std_free_defined
#endif /* free... */
#endif /* !__std_free_defined */
#ifdef __CRT_HAVE_srand
__CDECLARE_VOID(,__NOTHROW,srand,(long __seed),(__seed))
#elif defined(__CRT_HAVE_srandom) && (__SIZEOF_INT__ == __SIZEOF_LONG__)
__CREDIRECT_VOID(,__NOTHROW,srand,(long __seed),srandom,(__seed))
#else /* LIBC: srand */
__NAMESPACE_STD_END
#include <local/stdlib/srand.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(srand, __FORCELOCAL void __NOTHROW(__LIBCCALL srand)(long __seed) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(srand))(__seed); })
#endif /* srand... */
#ifdef __CRT_HAVE_rand
__CDECLARE(,int,__NOTHROW,rand,(void),())
#elif defined(__CRT_HAVE_random) && (__SIZEOF_INT__ == __SIZEOF_LONG__)
__CREDIRECT(,int,__NOTHROW,rand,(void),random,())
#else /* LIBC: rand */
__NAMESPACE_STD_END
#include <local/stdlib/rand.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(rand, __FORCELOCAL int __NOTHROW(__LIBCCALL rand)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rand))(); })
#endif /* rand... */
#ifdef __CRT_HAVE_atoi
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,atoi,(char const *__restrict __nptr),(__nptr))
#elif defined(__CRT_HAVE_atol) && (__SIZEOF_INT__ == __SIZEOF_LONG__)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,atoi,(char const *__restrict __nptr),atol,(__nptr))
#elif defined(__CRT_HAVE_atoll) && (__SIZEOF_INT__ == __SIZEOF_LONG_LONG__)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,atoi,(char const *__restrict __nptr),atoll,(__nptr))
#else /* LIBC: atoi */
__NAMESPACE_STD_END
#include <local/stdlib/atoi.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(atoi, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL atoi)(char const *__restrict __nptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(atoi))(__nptr); })
#endif /* atoi... */
#ifdef __CRT_HAVE_atol
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),long,__NOTHROW_NCX,atol,(char const *__restrict __nptr),(__nptr))
#elif defined(__CRT_HAVE_atoi) && (__SIZEOF_LONG__ == __SIZEOF_INT__)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),long,__NOTHROW_NCX,atol,(char const *__restrict __nptr),atoi,(__nptr))
#elif defined(__CRT_HAVE_atoll) && (__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),long,__NOTHROW_NCX,atol,(char const *__restrict __nptr),atoll,(__nptr))
#else /* LIBC: atol */
__NAMESPACE_STD_END
#include <local/stdlib/atol.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(atol, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) long __NOTHROW_NCX(__LIBCCALL atol)(char const *__restrict __nptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(atol))(__nptr); })
#endif /* atol... */
#ifdef __CRT_HAVE_atoll
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,atoll,(char const *__restrict __nptr),(__nptr))
#elif defined(__CRT_HAVE_atoi) && (__SIZEOF_LONG_LONG__ == __SIZEOF_INT__)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,atoll,(char const *__restrict __nptr),atoi,(__nptr))
#elif defined(__CRT_HAVE_atol) && (__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,atoll,(char const *__restrict __nptr),atol,(__nptr))
#else /* LIBC: atoll */
__NAMESPACE_STD_END
#include <local/stdlib/atoll.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(atoll, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __LONGLONG __NOTHROW_NCX(__LIBCCALL atoll)(char const *__restrict __nptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(atoll))(__nptr); })
#endif /* atoll... */
#ifdef __CRT_HAVE_strtoul
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,strtoul,(char const *__restrict __nptr, char **__endptr, int __base),(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoull) && (__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,strtoul,(char const *__restrict __nptr, char **__endptr, int __base),strtoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtouq) && (__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,strtoul,(char const *__restrict __nptr, char **__endptr, int __base),strtouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtou32) && (__SIZEOF_LONG__ == 4)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,strtoul,(char const *__restrict __nptr, char **__endptr, int __base),strtou32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtou64) && (__SIZEOF_LONG__ == 8)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,strtoul,(char const *__restrict __nptr, char **__endptr, int __base),strtou64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__strtoui64) && (__SIZEOF_LONG__ == 8)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,strtoul,(char const *__restrict __nptr, char **__endptr, int __base),_strtoui64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoumax) && (__SIZEOF_LONG__ == __SIZEOF_INTMAX_T__)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,strtoul,(char const *__restrict __nptr, char **__endptr, int __base),strtoumax,(__nptr,__endptr,__base))
#else /* LIBC: strtoul */
__NAMESPACE_STD_END
#include <local/stdlib/strtoul.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(strtoul, __FORCELOCAL __ATTR_LEAF __ATTR_NONNULL((1)) unsigned long __NOTHROW_NCX(__LIBCCALL strtoul)(char const *__restrict __nptr, char **__endptr, int __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtoul))(__nptr, __endptr, __base); })
#endif /* strtoul... */
#ifdef __CRT_HAVE_strtol
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),long,__NOTHROW_NCX,strtol,(char const *__restrict __nptr, char **__endptr, int __base),(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoll) && (__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),long,__NOTHROW_NCX,strtol,(char const *__restrict __nptr, char **__endptr, int __base),strtoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoq) && (__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),long,__NOTHROW_NCX,strtol,(char const *__restrict __nptr, char **__endptr, int __base),strtoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strto32) && (__SIZEOF_LONG__ == 4)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),long,__NOTHROW_NCX,strtol,(char const *__restrict __nptr, char **__endptr, int __base),strto32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strto64) && (__SIZEOF_LONG__ == 8)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),long,__NOTHROW_NCX,strtol,(char const *__restrict __nptr, char **__endptr, int __base),strto64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__strtoi64) && (__SIZEOF_LONG__ == 8)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),long,__NOTHROW_NCX,strtol,(char const *__restrict __nptr, char **__endptr, int __base),_strtoi64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoimax) && (__SIZEOF_LONG__ == __SIZEOF_INTMAX_T__)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),long,__NOTHROW_NCX,strtol,(char const *__restrict __nptr, char **__endptr, int __base),strtoimax,(__nptr,__endptr,__base))
#else /* LIBC: strtol */
__NAMESPACE_STD_END
#include <local/stdlib/strtol.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(strtol, __FORCELOCAL __ATTR_LEAF __ATTR_NONNULL((1)) long __NOTHROW_NCX(__LIBCCALL strtol)(char const *__restrict __nptr, char **__endptr, int __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtol))(__nptr, __endptr, __base); })
#endif /* strtol... */
#ifdef __ULONGLONG
#ifdef __USE_ISOC99
#ifndef __std_strtoull_defined
#define __std_strtoull_defined 1
#ifdef __strtoull_defined
__NAMESPACE_GLB_USING(strtoull)
#elif defined(__CRT_HAVE_strtoull)
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,strtoull,(char const *__restrict __nptr, char **__endptr, int __base),(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtouq)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,strtoull,(char const *__restrict __nptr, char **__endptr, int __base),strtouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtou64) && (__SIZEOF_LONG_LONG__ == 8)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,strtoull,(char const *__restrict __nptr, char **__endptr, int __base),strtou64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__strtoui64) && (__SIZEOF_LONG_LONG__ == 8)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,strtoull,(char const *__restrict __nptr, char **__endptr, int __base),_strtoui64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoumax) && (__SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,strtoull,(char const *__restrict __nptr, char **__endptr, int __base),strtoumax,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtou32) && (__SIZEOF_LONG_LONG__ == 4)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,strtoull,(char const *__restrict __nptr, char **__endptr, int __base),strtou32,(__nptr,__endptr,__base))
#else /* LIBC: strtoull */
__NAMESPACE_STD_END
#include <local/stdlib/strtoull.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(strtoull, __FORCELOCAL __ATTR_LEAF __ATTR_NONNULL((1)) __ULONGLONG __NOTHROW_NCX(__LIBCCALL strtoull)(char const *__restrict __nptr, char **__endptr, int __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtoull))(__nptr, __endptr, __base); })
#endif /* strtoull... */
#endif /* !__std_strtoull_defined */
#ifndef __std_strtoll_defined
#define __std_strtoll_defined 1
#ifdef __strtoll_defined
__NAMESPACE_GLB_USING(strtoll)
#elif defined(__CRT_HAVE_strtoll)
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,strtoll,(char const *__restrict __nptr, char **__endptr, int __base),(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoq)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,strtoll,(char const *__restrict __nptr, char **__endptr, int __base),strtoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strto64) && (__SIZEOF_LONG_LONG__ == 8)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,strtoll,(char const *__restrict __nptr, char **__endptr, int __base),strto64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__strtoi64) && (__SIZEOF_LONG_LONG__ == 8)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,strtoll,(char const *__restrict __nptr, char **__endptr, int __base),_strtoi64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoimax) && (__SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,strtoll,(char const *__restrict __nptr, char **__endptr, int __base),strtoimax,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strto32) && (__SIZEOF_LONG_LONG__ == 4)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,strtoll,(char const *__restrict __nptr, char **__endptr, int __base),strto32,(__nptr,__endptr,__base))
#else /* LIBC: strtoll */
__NAMESPACE_STD_END
#include <local/stdlib/strtoll.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(strtoll, __FORCELOCAL __ATTR_LEAF __ATTR_NONNULL((1)) __LONGLONG __NOTHROW_NCX(__LIBCCALL strtoll)(char const *__restrict __nptr, char **__endptr, int __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtoll))(__nptr, __endptr, __base); })
#endif /* strtoll... */
#endif /* !__std_strtoll_defined */
#endif /* __USE_ISOC99 */
#endif /* __ULONGLONG */
#ifndef __NO_FPU
#ifdef __CRT_HAVE_atof
__CDECLARE(__ATTR_LEAF __ATTR_WUNUSED __ATTR_NONNULL((1)),double,__NOTHROW_NCX,atof,(char const *__restrict __nptr),(__nptr))
#else /* LIBC: atof */
__NAMESPACE_STD_END
#include <local/stdlib/atof.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(atof, __FORCELOCAL __ATTR_LEAF __ATTR_WUNUSED __ATTR_NONNULL((1)) double __NOTHROW_NCX(__LIBCCALL atof)(char const *__restrict __nptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(atof))(__nptr); })
#endif /* atof... */
#ifdef __CRT_HAVE_strtod
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),double,__NOTHROW_NCX,strtod,(char const *__restrict __nptr, char **__endptr),(__nptr,__endptr))
#elif defined(__CRT_HAVE_strtold) && (__SIZEOF_LONG_DOUBLE__ == __SIZEOF_DOUBLE__)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),double,__NOTHROW_NCX,strtod,(char const *__restrict __nptr, char **__endptr),strtold,(__nptr,__endptr))
#else /* LIBC: strtod */
__NAMESPACE_STD_END
#include <local/stdlib/strtod.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(strtod, __FORCELOCAL __ATTR_LEAF __ATTR_NONNULL((1)) double __NOTHROW_NCX(__LIBCCALL strtod)(char const *__restrict __nptr, char **__endptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtod))(__nptr, __endptr); })
#endif /* strtod... */
#ifdef __USE_ISOC99
#ifndef __std_strtof_defined
#define __std_strtof_defined 1
#ifdef __strtof_defined
__NAMESPACE_GLB_USING(strtof)
#elif defined(__CRT_HAVE_strtof)
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),float,__NOTHROW_NCX,strtof,(char const *__restrict __nptr, char **__endptr),(__nptr,__endptr))
#else /* LIBC: strtof */
__NAMESPACE_STD_END
#include <local/stdlib/strtof.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(strtof, __FORCELOCAL __ATTR_LEAF __ATTR_NONNULL((1)) float __NOTHROW_NCX(__LIBCCALL strtof)(char const *__restrict __nptr, char **__endptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtof))(__nptr, __endptr); })
#endif /* strtof... */
#endif /* !__std_strtof_defined */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#ifndef __std_strtold_defined
#define __std_strtold_defined 1
#ifdef __strtold_defined
__NAMESPACE_GLB_USING(strtold)
#elif defined(__CRT_HAVE_strtold)
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),long double,__NOTHROW_NCX,strtold,(char const *__restrict __nptr, char **__endptr),(__nptr,__endptr))
#elif defined(__CRT_HAVE_strtod) && (__SIZEOF_LONG_DOUBLE__ == __SIZEOF_DOUBLE__)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),long double,__NOTHROW_NCX,strtold,(char const *__restrict __nptr, char **__endptr),strtod,(__nptr,__endptr))
#else /* LIBC: strtold */
__NAMESPACE_STD_END
#include <local/stdlib/strtold.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(strtold, __FORCELOCAL __ATTR_LEAF __ATTR_NONNULL((1)) long double __NOTHROW_NCX(__LIBCCALL strtold)(char const *__restrict __nptr, char **__endptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtold))(__nptr, __endptr); })
#endif /* strtold... */
#endif /* !__std_strtold_defined */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_ISOC99 */
#endif /* !__NO_FPU */
#ifdef __USE_ISOCXX17
#ifndef __std_aligned_alloc_defined
#define __std_aligned_alloc_defined 1
#ifdef __aligned_alloc_defined
__NAMESPACE_GLB_USING(aligned_alloc)
#elif __has_builtin(__builtin_aligned_alloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_aligned_alloc)
__FORCELOCAL __ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) __ATTR_ALLOC_ALIGN(1) void *__NOTHROW_NCX(__LIBCCALL aligned_alloc)(__SIZE_TYPE__ __alignment, __SIZE_TYPE__ __n_bytes) { return __builtin_aligned_alloc(__alignment, __n_bytes); }
#elif defined(__CRT_HAVE_aligned_alloc)
__CDECLARE(__ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) __ATTR_ALLOC_ALIGN(1),void *,__NOTHROW_NCX,aligned_alloc,(__SIZE_TYPE__ __alignment, __SIZE_TYPE__ __n_bytes),(__alignment,__n_bytes))
#elif defined(__CRT_HAVE_memalign)
__CREDIRECT(__ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) __ATTR_ALLOC_ALIGN(1),void *,__NOTHROW_NCX,aligned_alloc,(__SIZE_TYPE__ __alignment, __SIZE_TYPE__ __n_bytes),memalign,(__alignment,__n_bytes))
#elif defined(__CRT_HAVE_posix_memalign)
__NAMESPACE_STD_END
#include <local/malloc/memalign.h>
__NAMESPACE_STD_BEGIN
__FORCELOCAL __ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) __ATTR_ALLOC_ALIGN(1) void *__NOTHROW_NCX(__LIBCCALL aligned_alloc)(__SIZE_TYPE__ __alignment, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memalign))(__alignment, __n_bytes); }
#else /* CUSTOM: memalign */
#undef __std_aligned_alloc_defined
#endif /* aligned_alloc... */
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
#if !defined(__getenv_defined) && defined(__std_getenv_defined)
#define __getenv_defined 1
__NAMESPACE_STD_USING(getenv)
#endif /* !__getenv_defined && !__std_getenv_defined */
__NAMESPACE_STD_USING(mblen)
__NAMESPACE_STD_USING(mbtowc)
__NAMESPACE_STD_USING(wctomb)
__NAMESPACE_STD_USING(mbstowcs)
__NAMESPACE_STD_USING(wcstombs)
#if !defined(__system_defined) && defined(__std_system_defined)
#define __system_defined 1
__NAMESPACE_STD_USING(system)
#endif /* !__system_defined && !__std_system_defined */
#if !defined(__abort_defined) && defined(__std_abort_defined)
#define __abort_defined 1
__NAMESPACE_STD_USING(abort)
#endif /* !__abort_defined && !__std_abort_defined */
#if !defined(__exit_defined) && defined(__std_exit_defined)
#define __exit_defined 1
__NAMESPACE_STD_USING(exit)
#endif /* !__exit_defined && !__std_exit_defined */
#if !defined(__atexit_defined) && defined(__std_atexit_defined)
#define __atexit_defined 1
__NAMESPACE_STD_USING(atexit)
#endif /* !__atexit_defined && !__std_atexit_defined */
#endif /* !__CXX_SYSTEM_HEADER */
#if defined(__USE_ISOC11) || defined(__USE_ISOCXX11)
#ifndef __CXX_SYSTEM_HEADER
#if !defined(__quick_exit_defined) && defined(__std_quick_exit_defined)
#define __quick_exit_defined 1
__NAMESPACE_STD_USING(quick_exit)
#endif /* !__quick_exit_defined && !__std_quick_exit_defined */
#if !defined(__at_quick_exit_defined) && defined(__std_at_quick_exit_defined)
#define __at_quick_exit_defined 1
__NAMESPACE_STD_USING(at_quick_exit)
#endif /* !__at_quick_exit_defined && !__std_at_quick_exit_defined */
#endif /* !__CXX_SYSTEM_HEADER */
#endif /* __USE_ISOC11 || __USE_ISOCXX11 */
#ifdef __USE_ISOC99
#ifndef __CXX_SYSTEM_HEADER
#if !defined(___Exit_defined) && defined(__std__Exit_defined)
#define ___Exit_defined 1
__NAMESPACE_STD_USING(_Exit)
#endif /* !___Exit_defined && !__std__Exit_defined */
#endif /* !__CXX_SYSTEM_HEADER */
#endif /* __USE_ISOC99 */
#ifndef __CXX_SYSTEM_HEADER
#if !defined(__malloc_defined) && defined(__std_malloc_defined)
#define __malloc_defined 1
__NAMESPACE_STD_USING(malloc)
#endif /* !__malloc_defined && !__std_malloc_defined */
#if !defined(__calloc_defined) && defined(__std_calloc_defined)
#define __calloc_defined 1
__NAMESPACE_STD_USING(calloc)
#endif /* !__calloc_defined && !__std_calloc_defined */
#if !defined(__realloc_defined) && defined(__std_realloc_defined)
#define __realloc_defined 1
__NAMESPACE_STD_USING(realloc)
#endif /* !__realloc_defined && !__std_realloc_defined */
#if !defined(__free_defined) && defined(__std_free_defined)
#define __free_defined 1
__NAMESPACE_STD_USING(free)
#endif /* !__free_defined && !__std_free_defined */
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
#endif /* !__strtoull_defined && !__std_strtoull_defined */
#if !defined(__strtoll_defined) && defined(__std_strtoll_defined)
#define __strtoll_defined 1
__NAMESPACE_STD_USING(strtoll)
#endif /* !__strtoll_defined && !__std_strtoll_defined */
#endif /* !__CXX_SYSTEM_HEADER */
#ifndef __NO_FPU
#ifndef __CXX_SYSTEM_HEADER
__NAMESPACE_STD_USING(atof)
__NAMESPACE_STD_USING(strtod)
#if !defined(__strtof_defined) && defined(__std_strtof_defined)
#define __strtof_defined 1
__NAMESPACE_STD_USING(strtof)
#endif /* !__strtof_defined && !__std_strtof_defined */
#if !defined(__strtold_defined) && defined(__std_strtold_defined)
#define __strtold_defined 1
__NAMESPACE_STD_USING(strtold)
#endif /* !__strtold_defined && !__std_strtold_defined */
#endif /* !__CXX_SYSTEM_HEADER */
#endif /* !__NO_FPU */

#ifdef __ULONGLONG
#ifdef __USE_MISC
#ifndef __strtoq_defined
#define __strtoq_defined 1
#ifdef __CRT_HAVE_strtoq
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,strtoq,(char const *__restrict __nptr, char **__endptr, int __base),(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoll)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,strtoq,(char const *__restrict __nptr, char **__endptr, int __base),strtoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strto64) && (__SIZEOF_LONG_LONG__ == 8)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,strtoq,(char const *__restrict __nptr, char **__endptr, int __base),strto64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__strtoi64) && (__SIZEOF_LONG_LONG__ == 8)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,strtoq,(char const *__restrict __nptr, char **__endptr, int __base),_strtoi64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoimax) && (__SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,strtoq,(char const *__restrict __nptr, char **__endptr, int __base),strtoimax,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strto32) && (__SIZEOF_LONG_LONG__ == 4)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,strtoq,(char const *__restrict __nptr, char **__endptr, int __base),strto32,(__nptr,__endptr,__base))
#else /* LIBC: strtoll */
#include <local/stdlib/strtoll.h>
__FORCELOCAL __ATTR_LEAF __ATTR_NONNULL((1)) __LONGLONG __NOTHROW_NCX(__LIBCCALL strtoq)(char const *__restrict __nptr, char **__endptr, int __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtoll))(__nptr, __endptr, __base); }
#endif /* strtoq... */
#endif /* !__strtoq_defined */
#ifndef __strtouq_defined
#define __strtouq_defined 1
#ifdef __CRT_HAVE_strtouq
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,strtouq,(char const *__restrict __nptr, char **__endptr, int __base),(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoull)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,strtouq,(char const *__restrict __nptr, char **__endptr, int __base),strtoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtou64) && (__SIZEOF_LONG_LONG__ == 8)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,strtouq,(char const *__restrict __nptr, char **__endptr, int __base),strtou64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__strtoui64) && (__SIZEOF_LONG_LONG__ == 8)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,strtouq,(char const *__restrict __nptr, char **__endptr, int __base),_strtoui64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoumax) && (__SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,strtouq,(char const *__restrict __nptr, char **__endptr, int __base),strtoumax,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtou32) && (__SIZEOF_LONG_LONG__ == 4)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,strtouq,(char const *__restrict __nptr, char **__endptr, int __base),strtou32,(__nptr,__endptr,__base))
#else /* LIBC: strtoull */
#include <local/stdlib/strtoull.h>
__FORCELOCAL __ATTR_LEAF __ATTR_NONNULL((1)) __ULONGLONG __NOTHROW_NCX(__LIBCCALL strtouq)(char const *__restrict __nptr, char **__endptr, int __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtoull))(__nptr, __endptr, __base); }
#endif /* strtouq... */
#endif /* !__strtouq_defined */
#endif /* __USE_MISC */
#endif /* __ULONGLONG */
#ifdef __USE_KOS
#ifdef __CRT_HAVE_strtou32
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,strtou32,(char const *__restrict __nptr, char **__endptr, int __base),(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoul) && (__SIZEOF_LONG__ == 4)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,strtou32,(char const *__restrict __nptr, char **__endptr, int __base),strtoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoull) && (__SIZEOF_LONG_LONG__ == 4)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,strtou32,(char const *__restrict __nptr, char **__endptr, int __base),strtoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtouq) && (__SIZEOF_LONG_LONG__ == 4)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,strtou32,(char const *__restrict __nptr, char **__endptr, int __base),strtouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoumax) && (__SIZEOF_INTMAX_T__ == 4)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,strtou32,(char const *__restrict __nptr, char **__endptr, int __base),strtoumax,(__nptr,__endptr,__base))
#else /* LIBC: strtou32 */
#include <local/stdlib/strtou32.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strtou32, __FORCELOCAL __ATTR_LEAF __ATTR_NONNULL((1)) __UINT32_TYPE__ __NOTHROW_NCX(__LIBCCALL strtou32)(char const *__restrict __nptr, char **__endptr, int __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtou32))(__nptr, __endptr, __base); })
#endif /* strtou32... */
#ifdef __CRT_HAVE_strto32
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,strto32,(char const *__restrict __nptr, char **__endptr, int __base),(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtol) && (__SIZEOF_LONG__ == 4)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,strto32,(char const *__restrict __nptr, char **__endptr, int __base),strtol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoll) && (__SIZEOF_LONG_LONG__ == 4)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,strto32,(char const *__restrict __nptr, char **__endptr, int __base),strtoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoq) && (__SIZEOF_LONG_LONG__ == 4)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,strto32,(char const *__restrict __nptr, char **__endptr, int __base),strtoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoimax) && (__SIZEOF_INTMAX_T__ == 4)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,strto32,(char const *__restrict __nptr, char **__endptr, int __base),strtoimax,(__nptr,__endptr,__base))
#else /* LIBC: strto32 */
#include <local/stdlib/strto32.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strto32, __FORCELOCAL __ATTR_LEAF __ATTR_NONNULL((1)) __INT32_TYPE__ __NOTHROW_NCX(__LIBCCALL strto32)(char const *__restrict __nptr, char **__endptr, int __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strto32))(__nptr, __endptr, __base); })
#endif /* strto32... */
#ifdef __UINT64_TYPE__
#ifdef __CRT_HAVE_strtou64
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,strtou64,(char const *__restrict __nptr, char **__endptr, int __base),(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__strtoui64)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,strtou64,(char const *__restrict __nptr, char **__endptr, int __base),_strtoui64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoul) && (__SIZEOF_LONG__ == 8)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,strtou64,(char const *__restrict __nptr, char **__endptr, int __base),strtoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoull) && (__SIZEOF_LONG_LONG__ == 8)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,strtou64,(char const *__restrict __nptr, char **__endptr, int __base),strtoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtouq) && (__SIZEOF_LONG_LONG__ == 8)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,strtou64,(char const *__restrict __nptr, char **__endptr, int __base),strtouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoumax) && (__SIZEOF_INTMAX_T__ == 8)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,strtou64,(char const *__restrict __nptr, char **__endptr, int __base),strtoumax,(__nptr,__endptr,__base))
#else /* LIBC: strtou64 */
#include <local/stdlib/strtou64.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strtou64, __FORCELOCAL __ATTR_LEAF __ATTR_NONNULL((1)) __UINT64_TYPE__ __NOTHROW_NCX(__LIBCCALL strtou64)(char const *__restrict __nptr, char **__endptr, int __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtou64))(__nptr, __endptr, __base); })
#endif /* strtou64... */
#ifdef __CRT_HAVE_strto64
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,strto64,(char const *__restrict __nptr, char **__endptr, int __base),(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__strtoi64)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,strto64,(char const *__restrict __nptr, char **__endptr, int __base),_strtoi64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtol) && (__SIZEOF_LONG__ == 8)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,strto64,(char const *__restrict __nptr, char **__endptr, int __base),strtol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoll) && (__SIZEOF_LONG_LONG__ == 8)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,strto64,(char const *__restrict __nptr, char **__endptr, int __base),strtoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoq) && (__SIZEOF_LONG_LONG__ == 8)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,strto64,(char const *__restrict __nptr, char **__endptr, int __base),strtoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoimax) && (__SIZEOF_INTMAX_T__ == 8)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,strto64,(char const *__restrict __nptr, char **__endptr, int __base),strtoimax,(__nptr,__endptr,__base))
#else /* LIBC: strto64 */
#include <local/stdlib/strto64.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strto64, __FORCELOCAL __ATTR_LEAF __ATTR_NONNULL((1)) __INT64_TYPE__ __NOTHROW_NCX(__LIBCCALL strto64)(char const *__restrict __nptr, char **__endptr, int __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strto64))(__nptr, __endptr, __base); })
#endif /* strto64... */
#endif /* __UINT64_TYPE__ */
#endif /* __USE_KOS */


#if defined(__USE_MISC) || defined(__USE_DOS) || \
   (defined(__USE_XOPEN_EXTENDED) && !defined(__USE_XOPEN2K8))
#ifndef __NO_FPU
#ifdef __CRT_HAVE_gcvt
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((3)),char *,__NOTHROW_NCX,gcvt,(double __val, int __ndigit, char *__buf),(__val,__ndigit,__buf))
#elif defined(__CRT_HAVE__gcvt)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((3)),char *,__NOTHROW_NCX,gcvt,(double __val, int __ndigit, char *__buf),_gcvt,(__val,__ndigit,__buf))
#else /* LIBC: gcvt */
#include <local/stdlib/gcvt.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(gcvt, __FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((3)) char *__NOTHROW_NCX(__LIBCCALL gcvt)(double __val, int __ndigit, char *__buf) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(gcvt))(__val, __ndigit, __buf); })
#endif /* gcvt... */
#endif /* !__NO_FPU */
#endif /* ... */

#ifdef __USE_MISC
#ifndef __NO_FPU
#ifdef __CRT_HAVE_ecvt_r
__CDECLARE(__ATTR_NONNULL((3, 4, 5)),int,__NOTHROW_NCX,ecvt_r,(double __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign, char *__restrict __buf, __SIZE_TYPE__ __len),(__val,__ndigit,__decptr,__sign,__buf,__len))
#else /* LIBC: ecvt_r */
#include <local/stdlib/ecvt_r.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(ecvt_r, __FORCELOCAL __ATTR_NONNULL((3, 4, 5)) int __NOTHROW_NCX(__LIBCCALL ecvt_r)(double __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign, char *__restrict __buf, __SIZE_TYPE__ __len) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ecvt_r))(__val, __ndigit, __decptr, __sign, __buf, __len); })
#endif /* ecvt_r... */
#ifdef __CRT_HAVE_fcvt_r
__CDECLARE(__ATTR_NONNULL((3, 4, 5)),int,__NOTHROW_NCX,fcvt_r,(double __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign, char *__restrict __buf, __SIZE_TYPE__ __len),(__val,__ndigit,__decptr,__sign,__buf,__len))
#else /* LIBC: fcvt_r */
#include <local/stdlib/fcvt_r.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fcvt_r, __FORCELOCAL __ATTR_NONNULL((3, 4, 5)) int __NOTHROW_NCX(__LIBCCALL fcvt_r)(double __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign, char *__restrict __buf, __SIZE_TYPE__ __len) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fcvt_r))(__val, __ndigit, __decptr, __sign, __buf, __len); })
#endif /* fcvt_r... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#ifdef __CRT_HAVE_qgcvt
__CDECLARE(__ATTR_NONNULL((3)),char *,__NOTHROW_NCX,qgcvt,(long double __val, int __ndigit, char *__buf),(__val,__ndigit,__buf))
#elif defined(__CRT_HAVE__gcvt) && (__SIZEOF_LONG_DOUBLE__ == __SIZEOF_DOUBLE__)
__CREDIRECT(__ATTR_NONNULL((3)),char *,__NOTHROW_NCX,qgcvt,(long double __val, int __ndigit, char *__buf),_gcvt,(__val,__ndigit,__buf))
#else /* LIBC: qgcvt */
#include <local/stdlib/qgcvt.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(qgcvt, __FORCELOCAL __ATTR_NONNULL((3)) char *__NOTHROW_NCX(__LIBCCALL qgcvt)(long double __val, int __ndigit, char *__buf) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(qgcvt))(__val, __ndigit, __buf); })
#endif /* qgcvt... */
#ifdef __CRT_HAVE_qecvt_r
__CDECLARE(__ATTR_NONNULL((3, 4, 5)),int,__NOTHROW_NCX,qecvt_r,(long double __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign, char *__restrict __buf, __SIZE_TYPE__ __len),(__val,__ndigit,__decptr,__sign,__buf,__len))
#else /* LIBC: qecvt_r */
#include <local/stdlib/qecvt_r.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(qecvt_r, __FORCELOCAL __ATTR_NONNULL((3, 4, 5)) int __NOTHROW_NCX(__LIBCCALL qecvt_r)(long double __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign, char *__restrict __buf, __SIZE_TYPE__ __len) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(qecvt_r))(__val, __ndigit, __decptr, __sign, __buf, __len); })
#endif /* qecvt_r... */
#ifdef __CRT_HAVE_qfcvt_r
__CDECLARE(__ATTR_NONNULL((3, 4, 5)),int,__NOTHROW_NCX,qfcvt_r,(long double __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign, char *__restrict __buf, __SIZE_TYPE__ __len),(__val,__ndigit,__decptr,__sign,__buf,__len))
#else /* LIBC: qfcvt_r */
#include <local/stdlib/qfcvt_r.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(qfcvt_r, __FORCELOCAL __ATTR_NONNULL((3, 4, 5)) int __NOTHROW_NCX(__LIBCCALL qfcvt_r)(long double __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign, char *__restrict __buf, __SIZE_TYPE__ __len) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(qfcvt_r))(__val, __ndigit, __decptr, __sign, __buf, __len); })
#endif /* qfcvt_r... */
#ifdef __CRT_HAVE_qecvt
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((3, 4)),char *,__NOTHROW_NCX,qecvt,(long double __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign),(__val,__ndigit,__decptr,__sign))
#elif defined(__CRT_HAVE__ecvt)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((3, 4)),char *,__NOTHROW_NCX,qecvt,(long double __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign),_ecvt,(__val,__ndigit,__decptr,__sign))
#else /* LIBC: qecvt */
#include <local/stdlib/qecvt.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(qecvt, __FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((3, 4)) char *__NOTHROW_NCX(__LIBCCALL qecvt)(long double __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(qecvt))(__val, __ndigit, __decptr, __sign); })
#endif /* qecvt... */
#ifdef __CRT_HAVE_qfcvt
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((3, 4)),char *,__NOTHROW_NCX,qfcvt,(long double __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign),(__val,__ndigit,__decptr,__sign))
#elif defined(__CRT_HAVE__fcvt)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((3, 4)),char *,__NOTHROW_NCX,qfcvt,(long double __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign),_fcvt,(__val,__ndigit,__decptr,__sign))
#else /* LIBC: qfcvt */
#include <local/stdlib/qfcvt.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(qfcvt, __FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((3, 4)) char *__NOTHROW_NCX(__LIBCCALL qfcvt)(long double __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(qfcvt))(__val, __ndigit, __decptr, __sign); })
#endif /* qfcvt... */
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
#ifdef __CRT_HAVE_drand48_r
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,drand48_r,(struct drand48_data *__restrict __buffer, double *__restrict __result),(__buffer,__result))
#endif /* drand48_r... */
#ifdef __CRT_HAVE_erand48_r
__CDECLARE(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_NCX,erand48_r,(unsigned short __xsubi[3], struct drand48_data *__restrict __buffer, double *__restrict __result),(__xsubi,__buffer,__result))
#endif /* erand48_r... */
#endif /* !__NO_FPU */
#ifdef __CRT_HAVE_lrand48_r
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,lrand48_r,(struct drand48_data *__restrict __buffer, long *__restrict __result),(__buffer,__result))
#endif /* lrand48_r... */
#ifdef __CRT_HAVE_nrand48_r
__CDECLARE(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_NCX,nrand48_r,(unsigned short __xsubi[3], struct drand48_data *__restrict __buffer, long *__restrict __result),(__xsubi,__buffer,__result))
#endif /* nrand48_r... */
#ifdef __CRT_HAVE_mrand48_r
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,mrand48_r,(struct drand48_data *__restrict __buffer, long *__restrict __result),(__buffer,__result))
#endif /* mrand48_r... */
#ifdef __CRT_HAVE_jrand48_r
__CDECLARE(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_NCX,jrand48_r,(unsigned short __xsubi[3], struct drand48_data *__restrict __buffer, long *__restrict __result),(__xsubi,__buffer,__result))
#endif /* jrand48_r... */
#ifdef __CRT_HAVE_srand48_r
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,srand48_r,(long __seedval, struct drand48_data *__buffer),(__seedval,__buffer))
#endif /* srand48_r... */
#ifdef __CRT_HAVE_seed48_r
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,seed48_r,(unsigned short __seed16v[3], struct drand48_data *__buffer),(__seed16v,__buffer))
#endif /* seed48_r... */
#ifdef __CRT_HAVE_lcong48_r
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,lcong48_r,(unsigned short __param[7], struct drand48_data *__buffer),(__param,__buffer))
#endif /* lcong48_r... */
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
#ifdef __CRT_HAVE_random_r
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,random_r,(struct random_data *__restrict __buf, __INT32_TYPE__ *__restrict __result),(__buf,__result))
#endif /* random_r... */
#ifdef __CRT_HAVE_srandom_r
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,srandom_r,(unsigned int __seed, struct random_data *__buf),(__seed,__buf))
#endif /* srandom_r... */
#ifdef __CRT_HAVE_initstate_r
__CDECLARE(__ATTR_NONNULL((2, 4)),int,__NOTHROW_NCX,initstate_r,(unsigned int __seed, char *__restrict __statebuf, __SIZE_TYPE__ __statelen, struct random_data *__restrict __buf),(__seed,__statebuf,__statelen,__buf))
#endif /* initstate_r... */
#ifdef __CRT_HAVE_setstate_r
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,setstate_r,(char *__restrict __statebuf, struct random_data *__restrict __buf),(__statebuf,__buf))
#endif /* setstate_r... */
typedef void (__LIBCCALL *__on_exit_func_t)(int __status, void *__arg);
#ifdef __CRT_HAVE_on_exit
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,on_exit,(__on_exit_func_t __func, void *__arg),(__func,__arg))
#endif /* on_exit... */
#ifdef __CRT_HAVE_clearenv
__CDECLARE(,int,__NOTHROW_NCX,clearenv,(void),())
#endif /* clearenv... */
#if defined(__CRT_HAVE_mkstemps64) && (defined(__USE_FILE_OFFSET64))
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,mkstemps,(char *__template_, int __suffixlen),mkstemps64,(__template_,__suffixlen))
#elif defined(__CRT_HAVE_mkstemps)
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,mkstemps,(char *__template_, int __suffixlen),(__template_,__suffixlen))
#endif /* mkstemps... */
#ifdef __CRT_HAVE_rpmatch
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,rpmatch,(char const *__response),(__response))
#endif /* rpmatch... */
#ifdef __USE_LARGEFILE64
#ifdef __CRT_HAVE_mkstemps64
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,mkstemps64,(char *__template_, int __suffixlen),(__template_,__suffixlen))
#elif defined(__CRT_HAVE_mkstemps)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,mkstemps64,(char *__template_, int __suffixlen),mkstemps,(__template_,__suffixlen))
#elif defined(__CRT_HAVE_mkstemps) && (!defined(__O_LARGEFILE) || (__O_LARGEFILE+0) == 0)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,mkstemps64,(char *__template_, int __suffixlen),mkstemps,(__template_,__suffixlen))
#endif /* mkstemps64... */
#endif /* __USE_LARGEFILE64 */
#endif /* __USE_MISC */


#ifdef __USE_POSIX
#ifdef __CRT_HAVE_rand_r
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,rand_r,(unsigned int *__restrict __pseed),(__pseed))
#else /* LIBC: rand_r */
#include <local/stdlib/rand_r.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(rand_r, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL rand_r)(unsigned int *__restrict __pseed) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rand_r))(__pseed); })
#endif /* rand_r... */
#endif /* __USE_POSIX */


#ifdef __USE_MISC
#ifndef __cfree_defined
#define __cfree_defined 1
#ifdef __CRT_HAVE_free
__CREDIRECT_VOID(,__NOTHROW_NCX,cfree,(void *__restrict __mallptr),free,(__mallptr))
#elif defined(__CRT_HAVE_cfree)
__CDECLARE_VOID(,__NOTHROW_NCX,cfree,(void *__restrict __mallptr),(__mallptr))
#else /* LIBC: cfree */
#undef __cfree_defined
#endif /* cfree... */
#endif /* !__cfree_defined */
#ifndef __NO_FPU
#ifdef __CRT_HAVE_getloadavg
__CDECLARE(,int,__NOTHROW_RPC,getloadavg,(double __loadavg[], int __nelem),(__loadavg,__nelem))
#endif /* getloadavg... */
#endif /* !__NO_FPU */
#endif /* __USE_MISC */


#if defined(__USE_MISC) || (defined(__USE_XOPEN_EXTENDED) && !defined(__USE_XOPEN2K))
#ifndef __valloc_defined
#define __valloc_defined 1
#ifdef __CRT_HAVE_valloc
__CDECLARE(__ATTR_MALL_PAGEALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,valloc,(__SIZE_TYPE__ __n_bytes),(__n_bytes))
#elif defined(__CRT_HAVE_posix_memalign) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc)
#include <local/malloc/valloc.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(valloc, __FORCELOCAL __ATTR_MALL_PAGEALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)) void *__NOTHROW_NCX(__LIBCCALL valloc)(__SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(valloc))(__n_bytes); })
#else /* CUSTOM: valloc */
#undef __valloc_defined
#endif /* valloc... */
#endif /* !__valloc_defined */
#endif /* __USE_MISC || (__USE_XOPEN_EXTENDED && !__USE_XOPEN2K) */


#ifdef __USE_XOPEN2K
#ifndef __posix_memalign_defined
#define __posix_memalign_defined 1
#if __has_builtin(__builtin_posix_memalign) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_posix_memalign)
__FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL posix_memalign)(void **__restrict __pp, __SIZE_TYPE__ __alignment, __SIZE_TYPE__ __n_bytes) { return __builtin_posix_memalign(__pp, __alignment, __n_bytes); }
#elif defined(__CRT_HAVE_posix_memalign)
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,posix_memalign,(void **__restrict __pp, __SIZE_TYPE__ __alignment, __SIZE_TYPE__ __n_bytes),(__pp,__alignment,__n_bytes))
#elif defined(__CRT_HAVE_posix_memalign) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc)
#include <local/malloc/posix_memalign.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(posix_memalign, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL posix_memalign)(void **__restrict __pp, __SIZE_TYPE__ __alignment, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(posix_memalign))(__pp, __alignment, __n_bytes); })
#else /* CUSTOM: posix_memalign */
#undef __posix_memalign_defined
#endif /* posix_memalign... */
#endif /* !__posix_memalign_defined */
#endif /* __USE_XOPEN2K */


#ifdef __USE_ISOCXX17
#ifndef __CXX_SYSTEM_HEADER
#if !defined(__aligned_alloc_defined) && defined(__std_aligned_alloc_defined)
#define __aligned_alloc_defined 1
__NAMESPACE_STD_USING(aligned_alloc)
#endif /* !__aligned_alloc_defined && !__std_aligned_alloc_defined */
#endif /* !__CXX_SYSTEM_HEADER */
#endif /* __USE_ISOCXX17 */

/* aligned_alloc() is defined by both c11 and c++17 */
#ifdef __USE_ISOC11
#ifndef __aligned_alloc_defined
#define __aligned_alloc_defined 1
#ifdef __std_aligned_alloc_defined
__NAMESPACE_STD_USING(aligned_alloc)
#elif __has_builtin(__builtin_aligned_alloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_aligned_alloc)
__FORCELOCAL __ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) __ATTR_ALLOC_ALIGN(1) void *__NOTHROW_NCX(__LIBCCALL aligned_alloc)(__SIZE_TYPE__ __alignment, __SIZE_TYPE__ __n_bytes) { return __builtin_aligned_alloc(__alignment, __n_bytes); }
#elif defined(__CRT_HAVE_aligned_alloc)
__CDECLARE(__ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) __ATTR_ALLOC_ALIGN(1),void *,__NOTHROW_NCX,aligned_alloc,(__SIZE_TYPE__ __alignment, __SIZE_TYPE__ __n_bytes),(__alignment,__n_bytes))
#elif defined(__CRT_HAVE_memalign)
__CREDIRECT(__ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) __ATTR_ALLOC_ALIGN(1),void *,__NOTHROW_NCX,aligned_alloc,(__SIZE_TYPE__ __alignment, __SIZE_TYPE__ __n_bytes),memalign,(__alignment,__n_bytes))
#elif defined(__CRT_HAVE_posix_memalign)
#include <local/malloc/memalign.h>
__FORCELOCAL __ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) __ATTR_ALLOC_ALIGN(1) void *__NOTHROW_NCX(__LIBCCALL aligned_alloc)(__SIZE_TYPE__ __alignment, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memalign))(__alignment, __n_bytes); }
#else /* CUSTOM: memalign */
#undef __aligned_alloc_defined
#endif /* aligned_alloc... */
#endif /* !__aligned_alloc_defined */
#endif /* __USE_ISOC11 */

#ifndef MB_CUR_MAX
#ifdef __CRT_HAVE___ctype_get_mb_cur_max
__CDECLARE(__ATTR_WUNUSED,__SIZE_TYPE__,__NOTHROW,__ctype_get_mb_cur_max,(void),())
#define MB_CUR_MAX  (__ctype_get_mb_cur_max())
#else
#define MB_CUR_MAX   7 /* == UNICODE_UTF8_CURLEN */
#endif
#endif /* !MB_CUR_MAX */

#if defined(__USE_MISC) || defined(__USE_XOPEN)
#ifndef __NO_FPU
#ifdef __CRT_HAVE_drand48
__CDECLARE(,double,__NOTHROW_NCX,drand48,(void),())
#endif /* drand48... */
#endif /* !__NO_FPU */
#ifdef __CRT_HAVE_lrand48
__CDECLARE(,long,__NOTHROW_NCX,lrand48,(void),())
#endif /* lrand48... */
#ifdef __CRT_HAVE_mrand48
__CDECLARE(,long,__NOTHROW_NCX,mrand48,(void),())
#endif /* mrand48... */
#ifndef __NO_FPU
#ifdef __CRT_HAVE_erand48
__CDECLARE(__ATTR_NONNULL((1)),double,__NOTHROW_NCX,erand48,(unsigned short __xsubi[3]),(__xsubi))
#endif /* erand48... */
#endif /* !__NO_FPU */
#ifdef __CRT_HAVE_nrand48
__CDECLARE(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,nrand48,(unsigned short __xsubi[3]),(__xsubi))
#endif /* nrand48... */
#ifdef __CRT_HAVE_jrand48
__CDECLARE(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,jrand48,(unsigned short __xsubi[3]),(__xsubi))
#endif /* jrand48... */
#ifdef __CRT_HAVE_srand48
__CDECLARE_VOID(,__NOTHROW_NCX,srand48,(long __seedval),(__seedval))
#endif /* srand48... */
#ifdef __CRT_HAVE_seed48
__CDECLARE(__ATTR_NONNULL((1)),unsigned short *,__NOTHROW_NCX,seed48,(unsigned short __seed16v[3]),(__seed16v))
#endif /* seed48... */
#ifdef __CRT_HAVE_lcong48
__CDECLARE_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,lcong48,(unsigned short __param[7]),(__param))
#endif /* lcong48... */
#endif /* __USE_MISC || __USE_XOPEN */
#if defined(__USE_MISC) || defined(__USE_XOPEN) || defined(__USE_DOS)
#ifdef __CRT_HAVE_putenv
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,putenv,(char *__string),(__string))
#elif defined(__CRT_HAVE__putenv)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,putenv,(char *__string),_putenv,(__string))
#endif /* putenv... */
#endif /* __USE_MISC || __USE_XOPEN || __USE_DOS */
#if defined(__USE_MISC) || defined(__USE_XOPEN_EXTENDED)
#ifdef __CRT_HAVE_random
__CDECLARE(,long,__NOTHROW_NCX,random,(void),())
#elif defined(__CRT_HAVE_rand) && (__SIZEOF_LONG__ == __SIZEOF_INT__)
__CREDIRECT(,long,__NOTHROW_NCX,random,(void),rand,())
#else /* LIBC: random */
#include <local/stdlib/random.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(random, __FORCELOCAL long __NOTHROW_NCX(__LIBCCALL random)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(random))(); })
#endif /* random... */
#ifdef __CRT_HAVE_srandom
__CDECLARE_VOID(,__NOTHROW_NCX,srandom,(unsigned int __seed),(__seed))
#elif defined(__CRT_HAVE_srand) && (__SIZEOF_LONG__ == __SIZEOF_INT__)
__CREDIRECT_VOID(,__NOTHROW_NCX,srandom,(unsigned int __seed),srand,(__seed))
#else /* LIBC: srandom */
#include <local/stdlib/srandom.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(srandom, __FORCELOCAL void __NOTHROW_NCX(__LIBCCALL srandom)(unsigned int __seed) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(srandom))(__seed); })
#endif /* srandom... */
#ifdef __CRT_HAVE_initstate
__CDECLARE(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,initstate,(unsigned int __seed, char *__statebuf, __SIZE_TYPE__ __statelen),(__seed,__statebuf,__statelen))
#endif /* initstate... */
#ifdef __CRT_HAVE_setstate
__CDECLARE(__ATTR_NONNULL((1)),char *,__NOTHROW_NCX,setstate,(char *__statebuf),(__statebuf))
#endif /* setstate... */
#ifdef __CRT_HAVE_l64a
__CDECLARE(__ATTR_WUNUSED,char *,__NOTHROW_NCX,l64a,(long __n),(__n))
#endif /* l64a... */
#ifdef __CRT_HAVE_a64l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),long,__NOTHROW_NCX,a64l,(char const *__s),(__s))
#endif /* a64l... */
#ifdef __CRT_HAVE_realpath
/* Load the filesystem location of a given file handle.
 * This function behaves similar to `readlink()', but will also function for
 * non-symlink paths, as well as always return an absolute (unambiguous) path
 * @param: resolved: A buffer of `PATH_MAX' bytes to-be filled with the resulting
 *                   path, or NULL to automatically `malloc()'ate and return a
 *                   buffer of sufficient size. */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_RPC,realpath,(char const *__restrict __filename, char *__resolved),(__filename,__resolved))
#endif /* realpath... */
#endif /* __USE_MISC || __USE_XOPEN_EXTENDED */

#if defined(__USE_MISC) || defined(__USE_XOPEN_EXTENDED) || defined(__USE_KOS)
/* NOTE: I didn't come up with this function (https://docs.oracle.com/cd/E36784_01/html/E36874/frealpath-3c.html),
 *       but it seems to be something that GLibc isn't implementing for some reason...
 *       Because of that, I didn't really know where to put this, so I put it in the
 *       same _SOURCE-block as its `realpath()' companion. */
#ifdef __CRT_HAVE_frealpath
/* Load the filesystem location of a given file handle.
 * This function behaves similar to `readlink("/proc/self/fd/%d" % fd)'
 * NOTE: You may also pass `NULL' for `resolved' to have a buffer of `bufsize'
 *       bytes automatically allocated in the heap, ontop of which you may also
 *       pass `0' for `bufsize' to automatically determine the required buffer size. */
__CDECLARE(__ATTR_WUNUSED,char *,__NOTHROW_RPC,frealpath,(__fd_t __fd, char *__resolved, __SIZE_TYPE__ __bufsize),(__fd,__resolved,__bufsize))
#endif /* frealpath... */
#endif /* __USE_MISC || __USE_XOPEN_EXTENDED || __USE_KOS */

#ifdef __USE_KOS
#ifdef __CRT_HAVE_frealpath4
/* Load the filesystem location of a given file handle.
 * This function behaves similar to `readlink("/proc/self/fd/%d" % fd)'
 * @param flags: Set of `0|AT_ALTPATH|AT_DOSPATH'
 * NOTE: You may also pass `NULL' for `resolved' to have a buffer of `bufsize'
 *       bytes automatically allocated in the heap, ontop of which you may also
 *       pass `0' for `bufsize' to automatically determine the required buffer size. */
__CDECLARE(__ATTR_WUNUSED,char *,__NOTHROW_RPC,frealpath4,(__fd_t __fd, char *__resolved, __SIZE_TYPE__ __bufsize, __atflag_t __flags),(__fd,__resolved,__bufsize,__flags))
#endif /* frealpath4... */
#ifdef __CRT_HAVE_frealpathat
/* Returns the absolute filesystem path for the specified file
 * When `AT_SYMLINK_FOLLOW' is given, a final symlink is dereferenced,
 * causing the pointed-to file location to be retrieved. - Otherwise, the
 * location of the link is printed instead.
 * NOTE: You may also pass `NULL' for `resolved' to have a buffer of `bufsize'
 *       bytes automatically allocated in the heap, ontop of which you may also
 *       pass `0' for `bufsize' to automatically determine the required buffer size.
 * @param flags: Set of `0|AT_ALTPATH|AT_SYMLINK_FOLLOW|AT_DOSPATH' */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((2)),char *,__NOTHROW_RPC,frealpathat,(__fd_t __dirfd, char const *__filename, char *__resolved, __SIZE_TYPE__ __bufsize, __atflag_t __flags),(__dirfd,__filename,__resolved,__bufsize,__flags))
#endif /* frealpathat... */
#endif /* __USE_KOS */


#ifdef __USE_XOPEN2K
#ifdef __CRT_HAVE_setenv
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,setenv,(char const *__varname, char const *__val, int __replace),(__varname,__val,__replace))
#elif defined(__CRT_HAVE__putenv_s)
#include <local/stdlib/setenv.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(setenv, __FORCELOCAL __ATTR_NONNULL((2)) int __NOTHROW_NCX(__LIBCCALL setenv)(char const *__varname, char const *__val, int __replace) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(setenv))(__varname, __val, __replace); })
#endif /* setenv... */
#ifdef __CRT_HAVE_unsetenv
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,unsetenv,(char const *__varname),(__varname))
#elif defined(__CRT_HAVE_putenv) || defined(__CRT_HAVE__putenv)
#include <local/stdlib/unsetenv.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(unsetenv, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL unsetenv)(char const *__varname) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unsetenv))(__varname); })
#endif /* unsetenv... */
#endif /* __USE_XOPEN2K */


#if defined(__USE_MISC) || \
   (defined(__USE_XOPEN_EXTENDED) && !defined(__USE_XOPEN2K8))
#ifndef __mktemp_defined
#define __mktemp_defined 1
#ifdef __CRT_HAVE_mktemp
__CDECLARE(__ATTR_NONNULL((1)),char *,__NOTHROW_NCX,mktemp,(char *__template_),(__template_))
#elif defined(__CRT_HAVE__mktemp)
__CREDIRECT(__ATTR_NONNULL((1)),char *,__NOTHROW_NCX,mktemp,(char *__template_),_mktemp,(__template_))
#elif defined(__CRT_HAVE___mktemp)
__CREDIRECT(__ATTR_NONNULL((1)),char *,__NOTHROW_NCX,mktemp,(char *__template_),__mktemp,(__template_))
#else /* LIBC: mktemp */
#undef __mktemp_defined
#endif /* mktemp... */
#endif /* !__mktemp_defined */
#endif


#if defined(__USE_MISC) || defined(__USE_DOS) || \
   (defined(__USE_XOPEN_EXTENDED) && !defined(__USE_XOPEN2K8))
#ifndef __NO_FPU
#ifdef __CRT_HAVE_ecvt
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((3, 4)),char *,__NOTHROW_NCX,ecvt,(double __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign),(__val,__ndigit,__decptr,__sign))
#elif defined(__CRT_HAVE__ecvt)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((3, 4)),char *,__NOTHROW_NCX,ecvt,(double __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign),_ecvt,(__val,__ndigit,__decptr,__sign))
#else /* LIBC: ecvt */
#include <local/stdlib/ecvt.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(ecvt, __FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((3, 4)) char *__NOTHROW_NCX(__LIBCCALL ecvt)(double __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ecvt))(__val, __ndigit, __decptr, __sign); })
#endif /* ecvt... */
#ifdef __CRT_HAVE_fcvt
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((3, 4)),char *,__NOTHROW_NCX,fcvt,(double __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign),(__val,__ndigit,__decptr,__sign))
#elif defined(__CRT_HAVE__ecvt)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((3, 4)),char *,__NOTHROW_NCX,fcvt,(double __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign),_ecvt,(__val,__ndigit,__decptr,__sign))
#else /* LIBC: fcvt */
#include <local/stdlib/fcvt.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fcvt, __FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((3, 4)) char *__NOTHROW_NCX(__LIBCCALL fcvt)(double __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fcvt))(__val, __ndigit, __decptr, __sign); })
#endif /* fcvt... */
#endif /* !__NO_FPU */
#endif /* ... */
#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K8)
#ifdef __CRT_HAVE_getsubopt
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_NCX,getsubopt,(char **__restrict __optionp, char *const *__restrict __tokens, char **__restrict __valuep),(__optionp,__tokens,__valuep))
#else /* LIBC: getsubopt */
#include <local/stdlib/getsubopt.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(getsubopt, __FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((1, 2, 3)) int __NOTHROW_NCX(__LIBCCALL getsubopt)(char **__restrict __optionp, char *const *__restrict __tokens, char **__restrict __valuep) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getsubopt))(__optionp, __tokens, __valuep); })
#endif /* getsubopt... */
#if defined(__CRT_HAVE_mkstemp64) && (defined(__USE_FILE_OFFSET64))
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,mkstemp,(char *__template_),mkstemp64,(__template_))
#elif defined(__CRT_HAVE_mkstemp)
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,mkstemp,(char *__template_),(__template_))
#elif defined(__CRT_HAVE_mktemp) || defined(__CRT_HAVE__mktemp) || defined(__CRT_HAVE___mktemp)
#include <local/stdlib/mkstemp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(mkstemp, __FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL mkstemp)(char *__template_) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mkstemp))(__template_); })
#endif /* mkstemp... */
#ifdef __USE_LARGEFILE64
#ifdef __CRT_HAVE_mkstemp64
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,mkstemp64,(char *__template_),(__template_))
#elif defined(__CRT_HAVE_mkstemp)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,mkstemp64,(char *__template_),mkstemp,(__template_))
#elif defined(__CRT_HAVE_mkstemp) && (!defined(__O_LARGEFILE) || (__O_LARGEFILE+0) == 0)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,mkstemp64,(char *__template_),mkstemp,(__template_))
#elif defined(__CRT_HAVE_mktemp) || defined(__CRT_HAVE__mktemp) || defined(__CRT_HAVE___mktemp)
#include <local/stdlib/mkstemp.h>
__FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL mkstemp64)(char *__template_) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mkstemp))(__template_); }
#endif /* mkstemp64... */
#endif /* __USE_LARGEFILE64 */
#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K8 */

#ifdef __USE_XOPEN2K8
#ifndef __mkdtemp_defined
#define __mkdtemp_defined 1
#ifdef __CRT_HAVE_mkdtemp
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,mkdtemp,(char *__template_),(__template_))
#elif defined(__CRT_HAVE__mktemp)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,mkdtemp,(char *__template_),_mktemp,(__template_))
#else /* LIBC: mkdtemp */
#undef __mkdtemp_defined
#endif /* mkdtemp... */
#endif /* !__mkdtemp_defined */
#endif /* __USE_XOPEN2K8 */

#ifdef __USE_XOPEN
#ifdef __CRT_HAVE_setkey
__CDECLARE_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,setkey,(char const *__key),(__key))
#endif /* setkey... */
#ifdef __CRT_HAVE_grantpt
__CDECLARE(,int,__NOTHROW_NCX,grantpt,(__fd_t __fd),(__fd))
#endif /* grantpt... */
#ifdef __CRT_HAVE_unlockpt
__CDECLARE(,int,__NOTHROW_NCX,unlockpt,(__fd_t __fd),(__fd))
#endif /* unlockpt... */
#ifdef __CRT_HAVE_ptsname
__CDECLARE(__ATTR_WUNUSED,char *,__NOTHROW_NCX,ptsname,(__fd_t __fd),(__fd))
#endif /* ptsname... */
#endif /* __USE_XOPEN */

#ifdef __USE_XOPEN2KXSI
#ifdef __CRT_HAVE_posix_openpt
__CDECLARE(__ATTR_WUNUSED,int,__NOTHROW_RPC,posix_openpt,(__oflag_t __oflags),(__oflags))
#endif /* posix_openpt... */
#endif /* __USE_XOPEN2KXSI */
#ifdef __USE_GNU
#ifdef __CRT_HAVE_strtol_l
__CDECLARE(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,strtol_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtol_l)
__CREDIRECT(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,strtol_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),_strtol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___strtol_l)
__CREDIRECT(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,strtol_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),__strtol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtoll_l) && (__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__)
__CREDIRECT(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,strtol_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),strtoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoll_l) && (__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__)
__CREDIRECT(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,strtol_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),_strtoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtoq_l) && (__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__)
__CREDIRECT(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,strtol_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),strtoq_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strto32_l) && (__SIZEOF_LONG__ == 4)
__CREDIRECT(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,strtol_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),strto32_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strto64_l) && (__SIZEOF_LONG__ == 8)
__CREDIRECT(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,strtol_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),strto64_l,(__nptr,__endptr,__base,__locale))
#else /* LIBC: strtol_l */
#include <local/stdlib/strtol_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strtol_l, __FORCELOCAL __ATTR_NONNULL((1)) long __NOTHROW_NCX(__LIBCCALL strtol_l)(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtol_l))(__nptr, __endptr, __base, __locale); })
#endif /* strtol_l... */
#ifdef __CRT_HAVE_strtoul_l
__CDECLARE(__ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,strtoul_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoul_l)
__CREDIRECT(__ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,strtoul_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),_strtoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___strtoul_l)
__CREDIRECT(__ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,strtoul_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),__strtoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtoull_l) && (__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__)
__CREDIRECT(__ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,strtoul_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),strtoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoll_l) && (__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__)
__CREDIRECT(__ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,strtoul_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),_strtoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtouq_l) && (__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__)
__CREDIRECT(__ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,strtoul_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),strtouq_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtou32_l) && (__SIZEOF_LONG__ == 4)
__CREDIRECT(__ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,strtoul_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),strtou32_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtou64_l) && (__SIZEOF_LONG__ == 8)
__CREDIRECT(__ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,strtoul_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),strtou64_l,(__nptr,__endptr,__base,__locale))
#else /* LIBC: strtoul_l */
#include <local/stdlib/strtoul_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strtoul_l, __FORCELOCAL __ATTR_NONNULL((1)) unsigned long __NOTHROW_NCX(__LIBCCALL strtoul_l)(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtoul_l))(__nptr, __endptr, __base, __locale); })
#endif /* strtoul_l... */
#ifdef __LONGLONG
#ifdef __CRT_HAVE_strtoll_l
__CDECLARE(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,strtoll_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoll_l)
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,strtoll_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),_strtoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtoq_l)
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,strtoll_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),strtoq_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___strtoll_l)
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,strtoll_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),__strtoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtol_l) && (__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__)
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,strtoll_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),strtol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtol_l) && (__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__)
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,strtoll_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),_strtol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strto64_l) && (__SIZEOF_LONG_LONG__ == 8)
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,strtoll_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),strto64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strto32_l) && (__SIZEOF_LONG_LONG__ == 4)
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,strtoll_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),strto32_l,(__nptr,__endptr,__base,__locale))
#else /* LIBC: strtoll_l */
#include <local/stdlib/strtoll_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strtoll_l, __FORCELOCAL __ATTR_NONNULL((1)) __LONGLONG __NOTHROW_NCX(__LIBCCALL strtoll_l)(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtoll_l))(__nptr, __endptr, __base, __locale); })
#endif /* strtoll_l... */
#ifdef __CRT_HAVE_strtoull_l
__CDECLARE(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,strtoull_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoull_l)
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,strtoull_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),_strtoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtouq_l)
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,strtoull_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),strtouq_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___strtoull_l)
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,strtoull_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),__strtoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtoul_l) && (__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__)
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,strtoull_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),strtoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoul_l) && (__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__)
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,strtoull_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),_strtoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtou64_l) && (__SIZEOF_LONG_LONG__ == 8)
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,strtoull_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),strtou64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtou32_l) && (__SIZEOF_LONG_LONG__ == 4)
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,strtoull_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),strtou32_l,(__nptr,__endptr,__base,__locale))
#else /* LIBC: strtoull_l */
#include <local/stdlib/strtoull_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strtoull_l, __FORCELOCAL __ATTR_NONNULL((1)) __ULONGLONG __NOTHROW_NCX(__LIBCCALL strtoull_l)(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtoull_l))(__nptr, __endptr, __base, __locale); })
#endif /* strtoull_l... */
#endif /* __LONGLONG */
#ifndef __NO_FPU
#ifdef __CRT_HAVE_strtod_l
__CDECLARE(__ATTR_NONNULL((1)),double,__NOTHROW_NCX,strtod_l,(char const *__restrict __nptr, char **__endptr, __locale_t __locale),(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE__strtod_l)
__CREDIRECT(__ATTR_NONNULL((1)),double,__NOTHROW_NCX,strtod_l,(char const *__restrict __nptr, char **__endptr, __locale_t __locale),_strtod_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE___strtod_l)
__CREDIRECT(__ATTR_NONNULL((1)),double,__NOTHROW_NCX,strtod_l,(char const *__restrict __nptr, char **__endptr, __locale_t __locale),__strtod_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE_strtold_l) && (__SIZEOF_LONG_DOUBLE__ == __SIZEOF_DOUBLE__)
__CREDIRECT(__ATTR_NONNULL((1)),double,__NOTHROW_NCX,strtod_l,(char const *__restrict __nptr, char **__endptr, __locale_t __locale),strtold_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE__strtold_l) && (__SIZEOF_LONG_DOUBLE__ == __SIZEOF_DOUBLE__)
__CREDIRECT(__ATTR_NONNULL((1)),double,__NOTHROW_NCX,strtod_l,(char const *__restrict __nptr, char **__endptr, __locale_t __locale),_strtold_l,(__nptr,__endptr,__locale))
#else /* LIBC: strtod_l */
#include <local/stdlib/strtod_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strtod_l, __FORCELOCAL __ATTR_NONNULL((1)) double __NOTHROW_NCX(__LIBCCALL strtod_l)(char const *__restrict __nptr, char **__endptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtod_l))(__nptr, __endptr, __locale); })
#endif /* strtod_l... */
#ifdef __CRT_HAVE_strtof_l
__CDECLARE(__ATTR_NONNULL((1)),float,__NOTHROW_NCX,strtof_l,(char const *__restrict __nptr, char **__endptr, __locale_t __locale),(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE__strtof_l)
__CREDIRECT(__ATTR_NONNULL((1)),float,__NOTHROW_NCX,strtof_l,(char const *__restrict __nptr, char **__endptr, __locale_t __locale),_strtof_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE___strtof_l)
__CREDIRECT(__ATTR_NONNULL((1)),float,__NOTHROW_NCX,strtof_l,(char const *__restrict __nptr, char **__endptr, __locale_t __locale),__strtof_l,(__nptr,__endptr,__locale))
#else /* LIBC: strtof_l */
#include <local/stdlib/strtof_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strtof_l, __FORCELOCAL __ATTR_NONNULL((1)) float __NOTHROW_NCX(__LIBCCALL strtof_l)(char const *__restrict __nptr, char **__endptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtof_l))(__nptr, __endptr, __locale); })
#endif /* strtof_l... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#ifdef __CRT_HAVE_strtold_l
__CDECLARE(__ATTR_NONNULL((1)),long double,__NOTHROW_NCX,strtold_l,(char const *__restrict __nptr, char **__endptr, __locale_t __locale),(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE__strtold_l)
__CREDIRECT(__ATTR_NONNULL((1)),long double,__NOTHROW_NCX,strtold_l,(char const *__restrict __nptr, char **__endptr, __locale_t __locale),_strtold_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE___strtold_l)
__CREDIRECT(__ATTR_NONNULL((1)),long double,__NOTHROW_NCX,strtold_l,(char const *__restrict __nptr, char **__endptr, __locale_t __locale),__strtold_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE_strtod_l) && (__SIZEOF_LONG_DOUBLE__ == __SIZEOF_DOUBLE__)
__CREDIRECT(__ATTR_NONNULL((1)),long double,__NOTHROW_NCX,strtold_l,(char const *__restrict __nptr, char **__endptr, __locale_t __locale),strtod_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE__strtod_l) && (__SIZEOF_LONG_DOUBLE__ == __SIZEOF_DOUBLE__)
__CREDIRECT(__ATTR_NONNULL((1)),long double,__NOTHROW_NCX,strtold_l,(char const *__restrict __nptr, char **__endptr, __locale_t __locale),_strtod_l,(__nptr,__endptr,__locale))
#else /* LIBC: strtold_l */
#include <local/stdlib/strtold_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strtold_l, __FORCELOCAL __ATTR_NONNULL((1)) long double __NOTHROW_NCX(__LIBCCALL strtold_l)(char const *__restrict __nptr, char **__endptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtold_l))(__nptr, __endptr, __locale); })
#endif /* strtold_l... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__NO_FPU */
#ifdef __CRT_HAVE_secure_getenv
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,secure_getenv,(char const *__varname),(__varname))
#elif defined(__CRT_HAVE_getenv)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,secure_getenv,(char const *__varname),getenv,(__varname))
#elif defined(__CRT_HAVE___secure_getenv)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,secure_getenv,(char const *__varname),__secure_getenv,(__varname))
#endif /* secure_getenv... */
#ifdef __CRT_HAVE_ptsname_r
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,ptsname_r,(__fd_t __fd, char *__buf, __SIZE_TYPE__ __buflen),(__fd,__buf,__buflen))
#endif /* ptsname_r... */
#ifdef __CRT_HAVE_getpt
__CDECLARE(,int,__NOTHROW_RPC,getpt,(void),())
#endif /* getpt... */
#ifdef __CRT_HAVE_canonicalize_file_name
/* Return the result of `realpath(filename)' as a `malloc()'-allocated buffer
 * Upon error, `NULL' is returned instead */
__CDECLARE(__ATTR_MALLOC __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_RPC,canonicalize_file_name,(char const *__filename),(__filename))
#endif /* canonicalize_file_name... */
#if defined(__CRT_HAVE_mkostemp64) && (defined(__USE_FILE_OFFSET64))
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_RPC,mkostemp,(char *__template_, int __flags),mkostemp64,(__template_,__flags))
#elif defined(__CRT_HAVE_mkostemp)
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_RPC,mkostemp,(char *__template_, int __flags),(__template_,__flags))
#elif defined(__CRT_HAVE_mkostemp64)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_RPC,mkostemp,(char *__template_, int __flags),mkostemp64,(__template_,__flags))
#endif /* mkostemp... */
#if defined(__CRT_HAVE_mkostemps64) && (defined(__USE_FILE_OFFSET64))
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_RPC,mkostemps,(char *__template_, int __suffixlen, int __flags),mkostemps64,(__template_,__suffixlen,__flags))
#elif defined(__CRT_HAVE_mkostemps)
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_RPC,mkostemps,(char *__template_, int __suffixlen, int __flags),(__template_,__suffixlen,__flags))
#elif defined(__CRT_HAVE_mkostemps64)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_RPC,mkostemps,(char *__template_, int __suffixlen, int __flags),mkostemps64,(__template_,__suffixlen,__flags))
#endif /* mkostemps... */
#ifdef __USE_LARGEFILE64
#ifdef __CRT_HAVE_mkostemp64
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_RPC,mkostemp64,(char *__template_, int __flags),(__template_,__flags))
#elif defined(__CRT_HAVE_mkostemp) && (!defined(__O_LARGEFILE) || (__O_LARGEFILE+0) == 0)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_RPC,mkostemp64,(char *__template_, int __flags),mkostemp,(__template_,__flags))
#endif /* mkostemp64... */
#ifdef __CRT_HAVE_mkostemps64
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_RPC,mkostemps64,(char *__template_, int __suffixlen, int __flags),(__template_,__suffixlen,__flags))
#elif defined(__CRT_HAVE_mkostemps) && (!defined(__O_LARGEFILE) || (__O_LARGEFILE+0) == 0)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_RPC,mkostemps64,(char *__template_, int __suffixlen, int __flags),mkostemps,(__template_,__suffixlen,__flags))
#endif /* mkostemps64... */
#endif /* __USE_LARGEFILE64 */
#endif /* __USE_GNU */

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

#include <hybrid/__minmax.h>
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
typedef int (__LIBCCALL *_onexit_t)(void);
#define onexit_t         _onexit_t
#endif  /* _ONEXIT_T_DEFINED */

#ifndef _CRT_ERRNO_DEFINED
#define _CRT_ERRNO_DEFINED 1
#ifndef errno
#ifndef ____errno_location_defined
#define ____errno_location_defined 1
#ifdef __CRT_HAVE___errno_location
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,errno_t *,__NOTHROW_NCX,__errno_location,(void),())
#elif defined(__CRT_HAVE__errno)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,errno_t *,__NOTHROW_NCX,__errno_location,(void),_errno,())
#elif defined(__CRT_HAVE___errno)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,errno_t *,__NOTHROW_NCX,__errno_location,(void),__errno,())
#else /* LIBC: __errno_location */
#undef ____errno_location_defined
#endif /* __errno_location... */
#endif /* !____errno_location_defined */
#ifdef ____errno_location_defined
#define errno     (*__errno_location())
#endif /* ____errno_location_defined */
#endif /* !errno */
#endif /* !_CRT_ERRNO_DEFINED */

#ifdef __CRT_HAVE___doserrno
#define _doserrno     (*__doserrno())
#endif /* __CRT_HAVE___doserrno */
#ifdef __CRT_HAVE___doserrno
__CDECLARE(__ATTR_CONST,__UINT32_TYPE__ *,__NOTHROW_NCX,__doserrno,(void),())
#endif /* __doserrno... */
#ifdef __CRT_HAVE__get_doserrno
__CDECLARE(,errno_t,__NOTHROW_NCX,_get_doserrno,(__UINT32_TYPE__ *__perr),(__perr))
#endif /* _get_doserrno... */
#ifdef __CRT_HAVE__set_doserrno
__CDECLARE(,errno_t,__NOTHROW_NCX,_set_doserrno,(__UINT32_TYPE__ __err),(__err))
#endif /* _set_doserrno... */

#ifndef ___sys_errlist_defined
#define ___sys_errlist_defined 1
#if defined(__CRT_HAVE__sys_errlist)
__LIBC char const *const _sys_errlist[];
#elif defined(__CRT_HAVE___sys_errlist)
__CDECLARE(, char const *const *,__NOTHROW, __sys_errlist, (void), ())
#define _sys_errlist (__sys_errlist())
#endif

#if defined(__CRT_HAVE__sys_nerr)
__LIBC int _sys_nerr;
#elif defined(__CRT_HAVE___sys_nerr)
__CDECLARE(, int *,__NOTHROW, __sys_nerr, (void), ())
#define _sys_nerr    (*__sys_nerr())
#endif
#endif /* !___sys_errlist_defined */


#ifndef ___environ_defined
#define ___environ_defined 1
#undef _environ
#if defined(__CRT_HAVE_environ) && !defined(__NO_ASMNAME)
__LIBC char **_environ __ASMNAME("environ");
#elif defined(__CRT_HAVE__environ)
__LIBC char **_environ;
#elif defined(__CRT_HAVE___environ) && !defined(__NO_ASMNAME)
__LIBC char **_environ __ASMNAME("__environ");
#elif defined(__CRT_HAVE_environ)
#undef environ
#ifndef __environ_defined
#define __environ_defined 1
__LIBC char **environ;
#endif /* !__environ_defined */
#define _environ environ
#elif defined(__CRT_HAVE___p__environ)
#ifndef ____p__environ_defined
#define ____p__environ_defined 1
__CDECLARE(__ATTR_WUNUSED __ATTR_CONST __ATTR_RETNONNULL,char ***,__NOTHROW,__p__environ,(void),())
#endif /* !____p__environ_defined */
#define _environ (*__p__environ())
#else
#undef ___environ_defined
#endif
#endif /* !___environ_defined */

#ifndef __argc
#ifdef __CRT_HAVE___argc
__LIBC int __argc;
#define __argc __argc
#else /* .... */
#ifndef ____p___argc_defined
#define ____p___argc_defined 1
#ifdef __CRT_HAVE___p___argc
__CDECLARE(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,int *,__NOTHROW_NCX,__p___argc,(void),())
#else /* LIBC: __p___argc */
#undef ____p___argc_defined
#endif /* __p___argc... */
#endif /* !____p___argc_defined */
#ifdef ____p___argc_defined
#define __argc (*__p___argc())
#endif /* ____p___argc_defined */
#endif /* !... */
#endif /* !__argc */

#ifndef __argv
#ifdef __CRT_HAVE___argv
__LIBC char **__argv;
#else /* .... */
#ifndef ____p___argv_defined
#define ____p___argv_defined 1
#ifdef __CRT_HAVE___p___argv
__CDECLARE(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,char ***,__NOTHROW_NCX,__p___argv,(void),())
#else /* LIBC: __p___argv */
#undef ____p___argv_defined
#endif /* __p___argv... */
#endif /* !____p___argv_defined */
#ifdef ____p___argv_defined
#define __argv (*__p___argv())
#endif /* ____p___argv_defined */
#endif /* !... */
#endif /* !__argv */

#ifndef __wargv
#ifdef __CRT_HAVE___wargv
__LIBC wchar_t **__wargv;
#define __wargv __wargv
#else /* .... */
#ifndef ____p___wargv_defined
#define ____p___wargv_defined 1
#ifdef __CRT_HAVE___p___wargv
__CDECLARE(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,wchar_t ***,__NOTHROW_NCX,__p___wargv,(void),())
#else /* LIBC: __p___wargv */
#undef ____p___wargv_defined
#endif /* __p___wargv... */
#endif /* !____p___wargv_defined */
#ifdef ____p___wargv_defined
#define __wargv (*__p___wargv())
#endif /* ____p___wargv_defined */
#endif /* !... */
#endif /* !__wargv */

#ifndef _wenviron
#ifdef __CRT_HAVE__wenviron
__LIBC wchar_t **_wenviron;
#define _wenviron _wenviron
#else /* .... */
#ifndef ____p__wenviron_defined
#define ____p__wenviron_defined 1
#ifdef __CRT_HAVE___p__wenviron
__CDECLARE(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,wchar_t ***,__NOTHROW_NCX,__p__wenviron,(void),())
#else /* LIBC: __p__wenviron */
#undef ____p__wenviron_defined
#endif /* __p__wenviron... */
#endif /* !____p__wenviron_defined */
#ifdef ____p__wenviron_defined
#define _wenviron (*__p__wenviron())
#endif /* ____p__wenviron_defined */
#endif /* !... */
#endif /* !_wenviron */

#ifndef _wpgmptr
#ifdef __CRT_HAVE__wpgmptr
__LIBC wchar_t *_wpgmptr;
#define _wpgmptr _wpgmptr
#else /* .... */
#ifndef ____p__wpgmptr_defined
#define ____p__wpgmptr_defined 1
#ifdef __CRT_HAVE___p__wpgmptr
__CDECLARE(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,wchar_t **,__NOTHROW_NCX,__p__wpgmptr,(void),())
#else /* LIBC: __p__wpgmptr */
#undef ____p__wpgmptr_defined
#endif /* __p__wpgmptr... */
#endif /* !____p__wpgmptr_defined */
#ifdef ____p__wpgmptr_defined
#define _wpgmptr (*__p__wpgmptr())
#endif /* ____p__wpgmptr_defined */
#endif /* !... */
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
#else /* LIBC: __p__pgmptr */
#undef ____p__pgmptr_defined
#endif /* __p__pgmptr... */
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
#else /* .... */
#ifndef ____p___initenv_defined
#define ____p___initenv_defined 1
#ifdef __CRT_HAVE___p___initenv
/* Access to the initial environment block */
__CDECLARE(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,char ***,__NOTHROW_NCX,__p___initenv,(void),())
#else /* LIBC: __p___initenv */
#undef ____p___initenv_defined
#endif /* __p___initenv... */
#endif /* !____p___initenv_defined */
#ifdef ____p___initenv_defined
#define __initenv (*__p___initenv())
#endif /* ____p___initenv_defined */
#endif /* !... */
#endif /* !__initenv */
#ifndef __winitenv
#ifdef __CRT_HAVE___winitenv
__LIBC wchar_t **__winitenv;
#else /* .... */
#ifndef ____p___winitenv_defined
#define ____p___winitenv_defined 1
#ifdef __CRT_HAVE___p___winitenv
/* Access to the initial environment block */
__CDECLARE(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,wchar_t ***,__NOTHROW_NCX,__p___winitenv,(void),())
#else /* LIBC: __p___winitenv */
#undef ____p___winitenv_defined
#endif /* __p___winitenv... */
#endif /* !____p___winitenv_defined */
#ifdef ____p___winitenv_defined
#define __winitenv (*__p___winitenv())
#endif /* ____p___winitenv_defined */
#endif /* !... */
#endif /* !__winitenv */
#endif /* __USE_KOS */

#ifndef _countof
#define _countof(a) __COMPILER_LENOF(a)
#endif /* !_countof */

#ifdef __INT64_TYPE__
#ifdef _MSC_VER
extern __ATTR_CONST __INT64_TYPE__ (__LIBCCALL _abs64)(__INT64_TYPE__ __x);
#pragma intrinsic(_abs64)
#else /* _MSC_VER */
#ifdef __CRT_HAVE__abs64
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__INT64_TYPE__,__NOTHROW,_abs64,(__INT64_TYPE__ __x),(__x))
#elif defined(__CRT_HAVE_llabs) && (__SIZEOF_LONG_LONG__ == 8)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__INT64_TYPE__,__NOTHROW,_abs64,(__INT64_TYPE__ __x),llabs,(__x))
#elif defined(__CRT_HAVE_imaxabs) && (__SIZEOF_INTMAX_T__ == 8)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__INT64_TYPE__,__NOTHROW,_abs64,(__INT64_TYPE__ __x),imaxabs,(__x))
#elif defined(__CRT_HAVE_abs) && (__SIZEOF_INT__ == 8)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__INT64_TYPE__,__NOTHROW,_abs64,(__INT64_TYPE__ __x),abs,(__x))
#else /* LIBC: _abs64 */
#include <local/stdlib/_abs64.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_abs64, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __INT64_TYPE__ __NOTHROW(__LIBCCALL _abs64)(__INT64_TYPE__ __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_abs64))(__x); })
#endif /* _abs64... */
#endif /* !_MSC_VER */
#endif /* __INT64_TYPE__ */
#ifndef __NO_FPU
#ifdef __CRT_HAVE__atof_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),double,__NOTHROW_NCX,_atof_l,(char const *__restrict __nptr, __locale_t __locale),(__nptr,__locale))
#else /* LIBC: _atof_l */
#include <local/stdlib/_atof_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_atof_l, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) double __NOTHROW_NCX(__LIBCCALL _atof_l)(char const *__restrict __nptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_atof_l))(__nptr, __locale); })
#endif /* _atof_l... */
#endif /* !__NO_FPU */
#ifdef __CRT_HAVE__atoi_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,_atoi_l,(char const *__restrict __nptr, __locale_t __locale),(__nptr,__locale))
#else /* LIBC: _atoi_l */
#include <local/stdlib/_atoi_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_atoi_l, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL _atoi_l)(char const *__restrict __nptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_atoi_l))(__nptr, __locale); })
#endif /* _atoi_l... */
#ifdef __CRT_HAVE__atol_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),long int,__NOTHROW_NCX,_atol_l,(char const *__restrict __nptr, __locale_t __locale),(__nptr,__locale))
#else /* LIBC: _atol_l */
#include <local/stdlib/_atol_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_atol_l, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) long int __NOTHROW_NCX(__LIBCCALL _atol_l)(char const *__restrict __nptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_atol_l))(__nptr, __locale); })
#endif /* _atol_l... */
#ifdef __LONGLONG
#ifdef __CRT_HAVE__atoll_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,_atoll_l,(char const *__restrict __nptr, __locale_t __locale),(__nptr,__locale))
#else /* LIBC: _atoll_l */
#include <local/stdlib/_atoll_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_atoll_l, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __LONGLONG __NOTHROW_NCX(__LIBCCALL _atoll_l)(char const *__restrict __nptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_atoll_l))(__nptr, __locale); })
#endif /* _atoll_l... */
#endif /* __LONGLONG */

#ifdef _MSC_VER
extern unsigned short (_byteswap_ushort)(unsigned short x);
extern unsigned long (_byteswap_ulong)(unsigned long x);
extern unsigned __int64 (_byteswap_uint64)(unsigned __int64 x);
#pragma intrinsic(_byteswap_ushort)
#pragma intrinsic(_byteswap_ulong)
#pragma intrinsic(_byteswap_uint64)
#else /* _MSC_VER */
#ifdef __CRT_HAVE__byteswap_ushort
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__UINT16_TYPE__,__NOTHROW_NCX,_byteswap_ushort,(__UINT16_TYPE__ __val),(__val))
#else /* LIBC: _byteswap_ushort */
#include <local/stdlib/_byteswap_ushort.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_byteswap_ushort, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __UINT16_TYPE__ __NOTHROW_NCX(__LIBCCALL _byteswap_ushort)(__UINT16_TYPE__ __val) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_byteswap_ushort))(__val); })
#endif /* _byteswap_ushort... */
#ifdef __CRT_HAVE__byteswap_ulong
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__UINT32_TYPE__,__NOTHROW_NCX,_byteswap_ulong,(__UINT32_TYPE__ __val),(__val))
#else /* LIBC: _byteswap_ulong */
#include <local/stdlib/_byteswap_ulong.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_byteswap_ulong, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __UINT32_TYPE__ __NOTHROW_NCX(__LIBCCALL _byteswap_ulong)(__UINT32_TYPE__ __val) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_byteswap_ulong))(__val); })
#endif /* _byteswap_ulong... */
#ifdef __UINT64_TYPE__
#ifdef __CRT_HAVE__byteswap_uint64
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__UINT64_TYPE__,__NOTHROW_NCX,_byteswap_uint64,(__UINT64_TYPE__ __val),(__val))
#else /* LIBC: _byteswap_uint64 */
#include <local/stdlib/_byteswap_uint64.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_byteswap_uint64, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __UINT64_TYPE__ __NOTHROW_NCX(__LIBCCALL _byteswap_uint64)(__UINT64_TYPE__ __val) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_byteswap_uint64))(__val); })
#endif /* _byteswap_uint64... */
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
typedef int (__LIBCCALL *__dos_compar_d_fn_t)(void *__arg, void const *__a, void const *__b);
#endif /* !__dos_compar_d_fn_t_defined */
#ifdef __CRT_HAVE_bsearch_s
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 2, 5)),void *,__NOTHROW_NCX,bsearch_s,(void const *__key, void const *__base, __SIZE_TYPE__ __nmemb, __SIZE_TYPE__ __size, __dos_compar_d_fn_t __compar, void *__arg),(__key,__base,__nmemb,__size,__compar,__arg))
#else /* LIBC: bsearch_s */
#include <local/stdlib/bsearch_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(bsearch_s, __FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((1, 2, 5)) void *__NOTHROW_NCX(__LIBCCALL bsearch_s)(void const *__key, void const *__base, __SIZE_TYPE__ __nmemb, __SIZE_TYPE__ __size, __dos_compar_d_fn_t __compar, void *__arg) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(bsearch_s))(__key, __base, __nmemb, __size, __compar, __arg); })
#endif /* bsearch_s... */
#ifdef __CRT_HAVE_qsort_s
__CDECLARE_VOID(__ATTR_NONNULL((1, 4)),__NOTHROW_NCX,qsort_s,(void *__base, __SIZE_TYPE__ __nmemb, __SIZE_TYPE__ __size, __dos_compar_d_fn_t __compar, void *__arg),(__base,__nmemb,__size,__compar,__arg))
#else /* LIBC: qsort_s */
#include <local/stdlib/qsort_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(qsort_s, __FORCELOCAL __ATTR_NONNULL((1, 4)) void __NOTHROW_NCX(__LIBCCALL qsort_s)(void *__base, __SIZE_TYPE__ __nmemb, __SIZE_TYPE__ __size, __dos_compar_d_fn_t __compar, void *__arg) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(qsort_s))(__base, __nmemb, __size, __compar, __arg); })
#endif /* qsort_s... */
#endif  /* _CRT_ALGO_DEFINED */

#ifdef __CRT_HAVE_getenv_s
__CDECLARE(__ATTR_NONNULL((1, 2, 4)),errno_t,__NOTHROW_NCX,getenv_s,(__SIZE_TYPE__ *__psize, char *__buf, rsize_t __bufsize, char const *__varname),(__psize,__buf,__bufsize,__varname))
#endif /* getenv_s... */
#ifdef __CRT_HAVE__dupenv_s
__CDECLARE(__ATTR_NONNULL((1, 2, 3)),errno_t,__NOTHROW_NCX,_dupenv_s,(char **__restrict __pbuf, __SIZE_TYPE__ *__pbuflen, char const *__varname),(__pbuf,__pbuflen,__varname))
#endif /* _dupenv_s... */
#endif /* __USE_DOS_SLIB */

#ifdef __CRT_HAVE__itoa
__CDECLARE(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,_itoa,(int __val, char *__buf, int __radix),(__val,__buf,__radix))
#elif defined(__CRT_HAVE_itoa)
__CREDIRECT(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,_itoa,(int __val, char *__buf, int __radix),itoa,(__val,__buf,__radix))
#elif defined(__CRT_HAVE__ltoa) && (__SIZEOF_INT__ == __SIZEOF_LONG__)
__CREDIRECT(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,_itoa,(int __val, char *__buf, int __radix),_ltoa,(__val,__buf,__radix))
#elif defined(__CRT_HAVE_ltoa) && (__SIZEOF_INT__ == __SIZEOF_LONG__)
__CREDIRECT(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,_itoa,(int __val, char *__buf, int __radix),ltoa,(__val,__buf,__radix))
#elif defined(__CRT_HAVE__i64toa) && (__SIZEOF_INT__ == 8)
__CREDIRECT(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,_itoa,(int __val, char *__buf, int __radix),_i64toa,(__val,__buf,__radix))
#elif defined(__CRT_HAVE_i64toa) && (__SIZEOF_INT__ == 8)
__CREDIRECT(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,_itoa,(int __val, char *__buf, int __radix),i64toa,(__val,__buf,__radix))
#else /* LIBC: itoa */
#include <local/stdlib/itoa.h>
__FORCELOCAL __ATTR_NONNULL((2)) char *__NOTHROW_NCX(__LIBCCALL _itoa)(int __val, char *__buf, int __radix) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(itoa))(__val, __buf, __radix); }
#endif /* _itoa... */
#ifdef __CRT_HAVE__ltoa
__CDECLARE(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,_ltoa,(long __val, char *__buf, int __radix),(__val,__buf,__radix))
#elif defined(__CRT_HAVE_ltoa)
__CREDIRECT(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,_ltoa,(long __val, char *__buf, int __radix),ltoa,(__val,__buf,__radix))
#elif defined(__CRT_HAVE__itoa) && (__SIZEOF_LONG__ == __SIZEOF_INT__)
__CREDIRECT(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,_ltoa,(long __val, char *__buf, int __radix),_itoa,(__val,__buf,__radix))
#elif defined(__CRT_HAVE_itoa) && (__SIZEOF_LONG__ == __SIZEOF_INT__)
__CREDIRECT(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,_ltoa,(long __val, char *__buf, int __radix),itoa,(__val,__buf,__radix))
#elif defined(__CRT_HAVE__i64toa) && (__SIZEOF_LONG__ == 8)
__CREDIRECT(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,_ltoa,(long __val, char *__buf, int __radix),_i64toa,(__val,__buf,__radix))
#elif defined(__CRT_HAVE_i64toa) && (__SIZEOF_LONG__ == 8)
__CREDIRECT(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,_ltoa,(long __val, char *__buf, int __radix),i64toa,(__val,__buf,__radix))
#else /* LIBC: ltoa */
#include <local/stdlib/ltoa.h>
__FORCELOCAL __ATTR_NONNULL((2)) char *__NOTHROW_NCX(__LIBCCALL _ltoa)(long __val, char *__buf, int __radix) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ltoa))(__val, __buf, __radix); }
#endif /* _ltoa... */
#ifdef __CRT_HAVE__ultoa
__CDECLARE(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,_ultoa,(unsigned long __val, char *__buf, int __radix),(__val,__buf,__radix))
#elif defined(__CRT_HAVE_ultoa)
__CREDIRECT(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,_ultoa,(unsigned long __val, char *__buf, int __radix),ultoa,(__val,__buf,__radix))
#elif defined(__CRT_HAVE__ui64toa) && (__SIZEOF_LONG__ == 8)
__CREDIRECT(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,_ultoa,(unsigned long __val, char *__buf, int __radix),_ui64toa,(__val,__buf,__radix))
#elif defined(__CRT_HAVE_ui64toa) && (__SIZEOF_LONG__ == 8)
__CREDIRECT(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,_ultoa,(unsigned long __val, char *__buf, int __radix),ui64toa,(__val,__buf,__radix))
#else /* LIBC: ultoa */
#include <local/stdlib/ultoa.h>
__FORCELOCAL __ATTR_NONNULL((2)) char *__NOTHROW_NCX(__LIBCCALL _ultoa)(unsigned long __val, char *__buf, int __radix) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ultoa))(__val, __buf, __radix); }
#endif /* _ultoa... */
#ifdef __CRT_HAVE__itoa_s
__CDECLARE(__ATTR_NONNULL((2)),errno_t,__NOTHROW_NCX,_itoa_s,(int __val, char *__buf, __SIZE_TYPE__ __bufsize, int __radix),(__val,__buf,__bufsize,__radix))
#elif defined(__CRT_HAVE_itoa_s)
__CREDIRECT(__ATTR_NONNULL((2)),errno_t,__NOTHROW_NCX,_itoa_s,(int __val, char *__buf, __SIZE_TYPE__ __bufsize, int __radix),itoa_s,(__val,__buf,__bufsize,__radix))
#elif defined(__CRT_HAVE__ltoa_s) && (__SIZEOF_INT__ == __SIZEOF_LONG__)
__CREDIRECT(__ATTR_NONNULL((2)),errno_t,__NOTHROW_NCX,_itoa_s,(int __val, char *__buf, __SIZE_TYPE__ __bufsize, int __radix),_ltoa_s,(__val,__buf,__bufsize,__radix))
#elif defined(__CRT_HAVE_ltoa_s) && (__SIZEOF_INT__ == __SIZEOF_LONG__)
__CREDIRECT(__ATTR_NONNULL((2)),errno_t,__NOTHROW_NCX,_itoa_s,(int __val, char *__buf, __SIZE_TYPE__ __bufsize, int __radix),ltoa_s,(__val,__buf,__bufsize,__radix))
#elif defined(__CRT_HAVE__i64toa_s) && (__SIZEOF_INT__ == 8)
__CREDIRECT(__ATTR_NONNULL((2)),errno_t,__NOTHROW_NCX,_itoa_s,(int __val, char *__buf, __SIZE_TYPE__ __bufsize, int __radix),_i64toa_s,(__val,__buf,__bufsize,__radix))
#elif defined(__CRT_HAVE_i64toa_s) && (__SIZEOF_INT__ == 8)
__CREDIRECT(__ATTR_NONNULL((2)),errno_t,__NOTHROW_NCX,_itoa_s,(int __val, char *__buf, __SIZE_TYPE__ __bufsize, int __radix),i64toa_s,(__val,__buf,__bufsize,__radix))
#else /* LIBC: _itoa_s */
#include <local/stdlib/_itoa_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_itoa_s, __FORCELOCAL __ATTR_NONNULL((2)) errno_t __NOTHROW_NCX(__LIBCCALL _itoa_s)(int __val, char *__buf, __SIZE_TYPE__ __bufsize, int __radix) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_itoa_s))(__val, __buf, __bufsize, __radix); })
#endif /* _itoa_s... */
#ifdef __CRT_HAVE__ltoa_s
__CDECLARE(__ATTR_NONNULL((2)),errno_t,__NOTHROW_NCX,_ltoa_s,(long __val, char *__buf, __SIZE_TYPE__ __bufsize, int __radix),(__val,__buf,__bufsize,__radix))
#elif defined(__CRT_HAVE_ltoa_s)
__CREDIRECT(__ATTR_NONNULL((2)),errno_t,__NOTHROW_NCX,_ltoa_s,(long __val, char *__buf, __SIZE_TYPE__ __bufsize, int __radix),ltoa_s,(__val,__buf,__bufsize,__radix))
#elif defined(__CRT_HAVE__itoa_s) && (__SIZEOF_LONG__ == __SIZEOF_INT__)
__CREDIRECT(__ATTR_NONNULL((2)),errno_t,__NOTHROW_NCX,_ltoa_s,(long __val, char *__buf, __SIZE_TYPE__ __bufsize, int __radix),_itoa_s,(__val,__buf,__bufsize,__radix))
#elif defined(__CRT_HAVE_itoa_s) && (__SIZEOF_LONG__ == __SIZEOF_INT__)
__CREDIRECT(__ATTR_NONNULL((2)),errno_t,__NOTHROW_NCX,_ltoa_s,(long __val, char *__buf, __SIZE_TYPE__ __bufsize, int __radix),itoa_s,(__val,__buf,__bufsize,__radix))
#elif defined(__CRT_HAVE__i64toa_s) && (__SIZEOF_LONG__ == 8)
__CREDIRECT(__ATTR_NONNULL((2)),errno_t,__NOTHROW_NCX,_ltoa_s,(long __val, char *__buf, __SIZE_TYPE__ __bufsize, int __radix),_i64toa_s,(__val,__buf,__bufsize,__radix))
#elif defined(__CRT_HAVE_i64toa_s) && (__SIZEOF_LONG__ == 8)
__CREDIRECT(__ATTR_NONNULL((2)),errno_t,__NOTHROW_NCX,_ltoa_s,(long __val, char *__buf, __SIZE_TYPE__ __bufsize, int __radix),i64toa_s,(__val,__buf,__bufsize,__radix))
#else /* LIBC: _ltoa_s */
#include <local/stdlib/_ltoa_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_ltoa_s, __FORCELOCAL __ATTR_NONNULL((2)) errno_t __NOTHROW_NCX(__LIBCCALL _ltoa_s)(long __val, char *__buf, __SIZE_TYPE__ __bufsize, int __radix) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_ltoa_s))(__val, __buf, __bufsize, __radix); })
#endif /* _ltoa_s... */
#ifdef __CRT_HAVE__ultoa_s
__CDECLARE(__ATTR_NONNULL((2)),errno_t,__NOTHROW_NCX,_ultoa_s,(unsigned long __val, char *__buf, __SIZE_TYPE__ __bufsize, int __radix),(__val,__buf,__bufsize,__radix))
#elif defined(__CRT_HAVE_ultoa_s)
__CREDIRECT(__ATTR_NONNULL((2)),errno_t,__NOTHROW_NCX,_ultoa_s,(unsigned long __val, char *__buf, __SIZE_TYPE__ __bufsize, int __radix),ultoa_s,(__val,__buf,__bufsize,__radix))
#elif defined(__CRT_HAVE__ui64toa_s) && (__SIZEOF_LONG__ == 8)
__CREDIRECT(__ATTR_NONNULL((2)),errno_t,__NOTHROW_NCX,_ultoa_s,(unsigned long __val, char *__buf, __SIZE_TYPE__ __bufsize, int __radix),_ui64toa_s,(__val,__buf,__bufsize,__radix))
#elif defined(__CRT_HAVE_ui64toa_s) && (__SIZEOF_LONG__ == 8)
__CREDIRECT(__ATTR_NONNULL((2)),errno_t,__NOTHROW_NCX,_ultoa_s,(unsigned long __val, char *__buf, __SIZE_TYPE__ __bufsize, int __radix),ui64toa_s,(__val,__buf,__bufsize,__radix))
#else /* LIBC: _ultoa_s */
#include <local/stdlib/_ultoa_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_ultoa_s, __FORCELOCAL __ATTR_NONNULL((2)) errno_t __NOTHROW_NCX(__LIBCCALL _ultoa_s)(unsigned long __val, char *__buf, __SIZE_TYPE__ __bufsize, int __radix) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_ultoa_s))(__val, __buf, __bufsize, __radix); })
#endif /* _ultoa_s... */

#ifdef __UINT64_TYPE__
#ifdef __CRT_HAVE__i64toa
__CDECLARE(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,_i64toa,(__INT64_TYPE__ __val, char *__buf, int __radix),(__val,__buf,__radix))
#elif defined(__CRT_HAVE_i64toa)
__CREDIRECT(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,_i64toa,(__INT64_TYPE__ __val, char *__buf, int __radix),i64toa,(__val,__buf,__radix))
#elif defined(__CRT_HAVE__ltoa) && (__SIZEOF_LONG__ == 8)
__CREDIRECT(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,_i64toa,(__INT64_TYPE__ __val, char *__buf, int __radix),_ltoa,(__val,__buf,__radix))
#elif defined(__CRT_HAVE_ltoa) && (__SIZEOF_LONG__ == 8)
__CREDIRECT(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,_i64toa,(__INT64_TYPE__ __val, char *__buf, int __radix),ltoa,(__val,__buf,__radix))
#elif defined(__CRT_HAVE__itoa) && (__SIZEOF_INT__ == 8)
__CREDIRECT(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,_i64toa,(__INT64_TYPE__ __val, char *__buf, int __radix),_itoa,(__val,__buf,__radix))
#elif defined(__CRT_HAVE_itoa) && (__SIZEOF_INT__ == 8)
__CREDIRECT(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,_i64toa,(__INT64_TYPE__ __val, char *__buf, int __radix),itoa,(__val,__buf,__radix))
#else /* LIBC: _i64toa */
#include <local/stdlib/_i64toa.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_i64toa, __FORCELOCAL __ATTR_NONNULL((2)) char *__NOTHROW_NCX(__LIBCCALL _i64toa)(__INT64_TYPE__ __val, char *__buf, int __radix) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_i64toa))(__val, __buf, __radix); })
#endif /* _i64toa... */
#ifdef __CRT_HAVE__ui64toa
__CDECLARE(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,_ui64toa,(__UINT64_TYPE__ __val, char *__buf, int __radix),(__val,__buf,__radix))
#elif defined(__CRT_HAVE_ui64toa)
__CREDIRECT(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,_ui64toa,(__UINT64_TYPE__ __val, char *__buf, int __radix),ui64toa,(__val,__buf,__radix))
#elif defined(__CRT_HAVE__ultoa) && (__SIZEOF_LONG__ == 8)
__CREDIRECT(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,_ui64toa,(__UINT64_TYPE__ __val, char *__buf, int __radix),_ultoa,(__val,__buf,__radix))
#elif defined(__CRT_HAVE_ultoa) && (__SIZEOF_LONG__ == 8)
__CREDIRECT(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,_ui64toa,(__UINT64_TYPE__ __val, char *__buf, int __radix),ultoa,(__val,__buf,__radix))
#else /* LIBC: _ui64toa */
#include <local/stdlib/_ui64toa.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_ui64toa, __FORCELOCAL __ATTR_NONNULL((2)) char *__NOTHROW_NCX(__LIBCCALL _ui64toa)(__UINT64_TYPE__ __val, char *__buf, int __radix) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_ui64toa))(__val, __buf, __radix); })
#endif /* _ui64toa... */
#ifdef __CRT_HAVE__i64toa_s
__CDECLARE(__ATTR_NONNULL((2)),errno_t,__NOTHROW_NCX,_i64toa_s,(__INT64_TYPE__ __val, char *__buf, __SIZE_TYPE__ __bufsize, int __radix),(__val,__buf,__bufsize,__radix))
#elif defined(__CRT_HAVE_i64toa_s)
__CREDIRECT(__ATTR_NONNULL((2)),errno_t,__NOTHROW_NCX,_i64toa_s,(__INT64_TYPE__ __val, char *__buf, __SIZE_TYPE__ __bufsize, int __radix),i64toa_s,(__val,__buf,__bufsize,__radix))
#elif defined(__CRT_HAVE__ltoa_s) && (__SIZEOF_LONG__ == 8)
__CREDIRECT(__ATTR_NONNULL((2)),errno_t,__NOTHROW_NCX,_i64toa_s,(__INT64_TYPE__ __val, char *__buf, __SIZE_TYPE__ __bufsize, int __radix),_ltoa_s,(__val,__buf,__bufsize,__radix))
#elif defined(__CRT_HAVE_ltoa_s) && (__SIZEOF_LONG__ == 8)
__CREDIRECT(__ATTR_NONNULL((2)),errno_t,__NOTHROW_NCX,_i64toa_s,(__INT64_TYPE__ __val, char *__buf, __SIZE_TYPE__ __bufsize, int __radix),ltoa_s,(__val,__buf,__bufsize,__radix))
#elif defined(__CRT_HAVE__itoa_s) && (__SIZEOF_INT__ == 8)
__CREDIRECT(__ATTR_NONNULL((2)),errno_t,__NOTHROW_NCX,_i64toa_s,(__INT64_TYPE__ __val, char *__buf, __SIZE_TYPE__ __bufsize, int __radix),_itoa_s,(__val,__buf,__bufsize,__radix))
#elif defined(__CRT_HAVE_itoa_s) && (__SIZEOF_INT__ == 8)
__CREDIRECT(__ATTR_NONNULL((2)),errno_t,__NOTHROW_NCX,_i64toa_s,(__INT64_TYPE__ __val, char *__buf, __SIZE_TYPE__ __bufsize, int __radix),itoa_s,(__val,__buf,__bufsize,__radix))
#else /* LIBC: _i64toa_s */
#include <local/stdlib/_i64toa_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_i64toa_s, __FORCELOCAL __ATTR_NONNULL((2)) errno_t __NOTHROW_NCX(__LIBCCALL _i64toa_s)(__INT64_TYPE__ __val, char *__buf, __SIZE_TYPE__ __bufsize, int __radix) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_i64toa_s))(__val, __buf, __bufsize, __radix); })
#endif /* _i64toa_s... */
#ifdef __CRT_HAVE__ui64toa_s
__CDECLARE(__ATTR_NONNULL((2)),errno_t,__NOTHROW_NCX,_ui64toa_s,(__UINT64_TYPE__ __val, char *__buf, __SIZE_TYPE__ __bufsize, int __radix),(__val,__buf,__bufsize,__radix))
#elif defined(__CRT_HAVE_ui64toa_s)
__CREDIRECT(__ATTR_NONNULL((2)),errno_t,__NOTHROW_NCX,_ui64toa_s,(__UINT64_TYPE__ __val, char *__buf, __SIZE_TYPE__ __bufsize, int __radix),ui64toa_s,(__val,__buf,__bufsize,__radix))
#elif defined(__CRT_HAVE__ultoa_s) && (__SIZEOF_LONG__ == 8)
__CREDIRECT(__ATTR_NONNULL((2)),errno_t,__NOTHROW_NCX,_ui64toa_s,(__UINT64_TYPE__ __val, char *__buf, __SIZE_TYPE__ __bufsize, int __radix),_ultoa_s,(__val,__buf,__bufsize,__radix))
#elif defined(__CRT_HAVE_ultoa_s) && (__SIZEOF_LONG__ == 8)
__CREDIRECT(__ATTR_NONNULL((2)),errno_t,__NOTHROW_NCX,_ui64toa_s,(__UINT64_TYPE__ __val, char *__buf, __SIZE_TYPE__ __bufsize, int __radix),ultoa_s,(__val,__buf,__bufsize,__radix))
#else /* LIBC: _ui64toa_s */
#include <local/stdlib/_ui64toa_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_ui64toa_s, __FORCELOCAL __ATTR_NONNULL((2)) errno_t __NOTHROW_NCX(__LIBCCALL _ui64toa_s)(__UINT64_TYPE__ __val, char *__buf, __SIZE_TYPE__ __bufsize, int __radix) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_ui64toa_s))(__val, __buf, __bufsize, __radix); })
#endif /* _ui64toa_s... */
#ifdef __CRT_HAVE__strtoi64
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_strtoi64,(char const *__restrict __nptr, char **__endptr, int __radix),(__nptr,__endptr,__radix))
#elif defined(__CRT_HAVE_strto64)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_strtoi64,(char const *__restrict __nptr, char **__endptr, int __radix),strto64,(__nptr,__endptr,__radix))
#elif defined(__CRT_HAVE_strtol) && (__SIZEOF_LONG__ == 8)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_strtoi64,(char const *__restrict __nptr, char **__endptr, int __radix),strtol,(__nptr,__endptr,__radix))
#elif defined(__CRT_HAVE_strtoll) && (__SIZEOF_LONG_LONG__ == 8)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_strtoi64,(char const *__restrict __nptr, char **__endptr, int __radix),strtoll,(__nptr,__endptr,__radix))
#elif defined(__CRT_HAVE_strtoq) && (__SIZEOF_LONG_LONG__ == 8)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_strtoi64,(char const *__restrict __nptr, char **__endptr, int __radix),strtoq,(__nptr,__endptr,__radix))
#elif defined(__CRT_HAVE_strtoimax) && (__SIZEOF_INTMAX_T__ == 8)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_strtoi64,(char const *__restrict __nptr, char **__endptr, int __radix),strtoimax,(__nptr,__endptr,__radix))
#else /* LIBC: strto64 */
#include <local/stdlib/strto64.h>
__FORCELOCAL __ATTR_LEAF __ATTR_NONNULL((1)) __INT64_TYPE__ __NOTHROW_NCX(__LIBCCALL _strtoi64)(char const *__restrict __nptr, char **__endptr, int __radix) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strto64))(__nptr, __endptr, __radix); }
#endif /* _strtoi64... */
#ifdef __CRT_HAVE__strtoui64
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,_strtoui64,(char const *__restrict __nptr, char **__endptr, int __radix),(__nptr,__endptr,__radix))
#elif defined(__CRT_HAVE_strtou64)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,_strtoui64,(char const *__restrict __nptr, char **__endptr, int __radix),strtou64,(__nptr,__endptr,__radix))
#elif defined(__CRT_HAVE_strtoul) && (__SIZEOF_LONG__ == 8)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,_strtoui64,(char const *__restrict __nptr, char **__endptr, int __radix),strtoul,(__nptr,__endptr,__radix))
#elif defined(__CRT_HAVE_strtoll) && (__SIZEOF_LONG_LONG__ == 8)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,_strtoui64,(char const *__restrict __nptr, char **__endptr, int __radix),strtoll,(__nptr,__endptr,__radix))
#elif defined(__CRT_HAVE_strtouq) && (__SIZEOF_LONG_LONG__ == 8)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,_strtoui64,(char const *__restrict __nptr, char **__endptr, int __radix),strtouq,(__nptr,__endptr,__radix))
#elif defined(__CRT_HAVE_strtoumax) && (__SIZEOF_INTMAX_T__ == 8)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,_strtoui64,(char const *__restrict __nptr, char **__endptr, int __radix),strtoumax,(__nptr,__endptr,__radix))
#else /* LIBC: strtou64 */
#include <local/stdlib/strtou64.h>
__FORCELOCAL __ATTR_LEAF __ATTR_NONNULL((1)) __UINT64_TYPE__ __NOTHROW_NCX(__LIBCCALL _strtoui64)(char const *__restrict __nptr, char **__endptr, int __radix) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtou64))(__nptr, __endptr, __radix); }
#endif /* _strtoui64... */
#ifdef __CRT_HAVE__strtoi64_l
__CDECLARE(__ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_strtoi64_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strto64_l)
__CREDIRECT(__ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_strtoi64_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),strto64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtol_l) && (__SIZEOF_LONG__ == 8)
__CREDIRECT(__ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_strtoi64_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),_strtol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtol_l) && (__SIZEOF_LONG__ == 8)
__CREDIRECT(__ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_strtoi64_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),strtol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtoll_l) && (__SIZEOF_LONG_LONG__ == 8)
__CREDIRECT(__ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_strtoi64_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),strtoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoll_l) && (__SIZEOF_LONG_LONG__ == 8)
__CREDIRECT(__ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_strtoi64_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),_strtoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtoq_l) && (__SIZEOF_LONG_LONG__ == 8)
__CREDIRECT(__ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_strtoi64_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),strtoq_l,(__nptr,__endptr,__base,__locale))
#else /* LIBC: strto64_l */
#include <local/stdlib/strto64_l.h>
__FORCELOCAL __ATTR_NONNULL((1)) __INT64_TYPE__ __NOTHROW_NCX(__LIBCCALL _strtoi64_l)(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strto64_l))(__nptr, __endptr, __base, __locale); }
#endif /* _strtoi64_l... */
#ifdef __CRT_HAVE__strtoui64_l
__CDECLARE(__ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,_strtoui64_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtou64_l)
__CREDIRECT(__ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,_strtoui64_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),strtou64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoul_l) && (__SIZEOF_LONG__ == 8)
__CREDIRECT(__ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,_strtoui64_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),_strtoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtoul_l) && (__SIZEOF_LONG__ == 8)
__CREDIRECT(__ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,_strtoui64_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),strtoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtoull_l) && (__SIZEOF_LONG_LONG__ == 8)
__CREDIRECT(__ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,_strtoui64_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),strtoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoull_l) && (__SIZEOF_LONG_LONG__ == 8)
__CREDIRECT(__ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,_strtoui64_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),_strtoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtouq_l) && (__SIZEOF_LONG_LONG__ == 8)
__CREDIRECT(__ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,_strtoui64_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),strtouq_l,(__nptr,__endptr,__base,__locale))
#else /* LIBC: strtou64_l */
#include <local/stdlib/strtou64_l.h>
__FORCELOCAL __ATTR_NONNULL((1)) __UINT64_TYPE__ __NOTHROW_NCX(__LIBCCALL _strtoui64_l)(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtou64_l))(__nptr, __endptr, __base, __locale); }
#endif /* _strtoui64_l... */
#ifdef __CRT_HAVE__atoi64
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_atoi64,(char const *__restrict __nptr),(__nptr))
#else /* LIBC: _atoi64 */
#include <local/stdlib/_atoi64.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_atoi64, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __INT64_TYPE__ __NOTHROW_NCX(__LIBCCALL _atoi64)(char const *__restrict __nptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_atoi64))(__nptr); })
#endif /* _atoi64... */
#ifdef __CRT_HAVE__atoi64_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_atoi64_l,(char const *__restrict __nptr, __locale_t __locale),(__nptr,__locale))
#else /* LIBC: _atoi64_l */
#include <local/stdlib/_atoi64_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_atoi64_l, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __INT64_TYPE__ __NOTHROW_NCX(__LIBCCALL _atoi64_l)(char const *__restrict __nptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_atoi64_l))(__nptr, __locale); })
#endif /* _atoi64_l... */
#endif /* __UINT64_TYPE__ */
#ifdef __CRT_HAVE__mbstrlen
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,_mbstrlen,(char const *__str),(__str))
#else /* LIBC: _mbstrlen */
#include <local/stdlib/_mbstrlen.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_mbstrlen, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL _mbstrlen)(char const *__str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_mbstrlen))(__str); })
#endif /* _mbstrlen... */
#ifdef __CRT_HAVE__mbstrnlen
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,_mbstrnlen,(char const *__str, __SIZE_TYPE__ __maxlen),(__str,__maxlen))
#else /* LIBC: _mbstrnlen */
#include <local/stdlib/_mbstrnlen.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_mbstrnlen, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL _mbstrnlen)(char const *__str, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_mbstrnlen))(__str, __maxlen); })
#endif /* _mbstrnlen... */
#ifdef __CRT_HAVE__mbstrlen_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,_mbstrlen_l,(char const *__str, __locale_t __locale),(__str,__locale))
#else /* LIBC: _mbstrlen_l */
#include <local/stdlib/_mbstrlen_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_mbstrlen_l, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL _mbstrlen_l)(char const *__str, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_mbstrlen_l))(__str, __locale); })
#endif /* _mbstrlen_l... */
#ifdef __CRT_HAVE__mbstrnlen_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,_mbstrnlen_l,(char const *__str, __SIZE_TYPE__ __maxlen, __locale_t __locale),(__str,__maxlen,__locale))
#else /* LIBC: _mbstrnlen_l */
#include <local/stdlib/_mbstrnlen_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_mbstrnlen_l, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL _mbstrnlen_l)(char const *__str, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_mbstrnlen_l))(__str, __maxlen, __locale); })
#endif /* _mbstrnlen_l... */
#ifdef __CRT_HAVE__mblen_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,_mblen_l,(char const *__str, __SIZE_TYPE__ __maxlen, __locale_t __locale),(__str,__maxlen,__locale))
#else /* LIBC: _mblen_l */
#include <local/stdlib/_mblen_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_mblen_l, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL _mblen_l)(char const *__str, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_mblen_l))(__str, __maxlen, __locale); })
#endif /* _mblen_l... */
#ifdef __CRT_HAVE__mbtowc_l
__CDECLARE(,int,__NOTHROW_NCX,_mbtowc_l,(wchar_t *__dst, char const *__src, __SIZE_TYPE__ __srclen, __locale_t __locale),(__dst,__src,__srclen,__locale))
#else /* LIBC: _mbtowc_l */
#include <local/stdlib/_mbtowc_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_mbtowc_l, __FORCELOCAL int __NOTHROW_NCX(__LIBCCALL _mbtowc_l)(wchar_t *__dst, char const *__src, __SIZE_TYPE__ __srclen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_mbtowc_l))(__dst, __src, __srclen, __locale); })
#endif /* _mbtowc_l... */
#ifdef __CRT_HAVE__mbstowcs_l
__CDECLARE(,__SIZE_TYPE__,__NOTHROW_NCX,_mbstowcs_l,(wchar_t *__dst, char const *__src, __SIZE_TYPE__ __dstlen, __locale_t __locale),(__dst,__src,__dstlen,__locale))
#else /* LIBC: _mbstowcs_l */
#include <local/stdlib/_mbstowcs_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_mbstowcs_l, __FORCELOCAL __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL _mbstowcs_l)(wchar_t *__dst, char const *__src, __SIZE_TYPE__ __dstlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_mbstowcs_l))(__dst, __src, __dstlen, __locale); })
#endif /* _mbstowcs_l... */
#ifdef __CRT_HAVE__mbstowcs_s
__CDECLARE(,errno_t,__NOTHROW_NCX,_mbstowcs_s,(__SIZE_TYPE__ *__presult, wchar_t *__dst, __SIZE_TYPE__ __dstsize, char const *__src, __SIZE_TYPE__ __dstlen),(__presult,__dst,__dstsize,__src,__dstlen))
#else /* LIBC: _mbstowcs_s */
#include <local/stdlib/_mbstowcs_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_mbstowcs_s, __FORCELOCAL errno_t __NOTHROW_NCX(__LIBCCALL _mbstowcs_s)(__SIZE_TYPE__ *__presult, wchar_t *__dst, __SIZE_TYPE__ __dstsize, char const *__src, __SIZE_TYPE__ __dstlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_mbstowcs_s))(__presult, __dst, __dstsize, __src, __dstlen); })
#endif /* _mbstowcs_s... */
#ifdef __CRT_HAVE__mbstowcs_s_l
__CDECLARE(,errno_t,__NOTHROW_NCX,_mbstowcs_s_l,(__SIZE_TYPE__ *__presult, wchar_t *__dst, __SIZE_TYPE__ __dstsize, char const *__src, __SIZE_TYPE__ __dstlen, __locale_t __locale),(__presult,__dst,__dstsize,__src,__dstlen,__locale))
#else /* LIBC: _mbstowcs_s_l */
#include <local/stdlib/_mbstowcs_s_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_mbstowcs_s_l, __FORCELOCAL errno_t __NOTHROW_NCX(__LIBCCALL _mbstowcs_s_l)(__SIZE_TYPE__ *__presult, wchar_t *__dst, __SIZE_TYPE__ __dstsize, char const *__src, __SIZE_TYPE__ __dstlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_mbstowcs_s_l))(__presult, __dst, __dstsize, __src, __dstlen, __locale); })
#endif /* _mbstowcs_s_l... */
#ifdef __CRT_HAVE_rand_s
__CDECLARE(__ATTR_NONNULL((1)),errno_t,__NOTHROW_NCX,rand_s,(unsigned int *__restrict __randval),(__randval))
#else /* LIBC: rand_s */
#include <local/stdlib/rand_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(rand_s, __FORCELOCAL __ATTR_NONNULL((1)) errno_t __NOTHROW_NCX(__LIBCCALL rand_s)(unsigned int *__restrict __randval) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rand_s))(__randval); })
#endif /* rand_s... */
#ifdef __CRT_HAVE__strtol_l
__CDECLARE(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,_strtol_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtol_l)
__CREDIRECT(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,_strtol_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),strtol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtoll_l) && (__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__)
__CREDIRECT(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,_strtol_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),strtoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoll_l) && (__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__)
__CREDIRECT(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,_strtol_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),_strtoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtoq_l) && (__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__)
__CREDIRECT(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,_strtol_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),strtoq_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strto32_l) && (__SIZEOF_LONG__ == 4)
__CREDIRECT(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,_strtol_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),strto32_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strto64_l) && (__SIZEOF_LONG__ == 8)
__CREDIRECT(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,_strtol_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),strto64_l,(__nptr,__endptr,__base,__locale))
#else /* LIBC: strtol_l */
#include <local/stdlib/strtol_l.h>
__FORCELOCAL __ATTR_NONNULL((1)) long __NOTHROW_NCX(__LIBCCALL _strtol_l)(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtol_l))(__nptr, __endptr, __base, __locale); }
#endif /* _strtol_l... */
#ifdef __CRT_HAVE__strtoul_l
__CDECLARE(__ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,_strtoul_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtoul_l)
__CREDIRECT(__ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,_strtoul_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),strtoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtoull_l) && (__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__)
__CREDIRECT(__ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,_strtoul_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),strtoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoull_l) && (__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__)
__CREDIRECT(__ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,_strtoul_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),_strtoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtouq_l) && (__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__)
__CREDIRECT(__ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,_strtoul_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),strtouq_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtou32_l) && (__SIZEOF_LONG__ == 4)
__CREDIRECT(__ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,_strtoul_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),strtou32_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtou64_l) && (__SIZEOF_LONG__ == 8)
__CREDIRECT(__ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,_strtoul_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),strtou64_l,(__nptr,__endptr,__base,__locale))
#else /* LIBC: strtoul_l */
#include <local/stdlib/strtoul_l.h>
__FORCELOCAL __ATTR_NONNULL((1)) unsigned long __NOTHROW_NCX(__LIBCCALL _strtoul_l)(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtoul_l))(__nptr, __endptr, __base, __locale); }
#endif /* _strtoul_l... */
#ifdef __CRT_HAVE__strtoll_l
__CDECLARE(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,_strtoll_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtoll_l)
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,_strtoll_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),strtoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtoq_l)
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,_strtoll_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),strtoq_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtol_l) && (__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__)
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,_strtoll_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),strtol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtol_l) && (__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__)
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,_strtoll_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),_strtol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strto64_l) && (__SIZEOF_LONG_LONG__ == 8)
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,_strtoll_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),strto64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strto32_l) && (__SIZEOF_LONG_LONG__ == 4)
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,_strtoll_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),strto32_l,(__nptr,__endptr,__base,__locale))
#else /* LIBC: strtoll_l */
#include <local/stdlib/strtoll_l.h>
__FORCELOCAL __ATTR_NONNULL((1)) __LONGLONG __NOTHROW_NCX(__LIBCCALL _strtoll_l)(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtoll_l))(__nptr, __endptr, __base, __locale); }
#endif /* _strtoll_l... */
#ifdef __CRT_HAVE__strtoull_l
__CDECLARE(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,_strtoull_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtoull_l)
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,_strtoull_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),strtoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtouq_l)
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,_strtoull_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),strtouq_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtoul_l) && (__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__)
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,_strtoull_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),strtoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoul_l) && (__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__)
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,_strtoull_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),_strtoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtou64_l) && (__SIZEOF_LONG_LONG__ == 8)
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,_strtoull_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),strtou64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtou32_l) && (__SIZEOF_LONG_LONG__ == 4)
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,_strtoull_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),strtou32_l,(__nptr,__endptr,__base,__locale))
#else /* LIBC: strtoull_l */
#include <local/stdlib/strtoull_l.h>
__FORCELOCAL __ATTR_NONNULL((1)) __ULONGLONG __NOTHROW_NCX(__LIBCCALL _strtoull_l)(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtoull_l))(__nptr, __endptr, __base, __locale); }
#endif /* _strtoull_l... */
#ifndef __NO_FPU
#ifdef __CRT_HAVE__strtod_l
__CDECLARE(__ATTR_NONNULL((1)),double,__NOTHROW_NCX,_strtod_l,(char const *__restrict __nptr, char **__endptr, __locale_t __locale),(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE_strtod_l)
__CREDIRECT(__ATTR_NONNULL((1)),double,__NOTHROW_NCX,_strtod_l,(char const *__restrict __nptr, char **__endptr, __locale_t __locale),strtod_l,(__nptr,__endptr,__locale))
#else /* LIBC: strtod_l */
#include <local/stdlib/strtod_l.h>
__FORCELOCAL __ATTR_NONNULL((1)) double __NOTHROW_NCX(__LIBCCALL _strtod_l)(char const *__restrict __nptr, char **__endptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtod_l))(__nptr, __endptr, __locale); }
#endif /* _strtod_l... */
#ifdef __CRT_HAVE__strtof_l
__CDECLARE(__ATTR_NONNULL((1)),float,__NOTHROW_NCX,_strtof_l,(char const *__restrict __nptr, char **__endptr, __locale_t __locale),(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE_strtof_l)
__CREDIRECT(__ATTR_NONNULL((1)),float,__NOTHROW_NCX,_strtof_l,(char const *__restrict __nptr, char **__endptr, __locale_t __locale),strtof_l,(__nptr,__endptr,__locale))
#else /* LIBC: strtof_l */
#include <local/stdlib/strtof_l.h>
__FORCELOCAL __ATTR_NONNULL((1)) float __NOTHROW_NCX(__LIBCCALL _strtof_l)(char const *__restrict __nptr, char **__endptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtof_l))(__nptr, __endptr, __locale); }
#endif /* _strtof_l... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#ifdef __CRT_HAVE__strtold_l
__CDECLARE(__ATTR_NONNULL((1)),long double,__NOTHROW_NCX,_strtold_l,(char const *__restrict __nptr, char **__endptr, __locale_t __locale),(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE_strtold_l)
__CREDIRECT(__ATTR_NONNULL((1)),long double,__NOTHROW_NCX,_strtold_l,(char const *__restrict __nptr, char **__endptr, __locale_t __locale),strtold_l,(__nptr,__endptr,__locale))
#else /* LIBC: strtold_l */
#include <local/stdlib/strtold_l.h>
__FORCELOCAL __ATTR_NONNULL((1)) long double __NOTHROW_NCX(__LIBCCALL _strtold_l)(char const *__restrict __nptr, char **__endptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtold_l))(__nptr, __endptr, __locale); }
#endif /* _strtold_l... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__NO_FPU */

#ifndef _CRT_SYSTEM_DEFINED
#define _CRT_SYSTEM_DEFINED 1
#endif /* !_CRT_SYSTEM_DEFINED */

#ifdef __CRT_HAVE__wctomb_l
__CDECLARE(,int,__NOTHROW_NCX,_wctomb_l,(char *__buf, wchar_t __wc, __locale_t __locale),(__buf,__wc,__locale))
#else /* LIBC: _wctomb_l */
#include <local/stdlib/_wctomb_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wctomb_l, __FORCELOCAL int __NOTHROW_NCX(__LIBCCALL _wctomb_l)(char *__buf, wchar_t __wc, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wctomb_l))(__buf, __wc, __locale); })
#endif /* _wctomb_l... */

#ifdef __USE_DOS_SLIB
#ifdef __CRT_HAVE_wctomb_s
__CDECLARE(__ATTR_NONNULL((1, 2)),errno_t,__NOTHROW_NCX,wctomb_s,(int *__presult, char *__buf, rsize_t __buflen, wchar_t __wc),(__presult,__buf,__buflen,__wc))
#else /* LIBC: wctomb_s */
#include <local/stdlib/wctomb_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wctomb_s, __FORCELOCAL __ATTR_NONNULL((1, 2)) errno_t __NOTHROW_NCX(__LIBCCALL wctomb_s)(int *__presult, char *__buf, rsize_t __buflen, wchar_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wctomb_s))(__presult, __buf, __buflen, __wc); })
#endif /* wctomb_s... */
#endif /* __USE_DOS_SLIB */
#ifdef __CRT_HAVE__wctomb_s_l
__CDECLARE(__ATTR_NONNULL((1, 2)),errno_t,__NOTHROW_NCX,_wctomb_s_l,(int *__presult, char *__buf, __SIZE_TYPE__ __buflen, wchar_t __wc, __locale_t __locale),(__presult,__buf,__buflen,__wc,__locale))
#else /* LIBC: _wctomb_s_l */
#include <local/stdlib/_wctomb_s_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wctomb_s_l, __FORCELOCAL __ATTR_NONNULL((1, 2)) errno_t __NOTHROW_NCX(__LIBCCALL _wctomb_s_l)(int *__presult, char *__buf, __SIZE_TYPE__ __buflen, wchar_t __wc, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wctomb_s_l))(__presult, __buf, __buflen, __wc, __locale); })
#endif /* _wctomb_s_l... */
#ifdef __CRT_HAVE__wcstombs_s_l
__CDECLARE(__ATTR_NONNULL((1, 2, 4)),errno_t,__NOTHROW_NCX,_wcstombs_s_l,(__SIZE_TYPE__ *__presult, char *__buf, __SIZE_TYPE__ __buflen, wchar_t const *__src, __SIZE_TYPE__ __maxlen, __locale_t __locale),(__presult,__buf,__buflen,__src,__maxlen,__locale))
#else /* LIBC: _wcstombs_s_l */
#include <local/stdlib/_wcstombs_s_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wcstombs_s_l, __FORCELOCAL __ATTR_NONNULL((1, 2, 4)) errno_t __NOTHROW_NCX(__LIBCCALL _wcstombs_s_l)(__SIZE_TYPE__ *__presult, char *__buf, __SIZE_TYPE__ __buflen, wchar_t const *__src, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wcstombs_s_l))(__presult, __buf, __buflen, __src, __maxlen, __locale); })
#endif /* _wcstombs_s_l... */
#ifdef __CRT_HAVE__wcstombs_l
__CDECLARE(__ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,_wcstombs_l,(char *__dst, wchar_t const *__src, __SIZE_TYPE__ __maxlen, __locale_t __locale),(__dst,__src,__maxlen,__locale))
#else /* LIBC: _wcstombs_l */
#include <local/stdlib/_wcstombs_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wcstombs_l, __FORCELOCAL __ATTR_NONNULL((1, 2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL _wcstombs_l)(char *__dst, wchar_t const *__src, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wcstombs_l))(__dst, __src, __maxlen, __locale); })
#endif /* _wcstombs_l... */
#ifdef __CRT_HAVE_wcstombs_s
__CDECLARE(__ATTR_NONNULL((1, 2, 4)),errno_t,__NOTHROW_NCX,wcstombs_s,(__SIZE_TYPE__ *__presult, char *__buf, __SIZE_TYPE__ __buflen, wchar_t const *__src, __SIZE_TYPE__ __maxlen),(__presult,__buf,__buflen,__src,__maxlen))
#else /* LIBC: wcstombs_s */
#include <local/stdlib/wcstombs_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstombs_s, __FORCELOCAL __ATTR_NONNULL((1, 2, 4)) errno_t __NOTHROW_NCX(__LIBCCALL wcstombs_s)(__SIZE_TYPE__ *__presult, char *__buf, __SIZE_TYPE__ __buflen, wchar_t const *__src, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstombs_s))(__presult, __buf, __buflen, __src, __maxlen); })
#endif /* wcstombs_s... */

/* DOS malloc extensions */
#ifdef __CRT_HAVE__recalloc
__CDECLARE(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2, 3)),void *,__NOTHROW_NCX,_recalloc,(void *__mptr, __SIZE_TYPE__ __count, __SIZE_TYPE__ __num_bytes),(__mptr,__count,__num_bytes))
#endif /* _recalloc... */
#ifdef __CRT_HAVE__aligned_malloc
__CDECLARE(__ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)) __ATTR_ALLOC_ALIGN(2),void *,__NOTHROW_NCX,_aligned_malloc,(__SIZE_TYPE__ __num_bytes, __SIZE_TYPE__ __min_alignment),(__num_bytes,__min_alignment))
#elif defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_posix_memalign) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_malloc)
#include <local/stdlib/_aligned_malloc.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_aligned_malloc, __FORCELOCAL __ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)) __ATTR_ALLOC_ALIGN(2) void *__NOTHROW_NCX(__LIBCCALL _aligned_malloc)(__SIZE_TYPE__ __num_bytes, __SIZE_TYPE__ __min_alignment) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_aligned_malloc))(__num_bytes, __min_alignment); })
#endif /* _aligned_malloc... */
#ifdef __CRT_HAVE__aligned_offset_malloc
__CDECLARE(__ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,_aligned_offset_malloc,(__SIZE_TYPE__ __num_bytes, __SIZE_TYPE__ __min_alignment, __SIZE_TYPE__ __offset),(__num_bytes,__min_alignment,__offset))
#elif defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_posix_memalign) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_malloc)
#include <local/stdlib/_aligned_offset_malloc.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_aligned_offset_malloc, __FORCELOCAL __ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)) void *__NOTHROW_NCX(__LIBCCALL _aligned_offset_malloc)(__SIZE_TYPE__ __num_bytes, __SIZE_TYPE__ __min_alignment, __SIZE_TYPE__ __offset) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_aligned_offset_malloc))(__num_bytes, __min_alignment, __offset); })
#endif /* _aligned_offset_malloc... */
#ifdef __CRT_HAVE__aligned_realloc
__CDECLARE(__ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) __ATTR_ALLOC_ALIGN(3),void *,__NOTHROW_NCX,_aligned_realloc,(void *__mptr, __SIZE_TYPE__ __newsize, __SIZE_TYPE__ __min_alignment),(__mptr,__newsize,__min_alignment))
#elif (defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_posix_memalign) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE__aligned_malloc)) && (defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE__aligned_free))
#include <local/stdlib/_aligned_realloc.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_aligned_realloc, __FORCELOCAL __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) __ATTR_ALLOC_ALIGN(3) void *__NOTHROW_NCX(__LIBCCALL _aligned_realloc)(void *__mptr, __SIZE_TYPE__ __newsize, __SIZE_TYPE__ __min_alignment) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_aligned_realloc))(__mptr, __newsize, __min_alignment); })
#endif /* _aligned_realloc... */
#ifdef __CRT_HAVE__aligned_recalloc
__CDECLARE(__ATTR_WUNUSED __ATTR_ALLOC_SIZE((2, 3)) __ATTR_ALLOC_ALIGN(4),void *,__NOTHROW_NCX,_aligned_recalloc,(void *__mptr, __SIZE_TYPE__ __count, __SIZE_TYPE__ __num_bytes, __SIZE_TYPE__ __min_alignment),(__mptr,__count,__num_bytes,__min_alignment))
#elif (defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_posix_memalign) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE__aligned_malloc)) && (defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE__aligned_free))
#include <local/stdlib/_aligned_recalloc.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_aligned_recalloc, __FORCELOCAL __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2, 3)) __ATTR_ALLOC_ALIGN(4) void *__NOTHROW_NCX(__LIBCCALL _aligned_recalloc)(void *__mptr, __SIZE_TYPE__ __count, __SIZE_TYPE__ __num_bytes, __SIZE_TYPE__ __min_alignment) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_aligned_recalloc))(__mptr, __count, __num_bytes, __min_alignment); })
#endif /* _aligned_recalloc... */
#ifdef __CRT_HAVE__aligned_offset_realloc
__CDECLARE(__ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,_aligned_offset_realloc,(void *__mptr, __SIZE_TYPE__ __newsize, __SIZE_TYPE__ __min_alignment, __SIZE_TYPE__ __offset),(__mptr,__newsize,__min_alignment,__offset))
#elif (defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_posix_memalign) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE__aligned_offset_malloc)) && (defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE__aligned_free))
#include <local/stdlib/_aligned_offset_realloc.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_aligned_offset_realloc, __FORCELOCAL __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) void *__NOTHROW_NCX(__LIBCCALL _aligned_offset_realloc)(void *__mptr, __SIZE_TYPE__ __newsize, __SIZE_TYPE__ __min_alignment, __SIZE_TYPE__ __offset) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_aligned_offset_realloc))(__mptr, __newsize, __min_alignment, __offset); })
#endif /* _aligned_offset_realloc... */
#ifdef __CRT_HAVE__aligned_offset_recalloc
__CDECLARE(__ATTR_WUNUSED __ATTR_ALLOC_SIZE((2, 3)),void *,__NOTHROW_NCX,_aligned_offset_recalloc,(void *__mptr, __SIZE_TYPE__ __count, __SIZE_TYPE__ __num_bytes, __SIZE_TYPE__ __min_alignment, __SIZE_TYPE__ __offset),(__mptr,__count,__num_bytes,__min_alignment,__offset))
#elif (defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_posix_memalign) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE__aligned_offset_malloc)) && (defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE__aligned_free))
#include <local/stdlib/_aligned_offset_recalloc.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_aligned_offset_recalloc, __FORCELOCAL __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2, 3)) void *__NOTHROW_NCX(__LIBCCALL _aligned_offset_recalloc)(void *__mptr, __SIZE_TYPE__ __count, __SIZE_TYPE__ __num_bytes, __SIZE_TYPE__ __min_alignment, __SIZE_TYPE__ __offset) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_aligned_offset_recalloc))(__mptr, __count, __num_bytes, __min_alignment, __offset); })
#endif /* _aligned_offset_recalloc... */
#ifdef __CRT_HAVE__aligned_msize
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,__SIZE_TYPE__,__NOTHROW_NCX,_aligned_msize,(void *__mptr, __SIZE_TYPE__ __min_alignment, __SIZE_TYPE__ __offset),(__mptr,__min_alignment,__offset))
#else /* LIBC: _aligned_msize */
#include <local/stdlib/_aligned_msize.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_aligned_msize, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL _aligned_msize)(void *__mptr, __SIZE_TYPE__ __min_alignment, __SIZE_TYPE__ __offset) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_aligned_msize))(__mptr, __min_alignment, __offset); })
#endif /* _aligned_msize... */
#ifdef __CRT_HAVE__aligned_free
__CDECLARE_VOID(,__NOTHROW_NCX,_aligned_free,(void *__mptr),(__mptr))
#elif defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree)
#include <local/stdlib/_aligned_free.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_aligned_free, __FORCELOCAL void __NOTHROW_NCX(__LIBCCALL _aligned_free)(void *__mptr) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_aligned_free))(__mptr); })
#endif /* _aligned_free... */

#define _CVTBUFSIZE   349
#ifdef __CRT_HAVE__fullpath
__CDECLARE(,char *,__NOTHROW_RPC,_fullpath,(char *__buf, char const *__path, __SIZE_TYPE__ __buflen),(__buf,__path,__buflen))
#endif /* _fullpath... */
#ifndef __NO_FPU
#ifdef __CRT_HAVE__ecvt_s
__CDECLARE(__ATTR_NONNULL((1, 5, 6)),errno_t,__NOTHROW_NCX,_ecvt_s,(char *__buf, __SIZE_TYPE__ __buflen, double __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign),(__buf,__buflen,__val,__ndigit,__decptr,__sign))
#else /* LIBC: _ecvt_s */
#include <local/stdlib/_ecvt_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_ecvt_s, __FORCELOCAL __ATTR_NONNULL((1, 5, 6)) errno_t __NOTHROW_NCX(__LIBCCALL _ecvt_s)(char *__buf, __SIZE_TYPE__ __buflen, double __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_ecvt_s))(__buf, __buflen, __val, __ndigit, __decptr, __sign); })
#endif /* _ecvt_s... */
#ifdef __CRT_HAVE__fcvt_s
__CDECLARE(__ATTR_NONNULL((1, 5, 6)),errno_t,__NOTHROW_NCX,_fcvt_s,(char *__buf, __SIZE_TYPE__ __buflen, double __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign),(__buf,__buflen,__val,__ndigit,__decptr,__sign))
#else /* LIBC: _fcvt_s */
#include <local/stdlib/_fcvt_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_fcvt_s, __FORCELOCAL __ATTR_NONNULL((1, 5, 6)) errno_t __NOTHROW_NCX(__LIBCCALL _fcvt_s)(char *__buf, __SIZE_TYPE__ __buflen, double __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_fcvt_s))(__buf, __buflen, __val, __ndigit, __decptr, __sign); })
#endif /* _fcvt_s... */
#ifdef __CRT_HAVE__gcvt_s
__CDECLARE(__ATTR_NONNULL((1)),errno_t,__NOTHROW_NCX,_gcvt_s,(char *__buf, __SIZE_TYPE__ __buflen, double __val, int __ndigit),(__buf,__buflen,__val,__ndigit))
#else /* LIBC: _gcvt_s */
#include <local/stdlib/_gcvt_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_gcvt_s, __FORCELOCAL __ATTR_NONNULL((1)) errno_t __NOTHROW_NCX(__LIBCCALL _gcvt_s)(char *__buf, __SIZE_TYPE__ __buflen, double __val, int __ndigit) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_gcvt_s))(__buf, __buflen, __val, __ndigit); })
#endif /* _gcvt_s... */
#ifdef __CRT_HAVE_ecvt
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((3, 4)),char *,__NOTHROW_NCX,_ecvt,(double __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign),ecvt,(__val,__ndigit,__decptr,__sign))
#elif defined(__CRT_HAVE__ecvt)
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((3, 4)),char *,__NOTHROW_NCX,_ecvt,(double __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign),(__val,__ndigit,__decptr,__sign))
#else /* LIBC: ecvt */
#include <local/stdlib/ecvt.h>
__FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((3, 4)) char *__NOTHROW_NCX(__LIBCCALL _ecvt)(double __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ecvt))(__val, __ndigit, __decptr, __sign); }
#endif /* _ecvt... */
#ifdef __CRT_HAVE__fcvt
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((3, 4)),char *,__NOTHROW_NCX,_fcvt,(double __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign),(__val,__ndigit,__decptr,__sign))
#elif defined(__CRT_HAVE_fcvt)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((3, 4)),char *,__NOTHROW_NCX,_fcvt,(double __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign),fcvt,(__val,__ndigit,__decptr,__sign))
#elif defined(__CRT_HAVE__ecvt)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((3, 4)),char *,__NOTHROW_NCX,_fcvt,(double __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign),_ecvt,(__val,__ndigit,__decptr,__sign))
#else /* LIBC: fcvt */
#include <local/stdlib/fcvt.h>
__FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((3, 4)) char *__NOTHROW_NCX(__LIBCCALL _fcvt)(double __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fcvt))(__val, __ndigit, __decptr, __sign); }
#endif /* _fcvt... */
#ifdef __CRT_HAVE_gcvt
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((3)),char *,__NOTHROW_NCX,_gcvt,(double __val, int __ndigit, char *__buf),gcvt,(__val,__ndigit,__buf))
#elif defined(__CRT_HAVE__gcvt)
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((3)),char *,__NOTHROW_NCX,_gcvt,(double __val, int __ndigit, char *__buf),(__val,__ndigit,__buf))
#else /* LIBC: gcvt */
#include <local/stdlib/gcvt.h>
__FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((3)) char *__NOTHROW_NCX(__LIBCCALL _gcvt)(double __val, int __ndigit, char *__buf) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(gcvt))(__val, __ndigit, __buf); }
#endif /* _gcvt... */
#ifdef __CRT_HAVE__atoflt
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_atoflt,(float *__restrict __result, char const *__restrict __nptr),(__result,__nptr))
#else /* LIBC: _atoflt */
#include <local/stdlib/_atoflt.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_atoflt, __FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _atoflt)(float *__restrict __result, char const *__restrict __nptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_atoflt))(__result, __nptr); })
#endif /* _atoflt... */
#ifdef __CRT_HAVE__atoflt_l
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_atoflt_l,(float *__restrict __result, char const *__restrict __nptr, __locale_t __locale),(__result,__nptr,__locale))
#else /* LIBC: _atoflt_l */
#include <local/stdlib/_atoflt_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_atoflt_l, __FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _atoflt_l)(float *__restrict __result, char const *__restrict __nptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_atoflt_l))(__result, __nptr, __locale); })
#endif /* _atoflt_l... */
#ifdef __CRT_HAVE__atodbl
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_atodbl,(double *__restrict __result, char __KOS_FIXED_CONST *__restrict __nptr),(__result,__nptr))
#elif defined(__CRT_HAVE__atoldbl) && (__SIZEOF_DOUBLE__ == __SIZEOF_LONG_DOUBLE__)
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_atodbl,(double *__restrict __result, char __KOS_FIXED_CONST *__restrict __nptr),_atoldbl,(__result,__nptr))
#else /* LIBC: _atodbl */
#include <local/stdlib/_atodbl.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_atodbl, __FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _atodbl)(double *__restrict __result, char __KOS_FIXED_CONST *__restrict __nptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_atodbl))(__result, __nptr); })
#endif /* _atodbl... */
#ifdef __CRT_HAVE__atodbl_l
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_atodbl_l,(double *__restrict __result, char __KOS_FIXED_CONST *__restrict __nptr, __locale_t __locale),(__result,__nptr,__locale))
#elif defined(__CRT_HAVE__atoldbl_l) && (__SIZEOF_DOUBLE__ == __SIZEOF_LONG_DOUBLE__)
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_atodbl_l,(double *__restrict __result, char __KOS_FIXED_CONST *__restrict __nptr, __locale_t __locale),_atoldbl_l,(__result,__nptr,__locale))
#else /* LIBC: _atodbl_l */
#include <local/stdlib/_atodbl_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_atodbl_l, __FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _atodbl_l)(double *__restrict __result, char __KOS_FIXED_CONST *__restrict __nptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_atodbl_l))(__result, __nptr, __locale); })
#endif /* _atodbl_l... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#ifdef __CRT_HAVE__atoldbl
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_atoldbl,(long double *__restrict __result, char __KOS_FIXED_CONST *__restrict __nptr),(__result,__nptr))
#elif defined(__CRT_HAVE__atodbl) && (__SIZEOF_DOUBLE__ == __SIZEOF_LONG_DOUBLE__)
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_atoldbl,(long double *__restrict __result, char __KOS_FIXED_CONST *__restrict __nptr),_atodbl,(__result,__nptr))
#else /* LIBC: _atoldbl */
#include <local/stdlib/_atoldbl.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_atoldbl, __FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _atoldbl)(long double *__restrict __result, char __KOS_FIXED_CONST *__restrict __nptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_atoldbl))(__result, __nptr); })
#endif /* _atoldbl... */
#ifdef __CRT_HAVE__atoldbl_l
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_atoldbl_l,(long double *__restrict __result, char __KOS_FIXED_CONST *__restrict __nptr, __locale_t __locale),(__result,__nptr,__locale))
#elif defined(__CRT_HAVE__atodbl_l) && (__SIZEOF_DOUBLE__ == __SIZEOF_LONG_DOUBLE__)
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_atoldbl_l,(long double *__restrict __result, char __KOS_FIXED_CONST *__restrict __nptr, __locale_t __locale),_atodbl_l,(__result,__nptr,__locale))
#else /* LIBC: _atoldbl_l */
#include <local/stdlib/_atoldbl_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_atoldbl_l, __FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _atoldbl_l)(long double *__restrict __result, char __KOS_FIXED_CONST *__restrict __nptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_atoldbl_l))(__result, __nptr, __locale); })
#endif /* _atoldbl_l... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__NO_FPU */
#ifdef __CRT_HAVE__rotl
__CDECLARE(__ATTR_CONST,unsigned int,__NOTHROW,_rotl,(unsigned int __val, int __shift),(__val,__shift))
#elif defined(__CRT_HAVE__lrotl) && (__SIZEOF_INT__ == __SIZEOF_LONG__)
__CREDIRECT(__ATTR_CONST,unsigned int,__NOTHROW,_rotl,(unsigned int __val, int __shift),_lrotl,(__val,__shift))
#elif defined(__CRT_HAVE__rotl64) && (__SIZEOF_INT__ == 8)
__CREDIRECT(__ATTR_CONST,unsigned int,__NOTHROW,_rotl,(unsigned int __val, int __shift),_rotl64,(__val,__shift))
#else /* LIBC: _rotl */
#include <local/stdlib/_rotl.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_rotl, __FORCELOCAL __ATTR_CONST unsigned int __NOTHROW(__LIBCCALL _rotl)(unsigned int __val, int __shift) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_rotl))(__val, __shift); })
#endif /* _rotl... */
#ifdef __CRT_HAVE__rotr
__CDECLARE(__ATTR_CONST,unsigned int,__NOTHROW,_rotr,(unsigned int __val, int __shift),(__val,__shift))
#elif defined(__CRT_HAVE__lrotr) && (__SIZEOF_INT__ == __SIZEOF_LONG__)
__CREDIRECT(__ATTR_CONST,unsigned int,__NOTHROW,_rotr,(unsigned int __val, int __shift),_lrotr,(__val,__shift))
#elif defined(__CRT_HAVE__rotr64) && (__SIZEOF_INT__ == 8)
__CREDIRECT(__ATTR_CONST,unsigned int,__NOTHROW,_rotr,(unsigned int __val, int __shift),_rotr64,(__val,__shift))
#else /* LIBC: _rotr */
#include <local/stdlib/_rotr.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_rotr, __FORCELOCAL __ATTR_CONST unsigned int __NOTHROW(__LIBCCALL _rotr)(unsigned int __val, int __shift) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_rotr))(__val, __shift); })
#endif /* _rotr... */
#ifdef __UINT64_TYPE__
#ifdef __CRT_HAVE__rotl64
__CDECLARE(__ATTR_CONST,__UINT64_TYPE__,__NOTHROW,_rotl64,(__UINT64_TYPE__ __val, int __shift),(__val,__shift))
#elif defined(__CRT_HAVE__lrotl) && (__SIZEOF_LONG__ == 8)
__CREDIRECT(__ATTR_CONST,__UINT64_TYPE__,__NOTHROW,_rotl64,(__UINT64_TYPE__ __val, int __shift),_lrotl,(__val,__shift))
#elif defined(__CRT_HAVE__rotl) && (__SIZEOF_INT__ == 8)
__CREDIRECT(__ATTR_CONST,__UINT64_TYPE__,__NOTHROW,_rotl64,(__UINT64_TYPE__ __val, int __shift),_rotl,(__val,__shift))
#else /* LIBC: _rotl64 */
#include <local/stdlib/_rotl64.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_rotl64, __FORCELOCAL __ATTR_CONST __UINT64_TYPE__ __NOTHROW(__LIBCCALL _rotl64)(__UINT64_TYPE__ __val, int __shift) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_rotl64))(__val, __shift); })
#endif /* _rotl64... */
#ifdef __CRT_HAVE__rotr64
__CDECLARE(__ATTR_CONST,__UINT64_TYPE__,__NOTHROW,_rotr64,(__UINT64_TYPE__ __val, int __shift),(__val,__shift))
#elif defined(__CRT_HAVE__lrotr) && (__SIZEOF_LONG__ == 8)
__CREDIRECT(__ATTR_CONST,__UINT64_TYPE__,__NOTHROW,_rotr64,(__UINT64_TYPE__ __val, int __shift),_lrotr,(__val,__shift))
#elif defined(__CRT_HAVE__rotr) && (__SIZEOF_INT__ == 8)
__CREDIRECT(__ATTR_CONST,__UINT64_TYPE__,__NOTHROW,_rotr64,(__UINT64_TYPE__ __val, int __shift),_rotr,(__val,__shift))
#else /* LIBC: _rotr64 */
#include <local/stdlib/_rotr64.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_rotr64, __FORCELOCAL __ATTR_CONST __UINT64_TYPE__ __NOTHROW(__LIBCCALL _rotr64)(__UINT64_TYPE__ __val, int __shift) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_rotr64))(__val, __shift); })
#endif /* _rotr64... */
#endif /* __UINT64_TYPE__ */
#ifdef __CRT_HAVE__lrotl
__CDECLARE(__ATTR_CONST,unsigned long,__NOTHROW,_lrotl,(unsigned long __val, int __shift),(__val,__shift))
#elif defined(__CRT_HAVE__rotl) && (__SIZEOF_LONG__ == __SIZEOF_INT__)
__CREDIRECT(__ATTR_CONST,unsigned long,__NOTHROW,_lrotl,(unsigned long __val, int __shift),_rotl,(__val,__shift))
#elif defined(__CRT_HAVE__rotl64) && (__SIZEOF_LONG__ == 8)
__CREDIRECT(__ATTR_CONST,unsigned long,__NOTHROW,_lrotl,(unsigned long __val, int __shift),_rotl64,(__val,__shift))
#else /* LIBC: _lrotl */
#include <local/stdlib/_lrotl.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_lrotl, __FORCELOCAL __ATTR_CONST unsigned long __NOTHROW(__LIBCCALL _lrotl)(unsigned long __val, int __shift) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_lrotl))(__val, __shift); })
#endif /* _lrotl... */
#ifdef __CRT_HAVE__lrotr
__CDECLARE(__ATTR_CONST,unsigned long,__NOTHROW,_lrotr,(unsigned long __val, int __shift),(__val,__shift))
#elif defined(__CRT_HAVE__rotr) && (__SIZEOF_LONG__ == __SIZEOF_INT__)
__CREDIRECT(__ATTR_CONST,unsigned long,__NOTHROW,_lrotr,(unsigned long __val, int __shift),_rotr,(__val,__shift))
#elif defined(__CRT_HAVE__rotr64) && (__SIZEOF_LONG__ == 8)
__CREDIRECT(__ATTR_CONST,unsigned long,__NOTHROW,_lrotr,(unsigned long __val, int __shift),_rotr64,(__val,__shift))
#else /* LIBC: _lrotr */
#include <local/stdlib/_lrotr.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_lrotr, __FORCELOCAL __ATTR_CONST unsigned long __NOTHROW(__LIBCCALL _lrotr)(unsigned long __val, int __shift) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_lrotr))(__val, __shift); })
#endif /* _lrotr... */

#ifndef _CRT_PERROR_DEFINED
#define _CRT_PERROR_DEFINED 1
#ifndef __perror_defined
#define __perror_defined 1
#ifdef __std_perror_defined
__NAMESPACE_STD_USING(perror)
#elif defined(__CRT_HAVE_perror)
/* Print a given `MESSAGE' alongside `strerror(errno)' to stderr:
 * >> if (message) {
 * >>     fprintf(stderr, "%s: %s\n", message, strerror(errno));
 * >> } else {
 * >>     fprintf(stderr, "%s\n", strerror(errno));
 * >> } */
__CDECLARE_VOID(,__NOTHROW_RPC,perror,(char const *__message),(__message))
#else /* LIBC: perror */
#undef __perror_defined
#endif /* perror... */
#endif /* !__perror_defined */
#endif  /* _CRT_PERROR_DEFINED */

#ifdef __CRT_HAVE__putenv
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,_putenv,(char *__string),(__string))
#elif defined(__CRT_HAVE_putenv)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,_putenv,(char *__string),putenv,(__string))
#endif /* _putenv... */
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
#else /* LIBC: swab */
#include <local/unistd/swab.h>
/* Copy `n_bytes & ~1' (FLOOR_ALIGN(n_bytes, 2)) from `from' to `to',
 * exchanging the order of even and odd bytes ("123456" --> "214365")
 * When `n_bytes <= 1', don't do anything and return immediately */
__FORCELOCAL __ATTR_NONNULL((1, 2)) void __NOTHROW_NCX(__LIBCCALL _swab)(void const *__restrict __from, void *__restrict __to, __STDC_INT_AS_SSIZE_T __n_bytes) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(swab))(__from, __to, __n_bytes); }
#endif /* _swab... */
#ifdef __CRT_HAVE__putenv_s
__CDECLARE(,errno_t,__NOTHROW_NCX,_putenv_s,(char const *__varname, char const *__val),(__varname,__val))
#elif defined(__CRT_HAVE_setenv)
#include <local/stdlib/_putenv_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_putenv_s, __FORCELOCAL errno_t __NOTHROW_NCX(__LIBCCALL _putenv_s)(char const *__varname, char const *__val) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_putenv_s))(__varname, __val); })
#endif /* _putenv_s... */
#ifdef __CRT_HAVE__searchenv
__CDECLARE_VOID(__ATTR_NONNULL((1, 2, 3)),__NOTHROW_RPC,_searchenv,(char const *__file, char const *__envvar, char *__restrict __resultpath),(__file,__envvar,__resultpath))
#elif defined(__CRT_HAVE__searchenv_s)
#include <local/stdlib/_searchenv.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_searchenv, __FORCELOCAL __ATTR_NONNULL((1, 2, 3)) void __NOTHROW_RPC(__LIBCCALL _searchenv)(char const *__file, char const *__envvar, char *__restrict __resultpath) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_searchenv))(__file, __envvar, __resultpath); })
#endif /* _searchenv... */
#ifdef __CRT_HAVE__searchenv_s
__CDECLARE(__ATTR_NONNULL((1, 2, 3)),errno_t,__NOTHROW_RPC,_searchenv_s,(char const *__file, char const *__envvar, char *__restrict __resultpath, __SIZE_TYPE__ __buflen),(__file,__envvar,__resultpath,__buflen))
#endif /* _searchenv_s... */
#ifdef __CRT_HAVE__makepath
__CDECLARE_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,_makepath,(char *__restrict __buf, char const *__drive, char const *__dir, char const *__file, char const *__ext),(__buf,__drive,__dir,__file,__ext))
#else /* LIBC: _makepath */
#include <local/stdlib/_makepath.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_makepath, __FORCELOCAL __ATTR_NONNULL((1)) void __NOTHROW_NCX(__LIBCCALL _makepath)(char *__restrict __buf, char const *__drive, char const *__dir, char const *__file, char const *__ext) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_makepath))(__buf, __drive, __dir, __file, __ext); })
#endif /* _makepath... */
#ifdef __CRT_HAVE__splitpath
__CDECLARE_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,_splitpath,(char const *__restrict __abspath, char *__drive, char *__dir, char *__file, char *__ext),(__abspath,__drive,__dir,__file,__ext))
#else /* LIBC: _splitpath */
#include <local/stdlib/_splitpath.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_splitpath, __FORCELOCAL __ATTR_NONNULL((1)) void __NOTHROW_NCX(__LIBCCALL _splitpath)(char const *__restrict __abspath, char *__drive, char *__dir, char *__file, char *__ext) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_splitpath))(__abspath, __drive, __dir, __file, __ext); })
#endif /* _splitpath... */
#ifdef __CRT_HAVE__makepath_s
__CDECLARE(__ATTR_NONNULL((1)),errno_t,__NOTHROW_NCX,_makepath_s,(char *__buf, __SIZE_TYPE__ __buflen, char const *__drive, char const *__dir, char const *__file, char const *__ext),(__buf,__buflen,__drive,__dir,__file,__ext))
#else /* LIBC: _makepath_s */
#include <local/stdlib/_makepath_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_makepath_s, __FORCELOCAL __ATTR_NONNULL((1)) errno_t __NOTHROW_NCX(__LIBCCALL _makepath_s)(char *__buf, __SIZE_TYPE__ __buflen, char const *__drive, char const *__dir, char const *__file, char const *__ext) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_makepath_s))(__buf, __buflen, __drive, __dir, __file, __ext); })
#endif /* _makepath_s... */
#ifdef __CRT_HAVE__splitpath_s
__CDECLARE(__ATTR_NONNULL((1)),errno_t,__NOTHROW_NCX,_splitpath_s,(char const *__restrict __abspath, char *__drive, __SIZE_TYPE__ __drivelen, char *__dir, __SIZE_TYPE__ __dirlen, char *__file, __SIZE_TYPE__ __filelen, char *__ext, __SIZE_TYPE__ __extlen),(__abspath,__drive,__drivelen,__dir,__dirlen,__file,__filelen,__ext,__extlen))
#else /* LIBC: _splitpath_s */
#include <local/stdlib/_splitpath_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_splitpath_s, __FORCELOCAL __ATTR_NONNULL((1)) errno_t __NOTHROW_NCX(__LIBCCALL _splitpath_s)(char const *__restrict __abspath, char *__drive, __SIZE_TYPE__ __drivelen, char *__dir, __SIZE_TYPE__ __dirlen, char *__file, __SIZE_TYPE__ __filelen, char *__ext, __SIZE_TYPE__ __extlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_splitpath_s))(__abspath, __drive, __drivelen, __dir, __dirlen, __file, __filelen, __ext, __extlen); })
#endif /* _splitpath_s... */

#ifdef __CRT_HAVE__seterrormode
__CDECLARE_VOID(,__NOTHROW_NCX,_seterrormode,(int __mode),(__mode))
#endif /* _seterrormode... */
#ifdef __CRT_HAVE__set_error_mode
__CDECLARE(,int,__NOTHROW_NCX,_set_error_mode,(int __mode),(__mode))
#endif /* _set_error_mode... */

#ifdef __CRT_HAVE__beep
__CDECLARE_VOID(,__NOTHROW_NCX,_beep,(unsigned int __freq, unsigned int __duration),(__freq,__duration))
#endif /* _beep... */

#ifndef _CRT_WPERROR_DEFINED
#define _CRT_WPERROR_DEFINED 1
#ifdef __CRT_HAVE__wperror
__CDECLARE_VOID(__ATTR_COLD,__NOTHROW_RPC,_wperror,(wchar_t const *__errmsg),(__errmsg))
#endif /* _wperror... */
#endif /* !_CRT_WPERROR_DEFINED */
#ifdef __CRT_HAVE__sleep
/* >> sleep(3)
 * Sleep for up to `SECONDS' seconds */
__CDECLARE_VOID(,__NOTHROW_RPC,_sleep,(__UINT32_TYPE__ __duration),(__duration))
#elif defined(__CRT_HAVE_sleep)
/* >> sleep(3)
 * Sleep for up to `SECONDS' seconds */
__CREDIRECT_VOID(,__NOTHROW_RPC,_sleep,(__UINT32_TYPE__ __duration),sleep,(__duration))
#elif defined(__CRT_HAVE__sleep)
#include <local/unistd/sleep.h>
/* >> sleep(3)
 * Sleep for up to `SECONDS' seconds */
__FORCELOCAL void __NOTHROW_RPC(__LIBCCALL _sleep)(__UINT32_TYPE__ __duration) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sleep))((unsigned int)__duration); }
#endif /* _sleep... */

#ifndef __cplusplus
#define min(a, b)   __min(a, b)
#define max(a, b)   __max(a, b)
#endif /* !__cplusplus */

#define sys_errlist _sys_errlist
#define sys_nerr    _sys_nerr

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
#undef _environ
#ifndef ___environ_defined
#define ___environ_defined 1
__LIBC char **_environ;
#endif /* !___environ_defined */
#define environ _environ
#elif defined(__CRT_HAVE___p__environ)
#ifndef ____p__environ_defined
#define ____p__environ_defined 1
__CDECLARE(__ATTR_WUNUSED __ATTR_CONST __ATTR_RETNONNULL,char ***,__NOTHROW,__p__environ,(void),())
#endif /* !____p__environ_defined */
#define environ   (*__p__environ())
#else
#undef __environ_defined
#endif
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
#else /* LIBC: swab */
#include <local/unistd/swab.h>
/* Copy `n_bytes & ~1' (FLOOR_ALIGN(n_bytes, 2)) from `from' to `to',
 * exchanging the order of even and odd bytes ("123456" --> "214365")
 * When `n_bytes <= 1', don't do anything and return immediately */
__NAMESPACE_LOCAL_USING_OR_IMPL(swab, __FORCELOCAL __ATTR_NONNULL((1, 2)) void __NOTHROW_NCX(__LIBCCALL swab)(void const *__restrict __from, void *__restrict __to, __STDC_INT_AS_SSIZE_T __n_bytes) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(swab))(__from, __to, __n_bytes); })
#endif /* swab... */
#endif /* !__swab_defined */



#ifdef __CRT_HAVE_itoa
__CDECLARE(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,itoa,(int __val, char *__dst, int __radix),(__val,__dst,__radix))
#elif defined(__CRT_HAVE__itoa)
__CREDIRECT(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,itoa,(int __val, char *__dst, int __radix),_itoa,(__val,__dst,__radix))
#elif defined(__CRT_HAVE__ltoa) && (__SIZEOF_INT__ == __SIZEOF_LONG__)
__CREDIRECT(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,itoa,(int __val, char *__dst, int __radix),_ltoa,(__val,__dst,__radix))
#elif defined(__CRT_HAVE_ltoa) && (__SIZEOF_INT__ == __SIZEOF_LONG__)
__CREDIRECT(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,itoa,(int __val, char *__dst, int __radix),ltoa,(__val,__dst,__radix))
#elif defined(__CRT_HAVE__i64toa) && (__SIZEOF_INT__ == 8)
__CREDIRECT(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,itoa,(int __val, char *__dst, int __radix),_i64toa,(__val,__dst,__radix))
#elif defined(__CRT_HAVE_i64toa) && (__SIZEOF_INT__ == 8)
__CREDIRECT(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,itoa,(int __val, char *__dst, int __radix),i64toa,(__val,__dst,__radix))
#else /* LIBC: itoa */
#include <local/stdlib/itoa.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(itoa, __FORCELOCAL __ATTR_NONNULL((2)) char *__NOTHROW_NCX(__LIBCCALL itoa)(int __val, char *__dst, int __radix) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(itoa))(__val, __dst, __radix); })
#endif /* itoa... */
#ifdef __CRT_HAVE_ltoa
__CDECLARE(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,ltoa,(long __val, char *__dst, int __radix),(__val,__dst,__radix))
#elif defined(__CRT_HAVE__ltoa)
__CREDIRECT(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,ltoa,(long __val, char *__dst, int __radix),_ltoa,(__val,__dst,__radix))
#elif defined(__CRT_HAVE__itoa) && (__SIZEOF_LONG__ == __SIZEOF_INT__)
__CREDIRECT(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,ltoa,(long __val, char *__dst, int __radix),_itoa,(__val,__dst,__radix))
#elif defined(__CRT_HAVE_itoa) && (__SIZEOF_LONG__ == __SIZEOF_INT__)
__CREDIRECT(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,ltoa,(long __val, char *__dst, int __radix),itoa,(__val,__dst,__radix))
#elif defined(__CRT_HAVE__i64toa) && (__SIZEOF_LONG__ == 8)
__CREDIRECT(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,ltoa,(long __val, char *__dst, int __radix),_i64toa,(__val,__dst,__radix))
#elif defined(__CRT_HAVE_i64toa) && (__SIZEOF_LONG__ == 8)
__CREDIRECT(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,ltoa,(long __val, char *__dst, int __radix),i64toa,(__val,__dst,__radix))
#else /* LIBC: ltoa */
#include <local/stdlib/ltoa.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(ltoa, __FORCELOCAL __ATTR_NONNULL((2)) char *__NOTHROW_NCX(__LIBCCALL ltoa)(long __val, char *__dst, int __radix) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ltoa))(__val, __dst, __radix); })
#endif /* ltoa... */
#ifdef __CRT_HAVE_ultoa
__CDECLARE(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,ultoa,(unsigned long __val, char *__dst, int __radix),(__val,__dst,__radix))
#elif defined(__CRT_HAVE__ultoa)
__CREDIRECT(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,ultoa,(unsigned long __val, char *__dst, int __radix),_ultoa,(__val,__dst,__radix))
#elif defined(__CRT_HAVE__ui64toa) && (__SIZEOF_LONG__ == 8)
__CREDIRECT(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,ultoa,(unsigned long __val, char *__dst, int __radix),_ui64toa,(__val,__dst,__radix))
#elif defined(__CRT_HAVE_ui64toa) && (__SIZEOF_LONG__ == 8)
__CREDIRECT(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,ultoa,(unsigned long __val, char *__dst, int __radix),ui64toa,(__val,__dst,__radix))
#else /* LIBC: ultoa */
#include <local/stdlib/ultoa.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(ultoa, __FORCELOCAL __ATTR_NONNULL((2)) char *__NOTHROW_NCX(__LIBCCALL ultoa)(unsigned long __val, char *__dst, int __radix) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ultoa))(__val, __dst, __radix); })
#endif /* ultoa... */
#ifdef __CRT_HAVE__onexit
__CDECLARE(,onexit_t,__NOTHROW_NCX,_onexit,(onexit_t __func),(__func))
#elif defined(__CRT_HAVE_onexit)
__CREDIRECT(,onexit_t,__NOTHROW_NCX,_onexit,(onexit_t __func),onexit,(__func))
#endif /* _onexit... */
#ifdef __CRT_HAVE_onexit
__CDECLARE(,onexit_t,__NOTHROW_NCX,onexit,(onexit_t __func),(__func))
#elif defined(__CRT_HAVE__onexit)
__CREDIRECT(,onexit_t,__NOTHROW_NCX,onexit,(onexit_t __func),_onexit,(__func))
#endif /* onexit... */

#endif /* __CC__ */
#endif /* __USE_DOS */









#ifdef __USE_KOS
#ifdef __CC__
#ifdef __UINT64_TYPE__
#ifdef __CRT_HAVE_strto64_l
__CDECLARE(__ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,strto64_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoi64_l)
__CREDIRECT(__ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,strto64_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),_strtoi64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtol_l) && (__SIZEOF_LONG__ == 8)
__CREDIRECT(__ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,strto64_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),_strtol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtol_l) && (__SIZEOF_LONG__ == 8)
__CREDIRECT(__ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,strto64_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),strtol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtoll_l) && (__SIZEOF_LONG_LONG__ == 8)
__CREDIRECT(__ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,strto64_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),strtoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoll_l) && (__SIZEOF_LONG_LONG__ == 8)
__CREDIRECT(__ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,strto64_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),_strtoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtoq_l) && (__SIZEOF_LONG_LONG__ == 8)
__CREDIRECT(__ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,strto64_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),strtoq_l,(__nptr,__endptr,__base,__locale))
#else /* LIBC: strto64_l */
#include <local/stdlib/strto64_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strto64_l, __FORCELOCAL __ATTR_NONNULL((1)) __INT64_TYPE__ __NOTHROW_NCX(__LIBCCALL strto64_l)(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strto64_l))(__nptr, __endptr, __base, __locale); })
#endif /* strto64_l... */
#ifdef __CRT_HAVE_strtou64_l
__CDECLARE(__ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,strtou64_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoui64_l)
__CREDIRECT(__ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,strtou64_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),_strtoui64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoul_l) && (__SIZEOF_LONG__ == 8)
__CREDIRECT(__ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,strtou64_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),_strtoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtoul_l) && (__SIZEOF_LONG__ == 8)
__CREDIRECT(__ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,strtou64_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),strtoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtoull_l) && (__SIZEOF_LONG_LONG__ == 8)
__CREDIRECT(__ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,strtou64_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),strtoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoull_l) && (__SIZEOF_LONG_LONG__ == 8)
__CREDIRECT(__ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,strtou64_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),_strtoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtouq_l) && (__SIZEOF_LONG_LONG__ == 8)
__CREDIRECT(__ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,strtou64_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),strtouq_l,(__nptr,__endptr,__base,__locale))
#else /* LIBC: strtou64_l */
#include <local/stdlib/strtou64_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strtou64_l, __FORCELOCAL __ATTR_NONNULL((1)) __UINT64_TYPE__ __NOTHROW_NCX(__LIBCCALL strtou64_l)(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtou64_l))(__nptr, __endptr, __base, __locale); })
#endif /* strtou64_l... */
#endif /* __UINT64_TYPE__ */
#endif /* __CC__ */
#endif /* __USE_KOS */

__SYSDECL_END

#ifdef __USE_UTF
#if defined(_UCHAR_H) && !defined(_PARTS_UCHAR_STDLIB_H)
#include <parts/uchar/stdlib.h>
#endif
#endif /* __USE_UTF */

#ifdef __CXX_SYSTEM_HEADER
#define _CXX_STDONLY_CSTDLIB 1
#undef _STDLIB_H
#endif /* __CXX_SYSTEM_HEADER */
#endif /* !_CXX_STDONLY_CSTDLIB */
#endif /* !_STDLIB_H */
