/* HASH CRC-32:0x4d00530d */
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
#ifndef __local_strnlwr_defined
#define __local_strnlwr_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_tolower_defined
#define __local___localdep_tolower_defined
__NAMESPACE_LOCAL_END
#include <bits/crt/ctype.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__crt_tolower) && defined(__CRT_HAVE_tolower)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_tolower,(int __ch),tolower,{ return __crt_tolower(__ch); })
#elif defined(__crt_tolower)
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __localdep_tolower)(int __ch) { return __crt_tolower(__ch); }
#elif __has_builtin(__builtin_tolower) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_tolower)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_tolower,(int __ch),tolower,{ return __builtin_tolower(__ch); })
#elif defined(__CRT_HAVE_tolower)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_tolower,(int __ch),tolower,(__ch))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/ctype/tolower.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_tolower __LIBC_LOCAL_NAME(tolower)
#endif /* !... */
#endif /* !__local___localdep_tolower_defined */
__LOCAL_LIBC(strnlwr) __ATTR_LEAF __ATTR_RETNONNULL __ATTR_ACCESS_RWS(1, 2) __ATTR_NONNULL((1)) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strnlwr))(char *__restrict __str, __SIZE_TYPE__ __maxlen) {
	char *__iter, __ch;
	for (__iter = __str; __maxlen-- && (__ch = *__iter) != '\0'; ++__iter)
		*__iter = (char)(__NAMESPACE_LOCAL_SYM __localdep_tolower)((unsigned char)__ch);
	return __str;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_strnlwr_defined
#define __local___localdep_strnlwr_defined
#define __localdep_strnlwr __LIBC_LOCAL_NAME(strnlwr)
#endif /* !__local___localdep_strnlwr_defined */
#endif /* !__local_strnlwr_defined */
