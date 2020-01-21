/* HASH CRC-32:0x1225d65b */
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_fdim_defined
#define __local_fdim_defined 1
#include <libm/fabs.h>
/* Dependency: "fabs" from "math" */
#ifndef ____localdep_fabs_defined
#define ____localdep_fabs_defined 1
#if __has_builtin(__builtin_fabs) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fabs)
/* Absolute value of X */
__EXTERNINLINE __ATTR_CONST __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __localdep_fabs)(double __x) { return __builtin_fabs(__x); }
#elif defined(__CRT_HAVE_fabs)
/* Absolute value of X */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__localdep_fabs,(double __x),fabs,(__x))
#elif defined(__CRT_HAVE___fabs)
/* Absolute value of X */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__localdep_fabs,(double __x),__fabs,(__x))
#else /* LIBC: fabs */
#include <local/math/fabs.h>
/* Absolute value of X */
#define __localdep_fabs (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fabs))
#endif /* fabs... */
#endif /* !____localdep_fabs_defined */

__NAMESPACE_LOCAL_BEGIN
/* Return positive difference between X and Y */
__LOCAL_LIBC(fdim) __ATTR_CONST __ATTR_WUNUSED double
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(fdim))(double __x,
                                              double __y) {
#line 946 "kos/src/libc/magic/math.c"
	return __localdep_fabs(__y - __x);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_fdim_defined */
