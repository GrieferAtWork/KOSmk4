/* HASH CRC-32:0x914daa39 */
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
#ifndef __local__strnset_s_defined
#define __local__strnset_s_defined 1
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
__LOCAL_LIBC(_strnset_s) __ATTR_LEAF __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_strnset_s))(char *__restrict __buf,
                                                        __SIZE_TYPE__ __buflen,
                                                        int __ch,
                                                        __SIZE_TYPE__ __maxlen) {
#line 4674 "kos/src/libc/magic/string.c"


	char *__iter;
	__SIZE_TYPE__ __remaining;
	if (__maxlen == 0 && __buf == __NULLPTR && __buflen == 0)
		return 0;
	if (!__buf && __buflen)
		return __EINVAL;
	if (__maxlen >= __buflen)
		return __ERANGE;
	__iter = __buf;
	__remaining = __buflen;
	while (*__iter != 0 && __maxlen && --__remaining) {
		*__iter++ = (__WCHAR_TYPE__)__ch;
		--__maxlen;
	}
	if (!__maxlen) {
		while (*__iter && --__remaining)
			++__iter;
	}
	if (!__remaining) {
		__localdep_memset(__buf, 0, __buflen * sizeof(char));
		return __EINVAL;
	}
	__localdep_memset(__iter, 0, __remaining * sizeof(char));
	return 0;
}
__NAMESPACE_LOCAL_END
#endif /* !__local__strnset_s_defined */
