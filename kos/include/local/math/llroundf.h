/* HASH CRC-32:0xb93a20f6 */
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
#ifndef __local_llroundf_defined
#define __local_llroundf_defined 1
/* Dependency: "roundf" from "math" */
#ifndef ____localdep_roundf_defined
#define ____localdep_roundf_defined 1
#if __has_builtin(__builtin_roundf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_roundf)
/* Round X to nearest integral value, rounding halfway cases away from zero */
__EXTERNINLINE __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __localdep_roundf)(float __x) { return __builtin_roundf(__x); }
#elif defined(__CRT_HAVE_roundf)
/* Round X to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__localdep_roundf,(float __x),roundf,(__x))
#elif defined(__CRT_HAVE___roundf)
/* Round X to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__localdep_roundf,(float __x),__roundf,(__x))
#else /* LIBC: roundf */
#include <local/math/roundf.h>
/* Round X to nearest integral value, rounding halfway cases away from zero */
#define __localdep_roundf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(roundf))
#endif /* roundf... */
#endif /* !____localdep_roundf_defined */

__NAMESPACE_LOCAL_BEGIN
/* Round X to nearest integral value, rounding halfway cases away from zero */
__LOCAL_LIBC(llroundf) __ATTR_CONST __ATTR_WUNUSED __LONGLONG
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(llroundf))(float __x) {
#line 610 "kos/src/libc/magic/math.c"
	return (__LONGLONG)__localdep_roundf(__x);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_llroundf_defined */
