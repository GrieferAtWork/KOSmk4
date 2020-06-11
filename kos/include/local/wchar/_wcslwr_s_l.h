/* HASH CRC-32:0xc703b8bc */
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local__wcslwr_s_l_defined
#define __local__wcslwr_s_l_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: tolower_l from ctype */
#ifndef __local___localdep_tolower_l_defined
#define __local___localdep_tolower_l_defined 1
#ifdef __CRT_HAVE_tolower_l
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_tolower_l,(int __ch, __locale_t __locale),tolower_l,(__ch,__locale))
#elif defined(__CRT_HAVE__tolower_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_tolower_l,(int __ch, __locale_t __locale),_tolower_l,(__ch,__locale))
#elif defined(__CRT_HAVE___tolower_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_tolower_l,(int __ch, __locale_t __locale),__tolower_l,(__ch,__locale))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/ctype/tolower_l.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_tolower_l __LIBC_LOCAL_NAME(tolower_l)
#endif /* !... */
#endif /* !__local___localdep_tolower_l_defined */
/* Dependency: wcsnlen from wchar */
#ifndef __local___localdep_wcsnlen_defined
#define __local___localdep_wcsnlen_defined 1
#ifdef __wcsnlen_defined
/* Same as `strlen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
__NAMESPACE_GLB_USING(wcsnlen)
#define __localdep_wcsnlen wcsnlen
#elif defined(__CRT_HAVE_wcsnlen)
/* Same as `strlen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_wcsnlen,(__WCHAR_TYPE__ const *__restrict __string, __SIZE_TYPE__ __maxlen),wcsnlen,(__string,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsnlen) && __SIZEOF_WCHAR_T__ == 4
/* Same as `strlen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_wcsnlen,(__CHAR32_TYPE__ const *__restrict __string, __SIZE_TYPE__ __maxlen),wcsnlen,(__string,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsnlen) && __SIZEOF_WCHAR_T__ == 2
/* Same as `strlen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_wcsnlen,(__CHAR16_TYPE__ const *__restrict __string, __SIZE_TYPE__ __maxlen),wcsnlen,(__string,__maxlen))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/wchar/wcsnlen.h>
__NAMESPACE_LOCAL_BEGIN
/* Same as `strlen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
#define __localdep_wcsnlen __LIBC_LOCAL_NAME(wcsnlen)
#endif /* !... */
#endif /* !__local___localdep_wcsnlen_defined */
__LOCAL_LIBC(_wcslwr_s_l) __ATTR_LEAF __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_wcslwr_s_l))(__WCHAR_TYPE__ *__buf, __SIZE_TYPE__ __buflen, __locale_t __locale) {
	__WCHAR_TYPE__ *__iter, __ch;
	if (__buf == __NULLPTR)
		return __EINVAL;
	if (__localdep_wcsnlen(__buf, __buflen) >= __buflen)
		return __EINVAL;
	for (__iter = __buf; (__ch = *__iter) != '\0'; ++__iter)
		*__iter = __localdep_tolower_l(__ch, __locale);
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__wcslwr_s_l_defined
#define __local___localdep__wcslwr_s_l_defined 1
#define __localdep__wcslwr_s_l __LIBC_LOCAL_NAME(_wcslwr_s_l)
#endif /* !__local___localdep__wcslwr_s_l_defined */
#endif /* !__local__wcslwr_s_l_defined */
