/* HASH CRC-32:0x85c8d09a */
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
#ifndef __local_isdigit16_defined
#define __local_isdigit16_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_c16tob_defined
#define __local___localdep_c16tob_defined
#if defined(__CRT_HAVE_wctob) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_c16tob,(__WINT16_TYPE__ __ch),wctob,(__ch))
#elif defined(__CRT_HAVE_DOS$wctob)
__CREDIRECT_DOS(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_c16tob,(__WINT16_TYPE__ __ch),wctob,(__ch))
#elif __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wctob.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c16tob __NAMESPACE_LOCAL_TYPEHAX(int(__LIBDCALL*)(__WINT16_TYPE__),int(__LIBDCALL&)(__WINT16_TYPE__),wctob)
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.wchar/c16tob.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c16tob __LIBC_LOCAL_NAME(c16tob)
#endif /* !... */
#endif /* !__local___localdep_c16tob_defined */
#ifndef __local___localdep_isdigit_defined
#define __local___localdep_isdigit_defined
__NAMESPACE_LOCAL_END
#include <bits/crt/ctype.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__crt_isdigit) && defined(__CRT_HAVE_isdigit)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isdigit,(int __ch),isdigit,{ return __crt_isdigit(__ch); })
#elif defined(__crt_isdigit)
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __localdep_isdigit)(int __ch) { return __crt_isdigit(__ch); }
#elif __has_builtin(__builtin_isdigit) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isdigit)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isdigit,(int __ch),isdigit,{ return __builtin_isdigit(__ch); })
#elif defined(__CRT_HAVE_isdigit)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isdigit,(int __ch),isdigit,(__ch))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/ctype/isdigit.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_isdigit __LIBC_LOCAL_NAME(isdigit)
#endif /* !... */
#endif /* !__local___localdep_isdigit_defined */
__NAMESPACE_LOCAL_END
#include <bits/crt/wctype.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(isdigit16) __ATTR_CONST __ATTR_WUNUSED int
__NOTHROW(__LIBDCALL __LIBC_LOCAL_NAME(isdigit16))(__WINT16_TYPE__ __wc) {
#ifdef __crt_iswdigit
	return __crt_iswdigit(__wc);
#else /* __crt_iswdigit */
	return (__NAMESPACE_LOCAL_SYM __localdep_isdigit)((__NAMESPACE_LOCAL_SYM __localdep_c16tob)(__wc));
#endif /* !__crt_iswdigit */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_isdigit16_defined
#define __local___localdep_isdigit16_defined
#define __localdep_isdigit16 __LIBC_LOCAL_NAME(isdigit16)
#endif /* !__local___localdep_isdigit16_defined */
#endif /* !__local_isdigit16_defined */
