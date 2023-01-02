/* HASH CRC-32:0x28a8cae4 */
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
#ifndef __local_iswalpha_defined
#define __local_iswalpha_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_isalpha_defined
#define __local___localdep_isalpha_defined
__NAMESPACE_LOCAL_END
#include <bits/crt/ctype.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__crt_isalpha) && defined(__CRT_HAVE_isalpha)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isalpha,(int __ch),isalpha,{ return __crt_isalpha(__ch); })
#elif defined(__crt_isalpha)
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __localdep_isalpha)(int __ch) { return __crt_isalpha(__ch); }
#elif __has_builtin(__builtin_isalpha) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isalpha)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isalpha,(int __ch),isalpha,{ return __builtin_isalpha(__ch); })
#elif defined(__CRT_HAVE_isalpha)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isalpha,(int __ch),isalpha,(__ch))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/ctype/isalpha.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_isalpha __LIBC_LOCAL_NAME(isalpha)
#endif /* !... */
#endif /* !__local___localdep_isalpha_defined */
#ifndef __local___localdep_wctob_defined
#define __local___localdep_wctob_defined
#ifdef __CRT_HAVE_wctob
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_wctob,(__WINT_TYPE__ __ch),wctob,(__ch))
#else /* __CRT_HAVE_wctob */
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wctob.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_wctob __LIBC_LOCAL_NAME(wctob)
#endif /* !__CRT_HAVE_wctob */
#endif /* !__local___localdep_wctob_defined */
__NAMESPACE_LOCAL_END
#include <bits/crt/wctype.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(iswalpha) __ATTR_CONST __ATTR_WUNUSED int
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(iswalpha))(__WINT_TYPE__ __wc) {
#ifdef __crt_iswalpha
	return __crt_iswalpha(__wc);
#else /* __crt_iswalpha */
	return (__NAMESPACE_LOCAL_SYM __localdep_isalpha)((__NAMESPACE_LOCAL_SYM __localdep_wctob)(__wc));
#endif /* !__crt_iswalpha */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_iswalpha_defined
#define __local___localdep_iswalpha_defined
#define __localdep_iswalpha __LIBC_LOCAL_NAME(iswalpha)
#endif /* !__local___localdep_iswalpha_defined */
#endif /* !__local_iswalpha_defined */
