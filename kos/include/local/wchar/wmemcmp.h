/* HASH CRC-32:0x1dada31b */
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
#ifndef __local_wmemcmp_defined
#define __local_wmemcmp_defined 1
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/string.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */
/* Dependency: "memcmpw" from "string" */
#ifndef ____localdep_memcmpw_defined
#define ____localdep_memcmpw_defined 1
#if defined(__fast_memcmpw_defined)
/* Compare memory buffers and return the difference of the first non-matching word */
#define __localdep_memcmpw (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcmpw))
#elif defined(__CRT_HAVE_memcmpw)
/* Compare memory buffers and return the difference of the first non-matching word */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),__INT16_TYPE__,__NOTHROW_NCX,__localdep_memcmpw,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_words),memcmpw,(__s1,__s2,__n_words))
#elif defined(__CRT_HAVE_wmemcmp) && (__SIZEOF_WCHAR_T__ == 2)
/* Compare memory buffers and return the difference of the first non-matching word */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),__INT16_TYPE__,__NOTHROW_NCX,__localdep_memcmpw,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_words),wmemcmp,(__s1,__s2,__n_words))
#else /* LIBC: memcmpw */
#include <local/string/memcmpw.h>
/* Compare memory buffers and return the difference of the first non-matching word */
#define __localdep_memcmpw (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcmpw))
#endif /* memcmpw... */
#endif /* !____localdep_memcmpw_defined */

/* Dependency: "memcmpl" from "string" */
#ifndef ____localdep_memcmpl_defined
#define ____localdep_memcmpl_defined 1
#if defined(__fast_memcmpl_defined)
/* Compare memory buffers and return the difference of the first non-matching dword */
#define __localdep_memcmpl (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcmpl))
#elif defined(__CRT_HAVE_memcmpl)
/* Compare memory buffers and return the difference of the first non-matching dword */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),__INT32_TYPE__,__NOTHROW_NCX,__localdep_memcmpl,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_dwords),memcmpl,(__s1,__s2,__n_dwords))
#elif defined(__CRT_HAVE_wmemcmp) && (__SIZEOF_WCHAR_T__ == 4)
/* Compare memory buffers and return the difference of the first non-matching dword */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),__INT32_TYPE__,__NOTHROW_NCX,__localdep_memcmpl,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_dwords),wmemcmp,(__s1,__s2,__n_dwords))
#else /* LIBC: memcmpl */
#include <local/string/memcmpl.h>
/* Compare memory buffers and return the difference of the first non-matching dword */
#define __localdep_memcmpl (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcmpl))
#endif /* memcmpl... */
#endif /* !____localdep_memcmpl_defined */

/* Dependency: "memcmp" from "string" */
#ifndef ____localdep_memcmp_defined
#define ____localdep_memcmp_defined 1
#if defined(__fast_memcmp_defined)
/* Compare memory buffers and return the difference of the first non-matching byte
 * @return:  < 0: `s1...+=n_bytes'  < `s2...+=n_bytes'
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return:  > 0: `s1...+=n_bytes'  > `s2...+=n_bytes' */
#define __localdep_memcmp (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcmp))
#elif defined(__CRT_HAVE_memcmp)
/* Compare memory buffers and return the difference of the first non-matching byte
 * @return:  < 0: `s1...+=n_bytes'  < `s2...+=n_bytes'
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return:  > 0: `s1...+=n_bytes'  > `s2...+=n_bytes' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_memcmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes),memcmp,(__s1,__s2,__n_bytes))
#elif defined(__CRT_HAVE_bcmp)
/* Compare memory buffers and return the difference of the first non-matching byte
 * @return:  < 0: `s1...+=n_bytes'  < `s2...+=n_bytes'
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return:  > 0: `s1...+=n_bytes'  > `s2...+=n_bytes' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_memcmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes),bcmp,(__s1,__s2,__n_bytes))
#else /* LIBC: memcmp */
#include <local/string/memcmp.h>
/* Compare memory buffers and return the difference of the first non-matching byte
 * @return:  < 0: `s1...+=n_bytes'  < `s2...+=n_bytes'
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return:  > 0: `s1...+=n_bytes'  > `s2...+=n_bytes' */
#define __localdep_memcmp (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcmp))
#endif /* memcmp... */
#endif /* !____localdep_memcmp_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(wmemcmp) __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(wmemcmp))(__WCHAR_TYPE__ const *__s1,
                                                     __WCHAR_TYPE__ const *__s2,
                                                     __SIZE_TYPE__ __num_chars) {
#line 262 "kos/src/libc/magic/wchar.c"
#if __SIZEOF_WCHAR_T__ == 2
	return __localdep_memcmpw(__s1, __s2, __num_chars);
#elif __SIZEOF_WCHAR_T__ == 4
	return __localdep_memcmpl(__s1, __s2, __num_chars);
#else
	return __localdep_memcmp(__s1, __s2, __num_chars * sizeof(__WCHAR_TYPE__));
#endif
}
__NAMESPACE_LOCAL_END
#endif /* !__local_wmemcmp_defined */
