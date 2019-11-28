/* HASH CRC-32:0x9c3290f1 */
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
#ifndef __local_fuzzy_c16cmp_defined
#if !defined(__NO_MALLOCA) || defined(__CRT_HAVE_fuzzy_wmemcmp)
#define __local_fuzzy_c16cmp_defined 1
#include <parts/malloca.h>
/* Dependency: "fuzzy_wmemcmp" from "wchar" */
#ifndef ____localdep_fuzzy_c16memcmp_defined
#define ____localdep_fuzzy_c16memcmp_defined 1
#if defined(__CRT_HAVE_fuzzy_wmemcmp) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_fuzzy_c16memcmp,(__CHAR16_TYPE__ const *__s1, __SIZE_TYPE__ __s1_chars, __CHAR16_TYPE__ const *__s2, __SIZE_TYPE__ __s2_chars),fuzzy_wmemcmp,(__s1,__s1_chars,__s2,__s2_chars))
#elif defined(__CRT_HAVE_DOS$fuzzy_wmemcmp)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_fuzzy_c16memcmp,(__CHAR16_TYPE__ const *__s1, __SIZE_TYPE__ __s1_chars, __CHAR16_TYPE__ const *__s2, __SIZE_TYPE__ __s2_chars),fuzzy_wmemcmp,(__s1,__s1_chars,__s2,__s2_chars))
#elif !defined(__NO_MALLOCA)
#if __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/fuzzy_wmemcmp.h>
#define __localdep_fuzzy_c16memcmp(s1, s1_chars, s2, s2_chars) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wmemcmp))((__WCHAR_TYPE__ const *)(s1), s1_chars, (__WCHAR_TYPE__ const *)(s2), s2_chars)
#else /* LIBC: fuzzy_c16memcmp */
#include <local/wchar/fuzzy_c16memcmp.h>
#define __localdep_fuzzy_c16memcmp (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_c16memcmp))
#endif /* LIBC: fuzzy_c16memcmp */
#else /* CUSTOM: fuzzy_wmemcmp */
#undef ____localdep_fuzzy_c16memcmp_defined
#endif /* fuzzy_c16memcmp... */
#endif /* !____localdep_fuzzy_c16memcmp_defined */

/* Dependency: "wcslen" from "wchar" */
#ifndef ____localdep_c16len_defined
#define ____localdep_c16len_defined 1
#if defined(__CRT_HAVE_wcslen) && (__SIZEOF_WCHAR_T__ == 2)
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c16len,(__CHAR16_TYPE__ const *__restrict __string),wcslen,(__string))
#elif defined(__CRT_HAVE_DOS$wcslen)
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c16len,(__CHAR16_TYPE__ const *__restrict __string),wcslen,(__string))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcslen.h>
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
#define __localdep_c16len(string) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcslen))((__WCHAR_TYPE__ const *)(string))
#else /* LIBC: c16len */
#include <local/wchar/c16len.h>
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
#define __localdep_c16len (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16len))
#endif /* c16len... */
#endif /* !____localdep_c16len_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(fuzzy_c16cmp) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(fuzzy_c16cmp))(__CHAR16_TYPE__ const *__s1,
                                                          __CHAR16_TYPE__ const *__s2) {
#line 1474 "kos/src/libc/magic/wchar.c"
	return __localdep_fuzzy_c16memcmp(__s1, __localdep_c16len(__s1), __s2, __localdep_c16len(__s2));
}
__NAMESPACE_LOCAL_END
#endif /* !__NO_MALLOCA || __CRT_HAVE_fuzzy_wmemcmp */
#endif /* !__local_fuzzy_c16cmp_defined */
