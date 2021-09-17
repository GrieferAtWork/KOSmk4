/* HASH CRC-32:0x9e57e71c */
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
#ifndef __local_isblank16_defined
#define __local_isblank16_defined 1
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_c16tob_defined
#define __local___localdep_c16tob_defined 1
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
#ifndef __local___localdep_isblank_defined
#define __local___localdep_isblank_defined 1
__NAMESPACE_LOCAL_END
#include <bits/crt/ctype.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__crt_isblank) && defined(__CRT_HAVE_isblank)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isblank,(int __ch),isblank,{ return __crt_isblank(__ch); })
#elif defined(__crt_isblank)
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __localdep_isblank)(int __ch) { return __crt_isblank(__ch); }
#elif __has_builtin(__builtin_isblank) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isblank)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isblank,(int __ch),isblank,{ return __builtin_isblank(__ch); })
#elif defined(__CRT_HAVE_isblank)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isblank,(int __ch),isblank,(__ch))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/ctype/isblank.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_isblank __LIBC_LOCAL_NAME(isblank)
#endif /* !... */
#endif /* !__local___localdep_isblank_defined */
__NAMESPACE_LOCAL_END
#include <bits/crt/wctype.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(isblank16) __ATTR_CONST __ATTR_WUNUSED int
__NOTHROW(__LIBDCALL __LIBC_LOCAL_NAME(isblank16))(__WINT16_TYPE__ __wc) {
#ifdef __crt_iswblank
	return __crt_iswblank(__wc);
#else /* __crt_iswblank */
	return (__NAMESPACE_LOCAL_SYM __localdep_isblank)((__NAMESPACE_LOCAL_SYM __localdep_c16tob)(__wc));
#endif /* !__crt_iswblank */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_isblank16_defined
#define __local___localdep_isblank16_defined 1
#define __localdep_isblank16 __LIBC_LOCAL_NAME(isblank16)
#endif /* !__local___localdep_isblank16_defined */
#endif /* !__local_isblank16_defined */
