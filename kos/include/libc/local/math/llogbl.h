/* HASH CRC-32:0x8f3f553 */
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
#ifndef __local_llogbl_defined
#define __local_llogbl_defined
#include <__crt.h>
#include <hybrid/typecore.h>
#include <ieee754.h>
#if defined(__CRT_HAVE_ilogbl) || (defined(__CRT_HAVE_llogbl) && __SIZEOF_INT__ == __SIZEOF_LONG__) || defined(__CRT_HAVE___ilogbl) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_llogb) || defined(__CRT_HAVE_ilogb) || defined(__CRT_HAVE___ilogb) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_ilogbl_defined
#define __local___localdep_ilogbl_defined
#if __has_builtin(__builtin_ilogbl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_ilogbl)
__CEIREDIRECT(__ATTR_WUNUSED,int,__NOTHROW,__localdep_ilogbl,(__LONGDOUBLE __x),ilogbl,{ return __builtin_ilogbl(__x); })
#elif defined(__CRT_HAVE_ilogbl)
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW,__localdep_ilogbl,(__LONGDOUBLE __x),ilogbl,(__x))
#elif defined(__CRT_HAVE_llogb) && __SIZEOF_INT__ == __SIZEOF_LONG__ && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW,__localdep_ilogbl,(__LONGDOUBLE __x),llogb,(__x))
#elif defined(__CRT_HAVE_llogbl) && __SIZEOF_INT__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW,__localdep_ilogbl,(__LONGDOUBLE __x),llogbl,(__x))
#elif defined(__CRT_HAVE___ilogbl)
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW,__localdep_ilogbl,(__LONGDOUBLE __x),__ilogbl,(__x))
#elif defined(__CRT_HAVE_ilogb) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW,__localdep_ilogbl,(__LONGDOUBLE __x),ilogb,(__x))
#elif defined(__CRT_HAVE___ilogb) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW,__localdep_ilogbl,(__LONGDOUBLE __x),__ilogb,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_ilogb) || (defined(__CRT_HAVE_llogb) && __SIZEOF_INT__ == __SIZEOF_LONG__) || defined(__CRT_HAVE___ilogb) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_END
#include <libc/local/math/ilogbl.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_ilogbl __LIBC_LOCAL_NAME(ilogbl)
#else /* ... */
#undef __local___localdep_ilogbl_defined
#endif /* !... */
#endif /* !__local___localdep_ilogbl_defined */
#ifndef __local___localdep_llogb_defined
#define __local___localdep_llogb_defined
#ifdef __CRT_HAVE_llogb
__CREDIRECT(__ATTR_WUNUSED,long int,__NOTHROW,__localdep_llogb,(double __x),llogb,(__x))
#elif defined(__CRT_HAVE_ilogb) && __SIZEOF_INT__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_WUNUSED,long int,__NOTHROW,__localdep_llogb,(double __x),ilogb,(__x))
#elif defined(__CRT_HAVE_ilogb) || defined(__CRT_HAVE___ilogb) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_END
#include <libc/local/math/llogb.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_llogb __LIBC_LOCAL_NAME(llogb)
#else /* ... */
#undef __local___localdep_llogb_defined
#endif /* !... */
#endif /* !__local___localdep_llogb_defined */
__LOCAL_LIBC(llogbl) __ATTR_WUNUSED long int
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(llogbl))(__LONGDOUBLE __x) {
#if defined(__CRT_HAVE_ilogbl) || (defined(__CRT_HAVE_llogbl) && __SIZEOF_INT__ == __SIZEOF_LONG__) || defined(__CRT_HAVE___ilogbl) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_ilogb) || (defined(__CRT_HAVE_llogb) && __SIZEOF_INT__ == __SIZEOF_LONG__) || defined(__CRT_HAVE___ilogb) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)
	return (long int)(__NAMESPACE_LOCAL_SYM __localdep_ilogbl)(__x); /* TODO: support for sizeof(long) > sizeof(int) */
#else /* __CRT_HAVE_ilogbl || (__CRT_HAVE_llogbl && __SIZEOF_INT__ == __SIZEOF_LONG__) || __CRT_HAVE___ilogbl || __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __CRT_HAVE_ilogb || (__CRT_HAVE_llogb && __SIZEOF_INT__ == __SIZEOF_LONG__) || __CRT_HAVE___ilogb || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ */
	return (__NAMESPACE_LOCAL_SYM __localdep_llogb)((double)__x);
#endif /* !__CRT_HAVE_ilogbl && (!__CRT_HAVE_llogbl || __SIZEOF_INT__ != __SIZEOF_LONG__) && !__CRT_HAVE___ilogbl && !__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ && !__CRT_HAVE_ilogb && (!__CRT_HAVE_llogb || __SIZEOF_INT__ != __SIZEOF_LONG__) && !__CRT_HAVE___ilogb && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_llogbl_defined
#define __local___localdep_llogbl_defined
#define __localdep_llogbl __LIBC_LOCAL_NAME(llogbl)
#endif /* !__local___localdep_llogbl_defined */
#else /* __CRT_HAVE_ilogbl || (__CRT_HAVE_llogbl && __SIZEOF_INT__ == __SIZEOF_LONG__) || __CRT_HAVE___ilogbl || __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __CRT_HAVE_llogb || __CRT_HAVE_ilogb || __CRT_HAVE___ilogb || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ */
#undef __local_llogbl_defined
#endif /* !__CRT_HAVE_ilogbl && (!__CRT_HAVE_llogbl || __SIZEOF_INT__ != __SIZEOF_LONG__) && !__CRT_HAVE___ilogbl && !__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ && !__CRT_HAVE_llogb && !__CRT_HAVE_ilogb && !__CRT_HAVE___ilogb && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ */
#endif /* !__local_llogbl_defined */
