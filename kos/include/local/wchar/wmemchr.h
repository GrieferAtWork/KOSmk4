/* HASH CRC-32:0x98c21cc5 */
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
#ifndef __local_wmemchr_defined
#define __local_wmemchr_defined 1
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/string.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */
/* Dependency: "memchrw" from "string" */
#ifndef ____localdep_memchrw_defined
#define ____localdep_memchrw_defined 1
#ifdef __fast_memchrw_defined
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
#define __localdep_memchrw (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memchrw))
#elif defined(__CRT_HAVE_memchrw)
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,__localdep_memchrw,(/*aligned(2)*/ void const *__restrict __haystack, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words),memchrw,(__haystack,__word,__n_words))
#elif defined(__CRT_HAVE_wmemchr) && (__SIZEOF_WCHAR_T__ == 2)
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,__localdep_memchrw,(/*aligned(2)*/ void const *__restrict __haystack, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words),wmemchr,(__haystack,__word,__n_words))
#else /* LIBC: memchrw */
#include <local/string/memchrw.h>
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
#define __localdep_memchrw (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memchrw))
#endif /* memchrw... */
#endif /* !____localdep_memchrw_defined */

/* Dependency: "memchrl" from "string" */
#ifndef ____localdep_memchrl_defined
#define ____localdep_memchrl_defined 1
#ifdef __fast_memchrl_defined
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
#define __localdep_memchrl (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memchrl))
#elif defined(__CRT_HAVE_memchrl)
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,__localdep_memchrl,(/*aligned(4)*/ void const *__restrict __haystack, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords),memchrl,(__haystack,__dword,__n_dwords))
#elif defined(__CRT_HAVE_wmemchr) && (__SIZEOF_WCHAR_T__ == 4)
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,__localdep_memchrl,(/*aligned(4)*/ void const *__restrict __haystack, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords),wmemchr,(__haystack,__dword,__n_dwords))
#else /* LIBC: memchrl */
#include <local/string/memchrl.h>
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
#define __localdep_memchrl (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memchrl))
#endif /* memchrl... */
#endif /* !____localdep_memchrl_defined */

/* Dependency: "memchr" from "string" */
#ifndef ____localdep_memchr_defined
#define ____localdep_memchr_defined 1
#ifdef __fast_memchr_defined
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
#define __localdep_memchr (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memchr))
#elif defined(__CRT_HAVE_memchr)
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,__localdep_memchr,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memchr,(__haystack,__needle,__n_bytes))
#else /* LIBC: memchr */
#include <local/string/memchr.h>
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
#define __localdep_memchr (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memchr))
#endif /* memchr... */
#endif /* !____localdep_memchr_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(wmemchr) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __WCHAR_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(wmemchr))(__WCHAR_TYPE__ const *__restrict __haystack,
                                                     __WCHAR_TYPE__ __needle,
                                                     __SIZE_TYPE__ __num_chars) {
#line 611 "kos/src/libc/magic/wchar.c"
#if __SIZEOF_WCHAR_T__ == 2
	return (__WCHAR_TYPE__ *)__localdep_memchrw(__haystack, __needle, __num_chars);
#elif __SIZEOF_WCHAR_T__ == 4
	return (__WCHAR_TYPE__ *)__localdep_memchrl(__haystack, __needle, __num_chars);
#else
	return (__WCHAR_TYPE__ *)__localdep_memchr(__haystack, (int)__needle, __num_chars * sizeof(__WCHAR_TYPE__));
#endif
}
__NAMESPACE_LOCAL_END
#endif /* !__local_wmemchr_defined */
