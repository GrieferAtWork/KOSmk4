/* HASH CRC-32:0x45ea50e7 */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_wcsrtombs_defined
#define __local_wcsrtombs_defined 1
#include <__crt.h>
#include <bits/crt/mbstate.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_mempcpy_defined
#define __local___localdep_mempcpy_defined 1
#ifdef __CRT_HAVE_mempcpy
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_mempcpy,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),mempcpy,(__dst,__src,__n_bytes))
#elif defined(__CRT_HAVE___mempcpy)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_mempcpy,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),__mempcpy,(__dst,__src,__n_bytes))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/mempcpy.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_mempcpy __LIBC_LOCAL_NAME(mempcpy)
#endif /* !... */
#endif /* !__local___localdep_mempcpy_defined */
#ifndef __local___localdep_wcrtomb_defined
#define __local___localdep_wcrtomb_defined 1
#ifdef __CRT_HAVE_wcrtomb
__CREDIRECT(,__SIZE_TYPE__,__NOTHROW_NCX,__localdep_wcrtomb,(char *__restrict __str, __WCHAR_TYPE__ __wc, struct __mbstate *__mbs),wcrtomb,(__str,__wc,__mbs))
#elif defined(__CRT_HAVE_c16rtomb) && __SIZEOF_WCHAR_T__ == 2
__CREDIRECT(,__SIZE_TYPE__,__NOTHROW_NCX,__localdep_wcrtomb,(char *__restrict __str, __WCHAR_TYPE__ __wc, struct __mbstate *__mbs),c16rtomb,(__str,__wc,__mbs))
#elif defined(__CRT_HAVE_c32rtomb) && __SIZEOF_WCHAR_T__ == 4
__CREDIRECT(,__SIZE_TYPE__,__NOTHROW_NCX,__localdep_wcrtomb,(char *__restrict __str, __WCHAR_TYPE__ __wc, struct __mbstate *__mbs),c32rtomb,(__str,__wc,__mbs))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcrtomb.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_wcrtomb __LIBC_LOCAL_NAME(wcrtomb)
#endif /* !... */
#endif /* !__local___localdep_wcrtomb_defined */
__LOCAL_LIBC(wcsrtombs) __ATTR_NONNULL((1, 2)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(wcsrtombs))(char *__dst, __WCHAR_TYPE__ const **__restrict __psrc, __SIZE_TYPE__ __dstlen, struct __mbstate *__mbs) {
	__SIZE_TYPE__ __result = 0;
	__WCHAR_TYPE__ const *__src = *__psrc;
	while (__dstlen) {
		__SIZE_TYPE__ __error;
		char __buf[7];
		__error = __localdep_wcrtomb(__buf, *__src, __mbs);
		if (!__error)
			break;
		if (__error == (__SIZE_TYPE__)-1)
			return (__SIZE_TYPE__)-1; /* EILSEQ */
		if (__error > __dstlen)
			break;
		__dst = (char *)__localdep_mempcpy(__dst, __buf, __error);
		__result += __error;
		__dstlen -= __error;
		++__src;
	}
	*__psrc = __src;
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_wcsrtombs_defined
#define __local___localdep_wcsrtombs_defined 1
#define __localdep_wcsrtombs __LIBC_LOCAL_NAME(wcsrtombs)
#endif /* !__local___localdep_wcsrtombs_defined */
#endif /* !__local_wcsrtombs_defined */
