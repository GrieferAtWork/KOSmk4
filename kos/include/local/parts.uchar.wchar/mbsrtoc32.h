/* HASH CRC-32:0xbeec9c33 */
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
#ifndef __local_mbsrtoc32_defined
#define __local_mbsrtoc32_defined 1
#include <__crt.h>
#include <bits/mbstate.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: uchar_mbrtoc32 from uchar */
#ifndef __local___localdep_uchar_mbrtoc32_defined
#define __local___localdep_uchar_mbrtoc32_defined 1
#if defined(__CRT_HAVE_mbrtowc) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(,__SIZE_TYPE__,__NOTHROW_NCX,__localdep_uchar_mbrtoc32,(__CHAR32_TYPE__ *__pwc, char const *__restrict __str, __SIZE_TYPE__ __maxlen, __mbstate_t *__mbs),mbrtowc,(__pwc,__str,__maxlen,__mbs))
#elif defined(__CRT_HAVE_KOS$mbrtowc)
__CREDIRECT_KOS(,__SIZE_TYPE__,__NOTHROW_NCX,__localdep_uchar_mbrtoc32,(__CHAR32_TYPE__ *__pwc, char const *__restrict __str, __SIZE_TYPE__ __maxlen, __mbstate_t *__mbs),mbrtowc,(__pwc,__str,__maxlen,__mbs))
#elif defined(__CRT_HAVE___mbrtowc) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(,__SIZE_TYPE__,__NOTHROW_NCX,__localdep_uchar_mbrtoc32,(__CHAR32_TYPE__ *__pwc, char const *__restrict __str, __SIZE_TYPE__ __maxlen, __mbstate_t *__mbs),__mbrtowc,(__pwc,__str,__maxlen,__mbs))
#elif defined(__CRT_HAVE_KOS$__mbrtowc)
__CREDIRECT_KOS(,__SIZE_TYPE__,__NOTHROW_NCX,__localdep_uchar_mbrtoc32,(__CHAR32_TYPE__ *__pwc, char const *__restrict __str, __SIZE_TYPE__ __maxlen, __mbstate_t *__mbs),__mbrtowc,(__pwc,__str,__maxlen,__mbs))
#elif defined(__CRT_HAVE_mbrtoc32) && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(,__SIZE_TYPE__,__NOTHROW_NCX,__localdep_uchar_mbrtoc32,(__CHAR32_TYPE__ *__pwc, char const *__restrict __str, __SIZE_TYPE__ __maxlen, __mbstate_t *__mbs),mbrtoc32,(__pwc,__str,__maxlen,__mbs))
#elif defined(__CRT_HAVE_KOS$mbrtoc32)
__CREDIRECT_KOS(,__SIZE_TYPE__,__NOTHROW_NCX,__localdep_uchar_mbrtoc32,(__CHAR32_TYPE__ *__pwc, char const *__restrict __str, __SIZE_TYPE__ __maxlen, __mbstate_t *__mbs),mbrtoc32,(__pwc,__str,__maxlen,__mbs))
#elif __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <local/wchar/mbrtowc.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_uchar_mbrtoc32 (*(__SIZE_TYPE__(__LIBKCALL *)(__CHAR32_TYPE__ *, char const *__restrict, __SIZE_TYPE__, __mbstate_t *))&__LIBC_LOCAL_NAME(mbrtowc))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/uchar/uchar_mbrtoc32.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_uchar_mbrtoc32 __LIBC_LOCAL_NAME(uchar_mbrtoc32)
#endif /* !... */
#endif /* !__local___localdep_uchar_mbrtoc32_defined */
__LOCAL_LIBC(mbsrtoc32) __ATTR_NONNULL((1, 2)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBKCALL __LIBC_LOCAL_NAME(mbsrtoc32))(__CHAR32_TYPE__ *__restrict __dst, char const **__restrict __psrc, __SIZE_TYPE__ __dstlen, __mbstate_t *__mbs) {
	__SIZE_TYPE__ __result = 0;
	char const *__src = *__psrc;
	while (__dstlen) {
		__SIZE_TYPE__ __error;
		__CHAR32_TYPE__ __wc;
		__error = __localdep_uchar_mbrtoc32(&__wc, __src, (__SIZE_TYPE__)-1, __mbs);
		if (!__error)
			break;
		if (__error == (__SIZE_TYPE__)-1)
			return (__SIZE_TYPE__)-1; /* EILSEQ */
		*__dst++ = __wc;
		__src += __error;
		--__dstlen;
		++__result;
	}
	*__psrc = __src;
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_mbsrtoc32_defined
#define __local___localdep_mbsrtoc32_defined 1
#define __localdep_mbsrtoc32 __LIBC_LOCAL_NAME(mbsrtoc32)
#endif /* !__local___localdep_mbsrtoc32_defined */
#endif /* !__local_mbsrtoc32_defined */
