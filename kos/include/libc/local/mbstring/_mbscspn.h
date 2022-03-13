/* HASH CRC-32:0xf3930dab */
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
#ifndef __local__mbscspn_defined
#define __local__mbscspn_defined
#include <__crt.h>
#if defined(__CRT_HAVE__mbscspn_l) || defined(__CRT_HAVE__ismbblead_l)
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__mbscspn_l_defined
#define __local___localdep__mbscspn_l_defined
#ifdef __CRT_HAVE__mbscspn_l
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep__mbscspn_l,(unsigned char const *__haystack, unsigned char const *__reject, __locale_t __locale),_mbscspn_l,(__haystack,__reject,__locale))
#elif defined(__CRT_HAVE__ismbblead_l)
__NAMESPACE_LOCAL_END
#include <libc/local/mbstring/_mbscspn_l.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__mbscspn_l __LIBC_LOCAL_NAME(_mbscspn_l)
#else /* ... */
#undef __local___localdep__mbscspn_l_defined
#endif /* !... */
#endif /* !__local___localdep__mbscspn_l_defined */
__LOCAL_LIBC(_mbscspn) __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_mbscspn))(unsigned char const *__haystack, unsigned char const *__reject) {
	return (__NAMESPACE_LOCAL_SYM __localdep__mbscspn_l)(__haystack, __reject, __NULLPTR);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__mbscspn_defined
#define __local___localdep__mbscspn_defined
#define __localdep__mbscspn __LIBC_LOCAL_NAME(_mbscspn)
#endif /* !__local___localdep__mbscspn_defined */
#else /* __CRT_HAVE__mbscspn_l || __CRT_HAVE__ismbblead_l */
#undef __local__mbscspn_defined
#endif /* !__CRT_HAVE__mbscspn_l && !__CRT_HAVE__ismbblead_l */
#endif /* !__local__mbscspn_defined */
