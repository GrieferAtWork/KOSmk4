/* HASH CRC-32:0x3a53cc1f */
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
#ifndef __local_mbtoc32_defined
#define __local_mbtoc32_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_uchar_mbrtoc32_defined
#define __local___localdep_uchar_mbrtoc32_defined
#if defined(__CRT_HAVE_mbrtowc) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__NAMESPACE_LOCAL_END
#include <bits/crt/mbstate.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_INOUT_OPT(4) __ATTR_IN_OPT(2) __ATTR_OUT_OPT(1),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_uchar_mbrtoc32,(__CHAR32_TYPE__ *__pwc, char const *__restrict __str, __SIZE_TYPE__ __maxlen, struct __mbstate *__mbs),mbrtowc,(__pwc,__str,__maxlen,__mbs))
#elif defined(__CRT_HAVE_KOS$mbrtowc)
__NAMESPACE_LOCAL_END
#include <bits/crt/mbstate.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_KOS(__ATTR_INOUT_OPT(4) __ATTR_IN_OPT(2) __ATTR_OUT_OPT(1),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_uchar_mbrtoc32,(__CHAR32_TYPE__ *__pwc, char const *__restrict __str, __SIZE_TYPE__ __maxlen, struct __mbstate *__mbs),mbrtowc,(__pwc,__str,__maxlen,__mbs))
#elif defined(__CRT_HAVE___mbrtowc) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__NAMESPACE_LOCAL_END
#include <bits/crt/mbstate.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_INOUT_OPT(4) __ATTR_IN_OPT(2) __ATTR_OUT_OPT(1),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_uchar_mbrtoc32,(__CHAR32_TYPE__ *__pwc, char const *__restrict __str, __SIZE_TYPE__ __maxlen, struct __mbstate *__mbs),__mbrtowc,(__pwc,__str,__maxlen,__mbs))
#elif defined(__CRT_HAVE_KOS$__mbrtowc)
__NAMESPACE_LOCAL_END
#include <bits/crt/mbstate.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_KOS(__ATTR_INOUT_OPT(4) __ATTR_IN_OPT(2) __ATTR_OUT_OPT(1),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_uchar_mbrtoc32,(__CHAR32_TYPE__ *__pwc, char const *__restrict __str, __SIZE_TYPE__ __maxlen, struct __mbstate *__mbs),__mbrtowc,(__pwc,__str,__maxlen,__mbs))
#elif defined(__CRT_HAVE_mbrtoc32) && defined(__LIBCCALL_IS_LIBKCALL)
__NAMESPACE_LOCAL_END
#include <bits/crt/mbstate.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_INOUT_OPT(4) __ATTR_IN_OPT(2) __ATTR_OUT_OPT(1),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_uchar_mbrtoc32,(__CHAR32_TYPE__ *__pwc, char const *__restrict __str, __SIZE_TYPE__ __maxlen, struct __mbstate *__mbs),mbrtoc32,(__pwc,__str,__maxlen,__mbs))
#elif defined(__CRT_HAVE_KOS$mbrtoc32)
__NAMESPACE_LOCAL_END
#include <bits/crt/mbstate.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_KOS(__ATTR_INOUT_OPT(4) __ATTR_IN_OPT(2) __ATTR_OUT_OPT(1),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_uchar_mbrtoc32,(__CHAR32_TYPE__ *__pwc, char const *__restrict __str, __SIZE_TYPE__ __maxlen, struct __mbstate *__mbs),mbrtoc32,(__pwc,__str,__maxlen,__mbs))
#elif __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/mbrtowc.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_uchar_mbrtoc32 __NAMESPACE_LOCAL_TYPEHAX(__SIZE_TYPE__(__LIBKCALL*)(__CHAR32_TYPE__ *,char const *__restrict,__SIZE_TYPE__,struct __mbstate *),__SIZE_TYPE__(__LIBKCALL&)(__CHAR32_TYPE__ *,char const *__restrict,__SIZE_TYPE__,struct __mbstate *),mbrtowc)
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/uchar/uchar_mbrtoc32.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_uchar_mbrtoc32 __LIBC_LOCAL_NAME(uchar_mbrtoc32)
#endif /* !... */
#endif /* !__local___localdep_uchar_mbrtoc32_defined */
__LOCAL_LIBC(mbtoc32) __ATTR_IN_OPT(2) __ATTR_OUT_OPT(1) int
__NOTHROW_NCX(__LIBKCALL __LIBC_LOCAL_NAME(mbtoc32))(__CHAR32_TYPE__ *__restrict __pwc, char const *__restrict __str, __SIZE_TYPE__ __maxlen) {
	return (__NAMESPACE_LOCAL_SYM __localdep_uchar_mbrtoc32)(__pwc, __str, __maxlen, __NULLPTR);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_mbtoc32_defined
#define __local___localdep_mbtoc32_defined
#define __localdep_mbtoc32 __LIBC_LOCAL_NAME(mbtoc32)
#endif /* !__local___localdep_mbtoc32_defined */
#endif /* !__local_mbtoc32_defined */
