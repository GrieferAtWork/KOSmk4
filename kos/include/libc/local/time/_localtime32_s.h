/* HASH CRC-32:0x913a1df4 */
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
#ifndef __local__localtime32_s_defined
#define __local__localtime32_s_defined
#include <__crt.h>
#include <bits/types.h>
#include <bits/crt/tm.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_localtime_r_defined
#define __local___localdep_localtime_r_defined
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__CRT_HAVE_localtime_r) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__CREDIRECT(__ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR(2),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,__localdep_localtime_r,(__TM_TYPE(time) const *__restrict __timer, struct __NAMESPACE_STD_SYM tm *__restrict __tp),localtime_r,(__timer,__tp))
#elif defined(__CRT_HAVE_localtime64_r) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__CREDIRECT(__ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR(2),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,__localdep_localtime_r,(__TM_TYPE(time) const *__restrict __timer, struct __NAMESPACE_STD_SYM tm *__restrict __tp),localtime64_r,(__timer,__tp))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/time/localtime_r.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_localtime_r __LIBC_LOCAL_NAME(localtime_r)
#endif /* !... */
#endif /* !__local___localdep_localtime_r_defined */
__NAMESPACE_LOCAL_END
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_localtime32_s) __ATTR_ACCESS_RO(2) __ATTR_ACCESS_WR(1) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_localtime32_s))(struct __NAMESPACE_STD_SYM tm *__restrict __tp, __time32_t const *__restrict __timer) {
#if !defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__



	if __unlikely(!(__NAMESPACE_LOCAL_SYM __localdep_localtime_r)(__timer, __tp))
		return __libc_geterrno_or(1);

#else /* !__USE_TIME_BITS64 || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
	__TM_TYPE(time) __ttimer = (__TM_TYPE(time))*__timer;



	if __unlikely(!(__NAMESPACE_LOCAL_SYM __localdep_localtime_r)(&__ttimer, __tp))
		return __libc_geterrno_or(1);

#endif /* __USE_TIME_BITS64 && __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__localtime32_s_defined
#define __local___localdep__localtime32_s_defined
#define __localdep__localtime32_s __LIBC_LOCAL_NAME(_localtime32_s)
#endif /* !__local___localdep__localtime32_s_defined */
#endif /* !__local__localtime32_s_defined */
