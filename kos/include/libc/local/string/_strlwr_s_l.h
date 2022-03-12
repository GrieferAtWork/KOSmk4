/* HASH CRC-32:0x35126ff1 */
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
#ifndef __local__strlwr_s_l_defined
#define __local__strlwr_s_l_defined
#include <__crt.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_strnlen_defined
#define __local___localdep_strnlen_defined
#if __has_builtin(__builtin_strnlen) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strnlen)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_strnlen,(char const *__restrict __str, __SIZE_TYPE__ __maxlen),strnlen,{ return __builtin_strnlen(__str, __maxlen); })
#elif defined(__CRT_HAVE_strnlen)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_strnlen,(char const *__restrict __str, __SIZE_TYPE__ __maxlen),strnlen,(__str,__maxlen))
#elif defined(__CRT_HAVE___strncnt)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_strnlen,(char const *__restrict __str, __SIZE_TYPE__ __maxlen),__strncnt,(__str,__maxlen))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strnlen.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strnlen __LIBC_LOCAL_NAME(strnlen)
#endif /* !... */
#endif /* !__local___localdep_strnlen_defined */
#ifndef __local___localdep_tolower_l_defined
#define __local___localdep_tolower_l_defined
__NAMESPACE_LOCAL_END
#include <bits/crt/ctype.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__crt_tolower_l) && defined(__CRT_HAVE_tolower_l)
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_tolower_l,(int __ch, __locale_t __locale),tolower_l,{ return __crt_tolower_l(__ch, __locale); })
#elif defined(__crt_tolower_l) && defined(__CRT_HAVE__tolower_l)
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_tolower_l,(int __ch, __locale_t __locale),_tolower_l,{ return __crt_tolower_l(__ch, __locale); })
#elif defined(__crt_tolower_l) && defined(__CRT_HAVE___tolower_l)
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_tolower_l,(int __ch, __locale_t __locale),__tolower_l,{ return __crt_tolower_l(__ch, __locale); })
#elif defined(__crt_tolower_l)
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL __localdep_tolower_l)(int __ch, __locale_t __locale) { return __crt_tolower_l(__ch, __locale); }
#elif defined(__CRT_HAVE_tolower_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_tolower_l,(int __ch, __locale_t __locale),tolower_l,(__ch,__locale))
#elif defined(__CRT_HAVE__tolower_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_tolower_l,(int __ch, __locale_t __locale),_tolower_l,(__ch,__locale))
#elif defined(__CRT_HAVE___tolower_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_tolower_l,(int __ch, __locale_t __locale),__tolower_l,(__ch,__locale))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/ctype/tolower_l.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_tolower_l __LIBC_LOCAL_NAME(tolower_l)
#endif /* !... */
#endif /* !__local___localdep_tolower_l_defined */
__LOCAL_LIBC(_strlwr_s_l) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_strlwr_s_l))(char *__buf, __SIZE_TYPE__ __buflen, __locale_t __locale) {
	char *__iter, __ch;
	if (__buf == __NULLPTR)
		return 22;
	if ((__NAMESPACE_LOCAL_SYM __localdep_strnlen)(__buf, __buflen) >= __buflen)
		return 22;
	for (__iter = __buf; (__ch = *__iter) != '\0'; ++__iter)
		*__iter = (char)(__NAMESPACE_LOCAL_SYM __localdep_tolower_l)((unsigned char)__ch, __locale);
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__strlwr_s_l_defined
#define __local___localdep__strlwr_s_l_defined
#define __localdep__strlwr_s_l __LIBC_LOCAL_NAME(_strlwr_s_l)
#endif /* !__local___localdep__strlwr_s_l_defined */
#endif /* !__local__strlwr_s_l_defined */
