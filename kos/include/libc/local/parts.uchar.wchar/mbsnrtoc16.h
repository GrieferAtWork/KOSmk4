/* HASH CRC-32:0x7d09165b */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_mbsnrtoc16_defined
#define __local_mbsnrtoc16_defined
#include <__crt.h>
#include <hybrid/typecore.h>
#include <bits/crt/mbstate.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_bzero_defined
#define __local___localdep_bzero_defined
#ifdef __CRT_HAVE_bzero
__CREDIRECT_VOID(__ATTR_OUTS(1, 2),__NOTHROW_NCX,__localdep_bzero,(void *__restrict __dst, __SIZE_TYPE__ __num_bytes),bzero,(__dst,__num_bytes))
#elif defined(__CRT_HAVE___bzero)
__CREDIRECT_VOID(__ATTR_OUTS(1, 2),__NOTHROW_NCX,__localdep_bzero,(void *__restrict __dst, __SIZE_TYPE__ __num_bytes),__bzero,(__dst,__num_bytes))
#elif defined(__CRT_HAVE_explicit_bzero)
__CREDIRECT_VOID(__ATTR_OUTS(1, 2),__NOTHROW_NCX,__localdep_bzero,(void *__restrict __dst, __SIZE_TYPE__ __num_bytes),explicit_bzero,(__dst,__num_bytes))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/bzero.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_bzero __LIBC_LOCAL_NAME(bzero)
#endif /* !... */
#endif /* !__local___localdep_bzero_defined */
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
#ifndef __local___localdep_uchar_mbrtoc16_defined
#define __local___localdep_uchar_mbrtoc16_defined
#if defined(__CRT_HAVE_mbrtowc) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_INOUT_OPT(4) __ATTR_IN_OPT(2) __ATTR_OUT_OPT(1),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_uchar_mbrtoc16,(__CHAR16_TYPE__ *__pwc, char const *__restrict __str, __SIZE_TYPE__ __maxlen, struct __mbstate *__mbs),mbrtowc,(__pwc,__str,__maxlen,__mbs))
#elif defined(__CRT_HAVE_DOS$mbrtowc)
__CREDIRECT_DOS(__ATTR_INOUT_OPT(4) __ATTR_IN_OPT(2) __ATTR_OUT_OPT(1),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_uchar_mbrtoc16,(__CHAR16_TYPE__ *__pwc, char const *__restrict __str, __SIZE_TYPE__ __maxlen, struct __mbstate *__mbs),mbrtowc,(__pwc,__str,__maxlen,__mbs))
#elif defined(__CRT_HAVE___mbrtowc) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_INOUT_OPT(4) __ATTR_IN_OPT(2) __ATTR_OUT_OPT(1),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_uchar_mbrtoc16,(__CHAR16_TYPE__ *__pwc, char const *__restrict __str, __SIZE_TYPE__ __maxlen, struct __mbstate *__mbs),__mbrtowc,(__pwc,__str,__maxlen,__mbs))
#elif defined(__CRT_HAVE_DOS$__mbrtowc)
__CREDIRECT_DOS(__ATTR_INOUT_OPT(4) __ATTR_IN_OPT(2) __ATTR_OUT_OPT(1),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_uchar_mbrtoc16,(__CHAR16_TYPE__ *__pwc, char const *__restrict __str, __SIZE_TYPE__ __maxlen, struct __mbstate *__mbs),__mbrtowc,(__pwc,__str,__maxlen,__mbs))
#elif defined(__CRT_HAVE_mbrtoc16) && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_INOUT_OPT(4) __ATTR_IN_OPT(2) __ATTR_OUT_OPT(1),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_uchar_mbrtoc16,(__CHAR16_TYPE__ *__pwc, char const *__restrict __str, __SIZE_TYPE__ __maxlen, struct __mbstate *__mbs),mbrtoc16,(__pwc,__str,__maxlen,__mbs))
#elif defined(__CRT_HAVE_DOS$mbrtoc16)
__CREDIRECT_DOS(__ATTR_INOUT_OPT(4) __ATTR_IN_OPT(2) __ATTR_OUT_OPT(1),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_uchar_mbrtoc16,(__CHAR16_TYPE__ *__pwc, char const *__restrict __str, __SIZE_TYPE__ __maxlen, struct __mbstate *__mbs),mbrtoc16,(__pwc,__str,__maxlen,__mbs))
#elif __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/mbrtowc.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_uchar_mbrtoc16 __NAMESPACE_LOCAL_TYPEHAX(__SIZE_TYPE__(__LIBDCALL*)(__CHAR16_TYPE__ *,char const *__restrict,__SIZE_TYPE__,struct __mbstate *),__SIZE_TYPE__(__LIBDCALL&)(__CHAR16_TYPE__ *,char const *__restrict,__SIZE_TYPE__,struct __mbstate *),mbrtowc)
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/uchar/uchar_mbrtoc16.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_uchar_mbrtoc16 __LIBC_LOCAL_NAME(uchar_mbrtoc16)
#endif /* !... */
#endif /* !__local___localdep_uchar_mbrtoc16_defined */
__LOCAL_LIBC(mbsnrtoc16) __ATTR_INOUT(2) __ATTR_INOUT_OPT(5) __ATTR_OUT_OPT(1) __SIZE_TYPE__
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(mbsnrtoc16))(__CHAR16_TYPE__ *__restrict __dst, char const **__restrict __psrc, __SIZE_TYPE__ __nmc, __SIZE_TYPE__ __dstlen, struct __mbstate *__mbs) {
	__SIZE_TYPE__ __result = 0;
	char const *__src = *__psrc;
	if (__nmc) {
		while (__dstlen) {
			__SIZE_TYPE__ __error;
			__CHAR16_TYPE__ __wc;
			if (__nmc >= 7) {
				__error = (__NAMESPACE_LOCAL_SYM __localdep_uchar_mbrtoc16)(&__wc, __src, (__SIZE_TYPE__)-1, __mbs);
			} else {
				char __temp[7];
				(__NAMESPACE_LOCAL_SYM __localdep_bzero)((__NAMESPACE_LOCAL_SYM __localdep_mempcpy)(__temp, __src, __nmc), 7 - __nmc);
				__error = (__NAMESPACE_LOCAL_SYM __localdep_uchar_mbrtoc16)(&__wc, __temp, (__SIZE_TYPE__)-1, __mbs);
			}
			if (!__error) {
				__src = __NULLPTR; /* NUL-character reached */
				break;
			}
			if (__error == (__SIZE_TYPE__)-1) {
				__result = (__SIZE_TYPE__)-1; /* EILSEQ */
				break;
			}
			if (__dst != __NULLPTR)
				*__dst++ = __wc;
			--__dstlen;
			++__result;
			if (__error >= __nmc) {
				__src = __NULLPTR; /* (implicit) NUL-character reached */
				break;
			}
			__src += __error;
			__nmc -= __error;
		}
	} else {
		__src = __NULLPTR; /* (implicit) NUL-character reached */
	}
	if (__dst != __NULLPTR)
		*__psrc = __src; /* Only update source if destination was given */
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_mbsnrtoc16_defined
#define __local___localdep_mbsnrtoc16_defined
#define __localdep_mbsnrtoc16 __LIBC_LOCAL_NAME(mbsnrtoc16)
#endif /* !__local___localdep_mbsnrtoc16_defined */
#endif /* !__local_mbsnrtoc16_defined */
