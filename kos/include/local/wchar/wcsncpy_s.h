/* HASH CRC-32:0xf232847e */
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
#ifndef __local_wcsncpy_s_defined
#define __local_wcsncpy_s_defined 1
#include <parts/errno.h>
/* Dependency: "wmemset" from "wchar" */
#ifndef ____localdep_wmemset_defined
#define ____localdep_wmemset_defined 1
#ifdef __CRT_HAVE_wmemset
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),__WCHAR_TYPE__ *,__NOTHROW_NCX,__localdep_wmemset,(__WCHAR_TYPE__ *__dst, __WCHAR_TYPE__ __filler, __SIZE_TYPE__ __num_chars),wmemset,(__dst,__filler,__num_chars))
#elif defined(__CRT_HAVE_memsetw) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),__WCHAR_TYPE__ *,__NOTHROW_NCX,__localdep_wmemset,(__WCHAR_TYPE__ *__dst, __WCHAR_TYPE__ __filler, __SIZE_TYPE__ __num_chars),memsetw,(__dst,__filler,__num_chars))
#elif defined(__CRT_HAVE_memsetl) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),__WCHAR_TYPE__ *,__NOTHROW_NCX,__localdep_wmemset,(__WCHAR_TYPE__ *__dst, __WCHAR_TYPE__ __filler, __SIZE_TYPE__ __num_chars),memsetl,(__dst,__filler,__num_chars))
#else /* LIBC: wmemset */
#include <local/wchar/wmemset.h>
#define __localdep_wmemset (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wmemset))
#endif /* wmemset... */
#endif /* !____localdep_wmemset_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(wcsncpy_s) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(wcsncpy_s))(__WCHAR_TYPE__ *__dst,
                                                       __SIZE_TYPE__ __dstsize,
                                                       __WCHAR_TYPE__ const *__src,
                                                       __SIZE_TYPE__ __maxlen) {
#line 4554 "kos/src/libc/magic/string.c"


	__WCHAR_TYPE__ *__iter;
	__SIZE_TYPE__ __remaining;
	if (__maxlen == 0 && __dst == __NULLPTR && __dstsize == 0)
		return 0;
	if ((!__dst && __dstsize) || (!__src && __maxlen))
		return __EINVAL;
	if (!__maxlen) {
		__localdep_wmemset(__dst, 0, __dstsize);
		return 0;
	}
	__iter = __dst;
	__remaining = __dstsize;
	if (__maxlen == (__SIZE_TYPE__)-1) {
		while ((*__iter++ = *__src++) != 0 && --__remaining)
			;
	} else {
		if (__maxlen >= __remaining)
			return __ERANGE;
		while ((*__iter++ = *__src++) != 0 && --__remaining && --__maxlen)
			;
		if (!__maxlen)
			*__iter = 0;
	}
	if (!__remaining) {
		if (__maxlen == (__SIZE_TYPE__)-1) {
			__dst[__dstsize - 1] = 0;
			return __STRUNCATE;
		}
		__localdep_wmemset(__dst, 0, __dstsize);
		return __ERANGE;
	}
	__localdep_wmemset(__iter, 0, __remaining);
	return 0;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_wcsncpy_s_defined */
