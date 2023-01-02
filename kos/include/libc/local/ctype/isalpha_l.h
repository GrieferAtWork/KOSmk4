/* HASH CRC-32:0x16870192 */
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
#ifndef __local_isalpha_l_defined
#define __local_isalpha_l_defined
#include <__crt.h>
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
__LOCAL_LIBC(isalpha_l) __ATTR_PURE __ATTR_WUNUSED int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(isalpha_l))(int __ch, __locale_t __locale) {
	__COMPILER_IMPURE();
	(void)__locale;
	return (__NAMESPACE_LOCAL_SYM __localdep_isalpha)(__ch);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_isalpha_l_defined
#define __local___localdep_isalpha_l_defined
#define __localdep_isalpha_l __LIBC_LOCAL_NAME(isalpha_l)
#endif /* !__local___localdep_isalpha_l_defined */
#endif /* !__local_isalpha_l_defined */
