/* HASH CRC-32:0x15626b7a */
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
#ifndef __local_c16sto64_defined
#define __local_c16sto64_defined 1
/* Dependency: "wcstou64" from "wchar" */
#ifndef ____localdep_c16stou64_defined
#define ____localdep_c16stou64_defined 1
#if defined(__CRT_HAVE_wcstou64) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,__localdep_c16stou64,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, int __base),wcstou64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstou64)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,__localdep_c16stou64,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, int __base),wcstou64,(__nptr,__endptr,__base))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcstou64.h>
#define __localdep_c16stou64(nptr, endptr, base) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstou64))((__WCHAR_TYPE__ const *)(nptr), (__WCHAR_TYPE__ **)(endptr), base)
#else /* LIBC: c16stou64 */
#include <local/wchar/c16stou64.h>
#define __localdep_c16stou64 (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16stou64))
#endif /* c16stou64... */
#endif /* !____localdep_c16stou64_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(c16sto64) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __INT64_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(c16sto64))(__CHAR16_TYPE__ const *__restrict __nptr,
                                                      __CHAR16_TYPE__ **__endptr,
                                                      int __base) {
#line 981 "kos/src/libc/magic/stdlib.c"
	__UINT64_TYPE__ __result;
	__BOOL __neg = 0;
	while (*__nptr == '-') {
		__neg = !__neg;
		++__nptr;
	}
	__result = __localdep_c16stou64(__nptr, __endptr, __base);
	return __neg ? -(__INT64_TYPE__)__result : (__INT64_TYPE__)__result;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_c16sto64_defined */
