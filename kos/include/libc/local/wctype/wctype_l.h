/* HASH CRC-32:0xe5c12185 */
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
#ifndef __local_wctype_l_defined
#define __local_wctype_l_defined
#include <__crt.h>
#if defined(__CRT_HAVE_wctype) || (defined(__CRT_KOS) && defined(__CRT_HAVE___unicode_descriptor))
#include <bits/crt/wctype.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_wctype_defined
#define __local___localdep_wctype_defined
#ifdef __CRT_HAVE_wctype
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO(1),__wctype_t,__NOTHROW_NCX,__localdep_wctype,(char const *__prop),wctype,(__prop))
#elif defined(__CRT_KOS) && defined(__CRT_HAVE___unicode_descriptor)
__NAMESPACE_LOCAL_END
#include <libc/local/wctype/wctype.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_wctype __LIBC_LOCAL_NAME(wctype)
#else /* ... */
#undef __local___localdep_wctype_defined
#endif /* !... */
#endif /* !__local___localdep_wctype_defined */
__LOCAL_LIBC(wctype_l) __ATTR_WUNUSED __ATTR_ACCESS_RO(1) __wctype_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(wctype_l))(char const *__prop, __locale_t __locale) {
	__COMPILER_IMPURE();
	(void)__locale;
	return (__NAMESPACE_LOCAL_SYM __localdep_wctype)(__prop);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_wctype_l_defined
#define __local___localdep_wctype_l_defined
#define __localdep_wctype_l __LIBC_LOCAL_NAME(wctype_l)
#endif /* !__local___localdep_wctype_l_defined */
#else /* __CRT_HAVE_wctype || (__CRT_KOS && __CRT_HAVE___unicode_descriptor) */
#undef __local_wctype_l_defined
#endif /* !__CRT_HAVE_wctype && (!__CRT_KOS || !__CRT_HAVE___unicode_descriptor) */
#endif /* !__local_wctype_l_defined */
