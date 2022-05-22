/* HASH CRC-32:0x6d36246d */
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
#ifndef __local__dtest_defined
#define __local__dtest_defined
#include <__crt.h>
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep___fpclassify_defined
#define __local___localdep___fpclassify_defined
#ifdef __CRT_HAVE___fpclassify
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep___fpclassify,(double __x),__fpclassify,(__x))
#elif defined(__CRT_HAVE_fpclassify)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep___fpclassify,(double __x),fpclassify,(__x))
#elif defined(__CRT_HAVE__dclass)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep___fpclassify,(double __x),_dclass,(__x))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <ieee754.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_END
#include <libc/local/math/__fpclassify.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep___fpclassify __LIBC_LOCAL_NAME(__fpclassify)
#else /* __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#undef __local___localdep___fpclassify_defined
#endif /* !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#endif /* !... */
#endif /* !__local___localdep___fpclassify_defined */
__LOCAL_LIBC(_dtest) __ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO(1) short
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_dtest))(double __KOS_FIXED_CONST *__px) {
	return (__NAMESPACE_LOCAL_SYM __localdep___fpclassify)(*__px);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__dtest_defined
#define __local___localdep__dtest_defined
#define __localdep__dtest __LIBC_LOCAL_NAME(_dtest)
#endif /* !__local___localdep__dtest_defined */
#endif /* !__local__dtest_defined */
