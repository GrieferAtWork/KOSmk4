/* HASH CRC-32:0x70ea287f */
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
#ifndef __local__mbsnbcat_l_defined
#define __local__mbsnbcat_l_defined
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
#ifndef __local___localdep_strend_defined
#define __local___localdep_strend_defined
#ifdef __CRT_HAVE_strend
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,__localdep_strend,(char const *__restrict __str),strend,(__str))
#else /* __CRT_HAVE_strend */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strend.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strend __LIBC_LOCAL_NAME(strend)
#endif /* !__CRT_HAVE_strend */
#endif /* !__local___localdep_strend_defined */
__LOCAL_LIBC(_mbsnbcat_l) __ATTR_INOUT(1) __ATTR_INS(2, 3) unsigned char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_mbsnbcat_l))(unsigned char *__buf, unsigned char const *__src, __SIZE_TYPE__ __max_bytes, __locale_t __locale) {
	unsigned char *__dst;
	__dst = (unsigned char *)(__NAMESPACE_LOCAL_SYM __localdep_strend)((char const *)__buf);
	for (;;) {
		unsigned char __ch;
		if (!__max_bytes)
			break;
		--__max_bytes;
		*__dst++ = __ch = *__src++;
		if (!__ch)
			return __buf;
		if ((__NAMESPACE_LOCAL_SYM __localdep__ismbblead_l)(__ch, __locale)) {
			if (!__max_bytes) {
				__dst[-1] = '\0'; /* "fix" incomplete 2-byte character. */
				return __buf;
			}
			--__max_bytes;
			*__dst++ = __ch = *__src++;
			if __unlikely(!__ch) {
				__dst[-2] = '\0'; /* "fix" incomplete 2-byte character. */
				return __buf;
			}
		}
	}
	*__dst = '\0';
	return __buf;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__mbsnbcat_l_defined
#define __local___localdep__mbsnbcat_l_defined
#define __localdep__mbsnbcat_l __LIBC_LOCAL_NAME(_mbsnbcat_l)
#endif /* !__local___localdep__mbsnbcat_l_defined */
#else /* __CRT_HAVE__ismbblead_l || __CRT_HAVE__mbctype || __CRT_HAVE___p__mbctype */
#undef __local__mbsnbcat_l_defined
#endif /* !__CRT_HAVE__ismbblead_l && !__CRT_HAVE__mbctype && !__CRT_HAVE___p__mbctype */
#endif /* !__local__mbsnbcat_l_defined */
