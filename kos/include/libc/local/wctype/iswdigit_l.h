/* HASH CRC-32:0x2f99aeeb */
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
#ifndef __local_iswdigit_l_defined
#define __local_iswdigit_l_defined 1
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_iswdigit_defined
#define __local___localdep_iswdigit_defined 1
#if __has_builtin(__builtin_iswdigit) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_iswdigit)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_iswdigit,(__WINT_TYPE__ __wc),iswdigit,{ return __builtin_iswdigit(__wc); })
#elif defined(__CRT_HAVE_iswdigit)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_iswdigit,(__WINT_TYPE__ __wc),iswdigit,(__wc))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/wctype/iswdigit.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_iswdigit __LIBC_LOCAL_NAME(iswdigit)
#endif /* !... */
#endif /* !__local___localdep_iswdigit_defined */
__LOCAL_LIBC(iswdigit_l) __ATTR_PURE __ATTR_WUNUSED int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(iswdigit_l))(__WINT_TYPE__ __wc, __locale_t __locale) {
	(void)__locale;
	__COMPILER_IMPURE();
	return __localdep_iswdigit(__wc);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_iswdigit_l_defined
#define __local___localdep_iswdigit_l_defined 1
#define __localdep_iswdigit_l __LIBC_LOCAL_NAME(iswdigit_l)
#endif /* !__local___localdep_iswdigit_l_defined */
#endif /* !__local_iswdigit_l_defined */
