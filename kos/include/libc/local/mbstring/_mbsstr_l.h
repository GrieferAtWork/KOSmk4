/* HASH CRC-32:0xd9cc47c2 */
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
#ifndef __local__mbsstr_l_defined
#define __local__mbsstr_l_defined
#include <__crt.h>
#if defined(__CRT_HAVE__ismbblead_l) || defined(__CRT_HAVE__mbctype) || defined(__CRT_HAVE___p__mbctype)
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
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),unsigned char *,__NOTHROW_NCX,__localdep__mbschr_l,(unsigned char const *__restrict __haystack, unsigned int __needle, __locale_t __locale),_mbschr_l,(__haystack,__needle,__locale))
#else /* __CRT_HAVE__mbschr_l */
__NAMESPACE_LOCAL_END
#include <libc/local/mbstring/_mbschr_l.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__mbschr_l __LIBC_LOCAL_NAME(_mbschr_l)
#endif /* !__CRT_HAVE__mbschr_l */
#endif /* !__local___localdep__mbschr_l_defined */
#ifndef __local___localdep_strcmpz_defined
#define __local___localdep_strcmpz_defined
#ifdef __CRT_HAVE_strcmpz
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_strcmpz,(char const *__lhs, char const *__rhs, __SIZE_TYPE__ __rhs_len),strcmpz,(__lhs,__rhs,__rhs_len))
#else /* __CRT_HAVE_strcmpz */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strcmpz.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strcmpz __LIBC_LOCAL_NAME(strcmpz)
#endif /* !__CRT_HAVE_strcmpz */
#endif /* !__local___localdep_strcmpz_defined */
#ifndef __local___localdep_strlen_defined
#define __local___localdep_strlen_defined
#ifdef __CRT_HAVE_strlen
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_strlen,(char const *__restrict __str),strlen,(__str))
#else /* __CRT_HAVE_strlen */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strlen.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strlen __LIBC_LOCAL_NAME(strlen)
#endif /* !__CRT_HAVE_strlen */
#endif /* !__local___localdep_strlen_defined */
__LOCAL_LIBC(_mbsstr_l) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) unsigned char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_mbsstr_l))(unsigned char const *__haystack, unsigned char const *__needle, __locale_t __locale) {
	__UINT16_TYPE__ __needle_first;
	__SIZE_TYPE__ __needle_first_len;
	__SIZE_TYPE__ __needle_len;
	__needle_first     = *__needle++;
	__needle_first_len = 1;
	if ((__NAMESPACE_LOCAL_SYM __localdep__ismbblead_l)(__needle_first, __locale)) {
		__needle_first     = *__needle ? (__needle_first << 8) | *__needle++ : 0;
		__needle_first_len = 2;
	}
	if __unlikely(!__needle_first)
		return __NULLPTR;
	__needle_len = (__NAMESPACE_LOCAL_SYM __localdep_strlen)((char const *)__needle);

	/* Enumerate candidates */
	while ((__haystack = (__NAMESPACE_LOCAL_SYM __localdep__mbschr_l)(__haystack, __needle_first, __locale)) != __NULLPTR) {

		/* Skip first character. */
		__haystack += __needle_first_len;

		/* Check that all of the remaining bytes match. */
		if ((__NAMESPACE_LOCAL_SYM __localdep_strcmpz)((char const *)__needle, (char const *)__haystack, __needle_len) == 0)
			break; /* Found it! */
	}
	return (unsigned char *)__haystack;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__mbsstr_l_defined
#define __local___localdep__mbsstr_l_defined
#define __localdep__mbsstr_l __LIBC_LOCAL_NAME(_mbsstr_l)
#endif /* !__local___localdep__mbsstr_l_defined */
#else /* __CRT_HAVE__ismbblead_l || __CRT_HAVE__mbctype || __CRT_HAVE___p__mbctype */
#undef __local__mbsstr_l_defined
#endif /* !__CRT_HAVE__ismbblead_l && !__CRT_HAVE__mbctype && !__CRT_HAVE___p__mbctype */
#endif /* !__local__mbsstr_l_defined */
