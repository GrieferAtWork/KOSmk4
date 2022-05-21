/* HASH CRC-32:0x50bae142 */
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
#ifndef __local_fuzzy_wmemcmp_defined
#define __local_fuzzy_wmemcmp_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_fuzzy_memcmp_defined
#define __local___localdep_fuzzy_memcmp_defined
#ifdef __CRT_HAVE_fuzzy_memcmp
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_ROS(1, 2) __ATTR_ACCESS_ROS(3, 4) __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_fuzzy_memcmp,(void const *__s1, __SIZE_TYPE__ __s1_bytes, void const *__s2, __SIZE_TYPE__ __s2_bytes),fuzzy_memcmp,(__s1,__s1_bytes,__s2,__s2_bytes))
#else /* __CRT_HAVE_fuzzy_memcmp */
__NAMESPACE_LOCAL_END
#include <parts/malloca.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __NO_MALLOCA
__NAMESPACE_LOCAL_END
#include <libc/local/string/fuzzy_memcmp.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_fuzzy_memcmp __LIBC_LOCAL_NAME(fuzzy_memcmp)
#else /* !__NO_MALLOCA */
#undef __local___localdep_fuzzy_memcmp_defined
#endif /* __NO_MALLOCA */
#endif /* !__CRT_HAVE_fuzzy_memcmp */
#endif /* !__local___localdep_fuzzy_memcmp_defined */
#ifndef __local___localdep_fuzzy_memcmpl_defined
#define __local___localdep_fuzzy_memcmpl_defined
#ifdef __CRT_HAVE_fuzzy_memcmpl
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO(1) __ATTR_ACCESS_RO(3),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_fuzzy_memcmpl,(void const *__s1, __SIZE_TYPE__ __s1_dwords, void const *__s2, __SIZE_TYPE__ __s2_dwords),fuzzy_memcmpl,(__s1,__s1_dwords,__s2,__s2_dwords))
#elif defined(__CRT_HAVE_fuzzy_wmemcmp) && __SIZEOF_WCHAR_T__ == 4
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO(1) __ATTR_ACCESS_RO(3),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_fuzzy_memcmpl,(void const *__s1, __SIZE_TYPE__ __s1_dwords, void const *__s2, __SIZE_TYPE__ __s2_dwords),fuzzy_wmemcmp,(__s1,__s1_dwords,__s2,__s2_dwords))
#elif defined(__CRT_HAVE_KOS$fuzzy_wmemcmp) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_CREDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO(1) __ATTR_ACCESS_RO(3),__SIZE_TYPE__,__NOTHROW_NCX,__LIBCCALL,__localdep_fuzzy_memcmpl,(void const *__s1, __SIZE_TYPE__ __s1_dwords, void const *__s2, __SIZE_TYPE__ __s2_dwords),KOS$fuzzy_wmemcmp,(__s1,__s1_dwords,__s2,__s2_dwords))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <parts/malloca.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __NO_MALLOCA
__NAMESPACE_LOCAL_END
#include <libc/local/string/fuzzy_memcmpl.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_fuzzy_memcmpl __LIBC_LOCAL_NAME(fuzzy_memcmpl)
#else /* !__NO_MALLOCA */
#undef __local___localdep_fuzzy_memcmpl_defined
#endif /* __NO_MALLOCA */
#endif /* !... */
#endif /* !__local___localdep_fuzzy_memcmpl_defined */
#ifndef __local___localdep_fuzzy_memcmpw_defined
#define __local___localdep_fuzzy_memcmpw_defined
#ifdef __CRT_HAVE_fuzzy_memcmpw
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO(1) __ATTR_ACCESS_RO(3),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_fuzzy_memcmpw,(void const *__s1, __SIZE_TYPE__ __s1_words, void const *__s2, __SIZE_TYPE__ __s2_words),fuzzy_memcmpw,(__s1,__s1_words,__s2,__s2_words))
#elif defined(__CRT_HAVE_fuzzy_wmemcmp) && __SIZEOF_WCHAR_T__ == 2
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO(1) __ATTR_ACCESS_RO(3),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_fuzzy_memcmpw,(void const *__s1, __SIZE_TYPE__ __s1_words, void const *__s2, __SIZE_TYPE__ __s2_words),fuzzy_wmemcmp,(__s1,__s1_words,__s2,__s2_words))
#elif defined(__CRT_HAVE_DOS$fuzzy_wmemcmp) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_CREDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO(1) __ATTR_ACCESS_RO(3),__SIZE_TYPE__,__NOTHROW_NCX,__LIBCCALL,__localdep_fuzzy_memcmpw,(void const *__s1, __SIZE_TYPE__ __s1_words, void const *__s2, __SIZE_TYPE__ __s2_words),DOS$fuzzy_wmemcmp,(__s1,__s1_words,__s2,__s2_words))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <parts/malloca.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __NO_MALLOCA
__NAMESPACE_LOCAL_END
#include <libc/local/string/fuzzy_memcmpw.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_fuzzy_memcmpw __LIBC_LOCAL_NAME(fuzzy_memcmpw)
#else /* !__NO_MALLOCA */
#undef __local___localdep_fuzzy_memcmpw_defined
#endif /* __NO_MALLOCA */
#endif /* !... */
#endif /* !__local___localdep_fuzzy_memcmpw_defined */
__LOCAL_LIBC(fuzzy_wmemcmp) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(fuzzy_wmemcmp))(__WCHAR_TYPE__ const *__s1, __SIZE_TYPE__ __s1_chars, __WCHAR_TYPE__ const *__s2, __SIZE_TYPE__ __s2_chars) {
#if __SIZEOF_WCHAR_T__ == 2
	return (__NAMESPACE_LOCAL_SYM __localdep_fuzzy_memcmpw)(__s1, __s1_chars, __s2, __s2_chars);
#elif __SIZEOF_WCHAR_T__ == 4
	return (__NAMESPACE_LOCAL_SYM __localdep_fuzzy_memcmpl)(__s1, __s1_chars, __s2, __s2_chars);
#else /* ... */
	return (__NAMESPACE_LOCAL_SYM __localdep_fuzzy_memcmp)(__s1, __s1_chars * sizeof(__WCHAR_TYPE__), __s2, __s2_chars * sizeof(__WCHAR_TYPE__));
#endif /* !... */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_fuzzy_wmemcmp_defined
#define __local___localdep_fuzzy_wmemcmp_defined
#define __localdep_fuzzy_wmemcmp __LIBC_LOCAL_NAME(fuzzy_wmemcmp)
#endif /* !__local___localdep_fuzzy_wmemcmp_defined */
#endif /* !__local_fuzzy_wmemcmp_defined */
