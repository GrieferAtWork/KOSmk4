/* HASH CRC-32:0xec4285b1 */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_wcsfry_defined
#define __local_wcsfry_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: rand from stdlib */
#ifndef __local___localdep_rand_defined
#define __local___localdep_rand_defined 1
#ifdef __CRT_HAVE_rand
__CREDIRECT(,int,__NOTHROW,__localdep_rand,(void),rand,())
#else /* __CRT_HAVE_rand */
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__CRT_HAVE_random) && __SIZEOF_INT__ == __SIZEOF_LONG__
__CREDIRECT(,int,__NOTHROW,__localdep_rand,(void),random,())
#else /* __CRT_HAVE_random && __SIZEOF_INT__ == __SIZEOF_LONG__ */
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/rand.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_rand __LIBC_LOCAL_NAME(rand)
#endif /* !__CRT_HAVE_random || __SIZEOF_INT__ != __SIZEOF_LONG__ */
#endif /* !__CRT_HAVE_rand */
#endif /* !__local___localdep_rand_defined */
/* Dependency: wcslen from wchar */
#ifndef __local___localdep_wcslen_defined
#define __local___localdep_wcslen_defined 1
#ifdef __CRT_HAVE_wcslen
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* >> strlen(3)
 * Return the length of the string in characters (Same as `rawmemlen[...](str, '\0')') */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_wcslen,(__WCHAR_TYPE__ const *__restrict __str),wcslen,(__str))
#else /* __CRT_HAVE_wcslen */
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcslen.h>
__NAMESPACE_LOCAL_BEGIN
/* >> strlen(3)
 * Return the length of the string in characters (Same as `rawmemlen[...](str, '\0')') */
#define __localdep_wcslen __LIBC_LOCAL_NAME(wcslen)
#endif /* !__CRT_HAVE_wcslen */
#endif /* !__local___localdep_wcslen_defined */
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* >> strfry(3) */
__LOCAL_LIBC(wcsfry) __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) __WCHAR_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(wcsfry))(__WCHAR_TYPE__ *__restrict __str) {
	__SIZE_TYPE__ __i, __count = __localdep_wcslen(__str);
	for (__i = 0; __i < __count; ++__i) {
		__WCHAR_TYPE__ __temp;
		__SIZE_TYPE__ __j = __localdep_rand();
		__j = __i + (__j % (__count - __i));
		/* Swap these 2 characters. */
		__temp = __str[__i];
		__str[__i] = __str[__j];
		__str[__j] = __temp;
	}
	return __str;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_wcsfry_defined
#define __local___localdep_wcsfry_defined 1
#define __localdep_wcsfry __LIBC_LOCAL_NAME(wcsfry)
#endif /* !__local___localdep_wcsfry_defined */
#endif /* !__local_wcsfry_defined */
