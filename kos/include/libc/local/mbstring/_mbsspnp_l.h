/* HASH CRC-32:0x13292f65 */
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
#ifndef __local__mbsspnp_l_defined
#define __local__mbsspnp_l_defined
#include <__crt.h>
#if defined(__CRT_HAVE__mbsspn_l) || defined(__CRT_HAVE__ismbblead_l) || defined(__CRT_HAVE__mbctype) || defined(__CRT_HAVE___p__mbctype)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__mbsspn_l_defined
#define __local___localdep__mbsspn_l_defined
#ifdef __CRT_HAVE__mbsspn_l
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),__SIZE_TYPE__,__NOTHROW_NCX,__localdep__mbsspn_l,(unsigned char const *__haystack, unsigned char const *__accept, __locale_t __locale),_mbsspn_l,(__haystack,__accept,__locale))
#elif (defined(__CRT_HAVE__ismbblead_l) || defined(__CRT_HAVE__mbctype) || defined(__CRT_HAVE___p__mbctype)) && (defined(__CRT_HAVE__mbschr_l) || defined(__CRT_HAVE__ismbblead_l) || defined(__CRT_HAVE__mbctype) || defined(__CRT_HAVE___p__mbctype))
__NAMESPACE_LOCAL_END
#include <libc/local/mbstring/_mbsspn_l.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__mbsspn_l __LIBC_LOCAL_NAME(_mbsspn_l)
#else /* ... */
#undef __local___localdep__mbsspn_l_defined
#endif /* !... */
#endif /* !__local___localdep__mbsspn_l_defined */
__LOCAL_LIBC(_mbsspnp_l) __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) unsigned char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_mbsspnp_l))(unsigned char const *__haystack, unsigned char const *__accept, __locale_t __locale) {
	__haystack += (__NAMESPACE_LOCAL_SYM __localdep__mbsspn_l)(__haystack, __accept, __locale);
	if (*__haystack == 0)
		__haystack = __NULLPTR;
	return (unsigned char *)__haystack;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__mbsspnp_l_defined
#define __local___localdep__mbsspnp_l_defined
#define __localdep__mbsspnp_l __LIBC_LOCAL_NAME(_mbsspnp_l)
#endif /* !__local___localdep__mbsspnp_l_defined */
#else /* __CRT_HAVE__mbsspn_l || __CRT_HAVE__ismbblead_l || __CRT_HAVE__mbctype || __CRT_HAVE___p__mbctype */
#undef __local__mbsspnp_l_defined
#endif /* !__CRT_HAVE__mbsspn_l && !__CRT_HAVE__ismbblead_l && !__CRT_HAVE__mbctype && !__CRT_HAVE___p__mbctype */
#endif /* !__local__mbsspnp_l_defined */
