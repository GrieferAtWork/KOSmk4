/* HASH CRC-32:0x512c1365 */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local__mbsupr_l_defined
#define __local__mbsupr_l_defined
#include <__crt.h>
#if (defined(__CRT_HAVE__ismbblead_l) || defined(__CRT_HAVE__mbctype) || defined(__CRT_HAVE___p__mbctype)) && (defined(__CRT_HAVE__mbctoupper_l) || (defined(__CRT_HAVE__mbctouni_l) && defined(__CRT_HAVE__unitombc_l) && defined(__CRT_HAVE___unicode_descriptor)) || ((defined(__CRT_HAVE__mbctype) || defined(__CRT_HAVE___p__mbctype)) && (defined(__CRT_HAVE__mbcasemap) || defined(__CRT_HAVE___p__mbcasemap))))
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
#ifndef __local___localdep__mbctoupper_l_defined
#define __local___localdep__mbctoupper_l_defined
#ifdef __CRT_HAVE__mbctoupper_l
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,unsigned int,__NOTHROW_NCX,__localdep__mbctoupper_l,(unsigned int __ch, __locale_t __locale),_mbctoupper_l,(__ch,__locale))
#elif (defined(__CRT_HAVE__mbctouni_l) && defined(__CRT_HAVE__unitombc_l) && defined(__CRT_HAVE___unicode_descriptor)) || ((defined(__CRT_HAVE__mbctype) || defined(__CRT_HAVE___p__mbctype)) && (defined(__CRT_HAVE__mbcasemap) || defined(__CRT_HAVE___p__mbcasemap)))
__NAMESPACE_LOCAL_END
#include <libc/local/mbstring/_mbctoupper_l.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__mbctoupper_l __LIBC_LOCAL_NAME(_mbctoupper_l)
#else /* ... */
#undef __local___localdep__mbctoupper_l_defined
#endif /* !... */
#endif /* !__local___localdep__mbctoupper_l_defined */
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_mbsupr_l) __ATTR_RETNONNULL __ATTR_INOUT(1) unsigned char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_mbsupr_l))(unsigned char *__buf, __locale_t __locale) {
	unsigned char *__iter = __buf;
	for (;;) {
		__UINT16_TYPE__ __ch = *__iter;
		if (!__ch)
			break;
		if ((__NAMESPACE_LOCAL_SYM __localdep__ismbblead_l)(__ch, __locale)) {
			if __unlikely(!__iter[1])
				goto __do_1byte_lower;
			__ch      = (__ch << 8) | __iter[1];
			__ch      = (__NAMESPACE_LOCAL_SYM __localdep__mbctoupper_l)(__ch, __locale);
			__iter[0] = (unsigned char)((__ch & 0xff00) >> 8);
			__iter[1] = (unsigned char)(__ch & 0xff);
			__iter += 2;
		} else {
__do_1byte_lower:
			__ch      = (__NAMESPACE_LOCAL_SYM __localdep__mbctoupper_l)(__ch, __locale);
			__iter[0] = (unsigned char)(__ch & 0xff);
			++__iter;
		}
	}
	return __buf;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__mbsupr_l_defined
#define __local___localdep__mbsupr_l_defined
#define __localdep__mbsupr_l __LIBC_LOCAL_NAME(_mbsupr_l)
#endif /* !__local___localdep__mbsupr_l_defined */
#else /* (__CRT_HAVE__ismbblead_l || __CRT_HAVE__mbctype || __CRT_HAVE___p__mbctype) && (__CRT_HAVE__mbctoupper_l || (__CRT_HAVE__mbctouni_l && __CRT_HAVE__unitombc_l && __CRT_HAVE___unicode_descriptor) || ((__CRT_HAVE__mbctype || __CRT_HAVE___p__mbctype) && (__CRT_HAVE__mbcasemap || __CRT_HAVE___p__mbcasemap))) */
#undef __local__mbsupr_l_defined
#endif /* (!__CRT_HAVE__ismbblead_l && !__CRT_HAVE__mbctype && !__CRT_HAVE___p__mbctype) || (!__CRT_HAVE__mbctoupper_l && (!__CRT_HAVE__mbctouni_l || !__CRT_HAVE__unitombc_l || !__CRT_HAVE___unicode_descriptor) && ((!__CRT_HAVE__mbctype && !__CRT_HAVE___p__mbctype) || (!__CRT_HAVE__mbcasemap && !__CRT_HAVE___p__mbcasemap))) */
#endif /* !__local__mbsupr_l_defined */
