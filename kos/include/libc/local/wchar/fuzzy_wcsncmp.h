/* HASH CRC-32:0x2e85267a */
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
#ifndef __local_fuzzy_wcsncmp_defined
#define __local_fuzzy_wcsncmp_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_fuzzy_wmemcmp_defined
#define __local___localdep_fuzzy_wmemcmp_defined
#ifdef __CRT_HAVE_fuzzy_wmemcmp
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_fuzzy_wmemcmp,(__WCHAR_TYPE__ const *__s1, __SIZE_TYPE__ __s1_chars, __WCHAR_TYPE__ const *__s2, __SIZE_TYPE__ __s2_chars),fuzzy_wmemcmp,(__s1,__s1_chars,__s2,__s2_chars))
#elif defined(__CRT_HAVE_fuzzy_memcmpw) && __SIZEOF_WCHAR_T__ == 2
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_fuzzy_wmemcmp,(__WCHAR_TYPE__ const *__s1, __SIZE_TYPE__ __s1_chars, __WCHAR_TYPE__ const *__s2, __SIZE_TYPE__ __s2_chars),fuzzy_memcmpw,(__s1,__s1_chars,__s2,__s2_chars))
#elif defined(__CRT_HAVE_fuzzy_memcmpl) && __SIZEOF_WCHAR_T__ == 4
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_fuzzy_wmemcmp,(__WCHAR_TYPE__ const *__s1, __SIZE_TYPE__ __s1_chars, __WCHAR_TYPE__ const *__s2, __SIZE_TYPE__ __s2_chars),fuzzy_memcmpl,(__s1,__s1_chars,__s2,__s2_chars))
#elif __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <libc/local/string/fuzzy_memcmpw.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_fuzzy_wmemcmp __NAMESPACE_LOCAL_TYPEHAX(__SIZE_TYPE__(__LIBCCALL*)(__WCHAR_TYPE__ const *,__SIZE_TYPE__,__WCHAR_TYPE__ const *,__SIZE_TYPE__),__SIZE_TYPE__(__LIBCCALL&)(__WCHAR_TYPE__ const *,__SIZE_TYPE__,__WCHAR_TYPE__ const *,__SIZE_TYPE__),fuzzy_memcmpw)
#elif __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <libc/local/string/fuzzy_memcmpl.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_fuzzy_wmemcmp __NAMESPACE_LOCAL_TYPEHAX(__SIZE_TYPE__(__LIBCCALL*)(__WCHAR_TYPE__ const *,__SIZE_TYPE__,__WCHAR_TYPE__ const *,__SIZE_TYPE__),__SIZE_TYPE__(__LIBCCALL&)(__WCHAR_TYPE__ const *,__SIZE_TYPE__,__WCHAR_TYPE__ const *,__SIZE_TYPE__),fuzzy_memcmpl)
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/fuzzy_wmemcmp.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_fuzzy_wmemcmp __LIBC_LOCAL_NAME(fuzzy_wmemcmp)
#endif /* !... */
#endif /* !__local___localdep_fuzzy_wmemcmp_defined */
#ifndef __local___localdep_wcsnlen_defined
#define __local___localdep_wcsnlen_defined
#ifdef __CRT_HAVE_wcsnlen
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_wcsnlen,(__WCHAR_TYPE__ const *__restrict __str, __SIZE_TYPE__ __maxlen),wcsnlen,(__str,__maxlen))
#elif defined(__CRT_HAVE___wcsncnt)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_wcsnlen,(__WCHAR_TYPE__ const *__restrict __str, __SIZE_TYPE__ __maxlen),__wcsncnt,(__str,__maxlen))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcsnlen.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_wcsnlen __LIBC_LOCAL_NAME(wcsnlen)
#endif /* !... */
#endif /* !__local___localdep_wcsnlen_defined */
__LOCAL_LIBC(fuzzy_wcsncmp) __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(fuzzy_wcsncmp))(__WCHAR_TYPE__ const *__s1, __SIZE_TYPE__ __s1_maxlen, __WCHAR_TYPE__ const *__s2, __SIZE_TYPE__ __s2_maxlen) {
	return (__NAMESPACE_LOCAL_SYM __localdep_fuzzy_wmemcmp)(__s1, (__NAMESPACE_LOCAL_SYM __localdep_wcsnlen)(__s1, __s1_maxlen), __s2, (__NAMESPACE_LOCAL_SYM __localdep_wcsnlen)(__s2, __s2_maxlen));
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_fuzzy_wcsncmp_defined
#define __local___localdep_fuzzy_wcsncmp_defined
#define __localdep_fuzzy_wcsncmp __LIBC_LOCAL_NAME(fuzzy_wcsncmp)
#endif /* !__local___localdep_fuzzy_wcsncmp_defined */
#endif /* !__local_fuzzy_wcsncmp_defined */
