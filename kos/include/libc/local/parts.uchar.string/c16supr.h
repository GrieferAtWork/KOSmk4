/* HASH CRC-32:0x89cf473e */
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
#ifndef __local_c16supr_defined
#define __local_c16supr_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_toupper16_defined
#define __local___localdep_toupper16_defined 1
__NAMESPACE_LOCAL_END
#include <bits/crt/wctype.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__crt_towupper) && defined(__CRT_HAVE_towupper) && __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__COMPILER_EIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__WINT16_TYPE__,__NOTHROW,__LIBDCALL,__localdep_toupper16,(__WINT16_TYPE__ __wc),towupper,{ return __crt_towupper(__wc); })
#elif defined(__crt_towupper) && __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL __ATTR_CONST __ATTR_WUNUSED __WINT16_TYPE__ __NOTHROW(__LIBDCALL __localdep_toupper16)(__WINT16_TYPE__ __wc) { return __crt_towupper(__wc); }
#elif __has_builtin(__builtin_towupper) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_towupper) && __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__COMPILER_EIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__WINT16_TYPE__,__NOTHROW,__LIBDCALL,__localdep_toupper16,(__WINT16_TYPE__ __wc),towupper,{ return __builtin_towupper(__wc); })
#elif defined(__CRT_HAVE_towupper) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__WINT16_TYPE__,__NOTHROW,__localdep_toupper16,(__WINT16_TYPE__ __wc),towupper,(__wc))
#elif defined(__CRT_HAVE_DOS$towupper)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_DOS(__ATTR_CONST __ATTR_WUNUSED,__WINT16_TYPE__,__NOTHROW,__localdep_toupper16,(__WINT16_TYPE__ __wc),towupper,(__wc))
#elif __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <libc/local/wctype/towupper.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_toupper16 __NAMESPACE_LOCAL_TYPEHAX(__WINT16_TYPE__(__LIBDCALL*)(__WINT16_TYPE__),__WINT16_TYPE__(__LIBDCALL&)(__WINT16_TYPE__),towupper)
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.wctype/toupper16.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_toupper16 __LIBC_LOCAL_NAME(toupper16)
#endif /* !... */
#endif /* !__local___localdep_toupper16_defined */
__LOCAL_LIBC(c16supr) __ATTR_RETNONNULL __ATTR_NONNULL((1)) __CHAR16_TYPE__ *
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(c16supr))(__CHAR16_TYPE__ *__restrict __str) {
	__CHAR16_TYPE__ *__iter, __ch;
	for (__iter = __str; (__ch = *__iter) != '\0'; ++__iter)
		*__iter = (__CHAR16_TYPE__)(__NAMESPACE_LOCAL_SYM __localdep_toupper16)((__CHAR16_TYPE__)__ch);
	return __str;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c16supr_defined
#define __local___localdep_c16supr_defined 1
#define __localdep_c16supr __LIBC_LOCAL_NAME(c16supr)
#endif /* !__local___localdep_c16supr_defined */
#endif /* !__local_c16supr_defined */
