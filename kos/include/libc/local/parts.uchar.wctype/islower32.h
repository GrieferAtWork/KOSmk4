/* HASH CRC-32:0x89d9823c */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_islower32_defined
#define __local_islower32_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_c32tob_defined
#define __local___localdep_c32tob_defined
#if defined(__CRT_HAVE_wctob) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_c32tob,(__WINT32_TYPE__ __ch),wctob,(__ch))
#elif defined(__CRT_HAVE_KOS$wctob)
__CREDIRECT_KOS(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_c32tob,(__WINT32_TYPE__ __ch),wctob,(__ch))
#elif __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wctob.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c32tob __NAMESPACE_LOCAL_TYPEHAX(int(__LIBKCALL*)(__WINT32_TYPE__),int(__LIBKCALL&)(__WINT32_TYPE__),wctob)
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.wchar/c32tob.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c32tob __LIBC_LOCAL_NAME(c32tob)
#endif /* !... */
#endif /* !__local___localdep_c32tob_defined */
#ifndef __local___localdep_islower_defined
#define __local___localdep_islower_defined
__NAMESPACE_LOCAL_END
#include <bits/crt/ctype.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__crt_islower) && defined(__CRT_HAVE_islower)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_islower,(int __ch),islower,{ return __crt_islower(__ch); })
#elif defined(__crt_islower)
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __localdep_islower)(int __ch) { return __crt_islower(__ch); }
#elif __has_builtin(__builtin_islower) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_islower)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_islower,(int __ch),islower,{ return __builtin_islower(__ch); })
#elif defined(__CRT_HAVE_islower)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_islower,(int __ch),islower,(__ch))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/ctype/islower.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_islower __LIBC_LOCAL_NAME(islower)
#endif /* !... */
#endif /* !__local___localdep_islower_defined */
__NAMESPACE_LOCAL_END
#include <bits/crt/wctype.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(islower32) __ATTR_CONST __ATTR_WUNUSED int
__NOTHROW(__LIBKCALL __LIBC_LOCAL_NAME(islower32))(__WINT32_TYPE__ __wc) {
#ifdef __crt_iswlower
	return __crt_iswlower(__wc);
#else /* __crt_iswlower */
	return (__NAMESPACE_LOCAL_SYM __localdep_islower)((__NAMESPACE_LOCAL_SYM __localdep_c32tob)(__wc));
#endif /* !__crt_iswlower */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_islower32_defined
#define __local___localdep_islower32_defined
#define __localdep_islower32 __LIBC_LOCAL_NAME(islower32)
#endif /* !__local___localdep_islower32_defined */
#endif /* !__local_islower32_defined */
