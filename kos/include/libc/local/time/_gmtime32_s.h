/* HASH CRC-32:0x3c9bd89c */
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
#ifndef __local__gmtime32_s_defined
#define __local__gmtime32_s_defined
#include <__crt.h>
#include <bits/types.h>
#include <bits/crt/tm.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_gmtime_r_defined
#define __local___localdep_gmtime_r_defined
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__CRT_HAVE_gmtime_r) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,__localdep_gmtime_r,(__time_t const *__restrict __timer, struct __NAMESPACE_STD_SYM tm *__restrict __tp),gmtime_r,(__timer,__tp))
#elif defined(__CRT_HAVE___gmtime_r) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,__localdep_gmtime_r,(__time_t const *__restrict __timer, struct __NAMESPACE_STD_SYM tm *__restrict __tp),__gmtime_r,(__timer,__tp))
#elif defined(__CRT_HAVE_gmtime64_r) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,__localdep_gmtime_r,(__time_t const *__restrict __timer, struct __NAMESPACE_STD_SYM tm *__restrict __tp),gmtime64_r,(__timer,__tp))
#elif defined(__CRT_HAVE___gmtime64_r) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,__localdep_gmtime_r,(__time_t const *__restrict __timer, struct __NAMESPACE_STD_SYM tm *__restrict __tp),__gmtime64_r,(__timer,__tp))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/time/gmtime_r.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_gmtime_r __LIBC_LOCAL_NAME(gmtime_r)
#endif /* !... */
#endif /* !__local___localdep_gmtime_r_defined */
__NAMESPACE_LOCAL_END
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_gmtime32_s) __ATTR_IN(2) __ATTR_OUT(1) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_gmtime32_s))(struct __NAMESPACE_STD_SYM tm *__restrict __tp, __time32_t const *__restrict __timer) {
#if !defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__



	if __unlikely(!(__NAMESPACE_LOCAL_SYM __localdep_gmtime_r)(__timer, __tp))
		return __libc_geterrno_or(1);

#else /* !__USE_TIME_BITS64 || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
	__time_t __ttimer = (__time_t)*__timer;



	if __unlikely(!(__NAMESPACE_LOCAL_SYM __localdep_gmtime_r)(&__ttimer, __tp))
		return __libc_geterrno_or(1);

#endif /* __USE_TIME_BITS64 && __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__gmtime32_s_defined
#define __local___localdep__gmtime32_s_defined
#define __localdep__gmtime32_s __LIBC_LOCAL_NAME(_gmtime32_s)
#endif /* !__local___localdep__gmtime32_s_defined */
#endif /* !__local__gmtime32_s_defined */
