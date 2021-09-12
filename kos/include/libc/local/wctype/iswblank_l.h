/* HASH CRC-32:0x7c8d7c99 */
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
#ifndef __local_iswblank_l_defined
#define __local_iswblank_l_defined 1
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_iswblank_defined
#define __local___localdep_iswblank_defined 1
__NAMESPACE_LOCAL_END
#include <bits/crt/wctype.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__crt_iswblank) && defined(__CRT_HAVE_iswblank)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_iswblank,(__WINT_TYPE__ __wc),iswblank,{ return __crt_iswblank(__wc); })
#elif defined(__crt_iswblank)
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __localdep_iswblank)(__WINT_TYPE__ __wc) { return __crt_iswblank(__wc); }
#elif __has_builtin(__builtin_iswblank) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_iswblank)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_iswblank,(__WINT_TYPE__ __wc),iswblank,{ return __builtin_iswblank(__wc); })
#elif defined(__CRT_HAVE_iswblank)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_iswblank,(__WINT_TYPE__ __wc),iswblank,(__wc))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/wctype/iswblank.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_iswblank __LIBC_LOCAL_NAME(iswblank)
#endif /* !... */
#endif /* !__local___localdep_iswblank_defined */
__LOCAL_LIBC(iswblank_l) __ATTR_PURE __ATTR_WUNUSED int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(iswblank_l))(__WINT_TYPE__ __ch, __locale_t __locale) {
	__COMPILER_IMPURE();
	(void)__locale;
	return __NAMESPACE_LOCAL_SYM __localdep_iswblank(__ch);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_iswblank_l_defined
#define __local___localdep_iswblank_l_defined 1
#define __localdep_iswblank_l __LIBC_LOCAL_NAME(iswblank_l)
#endif /* !__local___localdep_iswblank_l_defined */
#endif /* !__local_iswblank_l_defined */
