/* HASH CRC-32:0x61114aaf */
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
#ifndef __local_mbsrtowcs_defined
#define __local_mbsrtowcs_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: mbrtowc from wchar */
#ifndef __local___localdep_mbrtowc_defined
#define __local___localdep_mbrtowc_defined 1
#ifdef __CRT_HAVE_mbrtowc
__NAMESPACE_LOCAL_END
#include <bits/mbstate.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(,__SIZE_TYPE__,__NOTHROW_NCX,__localdep_mbrtowc,(__WCHAR_TYPE__ *__pwc, char const *__restrict __str, __SIZE_TYPE__ __maxlen, __mbstate_t *__mbs),mbrtowc,(__pwc,__str,__maxlen,__mbs))
#elif defined(__CRT_HAVE_DOS$mbrtowc) && __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <bits/mbstate.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_KOS(,__SIZE_TYPE__,__NOTHROW_NCX,__localdep_mbrtowc,(__WCHAR_TYPE__ *__pwc, char const *__restrict __str, __SIZE_TYPE__ __maxlen, __mbstate_t *__mbs),mbrtowc,(__pwc,__str,__maxlen,__mbs))
#elif defined(__CRT_HAVE_DOS$mbrtowc) && __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <bits/mbstate.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_DOS(,__SIZE_TYPE__,__NOTHROW_NCX,__localdep_mbrtowc,(__WCHAR_TYPE__ *__pwc, char const *__restrict __str, __SIZE_TYPE__ __maxlen, __mbstate_t *__mbs),mbrtowc,(__pwc,__str,__maxlen,__mbs))
#elif defined(__CRT_HAVE___mbrtowc)
__NAMESPACE_LOCAL_END
#include <bits/mbstate.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(,__SIZE_TYPE__,__NOTHROW_NCX,__localdep_mbrtowc,(__WCHAR_TYPE__ *__pwc, char const *__restrict __str, __SIZE_TYPE__ __maxlen, __mbstate_t *__mbs),__mbrtowc,(__pwc,__str,__maxlen,__mbs))
#elif defined(__CRT_HAVE_DOS$__mbrtowc) && __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <bits/mbstate.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_KOS(,__SIZE_TYPE__,__NOTHROW_NCX,__localdep_mbrtowc,(__WCHAR_TYPE__ *__pwc, char const *__restrict __str, __SIZE_TYPE__ __maxlen, __mbstate_t *__mbs),__mbrtowc,(__pwc,__str,__maxlen,__mbs))
#elif defined(__CRT_HAVE_DOS$__mbrtowc) && __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <bits/mbstate.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_DOS(,__SIZE_TYPE__,__NOTHROW_NCX,__localdep_mbrtowc,(__WCHAR_TYPE__ *__pwc, char const *__restrict __str, __SIZE_TYPE__ __maxlen, __mbstate_t *__mbs),__mbrtowc,(__pwc,__str,__maxlen,__mbs))
#elif defined(__CRT_HAVE_mbrtoc16) && (__SIZEOF_WCHAR_T__ == 2)
__NAMESPACE_LOCAL_END
#include <bits/mbstate.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(,__SIZE_TYPE__,__NOTHROW_NCX,__localdep_mbrtowc,(__WCHAR_TYPE__ *__pwc, char const *__restrict __str, __SIZE_TYPE__ __maxlen, __mbstate_t *__mbs),mbrtoc16,(__pwc,__str,__maxlen,__mbs))
#elif defined(__CRT_HAVE_mbrtoc32) && (__SIZEOF_WCHAR_T__ == 4)
__NAMESPACE_LOCAL_END
#include <bits/mbstate.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(,__SIZE_TYPE__,__NOTHROW_NCX,__localdep_mbrtowc,(__WCHAR_TYPE__ *__pwc, char const *__restrict __str, __SIZE_TYPE__ __maxlen, __mbstate_t *__mbs),mbrtoc32,(__pwc,__str,__maxlen,__mbs))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/wchar/mbrtowc.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_mbrtowc __LIBC_LOCAL_NAME(mbrtowc)
#endif /* !... */
#endif /* !__local___localdep_mbrtowc_defined */
__LOCAL_LIBC(mbsrtowcs) __ATTR_NONNULL((1, 2)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(mbsrtowcs))(__WCHAR_TYPE__ *__restrict __dst, char const **__restrict __psrc, __SIZE_TYPE__ __dstlen, __mbstate_t *__mbs) {
	__SIZE_TYPE__ __result = 0;
	char const *__src = *__psrc;
	while (__dstlen) {
		__SIZE_TYPE__ __error;
		__WCHAR_TYPE__ __wc;
		__error = __localdep_mbrtowc(&__wc, __src, (__SIZE_TYPE__)-1, __mbs);
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
#ifndef __local___localdep_mbsrtowcs_defined
#define __local___localdep_mbsrtowcs_defined 1
#define __localdep_mbsrtowcs __LIBC_LOCAL_NAME(mbsrtowcs)
#endif /* !__local___localdep_mbsrtowcs_defined */
#endif /* !__local_mbsrtowcs_defined */
