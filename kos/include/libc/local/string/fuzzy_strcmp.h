/* HASH CRC-32:0x3d3bc25a */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_fuzzy_strcmp_defined
#define __local_fuzzy_strcmp_defined
#include <__crt.h>
#include <parts/malloca.h>
#if defined(__CRT_HAVE_fuzzy_memcmp) || !defined(__NO_MALLOCA)
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_fuzzy_memcmp_defined
#define __local___localdep_fuzzy_memcmp_defined
#ifdef __CRT_HAVE_fuzzy_memcmp
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_fuzzy_memcmp,(void const *__s1, __SIZE_TYPE__ __s1_bytes, void const *__s2, __SIZE_TYPE__ __s2_bytes),fuzzy_memcmp,(__s1,__s1_bytes,__s2,__s2_bytes))
#elif !defined(__NO_MALLOCA)
__NAMESPACE_LOCAL_END
#include <libc/local/string/fuzzy_memcmp.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_fuzzy_memcmp __LIBC_LOCAL_NAME(fuzzy_memcmp)
#else /* ... */
#undef __local___localdep_fuzzy_memcmp_defined
#endif /* !... */
#endif /* !__local___localdep_fuzzy_memcmp_defined */
#ifndef __local___localdep_strlen_defined
#define __local___localdep_strlen_defined
#ifdef __CRT_HAVE_strlen
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_strlen,(char const *__restrict __str),strlen,(__str))
#else /* __CRT_HAVE_strlen */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strlen.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strlen __LIBC_LOCAL_NAME(strlen)
#endif /* !__CRT_HAVE_strlen */
#endif /* !__local___localdep_strlen_defined */
__LOCAL_LIBC(fuzzy_strcmp) __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(fuzzy_strcmp))(char const *__s1, char const *__s2) {
	return (__NAMESPACE_LOCAL_SYM __localdep_fuzzy_memcmp)(__s1, (__NAMESPACE_LOCAL_SYM __localdep_strlen)(__s1), __s2, (__NAMESPACE_LOCAL_SYM __localdep_strlen)(__s2));
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_fuzzy_strcmp_defined
#define __local___localdep_fuzzy_strcmp_defined
#define __localdep_fuzzy_strcmp __LIBC_LOCAL_NAME(fuzzy_strcmp)
#endif /* !__local___localdep_fuzzy_strcmp_defined */
#else /* __CRT_HAVE_fuzzy_memcmp || !__NO_MALLOCA */
#undef __local_fuzzy_strcmp_defined
#endif /* !__CRT_HAVE_fuzzy_memcmp && __NO_MALLOCA */
#endif /* !__local_fuzzy_strcmp_defined */
