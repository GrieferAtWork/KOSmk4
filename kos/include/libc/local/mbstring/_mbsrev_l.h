/* HASH CRC-32:0x2244f8af */
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
#ifndef __local__mbsrev_l_defined
#define __local__mbsrev_l_defined
#include <__crt.h>
#ifdef __CRT_HAVE__ismbblead_l
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__ismbblead_l_defined
#define __local___localdep__ismbblead_l_defined
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep__ismbblead_l,(unsigned int __ch, __locale_t __locale),_ismbblead_l,(__ch,__locale))
#endif /* !__local___localdep__ismbblead_l_defined */
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
#ifndef __local___localdep_strrev_defined
#define __local___localdep_strrev_defined
#ifdef __CRT_HAVE_strrev
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,__localdep_strrev,(char *__restrict __str),strrev,(__str))
#elif defined(__CRT_HAVE__strrev)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,__localdep_strrev,(char *__restrict __str),_strrev,(__str))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strrev.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strrev __LIBC_LOCAL_NAME(strrev)
#endif /* !... */
#endif /* !__local___localdep_strrev_defined */
__LOCAL_LIBC(_mbsrev_l) __ATTR_RETNONNULL __ATTR_NONNULL((1)) unsigned char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_mbsrev_l))(unsigned char *__buf, __locale_t __locale) {
	__SIZE_TYPE__ __bytes;
	__bytes = (__NAMESPACE_LOCAL_SYM __localdep_strlen)((__NAMESPACE_LOCAL_SYM __localdep_strrev)((char *)__buf));
	while (__bytes >= 2) {
		unsigned char __ch = __buf[__bytes - 1];
		if ((__NAMESPACE_LOCAL_SYM __localdep__ismbblead_l)(__ch, __locale)) {
			/* Swap with preceding character to fix multi-byte character. */
			__buf[__bytes - 1] = __buf[__bytes - 2];
			__buf[__bytes - 2] = __ch;
			__bytes -= 2;
		} else {
			__bytes -= 1;
		}
	}
	return __buf;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__mbsrev_l_defined
#define __local___localdep__mbsrev_l_defined
#define __localdep__mbsrev_l __LIBC_LOCAL_NAME(_mbsrev_l)
#endif /* !__local___localdep__mbsrev_l_defined */
#else /* __CRT_HAVE__ismbblead_l */
#undef __local__mbsrev_l_defined
#endif /* !__CRT_HAVE__ismbblead_l */
#endif /* !__local__mbsrev_l_defined */
