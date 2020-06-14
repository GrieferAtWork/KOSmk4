/* HASH CRC-32:0x8374faf4 */
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
#ifndef __local_fuzzy_c32sncmp_defined
#define __local_fuzzy_c32sncmp_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_fuzzy_memcmpl) || (defined(__CRT_HAVE_fuzzy_wmemcmp) && (__SIZEOF_WCHAR_T__ == 4)) || (defined(__CRT_HAVE_DOS$fuzzy_wmemcmp) && defined(__PE__)) || !defined(__NO_MALLOCA)
__NAMESPACE_LOCAL_BEGIN
/* Dependency: c32snlen from parts.uchar.string */
#ifndef __local___localdep_c32snlen_defined
#define __local___localdep_c32snlen_defined 1
#if defined(__CRT_HAVE_wcsnlen) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
/* Same as `strlen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c32snlen,(__CHAR32_TYPE__ const *__restrict __string, __SIZE_TYPE__ __maxlen),wcsnlen,(__string,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsnlen)
/* Same as `strlen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c32snlen,(__CHAR32_TYPE__ const *__restrict __string, __SIZE_TYPE__ __maxlen),wcsnlen,(__string,__maxlen))
#elif (__SIZEOF_WCHAR_T__ == 4)
__NAMESPACE_LOCAL_END
#include <local/wchar/wcsnlen.h>
__NAMESPACE_LOCAL_BEGIN
/* Same as `strlen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
#define __localdep_c32snlen (*(__SIZE_TYPE__(__LIBKCALL *)(__CHAR32_TYPE__ const *__restrict, __SIZE_TYPE__))&__LIBC_LOCAL_NAME(wcsnlen))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/parts.uchar.string/c32snlen.h>
__NAMESPACE_LOCAL_BEGIN
/* Same as `strlen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
#define __localdep_c32snlen __LIBC_LOCAL_NAME(c32snlen)
#endif /* !... */
#endif /* !__local___localdep_c32snlen_defined */
/* Dependency: fuzzy_memcmpl from string */
#ifndef __local___localdep_fuzzy_memcmpl_defined
#define __local___localdep_fuzzy_memcmpl_defined 1
#ifdef __CRT_HAVE_fuzzy_memcmpl
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_fuzzy_memcmpl,(void const *__s1, __SIZE_TYPE__ __s1_dwords, void const *__s2, __SIZE_TYPE__ __s2_dwords),fuzzy_memcmpl,(__s1,__s1_dwords,__s2,__s2_dwords))
#elif defined(__CRT_HAVE_fuzzy_wmemcmp) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_fuzzy_memcmpl,(void const *__s1, __SIZE_TYPE__ __s1_dwords, void const *__s2, __SIZE_TYPE__ __s2_dwords),fuzzy_wmemcmp,(__s1,__s1_dwords,__s2,__s2_dwords))
#elif defined(__CRT_HAVE_DOS$fuzzy_wmemcmp) && defined(__PE__)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,__LIBCCALL,__localdep_fuzzy_memcmpl,(void const *__s1, __SIZE_TYPE__ __s1_dwords, void const *__s2, __SIZE_TYPE__ __s2_dwords),KOS$fuzzy_wmemcmp,(__s1,__s1_dwords,__s2,__s2_dwords))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <parts/malloca.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __NO_MALLOCA
__NAMESPACE_LOCAL_END
#include <local/string/fuzzy_memcmpl.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_fuzzy_memcmpl __LIBC_LOCAL_NAME(fuzzy_memcmpl)
#else /* !__NO_MALLOCA */
#undef __local___localdep_fuzzy_memcmpl_defined
#endif /* __NO_MALLOCA */
#endif /* !... */
#endif /* !__local___localdep_fuzzy_memcmpl_defined */
__NAMESPACE_LOCAL_END
#include <parts/malloca.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(fuzzy_c32sncmp) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBKCALL __LIBC_LOCAL_NAME(fuzzy_c32sncmp))(__CHAR32_TYPE__ const *__s1, __SIZE_TYPE__ __s1_maxlen, __CHAR32_TYPE__ const *__s2, __SIZE_TYPE__ __s2_maxlen) {
	return __localdep_fuzzy_memcmpl(__s1, __localdep_c32snlen(__s1, __s1_maxlen), __s2, __localdep_c32snlen(__s2, __s2_maxlen));
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_fuzzy_c32sncmp_defined
#define __local___localdep_fuzzy_c32sncmp_defined 1
#define __localdep_fuzzy_c32sncmp __LIBC_LOCAL_NAME(fuzzy_c32sncmp)
#endif /* !__local___localdep_fuzzy_c32sncmp_defined */
#else /* __CRT_HAVE_fuzzy_memcmpl || (__CRT_HAVE_fuzzy_wmemcmp && (__SIZEOF_WCHAR_T__ == 4)) || (__CRT_HAVE_DOS$fuzzy_wmemcmp && __PE__) || !__NO_MALLOCA */
#undef __local_fuzzy_c32sncmp_defined
#endif /* !__CRT_HAVE_fuzzy_memcmpl && (!__CRT_HAVE_fuzzy_wmemcmp || !(__SIZEOF_WCHAR_T__ == 4)) && (!__CRT_HAVE_DOS$fuzzy_wmemcmp || !__PE__) && __NO_MALLOCA */
#endif /* !__local_fuzzy_c32sncmp_defined */
