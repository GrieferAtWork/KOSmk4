/* HASH 0x1557bc06 */
/* Copyright (c) 2019 Griefer@Work                                            *
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
#ifndef __local_finitef_defined
#define __local_finitef_defined 1
/* Dependency: "isinff" from "math" */
#ifndef ____localdep_isinff_defined
#define ____localdep_isinff_defined 1
#if __has_builtin(__builtin_isinff) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isinff)
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST int __NOTHROW(__LIBCCALL __localdep_isinff)(float __val) { return __builtin_isinff(__val); }
#elif defined(__CRT_HAVE_isinff)
__CREDIRECT(__ATTR_WUNUSED __ATTR_CONST,int,__NOTHROW,__localdep_isinff,(float __val),isinff,(__val))
#elif defined(__CRT_HAVE___isinff)
__CREDIRECT(__ATTR_WUNUSED __ATTR_CONST,int,__NOTHROW,__localdep_isinff,(float __val),__isinff,(__val))
#else /* LIBC: isinff */
#include <local/math/isinff.h>
#define __localdep_isinff (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isinff))
#endif /* isinff... */
#endif /* !____localdep_isinff_defined */

/* Dependency: "isnanf" from "math" */
#ifndef ____localdep_isnanf_defined
#define ____localdep_isnanf_defined 1
#if __has_builtin(__builtin_isnanf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isnanf)
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST int __NOTHROW(__LIBCCALL __localdep_isnanf)(float __val) { return __builtin_isnanf(__val); }
#elif defined(__CRT_HAVE_isnanf)
__CREDIRECT(__ATTR_WUNUSED __ATTR_CONST,int,__NOTHROW,__localdep_isnanf,(float __val),isnanf,(__val))
#elif defined(__CRT_HAVE___isnanf)
__CREDIRECT(__ATTR_WUNUSED __ATTR_CONST,int,__NOTHROW,__localdep_isnanf,(float __val),__isnanf,(__val))
#else /* LIBC: isnanf */
#include <local/math/isnanf.h>
#define __localdep_isnanf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isnanf))
#endif /* isnanf... */
#endif /* !____localdep_isnanf_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(finitef) __ATTR_WUNUSED __ATTR_CONST int
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(finitef))(float __val) {
#line 833 "kos/src/libc/magic/math.c"
	return !__localdep_isinff(__val) && !__localdep_isnanf(__val);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_finitef_defined */
