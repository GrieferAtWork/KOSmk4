/* HASH CRC-32:0x58e34f1b */
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_iswspace_l_defined
#define __local_iswspace_l_defined 1
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: iswspace from wctype */
#ifndef __local___localdep_iswspace_defined
#define __local___localdep_iswspace_defined 1
#if __has_builtin(__builtin_iswspace) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_iswspace)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_iswspace,(__WINT_TYPE__ __wc),iswspace,{ return __builtin_iswspace(__wc); })
#elif defined(__CRT_HAVE_iswspace)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_iswspace,(__WINT_TYPE__ __wc),iswspace,(__wc))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/wctype/iswspace.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_iswspace __LIBC_LOCAL_NAME(iswspace)
#endif /* !... */
#endif /* !__local___localdep_iswspace_defined */
__LOCAL_LIBC(iswspace_l) __ATTR_PURE __ATTR_WUNUSED int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(iswspace_l))(__WINT_TYPE__ __wc, __locale_t __locale) {
	(void)__locale;
	__COMPILER_IMPURE();
	return __localdep_iswspace(__wc);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_iswspace_l_defined
#define __local___localdep_iswspace_l_defined 1
#define __localdep_iswspace_l __LIBC_LOCAL_NAME(iswspace_l)
#endif /* !__local___localdep_iswspace_l_defined */
#endif /* !__local_iswspace_l_defined */
