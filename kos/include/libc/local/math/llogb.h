/* HASH CRC-32:0xe2527072 */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_llogb_defined
#define __local_llogb_defined
#include <__crt.h>
#include <hybrid/typecore.h>
#include <ieee754.h>
#if defined(__CRT_HAVE_ilogb) || (defined(__CRT_HAVE_llogb) && __SIZEOF_INT__ == __SIZEOF_LONG__) || defined(__CRT_HAVE___ilogb) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_ilogb_defined
#define __local___localdep_ilogb_defined
#if __has_builtin(__builtin_ilogb) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_ilogb)
__CEIREDIRECT(__ATTR_WUNUSED,int,__NOTHROW,__localdep_ilogb,(double __x),ilogb,{ return __builtin_ilogb(__x); })
#elif defined(__CRT_HAVE_ilogb)
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW,__localdep_ilogb,(double __x),ilogb,(__x))
#elif defined(__CRT_HAVE_llogb) && __SIZEOF_INT__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW,__localdep_ilogb,(double __x),llogb,(__x))
#elif defined(__CRT_HAVE___ilogb)
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW,__localdep_ilogb,(double __x),__ilogb,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_END
#include <libc/local/math/ilogb.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_ilogb __LIBC_LOCAL_NAME(ilogb)
#else /* ... */
#undef __local___localdep_ilogb_defined
#endif /* !... */
#endif /* !__local___localdep_ilogb_defined */
__LOCAL_LIBC(llogb) __ATTR_WUNUSED long int
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(llogb))(double __x) {
	return (long int)(__NAMESPACE_LOCAL_SYM __localdep_ilogb)(__x); /* TODO: support for sizeof(long) > sizeof(int) */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_llogb_defined
#define __local___localdep_llogb_defined
#define __localdep_llogb __LIBC_LOCAL_NAME(llogb)
#endif /* !__local___localdep_llogb_defined */
#else /* __CRT_HAVE_ilogb || (__CRT_HAVE_llogb && __SIZEOF_INT__ == __SIZEOF_LONG__) || __CRT_HAVE___ilogb || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ */
#undef __local_llogb_defined
#endif /* !__CRT_HAVE_ilogb && (!__CRT_HAVE_llogb || __SIZEOF_INT__ != __SIZEOF_LONG__) && !__CRT_HAVE___ilogb && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ */
#endif /* !__local_llogb_defined */
