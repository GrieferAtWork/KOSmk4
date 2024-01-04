/* HASH CRC-32:0xfa9c649 */
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
#ifndef __local_strfry_defined
#define __local_strfry_defined
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
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
#ifndef __local___localdep_strlen_defined
#define __local___localdep_strlen_defined
#ifdef __CRT_HAVE_strlen
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_strlen,(char const *__restrict __str),strlen,(__str))
#else /* __CRT_HAVE_strlen */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strlen.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strlen __LIBC_LOCAL_NAME(strlen)
#endif /* !__CRT_HAVE_strlen */
#endif /* !__local___localdep_strlen_defined */
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(strfry) __ATTR_LEAF __ATTR_INOUT(1) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strfry))(char *__restrict __str) {
	__SIZE_TYPE__ __i, __count = (__NAMESPACE_LOCAL_SYM __localdep_strlen)(__str);
	for (__i = 0; __i < __count; ++__i) {
		char __temp;
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
#ifndef __local___localdep_strfry_defined
#define __local___localdep_strfry_defined
#define __localdep_strfry __LIBC_LOCAL_NAME(strfry)
#endif /* !__local___localdep_strfry_defined */
#endif /* !__local_strfry_defined */
