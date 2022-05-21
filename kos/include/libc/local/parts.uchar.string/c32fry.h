/* HASH CRC-32:0x73598924 */
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
#ifndef __local_c32fry_defined
#define __local_c32fry_defined
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_c32len_defined
#define __local___localdep_c32len_defined
#if defined(__CRT_HAVE_wcslen) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO(1),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c32len,(__CHAR32_TYPE__ const *__restrict __str),wcslen,(__str))
#elif defined(__CRT_HAVE_KOS$wcslen)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO(1),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c32len,(__CHAR32_TYPE__ const *__restrict __str),wcslen,(__str))
#elif __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcslen.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c32len __NAMESPACE_LOCAL_TYPEHAX(__SIZE_TYPE__(__LIBKCALL*)(__CHAR32_TYPE__ const *__restrict),__SIZE_TYPE__(__LIBKCALL&)(__CHAR32_TYPE__ const *__restrict),wcslen)
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.string/c32len.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c32len __LIBC_LOCAL_NAME(c32len)
#endif /* !... */
#endif /* !__local___localdep_c32len_defined */
#ifndef __local___localdep_rand_defined
#define __local___localdep_rand_defined
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
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(c32fry) __ATTR_LEAF __ATTR_ACCESS_RW(1) __CHAR32_TYPE__ *
__NOTHROW_NCX(__LIBKCALL __LIBC_LOCAL_NAME(c32fry))(__CHAR32_TYPE__ *__restrict __str) {
	__SIZE_TYPE__ __i, __count = (__NAMESPACE_LOCAL_SYM __localdep_c32len)(__str);
	for (__i = 0; __i < __count; ++__i) {
		__CHAR32_TYPE__ __temp;
		__SIZE_TYPE__ __j = (__NAMESPACE_LOCAL_SYM __localdep_rand)();
		__j = __i + (__j % (__count - __i));
		/* Swap these 2 characters. */
		__temp = __str[__i];
		__str[__i] = __str[__j];
		__str[__j] = __temp;
	}
	return __str;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c32fry_defined
#define __local___localdep_c32fry_defined
#define __localdep_c32fry __LIBC_LOCAL_NAME(c32fry)
#endif /* !__local___localdep_c32fry_defined */
#endif /* !__local_c32fry_defined */
