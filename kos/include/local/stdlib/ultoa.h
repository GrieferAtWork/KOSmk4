/* HASH CRC-32:0xc49694f4 */
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_ultoa_defined
#define __local_ultoa_defined 1
/* Dependency: "_ultoa_s" from "stdlib" */
#ifndef ____localdep__ultoa_s_defined
#define ____localdep__ultoa_s_defined 1
#ifdef __CRT_HAVE__ultoa_s
__CREDIRECT(__ATTR_NONNULL((2)),__errno_t,__NOTHROW_NCX,__localdep__ultoa_s,(unsigned long __val, char *__buf, __SIZE_TYPE__ __bufsize, int __radix),_ultoa_s,(__val,__buf,__bufsize,__radix))
#elif defined(__CRT_HAVE_ultoa_s)
__CREDIRECT(__ATTR_NONNULL((2)),__errno_t,__NOTHROW_NCX,__localdep__ultoa_s,(unsigned long __val, char *__buf, __SIZE_TYPE__ __bufsize, int __radix),ultoa_s,(__val,__buf,__bufsize,__radix))
#elif defined(__CRT_HAVE__ui64toa_s) && (__SIZEOF_LONG__ == 8)
__CREDIRECT(__ATTR_NONNULL((2)),__errno_t,__NOTHROW_NCX,__localdep__ultoa_s,(unsigned long __val, char *__buf, __SIZE_TYPE__ __bufsize, int __radix),_ui64toa_s,(__val,__buf,__bufsize,__radix))
#elif defined(__CRT_HAVE_ui64toa_s) && (__SIZEOF_LONG__ == 8)
__CREDIRECT(__ATTR_NONNULL((2)),__errno_t,__NOTHROW_NCX,__localdep__ultoa_s,(unsigned long __val, char *__buf, __SIZE_TYPE__ __bufsize, int __radix),ui64toa_s,(__val,__buf,__bufsize,__radix))
#else /* LIBC: _ultoa_s */
#include <local/stdlib/_ultoa_s.h>
#define __localdep__ultoa_s (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_ultoa_s))
#endif /* _ultoa_s... */
#endif /* !____localdep__ultoa_s_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(ultoa) __ATTR_NONNULL((2)) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(ultoa))(unsigned long __val,
                                                   char *__dst,
                                                   int __radix) {
#line 2990 "kos/src/libc/magic/stdlib.c"
	__localdep__ultoa_s(__val, __dst, (__SIZE_TYPE__)-1, __radix);
	return __dst;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_ultoa_defined */
