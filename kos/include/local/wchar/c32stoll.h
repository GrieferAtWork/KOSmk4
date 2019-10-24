/* HASH CRC-32:0x6e623d48 */
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
#ifndef __local_c32stoll_defined
#define __local_c32stoll_defined 1
/* Dependency: "wcsto32" from "wchar" */
#ifndef ____localdep_c32sto32_defined
#define ____localdep_c32sto32_defined 1
#if defined(__CRT_HAVE_wcsto32) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,__localdep_c32sto32,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, int __base),wcsto32,(__nptr,__endptr,__base))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcsto32.h>
#define __localdep_c32sto32(nptr, endptr, base) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsto32))((__WCHAR_TYPE__ const *)(nptr), (__WCHAR_TYPE__ **)(endptr), base)
#else /* LIBC: c32sto32 */
#include <local/wchar/c32sto32.h>
#define __localdep_c32sto32 (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32sto32))
#endif /* c32sto32... */
#endif /* !____localdep_c32sto32_defined */

/* Dependency: "wcsto64" from "wchar" */
#ifndef ____localdep_c32sto64_defined
#define ____localdep_c32sto64_defined 1
#if defined(__CRT_HAVE_wcsto64) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,__localdep_c32sto64,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, int __base),wcsto64,(__nptr,__endptr,__base))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcsto64.h>
#define __localdep_c32sto64(nptr, endptr, base) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsto64))((__WCHAR_TYPE__ const *)(nptr), (__WCHAR_TYPE__ **)(endptr), base)
#else /* LIBC: c32sto64 */
#include <local/wchar/c32sto64.h>
#define __localdep_c32sto64 (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32sto64))
#endif /* c32sto64... */
#endif /* !____localdep_c32sto64_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(c32stoll) __ATTR_NONNULL((1)) __LONGLONG
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(c32stoll))(__CHAR32_TYPE__ const *__restrict __nptr,
                                                      __CHAR32_TYPE__ **__endptr,
                                                      int __base) {
#line 819 "kos/src/libc/magic/stdlib.c"
#if __SIZEOF_LONG_LONG__ <= 4
	return (__LONGLONG)__localdep_c32sto32(__nptr, __endptr, __base);
#else
	return (__LONGLONG)__localdep_c32sto64(__nptr, __endptr, __base);
#endif
}
__NAMESPACE_LOCAL_END
#endif /* !__local_c32stoll_defined */
