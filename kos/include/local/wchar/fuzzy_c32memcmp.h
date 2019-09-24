/* HASH CRC-32:0x5f5397c4 */
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
#ifndef __local_fuzzy_c32memcmp_defined
#if !defined(__NO_MALLOCA)
#define __local_fuzzy_c32memcmp_defined 1
#include <parts/malloca.h>
/* Dependency: "fuzzy_memcmpw" from "string" */
#ifndef ____localdep_fuzzy_memcmpw_defined
#define ____localdep_fuzzy_memcmpw_defined 1
#if defined(__CRT_HAVE_fuzzy_memcmpw)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_fuzzy_memcmpw,(void const *__s1, __SIZE_TYPE__ __s1_words, void const *__s2, __SIZE_TYPE__ __s2_words),fuzzy_memcmpw,(__s1,__s1_words,__s2,__s2_words))
#elif !defined(__NO_MALLOCA)
#include <local/string/fuzzy_memcmpw.h>
#define __localdep_fuzzy_memcmpw (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_memcmpw))
#else /* CUSTOM: fuzzy_memcmpw */
#undef ____localdep_fuzzy_memcmpw_defined
#endif /* fuzzy_memcmpw... */
#endif /* !____localdep_fuzzy_memcmpw_defined */

/* Dependency: "fuzzy_memcmpl" from "string" */
#ifndef ____localdep_fuzzy_memcmpl_defined
#define ____localdep_fuzzy_memcmpl_defined 1
#if defined(__CRT_HAVE_fuzzy_memcmpl)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_fuzzy_memcmpl,(void const *__s1, __SIZE_TYPE__ __s1_dwords, void const *__s2, __SIZE_TYPE__ __s2_dwords),fuzzy_memcmpl,(__s1,__s1_dwords,__s2,__s2_dwords))
#elif !defined(__NO_MALLOCA)
#include <local/string/fuzzy_memcmpl.h>
#define __localdep_fuzzy_memcmpl (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_memcmpl))
#else /* CUSTOM: fuzzy_memcmpl */
#undef ____localdep_fuzzy_memcmpl_defined
#endif /* fuzzy_memcmpl... */
#endif /* !____localdep_fuzzy_memcmpl_defined */

/* Dependency: "fuzzy_memcmp" from "string" */
#ifndef ____localdep_fuzzy_memcmp_defined
#define ____localdep_fuzzy_memcmp_defined 1
#if defined(__CRT_HAVE_fuzzy_memcmp)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_fuzzy_memcmp,(void const *__s1, __SIZE_TYPE__ __s1_bytes, void const *__s2, __SIZE_TYPE__ __s2_bytes),fuzzy_memcmp,(__s1,__s1_bytes,__s2,__s2_bytes))
#elif !defined(__NO_MALLOCA)
#include <local/string/fuzzy_memcmp.h>
#define __localdep_fuzzy_memcmp (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_memcmp))
#else /* CUSTOM: fuzzy_memcmp */
#undef ____localdep_fuzzy_memcmp_defined
#endif /* fuzzy_memcmp... */
#endif /* !____localdep_fuzzy_memcmp_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(fuzzy_c32memcmp) __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 3)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(fuzzy_c32memcmp))(__CHAR32_TYPE__ const *__s1,
                                                             __SIZE_TYPE__ __s1_chars,
                                                             __CHAR32_TYPE__ const *__s2,
                                                             __SIZE_TYPE__ __s2_chars) {
#line 1324 "kos/src/libc/magic/wchar.c"
#if 4 == 2
	return __localdep_fuzzy_memcmpw(__s1, __s1_chars, __s2, __s2_chars);
#elif 4 == 4
	return __localdep_fuzzy_memcmpl(__s1, __s1_chars, __s2, __s2_chars);
#else
	return __localdep_fuzzy_memcmp(__s1, __s1_chars * sizeof(__CHAR32_TYPE__), __s2, __s2_chars * sizeof(__CHAR32_TYPE__));
#endif
}
__NAMESPACE_LOCAL_END
#endif /* !defined(__NO_MALLOCA) */
#endif /* !__local_fuzzy_c32memcmp_defined */
