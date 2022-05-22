/* HASH CRC-32:0x442bdb1f */
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
#ifndef __local__mbsnicmp_l_defined
#define __local__mbsnicmp_l_defined
#include <__crt.h>
#if (defined(__CRT_HAVE__ismbblead_l) || defined(__CRT_HAVE__mbctype) || defined(__CRT_HAVE___p__mbctype)) && (defined(__CRT_HAVE__mbctolower_l) || (defined(__CRT_HAVE__mbctouni_l) && defined(__CRT_HAVE__unitombc_l) && defined(__CRT_HAVE___unicode_descriptor)) || ((defined(__CRT_HAVE__mbctype) || defined(__CRT_HAVE___p__mbctype)) && (defined(__CRT_HAVE__mbcasemap) || defined(__CRT_HAVE___p__mbcasemap))))
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
#ifndef __local___localdep__mbctolower_l_defined
#define __local___localdep__mbctolower_l_defined
#ifdef __CRT_HAVE__mbctolower_l
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,unsigned int,__NOTHROW_NCX,__localdep__mbctolower_l,(unsigned int __ch, __locale_t __locale),_mbctolower_l,(__ch,__locale))
#elif (defined(__CRT_HAVE__mbctouni_l) && defined(__CRT_HAVE__unitombc_l) && defined(__CRT_HAVE___unicode_descriptor)) || ((defined(__CRT_HAVE__mbctype) || defined(__CRT_HAVE___p__mbctype)) && (defined(__CRT_HAVE__mbcasemap) || defined(__CRT_HAVE___p__mbcasemap)))
__NAMESPACE_LOCAL_END
#include <libc/local/mbstring/_mbctolower_l.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__mbctolower_l __LIBC_LOCAL_NAME(_mbctolower_l)
#else /* ... */
#undef __local___localdep__mbctolower_l_defined
#endif /* !... */
#endif /* !__local___localdep__mbctolower_l_defined */
__LOCAL_LIBC(_mbsnicmp_l) __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_mbsnicmp_l))(unsigned char const *__lhs, unsigned char const *__rhs, __SIZE_TYPE__ __max_chars, __locale_t __locale) {
	for (; __max_chars; --__max_chars) {
		__UINT16_TYPE__ __lc = 0, __rc = 0;
		__lc = *__lhs++;
		if ((__NAMESPACE_LOCAL_SYM __localdep__ismbblead_l)(__lc, __locale))
			__lc = *__lhs ? (__lc << 8) | *__lhs++ : 0;
		__rc = *__rhs++;
		if ((__NAMESPACE_LOCAL_SYM __localdep__ismbblead_l)(__rc, __locale))
			__rc = *__rhs ? (__rc << 8) | *__rhs++ : 0;
		if (__lc != __rc) {
			__lc = (__NAMESPACE_LOCAL_SYM __localdep__mbctolower_l)(__lc, __locale);
			__rc = (__NAMESPACE_LOCAL_SYM __localdep__mbctolower_l)(__rc, __locale);
			if (__lc != __rc)
				return (int)__lc - (int)__rc;
		}
		if (__lc == 0)
			break;
	}
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__mbsnicmp_l_defined
#define __local___localdep__mbsnicmp_l_defined
#define __localdep__mbsnicmp_l __LIBC_LOCAL_NAME(_mbsnicmp_l)
#endif /* !__local___localdep__mbsnicmp_l_defined */
#else /* (__CRT_HAVE__ismbblead_l || __CRT_HAVE__mbctype || __CRT_HAVE___p__mbctype) && (__CRT_HAVE__mbctolower_l || (__CRT_HAVE__mbctouni_l && __CRT_HAVE__unitombc_l && __CRT_HAVE___unicode_descriptor) || ((__CRT_HAVE__mbctype || __CRT_HAVE___p__mbctype) && (__CRT_HAVE__mbcasemap || __CRT_HAVE___p__mbcasemap))) */
#undef __local__mbsnicmp_l_defined
#endif /* (!__CRT_HAVE__ismbblead_l && !__CRT_HAVE__mbctype && !__CRT_HAVE___p__mbctype) || (!__CRT_HAVE__mbctolower_l && (!__CRT_HAVE__mbctouni_l || !__CRT_HAVE__unitombc_l || !__CRT_HAVE___unicode_descriptor) && ((!__CRT_HAVE__mbctype && !__CRT_HAVE___p__mbctype) || (!__CRT_HAVE__mbcasemap && !__CRT_HAVE___p__mbcasemap))) */
#endif /* !__local__mbsnicmp_l_defined */
