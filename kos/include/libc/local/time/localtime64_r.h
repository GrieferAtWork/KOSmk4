/* HASH CRC-32:0xbe521a4d */
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
#ifndef __local_localtime64_r_defined
#define __local_localtime64_r_defined
#include <__crt.h>
#include <bits/types.h>
#include <bits/crt/tm.h>
__NAMESPACE_LOCAL_BEGIN
#if !defined(__local___localdep_crt_localtime64_s_defined) && defined(__CRT_HAVE__localtime64_s)
#define __local___localdep_crt_localtime64_s_defined
__CREDIRECT(__ATTR_IN(2) __ATTR_OUT(1),__errno_t,__NOTHROW_NCX,__localdep_crt_localtime64_s,(struct __NAMESPACE_STD_SYM tm *__restrict __tp, __time64_t const *__restrict __timer),_localtime64_s,(__tp,__timer))
#endif /* !__local___localdep_crt_localtime64_s_defined && __CRT_HAVE__localtime64_s */
#ifndef __local___localdep_gmtime64_r_defined
#define __local___localdep_gmtime64_r_defined
#if defined(__CRT_HAVE_gmtime_r) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,__localdep_gmtime64_r,(__time64_t const *__restrict __timer, struct __NAMESPACE_STD_SYM tm *__restrict __tp),gmtime_r,(__timer,__tp))
#elif defined(__CRT_HAVE_gmtime64_r)
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,__localdep_gmtime64_r,(__time64_t const *__restrict __timer, struct __NAMESPACE_STD_SYM tm *__restrict __tp),gmtime64_r,(__timer,__tp))
#elif defined(__CRT_HAVE___gmtime64_r)
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,__localdep_gmtime64_r,(__time64_t const *__restrict __timer, struct __NAMESPACE_STD_SYM tm *__restrict __tp),__gmtime64_r,(__timer,__tp))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/time/gmtime64_r.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_gmtime64_r __LIBC_LOCAL_NAME(gmtime64_r)
#endif /* !... */
#endif /* !__local___localdep_gmtime64_r_defined */
__LOCAL_LIBC(localtime64_r) __ATTR_IN(1) __ATTR_OUT(2) struct __NAMESPACE_STD_SYM tm *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(localtime64_r))(__time64_t const *__restrict __timer, struct __NAMESPACE_STD_SYM tm *__restrict __tp) {
#ifdef __CRT_HAVE__localtime64_s
	return (__NAMESPACE_LOCAL_SYM __localdep_crt_localtime64_s)(__tp, __timer) ? __NULLPTR : __tp;
#else /* __CRT_HAVE__localtime64_s */
	/* XXX: Timezone support? */
	return (__NAMESPACE_LOCAL_SYM __localdep_gmtime64_r)(__timer, __tp);
#endif /* !__CRT_HAVE__localtime64_s */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_localtime64_r_defined
#define __local___localdep_localtime64_r_defined
#define __localdep_localtime64_r __LIBC_LOCAL_NAME(localtime64_r)
#endif /* !__local___localdep_localtime64_r_defined */
#endif /* !__local_localtime64_r_defined */
