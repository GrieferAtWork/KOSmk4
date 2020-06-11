/* HASH CRC-32:0xfe03f6d0 */
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
#ifndef __local_strto64_defined
#define __local_strto64_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: strtou64 from stdlib */
#ifndef __local___localdep_strtou64_defined
#define __local___localdep_strtou64_defined 1
#ifdef __CRT_HAVE_strtou64
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,__localdep_strtou64,(char const *__restrict __nptr, char **__endptr, int __base),strtou64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__strtoui64)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,__localdep_strtou64,(char const *__restrict __nptr, char **__endptr, int __base),_strtoui64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoul) && (__SIZEOF_LONG__ == 8)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,__localdep_strtou64,(char const *__restrict __nptr, char **__endptr, int __base),strtoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoull) && (__SIZEOF_LONG_LONG__ == 8)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,__localdep_strtou64,(char const *__restrict __nptr, char **__endptr, int __base),strtoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtouq) && (__SIZEOF_LONG_LONG__ == 8)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,__localdep_strtou64,(char const *__restrict __nptr, char **__endptr, int __base),strtouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoumax) && (__SIZEOF_INTMAX_T__ == 8)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,__localdep_strtou64,(char const *__restrict __nptr, char **__endptr, int __base),strtoumax,(__nptr,__endptr,__base))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/stdlib/strtou64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strtou64 __LIBC_LOCAL_NAME(strtou64)
#endif /* !... */
#endif /* !__local___localdep_strtou64_defined */
__LOCAL_LIBC(strto64) __ATTR_LEAF __ATTR_NONNULL((1)) __INT64_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strto64))(char const *__restrict __nptr, char **__endptr, int __base) {
	__UINT64_TYPE__ __result;
	__BOOL __neg = 0;
	while (*__nptr == '-') {
		__neg = !__neg;
		++__nptr;
	}
	__result = __localdep_strtou64(__nptr, __endptr, __base);
	return __neg ? -(__INT64_TYPE__)__result : (__INT64_TYPE__)__result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_strto64_defined
#define __local___localdep_strto64_defined 1
#define __localdep_strto64 __LIBC_LOCAL_NAME(strto64)
#endif /* !__local___localdep_strto64_defined */
#endif /* !__local_strto64_defined */
