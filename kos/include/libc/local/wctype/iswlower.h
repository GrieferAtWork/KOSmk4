/* HASH CRC-32:0x9ec5aab6 */
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
#ifndef __local_iswlower_defined
#define __local_iswlower_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
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
#ifndef __local___localdep_wctob_defined
#define __local___localdep_wctob_defined
#ifdef __CRT_HAVE_wctob
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_wctob,(__WINT_TYPE__ __ch),wctob,(__ch))
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
__LOCAL_LIBC(iswlower) __ATTR_CONST __ATTR_WUNUSED int
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(iswlower))(__WINT_TYPE__ __wc) {
#ifdef __crt_iswlower
	return __crt_iswlower(__wc);
#else /* __crt_iswlower */
	return (__NAMESPACE_LOCAL_SYM __localdep_islower)((__NAMESPACE_LOCAL_SYM __localdep_wctob)(__wc));
#endif /* !__crt_iswlower */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_iswlower_defined
#define __local___localdep_iswlower_defined
#define __localdep_iswlower __LIBC_LOCAL_NAME(iswlower)
#endif /* !__local___localdep_iswlower_defined */
#endif /* !__local_iswlower_defined */
