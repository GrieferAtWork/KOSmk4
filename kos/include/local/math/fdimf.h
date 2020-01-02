/* HASH CRC-32:0x45ce2144 */
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_fdimf_defined
#define __local_fdimf_defined 1
/* Dependency: "fabsf" from "math" */
#ifndef ____localdep_fabsf_defined
#define ____localdep_fabsf_defined 1
#if __has_builtin(__builtin_fabsf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fabsf)
/* Absolute value of X */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __localdep_fabsf)(float __x) { return __builtin_fabsf(__x); }
#elif defined(__CRT_HAVE_fabsf)
/* Absolute value of X */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__localdep_fabsf,(float __x),fabsf,(__x))
#elif defined(__CRT_HAVE___fabsf)
/* Absolute value of X */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__localdep_fabsf,(float __x),__fabsf,(__x))
#else /* LIBC: fabsf */
#include <local/math/fabsf.h>
/* Absolute value of X */
#define __localdep_fabsf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fabsf))
#endif /* fabsf... */
#endif /* !____localdep_fabsf_defined */

__NAMESPACE_LOCAL_BEGIN
/* Return positive difference between X and Y */
__LOCAL_LIBC(fdimf) __ATTR_CONST __ATTR_WUNUSED float
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(fdimf))(float __x,
                                               float __y) {
#line 527 "kos/src/libc/magic/math.c"
	return __localdep_fabsf(__y - __x);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_fdimf_defined */
