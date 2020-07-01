/* HASH CRC-32:0x37283f5b */
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
#ifndef __local_fuzzy_c16scasecmp_l_defined
#define __local_fuzzy_c16scasecmp_l_defined 1
#include <__crt.h>
#include <parts/malloca.h>
#if (defined(__CRT_HAVE_fuzzy_wmemcasecmp_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$fuzzy_wmemcasecmp_l) || !defined(__NO_MALLOCA)
__NAMESPACE_LOCAL_BEGIN
/* Dependency: c16slen from parts.uchar.string */
#ifndef __local___localdep_c16slen_defined
#define __local___localdep_c16slen_defined 1
#if defined(__CRT_HAVE_wcslen) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c16slen,(__CHAR16_TYPE__ const *__restrict __string),wcslen,(__string))
#elif defined(__CRT_HAVE_DOS$wcslen)
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c16slen,(__CHAR16_TYPE__ const *__restrict __string),wcslen,(__string))
#elif __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <local/wchar/wcslen.h>
__NAMESPACE_LOCAL_BEGIN
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
#define __localdep_c16slen (*(__SIZE_TYPE__(__LIBDCALL *)(__CHAR16_TYPE__ const *__restrict))&__LIBC_LOCAL_NAME(wcslen))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/parts.uchar.string/c16slen.h>
__NAMESPACE_LOCAL_BEGIN
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
#define __localdep_c16slen __LIBC_LOCAL_NAME(c16slen)
#endif /* !... */
#endif /* !__local___localdep_c16slen_defined */
/* Dependency: fuzzy_c16memcasecmp_l from parts.uchar.string */
#ifndef __local___localdep_fuzzy_c16memcasecmp_l_defined
#define __local___localdep_fuzzy_c16memcasecmp_l_defined 1
#if defined(__CRT_HAVE_fuzzy_wmemcasecmp_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_fuzzy_c16memcasecmp_l,(__CHAR16_TYPE__ const *__s1, __SIZE_TYPE__ __s1_bytes, __CHAR16_TYPE__ const *__s2, __SIZE_TYPE__ __s2_bytes, __locale_t __locale),fuzzy_wmemcasecmp_l,(__s1,__s1_bytes,__s2,__s2_bytes,__locale))
#elif defined(__CRT_HAVE_DOS$fuzzy_wmemcasecmp_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_fuzzy_c16memcasecmp_l,(__CHAR16_TYPE__ const *__s1, __SIZE_TYPE__ __s1_bytes, __CHAR16_TYPE__ const *__s2, __SIZE_TYPE__ __s2_bytes, __locale_t __locale),fuzzy_wmemcasecmp_l,(__s1,__s1_bytes,__s2,__s2_bytes,__locale))
#elif !defined(__NO_MALLOCA) && __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <local/wchar/fuzzy_wmemcasecmp_l.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_fuzzy_c16memcasecmp_l (*(__SIZE_TYPE__(__LIBDCALL *)(__CHAR16_TYPE__ const *, __SIZE_TYPE__, __CHAR16_TYPE__ const *, __SIZE_TYPE__, __locale_t))&__LIBC_LOCAL_NAME(fuzzy_wmemcasecmp_l))
#elif !defined(__NO_MALLOCA)
__NAMESPACE_LOCAL_END
#include <local/parts.uchar.string/fuzzy_c16memcasecmp_l.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_fuzzy_c16memcasecmp_l __LIBC_LOCAL_NAME(fuzzy_c16memcasecmp_l)
#else /* ... */
#undef __local___localdep_fuzzy_c16memcasecmp_l_defined
#endif /* !... */
#endif /* !__local___localdep_fuzzy_c16memcasecmp_l_defined */
__LOCAL_LIBC(fuzzy_c16scasecmp_l) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(fuzzy_c16scasecmp_l))(__CHAR16_TYPE__ const *__s1, __CHAR16_TYPE__ const *__s2, __locale_t __locale) {
	return __localdep_fuzzy_c16memcasecmp_l(__s1, __localdep_c16slen(__s1), __s2, __localdep_c16slen(__s2), __locale);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_fuzzy_c16scasecmp_l_defined
#define __local___localdep_fuzzy_c16scasecmp_l_defined 1
#define __localdep_fuzzy_c16scasecmp_l __LIBC_LOCAL_NAME(fuzzy_c16scasecmp_l)
#endif /* !__local___localdep_fuzzy_c16scasecmp_l_defined */
#else /* (__CRT_HAVE_fuzzy_wmemcasecmp_l && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$fuzzy_wmemcasecmp_l || !__NO_MALLOCA */
#undef __local_fuzzy_c16scasecmp_l_defined
#endif /* (!__CRT_HAVE_fuzzy_wmemcasecmp_l || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$fuzzy_wmemcasecmp_l && __NO_MALLOCA */
#endif /* !__local_fuzzy_c16scasecmp_l_defined */
