/* HASH CRC-32:0xd246c3ea */
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
#ifndef __local__mbschr_defined
#define __local__mbschr_defined
#include <__crt.h>
#ifdef __CRT_HAVE__mbschr_l
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__mbschr_l_defined
#define __local___localdep__mbschr_l_defined
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),unsigned char *,__NOTHROW_NCX,__localdep__mbschr_l,(unsigned char const *__restrict __haystack, unsigned int __needle, __locale_t __locale),_mbschr_l,(__haystack,__needle,__locale))
#endif /* !__local___localdep__mbschr_l_defined */
__LOCAL_LIBC(_mbschr) __ATTR_WUNUSED __ATTR_NONNULL((1)) unsigned char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_mbschr))(unsigned char const *__restrict __haystack, unsigned int __needle) {
	return (__NAMESPACE_LOCAL_SYM __localdep__mbschr_l)(__haystack, __needle, __NULLPTR);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__mbschr_defined
#define __local___localdep__mbschr_defined
#define __localdep__mbschr __LIBC_LOCAL_NAME(_mbschr)
#endif /* !__local___localdep__mbschr_defined */
#else /* __CRT_HAVE__mbschr_l */
#undef __local__mbschr_defined
#endif /* !__CRT_HAVE__mbschr_l */
#endif /* !__local__mbschr_defined */
