/* HASH CRC-32:0xc4f6382d */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_wcsnrtombs_defined
#define __local_wcsnrtombs_defined
#include <__crt.h>
#include <hybrid/typecore.h>
#include <bits/crt/mbstate.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_mempcpy_defined
#define __local___localdep_mempcpy_defined
#ifdef __CRT_HAVE_mempcpy
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_mempcpy,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),mempcpy,(__dst,__src,__n_bytes))
#elif defined(__CRT_HAVE___mempcpy)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_mempcpy,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),__mempcpy,(__dst,__src,__n_bytes))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/mempcpy.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_mempcpy __LIBC_LOCAL_NAME(mempcpy)
#endif /* !... */
#endif /* !__local___localdep_mempcpy_defined */
#ifndef __local___localdep_wcrtomb_defined
#define __local___localdep_wcrtomb_defined
#ifdef __CRT_HAVE_wcrtomb
__CREDIRECT(__ATTR_INOUT_OPT(3) __ATTR_OUT_OPT(1),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_wcrtomb,(char *__restrict __str, __WCHAR_TYPE__ __wc, struct __mbstate *__mbs),wcrtomb,(__str,__wc,__mbs))
#elif defined(__CRT_HAVE_c16rtomb) && __SIZEOF_WCHAR_T__ == 2
__CREDIRECT(__ATTR_INOUT_OPT(3) __ATTR_OUT_OPT(1),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_wcrtomb,(char *__restrict __str, __WCHAR_TYPE__ __wc, struct __mbstate *__mbs),c16rtomb,(__str,__wc,__mbs))
#elif defined(__CRT_HAVE_c32rtomb) && __SIZEOF_WCHAR_T__ == 4
__CREDIRECT(__ATTR_INOUT_OPT(3) __ATTR_OUT_OPT(1),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_wcrtomb,(char *__restrict __str, __WCHAR_TYPE__ __wc, struct __mbstate *__mbs),c32rtomb,(__str,__wc,__mbs))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcrtomb.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_wcrtomb __LIBC_LOCAL_NAME(wcrtomb)
#endif /* !... */
#endif /* !__local___localdep_wcrtomb_defined */
__LOCAL_LIBC(wcsnrtombs) __ATTR_INOUT(2) __ATTR_INOUT_OPT(5) __ATTR_OUT_OPT(1) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(wcsnrtombs))(char *__dst, __WCHAR_TYPE__ const **__restrict __psrc, __SIZE_TYPE__ __nwc, __SIZE_TYPE__ __dstlen, struct __mbstate *__mbs) {
	__SIZE_TYPE__ __result = 0;
	__WCHAR_TYPE__ const *__src = *__psrc;
	while (__dstlen) {
		__SIZE_TYPE__ __error;
		char __buf[7];
		__WCHAR_TYPE__ __ch;
		if (!__nwc) {
			__src = __NULLPTR; /* (implicit) NUL-character reached */
			break;
		}
		__ch = *__src;
		__error = (__NAMESPACE_LOCAL_SYM __localdep_wcrtomb)(__buf, __ch, __mbs);
		if (__error == (__SIZE_TYPE__)-1) {
			__result = (__SIZE_TYPE__)-1; /* EILSEQ */
			break;
		}
		if (__error > __dstlen)
			break;
		if (__dst != __NULLPTR)
			__dst = (char *)(__NAMESPACE_LOCAL_SYM __localdep_mempcpy)(__dst, __buf, __error);
		__result += __error;
		__dstlen -= __error;
		++__src;
		--__nwc;
		if (__ch == (__WCHAR_TYPE__)'\0') {
			__src = __NULLPTR; /* NUL-character reached */
			break;
		}
	}
	if (__dst != __NULLPTR)
		*__psrc = __src; /* Only update source if destination was given */
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_wcsnrtombs_defined
#define __local___localdep_wcsnrtombs_defined
#define __localdep_wcsnrtombs __LIBC_LOCAL_NAME(wcsnrtombs)
#endif /* !__local___localdep_wcsnrtombs_defined */
#endif /* !__local_wcsnrtombs_defined */
