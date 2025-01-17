/* HASH CRC-32:0x81365b1 */
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
#ifndef __local_llogbf_defined
#define __local_llogbf_defined
#include <__crt.h>
#include <hybrid/typecore.h>
#include <ieee754.h>
#if defined(__CRT_HAVE_ilogbf) || (defined(__CRT_HAVE_llogbf) && __SIZEOF_INT__ == __SIZEOF_LONG__) || defined(__CRT_HAVE___ilogbf) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_llogb) || defined(__CRT_HAVE_ilogb) || defined(__CRT_HAVE___ilogb) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_ilogbf_defined
#define __local___localdep_ilogbf_defined
#if __has_builtin(__builtin_ilogbf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_ilogbf)
__CEIREDIRECT(__ATTR_WUNUSED,int,__NOTHROW,__localdep_ilogbf,(float __x),ilogbf,{ return __builtin_ilogbf(__x); })
#elif defined(__CRT_HAVE_ilogbf)
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW,__localdep_ilogbf,(float __x),ilogbf,(__x))
#elif defined(__CRT_HAVE_llogbf) && __SIZEOF_INT__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW,__localdep_ilogbf,(float __x),llogbf,(__x))
#elif defined(__CRT_HAVE___ilogbf)
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW,__localdep_ilogbf,(float __x),__ilogbf,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_ilogb) || (defined(__CRT_HAVE_llogb) && __SIZEOF_INT__ == __SIZEOF_LONG__) || defined(__CRT_HAVE___ilogb) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_END
#include <libc/local/math/ilogbf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_ilogbf __LIBC_LOCAL_NAME(ilogbf)
#else /* ... */
#undef __local___localdep_ilogbf_defined
#endif /* !... */
#endif /* !__local___localdep_ilogbf_defined */
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
__LOCAL_LIBC(llogbf) __ATTR_WUNUSED long int
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(llogbf))(float __x) {
#if defined(__CRT_HAVE_ilogbf) || (defined(__CRT_HAVE_llogbf) && __SIZEOF_INT__ == __SIZEOF_LONG__) || defined(__CRT_HAVE___ilogbf) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_ilogb) || (defined(__CRT_HAVE_llogb) && __SIZEOF_INT__ == __SIZEOF_LONG__) || defined(__CRT_HAVE___ilogb) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)
	return (long int)(__NAMESPACE_LOCAL_SYM __localdep_ilogbf)(__x); /* TODO: support for sizeof(long) > sizeof(int) */
#else /* __CRT_HAVE_ilogbf || (__CRT_HAVE_llogbf && __SIZEOF_INT__ == __SIZEOF_LONG__) || __CRT_HAVE___ilogbf || __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __CRT_HAVE_ilogb || (__CRT_HAVE_llogb && __SIZEOF_INT__ == __SIZEOF_LONG__) || __CRT_HAVE___ilogb || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ */
	return (__NAMESPACE_LOCAL_SYM __localdep_llogb)((double)__x);
#endif /* !__CRT_HAVE_ilogbf && (!__CRT_HAVE_llogbf || __SIZEOF_INT__ != __SIZEOF_LONG__) && !__CRT_HAVE___ilogbf && !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__CRT_HAVE_ilogb && (!__CRT_HAVE_llogb || __SIZEOF_INT__ != __SIZEOF_LONG__) && !__CRT_HAVE___ilogb && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_llogbf_defined
#define __local___localdep_llogbf_defined
#define __localdep_llogbf __LIBC_LOCAL_NAME(llogbf)
#endif /* !__local___localdep_llogbf_defined */
#else /* __CRT_HAVE_ilogbf || (__CRT_HAVE_llogbf && __SIZEOF_INT__ == __SIZEOF_LONG__) || __CRT_HAVE___ilogbf || __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __CRT_HAVE_llogb || __CRT_HAVE_ilogb || __CRT_HAVE___ilogb || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ */
#undef __local_llogbf_defined
#endif /* !__CRT_HAVE_ilogbf && (!__CRT_HAVE_llogbf || __SIZEOF_INT__ != __SIZEOF_LONG__) && !__CRT_HAVE___ilogbf && !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__CRT_HAVE_llogb && !__CRT_HAVE_ilogb && !__CRT_HAVE___ilogb && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ */
#endif /* !__local_llogbf_defined */
