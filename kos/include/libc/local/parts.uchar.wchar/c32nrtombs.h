/* HASH CRC-32:0xf8299dbf */
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_c32nrtombs_defined
#define __local_c32nrtombs_defined
#include <__crt.h>
#include <hybrid/typecore.h>
#include <bits/crt/mbstate.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_mempcpy_defined
#define __local___localdep_mempcpy_defined
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
#ifndef __local___localdep_uchar_c32rtomb_defined
#define __local___localdep_uchar_c32rtomb_defined
#if defined(__CRT_HAVE_wcrtomb) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(,__SIZE_TYPE__,__NOTHROW_NCX,__localdep_uchar_c32rtomb,(char *__restrict __str, __CHAR32_TYPE__ __wc, struct __mbstate *__mbs),wcrtomb,(__str,__wc,__mbs))
#elif defined(__CRT_HAVE_KOS$wcrtomb)
__CREDIRECT_KOS(,__SIZE_TYPE__,__NOTHROW_NCX,__localdep_uchar_c32rtomb,(char *__restrict __str, __CHAR32_TYPE__ __wc, struct __mbstate *__mbs),wcrtomb,(__str,__wc,__mbs))
#elif defined(__CRT_HAVE_c32rtomb) && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(,__SIZE_TYPE__,__NOTHROW_NCX,__localdep_uchar_c32rtomb,(char *__restrict __str, __CHAR32_TYPE__ __wc, struct __mbstate *__mbs),c32rtomb,(__str,__wc,__mbs))
#elif defined(__CRT_HAVE_KOS$c32rtomb)
__CREDIRECT_KOS(,__SIZE_TYPE__,__NOTHROW_NCX,__localdep_uchar_c32rtomb,(char *__restrict __str, __CHAR32_TYPE__ __wc, struct __mbstate *__mbs),c32rtomb,(__str,__wc,__mbs))
#elif __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcrtomb.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_uchar_c32rtomb __NAMESPACE_LOCAL_TYPEHAX(__SIZE_TYPE__(__LIBKCALL*)(char *__restrict,__CHAR32_TYPE__,struct __mbstate *),__SIZE_TYPE__(__LIBKCALL&)(char *__restrict,__CHAR32_TYPE__,struct __mbstate *),wcrtomb)
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/uchar/uchar_c32rtomb.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_uchar_c32rtomb __LIBC_LOCAL_NAME(uchar_c32rtomb)
#endif /* !... */
#endif /* !__local___localdep_uchar_c32rtomb_defined */
__LOCAL_LIBC(c32nrtombs) __ATTR_NONNULL((2)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBKCALL __LIBC_LOCAL_NAME(c32nrtombs))(char *__dst, __CHAR32_TYPE__ const **__restrict __psrc, __SIZE_TYPE__ __nwc, __SIZE_TYPE__ __dstlen, struct __mbstate *__mbs) {
	__SIZE_TYPE__ __result = 0;
	__CHAR32_TYPE__ const *__src = *__psrc;
	while (__dstlen) {
		__SIZE_TYPE__ __error;
		char __buf[7];
		__CHAR32_TYPE__ __ch;
		if (!__nwc) {
			__src = __NULLPTR; /* (implicit) NUL-character reached */
			break;
		}
		__ch = *__src;
		__error = (__NAMESPACE_LOCAL_SYM __localdep_uchar_c32rtomb)(__buf, __ch, __mbs);
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
		if (__ch == (__CHAR32_TYPE__)'\0') {
			__src = __NULLPTR; /* NUL-character reached */
			break;
		}
	}
	if (__dst != __NULLPTR)
		*__psrc = __src; /* Only update source if destination was given */
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c32nrtombs_defined
#define __local___localdep_c32nrtombs_defined
#define __localdep_c32nrtombs __LIBC_LOCAL_NAME(c32nrtombs)
#endif /* !__local___localdep_c32nrtombs_defined */
#endif /* !__local_c32nrtombs_defined */
