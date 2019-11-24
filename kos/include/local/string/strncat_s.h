/* HASH CRC-32:0xc840f365 */
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
#ifndef __local_strncat_s_defined
#define __local_strncat_s_defined 1
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/string.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */
#include <parts/errno.h>
/* Dependency: "memset" from "string" */
#ifndef ____localdep_memset_defined
#define ____localdep_memset_defined 1
#ifdef __fast_memset_defined
/* Fill memory with a given byte
 * @return: * : Always re-returns `dst' */
#define __localdep_memset (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memset))
#elif defined(__CRT_HAVE_memset)
/* Fill memory with a given byte
 * @return: * : Always re-returns `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,__localdep_memset,(void *__restrict __dst, int __byte, __SIZE_TYPE__ __n_bytes),memset,(__dst,__byte,__n_bytes))
#else /* LIBC: memset */
#include <local/string/memset.h>
/* Fill memory with a given byte
 * @return: * : Always re-returns `dst' */
#define __localdep_memset (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memset))
#endif /* memset... */
#endif /* !____localdep_memset_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(strncat_s) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strncat_s))(char *__dst,
                                                       __SIZE_TYPE__ __dstsize,
                                                       const char *__src,
                                                       __SIZE_TYPE__ __maxlen) {
#line 4934 "kos/src/libc/magic/string.c"


	char *__iter;
	__SIZE_TYPE__ __remaining;
	if (!__maxlen && !__dst && !__dstsize)
		return 0;
	if ((!__dst && __dstsize) || (!__src && __maxlen))
		return __EINVAL;
	for (__iter = __dst, __remaining = __dstsize; __remaining && *__iter; ++__iter, --__remaining)
		;
	if (!__remaining) {
		__localdep_memset(__dst, 0, __dstsize * sizeof(char));
		return __EINVAL;
	}
	if (__maxlen == (__SIZE_TYPE__)-1) {
		while ((*__iter++ = *__src++) != 0 && --__dstsize)
			;
	} else {
		if (__maxlen >= __remaining)
			return __ERANGE;
		while (__maxlen && (*__iter++ = *__src++) != 0 && --__remaining)
			--__maxlen;
		if (!__maxlen)
			*__iter = 0;
	}
	if (!__remaining) {
		if (__maxlen == (__SIZE_TYPE__)-1) {
			__dst[__dstsize - 1] = 0;
			return __STRUNCATE;
		}
		__localdep_memset(__dst, 0, __dstsize * sizeof(char));
		return __ERANGE;
	}
	__localdep_memset(__iter, 0, __remaining * sizeof(char));
	return 0;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_strncat_s_defined */
