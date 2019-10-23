/* HASH CRC-32:0xd1c4543f */
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
#ifndef __local_itoa_defined
#define __local_itoa_defined 1
/* Dependency: "_itoa_s" from "stdlib" */
#ifndef ____localdep__itoa_s_defined
#define ____localdep__itoa_s_defined 1
#if defined(__CRT_HAVE__itoa_s)
__CREDIRECT(__ATTR_NONNULL((2)),__errno_t,__NOTHROW_NCX,__localdep__itoa_s,(int __val, char *__buf, __SIZE_TYPE__ __bufsize, int __radix),_itoa_s,(__val,__buf,__bufsize,__radix))
#elif defined(__CRT_HAVE_itoa_s)
__CREDIRECT(__ATTR_NONNULL((2)),__errno_t,__NOTHROW_NCX,__localdep__itoa_s,(int __val, char *__buf, __SIZE_TYPE__ __bufsize, int __radix),itoa_s,(__val,__buf,__bufsize,__radix))
#elif defined(__CRT_HAVE__ltoa_s) && (__SIZEOF_INT__ == __SIZEOF_LONG__)
__CREDIRECT(__ATTR_NONNULL((2)),__errno_t,__NOTHROW_NCX,__localdep__itoa_s,(int __val, char *__buf, __SIZE_TYPE__ __bufsize, int __radix),_ltoa_s,(__val,__buf,__bufsize,__radix))
#elif defined(__CRT_HAVE_ltoa_s) && (__SIZEOF_INT__ == __SIZEOF_LONG__)
__CREDIRECT(__ATTR_NONNULL((2)),__errno_t,__NOTHROW_NCX,__localdep__itoa_s,(int __val, char *__buf, __SIZE_TYPE__ __bufsize, int __radix),ltoa_s,(__val,__buf,__bufsize,__radix))
#elif defined(__CRT_HAVE__i64toa_s) && (__SIZEOF_INT__ == 8)
__CREDIRECT(__ATTR_NONNULL((2)),__errno_t,__NOTHROW_NCX,__localdep__itoa_s,(int __val, char *__buf, __SIZE_TYPE__ __bufsize, int __radix),_i64toa_s,(__val,__buf,__bufsize,__radix))
#elif defined(__CRT_HAVE_i64toa_s) && (__SIZEOF_INT__ == 8)
__CREDIRECT(__ATTR_NONNULL((2)),__errno_t,__NOTHROW_NCX,__localdep__itoa_s,(int __val, char *__buf, __SIZE_TYPE__ __bufsize, int __radix),i64toa_s,(__val,__buf,__bufsize,__radix))
#else /* LIBC: _itoa_s */
#include <local/stdlib/_itoa_s.h>
#define __localdep__itoa_s (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_itoa_s))
#endif /* _itoa_s... */
#endif /* !____localdep__itoa_s_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(itoa) __ATTR_NONNULL((2)) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(itoa))(int __val,
                                                  char *__dst,
                                                  int __radix) {
#line 2639 "kos/src/libc/magic/stdlib.c"
	__localdep__itoa_s(__val, __dst, (__SIZE_TYPE__)-1, __radix);
	return __dst;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_itoa_defined */
