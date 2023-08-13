/* HASH CRC-32:0x21adfbbf */
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
#ifndef __local__mbscspn_l_defined
#define __local__mbscspn_l_defined
#include <__crt.h>
#if defined(__CRT_HAVE__ismbblead_l) || defined(__CRT_HAVE__mbctype) || defined(__CRT_HAVE___p__mbctype)
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__ismbblead_l_defined
#define __local___localdep__ismbblead_l_defined
#ifdef __CRT_HAVE__ismbblead_l
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep__ismbblead_l,(unsigned int __ch, __locale_t __locale),_ismbblead_l,(__ch,__locale))
#elif defined(__CRT_HAVE__mbctype) || defined(__CRT_HAVE___p__mbctype)
__NAMESPACE_LOCAL_END
#include <libc/local/mbctype/_ismbblead_l.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__ismbblead_l __LIBC_LOCAL_NAME(_ismbblead_l)
#else /* ... */
#undef __local___localdep__ismbblead_l_defined
#endif /* !... */
#endif /* !__local___localdep__ismbblead_l_defined */
#ifndef __local___localdep__mbschr_l_defined
#define __local___localdep__mbschr_l_defined
#ifdef __CRT_HAVE__mbschr_l
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),unsigned char *,__NOTHROW_NCX,__localdep__mbschr_l,(unsigned char const *__restrict __haystack, unsigned int __needle, __locale_t __locale),_mbschr_l,(__haystack,__needle,__locale))
#else /* __CRT_HAVE__mbschr_l */
__NAMESPACE_LOCAL_END
#include <libc/local/mbstring/_mbschr_l.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__mbschr_l __LIBC_LOCAL_NAME(_mbschr_l)
#endif /* !__CRT_HAVE__mbschr_l */
#endif /* !__local___localdep__mbschr_l_defined */
__LOCAL_LIBC(_mbscspn_l) __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_mbscspn_l))(unsigned char const *__haystack, unsigned char const *__reject, __locale_t __locale) {
	unsigned char const *__iter = __haystack;
	for (;;) {
		__UINT16_TYPE__ __ch = *__iter++;
		if ((__NAMESPACE_LOCAL_SYM __localdep__ismbblead_l)(__ch, __locale))
			__ch = *__iter ? (__ch << 8) | *__iter++ : 0;
		if (__ch == 0)
			break;
		if ((__NAMESPACE_LOCAL_SYM __localdep__mbschr_l)(__reject, __ch, __locale) != __NULLPTR)
			break;
	}
	return (__SIZE_TYPE__)(__iter - __haystack);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__mbscspn_l_defined
#define __local___localdep__mbscspn_l_defined
#define __localdep__mbscspn_l __LIBC_LOCAL_NAME(_mbscspn_l)
#endif /* !__local___localdep__mbscspn_l_defined */
#else /* __CRT_HAVE__ismbblead_l || __CRT_HAVE__mbctype || __CRT_HAVE___p__mbctype */
#undef __local__mbscspn_l_defined
#endif /* !__CRT_HAVE__ismbblead_l && !__CRT_HAVE__mbctype && !__CRT_HAVE___p__mbctype */
#endif /* !__local__mbscspn_l_defined */
