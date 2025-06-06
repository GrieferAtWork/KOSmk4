/* HASH CRC-32:0x77cf8a24 */
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
#ifndef __local_fuzzy_c32ncasecmp_l_defined
#define __local_fuzzy_c32ncasecmp_l_defined
#include <__crt.h>
#include <parts/malloca.h>
#if (defined(__CRT_HAVE_fuzzy_wmemcasecmp_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$fuzzy_wmemcasecmp_l) || !defined(__NO_MALLOCA)
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_c32nlen_defined
#define __local___localdep_c32nlen_defined
#if defined(__CRT_HAVE_wcsnlen) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c32nlen,(__CHAR32_TYPE__ const *__restrict __str, __SIZE_TYPE__ __maxlen),wcsnlen,(__str,__maxlen))
#elif defined(__CRT_HAVE_KOS$wcsnlen)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c32nlen,(__CHAR32_TYPE__ const *__restrict __str, __SIZE_TYPE__ __maxlen),wcsnlen,(__str,__maxlen))
#elif defined(__CRT_HAVE___wcsncnt) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c32nlen,(__CHAR32_TYPE__ const *__restrict __str, __SIZE_TYPE__ __maxlen),__wcsncnt,(__str,__maxlen))
#elif defined(__CRT_HAVE_KOS$__wcsncnt)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c32nlen,(__CHAR32_TYPE__ const *__restrict __str, __SIZE_TYPE__ __maxlen),__wcsncnt,(__str,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcsnlen.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c32nlen __NAMESPACE_LOCAL_TYPEHAX(__SIZE_TYPE__(__LIBKCALL*)(__CHAR32_TYPE__ const *__restrict,__SIZE_TYPE__),__SIZE_TYPE__(__LIBKCALL&)(__CHAR32_TYPE__ const *__restrict,__SIZE_TYPE__),wcsnlen)
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.string/c32nlen.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c32nlen __LIBC_LOCAL_NAME(c32nlen)
#endif /* !... */
#endif /* !__local___localdep_c32nlen_defined */
#ifndef __local___localdep_fuzzy_c32memcasecmp_l_defined
#define __local___localdep_fuzzy_c32memcasecmp_l_defined
#if defined(__CRT_HAVE_fuzzy_wmemcasecmp_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_fuzzy_c32memcasecmp_l,(__CHAR32_TYPE__ const *__s1, __SIZE_TYPE__ __s1_bytes, __CHAR32_TYPE__ const *__s2, __SIZE_TYPE__ __s2_bytes, __locale_t __locale),fuzzy_wmemcasecmp_l,(__s1,__s1_bytes,__s2,__s2_bytes,__locale))
#elif defined(__CRT_HAVE_KOS$fuzzy_wmemcasecmp_l)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_fuzzy_c32memcasecmp_l,(__CHAR32_TYPE__ const *__s1, __SIZE_TYPE__ __s1_bytes, __CHAR32_TYPE__ const *__s2, __SIZE_TYPE__ __s2_bytes, __locale_t __locale),fuzzy_wmemcasecmp_l,(__s1,__s1_bytes,__s2,__s2_bytes,__locale))
#elif !defined(__NO_MALLOCA) && __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/fuzzy_wmemcasecmp_l.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_fuzzy_c32memcasecmp_l __NAMESPACE_LOCAL_TYPEHAX(__SIZE_TYPE__(__LIBKCALL*)(__CHAR32_TYPE__ const *,__SIZE_TYPE__,__CHAR32_TYPE__ const *,__SIZE_TYPE__,__locale_t),__SIZE_TYPE__(__LIBKCALL&)(__CHAR32_TYPE__ const *,__SIZE_TYPE__,__CHAR32_TYPE__ const *,__SIZE_TYPE__,__locale_t),fuzzy_wmemcasecmp_l)
#elif !defined(__NO_MALLOCA)
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.string/fuzzy_c32memcasecmp_l.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_fuzzy_c32memcasecmp_l __LIBC_LOCAL_NAME(fuzzy_c32memcasecmp_l)
#else /* ... */
#undef __local___localdep_fuzzy_c32memcasecmp_l_defined
#endif /* !... */
#endif /* !__local___localdep_fuzzy_c32memcasecmp_l_defined */
__LOCAL_LIBC(fuzzy_c32ncasecmp_l) __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBKCALL __LIBC_LOCAL_NAME(fuzzy_c32ncasecmp_l))(__CHAR32_TYPE__ const *__s1, __SIZE_TYPE__ __s1_maxlen, __CHAR32_TYPE__ const *__s2, __SIZE_TYPE__ __s2_maxlen, __locale_t __locale) {
	return (__NAMESPACE_LOCAL_SYM __localdep_fuzzy_c32memcasecmp_l)(__s1, (__NAMESPACE_LOCAL_SYM __localdep_c32nlen)(__s1, __s1_maxlen), __s2, (__NAMESPACE_LOCAL_SYM __localdep_c32nlen)(__s2, __s2_maxlen), __locale);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_fuzzy_c32ncasecmp_l_defined
#define __local___localdep_fuzzy_c32ncasecmp_l_defined
#define __localdep_fuzzy_c32ncasecmp_l __LIBC_LOCAL_NAME(fuzzy_c32ncasecmp_l)
#endif /* !__local___localdep_fuzzy_c32ncasecmp_l_defined */
#else /* (__CRT_HAVE_fuzzy_wmemcasecmp_l && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$fuzzy_wmemcasecmp_l || !__NO_MALLOCA */
#undef __local_fuzzy_c32ncasecmp_l_defined
#endif /* (!__CRT_HAVE_fuzzy_wmemcasecmp_l || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$fuzzy_wmemcasecmp_l && __NO_MALLOCA */
#endif /* !__local_fuzzy_c32ncasecmp_l_defined */
