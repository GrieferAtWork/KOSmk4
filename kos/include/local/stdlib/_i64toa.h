/* HASH CRC-32:0x2aa24bce */
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
#ifndef __local__i64toa_defined
#define __local__i64toa_defined 1
/* Dependency: "_i64toa_s" from "stdlib" */
#ifndef ____localdep__i64toa_s_defined
#define ____localdep__i64toa_s_defined 1
#ifdef __CRT_HAVE__i64toa_s
__CREDIRECT(__ATTR_NONNULL((2)),__errno_t,__NOTHROW_NCX,__localdep__i64toa_s,(__INT64_TYPE__ __val, char *__buf, __SIZE_TYPE__ __buflen, int __radix),_i64toa_s,(__val,__buf,__buflen,__radix))
#elif defined(__CRT_HAVE__ltoa_s) && (__SIZEOF_LONG__ == 8)
__CREDIRECT(__ATTR_NONNULL((2)),__errno_t,__NOTHROW_NCX,__localdep__i64toa_s,(__INT64_TYPE__ __val, char *__buf, __SIZE_TYPE__ __buflen, int __radix),_ltoa_s,(__val,__buf,__buflen,__radix))
#elif defined(__CRT_HAVE__itoa_s) && (__SIZEOF_INT__ == 8)
__CREDIRECT(__ATTR_NONNULL((2)),__errno_t,__NOTHROW_NCX,__localdep__i64toa_s,(__INT64_TYPE__ __val, char *__buf, __SIZE_TYPE__ __buflen, int __radix),_itoa_s,(__val,__buf,__buflen,__radix))
#else /* LIBC: _i64toa_s */
#include <local/stdlib/_i64toa_s.h>
#define __localdep__i64toa_s (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_i64toa_s))
#endif /* _i64toa_s... */
#endif /* !____localdep__i64toa_s_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_i64toa) __ATTR_NONNULL((2)) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_i64toa))(__INT64_TYPE__ __val,
                                                     char *__buf,
                                                     int __radix) {
#line 2314 "kos/src/libc/magic/stdlib.c"
	__localdep__i64toa_s(__val, __buf, (__SIZE_TYPE__)-1, __radix);
	return __buf;
}
__NAMESPACE_LOCAL_END
#endif /* !__local__i64toa_defined */
