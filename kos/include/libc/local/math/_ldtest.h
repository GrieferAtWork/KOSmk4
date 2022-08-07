/* HASH CRC-32:0x21a83dfe */
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
#ifndef __local__ldtest_defined
#define __local__ldtest_defined
#include <__crt.h>
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep___fpclassifyl_defined
#define __local___localdep___fpclassifyl_defined
#ifdef __CRT_HAVE___fpclassifyl
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep___fpclassifyl,(__LONGDOUBLE __x),__fpclassifyl,(__x))
#elif defined(__CRT_HAVE_fpclassifyl)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep___fpclassifyl,(__LONGDOUBLE __x),fpclassifyl,(__x))
#elif defined(__CRT_HAVE__ldclass)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep___fpclassifyl,(__LONGDOUBLE __x),_ldclass,(__x))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__CRT_HAVE___fpclassify) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep___fpclassifyl,(__LONGDOUBLE __x),__fpclassify,(__x))
#elif defined(__CRT_HAVE_fpclassify) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep___fpclassifyl,(__LONGDOUBLE __x),fpclassify,(__x))
#elif defined(__CRT_HAVE__dclass) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep___fpclassifyl,(__LONGDOUBLE __x),_dclass,(__x))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <ieee754.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE___fpclassify) || defined(__CRT_HAVE_fpclassify) || defined(__CRT_HAVE__dclass) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_END
#include <libc/local/math/__fpclassifyl.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep___fpclassifyl __LIBC_LOCAL_NAME(__fpclassifyl)
#else /* __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __CRT_HAVE___fpclassify || __CRT_HAVE_fpclassify || __CRT_HAVE__dclass || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#undef __local___localdep___fpclassifyl_defined
#endif /* !__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__CRT_HAVE___fpclassify && !__CRT_HAVE_fpclassify && !__CRT_HAVE__dclass && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#endif /* !... */
#endif /* !... */
#endif /* !__local___localdep___fpclassifyl_defined */
__LOCAL_LIBC(_ldtest) __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) short
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_ldtest))(__LONGDOUBLE __KOS_FIXED_CONST *__px) {
	return (__NAMESPACE_LOCAL_SYM __localdep___fpclassifyl)(*__px);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__ldtest_defined
#define __local___localdep__ldtest_defined
#define __localdep__ldtest __LIBC_LOCAL_NAME(_ldtest)
#endif /* !__local___localdep__ldtest_defined */
#endif /* !__local__ldtest_defined */
