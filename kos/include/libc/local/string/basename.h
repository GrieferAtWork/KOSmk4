/* HASH CRC-32:0xb7cc31d */
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
#ifndef __local_basename_defined
#define __local_basename_defined
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_isalpha_defined
#define __local___localdep_isalpha_defined
__NAMESPACE_LOCAL_END
#include <bits/crt/ctype.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__crt_isalpha) && defined(__CRT_HAVE_isalpha)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isalpha,(int __ch),isalpha,{ return __crt_isalpha(__ch); })
#elif defined(__crt_isalpha)
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __localdep_isalpha)(int __ch) { return __crt_isalpha(__ch); }
#elif __has_builtin(__builtin_isalpha) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isalpha)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isalpha,(int __ch),isalpha,{ return __builtin_isalpha(__ch); })
#elif defined(__CRT_HAVE_isalpha)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isalpha,(int __ch),isalpha,(__ch))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/ctype/isalpha.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_isalpha __LIBC_LOCAL_NAME(isalpha)
#endif /* !... */
#endif /* !__local___localdep_isalpha_defined */
__LOCAL_LIBC(basename) __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(basename))(char const *__filename) {
	/* >> char *slash = strrchr(filename, '/');
	 * >> return slash ? slash + 1 : (char *)filename; */
	char *__result, *__iter = (char *)__filename;
#ifdef _WIN32
	/* Skip drive letter. */
	if ((__NAMESPACE_LOCAL_SYM __localdep_isalpha)(__iter[0]) && __iter[1] == ':')
		__iter += 2;
#endif /* _WIN32 */
	__result = __iter;
	for (;;) {
		char __ch = *__iter++;
#ifdef _WIN32
		if (__ch == '/' || __ch == '\\')
#else /* _WIN32 */
		if (__ch == '/')
#endif /* !_WIN32 */
		{
			__result = __iter;
		}
		if (!__ch)
			break;
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_basename_defined
#define __local___localdep_basename_defined
#define __localdep_basename __LIBC_LOCAL_NAME(basename)
#endif /* !__local___localdep_basename_defined */
#endif /* !__local_basename_defined */
