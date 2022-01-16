/* HASH CRC-32:0xa0e88f0a */
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
#ifndef __local_remquol_defined
#define __local_remquol_defined
#include <__crt.h>
#if defined(__CRT_HAVE_remquo) || defined(__CRT_HAVE___remquo)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_remquo_defined
#define __local___localdep_remquo_defined
#if __has_builtin(__builtin_remquo) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_remquo)
__CEIREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((3)),double,__NOTHROW,__localdep_remquo,(double __x, double __y, int *__pquo),remquo,{ return __builtin_remquo(__x, __y, __pquo); })
#elif defined(__CRT_HAVE_remquo)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((3)),double,__NOTHROW,__localdep_remquo,(double __x, double __y, int *__pquo),remquo,(__x,__y,__pquo))
#elif defined(__CRT_HAVE___remquo)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((3)),double,__NOTHROW,__localdep_remquo,(double __x, double __y, int *__pquo),__remquo,(__x,__y,__pquo))
#else /* ... */
#undef __local___localdep_remquo_defined
#endif /* !... */
#endif /* !__local___localdep_remquo_defined */
__LOCAL_LIBC(remquol) __ATTR_WUNUSED __ATTR_NONNULL((3)) __LONGDOUBLE
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(remquol))(__LONGDOUBLE __x, __LONGDOUBLE __y, int *__pquo) {
	return (__LONGDOUBLE)(__NAMESPACE_LOCAL_SYM __localdep_remquo)((double)__x, (double)__y, __pquo);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_remquol_defined
#define __local___localdep_remquol_defined
#define __localdep_remquol __LIBC_LOCAL_NAME(remquol)
#endif /* !__local___localdep_remquol_defined */
#else /* __CRT_HAVE_remquo || __CRT_HAVE___remquo */
#undef __local_remquol_defined
#endif /* !__CRT_HAVE_remquo && !__CRT_HAVE___remquo */
#endif /* !__local_remquol_defined */
