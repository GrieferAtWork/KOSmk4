/* HASH CRC-32:0xc431e56e */
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
#ifndef __local_llroundf_defined
#define __local_llroundf_defined
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_roundf_defined
#define __local___localdep_roundf_defined
#if __has_builtin(__builtin_roundf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_roundf)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__localdep_roundf,(float __x),roundf,{ return __builtin_roundf(__x); })
#elif defined(__CRT_HAVE_roundf)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__localdep_roundf,(float __x),roundf,(__x))
#elif defined(__CRT_HAVE___roundf)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__localdep_roundf,(float __x),__roundf,(__x))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/math/roundf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_roundf __LIBC_LOCAL_NAME(roundf)
#endif /* !... */
#endif /* !__local___localdep_roundf_defined */
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
#include <libm/lround.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(llroundf) __ATTR_CONST __ATTR_WUNUSED __LONGLONG
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(llroundf))(float __x) {
#ifdef __LIBM_MATHFUNIF
	return __LIBM_MATHFUNIF(llround, __x);
#else /* __LIBM_MATHFUNIF */
	return (__LONGLONG)(__NAMESPACE_LOCAL_SYM __localdep_roundf)(__x);
#endif /* !__LIBM_MATHFUNIF */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_llroundf_defined
#define __local___localdep_llroundf_defined
#define __localdep_llroundf __LIBC_LOCAL_NAME(llroundf)
#endif /* !__local___localdep_llroundf_defined */
#endif /* !__local_llroundf_defined */
