/* HASH CRC-32:0x6f753464 */
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
#ifndef __local__mbsnbicoll_defined
#define __local__mbsnbicoll_defined
#include <__crt.h>
#if defined(__CRT_HAVE__mbsnbicoll_l) || defined(__CRT_HAVE__mbsnbicmp_l) || ((defined(__CRT_HAVE__ismbblead_l) || defined(__CRT_HAVE__mbctype) || defined(__CRT_HAVE___p__mbctype)) && (defined(__CRT_HAVE__mbctolower_l) || (defined(__CRT_HAVE__mbctouni_l) && defined(__CRT_HAVE__unitombc_l) && defined(__CRT_HAVE___unicode_descriptor)) || ((defined(__CRT_HAVE__mbctype) || defined(__CRT_HAVE___p__mbctype)) && (defined(__CRT_HAVE__mbcasemap) || defined(__CRT_HAVE___p__mbcasemap)))))
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__mbsnbicoll_l_defined
#define __local___localdep__mbsnbicoll_l_defined
#ifdef __CRT_HAVE__mbsnbicoll_l
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep__mbsnbicoll_l,(unsigned char const *__lhs, unsigned char const *__rhs, __SIZE_TYPE__ __max_bytes, __locale_t __locale),_mbsnbicoll_l,(__lhs,__rhs,__max_bytes,__locale))
#elif defined(__CRT_HAVE__mbsnbicmp_l) || ((defined(__CRT_HAVE__ismbblead_l) || defined(__CRT_HAVE__mbctype) || defined(__CRT_HAVE___p__mbctype)) && (defined(__CRT_HAVE__mbctolower_l) || (defined(__CRT_HAVE__mbctouni_l) && defined(__CRT_HAVE__unitombc_l) && defined(__CRT_HAVE___unicode_descriptor)) || ((defined(__CRT_HAVE__mbctype) || defined(__CRT_HAVE___p__mbctype)) && (defined(__CRT_HAVE__mbcasemap) || defined(__CRT_HAVE___p__mbcasemap)))))
__NAMESPACE_LOCAL_END
#include <libc/local/mbstring/_mbsnbicoll_l.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__mbsnbicoll_l __LIBC_LOCAL_NAME(_mbsnbicoll_l)
#else /* ... */
#undef __local___localdep__mbsnbicoll_l_defined
#endif /* !... */
#endif /* !__local___localdep__mbsnbicoll_l_defined */
__LOCAL_LIBC(_mbsnbicoll) __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_mbsnbicoll))(unsigned char const *__lhs, unsigned char const *__rhs, __SIZE_TYPE__ __max_bytes) {
	return (__NAMESPACE_LOCAL_SYM __localdep__mbsnbicoll_l)(__lhs, __rhs, __max_bytes, __NULLPTR);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__mbsnbicoll_defined
#define __local___localdep__mbsnbicoll_defined
#define __localdep__mbsnbicoll __LIBC_LOCAL_NAME(_mbsnbicoll)
#endif /* !__local___localdep__mbsnbicoll_defined */
#else /* __CRT_HAVE__mbsnbicoll_l || __CRT_HAVE__mbsnbicmp_l || ((__CRT_HAVE__ismbblead_l || __CRT_HAVE__mbctype || __CRT_HAVE___p__mbctype) && (__CRT_HAVE__mbctolower_l || (__CRT_HAVE__mbctouni_l && __CRT_HAVE__unitombc_l && __CRT_HAVE___unicode_descriptor) || ((__CRT_HAVE__mbctype || __CRT_HAVE___p__mbctype) && (__CRT_HAVE__mbcasemap || __CRT_HAVE___p__mbcasemap)))) */
#undef __local__mbsnbicoll_defined
#endif /* !__CRT_HAVE__mbsnbicoll_l && !__CRT_HAVE__mbsnbicmp_l && ((!__CRT_HAVE__ismbblead_l && !__CRT_HAVE__mbctype && !__CRT_HAVE___p__mbctype) || (!__CRT_HAVE__mbctolower_l && (!__CRT_HAVE__mbctouni_l || !__CRT_HAVE__unitombc_l || !__CRT_HAVE___unicode_descriptor) && ((!__CRT_HAVE__mbctype && !__CRT_HAVE___p__mbctype) || (!__CRT_HAVE__mbcasemap && !__CRT_HAVE___p__mbcasemap)))) */
#endif /* !__local__mbsnbicoll_defined */
