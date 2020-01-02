/* HASH CRC-32:0xea62fa0 */
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
#ifndef __local_finitel_defined
#define __local_finitel_defined 1
/* Dependency: "isinfl" from "math" */
#ifndef ____localdep_isinfl_defined
#define ____localdep_isinfl_defined 1
#if __has_builtin(__builtin_isinfl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isinfl)
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __localdep_isinfl)(long double __val) { return __builtin_isinfl(__val); }
#elif defined(__CRT_HAVE_isinfl)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isinfl,(long double __val),isinfl,(__val))
#elif defined(__CRT_HAVE___isinfl)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isinfl,(long double __val),__isinfl,(__val))
#elif defined(__CRT_HAVE___isinf) && (__SIZEOF_LONG_DOUBLE__ == __SIZEOF_DOUBLE__)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isinfl,(long double __val),__isinf,(__val))
#elif defined(__CRT_HAVE_isinf) && (__SIZEOF_LONG_DOUBLE__ == __SIZEOF_DOUBLE__)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isinfl,(long double __val),isinf,(__val))
#else /* LIBC: isinfl */
#include <local/math/isinfl.h>
#define __localdep_isinfl (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isinfl))
#endif /* isinfl... */
#endif /* !____localdep_isinfl_defined */

/* Dependency: "isnanl" from "math" */
#ifndef ____localdep_isnanl_defined
#define ____localdep_isnanl_defined 1
#if __has_builtin(__builtin_isnanl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isnanl)
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __localdep_isnanl)(long double __val) { return __builtin_isnanl(__val); }
#elif defined(__CRT_HAVE_isnanl)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isnanl,(long double __val),isnanl,(__val))
#elif defined(__CRT_HAVE___isnanl)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isnanl,(long double __val),__isnanl,(__val))
#elif defined(__CRT_HAVE___isnan) && (__SIZEOF_LONG_DOUBLE__ == __SIZEOF_DOUBLE__)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isnanl,(long double __val),__isnan,(__val))
#elif defined(__CRT_HAVE__isnan) && (__SIZEOF_LONG_DOUBLE__ == __SIZEOF_DOUBLE__)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isnanl,(long double __val),_isnan,(__val))
#elif defined(__CRT_HAVE_isnan) && (__SIZEOF_LONG_DOUBLE__ == __SIZEOF_DOUBLE__)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isnanl,(long double __val),isnan,(__val))
#else /* LIBC: isnanl */
#include <local/math/isnanl.h>
#define __localdep_isnanl (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isnanl))
#endif /* isnanl... */
#endif /* !____localdep_isnanl_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(finitel) __ATTR_CONST __ATTR_WUNUSED int
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(finitel))(long double __val) {
#line 843 "kos/src/libc/magic/math.c"
	return !__localdep_isinfl(__val) && !__localdep_isnanl(__val);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_finitel_defined */
