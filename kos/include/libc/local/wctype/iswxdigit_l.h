/* HASH CRC-32:0x7c07d1e7 */
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
#ifndef __local_iswxdigit_l_defined
#define __local_iswxdigit_l_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_iswxdigit_defined
#define __local___localdep_iswxdigit_defined
__NAMESPACE_LOCAL_END
#include <bits/crt/wctype.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__crt_iswxdigit) && defined(__CRT_HAVE_iswxdigit)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_iswxdigit,(__WINT_TYPE__ __wc),iswxdigit,{ return __crt_iswxdigit(__wc); })
#elif defined(__crt_iswxdigit)
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __localdep_iswxdigit)(__WINT_TYPE__ __wc) { return __crt_iswxdigit(__wc); }
#elif __has_builtin(__builtin_iswxdigit) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_iswxdigit)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_iswxdigit,(__WINT_TYPE__ __wc),iswxdigit,{ return __builtin_iswxdigit(__wc); })
#elif defined(__CRT_HAVE_iswxdigit)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_iswxdigit,(__WINT_TYPE__ __wc),iswxdigit,(__wc))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/wctype/iswxdigit.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_iswxdigit __LIBC_LOCAL_NAME(iswxdigit)
#endif /* !... */
#endif /* !__local___localdep_iswxdigit_defined */
__LOCAL_LIBC(iswxdigit_l) __ATTR_PURE __ATTR_WUNUSED int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(iswxdigit_l))(__WINT_TYPE__ __ch, __locale_t __locale) {
	__COMPILER_IMPURE();
	(void)__locale;
	return (__NAMESPACE_LOCAL_SYM __localdep_iswxdigit)(__ch);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_iswxdigit_l_defined
#define __local___localdep_iswxdigit_l_defined
#define __localdep_iswxdigit_l __LIBC_LOCAL_NAME(iswxdigit_l)
#endif /* !__local___localdep_iswxdigit_l_defined */
#endif /* !__local_iswxdigit_l_defined */
