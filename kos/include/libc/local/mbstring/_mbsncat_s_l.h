/* HASH CRC-32:0x138a0ef1 */
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
#ifndef __local__mbsncat_s_l_defined
#define __local__mbsncat_s_l_defined
#include <__crt.h>
#if (defined(__CRT_HAVE__mbsncat_l) || defined(__CRT_HAVE__ismbblead_l) || defined(__CRT_HAVE__mbctype) || defined(__CRT_HAVE___p__mbctype)) && (defined(__CRT_HAVE__mbsnbcnt_l) || defined(__CRT_HAVE__ismbblead_l) || defined(__CRT_HAVE__mbctype) || defined(__CRT_HAVE___p__mbctype))
#include <hybrid/typecore.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__mbsnbcnt_l_defined
#define __local___localdep__mbsnbcnt_l_defined
#ifdef __CRT_HAVE__mbsnbcnt_l
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep__mbsnbcnt_l,(unsigned char const *__str, __SIZE_TYPE__ __max_chars, __locale_t __locale),_mbsnbcnt_l,(__str,__max_chars,__locale))
#elif defined(__CRT_HAVE__ismbblead_l) || defined(__CRT_HAVE__mbctype) || defined(__CRT_HAVE___p__mbctype)
__NAMESPACE_LOCAL_END
#include <libc/local/mbstring/_mbsnbcnt_l.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__mbsnbcnt_l __LIBC_LOCAL_NAME(_mbsnbcnt_l)
#else /* ... */
#undef __local___localdep__mbsnbcnt_l_defined
#endif /* !... */
#endif /* !__local___localdep__mbsnbcnt_l_defined */
#ifndef __local___localdep__mbsncat_l_defined
#define __local___localdep__mbsncat_l_defined
#ifdef __CRT_HAVE__mbsncat_l
__CREDIRECT(__ATTR_NONNULL((1, 2)),unsigned char *,__NOTHROW_NCX,__localdep__mbsncat_l,(unsigned char *__buf, unsigned char const *__src, __SIZE_TYPE__ __max_chars, __locale_t __locale),_mbsncat_l,(__buf,__src,__max_chars,__locale))
#elif defined(__CRT_HAVE__ismbblead_l) || defined(__CRT_HAVE__mbctype) || defined(__CRT_HAVE___p__mbctype)
__NAMESPACE_LOCAL_END
#include <libc/local/mbstring/_mbsncat_l.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__mbsncat_l __LIBC_LOCAL_NAME(_mbsncat_l)
#else /* ... */
#undef __local___localdep__mbsncat_l_defined
#endif /* !... */
#endif /* !__local___localdep__mbsncat_l_defined */
#ifndef __local___localdep_strlen_defined
#define __local___localdep_strlen_defined
#ifdef __CRT_HAVE_strlen
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_strlen,(char const *__restrict __str),strlen,(__str))
#else /* __CRT_HAVE_strlen */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strlen.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strlen __LIBC_LOCAL_NAME(strlen)
#endif /* !__CRT_HAVE_strlen */
#endif /* !__local___localdep_strlen_defined */
__LOCAL_LIBC(_mbsncat_s_l) __ATTR_NONNULL((1, 3)) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_mbsncat_s_l))(unsigned char *__buf, __SIZE_TYPE__ __true_bufsize, unsigned char const *__src, __SIZE_TYPE__ __max_chars, __locale_t __locale) {
	if (__max_chars && (!__buf || !__src ||
	                  __true_bufsize <= ((__NAMESPACE_LOCAL_SYM __localdep_strlen)((char const *)__buf) +
	                                   (__NAMESPACE_LOCAL_SYM __localdep__mbsnbcnt_l)(__src, __max_chars, __locale))))
		return 22;
	(__NAMESPACE_LOCAL_SYM __localdep__mbsncat_l)(__buf, __src, __max_chars, __locale);
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__mbsncat_s_l_defined
#define __local___localdep__mbsncat_s_l_defined
#define __localdep__mbsncat_s_l __LIBC_LOCAL_NAME(_mbsncat_s_l)
#endif /* !__local___localdep__mbsncat_s_l_defined */
#else /* (__CRT_HAVE__mbsncat_l || __CRT_HAVE__ismbblead_l || __CRT_HAVE__mbctype || __CRT_HAVE___p__mbctype) && (__CRT_HAVE__mbsnbcnt_l || __CRT_HAVE__ismbblead_l || __CRT_HAVE__mbctype || __CRT_HAVE___p__mbctype) */
#undef __local__mbsncat_s_l_defined
#endif /* (!__CRT_HAVE__mbsncat_l && !__CRT_HAVE__ismbblead_l && !__CRT_HAVE__mbctype && !__CRT_HAVE___p__mbctype) || (!__CRT_HAVE__mbsnbcnt_l && !__CRT_HAVE__ismbblead_l && !__CRT_HAVE__mbctype && !__CRT_HAVE___p__mbctype) */
#endif /* !__local__mbsncat_s_l_defined */